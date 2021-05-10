/*  VCDmath.h

  vector management functions:
  math functions performed on each individual element of an
  array or vector of data type "dComplex" (complex double)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VCDMATH_H
#define __VCDMATH_H

#ifndef __VCDSTD_H 
#include <VCDstd.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/************************* Comparisons ****************************/

ui   __vf   VCD_cmp_eq0( cdVector Y, cdVector X, ui size );
ui   __vf   VCD_cmp_ne0( cdVector Y, cdVector X, ui size );
ui   __vf   VCD_cmp_eqC( cdVector Y, cdVector X, ui size, dComplex C );
ui   __vf   VCD_cmp_neC( cdVector Y, cdVector X, ui size, dComplex C );
ui   __vf   VCD_cmp_eqV( cdVector Z, cdVector X, cdVector Y, ui size );
ui   __vf   VCD_cmp_neV( cdVector Z, cdVector X, cdVector Y, ui size );
ui   __vf   VCD_cmp_eq0ind( uiVector Ind, cdVector X, ui size );
ui   __vf   VCD_cmp_ne0ind( uiVector Ind, cdVector X, ui size );
ui   __vf   VCD_cmp_eqCind( uiVector Ind, cdVector X, ui size, dComplex C );
ui   __vf   VCD_cmp_neCind( uiVector Ind, cdVector X, ui size, dComplex C );
ui   __vf   VCD_cmp_eqVind( uiVector Ind, cdVector X, cdVector Y, ui size );
ui   __vf   VCD_cmp_neVind( uiVector Ind, cdVector X, cdVector Y, ui size );


/********************  Standard Arithmetics   ***************************/

void  __vf   VCD_limit(  cdVector Y, cdVector X, ui size, dComplex Min,
                                                          dComplex Max );
void  __vf   VCD_flush0( cdVector Y, cdVector X, ui size, dComplex AbsMin );
void  __vf   VCD_flushInv( cdVector Y, cdVector X, ui size, dComplex AbsMin );

void  __vf   VCDx_equV( cdVector Y, cdVector X, ui size,
                        dComplex A, dComplex B );
void  __vf   VCD_addC(  cdVector Y, cdVector X, ui size, dComplex C );
void  __vf   VCD_subC(  cdVector Y, cdVector X, ui size, dComplex C );
void  __vf   VCD_subrC( cdVector Y, cdVector X, ui size, dComplex C );
void  __vf   VCD_mulC(  cdVector Y, cdVector X, ui size, dComplex C );
void  __vf   VCD_divC(  cdVector Y, cdVector X, ui size, dComplex C );
void  __vf   VCD_divrC( cdVector Y, cdVector X, ui size, dComplex C );
void  __vf   VCDx_divrC( cdVector Y, cdVector X, ui size,
                         dComplex A, dComplex B, dComplex C );

void  __vf   VCD_addReC(  cdVector Y, cdVector X, ui size, double CRe );
void  __vf   VCD_subReC(  cdVector Y, cdVector X, ui size, double CRe );
void  __vf   VCD_subrReC( cdVector Y, cdVector X, ui size, double CRe );
void  __vf   VCD_mulReC(  cdVector Y, cdVector X, ui size, double CRe );
void  __vf   VCD_divReC(  cdVector Y, cdVector X, ui size, double CRe );
void  __vf   VCD_divrReC( cdVector Y, cdVector X, ui size, double CRe );

