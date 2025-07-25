/*
 * prsht.h      Property sheet functions
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

#ifndef _PRSHT_H_
#define _PRSHT_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Macro to specify common control functions */
#ifndef WINCOMMCTRLAPI
    #define WINCOMMCTRLAPI  DECLSPEC_IMPORT
#endif

/* The following macros make it possible to disable nameless unions in certain structures
 * by defining NONAMELESSUNION.  They are shared with several other header files.
 */
#ifndef DUMMYUNIONNAME
    #ifdef NONAMELESSUNION
        #define DUMMYUNIONNAME  u
        #define DUMMYUNIONNAME2 u2
        #define DUMMYUNIONNAME3 u3
        #define DUMMYUNIONNAME4 u4
        #define DUMMYUNIONNAME5 u5
    #else
        #define DUMMYUNIONNAME
        #define DUMMYUNIONNAME2
        #define DUMMYUNIONNAME3
        #define DUMMYUNIONNAME4
        #define DUMMYUNIONNAME5
    #endif
#endif

/* These macro is used by other macros to invoke SendMessage().  It is shared with
 * several other header files.
 */
#ifndef SNDMSG
    #ifdef __cplusplus
        #define SNDMSG  ::SendMessage
    #else
        #define SNDMSG  SendMessage
    #endif
#endif

/* These macro is used by other macros to invoke PostMessage().  It is shared with
 * several other header files.
 */
#ifndef PSTMSG
    #ifdef __cplusplus
        #define PSTMSG  ::PostMessage
    #else
        #define PSTMSG  PostMessage
    #endif
#endif

/* Property sheet handle data types */
typedef struct _PSP *HPROPSHEETPAGE;

/* Property sheet page resource */
typedef LPCDLGTEMPLATE  PROPSHEETPAGE_RESOURCE;

/* Maximum number of property pages */
#define MAXPROPPAGES    100

/* Property sheet page flags */
#define PSP_DEFAULT                 0x00000000L
#define PSP_DLGINDIRECT             0x00000001L
#define PSP_USEHICON                0x00000002L
#define PSP_USEICONID               0x00000004L
#define PSP_USETITLE                0x00000008L
#define PSP_RTLREADING              0x00000010L
#define PSP_HASHELP                 0x00000020L
#define PSP_USEREFPARENT            0x00000040L
#define PSP_USECALLBACK             0x00000080L
#define PSP_PREMATURE               0x00000400L
#if (_WIN32_IE >= 0x0400)
    #define PSP_HIDEHEADER          0x00000800L
    #define PSP_USEHEADERTITLE      0x00001000L
    #define PSP_USEHEADERSUBTITLE   0x00002000L
#endif
#if (_WIN32_WINNT >= 0x0501)
    #define PSP_USEFUSIONCONTEXT    0x00004000L
#endif

/* Property sheet page callback return values */
#if (_WIN32_IE >= 0x0500)
    #define PSPCB_ADDREF    0
#endif
#define PSPCB_RELEASE       1
#define PSPCB_CREATE        2

/* Property sheet header flags */
#define PSH_DEFAULT                 0x00000000L
#define PSH_PROPTITLE               0x00000001L
#define PSH_USEHICON                0x00000002L
#define PSH_USEICONID               0x00000004L
#define PSH_PROPSHEETPAGE           0x00000008L
#define PSH_WIZARDHASFINISH         0x00000010L
#define PSH_WIZARD                  0x00000020L
#define PSH_USEPSTARTPAGE           0x00000040L
#define PSH_NOAPPLYNOW              0x00000080L
#define PSH_USECALLBACK             0x00000100L
#define PSH_HASHELP                 0x00000200L
#define PSH_MODELESS                0x00000400L
#define PSH_RTLREADING              0x00000800L
#define PSH_WIZARDCONTEXTHELP       0x00001000L
#if (_WIN32_IE >= 0x0400)
    #if (_WIN32_IE < 0x0500)
        #define PSH_WIZARD97        0x00002000L
    #else
        #define PSH_WIZARD97        0x01000000L
    #endif
    #define PSH_WATERMARK           0x00008000L
    #define PSH_USEHBMWATERMARK     0x00010000L
    #define PSH_USEHPLWATERMARK     0x00020000L
    #define PSH_STRETCHWATERMARK    0x00040000L
    #define PSH_HEADER              0x00080000L
    #define PSH_USEHBMHEADER        0x00100000L
    #define PSH_USEPAGELANG         0x00200000L
#endif
#if (_WIN32_IE >= 0x0500)
    #define PSH_WIZARD_LITE         0x00400000L
    #define PSH_NOCONTEXTHELP       0x02000000L
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define PSH_AEROWIZARD          0x00004000L
    #define PSH_RESIZABLE           0x04000000L
    #define PSH_HEADERBITMAP        0x08000000L
    #define PSH_NOMARGIN            0x10000000L
#endif

