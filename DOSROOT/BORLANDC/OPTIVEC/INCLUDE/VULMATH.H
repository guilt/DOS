/*  VULmath.h

  vector management functions for data type "unsigned long":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VULMATH_H
#define __VULMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/******************   Basic  Arithmetics   *************************/

void  __vf  VULo_addC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VULo_subC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VULo_subrC( ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VULo_mulC(  ulVector Y, ulVector X, ui size, unsigned long C );
#ifdef V_trapIntError
    #define VUL_addC    VULo_addC
    #define VUL_subC    VULo_subC
    #define VUL_subrC   VULo_subrC
    #define VUL_mulC    VULo_mulC
#else
    void  __vf  VUL_addC(  ulVector Y, ulVector X, ui size, unsigned long C );
    void  __vf  VUL_subC(  ulVector Y, ulVector X, ui size, unsigned long C );
    void  __vf  VUL_subrC( ulVector Y, ulVector X, ui size, unsigned long C );
    void  __vf  VUL_mulC(  ulVector Y, ulVector X, ui size, unsigned long C );
#endif

void  __vf  VUL_divC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VUL_divrC( ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VUL_modC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VUL_maxC(  ulVector Y, ulVector X, ui size, unsigned long C );
void  __vf  VUL_minC(  ulVector Y, ulVector X, ui size, unsigned long C );

void  __vf  VULo_addV(  ulVector Z, ulVector X, ulVector Y, ui size );
void  __vf  VULo_subV(  ulVector Z, ulVector X, ulVector Y, ui size );
void  __vf  VULo_subrV( ulVector Z, ulVector X, ulVector Y, ui size );
void  __vf  VULo_mulV(  ulVector Z, ulVector X, ulVector Y, ui size );
#ifdef V_trapIntError
    #define VUL_addV    VULo_addV
    #define VUL_subV    VULo_subV
    #define VUL_subrV   VULo_subrV
    #define VUL_mulV    VULo_mulV
#else
    void __vf  VUL_addV(  ulVector Z, ulVector X, ulVector Y, ui size );
    void __vf  VUL_subV(  ulVector Z, ulVector X, ulVector Y, ui size );
    void __vf  VUL_subrV( ulVector Z, ulVector X, ulVector Y, ui size );
    void __vf  VUL_mulV(  ulVector Z, ulVector X, ulVector Y, ui size );
#endif
void    __vf  VUL_divV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf  VUL_divrV( ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf  VUL_modV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf  VUL_maxV(  ulVector Z, ulVector X, ulVector Y, ui size );
void    __vf  VUL_minV(  ulVector Z, ulVector X, ulVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VUL_accV(   ulVector Y, ulVector  X, ui size );
void __vf VUL_accVUB( ulVector Y, ubVector  X, ui size );
void __vf VUL_accVUS( ulVector Y, usVector  X, ui size );
void __vf VUL_accVU(  ulVector Y, uVector   X, ui size );

/*****************   Bit-wise operations  *********************/

void    __vf  VUL_shl( ulVector Y, ulVector X, ui size, unsigned C );
void    __vf  VUL_shr( ulVector Y, ulVector X, ui size, unsigned C );

void    __vf  VUL_and( ulVector Y, ulVector X, ui size, unsigned long C );
void    __vf  VUL_or(  ulVector Y, ulVector X, ui size, unsigned long C );
void    __vf  VUL_xor( ulVector Y, ulVector X, ui size, unsigned long C );
void    __vf  VUL_not( ulVector Y, ulVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VUL_ODtoF( fVector OD, uVector X, uVector X0, ui size );
int  __vf VUL_ODtoD( dVector OD, uVector X, uVector X0, ui size );
int  __vf VUL_ODtoFwDark( fVector OD, uVector X, uVector XDark,
                          uVector X0, uVector X0Dark, ui size );
int  __vf VUL_ODtoDwDark( dVector OD, uVector X, uVector XDark,
                          uVector X0, uVector X0Dark, ui size );
void __vf VUL_setODThresh( unsigned long minX, unsigned long minX0 );
#ifdef __BORLANDC__   /* 80-bit reals supported ? */
int  __vf VUL_ODtoE( eVector OD, uVector X, uVector X0, ui size );
int  __vf VUL_ODtoEwDark( eVector OD, uVector X, uVector XDark,
                          uVector X0, uVector X0Dark, ui size );
#else
    #define VUL_ODtoE      VUL_ODtoD
    #define VUL_ODtoEwDark VUL_ODtoDwDark
#endif

#ifdef __cplusplus
}
#endif

#endif   /*  __VULMATH_H    */
