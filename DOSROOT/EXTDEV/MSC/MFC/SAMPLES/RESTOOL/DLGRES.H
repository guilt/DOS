// dlgres.h : Structures, constants and inline helpers for REStoH.
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

#ifndef __DLGRES_H__
#define __DLGRES_H__

/////////////////////////////////////////////////////////////////////////////

typedef struct {
	long style;
	BYTE cdit;
	int x, y;
	int cx, cy;
} DLGTEMPLATE;

typedef struct {
	int x, y;
	int cx, cy;
	int id;
	long style;
	// next comes a zero-terminated string,
	// then comes a length byte, followed by some data
} DLGITEMTEMPLATE;

#define CODEBIT       0x80
#define BUTTONCODE    0x80
#define EDITCODE      0x81
#define STATICCODE    0x82
#define LISTBOXCODE   0x83
#define SCROLLBARCODE 0x84
#define COMBOBOXCODE  0x85

// CheckReadValue:
// Returns TRUE iff n isn't either 0 or -1.
//
inline BOOL CheckReadValue(int n)
{
	return (n != 0) && (n != -1);
}

// SkipString:
// Advances the given BYTE* past the string.  Also handles 0xFF/WORD ordinal
// string references.
//
inline BYTE* SkipString(BYTE* pb)
{
	// Special case for "ordinal" strings: if the first char is
	// 0xFF, then the next two chars are really an int.  Skip past it.
	if (*pb == 0xFF)
		return pb + 3;

	while (*pb++)
		;

	return pb;
};

/////////////////////////////////////////////////////////////////////////////

#endif // __DLGRES_H__

