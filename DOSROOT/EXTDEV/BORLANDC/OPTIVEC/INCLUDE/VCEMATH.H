/*  VCEmath.h

  vector management functions:
  math functions performed on each individual element of an
  array or vector of data type "eComplex" (complex long double)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VCEMATH_H
#define __VCEMATH_H

#ifndef __VCESTD_H 
#include <VCEstd.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __BORLANDC__   /* 80-bit IEEE numbers supported.
                         The following  200 lines apply 
                         only to Borland C++            */

    /************************ Comparisons ********************************/

ui   __vf   VCE_cmp_eq0( ceVector Y, ceVector X, ui size );
ui   __vf   VCE_cmp_ne0( ceVector Y, ceVector X, ui size );
ui   __vf   VCE_cmp_eqC( ceVector Y, ceVector X, ui size,
                         eComplex C );
ui   __vf   VCE_cmp_neC( ceVector Y, ceVector X, ui size,
                         eComplex C );
ui   __vf   VCE_cmp_eqV( ceVector Z, ceVector X, ceVector Y, ui size );
ui   __vf   VCE_cmp_neV( ceVector Z, ceVector X, ceVector Y, ui size );
ui   __vf   VCE_cmp_eq0ind( uiVector Ind, ceVector X, ui size );
ui   __vf   VCE_cmp_ne0ind( uiVector Ind, ceVector X, ui size );
ui   __vf   VCE_cmp_eqCind( uiVector Ind, ceVector X, ui size,
                            eComplex C );
ui   __vf   VCE_cmp_neCind( uiVector Ind, ceVector X, ui size,
                            eComplex C );
ui   __vf   VCE_cmp_eqVind( uiVector Ind, ceVector X, ceVector Y, ui size );
ui   __vf   VCE_cmp_neVind( uiVector Ind, ceVector X, ceVector Y, ui size );


/********************  Standard Arithmetics   ***************************/

void  __vf   VCE_limit(  ceVector Y, ceVector X, ui size, eComplex Min,
                                                          eComplex Max );
void  __vf   VCE_flush0( ceVector Y, ceVector X, ui size, eComplex AbsMin );
void  __vf   VCE_flushInv( ceVector Y, ceVector X, ui size, eComplex AbsMin );

void  __vf   VCEx_equV( ceVector Y, ceVector X, ui size,
                        eComplex A, eComplex B );
void  __vf   VCE_addC(  ceVector Y, ceVector X, ui size, eComplex C );
void  __vf   VCE_subC(  ceVector Y, ceVector X, ui size, eComplex C );
void  __vf   VCE_subrC( ceVector Y, ceVector X, ui size, eComplex C );
void  __vf   VCE_mulC(  ceVector Y, ceVector X, ui size, eComplex C );
void  __vf   VCE_divC(  ceVector Y, ceVector X, ui size, eComplex C );
void  __vf   VCE_divrC( ceVector Y, ceVector X, ui size, eComplex C );
void  __vf   VCEx_divrC( ceVector Y, ceVector X, ui size,
                         eComplex A, eComplex B, eComplex C );

void  __vf   VCE_addReC(  ceVector Y, ceVector X, ui size, long double CRe );
void  __vf   VCE_subReC(  ceVector Y, ceVector X, ui size, long double CRe );
void  __vf   VCE_subrReC( ceVector Y, ceVector X, ui size, long double CRe );
void  __vf   VCE_mulReC(  ceVector Y, ceVector X, ui size, long double CRe );
void  __vf   VCE_divReC(  ceVector Y, ceVector X, ui size, long double CRe );
void  __vf   VCE_divrReC( ceVector Y, ceVector X, ui size, long double CRe );

