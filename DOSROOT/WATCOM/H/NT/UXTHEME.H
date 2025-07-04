/*
 *  uxtheme.h   Theme Manager functions
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

#ifndef _UXTHEME_H_
#define _UXTHEME_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <commctrl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Macros to specify theme functions */
#define THEMEAPI        EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define THEMEAPI_( x )  EXTERN_C DECLSPEC_IMPORT x STDAPICALLTYPE

/* Theme primitive data types */
typedef HANDLE  HTHEME;
#if (_WIN32_WINNT >= 0x0600)
typedef HANDLE  HPAINTBUFFER;
typedef HANDLE  HANIMATIONBUFFER;
#endif

/* Maximum string lengths */
#if (_WIN32_WINNT >= 0x0600)
    #define MAX_THEMECOLOR  64
    #define MAX_THEMESIZE   64
#endif

/* OpenThemeDataEx() flags */
#define OTD_FORCE_RECT_SIZING   0x00000001L
#define OTD_NONCLIENT           0x00000002L
#define OTD_VALIDBITS \
    (OTD_FORCE_RECT_SIZING | OTD_NONCLIENT)

/* DrawThemeBackgroundEx() flags */
#define DTBG_CLIPRECT           0x00000001L
#define DTBG_DRAWSOLID          0x00000002L
#define DTBG_OMITBORDER         0x00000004L
#define DTBG_OMITCONTENT        0x00000008L
#define DTBG_COMPUTINGREGION    0x00000010L
#define DTBG_MIRRORDC           0x00000020L
#define DTBG_NOMIRROR           0x00000040L
#define DTBG_VALIDBITS \
    (DTBG_CLIPRECT | DTBG_DRAWSOLID | DTBG_OMITBORDER | DTBG_OMITCONTENT | \
    DTBG_COMPUTINGREGION | DTBG_MIRRORDC | DTBG_NOMIRROR)

/* DrawThemeText() flags */
#define DTT_TEXTCOLOR       0x00000001L
#define DTT_BORDERCOLOR     0x00000002L
#define DTT_SHADOWCOLOR     0x00000004L
#define DTT_SHADOWTYPE      0x00000008L
#define DTT_SHADOWOFFSET    0x00000010L
#define DTT_BORDERSIZE      0x00000020L
#define DTT_FONTPROP        0x00000040L
#define DTT_COLORPROP       0x00000080L
#define DTT_STATEID         0x00000100L
#define DTT_CALCRECT        0x00000200L
#define DTT_APPLYOVERLAY    0x00000400L
#define DTT_GLOWSIZE        0x00000800L
#define DTT_CALLBACK        0x00001000L
#define DTT_COMPOSITED      0x00002000L
#define DTT_VALIDBITS \
    (DTT_TEXTCOLOR | DTT_BORDERCOLOR | DTT_SHADOWCOLOR | DTT_SHADOWTYPE | \
    DTT_SHADOWOFFSET | DTT_BORDERSIZE | DTT_FONTPROP | DTT_COLORPROP | \
    DTT_STATEID | DTT_CALCRECT | DTT_APPLYOVERLAY | DTT_GLOWSIZE | DTT_COMPOSITED)

/* DrawThemeText() secondary flags */
#define DTT_GRAYED          0x00000001L
#define DTT_FLAGS2VALIDBITS DTT_GRAYED

/* HitTestThemeBackground() flags */
#define HTTB_BACKGROUNDSEG          0x00000000L
#define HTTB_FIXEDBORDER            0x00000002L
#define HTTB_CAPTION                0x00000004L
#define HTTB_RESIZINGBORDER_LEFT    0x00000010L
#define HTTB_RESIZINGBORDER_TOP     0x00000020L
#define HTTB_RESIZINGBORDER_RIGHT   0x00000040L
#define HTTB_RESIZINGBORDER_BOTTOM  0x00000080L
#define HTTB_RESIZINGBORDER \
    (HTTB_RESIZINGBORDER_LEFT | HTTB_RESIZINGBORDER_TOP | HTTB_RESIZINGBORDER_RIGHT | \
    HTTB_RESIZINGBORDER_BOTTOM)
#define HTTB_SIZINGTEMPLATE         0x00000100L
#define HTTB_SYSTEMSIZINGMARGINS    0x00000200L

/* Maximum integer list count */
#if (_WIN32_WINNT >= 0x0600)
    #define MAX_INTLIST_COUNT   402
#else
    #define MAX_INTLIST_COUNT   10
#endif

/* Window theme attribute option masks */
#if (_WIN32_WINNT >= 0x0600)
    #define WTNCA_NODRAWCAPTION 0x00000001L
    #define WTNCA_NODRAWICON    0x00000002L
    #define WTNCA_NOSYSMENU     0x00000004L
    #define WTNCA_NOMIRRORHELP  0x00000008L
    #define WTNCA_VALIDBITS \
        (WTNCA_NODRAWCAPTION | WTNCA_NODRAWICON | WTNCA_NOSYSMENU | WTNCA_NOMIRRORHELP)
