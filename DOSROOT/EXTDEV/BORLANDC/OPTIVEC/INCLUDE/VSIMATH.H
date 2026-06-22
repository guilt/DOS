/*  VSImath.h

  vector management functions for data type "short":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VSIMATH_H
#define __VSIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/******************   Basic  Arithmetics   *************************/

void  __vf  VSI_neg( siVector Y, siVector X, ui size );
void  __vf  VSI_abs( siVector Y, siVector X, ui size );

void  __vf  VSIo_addC(  siVector Y, siVector X, ui size, short C );
void  __vf  VSIo_subC(  siVector Y, siVector X, ui size, short C );
void  __vf  VSIo_subrC( siVector Y, siVector X, ui size, short C );
void  __vf  VSIo_mulC(  siVector Y, siVector X, ui size, short C );
#ifdef V_trapIntError
    #define VSI_addC    VSIo_addC
    #define VSI_subC    VSIo_subC
    #define VSI_subrC   VSIo_subrC
    #define VSI_mulC    VSIo_mulC
#else
    void  __vf  VSI_addC(  siVector Y, siVector X, ui size, short C );
    void  __vf  VSI_subC(  siVector Y, siVector X, ui size, short C );
    void  __vf  VSI_subrC( siVector Y, siVector X, ui size, short C );
    void  __vf  VSI_mulC(  siVector Y, siVector X, ui size, short C );
#endif
void  __vf  VSI_divC(  siVector Y, siVector X, ui size, short C );
void  __vf  VSI_divrC( siVector Y, siVector X, ui size, short C );
void  __vf  VSI_modC(  siVector Y, siVector X, ui size, short C );
void  __vf  VSI_maxC(  siVector Y, siVector X, ui size, short C );
void  __vf  VSI_minC(  siVector Y, siVector X, ui size, short C );

void  __vf  VSIo_addV(  siVector Z, siVector X, siVector Y, ui size );
void  __vf  VSIo_subV(  siVector Z, siVector X, siVector Y, ui size );
void  __vf  VSIo_subrV( siVector Z, siVector X, siVector Y, ui size );
void  __vf  VSIo_mulV(  siVector Z, siVector X, siVector Y, ui size );
#ifdef V_trapIntError
    #define VSI_addV     VSIo_addV
    #define VSI_subV     VSIo_subV
    #define VSI_subrV    VSIo_subrV
    #define VSI_mulV     VSIo_mulV
#else
    void    __vf  VSI_addV(  siVector Z, siVector X, siVector Y, ui size );
    void    __vf  VSI_subV(  siVector Z, siVector X, siVector Y, ui size );
    void    __vf  VSI_subrV( siVector Z, siVector X, siVector Y, ui size );
    void    __vf  VSI_mulV(  siVector Z, siVector X, siVector Y, ui size );
#endif
void    __vf  VSI_divV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf  VSI_divrV( siVector Z, siVector X, siVector Y, ui size );
void    __vf  VSI_modV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf  VSI_maxV(  siVector Z, siVector X, siVector Y, ui size );
void    __vf  VSI_minV(  siVector Z, siVector X, siVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VSI_accV(   siVector Y, siVector  X, ui size );
void __vf VSI_accVBI( siVector Y, biVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf  VSI_shl( siVector Y, siVector X, ui size, unsigned C );
void    __vf  VSI_shr( siVector Y, siVector X, ui size, unsigned C );

void    __vf  VSI_and( siVector Y, siVector X, ui size, short C );
void    __vf  VSI_or(  siVector Y, siVector X, ui size, short C );
void    __vf  VSI_xor( siVector Y, siVector X, ui size, short C );
void    __vf  VSI_not( siVector Y, siVector X, ui size );

#ifdef __cplusplus
}
#endif

#endif   /*  __VSIMATH_H    */
