// newclnt.cpp : This file contains code which controls CNewClient which
//      is an override of COleClient.  It handles callbacks from
//      the OLE DLLs
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "resource.h"
#include "testclnt.h"
#include "defs.h"

extern CStdioFile *pOleDump;
static char szBuffer[80];


/////////////////////////////////////////////////////////////////////////////
// CNewClient::CNewClient(CTestClient* pParent, CNewClientDoc* pDoc)
//
CNewClient::CNewClient(CTestClient* pParent, CNewClientDoc* pDoc) :
	COleClientItem(pDoc)
{
	m_pTestClient = pParent;
}




/////////////////////////////////////////////////////////////////////////////
// CNewClient::OnChange()
//
void CNewClient::OnChange(OLE_NOTIFICATION wNotification)
{
	char szNoteName[20];

	ASSERT(m_pTestClient != NULL);

	switch (wNotification)
	{
		case OLE_CHANGED:
			strcpy(szNoteName,"OLE_CHANGED");
			break;

		case OLE_CLOSED:
			m_pTestClient->OnChanged();
			strcpy(szNoteName,"OLE_CLOSED");
			break;

		case OLE_SAVED:
			m_pTestClient->OnChanged();
				// we want to invalidate the client area as an action
				// has been performed.
			strcpy(szNoteName,"OLE_SAVED");
			break;

		default:
			ASSERT(FALSE);  // should never get here
	}


	if (m_pTestClient->m_bLogging)
	{
		ASSERT (pOleDump != NULL);
		wsprintf(szBuffer, 
			"An %s message has been processed in CNewClient::OnChange()\n",
				(LPCSTR)szNoteName);
		pOleDump->WriteString(szBuffer);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CNewClient::OnRenamed()
//
void CNewClient::OnRenamed()
{
	ASSERT(m_pTestClient != NULL);

	COleClientItem::OnRenamed();
	if (m_pTestClient->m_bLogging)
	{
		ASSERT (pOleDump != NULL);
		strcpy(szBuffer, 
			"An OLE_RENAMED message has been processed in CNewClient::OnRenamed()\n");
		pOleDump->WriteString(szBuffer);
	}
}