/* Property sheet callback messages */
#define PSCB_INITIALIZED        1
#define PSCB_PRECREATE          2
#if (_WIN32_IE >= 0x0560)
    #define PSCB_BUTTONPRESSED  3
#endif

/* Property sheet notification codes */
#define PSN_FIRST                       (0U - 200U)
#define PSN_LAST                        (0U - 299U)
#define PSN_SETACTIVE                   (PSN_FIRST - 0)
#define PSN_KILLACTIVE                  (PSN_FIRST - 1)
#define PSN_APPLY                       (PSN_FIRST - 2)
#define PSN_RESET                       (PSN_FIRST - 3)
#define PSN_HELP                        (PSN_FIRST - 5)
#define PSN_WIZBACK                     (PSN_FIRST - 6)
#define PSN_WIZNEXT                     (PSN_FIRST - 7)
#define PSN_WIZFINISH                   (PSN_FIRST - 8)
#define PSN_QUERYCANCEL                 (PSN_FIRST - 9)
#if (_WIN32_IE >= 0x0400)
    #define PSN_GETOBJECT               (PSN_FIRST - 10)
#endif
#if (_WIN32_IE >= 0x0500)
    #define PSN_TRANSLATEACCELERATOR    (PSN_FIRST - 12)
    #define PSN_QUERYINITIALFOCUS       (PSN_FIRST - 13)
#endif

/* Property sheet notification return codes */
#define PSNRET_NOERROR              0L
#define PSNRET_INVALID              1L
#define PSNRET_INVALID_NOCHANGEPAGE 2L
#define PSNRET_MESSAGEHANDLED       3L

/* Property sheet messages */
#define PSM_SETCURSEL               (WM_USER + 101)
#define PSM_REMOVEPAGE              (WM_USER + 102)
#define PSM_ADDPAGE                 (WM_USER + 103)
#define PSM_CHANGED                 (WM_USER + 104)
#define PSM_RESTARTWINDOWS          (WM_USER + 105)
#define PSM_REBOOTSYSTEM            (WM_USER + 106)
#define PSM_CANCELTOCLOSE           (WM_USER + 107)
#define PSM_QUERYSIBLINGS           (WM_USER + 108)
#define PSM_UNCHANGED               (WM_USER + 109)
#define PSM_APPLY                   (WM_USER + 110)
#define PSM_SETTITLEA               (WM_USER + 111)
#define PSM_SETWIZBUTTONS           (WM_USER + 112)
#define PSM_PRESSBUTTON             (WM_USER + 113)
#define PSM_SETCURSELID             (WM_USER + 114)
#define PSM_SETFINISHTEXTA          (WM_USER + 115)
#define PSM_GETTABCONTROL           (WM_USER + 116)
#define PSM_ISDIALOGMESSAGE         (WM_USER + 117)
#define PSM_GETCURRENTPAGEHWND      (WM_USER + 118)
#define PSM_INSERTPAGE              (WM_USER + 119)
#define PSM_INSERTPAGE              (WM_USER + 119)
#define PSM_SETTITLEW               (WM_USER + 120)
#define PSM_SETFINISHTEXTW          (WM_USER + 121)
#if (_WIN32_IE >= 0x0500)
    #define PSM_SETHEADERTITLEA     (WM_USER + 125)
    #define PSM_SETHEADERTITLEW     (WM_USER + 126)
    #define PSM_SETHEADERSUBTITLEA  (WM_USER + 127)
    #define PSM_SETHEADERSUBTITLEW  (WM_USER + 128)
    #define PSM_HWNDTOINDEX         (WM_USER + 129)
    #define PSM_INDEXTOHWND         (WM_USER + 130)
    #define PSM_PAGETOINDEX         (WM_USER + 131)
    #define PSM_INDEXTOPAGE         (WM_USER + 132)
    #define PSM_IDTOINDEX           (WM_USER + 133)
    #define PSM_INDEXTOID           (WM_USER + 134)
    #define PSM_GETRESULT           (WM_USER + 135)
    #define PSM_RECALCPAGESIZES     (WM_USER + 136)
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define PSM_SETNEXTTEXTW        (WM_USER + 137)
    #define PSM_SHOWWIZBUTTONS      (WM_USER + 138)
    #define PSM_ENABLEWIZBUTTONS    (WM_USER + 139)
    #define PSM_SETBUTTONTEXTW      (WM_USER + 140)
#endif
#ifdef UNICODE
    #define PSM_SETTITLE                PSM_SETTITLEW
    #define PSM_SETFINISHTEXT           PSM_SETFINISHTEXTW
    #if (_WIN32_IE >= 0x0500)
        #define PSM_SETHEADERTITLE      PSM_SETHEADERTITLEW
        #define PSM_SETHEADERSUBTITLE   PSM_SETHEADERSUBTITLEW
    #endif
