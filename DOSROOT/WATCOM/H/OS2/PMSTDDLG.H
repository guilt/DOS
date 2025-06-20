/*
 *  pmstddlg.h  OS/2 Presentation Manager standard dialogs include file.
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

#define STDDLG_INCLUDED

#ifdef INCL_WINSTDDLGS
    #define INCL_WINCIRCULARSLIDER
    #define INCL_WINSTDCNR
    #define INCL_WINSTDDRAG
    #define INCL_WINSTDFILE
    #define INCL_WINSTDFONT
    #define INCL_WINSTDBOOK
    #define INCL_WINSTDSLIDER
    #define INCL_WINSTDSPIN
    #define INCL_WINSTDVALSET
#endif

#if defined(INCL_WINSTDSPIN) && !defined(WINSTDSPIN_INCLUDED)
#define WINSTDSPIN_INCLUDED

#define SPBS_ALLCHARACTERS 0x00000000
#define SPBS_NUMERICONLY   0x00000001
#define SPBS_READONLY      0x00000002
#define SPBS_MASTER        0x00000010
#define SPBS_SERVANT       0x00000000
#define SPBS_JUSTDEFAULT   0x00000000
#define SPBS_JUSTLEFT      0x00000008
#define SPBS_JUSTRIGHT     0x00000004
#define SPBS_JUSTCENTER    0x0000000C
#define SPBS_NOBORDER      0x00000020
#define SPBS_FASTSPIN      0x00000100
#define SPBS_PADWITHZEROS  0x00000080

#define SPBN_UPARROW   0x20A
#define SPBN_DOWNARROW 0x20B
#define SPBN_ENDSPIN   0x20C
#define SPBN_CHANGE    0x20D
#define SPBN_SETFOCUS  0x20E
#define SPBN_KILLFOCUS 0x20F

#define SPBM_OVERRIDESETLIMITS 0x200
#define SPBM_QUERYLIMITS       0x201
#define SPBM_SETTEXTLIMIT      0x202
#define SPBM_SPINUP            0x203
#define SPBM_SPINDOWN          0x204
#define SPBM_QUERYVALUE        0x205
#define SPBM_SETARRAY          0x206
#define SPBM_SETLIMITS         0x207
#define SPBM_SETCURRENTVALUE   0x208
#define SPBM_SETMASTER         0x209

#define SPBQ_UPDATEIFVALID 0
#define SPBQ_ALWAYSUPDATE  1
#define SPBQ_DONOTUPDATE   3

typedef struct _SPBCDATA {
    ULONG  cbSize;
    ULONG  ulTextLimit;
    LONG   lLowerLimit;
    LONG   lUpperLimit;
    ULONG  idMasterSpb;
    PVOID  pHWXCtlData;
} SPBCDATA, *PSPBCDATA;

#endif

#if defined(INCL_WINSTDBOOK) && !defined(WINSTDBOOK_INCLUDED)
#define WINSTDBOOK_INCLUDED

#define BKM_CALCPAGERECT         0x0353
#define BKM_DELETEPAGE           0x0354
#define BKM_INSERTPAGE           0x0355
#define BKM_INVALIDATETABS       0x0356
#define BKM_TURNTOPAGE           0x0357
#define BKM_QUERYPAGECOUNT       0x0358
#define BKM_QUERYPAGEID          0x0359
#define BKM_QUERYPAGEDATA        0x035a
#define BKM_QUERYPAGEWINDOWHWND  0x035b
#define BKM_QUERYTABBITMAP       0x035c
#define BKM_QUERYTABTEXT         0x035d
#define BKM_SETDIMENSIONS        0x035e
#define BKM_SETPAGEDATA          0x035f
#define BKM_SETPAGEWINDOWHWND    0x0360
#define BKM_SETSTATUSLINETEXT    0x0361
#define BKM_SETTABBITMAP         0x0362
#define BKM_SETTABTEXT           0x0363
#define BKM_SETNOTEBOOKCOLORS    0x0364
#define BKM_QUERYPAGESTYLE       0x0365
#define BKM_QUERYSTATUSLINETEXT  0x0366
#define BKM_SETPAGEINFO          0x0367
#define BKM_QUERYPAGEINFO        0x0368
#define BKM_SETTABCOLOR          0x0374
#define BKM_SETNOTEBOOKBUTTONS   0x0375

#define BKN_PAGESELECTED        130
#define BKN_NEWPAGESIZE         131
#define BKN_HELP                132
#define BKN_PAGEDELETED         133
#define BKN_PAGESELECTEDPENDING 134

#define BKA_ALL    1
#define BKA_SINGLE 2
#define BKA_TAB    4

#define BKA_LAST  0x0002
#define BKA_FIRST 0x0004
#define BKA_NEXT  0x0008
#define BKA_PREV  0x0010
#define BKA_TOP   0x0020

#define BKA_MAJORTAB   0x0001
#define BKA_MINORTAB   0x0002
#define BKA_PAGEBUTTON 0x0100

#define BKA_STATUSTEXTON 0x0001
#define BKA_MAJOR        0x0040
#define BKA_MINOR        0x0080
#define BKA_AUTOPAGESIZE 0x0100
#define BKA_END          0x0200

#define BKA_TEXT   0x0400
#define BKA_BITMAP 0x0800

#define BKA_AUTOCOLOR   (-1)
#define BKA_MAXBUTTONID 7999

#define BKS_BACKPAGESBR      0x00000001
#define BKS_BACKPAGESBL      0x00000002
#define BKS_BACKPAGESTR      0x00000004
#define BKS_BACKPAGESTL      0x00000008
#define BKS_MAJORTABRIGHT    0x00000010
#define BKS_MAJORTABLEFT     0x00000020
#define BKS_MAJORTABTOP      0x00000040
#define BKS_MAJORTABBOTTOM   0x00000080
#define BKS_SQUARETABS       0x00000000
#define BKS_ROUNDEDTABS      0x00000100
#define BKS_POLYGONTABS      0x00000200
#define BKS_SOLIDBIND        0x00000000
#define BKS_SPIRALBIND       0x00000400
#define BKS_STATUSTEXTLEFT   0x00000000
#define BKS_STATUSTEXTRIGHT  0x00001000
#define BKS_STATUSTEXTCENTER 0x00002000
#define BKS_TABTEXTLEFT      0x00000000
#define BKS_TABTEXTRIGHT     0x00004000
#define BKS_TABTEXTCENTER    0x00008000
#define BKS_TABBEDDIALOG     0x00000800
#define BKS_BUTTONAREA       0x00000200

#define BKA_BACKGROUNDPAGECOLORINDEX  0x0001
#define BKA_BACKGROUNDPAGECOLOR       0x0002
#define BKA_BACKGROUNDMAJORCOLORINDEX 0x0003
#define BKA_BACKGROUNDMAJORCOLOR      0x0004
#define BKA_BACKGROUNDMINORCOLORINDEX 0x0005
#define BKA_BACKGROUNDMINORCOLOR      0x0006
#define BKA_FOREGROUNDMAJORCOLORINDEX 0x0007
#define BKA_FOREGROUNDMAJORCOLOR      0x0008
#define BKA_FOREGROUNDMINORCOLORINDEX 0x0009
#define BKA_FOREGROUNDMINORCOLOR      0x000A

#define BFA_PAGEDATA            0x00000001
#define BFA_PAGEFROMHWND        0x00000002
#define BFA_PAGEFROMDLGTEMPLATE 0x00000004
#define BFA_PAGEFROMDLGRES      0x00000008
#define BFA_STATUSLINE          0x00000010
#define BFA_MAJORTABBITMAP      0x00000020
#define BFA_MINORTABBITMAP      0x00000040
#define BFA_MAJORTABTEXT        0x00000080
#define BFA_MINORTABTEXT        0x00000100
#define BFA_BIDIINFO            0x00000200

#define BOOKERR_INVALID_PARAMETERS  (-1)

typedef struct _BOOKPAGEINFO {
    ULONG        cb;
    ULONG        fl;
    BOOL         bLoadDlg;
    ULONG        ulPageData;
    HWND         hwndPage;
    PFN          pfnPageDlgProc;
    ULONG        idPageDlg;
    HMODULE      hmodPageDlg;
    PVOID        pPageDlgCreateParams;
    PDLGTEMPLATE pdlgtPage;
    ULONG        cbStatusLine;
    PSZ          pszStatusLine;
    HBITMAP      hbmMajorTab;
    HBITMAP      hbmMinorTab;
    ULONG        cbMajorTab;
    PSZ          pszMajorTab;
    ULONG        cbMinorTab;
    PSZ          pszMinorTab;
    PVOID        pBidiInfo;
} BOOKPAGEINFO, *PBOOKPAGEINFO;

typedef struct _BOOKTEXT {
    PSZ   pString;
    ULONG textLen;
} BOOKTEXT, *PBOOKTEXT;

typedef struct _NOTEBOOKBUTTON {
    PSZ     pszText;
    ULONG   idButton;
    LHANDLE hImage;
    LONG    flStyle;
} NOTEBOOKBUTTON, *PNOTEBOOKBUTTON;

typedef struct _DELETENOTIFY {
    HWND    hwndBook;
    HWND    hwndPage;
    ULONG   ulAppPageData;
    HBITMAP hbmTab;
} DELETENOTIFY, *PDELETENOTIFY;

typedef struct _PAGESELECTNOTIFY {
    HWND  hwndBook;
    ULONG ulPageIdCur;
    ULONG ulPageIdNew;
} PAGESELECTNOTIFY, *PPAGESELECTNOTIFY;

#endif

#if defined(INCL_WINSTDFILE) && !defined(WINSTDFILE_INCLUDED)
#define WINSTDFILE_INCLUDED

#define FDS_CENTER            0x00000001
#define FDS_CUSTOM            0x00000002
#define FDS_FILTERUNION       0x00000004
#define FDS_HELPBUTTON        0x00000008
#define FDS_APPLYBUTTON       0x00000010
#define FDS_PRELOAD_VOLINFO   0x00000020
#define FDS_MODELESS          0x00000040
#define FDS_INCLUDE_EAS       0x00000080
#define FDS_OPEN_DIALOG       0x00000100
#define FDS_SAVEAS_DIALOG     0x00000200
#define FDS_MULTIPLESEL       0x00000400
#define FDS_ENABLEFILELB      0x00000800
#define FDS_NATIONAL_LANGUAGE 0x80000000

#define FDS_SUCCESSFUL                 0
#define FDS_ERR_DEALLOCATE_MEMORY      1
#define FDS_ERR_FILTER_TRUNC           2
#define FDS_ERR_INVALID_DIALOG         3
#define FDS_ERR_INVALID_DRIVE          4
#define FDS_ERR_INVALID_FILTER         5
#define FDS_ERR_INVALID_PATHFILE       6
#define FDS_ERR_OUT_OF_MEMORY          7
#define FDS_ERR_PATH_TOO_LONG          8
#define FDS_ERR_TOO_MANY_FILE_TYPES    9
#define FDS_ERR_INVALID_VERSION       10
#define FDS_ERR_INVALID_CUSTOM_HANDLE 11
#define FDS_ERR_DIALOG_LOAD_ERROR     12
#define FDS_ERR_DRIVE_ERROR           13

#define FDS_EFSELECTION 0
#define FDS_LBSELECTION 1

#define DID_FILE_DIALOG        256
#define DID_FILENAME_TXT       257
#define DID_FILENAME_ED        258
#define DID_DRIVE_TXT          259
#define DID_DRIVE_CB           260
#define DID_FILTER_TXT         261
#define DID_FILTER_CB          262
#define DID_DIRECTORY_TXT      263
#define DID_DIRECTORY_LB       264
#define DID_FILES_TXT          265
#define DID_FILES_LB           266
#define DID_HELP_PB            267
#define DID_APPLY_PB           268
#define DID_READ_ONLY          269
#define DID_DIRECTORY_SELECTED 270
#define DID_OK_PB              DID_OK
#define DID_CANCEL_PB          DID_CANCEL

#define FDM_FILTER   (WM_USER+40)
#define FDM_VALIDATE (WM_USER+41)
#define FDM_ERROR    (WM_USER+42)

typedef PSZ APSZ[1];
typedef APSZ *PAPSZ;

typedef struct _FILEDLG {
    ULONG   cbSize;
    ULONG   fl;
    ULONG   ulUser;
    LONG    lReturn;
    LONG    lSRC;
    PSZ     pszTitle;
    PSZ     pszOKButton;
    PFNWP   pfnDlgProc;
    PSZ     pszIType;
    PAPSZ   papszITypeList;
    PSZ     pszIDrive;
    PAPSZ   papszIDriveList;
    HMODULE hMod;
    CHAR    szFullFile[CCHMAXPATH];
    PAPSZ   papszFQFilename;
    ULONG   ulFQFCount;
    USHORT  usDlgId;
    SHORT   x;
    SHORT   y;
    SHORT   sEAType;
} FILEDLG, *PFILEDLG;

MRESULT APIENTRY WinDefFileDlgProc(HWND,ULONG,MPARAM,MPARAM);
HWND    APIENTRY WinFileDlg(HWND,HWND,PFILEDLG);
BOOL    APIENTRY WinFreeFileDlgList(PAPSZ);

#endif

#if defined(INCL_WINSTDFONT) && !defined(WINSTDFONT_INCLUDED)
#define WINSTDFONT_INCLUDED

#define CLRC_FOREGROUND 1
#define CLRC_BACKGROUND 2

#define FNTF_NOVIEWSCREENFONTS   1
#define FNTF_NOVIEWPRINTERFONTS  2
#define FNTF_SCREENFONTSELECTED  4
#define FNTF_PRINTERFONTSELECTED 8

#define FNTS_CENTER             0x00000001
#define FNTS_CUSTOM             0x00000002
#define FNTS_OWNERDRAWPREVIEW   0x00000004
#define FNTS_HELPBUTTON         0x00000008
#define FNTS_APPLYBUTTON        0x00000010
#define FNTS_RESETBUTTON        0x00000020
#define FNTS_MODELESS           0x00000040
#define FNTS_INITFROMFATTRS     0x00000080
#define FNTS_BITMAPONLY         0x00000100
#define FNTS_VECTORONLY         0x00000200
#define FNTS_FIXEDWIDTHONLY     0x00000400
#define FNTS_PROPORTIONALONLY   0x00000800
#define FNTS_NOSYNTHESIZEDFONTS 0x00001000
#define FNTS_NATIONAL_LANGUAGE  0x80000000

#define FNTS_SUCCESSFUL             0
#define FNTS_ERR_INVALID_DIALOG     3
#define FNTS_ERR_ALLOC_SHARED_MEM   4
#define FNTS_ERR_INVALID_PARM       5
#define FNTS_ERR_OUT_OF_MEMORY      7
#define FNTS_ERR_INVALID_VERSION   10
#define FNTS_ERR_DIALOG_LOAD_ERROR 12

#define FNTI_BITMAPFONT       0x0001
#define FNTI_VECTORFONT       0x0002
#define FNTI_FIXEDWIDTHFONT   0x0004
#define FNTI_PROPORTIONALFONT 0x0008
#define FNTI_SYNTHESIZED      0x0010
#define FNTI_DEFAULTLIST      0x0020
#define FNTI_FAMILYNAME       0x0100
#define FNTI_STYLENAME        0x0200
#define FNTI_POINTSIZE        0x0400

#define DID_FONT_DIALOG       300
#define DID_NAME              301
#define DID_STYLE             302
#define DID_DISPLAY_FILTER    303
#define DID_PRINTER_FILTER    304
#define DID_SIZE              305
#define DID_SAMPLE            306
#define DID_OUTLINE           307
#define DID_UNDERSCORE        308
#define DID_STRIKEOUT         309
#define DID_HELP_BUTTON       310
#define DID_APPLY_BUTTON      311
#define DID_RESET_BUTTON      312
#define DID_OK_BUTTON         DID_OK
#define DID_CANCEL_BUTTON     DID_CANCEL
#define DID_NAME_PREFIX       313
#define DID_STYLE_PREFIX      314
#define DID_SIZE_PREFIX       315
#define DID_SAMPLE_GROUPBOX   316
#define DID_EMPHASIS_GROUPBOX 317
#define DID_FONT_ISO_SUPPORT  318
#define DID_FONT_ISO_UNTESTED 319

#define FNTM_FACENAMECHANGED  (WM_USER+50)
#define FNTM_POINTSIZECHANGED (WM_USER+51)
#define FNTM_STYLECHANGED     (WM_USER+52)
#define FNTM_COLORCHANGED     (WM_USER+53)
#define FNTM_UPDATEPREVIEW    (WM_USER+54)
#define FNTM_FILTERLIST       (WM_USER+55)

typedef struct _FONTDLG {
    ULONG   cbSize;
    HPS     hpsScreen;
    HPS     hpsPrinter;
    PSZ     pszTitle;
    PSZ     pszPreview;
    PSZ     pszPtSizeList;
    PFNWP   pfnDlgProc;
    PSZ     pszFamilyname;
    FIXED   fxPointSize;
    ULONG   fl;
    ULONG   flFlags;
    ULONG   flType;
    ULONG   flTypeMask;
    ULONG   flStyle;
    ULONG   flStyleMask;
    LONG    clrFore;
    LONG    clrBack;
    ULONG   ulUser;
    LONG    lReturn;
    LONG    lSRC;
    LONG    lEmHeight;
    LONG    lXHeight;
    LONG    lExternalLeading;
    HMODULE hMod;
    FATTRS  fAttrs;
    SHORT   sNominalPointSize;
    USHORT  usWeight;
    USHORT  usWidth;
    SHORT   x;
    SHORT   y;
    USHORT  usDlgId;
    USHORT  usFamilyBufLen;
    USHORT  usReserved;
} FONTDLG, *PFONTDLG;

typedef struct _STYLECHANGE {
    USHORT usWeight;
    USHORT usWeightOld;
    USHORT usWidth;
    USHORT usWidthOld;
    ULONG  flType;
    ULONG  flTypeOld;
    ULONG  flTypeMask;
    ULONG  flTypeMaskOld;
    ULONG  flStyle;
    ULONG  flStyleOld;
    ULONG  flStyleMask;
    ULONG  flStyleMaskOld;
} STYLECHANGE, *PSTYLECHANGE;

MRESULT APIENTRY WinDefFontDlgProc(HWND,ULONG,MPARAM,MPARAM);
HWND    APIENTRY WinFontDlg(HWND,HWND,PFONTDLG);

#endif

#if defined(INCL_WINSTDCNR) || defined(INCL_WINSTDVALSET)
  #define INCL_WINSTDDRAG
#endif

#if defined(INCL_WINSTDDRAG) && !defined(STDDRAG_INCLUDED)
#define STDDRAG_INCLUDED

#define PMERR_NOT_DRAGGING     0x1f00
#define PMERR_ALREADY_DRAGGING 0x1f01

#define MSGF_DRAG 0x0010

#define DM_DROP             0x032f
#define DM_DRAGOVER         0x032e
#define DM_DRAGLEAVE        0x032d
#define DM_DROPHELP         0x032c
#define DM_ENDCONVERSATION  0x032b
#define DM_PRINT            0x032a
#define DM_RENDER           0x0329
#define DM_RENDERCOMPLETE   0x0328
#define DM_RENDERPREPARE    0x0327
#define DM_DRAGFILECOMPLETE 0x0326
#define DM_EMPHASIZETARGET  0x0325
#define DM_DRAGERROR        0x0324
#define DM_FILERENDERED     0x0323
#define DM_RENDERFILE       0x0322
#define DM_DRAGOVERNOTIFY   0x0321
#define DM_PRINTOBJECT      0x0320
#define DM_DISCARDOBJECT    0x031f
#define DM_DROPNOTIFY       0x031e

#define DRT_ASM      "Assembler Code"
#define DRT_BASIC    "BASIC Code"
#define DRT_BINDATA  "Binary Data"
#define DRT_BITMAP   "Bitmap"
#define DRT_C        "C Code"
#define DRT_COBOL    "COBOL Code"
#define DRT_DLL      "Dynamic Link Library"
#define DRT_DOSCMD   "DOS Command File"
#define DRT_EXE      "Executable"
#define DRT_FORTRAN  "FORTRAN Code"
#define DRT_ICON     "Icon"
#define DRT_LIB      "Library"
#define DRT_METAFILE "Metafile"
#define DRT_OS2CMD   "OS/2 Command File"
#define DRT_PASCAL   "Pascal Code"
#define DRT_RESOURCE "Resource File"
#define DRT_TEXT     "Plain Text"
#define DRT_UNKNOWN  "Unknown"

#define DOR_NODROP    0x0000
#define DOR_DROP      0x0001
#define DOR_NODROPOP  0x0002
#define DOR_NEVERDROP 0x0003

#define DO_COPYABLE                0x0001
#define DO_MOVEABLE                0x0002
#define DO_LINKABLE                0x0004
#define DO_CREATEABLE              0x0008
#define DO_CREATEPROGRAMOBJECTABLE 0x0010

#define DC_OPEN            0x0001
#define DC_REF             0x0002
#define DC_GROUP           0x0004
#define DC_CONTAINER       0x0008
#define DC_PREPARE         0x0010
#define DC_REMOVEABLEMEDIA 0x0020

#define DO_DEFAULT             0xBFFE
#define DO_UNKNOWN             0xBFFF
#define DO_COPY                0x0010
#define DO_MOVE                0x0020
#define DO_LINK                0x0018
#define DO_CREATE              0x0040
#define DO_CREATEPROGRAMOBJECT 0x0080

#define DGS_DRAGINPROGRESS     0x0001
#define DGS_LAZYDRAGINPROGRESS 0x0002

#define DMFL_TARGETSUCCESSFUL 0x0001
#define DMFL_TARGETFAIL       0x0002
#define DMFL_NATIVERENDER     0x0004
#define DMFL_RENDERRETRY      0x0008
#define DMFL_RENDEROK         0x0010
#define DMFL_RENDERFAIL       0x0020

#define DRG_ICON        0x00000001
#define DRG_BITMAP      0x00000002
#define DRG_POLYGON     0x00000004
#define DRG_STRETCH     0x00000008
#define DRG_TRANSPARENT 0x00000010
#define DRG_CLOSED      0x00000020
#define DRG_MINIBITMAP  0x00000040

#define DME_IGNOREABORT    1
#define DME_IGNORECONTINUE 2
#define DME_REPLACE        3
#define DME_RETRY          4

#define DF_MOVE       0x0001
#define DF_SOURCE     0x0002
#define DF_SUCCESSFUL 0x0004

#define DRR_SOURCE 1
#define DRR_TARGET 2
#define DRR_ABORT  3

#define DFF_MOVE   1
#define DFF_COPY   2
#define DFF_DELETE 3

#define WM_DRAGFIRST 0x0310
#define WM_DRAGLAST  0x032f

typedef LHANDLE HSTR;

typedef struct _DRAGITEM {
    HWND   hwndItem;
    ULONG  ulItemID;
    HSTR   hstrType;
    HSTR   hstrRMF;
    HSTR   hstrContainerName;
    HSTR   hstrSourceName;
    HSTR   hstrTargetName;
    SHORT  cxOffset;
    SHORT  cyOffset;
    USHORT fsControl;
    USHORT fsSupportedOps;
} DRAGITEM, *PDRAGITEM;

typedef struct _DRAGINFO {
    ULONG  cbDraginfo;
    USHORT cbDragitem;
    USHORT usOperation;
    HWND   hwndSource;
    SHORT  xDrop;
    SHORT  yDrop;
    USHORT cditem;
    USHORT usReserved;
} DRAGINFO, *PDRAGINFO;

typedef struct _DRAGIMAGE {
    USHORT  cb;
    USHORT  cptl;
    LHANDLE hImage;
    SIZEL   sizlStretch;
    ULONG   fl;
    SHORT   cxOffset;
    SHORT   cyOffset;
} DRAGIMAGE, *PDRAGIMAGE;

typedef struct _DRAGTRANSFER {
    ULONG     cb;
    HWND      hwndClient;
    PDRAGITEM pditem;
    HSTR      hstrSelectedRMF;
    HSTR      hstrRenderToName;
    ULONG     ulTargetInfo;
    USHORT    usOperation;
    USHORT    fsReply;
} DRAGTRANSFER, *PDRAGTRANSFER;

typedef struct _RENDERFILE {
    HWND   hwndDragFiles;
    HSTR   hstrSource;
    HSTR   hstrTarget;
    USHORT fMove;
    USHORT usRsvd;
} RENDERFILE, *PRENDERFILE;

BOOL      APIENTRY DrgAcceptDroppedFiles(HWND,PCSZ,PCSZ,ULONG,ULONG);
BOOL      APIENTRY DrgAccessDraginfo(PDRAGINFO);
PDRAGINFO APIENTRY DrgAllocDraginfo(ULONG);
PDRAGTRANSFER APIENTRY DrgAllocDragtransfer(ULONG);
HSTR      APIENTRY DrgAddStrHandle(PCSZ);
BOOL      APIENTRY DrgCancelLazyDrag(VOID);
BOOL      APIENTRY DrgDeleteDraginfoStrHandles(PDRAGINFO);
BOOL      APIENTRY DrgDeleteStrHandle(HSTR);
HWND      APIENTRY DrgDrag(HWND,PDRAGINFO,PDRAGIMAGE,ULONG,LONG,PVOID);
BOOL      APIENTRY DrgDragFiles(HWND,PCSZ*,PCSZ*,PCSZ*,ULONG,HPOINTER,ULONG,BOOL,ULONG);
BOOL      APIENTRY DrgFreeDraginfo(PDRAGINFO);
BOOL      APIENTRY DrgFreeDragtransfer(PDRAGTRANSFER);
HPS       APIENTRY DrgGetPS(HWND);
BOOL      APIENTRY DrgLazyDrag(HWND, PDRAGINFO, PDRAGIMAGE, ULONG, PVOID);
BOOL      APIENTRY DrgLazyDrop(HWND, ULONG, PPOINTL);
BOOL      APIENTRY DrgPostTransferMsg(HWND,ULONG,PDRAGTRANSFER,ULONG,ULONG,BOOL);
BOOL      APIENTRY DrgPushDraginfo(PDRAGINFO, HWND);
PDRAGINFO APIENTRY DrgQueryDraginfoPtr(PDRAGINFO);
PDRAGINFO APIENTRY DrgQueryDraginfoPtrFromHwnd(HWND);
PDRAGINFO APIENTRY DrgQueryDraginfoPtrFromDragitem(PDRAGITEM);
BOOL      APIENTRY DrgQueryDragitem(PDRAGINFO,ULONG,PDRAGITEM,ULONG);
ULONG     APIENTRY DrgQueryDragitemCount(PDRAGINFO);
PDRAGITEM APIENTRY DrgQueryDragitemPtr(PDRAGINFO,ULONG);
ULONG     APIENTRY DrgQueryDragStatus(VOID);
ULONG     APIENTRY DrgQueryFormat(PDRAGITEM, PCSZ, ULONG, PCSZ, ULONG);
BOOL      APIENTRY DrgQueryNativeRMF(PDRAGITEM,ULONG,PCHAR);
ULONG     APIENTRY DrgQueryNativeRMFLen(PDRAGITEM);
ULONG     APIENTRY DrgQueryStrName(HSTR,ULONG,PCSZ);
ULONG     APIENTRY DrgQueryStrNameLen(HSTR);
BOOL      APIENTRY DrgQueryTrueType(PDRAGITEM,ULONG,PCSZ);
ULONG     APIENTRY DrgQueryTrueTypeLen(PDRAGITEM);
PDRAGINFO APIENTRY DrgReallocDraginfo (PDRAGINFO, ULONG);
BOOL      APIENTRY DrgReleasePS(HPS);
MRESULT   APIENTRY DrgSendTransferMsg(HWND,ULONG,MPARAM,MPARAM);
BOOL      APIENTRY DrgSetDragitem(PDRAGINFO,PDRAGITEM,ULONG,ULONG);
BOOL      APIENTRY DrgSetDragImage(PDRAGINFO,PDRAGIMAGE,ULONG,PVOID);
BOOL      APIENTRY DrgSetDragPointer(PDRAGINFO, HPOINTER);
BOOL      APIENTRY DrgVerifyTypeSet(PDRAGITEM,PCSZ,ULONG,PCSZ);
BOOL      APIENTRY DrgVerifyNativeRMF(PDRAGITEM, PCSZ);
BOOL      APIENTRY DrgVerifyRMF(PDRAGITEM, PCSZ, PCSZ);
BOOL      APIENTRY DrgVerifyTrueType(PDRAGITEM, PCSZ);
BOOL      APIENTRY DrgVerifyType(PDRAGITEM, PCSZ);

#endif

#if defined (INCL_WINSTDCNR) && !defined (INCL_WINSTDCNR_INCLUDED)
#define INCL_WINSTDCNR_INCLUDED

#define CFA_IGNORE       0x80000000
#define CRA_IGNORE       0x00008000
#define CRA_SOURCE       0x00004000
#define CRA_DISABLED     0x00001000
#define CRA_OWNERFREE    0x00010000
#define CRA_OWNERDRAW    0x00020000
#define CV_EXACTLENGTH   0x10000000
#define CCS_MINIICONS    0x00000800
#define CCS_NOCONTROLPTR 0x00001000
#define CMA_FILTER       0x1000

#define CCS_EXTENDSEL      0x00000001
#define CCS_MULTIPLESEL    0x00000002
#define CCS_SINGLESEL      0x00000004
#define CCS_AUTOPOSITION   0x00000008
#define CCS_VERIFYPOINTERS 0x00000010
#define CCS_READONLY       0x00000020
#define CCS_MINIRECORDCORE 0x00000040
#define CCS_MINIICONS      0x00000800
#define CCS_NOCONTROLPTR   0x00001000

#define CV_TEXT        0x00000001
#define CV_NAME        0x00000002
#define CV_ICON        0x00000004
#define CV_DETAIL      0x00000008
#define CV_FLOW        0x00000010
#define CV_MINI        0x00000020
#define CV_TREE        0x00000040
#define CV_GRID        0x00000080
#define CV_EXACTLENGTH 0x10000000

#define CA_CONTAINERTITLE       0x00000200
#define CA_TITLESEPARATOR       0x00000400
#define CA_TITLELEFT            0x00000800
#define CA_TITLERIGHT           0x00001000
#define CA_TITLECENTER          0x00002000
#define CA_OWNERDRAW            0x00004000
#define CA_DETAILSVIEWTITLES    0x00008000
#define CA_ORDEREDTARGETEMPH    0x00010000
#define CA_DRAWBITMAP           0x00020000
#define CA_DRAWICON             0x00040000
#define CA_TITLEREADONLY        0x00080000
#define CA_OWNERPAINTBACKGROUND 0x00100000
#define CA_MIXEDTARGETEMPH      0x00200000
#define CA_TREELINE             0x00400000

#define CID_LEFTCOLTITLEWND  0x7FF0
#define CID_RIGHTCOLTITLEWND 0x7FF1
#define CID_BLANKBOX         0x7FF2
#define CID_HSCROLL          0x7FF3
#define CID_RIGHTHSCROLL     0x7FF4
#define CID_CNRTITLEWND      0x7FF5
#define CID_LEFTDVWND        0x7FF7
#define CID_RIGHTDVWND       0x7FF8
#define CID_VSCROLL          0x7FF9
#define CID_MLE              0x7FFA

#define CFA_LEFT            0x00000001
#define CFA_RIGHT           0x00000002
#define CFA_CENTER          0x00000004
#define CFA_TOP             0x00000008
#define CFA_VCENTER         0x00000010
#define CFA_BOTTOM          0x00000020
#define CFA_INVISIBLE       0x00000040
#define CFA_BITMAPORICON    0x00000100
#define CFA_SEPARATOR       0x00000200
#define CFA_HORZSEPARATOR   0x00000400
#define CFA_STRING          0x00000800
#define CFA_OWNER           0x00001000
#define CFA_DATE            0x00002000
#define CFA_TIME            0x00004000
#define CFA_FIREADONLY      0x00008000
#define CFA_FITITLEREADONLY 0x00010000
#define CFA_ULONG           0x00020000
#define CFA_RANGE           0x00040000
#define CFA_NEWCOMP         0x00080000
#define CFA_OBJECT          0x00100000
#define CFA_LIST            0x00200000
#define CFA_CLASS           0x00400000
#define CFA_IGNORE          0x80000000

#define CRA_SELECTED        0x00000001
#define CRA_TARGET          0x00000002
#define CRA_CURSORED        0x00000004
#define CRA_INUSE           0x00000008
#define CRA_FILTERED        0x00000010
#define CRA_DROPONABLE      0x00000020
#define CRA_RECORDREADONLY  0x00000040
#define CRA_EXPANDED        0x00000080
#define CRA_COLLAPSED       0x00000100
#define CRA_PICKED          0x00000200
#define CRA_LOCKED          0x00000400
#define CRA_DISABLED        0x00001000
#define CRA_SOURCE          0x00004000
#define CRA_IGNORE          0x00008000
#define CRA_OWNERFREE       0x00010000
#define CRA_OWNERDRAW       0x00020000

#define CMA_TOP              0x0001
#define CMA_BOTTOM           0x0002
#define CMA_LEFT             0x0004
#define CMA_RIGHT            0x0008
#define CMA_PERIMETER        0x0010
#define CMA_USER             0x0020
#define CMA_FIRST            0x0010
#define CMA_LAST             0x0020
#define CMA_END              0x0040
#define CMA_PREV             0x0080
#define CMA_NEXT             0x0100
#define CMA_HORIZONTAL       0x0200
#define CMA_VERTICAL         0x0400
#define CMA_ICON             0x0800
#define CMA_TEXT             0x1000
#define CMA_PARTIAL          0x2000
#define CMA_COMPLETE         0x4000
#define CMA_PARENT           0x0001
#define CMA_FIRSTCHILD       0x0002
#define CMA_LASTCHILD        0x0004
#define CMA_CNRTITLE         0x0001
#define CMA_DELTA            0x0002
#define CMA_FLWINDOWATTR     0x0004
#define CMA_LINESPACING      0x0008
#define CMA_PFIELDINFOLAST   0x0010
#define CMA_PSORTRECORD      0x0020
#define CMA_PTLORIGIN        0x0040
#define CMA_SLBITMAPORICON   0x0080
#define CMA_XVERTSPLITBAR    0x0100
#define CMA_PFIELDINFOOBJECT 0x0200
#define CMA_ITEMORDER        0x0001
#define CMA_WINDOW           0x0002
#define CMA_WORKSPACE        0x0004
#define CMA_ZORDER           0x0008
#define CMA_DELTATOP         0x0001
#define CMA_DELTABOT         0x0002
#define CMA_DELTAHOME        0x0004
#define CMA_DELTAEND         0x0008
#define CMA_NOREPOSITION     0x0001
#define CMA_REPOSITION       0x0002
#define CMA_TEXTCHANGED      0x0004
#define CMA_ERASE            0x0008
#define CMA_NOTEXTCHANGED    0x0010
#define CMA_FILTER           0x1000
#define CMA_FREE             0x0001
#define CMA_INVALIDATE       0x0002
#define CMA_ARRANGESTANDARD  0x0000
#define CMA_ARRANGEGRID      0x0001
#define CMA_ARRANGESELECTED  0x0002
#define CMA_AVAIL            0x0001
#define CMA_UNAVAIL          0x0002

#define CMA_TREEICON           0x0400
#define CMA_TREEBITMAP         0x0800
#define CMA_CXTREEINDENT       0x1000
#define CMA_CXTREELINE         0x2000
#define CMA_SLTREEBITMAPORICON 0x4000

#define CM_ALLOCDETAILFIELDINFO      0x0330
#define CM_ALLOCRECORD               0x0331
#define CM_ARRANGE                   0x0332
#define CM_ERASERECORD               0x0333
#define CM_FILTER                    0x0334
#define CM_FREEDETAILFIELDINFO       0x0335
#define CM_FREERECORD                0x0336
#define CM_HORZSCROLLSPLITWINDOW     0x0337
#define CM_INSERTDETAILFIELDINFO     0x0338
#define CM_INSERTRECORD              0x0339
#define CM_INVALIDATEDETAILFIELDINFO 0x033a
#define CM_INVALIDATERECORD          0x033b
#define CM_PAINTBACKGROUND           0x033c
#define CM_QUERYCNRINFO              0x033d
#define CM_QUERYDETAILFIELDINFO      0x033e
#define CM_QUERYDRAGIMAGE            0x033f
#define CM_QUERYRECORD               0x0340
#define CM_QUERYRECORDEMPHASIS       0x0341
#define CM_QUERYRECORDFROMRECT       0x0342
#define CM_QUERYRECORDRECT           0x0343
#define CM_QUERYVIEWPORTRECT         0x0344
#define CM_REMOVEDETAILFIELDINFO     0x0345
#define CM_REMOVERECORD              0x0346
#define CM_SCROLLWINDOW              0x0347
#define CM_SEARCHSTRING              0x0348
#define CM_SETCNRINFO                0x0349
#define CM_SETRECORDEMPHASIS         0x034a
#define CM_SORTRECORD                0x034b
#define CM_OPENEDIT                  0x034c
#define CM_CLOSEEDIT                 0x034d
#define CM_COLLAPSETREE              0x034e
#define CM_EXPANDTREE                0x034f
#define CM_QUERYRECORDINFO           0x0350
#define CM_INSERTRECORDARRAY         0x0351
#define CM_MOVETREE                  0x0352
#define CM_SETTEXTVISIBILITY         0x0353
#define CM_SETGRIDINFO               0x0354
#define CM_QUERYGRIDINFO             0x0355
#define CM_SNAPTOGRID                0x0356

#define CN_DRAGAFTER    101
#define CN_DRAGLEAVE    102
#define CN_DRAGOVER     103
#define CN_DROP         104
#define CN_DROPHELP     105
#define CN_ENTER        106
#define CN_INITDRAG     107
#define CN_EMPHASIS     108
#define CN_KILLFOCUS    109
#define CN_SCROLL       110
#define CN_QUERYDELTA   111
#define CN_SETFOCUS     112
#define CN_REALLOCPSZ   113
#define CN_BEGINEDIT    114
#define CN_ENDEDIT      115
#define CN_COLLAPSETREE 116
#define CN_EXPANDTREE   117
#define CN_HELP         118
#define CN_CONTEXTMENU  119
#define CN_VERIFYEDIT   134
#define CN_PICKUP       135
#define CN_DROPNOTIFY   136
#define CN_GRIDRESIZED  137

#define PMERR_NOFILTERED_ITEMS          0x1f02
#define PMERR_COMPARISON_FAILED         0x1f03
#define PMERR_RECORD_CURRENTLY_INSERTED 0x1f04
#define PMERR_FI_CURRENTLY_INSERTED     0x1f05

typedef struct _TREEITEMDESC {
    HBITMAP  hbmExpanded;
    HBITMAP  hbmCollapsed;
    HPOINTER hptrExpanded;
    HPOINTER hptrCollapsed;
} TREEITEMDESC, *PTREEITEMDESC;

typedef struct _FIELDINFO {
    ULONG  cb;
    ULONG  flData;
    ULONG  flTitle;
    PVOID  pTitleData;
    ULONG  offStruct;
    PVOID  pUserData;
    struct _FIELDINFO *pNextFieldInfo;
    ULONG  cxWidth;
} FIELDINFO, *PFIELDINFO;

typedef struct _RECORDCORE {
    ULONG    cb;
    ULONG    flRecordAttr;
    POINTL   ptlIcon;
    struct _RECORDCORE *preccNextRecord;
    PSZ      pszIcon;
    HPOINTER hptrIcon;
    HPOINTER hptrMiniIcon;
    HBITMAP  hbmBitmap;
    HBITMAP  hbmMiniBitmap;
    PTREEITEMDESC pTreeItemDesc;
    PSZ      pszText;
    PSZ      pszName;
    PSZ      pszTree;
} RECORDCORE,  *PRECORDCORE;

typedef struct _MINIRECORDCORE {
    ULONG    cb;
    ULONG    flRecordAttr;
    POINTL   ptlIcon;
    struct _MINIRECORDCORE *preccNextRecord;
    PSZ      pszIcon;
    HPOINTER hptrIcon;
} MINIRECORDCORE;
typedef MINIRECORDCORE *PMINIRECORDCORE;

typedef struct _TREEMOVE {
    PRECORDCORE preccMove;
    PRECORDCORE preccNewParent;
    PRECORDCORE pRecordOrder;
    BOOL        flMoveSiblings;
} TREEMOVE, *PTREEMOVE;

typedef struct _CNRINFO {
    ULONG      cb;
    PVOID      pSortRecord;
    PFIELDINFO pFieldInfoLast;
    PFIELDINFO pFieldInfoObject;
    PSZ        pszCnrTitle;
    ULONG      flWindowAttr;
    POINTL     ptlOrigin;
    ULONG      cDelta;
    ULONG      cRecords;
    SIZEL      slBitmapOrIcon;
    SIZEL      slTreeBitmapOrIcon;
    HBITMAP    hbmExpanded;
    HBITMAP    hbmCollapsed;
    HPOINTER   hptrExpanded;
    HPOINTER   hptrCollapsed;
    LONG       cyLineSpacing;
    LONG       cxTreeIndent;
    LONG       cxTreeLine;
    ULONG      cFields;
    LONG       xVertSplitbar;
} CNRINFO, *PCNRINFO;

typedef struct _GRIDSQUARE {
    ULONG ulNumber;
    ULONG ulState;
    RECTL rctlSquare;
} GRIDSQUARE, *PGRIDSQUARE;

typedef struct _GRIDINFO {
    ULONG cb;
    SHORT cxGrid;
    SHORT cyGrid;
    SHORT sGridRows;
    SHORT sGridCols;
    LONG  cGridSquares;
    PGRIDSQUARE pGrid;
} GRIDINFO, *PGRIDINFO;

typedef struct _CDATE {
    UCHAR  day;
    UCHAR  month;
    USHORT year;
} CDATE, *PCDATE;

typedef struct _CTIME {
    UCHAR hours;
    UCHAR minutes;
    UCHAR seconds;
    UCHAR ucReserved;
} CTIME, *PCTIME;

typedef struct _CNRDRAGINIT {
    HWND        hwndCnr;
    PRECORDCORE pRecord;
    LONG        x;
    LONG        y;
    LONG        cx;
    LONG        cy;
} CNRDRAGINIT, *PCNRDRAGINIT;

typedef struct _FIELDINFOINSERT {
    ULONG      cb;
    PFIELDINFO pFieldInfoOrder;
    ULONG      fInvalidateFieldInfo;
    ULONG      cFieldInfoInsert;
} FIELDINFOINSERT, *PFIELDINFOINSERT;

typedef struct _RECORDINSERT {
    ULONG       cb;
    PRECORDCORE pRecordOrder;
    PRECORDCORE pRecordParent;
    ULONG       fInvalidateRecord;
    ULONG       zOrder;
    ULONG       cRecordsInsert;
} RECORDINSERT, *PRECORDINSERT;

typedef struct _QUERYRECFROMRECT {
    ULONG cb;
    RECTL rect;
    ULONG fsSearch;
} QUERYRECFROMRECT, *PQUERYRECFROMRECT;

typedef struct _QUERYRECORDRECT {
    ULONG       cb;
    PRECORDCORE pRecord;
    ULONG       fRightSplitWindow;
    ULONG       fsExtent;
} QUERYRECORDRECT, *PQUERYRECORDRECT;

typedef struct _SEARCHSTRING {
    ULONG cb;
    PSZ   pszSearch;
    ULONG fsPrefix;
    ULONG fsCaseSensitive;
    ULONG usView;
} SEARCHSTRING, *PSEARCHSTRING;

typedef struct _CNRDRAGINFO {
    PDRAGINFO   pDragInfo;
    PRECORDCORE pRecord;
} CNRDRAGINFO, *PCNRDRAGINFO;

typedef struct _CNRLAZYDRAGINFO {
    PDRAGINFO   pDragInfo;
    PRECORDCORE pRecord;
    HWND        hwndTarget;
} CNRLAZYDRAGINFO, *PCNRLAZYDRAGINFO;

typedef struct _NOTIFYRECORDEMPHASIS {
    HWND        hwndCnr;
    PRECORDCORE pRecord;
    ULONG       fEmphasisMask;
} NOTIFYRECORDEMPHASIS, *PNOTIFYRECORDEMPHASIS;

typedef struct _NOTIFYRECORDENTER {
    HWND        hwndCnr;
    ULONG       fKey;
    PRECORDCORE pRecord;
} NOTIFYRECORDENTER, *PNOTIFYRECORDENTER;

typedef struct _NOTIFYDELTA {
    HWND  hwndCnr;
    ULONG fDelta;
} NOTIFYDELTA, *PNOTIFYDELTA;

typedef struct _NOTIFYSCROLL {
    HWND  hwndCnr;
    LONG  lScrollInc;
    ULONG fScroll;
} NOTIFYSCROLL, *PNOTIFYSCROLL;

typedef struct _CNREDITDATA {
    ULONG       cb;
    HWND        hwndCnr;
    PRECORDCORE pRecord;
    PFIELDINFO  pFieldInfo;
    PSZ         *ppszText;
    ULONG       cbText;
    ULONG       id;
} CNREDITDATA, *PCNREDITDATA;

typedef struct _OWNERBACKGROUND {
    HWND  hwnd;
    HPS   hps;
    RECTL rclBackground;
    LONG  idWindow;
} OWNERBACKGROUND, *POWNERBACKGROUND;

typedef struct _CNRDRAWITEMINFO {
    PRECORDCORE pRecord;
    PFIELDINFO  pFieldInfo;
} CNRDRAWITEMINFO, *PCNRDRAWITEMINFO;

#endif

#if defined(INCL_WINSTDVALSET) && !defined(INCL_WINSTDVALSET_INCLUDED)
#define INCL_WINSTDVALSET_INCLUDED

#define VS_BITMAP       0x0001
#define VS_ICON         0x0002
#define VS_TEXT         0x0004
#define VS_RGB          0x0008
#define VS_COLORINDEX   0x0010
#define VS_BORDER       0x0020
#define VS_ITEMBORDER   0x0040
#define VS_SCALEBITMAPS 0x0080
#define VS_RIGHTTOLEFT  0x0100
#define VS_OWNERDRAW    0x0200

#define VIA_BITMAP     0x0001
#define VIA_ICON       0x0002
#define VIA_TEXT       0x0004
#define VIA_RGB        0x0008
#define VIA_COLORINDEX 0x0010
#define VIA_OWNERDRAW  0x0020
#define VIA_DISABLED   0x0040
#define VIA_DRAGGABLE  0x0080
#define VIA_DROPONABLE 0x0100

#define VMA_ITEMSIZE    0x0001
#define VMA_ITEMSPACING 0x0002

#define VDA_ITEM           0x0001
#define VDA_ITEMBACKGROUND 0x0002
#define VDA_SURROUNDING    0x0003
#define VDA_BACKGROUND     0x0004

#define VSERR_INVALID_PARAMETERS (-1)

#define VM_QUERYITEM         0x0375
#define VM_QUERYITEMATTR     0x0376
#define VM_QUERYMETRICS      0x0377
#define VM_QUERYSELECTEDITEM 0x0378
#define VM_SELECTITEM        0x0379
#define VM_SETITEM           0x037a
#define VM_SETITEMATTR       0x037b
#define VM_SETMETRICS        0x037c

#define VN_SELECT     120
#define VN_ENTER      121
#define VN_DRAGLEAVE  122
#define VN_DRAGOVER   123
#define VN_DROP       124
#define VN_DROPHELP   125
#define VN_INITDRAG   126
#define VN_SETFOCUS   127
#define VN_KILLFOCUS  128
#define VN_HELP       129

typedef struct _VSCDATA {
    ULONG  cbSize;
    USHORT usRowCount;
    USHORT usColumnCount;
} VSCDATA, *PVSCDATA;

typedef struct _VSDRAGINIT {
    HWND   hwnd;
    LONG   x;
    LONG   y;
    LONG   cx;
    LONG   cy;
    USHORT usRow;
    USHORT usColumn;
} VSDRAGINIT, *PVSDRAGINIT;

typedef struct _VSDRAGINFO {
    PDRAGINFO pDragInfo;
    USHORT    usRow;
    USHORT    usColumn;
} VSDRAGINFO, *PVSDRAGINFO;

typedef struct _VSTEXT {
    PSZ   pszItemText;
    ULONG ulBufLen;
} VSTEXT, *PVSTEXT;

#endif

#if defined(INCL_WINSTDSLIDER) && !defined(INCL_WINSTDSLIDER_INCLUDED)
#define INCL_WINSTDSLIDER_INCLUDED

#define SLS_HORIZONTAL      0x00000000
#define SLS_VERTICAL        0x00000001
#define SLS_CENTER          0x00000000
#define SLS_BOTTOM          0x00000002
#define SLS_TOP             0x00000004
#define SLS_LEFT            0x00000002
#define SLS_RIGHT           0x00000004
#define SLS_SNAPTOINCREMENT 0x00000008
#define SLS_BUTTONSBOTTOM   0x00000010
#define SLS_BUTTONSTOP      0x00000020
#define SLS_BUTTONSLEFT     0x00000010
#define SLS_BUTTONSRIGHT    0x00000020
#define SLS_OWNERDRAW       0x00000040
#define SLS_READONLY        0x00000080
#define SLS_RIBBONSTRIP     0x00000100
#define SLS_HOMEBOTTOM      0x00000000
#define SLS_HOMETOP         0x00000200
#define SLS_HOMELEFT        0x00000000
#define SLS_HOMERIGHT       0x00000200
#define SLS_PRIMARYSCALE1   0x00000000
#define SLS_PRIMARYSCALE2   0x00000400

#define SMA_SCALE1              0x0001
#define SMA_SCALE2              0x0002
#define SMA_SHAFTDIMENSIONS     0x0000
#define SMA_SHAFTPOSITION       0x0001
#define SMA_SLIDERARMDIMENSIONS 0x0002
#define SMA_SLIDERARMPOSITION   0x0003
#define SMA_RANGEVALUE          0x0000
#define SMA_INCREMENTVALUE      0x0001
#define SMA_SETALLTICKS         0xFFFF

#define SDA_RIBBONSTRIP 0x0001
#define SDA_SLIDERSHAFT 0x0002
#define SDA_BACKGROUND  0x0003
#define SDA_SLIDERARM   0x0004

#define PMERR_UPDATE_IN_PROGRESS  0x1f06
#define SLDERR_INVALID_PARAMETERS (-1)

#define SLM_ADDDETENT       0x0369
#define SLM_QUERYDETENTPOS  0x036a
#define SLM_QUERYSCALETEXT  0x036b
#define SLM_QUERYSLIDERINFO 0x036c
#define SLM_QUERYTICKPOS    0x036d
#define SLM_QUERYTICKSIZE   0x036e
#define SLM_REMOVEDETENT    0x036f
#define SLM_SETSCALETEXT    0x0370
#define SLM_SETSLIDERINFO   0x0371
#define SLM_SETTICKSIZE     0x0372

#define SLN_CHANGE      1
#define SLN_SLIDERTRACK 2
#define SLN_SETFOCUS    3
#define SLN_KILLFOCUS   4

typedef struct _SLDCDATA {
    ULONG  cbSize;
    USHORT usScale1Increments;
    USHORT usScale1Spacing;
    USHORT usScale2Increments;
    USHORT usScale2Spacing;
} SLDCDATA, *PSLDCDATA;

#endif

#if defined (INCL_WINCIRCULARSLIDER) && !defined (INCL_WINCIRCULARSLIDER_INCLUDED)
#define INCL_WINCIRCULARSLIDER_INCLUDED

#define CSM_QUERYRANGE           0x053D
#define CSM_SETRANGE             0x053E
#define CSM_QUERYVALUE           0x053F
#define CSM_SETVALUE             0x0540
#define CSM_QUERYRADIUS          0x0541
#define CSM_SETINCREMENT         0x0542
#define CSM_QUERYINCREMENT       0x0543
#define CSM_SETBITMAPDATA        0x0544
#define CSN_SETFOCUS             0x0548
#define CSN_CHANGED              0x0549
#define CSN_TRACKING             0x054A
#define CSN_QUERYBACKGROUNDCOLOR 0x054B

#define CSS_NOBUTTON          0x0001
#define CSS_NOTEXT            0x0002
#define CSS_NONUMBER          0x0004
#define CSS_POINTSELECT       0x0008
#define CSS_360               0x0010
#define CSS_MIDPOINT          0x0020
#define CSS_PROPORTIONALTICKS 0x0040
#define CSS_NOTICKS           0x0080
#define CSS_CIRCULARVALUE     0x0100

typedef struct _CSBITMAPDATA {
    HBITMAP hbmLeftUp;
    HBITMAP hbmLeftDown;
    HBITMAP hbmRightUp;
    HBITMAP hbmRightDown;
} CSBITMAPDATA, *PCSBITMAPDATA;

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
