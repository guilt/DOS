/*  Vgraph.h

  graphics functions for all floating-point and integer vector types

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VGRAPH_H
#define __VGRAPH_H
#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#if defined _WINDOWS || defined _Windows
    #if defined _MSC_VER || defined __BORLANDC__
         /* <windows.h> or the MFC, OWL, OCF files must be included before <VGraph.h> ! */
    #else /* that means: Optima++ */
        #include <WCanvas.hpp>
        #include <WColor.hpp>
        #define COLORREF WColor
    #endif
#else
  #if defined( __WINDOWS_H )
     #error <windows.h> must not be included, if program will run under DOS!
  #endif
  #include <graphics.h>
  #define COLORREF unsigned   /* in <windows.h> defined as DWORD! */
#endif

#ifdef __cplusplus
extern "C" {
#endif


/********************  Plot-Routines **************************/

#if defined _WINDOWS || defined _Windows
    #if defined __BORLANDC__ || defined _MSC_VER
        void  __vf  V_initPlot( HWND vhwnd, HDC vdc );
        void  __vf  V_initPrint( HDC vprintdc );
    #else  /* Optima++ */
        void  __vf  V_initPlot( WCanvas _VFAR *vcanv );
        void  __vf  V_initPrint( WPrinterCanvas _VFAR *vcanvas );
    #endif
#else   /*  DOS: use Borland's BGI   */
        void  __vf  V_initGraph( char _VFAR *pathtodriver );
        void  __vf  V_initPlot( int graphmode );
#endif
void  __vf  V_setPlotRegion( int left, int top, int right, int bottom );
void  __vf  V_setSymbolSize( float symsize );
void  __vf  V_setLineThickness( unsigned thickness );
int   __vf  V_findAxisRange( extended _VFAR *LoX, extended _VFAR *HiX,
                             extended Xmin, extended Xmax );
void  __vf  V_findAxes( extended Xmin, extended Xmax,
                        extended Ymin, extended Ymax );
void  __vf  V_drawAxes( extended Xmin, extended Xmax,
                        extended Ymin, extended Ymax );
void  __vf  V_continuePlot( void );

#ifdef __BORLANDC__
    #pragma option -a-
#else /* Visual C++ */
    #pragma pack( push,1 )
#endif /* avoid insertion of dummy bytes  */
typedef struct {
      int         left, top, right, bottom,
                  outleft, outtop, outright, outbottom,
                  nPixx, nPixy,
                  xclipu, xclipl, yclipu, yclipl,
                  cs, cl, cdot;
      unsigned    linethickness, symlinethickness, DangerOver;
      float       symbolsize, x_scale, y_scale;
      extended    x_max, x_min, x_range, x_maxoverrange,
                  y_max, y_min, y_range, y_maxoverrange;
      } VCOORDSYSTEM;
#ifdef __BORLANDC__
       #pragma option -a.
#else /* Visual C++ */
       #pragma pack( pop )
#endif    /* restore default data packing  */

void  __vf  V_setCoordSystem( VCOORDSYSTEM _VFAR *xcs );
void  __vf  V_getCoordSystem( VCOORDSYSTEM _VFAR *xcs );

void  __vf  VF_xyAutoPlot(  fVector X, fVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VF_xy2AutoPlot( fVector X1, fVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            fVector X2, fVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VF_xyDataPlot(  fVector X, fVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VF_yAutoPlot(   fVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VF_y2AutoPlot(  fVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            fVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VF_yDataPlot(   fVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VCF_autoPlot(   cfVector X, ui size,
                            unsigned form, COLORREF color );
void  __vf  VCF_2AutoPlot(  cfVector X1, ui size1,
                            unsigned form1, COLORREF color1,
                            cfVector X2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VCF_dataPlot(   cfVector X, ui size,
                            unsigned form, COLORREF color );

void  __vf  VD_xyAutoPlot(  dVector X, dVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VD_xy2AutoPlot( dVector X1, dVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            dVector X2, dVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VD_xyDataPlot(  dVector X, dVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VD_yAutoPlot(   dVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VD_y2AutoPlot(  dVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            dVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VD_yDataPlot(   dVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VCD_autoPlot(   cdVector X, ui size,
                            unsigned form, COLORREF color );
void  __vf  VCD_2AutoPlot(  cdVector X1, ui size1,
                            unsigned form1, COLORREF color1,
                            cdVector X2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VCD_dataPlot(   cdVector X, ui size,
                            unsigned form, COLORREF color );

#ifdef __BORLANDC__   /* 80-bit IEEE numbers supported.
                         The following lines apply
                         only to Borland C++            */
void  __vf  VE_xyAutoPlot(  eVector X, eVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VE_xy2AutoPlot( eVector X1, eVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            eVector X2, eVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VE_xyDataPlot(  eVector X, eVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VE_yAutoPlot(   eVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VE_y2AutoPlot(  eVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            eVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VE_yDataPlot(   eVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VCE_autoPlot(   ceVector X, ui size,
                            unsigned form, COLORREF color );
void  __vf  VCE_2AutoPlot(  ceVector X1, ui size1,
                            unsigned form1, COLORREF color1,
                            ceVector X2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VCE_dataPlot(   ceVector X, ui size,
                            unsigned form, COLORREF color );

#else   /* no 80-bit IEEE number support:
     the following lines apply only to Visual C++ and Optima++ */
#define VE_xyAutoPlot       VD_xyAutoPlot
#define VE_xy2AutoPlot      VD_xy2AutoPlot
#define VE_xyDataPlot       VD_xyDataPlot
#define VE_yAutoPlot        VD_yAutoPlot
#define VE_y2AutoPlot       VD_y2AutoPlot
#define VE_yDataPlot        VD_yDataPlot
#define VCE_autoPlot        VCD_autoPlot
#define VCE_2AutoPlot       VCD_2AutoPlot
#define VCE_dataPlot        VCD_dataPlot

#endif  /* 80-bit real support */

void  __vf  VBI_xyAutoPlot(  biVector X, biVector Y, ui bize,
                             unsigned form, COLORREF color );
void  __vf  VBI_xy2AutoPlot( biVector X1, biVector Y1, ui bize1,
                             unsigned form1, COLORREF color1,
                             biVector X2, biVector Y2, ui bize2,
                             unsigned form2, COLORREF color2 );
void  __vf  VBI_xyDataPlot(  biVector X, biVector Y, ui bize,
                             unsigned form, COLORREF color );
void  __vf  VBI_yAutoPlot(   biVector Y, ui bize,
                             unsigned form, COLORREF color );
void  __vf  VBI_y2AutoPlot(  biVector Y1, ui bize1,
                             unsigned form1, COLORREF color1,
                             biVector Y2, ui bize2,
                             unsigned form2, COLORREF color2 );
void  __vf  VBI_yDataPlot(   biVector Y, ui bize,
                             unsigned form, COLORREF color );

void  __vf  VSI_xyAutoPlot(  siVector X, siVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VSI_xy2AutoPlot( siVector X1, siVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             siVector X2, siVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VSI_xyDataPlot(  siVector X, siVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VSI_yAutoPlot(   siVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VSI_y2AutoPlot(  siVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             siVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VSI_yDataPlot(   siVector Y, ui size,
                             unsigned form, COLORREF color );

void  __vf  VI_xyAutoPlot(  iVector X, iVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VI_xy2AutoPlot( iVector X1, iVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            iVector X2, iVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VI_xyDataPlot(  iVector X, iVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VI_yAutoPlot(   iVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VI_y2AutoPlot(  iVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            iVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VI_yDataPlot(   iVector Y, ui size,
                            unsigned form, COLORREF color );

void  __vf  VLI_xyAutoPlot(  liVector X, liVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VLI_xy2AutoPlot( liVector X1, liVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             liVector X2, liVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VLI_xyDataPlot(  liVector X, liVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VLI_yAutoPlot(   liVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VLI_y2AutoPlot(  liVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             liVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VLI_yDataPlot(   liVector Y, ui size,
                             unsigned form, COLORREF color );

void  __vf  VQI_xyAutoPlot(  qiVector X, qiVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VQI_xy2AutoPlot( qiVector X1, qiVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             qiVector X2, qiVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VQI_xyDataPlot(  qiVector X, qiVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VQI_yAutoPlot(   qiVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VQI_y2AutoPlot(  qiVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             qiVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VQI_yDataPlot(   qiVector Y, ui size,
                             unsigned form, COLORREF color );

void  __vf  VUB_xyAutoPlot(  ubVector X, ubVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VUB_xy2AutoPlot( ubVector X1, ubVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             ubVector X2, ubVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VUB_xyDataPlot(  ubVector X, ubVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VUB_yAutoPlot(   ubVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VUB_y2AutoPlot(  ubVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             ubVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VUB_yDataPlot(   ubVector Y, ui size,
                             unsigned form, COLORREF color );

void  __vf  VUS_xyAutoPlot(  usVector X, usVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VUS_xy2AutoPlot( usVector X1, usVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             usVector X2, usVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VUS_xyDataPlot(  usVector X, usVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VUS_yAutoPlot(   usVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VUS_y2AutoPlot(  usVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             usVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VUS_yDataPlot(   usVector Y, ui size,
                             unsigned form, COLORREF color );

void  __vf  VU_xyAutoPlot(  uVector X, uVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VU_xy2AutoPlot( uVector X1, uVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            uVector X2, uVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VU_xyDataPlot(  uVector X, uVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VU_yAutoPlot(   uVector Y, ui size,
                            unsigned form, COLORREF color );
void  __vf  VU_y2AutoPlot(  uVector Y1, ui size1,
                            unsigned form1, COLORREF color1,
                            uVector Y2, ui size2,
                            unsigned form2, COLORREF color2 );
void  __vf  VU_yDataPlot(   uVector Y, ui size,
                            unsigned form, COLORREF color );

void  __vf  VUL_xyAutoPlot(  ulVector X, ulVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VUL_xy2AutoPlot( ulVector X1, ulVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             ulVector X2, ulVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VUL_xyDataPlot(  ulVector X, ulVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VUL_yAutoPlot(   ulVector Y, ui size,
                             unsigned form, COLORREF color );
void  __vf  VUL_y2AutoPlot(  ulVector Y1, ui size1,
                             unsigned form1, COLORREF color1,
                             ulVector Y2, ui size2,
                             unsigned form2, COLORREF color2 );
void  __vf  VUL_yDataPlot(   ulVector Y, ui size,
                             unsigned form, COLORREF color );

#ifdef V_HUGE
    #define VUI_xyAutoPlot    VUL_xyAutoPlot
    #define VUI_xy2AutoPlot   VUL_xy2AutoPlot
    #define VUI_xyDataPlot    VUL_xyDataPlot
    #define VUI_yAutoPlot     VUL_yAutoPlot
    #define VUI_y2AutoPlot    VUL_y2AutoPlot
    #define VUI_yDataPlot     VUL_yDataPlot
#else
    #define VUI_xyAutoPlot    VU_xyAutoPlot
    #define VUI_xy2AutoPlot   VU_xy2AutoPlot
    #define VUI_xyDataPlot    VU_xyDataPlot
    #define VUI_yAutoPlot     VU_yAutoPlot
    #define VUI_y2AutoPlot    VU_y2AutoPlot
    #define VUI_yDataPlot     VU_yDataPlot
#endif

#ifdef __cplusplus
}  // end of extern "C" statement
#endif

/*   Plotting Styles
     The linestyles defined for DOS in Borland's <graphics.h> are
     translated into the appropriate MS-WINDOWS pen styles.
     The other way round, MS-WINDOWS pen styles are translated
     into BGI linestyles for DOS programs. */

#if defined _Windows || defined _WINDOWS
   #define SOLID_LINE  PS_SOLID
   #define DOTTED_LINE PS_DOT
   #define CENTER_LINE PS_DASHDOT
   #define DASHED_LINE PS_DASH
   #define NULL_LINE   PS_NULL
   /*  "USERBIT_LINE" cannot be translated */
#else
   #define PS_SOLID       SOLID_LINE
   #define PS_DASH        DASHED_LINE
   #define PS_DOT         DOTTED_LINE
   #define PS_DASHDOT     CENTER_LINE
   #define PS_DASHDOTDOT  USERBIT_LINE /* dahdotdot pattern set internally */
   #define PS_NULL        5
   #define PS_INSIDEFRAME SOLID_LINE /* not exactly */
   #define NULL_LINE      5          /* missing in BGI definitions */
#endif
#if !defined __BORLANDC__ && !defined _MSC_VER
         /* definitions for Watcom */
   #define PS_SOLID       WPStyleSolid
   #define PS_DASH        WPStyleDash
   #define PS_DOT         WPStyleDot
   #define PS_DASHDOT     WPStyleDashDot
   #define PS_DASHDOTDOT  WPStyleDashDotDot
#endif

/* Definition of the symbols marking the data points: */

#define SY_NULL          0
#define SY_CROSS         0x0100
#define SY_PLUS          0x0200
#define SY_STAR          0x0300
#define SY_CIRCLE        0x0400
#define SY_BOX           0x0500
#define SY_DIAMOND       0x0600
#define SY_TRIANGLEUP    0x0700  /* upwards-pointing triangle */
#define SY_TRIANGLEDOWN  0x0800  /* downwards-pointing triangle */

/* Filling of the symbols: */
#define SY_HOLLOW 0
#define SY_DOTTED 0x1000
#define SY_FILLED 0x2000

/*   Plotting Colors
     The following colors are defined for MS-WINDOWS by analogy with
     the COLORS defined for DOS programs in Borland's <graphics.h>:   */
#if defined _Windows || defined _WINDOWS
   #define __COLORS /*  overwrite COLORS of Borland C++'s <conio.h> */
   #define   BLACK        (DWORD) 0UL             /* dark colors */
   #define   BLUE         (DWORD) 0x00800000UL
   #define   GREEN        (DWORD) 0x00008000UL
   #define   CYAN         (DWORD) 0x00808000UL
   #define   RED          (DWORD) 0x000000B0UL
   #define   MAGENTA      (DWORD) 0x00800080UL
   #define   BROWN        (DWORD) 0x00000080UL
   #define   LIGHTGRAY    (DWORD) 0x00808080UL
   #define   DARKGRAY     (DWORD) 0x00B0B0B0UL   /* light colors */
   #define   LIGHTBLUE    (DWORD) 0x00FF0000UL
   #define   LIGHTGREEN   (DWORD) 0x0000FF00UL
   #define   LIGHTCYAN    (DWORD) 0x00FFFF00UL
   #define   LIGHTRED     (DWORD) 0x000000FFUL
   #define   LIGHTMAGENTA (DWORD) 0x00FF00FFUL
   #define   YELLOW       (DWORD) 0x0000FFFFUL
   #define   WHITE        (DWORD) 0x00FFFFFFUL
#endif

#endif /* __VGRAPH_H */