void  __vf   VCE_addV(  ceVector Z, ceVector X, ceVector Y, ui size );
void  __vf   VCE_subV(  ceVector Z, ceVector X, ceVector Y, ui size );
void  __vf   VCE_subrV( ceVector Z, ceVector X, ceVector Y, ui size );
void  __vf   VCE_mulV(  ceVector Z, ceVector X, ceVector Y, ui size );
void  __vf   VCE_divV(  ceVector Z, ceVector X, ceVector Y, ui size );
void  __vf   VCE_divrV( ceVector Z, ceVector X, ceVector Y, ui size );

void  __vf   VCE_addReV(  ceVector Z, ceVector X, eVector Y, ui size );
void  __vf   VCE_subReV(  ceVector Z, ceVector X, eVector Y, ui size );
void  __vf   VCE_subrReV( ceVector Z, ceVector X, eVector Y, ui size );
void  __vf   VCE_mulReV(  ceVector Z, ceVector X, eVector Y, ui size );
void  __vf   VCE_divReV(  ceVector Z, ceVector X, eVector Y, ui size );
void  __vf   VCE_divrReV( ceVector Z, ceVector X, eVector Y, ui size );

void  __vf   VCEx_addV(  ceVector Z, ceVector X, ceVector Y, ui size,
                         eComplex A, eComplex B );
void  __vf   VCEx_subV(  ceVector Z, ceVector X, ceVector Y, ui size,
                         eComplex A, eComplex B );
void  __vf   VCEx_subrV( ceVector Z, ceVector X, ceVector Y, ui size,
                         eComplex A, eComplex B );
void  __vf   VCEx_mulV(  ceVector Z, ceVector X, ceVector Y, ui size,
                         eComplex A, eComplex B );
void  __vf   VCEx_divV(  ceVector Z, ceVector X, ceVector Y, ui size,
                         eComplex A, eComplex B );
void  __vf   VCEx_divrV( ceVector Z, ceVector X, ceVector Y, ui size,
                         eComplex A, eComplex B );

void  __vf   VCEx_addReV(  ceVector Z, ceVector X, eVector Y, ui size,
                           eComplex A, eComplex B );
void  __vf   VCEx_subReV(  ceVector Z, ceVector X, eVector Y, ui size,
                           eComplex A, eComplex B );
void  __vf   VCEx_subrReV( ceVector Z, ceVector X, eVector Y, ui size,
                           eComplex A, eComplex B );
void  __vf   VCEx_mulReV(  ceVector Z, ceVector X, eVector Y, ui size,
                           eComplex A, eComplex B );
void  __vf   VCEx_divReV(  ceVector Z, ceVector X, eVector Y, ui size,
                           eComplex A, eComplex B );
void  __vf   VCEx_divrReV( ceVector Z, ceVector X, eVector Y, ui size,
                           eComplex A, eComplex B );

void  __vf   VCE_lincomb( ceVector Z, ceVector X, ceVector Y, ui size,
                          eComplex CX, eComplex CY );  /* Z[i]=CX*X[i]+CY*Y[i] */

/******************** Accumulation (Y += X) ******************************/

void __vf VCE_accV(   ceVector Y, ceVector  X, ui size );
void __vf VCE_accVCF( ceVector Y, cfVector  X, ui size );
void __vf VCE_accVCD( ceVector Y, cdVector  X, ui size );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VCE_subvector_equC(  ceVector Y, ui subsiz, unsigned samp,
                                 eComplex C );
void  __vf  VCE_subvector_equV(  ceVector Y, ui subsiz, unsigned samp,
                                 ceVector X );

void  __vf  VCE_subvector_addC(  ceVector Y, ui subsiz, unsigned samp,
                                 eComplex C );
void  __vf  VCE_subvector_subC(  ceVector Y, ui subsiz, unsigned samp,
                                 eComplex C );
void  __vf  VCE_subvector_subrC( ceVector Y, ui subsiz, unsigned samp,
                                 eComplex C );
void  __vf  VCE_subvector_mulC(  ceVector Y, ui subsiz, unsigned samp,
                                 eComplex C );
void  __vf  VCE_subvector_divC(  ceVector Y, ui subsiz, unsigned samp,
                                 eComplex C );
