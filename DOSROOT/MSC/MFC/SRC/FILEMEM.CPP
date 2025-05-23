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
#include <malloc.h>

#ifdef AFX_CORE_SEG
#pragma code_seg(AFX_CORE_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

////////////////////////////////////////////////////////////////////////////
// CMemFile implementation

IMPLEMENT_DYNAMIC(CMemFile, CFile)

CMemFile::CMemFile(UINT nGrowBytes /* = 1024 */)
{
	ASSERT(nGrowBytes <= USHRT_MAX);

	m_hFile = hFileNull;
	m_nGrowBytes = nGrowBytes;
	m_nPosition = 0;
	m_nBufferSize = 0;
	m_nFileSize = 0;
	m_lpBuffer = NULL;
	m_nBufferSize = 0;
}

CMemFile::~CMemFile()
{
	// Close should have already been called, but we check anyway
	if (m_lpBuffer)
		Close();
	ASSERT(m_lpBuffer == NULL);

	m_nGrowBytes = 0;
	m_nPosition = 0;
	m_nBufferSize = 0;
	m_nFileSize = 0;
}

BYTE FAR* 
CMemFile::Alloc(UINT nBytes)
{
	return (BYTE FAR*)_fmalloc(nBytes);
}

BYTE FAR* 
CMemFile::Realloc(BYTE FAR* pMem, UINT nBytes)
{
	return (BYTE FAR*)_frealloc(pMem, nBytes);
}

BYTE FAR* 
CMemFile::Memcpy(BYTE FAR* pMemTarget, const BYTE FAR* pMemSource, UINT nBytes)
{
	ASSERT(pMemTarget != NULL);
	ASSERT(pMemSource != NULL);
	ASSERT(AfxIsValidAddress(pMemTarget, nBytes));
	ASSERT(AfxIsValidAddress(pMemSource, nBytes, FALSE));

	return (BYTE FAR*)_fmemcpy(pMemTarget, pMemSource, nBytes);
}

void
CMemFile::Free(BYTE FAR* pMem)
{
	ASSERT(pMem != NULL);

	_ffree(pMem);
}

DWORD   
CMemFile::GetPosition() const
{
	ASSERT_VALID(this);
	return (DWORD)m_nPosition;
}

void 
CMemFile::GrowFile(DWORD dwNewLen)
{
	ASSERT_VALID(this);
	ASSERT((dwNewLen & 0xFFFF0000) == 0L);

	if (dwNewLen > m_nBufferSize)
	{
		// grow the buffer
		DWORD dwNewBufferSize = (DWORD)m_nBufferSize;

		while (dwNewBufferSize < dwNewLen)
			dwNewBufferSize += m_nGrowBytes;

		if (dwNewBufferSize > USHRT_MAX)
			AfxThrowFileException(CFileException::diskFull);
		ASSERT((dwNewBufferSize & 0xFFFF0000) == 0L);

		BYTE FAR* lpNew;
		if (m_lpBuffer == NULL)
			lpNew = Alloc((UINT)dwNewBufferSize);
		else
			lpNew = Realloc(m_lpBuffer, (UINT)dwNewBufferSize);

		if (lpNew == NULL)
			AfxThrowMemoryException();

		m_lpBuffer = lpNew;
		m_nBufferSize = (UINT)dwNewBufferSize;      
	}
	ASSERT_VALID(this);
}

void    
CMemFile::SetLength(DWORD dwNewLen)
{
	ASSERT_VALID(this);
	ASSERT((UINT)dwNewLen <= USHRT_MAX);

	if (dwNewLen > m_nBufferSize)
		GrowFile(dwNewLen);

	if (dwNewLen < m_nPosition)
		m_nPosition = (UINT)dwNewLen;

	m_nFileSize = (UINT)dwNewLen;
	ASSERT_VALID(this);
}


