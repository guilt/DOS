/*  VCDstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type dComplex
  (double-precision complex numbers)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VCDSTD_H
#define __VCDSTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

cdVector   __vf  VCD_vector( ui size );
cdVector   __vf  VCD_vector0( ui size );

/***************  Addressing single vector elements ******************/

dComplex _VFAR * VCD_Pelement( cdVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VCD_element( X, n )  (*VCD_Pelement( X, n ))

/*******************  Initialization **********************************/

void  __vf  VCD_equ0( cdVector X, ui size );
void  __vf  VCD_equ1( cdVector X, ui size );
void  __vf  VCD_equm1( cdVector X, ui size );
void  __vf  VCD_equC( cdVector X, ui size, dComplex C );
void  __vf  VCD_equV( cdVector Y, cdVector X, ui size );
void  __vf  VCDx_equV( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B );
void  __vf  VCD_ramp( cdVector X, ui size, dComplex Start, dComplex Rise );

void  __vf  VD_CtoReIm( dVector Re, dVector Im, cdVector X, ui size );
void  __vf  VD_ReImtoC( cdVector Y, dVector Re, dVector Im, ui size );
void  __vf  VD_CtoRe( dVector Re, cdVector X, ui size );
void  __vf  VD_RetoC( cdVector Y, dVector Re, ui size );
void  __vf  VD_CtoIm( dVector Im, cdVector X, ui size );
void  __vf  VD_ImtoC( cdVector Y, dVector Im, ui size );
void  __vf  VD_CtoPolar( dVector Mag, dVector Arg, cdVector X, ui size );
void  __vf  VD_PolartoC( cdVector Y, dVector Mag, dVector Arg, ui size );
void  __vf  VD_CtoNorm( dVector Norm, cdVector X, ui size );
void  __vf  VD_CtoAbs( dVector Abs, cdVector X, ui size );
void  __vf  VD_CtoArg( dVector Arg, cdVector X, ui size );
int   __vf  VCD_abs(   dVector Y, cdVector X, ui size );
#define     VCD_real( Y, X, sz )         VD_CtoRe( Y, X, sz )
#define     VCD_imag( Y, X, sz )         VD_CtoIm( Y, X, sz )
#define     VCD_arg( Y, X, sz )          VD_CtoArg( Y, X, sz )
#define     VCD_norm( Y, X, sz )         VD_CtoNorm( Y, X, sz )
#define     VCD_polar( Y, Mag, Arg, sz ) VD_PolartoC( Y, Mag, Arg, sz )
#define     VCD_complex( Y, Re, Im, sz ) VD_ReImtoC( Y, Re, Im, sz )


/****************  Data-type interconversions  ***************************/

void  __vf   V_CFtoCD( cdVector Y, cfVector X, ui size );
void  __vf   V_CDtoCF( cfVector Y, cdVector X, ui size );
#ifdef __BORLANDC__   /* 80-bit IEEE numbers supported */
    void  __vf   V_CDtoCE( ceVector Y, cdVector X, ui size );
    void  __vf   V_CEtoCD( cdVector Y, ceVector X, ui size );
#else  /* no IEEE number support with other compilers */
    #define V_CDtoCE VCD_equV
    #define V_CEtoCD VCD_equV
#endif


/****************  Index-oriented manipulations ***********************/

void  __vf  VCD_reflect( cdVector X, ui size );
void  __vf  VCD_delete( cdVector X, ui size, ui pos );
void  __vf  VCD_insert( cdVector X, ui size, ui pos, dComplex C );
void  __vf  VCD_rev( cdVector Y, cdVector X, ui size );
#ifdef V_HUGE
   void  __vf  VCD_rotate( cdVector Y, cdVector X, ui size, long pos );
#else
   void  __vf  VCD_rotate( cdVector Y, cdVector X, ui size, int pos );
#endif

void  __vf  VCD_indpick( cdVector Y, uiVector Ind, ui sizey, cdVector X );
void  __vf  VCD_indput(  cdVector Y, cdVector X, uiVector Ind, ui sizex );
void  __vf  VCD_subvector( cdVector Y, ui sizey, cdVector X, int step );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VCD_subvector_equC(  cdVector Y, ui subsiz, unsigned samp,
                                 dComplex C );
void  __vf  VCD_subvector_equV(  cdVector Y, ui subsiz, unsigned samp,
                                 cdVector X );
    /*   for arithmetic functions of subsets, see <VCDmath.h>  */


/**************** One-Dimensional Vector Operations ***********************/

double    __vf  VCD_absmax(  cdVector X, ui size );
double    __vf  VCD_absmin(  cdVector X, ui size );
double    __vf  VCD_absmaxind( ui _VFAR *pos, cdVector X, ui size );
double    __vf  VCD_absminind( ui _VFAR *pos, cdVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if dComplex is a class
#endif
dComplex  __vf  VCD_maxReIm(     cdVector X, ui size );
dComplex  __vf  VCD_minReIm(     cdVector X, ui size );
dComplex  __vf  VCD_absmaxReIm(  cdVector X, ui size );
dComplex  __vf  VCD_absminReIm(  cdVector X, ui size );
dComplex  __vf  VCD_sum(     cdVector X, ui size );
dComplex  __vf  VCD_prod(    cdVector X, ui size );
dComplex  __vf  VCD_mean(   cdVector X, ui size );
dComplex  __vf  VCD_meanwW( cdVector X, dVector Wt, ui size );
dComplex  __vf  VCD_scalprod( cdVector X, cdVector Y, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf  VCD_runsum(  cdVector Y, cdVector X, ui size );
void      __vf  VCD_runprod( cdVector Y, cdVector X, ui size );
int       __vf  VCD_iselementC( cdVector Tab, ui size, dComplex C );
ui        __vf  VCD_iselementV( cdVector Y, cdVector X, ui sizex,
                                cdVector Tab, ui sizetab );


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

void  __vf   VCDl_FFT( cdVector Y, cdVector X, ui size, int dir );
void  __vf   VCDl_filter( cdVector Y, cdVector X, cdVector Flt, ui size );

void  __vf   VCDs_FFT( cdVector Y, cdVector X, ui size, int dir );
void  __vf   VCDs_filter( cdVector Y, cdVector X, cdVector Flt, ui size );

#if( defined( __LARGE__ ) || defined( __COMPACT__ ) )
   #define VCD_FFT       VCDl_FFT
   #define VCD_filter    VCDl_filter
#else
   #define VCD_FFT       VCDs_FFT
   #define VCD_filter    VCDs_filter
#endif


/***************************  Input and Output *****************************/

void  __vf  VCD_fprint( FILE _VFAR *stream, cdVector X, ui size,
                                 unsigned nperline, unsigned linewidth );
#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void  __vf  VCD_cprint( cdVector X, ui size, unsigned nperline );
#endif
#define     VCD_print( X, sz, npl ) VCD_fprint( stdout, X, sz, npl, 80 )
  /*  VCD_print, VCD_cprint usable only for DOS and Win32 console applications! */
void  __vf  VCD_write( FILE _VFAR *stream, cdVector X, ui size );
void  __vf  VCD_read( cdVector X, ui size, FILE _VFAR *stream );
void  __vf  VCD_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf  VCD_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf  VCD_setWriteFormat( char _VFAR *FormatString );
                                            /* for VCD_write and VCD_nwrite */
void  __vf  VCD_setWriteSeparate( char _VFAR *SepString ); /* for VCD_write */
void  __vf  VCD_setNWriteSeparate( char _VFAR *SepString ); /* for VCD_nwrite */
#ifdef V_HUGE
    void  __vf  VCD_store( FILE _VFAR *stream, cdVector X, ui size );
    void  __vf  VCD_recall( cdVector X, ui size, FILE _VFAR *stream  );
#else
    #ifdef __cplusplus
         void  inline VCD_store( FILE _VFAR *stream, cdVector X, ui size )
         {    fwrite( X, sizeof(dComplex), size, stream ); 
         }
         void  inline VCD_recall( cdVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(dComplex), size, stream );
         }
    #else
        #define VCD_store( str, X, sz )  \
                     fwrite( X, sizeof(dComplex), sz, str )
        #define VCD_recall( X, sz, str ) \
                     fread(  X, sizeof(dComplex), sz, str )
    #endif
#endif      /* VCD_store, VCD_recall in binary format */


#ifdef __cplusplus
}
#endif


#endif /*  __VCDSTD_H */
