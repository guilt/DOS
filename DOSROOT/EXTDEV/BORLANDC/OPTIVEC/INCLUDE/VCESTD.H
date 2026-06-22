/*  VCEstd.h

  vector management functions:
  complex manipulations on whole arrays or vectors of data type eComplex
  (extended-precision complex)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VCESTD_H
#define __VCESTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif

#ifdef __BORLANDC__   /* 80-bit IEEE numbers supported.
                         The following  130 lines apply 
                         only to Borland C++            */

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

ceVector   __vf  VCE_vector( ui size );
ceVector   __vf  VCE_vector0( ui size );

/***************  Addressing single vector elements ******************/

eComplex _VFAR * VCE_Pelement( ceVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VCE_element( X, n )  (*VCE_Pelement( X, n ))

/*******************  Initialization **********************************/

void  __vf  VCE_equ0( ceVector X, ui size );
void  __vf  VCE_equ1( ceVector X, ui size );
void  __vf  VCE_equm1( ceVector X, ui size );
void  __vf  VCE_equC( ceVector X, ui size, eComplex C );
void  __vf  VCE_equV( ceVector Y, ceVector X, ui size );
void  __vf  VCEx_equV( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B );
void  __vf  VCE_ramp( ceVector X, ui size, eComplex Start, eComplex Rise );

void  __vf  VE_CtoReIm( eVector Re, eVector Im, ceVector X, ui size );
void  __vf  VE_ReImtoC( ceVector Y, eVector Re, eVector Im, ui size );
void  __vf  VE_CtoRe( eVector Re, ceVector X, ui size );
void  __vf  VE_RetoC( ceVector Y, eVector Re, ui size );
void  __vf  VE_CtoIm( eVector Im, ceVector X, ui size );
void  __vf  VE_ImtoC( ceVector Y, eVector Im, ui size );
void  __vf  VE_CtoPolar( eVector Mag, eVector Arg, ceVector X, ui size );
void  __vf  VE_PolartoC( ceVector Y, eVector Mag, eVector Arg, ui size );
void  __vf  VE_CtoNorm( eVector Norm, ceVector X, ui size );
void  __vf  VE_CtoAbs( eVector Abs, ceVector X, ui size );
void  __vf  VE_CtoArg( eVector Arg, ceVector X, ui size );
int   __vf  VCE_abs(  eVector Y, ceVector X, ui size );

#define     VCE_real         VE_CtoRe
#define     VCE_imag         VE_CtoIm
#define     VCE_arg          VE_CtoArg
#define     VCE_norm         VE_CtoNorm
#define     VCE_polar        VE_PolartoC
#define     VCE_complex      VE_ReImtoC

/****************  Data-type interconversions  ***************************/

void  __vf   V_CFtoCE( ceVector Y, cfVector X, ui size );
void  __vf   V_CEtoCF( cfVector Y, ceVector X, ui size );
void  __vf   V_CDtoCE( ceVector Y, cdVector X, ui size );
void  __vf   V_CEtoCD( cdVector Y, ceVector X, ui size );


/****************  Index-oriented manipulations ***********************/

void  __vf  VCE_reflect( ceVector X, ui size );
void  __vf  VCE_delete( ceVector X, ui size, ui pos );
void  __vf  VCE_insert( ceVector X, ui size, ui pos, eComplex C );
void  __vf  VCE_rev( ceVector Y, ceVector X, ui size );
#ifdef V_HUGE
   void  __vf  VCE_rotate( ceVector Y, ceVector X, ui size, long pos );
#else
   void  __vf  VCE_rotate( ceVector Y, ceVector X, ui size, int pos );
#endif

void  __vf  VCE_indpick( ceVector Y, uiVector Ind, ui sizey, ceVector X );
void  __vf  VCE_indput(  ceVector Y, ceVector X, uiVector Ind, ui sizex );
void  __vf  VCE_subvector( ceVector Y, ui sizey, ceVector X, int step );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VCE_subvector_equC(  ceVector Y, ui subsiz, unsigned samp,
                                 eComplex C );
void  __vf  VCE_subvector_equV(  ceVector Y, ui subsiz, unsigned samp,
                                 ceVector X );
    /*   for arithmetic functions of subsets, see <VCEmath.h>  */


/**************** One-Dimensional Vector Operations ***********************/

extended  __vf  VCE_absmax(  ceVector X, ui size );
extended  __vf  VCE_absmin(  ceVector X, ui size );
extended  __vf  VCE_absmaxind( ui _VFAR *pos, ceVector X, ui size );
extended  __vf  VCE_absminind( ui _VFAR *pos, ceVector X, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if eComplex is a class
#endif
eComplex  __vf  VCE_maxReIm(     ceVector X, ui size );
eComplex  __vf  VCE_minReIm(     ceVector X, ui size );
eComplex  __vf  VCE_absmaxReIm(  ceVector X, ui size );
eComplex  __vf  VCE_absminReIm(  ceVector X, ui size );
eComplex  __vf  VCE_sum(     ceVector X, ui size );
eComplex  __vf  VCE_prod(    ceVector X, ui size );
eComplex  __vf  VCE_mean(   ceVector X, ui size );
eComplex  __vf  VCE_meanwW( ceVector X, eVector Wt, ui size );
eComplex  __vf  VCE_scalprod( ceVector X, ceVector Y, ui size );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf  VCE_runsum(  ceVector Y, ceVector X, ui size );
void      __vf  VCE_runprod( ceVector Y, ceVector X, ui size );
int       __vf  VCE_iselementC( ceVector Tab, ui size, eComplex C );
ui        __vf  VCE_iselementV( ceVector Y, ceVector X, ui sizex,
                                ceVector Tab, ui sizetab );


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

void  __vf   VCEl_FFT( ceVector Y, ceVector X, ui size, int dir );
void  __vf   VCEl_filter( ceVector Y, ceVector X, ceVector Flt, ui size );

void  __vf   VCEs_FFT( ceVector Y, ceVector X, ui size, int dir );
void  __vf   VCEs_filter( ceVector Y, ceVector X, ceVector Flt, ui size );

#if( defined( __LARGE__ ) || defined( __COMPACT__ ) )
   #define VCE_FFT       VCEl_FFT
   #define VCE_filter    VCEl_filter
#else
   #define VCE_FFT       VCEs_FFT
   #define VCE_filter    VCEs_filter
#endif


/***************************  Input and Output *****************************/

void  __vf  VCE_fprint( FILE _VFAR *stream, ceVector X, ui size,
                                 unsigned nperline, unsigned linewidth );
#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void  __vf  VCE_cprint( ceVector X, ui size, unsigned nperline );
#endif
#define     VCE_print( X, sz, npl ) VCE_fprint( stdout, X, sz, npl, 80 )\
  /*  VCE_print, VCE_cprint usable only for DOS and Win32 console applications! */
void  __vf  VCE_write( FILE _VFAR *stream, ceVector X, ui size );
void  __vf  VCE_read( ceVector X, ui size, FILE _VFAR *stream );
void  __vf  VCE_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf  VCE_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf  VCE_setWriteFormat( char _VFAR *FormatString );
                                            /* for VCE_write and VCE_nwrite */
void  __vf  VCE_setWriteSeparate( char _VFAR *SepString ); /* for VCE_write */
void  __vf  VCE_setNWriteSeparate( char _VFAR *SepString ); /* for VCE_nwrite */
#ifdef V_HUGE
    void  __vf  VCE_store( FILE _VFAR *stream, ceVector X, ui size );
    void  __vf  VCE_recall( ceVector X, ui size, FILE _VFAR *stream  );
#else
    #ifdef __cplusplus
         void  inline VCE_store( FILE _VFAR *stream, ceVector X, ui size )
         {    fwrite( X, sizeof(eComplex), size, stream ); 
         }
         void  inline VCE_recall( ceVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(eComplex), size, stream );
         }
    #else
        #define VCE_store( str, X, sz )  \
                     fwrite( X, sizeof(eComplex), sz, str )
        #define VCE_recall( X, sz, str ) \
                     fread(  X, sizeof(eComplex), sz, str )
    #endif
#endif      /* VCE_store, VCE_recall in binary format */

#ifdef __cplusplus
}    /* end of extern "C"  */
#endif

