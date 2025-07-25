/*****************************************************************************\
*                                                                             *
* custcntl.h -  Custom Control Library header file                            *
*                                                                             *
\*****************************************************************************/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined(__FLAT__)
#ifndef __CUSTCNTL_H    /* prevent multiple includes */
#define __CUSTCNTL_H

#ifndef __WINDOWS_H
#include <windows.h>    /* <windows.h> must be included */
#endif  /* __WINDOWS_H */

#ifndef RC_INVOKED
#pragma option -a-      /* Assume byte packing throughout */
#endif /* RC_INVOKED */

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

/* If included with the 3.0 windows.h, define compatible aliases */
#if !defined(WINVER) || (WINVER < 0x030a)
#define WINAPI      FAR PASCAL
#define CALLBACK    FAR PASCAL
#define LPCSTR      LPSTR
#define UINT        WORD
#define LPARAM      LONG
#define WPARAM      WORD
#define LRESULT     LONG
#define HMODULE     HANDLE
#define HINSTANCE   HANDLE
#define HLOCAL      HANDLE
#define HGLOBAL     HANDLE
#endif  /* WIN3.0 */

/*
 * Every custom control DLL must have three functions present,
 * and they must be exported by the following ordinals.
 */
#define CCINFOORD       2       /* information function ordinal */
#define CCSTYLEORD      3       /* styles function ordinal */
#define CCFLAGSORD      4       /* translate flags function ordinal */

/* general size definitions */
#define CTLTYPES        12      /* max number of control types */
#define CTLDESCR        22      /* max size of description */
#define CTLCLASS        20      /* max size of class name */
#define CTLTITLE        94      /* max size of control text */

/*
 * CONTROL STYLE DATA STRUCTURE
 *
 * This data structure is used by the class style dialog function
 * to set and/or reset various control attributes.
 *
 */
typedef struct tagCTLSTYLE
{
    UINT    wX;                 /* x origin of control */
    UINT    wY;                 /* y origin of control */
    UINT    wCx;                /* width of control */
    UINT    wCy;                /* height of control */
    UINT    wId;                /* control child id */
    DWORD   dwStyle;            /* control style */
    char    szClass[CTLCLASS];  /* name of control class */
    char    szTitle[CTLTITLE];  /* control text */
} CTLSTYLE;
typedef CTLSTYLE *      PCTLSTYLE;
typedef CTLSTYLE FAR*   LPCTLSTYLE;

/*
 * CONTROL DATA STRUCTURE
 *
 * This data structure is returned by the control options function
 * when inquiring about the capabilities of a particular control.
 * Each control may contain various types (with predefined style
 * bits) under one general class.
 *
 * The width and height fields are used to provide the host
 * application with a suggested size.  The values in these fields
 * are in rc coordinates.
 *
 */
typedef struct tagCTLTYPE
{
    UINT    wType;              /* type style */
    UINT    wWidth;             /* suggested width */
    UINT    wHeight;            /* suggested height */
    DWORD   dwStyle;            /* default style */
    char    szDescr[CTLDESCR];  /* description */
} CTLTYPE;

typedef struct tagCTLINFO
{
    UINT    wVersion;           /* control version */
    UINT    wCtlTypes;          /* control types */
    char    szClass[CTLCLASS];  /* control class name */
    char    szTitle[CTLTITLE];  /* control title */
    char    szReserved[10];     /* reserved for future use */
    CTLTYPE Type[CTLTYPES];     /* control type list */
} CTLINFO;
typedef CTLINFO *       PCTLINFO;
typedef CTLINFO FAR*    LPCTLINFO;

/* These two function prototypes are used by the dialog editor */
#ifdef STRICT
typedef DWORD   (CALLBACK* LPFNSTRTOID)(LPCSTR);
#else
typedef DWORD   (CALLBACK* LPFNSTRTOID)(LPSTR);
#endif
typedef UINT    (CALLBACK* LPFNIDTOSTR)(UINT, LPSTR, UINT);

/* function  prototypes left out of the original custcntl.h */

typedef HGLOBAL (CALLBACK *LPFNINFO)( void );
typedef BOOL            (CALLBACK *LPFNSTYLE)
(
  HWND    hWnd,
  HGLOBAL hCntlStyle,
  LPFNSTRTOID lpfnSID,
  LPFNIDTOSTR lpfnIDS
);

typedef UINT   (CALLBACK *LPFNFLAGS)
(
  DWORD   dwStyle,
  LPSTR   lpBuff,
  UINT    wBuffLength
);

/*****************************************************************************

  Resource Workshop has extended the MS Dialog editor's custom control
  API in three main areas:

  1) More than 1 custom control can be placed in a single DLL

  2) The "Info" data structure has been extended to allow custom controls
     to be added to the RW toolbox

  3) The style data structure has been extended to allow custom controls
     access to the CTLDATA field. This field contains up to 255 bytes
     of binary data. A pointer to this data is passed to the control
     in the WM_CREATE message at runtime.


*****************************************************************************/

