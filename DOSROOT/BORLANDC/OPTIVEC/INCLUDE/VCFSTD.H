/*  VCFstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type "fComplex"
  (single-precision complex numbers)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VCFSTD_H
#define __VCFSTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

cfVector   __vf  VCF_vector( ui size );
cfVector   __vf  VCF_vector0( ui size );

/***************  Addressing single vector elements ******************/

fComplex _VFAR * VCF_Pelement( cfVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VCF_element( X, n )  (*VCF_Pelement( X, n ))

/*******************  Initialization **********************************/

void  __vf  VCF_equ0( cfVector X, ui size );
void  __vf  VCF_equ1( cfVector X, ui size );
void  __vf  VCF_equm1( cfVector X, ui size );
void  __vf  VCF_equC( cfVector X, ui size, fComplex C );
void  __vf  VCF_equV( cfVector Y, cfVector X, ui size );
void  __vf  VCFx_equV( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B );
void  __vf  VCF_ramp( cfVector X, ui size, fComplex Start, fComplex Rise );

void  __vf  VF_CtoReIm( fVector Re, fVector Im, cfVector X, ui size );
void  __vf  VF_ReImtoC( cfVector Y, fVector Re, fVector Im, ui size );
void  __vf  VF_CtoRe(  fVector Re, cfVector X, ui size );
void  __vf  VF_RetoC(  cfVector Y, fVector Re, ui size );
void  __vf  VF_CtoIm(  fVector Im, cfVector X, ui size );
void  __vf  VF_ImtoC(  cfVector Y, fVector Im, ui size );
void  __vf  VF_CtoPolar( fVector Mag, fVector Arg, cfVector X, ui size );
void  __vf  VF_PolartoC( cfVector Y, fVector Mag, fVector Arg, ui size );
void  __vf  VF_CtoNorm( fVector Norm, cfVector X, ui size );
void  __vf  VF_CtoAbs( fVector Abs, cfVector X, ui size );
void  __vf  VF_CtoArg( fVector Arg, cfVector X, ui size );
int   __vf  VCF_abs(   fVector Y, cfVector X, ui size );
#define     VCF_real       VF_CtoRe
#define     VCF_imag       VF_CtoIm
#define     VCF_arg        VF_CtoArg
#define     VCF_norm       VF_CtoNorm
#define     VCF_polar      VF_PolartoC
#define     VCF_complex    VF_ReImtoC

/****************  Data-type interconversions  ***************************/

void  __vf   V_CFtoCD( cdVector Y, cfVector X, ui size );
void  __vf   V_CDtoCF( cfVector Y, cdVector X, ui size );
#ifdef __BORLANDC__   /* 80-bit IEEE numbers supported */
    void  __vf   V_CFtoCE( ceVector Y, cfVector X, ui size );
    void  __vf   V_CEtoCF( cfVector Y, ceVector X, ui size );
#else  /* no IEEE number support for other compilers */
    #define V_CFtoCE V_CFtoCD
    #define V_CEtoCF V_CDtoCF
#endif


/****************  Index-oriented manipulations ***********************/

void  __vf  VCF_reflect( cfVector X, ui size );
void  __vf  VCF_delete( cfVector X, ui size, ui pos );
void  __vf  VCF_insert( cfVector X, ui size, ui pos, fComplex C );
void  __vf  VCF_rev( cfVector Y, cfVector X, ui size );
#ifdef V_HUGE
   void  __vf  VCF_rotate( cfVector Y, cfVector X, ui size, long pos );
#else
   void  __vf  VCF_rotate( cfVector Y, cfVector X, ui size, int pos );
#endif

void  __vf  VCF_indpick( cfVector Y, uiVector Ind, ui sizey, cfVector X );
void  __vf  VCF_indput(  cfVector Y, cfVector X, uiVector Ind, ui sizex );
void  __vf  VCF_subvector( cfVector Y, ui sizey, cfVector X, int step );


/*************** Functions of a sub-set of elements  ********************/

void  __vf  VCF_subvector_equC(  cfVector Y, ui subsiz, unsigned samp,
                                 fComplex C );
void  __vf  VCF_subvector_equV(  cfVector Y, ui subsiz, unsigned samp,
                                 cfVector X );
    /*   for arithmetic functions of subsets, see <VCFmath.h>  */

/**************** One-Dimensional Vector Operations ***********************/

float     __vf  VCF_absmax(  cfVector X, ui size );
float     __vf  VCF_absmin(  cfVector X, ui size );
float     __vf  VCF_absmaxind( ui _VFAR *pos, cfVector X, ui size );
float     __vf  VCF_absminind( ui _VFAR *pos, cfVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
fComplex  __vf  VCF_maxReIm(     cfVector X, ui size );
fComplex  __vf  VCF_minReIm(     cfVector X, ui size );
fComplex  __vf  VCF_absmaxReIm(  cfVector X, ui size );
fComplex  __vf  VCF_absminReIm(  cfVector X, ui size );
fComplex  __vf  VCF_sum(     cfVector X, ui size );
fComplex  __vf  VCF_prod(    cfVector X, ui size );
fComplex  __vf  VCF_mean(   cfVector X, ui size );
fComplex  __vf  VCF_meanwW( cfVector X, fVector Wt, ui size );
fComplex  __vf  VCF_scalprod( cfVector X, cfVector Y, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf  VCF_runsum(  cfVector Y, cfVector X, ui size );
void      __vf  VCF_runprod( cfVector Y, cfVector X, ui size );
int       __vf  VCF_iselementC( cfVector Tab, ui size, fComplex C );
ui        __vf  VCF_iselementV( cfVector Y, cfVector X, ui sizex,
                                cfVector Tab, ui sizetab );


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

void  __vf   VCFl_FFT( cfVector Y, cfVector X, ui size, int dir );
void  __vf   VCFl_filter( cfVector Y, cfVector X, cfVector Flt, ui size );

void  __vf   VCFs_FFT( cfVector Y, cfVector X, ui size, int dir );
void  __vf   VCFs_filter( cfVector Y, cfVector X, cfVector Flt, ui size );

#if( defined( __LARGE__ ) || defined( __COMPACT__ ) )
   #define VCF_FFT       VCFl_FFT
   #define VCF_filter    VCFl_filter
#else
   #define VCF_FFT       VCFs_FFT
   #define VCF_filter    VCFs_filter
#endif


/***************************  Input and Output *****************************/

void  __vf  VCF_fprint( FILE _VFAR *stream, cfVector X, ui size,
                                 unsigned nperline, unsigned linewidth );
#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void  __vf  VCF_cprint( cfVector X, ui size, unsigned nperline );
#endif
#define     VCF_print( X, sz, npl ) VCF_fprint( stdout, X, sz, npl, 80 )
  /*  VCF_print, VCF_cprint usable only for DOS and Win32 console applications! */
void  __vf  VCF_write( FILE _VFAR *stream, cfVector X, ui size );
void  __vf  VCF_read( cfVector X, ui size, FILE _VFAR *stream );
void  __vf  VCF_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf  VCF_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf  VCF_setWriteFormat( char _VFAR *FormatString );
                                            /* for VCF_write and VCF_nwrite */
void  __vf  VCF_setWriteSeparate( char _VFAR *SepString ); /* for VCF_write */
void  __vf  VCF_setNWriteSeparate( char _VFAR *SepString ); /* for VCF_nwrite */
#ifdef V_HUGE
    void  __vf  VCF_store( FILE *stream, cfVector X, ui size );
    void  __vf  VCF_recall( cfVector X, ui size, FILE _VFAR *stream  );
#else
    #ifdef __cplusplus
         void  inline VCF_store( FILE _VFAR *stream, cfVector X, ui size )
         {    fwrite( X, sizeof(fComplex), size, stream ); 
         }
         void  inline VCF_recall( cfVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(fComplex), size, stream );
         }
    #else
        #define VCF_store( str, X, sz )  \
                     fwrite( X, sizeof(fComplex), sz, str )
        #define VCF_recall( X, sz, str ) \
                     fread(  X, sizeof(fComplex), sz, str )
    #endif
#endif      /* VCF_store, VCF_recall in binary format */

#ifdef __cplusplus
}
#endif


#endif /*  __VCFSTD_H */