#else   /* the following 130 lines apply only to compilers without
           support for 80-bit IEEE numbers.  */

#define VCE_vector     VCD_vector
#define VCE_vector0    VCD_vector0
#define VCE_Pelement   VCD_Pelement
#define VCE_element( X, n )  (*VCE_Pelement( X, n ))

#define VCE_equ0        VCD_equ0
#define VCE_equ1        VCD_equ1
#define VCE_equm1       VCD_equm1
#define VCE_equC        VCD_equC
#define VCE_equV        VCD_equV
#define VCEx_equV       VCDx_equV
#define VCE_ramp        VCD_ramp

#define VE_CtoReIm      VD_CtoReIm
#define VE_ReImtoC      VD_ReImtoC
#define VE_CtoRe        VD_CtoRe
#define VE_RetoC        VD_RetoC
#define VE_CtoIm        VD_CtoIm
#define VE_ImtoC        VD_ImtoC
#define VE_CtoPolar     VD_CtoPolar
#define VE_PolartoC     VD_PolartoC
#define VE_CtoNorm      VD_CtoNorm
#define VE_CtoAbs       VD_CtoAbs
#define VE_CtoArg       VD_CtoArg
#define VCE_abs         VCD_abs


#define VCE_real        VE_CtoRe
#define VCE_imag        VE_CtoIm
#define VCE_arg         VE_CtoArg
#define VCE_norm        VE_CtoNorm
#define VCE_polar       VE_PolartoC
#define VCE_complex     VE_ReImtoC


