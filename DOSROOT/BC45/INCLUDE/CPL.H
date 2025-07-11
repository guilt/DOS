#if !defined(__FLAT__)
/*****************************************************************************\
*                                                                             *
* cpl.h -       Control panel extension DLL definitions                       *
*                                                                             *
*               Version 3.10                                                  *
*                                                                             *
******************************************************************************
*  General rules for being installed in the Control Panel:
*
*      1) The DLL must export a function named CPlApplet which will handle
*         the messages discussed below.
*      2) If the applet needs to save information in CONTROL.INI minimize
*         clutter by using the application name [MMCPL.appletname].
*      2) If the applet is refrenced in CONTROL.INI under [MMCPL] use
*         the following form:
*              ...
*              [MMCPL]
*              uniqueName=c:\mydir\myapplet.dll
*              ...
*
*
*  The order applet DLL's are loaded by CONTROL.EXE is:
*
*      1) MAIN.CPL is loaded from the windows system directory.
*
*      2) Installable drivers that are loaded and export the
*         CplApplet() routine.
*
*      3) DLL's specified in the [MMCPL] section of CONTROL.INI.
*
*      4) DLL's named *.CPL from windows system directory.
*
*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef _INC_CPL
#define _INC_CPL
#define __CPL_H

#include <pshpack1.h>

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif /* __cplusplus */

/*
 * CONTROL.EXE will answer this message and launch an applet
 *
 * WM_CPL_LAUNCH
 *
 *      wParam      - window handle of calling app
 *      lParam      - LPTSTR of name of applet to launch
 *
 * WM_CPL_LAUNCHED
 *
 *      wParam      - TRUE/FALSE if applet was launched
 *      lParam      - NULL
 *
 * CONTROL.EXE will post this message to the caller when the applet returns
 * (ie., when wParam is a valid window handle)
 *
 */
#define WM_CPL_LAUNCH   (WM_USER+1000)
#define WM_CPL_LAUNCHED (WM_USER+1001)

/* A function prototype for CPlApplet() */

typedef LRESULT (CALLBACK *APPLET_PROC)(HWND hwndCpl, UINT msg, LPARAM lParam1, LPARAM lParam2);

/* The data structure CPlApplet() must fill in. */

typedef struct tagCPLINFO
{
    int     idIcon;     /* icon resource id, provided by CPlApplet() */
    int     idName;     /* name string res. id, provided by CPlApplet() */
    int     idInfo;     /* info string res. id, provided by CPlApplet() */
    LONG    lData;      /* user defined data */
} CPLINFO, *PCPLINFO, FAR *LPCPLINFO;

typedef struct tagNEWCPLINFO
{
    DWORD       dwSize;         /* similar to the commdlg */
    DWORD       dwFlags;
    DWORD       dwHelpContext;  /* help context to use */
    LONG        lData;          /* user defined data */
    HICON       hIcon;          /* icon to use, this is owned by CONTROL.EXE (may be deleted) */
    char        szName[32];     /* short name */
    char        szInfo[64];     /* long name (status line) */
    char        szHelpFile[128];/* path to help file to use */
} NEWCPLINFO, *PNEWCPLINFO, FAR *LPNEWCPLINFO;

/* The messages CPlApplet() must handle: */

#define CPL_INIT        1
/*  This message is sent to indicate CPlApplet() was found. */
/*  lParam1 and lParam2 are not defined. */
/*  Return TRUE or FALSE indicating whether the control panel should proceed. */


#define CPL_GETCOUNT    2
/*  This message is sent to determine the number of applets to be displayed. */
/*  lParam1 and lParam2 are not defined. */
/*  Return the number of applets you wish to display in the control */
/*  panel window. */


#define CPL_INQUIRE     3
/*  This message is sent for information about each applet. */
/*  lParam1 is the applet number to register, a value from 0 to */
/*  (CPL_GETCOUNT - 1).  lParam2 is a far ptr to a CPLINFO structure. */
/*  Fill in CPL_INFO's idIcon, idName, idInfo and lData fields with */
/*  the resource id for an icon to display, name and description string ids, */
/*  and a long data item associated with applet #lParam1. */


#define CPL_SELECT      4
/*  This message is sent when the applet's icon has been clicked upon. */
/*  lParam1 is the applet number which was selected.  lParam2 is the */
/*  applet's lData value. */


#define CPL_DBLCLK      5
/*  This message is sent when the applet's icon has been double-clicked */
/*  upon.  lParam1 is the applet number which was selected.  lParam2 is the */
/*  applet's lData value. */
/*  This message should initiate the applet's dialog box. */