#else
    #define PSM_SETTITLE                PSM_SETTITLEA
    #define PSM_SETFINISHTEXT           PSM_SETFINISHTEXTA
    #if (_WIN32_IE >= 0x0500)
        #define PSM_SETHEADERTITLE      PSM_SETHEADERTITLEA
        #define PSM_SETHEADERSUBTITLE   PSM_SETHEADERSUBTITLEA
    #endif
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define PSM_SETNEXTTEXT             PSM_SETNEXTTEXTW
    #define PSM_SETBUTTONTEXT           PSM_SETBUTTONTEXTW
#endif

/* Property sheet wizard button flags */
#define PSWIZB_BACK             0x00000001L
#define PSWIZB_NEXT             0x00000002L
#define PSWIZB_FINISH           0x00000004L
#define PSWIZB_DISABLEDFINISH   0x00000008L
#if (_WIN32_WINNT >= 0x0600)
    #define PSWIZB_CANCEL       0x00000010L
#endif

/* Property sheet buttons */
#define PSBTN_BACK      0
#define PSBTN_NEXT      1
#define PSBTN_FINISH    2
#define PSBTN_OK        3
#define PSBTN_APPLYNOW  4
#define PSBTN_CANCEL    5
#define PSBTN_HELP      6
#define PSBTN_MAX       6

/* PSWIZB_SHOWWIZBUTTONS flags */
#if (_WIN32_WINNT >= 0x0600)
    #define PSWIZB_SHOW     0
    #define PSWIZB_RESTORE  1
#endif

/* Property sheet result values */
#define ID_PSRESTARTWINDOWS 0x00000002L
#define ID_PSREBOOTSYSTEM   (ID_PSRESTARTWINDOWS | 0x00000001L)

/* Property sheet sizes */
#define WIZ_CXDLG       276
#define WIZ_CYDLG       140
#define WIZ_CXBMP       80
#define WIZ_BODYX       92
#define WIZ_BODYCX      184
#define PROP_SM_CXDLG   212
#define PROP_SM_CYDLG   188
#define PROP_MED_CXDLG  227
#define PROP_MED_CYDLG  215
#define PROP_LG_CXDLG   252
#define PROP_LG_CYDLG   218

/* Property sheet page callback */
#if (_WIN32_WINNT >= 0x0600)
    #define _PROPSHEETPAGEA _PROPSHEETPAGEA_V4
    #define _PROPSHEETPAGEW _PROPSHEETPAGEW_V4
#elif (_WIN32_WINNT >= 0x0501)
    #define _PROPSHEETPAGEA _PROPSHEETPAGEA_V3
    #define _PROPSHEETPAGEW _PROPSHEETPAGEW_V3
#elif (_WIN32_IE >= 0x0400)
    #define _PROPSHEETPAGEA _PROPSHEETPAGEA_V2
    #define _PROPSHEETPAGEW _PROPSHEETPAGEW_V2
#else
    #define _PROPSHEETPAGEA _PROPSHEETPAGEA_V1
    #define _PROPSHEETPAGEW _PROPSHEETPAGEW_V1
#endif
typedef UINT (CALLBACK *LPFNPSPCALLBACKA)( HWND, UINT, struct _PROPSHEETPAGEA * );
typedef UINT (CALLBACK *LPFNPSPCALLBACKW)( HWND, UINT, struct _PROPSHEETPAGEW * );
#ifdef UNICODE
    #define LPFNPSPCALLBACK LPFNPSPCALLBACKW
#else
    #define LPFNPSPCALLBACK LPFNPSPCALLBACKA
#endif

/* Basic property sheet page fields */
#define PROPSHEETPAGEA_V1_FIELDS \
    DWORD               dwSize; \
    DWORD               dwFlags; \
    HINSTANCE           hInstance; \
    union { \
        LPCSTR                  pszTemplate; \
        PROPSHEETPAGE_RESOURCE  pResource; \
    } DUMMYUNIONNAME; \
    union { \
        HICON   hIcon; \
        LPCSTR  pszIcon; \
    } DUMMYUNIONNAME2; \
    LPCSTR              pszTitle; \
    DLGPROC             pfnDlgProc; \
    LPARAM              lParam; \
    LPFNPSPCALLBACKA    pfnCallback; \
    UINT                *pcRefParent;
#define PROPSHEETPAGEW_V1_FIELDS \
    DWORD               dwSize; \
    DWORD               dwFlags; \
    HINSTANCE           hInstance; \
    union { \
        LPCWSTR                 pszTemplate; \
        PROPSHEETPAGE_RESOURCE  pResource; \
    } DUMMYUNIONNAME; \
    union { \
        HICON   hIcon; \
        LPCWSTR pszIcon; \
    } DUMMYUNIONNAME2; \
    LPCWSTR             pszTitle; \
    DLGPROC             pfnDlgProc; \
    LPARAM              lParam; \
    LPFNPSPCALLBACKW    pfnCallback; \
    UINT                *pcRefParent;

