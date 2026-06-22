/*  VDmath.h

  vector management functions:
  math functions performed on each individual element of an
  array or vector of the data type "double";   real numbers

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VDMATH_H
#define __VDMATH_H

#ifndef __VDSTD_H 
#include <VDstd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif



/**************************  Rounding **********************************/

int  __vf   VD_round(  dVector  Y, dVector X, ui size );
int  __vf   VD_roundtoBI( biVector Y, dVector X, ui size );
int  __vf   VD_roundtoSI( siVector Y, dVector X, ui size );
int  __vf   VD_roundtoI(  iVector  Y, dVector X, ui size );
int  __vf   VD_roundtoLI( liVector Y, dVector X, ui size );
int  __vf   VD_roundtoQI( qiVector Y, dVector X, ui size );
int  __vf   VD_roundtoUB( ubVector Y, dVector X, ui size );
int  __vf   VD_roundtoUS( usVector Y, dVector X, ui size );
int  __vf   VD_roundtoU(  uVector  Y, dVector X, ui size );
int  __vf   VD_roundtoUL( ulVector Y, dVector X, ui size );

int  __vf   VD_floor(  dVector  Y, dVector X, ui size );
int  __vf   VD_floortoBI( biVector Y, dVector X, ui size );
int  __vf   VD_floortoSI( siVector Y, dVector X, ui size );
int  __vf   VD_floortoI(  iVector  Y, dVector X, ui size );
int  __vf   VD_floortoLI( liVector Y, dVector X, ui size );
int  __vf   VD_floortoQI( qiVector Y, dVector X, ui size );
int  __vf   VD_floortoUB( ubVector Y, dVector X, ui size );
int  __vf   VD_floortoUS( usVector Y, dVector X, ui size );
int  __vf   VD_floortoU(  uVector  Y, dVector X, ui size );
int  __vf   VD_floortoUL( ulVector Y, dVector X, ui size );

int  __vf   VD_ceil(  dVector  Y, dVector X, ui size );
int  __vf   VD_ceiltoBI( biVector Y, dVector X, ui size );
int  __vf   VD_ceiltoSI( siVector Y, dVector X, ui size );
int  __vf   VD_ceiltoI(  iVector  Y, dVector X, ui size );
int  __vf   VD_ceiltoLI( liVector Y, dVector X, ui size );
int  __vf   VD_ceiltoQI( qiVector Y, dVector X, ui size );
int  __vf   VD_ceiltoUB( ubVector Y, dVector X, ui size );
int  __vf   VD_ceiltoUS( usVector Y, dVector X, ui size );
int  __vf   VD_ceiltoU(  uVector  Y, dVector X, ui size );
int  __vf   VD_ceiltoUL( ulVector Y, dVector X, ui size );

int  __vf   VD_chop(  dVector  Y, dVector X, ui size );
int  __vf   VD_choptoBI( biVector Y, dVector X, ui size );
int  __vf   VD_choptoSI( siVector Y, dVector X, ui size );
int  __vf   VD_choptoI(  iVector  Y, dVector X, ui size );
int  __vf   VD_choptoLI( liVector Y, dVector X, ui size );
int  __vf   VD_choptoQI( qiVector Y, dVector X, ui size );
int  __vf   VD_choptoUB( ubVector Y, dVector X, ui size );
int  __vf   VD_choptoUS( usVector Y, dVector X, ui size );
int  __vf   VD_choptoU(  uVector  Y, dVector X, ui size );
int  __vf   VD_choptoUL( ulVector Y, dVector X, ui size );

#define     VD_trunc      VD_chop
#define     VD_trunctoBI  VD_choptoBI
#define     VD_trunctoSI  VD_choptoSI
#define     VD_trunctoI   VD_choptoI
#define     VD_trunctoLI  VD_choptoLI
#define     VD_trunctoQI  VD_choptoQI
#define     VD_trunctoUB  VD_choptoUB
#define     VD_trunctoUS  VD_choptoUS
#define     VD_trunctoU   VD_choptoU
#define     VD_trunctoUL  VD_choptoUL

