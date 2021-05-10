/*  VEmath.h

  vector management functions:
  math functions performed on each individual element of an
  array or vector of the data type "extended";   real numbers

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VEMATH_H
#define __VEMATH_H

#ifndef __VESTD_H 
#include <VEstd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __BORLANDC__   /* 80-bit IEEE numbers supported.
                         The following  330 lines apply 
                         only to Borland C++            */

/**************************  Rounding **********************************/

int  __vf   VE_round(  eVector  Y, eVector X, ui size );
int  __vf   VE_roundtoBI( biVector Y, eVector X, ui size );
int  __vf   VE_roundtoSI( siVector Y, eVector X, ui size );
int  __vf   VE_roundtoI(  iVector  Y, eVector X, ui size );
int  __vf   VE_roundtoLI( liVector Y, eVector X, ui size );
int  __vf   VE_roundtoQI( qiVector Y, eVector X, ui size );
int  __vf   VE_roundtoUB( ubVector Y, eVector X, ui size );
int  __vf   VE_roundtoUS( usVector Y, eVector X, ui size );
int  __vf   VE_roundtoU(  uVector  Y, eVector X, ui size );
int  __vf   VE_roundtoUL( ulVector Y, eVector X, ui size );

int  __vf   VE_floor(  eVector  Y, eVector X, ui size );
int  __vf   VE_floortoBI( biVector Y, eVector X, ui size );
int  __vf   VE_floortoSI( siVector Y, eVector X, ui size );
int  __vf   VE_floortoI(  iVector  Y, eVector X, ui size );
int  __vf   VE_floortoLI( liVector Y, eVector X, ui size );
int  __vf   VE_floortoQI( qiVector Y, eVector X, ui size );
int  __vf   VE_floortoUB( ubVector Y, eVector X, ui size );
int  __vf   VE_floortoUS( usVector Y, eVector X, ui size );
int  __vf   VE_floortoU(  uVector  Y, eVector X, ui size );
int  __vf   VE_floortoUL( ulVector Y, eVector X, ui size );

int  __vf   VE_ceil(  eVector  Y, eVector X, ui size );
int  __vf   VE_ceiltoBI( biVector Y, eVector X, ui size );
int  __vf   VE_ceiltoSI( siVector Y, eVector X, ui size );
int  __vf   VE_ceiltoI(  iVector  Y, eVector X, ui size );
int  __vf   VE_ceiltoLI( liVector Y, eVector X, ui size );
int  __vf   VE_ceiltoQI( qiVector Y, eVector X, ui size );
int  __vf   VE_ceiltoUB( ubVector Y, eVector X, ui size );
int  __vf   VE_ceiltoUS( usVector Y, eVector X, ui size );
int  __vf   VE_ceiltoU(  uVector  Y, eVector X, ui size );
int  __vf   VE_ceiltoUL( ulVector Y, eVector X, ui size );

int  __vf   VE_chop(  eVector  Y, eVector X, ui size );
int  __vf   VE_choptoBI( biVector Y, eVector X, ui size );
int  __vf   VE_choptoSI( siVector Y, eVector X, ui size );
int  __vf   VE_choptoI(  iVector  Y, eVector X, ui size );
int  __vf   VE_choptoLI( liVector Y, eVector X, ui size );
int  __vf   VE_choptoQI( qiVector Y, eVector X, ui size );
int  __vf   VE_choptoUB( ubVector Y, eVector X, ui size );
int  __vf   VE_choptoUS( usVector Y, eVector X, ui size );
int  __vf   VE_choptoU(  uVector  Y, eVector X, ui size );
int  __vf   VE_choptoUL( ulVector Y, eVector X, ui size );

#define     VE_trunc      VE_chop
#define     VE_trunctoBI  VE_choptoBI
#define     VE_trunctoSI  VE_choptoSI
#define     VE_trunctoI   VE_choptoI
#define     VE_trunctoLI  VE_choptoLI
#define     VE_trunctoQI  VE_choptoQI
#define     VE_trunctoUB  VE_choptoUB
#define     VE_trunctoUS  VE_choptoUS
#define     VE_trunctoU   VE_choptoU
#define     VE_trunctoUL  VE_choptoUL

#if defined V_HUGE
      #define   VE_roundtoUI   VE_roundtoUL
      #define   VE_floortoUI   VE_floortoUL
      #define   VE_ceiltoUI    VE_ceiltoUL
      #define   VE_choptoUI    VE_choptoUL
      #define   VE_trunctoUI   VE_trunctoUL
#else
      #define   VE_roundtoUI   VE_roundtoU
      #define   VE_floortoUI   VE_floortoU
      #define   VE_ceiltoUI    VE_ceiltoU
      #define   VE_choptoUI    VE_choptoU
      #define   VE_trunctoUI   VE_trunctoU
#endif

/********************  Comparisons   ********************/

void __vf   VE_cmp0(    eVector Y, eVector X, ui size );
ui   __vf   VE_cmp_eq0( eVector Y, eVector X, ui size );
ui   __vf   VE_cmp_ne0( eVector Y, eVector X, ui size );
ui   __vf   VE_cmp_le0( eVector Y, eVector X, ui size );
ui   __vf   VE_cmp_lt0( eVector Y, eVector X, ui size );
ui   __vf   VE_cmp_ge0( eVector Y, eVector X, ui size );
ui   __vf   VE_cmp_gt0( eVector Y, eVector X, ui size );