/* Property sheet page (version 1) */
typedef struct _PROPSHEETPAGEA_V1 {
    PROPSHEETPAGEA_V1_FIELDS
} PROPSHEETPAGEA_V1;
typedef PROPSHEETPAGEA_V1       *LPPROPSHEETPAGEA_V1;
typedef const PROPSHEETPAGEA_V1 *LPCPROPSHEETPAGEA_V1;
typedef struct _PROPSHEETPAGEW_V1 {
    PROPSHEETPAGEW_V1_FIELDS
} PROPSHEETPAGEW_V1;
typedef PROPSHEETPAGEW_V1       *LPPROPSHEETPAGEW_V1;
typedef const PROPSHEETPAGEW_V1 *LPCPROPSHEETPAGEW_V1;
#ifdef UNICODE
typedef PROPSHEETPAGEW_V1       PROPSHEETPAGE_V1;
typedef LPPROPSHEETPAGEW_V1     LPPROPSHEETPAGE_V1;
typedef LPCPROPSHEETPAGEW_V1    LPCPROPSHEETPAGE_V1;
#else
typedef PROPSHEETPAGEA_V1       PROPSHEETPAGE_V1;
typedef LPPROPSHEETPAGEA_V1     LPPROPSHEETPAGE_V1;
typedef LPCPROPSHEETPAGEA_V1    LPCPROPSHEETPAGE_V1;
#endif

/* Property sheet page (version 2) */
typedef struct _PROPSHEETPAGEA_V2 {
    PROPSHEETPAGEA_V1_FIELDS
    LPCSTR  pszHeaderTitle;
    LPCSTR  pszHeaderSubTitle;
} PROPSHEETPAGEA_V2;
typedef PROPSHEETPAGEA_V2       *LPPROPSHEETPAGEA_V2;
typedef const PROPSHEETPAGEA_V2 *LPCPROPSHEETPAGEA_V2;
typedef struct _PROPSHEETPAGEW_V2 {
    PROPSHEETPAGEW_V1_FIELDS
    LPCWSTR pszHeaderTitle;
    LPCWSTR pszHeaderSubTitle;
} PROPSHEETPAGEW_V2;
typedef PROPSHEETPAGEW_V2       *LPPROPSHEETPAGEW_V2;
typedef const PROPSHEETPAGEW_V2 *LPCPROPSHEETPAGEW_V2;
#ifdef UNICODE
typedef PROPSHEETPAGEW_V2       PROPSHEETPAGE_V2;
typedef LPPROPSHEETPAGEW_V2     LPPROPSHEETPAGE_V2;
typedef LPCPROPSHEETPAGEW_V2    LPCPROPSHEETPAGE_V2;
#else
typedef PROPSHEETPAGEA_V2       PROPSHEETPAGE_V2;
typedef LPPROPSHEETPAGEA_V2     LPPROPSHEETPAGE_V2;
typedef LPCPROPSHEETPAGEA_V2    LPCPROPSHEETPAGE_V2;
#endif

/* Property sheet page (version 3) */
typedef struct _PROPSHEETPAGEA_V3 {
    PROPSHEETPAGEA_V1_FIELDS
    LPCSTR  pszHeaderTitle;
    LPCSTR  pszHeaderSubTitle;
    HANDLE  hActCtx;
} PROPSHEETPAGEA_V3;
typedef PROPSHEETPAGEA_V3       *LPPROPSHEETPAGEA_V3;
typedef const PROPSHEETPAGEA_V3 *LPCPROPSHEETPAGEA_V3;
typedef struct _PROPSHEETPAGEW_V3 {
    PROPSHEETPAGEW_V1_FIELDS
    LPCWSTR pszHeaderTitle;
    LPCWSTR pszHeaderSubTitle;
    HANDLE  hActCtx;
} PROPSHEETPAGEW_V3;
typedef PROPSHEETPAGEW_V3       *LPPROPSHEETPAGEW_V3;
typedef const PROPSHEETPAGEW_V3 *LPCPROPSHEETPAGEW_V3;
#ifdef UNICODE
typedef PROPSHEETPAGEW_V3       PROPSHEETPAGE_V3;
typedef LPPROPSHEETPAGEW_V3     LPPROPSHEETPAGE_V3;
typedef LPCPROPSHEETPAGEW_V3    LPCPROPSHEETPAGE_V3;
#else
typedef PROPSHEETPAGEA_V3       PROPSHEETPAGE_V3;
typedef LPPROPSHEETPAGEA_V3     LPPROPSHEETPAGE_V3;
typedef LPCPROPSHEETPAGEA_V3    LPCPROPSHEETPAGE_V3;
#endif