#define V_CFtoCE        V_CFtoCD
#define V_CEtoCF        V_CDtoCF
#define V_CDtoCE        VCD_equV
#define V_CEtoCD        VCD_equV

#define VCE_reflect     VCD_reflect
#define VCE_delete      VCD_delete
#define VCE_insert      VCD_insert
#define VCE_rev         VCD_rev
#define VCE_rotate      VCD_rotate
#define VCE_indpick     VCD_indpick
#define VCE_indput      VCD_indput
#define VCE_subvector   VCD_subvector
#define VCE_subvector_equC  VCD_subvector_equC
#define VCE_subvector_equV  VCE_subvector_equV

#define VCE_maxReIm     VCD_maxReIm
#define VCE_minReIm     VCD_minReIm
#define VCE_absmaxReIm  VCD_absmaxReIm
#define VCE_absminReIm  VCD_absminReIm
#define VCE_absmax      VCD_absmax
#define VCE_absmin      VCD_absmin
#define VCE_absmaxind   VCD_absmaxind
#define VCE_absminind   VCD_absminind
#define VCE_sum         VCD_sum
#define VCE_prod        VCD_prod
#define VCE_runsum      VCD_runsum
#define VCE_runprod     VCD_runprod
#define VCE_iselementC  VCD_iselementC
#define VCE_iselementV  VCD_iselementV

#define VCE_mean        VCD_mean
#define VCE_meanwW      VCD_meanwW

#define VCEl_FFT        VCDl_FFT
#define VCEl_filter     VCDl_filter
#define VCEs_FFT        VCDs_FFT
#define VCEs_filter     VCDs_filter
#define VCE_FFT         VCEs_FFT
#define VCE_filter      VCEs_filter

#define VCE_fprint      VCD_fprint
#define VCE_cprint      VCD_cprint
#define VCE_print       VCD_print
#define VCE_write       VCD_write
#define VCE_read        VCD_read
#define VCE_nwrite      VCD_nwrite
#define VCE_nread       VCD_nread
#define VCE_setWriteFormat      VCD_setWriteFormat
#define VCE_setWriteSeparate    VCD_setWriteSeparate    
#define VCE_setNWriteSeparate   VCD_setNWriteSeparate
#define VCE_store       VCD_store
#define VCE_recall      VCD_recall


#endif   /* IEEE number support */

#endif /*  __VCESTD_H */