void  __vf   VCD_addV(  cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf   VCD_subV(  cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf   VCD_subrV( cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf   VCD_mulV(  cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf   VCD_divV(  cdVector Z, cdVector X, cdVector Y, ui size );
void  __vf   VCD_divrV( cdVector Z, cdVector X, cdVector Y, ui size );

void  __vf   VCD_addReV(  cdVector Z, cdVector X, dVector Y, ui size );
void  __vf   VCD_subReV(  cdVector Z, cdVector X, dVector Y, ui size );
void  __vf   VCD_subrReV( cdVector Z, cdVector X, dVector Y, ui size );
void  __vf   VCD_mulReV(  cdVector Z, cdVector X, dVector Y, ui size );
void  __vf   VCD_divReV(  cdVector Z, cdVector X, dVector Y, ui size );
void  __vf   VCD_divrReV( cdVector Z, cdVector X, dVector Y, ui size );

void  __vf   VCDx_addV(  cdVector Z, cdVector X, cdVector Y, ui size,
                         dComplex A, dComplex B );
void  __vf   VCDx_subV(  cdVector Z, cdVector X, cdVector Y, ui size,
                         dComplex A, dComplex B );
void  __vf   VCDx_subrV( cdVector Z, cdVector X, cdVector Y, ui size,
                         dComplex A, dComplex B );
void  __vf   VCDx_mulV(  cdVector Z, cdVector X, cdVector Y, ui size,
                         dComplex A, dComplex B );
void  __vf   VCDx_divV(  cdVector Z, cdVector X, cdVector Y, ui size,
                         dComplex A, dComplex B );
void  __vf   VCDx_divrV( cdVector Z, cdVector X, cdVector Y, ui size,
                         dComplex A, dComplex B );

void  __vf   VCDx_addReV(  cdVector Z, cdVector X, dVector Y, ui size,
                           dComplex A, dComplex B );
void  __vf   VCDx_subReV(  cdVector Z, cdVector X, dVector Y, ui size,
                           dComplex A, dComplex B );
void  __vf   VCDx_subrReV( cdVector Z, cdVector X, dVector Y, ui size,
                           dComplex A, dComplex B );
void  __vf   VCDx_mulReV(  cdVector Z, cdVector X, dVector Y, ui size,
                           dComplex A, dComplex B );
void  __vf   VCDx_divReV(  cdVector Z, cdVector X, dVector Y, ui size,
                           dComplex A, dComplex B );
void  __vf   VCDx_divrReV( cdVector Z, cdVector X, dVector Y, ui size,
                           dComplex A, dComplex B );

void __vf VCD_lincomb( cdVector Z, cdVector X, cdVector Y, ui size,
                       dComplex CX, dComplex CY );  /* Z[i]=CX*X[i]+CY*Y[i] */

/******************** Accumulation (Y += X) ******************************/

void __vf VCD_accV(   cdVector Y, cdVector  X, ui size );
void __vf VCD_accVCF( cdVector Y, cfVector  X, ui size );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VCD_subvector_equC(  cdVector Y, ui subsiz, unsigned samp,
                                 dComplex C );
void  __vf  VCD_subvector_equV(  cdVector Y, ui subsiz, unsigned samp,
                                 cdVector X );

void  __vf  VCD_subvector_addC(  cdVector Y, ui subsiz, unsigned samp,
                                 dComplex C );
void  __vf  VCD_subvector_subC(  cdVector Y, ui subsiz, unsigned samp,
                                 dComplex C );
void  __vf  VCD_subvector_subrC( cdVector Y, ui subsiz, unsigned samp,
                                 dComplex C );
void  __vf  VCD_subvector_mulC(  cdVector Y, ui subsiz, unsigned samp,
                                 dComplex C );
void  __vf  VCD_subvector_divC(  cdVector Y, ui subsiz, unsigned samp,
                                 dComplex C );
void  __vf  VCD_subvector_divrC( cdVector Y, ui subsiz, unsigned samp,
                                 dComplex C );

void  __vf  VCD_subvector_addV(  cdVector Y, ui subsiz, unsigned samp,
                                 cdVector X );
void  __vf  VCD_subvector_subV(  cdVector Y, ui subsiz, unsigned samp,
                                 cdVector X );
void  __vf  VCD_subvector_subrV( cdVector Y, ui subsiz, unsigned samp,
                                 cdVector X );
void  __vf  VCD_subvector_mulV(  cdVector Y, ui subsiz, unsigned samp,
                                 cdVector X );
void  __vf  VCD_subvector_divV(  cdVector Y, ui subsiz, unsigned samp,
                                 cdVector X );
void  __vf  VCD_subvector_divrV( cdVector Y, ui subsiz, unsigned samp,
                                 cdVector X );


/********************  Mathematical Functions ***************************/

int __vf   VCD_neg(  cdVector Y, cdVector X, ui size );
int __vf   VCD_conj( cdVector Y, cdVector X, ui size );
int __vf   VCD_abs(   dVector Y, cdVector X, ui size );
int __vf   VCD_inv(  cdVector Y, cdVector X, ui size );
int __vf   VCDx_inv( cdVector Y, cdVector X, ui size, dComplex A, dComplex B );

int  __vf   VCD_square(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_square( cdVector Y, cdVector X, ui size,
                         dComplex A, dComplex B );
int  __vf   VCD_cubic(   cdVector Y, cdVector X, ui size );
int  __vf   VCDx_cubic(  cdVector Y, cdVector X, ui size,
                         dComplex A, dComplex B );
int  __vf   VCD_quartic( cdVector Y, cdVector X, ui size );
int  __vf   VCDx_quartic( cdVector Y, cdVector X, ui size,
                          dComplex A, dComplex B );
int  __vf   VCD_ipow(    cdVector Y, cdVector X, ui size, int ipow );
int  __vf   VCDx_ipow(   cdVector Y, cdVector X, ui size, int ipow,
                         dComplex A, dComplex B, dComplex C );

       /* extra fast integer powers: "unprotected", without error handling: */
int  __vf   VCDu_square(  cdVector Y, cdVector X, ui size );
int  __vf   VCDux_square( cdVector Y, cdVector X, ui size,
                          dComplex A, dComplex B );
int  __vf   VCDu_cubic(   cdVector Y, cdVector X, ui size );
int  __vf   VCDux_cubic(  cdVector Y, cdVector X, ui size,
                          dComplex A, dComplex B );
int  __vf   VCDu_quartic( cdVector Y, cdVector X, ui size );
int  __vf   VCDux_quartic( cdVector Y, cdVector X, ui size,
                           dComplex A, dComplex B );
int  __vf   VCDu_ipow(    cdVector Y, cdVector X, ui size, int ipow );
int  __vf   VCDux_ipow(   cdVector Y, cdVector X, ui size, int ipow,
                          dComplex A, dComplex B, dComplex C );

int  __vf   VCD_pow(     cdVector Y, cdVector X, ui size, dComplex Expo );
int  __vf   VCDx_pow(    cdVector Y, cdVector X, ui size,  dComplex Expo,
                         dComplex A, dComplex B, dComplex C );
int  __vf   VCD_powReExpo(  cdVector Y, cdVector X, ui size, double Expo );
int  __vf   VCDx_powReExpo( cdVector Y, cdVector X, ui size, double Expo,
                            dComplex A, dComplex B, dComplex C );

int  __vf   VCD_sqrt(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_sqrt( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );

int  __vf   VCD_log(   cdVector Y, cdVector X, ui size );
int  __vf   VCD_log2(  cdVector Y, cdVector X, ui size );
int  __vf   VCD_log10( cdVector Y, cdVector X, ui size );
#define     VCD_ln   VCD_log
int  __vf   VCDx_log(  cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );
int  __vf   VCDx_log2( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );
int  __vf   VCDx_log10( cdVector Y, cdVector X, ui size,
                        dComplex A, dComplex B, dComplex C );
#define     VCDx_ln    VCDx_log

int  __vf   VCD_exp(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_exp( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );
int  __vf   VCD_expArbBase(  cdVector Y, cdVector X, ui size, dComplex Base );
int  __vf   VCDx_expArbBase( cdVector Y, cdVector X, ui size, dComplex Base,
                             dComplex A, dComplex B, dComplex C );

int  __vf   VCD_sin(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_sin( cdVector Y, cdVector X, ui size,
                      dComplex A, dComplex B, dComplex C );
int  __vf   VCD_cos(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_cos( cdVector Y, cdVector X, ui size,
                      dComplex A, dComplex B, dComplex C );
int  __vf   VCD_tan(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_tan( cdVector Y, cdVector X, ui size,
                      dComplex A, dComplex B, dComplex C );

int  __vf   VCD_asin(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_asin( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );
int  __vf   VCD_acos(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_acos( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );
int  __vf   VCD_atan(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_atan( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );

int  __vf   VCD_sinh(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_sinh( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );
int  __vf   VCD_cosh(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_cosh( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );
int  __vf   VCD_tanh(  cdVector Y, cdVector X, ui size );
int  __vf   VCDx_tanh( cdVector Y, cdVector X, ui size,
                       dComplex A, dComplex B, dComplex C );


#ifdef __cplusplus
}
#endif


#endif /* __VCDMATH_H */
