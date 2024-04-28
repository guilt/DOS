// tsobject.h : This file contains prototypes for the CEditObjectDlg and
//      CServItem classes.  CServItem inherits from COleServerItem
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




#ifndef __TSOBJECT_H__
#define __TSOBJECT_H__

/////////////////////////////////////////////////////////////////////////////
class CServDoc;
class CTestServer;

class CEditObjectDlg : public CModalDialog
{   
public:
	CString m_Text;
	CEdit *pWnd;
	
	CEditObjectDlg(CWnd* pWnd, CString stringText);

	BOOL OnInitDialog();
	void OnOK();
	void OnCancel();

	DECLARE_MESSAGE_MAP()
};



class CServItem : public COleServerItem
{
	DECLARE_SERIAL(CServItem)
public:
	// constructors and destructors
	CServItem(CTestServer *pTest, CServDoc* pDoc, 
		LPCSTR lpszDocName, LPCSTR lpszItemName);
	CServItem();

	// Non-required overrides and helper functions
	virtual BOOL        OnGetTextData(CString &stringText);
	virtual HANDLE      GetLinkData();
	virtual OLESTATUS   OnRelease();
			void        SetDocName(LPCSTR pName) 
							{ m_DocName = pName; };
			BOOL        IsConnected() 
							{ return COleServerItem::IsConnected(); };

	// Debugging functions
#ifdef _DEBUG
	virtual void        AssertValid() const;
	virtual void        Dump (CDumpContext &dc) const;
#endif

	// public attributes
	CString         m_Text;
	CTestServer*    m_pOwner;
	CRect           m_Rect;

// Overridables
protected:
	virtual OLESTATUS   OnShow(BOOL bTakeFocus);
	virtual OLESTATUS   OnSetBounds(LPRECT lpRect);
	virtual BOOL        OnDraw(CMetaFileDC* pDC);
	void Serialize (CArchive &ar);

	// protected attributes
	CString m_DocName;
	CString m_ItemName;
};


/////////////////////////////////////////////////////////////////////////////

#endif // __TSOBJECT_H__
