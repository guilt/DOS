// This is a part of the Microsoft Foundation Classes C++ library. 
// Copyright (C) 1992 Microsoft Corporation 
// All rights reserved. 
//  
// This source code is only intended as a supplement to the 
// Microsoft Foundation Classes Reference and Microsoft 
// QuickHelp documentation provided with the library. 
// See these sources for detailed information regarding the 
// Microsoft Foundation Classes product. 

//  Private AFX Windows globals

// from window.cpp
extern char NEAR _afxWnd[];
extern char NEAR _afxMDIFrameWnd[];
extern char NEAR _afxFrameWnd[];

extern void _AfxHookWindowCreate(register CWnd* pWnd);
extern BOOL _AfxUnhookWindowCreate();
extern LONG FAR PASCAL AFX_EXPORT 
	_AfxDlgProc(HWND hWnd, register UINT message, UINT wParam, LONG lParam);
extern UINT FAR PASCAL AFX_EXPORT
	_AfxCommDlgProc(HWND hWnd, register UINT message, UINT wParam, LONG lParam);

// Proc addresses for Win3.1 specifics
#ifndef _WINDLL
extern HOOKPROC (WINAPI* _afxSetWindowsHookExProc)(int, HOOKPROC, HINSTANCE, HTASK);
	// != NULL if Windows 3.1 or better
#endif //!_WINDLL