#endif

/* EnableThemeDialogTexture() flags */
#define ETDT_DISABLE                        0x00000001L
#define ETDT_ENABLE                         0x00000002L
#define ETDT_USETABTEXTURE                  0x00000004L
#define ETDT_ENABLETAB                      (ETDT_ENABLE | ETDT_USETABTEXTURE)
#if (_WIN32_WINNT >= 0x0600)
    #define ETDT_USEAEROWIZARDTABTEXTURE    0x00000008L
    #define ETDT_ENABLEAEROWIZARDTAB        (ETDT_ENABLE | ETDT_USEAEROWIZARDTABTEXTURE)
    #define ETDT_VALIDBITS \
        (ETDT_DISABLE | ETDT_ENABLE | ETDT_USETABTEXTURE | ETDT_USEAEROWIZARDTABTEXTURE)
#endif

/* SetThemeAppProperties() flags */
#define STAP_ALLOW_NONCLIENT    0x00000001L
#define STAP_ALLOW_CONTROLS     0x00000002L
#define STAP_ALLOW_WEBCONTENT   0x00000004L
#define STAP_VALIDBITS \
    (STAP_ALLOW_NONCLIENT | STAP_ALLOW_CONTROLS | STAP_ALLOW_WEBCONTENT)

/* Theme documentation properties */
#define SZ_THDOCPROP_DISPLAYNAME    L"DisplayName"
#define SZ_THDOCPROP_CANONICALNAME  L"ThemeName"
#define SZ_THDOCPROP_TOOLTIP        L"ToolTip"
#define SZ_THDOCPROP_AUTHOR         L"author"

/* DrawThemeParentBackground() flags */
#if (_WIN32_WINNT >= 0x0600)
    #define DTPB_WINDOWDC           0x00000001L
    #define DTPB_USECTLCOLORSTATIC  0x00000002L
    #define DTPB_USEERASEBKGND      0x00000004L
#endif

/* GetThemeBitmap() flags */
#define GBF_DIRECT      0x00000001L
#define GBF_COPY        0x00000002L
#define GBF_VALIDBITS   (GBF_DIRECT | GBF_COPY)

/* Buffered paint paint flags */
#if (_WIN32_WINNT >= 0x0600)
    #define BPPF_ERASE      0x00000001L
    #define BPPF_NOCLIP     0x00000002L
    #define BPPF_NONCLIENT  0x00000004L
#endif

/* DrawThemeBackgroundEx() options */
typedef struct {
    DWORD   dwSize;
    DWORD   dwFlags;
    RECT    rcClip;
} DTBGOPTS;
typedef DTBGOPTS    *PDTBGOPTS;

/* DrawThemeTextEx() callback */
typedef int (WINAPI *DTT_CALLBACK_PROC)( HDC, LPWSTR, int, LPRECT, UINT, LPARAM );

/* DrawThemeTextEx() options */
typedef struct _DTTOPTS {
    DWORD       dwSize;
    DWORD       dwFlags;
    COLORREF    crText;
    COLORREF    crBorder;
    COLORREF    crShadow;
    int         iTextShadowType;
    POINT       ptShadowOffset;
    int         iBorderSize;
    int         iFontPropId;
    int         iColorPropId;
    int         iStateId;
    BOOL        fApplyOverlay;
    int         iGlowSize;
    DTT_CALLBACK_PROC   pfnDrawTextCallback;
    LPARAM      lParam;
} DTTOPTS;
typedef DTTOPTS *PDTTOPTS;

/* Theme sizes */
enum THEMESIZE {
    TS_MIN  = 0,
    TS_TRUE = 1,
    TS_DRAW = 2
};

/* Margins */
typedef struct _MARGINS {
    int cxLeftWidth;
    int cxRightWidth;
    int cyTopHeight;
    int cyBottomHeight;
} MARGINS;
typedef MARGINS *PMARGINS;

/* Integer list */
typedef struct _INTLIST {
    int iValueCount;
    int iValues[MAX_INTLIST_COUNT];
} INTLIST;
typedef INTLIST *PINTLIST;

/* Property origin */
enum PROPERTYORIGIN {
    PO_STATE    = 0,
    PO_PART     = 1,
    PO_CLASS    = 2,
    PO_GLOBAL   = 3,
    PO_NOTFOUND = 4
};

/* Window theme attribute types */
#if (_WIN32_WINNT >= 0x0600)
enum WINDOWTHEMEATTRIBUTETYPE {
    WTA_NONCLIENT   = 1
};
#endif

