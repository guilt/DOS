// clipbd.cpp : This file contains all code which deals with the 
//      clipboard.  It contains code which updates the
//      menus on the clipboard contents and code which 
//      copies, pastes, and paste links to/from the clipboard.
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
static CString GLOBAL_szProtocol = "StdFileEditing";
static char szBuffer[80];


/////////////////////////////////////////////////////////////////////////////
// OLE Paste Link
//
void CTestClient::OnPasteLink()
{
	ASSERT(m_pClient != NULL);
	ASSERT(m_pItemTitle != NULL);

	if (!OpenClipboard())
	{
		MessageBox("Couldn't Open Clipboard", "Test Client", 
			MB_ICONEXCLAMATION);
		return;                    
		// Couldn't open the clipboard 
	}

	char szTmp[CBOBJNAMEMAX];

	CreateNewUniqueName(szTmp);

	// Here we deal with the case where there is an existing object
	// on the board by deleting the current object

	if (m_pClient->m_lpObject != NULL)
	{
		TRY
		{
			m_pClient->Delete();
		}
		CATCH (COleException, e)
		{
			if (m_bLogging)
			{
				LogError( THIS_FILE, e->m_status );
			}
			return;
		}
		END_CATCH
	}

	TRY
	{
		if (!m_pClient->CreateLinkFromClipboard(szTmp))
		{
			// error pasting link
			MessageBox("Clipboard Paste Link Failed","Test Client",
				MB_ICONEXCLAMATION);
			// No delete is required here since the object is only  
			// created on success
			return;
		}

		CloseClipboard();
		if (!DrawObject())
		{
			MessageBox("Couldn't Draw Object!", "Test Client",
				MB_ICONEXCLAMATION);
			m_pClient->Delete();        // Delete the object here
		}
	}
	CATCH (COleException, e)
	{
		if (m_bLogging)
		{
			LogError( THIS_FILE, e->m_status );
		}
		CloseClipboard();
		return;
	}
	END_CATCH

	

	// Set the information bars', object title
	m_pItemTitle->SetWindowText(m_pClient->GetName());
	m_bUntitled = TRUE;
	m_bDirty = TRUE;
	Invalidate(TRUE);
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient OnPaste
//
void CTestClient::OnPaste()
{
	char        szTmp[CBOBJNAMEMAX];

	ASSERT(m_pClient != NULL);
	ASSERT(m_pItemTitle != NULL);

	if (!OpenClipboard())
	{
		MessageBox("Couldn't Open Clipboard", "Test Client", 
			MB_ICONEXCLAMATION);
		return;                    
		// Couldn't open the clipboard 
	}

	CreateNewUniqueName(szTmp);


	// if an object exists, delete it

	TRY
	{
		if (m_pClient->m_lpObject != NULL)
		{
			m_pClient->Delete();
		}
	}
	CATCH (COleException, e)
	{
		if (m_bLogging)
		{
			LogError( THIS_FILE, e->m_status );
		}
		return;

	}
	END_CATCH



	TRY
	{
		if (!m_pClient->CreateFromClipboard(szTmp)) 
		{
			// error in pasting object
			MessageBox("Clipboard Paste Failed", "Test Client",
				MB_ICONEXCLAMATION);
			// No delete is required since the object is created only
			// on success, I think
			return;
		} 

		CloseClipboard();
		if (!DrawObject())
		{
			MessageBox("Couldn't Draw Object!", "Test Client",
				MB_ICONEXCLAMATION);
			m_pClient->Delete();        // Delete the object here
		}
	}
	CATCH (COleException, e)
	{
		if (m_bLogging)
		{
			LogError( THIS_FILE, e->m_status );
		}
		CloseClipboard();
		return;
	}
	END_CATCH

	// Set up the information bars' object title
	m_pItemTitle->SetWindowText(m_pClient->GetName());
	m_bUntitled = TRUE;
	m_bDirty = TRUE;
	Invalidate(TRUE);
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient OnCopy
//
void CTestClient::OnCopy() 
{
	ASSERT(m_pClient != NULL);

	if (!OpenClipboard())
	{
		MessageBox("Couldn't Open Clipboard", "Test Client", 
			MB_ICONEXCLAMATION);
		return;
	}

	EmptyClipboard();

	TRY
	{
		m_pClient->CopyToClipboard();
	}
	CATCH(COleException, e)
	{
		if (m_bLogging)
		{
			LogError( THIS_FILE, e->m_status );
		}

		MessageBox("Object Not Copied To Clipboard", "Test Client",
			MB_ICONEXCLAMATION);
		CloseClipboard();
		return;
	}
	END_CATCH

	CloseClipboard();
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CTestClient OnDrawClipboard()
//
void CTestClient::OnDrawClipboard()
{

	// Regenerate Listbox Entries for Clipboard Format
	ASSERT (m_pClipFormat != NULL);

	if (!OpenClipboard())
	{
		return;
	}
	m_pClipFormat->ResetContent();
	
	WORD wCurrentFormat, wFormat;
	wCurrentFormat = 0;

	int nFormats = CountClipboardFormats();
	for (int i=0; i < nFormats; i++)
	{
		wFormat = EnumClipboardFormats(wCurrentFormat);
		int nCnt = GetClipboardFormatName(wFormat, szBuffer, sizeof(szBuffer));
		if (nCnt == 0)
		{
			if (wFormat & CF_OWNERDISPLAY)
			{
				strcpy(szBuffer, szOwnerFormat[wFormat-CF_OWNERDISPLAY]);
			}
			else
			{
				strcpy(szBuffer, szDefinedFormat[wFormat-CF_TEXT]);
			}
		}

		m_pClipFormat->AddString(szBuffer);
		wCurrentFormat = wFormat;   
	}
	CloseClipboard();


	if (m_hWndNextView != NULL)
	{
		::SendMessage(m_hWndNextView, WM_DRAWCLIPBOARD,
			(GetCurrentMessage())->wParam, (GetCurrentMessage())->lParam);
	}
}




/////////////////////////////////////////////////////////////////////////////
// CTestClient OnChangeCbChain(HWND hRemove, HWND hNew)
//
void CTestClient::OnChangeCbChain(HWND hRemove, HWND hNew)
{
	if (hRemove == m_hWndNextView)
	{
		m_hWndNextView = hNew;
	}

	else if (m_hWndNextView != NULL)
	{
		::SendMessage(m_hWndNextView, WM_CHANGECBCHAIN, 
			(GetCurrentMessage())->wParam, (GetCurrentMessage())->lParam) ;
	}
}



