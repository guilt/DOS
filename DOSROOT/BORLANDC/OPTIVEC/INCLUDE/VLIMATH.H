/*  VLImath.h

  vector management functions for data type "long":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VLIMATH_H
#define __VLIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/******************   Basic  Arithmetics   *************************/

void  __vf  VLI_neg( liVector Y, liVector X, ui size );
void  __vf  VLI_abs( liVector Y, liVector X, ui size );

void  __vf  VLIo_addC(  liVector Y, liVector X, ui size, long C );
void  __vf  VLIo_subC(  liVector Y, liVector X, ui size, long C );
void  __vf  VLIo_subrC( liVector Y, liVector X, ui size, long C );
void  __vf  VLIo_mulC(  liVector Y, liVector X, ui size, long C );
#ifdef V_trapIntError
    #define VLI_addC    VLIo_addC
    #define VLI_subC    VLIo_subC
    #define VLI_subrC   VLIo_subrC
    #define VLI_mulC    VLIo_mulC
#else
    void  __vf  VLI_addC(  liVector Y, liVector X, ui size, long C );
    void  __vf  VLI_subC(  liVector Y, liVector X, ui size, long C );
    void  __vf  VLI_subrC( liVector Y, liVector X, ui size, long C );
    void  __vf  VLI_mulC(  liVector Y, liVector X, ui size, long C );
#endif
void  __vf  VLI_divC(  liVector Y, liVector X, ui size, long C );
void  __vf  VLI_divrC( liVector Y, liVector X, ui size, long C );
void  __vf  VLI_modC(  liVector Y, liVector X, ui size, long C );
void  __vf  VLI_maxC(  liVector Y, liVector X, ui size, long C );
void  __vf  VLI_minC(  liVector Y, liVector X, ui size, long C );

void  __vf  VLIo_addV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLIo_subV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLIo_subrV( liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLIo_mulV(  liVector Z, liVector X, liVector Y, ui size );
#ifdef V_trapIntError
    #define VLI_addV    VLIo_addV
    #define VLI_subV    VLIo_subV
    #define VLI_subrV   VLIo_subrV
    #define VLI_mulV    VLIo_mulV
#else
    void  __vf  VLI_addV(  liVector Z, liVector X, liVector Y, ui size );
    void  __vf  VLI_subV(  liVector Z, liVector X, liVector Y, ui size );
    void  __vf  VLI_subrV( liVector Z, liVector X, liVector Y, ui size );
    void  __vf  VLI_mulV(  liVector Z, liVector X, liVector Y, ui size );
#endif
void  __vf  VLI_divV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLI_divrV( liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLI_modV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLI_maxV(  liVector Z, liVector X, liVector Y, ui size );
void  __vf  VLI_minV(  liVector Z, liVector X, liVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VLI_accV(   liVector Y, liVector  X, ui size );
void __vf VLI_accVBI( liVector Y, biVector  X, ui size );
void __vf VLI_accVSI( liVector Y, siVector  X, ui size );
void __vf VLI_accVI(  liVector Y, iVector   X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf  VLI_shl( liVector Y, liVector X, ui size, unsigned C );
void    __vf  VLI_shr( liVector Y, liVector X, ui size, unsigned C );

void    __vf  VLI_and( liVector Y, liVector X, ui size, long C );
void    __vf  VLI_or(  liVector Y, liVector X, ui size, long C );
void    __vf  VLI_xor( liVector Y, liVector X, ui size, long C );
void    __vf  VLI_not( liVector Y, liVector X, ui size );

#ifdef __cplusplus
}
#endif

#endif   /*  __VLIMATH_H    */