/* Property sheet page (version 4) */
#if (_WIN32_WINNT >= 0x0600)
typedef struct _PROPSHEETPAGEA_V4 {
    PROPSHEETPAGEA_V1_FIELDS
    LPCSTR  pszHeaderTitle;
    LPCSTR  pszHeaderSubTitle;
    HANDLE  hActCtx;
    union {
        HBITMAP hbmHeader;
        LPCSTR  pszbmHeader;
    } DUMMYUNIONNAME3;
} PROPSHEETPAGEA_V4;
typedef PROPSHEETPAGEA_V4       *LPPROPSHEETPAGEA_V4;
typedef const PROPSHEETPAGEA_V4 *LPCPROPSHEETPAGEA_V4;
typedef struct _PROPSHEETPAGEW_V4 {
    PROPSHEETPAGEW_V1_FIELDS
    LPCWSTR pszHeaderTitle;
    LPCWSTR pszHeaderSubTitle;
    HANDLE  hActCtx;
    union {
        HBITMAP hbmHeader;
        LPCWSTR pszbmHeader;
    } DUMMYUNIONNAME3;
} PROPSHEETPAGEW_V4;
typedef PROPSHEETPAGEW_V4       *LPPROPSHEETPAGEW_V4;
typedef const PROPSHEETPAGEW_V4 *LPCPROPSHEETPAGEW_V4;
#ifdef UNICODE
typedef PROPSHEETPAGEW_V4       PROPSHEETPAGE_V4;
typedef LPPROPSHEETPAGEW_V4     LPPROPSHEETPAGE_V4;
typedef LPCPROPSHEETPAGEW_V4    LPCPROPSHEETPAGE_V4;
#else
typedef PROPSHEETPAGEA_V4       PROPSHEETPAGE_V4;
typedef LPPROPSHEETPAGEA_V4     LPPROPSHEETPAGE_V4;
typedef LPCPROPSHEETPAGEA_V4    LPCPROPSHEETPAGE_V4;
#endif
#endif

/* Use the appropriate version of the property sheet page data structure. */
#if (_WIN32_WINNT >= 0x0600)
typedef PROPSHEETPAGEA_V4       PROPSHEETPAGEA_LATEST;
typedef PROPSHEETPAGEW_V4       PROPSHEETPAGEW_LATEST;
typedef LPPROPSHEETPAGEA_V4     LPPROPSHEETPAGEA_LATEST;
typedef LPPROPSHEETPAGEW_V4     LPPROPSHEETPAGEW_LATEST;
typedef LPCPROPSHEETPAGEA_V4    LPCPROPSHEETPAGEA_LATEST;
typedef LPCPROPSHEETPAGEW_V4    LPCPROPSHEETPAGEW_LATEST;
#else
typedef PROPSHEETPAGEA_V3       PROPSHEETPAGEA_LATEST;
typedef PROPSHEETPAGEW_V3       PROPSHEETPAGEW_LATEST;
typedef LPPROPSHEETPAGEA_V3     LPPROPSHEETPAGEA_LATEST;
typedef LPPROPSHEETPAGEW_V3     LPPROPSHEETPAGEW_LATEST;
typedef LPCPROPSHEETPAGEA_V3    LPCPROPSHEETPAGEA_LATEST;
typedef LPCPROPSHEETPAGEW_V3    LPCPROPSHEETPAGEW_LATEST;
#endif
#if (_WIN32_WINNT >= 0x0600)
typedef PROPSHEETPAGEA_V4       PROPSHEETPAGEA;
typedef PROPSHEETPAGEW_V4       PROPSHEETPAGEW;
typedef LPPROPSHEETPAGEA_V4     LPPROPSHEETPAGEA;
typedef LPPROPSHEETPAGEW_V4     LPPROPSHEETPAGEW;
typedef LPCPROPSHEETPAGEA_V4    LPCPROPSHEETPAGEA;
typedef LPCPROPSHEETPAGEW_V4    LPCPROPSHEETPAGEW;
#elif (_WIN32_WINNT >= 0x0501)
typedef PROPSHEETPAGEA_V3       PROPSHEETPAGEA;
typedef PROPSHEETPAGEW_V3       PROPSHEETPAGEW;
typedef LPPROPSHEETPAGEA_V3     LPPROPSHEETPAGEA;
typedef LPPROPSHEETPAGEW_V3     LPPROPSHEETPAGEW;
typedef LPCPROPSHEETPAGEA_V3    LPCPROPSHEETPAGEA;
typedef LPCPROPSHEETPAGEW_V3    LPCPROPSHEETPAGEW;
#elif (_WIN32_IE >= 0x0400)
typedef PROPSHEETPAGEA_V2       PROPSHEETPAGEA;
typedef PROPSHEETPAGEW_V2       PROPSHEETPAGEW;
typedef LPPROPSHEETPAGEA_V2     LPPROPSHEETPAGEA;
typedef LPPROPSHEETPAGEW_V2     LPPROPSHEETPAGEW;
typedef LPCPROPSHEETPAGEA_V2    LPCPROPSHEETPAGEA;
typedef LPCPROPSHEETPAGEW_V2    LPCPROPSHEETPAGEW;
#else
typedef PROPSHEETPAGEA_V1       PROPSHEETPAGEA;
typedef PROPSHEETPAGEW_V1       PROPSHEETPAGEW;
typedef LPPROPSHEETPAGEA_V1     LPPROPSHEETPAGEA;
typedef LPPROPSHEETPAGEW_V1     LPPROPSHEETPAGEW;
typedef LPCPROPSHEETPAGEA_V1    LPCPROPSHEETPAGEA;
typedef LPCPROPSHEETPAGEW_V1    LPCPROPSHEETPAGEW;
#endif
#ifdef UNICODE
typedef PROPSHEETPAGEW          PROPSHEETPAGE;
typedef LPPROPSHEETPAGEW        LPPROPSHEETPAGE;
typedef LPCPROPSHEETPAGEW       LPCPROPSHEETPAGE;
#else
typedef PROPSHEETPAGEA          PROPSHEETPAGE;
typedef LPPROPSHEETPAGEA        LPPROPSHEETPAGE;
typedef LPCPROPSHEETPAGEA       LPCPROPSHEETPAGE;
#endif