#if defined V_HUGE
      #define   VD_roundtoUI   VD_roundtoUL
      #define   VD_floortoUI   VD_floortoUL
      #define   VD_ceiltoUI    VD_ceiltoUL
      #define   VD_choptoUI    VD_choptoUL
      #define   VD_trunctoUI   VD_trunctoUL
#else
      #define   VD_roundtoUI   VD_roundtoU
      #define   VD_floortoUI   VD_floortoU
      #define   VD_ceiltoUI    VD_ceiltoU
      #define   VD_choptoUI    VD_choptoU
      #define   VD_trunctoUI   VD_trunctoU
#endif

/************************  Comparisons   ***************************/

void __vf   VD_cmp0(    dVector Y, dVector X, ui size );
ui   __vf   VD_cmp_eq0( dVector Y, dVector X, ui size );
ui   __vf   VD_cmp_ne0( dVector Y, dVector X, ui size );
ui   __vf   VD_cmp_le0( dVector Y, dVector X, ui size );
ui   __vf   VD_cmp_lt0( dVector Y, dVector X, ui size );
ui   __vf   VD_cmp_ge0( dVector Y, dVector X, ui size );
ui   __vf   VD_cmp_gt0( dVector Y, dVector X, ui size );

ui   __vf   VD_cmp_eq0ind( uiVector Ind, dVector X, ui size );
ui   __vf   VD_cmp_ne0ind( uiVector Ind, dVector X, ui size );
ui   __vf   VD_cmp_le0ind( uiVector Ind, dVector X, ui size );
ui   __vf   VD_cmp_lt0ind( uiVector Ind, dVector X, ui size );
ui   __vf   VD_cmp_ge0ind( uiVector Ind, dVector X, ui size );
ui   __vf   VD_cmp_gt0ind( uiVector Ind, dVector X, ui size );

void __vf   VD_cmpC(    dVector Y, dVector X, ui size, double C );
ui   __vf   VD_cmp_eqC( dVector Y, dVector X, ui size, double C );
ui   __vf   VD_cmp_neC( dVector Y, dVector X, ui size, double C );
ui   __vf   VD_cmp_leC( dVector Y, dVector X, ui size, double C );
ui   __vf   VD_cmp_ltC( dVector Y, dVector X, ui size, double C );
ui   __vf   VD_cmp_geC( dVector Y, dVector X, ui size, double C );
ui   __vf   VD_cmp_gtC( dVector Y, dVector X, ui size, double C );

ui   __vf   VD_cmp_eqCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf   VD_cmp_neCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf   VD_cmp_leCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf   VD_cmp_ltCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf   VD_cmp_geCind( uiVector Ind, dVector X, ui size, double C );
ui   __vf   VD_cmp_gtCind( uiVector Ind, dVector X, ui size, double C );

