// tsobject.cpp : This file contains code which implements the pure
//      virtual functions for CServItem which inherits from COleServerItem
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

LPSTR CreateNewUniqueName(LPSTR lpstr);
extern void OutputLog(const char* pText);
static char szPrefix[] = "Test Server # ";
static int GLOBAL_nCurrentNumber;


IMPLEMENT_SERIAL(CServItem,COleServerItem,0)

/////////////////////////////////////////////////////////////////////////////
// Edit Object dialog
CEditObjectDlg::CEditObjectDlg(CWnd* pWnd, CString stringText)
			: CModalDialog(IDDT_EDIT, pWnd)
{
	if (!stringText.IsEmpty())
	{
		m_Text = stringText;
	}
}

BOOL CEditObjectDlg::OnInitDialog()
{
	pWnd = (CEdit *)GetDlgItem(IDC_EDIT);
	pWnd->SetSel(-1);       // Select entire box
	pWnd->ReplaceSel(m_Text);
	pWnd->SetFocus();
	return TRUE;
}



void CEditObjectDlg::OnOK()
{
	char szBuf[40];
	pWnd = (CEdit*)GetDlgItem(IDC_EDIT);
	pWnd->GetWindowText(szBuf, sizeof(szBuf)-1);
	m_Text = szBuf;
	EndDialog(IDOK);
}



void CEditObjectDlg::OnCancel()
{
	EndDialog(IDCANCEL);
}



BEGIN_MESSAGE_MAP(CEditObjectDlg, CModalDialog)
	ON_COMMAND(IDC_OK, OnOK)
	ON_COMMAND(IDC_CANCEL, OnCancel)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CServItem::default constructor
//
CServItem::CServItem()
{
	m_pOwner = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CServItem::CServItem (CTestServer* pDoc, CServDoc* pDoc, LPOLECLIENT 
//          lpOleClient, LPCSTR lpszItemName, 
//          LPCSTR lpszItemName)
//
CServItem::CServItem(CTestServer *pTest, CServDoc* pDoc,
			LPCSTR lpszDocName, LPCSTR lpszItemName) 
{
	char szBuffer[80];
	ASSERT(pTest != NULL);
	ASSERT(pDoc != NULL);
	
	m_DocName = lpszDocName;
	m_ItemName = lpszItemName;

	if (pTest->m_bLogging)
	{
		wsprintf(szBuffer, 
			"Creating new CServItem with Parameters:  %x \t %x\n",
				pTest, pDoc);
		OutputLog(szBuffer);
	}

	m_pOwner = pTest;   // used to display window when embedded
	m_Text = "";
	m_pOwner->m_bDirty = TRUE;
	m_pOwner->m_pItem = this;
}




/////////////////////////////////////////////////////////////////////////////
// CServItem::Serialize(CArchive &ar)
//
void CServItem::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar << m_Text;
	}
	else
	{
		TRACE("Now loading the data\n");
		ar >> m_Text;
		char szBuf[80];
		m_ItemName = CreateNewUniqueName(szBuf);
	}
}



/////////////////////////////////////////////////////////////////////////////
// CServItem::OnShow (BOOL bTakeFocus)
//
OLESTATUS CServItem::OnShow (BOOL bTakeFocus)
{
	// if we are to take the focus, then we should bring up an edit
	// control with the text.  We assume here that we will be edited.
	// Otherwise we just draw the text with a particular rectangle

	m_pOwner->ShowWindow(SW_SHOWNORMAL);

	if (bTakeFocus != 0)
	{
		// Bring up Edit Box
		CEditObjectDlg editObject(NULL, m_Text);

		if (editObject.DoModal() == IDOK)
		{
			m_Text = editObject.m_Text;
		}

		m_pOwner->m_pList->ResetContent();
		m_pOwner->m_pList->AddString(m_Text);
		m_pOwner->Invalidate(TRUE);
		m_pOwner->m_bDirty = TRUE;
		char szBuf[80];
		m_ItemName = CreateNewUniqueName(szBuf);
		NotifyChanged();
	}
	return OLE_OK;
}



