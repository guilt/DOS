// testserv.cpp : This file contains code which implements functions
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
#include "resource.h"
#include "defs.h"

extern void OutputLog(const char *pText);
extern LPSTR CreateNewUniqueName(LPSTR lpstr);

/////////////////////////////////////////////////////////////////////////////
//  GLOBALS
//
BOOL GLOBAL_bRegisterDoc, GLOBAL_bNoDisplay, GLOBAL_bEmbedded;
BOOL CTestServer::m_bCreationFailed = FALSE;
UINT GLOBAL_uNativeFormat, GLOBAL_uOwnerFormat, GLOBAL_uObjectFormat;
CString GLOBAL_szFileName;
CStdioFile *pOleDump;
CTestApp app;
static CNewServer* GLOBAL_pServer;

/////////////////////////////////////////////////////////////////////////////
// CTestServer::CTestServer()
//
CTestServer::CTestServer()
{
	m_bDirty = FALSE;
	m_bLogging = FALSE;
	m_bUntitled = TRUE;
	m_pItem = NULL;

	VERIFY(Create(NULL, "Test Server",
		WS_OVERLAPPEDWINDOW, rectDefault, NULL, "MainMenu"));

	if (m_bCreationFailed)
	{
		TRACE("CTestServer::CTestServer : OnCreate failed\n");
		if (m_pDoc->IsOpen())
		{
			m_pDoc->BeginRevoke();
		}
		DestroyWindow();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnCreate(LPCREATESTRUCT p)
//
int CTestServer::OnCreate(LPCREATESTRUCT p)
{
	// suppress 'unused formal parameter' warnings

	(void) p;

	CRect rect;
	GetClientRect(&rect);

	m_pList = new CListBox();
	if (!m_pList->Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL | 
		LBS_STANDARD | LBS_USETABSTOPS, rect, this, IDC_LIST))
	{
		TRACE("Error creating listbox\n");
		return -1;
	}

	m_pList->SetTabStops(40);

	TRY
	{

		m_pServer = GLOBAL_pServer;

		// if we are being instantiated directly, go ahead and create the
		// document and register it as an untitled.

		m_pDoc = new CServDoc("Untitled");

		if (GLOBAL_bRegisterDoc)
		{
			if (!m_pDoc->Register(m_pServer, GLOBAL_szFileName))
			{
				m_bCreationFailed = TRUE;
				return 0;
			}
			m_szFileName = GLOBAL_szFileName;

			if (!LoadFile(m_szFileName))
			{
				TRACE("CTestServer::OnCreate : LoadFile failed.\n");
				m_bCreationFailed = TRUE;
				return 0;
			}

			m_pItem->m_pOwner = this;
			m_bUntitled = FALSE;
		}

		if (!GLOBAL_bEmbedded)
		{
			TRACE("Registering Server for Non Embedded\n");
			if (!m_pDoc->Register(m_pServer, "Untitled"))
			{
				m_bCreationFailed = TRUE;
				return 0;
			}
		}
	}
	CATCH (COleException, e)
	{
		MessageBox ("Registrations Didn't Work","Test Server",
			MB_ICONEXCLAMATION);
	}
	END_CATCH

	return 0;
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnInitMenu(CMenu* pMenu)
//

void CTestServer::OnInitMenu(CMenu* pMenu)
{
	CMenu *myMenu;
	myMenu = GetMenu();

	if (myMenu != pMenu)
	{
		return;
	}

	// Set up file menus
	if ((GLOBAL_bRegisterDoc) || (m_pItem != NULL))
	{
		pMenu->EnableMenuItem(IDM_SAVE, MF_ENABLED);
		pMenu->EnableMenuItem(IDM_SAVEAS, MF_ENABLED);
		pMenu->EnableMenuItem(IDM_COPYLINK, MF_ENABLED);
		pMenu->EnableMenuItem(IDM_COPYOBJECT, MF_ENABLED);
	}
	else
	{
		pMenu->EnableMenuItem(IDM_SAVE, MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(IDM_SAVEAS, MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(IDM_COPYLINK, MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(IDM_COPYOBJECT, MF_DISABLED | MF_GRAYED);
	}   

	if ((m_pItem != NULL) && (m_pItem->IsConnected()))
	{
		pMenu->EnableMenuItem(IDM_CLOSEDOC, MF_ENABLED);
		pMenu->EnableMenuItem(IDM_CHANGEDOC, MF_ENABLED);
		pMenu->EnableMenuItem(IDM_CHANGEITEM, MF_ENABLED);
	}
	else
	{
		pMenu->EnableMenuItem(IDM_CLOSEDOC, MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(IDM_CHANGEDOC, MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(IDM_CHANGEITEM, MF_DISABLED | MF_GRAYED);
	}


	// Don't allow copying links unless the file has been saved
	if (!m_szFileName.IsEmpty())
	{
		pMenu->EnableMenuItem(IDM_COPYLINK, MF_ENABLED);
	}
	else
	{
		pMenu->EnableMenuItem(IDM_COPYLINK, MF_DISABLED | MF_GRAYED);
	}


	// Don't allow calling CloseDocApi if Embedded will cause problems.
	// do it through the normal route.
	if (GLOBAL_bEmbedded && !GLOBAL_bRegisterDoc)
	{
		pMenu->EnableMenuItem(IDM_CLOSEDOC, MF_DISABLED | MF_GRAYED);
	}

	CMenu *pTestMenu;

	// pTestMenu is the Test submenu and should be position 2
	pTestMenu = pMenu->GetSubMenu(2);
	ASSERT (pTestMenu != NULL);

	// Disable/Enable Test/Document/Server API Popup Menu
	if ((m_pDoc != NULL) && (m_pDoc->IsOpen()))
	{
		pTestMenu->EnableMenuItem(2, MF_ENABLED | MF_BYPOSITION);
		pTestMenu->EnableMenuItem(3, MF_ENABLED | MF_BYPOSITION);

	}
	else
	{
		pTestMenu->EnableMenuItem(2, MF_DISABLED | MF_GRAYED | MF_BYPOSITION);
		pTestMenu->EnableMenuItem(3, MF_DISABLED | MF_GRAYED | MF_BYPOSITION);
	}
}

	




/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnSize()
//
void CTestServer::OnSize(UINT nType, int cx, int cy)
{
	CRect listRect;
	GetClientRect(&listRect);

	m_pList->MoveWindow(listRect,TRUE);
	CFrameWnd::OnSize(nType, cx, cy);
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnNew()
//
void CTestServer::OnNew()
{
	char szBuf[80];
	int nResponse;
	ASSERT_VALID (this);

	// if any object is currently around, ask to save it

	if (m_bDirty)
	{
		nResponse = MessageBox("Save changes to file?","Test Server", 
			MB_YESNOCANCEL | MB_ICONQUESTION);

		if (nResponse == IDCANCEL)
		{
			return;     // user selected CANCEL
		}

		if (nResponse == IDYES)
		{
			SaveFile(m_bUntitled);
		}
	}

	TRY
	{
		if ((m_pDoc != NULL) && (m_pDoc->IsOpen()))
		{
			m_pDoc->Revoke();       // will revoke CServItem as well
		}

		// delete off old objects as they are useless.  Deleting the
		// document will also delete the item since it is embedded.
		delete m_pDoc;

		// clean up pointers
		m_pDoc = NULL;
		m_pItem = NULL;

		m_pDoc = new CServDoc("Untitled");

		if (!m_pDoc->Register(m_pServer, "Untitled"))
		{
			AfxThrowOleException(OLE_ERROR_REGISTRATION);
		}

		m_pItem = new CServItem(this, m_pDoc, "Untitled", 
			CreateNewUniqueName(szBuf));
		m_bUntitled = TRUE;
		m_pDoc->m_pItem = m_pItem;      // set document's item to this one
		m_pItem->m_pOwner = this;
		CEditObjectDlg editObject(this, m_pItem->m_Text);

		if (editObject.DoModal() == IDOK)
		{
			m_pItem->m_Text = editObject.m_Text;
		}
		m_pList->ResetContent();
		m_pList->AddString(m_pItem->m_Text);
		SetWindowText((LPCSTR)AfxGetAppName());
	}
	CATCH(CException, e)
	{
		MessageBox("Unable to perform file new.  Please exit program.",
			"Test Server", MB_ICONEXCLAMATION);

		if (m_pDoc)
		{
			delete m_pDoc;
		}

		if (m_pItem)
		{
			delete m_pItem;
		}
	}
	END_CATCH
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnUpdate()
//
void CTestServer::OnUpdate()
{
	ASSERT_VALID (this);

	TRACE("In OnUpdate\n");
	m_pDoc->NotifySaved();
	m_bDirty = FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnClose()
//
void CTestServer::OnClose()
{
	ASSERT_VALID (this);

	if (GLOBAL_bEmbedded && !GLOBAL_bRegisterDoc)
	{
		if (!QueryUpdateClient())
		{
			return; // user selected cancel
		}
	}
	else
	{
		if (!QuerySaveChanges())
		{
			return;     // user selected cancel
		}
	}
	m_pServer->BeginRevoke();
}




/////////////////////////////////////////////////////////////////////////////
// CTestServer::QueryUpdateClient()
//
BOOL CTestServer::QueryUpdateClient()
{
	ASSERT_VALID (this);
	if (!m_bDirty)
	{
		return TRUE;
	}

	int nResponse;
	nResponse = MessageBox("Update client before exit?", "Test Server",
		MB_YESNOCANCEL | MB_ICONQUESTION);

	if (nResponse == IDCANCEL)
	{
		return FALSE;
	}
	
	if (nResponse == IDYES)
	{
		m_pDoc->NotifySaved();

		EnableWindow(FALSE);
		MSG msg;

		for (int i=0; i<10000; i++)
		{
			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{   
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
				
		EnableWindow(TRUE);
	}
	return TRUE;
}




/////////////////////////////////////////////////////////////////////////////
// CTestServer::QuerySaveChanges()
//
BOOL CTestServer::QuerySaveChanges()
{
	ASSERT_VALID (this);
	if (!m_bDirty)
	{
		return TRUE;
	}
	 
	int nResponse;
	nResponse = MessageBox("Save file before exit?", "Test Server",
		MB_YESNOCANCEL | MB_ICONQUESTION);

	if (nResponse == IDCANCEL)
	{
		return FALSE;
	}
	
	if (nResponse == IDYES)
	{
		SaveFile(m_bUntitled);
	}
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnAbout()
//
void CTestServer::OnAbout()
{
	CModalDialog about(IDDT_ABOUT, this);
	about.DoModal();
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnMenuExit()
//
void CTestServer::OnMenuExit()
{
	PostMessage(WM_CLOSE);
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::~CTestServer()
//
CTestServer::~CTestServer()
{
	if (m_pDoc)
	{
		TRACE("Now Deleting the document\n");
		delete m_pDoc;
		m_pDoc = NULL;
	}


	if (m_bLogging)
	{   
		if (pOleDump)
		{
			pOleDump->Flush();
			pOleDump->Close();
			delete pOleDump;
			pOleDump = NULL;
		}
	}

	if (m_pList)
	{
		delete m_pList;
		m_pList = NULL;
	}
}



#ifdef _DEBUG
void CTestServer::AssertValid() const
{
	CFrameWnd::AssertValid();
	ASSERT(m_pDoc != NULL);
	ASSERT(m_pServer != NULL);
}


void CTestServer::Dump (CDumpContext &dc) const 
{
	dc << "\nCTestServer Dump Beginning\n";
	CFrameWnd::Dump(dc);

	dc << "\nCurrent FileName is:  " << m_szFileName;

	if (m_pDoc)
	{
		m_pDoc->Dump(dc);
		dc << "\n";
	}
	else
	{
		dc << "\nNo CServDoc is present\n";
	}

	if (m_pServer)
	{
		m_pServer->Dump(dc);
		dc << "\n";
	}
	else
	{
		dc << "\nNo CNewServer is present\n";
	}

	if (!GLOBAL_bRegisterDoc)
	{
		if (m_pItem)
		{
			m_pItem->Dump(dc);
			dc << "\n";
		}
		else
		{
			dc << "\nNo CServItem is present\n";
		}
	}
}
#endif  



BEGIN_MESSAGE_MAP(CTestServer, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_INITMENU()
	ON_COMMAND(IDM_NEW, OnNew)
	ON_COMMAND(IDM_OPEN, OnOpen)
	ON_COMMAND(IDM_SAVE, OnSave)
	ON_COMMAND(IDM_SAVEAS, OnSaveAs)
	ON_COMMAND(IDM_UPDATE, OnUpdate)
	ON_COMMAND(IDM_EXIT, OnMenuExit)
	ON_COMMAND(IDM_COPYLINK, OnCopyLink)
	ON_COMMAND(IDM_COPYOBJECT, OnCopyObject)
	ON_COMMAND(IDM_LOGGING, OnLogging)
	ON_COMMAND(IDM_REVOKESVR, OnRevokeServerApi)
	ON_COMMAND(IDM_REVOKEDOC, OnRevokeDocApi)
	ON_COMMAND(IDM_REVERTDOC, OnRevertDocApi)
	ON_COMMAND(IDM_SAVEDOC, OnSaveDocApi)
	ON_COMMAND(IDM_CLOSEDOC, OnCloseDocApi)
	ON_COMMAND(IDM_CHANGEDOC, OnChangeDocApi)
	ON_COMMAND(IDM_CHANGEITEM, OnChangeItemApi)
	ON_COMMAND(IDM_ABOUT, OnAbout)
END_MESSAGE_MAP()


BOOL CTestApp::InitInstance()
{
	// Following the OLE V1.0 SDK, the clipboard formats are registered.
	// Note the stream, document, and client are all created in testserv.h.
	GLOBAL_uNativeFormat = RegisterClipboardFormat("Native");
	GLOBAL_uOwnerFormat = RegisterClipboardFormat("OwnerLink");
	GLOBAL_uObjectFormat = RegisterClipboardFormat("ObjectLink");

	// A check is performed on each value returned by the register
	// operation.  

	if ((GLOBAL_uNativeFormat < 0xC000) && (GLOBAL_uNativeFormat > 0xFFFF))
	{
		MessageBox(m_pMainWnd->m_hWnd, "Native Data Clipboard Format Not Registered!",
			"TestServ", MB_ICONEXCLAMATION);
		return FALSE;
	}


	if ((GLOBAL_uOwnerFormat < 0xC000) && (GLOBAL_uOwnerFormat > 0xFFFF))
	{
		MessageBox(m_pMainWnd->m_hWnd, "OwnerLink Clipboard Format Not Registered!",
			"TestServ", MB_ICONEXCLAMATION);
		return FALSE;
	}


	if ((GLOBAL_uObjectFormat < 0xC000) && (GLOBAL_uObjectFormat > 0xFFFF))
	{
		MessageBox(m_pMainWnd->m_hWnd, "ObjectLink Clipboard Format Not Registered!",
			"TestServ", MB_ICONEXCLAMATION);
		return FALSE;
	}


	GLOBAL_bRegisterDoc = GLOBAL_bNoDisplay = GLOBAL_bEmbedded = FALSE;
	// check if run with /Embedding
	LPCSTR lpsz = m_lpCmdLine;

	while (*lpsz == ' ')
		lpsz++;
	if ((*lpsz == '-' || *lpsz == '/') &&
		_fstrncmp("Embedding", lpsz+1, 9) == 0)
	{
		lpsz += 10;
		TRACE("Embedding Detected\n");
		GLOBAL_bNoDisplay = TRUE;
		GLOBAL_bEmbedded = TRUE;
	}
	else
	{
		TRACE("Manual Startup Detected\n");
	}
 
	while (*lpsz == ' ') 
		lpsz++;

	if (*lpsz != '\0')
	{
		TRACE("Embedded Linking Detected\n");
		TRACE("FileName is:  %Fs\n",lpsz);
		GLOBAL_szFileName = lpsz;
		GLOBAL_bRegisterDoc = TRUE;

		CFileStatus status;     // check to see if the file exists

		// If the file doesn't exist, get out quick.
		if (!CFile::GetStatus(GLOBAL_szFileName, status))
		{
			return FALSE;
		}
	}
	else
	{
		TRACE("No Linking Detected\n");
	}

	GLOBAL_pServer = new CNewServer(GLOBAL_bEmbedded);

	// register name before server just in case
	AfxOleRegisterServerName("TestServ", "AFX OLE Test Server");

	if (!(GLOBAL_pServer->Register("TestServ", TRUE)))  // multi-instance
	{
		MessageBox(NULL, "Couldn't register server", "Test Server", MB_OK);
		return FALSE;
	}

	CTestServer* pWnd = new CTestServer;
	m_pMainWnd = pWnd;

	if (CTestServer::m_bCreationFailed)
	{
		// CTestServer::OnCreate failed because of OLE problems.  
		// CTestServer has been deleted and shouldn't be used.
		m_pMainWnd = pWnd = NULL;
		return FALSE;
	}

	if (GLOBAL_bEmbedded && !GLOBAL_bRegisterDoc)
	{
		pWnd->ShowWindow(SW_HIDE);

		CMenu *pMenu;
		pMenu = pWnd->GetMenu();

		pMenu->EnableMenuItem(IDM_NEW, MF_DISABLED | MF_GRAYED);
		pMenu->EnableMenuItem(IDM_OPEN, MF_DISABLED | MF_GRAYED);
		if (!pMenu->ModifyMenu(IDM_SAVE, MF_BYCOMMAND, IDM_UPDATE,
			"&Update"))
		{
			OutputLog("CTestServer::Didn't Change Save to Update in File Menu\n");
		}

		if (!pMenu->ModifyMenu(IDM_EXIT, MF_BYCOMMAND, IDM_EXIT,
			"E&xit and Return"))
		{
			OutputLog("CTestServer::Didn't Modify Exit in File Menu\n");
		}
	}
	else
	{
		pWnd->ShowWindow(m_nCmdShow);
	}
	pWnd->UpdateWindow();

	return TRUE;
}





int CTestApp::ExitInstance()
{
	ASSERT_VALID(this);

	int nRet;

	if (m_pMainWnd != NULL)
	{
		nRet = m_pMainWnd->DestroyWindow();
	}

	if (nRet != 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



