/*
 *  pmgpi.h     OS/2 Graphics Programming Interface include file
 *              for 32-bit development.
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

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define INCL_GPIINCLUDED

#ifdef INCL_GPI
    #define INCL_GPIBITMAPS
    #define INCL_GPICONTROL
    #define INCL_GPICORRELATION
    #define INCL_GPIDEFAULTS
    #define INCL_GPILCIDS
    #define INCL_GPILOGCOLORTABLE
    #define INCL_GPIMETAFILES
    #define INCL_GPIPATHS
    #define INCL_GPIPOLYGON
    #define INCL_GPIPRIMITIVES
    #define INCL_GPIREGIONS
    #define INCL_GPITRANSFORMS
    #define INCL_GPISEGMENTS
#endif

#define GPI_ERROR      0
#define GPI_OK         1
#define GPI_ALTERROR (-1)

#define CLR_NOINDEX (-254)

#define FIXEDINT(fx)                 ((SHORT)HIUSHORT(fx))
#define FIXEDFRAC(fx)                (LOUSHORT(fx))
#define MAKEFIXED(intpart,fractpart) MAKELONG(fractpart,intpart)

typedef struct _SIZEL {
    LONG cx;
    LONG cy;
} SIZEL, *PSIZEL;

#if defined(INCL_GPIBITMAPS) || !defined(INCL_NOCOMMON)

#define ROP_SRCCOPY     0x00CC
#define ROP_SRCPAINT    0x00EE
#define ROP_SRCAND      0x0088
#define ROP_SRCINVERT   0x0066
#define ROP_SRCERASE    0x0044
#define ROP_NOTSRCCOPY  0x0033
#define ROP_NOTSRCERASE 0x0011
#define ROP_MERGECOPY   0x00C0
#define ROP_MERGEPAINT  0x00BB
#define ROP_PATCOPY     0x00F0
#define ROP_PATPAINT    0x00FB
#define ROP_PATINVERT   0x005A
#define ROP_DSTINVERT   0x0055
#define ROP_ZERO        0x0000
#define ROP_ONE         0x00FF

#define BBO_OR            0
#define BBO_AND           1
#define BBO_IGNORE        2
#define BBO_PAL_COLORS    4
#define BBO_NO_COLOR_INFO 8

#define FF_BOUNDARY 0
#define FF_SURFACE  1

#define HBM_ERROR ((HBITMAP)-1)

LONG    APIENTRY GpiBitBlt(HPS,HPS,LONG,PPOINTL,LONG,ULONG);
BOOL    APIENTRY GpiDeleteBitmap(HBITMAP);
HBITMAP APIENTRY GpiLoadBitmap(HPS,HMODULE,ULONG,LONG,LONG);
HBITMAP APIENTRY GpiSetBitmap(HPS,HBITMAP);
LONG    APIENTRY GpiWCBitBlt(HPS,HBITMAP,LONG,PPOINTL,LONG,ULONG);

#endif

#if defined(INCL_GPIBITMAPS)

#define CBM_INIT 4

#define BCA_UNCOMP         0
#define BCA_HUFFMAN1D      3
#define BCA_RLE4           2
#define BCA_RLE8           1
#define BCA_RLE24          4
#define BRU_METRIC         0
#define BRA_BOTTOMUP       0
#define BRH_NOTHALFTONED   0
#define BRH_ERRORDIFFUSION 1
#define BRH_PANDA          2
#define BRH_SUPERCIRCLE    3
#define BCE_PALETTE      (-1)
#define BCE_RGB            0

#define BFT_ICON         0x4349
#define BFT_BMAP         0x4d42
#define BFT_POINTER      0x5450
#define BFT_COLORICON    0x4943
#define BFT_COLORPOINTER 0x5043
#define BFT_BITMAPARRAY  0x4142

#define BMB_ERROR (-1)

#pragma pack( __push, 1 )

typedef struct _RGB {
    BYTE bBlue;
    BYTE bGreen;
    BYTE bRed;
} RGB;

typedef struct _RGB2 {
    BYTE bBlue;
    BYTE bGreen;
    BYTE bRed;
    BYTE fcOptions;
} RGB2, *PRGB2;

typedef struct _BITMAPINFO {
    ULONG  cbFix;
    USHORT cx;
    USHORT cy;
    USHORT cPlanes;
    USHORT cBitCount;
    RGB    argbColor[1];
} BITMAPINFO, *PBITMAPINFO;

typedef struct _BITMAPINFO2 {
    ULONG  cbFix;
    ULONG  cx;
    ULONG  cy;
    USHORT cPlanes;
    USHORT cBitCount;
    ULONG  ulCompression;
    ULONG  cbImage;
    ULONG  cxResolution;
    ULONG  cyResolution;
    ULONG  cclrUsed;
    ULONG  cclrImportant;
    USHORT usUnits;
    USHORT usReserved;
    USHORT usRecording;
    USHORT usRendering;
    ULONG  cSize1;
    ULONG  cSize2;
    ULONG  ulColorEncoding;
    ULONG  ulIdentifier;
    RGB2   argbColor[1];
} BITMAPINFO2, *PBITMAPINFO2;

typedef struct _BITMAPINFOHEADER {
    ULONG  cbFix;
    USHORT cx;
    USHORT cy;
    USHORT cPlanes;
    USHORT cBitCount;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct _BITMAPINFOHEADER2 {
    ULONG  cbFix;
    ULONG  cx;
    ULONG  cy;
    USHORT cPlanes;
    USHORT cBitCount;
    ULONG  ulCompression;
    ULONG  cbImage;
    ULONG  cxResolution;
    ULONG  cyResolution;
    ULONG  cclrUsed;
    ULONG  cclrImportant;
    USHORT usUnits;
    USHORT usReserved;
    USHORT usRecording;
    USHORT usRendering;
    ULONG  cSize1;
    ULONG  cSize2;
    ULONG  ulColorEncoding;
    ULONG  ulIdentifier;
} BITMAPINFOHEADER2, *PBITMAPINFOHEADER2;

typedef struct _BITMAPFILEHEADER {
    USHORT usType;
    ULONG  cbSize;
    SHORT  xHotspot;
    SHORT  yHotspot;
    ULONG  offBits;
    BITMAPINFOHEADER bmp;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct _BITMAPARRAYFILEHEADER {
    USHORT usType;
    ULONG  cbSize;
    ULONG  offNext;
    USHORT cxDisplay;
    USHORT cyDisplay;
    BITMAPFILEHEADER bfh;
} BITMAPARRAYFILEHEADER, *PBITMAPARRAYFILEHEADER;

typedef struct _BITMAPFILEHEADER2 {
    USHORT usType;
    ULONG  cbSize;
    SHORT  xHotspot;
    SHORT  yHotspot;
    ULONG  offBits;
    BITMAPINFOHEADER2 bmp2;
} BITMAPFILEHEADER2, *PBITMAPFILEHEADER2;

typedef struct _BITMAPARRAYFILEHEADER2 {
    USHORT usType;
    ULONG  cbSize;
    ULONG  offNext;
    USHORT cxDisplay;
    USHORT cyDisplay;
    BITMAPFILEHEADER2 bfh2;
} BITMAPARRAYFILEHEADER2, *PBITMAPARRAYFILEHEADER2;

#pragma pack( __pop )

HBITMAP APIENTRY GpiCreateBitmap(HPS,PBITMAPINFOHEADER2,ULONG,PBYTE,PBITMAPINFO2);
LONG    APIENTRY GpiFloodFill(HPS,LONG,LONG);
LONG    APIENTRY GpiQueryBitmapBits(HPS,LONG,LONG,PBYTE,PBITMAPINFO2);
BOOL    APIENTRY GpiQueryBitmapDimension(HBITMAP,PSIZEL);
HBITMAP APIENTRY GpiQueryBitmapHandle(HPS,LONG);
BOOL    APIENTRY GpiQueryBitmapInfoHeader(HBITMAP,PBITMAPINFOHEADER2);
BOOL    APIENTRY GpiQueryBitmapParameters(HBITMAP,PBITMAPINFOHEADER);
BOOL    APIENTRY GpiQueryDeviceBitmapFormats(HPS,LONG,PLONG);
LONG    APIENTRY GpiQueryPel(HPS,PPOINTL);
LONG    APIENTRY GpiSetBitmapBits(HPS,LONG,LONG,PBYTE,PBITMAPINFO2);
BOOL    APIENTRY GpiSetBitmapDimension(HBITMAP,PSIZEL);
BOOL    APIENTRY GpiSetBitmapId(HPS,HBITMAP,LONG);
LONG    APIENTRY GpiSetPel(HPS,PPOINTL);
LONG    APIENTRY GpiDrawBits(HPS,PVOID,PBITMAPINFO2,LONG,PPOINTL,LONG,ULONG);

#endif

#if defined(INCL_GPICONTROL) || !defined(INCL_NOCOMMON)

#define PU_ARBITRARY 0x0004
#define PU_PELS      0x0008
#define PU_LOMETRIC  0x000C
#define PU_HIMETRIC  0x0010
#define PU_LOENGLISH 0x0014
#define PU_HIENGLISH 0x0018
#define PU_TWIPS     0x001C

#define GPIF_DEFAULT      0
#define GPIF_SHORT   0x0100
#define GPIF_LONG    0x0200

#define GPIT_NORMAL       0
#define GPIT_MICRO   0x1000
#define GPIT_INK     0x2000

#define GPIA_NOASSOC      0
#define GPIA_ASSOC   0x4000

#define GPIM_AREAEXCL 0x8000

#define HDC_ERROR ((HDC)-1)

BOOL   APIENTRY GpiAssociate(HPS,HDC);
HPS    APIENTRY GpiCreatePS(HAB,HDC,PSIZEL,ULONG);
BOOL   APIENTRY GpiDestroyPS(HPS);
BOOL   APIENTRY GpiErase(HPS);
HDC    APIENTRY GpiQueryDevice(HPS);
BOOL   APIENTRY GpiRestorePS(HPS,LONG);
LONG   APIENTRY GpiSavePS(HPS);

#endif

#if defined(INCL_GPICONTROL)

#define DCTL_ERASE      1
#define DCTL_DISPLAY    2
#define DCTL_BOUNDARY   3
#define DCTL_DYNAMIC    4
#define DCTL_CORRELATE  5
#define DCTL_ERROR    (-1)
#define DCTL_OFF        0
#define DCTL_ON         1

#define SDW_ERROR (-1)
#define SDW_OFF     0
#define SDW_ON      1

#define GRES_ATTRS    0x0001
#define GRES_SEGMENTS 0x0002
#define GRES_ALL      0x0004

#define PS_UNITS      0x00FC
#define PS_FORMAT     0x0F00
#define PS_TYPE       0x1000
#define PS_MODE       0x2000
#define PS_ASSOCIATE  0x4000
#define PS_NORESET    0x8000

#define GPIE_SEGMENT     0
#define GPIE_ELEMENT     1
#define GPIE_DATA        2

#define DM_ERROR         0
#define DM_DRAW          1
#define DM_RETAIN        2
#define DM_DRAWANDRETAIN 3

LONG   APIENTRY GpiQueryDrawControl(HPS,LONG);
LONG   APIENTRY GpiQueryDrawingMode(HPS);
ULONG  APIENTRY GpiQueryPS(HPS,PSIZEL);
LONG   APIENTRY GpiQueryStopDraw(HPS);
BOOL   APIENTRY GpiResetPS(HPS,ULONG);
BOOL   APIENTRY GpiSetDrawControl(HPS,LONG,LONG);
BOOL   APIENTRY GpiSetDrawingMode(HPS,LONG);
BOOL   APIENTRY GpiSetPS(HPS,PSIZEL,ULONG);
BOOL   APIENTRY GpiSetStopDraw(HPS,LONG);

#endif

#if defined(INCL_GPILCIDS)

#define QF_PUBLIC     1
#define QF_PRIVATE    2
#define QF_NO_GENERIC 4
#define QF_NO_DEVICE  8

#define QFA_PUBLIC  1
#define QFA_PRIVATE 2
#define QFA_ERROR   GPI_ALTERROR

#define FONT_IGNORE_FONTRES 1
#define FONT_MATCH_NEAREST  2

#define FONT_DEFAULT   1
#define FONT_MATCH     2
#define LCIDT_FONT     6
#define LCIDT_BITMAP   7
#define LCID_ALL     (-1)

#define RC_ATMAVAIL   1
#define RC_ATMENABLED 1
#define RC_TTAVAIL    2
#define RC_TTENABLED  2

#define FWEIGHT_DONT_CARE   0
#define FWEIGHT_ULTRA_LIGHT 1
#define FWEIGHT_EXTRA_LIGHT 2
#define FWEIGHT_LIGHT       3
#define FWEIGHT_SEMI_LIGHT  4
#define FWEIGHT_NORMAL      5
#define FWEIGHT_SEMI_BOLD   6
#define FWEIGHT_BOLD        7
#define FWEIGHT_EXTRA_BOLD  8
#define FWEIGHT_ULTRA_BOLD  9

#define FWIDTH_DONT_CARE       0
#define FWIDTH_ULTRA_CONDENSED 1
#define FWIDTH_EXTRA_CONDENSED 2
#define FWIDTH_CONDENSED       3
#define FWIDTH_SEMI_CONDENSED  4
#define FWIDTH_NORMAL          5
#define FWIDTH_SEMI_EXPANDED   6
#define FWIDTH_EXPANDED        7
#define FWIDTH_EXTRA_EXPANDED  8
#define FWIDTH_ULTRA_EXPANDED  9

#define FTYPE_ITALIC            0x01
#define FTYPE_ITALIC_DONT_CARE  0x02
#define FTYPE_OBLIQUE           0x04
#define FTYPE_OBLIQUE_DONT_CARE 0x08
#define FTYPE_ROUNDED           0x10
#define FTYPE_ROUNDED_DONT_CARE 0x20

typedef struct _KERNINGPAIRS {
    SHORT sFirstChar;
    SHORT sSecondChar;
    LONG  lKerningAmount;
} KERNINGPAIRS,*PKERNINGPAIRS;

typedef struct _RASTERIZERCAPS {
    ULONG cb;
    ULONG ulAvailFlags;
    ULONG ulEnabledFlags;
} RASTERIZERCAPS,*PRASTERIZERCAPS;

typedef struct _FACENAMEDESC {
    USHORT usSize;
    USHORT usWeightClass;
    USHORT usWidthClass;
    USHORT usReserved;
    ULONG  flOptions;
} FACENAMEDESC,*PFACENAMEDESC;

typedef CHAR FFDESCS[2][FACESIZE],*PFFDESCS;

typedef struct _FFDESCS2 {
    ULONG cbLength;
    ULONG cbFacenameOffset;
    BYTE  abFamilyName[1];
} FFDESCS2,*PFFDESCS2;

LONG  APIENTRY GpiCreateLogFont(HPS,PSTR8,LONG,PFATTRS);
BOOL  APIENTRY GpiDeleteSetId(HPS,LONG);
BOOL  APIENTRY GpiLoadFonts(HAB,PCSZ);
BOOL  APIENTRY GpiLoadPublicFonts(HAB,PCSZ);
ULONG APIENTRY GpiQueryCp(HPS);
ULONG APIENTRY GpiQueryFaceString(HPS,PCSZ,PFACENAMEDESC,LONG,PCSZ);
ULONG APIENTRY GpiQueryFontAction(HAB,ULONG);
LONG  APIENTRY GpiQueryFontFileDescriptions(HAB,PCSZ,PLONG,PFFDESCS);
ULONG APIENTRY GpiQueryFontMappingFlags(HPS);
BOOL  APIENTRY GpiQueryFontMetrics(HPS,LONG,PFONTMETRICS);
LONG  APIENTRY GpiQueryFonts(HPS,ULONG,PCSZ,PLONG,LONG,PFONTMETRICS);
LONG  APIENTRY GpiQueryFullFontFileDescs(HAB,PCSZ,PLONG,PVOID,PLONG);
LONG  APIENTRY GpiQueryKerningPairs(HPS,LONG,PKERNINGPAIRS);
BOOL  APIENTRY GpiQueryLogicalFont(HPS,LONG,PSTR8,PFATTRS,LONG);
LONG  APIENTRY GpiQueryNumberSetIds(HPS);
BOOL  APIENTRY GpiQueryRasterizerCaps(PRASTERIZERCAPS);
BOOL  APIENTRY GpiQuerySetIds(HPS,LONG,PLONG,PSTR8,PLONG);
BOOL  APIENTRY GpiQueryWidthTable(HPS,LONG,LONG,PLONG);
BOOL  APIENTRY GpiSetCp(HPS,ULONG);
ULONG APIENTRY GpiSetFontMappingFlags(HPS,ULONG);
BOOL  APIENTRY GpiUnloadFonts(HAB,PCSZ);
BOOL  APIENTRY GpiUnloadPublicFonts(HAB,PCSZ);

#endif

#if defined(INCL_GPILOGCOLORTABLE)

#define LCOL_RESET                   0x0001
#define LCOL_REALIZABLE              0x0002
#define LCOL_PURECOLOR               0x0004
#define LCOL_OVERRIDE_DEFAULT_COLORS 0x0008
#define LCOL_REALIZED                0x0010

#define LCOLF_DEFAULT   0
#define LCOLF_INDRGB    1
#define LCOLF_CONSECRGB 2
#define LCOLF_RGB       3
#define LCOLF_PALETTE   4

#define LCOLOPT_REALIZED 1
#define LCOLOPT_INDEX    2

#define PC_RESERVED   1
#define PC_EXPLICIT   2
#define PC_NOCOLLAPSE 4

#define QCD_LCT_FORMAT  0
#define QCD_LCT_LOINDEX 1
#define QCD_LCT_HIINDEX 2
#define QCD_LCT_OPTIONS 3

#define QLCT_ERROR     (-1)
#define QLCT_RGB       (-2)
#define QLCT_NOTLOADED (-1)

#define PAL_ERROR (-1)

LONG   APIENTRY GpiAnimatePalette(HPAL,ULONG,ULONG,ULONG,PULONG);
BOOL   APIENTRY GpiCreateLogColorTable(HPS,ULONG,LONG,LONG,LONG,PLONG);
HPAL   APIENTRY GpiCreatePalette(HAB,ULONG,ULONG,ULONG,PULONG);
BOOL   APIENTRY GpiDeletePalette(HPAL);
BOOL   APIENTRY GpiQueryColorData(HPS,LONG,PLONG);
LONG   APIENTRY GpiQueryColorIndex(HPS,ULONG,LONG);
LONG   APIENTRY GpiQueryLogColorTable(HPS,ULONG,LONG,LONG,PLONG);
LONG   APIENTRY GpiQueryNearestColor(HPS,ULONG,LONG);
LONG   APIENTRY GpiQueryNearestPaletteIndex(HPAL,ULONG);
HPAL   APIENTRY GpiQueryPalette(HPS);
LONG   APIENTRY GpiQueryPaletteInfo(HPAL,HPS,ULONG,ULONG,ULONG,PULONG);
LONG   APIENTRY GpiQueryRealColors(HPS,ULONG,LONG,LONG,PLONG);
LONG   APIENTRY GpiQueryRGBColor(HPS,ULONG,LONG);
HPAL   APIENTRY GpiSelectPalette(HPS,HPAL);
BOOL   APIENTRY GpiSetPaletteEntries(HPAL,ULONG,ULONG,ULONG,PULONG);
ULONG  APIENTRY GpiResizePalette(HPAL,ULONG);

#endif

#if defined(INCL_GPIPATHS)

#define FPATH_ALTERNATE 0
#define FPATH_WINDING   2
#define FPATH_INCL      0
#define FPATH_EXCL      8

#define MPATH_STROKE 6

#define SCP_ALTERNATE 0
#define SCP_WINDING   2
#define SCP_AND       4
#define SCP_RESET     0
#define SCP_INCL      0
#define SCP_EXCL      8

BOOL   APIENTRY GpiBeginPath(HPS,LONG);
BOOL   APIENTRY GpiCloseFigure(HPS);
BOOL   APIENTRY GpiEndPath(HPS);
LONG   APIENTRY GpiFillPath(HPS,LONG,LONG);
BOOL   APIENTRY GpiModifyPath(HPS,LONG,LONG);
LONG   APIENTRY GpiOutlinePath(HPS,LONG,LONG);
HRGN   APIENTRY GpiPathToRegion(HPS,LONG,LONG);
BOOL   APIENTRY GpiSetClipPath(HPS,LONG,LONG);
LONG   APIENTRY GpiStrokePath(HPS,LONG,ULONG);

#endif

#if defined(INCL_GPIPOLYGON)

#define POLYGON_NOBOUNDARY  0
#define POLYGON_BOUNDARY    1
#define POLYGON_ALTERNATE   0
#define POLYGON_WINDING     2
#define POLYGON_INCL        0
#define POLYGON_EXCL        8
#define POLYGON_FILL        0
#define POLYGON_NOFILL     16

typedef struct _POLYGON {
    ULONG   ulPoints;
    PPOINTL aPointl;
} POLYGON, *PPOLYGON;

typedef struct _POLYSET {
    ULONG   ulPolys;
    POLYGON aPolygon[1];
} POLYSET, *PPOLYSET;

LONG   APIENTRY GpiPolygons(HPS hps, ULONG ulCount, PPOLYGON paplgn, ULONG flOpts, ULONG flMdl);

#endif

#if defined(INCL_GPIPRIMITIVES) || !defined(INCL_NOCOMMON)

#define BA_NOBOUNDARY 0
#define BA_BOUNDARY   1
#define BA_ALTERNATE  0
#define BA_WINDING    2
#define BA_INCL       0
#define BA_EXCL       8

#define CHS_OPAQUE     0x0001
#define CHS_VECTOR     0x0002
#define CHS_LEAVEPOS   0x0008
#define CHS_CLIP       0x0010
#define CHS_UNDERSCORE 0x0200
#define CHS_STRIKEOUT  0x0400

#define CLR_ERROR      (-255)
#define CLR_FALSE        (-5)
#define CLR_TRUE         (-4)
#define CLR_DEFAULT      (-3)
#define CLR_WHITE        (-2)
#define CLR_BLACK        (-1)
#define CLR_BACKGROUND     0
#define CLR_BLUE           1
#define CLR_RED            2
#define CLR_PINK           3
#define CLR_GREEN          4
#define CLR_CYAN           5
#define CLR_YELLOW         6
#define CLR_NEUTRAL        7
#define CLR_DARKGRAY       8
#define CLR_DARKBLUE       9
#define CLR_DARKRED       10
#define CLR_DARKPINK      11
#define CLR_DARKGREEN     12
#define CLR_DARKCYAN      13
#define CLR_BROWN         14
#define CLR_PALEGRAY      15

#define DRO_FILL        1
#define DRO_OUTLINE     2
#define DRO_OUTLINEFILL 3
#define DRO_EXCLUSIVE   0x10000000

#define FM_ERROR         (-1)
#define FM_DEFAULT         0
#define FM_OR              1
#define FM_OVERPAINT       2
#define FM_XOR             4
#define FM_LEAVEALONE      5
#define FM_AND             6
#define FM_SUBTRACT        7
#define FM_MASKSRCNOT      8
#define FM_ZERO            9
#define FM_NOTMERGESRC    10
#define FM_NOTXORSRC      11
#define FM_INVERT         12
#define FM_MERGESRCNOT    13
#define FM_NOTCOPYSRC     14
#define FM_MERGENOTSRC    15
#define FM_NOTMASKSRC     16
#define FM_ONE            17

#define BM_ERROR          (-1)
#define BM_DEFAULT          0
#define BM_OR               1
#define BM_OVERPAINT        2
#define BM_XOR              4
#define BM_LEAVEALONE       5
#define BM_AND              6
#define BM_SUBTRACT         7
#define BM_MASKSRCNOT       8
#define BM_ZERO             9
#define BM_NOTMERGESRC     10
#define BM_NOTXORSRC       11
#define BM_INVERT          12
#define BM_MERGESRCNOT     13
#define BM_NOTCOPYSRC      14
#define BM_MERGENOTSRC     15
#define BM_NOTMASKSRC      16
#define BM_ONE             17
#define BM_SRCTRANSPARENT  18
#define BM_DESTTRANSPARENT 19

#define LCID_ERROR   (-1)
#define LCID_DEFAULT   0

#define PATSYM_ERROR    (-1)
#define PATSYM_DEFAULT    0
#define PATSYM_DENSE1     1
#define PATSYM_DENSE2     2
#define PATSYM_DENSE3     3
#define PATSYM_DENSE4     4
#define PATSYM_DENSE5     5
#define PATSYM_DENSE6     6
#define PATSYM_DENSE7     7
#define PATSYM_DENSE8     8
#define PATSYM_VERT       9
#define PATSYM_HORIZ     10
#define PATSYM_DIAG1     11
#define PATSYM_DIAG2     12
#define PATSYM_DIAG3     13
#define PATSYM_DIAG4     14
#define PATSYM_NOSHADE   15
#define PATSYM_SOLID     16
#define PATSYM_HALFTONE  17
#define PATSYM_HATCH     18
#define PATSYM_DIAGHATCH 19
#define PATSYM_BLANK     64

#define RGB_ERROR       (-255)
#define RGB_BLACK  0x00000000
#define RGB_BLUE   0x000000FF
#define RGB_GREEN  0x0000FF00
#define RGB_CYAN   0x0000FFFF
#define RGB_RED    0x00FF0000
#define RGB_PINK   0x00FF00FF
#define RGB_YELLOW 0x00FFFF00
#define RGB_WHITE  0x00FFFFFF

#define TXTBOX_TOPLEFT     0
#define TXTBOX_BOTTOMLEFT  1
#define TXTBOX_TOPRIGHT    2
#define TXTBOX_BOTTOMRIGHT 3
#define TXTBOX_CONCAT      4
#define TXTBOX_COUNT       5

BOOL   APIENTRY GpiBeginArea(HPS hps, ULONG flOptions);
LONG   APIENTRY GpiEndArea(HPS hps);
LONG   APIENTRY GpiBox(HPS hps, LONG lControl, PPOINTL pptlPoint, LONG lHRound, LONG lVRound);
LONG   APIENTRY GpiLine(HPS hps, PPOINTL pptlEndPoint);
BOOL   APIENTRY GpiMove(HPS hps, PPOINTL pptlPoint);
LONG   APIENTRY GpiPolyLine(HPS hps, LONG lCount, PPOINTL aptlPoints);
LONG   APIENTRY GpiPolyLineDisjoint(HPS hps, LONG lCount, PPOINTL aptlPoints);
LONG   APIENTRY GpiQueryColor(HPS hps);
LONG   APIENTRY GpiQueryPattern(HPS hps);
BOOL   APIENTRY GpiSetColor(HPS hps, LONG lColor);
BOOL   APIENTRY GpiSetPattern(HPS hps, LONG lPatternSymbol);
LONG   APIENTRY GpiCharString(HPS hps, LONG lCount, PCH pchString);
LONG   APIENTRY GpiCharStringAt(HPS hps, PPOINTL pptlPoint, LONG lCount, PCH pchString);

#endif

#if defined(INCL_GPIPRIMITIVES)

#define AM_ERROR     (-1)
#define AM_PRESERVE    0
#define AM_NOPRESERVE  1

#define CM_ERROR   (-1)
#define CM_DEFAULT   0
#define CM_MODE1     1
#define CM_MODE2     2
#define CM_MODE3     3

#define LINETYPE_ERROR       (-1)
#define LINETYPE_DEFAULT       0
#define LINETYPE_DOT           1
#define LINETYPE_SHORTDASH     2
#define LINETYPE_DASHDOT       3
#define LINETYPE_DOUBLEDOT     4
#define LINETYPE_LONGDASH      5
#define LINETYPE_DASHDOUBLEDOT 6
#define LINETYPE_SOLID         7
#define LINETYPE_INVISIBLE     8
#define LINETYPE_ALTERNATE     9

#define LINEWIDTH_ERROR          (-1)
#define LINEWIDTH_DEFAULT          0
#define LINEWIDTH_NORMAL  0x00010000
#define LINEWIDTH_THICK   0x00020000

#define LINEWIDTHGEOM_ERROR (-1)

#define LINEEND_ERROR     (-1)
#define LINEEND_DEFAULT     0
#define LINEEND_FLAT        1
#define LINEEND_SQUARE      2
#define LINEEND_ROUND       3

#define LINEJOIN_ERROR    (-1)
#define LINEJOIN_DEFAULT    0
#define LINEJOIN_BEVEL      1
#define LINEJOIN_ROUND      2
#define LINEJOIN_MITRE      3

#define CHDIRN_ERROR      (-1)
#define CHDIRN_DEFAULT      0
#define CHDIRN_LEFTRIGHT    1
#define CHDIRN_TOPBOTTOM    2
#define CHDIRN_RIGHTLEFT    3
#define CHDIRN_BOTTOMTOP    4

#define PRIM_LINE   1
#define PRIM_CHAR   2
#define PRIM_MARKER 3
#define PRIM_AREA   4
#define PRIM_IMAGE  5

#define LBB_COLOR         0x0001
#define LBB_BACK_COLOR    0x0002
#define LBB_MIX_MODE      0x0004
#define LBB_BACK_MIX_MODE 0x0008
#define LBB_WIDTH         0x0010
#define LBB_GEOM_WIDTH    0x0020
#define LBB_TYPE          0x0040
#define LBB_END           0x0080
#define LBB_JOIN          0x0100

#define CBB_COLOR         0x0001
#define CBB_BACK_COLOR    0x0002
#define CBB_MIX_MODE      0x0004
#define CBB_BACK_MIX_MODE 0x0008
#define CBB_SET           0x0010
#define CBB_MODE          0x0020
#define CBB_BOX           0x0040
#define CBB_ANGLE         0x0080
#define CBB_SHEAR         0x0100
#define CBB_DIRECTION     0x0200
#define CBB_TEXT_ALIGN    0x0400
#define CBB_EXTRA         0x0800
#define CBB_BREAK_EXTRA   0x1000

#define MBB_COLOR         0x0001
#define MBB_BACK_COLOR    0x0002
#define MBB_MIX_MODE      0x0004
#define MBB_BACK_MIX_MODE 0x0008
#define MBB_SET           0x0010
#define MBB_SYMBOL        0x0020
#define MBB_BOX           0x0040

#define ABB_COLOR         0x0001
#define ABB_BACK_COLOR    0x0002
#define ABB_MIX_MODE      0x0004
#define ABB_BACK_MIX_MODE 0x0008
#define ABB_SET           0x0010
#define ABB_SYMBOL        0x0020
#define ABB_REF_POINT     0x0040

#define IBB_COLOR         0x0001
#define IBB_BACK_COLOR    0x0002
#define IBB_MIX_MODE      0x0004
#define IBB_BACK_MIX_MODE 0x0008

#define TA_NORMAL_HORIZ   0x0001
#define TA_LEFT           0x0002
#define TA_CENTER         0x0003
#define TA_RIGHT          0x0004
#define TA_STANDARD_HORIZ 0x0005
#define TA_NORMAL_VERT    0x0100
#define TA_TOP            0x0200
#define TA_HALF           0x0300
#define TA_BASE           0x0400
#define TA_BOTTOM         0x0500
#define TA_STANDARD_VERT  0x0600

typedef PVOID PBUNDLE;

typedef struct _SIZEF {
    FIXED  cx;
    FIXED  cy;
} SIZEF, *PSIZEF;

typedef struct _ARCPARAMS {
    LONG lP;
    LONG lQ;
    LONG lR;
    LONG lS;
} ARCPARAMS, *PARCPARAMS;

typedef struct _AREABUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
    USHORT usSet;
    USHORT usSymbol;
    POINTL ptlRefPoint;
} AREABUNDLE, *PAREABUNDLE;

typedef struct _CHARBUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
    USHORT usSet;
    USHORT usPrecision;
    SIZEF  sizfxCell;
    POINTL ptlAngle;
    POINTL ptlShear;
    USHORT usDirection;
    USHORT usTextAlign;
    FIXED  fxExtra;
    FIXED  fxBreakExtra;
} CHARBUNDLE, *PCHARBUNDLE;

typedef struct _IMAGEBUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
} IMAGEBUNDLE, *PIMAGEBUNDLE;

typedef struct _LINEBUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
    FIXED  fxWidth;
    LONG   lGeomWidth;
    USHORT usType;
    USHORT usEnd;
    USHORT usJoin;
    USHORT usReserved;
} LINEBUNDLE, *PLINEBUNDLE;

typedef struct _MARKERBUNDLE {
    LONG   lColor;
    LONG   lBackColor;
    USHORT usMixMode;
    USHORT usBackMixMode;
    USHORT usSet;
    USHORT usSymbol;
    SIZEF  sizfxCell;
} MARKERBUNDLE, *PMARKERBUNDLE;

typedef struct _GRADIENTL {
    LONG x;
    LONG y;
} GRADIENTL, *PGRADIENTL;

LONG   APIENTRY GpiCharStringPos(HPS,PRECTL,ULONG,LONG,PCH,PLONG);
LONG   APIENTRY GpiCharStringPosAt(HPS,PPOINTL,PRECTL,ULONG,LONG,PCH,PLONG);
BOOL   APIENTRY GpiComment(HPS,LONG,PBYTE);
LONG   APIENTRY GpiFullArc(HPS,LONG,FIXED);
LONG   APIENTRY GpiImage(HPS,LONG,PSIZEL,LONG,PBYTE);
LONG   APIENTRY GpiMarker(HPS,PPOINTL);
LONG   APIENTRY GpiOval(HPS,PPOINTL,FIXED,FIXED,ULONG);
LONG   APIENTRY GpiPartialArc(HPS,PPOINTL,FIXED,FIXED,FIXED);
LONG   APIENTRY GpiPointArc(HPS,PPOINTL);
LONG   APIENTRY GpiPolyFillet(HPS,LONG,PPOINTL);
LONG   APIENTRY GpiPolyFilletSharp(HPS,LONG,PPOINTL,PFIXED);
LONG   APIENTRY GpiPolyMarker(HPS,LONG,PPOINTL);
LONG   APIENTRY GpiPolySpline(HPS,LONG,PPOINTL);
BOOL   APIENTRY GpiPop(HPS,LONG);
LONG   APIENTRY GpiPtVisible(HPS,PPOINTL);
LONG   APIENTRY GpiQueryAttrMode(HPS);
LONG   APIENTRY GpiQueryAttrs(HPS,LONG,ULONG,PBUNDLE);
LONG   APIENTRY GpiQueryBackColor(HPS);
LONG   APIENTRY GpiQueryBackMix(HPS);
BOOL   APIENTRY GpiQueryCharAngle(HPS,PGRADIENTL);
BOOL   APIENTRY GpiQueryCharBox(HPS,PSIZEF);
BOOL   APIENTRY GpiQueryCharBreakExtra(HPS,PFIXED);
LONG   APIENTRY GpiQueryCharDirection(HPS);
BOOL   APIENTRY GpiQueryCharExtra(HPS,PFIXED);
LONG   APIENTRY GpiQueryCharMode(HPS);
LONG   APIENTRY GpiQueryCharSet(HPS);
BOOL   APIENTRY GpiQueryCharShear(HPS,PPOINTL);
BOOL   APIENTRY GpiQueryCharStringPos(HPS,ULONG,LONG,PCH,PLONG,PPOINTL);
BOOL   APIENTRY GpiQueryCharStringPosAt(HPS,PPOINTL,ULONG,LONG,PCH,PLONG,PPOINTL);
LONG   APIENTRY GpiQueryClipBox(HPS,PRECTL);
HRGN   APIENTRY GpiQueryClipRegion(HPS);
BOOL   APIENTRY GpiQueryCurrentPosition(HPS,PPOINTL);
BOOL   APIENTRY GpiQueryDefCharBox(HPS,PSIZEL);
LONG   APIENTRY GpiQueryLineEnd(HPS);
LONG   APIENTRY GpiQueryLineJoin(HPS);
LONG   APIENTRY GpiQueryLineType(HPS);
FIXED  APIENTRY GpiQueryLineWidth(HPS);
LONG   APIENTRY GpiQueryLineWidthGeom(HPS);
LONG   APIENTRY GpiQueryMarker(HPS);
BOOL   APIENTRY GpiQueryMarkerBox(HPS,PSIZEF);
LONG   APIENTRY GpiQueryMarkerSet(HPS);
LONG   APIENTRY GpiQueryMix(HPS);
BOOL   APIENTRY GpiQueryPatternRefPoint(HPS,PPOINTL);
LONG   APIENTRY GpiQueryPatternSet(HPS);
LONG   APIENTRY GpiQueryTabbedTextExtent(HPS,LONG,PCH,LONG,PULONG);
BOOL   APIENTRY GpiQueryTextAlignment(HPS,PLONG,PLONG);
BOOL   APIENTRY GpiQueryTextBox(HPS,LONG,PCH,LONG,PPOINTL);
LONG   APIENTRY GpiRectVisible(HPS,PRECTL);
BOOL   APIENTRY GpiSetArcParams(HPS,PARCPARAMS);
BOOL   APIENTRY GpiSetAttrMode(HPS,LONG);
BOOL   APIENTRY GpiSetAttrs(HPS,LONG,ULONG,ULONG,PBUNDLE);
BOOL   APIENTRY GpiSetBackColor(HPS,LONG);
BOOL   APIENTRY GpiSetBackMix(HPS,LONG);
BOOL   APIENTRY GpiSetCharAngle(HPS,PGRADIENTL);
BOOL   APIENTRY GpiSetCharBox(HPS,PSIZEF);
BOOL   APIENTRY GpiSetCharBreakExtra(HPS,FIXED);
BOOL   APIENTRY GpiSetCharDirection(HPS,LONG);
BOOL   APIENTRY GpiSetCharExtra(HPS,FIXED);
BOOL   APIENTRY GpiSetCharMode(HPS,LONG);
BOOL   APIENTRY GpiSetCharSet(HPS,LONG);
BOOL   APIENTRY GpiSetCharShear(HPS,PPOINTL);
BOOL   APIENTRY GpiSetCurrentPosition(HPS,PPOINTL);
BOOL   APIENTRY GpiSetLineEnd(HPS,LONG);
BOOL   APIENTRY GpiSetLineJoin(HPS,LONG);
BOOL   APIENTRY GpiSetLineType(HPS,LONG);
BOOL   APIENTRY GpiSetLineWidth(HPS,FIXED);
BOOL   APIENTRY GpiSetLineWidthGeom(HPS,LONG);
BOOL   APIENTRY GpiSetMarker(HPS,LONG);
BOOL   APIENTRY GpiSetMarkerBox(HPS,PSIZEF);
BOOL   APIENTRY GpiSetMarkerSet(HPS,LONG);
BOOL   APIENTRY GpiSetMix(HPS,LONG);
BOOL   APIENTRY GpiSetPatternRefPoint(HPS,PPOINTL);
BOOL   APIENTRY GpiSetPatternSet(HPS,LONG);
BOOL   APIENTRY GpiSetTextAlignment(HPS,LONG,LONG);
LONG   APIENTRY GpiTabbedCharStringAt(HPS,PPOINTL,PRECTL,ULONG,LONG,PCH,LONG,PULONG,LONG);

#endif

#if defined(INCL_GPIDEFAULTS)

BOOL   APIENTRY GpiQueryDefArcParams(HPS,PARCPARAMS);
BOOL   APIENTRY GpiQueryDefAttrs(HPS,LONG,ULONG,PBUNDLE);
BOOL   APIENTRY GpiQueryDefTag(HPS,PLONG);
BOOL   APIENTRY GpiQueryDefViewingLimits(HPS,PRECTL);
BOOL   APIENTRY GpiSetDefArcParams(HPS,PARCPARAMS);
BOOL   APIENTRY GpiSetDefAttrs(HPS,LONG,ULONG,PBUNDLE);
BOOL   APIENTRY GpiSetDefTag(HPS,LONG);
BOOL   APIENTRY GpiSetDefViewingLimits(HPS,PRECTL);

#endif

#if defined(INCL_GPIREGIONS)

#define CRGN_OR   1
#define CRGN_COPY 2
#define CRGN_XOR  4
#define CRGN_AND  6
#define CRGN_DIFF 7

#define EQRGN_ERROR    0
#define EQRGN_NOTEQUAL 1
#define EQRGN_EQUAL    2

#define HRGN_ERROR ((HRGN)-1)

#define PRGN_ERROR   0
#define PRGN_OUTSIDE 1
#define PRGN_INSIDE  2

#define RECTDIR_LFRT_TOPBOT 1
#define RECTDIR_RTLF_TOPBOT 2
#define RECTDIR_LFRT_BOTTOP 3
#define RECTDIR_RTLF_BOTTOP 4

#define RGN_ERROR   0
#define RGN_NULL    1
#define RGN_RECT    2
#define RGN_COMPLEX 3

#define RRGN_ERROR   0
#define RRGN_OUTSIDE 1
#define RRGN_PARTIAL 2
#define RRGN_INSIDE  3

typedef struct _RGNRECT {
    ULONG ircStart;
    ULONG crc;
    ULONG crcReturned;
    ULONG ulDirection;
} RGNRECT, *PRGNRECT;

LONG   APIENTRY GpiCombineRegion(HPS hps, HRGN hrgnDest, HRGN hrgnSr1, HRGN hrgnSr2, LONG lMode);
HRGN   APIENTRY GpiCreateEllipticRegion(HPS hps, PRECTL prclRect);
HRGN   APIENTRY GpiCreateRegion(HPS hps, LONG lCount, PRECTL arclRectangles);
HRGN   APIENTRY GpiCreateRoundRectRegion(HPS hps, PPOINTL pptlPt, LONG lHround, LONG lVRound);
BOOL   APIENTRY GpiDestroyRegion(HPS hps, HRGN hrgn);
LONG   APIENTRY GpiEqualRegion(HPS hps, HRGN hrgnSrc1, HRGN hrgnSrc2);
LONG   APIENTRY GpiExcludeClipRectangle(HPS hps, PRECTL prclRectangle);
LONG   APIENTRY GpiIntersectClipRectangle(HPS hps, PRECTL prclRectangle);
LONG   APIENTRY GpiFrameRegion(HPS hps, HRGN hrgn, PSIZEL thickness);
LONG   APIENTRY GpiOffsetClipRegion(HPS hps, PPOINTL pptlPoint);
BOOL   APIENTRY GpiOffsetRegion(HPS hps, HRGN Hrgn, PPOINTL pptlOffset);
LONG   APIENTRY GpiPaintRegion(HPS hps, HRGN hrgn);
LONG   APIENTRY GpiPtInRegion(HPS hps, HRGN hrgn, PPOINTL pptlPoint);
LONG   APIENTRY GpiQueryClipBox(HPS hps, PRECTL prclBound);
HRGN   APIENTRY GpiQueryClipRegion(HPS hps);
LONG   APIENTRY GpiQueryRegionBox(HPS hps, HRGN hrgn, PRECTL prclBound);
BOOL   APIENTRY GpiQueryRegionRects(HPS hps, HRGN hrgn, PRECTL prclBound,
                   PRGNRECT prgnrcControl, PRECTL prclRect);
LONG   APIENTRY GpiRectInRegion(HPS hps, HRGN hrgn, PRECTL prclRect);
LONG   APIENTRY GpiSetClipRegion(HPS hps, HRGN hrgn, PHRGN phrgnOld);
BOOL   APIENTRY GpiSetRegion(HPS hps, HRGN hrgn, LONG lcount, PRECTL arclRectangles);

#endif

#if defined(INCL_GPITRANSFORMS)

#define CVTC_WORLD        1
#define CVTC_MODEL        2
#define CVTC_DEFAULTPAGE  3
#define CVTC_PAGE         4
#define CVTC_DEVICE       5

#define TRANSFORM_REPLACE 0
#define TRANSFORM_ADD     1
#define TRANSFORM_PREEMPT 2

LONG   APIENTRY GpiCallSegmentMatrix(HPS,LONG,LONG,PMATRIXLF,LONG);
BOOL   APIENTRY GpiConvert(HPS,LONG,LONG,LONG,PPOINTL);
BOOL   APIENTRY GpiConvertWithMatrix(HPS,LONG,PPOINTL,LONG,PMATRIXLF);
BOOL   APIENTRY GpiQueryDefaultViewMatrix(HPS,LONG,PMATRIXLF);
BOOL   APIENTRY GpiQueryGraphicsField(HPS,PRECTL);
BOOL   APIENTRY GpiQueryModelTransformMatrix(HPS,LONG,PMATRIXLF);
BOOL   APIENTRY GpiQueryPageViewport(HPS,PRECTL);
BOOL   APIENTRY GpiQuerySegmentTransformMatrix(HPS,LONG,LONG,PMATRIXLF);
BOOL   APIENTRY GpiQueryViewingTransformMatrix(HPS,LONG,PMATRIXLF);
BOOL   APIENTRY GpiQueryViewingLimits(HPS,PRECTL);
BOOL   APIENTRY GpiRotate(HPS,PMATRIXLF,LONG,FIXED,PPOINTL);
BOOL   APIENTRY GpiScale(HPS,PMATRIXLF,LONG,PFIXED,PPOINTL);
BOOL   APIENTRY GpiSetDefaultViewMatrix(HPS,LONG,PMATRIXLF,LONG);
BOOL   APIENTRY GpiSetGraphicsField(HPS,PRECTL);
BOOL   APIENTRY GpiSetModelTransformMatrix(HPS,LONG,PMATRIXLF,LONG);
BOOL   APIENTRY GpiSetPageViewport(HPS,PRECTL);
BOOL   APIENTRY GpiSetSegmentTransformMatrix(HPS,LONG,LONG,PMATRIXLF,LONG);
BOOL   APIENTRY GpiSetViewingTransformMatrix(HPS,LONG,PMATRIXLF,LONG);
BOOL   APIENTRY GpiSetViewingLimits(HPS,PRECTL);
BOOL   APIENTRY GpiTranslate(HPS,PMATRIXLF,LONG,PPOINTL);

#endif

#if defined(INCL_GPIMETAFILES)

#define PMF_SEGBASE         0
#define PMF_LOADTYPE        1
#define PMF_RESOLVE         2
#define PMF_LCIDS           3
#define PMF_RESET           4
#define PMF_SUPPRESS        5
#define PMF_COLORTABLES     6
#define PMF_COLORREALIZABLE 7
#define PMF_DEFAULTS        8
#define PMF_DELETEOBJECTS   9
#define PMF_PERPAGEINFOPTR  12

#define PPI_PLAYSEQ     0
#define PPI_PLAYDEFINED 1

#define RS_DEFAULT          0
#define RS_NODISCARD        1
#define LC_DEFAULT          0
#define LC_NOLOAD           1
#define LC_LOADDISC         3
#define LT_DEFAULT          0
#define LT_NOMODIFY         1
#define LT_ORIGINALVIEW     4
#define RES_DEFAULT         0
#define RES_NORESET         1
#define RES_RESET           2
#define SUP_DEFAULT         0
#define SUP_NOSUPPRESS      1
#define SUP_SUPPRESS        2
#define CTAB_DEFAULT        0
#define CTAB_NOMODIFY       1
#define CTAB_REPLACE        3
#define CTAB_REPLACEPALETTE 4
#define CREA_DEFAULT        0
#define CREA_REALIZE        1
#define CREA_NOREALIZE      2
#define CREA_DOREALIZE      3
#define DDEF_DEFAULT        0
#define DDEF_IGNORE         1
#define DDEF_LOADDISC       3
#define DOBJ_DEFAULT        0
#define DOBJ_NODELETE       1
#define DOBJ_DELETE         2
#define RSP_DEFAULT         0
#define RSP_NODISCARD       1

typedef struct  _PERPAGEINFO {
    ULONG  ulType;
    ULONG  ulStart;
    ULONG  ulEnd;
    ULONG  ulSkip;
    ULONG  ulPageCnt;
    PULONG pulDefined;
} PERPAGEINFO;

HMF    APIENTRY GpiCopyMetaFile(HMF);
BOOL   APIENTRY GpiDeleteMetaFile(HMF);
HMF    APIENTRY GpiLoadMetaFile(HAB,PCSZ);
LONG   APIENTRY GpiPlayMetaFile(HPS,HMF,LONG,PLONG,PLONG,LONG,PCSZ);
BOOL   APIENTRY GpiQueryMetaFileBits(HMF,LONG,LONG,PBYTE);
LONG   APIENTRY GpiQueryMetaFileLength(HMF);
BOOL   APIENTRY GpiResumePlay(HPS);
BOOL   APIENTRY GpiSaveMetaFile(HMF,PCSZ);
BOOL   APIENTRY GpiSetMetaFileBits(HMF,LONG,LONG,PBYTE);
BOOL   APIENTRY GpiSuspendPlay(HPS);

#endif

#if defined(INCL_GPICORRELATION)

#define PICKAP_DEFAULT 0
#define PICKAP_REC     2

#define PICKSEL_VISIBLE 0
#define PICKSEL_ALL     1

#define GPI_HITS 2

LONG   APIENTRY GpiCorrelateChain(HPS,LONG,PPOINTL,LONG,LONG,PLONG);
LONG   APIENTRY GpiCorrelateFrom(HPS,LONG,LONG,LONG,PPOINTL,LONG,LONG,PLONG);
LONG   APIENTRY GpiCorrelateSegment(HPS,LONG,LONG,PPOINTL,LONG,LONG,PLONG);
BOOL   APIENTRY GpiQueryBoundaryData(HPS,PRECTL);
BOOL   APIENTRY GpiQueryPickAperturePosition(HPS,PPOINTL);
BOOL   APIENTRY GpiQueryPickApertureSize(HPS,PSIZEL);
BOOL   APIENTRY GpiQueryTag(HPS,PLONG);
BOOL   APIENTRY GpiResetBoundaryData(HPS);
BOOL   APIENTRY GpiSetPickAperturePosition(HPS,PPOINTL);
BOOL   APIENTRY GpiSetPickApertureSize(HPS,LONG,PSIZEL);
BOOL   APIENTRY GpiSetTag(HPS,LONG);

#endif

#if defined(INCL_GPISEGMENTS)

#define DFORM_NOCONV    0
#define DFORM_S370SHORT 1
#define DFORM_PCSHORT   2
#define DFORM_PCLONG    4

#define ATTR_ERROR         (-1)
#define ATTR_DETECTABLE      1
#define ATTR_VISIBLE         2
#define ATTR_CHAINED         6
#define ATTR_DYNAMIC         8
#define ATTR_FASTCHAIN       9
#define ATTR_PROP_DETECTABLE 10
#define ATTR_PROP_VISIBLE    11

#define ATTR_OFF 0
#define ATTR_ON  1

#define LOWER_PRI  (-1)
#define HIGHER_PRI   1

BOOL   APIENTRY GpiCloseSegment(HPS);
BOOL   APIENTRY GpiDeleteSegment(HPS,LONG);
BOOL   APIENTRY GpiDeleteSegments(HPS,LONG,LONG);
BOOL   APIENTRY GpiDrawChain(HPS);
BOOL   APIENTRY GpiDrawDynamics(HPS);
BOOL   APIENTRY GpiDrawFrom(HPS,LONG,LONG);
BOOL   APIENTRY GpiDrawSegment(HPS,LONG);
LONG   APIENTRY GpiGetData(HPS,LONG,PLONG,LONG,LONG,PBYTE);
BOOL   APIENTRY GpiOpenSegment(HPS,LONG);
LONG   APIENTRY GpiPutData(HPS,LONG,PLONG,PBYTE);
LONG   APIENTRY GpiQueryInitialSegmentAttrs(HPS,LONG);
LONG   APIENTRY GpiQuerySegmentAttrs(HPS,LONG,LONG);
LONG   APIENTRY GpiQuerySegmentNames(HPS,LONG,LONG,LONG,PLONG);
LONG   APIENTRY GpiQuerySegmentPriority(HPS,LONG,LONG);
BOOL   APIENTRY GpiRemoveDynamics(HPS,LONG,LONG);
BOOL   APIENTRY GpiSetInitialSegmentAttrs(HPS,LONG,LONG);
BOOL   APIENTRY GpiSetSegmentAttrs(HPS,LONG,LONG,LONG);
BOOL   APIENTRY GpiSetSegmentPriority(HPS,LONG,LONG,LONG);

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