/*****************************************************************************

  Two new fields have been added to the CTLTYPE data structure to
  make the RWCTLTYPE structure:

  hToolBit is a handle to a 24X24 bitmap which is added to the
  RW toolbox. If this field is 0, no button will be added for this style,
  and it will only be selectable via the Custom control dialog. This bitmap
  is "owned" by RW, and will be freed by RW when the dialog editor is
  unloaded.

  hDropCurs is a handle to a cursor which is used by RW when a user
  selects the control from the toolbox. If 0, a cross cursor will be used.


*****************************************************************************/

#define TOOLBIT_SIZE  24

typedef struct
{
   UINT       wType;                  /* type style */
   UINT       wWidth;                 /* suggested width */
   UINT       wHeight;                /* suggested height */
   DWORD      dwStyle;                /* default style */
   char       szDescr[CTLDESCR];      /* dialog name */
   HBITMAP    hToolBit;               // Toolbox bitmap
   HCURSOR    hDropCurs;              // Drag and drop cursor

} RWCTLTYPE, FAR * LPRWCTLTYPE;

/*****************************************************************************

  This structure reflects the RWCTLTYPE data structure

*****************************************************************************/


typedef struct
{
   UINT       wVersion;              /* control version */
   UINT       wCtlTypes;             /* control types */
   char       szClass[CTLCLASS];     /* control class name */
   char       szTitle[CTLTITLE];     /* control title */
   char       szReserved[10];        /* reserved for future use */
   RWCTLTYPE  Type[CTLTYPES];        /* Resource Workshop control type list */

} RWCTLINFO;

typedef RWCTLINFO *             PRWCTLINFO;
typedef RWCTLINFO FAR *         LPRWCTLINFO;

/*****************************************************************************

  Two new fields have been added to the CTLSTYLE data structure to make
  the RWCTLSTYLE data structure:

  CtlDataSize is the size of
  CtlData, which is an array of bytes passed to the control in the
  WM_CREATE message.


*****************************************************************************/

#define CTLDATALENGTH 255            // 255 bytes + Length Byte

typedef struct {
  UINT    wX;                       /* x origin of control */
  UINT    wY;                       /* y origin of control */
  UINT    wCx;                      /* width of control */
  UINT    wCy;                      /* height of control */
  UINT    wId;                      /* control child id */
  DWORD   dwStyle;                            /* control style */
  char    szClass[CTLCLASS];        /* name of control class */
  char    szTitle[CTLTITLE];        /* control text */
  BYTE    CtlDataSize;              // Control data Size
  BYTE    CtlData[ CTLDATALENGTH];  // Control data

} RWCTLSTYLE;

typedef RWCTLSTYLE *              PRWCTLSTYLE;
typedef RWCTLSTYLE FAR *          LPRWCTLSTYLE;

/*****************************************************************************

  In order to use RW's extensions to the custom controls, a custom
  control DLL *must* implement the ListClasses function. This function
  returns a global memory handle to an initialized CTLCLASSLIST data
  structure. All function pointers *must* point to valid functions.


*****************************************************************************/

typedef struct
{
  LPFNINFO  fnRWInfo;           // RW Info function
  LPFNSTYLE fnRWStyle;          // RW Style function
  LPFNFLAGS fnFlags;            // Flags function
  char  szClass[ CTLCLASS];

} RWCTLCLASS, FAR *LPRWCTLCLASS;

typedef struct
{
  short       nClasses;
#if defined (__cplusplus)
  RWCTLCLASS Classes[1];
#else
  RWCTLCLASS Classes[];
#endif

} CTLCLASSLIST, FAR *LPCTLCLASSLIST;

#ifdef STRICT
typedef HGLOBAL   (CALLBACK *LPFNLOADRES)( LPCSTR szType, LPCSTR szId);
typedef BOOL      (CALLBACK *LPFNEDITRES)( LPCSTR szType, LPCSTR szId);
#else
typedef HGLOBAL   (CALLBACK *LPFNLOADRES)( LPSTR szType, LPSTR szId);
typedef BOOL      (CALLBACK *LPFNEDITRES)( LPSTR szType, LPSTR szId);
#endif

#ifdef STRICT
typedef HGLOBAL (CALLBACK *LPFNLIST)
(
  LPSTR       szAppName,
  UINT        wVersion,
  LPFNLOADRES fnLoad,
  LPFNEDITRES fnEdit
);
#else
typedef HGLOBAL (CALLBACK *LPFNLIST)
(
  LPCSTR      szAppName,
  UINT        wVersion,
  LPFNLOADRES fnLoad,
  LPFNEDITRES fnEdit
);
#endif

