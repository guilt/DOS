/*  VUmath.h

  vector management functions for data type "unsigned":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VUMATH_H
#define __VUMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/******************   Basic  Arithmetics   *************************/

void  __vf  VUo_addC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf  VUo_subC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf  VUo_subrC( uVector Y, uVector X, ui size, unsigned C );
void  __vf  VUo_mulC(  uVector Y, uVector X, ui size, unsigned C );
#ifdef V_trapIntError
    #define VU_addC    VUo_addC
    #define VU_subC    VUo_subC
    #define VU_subrC   VUo_subrC
    #define VU_mulC    VUo_mulC
#else
    void  __vf  VU_addC(  uVector Y, uVector X, ui size, unsigned C );
    void  __vf  VU_subC(  uVector Y, uVector X, ui size, unsigned C );
    void  __vf  VU_subrC( uVector Y, uVector X, ui size, unsigned C );
    void  __vf  VU_mulC(  uVector Y, uVector X, ui size, unsigned C );
#endif

void  __vf  VU_divC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf  VU_divrC( uVector Y, uVector X, ui size, unsigned C );
void  __vf  VU_modC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf  VU_maxC(  uVector Y, uVector X, ui size, unsigned C );
void  __vf  VU_minC(  uVector Y, uVector X, ui size, unsigned C );

void  __vf  VUo_addV(  uVector Z, uVector X, uVector Y, ui size );
void  __vf  VUo_subV(  uVector Z, uVector X, uVector Y, ui size );
void  __vf  VUo_subrV( uVector Z, uVector X, uVector Y, ui size );
void  __vf  VUo_mulV(  uVector Z, uVector X, uVector Y, ui size );
#ifdef V_trapIntError
    #define VU_addV    VUo_addV
    #define VU_subV    VUo_subV
    #define VU_subrV   VUo_subrV
    #define VU_mulV    VUo_mulV
#else
    void __vf  VU_addV(  uVector Z, uVector X, uVector Y, ui size );
    void __vf  VU_subV(  uVector Z, uVector X, uVector Y, ui size );
    void __vf  VU_subrV( uVector Z, uVector X, uVector Y, ui size );
    void __vf  VU_mulV(  uVector Z, uVector X, uVector Y, ui size );
#endif
void    __vf  VU_divV(  uVector Z, uVector X, uVector Y, ui size );
void    __vf  VU_divrV( uVector Z, uVector X, uVector Y, ui size );
void    __vf  VU_modV(  uVector Z, uVector X, uVector Y, ui size );
void    __vf  VU_maxV(  uVector Z, uVector X, uVector Y, ui size );
void    __vf  VU_minV(  uVector Z, uVector X, uVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VU_accV(   uVector Y, uVector   X, ui size );
void __vf VU_accVUB( uVector Y, ubVector  X, ui size );
void __vf VU_accVUS( uVector Y, usVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf  VU_shl( uVector Y, uVector X, ui size, unsigned C );
void    __vf  VU_shr( uVector Y, uVector X, ui size, unsigned C );

void    __vf  VU_and( uVector Y, uVector X, ui size, unsigned C );
void    __vf  VU_or(  uVector Y, uVector X, ui size, unsigned C );
void    __vf  VU_xor( uVector Y, uVector X, ui size, unsigned C );
void    __vf  VU_not( uVector Y, uVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VU_ODtoF( fVector OD, uVector X, uVector X0, ui size );
int  __vf VU_ODtoD( dVector OD, uVector X, uVector X0, ui size );
int  __vf VU_ODtoFwDark( fVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
int  __vf VU_ODtoDwDark( dVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
void __vf VU_setODThresh( unsigned minX, unsigned minX0 );
#ifdef __BORLANDC__   /* 80-bit reals supported ? */
int  __vf VU_ODtoE( eVector OD, uVector X, uVector X0, ui size );
int  __vf VU_ODtoEwDark( eVector OD, uVector X, uVector XDark,
                         uVector X0, uVector X0Dark, ui size );
#else
    #define VU_ODtoE      VU_ODtoD
    #define VU_ODtoEwDark VU_ODtoDwDark
#endif

#ifdef __cplusplus
}
#endif

#endif   /*  __VUMATH_H    */