void  __vf  VCE_subvector_divrC( ceVector Y, ui subsiz, unsigned samp,
                                 eComplex C );

void  __vf  VCE_subvector_addV(  ceVector Y, ui subsiz, unsigned samp,
                                 ceVector X );
void  __vf  VCE_subvector_subV(  ceVector Y, ui subsiz, unsigned samp,
                                 ceVector X );
void  __vf  VCE_subvector_subrV( ceVector Y, ui subsiz, unsigned samp,
                                 ceVector X );
void  __vf  VCE_subvector_mulV(  ceVector Y, ui subsiz, unsigned samp,
                                 ceVector X );
void  __vf  VCE_subvector_divV(  ceVector Y, ui subsiz, unsigned samp,
                                 ceVector X );
void  __vf  VCE_subvector_divrV( ceVector Y, ui subsiz, unsigned samp,
                                 ceVector X );


/*******************  Mathematical Functions *************************/

int   __vf   VCE_neg(  ceVector Y, ceVector X, ui size );
int   __vf   VCE_conj( ceVector Y, ceVector X, ui size );
int   __vf   VCE_abs(   eVector Y, ceVector X, ui size );
int   __vf   VCE_inv(  ceVector Y, ceVector X, ui size );
int   __vf   VCEx_inv( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B );

int  __vf   VCE_square(  ceVector Y, ceVector X, ui size );
int  __vf   VCEx_square( ceVector Y, ceVector X, ui size,
                         eComplex A, eComplex B );
int  __vf   VCE_cubic(   ceVector Y, ceVector X, ui size );
int  __vf   VCEx_cubic(  ceVector Y, ceVector X, ui size,
                         eComplex A, eComplex B );
