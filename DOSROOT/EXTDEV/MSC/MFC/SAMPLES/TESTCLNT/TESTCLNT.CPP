// testclnt.cpp : This is the main file for the AFXOLE Test Client.  The
//               test client is mean to be an API, stress, and usability
//               test of the AFX OLE implementation.
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

IMPLEMENT_DYNAMIC(CTestClient,CFrameWnd)

/////////////////////////////////////////////////////////////////////////////
// GLOBALS
//
UINT GLOBAL_uNativeFormat, GLOBAL_uOwnerFormat, GLOBAL_uObjectFormat;
CString GLOBAL_szFile;
CStdioFile *pOleDump;
static char szBuffer[80];
CTheApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CTestClient constructor:
//
CTestClient::CTestClient()
{
	VERIFY(m_title.LoadString(IDS_APPNAME));
	VERIFY(LoadAccelTable(MAKEINTRESOURCE(ID_APPLICATION)));
	
	VERIFY(Create(NULL, m_title, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		rectDefault, NULL, MAKEINTRESOURCE(ID_APPLICATION)));

	ASSERT(m_hWnd != NULL);

	m_pDoc = new CNewClientDoc(this);
	VERIFY(m_pDoc->Register(AfxGetApp()->m_pszAppName, 
		"Document 1") != 0);

	m_pClient = new CNewClient(this, m_pDoc);

	m_pBorder = NULL;
	m_bRevertAvailable = FALSE;
	m_bLogging = FALSE;
	m_bUntitled = TRUE;

	m_hWndNextView = NULL;
	m_hWndNextView = SetClipboardViewer();
	m_bDirty = FALSE;
}