void __vf   VD_cmpV(    dVector Z, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_eqV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_neV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_leV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_ltV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_geV( dVector Z, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_gtV( dVector Z, dVector X, dVector Y, ui size );

ui   __vf   VD_cmp_eqVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_neVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_leVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_ltVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_geVind( uiVector Ind, dVector X, dVector Y, ui size );
ui   __vf   VD_cmp_gtVind( uiVector Ind, dVector X, dVector Y, ui size );

ui   __vf   VD_cmp_inclrange0C( dVector Y, dVector X, ui size, double C );
ui   __vf   VD_cmp_exclrange0C( dVector Y, dVector X, ui size, double C );
ui   __vf   VD_cmp_inclrangeCC( dVector Y, dVector X, ui size, double CLo, double CHi );
ui   __vf   VD_cmp_exclrangeCC( dVector Y, dVector X, ui size, double CLo, double CHi );

ui   __vf   VD_cmp_inclrange0Cind( uiVector Ind, dVector X, ui size, double C );
ui   __vf   VD_cmp_exclrange0Cind( uiVector Ind, dVector X, ui size, double C );
ui   __vf   VD_cmp_inclrangeCCind( uiVector Ind, dVector X, ui size, double CLo, double CHi );
ui   __vf   VD_cmp_exclrangeCCind( uiVector Ind, dVector X, ui size, double CLo, double CHi );


/********************  Standard Arithmetics   ***************************/

void  __vf  VD_equC( dVector X, ui size, double C );
void  __vf  VD_equV( dVector Y, dVector X, ui size );
void  __vf  VDx_equV( dVector Y, dVector X, ui size, double A, double B );

void  __vf  VD_addC(  dVector Y, dVector X, ui size, double C );
void  __vf  VD_subC(  dVector Y, dVector X, ui size, double C );
void  __vf  VD_subrC( dVector Y, dVector X, ui size, double C );
void  __vf  VD_mulC(  dVector Y, dVector X, ui size, double C );
void  __vf  VD_divC(  dVector Y, dVector X, ui size, double C );
void  __vf  VD_divrC( dVector Y, dVector X, ui size, double C );
void  __vf  VDx_divrC( dVector Y, dVector X, ui size, double A, double B, double C );

void  __vf  VD_addV(  dVector Z, dVector X, dVector Y, ui size );
void  __vf  VD_subV(  dVector Z, dVector X, dVector Y, ui size );
void  __vf  VD_subrV( dVector Z, dVector X, dVector Y, ui size );
void  __vf  VD_mulV(  dVector Z, dVector X, dVector Y, ui size );
void  __vf  VD_divV(  dVector Z, dVector X, dVector Y, ui size );
void  __vf  VD_divrV( dVector Z, dVector X, dVector Y, ui size );

void  __vf  VDx_addV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
                                  /* Z = (A*X+B) + Y */
void  __vf  VDx_subV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
void  __vf  VDx_subrV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
void  __vf  VDx_mulV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
void  __vf  VDx_divV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
void  __vf  VDx_divrV( dVector Z, dVector X, dVector Y, ui size, double A, double B );

void  __vf  VDs_addV(  dVector Z, dVector X, dVector Y, ui size, double C ); /* Z=C*(X+Y) */
void  __vf  VDs_subV(  dVector Z, dVector X, dVector Y, ui size, double C );
void  __vf  VDs_subrV( dVector Z, dVector X, dVector Y, ui size, double C );
void  __vf  VDs_mulV(  dVector Z, dVector X, dVector Y, ui size, double C );
void  __vf  VDs_divV(  dVector Z, dVector X, dVector Y, ui size, double C );
void  __vf  VDs_divrV( dVector Z, dVector X, dVector Y, ui size, double C );

void  __vf  VD_maxC(   dVector Y, dVector X, ui size, double C );
void  __vf  VD_minC(   dVector Y, dVector X, ui size, double C );
void  __vf  VD_limit(  dVector Y, dVector X, ui size, double Min, double Max );
void  __vf  VD_flush0( dVector Y, dVector X, ui size, double AbsMin );
void  __vf  VD_flushInv( dVector Y, dVector X, ui size, double AbsMin );
void  __vf  VD_maxV(   dVector Z, dVector X, dVector Y, ui size );
void  __vf  VD_minV(   dVector Z, dVector X, dVector Y, ui size );
void  __vf  VD_modC(   dVector Y, dVector X, ui size, double C );
void  __vf  VD_modV(   dVector Z, dVector X, dVector Y, ui size );
void  __vf  VDx_modV(  dVector Z, dVector X, dVector Y, ui size, double A, double B );
#define     VD_fmodC    VD_modC
#define     VD_fmodV    VD_modV
#define     VDx_fmodV   VDx_modV

void __vf  VD_redC(  dVector Y, dVector X, ui size, double C );
void __vf  VD_redV(  dVector Z, dVector X, dVector Y, ui size );
void __vf  VDx_redV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
void __vf  VD_visC(  dVector Y, dVector X, ui size, double C );
void __vf  VD_visV(  dVector Z, dVector X, dVector Y, ui size );
void __vf  VDx_visV( dVector Z, dVector X, dVector Y, ui size, double A, double B );
void __vf  VD_hypC(  dVector Y, dVector X, ui size, double C );
void __vf  VD_hypV(  dVector Z, dVector X, dVector Y, ui size );
void __vf  VDx_hypV( dVector Z, dVector X, dVector Y, ui size, double A, double B );

void __vf VD_lincomb( dVector Z, dVector X, dVector Y, ui size,
                      double CX, double CY );  /* Z[i]=CX*X[i]+CY*Y[i] */
#define    VD_sgn    VD_cmp0

/******************** Accumulation (Y += X) ******************************/

void __vf VD_accV(   dVector Y, dVector  X, ui size );
void __vf VD_accVF(  dVector Y, fVector  X, ui size );
void __vf VD_accVBI( dVector Y, biVector X, ui size );
void __vf VD_accVSI( dVector Y, siVector X, ui size );
void __vf VD_accVI(  dVector Y, iVector  X, ui size );
void __vf VD_accVLI( dVector Y, liVector X, ui size );
void __vf VD_accVQI( dVector Y, qiVector X, ui size );
void __vf VD_accVUB( dVector Y, ubVector X, ui size );
void __vf VD_accVUS( dVector Y, usVector X, ui size );
void __vf VD_accVU(  dVector Y, uVector  X, ui size );
void __vf VD_accVUL( dVector Y, ulVector X, ui size );
#if defined V_HUGE
    #define VD_accVUI  VD_accVUL
#else
    #define VD_accVUI  VD_accVU
#endif

/***************** Functions of a sub-set of elements  ********************/

void  __vf  VD_subvector_equC(  dVector Y, ui subsiz, unsigned samp, double C );
void  __vf  VD_subvector_equV(  dVector Y, ui subsiz, unsigned samp, dVector X );

void  __vf  VD_subvector_addC(  dVector Y, ui subsiz, unsigned samp, double C );
void  __vf  VD_subvector_subC(  dVector Y, ui subsiz, unsigned samp, double C );
void  __vf  VD_subvector_subrC( dVector Y, ui subsiz, unsigned samp, double C );
void  __vf  VD_subvector_mulC(  dVector Y, ui subsiz, unsigned samp, double C );
void  __vf  VD_subvector_divC(  dVector Y, ui subsiz, unsigned samp, double C );
void  __vf  VD_subvector_divrC( dVector Y, ui subsiz, unsigned samp, double C );

void  __vf  VD_subvector_addV(  dVector Y, ui subsiz, unsigned samp, dVector X );
void  __vf  VD_subvector_subV(  dVector Y, ui subsiz, unsigned samp, dVector X );
void  __vf  VD_subvector_subrV( dVector Y, ui subsiz, unsigned samp, dVector X );
void  __vf  VD_subvector_mulV(  dVector Y, ui subsiz, unsigned samp, dVector X );
void  __vf  VD_subvector_divV(  dVector Y, ui subsiz, unsigned samp, dVector X );
void  __vf  VD_subvector_divrV( dVector Y, ui subsiz, unsigned samp, dVector X );


/********************  Mathematical Functions **************************/

int   __vf   VD_abs( dVector Y, dVector X, ui size );
int   __vf   VD_neg( dVector Y, dVector X, ui size );
int   __vf   VD_inv( dVector Y, dVector X, ui size );
int   __vf   VDx_inv( dVector Y, dVector X, ui size, double A, double B );
int   __vf   VD_intfrac( dVector Int, dVector Frac, dVector X, ui size );
#define      VD_modf    VD_intfrac
int   __vf   VD_mantexp( dVector Mant, iVector Exp, dVector X, ui size );
#define      VD_frexp   VD_mantexp

int  __vf    VD_hypotC( dVector Y, dVector X, ui size, double C );
int  __vf    VD_hypotV( dVector Z, dVector X, dVector Y, ui size );
int  __vf    VDx_hypotV( dVector Z, dVector X, dVector Y, ui size, double A, double B );

int  __vf    VD_scale2( dVector Y, dVector X, ui size, int expo );
int  __vf    VD_scale10( dVector Y, dVector X, ui size, int expo );
#define      VD_ldexp    VD_scale2

int  __vf    VD_square( dVector Y, dVector X, ui size );
int  __vf    VDx_square( dVector Y, dVector X, ui size, double A, double B );
int  __vf    VD_cubic( dVector Y, dVector X, ui size );
int  __vf    VDx_cubic( dVector Y, dVector X, ui size, double A, double B );
int  __vf    VD_quartic( dVector Y, dVector X, ui size );
int  __vf    VDx_quartic( dVector Y, dVector X, ui size, double A, double B );
int  __vf    VD_poly( dVector Y, dVector X, ui size, dVector Coeff, unsigned deg );
int  __vf    VDx_poly( dVector Y, dVector X, ui size, dVector Coeff, unsigned deg, double A, double B );
int  __vf    VD_ipow( dVector Y, dVector X, ui size, int ipow );
int  __vf    VDx_ipow( dVector Y, dVector X, ui size, int ipow, double A, double B, double C );
                          /* ipow: integer powers of x */
        /* extra fast integer powers: "unprotected", without error handling: */
int  __vf    VDu_square( dVector Y, dVector X, ui size ); /* fast, unprotected version */
int  __vf    VDux_square( dVector Y, dVector X, ui size, double A, double B );
int  __vf    VDu_cubic( dVector Y, dVector X, ui size );
int  __vf    VDux_cubic( dVector Y, dVector X, ui size, double A, double B );
int  __vf    VDu_quartic( dVector Y, dVector X, ui size );
int  __vf    VDux_quartic( dVector Y, dVector X, ui size, double A, double B );
int  __vf    VDu_poly( dVector Y, dVector X, ui size, dVector Coeff, unsigned deg );
int  __vf    VDux_poly( dVector Y, dVector X, ui size, dVector Coeff, unsigned deg, double A, double B );
int  __vf    VDu_ipow( dVector Y, dVector X, ui size, int ipow );
int  __vf    VDux_ipow( dVector Y, dVector X, ui size, int ipow, double A, double B, double C );

int  __vf    VD_ipow2(  dVector Y, iVector X, ui size );
int  __vf    VD_ipow10( dVector Y, iVector X, ui size );
                          /* ipow2 and ipow10: integer powers of 2 and 10 */

int  __vf   VD_pow(    dVector Y, dVector X, ui size, double expo );
int  __vf   VDx_pow(   dVector Y, dVector X, ui size, double expo, double A, double B, double C );
int  __vf   VD_pow2(   dVector Y, dVector X, ui size );
int  __vf   VDx_pow2(  dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_pow10(  dVector Y, dVector X, ui size );
int  __vf   VDx_pow10( dVector Y, dVector X, ui size, double A, double B, double C );
                          /* pow2 and pow10: basis 2 or 10 raised to power x */

int  __vf   VD_sqrt(  dVector Y, dVector X, ui size );
int  __vf   VDx_sqrt( dVector Y, dVector X, ui size, double A, double B, double C );

int  __vf   VD_log(    dVector Y, dVector X, ui size );
int  __vf   VD_log2(   dVector Y, dVector X, ui size );
int  __vf   VD_log10(  dVector Y, dVector X, ui size );
#define     VD_ln    VD_log
int  __vf   VDx_log(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VDx_log2(  dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VDx_log10( dVector Y, dVector X, ui size, double A, double B, double C );
#define     VDx_ln   VDx_log

int  __vf   VD_OD( dVector OD, dVector X, dVector X0, ui size );  /* OD = log10( X0/X ) */
int  __vf   VD_ODwDark( dVector OD, dVector X, dVector XDark,
                        dVector X0, dVector X0Dark, ui size );
void __vf   VD_setODThresh( double minX, double minX0 );

int  __vf   VD_exp(   dVector Y, dVector X, ui size );
int  __vf   VDx_exp(  dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_expArbBase(  dVector Y, dVector X, ui size, double Base );
int  __vf   VDx_expArbBase( dVector Y, dVector X, ui size, double Base,
                            double A, double B, double C );
int  __vf   VD_expc(  dVector Y, dVector X, ui size );
int  __vf   VDx_expc( dVector Y, dVector X, ui size, double A, double B, double C );
                         /* expc(x) = 1 - exp(x) */
int  __vf   VD_exp2(  dVector Y, dVector X, ui size );
int  __vf   VDx_exp2( dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_exp10(  dVector Y, dVector X, ui size );
int  __vf   VDx_exp10( dVector Y, dVector X, ui size, double A, double B, double C );
                       /* exp2 and exp10 used as synonyms for pow2 and pow10 */
int  __vf   VD_expmx2(  dVector Y, dVector X, ui size );
int  __vf   VDx_expmx2( dVector Y, dVector X, ui size, double A, double B, double C );
                        /* expmx2(x) = exp( -x**2 ) */

int  __vf   VD_erf(     dVector Y, dVector X, ui size );
int  __vf   VDx_erf(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_erfc(    dVector Y, dVector X, ui size );
int  __vf   VDx_erfc(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_Gauss(   dVector Y, dVector X, ui size, double Wid, double Cent, double C );
#define VD_gauss  VD_Gauss
int  __vf   VD_Lorentz( dVector Y, dVector X, ui size, double Wid, double Cent, double C );
#define VD_lorentz VD_Lorentz

int  __vf   VD_sin(     dVector Y, dVector X, ui size );
int  __vf   VDx_sin(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_cos(     dVector Y, dVector X, ui size );
int  __vf   VDx_cos(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_sincos(  dVector Sin, dVector Cos, dVector X, ui size );
int  __vf   VDx_sincos( dVector Sin, dVector Cos, dVector X, ui size, double A, double B, double C );

int  __vf   VD_tan(     dVector Y, dVector X, ui size );
int  __vf   VDx_tan(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_cot(     dVector Y, dVector X, ui size );
int  __vf   VDx_cot(    dVector Y, dVector X, ui size, double A, double B, double C );

int  __vf   VD_sec(     dVector Y, dVector X, ui size );
int  __vf   VDx_sec(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_cosec(   dVector Y, dVector X, ui size );
int  __vf   VDx_cosec(  dVector Y, dVector X, ui size, double A, double B, double C );

int  __vf   VD_sin2(    dVector Y, dVector X, ui size );
int  __vf   VDx_sin2(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_cos2(    dVector Y, dVector X, ui size );
int  __vf   VDx_cos2(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_sincos2( dVector Sin, dVector Cos, dVector X, ui size );
int  __vf   VDx_sincos2( dVector Sin, dVector Cos, dVector X, ui size, double A, double B, double C );

int  __vf   VD_tan2(     dVector Y, dVector X, ui size );
int  __vf   VDx_tan2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_cot2(     dVector Y, dVector X, ui size );
int  __vf   VDx_cot2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_sec2(     dVector Y, dVector X, ui size );
int  __vf   VDx_sec2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_cosec2(   dVector Y, dVector X, ui size );
int  __vf   VDx_cosec2(  dVector Y, dVector X, ui size, double A, double B, double C );

 /*  reduced-range sine and cosine for -2Pi <= x <= +2Pi */
int  __vf   VDr_sin(     dVector Y, dVector X, ui size );
int  __vf   VDrx_sin(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VDr_cos(     dVector Y, dVector X, ui size );
int  __vf   VDrx_cos(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VDr_sincos(  dVector Sin, dVector Cos, dVector X, ui size );
int  __vf   VDrx_sincos( dVector Sin, dVector Cos, dVector X, ui size, double A, double B, double C );
int  __vf   VDr_sin2(     dVector Y, dVector X, ui size );
int  __vf   VDrx_sin2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VDr_cos2(     dVector Y, dVector X, ui size );
int  __vf   VDrx_cos2(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VDr_sincos2(  dVector Sin, dVector Cos, dVector X, ui size );
int  __vf   VDrx_sincos2( dVector Sin, dVector Cos, dVector X, ui size, double A, double B, double C );

/* trigonometric functions of rational multiples of Pi: x = p/q * Pi */
int  __vf   VD_sinrpi(   dVector Y, iVector P, ui size, int q );
int  __vf   VD_cosrpi(   dVector Y, iVector P, ui size, int q );
int  __vf   VD_sincosrpi( dVector Sin, dVector Cos, iVector P, ui size, int q );
int  __vf   VD_tanrpi(   dVector Y, iVector P, ui size, int q );
int  __vf   VD_cotrpi(   dVector Y, iVector P, ui size, int q );
int  __vf   VD_secrpi(   dVector Y, iVector P, ui size, int q );
int  __vf   VD_cosecrpi( dVector Y, iVector P, ui size, int q );

int  __vf   VD_sinrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_cosrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_sincosrpi2( dVector Sin, dVector Cos, iVector P, ui size, int q );
int  __vf   VD_tanrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_cotrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_secrpi2(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_cosecrpi2( dVector Y, iVector P, ui size, int q );

int  __vf   VD_sinrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_cosrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_sincosrpi3( dVector Sin, dVector Cos, iVector P, ui size, int q );
int  __vf   VD_tanrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_cotrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_secrpi3(  dVector Y, iVector P, ui size, int q );
int  __vf   VD_cosecrpi3( dVector Y, iVector P, ui size, int q );

int  __vf   VD_sinc(     dVector Y, dVector X, ui size );
int  __vf   VDx_sinc(    dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_Kepler(   dVector Y, dVector X, ui size, double T, double e );
int  __vf   VDx_Kepler(  dVector Y, dVector X, ui size, double T, double e,
                         double A, double B );
#define VD_kepler  VD_Kepler
#define VDx_kepler VDx_Kepler

int  __vf   VD_asin(    dVector Y, dVector X, ui size );
int  __vf   VDx_asin(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_acos(    dVector Y, dVector X, ui size );
int  __vf   VDx_acos(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_atan(    dVector Y, dVector X, ui size );
int  __vf   VDx_atan(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_atan2(   dVector Z, dVector X, dVector Y, ui size );
int  __vf   VDx_atan2(  dVector Z, dVector X, dVector Y, ui size, double A, double B, double C );

int  __vf   VD_sinh(    dVector Y, dVector X, ui size );
int  __vf   VDx_sinh(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_cosh(    dVector Y, dVector X, ui size );
int  __vf   VDx_cosh(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_tanh(    dVector Y, dVector X, ui size );
int  __vf   VDx_tanh(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_coth(    dVector Y, dVector X, ui size );
int  __vf   VDx_coth(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_sech(    dVector Y, dVector X, ui size );
int  __vf   VDx_sech(   dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_cosech(  dVector Y, dVector X, ui size );
int  __vf   VDx_cosech( dVector Y, dVector X, ui size, double A, double B, double C );
int  __vf   VD_sech2(   dVector Y, dVector X, ui size );
int  __vf   VDx_sech2(  dVector Y, dVector X, ui size, double A, double B, double C );


#ifdef __cplusplus
}
#endif


#endif /* __VDMATH_H */