int  __vf   VCE_quartic( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_quartic( ceVector Y, ceVector X, ui size,
                         eComplex A, eComplex B );
int  __vf   VCE_ipow( ceVector Y, ceVector X, ui size, int ipow );
int  __vf   VCEx_ipow( ceVector Y, ceVector X, ui size, int ipow,
                       eComplex A, eComplex B, eComplex C );

       /* extra fast integer powers: "unprotected", without error handling: */
int  __vf   VCEu_square(  ceVector Y, ceVector X, ui size );
int  __vf   VCEux_square( ceVector Y, ceVector X, ui size,
                          eComplex A, eComplex B );
int  __vf   VCEu_cubic(   ceVector Y, ceVector X, ui size );
int  __vf   VCEux_cubic(  ceVector Y, ceVector X, ui size,
                          eComplex A, eComplex B );
int  __vf   VCEu_quartic( ceVector Y, ceVector X, ui size );
int  __vf   VCEux_quartic( ceVector Y, ceVector X, ui size,
                          eComplex A, eComplex B );
int  __vf   VCEu_ipow( ceVector Y, ceVector X, ui size, int ipow );
int  __vf   VCEux_ipow( ceVector Y, ceVector X, ui size, int ipow,
                        eComplex A, eComplex B, eComplex C );

int  __vf   VCE_pow( ceVector Y, ceVector X, ui size, eComplex Expo );
int  __vf   VCEx_pow( ceVector Y, ceVector X, ui size,  eComplex Expo,
                      eComplex A, eComplex B, eComplex C );
int  __vf   VCE_powReExpo(  ceVector Y, ceVector X, ui size, extended Expo );
int  __vf   VCEx_powReExpo( ceVector Y, ceVector X, ui size, extended Expo,
                            eComplex A, eComplex B, eComplex C );

int  __vf   VCE_sqrt( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_sqrt( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B, eComplex C );

int  __vf   VCE_log( ceVector Y, ceVector X, ui size );
int  __vf   VCE_log2( ceVector Y, ceVector X, ui size );
int  __vf   VCE_log10( ceVector Y, ceVector X, ui size );
#define     VCE_ln  VCE_log
int  __vf   VCEx_log( ceVector Y, ceVector X, ui size,
                      eComplex A, eComplex B, eComplex C );
int  __vf   VCEx_log2( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B, eComplex C );
int  __vf   VCEx_log10( ceVector Y, ceVector X, ui size,
                        eComplex A, eComplex B, eComplex C );
#define     VCEx_ln    VCEx_log

int  __vf   VCE_exp( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_exp( ceVector Y, ceVector X, ui size,
                      eComplex A, eComplex B, eComplex C );
int  __vf   VCE_expArbBase(  ceVector Y, ceVector X, ui size, eComplex Base );
int  __vf   VCEx_expArbBase( ceVector Y, ceVector X, ui size, eComplex Base,
                             eComplex A, eComplex B, eComplex C );

int  __vf   VCE_sin( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_sin( ceVector Y, ceVector X, ui size,
                      eComplex A, eComplex B, eComplex C );
int  __vf   VCE_cos( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_cos( ceVector Y, ceVector X, ui size,
                      eComplex A, eComplex B, eComplex C );
int  __vf   VCE_tan( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_tan( ceVector Y, ceVector X, ui size,
                      eComplex A, eComplex B, eComplex C );

int  __vf   VCE_asin( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_asin( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B, eComplex C );
int  __vf   VCE_acos( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_acos( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B, eComplex C );
int  __vf   VCE_atan( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_atan( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B, eComplex C );

int  __vf   VCE_sinh( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_sinh( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B, eComplex C );
int  __vf   VCE_cosh( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_cosh( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B, eComplex C );
int  __vf   VCE_tanh( ceVector Y, ceVector X, ui size );
int  __vf   VCEx_tanh( ceVector Y, ceVector X, ui size,
                       eComplex A, eComplex B, eComplex C );


#else   /* no 80-bit IEEE number support with Visual C++:
           the following 120 lines apply only to Visual C++  */

#define VCE_cmp_eq0     VCD_cmp_eq0
#define VCE_cmp_ne0     VCD_cmp_ne0
#define VCE_cmp_eqC     VCD_cmp_eqC
#define VCE_cmp_neC     VCD_cmp_neC
#define VCE_cmp_eqV     VCD_cmp_eqV
#define VCE_cmp_neV     VCD_cmp_neV
#define VCE_cmp_eq0ind  VCD_cmp_eq0ind
#define VCE_cmp_ne0ind  VCD_cmp_ne0ind
#define VCE_cmp_eqCind  VCD_cmp_eqCind
#define VCE_cmp_neCind  VCD_cmp_neCind
#define VCE_cmp_eqVind  VCD_cmp_eqVind
#define VCE_cmp_neVind  VCD_cmp_neVind

#define VCE_limit       VCD_limit
#define VCE_flush0      VCD_flush0
#define VCEx_equV       VCDx_equV
#define VCE_addC        VCD_addC
#define VCE_subC        VCD_subC
#define VCE_subrC       VCD_subrC
#define VCE_mulC        VCD_mulC
#define VCE_divC        VCD_divC
#define VCE_divrC       VCD_divrC
#define VCEx_divrC      VCDx_divrC
#define VCE_addReC      VCD_addReC
#define VCE_subReC      VCD_subReC
#define VCE_subrReC     VCD_subrReC
#define VCE_mulReC      VCD_mulReC
#define VCE_divReC      VCD_divReC
#define VCE_divrReC     VCD_divrReC
#define VCE_addV        VCD_addV
#define VCE_subV        VCD_subV
#define VCE_subrV       VCD_subrV
#define VCE_mulV        VCD_mulV
#define VCE_divV        VCD_divV
#define VCE_divrV       VCD_divrV
#define VCE_addReV      VCD_addReV
#define VCE_subReV      VCD_subReV
#define VCE_subrReV     VCD_subrReV
#define VCE_mulReV      VCD_mulReV
#define VCE_divReV      VCD_divReV
#define VCE_divrReV     VCD_divrReV
#define VCEx_addV       VCDx_addV
#define VCEx_subV       VCDx_subV
#define VCEx_subrV      VCDx_subrV
#define VCEx_mulV       VCDx_mulV
#define VCEx_divV       VCDx_divV
#define VCEx_divrV      VCDx_divrV
#define VCEx_addReV     VCDx_addReV
#define VCEx_subReV     VCDx_subReV
#define VCEx_subrReV    VCDx_subrReV
#define VCEx_mulReV     VCDx_mulReV
#define VCEx_divReV     VCDx_divReV
#define VCEx_divrReV    VCDx_divrReV

#define VCE_lincomb     VCD_lincomb
#define VCE_accV        VCD_accV
#define VCE_accVF       VCD_accVF
#define VCE_accVD       VCD_accV

#define VCE_subvector_equC  VCD_subvector_equC
#define VCE_subvector_addC  VCD_subvector_addC
#define VCE_subvector_subC  VCD_subvector_subC
#define VCE_subvector_subrC VCD_subvector_subrC
#define VCE_subvector_mulC  VCD_subvector_mulC
#define VCE_subvector_divC  VCD_subvector_divC
#define VCE_subvector_divrC VCD_subvector_divrC
#define VCE_subvector_addV  VCD_subvector_addV
#define VCE_subvector_subV  VCD_subvector_subV
#define VCE_subvector_subrV VCD_subvector_subrV
#define VCE_subvector_mulV  VCD_subvector_mulV
#define VCE_subvector_divV  VCD_subvector_divV
#define VCE_subvector_divrV VCD_subvector_divrV

/*******************  Mathematical Functions *************************/

#define VCE_neg     VCD_neg
#define VCE_conj    VCD_conj
#define VCE_abs     VCD_abs
#define VCE_inv     VCD_inv
#define VCEx_inv    VCDx_inv
#define VCE_square  VCD_square
#define VCEx_square VCDx_square
#define VCE_cubic   VCD_cubic
#define VCEx_cubic  VCDx_cubic
#define VCE_quartic VCD_quartic
#define VCEx_quartic VCDx_quartic
#define VCE_ipow    VCD_ipow
#define VCEx_ipow   VCDx_ipow
#define VCE_pow     VCD_pow
#define VCEx_pow    VCDx_pow
#define VCE_powReBase  VCD_powReBase
#define VCE_powReExpo  VCD_powReExpo
#define VCEx_powReExpo VCDx_powReExpo
#define VCE_sqrt    VCD_sqrt
#define VCEx_sqrt   VCDx_sqrt
#define VCE_log     VCD_log
#define VCEx_log    VCDx_log
#define VCE_log2    VCD_log2
#define VCEx_log2   VCDx_log2
#define VCE_log10   VCD_log10
#define VCEx_log10  VCDx_log10
#define VCE_ln      VCE_log
#define VCEx_ln     VCEx_log
#define VCE_exp     VCD_exp
#define VCEx_exp    VCDx_exp
#define VCE_expArbBase  VCD_expArbBase
#define VCEx_expArbBase VCDx_expArbBase
#define VCE_sin     VCD_sin
#define VCEx_sin    VCDx_sin
#define VCE_cos     VCD_cos
#define VCEx_cos    VCDx_cos
#define VCE_tan     VCD_tan
#define VCEx_tan    VCDx_tan
#define VCE_asin    VCD_asin
#define VCEx_asin   VCDx_asin
#define VCE_acos    VCD_acos
#define VCEx_acos   VCDx_acos
#define VCE_atan    VCD_atan
#define VCEx_atan   VCDx_atan
#define VCE_sinh    VCD_sinh
#define VCEx_sinh   VCDx_sinh
#define VCE_cosh    VCD_cosh
#define VCEx_cosh   VCDx_cosh
#define VCE_tanh    VCD_tanh
#define VCEx_tanh   VCDx_tanh

#endif  /* Borland or Microsoft */

#ifdef __cplusplus
}
#endif


#endif /* __VCEMATH_H */