/* Window theme attribute options */
#if (_WIN32_WINNT >= 0x0600)
typedef struct _WTA_OPTIONS {
    DWORD   dwFlags;
    DWORD   dwMask;
} WTA_OPTIONS;
typedef WTA_OPTIONS *PWTA_OPTIONS;
#endif

/* Buffered paint buffer formats */
#if (_WIN32_WINNT >= 0x0600)
typedef enum _BP_BUFFERFORMAT {
    BPBF_COMPATIBLEBITMAP   = 0,
    BPBF_DIB                = 1,
    BPBF_TOPDOWNDIB         = 2,
    BPBF_TOPDOWNMONODIB     = 3
} BP_BUFFERFORMAT;
#define BPBF_COMPOSITED BPBF_TOPDOWNDIB
#endif

/* Buffered paint animation styles */
#if (_WIN32_WINNT >= 0x0600)
typedef enum _BP_ANIMATIONSTYLE {
    BPAS_NONE   = 0,
    BPAS_LINEAR = 1,
    BPAS_CUBIC  = 2,
    BPAS_SINE   = 3
} BP_ANIMATIONSTYLE;
#endif

/* Buffered paint animation parameters */
#if (_WIN32_WINNT >= 0x0600)
typedef struct _BP_ANIMATIONPARAMS {
    DWORD               cbSize;
    DWORD               dwFlags;
    BP_ANIMATIONSTYLE   style;
    DWORD               dwDuration;
} BP_ANIMATIONPARAMS;
typedef BP_ANIMATIONPARAMS  *PBP_ANIMATIONPARAMS;
#endif

/* Buffered paint paint parameters */
#if (_WIN32_WINNT >= 0x0600)
typedef struct _BP_PAINTPARAMS {
    DWORD               cbSize;
    DWORD               dwFlags;
    const RECT          *prcExclude;
    const BLENDFUNCTION *pBlendFunction;
} BP_PAINTPARAMS;
typedef BP_PAINTPARAMS  *PBP_PAINTPARAMS;
#endif

