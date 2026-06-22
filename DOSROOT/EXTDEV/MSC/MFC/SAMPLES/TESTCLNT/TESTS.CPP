// tests.cpp : This file contains code which just hasn't been introduced
//        into the main program.  It is meant more as an experimental
//        file.  It should be removed when development is completed.
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

#include "testclnt.h"
#include "resource.h"
#include "defs.h"

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

extern CStdioFile *pOleDump;
static char szBuffer[80];


/////////////////////////////////////////////////////////////////////////////
// CTestClient::OnLogging()
//

void CTestClient::OnLogging()
{
	CMenu *pMenu;
	pMenu = GetMenu();

	if (m_bLogging)
	{
		pMenu->CheckMenuItem(IDM_LOGGING, MF_UNCHECKED);
		pOleDump->Flush();
		pOleDump->Close();
		delete pOleDump;
		m_bLogging = !m_bLogging;
	}
	else
	{

		pMenu->CheckMenuItem(IDM_LOGGING, MF_CHECKED);
		pOleDump = new CStdioFile();
		if (!pOleDump->Open("testclnt.log", CFile::typeText |
			CFile::modeWrite | CFile::modeCreate))
		{
			TRACE("Logging File TESTCLNT.LOG not opened\n");
		}
		else
		{
			m_bLogging = !m_bLogging;
		}
	}
}


void CTestClient::OnCloseApi()
{
	ASSERT(m_pClient != NULL);

	TRY
	{
		m_pClient->CloseLink();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit the application and restart.", "Test Client",
			MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH
}


void CTestClient::OnUpdateApi()
{
	ASSERT(m_pClient != NULL);

	TRY
	{
		m_pClient->UpdateLink();
		Invalidate(TRUE);
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit the application and restart.", "Test Client",
			MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH

}


void CTestClient::OnReleaseApi()
{
	ASSERT(m_pClient != NULL);

	TRY
	{
		m_pClient->Release();
		Invalidate(TRUE);
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit the application and restart.", "Test Client",
			MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH
}



void CTestClient::OnDeleteApi()
{
	ASSERT(m_pClient != NULL);

	TRY
	{
		m_pClient->Delete();
		Invalidate(TRUE);
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit the application and restart.", "Test Client",
			MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH
}



void CTestClient::OnReconnectApi()
{
	ASSERT(m_pClient != NULL);

	TRY
	{
		m_pClient->ReconnectLink();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit the application and restart.", "Test Client",
			MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH
}



void CTestClient::OnRevertApi()
{
	ASSERT(m_pDoc != NULL);

	TRY
	{
		m_pDoc->NotifyRevert();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit the application and restart.", "Test Client",
			MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH
}



void CTestClient::OnSavedApi()
{
	ASSERT(m_pDoc != NULL);

	TRY
	{
		m_pDoc->NotifySaved();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit the application and restart.", "Test Client",
			MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH
}
