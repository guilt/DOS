// tests.cpp : This file contains code which implements the test routines
// specific to the Test Server application.
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



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnRevokeServerApi()
//
void CTestServer::OnRevokeServerApi()
{
	ASSERT (m_pServer != NULL);

	TRY
	{
		m_pServer->BeginRevoke();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit Test Server.", "Test Server", MB_ICONINFORMATION);
		return;
	}
	END_CATCH
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnRevokeDocApi()
//
void CTestServer::OnRevokeDocApi()
{
	ASSERT (m_pDoc != NULL);

	TRY
	{
		m_pDoc->Revoke();
		PostQuitMessage(0);
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit Test Server.", "Test Server", MB_ICONINFORMATION);
		return;
	}
	END_CATCH
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnRevertDocApi()
//
void CTestServer::OnRevertDocApi()
{
	ASSERT (m_pDoc != NULL);

	TRY
	{
		m_pDoc->NotifyRevert();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit Test Server.", "Test Server", MB_ICONINFORMATION);
		return;
	}
	END_CATCH
}




/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnSaveDocApi()
//
void CTestServer::OnSaveDocApi()
{
	ASSERT (m_pDoc != NULL);

	TRY
	{
		m_pDoc->NotifySaved();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit Test Server.", "Test Server", MB_ICONINFORMATION);
		return;
	}
	END_CATCH
}




/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnCloseDocApi()
//
void CTestServer::OnCloseDocApi()
{
	ASSERT (m_pDoc != NULL);

	TRY
	{
		m_pDoc->NotifyClosed();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit Test Server.", "Test Server", MB_ICONINFORMATION);
		return;
	}
	END_CATCH
}




/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnChangeDocApi()
//
void CTestServer::OnChangeDocApi()
{
	ASSERT (m_pDoc != NULL);

	TRY
	{
		m_pDoc->NotifyChanged();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit Test Server.", "Test Server", MB_ICONINFORMATION);
		return;
	}
	END_CATCH
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnChangeItemApi()
//
void CTestServer::OnChangeItemApi()
{
	if (!m_pItem)
	{
		MessageBox("Need to Create Item First","Test Server",
			MB_ICONINFORMATION);
		return;
	}

	TRY
	{
		m_pItem->NotifyChanged();
	}
	CATCH(CException, e)
	{
		MessageBox("An exception was thrown during this operation.  "
			"Please exit Test Server.", "Test Server", MB_ICONINFORMATION);
		return;
	}
	END_CATCH
}