UINT    
CMemFile::Read(void FAR* lpBuf, UINT nCount)
{
	ASSERT_VALID(this);
	ASSERT(lpBuf != NULL);
	ASSERT(AfxIsValidAddress(lpBuf, nCount));

	UINT nRead;

	if (m_nPosition > m_nFileSize)
		return 0;

	if (m_nPosition + nCount > m_nFileSize)
		nRead = m_nFileSize - m_nPosition;
	else
		nRead = nCount;

	Memcpy((BYTE FAR*)lpBuf, m_lpBuffer + m_nPosition, nRead);
	m_nPosition += nRead;

	ASSERT_VALID(this);

	return nRead;
}

void
CMemFile::Write(const void FAR* lpBuf, UINT nCount)
{
	ASSERT_VALID(this);
	ASSERT(lpBuf != NULL);
	ASSERT(AfxIsValidAddress(lpBuf, nCount, FALSE));

	if (m_nPosition + nCount > m_nBufferSize)
		GrowFile(m_nPosition + nCount);

	ASSERT(m_nPosition + nCount <= m_nBufferSize);

	Memcpy(m_lpBuffer + m_nPosition, (BYTE FAR*)lpBuf, nCount);

	m_nPosition += nCount;

	if (m_nPosition > m_nFileSize)
		m_nFileSize = m_nPosition;

	ASSERT_VALID(this);
}


LONG
CMemFile::Seek(LONG lOff, UINT nFrom)
{
	ASSERT_VALID(this);
	ASSERT(lOff <= USHRT_MAX);
	ASSERT(nFrom == CFile::begin || nFrom == CFile::end || nFrom == CFile::current);

	LONG lNewPos = m_nPosition;

	if (nFrom == CFile::begin)
		lNewPos = lOff;
	else if (nFrom == CFile::current)
		lNewPos += lOff;
	else if (nFrom == CFile::end)
		lNewPos = m_nFileSize + lOff;
	else
		return -1;

	if (lNewPos < 0)
		AfxThrowFileException(CFileException::badSeek);

	m_nPosition = (UINT)lNewPos;

	ASSERT_VALID(this);
	return m_nPosition;
}

void    
CMemFile::Flush()
{
	ASSERT_VALID(this);
}

void    
CMemFile::Close()
{
	ASSERT_VALID(this);
	m_nGrowBytes = 0;
	m_nPosition = 0;
	m_nBufferSize = 0;
	m_nFileSize = 0;
	if (m_lpBuffer)
		Free(m_lpBuffer);
	m_lpBuffer = NULL;
}

void 
CMemFile::LockRange(DWORD /* dwPos */, DWORD /* dwCount */)
{
	ASSERT_VALID(this);
	AfxThrowNotSupportedException();
}


void 
CMemFile::UnlockRange(DWORD /* dwPos */, DWORD /* dwCount */)
{
	ASSERT_VALID(this);
	AfxThrowNotSupportedException();
}

CFile*
CMemFile::Duplicate() const
{
	ASSERT_VALID(this);
	AfxThrowNotSupportedException();
	return NULL;
}

BOOL
CMemFile::GetStatus(CFileStatus& rStatus) const
{
	ASSERT_VALID(this);

	rStatus.m_ctime = 0;
	rStatus.m_mtime = 0;
	rStatus.m_atime = 0;
	rStatus.m_size = m_nFileSize;
	rStatus.m_attribute = CFile::normal;
	rStatus.m_szFullName[0] = '\0';
	return TRUE;
}

#ifdef _DEBUG

void    
CMemFile::Dump(CDumpContext& dc) const
{
	ASSERT_VALID(this);

	CFile::Dump(dc);

	dc << "\n\tfile size = " << m_nFileSize;
	dc << "\n\tbuffer size = " << m_nBufferSize;
	dc << "\n\tposition = " << m_nPosition;
	dc << "\n\tgrowth rate = " << m_nGrowBytes;
}

void
CMemFile::AssertValid() const
{
	CFile::AssertValid();

	ASSERT((m_lpBuffer == NULL && m_nBufferSize == 0) || AfxIsValidAddress(m_lpBuffer, m_nBufferSize));
	ASSERT(m_nFileSize <= m_nBufferSize);
	// m_nPosition might be after the end of file, so we cannot ASSERT
	// its validity
}

#endif // _DEBUG