ui   __vf   VE_cmp_eq0ind( uiVector Ind, eVector X, ui size );
ui   __vf   VE_cmp_ne0ind( uiVector Ind, eVector X, ui size );
ui   __vf   VE_cmp_le0ind( uiVector Ind, eVector X, ui size );
ui   __vf   VE_cmp_lt0ind( uiVector Ind, eVector X, ui size );
ui   __vf   VE_cmp_ge0ind( uiVector Ind, eVector X, ui size );
ui   __vf   VE_cmp_gt0ind( uiVector Ind, eVector X, ui size );

void __vf   VE_cmpC(    eVector Y, eVector X, ui size, extended C );
ui   __vf   VE_cmp_eqC( eVector Y, eVector X, ui size, extended C );
ui   __vf   VE_cmp_neC( eVector Y, eVector X, ui size, extended C );
ui   __vf   VE_cmp_leC( eVector Y, eVector X, ui size, extended C );
ui   __vf   VE_cmp_ltC( eVector Y, eVector X, ui size, extended C );
ui   __vf   VE_cmp_geC( eVector Y, eVector X, ui size, extended C );
ui   __vf   VE_cmp_gtC( eVector Y, eVector X, ui size, extended C );

ui   __vf   VE_cmp_eqCind( uiVector Ind, eVector X, ui size, extended C );
ui   __vf   VE_cmp_neCind( uiVector Ind, eVector X, ui size, extended C );
ui   __vf   VE_cmp_leCind( uiVector Ind, eVector X, ui size, extended C );
ui   __vf   VE_cmp_ltCind( uiVector Ind, eVector X, ui size, extended C );
ui   __vf   VE_cmp_geCind( uiVector Ind, eVector X, ui size, extended C );
ui   __vf   VE_cmp_gtCind( uiVector Ind, eVector X, ui size, extended C );