#define CPL_STOP        6
/*  This message is sent for each applet when the control panel is exiting. */
/*  lParam1 is the applet number.  lParam2 is the applet's lData  value. */
/*  Do applet specific cleaning up here. */


#define CPL_EXIT        7
/*  This message is sent just before the control panel calls FreeLibrary. */
/*  lParam1 and lParam2 are not defined. */
/*  Do non-applet specific cleaning up here. */


#define CPL_NEWINQUIRE    8
/* this is the same as CPL_INQUIRE execpt lParam2 is a pointer to a */
/* NEWCPLINFO structure.  this will be sent before the CPL_INQUIRE */
/* and if it is responed to (return != 0) CPL_INQUIRE will not be sent */

#define CPL_DO_PRINTER_SETUP    100    /* ;Internal */
#define CPL_DO_NETPRN_SETUP     101    /* ;Internal */

/* This message is internal to the Control Panel and MAIN applets.  */
/* It is only sent when an applet is invoked from the Command line  */
/* during system installation.                                      */
#define CPL_SETUP               200

#ifdef __cplusplus
}
#endif    /* __cplusplus */

#include <poppack.h>

#endif  /* _INC_CPL */


#else /* !__FLAT__ */
/*****************************************************************************\
*                                                                             *
* cpl.h -       Control panel extension DLL definitions                       *
*                                                                             *
*               Version 3.10                                                  *
*                                                                             *
*               Copyright (c) 1992-1995, Microsoft Corp.  All rights reserved *
*                                                                             *
******************************************************************************/
/*
*  General rules for being installed in the Control Panel:
*
*      1) The DLL must export a function named CPlApplet which will handle
*         the messages discussed below.
*      2) If the applet needs to save information in CONTROL.INI minimize
*         clutter by using the application name [MMCPL.appletname].
*      2) If the applet is refrenced in CONTROL.INI under [MMCPL] use
*         the following form:
*              ...
*              [MMCPL]
*              uniqueName=c:\mydir\myapplet.dll
*              ...
*
*
*  The order applet DLL's are loaded by CONTROL.EXE is:
*
*      1) MAIN.CPL is loaded from the windows system directory.
*
*      2) Installable drivers that are loaded and export the
*         CplApplet() routine.
*
*      3) DLL's specified in the [MMCPL] section of CONTROL.INI.
*
*      4) DLL's named *.CPL from windows system directory.
*
*/
#ifndef _INC_CPL
#define _INC_CPL


#include <pshpack1.h>   /* Assume byte packing throughout */

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif /* __cplusplus */

/*
 * CONTROL.EXE will answer this message and launch an applet
 *
 * WM_CPL_LAUNCH
 *
 *      wParam      - window handle of calling app
 *      lParam      - LPTSTR of name of applet to launch
 *
 * WM_CPL_LAUNCHED
 *
 *      wParam      - TRUE/FALSE if applet was launched
 *      lParam      - NULL
 *
 * CONTROL.EXE will post this message to the caller when the applet returns
 * (ie., when wParam is a valid window handle)
 *
 */
#define WM_CPL_LAUNCH   (WM_USER+1000)
#define WM_CPL_LAUNCHED (WM_USER+1001)

/* A function prototype for CPlApplet() */

//typedef LRESULT (APIENTRY *APPLET_PROC)(HWND hwndCpl, UINT msg, LPARAM lParam1, LPARAM lParam2);
typedef LONG (APIENTRY *APPLET_PROC)(HWND hwndCpl, UINT msg, LONG lParam1, LONG lParam2);

/* The data structure CPlApplet() must fill in. */

typedef struct tagCPLINFO
{
    int     idIcon;     /* icon resource id, provided by CPlApplet() */
    int     idName;     /* name string res. id, provided by CPlApplet() */
    int     idInfo;     /* info string res. id, provided by CPlApplet() */
    LONG    lData;      /* user defined data */
} CPLINFO, *LPCPLINFO;

