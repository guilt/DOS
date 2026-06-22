// newdoc.cpp : This file contains code for the CNewClientDoc class which
//              implements the pure virtual functions required by the
//              COleClientDoc class.
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


IMPLEMENT_DYNAMIC(CNewClientDoc,COleClientDoc)

/////////////////////////////////////////////////////////////////////////////
// CNewClientDoc constructor:
//
CNewClientDoc::CNewClientDoc(CTestClient *pParent) : COleClientDoc()
{
	m_pOwner = pParent;
}




/////////////////////////////////////////////////////////////////////////////
// CNewClientDoc destructor:
//
CNewClientDoc::~CNewClientDoc()
{
	m_pOwner = NULL;
}



/////////////////////////////////////////////////////////////////////////////
// CNewClientDoc GetNextItem(POSITION& rPosition, BOOL*)
//
COleClientItem* CNewClientDoc::GetNextItem(POSITION& rPosition, BOOL*)
{
	ASSERT(m_pOwner != NULL);

	if (rPosition == NULL)
	{
		rPosition = (POSITION) 1;
		return m_pOwner->m_pClient;
	}
	else
	{
		return NULL;
	}
}

