// servdoc.cpp : This file contains code which implements the pure
//  virtual functions for CServDoc which inherits from COleServerDoc.
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

static CString GLOBAL_szItemName = "TestServ";
extern void OutputLog(const char* pText);

/////////////////////////////////////////////////////////////////////////////
// CServDoc::CServDoc
//
CServDoc::CServDoc(LPCSTR lpszDoc)
{
	m_DocName = lpszDoc;
	m_pItem = NULL;
}



/////////////////////////////////////////////////////////////////////////////
// CServDoc::OnGetItem(LPCSTR lpszObjname)
//
COleServerItem* CServDoc::OnGetItem(LPCSTR lpszObjname)
{
	ASSERT_VALID(this);
	ASSERT(lpszObjname != NULL);

	if (m_pItem == NULL)
	{
		m_pItem = new CServItem((CTestServer*)AfxGetApp()->m_pMainWnd,
					this, m_DocName, lpszObjname);
	}

	return m_pItem;
}




/////////////////////////////////////////////////////////////////////////////
// CServDoc::OnGetDocument()
//
COleServerItem* CServDoc::OnGetDocument()
{
	ASSERT_VALID(this);

	// we return only the one object we have
	TRACE("CServDoc::OnGetDocument\n");

	TRACE("The current CServDoc.m_pItem is:  %x\n",m_pItem);
	if (m_pItem == NULL)
	{
		TRACE("We are about to create a new Item:  %x\n",m_pItem);
		m_pItem = new CServItem((CTestServer*)AfxGetApp()->m_pMainWnd,
					this, m_DocName, NULL);
	}

	TRACE("Returning New Item as %x\n",m_pItem);
	return m_pItem;
}




/////////////////////////////////////////////////////////////////////////////
// CServDoc::GetNextItem(POSITION &rPosition)
//
COleServerItem* CServDoc::GetNextItem(POSITION &rPosition)
{
	if (rPosition == NULL)
	{
		rPosition = (POSITION) 1;
		return m_pItem;
	}
	else
	{
		return NULL;
	}
}


#ifdef _DEBUG
/////////////////////////////////////////////////////////////////////////////
// CServDoc::AssertValid() const
//
void CServDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}




/////////////////////////////////////////////////////////////////////////////
// CServDoc::Dump(CDumpContext &dc) const
//
void CServDoc::Dump (CDumpContext &dc) const
{
	dc << "\nCServDoc Dump Beginning";
	COleServerDoc::Dump(dc);
	dc << "\nCServItem object at " << m_pItem;
}
#endif

/////////////////////////////////////////////////////////////////////////////
