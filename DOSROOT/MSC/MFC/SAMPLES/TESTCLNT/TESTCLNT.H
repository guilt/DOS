// testclnt.h : testclnt.h is the prototypes for the AFXOLE Test Client.
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

#ifndef __TESTCLNT_H__
#define __TESTCLNT_H__

#include <afxole.h>
#include "newdoc.h"
#include "newclnt.h"

class CTestClient;

/////////////////////////////////////////////////////////////////////////////
// CTestClient:
// See testclnt.cpp for the code to the member functions and the message map.
//
class CTestClient : public CFrameWnd
{
public:
	DECLARE_DYNAMIC(CTestClient)

	CTestClient();
	~CTestClient();

	// Message Handling Routines
	afx_msg int  OnCreate(LPCREATESTRUCT p);
	afx_msg void OnDestroy();
	afx_msg void OnDrawClipboard();
	afx_msg void OnChangeCbChain(HWND hRemove, HWND hNew);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg BOOL OnCommand(UINT wParam, LONG lParam);

	// Command Table Messages
	afx_msg void OnMenuExit();
	afx_msg void OnEditLinks();
	afx_msg void OnAbout();
	afx_msg void OnPasteLink();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnInsertObject();
	afx_msg void OnFileSave();  
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnChanged();
	afx_msg void OnLogging();
	afx_msg void OnCloseApi();
	afx_msg void OnUpdateApi();
	afx_msg void OnReleaseApi();
	afx_msg void OnDeleteApi();
	afx_msg void OnReconnectApi();
	afx_msg void OnRevertApi();
	afx_msg void OnSavedApi();
	afx_msg void OnRevert();
	afx_msg void OnLinks();

	// Helper Routines which are not called by Windows Messages
	void DoVerb(UINT nVerb);
	BOOL DrawObject();
	void FixObjectBounds (CRect& rect);
	BOOL FileDlg(BOOL bOpen, int nMaxFile, LPSTR szFile);
	void Serialize(CArchive& ar);
	BOOL LoadFile(const char* pName);
	void SaveFile(BOOL bNewFileName);
	void LogError(char* pszFileName, int nStatus);
	BOOL QuerySaveChanges();
	void PrepareDC(CDC* pDC);

	CNewClient*         m_pClient;
	CNewClientDoc*      m_pDoc;
	CWnd*               m_pBorder;
	HWND                m_hWndNextView;
	CString             m_title, m_szFileName, m_szLogFile;
	BOOL                m_bRevertAvailable, m_bLogging, m_bUntitled, m_bDirty;

	// Controls for Information Window
	CListBox*           m_pClipFormat; 
	CListBox*           m_pObjectFormat;
	CStatic*            m_pInfoTitle;
	CStatic*            m_pItemTitle; 
	CStatic*            m_pClipTitle; 
	CStatic*            m_pObjectTitle;
	CStatic*            m_pNameTitle;
	
	DECLARE_MESSAGE_MAP()
};




/////////////////////////////////////////////////////////////////////////////
// CTheApp:
// See testclnt.cpp for the code to the InitInstance member function.
//
class CTheApp : public CWinApp
{
public:
	CTheApp() : CWinApp("testclnt") { }
	virtual BOOL InitInstance();
	BOOL PumpMessage();
};

/////////////////////////////////////////////////////////////////////////////

#endif // __TESTCLNT_H__

