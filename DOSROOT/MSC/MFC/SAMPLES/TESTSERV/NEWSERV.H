// newserv.h : This file contains prototypes which is specific to the
//              CNewServer class.
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


#ifndef __NEWSERV_H__
#define __NEWSERV_H__

/////////////////////////////////////////////////////////////////////////////
// CNewServer:
class CNewServer : public COleServer
{
public:
	CNewServer(BOOL bEmbedded) : COleServer(bEmbedded)
		{ };

protected:
// Overridables for OLE Server requests
	virtual COleServerDoc* OnOpenDoc(LPCSTR lpszDoc);
	virtual COleServerDoc* OnCreateDoc(LPCSTR lpszClass, LPCSTR lpszDoc);
	virtual COleServerDoc* OnEditDoc(LPCSTR lpszClass, LPCSTR lpszDoc);
	virtual COleServerDoc* OnCreateDocFromTemplate(LPCSTR lpszClass,
				LPCSTR lpszDoc, LPCSTR lpszTemplate);
};

/////////////////////////////////////////////////////////////////////////////

#endif // __NEWSERV_H__