/* Property sheet callback */
typedef int (CALLBACK *PFNPROPSHEETCALLBACK)( HWND, UINT, LPARAM );

/* Basic property sheet header fields */
#define PROPSHEETHEADERA_V1_FIELDS \
    DWORD                   dwSize; \
    DWORD                   dwFlags; \
    HWND                    hwndParent; \
    HINSTANCE               hInstance; \
    union { \
        HICON   hIcon; \
        LPCSTR  pszIcon; \
    } DUMMYUNIONNAME; \
    LPCSTR                  pszCaption; \
    UINT                    nPages; \
    union { \
        UINT    nStartPage; \
        LPCSTR  pStartPage; \
    } DUMMYUNIONNAME2; \
    union { \
        LPCPROPSHEETPAGEA   ppsp; \
        HPROPSHEETPAGE      *phpage; \
    } DUMMYUNIONNAME3; \
    PFNPROPSHEETCALLBACK    pfnCallback;
#define PROPSHEETHEADERW_V1_FIELDS \
    DWORD                   dwSize; \
    DWORD                   dwFlags; \
    HWND                    hwndParent; \
    HINSTANCE               hInstance;  \
    union { \
        HICON   hIcon; \
        LPCWSTR pszIcon; \
    } DUMMYUNIONNAME; \
    LPCWSTR                 pszCaption; \
    UINT                    nPages; \
    union { \
        UINT    nStartPage; \
        LPCWSTR pStartPage; \
    } DUMMYUNIONNAME2; \
    union { \
        LPCPROPSHEETPAGEW   ppsp; \
        HPROPSHEETPAGE      *phpage; \
    } DUMMYUNIONNAME3; \
    PFNPROPSHEETCALLBACK    pfnCallback;

/* Property sheet header (version 1) */
typedef struct _PROPSHEETHEADERA_V1 {
    PROPSHEETHEADERA_V1_FIELDS
} PROPSHEETHEADERA_V1;
typedef PROPSHEETHEADERA_V1         *LPPROPSHEETHEADERA_V1;
typedef const PROPSHEETHEADERA_V1   *LPCPROPSHEETHEADERA_V1;
typedef struct _PROPSHEETHEADERW_V1 {
    PROPSHEETHEADERW_V1_FIELDS
} PROPSHEETHEADERW_V1;
typedef PROPSHEETHEADERW_V1         *LPPROPSHEETHEADERW_V1;
typedef const PROPSHEETHEADERW_V1   *LPCPROPSHEETHEADERW_V1;
#ifdef UNICODE
typedef PROPSHEETHEADERW_V1         PROPSHEETHEADER_V1;
typedef LPPROPSHEETHEADERW_V1       LPPROPSHEETHEADER_V1;
typedef LPCPROPSHEETHEADERW_V1      LPCPROPSHEETHEADER_V1;
#else
typedef PROPSHEETHEADERA_V1         PROPSHEETHEADER_V1;
typedef LPPROPSHEETHEADERA_V1       LPPROPSHEETHEADER_V1;
typedef LPCPROPSHEETHEADERA_V1      LPCPROPSHEETHEADER_V1;
#endif

