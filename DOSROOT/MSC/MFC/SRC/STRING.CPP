// This is a part of the Microsoft Foundation Classes C++ library. 
// Copyright (C) 1992 Microsoft Corporation 
// All rights reserved. 
//  
// This source code is only intended as a supplement to the 
// Microsoft Foundation Classes Reference and Microsoft 
// QuickHelp documentation provided with the library. 
// See these sources for detailed information regarding the 
// Microsoft Foundation Classes product. 


#include "afx.h"
#pragma hdrstop
#include <limits.h>

#ifdef AFX_CORE_SEG
#pragma code_seg(AFX_CORE_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// static class data, special inlines

char _afxChNil = '\0';

// For an empty string, m_???Data will point here
// (note: avoids a lot of NULL pointer tests when we call standard
//  C runtime libraries

extern const CString NEAR afxEmptyString;
const CString NEAR afxEmptyString;

void CString::Init()
{
	m_nDataLength = m_nAllocLength = 0;
	m_pchData = &_afxChNil;
}

//////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

CString::CString()
{
	Init();
}

CString::CString(const CString& stringSrc)
{
	// if constructing a CString from another CString, we make a copy of the
	// original string data to enforce value semantics (i.e. each string
	// gets a copy of it's own

	stringSrc.AllocCopy(*this, stringSrc.m_nDataLength, 0, 0);
}

void CString::AllocBuffer(int nLen)
 // always allocate one extra character for '\0' termination
 // assumes [optimistically] that data length will equal allocation length
{
	ASSERT(nLen >= 0);
	ASSERT(nLen < INT_MAX - 1); // max size (enough room for 1 extra)

	if (nLen == 0)
	{
		Init();
	}
	else
	{
		m_pchData = new char[nLen+1];       // may throw an exception
		m_pchData[nLen] = '\0';
		m_nDataLength = nLen;
		m_nAllocLength = nLen;
	}
}

void CString::Empty()
{
	if (m_pchData != &_afxChNil)
	{
		delete [] m_pchData;
		Init();
	}
	ASSERT(m_nDataLength == 0);
	ASSERT(m_nAllocLength == 0);
}

CString::~CString()
 //  free any attached data
{
	if (m_pchData != &_afxChNil)
		delete [] m_pchData;        // NOTE: not type safe
}

//////////////////////////////////////////////////////////////////////////////
// Helpers for the rest of the implementation

static inline int SafeStrlen(const char* psz)
	{ return (psz == NULL) ? NULL : strlen(psz); }

void CString::AllocCopy(CString& dest, int nCopyLen, int nCopyIndex,
	 int nExtraLen) const
{
	// will clone the data attached to this string
	// allocating 'nExtraLen' characters
	// Places results in uninitialized string 'dest'
	// Will copy the part or all of original data to start of new string

	int nNewLen = nCopyLen + nExtraLen;

	if (nNewLen == 0)
	{
		dest.Init();
	}
	else
	{
		dest.AllocBuffer(nNewLen);
		memcpy(dest.m_pchData, &m_pchData[nCopyIndex], nCopyLen);
	}
}

//////////////////////////////////////////////////////////////////////////////
// More sophisticated construction

CString::CString(const char* psz)
{
	int nLen;
	if ((nLen = SafeStrlen(psz)) == 0)
		Init();
	else
	{
		AllocBuffer(nLen);
		memcpy(m_pchData, psz, nLen);
	}
}

//////////////////////////////////////////////////////////////////////////////
// Diagnostic support

#ifdef _DEBUG 

CDumpContext&
operator <<(CDumpContext& dc, const CString& string)
{
	dc << string.m_pchData;
	return dc;
}

#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
// Assignment operators
//  All assign a new value to the string
//      (a) first see if the buffer is big enough
//      (b) if enough room, copy on top of old buffer, set size and type
//      (c) otherwise free old string data, and create a new one
//
//  All routines return the new string (but as a 'const CString&' so that
//      assigning it again will cause a copy, eg: s1 = s2 = "hi there".
//

void CString::AssignCopy(int nSrcLen, const char* pszSrcData)
{
	// check if it will fit
	if (nSrcLen > m_nAllocLength)
	{
		// it won't fit, allocate another one
		Empty();
		AllocBuffer(nSrcLen);
	}
	if (nSrcLen != 0)
		memcpy(m_pchData, pszSrcData, nSrcLen);
	m_nDataLength = nSrcLen;
	m_pchData[nSrcLen] = '\0';
}

const CString&
CString::operator =(const CString& stringSrc)
{
	AssignCopy(stringSrc.m_nDataLength, stringSrc.m_pchData);
	return *this;
}

const CString&
CString::operator =(const char* psz)
{
	AssignCopy(SafeStrlen(psz), psz);
	return *this;
}


//////////////////////////////////////////////////////////////////////////////
// concatenation

// NOTE: "operator +" is done as friend functions for simplicity
//      There are three variants:
//          CString + CString
// and for ? = char, const char*
//          CString + ?
//          ? + CString

void
CString::ConcatCopy(int nSrc1Len, const char* pszSrc1Data,
		int nSrc2Len, const char* pszSrc2Data)
{
  // -- master concatenation routine
  // Concatenate two sources
  // -- assume that 'this' is a new CString object

	int nNewLen = nSrc1Len + nSrc2Len;
	AllocBuffer(nNewLen);
	memcpy(m_pchData, pszSrc1Data, nSrc1Len);
	memcpy(&m_pchData[nSrc1Len], pszSrc2Data, nSrc2Len);
}

CString
operator +(const CString& string1, const CString& string2)
{
	CString s;
	s.ConcatCopy(string1.m_nDataLength, string1.m_pchData,
		string2.m_nDataLength, string2.m_pchData);
	return s;
}

CString
operator +(const CString& string, const char* psz)
{
	CString s;
	s.ConcatCopy(string.m_nDataLength, string.m_pchData, SafeStrlen(psz), psz);
	return s;
}


CString
operator +(const char* psz, const CString& string)
{
	CString s;
	s.ConcatCopy(SafeStrlen(psz), psz, string.m_nDataLength, string.m_pchData);
	return s;
}

//////////////////////////////////////////////////////////////////////////////
// concatenate in place

void
CString::ConcatInPlace(int nSrcLen, const char* pszSrcData)
{
	//  -- the main routine for += operators

	// if the buffer is too small, or we have a width mis-match, just
	//   allocate a new buffer (slow but sure)
	if (m_nDataLength + nSrcLen > m_nAllocLength)
	{
		// we have to grow the buffer, use the Concat in place routine
		char* pszOldData = m_pchData;
		ConcatCopy(m_nDataLength, pszOldData, nSrcLen, pszSrcData);
		ASSERT(pszOldData != NULL);
		if (pszOldData != &_afxChNil)
			delete [] pszOldData;
	}
	else
	{
		// fast concatenation when buffer big enough
		memcpy(&m_pchData[m_nDataLength], pszSrcData, nSrcLen);
		m_nDataLength += nSrcLen;
	}
	ASSERT(m_nDataLength <= m_nAllocLength);
	m_pchData[m_nDataLength] = '\0';
}

const CString&
CString::operator +=(const char* psz)
{
	ConcatInPlace(SafeStrlen(psz), psz);
	return *this;
}

const CString&
CString::operator +=(const CString& string)
{
	ConcatInPlace(string.m_nDataLength, string.m_pchData);
	return *this;
}


///////////////////////////////////////////////////////////////////////////////