#define DLGCUSTCLASSNAME   "_BorDlg_DlgEditChild"
#define DLGTESTCLASSNAME   "_BorDlg_DlgEditTest"


// Rw version 1.02 and above send a message to a control
// when the user is about to delete it. The message id
// is that returned by RegisterWindowMessage, with the following
// name:

#define RWDELETEMSGNAME "Rws_deletecontrol"


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#ifndef RC_INVOKED
#pragma option -a.      /* Revert to default packing */
#endif  /* RC_INVOKED */

#endif  /* __CUSTCNTL_H */

#else  /* !__FLAT__ */
/*****************************************************************************\
*                                                                             *
* custcntl.h -  Custom Control Library header file                            *
*                                                                             *
*               Copyright (c) 1992-1995, Microsoft Corp.  All rights reserved *
*                                                                             *
\*****************************************************************************/

#ifndef _INC_CUSTCNTL
#define _INC_CUSTCNTL

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


/*
 * General size defines.
 */
#define CCHCCCLASS          32          // Max chars in a class name.
#define CCHCCDESC           32          // Max chars in a control description.
#define CCHCCTEXT           256         // Max chars in a text field.


/*
 * CCSTYLE - Custom Control Style structure.  This structure is passed
 * tp the Custom Control Style function when the user wants to edit the
 * styles of the custom control.
 */
typedef struct tagCCSTYLEA {
    DWORD   flStyle;                    // Style of the control.
    DWORD   flExtStyle;                 // Extended style of the control.
    CHAR    szText[CCHCCTEXT];          // Text of the control.
    LANGID  lgid;                       // Language Id of the control's dialog.
    WORD    wReserved1;                 // Reserved value.  Do not change.
} CCSTYLEA, *LPCCSTYLEA;

typedef struct tagCCSTYLEW {
    DWORD   flStyle;                    // Style of the control.
    DWORD   flExtStyle;                 // Extended style of the control.
    WCHAR   szText[CCHCCTEXT];          // Text of the control.
    LANGID  lgid;                       // Language Id of the control's dialog.
    WORD    wReserved1;                 // Reserved value.  Do not change.
} CCSTYLEW, *LPCCSTYLEW;

#ifdef UNICODE
#define CCSTYLE     CCSTYLEW
#define LPCCSTYLE   LPCCSTYLEW
#else
#define CCSTYLE     CCSTYLEA
#define LPCCSTYLE   LPCCSTYLEA
#endif // UNICODE


/*
 * The Style function prototype.  This will be called when the user
 * wants to edit the styles of a custom control.  It should display a
 * dialog to edit the styles, update the styles in the pccs structure,
 * then return TRUE for success.  If an error occurs or the user
 * cancels the dialog, FALSE should be returned.
 */
typedef BOOL (CALLBACK* LPFNCCSTYLEA)(HWND hwndParent,  LPCCSTYLEA pccs);
typedef BOOL (CALLBACK* LPFNCCSTYLEW)(HWND hwndParent,  LPCCSTYLEW pccs);

#ifdef UNICODE
#define LPFNCCSTYLE LPFNCCSTYLEW
#else
#define LPFNCCSTYLE LPFNCCSTYLEA
#endif  // UNICODE


/*
 * The SizeToText function prototype.  This will be called if the user
 * requests that the custom control be sized to fit it's text.  It
 * should use the specified styles, text and font to determine how
 * large the control must be to accommodate the text, then return this
 * value in pixels.  The value of -1 should be returned if an error
 * occurs.
 */
typedef INT (CALLBACK* LPFNCCSIZETOTEXTA)(DWORD flStyle, DWORD flExtStyle,
    HFONT hfont, LPSTR pszText);
typedef INT (CALLBACK* LPFNCCSIZETOTEXTW)(DWORD flStyle, DWORD flExtStyle,
    HFONT hfont, LPWSTR pszText);

#ifdef UNICODE
#define LPFNCCSIZETOTEXT    LPFNCCSIZETOTEXTW
#else
#define LPFNCCSIZETOTEXT    LPFNCCSIZETOTEXTA
#endif  // UNICODE


/*
 * CCSTYLEFLAG - Custom Control Style Flag structure.  A table of these
 * structures is used to specify the define strings that match the
 * different styles for a custom control.
 */
typedef struct tagCCSTYLEFLAGA {
    DWORD flStyle;                      // Style bits for this style.
    DWORD flStyleMask;                  // Mask for the style.  Can be zero.
    LPSTR pszStyle;                     // Points to the style define string.
} CCSTYLEFLAGA, *LPCCSTYLEFLAGA;

