/*  VImath.h

  vector management functions for data type "int":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VIMATH_H
#define __VIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/******************   Basic  Arithmetics   *************************/

void  __vf  VI_neg( iVector Y, iVector X, ui size );
void  __vf  VI_abs( iVector Y, iVector X, ui size );

void  __vf  VIo_addC(  iVector Y, iVector X, ui size, int C );
void  __vf  VIo_subC(  iVector Y, iVector X, ui size, int C );
void  __vf  VIo_subrC( iVector Y, iVector X, ui size, int C );
void  __vf  VIo_mulC(  iVector Y, iVector X, ui size, int C );
#ifdef V_trapIntError
    #define VI_addC     VIo_addC
    #define VI_subC     VIo_subC
    #define VI_subrC    VIo_subrC
    #define VI_mulC     VIo_mulC
#else
    void  __vf  VI_addC(  iVector Y, iVector X, ui size, int C );
    void  __vf  VI_subC(  iVector Y, iVector X, ui size, int C );
    void  __vf  VI_subrC( iVector Y, iVector X, ui size, int C );
    void  __vf  VI_mulC(  iVector Y, iVector X, ui size, int C );
#endif
void  __vf  VI_divC(  iVector Y, iVector X, ui size, int C );
void  __vf  VI_divrC( iVector Y, iVector X, ui size, int C );
void  __vf  VI_modC(  iVector Y, iVector X, ui size, int C );
void  __vf  VI_maxC(  iVector Y, iVector X, ui size, int C );
void  __vf  VI_minC(  iVector Y, iVector X, ui size, int C );

void  __vf  VIo_addV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VIo_subV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VIo_subrV( iVector Z, iVector X, iVector Y, ui size );
void  __vf  VIo_mulV(  iVector Z, iVector X, iVector Y, ui size );
#ifdef V_trapIntError
    #define VI_addV    VIo_addV
    #define VI_subV    VIo_subV
    #define VI_subrV   VIo_subrV
    #define VI_mulV    VIo_mulV
#else
    void  __vf  VI_addV(  iVector Z, iVector X, iVector Y, ui size );
    void  __vf  VI_subV(  iVector Z, iVector X, iVector Y, ui size );
    void  __vf  VI_subrV( iVector Z, iVector X, iVector Y, ui size );
    void  __vf  VI_mulV(  iVector Z, iVector X, iVector Y, ui size );
#endif
void  __vf  VI_divV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VI_divrV( iVector Z, iVector X, iVector Y, ui size );
void  __vf  VI_modV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VI_maxV(  iVector Z, iVector X, iVector Y, ui size );
void  __vf  VI_minV(  iVector Z, iVector X, iVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VI_accV(   iVector Y, iVector   X, ui size );
void __vf VI_accVBI( iVector Y, biVector  X, ui size );
void __vf VI_accVSI( iVector Y, siVector  X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf  VI_shl( iVector Y, iVector X, ui size, unsigned C );
void    __vf  VI_shr( iVector Y, iVector X, ui size, unsigned C );

void    __vf  VI_and( iVector Y, iVector X, ui size, int C );
void    __vf  VI_or(  iVector Y, iVector X, ui size, int C );
void    __vf  VI_xor( iVector Y, iVector X, ui size, int C );
void    __vf  VI_not( iVector Y, iVector X, ui size );

#ifdef __cplusplus
}
#endif

#endif   /*  __VIMATH_H    */
