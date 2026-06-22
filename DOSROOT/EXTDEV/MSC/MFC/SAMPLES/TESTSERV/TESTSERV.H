// testserv.h : This file contains prototypes for the CTestServer class
//              which inherits from CFrameWnd.
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


#ifndef __TESTSERV_H__
#define __TESTSERV_H__

#include <afxole.h>
#include "tsobject.h"
#include "servdoc.h"
#include "newserv.h"



/////////////////////////////////////////////////////////////////////////////
// CTestServer:
class CTestServer : public CFrameWnd
{
public:
	CTestServer();
	~CTestServer();

	// windows messages
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnClose();

	// menu commands
	afx_msg void OnNew();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnSaveAs();
	afx_msg void OnUpdate();
	afx_msg void OnMenuExit();
	afx_msg void OnCopyLink();
	afx_msg void OnCopyObject();
	afx_msg void OnLogging();
	afx_msg void OnRevokeServerApi();
	afx_msg void OnRevokeDocApi();
	afx_msg void OnRevertDocApi();
	afx_msg void OnSaveDocApi();
	afx_msg void OnCloseDocApi();
	afx_msg void OnChangeDocApi();
	afx_msg void OnChangeItemApi();
	afx_msg void OnAbout();

	// helper functions which do not handle messages
	BOOL FileDlg (BOOL bOpen, int nMaxFile, LPSTR szFile);
	BOOL LoadFile (const char* pName);
	void Serialize (CArchive &ar);
	void SaveFile (BOOL bNewFileName);
	BOOL QuerySaveChanges();
	BOOL QueryUpdateClient();
	CServDoc* GetDocument() { return m_pDoc; };
	void LogError(char *pszFileName, int nStatus);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	// member variables
	static BOOL m_bCreationFailed;
	BOOL m_bDirty, m_bUntitled, m_bLogging;
	CServDoc*   m_pDoc;
	CNewServer* m_pServer;
	CServItem*  m_pItem;
	CListBox*   m_pList;
	CString m_szFileName;

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CTestApp:
// See testserv.cpp for the code to the InitInstance member function.
//
class CTestApp : public CWinApp
{
public:
	CTestApp() : CWinApp("Test Server") { }
	virtual BOOL InitInstance();
	virtual int  ExitInstance();
};


/////////////////////////////////////////////////////////////////////////////

#endif // __TESTSERV_H__