/////////////////////////////////////////////////////////////////////////////
// CServItem::OnSetBounds (LPRECT lpRect)
//
OLESTATUS CServItem::OnSetBounds (LPRECT lpRect)
{
	ASSERT_VALID (this);
	ASSERT (lpRect != NULL);

	m_Rect.top = lpRect->top;
	m_Rect.bottom = lpRect->bottom;
	m_Rect.left = lpRect->left;
	m_Rect.right = lpRect->right;
	return OLE_OK;
}




/////////////////////////////////////////////////////////////////////////////
// CServItem::OnDraw (CMetaFile* pDC)
//
BOOL CServItem::OnDraw(CMetaFileDC* pDC)
{
	ASSERT(pDC != NULL);
	BOOL bPass;
	pDC->SetMapMode(MM_TEXT);
	bPass = pDC->TextOut(10, 10, m_Text);

	return bPass;
}
	



LPSTR CreateNewUniqueName(LPSTR lpstr)
{
	wsprintf(lpstr, "%s%04d", (LPCSTR)szPrefix, GLOBAL_nCurrentNumber++);
	return(lpstr);
}





/////////////////////////////////////////////////////////////////////////////
// CServItem::OnGetTextData()
//
BOOL CServItem::OnGetTextData(CString &stringText)
{
	stringText = m_Text;
	return TRUE;
}
	



/////////////////////////////////////////////////////////////////////////////
// CServItem::GetLinkData()
//
HANDLE CServItem::GetLinkData()
{
	LPSTR       lpLink;
	HANDLE      hLink;
	int         len;
	CString     linkData, className;

	ASSERT_VALID(this);
	linkData = "TestServ";

	len = linkData.GetLength() + m_DocName.GetLength() + 
		m_ItemName.GetLength() + 4;

	hLink = GlobalAlloc(GMEM_DDESHARE | GHND, len + 1);
	lpLink = (LPSTR)GlobalLock(hLink);

	TRACE("linkData is: %s\n", (const char*)linkData);
	TRACE("m_DocName is:  %s\n", (const char*)m_DocName);
	TRACE("m_ItemName is:  %s\n", (const char*)m_ItemName);

	len = linkData.GetLength();
	lstrcpy(lpLink, linkData);
	lpLink += (len + 1);

	len = m_DocName.GetLength();
	lstrcpy(lpLink, m_DocName);
	lpLink += (len + 1);

	lstrcpy(lpLink, m_ItemName);
	len = linkData.GetLength();
	lpLink += (len + 1);
	*lpLink = '\0';     // Add a 2nd null terminating string

	GlobalUnlock(hLink);

	return hLink;
}





/////////////////////////////////////////////////////////////////////////////
// CServItem::OnRelease
//
OLESTATUS CServItem::OnRelease()
{
	OLESTATUS status;
	status = COleServerItem::OnRelease();
	if (status != OLE_OK)
	{
		MessageBox(NULL, "Error in Deleting Item", "Test Server",
			MB_ICONEXCLAMATION);
	}

	delete this;
	return status;
}



#ifdef _DEBUG
/////////////////////////////////////////////////////////////////////////////
// CServItem::AssertValid() const
//
void CServItem::AssertValid() const
{
	COleServerItem::AssertValid();
	ASSERT(m_pOwner != NULL);
}




/////////////////////////////////////////////////////////////////////////////
// CServItem::Dump (CDumpContext &dc)
//
void CServItem::Dump (CDumpContext &dc) const
{
	dc << "Beginning CServItem Dump\n";
	COleServerItem::Dump(dc);
	dc << "\nContains Text:  " << m_Text << "\n";
}
#endif



/////////////////////////////////////////////////////////////////////////////
