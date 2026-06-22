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
// INTERNAL INTERNAL INTERNAL
// Do not explicitly include


#define CFile_shareMask ((UINT)(CFile::shareExclusive | CFile::shareDenyWrite | CFile::shareDenyRead | CFile::shareDenyNone | CFile::shareCompat))

#ifndef _WINDOWS
typedef  char FAR* LPSTR;
typedef  const char FAR* LPCSTR;
inline int AnsiToOem(LPCSTR src, LPSTR dst)
			{ _fstrcpy(dst, src); return -1; }
inline int OemToAnsi(LPCSTR src, LPSTR dst)
			{ _fstrcpy(dst, src); return -1; }
#endif

/////////////////////////////////////////////////////////////////////////////
#ifdef _DOSWIN
#include <dos.h>

#ifdef _WINDOWS
extern "C" void FAR PASCAL DOS3Call();
#define DOSCALL call DOS3Call
#else // _DOS
#define DOSCALL int 21h
#endif // _WINDOWS

#endif //_DOSWIN

/////////////////////////////////////////////////////////////////////////////
