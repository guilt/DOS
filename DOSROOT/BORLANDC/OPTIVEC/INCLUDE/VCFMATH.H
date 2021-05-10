/*  VCFmath.h

  vector management functions:
  arithmetic and math functions performed on each individual element
  of an array or vector of data type "fComplex"  (complex float)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VCFMATH_H
#define __VCFMATH_H

#ifndef __VCFSTD_H 
#include <VCFstd.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/********************* Comparisons ****************************/

ui   __vf   VCF_cmp_eq0( cfVector Y, cfVector X, ui size );
ui   __vf   VCF_cmp_ne0( cfVector Y, cfVector X, ui size );
ui   __vf   VCF_cmp_eqC( cfVector Y, cfVector X, ui size, fComplex C );
ui   __vf   VCF_cmp_neC( cfVector Y, cfVector X, ui size, fComplex C );
ui   __vf   VCF_cmp_eqV( cfVector Z, cfVector X, cfVector Y, ui size );
ui   __vf   VCF_cmp_neV( cfVector Z, cfVector X, cfVector Y, ui size );
ui   __vf   VCF_cmp_eq0ind( uiVector Ind, cfVector X, ui size );
ui   __vf   VCF_cmp_ne0ind( uiVector Ind, cfVector X, ui size );
ui   __vf   VCF_cmp_eqCind( uiVector Ind, cfVector X, ui size, fComplex C );
ui   __vf   VCF_cmp_neCind( uiVector Ind, cfVector X, ui size, fComplex C );
ui   __vf   VCF_cmp_eqVind( uiVector Ind, cfVector X, cfVector Y, ui size );
ui   __vf   VCF_cmp_neVind( uiVector Ind, cfVector X, cfVector Y, ui size );


/********************  Standard Arithmetics   ***************************/

void  __vf   VCF_limit(  cfVector Y, cfVector X, ui size, fComplex Min,
                                                          fComplex Max );
void  __vf   VCF_flush0( cfVector Y, cfVector X, ui size, fComplex AbsMin );
void  __vf   VCF_flushInv( cfVector Y, cfVector X, ui size, fComplex AbsMin );

void  __vf   VCFx_equV(  cfVector Y, cfVector X, ui size,
                         fComplex A, fComplex B );
void  __vf   VCF_addC(   cfVector Y, cfVector X, ui size, fComplex C );
void  __vf   VCF_subC(   cfVector Y, cfVector X, ui size, fComplex C );
void  __vf   VCF_subrC(  cfVector Y, cfVector X, ui size, fComplex C );
void  __vf   VCF_mulC(   cfVector Y, cfVector X, ui size, fComplex C );
void  __vf   VCF_divC(   cfVector Y, cfVector X, ui size, fComplex C );
void  __vf   VCF_divrC(  cfVector Y, cfVector X, ui size, fComplex C );
void  __vf   VCFx_divrC( cfVector Y, cfVector X, ui size,
                         fComplex A, fComplex B, fComplex C );

void  __vf   VCF_addReC(  cfVector Y, cfVector X, ui size, float CRe );
void  __vf   VCF_subReC(  cfVector Y, cfVector X, ui size, float CRe );
void  __vf   VCF_subrReC( cfVector Y, cfVector X, ui size, float CRe );
void  __vf   VCF_mulReC(  cfVector Y, cfVector X, ui size, float CRe );
void  __vf   VCF_divReC(  cfVector Y, cfVector X, ui size, float CRe );
void  __vf   VCF_divrReC( cfVector Y, cfVector X, ui size, float CRe );

