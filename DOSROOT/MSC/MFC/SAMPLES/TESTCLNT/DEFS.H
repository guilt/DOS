// defs.h -- This file contains definitions which are not considered
//           to be resource dependent.
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


#ifndef __DEFS_H__
#define __DEFS_H__

#define FILENAMELEN 128
#define CBOBJNAMEMAX    32
#define KEYNAMESIZE 300
#define CBOBJMAXNAME    14
#define CXDEFAULT       120
#define CYDEFAULT       100
#define OLEVERB_PLAY    1

#define new DEBUG_NEW

LPSTR CreateNewUniqueName(LPSTR lpstr);


static char *szDefinedFormat[] =
{
	{ "CF_TEXT" },
	{ "CF_BITMAP" },      
	{ "CF_METAFILEPICT" },
	{ "CF_SYLK" },
	{ "CF_DIF" },
	{ "CF_TIFF" },         
	{ "CF_OEMTEXT" },      
	{ "CF_DIB" },          
	{ "CF_PALETTE" }
};     


static char *szOwnerFormat[] = 
{
	{ "CF_OWNERDISPLAY" },
	{ "CF_DSPTEXT" },     
	{ "CF_DSPBITMAP" },   
	{ "CF_DSPMETAFILEPICT" }
};




#endif // __DEFS_H__