/* Functions in UXTHEME.DLL */
THEMEAPI            CloseThemeData( HTHEME );
THEMEAPI            DrawThemeBackground( HTHEME, HDC, int, int, LPCRECT, LPCRECT );
THEMEAPI            DrawThemeBackgroundEx( HTHEME, HDC, int, int, LPCRECT, const DTBGOPTS * );
THEMEAPI            DrawThemeEdge( HTHEME, HDC, int, int, LPCRECT, UINT, UINT, LPRECT );
THEMEAPI            DrawThemeIcon( HTHEME, HDC, int, int, LPCRECT, HIMAGELIST, int );
THEMEAPI            DrawThemeParentBackground( HWND, HDC, const RECT * );
THEMEAPI            DrawThemeText( HTHEME, HDC, int, int, LPCWSTR, int, DWORD, DWORD, LPCRECT );
THEMEAPI            EnableThemeDialogTexture( HWND, DWORD );
THEMEAPI            EnableTheming( BOOL );
THEMEAPI            GetCurrentThemeName( LPWSTR, int, LPWSTR, int, LPWSTR, int );
THEMEAPI_( DWORD )  GetThemeAppProperties( VOID );
THEMEAPI            GetThemeBackgroundContentRect( HTHEME, HDC, int, int, LPCRECT, LPRECT );
THEMEAPI            GetThemeBackgroundExtent( HTHEME, HDC, int, int, LPCRECT, LPRECT );
THEMEAPI            GetThemeBackgroundRegion( HTHEME, HDC, int, int, LPCRECT, HRGN * );
THEMEAPI            GetThemeBool( HTHEME, int, int, int, BOOL * );
THEMEAPI            GetThemeColor( HTHEME, int, int, int, COLORREF * );
THEMEAPI            GetThemeDocumentationProperty( LPCWSTR, LPCWSTR, LPWSTR, int );
THEMEAPI            GetThemeEnumValue( HTHEME, int, int, int, int * );
THEMEAPI            GetThemeFilename( HTHEME, int, int, int, LPWSTR, int );
THEMEAPI            GetThemeFont( HTHEME, HDC, int, int, int, LOGFONTW * );
THEMEAPI            GetThemeInt( HTHEME, int, int, int, int * );
THEMEAPI            GetThemeIntList( HTHEME, int, int, int, INTLIST * );
THEMEAPI            GetThemeMargins( HTHEME, HDC, int, int, int, LPCRECT, MARGINS * );
THEMEAPI            GetThemeMetric( HTHEME, HDC, int, int, int, int * );
THEMEAPI            GetThemePartSize( HTHEME, HDC, int, int, LPCRECT, enum THEMESIZE, SIZE * );
THEMEAPI            GetThemePosition( HTHEME, int, int, int, POINT * );
THEMEAPI            GetThemePropertyOrigin( HTHEME, int, int, int, enum PROPERTYORIGIN * );
THEMEAPI            GetThemeRect( HTHEME, int, int, int, LPRECT );
THEMEAPI            GetThemeString( HTHEME, int, int, int, LPWSTR, int );
THEMEAPI_( BOOL )   GetThemeSysBool( HTHEME, int );
THEMEAPI_( COLORREF )   GetThemeSysColor( HTHEME, int );
THEMEAPI_( HBRUSH ) GetThemeSysColorBrush( HTHEME, int );
THEMEAPI            GetThemeSysFont( HTHEME, int, LOGFONTW * );
THEMEAPI            GetThemeSysInt( HTHEME, int, int * );
THEMEAPI_( int )    GetThemeSysSize( HTHEME, int );
THEMEAPI            GetThemeSysString( HTHEME, int, LPWSTR, int );
THEMEAPI            GetThemeTextExtent( HTHEME, HDC, int, int, LPCWSTR, int, DWORD, LPCRECT, LPRECT );
THEMEAPI            GetThemeTextMetrics( HTHEME, HDC, int, int, TEXTMETRICW * );
THEMEAPI_( HTHEME ) GetWindowTheme( HWND );
THEMEAPI            HitTestThemeBackground( HTHEME, HDC, int, int, DWORD, LPCRECT, HRGN, POINT, WORD * );
THEMEAPI_( BOOL )   IsAppThemed( VOID );
THEMEAPI_( BOOL )   IsThemeActive( VOID );
THEMEAPI_( BOOL )   IsThemeBackgroundPartiallyTransparent( HTHEME, int, int );
THEMEAPI_( BOOL )   IsThemeDialogTextureEnabled( HWND );
THEMEAPI_( BOOL )   IsThemePartDefined( HTHEME, int, int );
THEMEAPI_( HTHEME ) OpenThemeData( HWND, LPCWSTR );
THEMEAPI_( HTHEME ) OpenThemeDataEx( HWND, LPCWSTR, DWORD );
THEMEAPI_( void )   SetThemeAppProperties( DWORD );
THEMEAPI            SetWindowTheme( HWND, LPCWSTR, LPCWSTR );
#if (_WIN32_WINNT >= 0x0600)
THEMEAPI_( HANIMATIONBUFFER )   BeginBufferedAnimation( HWND, HDC, const RECT *, BP_BUFFERFORMAT, BP_PAINTPARAMS *, BP_ANIMATIONPARAMS *, HDC *, HDC * );
THEMEAPI_( HPAINTBUFFER )   BeginBufferedPaint( HDC, const RECT *, BP_BUFFERFORMAT, BP_PAINTPARAMS *, HDC * );
THEMEAPI            BufferedPaintClear( HPAINTBUFFER, const RECT * );
THEMEAPI            BufferedPaintInit( VOID );
THEMEAPI_( BOOL )   BufferedPaintRenderAnimation( HWND, HDC );
THEMEAPI            BufferedPaintSetAlpha( HPAINTBUFFER, const RECT *, BYTE );
THEMEAPI            BufferedPaintStopAllAnimations( HWND );
THEMEAPI            BufferedPaintUnInit( VOID );
THEMEAPI            DrawThemeParentBackgroundEx( HWND, HDC, DWORD, const RECT * );
THEMEAPI            DrawThemeTextEx( HTHEME, HDC, int, int, LPCWSTR, int, DWORD, LPRECT, const DTTOPTS * );
THEMEAPI            EndBufferedAnimation( HANIMATIONBUFFER, BOOL );
THEMEAPI            EndBufferedPaint( HPAINTBUFFER, BOOL );
THEMEAPI            GetBufferedPaintBits( HPAINTBUFFER, RGBQUAD **, int * );
THEMEAPI_( HDC )    GetBufferedPaintDC( HPAINTBUFFER );
THEMEAPI_( HDC )    GetBufferedPaintTargetDC( HPAINTBUFFER );
THEMEAPI            GetBufferedPaintTargetRect( HPAINTBUFFER, RECT * );
THEMEAPI            GetThemeBitmap( HTHEME, int, int, int, ULONG, HBITMAP * );
THEMEAPI            GetThemeStream( HTHEME, int, int, int, VOID **, DWORD *, HINSTANCE );
THEMEAPI            GetThemeTransitionDuration( HTHEME, int, int, int, int, DWORD * );
THEMEAPI_( BOOL )   IsCompositionActive();
THEMEAPI            SetWindowThemeAttribute( HWND, enum WINDOWTHEMEATTRIBUTETYPE, PVOID, DWORD );
#endif

/* Functions implemented as macros */
#if (_WIN32_WINNT >= 0x0600)
    #define BufferedPaintMakeOpaque( p1, p2 ) \
        BufferedPaintSetAlpha( p1, p2, 255 )
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _UXTHEME_H_ */