/* Property sheet header (version 2) */
#if (_WIN32_IE >= 0x0400)
typedef struct _PROPSHEETHEADERA_V2 {
    PROPSHEETHEADERA_V1_FIELDS
    union {
        HBITMAP hbmWatermark;
        LPCSTR  pszbmWatermark;
    } DUMMYUNIONNAME4;
    HPALETTE    hplWatermark;
    union {
        HBITMAP hbmHeader;
        LPCSTR  pszbmHeader;
    } DUMMYUNIONNAME5;
} PROPSHEETHEADERA_V2;
typedef PROPSHEETHEADERA_V2         *LPPROPSHEETHEADERA_V2;
typedef const PROPSHEETHEADERA_V2   *LPCPROPSHEETHEADERA_V2;
typedef struct _PROPSHEETHEADERW_V2 {
    PROPSHEETHEADERW_V1_FIELDS
    union {
        HBITMAP hbmWatermark;
        LPCWSTR pszbmWatermark;
    } DUMMYUNIONNAME4;
    HPALETTE    hplWatermark;
    union {
        HBITMAP hbmHeader;
        LPCWSTR pszbmHeader;
    } DUMMYUNIONNAME5;
} PROPSHEETHEADERW_V2;
typedef PROPSHEETHEADERW_V2         *LPPROPSHEETHEADERW_V2;
typedef const PROPSHEETHEADERW_V2   *LPCPROPSHEETHEADERW_V2;
#ifdef UNICODE
typedef PROPSHEETHEADERW_V2         PROPSHEETHEADER_V2;
typedef LPPROPSHEETHEADERW_V2       LPPROPSHEETHEADER_V2;
typedef LPCPROPSHEETHEADERW_V2      LPCPROPSHEETHEADER_V2;
#else
typedef PROPSHEETHEADERA_V2         PROPSHEETHEADER_V2;
typedef LPPROPSHEETHEADERA_V2       LPPROPSHEETHEADER_V2;
typedef LPCPROPSHEETHEADERA_V2      LPCPROPSHEETHEADER_V2;
#endif
#endif

/* Use the appropriate version of the property sheet header data structure. */
#if (_WIN32_IE >= 0x0400)
typedef PROPSHEETHEADERA_V2     PROPSHEETHEADERA;
typedef PROPSHEETHEADERW_V2     PROPSHEETHEADERW;
typedef LPPROPSHEETHEADERA_V2   LPPROPSHEETHEADERA;
typedef LPPROPSHEETHEADERW_V2   LPPROPSHEETHEADERW;
typedef LPCPROPSHEETHEADERA_V2  LPCPROPSHEETHEADERA;
typedef LPCPROPSHEETHEADERW_V2  LPCPROPSHEETHEADERW;
#else
typedef PROPSHEETHEADERA_V1     PROPSHEETHEADERA;
typedef PROPSHEETHEADERW_V1     PROPSHEETHEADERW;
typedef LPPROPSHEETHEADERA_V1   LPPROPSHEETHEADERA;
typedef LPPROPSHEETHEADERW_V1   LPPROPSHEETHEADERW;
typedef LPCPROPSHEETHEADERA_V1  LPCPROPSHEETHEADERA;
typedef LPCPROPSHEETHEADERW_V1  LPCPROPSHEETHEADERW;
#endif
#ifdef UNICODE
typedef PROPSHEETHEADERW        PROPSHEETHEADER;
typedef LPPROPSHEETHEADERW      LPPROPSHEETHEADER;
typedef LPCPROPSHEETHEADERW     LPCPROPSHEETHEADER;
#else
typedef PROPSHEETHEADERA        PROPSHEETHEADER;
typedef LPPROPSHEETHEADERA      LPPROPSHEETHEADER;
typedef LPCPROPSHEETHEADERA     LPCPROPSHEETHEADER;
#endif

/* Shell property sheet callbacks */
typedef BOOL (CALLBACK *LPFNADDPROPSHEETPAGE)( HPROPSHEETPAGE, LPARAM );
typedef BOOL (CALLBACK *LPFNADDPROPSHEETPAGES)( LPVOID, LPFNADDPROPSHEETPAGE, LPARAM );

/* Property sheet notification information */
typedef struct _PSHNOTIFY {
    NMHDR   hdr;
    LPARAM  lParam;
} PSHNOTIFY;
typedef PSHNOTIFY   *LPPSHNOTIFY;

/* Functions in COMCTL32.DLL */
WINCOMMCTRLAPI HPROPSHEETPAGE WINAPI    CreatePropertySheetPageA( LPCPROPSHEETPAGEA );
WINCOMMCTRLAPI HPROPSHEETPAGE WINAPI    CreatePropertySheetPageW( LPCPROPSHEETPAGEW );
WINCOMMCTRLAPI BOOL WINAPI              DestroyPropertySheetPage( HPROPSHEETPAGE );
WINCOMMCTRLAPI INT_PTR WINAPI           PropertySheetA( LPCPROPSHEETHEADERA );
WINCOMMCTRLAPI INT_PTR WINAPI           PropertySheetW( LPCPROPSHEETHEADERW );

/* Functions implemented as macros */
#define PropSheet_SetCurSel( x, p1, p2 ) \
    SNDMSG( x, PSM_SETCURSEL, (WPARAM)(p2), (LPARAM)(p1) )
#define PropSheet_RemovePage( x, p1, p2 ) \
    SNDMSG( x, PSM_REMOVEPAGE, p1, (LPARAM)(p2) )
#define PropSheet_AddPage( x, p ) \
    SNDMSG( x, PSM_ADDPAGE, 0, (LPARAM)(p) )
#define PropSheet_Changed( x, p ) \
    SNDMSG( x, PSM_CHANGED, (WPARAM)(p), 0L )
