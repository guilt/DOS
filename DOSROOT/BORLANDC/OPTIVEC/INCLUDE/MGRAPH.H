/*  Mgraph.h

  matrix graphics functions for all floating-point data types
  for image processing

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __MGRAPH_H
#define __MGRAPH_H
#if !defined( __VGRAPH_H )
   #include <VGraph.h>
#endif
#if !defined( __MATLIB_H )
    #include <MatLib.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

/*  Density map:  values are translated into a color between
    two extremes, given as mincolor and maxcolor.
*/

typedef struct {
      VCOORDSYSTEM CartesCoord;
      extended     z_max, z_min, z_range, z_maxoverrange,
                   x_LoBorder, x_HiBorder, x_Pad,
                   y_LoBorder, y_HiBorder, y_Pad,
      #if defined _WINDOWS
           z_densityScale[4];
      #else
           z_densityScale;
      #endif
      COLORREF z_minColor;
} MCOORDSYSTEM;

#define M_continuePlot V_continuePlot
void __vf M_getCoordSystem( MCOORDSYSTEM _VFAR *xcs );
void __vf M_setCoordSystem( MCOORDSYSTEM _VFAR *xcs );

void __vf M_findDensityMapBounds( extended xmin, extended xmax,
                                  extended ymin, extended ymax,
                                  extended zmin, extended zmax,
                                  COLORREF mincolor, COLORREF maxcolor );
void __vf M_setDensityMapBounds(  extended xmin, extended xmax,
                                  extended ymin, extended ymax,
                                  extended zmin, extended zmax,
                                  COLORREF mincolor, COLORREF maxcolor );
void __vf M_setDensityBounds(  extended zmin, extended zmax,
                               COLORREF mincolor, COLORREF maxcolor );

#define MF_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MFxyzAutoDensityMap( X, Y, MZ[0], ht, len, mincol, maxcol )
#define MF_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MFxyzDataDensityMap( X, Y, MZ[0], ht, len )
#define MF_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MFzAutoDensityMap( MZ[0], ht, len, mincol, maxcol )
#define MF_zDataDensityMap( MZ, ht, len ) \
                 MFzDataDensityMap( MZ[0], ht, len )

void __vf MFxyzAutoDensityMap( fVector X, fVector Y, fPMatrix MZ,
                             unsigned ht, unsigned len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MFxyzDataDensityMap( fVector X, fVector Y, fPMatrix MZ,
                             unsigned ht, unsigned len );
void __vf MFzAutoDensityMap( fPMatrix MZ, unsigned ht, unsigned len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MFzDataDensityMap( fPMatrix MZ, unsigned ht, unsigned len );

#define MD_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MDxyzAutoDensityMap( X, Y, MZ[0], ht, len, mincol, maxcol )
#define MD_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MDxyzDataDensityMap( X, Y, MZ[0], ht, len )
#define MD_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MDzAutoDensityMap( MZ[0], ht, len, mincol, maxcol )
#define MD_zDataDensityMap( MZ, ht, len ) \
                 MDzDataDensityMap( MZ[0], ht, len )

void __vf MDxyzAutoDensityMap( dVector X, dVector Y, dPMatrix MZ,
                             unsigned ht, unsigned len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MDxyzDataDensityMap( dVector X, dVector Y, dPMatrix MZ,
                             unsigned ht, unsigned len );
void __vf MDzAutoDensityMap( dPMatrix MZ, unsigned ht, unsigned len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MDzDataDensityMap( dPMatrix MZ, unsigned ht, unsigned len );

#ifdef __BORLANDC__   /* 80-bit reals supported ? */
#define ME_xyzAutoDensityMap( X, Y, MZ, ht, len, mincol, maxcol ) \
                 MExyzAutoDensityMap( X, Y, MZ[0], ht, len, mincol, maxcol )
#define ME_xyzDataDensityMap( X, Y, MZ, ht, len ) \
                 MExyzDataDensityMap( X, Y, MZ[0], ht, len )
#define ME_zAutoDensityMap( MZ, ht, len, mincol, maxcol ) \
                 MEzAutoDensityMap( MZ[0], ht, len, mincol, maxcol )
#define ME_zDataDensityMap( MZ, ht, len ) \
                 MEzDataDensityMap( MZ[0], ht, len )

void __vf MExyzAutoDensityMap( eVector X, eVector Y, ePMatrix MZ,
                               unsigned ht, unsigned len,
                               COLORREF mincolor, COLORREF maxcolor );
void __vf MExyzDataDensityMap( eVector X, eVector Y, ePMatrix MZ,
                               unsigned ht, unsigned len );
void __vf MEzAutoDensityMap( ePMatrix MZ, unsigned ht, unsigned len,
                             COLORREF mincolor, COLORREF maxcolor );
void __vf MEzDataDensityMap( ePMatrix MZ, unsigned ht, unsigned len );

#else   /* ME_ functions identical to MD_ for MSVC, Optima++ */
#define ME_xyzAutoDensityMap  MD_xyzAutoDensityMap
#define ME_xyzDataDensityMap  MD_xyzDataDensityMap
#define ME_zAutoDensityMap    MD_zAutoDensityMap
#define ME_zDataDensityMap    MD_zDataDensityMap
#endif   /*  Borland, Microsoft, Powersoft */

/*  Color-Map: each range of values is associated with a certain color.
    Values are defined in a vector ValScale, associated colors in ColScale.
    The parameter "mode" decides how to interpret ValScale:
    mode=0: Val is mid-point;      +1: Val gives upper limit;
        -1: Val gives lower limit.
*/
/* not yet implemented:
void __vf M_findColorMapBounds( extended xmin, extended xmax,
                                extended ymin, extended ymax,
                                extended zmin, extended zmax );
void __vf M_setColorMapBounds(  extended xmin, extended xmax,
                                extended ymin, extended ymax,
                                extended zmin, extended zmax );

void __vf MFxyzAutoColorMap( fVector X, fVector Y, fPMatrix MZ,
                             unsigned ht, unsigned len,
                             fVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MFxyzDataColorMap( fVector X, fVector Y, fPMatrix MZ,
                             unsigned ht, unsigned len );
void __vf MFzAutoColorMap(   fPMatrix MZ, unsigned ht, unsigned len,
                             fVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MFzDataColorMap(   fPMatrix MZ, unsigned ht, unsigned len );

void __vf MDxyzAutoColorMap( dVector X, dVector Y, dPMatrix MZ,
                             unsigned ht, unsigned len,
                             dVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MDxyzDataColorMap( dVector X, dVector Y, dPMatrix MZ,
                             unsigned ht, unsigned len );
void __vf MDzAutoColorMap(   dPMatrix MZ, unsigned ht, unsigned len,
                             dVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MDzDataColorMap(   dPMatrix MZ, unsigned ht, unsigned len );

void __vf MExyzAutoColorMap( eVector X, eVector Y, ePMatrix MZ,
                             unsigned ht, unsigned len,
                             eVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MExyzDataColorMap( eVector X, eVector Y, ePMatrix MZ,
                             unsigned ht, unsigned len );
void __vf MEzAutoColorMap(   ePMatrix MZ, unsigned ht, unsigned len,
                             eVector ValScale, COLORREF _VFAR *ColScale,
                             unsigned ncolors, int mode );
void __vf MEzDataColorMap(   ePMatrix MZ, unsigned ht, unsigned len );
*/

#ifdef __cplusplus
}
#endif
#endif /* __MGRAPH_H */