void __vf   VE_cmpV(    eVector Z, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_eqV( eVector Z, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_neV( eVector Z, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_leV( eVector Z, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_ltV( eVector Z, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_geV( eVector Z, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_gtV( eVector Z, eVector X, eVector Y, ui size );

ui   __vf   VE_cmp_eqVind( uiVector Ind, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_neVind( uiVector Ind, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_leVind( uiVector Ind, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_ltVind( uiVector Ind, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_geVind( uiVector Ind, eVector X, eVector Y, ui size );
ui   __vf   VE_cmp_gtVind( uiVector Ind, eVector X, eVector Y, ui size );

ui   __vf   VE_cmp_inclrange0C( eVector Y, eVector X, ui size, extended C );
ui   __vf   VE_cmp_exclrange0C( eVector Y, eVector X, ui size, extended C );
ui   __vf   VE_cmp_inclrangeCC( eVector Y, eVector X, ui size, extended CLo, extended CHi );
ui   __vf   VE_cmp_exclrangeCC( eVector Y, eVector X, ui size, extended CLo, extended CHi );

ui   __vf   VE_cmp_inclrange0Cind( uiVector Ind, eVector X, ui size, extended C );
ui   __vf   VE_cmp_exclrange0Cind( uiVector Ind, eVector X, ui size, extended C );
ui   __vf   VE_cmp_inclrangeCCind( uiVector Ind, eVector X, ui size, extended CLo, extended CHi );
ui   __vf   VE_cmp_exclrangeCCind( uiVector Ind, eVector X, ui size, extended CLo, extended CHi );


/********************  Standard Arithmetics   ***************************/

void  __vf  VE_equC( eVector X, ui size, extended C );
void  __vf  VE_equV( eVector Y, eVector X, ui size );
void  __vf  VEx_equV( eVector Y, eVector X, ui size, extended A, extended B );

void  __vf  VE_addC(  eVector Y, eVector X, ui size, extended C );
void  __vf  VE_subC(  eVector Y, eVector X, ui size, extended C );
void  __vf  VE_subrC( eVector Y, eVector X, ui size, extended C );
void  __vf  VE_mulC(  eVector Y, eVector X, ui size, extended C );
void  __vf  VE_divC(  eVector Y, eVector X, ui size, extended C );
void  __vf  VE_divrC( eVector Y, eVector X, ui size, extended C );
void  __vf  VEx_divrC( eVector Y, eVector X, ui size, extended A, extended B, extended C );

void  __vf  VE_addV(  eVector Z, eVector X, eVector Y, ui size );
void  __vf  VE_subV(  eVector Z, eVector X, eVector Y, ui size );
void  __vf  VE_subrV( eVector Z, eVector X, eVector Y, ui size );
void  __vf  VE_mulV(  eVector Z, eVector X, eVector Y, ui size );
void  __vf  VE_divV(  eVector Z, eVector X, eVector Y, ui size );
void  __vf  VE_divrV( eVector Z, eVector X, eVector Y, ui size );

void  __vf  VEx_addV(  eVector Z, eVector X, eVector Y, ui size, extended A, extended B );
                                 /* Z = (A*X+B) + Y */
void  __vf  VEx_subV(  eVector Z, eVector X, eVector Y, ui size, extended A, extended B );
void  __vf  VEx_subrV( eVector Z, eVector X, eVector Y, ui size, extended A, extended B );
void  __vf  VEx_mulV(  eVector Z, eVector X, eVector Y, ui size, extended A, extended B );
void  __vf  VEx_divV(  eVector Z, eVector X, eVector Y, ui size, extended A, extended B );
void  __vf  VEx_divrV( eVector Z, eVector X, eVector Y, ui size, extended A, extended B );

void  __vf  VEs_addV(  eVector Z, eVector X, eVector Y, ui size, extended C ); /* Z=C*(X+Y) */
void  __vf  VEs_subV(  eVector Z, eVector X, eVector Y, ui size, extended C );
void  __vf  VEs_subrV( eVector Z, eVector X, eVector Y, ui size, extended C );
void  __vf  VEs_mulV(  eVector Z, eVector X, eVector Y, ui size, extended C );
void  __vf  VEs_divV(  eVector Z, eVector X, eVector Y, ui size, extended C );
void  __vf  VEs_divrV( eVector Z, eVector X, eVector Y, ui size, extended C );

void  __vf  VE_maxC(   eVector Y, eVector X, ui size, extended C );
void  __vf  VE_minC(   eVector Y, eVector X, ui size, extended C );
void  __vf  VE_limit(  eVector Y, eVector X, ui size, extended Min, extended Max );
void  __vf  VE_flush0( eVector Y, eVector X, ui size, extended AbsMin );
void  __vf  VE_flushInv( eVector Y, eVector X, ui size, extended AbsMin );
void  __vf  VE_maxV(   eVector Z, eVector X, eVector Y, ui size );
void  __vf  VE_minV(   eVector Z, eVector X, eVector Y, ui size );
void  __vf  VE_modC(   eVector Y, eVector X, ui size, extended C );
void  __vf  VE_modV(   eVector Z, eVector X, eVector Y, ui size );
void  __vf  VEx_modV(  eVector Z, eVector X, eVector Y, ui size, extended A, extended B );
#define     VE_fmodC    VE_modC
#define     VE_fmodV    VE_modV
#define     VEx_fmodV   VEx_modV

void __vf  VE_redC(  eVector Y, eVector X, ui size, extended C );
void __vf  VE_redV(  eVector Z, eVector X, eVector Y, ui size );
void __vf  VEx_redV( eVector Z, eVector X, eVector Y, ui size, extended A, extended B );
void __vf  VE_visC(  eVector Y, eVector X, ui size, extended C );
void __vf  VE_visV(  eVector Z, eVector X, eVector Y, ui size );
void __vf  VEx_visV( eVector Z, eVector X, eVector Y, ui size, extended A, extended B );
void __vf  VE_hypC(  eVector Y, eVector X, ui size, extended C );
void __vf  VE_hypV(  eVector Z, eVector X, eVector Y, ui size );
void __vf  VEx_hypV( eVector Z, eVector X, eVector Y, ui size, extended A, extended B );

void __vf VE_lincomb( eVector Z, eVector X, eVector Y, ui size,
                      extended CX, extended CY );  /* Z[i]=CX*X[i]+CY*Y[i] */

#define    VE_sgn    VE_cmp0

/******************** Accumulation (Y += X) ******************************/

void __vf VE_accV(   eVector Y, eVector  X, ui size );
void __vf VE_accVF(  eVector Y, fVector  X, ui size );
void __vf VE_accVD(  eVector Y, dVector  X, ui size );
void __vf VE_accVBI( eVector Y, biVector X, ui size );
void __vf VE_accVSI( eVector Y, siVector X, ui size );
void __vf VE_accVI(  eVector Y, iVector  X, ui size );
void __vf VE_accVLI( eVector Y, liVector X, ui size );
void __vf VE_accVQI( eVector Y, qiVector X, ui size );
void __vf VE_accVUB( eVector Y, ubVector X, ui size );
void __vf VE_accVUS( eVector Y, usVector X, ui size );
void __vf VE_accVU(  eVector Y, uVector  X, ui size );
void __vf VE_accVUL( eVector Y, ulVector X, ui size );
#if defined V_HUGE
    #define VE_accVUI  VE_accVUL
#else
    #define VE_accVUI  VE_accVU
#endif

/***************** Functions of a sub-set of elements  ********************/

void  __vf  VE_subvector_equC(  eVector Y, ui subsiz, unsigned samp, extended C );
void  __vf  VE_subvector_equV(  eVector Y, ui subsiz, unsigned samp, eVector X );

void  __vf  VE_subvector_addC(  eVector Y, ui subsiz, unsigned samp, extended C );
void  __vf  VE_subvector_subC(  eVector Y, ui subsiz, unsigned samp, extended C );
void  __vf  VE_subvector_subrC( eVector Y, ui subsiz, unsigned samp, extended C );
void  __vf  VE_subvector_mulC(  eVector Y, ui subsiz, unsigned samp, extended C );
void  __vf  VE_subvector_divC(  eVector Y, ui subsiz, unsigned samp, extended C );
void  __vf  VE_subvector_divrC( eVector Y, ui subsiz, unsigned samp, extended C );

void  __vf  VE_subvector_addV(  eVector Y, ui subsiz, unsigned samp, eVector X );
void  __vf  VE_subvector_subV(  eVector Y, ui subsiz, unsigned samp, eVector X );
void  __vf  VE_subvector_subrV( eVector Y, ui subsiz, unsigned samp, eVector X );
void  __vf  VE_subvector_mulV(  eVector Y, ui subsiz, unsigned samp, eVector X );
void  __vf  VE_subvector_divV(  eVector Y, ui subsiz, unsigned samp, eVector X );
void  __vf  VE_subvector_divrV( eVector Y, ui subsiz, unsigned samp, eVector X );


/**********************  Mathematical Functions ***********************/

int   __vf   VE_abs( eVector Y, eVector X, ui size );
int   __vf   VE_neg( eVector Y, eVector X, ui size );
int   __vf   VE_inv( eVector Y, eVector X, ui size );
int   __vf   VEx_inv( eVector Y, eVector X, ui size, extended A, extended B );
int   __vf   VE_intfrac( eVector Int, eVector Frac, eVector X, ui size );
#define      VE_modf    VE_intfrac
int   __vf   VE_mantexp( eVector Mant, iVector Exp, eVector X, ui size );
#define      VE_frexp   VE_mantexp

int  __vf    VE_hypotC( eVector Y, eVector X, ui size, extended C );
int  __vf    VE_hypotV( eVector Z, eVector X, eVector Y, ui size );
int  __vf    VEx_hypotV( eVector Z, eVector X, eVector Y, ui size, extended A, extended B );

int  __vf    VE_scale2( eVector Y, eVector X, ui size, int expo );
int  __vf    VE_scale10( eVector Y, eVector X, ui size, int expo );
#define      VE_ldexp    VE_scale2

int  __vf    VE_square( eVector Y, eVector X, ui size );
int  __vf    VEx_square( eVector Y, eVector X, ui size, extended A, extended B );
int  __vf    VE_cubic( eVector Y, eVector X, ui size );
int  __vf    VEx_cubic( eVector Y, eVector X, ui size, extended A, extended B );
int  __vf    VE_quartic( eVector Y, eVector X, ui size );
int  __vf    VEx_quartic( eVector Y, eVector X, ui size, extended A, extended B );
int  __vf    VE_poly( eVector Y, eVector X, ui size, eVector Coeff, unsigned deg );
int  __vf    VEx_poly( eVector Y, eVector X, ui size, eVector Coeff, unsigned deg, extended A, extended B );
int  __vf    VE_ipow( eVector Y, eVector X, ui size, int ipow );
int  __vf    VEx_ipow( eVector Y, eVector X, ui size, int ipow, extended A, extended B, extended C );
                          /* ipow: integer powers of x */

         /* extra fast powers: "unprotected", without error handling: */
int  __vf    VEu_square( eVector Y, eVector X, ui size ); /* fast, unprotected versions */
int  __vf    VEux_square( eVector Y, eVector X, ui size, extended A, extended B );
int  __vf    VEu_cubic( eVector Y, eVector X, ui size );
int  __vf    VEux_cubic( eVector Y, eVector X, ui size, extended A, extended B );
int  __vf    VEu_quartic( eVector Y, eVector X, ui size );
int  __vf    VEux_quartic( eVector Y, eVector X, ui size, extended A, extended B );
int  __vf    VEu_poly( eVector Y, eVector X, ui size, eVector Coeff, unsigned deg );
int  __vf    VEux_poly( eVector Y, eVector X, ui size, eVector Coeff, unsigned deg, extended A, extended B );
int  __vf    VEu_ipow( eVector Y, eVector X, ui size, int ipow );
int  __vf    VEux_ipow( eVector Y, eVector X, ui size, int ipow, extended A, extended B, extended C );

int  __vf    VE_ipow2(  eVector Y, iVector X, ui size );
int  __vf    VE_ipow10( eVector Y, iVector X, ui size );
                          /* ipow2 and ipow10: integer powers of 2 and 10 */

int  __vf   VE_pow(    eVector Y, eVector X, ui size, extended expo );
int  __vf   VEx_pow(   eVector Y, eVector X, ui size, extended expo, extended A, extended B, extended C );
int  __vf   VE_pow2(   eVector Y, eVector X, ui size );
int  __vf   VEx_pow2(  eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_pow10(  eVector Y, eVector X, ui size );
int  __vf   VEx_pow10( eVector Y, eVector X, ui size, extended A, extended B, extended C );
                          /* pow2 and pow10: powers of 2 and 10 */

int  __vf   VE_sqrt(  eVector Y, eVector X, ui size );
int  __vf   VEx_sqrt( eVector Y, eVector X, ui size, extended A, extended B, extended C );

int  __vf   VE_log(    eVector Y, eVector X, ui size );
int  __vf   VE_log2(   eVector Y, eVector X, ui size );
int  __vf   VE_log10(  eVector Y, eVector X, ui size );
#define     VE_ln    VE_log
int  __vf   VEx_log(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VEx_log2(  eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VEx_log10( eVector Y, eVector X, ui size, extended A, extended B, extended C );
#define     VEx_ln   VEx_log

int  __vf   VE_OD( eVector OD, eVector X, eVector X0, ui size );  /* OD = log10( X0/X ) */
int  __vf   VE_ODwDark( eVector OD, eVector X, eVector XDark,
                        eVector X0, eVector X0Dark, ui size );
void __vf   VE_setODThresh( extended minX, extended minX0 );

int  __vf   VE_exp(   eVector Y, eVector X, ui size );
int  __vf   VEx_exp(  eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_expArbBase(  eVector Y, eVector X, ui size, extended Base );
int  __vf   VEx_expArbBase( eVector Y, eVector X, ui size, extended Base,
                            extended A, extended B, extended C );
int  __vf   VE_expc(  eVector Y, eVector X, ui size );
int  __vf   VEx_expc( eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_exp2(  eVector Y, eVector X, ui size );
int  __vf   VEx_exp2( eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_exp2(  eVector Y, eVector X, ui size );
int  __vf   VEx_exp2( eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_exp10(  eVector Y, eVector X, ui size );
int  __vf   VEx_exp10( eVector Y, eVector X, ui size, extended A, extended B, extended C );
                       /* exp2 and exp10 used as synonyms for pow2 and pow10 */
int  __vf   VE_expmx2(  eVector Y, eVector X, ui size );
int  __vf   VEx_expmx2( eVector Y, eVector X, ui size, extended A, extended B, extended C );
                        /* expmx2(x) = exp( -x**2 ) */

int  __vf   VE_erf(     eVector Y, eVector X, ui size );
int  __vf   VEx_erf(    eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_erfc(    eVector Y, eVector X, ui size );
int  __vf   VEx_erfc(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_Gauss(   eVector Y, eVector X, ui size, extended Wid, extended Cent, extended C );
int  __vf   VE_Lorentz( eVector Y, eVector X, ui size, extended Wid, extended Cent, extended C );

int  __vf   VE_sin(     eVector Y, eVector X, ui size );
int  __vf   VEx_sin(    eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_cos(     eVector Y, eVector X, ui size );
int  __vf   VEx_cos(    eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_sincos(  eVector Sin, eVector Cos, eVector X, ui size );
int  __vf   VEx_sincos( eVector Sin, eVector Cos, eVector X, ui size, extended A, extended B, extended C );

int  __vf   VE_tan(     eVector Y, eVector X, ui size );
int  __vf   VEx_tan(    eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_cot(     eVector Y, eVector X, ui size );
int  __vf   VEx_cot(    eVector Y, eVector X, ui size, extended A, extended B, extended C );

int  __vf   VE_sec(     eVector Y, eVector X, ui size );
int  __vf   VEx_sec(    eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_cosec(   eVector Y, eVector X, ui size );
int  __vf   VEx_cosec(  eVector Y, eVector X, ui size, extended A, extended B, extended C );

int  __vf   VE_sin2(    eVector Y, eVector X, ui size );
int  __vf   VEx_sin2(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_cos2(    eVector Y, eVector X, ui size );
int  __vf   VEx_cos2(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_sincos2( eVector Sin, eVector Cos, eVector X, ui size );
int  __vf   VEx_sincos2( eVector Sin, eVector Cos, eVector X, ui size, extended A, extended B, extended C );

int  __vf   VE_tan2(     eVector Y, eVector X, ui size );
int  __vf   VEx_tan2(    eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_cot2(     eVector Y, eVector X, ui size );
int  __vf   VEx_cot2(    eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_sec2(     eVector Y, eVector X, ui size );
int  __vf   VEx_sec2(    eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_cosec2(   eVector Y, eVector X, ui size );
int  __vf   VEx_cosec2(  eVector Y, eVector X, ui size, extended A, extended B, extended C );

 /*  reduced-range sine and cosine for -2Pi <= x <= +2Pi */
int  __vf   VEr_sin(    eVector Y, eVector X, ui size );
int  __vf   VErx_sin(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VEr_cos(    eVector Y, eVector X, ui size );
int  __vf   VErx_cos(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VEr_sincos( eVector Sin, eVector Cos, eVector X, ui size );
int  __vf   VErx_sincos( eVector Sin, eVector Cos, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VEr_sin2(    eVector Y, eVector X, ui size );
int  __vf   VErx_sin2(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VEr_cos2(    eVector Y, eVector X, ui size );
int  __vf   VErx_cos2(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VEr_sincos2( eVector Sin, eVector Cos, eVector X, ui size );
int  __vf   VErx_sincos2( eVector Sin, eVector Cos, eVector X, ui size, extended A, extended B, extended C );

/* trigonometric functions of rational multiples of Pi: x = p/q * Pi */
int  __vf   VE_sinrpi(   eVector Y, iVector P, ui size, int q );
int  __vf   VE_cosrpi(   eVector Y, iVector P, ui size, int q );
int  __vf   VE_sincosrpi( eVector Sin, eVector Cos, iVector P, ui size, int q );
int  __vf   VE_tanrpi(   eVector Y, iVector P, ui size, int q );
int  __vf   VE_cotrpi(   eVector Y, iVector P, ui size, int q );
int  __vf   VE_secrpi(   eVector Y, iVector P, ui size, int q );
int  __vf   VE_cosecrpi( eVector Y, iVector P, ui size, int q );

int  __vf   VE_sinrpi2(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_cosrpi2(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_sincosrpi2( eVector Sin, eVector Cos, iVector P, ui size, int q );
int  __vf   VE_tanrpi2(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_cotrpi2(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_secrpi2(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_cosecrpi2( eVector Y, iVector P, ui size, int q );

int  __vf   VE_sinrpi3(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_cosrpi3(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_sincosrpi3( eVector Sin, eVector Cos, iVector P, ui size, int q );
int  __vf   VE_tanrpi3(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_cotrpi3(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_secrpi3(  eVector Y, iVector P, ui size, int q );
int  __vf   VE_cosecrpi3( eVector Y, iVector P, ui size, int q );

int  __vf   VE_sinc(     eVector Y, eVector X, ui size );
int  __vf   VEx_sinc(    eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_Kepler(   eVector Y, eVector X, ui size, long double T, long double e );
int  __vf   VEx_Kepler(  eVector Y, eVector X, ui size, long double T, long double e,
                         long double A, long double B );

int  __vf   VE_asin(    eVector Y, eVector X, ui size );
int  __vf   VEx_asin(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_acos(    eVector Y, eVector X, ui size );
int  __vf   VEx_acos(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_atan(    eVector Y, eVector X, ui size );
int  __vf   VEx_atan(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_atan2(   eVector Z, eVector X, eVector Y, ui size );
int  __vf   VEx_atan2(  eVector Z, eVector X, eVector Y, ui size, extended A, extended B, extended C );

int  __vf   VE_sinh(    eVector Y, eVector X, ui size );
int  __vf   VEx_sinh(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_cosh(    eVector Y, eVector X, ui size );
int  __vf   VEx_cosh(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_tanh(    eVector Y, eVector X, ui size );
int  __vf   VEx_tanh(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_coth(    eVector Y, eVector X, ui size );
int  __vf   VEx_coth(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_sech(    eVector Y, eVector X, ui size );
int  __vf   VEx_sech(   eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_cosech(  eVector Y, eVector X, ui size );
int  __vf   VEx_cosech( eVector Y, eVector X, ui size, extended A, extended B, extended C );
int  __vf   VE_sech2(   eVector Y, eVector X, ui size );
int  __vf   VEx_sech2(  eVector Y, eVector X, ui size, extended A, extended B, extended C );


#else   /* no 80-bit IEEE number support with Visual C++:
           the following 340 lines apply only to Visual C++  */

#define VE_round        VD_round
#define VE_roundtoSI    VD_roundtoSI
#define VE_roundtoI     VD_roundtoI
#define VE_roundtoLI    VD_roundtoLI
#define VE_roundtoQI    VD_roundtoQI
#define VE_roundtoUS    VD_roundtoUS
#define VE_roundtoU     VD_roundtoU
#define VE_roundtoUL    VD_roundtoUL

#define VE_floor        VD_floor
#define VE_floortoSI    VD_floortoSI
#define VE_floortoI     VD_floortoI
#define VE_floortoLI    VD_floortoLI
#define VE_floortoQI    VD_floortoQI
#define VE_floortoUS    VD_floortoUS
#define VE_floortoU     VD_floortoU
#define VE_floortoUL    VD_floortoUL

#define VE_ceil        VD_ceil
#define VE_ceiltoSI    VD_ceiltoSI
#define VE_ceiltoI     VD_ceiltoI
#define VE_ceiltoLI    VD_ceiltoLI
#define VE_ceiltoQI    VD_ceiltoQI
#define VE_ceiltoUS    VD_ceiltoUS
#define VE_ceiltoU     VD_ceiltoU
#define VE_ceiltoUL    VD_ceiltoUL

#define VE_chop        VD_chop
#define VE_choptoSI    VD_choptoSI
#define VE_choptoI     VD_choptoI
#define VE_choptoLI    VD_choptoLI
#define VE_choptoQI    VD_choptoQI
#define VE_choptoUS    VD_choptoUS
#define VE_choptoU     VD_choptoU
#define VE_choptoUL    VD_choptoUL

#define VE_trunc       VE_chop
#define VE_trunctoSI   VE_choptoSI
#define VE_trunctoI    VE_choptoI
#define VE_trunctoLI   VE_choptoLI
#define VE_trunctoQI   VE_choptoQI
#define VE_trunctoUS   VE_choptoUS
#define VE_trunctoU    VE_choptoU
#define VE_trunctoUL   VE_choptoUL

#define VE_roundtoUI VE_roundtoU
#define VE_floortoUI VE_floortoU
#define VE_ceiltoUI  VE_ceiltoU
#define VE_choptoUI  VE_choptoU
#define VE_trunctoUI VE_trunctoU

#define VE_cmp0         VD_cmp0
#define VE_cmp_eq0      VD_cmp_eq0
#define VE_cmp_ne0      VD_cmp_ne0
#define VE_cmp_le0      VD_cmp_le0
#define VE_cmp_lt0      VD_cmp_lt0
#define VE_cmp_ge0      VD_cmp_ge0
#define VE_cmp_gt0      VD_cmp_gt0

#define VE_cmp_eq0ind   VD_cmp_eq0ind
#define VE_cmp_ne0ind   VD_cmp_ne0ind
#define VE_cmp_le0ind   VD_cmp_le0ind
#define VE_cmp_lt0ind   VD_cmp_lt0ind
#define VE_cmp_ge0ind   VD_cmp_ge0ind
#define VE_cmp_gt0ind   VD_cmp_gt0ind

#define VE_cmpC         VD_cmpC
#define VE_cmp_eqC      VD_cmp_eqC
#define VE_cmp_neC      VD_cmp_neC
#define VE_cmp_leC      VD_cmp_leC
#define VE_cmp_ltC      VD_cmp_ltC
#define VE_cmp_geC      VD_cmp_geC
#define VE_cmp_gtC      VD_cmp_gtC

#define VE_cmp_eqCind   VD_cmp_eqCind
#define VE_cmp_neCind   VD_cmp_neCind
#define VE_cmp_leCind   VD_cmp_leCind
#define VE_cmp_ltCind   VD_cmp_ltCind
#define VE_cmp_geCind   VD_cmp_geCind
#define VE_cmp_gtCind   VD_cmp_gtCind

#define VE_cmpV         VD_cmpV
#define VE_cmp_eqV      VD_cmp_eqV
#define VE_cmp_neV      VD_cmp_neV
#define VE_cmp_leV      VD_cmp_leV
#define VE_cmp_ltV      VD_cmp_ltV
#define VE_cmp_geV      VD_cmp_geV
#define VE_cmp_gtV      VD_cmp_gtV

#define VE_cmp_eqVind   VD_cmp_eqVind
#define VE_cmp_neVind   VD_cmp_neVind
#define VE_cmp_leVind   VD_cmp_leVind
#define VE_cmp_ltVind   VD_cmp_ltVind
#define VE_cmp_geVind   VD_cmp_geVind
#define VE_cmp_gtVind   VD_cmp_gtVind

#define VE_equC         VD_equC
#define VE_equV         VD_equV
#define VEx_equV        VDx_equV
#define VE_addC         VD_addC
#define VE_subC         VD_subC
#define VE_subrC        VD_subrC
#define VE_mulC         VD_mulC
#define VE_divC         VD_divC
#define VE_divrC        VD_divrC
#define VEx_divrC       VDx_divrC

#define VE_addV         VD_addV
#define VE_subV         VD_subV
#define VE_subrV        VD_subrV
#define VE_mulV         VD_mulV
#define VE_divV         VD_divV
#define VE_divrV        VD_divrV

#define VEx_addV        VDx_addV
#define VEx_subV        VDx_subV
#define VEx_subrV       VDx_subrV
#define VEx_mulV        VDx_mulV
#define VEx_divV        VDx_divV
#define VEx_divrV       VDx_divrV

#define VEs_addV        VDs_addV
#define VEs_subV        VDs_subV
#define VEs_subrV       VDs_subrV
#define VEs_mulV        VDs_mulV
#define VEs_divV        VDs_divV
#define VEs_divrV       VDs_divrV

#define VE_accV         VD_accV
#define VE_accVF        VD_accVF
#define VE_accVD        VE_accV
#define VE_accVBI       VD_accVBI
#define VE_accVSI       VD_accVSI
#define VE_accVI        VD_accVI
#define VE_accVLI       VD_accVLI
#define VE_accVQI       VD_accVQI
#define VE_accVUB       VD_accVUB
#define VE_accVUS       VD_accVUS
#define VE_accVU        VD_accVU
#define VE_accVUL       VD_accVUL
#define VE_accVUI       VD_accVUI

#define VE_maxC         VD_maxC
#define VE_minC         VD_minC
#define VE_limit        VD_limit
#define VE_flush0       VD_flush0
#define VE_maxV         VD_maxV
#define VE_minV         VD_minV
#define VE_modC         VD_modC
#define VE_modV         VD_modV
#define VEx_modV        VDx_modV
#define VE_fmodC        VE_modC
#define VE_fmodV        VE_modV
#define VEx_fmodV       VEx_modV

#define VE_redC         VD_redC
#define VE_redV         VD_redV
#define VEx_redV        VDx_redV
#define VE_visC         VD_visC
#define VE_visV         VD_visV
#define VEx_visV        VDx_visV
#define VE_hypC         VD_hypC
#define VE_hypV         VD_hypV
#define VEx_hypV        VDx_hypV

#define VE_sgn          VE_cmp0

#define VE_subvector_equC   VD_subvector_equC
#define VE_subvector_equV   VD_subvector_equV
#define VE_subvector_addC   VD_subvector_addC
#define VE_subvector_subC   VD_subvector_subC
#define VE_subvector_subrC  VD_subvector_subrC
#define VE_subvector_mulC   VD_subvector_mulC
#define VE_subvector_divC   VD_subvector_divC
#define VE_subvector_divrC  VD_subvector_divrC

#define VE_subvector_addV   VD_subvector_addV
#define VE_subvector_subV   VD_subvector_subV
#define VE_subvector_subrV  VD_subvector_subrV
#define VE_subvector_mulV   VD_subvector_mulV
#define VE_subvector_divV   VD_subvector_divV
#define VE_subvector_divrV  VD_subvector_divrV

/**********************  Mathematical Functions ***********************/

#define VE_abs          VD_abs
#define VE_neg          VD_neg
#define VE_inv          VD_inv
#define VEx_inv         VDx_inv
#define VE_intfrac      VD_intfrac
#define VE_modf         VE_intfrac
#define VE_mantexp      VD_mantexp
#define VE_frexp        VE_mantexp
#define VE_hypotC       VD_hypotC
#define VE_hypotV       VD_hypotV
#define VEx_hypotV      VDx_hypotV
#define VE_scale2       VD_scale2
#define VE_ldexp        VE_scale2
#define VE_scale10      VD_scale10
#define VE_square       VD_square
#define VEx_square      VDx_square
#define VE_cubic        VD_cubic
#define VEx_cubic       VDx_cubic
#define VE_quartic      VD_quartic
#define VEx_quartic     VDx_quartic
#define VE_poly         VD_poly
#define VEx_poly        VDx_poly
#define VE_ipow         VD_ipow
#define VEx_ipow        VDx_ipow
#define VE_ipow2        VD_ipow2
#define VE_ipow10       VD_ipow10
#define VE_pow          VD_pow
#define VEx_pow         VDx_pow
#define VE_pow2         VD_pow10
#define VEx_pow2        VDx_pow10
#define VE_pow10        VD_pow10
#define VEx_pow10       VDx_pow10
#define VE_sqrt         VD_sqrt
#define VEx_sqrt        VDx_sqrt
#define VE_log          VD_log
#define VEx_log         VDx_log
#define VE_log2         VD_log2
#define VEx_log2        VDx_log2
#define VE_log10        VD_log10
#define VEx_log10       VDx_log10
#define VE_ln           VE_log
#define VEx_ln          VEx_log
#define VE_exp          VD_exp
#define VE_OD           VD_OD
#define VE_ODwDark      VD_ODwDark
#define VE_setODThresh  VD_setODThresh
#define VEx_exp         VDx_exp
#define VE_expArbBase   VD_expArbBase
#define VEx_expArbBase  VDx_expArbBase
#define VE_expc         VD_expc
#define VEx_expc        VDx_expc
#define VE_exp2         VD_exp2
#define VEx_exp2        VDx_exp2
#define VE_erf          VD_erf
#define VEx_erf         VDx_erf 
#define VE_erfc         VD_erfc
#define VEx_erfc        VDx_erfc
#define VE_Gauss        VD_Gauss
#define VE_Lorentz      VD_Lorentz
#define VE_sin          VD_sin
#define VEx_sin         VDx_sin
#define VE_cos          VD_cos
#define VEx_cos         VDx_cos
#define VE_sincos       VD_sincos
#define VEx_sincos      VDx_sincos
#define VE_tan          VD_tan
#define VEx_tan         VDx_tan
#define VE_cot          VD_cot
#define VEx_cot         VDx_cot
#define VE_sec          VD_sec
#define VEx_sec         VDx_sec
#define VE_cosec        VD_cosec
#define VEx_cosec       VDx_cosec
#define VE_sin2         VD_sin2
#define VEx_sin2        VDx_sin2
#define VE_cos2         VD_cos2
#define VEx_cos2        VDx_cos2
#define VE_sincos2      VD_sincos2
#define VEx_sincos2     VDx_sincos
#define VE_tan2         VD_tan2
#define VEx_tan2        VDx_tan2
#define VE_cot2         VD_cot2
#define VEx_cot2        VDx_cot2
#define VE_sec2         VD_sec2
#define VEx_sec2        VDx_sec2
#define VE_cosec2       VD_cosec2
#define VEx_cosec2      VDx_cosec2
#define VE_sinrpi       VD_sinrpi
#define VEx_sinrpi      VDx_sinrpi
#define VE_cosrpi       VD_cosrpi
#define VEx_cosrpi      VDx_cosrpi
#define VE_sincosrpi    VD_sincosrpi
#define VEx_sincosrpi   VDx_sincos
#define VE_tanrpi       VD_tanrpi
#define VEx_tanrpi      VDx_tanrpi
#define VE_cotrpi       VD_cotrpi
#define VEx_cotrpi      VDx_cotrpi
#define VE_secrpi       VD_secrpi
#define VEx_secrpi      VDx_secrpi
#define VE_cosecrpi     VD_cosecrpi
#define VEx_cosecrpi    VDx_cosecrpi
#define VE_sinrpi2      VD_sinrpi2
#define VEx_sinrpi2     VDx_sinrpi2
#define VE_cosrpi2      VD_cosrpi2
#define VEx_cosrpi2     VDx_cosrpi2
#define VE_sincosrpi2   VD_sincosrpi2
#define VEx_sincosrpi2  VDx_sincos
#define VE_tanrpi2      VD_tanrpi2
#define VEx_tanrpi2     VDx_tanrpi2
#define VE_cotrpi2      VD_cotrpi2
#define VEx_cotrpi2     VDx_cotrpi2
#define VE_secrpi2      VD_secrpi2
#define VEx_secrpi2     VDx_secrpi2
#define VE_cosecrpi2    VD_cosecrpi2
#define VEx_cosecrpi2   VDx_cosecrpi2
#define VE_sinrpi3      VD_sinrpi3
#define VEx_sinrpi3     VDx_sinrpi3
#define VE_cosrpi3      VD_cosrpi3
#define VEx_cosrpi3     VDx_cosrpi3
#define VE_sincosrpi3   VD_sincosrpi3
#define VEx_sincosrpi3  VDx_sincos
#define VE_tanrpi3      VD_tanrpi3
#define VEx_tanrpi3     VDx_tanrpi3
#define VE_cotrpi3      VD_cotrpi3
#define VEx_cotrpi3     VDx_cotrpi3
#define VE_secrpi3      VD_secrpi3
#define VEx_secrpi3     VDx_secrpi3
#define VE_cosecrpi3    VD_cosecrpi3
#define VEx_cosecrpi3   VDx_cosecrpi3
#define VE_sinc         VD_sinc
#define VEx_sinc        VDx_sinc
#define VE_Kepler       VD_Kepler
#define VEx_Kepler      VDx_Kepler
#define VE_asin         VD_asin
#define VEx_asin        VDx_asin
#define VE_acos         VD_acos
#define VEx_acos        VDx_acos
#define VE_atan         VD_atan
#define VEx_atan        VDx_atan
#define VE_atan2        VD_atan2
#define VEx_atan2       VDx_atan2
#define VE_sinh         VD_sinh
#define VEx_sinh        VDx_sinh
#define VE_cosh         VD_cosh
#define VEx_cosh        VDx_cosh
#define VE_tanh         VD_tanh
#define VEx_tanh        VDx_tanh
#define VE_coth         VD_coth
#define VEx_coth        VDx_coth
#define VE_sech         VD_sech
#define VEx_sech        VDx_sech
#define VE_cosech       VD_cosech
#define VEx_cosech      VDx_cosech
#define VE_sech2        VD_sech2
#define VEx_sech2       VDx_sech2

#endif  /* Borland or Microsoft */

#define VE_gauss   VE_Gauss
#define VE_lorentz VE_Lorentz
#define VE_kepler  VE_Kepler
#define VEx_kepler VEx_Kepler

#ifdef __cplusplus
}
#endif


#endif /* __VEMATH_H */