typedef struct tagCCSTYLEFLAGW {
    DWORD flStyle;                      // Style bits for this style.
    DWORD flStyleMask;                  // Mask for the style.  Can be zero.
    LPWSTR pszStyle;                    // Points to the style define string.
} CCSTYLEFLAGW, *LPCCSTYLEFLAGW;

#ifdef UNICODE
#define CCSTYLEFLAG     CCSTYLEFLAGW
#define LPCCSTYLEFLAG   LPCCSTYLEFLAGW
#else
#define CCSTYLEFLAG     CCSTYLEFLAGA
#define LPCCSTYLEFLAG   LPCCSTYLEFLAGA
#endif // UNICODE


/*
 * CCF_* defines.  These flags are used for the flOptions field of the
 * CCINFO structure, and describe some basic characteristics of the
 * custom control.
 */
#define CCF_NOTEXT          0x00000001  // Control cannot have text.


/*
 * CCINFO - Custom Control Info structure.  This structure provides
 * the dialog editor with information about the control types that the
 * DLL supports.
 */
typedef struct tagCCINFOA {
    CHAR    szClass[CCHCCCLASS];        // Class name for the control.
    DWORD   flOptions;                  // Option flags (CCF_* defines).
    CHAR    szDesc[CCHCCDESC];          // Short, descriptive text for the ctrl.
    UINT    cxDefault;                  // Default width (in dialog units).
    UINT    cyDefault;                  // Default height (in dialog units).
    DWORD   flStyleDefault;             // Default style (WS_CHILD | WS_VISIBLE).
    DWORD   flExtStyleDefault;          // Default extended style.
    DWORD   flCtrlTypeMask;             // Mask for control type styles.
    CHAR    szTextDefault[CCHCCTEXT];   // Default text.
    INT     cStyleFlags;                // Entries in the following style table.
    LPCCSTYLEFLAGA aStyleFlags;         // Points to style flag table.
    LPFNCCSTYLEA lpfnStyle;             // Pointer to the Styles function.
    LPFNCCSIZETOTEXTA lpfnSizeToText;   // Pointer to the SizeToText function.
    DWORD   dwReserved1;                // Reserved.  Must be zero.
    DWORD   dwReserved2;                // Reserved.  Must be zero.
} CCINFOA, *LPCCINFOA;

typedef struct tagCCINFOW {
    WCHAR   szClass[CCHCCCLASS];        // Class name for the control.
    DWORD   flOptions;                  // Option flags (CCF_* defines).
    WCHAR   szDesc[CCHCCDESC];          // Short, descriptive text for the ctrl.
    UINT    cxDefault;                  // Default width (in dialog units).
    UINT    cyDefault;                  // Default height (in dialog units).
    DWORD   flStyleDefault;             // Default style (WS_CHILD | WS_VISIBLE).
    DWORD   flExtStyleDefault;          // Default extended style.
    DWORD   flCtrlTypeMask;             // Mask for control type styles.
    INT     cStyleFlags;                // Entries in the following style table.
    LPCCSTYLEFLAGW aStyleFlags;         // Points to style flag table.
    WCHAR   szTextDefault[CCHCCTEXT];   // Default text.
    LPFNCCSTYLEW lpfnStyle;             // Pointer to the Styles function.
    LPFNCCSIZETOTEXTW lpfnSizeToText;   // Pointer to the SizeToText function.
    DWORD   dwReserved1;                // Reserved.  Must be zero.
    DWORD   dwReserved2;                // Reserved.  Must be zero.
} CCINFOW, *LPCCINFOW;

#ifdef UNICODE
#define CCINFO      CCINFOW
#define LPCCINFO    LPCCINFOW
#else
#define CCINFO      CCINFOA
#define LPCCINFO    LPCCINFOA
#endif // UNICODE


/*
 * The Info function prototype.  This function is the first one
 * called by the dialog editor.  Custom control DLL's must export
 * one or both of the following functions by name (the ordinal
 * used for the export does not matter):
 *
 *  UINT CALLBACK CustomControlInfoA(LPCCINFOA acci)
 *  UINT CALLBACK CustomControlInfoW(LPCCINFOW acci)
 *
 * This function must return the number of controls that the DLL
 * supports, or NULL if an error occurs.  If the acci parameter is
 * not NULL, it will be pointing to an array of CCINFOA or CCINFOW
 * structures that should be filled in with the information about
 * the different control types supported by the DLL.
 *
 * If both functions are present, the CustomControlInfoW function
 * will be used by the dialog editor.
 */
typedef UINT (CALLBACK* LPFNCCINFOA)(LPCCINFOA acci);
typedef UINT (CALLBACK* LPFNCCINFOW)(LPCCINFOW acci);

#ifdef UNICODE
#define LPFNCCINFO  LPFNCCINFOW
#else
#define LPFNCCINFO  LPFNCCINFOA
#endif  // UNICODE


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_CUSTCNTL */


#endif  /* __FLAT__ */
