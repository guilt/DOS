// This is a part of the Microsoft Foundation Classes C++ library. 
// Copyright (C) 1992 Microsoft Corporation 
// All rights reserved. 
//  
// This source code is only intended as a supplement to the 
// Microsoft Foundation Classes Reference and Microsoft 
// QuickHelp documentation provided with the library. 
// See these sources for detailed information regarding the 
// Microsoft Foundation Classes product. 

#include "afxole.h"
#pragma hdrstop

#ifdef AFX_OLE_SEG
#pragma code_seg(AFX_OLE_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

////////////////////////////////////////////////////////////////////////////
// CSharedFile implementation

IMPLEMENT_DYNAMIC(CSharedFile, CMemFile)

CSharedFile::CSharedFile(UINT nAllocFlags, UINT nGrowBytes /* = 1024 */)
	: CMemFile(nGrowBytes)
{
	m_nAllocFlags = nAllocFlags;
	m_hGlobalMemory = NULL;
}

CSharedFile::~CSharedFile()
{
	if (m_lpBuffer)
		Close();        // call appropriate Close/Free
	ASSERT(m_lpBuffer == NULL);
}

void
CSharedFile::SetHandle(HANDLE hGlobalMemory)
{
	ASSERT(m_hGlobalMemory == NULL);        // do once only
	ASSERT(m_lpBuffer == NULL);     // do once only
	ASSERT(m_nPosition == 0);   

	m_hGlobalMemory = hGlobalMemory;
	m_lpBuffer = (BYTE FAR*)::GlobalLock(m_hGlobalMemory);
	m_nBufferSize = m_nFileSize = (UINT)::GlobalSize(m_hGlobalMemory);
}

BYTE FAR* 
CSharedFile::Alloc(UINT nBytes)
{
	ASSERT(m_hGlobalMemory == NULL);        // do once only
	m_hGlobalMemory = ::GlobalAlloc(m_nAllocFlags, (DWORD) nBytes);
	if (m_hGlobalMemory == NULL)
		return NULL;
	return (BYTE FAR*)::GlobalLock(m_hGlobalMemory);
}

BYTE FAR* 
CSharedFile::Realloc(BYTE FAR*, UINT nBytes)
{
	ASSERT(m_hGlobalMemory != NULL);
	::GlobalUnlock(m_hGlobalMemory);
	HANDLE hNew;
	hNew = ::GlobalReAlloc(m_hGlobalMemory, (DWORD) nBytes, m_nAllocFlags);
	if (hNew == NULL)
		return NULL;
	m_hGlobalMemory = hNew;
	return (BYTE FAR*)::GlobalLock(m_hGlobalMemory);
}

void
CSharedFile::Free(BYTE FAR*)
{
	ASSERT(m_hGlobalMemory != NULL);
	::GlobalUnlock(m_hGlobalMemory);
	::GlobalFree(m_hGlobalMemory);
}

HANDLE
CSharedFile::Detach()
{
	HANDLE  hMem;
	ASSERT(m_hGlobalMemory != NULL);
	hMem = m_hGlobalMemory;

	m_hGlobalMemory = NULL; // detach from global handle

	// re-initialize the CMemFile parts too
	m_lpBuffer = NULL;
	m_nBufferSize = 0;

	return hMem;
}

////////////////////////////////////////////////////////////////////////////
