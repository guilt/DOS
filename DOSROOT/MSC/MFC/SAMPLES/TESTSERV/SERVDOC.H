// servdoc.h : This file contains prototypes for the CServDoc class
//              which inherits from COleServerDoc.
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

/////////////////////////////////////////////////////////////////////////////

#ifndef __SERVDOC_H__
#define __SERVDOC_H__

/////////////////////////////////////////////////////////////////////////////
// CServDoc:

class CServDoc : public COleServerDoc
{
public:
	CServDoc(LPCSTR lpszDoc);
	CServDoc() { m_DocName = "blank"; m_pItem = NULL; };
	~CServDoc() { m_pItem = NULL; };
 
	OLESTATUS BeginRevoke() { return COleServerDoc::BeginRevoke(); };

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump (CDumpContext &dc) const;
#endif

	CServItem* m_pItem;
	CString m_DocName;

// Overridables for OLE server
protected:
	virtual COleServerItem* OnGetItem(LPCSTR lpszObjname);
	virtual COleServerItem* OnGetDocument ();
	virtual COleServerItem* GetNextItem(POSITION &rPosition);
};

/////////////////////////////////////////////////////////////////////////////

#endif // __SERVDOC_H__