typedef struct tagNEWCPLINFOA
{
    DWORD   dwSize;         /* similar to the commdlg */
    DWORD   dwFlags;
    DWORD   dwHelpContext;  /* help context to use */
    LONG    lData;          /* user defined data */
    HICON   hIcon;          /* icon to use, this is owned by CONTROL.EXE (may be deleted) */
    CHAR    szName[32];     /* short name */
    CHAR    szInfo[64];     /* long name (status line) */
    CHAR    szHelpFile[128];/* path to help file to use */
} NEWCPLINFOA, *LPNEWCPLINFOA;
typedef struct tagNEWCPLINFOW
{
    DWORD   dwSize;         /* similar to the commdlg */
    DWORD   dwFlags;
    DWORD   dwHelpContext;  /* help context to use */
    LONG    lData;          /* user defined data */
    HICON   hIcon;          /* icon to use, this is owned by CONTROL.EXE (may be deleted) */
    WCHAR   szName[32];     /* short name */
    WCHAR   szInfo[64];     /* long name (status line) */
    WCHAR   szHelpFile[128];/* path to help file to use */
} NEWCPLINFOW, *LPNEWCPLINFOW;
#ifdef UNICODE
typedef NEWCPLINFOW NEWCPLINFO;
typedef LPNEWCPLINFOW LPNEWCPLINFO;
#else
typedef NEWCPLINFOA NEWCPLINFO;
typedef LPNEWCPLINFOA LPNEWCPLINFO;
#endif // UNICODE

/* The messages CPlApplet() must handle: */

#if(WINVER >= 0x0400)
#define CPL_DYNAMIC_RES 0
// This constant may be used in place of real resource IDs for the idIcon,
// idName or idInfo members of the CPLINFO structure.  Normally, the system
// uses these values to extract copies of the resources and store them in a
// cache.  Once the resource information is in the cache, the system does not
// need to load a CPL unless the user actually tries to use it.
// CPL_DYNAMIC_RES tells the system not to cache the resource, but instead to
// load the CPL every time it needs to display information about an item.  This
// allows a CPL to dynamically decide what information will be displayed, but
// is SIGNIFICANTLY SLOWER than displaying information from a cache.
// Typically, CPL_DYNAMIC_RES is used when a control panel must inspect the
// runtime status of some device in order to provide text or icons to display.

#endif /* WINVER >= 0x0400 */

#define CPL_INIT        1
/*  This message is sent to indicate CPlApplet() was found. */
/*  lParam1 and lParam2 are not defined. */
/*  Return TRUE or FALSE indicating whether the control panel should proceed. */


#define CPL_GETCOUNT    2
/*  This message is sent to determine the number of applets to be displayed. */
/*  lParam1 and lParam2 are not defined. */
/*  Return the number of applets you wish to display in the control */
/*  panel window. */


#define CPL_INQUIRE     3
/*  This message is sent for information about each applet. */
/*  lParam1 is the applet number to register, a value from 0 to */
/*  (CPL_GETCOUNT - 1).  lParam2 is a far ptr to a CPLINFO structure. */
/*  Fill in CPL_INFO's idIcon, idName, idInfo and lData fields with */
/*  the resource id for an icon to display, name and description string ids, */
/*  and a long data item associated with applet #lParam1. */


#define CPL_SELECT      4
/*  This message is sent when the applet's icon has been clicked upon. */
/*  lParam1 is the applet number which was selected.  lParam2 is the */
/*  applet's lData value. */


#define CPL_DBLCLK      5
/*  This message is sent when the applet's icon has been double-clicked */
/*  upon.  lParam1 is the applet number which was selected.  lParam2 is the */
/*  applet's lData value. */
/*  This message should initiate the applet's dialog box. */


#define CPL_STOP        6
/*  This message is sent for each applet when the control panel is exiting. */
/*  lParam1 is the applet number.  lParam2 is the applet's lData  value. */
/*  Do applet specific cleaning up here. */


#define CPL_EXIT        7
/*  This message is sent just before the control panel calls FreeLibrary. */
/*  lParam1 and lParam2 are not defined. */
/*  Do non-applet specific cleaning up here. */


#define CPL_NEWINQUIRE    8
/* this is the same as CPL_INQUIRE execpt lParam2 is a pointer to a */
/* NEWCPLINFO structure.  this will be sent before the CPL_INQUIRE */
/* and if it is responed to (return != 0) CPL_INQUIRE will not be sent */

#if(WINVER >= 0x0400)
#define CPL_STARTWPARMS 9
/* this message parallels CPL_DBLCLK in that the applet should initiate
** its dialog box.  where it differs is that this invocation is coming
** out of RUNDLL, and there may be some extra directions for execution.
** lParam1: the applet number.
** lParam2: an LPSTR to any extra directions that might exist.
** returns: TRUE if the message was handled; FALSE if not.
*/
#endif /* WINVER >= 0x0400 */


/* This message is internal to the Control Panel and MAIN applets.  */
/* It is only sent when an applet is invoked from the Command line  */
/* during system installation.                                      */
#define CPL_SETUP               200 

#ifdef __cplusplus
}
#endif    /* __cplusplus */

#include <poppack.h>

#endif  /* _INC_CPL */


#endif /* !__FLAT__ */