#define PropSheet_RestartWindows( x ) \
    SNDMSG( x, PSM_RESTARTWINDOWS, 0, 0L )
#define PropSheet_RebootSystem( x ) \
    SNDMSG( x, PSM_REBOOTSYSTEM, 0, 0L )
#define PropSheet_CancelToClose( x ) \
    PSTMSG( x, PSM_CANCELTOCLOSE, 0, 0L )
#define PropSheet_QuerySiblings( x, p1, p2 ) \
    SNDMSG( x, PSM_QUERYSIBLINGS, p1, p2 )
#define PropSheet_UnChanged( x, p ) \
    SNDMSG( x, PSM_UNCHANGED, (WPARAM)(p), 0L )
#define PropSheet_Apply( x ) \
    SNDMSG( x, PSM_APPLY, 0, 0L )
#define PropSheet_SetTitle( x, p1, p2 ) \
    SNDMSG( x, PSM_SETTITLE, p1, (LPARAM)(LPCTSTR)(p2) )
#define PropSheet_SetWizButtons( x, p ) \
    PSTMSG( x, PSM_SETWIZBUTTONS, 0, (LPARAM)(p) )
#define PropSheet_PressButton( x, p ) \
    PSTMSG( x, PSM_PRESSBUTTON, (WPARAM)(p), 0 )
#define PropSheet_SetCurSelByID( x, p ) \
    SNDMSG( x, PSM_SETCURSELBYID, 0, (LPARAM)(p) )
#define PropSheet_SetFinishText( x, p ) \
    SNDMSG( x, PSM_SETFINISHTEXT, 0, (LPARAM)(p) )
#define PropSheet_GetTabControl( x, p ) \
    (HWND)SNDMSG( x, PSM_GETTABCONTROL, 0, 0L )
#define PropSheet_IsDialogMessage( x, p ) \
    (BOOL)SNDMSG( x, PSM_ISDIALOGMESSAGE, 0, (LPARAM)(p) )
#define PropSheet_GetCurrentPageHwnd( x ) \
    (HWND)SNDMSG( x, PSM_GETCURRENTPAGEHWND, 0, 0L )
#define PropSheet_InsertPage( x, p1, p2 ) \
    SNDMSG( x, PSM_INSERTPAGE, (WPARAM)(p1), (LPARAM)(p2) )
#if (_WIN32_IE >= 0x0500)
    #define PropSheet_SetHeaderTitle( x, p1, p2 ) \
        SNDMSG( x, PSM_SETHEADERTITLE, (WPARAM)(p1), (LPARAM)(p2) )
    #define PropSheet_SetHeaderSubTitle( x, p1, p2 ) \
        SNDMSG( x, PSM_SETHEADERSUBTITLE, (WPARAM)(p1), (LPARAM)(p2) )
    #define PropSheet_HwndToIndex( x, p ) \
        (int)SNDMSG( x, PSM_HWNDTOINDEX, (WPARAM)(p), 0L )
    #define PropSheet_IndexToHwnd( x, p ) \
        (HWND)SNDMSG( x, PSM_INDEXTOHWND, (WPARAM)(p), 0L )
    #define PropSheet_PageToIndex( x, p ) \
        (int)SNDMSG( x, PSM_PAGETOINDEX, 0, (LPARAM)(p) )
    #define PropSheet_IndexToPage( x, p ) \
        (HPROPSHEETPAGE)SNDMSG( x, PSM_INDEXTOPAGE, (WPARAM)(p), 0L )
    #define PropSheet_IdToIndex( x, p ) \
        (int)SNDMSG( x, PSM_IDTOINDEX, 0, (LPARAM)(p) )
    #define PropSheet_IndexToId( x, p ) \
        SNDMSG( x, PSM_INDEXTOID, (WPARAM)(p), 0L )
    #define PropSheet_GetResult( x ) \
        SNDMSG( x, PSM_GETRESULT, 0, 0L )
    #define PropSheet_RecalcPageSizes( x ) \
        SNDMSG( x, PSM_RECALCPAGESIZES, 0, 0L )
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define PropSheet_SetNextText( x, p ) \
        SNDMSG( x, PSM_SETNEXTTEXT, 0, (LPARAM)(p) )
    #define PropSheet_ShowWizButtons( x, p1, p2 ) \
        PSTMSG( x, PSM_SHOWWIZBUTTONS, (WPARAM)(p1), (LPARAM)(p2) )
    #define PropSheet_EnableWizButtons( x, p1, p2 ) \
        PSTMSG( x, PSM_ENABLEWIZBUTTONS, (WPARAM)(p1), (LPARAM)(p2) )
#endif

/* Map generic function names to the appropriate ANSI or Unicode version. */
#ifdef UNICODE
    #define CreatePropertySheetPage CreatePropertySheetPageW
    #define PropertySheet           PropertySheetW
#else
    #define CreatePropertySheetPage CreatePropertySheetPageA
    #define PropertySheet           PropertySheetA
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _PRSHT_H_ */
