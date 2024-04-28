// newclnt.h : This file contains prototypes for the CNewClient class 
//              which inherits from COleClientItem.
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


#ifndef __NEWCLNT_H__
#define __NEWCLNT_H__

class CTestClient;

class CNewClient : public COleClientItem
{
public:
	CNewClient(CTestClient* pParent, CNewClientDoc* pDoc);
	virtual void OnChange(OLE_NOTIFICATION wNotification);
	virtual void OnRenamed();

protected:
	CTestClient*    m_pTestClient;
};


#endif // __NEWCLNT_H__
