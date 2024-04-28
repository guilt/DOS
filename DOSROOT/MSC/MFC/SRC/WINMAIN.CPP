// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "afxwin.h"
#pragma hdrstop

#ifdef AFX_CORE_SEG
#pragma code_seg(AFX_CORE_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
// Standard WinMain implementation
//  Can be replaced as long as 'AfxWinInit' is called first

#ifndef _WINDLL
extern "C"
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int nReturnCode = -1;

	// AFX internal initialization
	if (!AfxWinInit(hInstance, hPrevInstance, lpCmdLine, nCmdShow))
		goto InitFailure;

	// App global initializations (rare)
	if (hPrevInstance == NULL && !AfxGetApp()->InitApplication())
		goto InitFailure;

	// Perform specific initializations
	if (!AfxGetApp()->InitInstance())
		goto InitFailure;

	nReturnCode = AfxGetApp()->Run();

InitFailure:
	AfxWinTerm();
	return nReturnCode;
}
#else
// _WINDLL initialization

extern "C"
int FAR PASCAL LibMain(HINSTANCE hInstance,
	WORD wDataSegment, WORD wHeapSize, LPSTR lpszCmdLine)
{
	// Initialize DLL's instance(/module) not the app's
	if (!AfxWinInit(hInstance, NULL, lpszCmdLine, 0))
	{
		AfxWinTerm();
		return 0;       // Init Failed
	}

	// initialize the single instance DLL
	if (!AfxGetApp()->InitInstance())
	{
		AfxWinTerm();
		return 0;
	}

	// nothing to run
	return 1;   // ok
}

#endif //_WINDLL

/////////////////////////////////////////////////////////////////////////////
