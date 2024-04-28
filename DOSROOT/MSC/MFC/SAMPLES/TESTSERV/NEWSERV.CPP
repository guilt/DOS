// newserv.cpp : This file contains code which implements functions
//  specific to the CNewServer class which is a derived class of
//  COleServer.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "testserv.h"
#include "defs.h"

extern CStdioFile *pOleDump;
extern void OutputLog (const char *pText);


/////////////////////////////////////////////////////////////////////////////
static CServDoc* GetAppDoc()
{
	CTestServer* pView = (CTestServer*)AfxGetApp()->m_pMainWnd;
	if (pView == NULL)
	{
		return NULL;
	}

	CServDoc* pDoc = pView->GetDocument();

	TRACE("The Server Doc is:  %x in GetAppDoc\n",pDoc);
	if (pDoc == NULL)
	{
		return NULL;
	}
	
	return pDoc;
}



/////////////////////////////////////////////////////////////////////////////
// CNewServer::OnOpenDoc(LPCSTR lpszDoc)
//

#pragma warning(disable:4100)
// C4100 is 'unused formal parameter' warning

COleServerDoc*
CNewServer::OnOpenDoc(LPCSTR lpszDoc)
{
	ASSERT(lpszDoc != NULL);

	CTestServer* pOwner = (CTestServer*)AfxGetApp()->m_pMainWnd;

	if (pOwner->m_pDoc && pOwner->m_pDoc->IsOpen())
	{
		return NULL;    // handle only one request at a time.
	}

	CServDoc* pDoc = GetAppDoc();
	
	if (pDoc == NULL)
	{
		CTestServer* pOwner = (CTestServer*)AfxGetApp()->m_pMainWnd;
		if (pOwner->m_bLogging)
		{
			OutputLog("NEWSERV.CPP::OnOpenDoc  GetAppDoc returned a NULL Pointer\n");
		}
	}
	return pDoc;
}

#pragma warning(default:4100)


/////////////////////////////////////////////////////////////////////////////
// CNewServer::OnCreateDoc(LPCSTR lpszClass, LPCSTR lpszDoc)
//
COleServerDoc*
CNewServer::OnCreateDoc(LPCSTR lpszClass, LPCSTR lpszDoc)
{
	ASSERT(lpszClass != NULL);
	ASSERT(lpszDoc != NULL);

	CTestServer* pOwner = (CTestServer*)AfxGetApp()->m_pMainWnd;

	if (pOwner->m_pDoc && pOwner->m_pDoc->IsOpen())
	{
		return NULL;    // handle only one request at a time.
	}

	if (pOwner->m_bLogging)
	{
		OutputLog("CNewServer:  Now Receiving a Create Message With:\n");
		char szBuffer[80];
		wsprintf(szBuffer, "parameters (%Fs, %Fs)\n", lpszClass, lpszDoc);
		OutputLog(szBuffer);
	}

	CServDoc* pDoc = GetAppDoc();

	if (pDoc == NULL)
	{
		if (pOwner->m_bLogging)
		{
			OutputLog("NEWSERV.CPP::OnCreateDoc GetAppDoc returned a NULL pointer\n");
		}
	}
	return pDoc;
}





/////////////////////////////////////////////////////////////////////////////
// CNewServer::OnEditDoc(LPCSTR lpszClass, LPCSTR lpszDoc)
//

#pragma warning(disable:4100)
// C4100 is 'unused formal parameter' warning

COleServerDoc*
CNewServer::OnEditDoc(LPCSTR lpszClass, LPCSTR lpszDoc)
{
	ASSERT(lpszClass != NULL);
	ASSERT(lpszDoc != NULL);
	
	CTestServer* pOwner = (CTestServer*)AfxGetApp()->m_pMainWnd;

	if (pOwner->m_pDoc && pOwner->m_pDoc->IsOpen())
	{
		return NULL;    // handle only one request at a time.
	}

	CServDoc* pDoc = GetAppDoc();
	
	if (pDoc == NULL)
	{
		if (pOwner->m_bLogging)
		{
			OutputLog("NEWSERV.CPP::OnEditDoc  GetAppDoc returned a NULL pointer\n");
		}
	}
	return pDoc;
}

#pragma warning(default:4100)



/////////////////////////////////////////////////////////////////////////////
// CNewServer::OnCreateDocFromTemplate(LPCSTR lpszClass,
//              LPCSTR lpszDoc, LPCSTR lpszTemplate)
//
COleServerDoc* CNewServer::OnCreateDocFromTemplate(LPCSTR lpszClass,
	LPCSTR lpszDoc, LPCSTR lpszTemplate)
{
	ASSERT(lpszClass != NULL);
	ASSERT(lpszDoc != NULL);
	ASSERT(lpszTemplate != NULL);

	CTestServer *pOwner = (CTestServer*)AfxGetApp()->m_pMainWnd;

	if (pOwner->m_pDoc && pOwner->m_pDoc->IsOpen())
	{
		return NULL;    // handle only one request at a time.
	}

	if (pOwner->m_bLogging)
	{
		OutputLog("CNewServer::Received a CreateFromTemplate message\n");
	}
	

	return COleServer::OnCreateDocFromTemplate( lpszClass, lpszDoc,
		lpszTemplate);
}




/////////////////////////////////////////////////////////////////////////////
