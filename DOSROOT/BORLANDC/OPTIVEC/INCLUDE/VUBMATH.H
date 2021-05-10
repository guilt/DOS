/*  VUBmath.h


  vector management functions for unsigned byte-sized integers:
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VUBMATH_H
#define __VUBMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/******************   Basic  Arithmetics   *************************/

void  __vf  VUB_addC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_subC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_subrC( ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_mulC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_divC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_divrC( ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_modC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_maxC(  ubVector Y, ubVector X, ui size, unsigned char C );
void  __vf  VUB_minC(  ubVector Y, ubVector X, ui size, unsigned char C );

void __vf  VUB_addV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_subV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_subrV( ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_mulV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_divV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_divrV( ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_modV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_maxV(  ubVector Z, ubVector X, ubVector Y, ui size );
void __vf  VUB_minV(  ubVector Z, ubVector X, ubVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VUB_accV(   ubVector Y, ubVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf  VUB_shl( ubVector Y, ubVector X, ui size, unsigned C );
void    __vf  VUB_shr( ubVector Y, ubVector X, ui size, unsigned C );

void    __vf  VUB_and( ubVector Y, ubVector X, ui size, unsigned char C );
void    __vf  VUB_or(  ubVector Y, ubVector X, ui size, unsigned char C );
void    __vf  VUB_xor( ubVector Y, ubVector X, ui size, unsigned char C );
void    __vf  VUB_not( ubVector Y, ubVector X, ui size );

#ifdef __cplusplus
}
#endif

#endif   /*  __VUBMATH_H    */