/////////////////////////////////////////////////////////////////////////////
// CTestClient::OnCreate(LPCREATESTRUCT p)
//
int CTestClient::OnCreate(LPCREATESTRUCT p)
{
	CRect nullRect(0,0,0,0);
	m_pObjectFormat = new CListBox();
	m_pObjectFormat->Create( LBS_USETABSTOPS | WS_CHILD | 
		WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL, nullRect,
		this, IDC_OBJECTFORMAT);

	m_pClipFormat = new CListBox();
	m_pClipFormat->Create( LBS_USETABSTOPS | WS_CHILD | 
		WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL, nullRect, 
		this, IDC_CLIPFORMAT);

	m_pInfoTitle = new CStatic();
	m_pInfoTitle->Create("Information Bar", WS_VISIBLE | WS_CHILD |
		SS_CENTER, nullRect, this, IDC_INFOTITLE);

	m_pItemTitle = new CStatic();
	m_pItemTitle->Create("None", WS_VISIBLE | WS_CHILD |
		SS_CENTER, nullRect, this, IDC_INFOITEM);

	m_pClipTitle = new CStatic();
	m_pClipTitle->Create("Clipboard Formats:", WS_VISIBLE | WS_CHILD |
		SS_LEFT, nullRect, this, IDC_INFOCLIPFORMAT);

	m_pObjectTitle = new CStatic();
	m_pObjectTitle->Create("Object Formats:", WS_VISIBLE | WS_CHILD |
		SS_LEFT, nullRect, this, IDC_INFOOBJECTFORMAT);

	m_pNameTitle = new CStatic();
	m_pNameTitle->Create("Name:", WS_VISIBLE | WS_CHILD |
		SS_LEFT, nullRect, this, IDC_INFONAME);

	return CFrameWnd::OnCreate(p);
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient::OnInitMenu(CMenu* pMenu)
//
void CTestClient::OnInitMenu(CMenu* pMenu)
{
	CMenu *myMenu;
	BOOL bCanLink, bCanPaste;

	myMenu = GetMenu();

	if ((myMenu != pMenu) || (m_pClient == NULL))
	{
		// just return on weird cases, we don't want to assert here.
		return;
	}


	// Set up file and object menus
	if (m_pClient->m_lpObject != NULL)
	{
		pMenu->EnableMenuItem(IDM_SAVE, MF_ENABLED);
		pMenu->EnableMenuItem(IDM_SAVEAS, MF_ENABLED);
		pMenu->EnableMenuItem(IDM_COPY, MF_ENABLED);

	}
	else
	{
		pMenu->EnableMenuItem(IDM_SAVE, MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(IDM_SAVEAS, MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(IDM_COPY, MF_DISABLED | MF_GRAYED);
	}


	if (m_bRevertAvailable)
	{
		pMenu->EnableMenuItem(IDM_REVERT, MF_ENABLED);
	}
	else
	{
		pMenu->EnableMenuItem(IDM_REVERT, MF_DISABLED | MF_GRAYED);
	}


	
	TRY
	{
		// Generate the EDIT menus
		ASSERT (m_pClient != NULL);
		bCanPaste = m_pClient->CanPaste();
		bCanLink = m_pClient->CanPasteLink();

		if (bCanLink)
		{
			pMenu->EnableMenuItem(IDM_PASTELINK, MF_ENABLED);
		}
		else
		{
			pMenu->EnableMenuItem(IDM_PASTELINK, MF_DISABLED | MF_GRAYED);
		}


		if (bCanPaste)
		{
			pMenu->EnableMenuItem(IDM_PASTE, MF_ENABLED);
		}
		else
		{
			pMenu->EnableMenuItem(IDM_PASTE, MF_DISABLED | MF_GRAYED);
		}


		if ((m_pClient->m_lpObject != NULL) &&
			(m_pClient->GetType() == OT_LINK))
		{
			pMenu->EnableMenuItem(IDM_LINKS, MF_ENABLED);
			pMenu->EnableMenuItem(IDM_RECONNECT, MF_ENABLED);
			pMenu->EnableMenuItem(IDM_UPDATE, MF_ENABLED);
		}
		else
		{
			pMenu->EnableMenuItem(IDM_LINKS, MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem(IDM_RECONNECT, MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem(IDM_UPDATE, MF_DISABLED | MF_GRAYED);
		}


		// if it is a picture don't allow any calls to the API menus
		if ((m_pClient->m_lpObject != NULL) &&
			(m_pClient->GetType() == OT_STATIC))
		{
			pMenu->EnableMenuItem(IDM_CLOSE, MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem(IDM_UPDATE, MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem(IDM_RELEASE, MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem(IDM_DELETE, MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem(IDM_RECONNECT, MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem(IDM_REVERTDOC, MF_DISABLED | MF_GRAYED);
			pMenu->EnableMenuItem(IDM_SAVED, MF_DISABLED | MF_GRAYED);
		}
			

		// add the object verb menus on the end of the object sub-menu
		CMenu *pObjectMenu;

		pObjectMenu = pMenu->GetSubMenu(2);
		static int iItemObjectVerb = -1;    // position on the Edit menu

		if (iItemObjectVerb == -1)
		{
			// one-time init - find the position of the "Object ?" menuitem
			int nItems = pObjectMenu->GetMenuItemCount();
			for (int iItem = 0; iItem < nItems; iItem++)
			{
				if (pObjectMenu->GetMenuItemID(iItem) == IDM_OBJECT_VERB_MIN)
				{
					iItemObjectVerb = iItem;
					break;
				}
			}
		}
		ASSERT(iItemObjectVerb != -1);
		// MUST BE IN THE MENU TEMPLATE ON INIT !

		AfxOleSetEditMenu(m_pClient->m_lpObject == NULL ? NULL : m_pClient, 
			pObjectMenu, iItemObjectVerb, IDM_OBJECT_VERB_MIN);
	}
	CATCH(CException, e)
	{
		return;
	}
	END_CATCH
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient::OnCommand(UINT wParam, LONG lParam)
//
BOOL CTestClient::OnCommand(UINT wParam, LONG lParam)
{
	if (!m_pClient)
	{
		return CFrameWnd::OnCommand(wParam, lParam);
	}

	// if we are waiting for release - ignore all commands
	if (COleClientItem::InWaitForRelease())
	{
		return TRUE;        // handled
	}

	if (LOWORD(lParam) == 0 && wParam >= IDM_OBJECT_VERB_MIN &&
		wParam <= IDM_OBJECT_VERB_MAX && m_pClient != NULL)
	{
		DoVerb(wParam - IDM_OBJECT_VERB_MIN);
		return TRUE;        // handled
	}
	return CFrameWnd::OnCommand(wParam, lParam);
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient OnAbout()
//
void CTestClient::OnAbout()
{
	CModalDialog about(MAKEINTRESOURCE(IDDT_ABOUT), this);
	about.DoModal();
}




/////////////////////////////////////////////////////////////////////////////
// CTestClient OnDestroy()
//
void CTestClient::OnDestroy()
{
	if (IsWindow(m_hWndNextView))
	{
		ChangeClipboardChain(m_hWndNextView);
	}

	TRY
	{
		if (m_pClient->m_lpObject)
		{
			m_pClient->Delete();// Go ahead and destroy the item
		}
		m_pDoc->Revoke();           // Revoke Document
	}
	CATCH(COleException, e)
	{
		// There is not much we can do here to clean up.  The TRY/CATCH
		// is only provided to prevent an assertion in the message pump.
	}
	END_CATCH

	CFrameWnd::OnDestroy();
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient::OnSize(UNIT nType, int cx, int cy)
//
void CTestClient::OnSize (UINT nType, int cx, int cy)
{
	int iRegion;
	CRect clipRect, objectClipRect, objectTitleRect, infoRect, 
		itemRect, nameRect, cpTitleRect;
	CClientDC dc(this);

	// Divide screen region into two regions: object and information bar.
	// information bar takes up right hand 1/3rd of screen.
	iRegion = cx/3;

	// Set up left borders
	clipRect.left = objectClipRect.left = infoRect.left = cx - iRegion;
	itemRect.left = nameRect.left = cpTitleRect.left = cx - iRegion;
	objectTitleRect.left = cx - iRegion;

	// set up right borders
	clipRect.right = objectClipRect.right = infoRect.right = cx;
	itemRect.right = nameRect.right = cpTitleRect.right = cx;
	objectTitleRect.right = cx;

	// setup Information Bar (infoRect) top and bottom
	infoRect.top = 0;
	m_pInfoTitle->GetWindowText(szBuffer, sizeof(szBuffer));
	infoRect.bottom = (dc.GetTextExtent(szBuffer, strlen(szBuffer))).cy;

	// setup name top and bottom
	nameRect.top = infoRect.bottom;
	m_pNameTitle->GetWindowText(szBuffer,sizeof(szBuffer));
	nameRect.bottom = nameRect.top + 
		(dc.GetTextExtent(szBuffer, strlen(szBuffer))).cy;

	// setup object tile top and bottom
	itemRect.top = nameRect.bottom;
	m_pItemTitle->GetWindowText(szBuffer,sizeof(szBuffer));
	itemRect.bottom = itemRect.top + 
		(dc.GetTextExtent(szBuffer, strlen(szBuffer))).cy;

	// setup clipboard format title top and bottom
	cpTitleRect.top = itemRect.bottom;
	m_pClipTitle->GetWindowText(szBuffer,sizeof(szBuffer));
	cpTitleRect.bottom = cpTitleRect.top +
		(dc.GetTextExtent(szBuffer, strlen(szBuffer))).cy;


	// setup clipboard area
	clipRect.top = cpTitleRect.bottom;
	m_pObjectTitle->GetWindowText(szBuffer,sizeof(szBuffer));
	clipRect.bottom = cy/2 + 
		((dc.GetTextExtent(szBuffer, strlen(szBuffer))).cy/2);

	// setup object format title area
	objectTitleRect.top = clipRect.bottom;
	m_pObjectTitle->GetWindowText(szBuffer,sizeof(szBuffer));
	objectTitleRect.bottom = objectTitleRect.top + 
		(dc.GetTextExtent(szBuffer, strlen(szBuffer))).cy;

	// setup object clipboard format area
	objectClipRect.top = objectTitleRect.bottom;
	objectClipRect.bottom = cy;

	m_pClipFormat->MoveWindow(clipRect);
	m_pObjectFormat->MoveWindow(objectClipRect);
	m_pItemTitle->MoveWindow(itemRect);
	m_pObjectTitle->MoveWindow(objectTitleRect);
	m_pInfoTitle->MoveWindow(infoRect);
	m_pClipTitle->MoveWindow(cpTitleRect);
	m_pNameTitle->MoveWindow(nameRect);

	CFrameWnd::OnSize (nType, cx, cy);
}




/////////////////////////////////////////////////////////////////////////////
// CTestClient::QuerySaveChanges()
//
BOOL CTestClient::QuerySaveChanges()
{
	if (!m_bDirty)
	{
		return TRUE;
	}

	int fResponse;
	fResponse = MessageBox("Save file before proceeding?", "Test Client",
		MB_YESNOCANCEL | MB_ICONQUESTION);

	if (fResponse == IDCANCEL)
	{
		return FALSE;
	}
	
	if (fResponse == IDYES)
	{
		SaveFile(m_bUntitled);
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient OnClose
//
void CTestClient::OnClose()
{

	if (COleClientItem::InWaitForRelease())
	{
		MessageBox("Server still busy or dead", "Test Client",
			MB_ICONEXCLAMATION);
		return;
	}

	if (!QuerySaveChanges())
	{
		return;
	}
	DestroyWindow();
}




/////////////////////////////////////////////////////////////////////////////
// CTestClient PrepareDC
//
void CTestClient::PrepareDC(CDC* pDC)
{
	pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
}

/////////////////////////////////////////////////////////////////////////////
// CTestClient OnPaint
//
void CTestClient::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;

	PrepareDC(&dc);
	GetClientRect(rect);

	// Object uses left hand 2/3rds of screen to draw on.
	rect.right = (int)((2 * rect.right) / 3);

	if (m_pClient->m_lpObject != NULL)
	{
		TRY
		{
			if (!m_pClient->Draw(&dc, &rect, NULL, &dc))
			{

				if (m_pClient->GetLastStatus() == OLE_ERROR_BLANK)
				{
					// It's blank, just return
					return;
				}

				MessageBox ("Couldn't Paint Object!", "Test Client",
					MB_ICONEXCLAMATION);
			}
		}
		CATCH (COleException, e)
		{
			MessageBox("An OleException was Thrown in CTestClient::OnPaint", "Test Client",
					MB_ICONEXCLAMATION);    
			if (m_bLogging)
			{
				LogError (THIS_FILE, e->m_status);
			}
		}
		END_CATCH
	}
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient::OnLinks()
//
void CTestClient::OnLinks()
{
	ASSERT(m_pDoc != NULL);
	AfxOleLinksDialog(m_pDoc);
	Invalidate(TRUE);
}




/////////////////////////////////////////////////////////////////////////////
// CTestClient::OnExit()
//
void CTestClient::OnMenuExit()
{
	PostMessage(WM_CLOSE);
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient::~CTestClient()
//
CTestClient::~CTestClient()
{
	if (m_pClipFormat != NULL)
	{
		delete m_pClipFormat;
	}

	if (m_pObjectFormat != NULL)
	{
		delete m_pObjectFormat;
	}

	if (m_pInfoTitle != NULL)
	{
		delete m_pInfoTitle;
	}
	
	if (m_pItemTitle != NULL)
	{
		delete m_pItemTitle;
	}

	if (m_pClipTitle != NULL)
	{
		delete m_pClipTitle;
	}

	if (m_pObjectTitle != NULL)
	{
		delete m_pObjectTitle;
	}

	if (m_pNameTitle != NULL)
	{
		delete m_pNameTitle;
	}

	if (pOleDump != NULL)
	{
		pOleDump->Flush();
		pOleDump->Close();
		delete pOleDump;
	}
	
	if (m_pClient != NULL)
	{
		delete m_pClient;
	}

}


// CTestClient message map:
// Associate messages with member functions.
BEGIN_MESSAGE_MAP( CTestClient, CFrameWnd )
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_PASTELINK, OnPasteLink)
	ON_COMMAND(IDM_INSERT_OBJECT, OnInsertObject)
	ON_COMMAND(IDM_REVERT, OnRevert)
	ON_COMMAND(IDM_LINKS, OnLinks)
	ON_COMMAND(IDM_PASTE, OnPaste)
	ON_COMMAND(IDM_COPY, OnCopy)
	ON_COMMAND(IDM_OPEN, OnFileOpen)
	ON_COMMAND(IDM_SAVE, OnFileSave)
	ON_COMMAND(IDM_SAVEAS, OnFileSaveAs)
	ON_COMMAND(IDM_EXIT, OnMenuExit)
	ON_COMMAND(IDM_LOGGING, OnLogging)
	ON_COMMAND(IDM_CLOSE, OnCloseApi)
	ON_COMMAND(IDM_UPDATE, OnUpdateApi)
	ON_COMMAND(IDM_RELEASE, OnReleaseApi)
	ON_COMMAND(IDM_DELETE, OnDeleteApi)
	ON_COMMAND(IDM_RECONNECT, OnReconnectApi)
	ON_COMMAND(IDM_REVERTDOC, OnRevertApi)
	ON_COMMAND(IDM_SAVED, OnSavedApi)
	ON_WM_DRAWCLIPBOARD()
	ON_WM_CHANGECBCHAIN()
	ON_WM_INITMENU()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CTheApp InitInstance:
// 
BOOL CTheApp::InitInstance()
{
	m_pMainWnd = new CTestClient();

	ASSERT (m_pMainWnd != NULL);
	m_pMainWnd->ShowWindow( m_nCmdShow );
	m_pMainWnd->UpdateWindow();

	
	// Following the OLE V1.0 SDK, the clipboard formats are registered.
	// Note the stream, document, and client are all created in testclnt.h.
	GLOBAL_uNativeFormat = RegisterClipboardFormat("Native");
	GLOBAL_uOwnerFormat = RegisterClipboardFormat("OwnerLink");
	GLOBAL_uObjectFormat = RegisterClipboardFormat("ObjectLink");

	// A check is performed on each value returned by the register
	// operation.

	if ((GLOBAL_uNativeFormat < 0xC000) && (GLOBAL_uNativeFormat > 0xFFFF))
	{
		MessageBox(m_pMainWnd->m_hWnd, "Native Data Clipboard Format Not Registered!",
			"Test Client", MB_ICONEXCLAMATION);
		return FALSE;
	}


	if ((GLOBAL_uOwnerFormat < 0xC000) && (GLOBAL_uOwnerFormat > 0xFFFF))
	{
		MessageBox(m_pMainWnd->m_hWnd, "Native Data Clipboard Format Not Registered!",
			"Test Client", MB_ICONEXCLAMATION);
		return FALSE;
	}


	if ((GLOBAL_uObjectFormat < 0xC000) && (GLOBAL_uObjectFormat > 0xFFFF))
	{
		MessageBox(m_pMainWnd->m_hWnd, "Native Data Clipboard Format Not Registered!",
			"Test Client", MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}