void  __vf   VCF_addV(  cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf   VCF_subV(  cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf   VCF_subrV( cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf   VCF_mulV(  cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf   VCF_divV(  cfVector Z, cfVector X, cfVector Y, ui size );
void  __vf   VCF_divrV( cfVector Z, cfVector X, cfVector Y, ui size );

void  __vf   VCF_addReV(  cfVector Z, cfVector X, fVector Y, ui size );
void  __vf   VCF_subReV(  cfVector Z, cfVector X, fVector Y, ui size );
void  __vf   VCF_subrReV( cfVector Z, cfVector X, fVector Y, ui size );
void  __vf   VCF_mulReV(  cfVector Z, cfVector X, fVector Y, ui size );
void  __vf   VCF_divReV(  cfVector Z, cfVector X, fVector Y, ui size );
void  __vf   VCF_divrReV( cfVector Z, cfVector X, fVector Y, ui size );

void  __vf   VCFx_addV(  cfVector Z, cfVector X, cfVector Y, ui size,
                         fComplex A, fComplex B );
void  __vf   VCFx_subV(  cfVector Z, cfVector X, cfVector Y, ui size,
                         fComplex A, fComplex B );
void  __vf   VCFx_subrV( cfVector Z, cfVector X, cfVector Y, ui size,
                         fComplex A, fComplex B );
void  __vf   VCFx_mulV(  cfVector Z, cfVector X, cfVector Y, ui size,
                         fComplex A, fComplex B );
void  __vf   VCFx_divV(  cfVector Z, cfVector X, cfVector Y, ui size,
                         fComplex A, fComplex B );
void  __vf   VCFx_divrV( cfVector Z, cfVector X, cfVector Y, ui size,
                         fComplex A, fComplex B );

void  __vf   VCFx_addReV(  cfVector Z, cfVector X, fVector Y, ui size,
                           fComplex A, fComplex B );
void  __vf   VCFx_subReV(  cfVector Z, cfVector X, fVector Y, ui size,
                           fComplex A, fComplex B );
void  __vf   VCFx_subrReV( cfVector Z, cfVector X, fVector Y, ui size,
                           fComplex A, fComplex B );
void  __vf   VCFx_mulReV(  cfVector Z, cfVector X, fVector Y, ui size,
                           fComplex A, fComplex B );
void  __vf   VCFx_divReV(  cfVector Z, cfVector X, fVector Y, ui size,
                           fComplex A, fComplex B );
void  __vf   VCFx_divrReV( cfVector Z, cfVector X, fVector Y, ui size,
                           fComplex A, fComplex B );

void __vf VCF_lincomb( cfVector Z, cfVector X, cfVector Y, ui size,
                       fComplex CX, fComplex CY );  /* Z[i]=CX*X[i]+CY*Y[i] */

/******************** Accumulation (Y += X) ******************************/

void __vf VCF_accV( cfVector Y, cfVector  X, ui size );


/*************** Functions of a sub-set of elements  ********************/

void  __vf  VCF_subvector_equC(  cfVector Y, ui subsiz, unsigned samp,
                                 fComplex C );
void  __vf  VCF_subvector_equV(  cfVector Y, ui subsiz, unsigned samp,
                                 cfVector X );

void  __vf  VCF_subvector_addC(  cfVector Y, ui subsiz, unsigned samp,
                                 fComplex C );
void  __vf  VCF_subvector_subC(  cfVector Y, ui subsiz, unsigned samp,
                                 fComplex C );
void  __vf  VCF_subvector_subrC( cfVector Y, ui subsiz, unsigned samp,
                                 fComplex C );
void  __vf  VCF_subvector_mulC(  cfVector Y, ui subsiz, unsigned samp,
                                 fComplex C );
void  __vf  VCF_subvector_divC(  cfVector Y, ui subsiz, unsigned samp,
                                 fComplex C );
void  __vf  VCF_subvector_divrC( cfVector Y, ui subsiz, unsigned samp,
                                 fComplex C );

void  __vf  VCF_subvector_addV(  cfVector Y, ui subsiz, unsigned samp,
                                 cfVector X );
void  __vf  VCF_subvector_subV(  cfVector Y, ui subsiz, unsigned samp,
                                 cfVector X );
void  __vf  VCF_subvector_subrV( cfVector Y, ui subsiz, unsigned samp,
                                 cfVector X );
void  __vf  VCF_subvector_mulV(  cfVector Y, ui subsiz, unsigned samp,
                                 cfVector X );
void  __vf  VCF_subvector_divV(  cfVector Y, ui subsiz, unsigned samp,
                                 cfVector X );
void  __vf  VCF_subvector_divrV( cfVector Y, ui subsiz, unsigned samp,
                                 cfVector X );


/*********************  Mathematical Functions *************************/

int   __vf   VCF_neg(  cfVector Y, cfVector X, ui size );
int   __vf   VCF_conj( cfVector Y, cfVector X, ui size );
int   __vf   VCF_abs(   fVector Y, cfVector X, ui size );
int   __vf   VCF_inv(  cfVector Y, cfVector X, ui size );
int   __vf   VCFx_inv( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B );

int  __vf   VCF_square(   cfVector Y, cfVector X, ui size );
int  __vf   VCFx_square(  cfVector Y, cfVector X, ui size,
                          fComplex A, fComplex B );
int  __vf   VCF_cubic(    cfVector Y, cfVector X, ui size );
int  __vf   VCFx_cubic(   cfVector Y, cfVector X, ui size,
                          fComplex A, fComplex B );
int  __vf   VCF_quartic(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_quartic( cfVector Y, cfVector X, ui size,
                          fComplex A, fComplex B );
int  __vf   VCF_ipow(     cfVector Y, cfVector X, ui size, int ipow );
int  __vf   VCFx_ipow(    cfVector Y, cfVector X, ui size, int ipow,
                          fComplex A, fComplex B, fComplex C );

       /* extra fast integer powers: "unprotected", without error handling: */
int  __vf   VCFu_square(   cfVector Y, cfVector X, ui size );
int  __vf   VCFux_square(  cfVector Y, cfVector X, ui size,
                           fComplex A, fComplex B );
int  __vf   VCFu_cubic(    cfVector Y, cfVector X, ui size );
int  __vf   VCFux_cubic(   cfVector Y, cfVector X, ui size,
                           fComplex A, fComplex B );
int  __vf   VCFu_quartic(  cfVector Y, cfVector X, ui size );
int  __vf   VCFux_quartic( cfVector Y, cfVector X, ui size,
                           fComplex A, fComplex B );
int  __vf   VCFu_ipow(     cfVector Y, cfVector X, ui size, int ipow );
int  __vf   VCFux_ipow(    cfVector Y, cfVector X, ui size, int ipow,
                           fComplex A, fComplex B, fComplex C );

int  __vf   VCF_pow(      cfVector Y, cfVector X, ui size, fComplex Expo );
int  __vf   VCFx_pow(     cfVector Y, cfVector X, ui size, fComplex Expo,
                          fComplex A, fComplex B, fComplex C );
int  __vf   VCF_powReExpo(  cfVector Y, cfVector X, ui size, float Expo );
int  __vf   VCFx_powReExpo( cfVector Y, cfVector X, ui size, float Expo,
                            fComplex A, fComplex B, fComplex C );

int  __vf   VCF_sqrt(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_sqrt( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );

int  __vf   VCF_log(   cfVector Y, cfVector X, ui size );
int  __vf   VCF_log2(  cfVector Y, cfVector X, ui size );
int  __vf   VCF_log10( cfVector Y, cfVector X, ui size );
#define     VCF_ln   VCF_log
int  __vf   VCFx_log(  cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );
int  __vf   VCFx_log2( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );
int  __vf   VCFx_log10( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );
#define     VCFx_ln    VCFx_log

int  __vf   VCF_exp(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_exp( cfVector Y, cfVector X, ui size,
                      fComplex A, fComplex B, fComplex C );
int  __vf   VCF_expArbBase(  cfVector Y, cfVector X, ui size, fComplex Base );
int  __vf   VCFx_expArbBase( cfVector Y, cfVector X, ui size, fComplex Base,
                             fComplex A, fComplex B, fComplex C );

int  __vf   VCF_sin(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_sin( cfVector Y, cfVector X, ui size,
                      fComplex A, fComplex B, fComplex C );
int  __vf   VCF_cos(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_cos( cfVector Y, cfVector X, ui size,
                      fComplex A, fComplex B, fComplex C );
int  __vf   VCF_tan(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_tan( cfVector Y, cfVector X, ui size,
                      fComplex A, fComplex B, fComplex C );

int  __vf   VCF_asin(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_asin( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );
int  __vf   VCF_acos(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_acos( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );
int  __vf   VCF_atan(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_atan( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );

int  __vf   VCF_sinh(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_sinh( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );
int  __vf   VCF_cosh(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_cosh( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );
int  __vf   VCF_tanh(  cfVector Y, cfVector X, ui size );
int  __vf   VCFx_tanh( cfVector Y, cfVector X, ui size,
                       fComplex A, fComplex B, fComplex C );


#ifdef __cplusplus
}
#endif


#endif /* __VCFMATH_H */
