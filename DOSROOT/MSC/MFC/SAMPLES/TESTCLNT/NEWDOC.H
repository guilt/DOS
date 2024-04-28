// newdoc.h : This file contains prototypes for the CNewClientDoc class
//              which inherits from the COleClientDoc class.
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

#ifndef __NEWDOC_H__
#define __NEWDOC_H__

class CTestClient;

class CNewClientDoc : public COleClientDoc
{
	DECLARE_DYNAMIC(CNewClientDoc)

// Constructors and Destructors
public:
	CNewClientDoc(CTestClient* pParent);
	CNewClientDoc() { m_pOwner = NULL; };
	~CNewClientDoc();

// implementations for pure virtual function(s)
	virtual COleClientItem* GetNextItem(POSITION& rPosition, BOOL*);

// member variables
protected:
	CTestClient* m_pOwner;
};

#endif  // __NEWDOC_H__


