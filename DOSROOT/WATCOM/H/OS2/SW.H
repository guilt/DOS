/*
 *  sw.h        OS/2 Secondary Window include file.
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */

#ifndef __SW_H__
#define __SW_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef INCL_SECONDARYWINDOW

#define MAX_SMBDTEXT 35
#define MB_ICONCUSTOM 0x0001
#define SC_DEFAULTSIZE 0xc000
#define WM_INITSECONDARYWINDOW 0x0519
#define QS_FRAME 1
#define QS_DIALOG 2

#pragma pack( __push, 4 )

typedef struct _SMBD {
    CHAR  achText[MAX_SMBDTEXT+1];
    ULONG idButton;
    LONG  flStyle;
} SMBD, *PSMBD;

typedef struct _SMBINFO {
    HPOINTER hIcon;
    ULONG    cButtons;
    ULONG    flStyle;
    HWND     hwndNotify;
    PSMBD    psmbd;
} SMBINFO, *PSMBINFO;

#pragma pack( __pop )

HWND    EXPENTRY WinCreateSecondaryWindow(HWND,HWND,PFNWP,PDLGTEMPLATE,PVOID);
BOOL    EXPENTRY WinDefaultSize(HWND);
MRESULT EXPENTRY WinDefSecondaryWindowProc(HWND,ULONG,MPARAM,MPARAM);
BOOL    EXPENTRY WinDestroySecondaryWindow(HWND);
BOOL    EXPENTRY WinDismissSecondaryWindow(HWND,ULONG);
BOOL    EXPENTRY WinInsertDefaultSize(HWND,PSZ);
HWND    EXPENTRY WinLoadSecondaryWindow(HWND,HWND,PFNWP,HMODULE,ULONG,PVOID);
ULONG   EXPENTRY WinProcessSecondaryWindow(HWND);
HWND    EXPENTRY WinQuerySecondaryHWND(HWND,ULONG);
ULONG   EXPENTRY WinSecondaryMessageBox(HWND,HWND,PSZ,PSZ,ULONG,PSMBINFO);
ULONG   EXPENTRY WinSecondaryWindow(HWND,HWND,PFNWP,HMODULE,ULONG,PVOID);

#endif

#ifdef INCL_GRAPHICBUTTON

#define WC_GRAPHICBUTTON ((PSZ)0xffff0040)

#define GBS_TWOSTATE 0x1000
#define GBS_AUTOTWOSTATE 0x2000
#define GBS_ANIMATION 0x4000
#define GBS_AUTOANIMATION 0x8000
#define GBS_DISABLEBITMAP 0x0010
#define GBS_HILITEBITMAP 0x0020
#define GBS_3D_TEXTRECESSED 0x0040
#define GBS_3D_TEXTRAISED 0x0080
#define GBS_MINIBUTTON 0x0001
#define GB_ERROR (-1)
#define GB_UP 1
#define GB_DOWN 2
#define GB_DISABLE 3
#define GB_HILITE 4
#define GB_OUTOFHILITE 5
#define GB_TOGGLE 10
#define GB_CURRENTSTATE 11
#define GB_ANIMATIONBEGIN 12
#define GB_ANIMATIONEND 13
#define GB_MAXINDEX 14
#define GB_TEXTBELOW 1
#define GB_TEXTABOVE 2
#define GB_INDEX_FORWARD (-1)
#define GB_INDEX_BACKWARD (-2)
#define GB_INDEX_FIRST (-3)
#define GB_INDEX_LAST (-4)

#define GB_RESOURCE  1
#define GB_STRUCTURE 0

#define GBN_BUTTONUP 0x0524
#define GBN_BUTTONDOWN 0x0525
#define GBN_BUTTONHILITE 0x0526
#define GBN_SETFOCUS 0x0527
#define GBM_SETGRAPHICDATA 0x052a
#define GBM_ANIMATE 0x052b
#define GBM_SETANIMATIONRATE 0x052c
#define GBM_QUERYANIMATIONRATE 0x052e
#define GBM_SETBITMAPINDEX 0x052f
#define GBM_QUERYBITMAPINDEX 0x0530
#define GBM_SETSTATE 0x0531
#define GBM_QUERYSTATE 0x0532
#define GBM_SETTEXTPOSITION 0x0533
#define GBM_QUERYTEXTPOSITION 0x0534

#pragma pack( __push, 1 )

typedef struct _GBTNCDATA {
    USHORT  usReserved;
    PSZ     pszText;
    HMODULE hmod;
    USHORT  cBitmaps;
    USHORT  aidBitmap[1];
} GBTNCDATA, *PGBTNCDATA;

#pragma pack( __pop )

BOOL EXPENTRY WinRegisterGraphicButton(VOID);

#endif

#ifdef INCL_STPMPAGE
  #define MM_TABHELP  0x054c
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
