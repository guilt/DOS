// resource.h : Defines the resource constants for the Test Client 
//              application.
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
//
// Note that this window only contains #define directives.  This makes it
// suitable for including in the testclnt.rc resource file.

#ifndef __RESOURCE_H__
#define __RESOURCE_H__

// File menu
#define IDM_OPEN            0x100
#define IDM_REVERT          0x101
#define IDM_SAVE            0x102
#define IDM_SAVEAS          0x103
#define IDM_EXIT            0x104

// Edit menu
#define IDM_COPY            0x200
#define IDM_PASTE           0x201
#define IDM_PASTELINK       0x202
#define IDM_LINKS           0x203

// Object Menu
#define IDM_INSERT_OBJECT   0x300
#define IDM_OBJECT_VERB_MIN 0x301
#define IDM_OBJECT_VERB_MAX 0x3ff

// Testing popup menu
#define IDM_LOGGING         0x400
#define IDM_CLOSE           0x401
#define IDM_UPDATE          0x402
#define IDM_RELEASE         0x403
#define IDM_DELETE          0x404
#define IDM_RECONNECT       0x405
#define IDM_REVERTDOC       0x406
#define IDM_SAVED           0x407

// Help Menu
#define IDM_ABOUT           0x500

#define IDDT_ABOUT          1

// Dialog control IDs
#define IDD_LISTBOX         0x1000

// commands (used as control IDs as well as notifications
#define IDC_OBJECTFORMAT    0x1010
#define IDC_CLIPFORMAT      0x100A
#define IDC_INFOTITLE       0x100B
#define IDC_INFOCLIPFORMAT  0x100C
#define IDC_INFOOBJECTFORMAT 0x100D
#define IDC_INFONAME        0x100E
#define IDC_INFOITEM        0x100F

// String Tables
#define IDS_APPNAME         0x2000

// Misc
#define ID_APPLICATION      1
#define ID_VERB_POS         21

#endif // __RESOURCE_H__

