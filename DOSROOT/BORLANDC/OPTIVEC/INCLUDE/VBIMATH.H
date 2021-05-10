/*  VBImath.h

  vector management functions for byte-size integers:
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VBIMATH_H
#define __VBIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/******************   Basic  Arithmetics   *************************/

void  __vf  VBI_neg( biVector Y, biVector X, ui size );
void  __vf  VBI_abs( biVector Y, biVector X, ui size );

void  __vf  VBI_addC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_subC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_subrC( biVector Y, biVector X, ui size, char C );
void  __vf  VBI_mulC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_divC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_divrC( biVector Y, biVector X, ui size, char C );
void  __vf  VBI_modC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_maxC(  biVector Y, biVector X, ui size, char C );
void  __vf  VBI_minC(  biVector Y, biVector X, ui size, char C );

void  __vf  VBI_addV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_subV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_subrV( biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_mulV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_divV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_divrV( biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_modV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_maxV(  biVector Z, biVector X, biVector Y, ui size );
void  __vf  VBI_minV(  biVector Z, biVector X, biVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VBI_accV(   biVector Y, biVector  X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf  VBI_shl( biVector Y, biVector X, ui size, unsigned C );
void    __vf  VBI_shr( biVector Y, biVector X, ui size, unsigned C );

void    __vf  VBI_and( biVector Y, biVector X, ui size, char C );
void    __vf  VBI_or(  biVector Y, biVector X, ui size, char C );
void    __vf  VBI_xor( biVector Y, biVector X, ui size, char C );
void    __vf  VBI_not( biVector Y, biVector X, ui size );

#ifdef __cplusplus
}
#endif

#endif   /*  __VBIMATH_H    */
