/*  VQImath.h

  vector management functions for data type "quad":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VQIMATH_H
#define __VQIMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif


#ifdef __cplusplus
   extern "C" {
#endif

/******************   Basic  Arithmetics   *************************/

void    __vf  VQI_neg( qiVector Y, qiVector X, ui size );
void    __vf  VQI_abs( qiVector Y, qiVector X, ui size );

void    __vf  VQI_addC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_subC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_subrC( qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_mulC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_divC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_divrC( qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_modC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_maxC(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_minC(  qiVector Y, qiVector X, ui size, quad C );

void    __vf  VQI_addV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_subV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_subrV( qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_mulV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_divV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_divrV( qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_modV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_maxV(  qiVector Z, qiVector X, qiVector Y, ui size );
void    __vf  VQI_minV(  qiVector Z, qiVector X, qiVector Y, ui size );

/******************** Accumulation (Y += X) ******************************/

void __vf VQI_accV(   qiVector Y, qiVector  X, ui size );
void __vf VQI_accVBI( qiVector Y, biVector  X, ui size );
void __vf VQI_accVSI( qiVector Y, siVector  X, ui size );
void __vf VQI_accVI(  qiVector Y, iVector   X, ui size );
void __vf VQI_accVLI( qiVector Y, liVector  X, ui size );
void __vf VQI_accVUB( qiVector Y, ubVector  X, ui size );
void __vf VQI_accVUS( qiVector Y, usVector  X, ui size );
void __vf VQI_accVU(  qiVector Y, uVector   X, ui size );
void __vf VQI_accVUL( qiVector Y, ulVector  X, ui size );
#if defined (V_HUGE)
    #define VQI_accVUI  VQI_accVUL
#else
    #define VQI_accVUI  VQI_accVU
#endif

/*****************   Bit-wise operations  *********************/

void    __vf  VQI_shl( qiVector Y, qiVector X, ui size, unsigned C );
void    __vf  VQI_shr( qiVector Y, qiVector X, ui size, unsigned C );

void    __vf  VQI_and( qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_or(  qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_xor( qiVector Y, qiVector X, ui size, quad C );
void    __vf  VQI_not( qiVector Y, qiVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VQI_ODtoF( fVector OD, qiVector X, qiVector X0, ui size );
int  __vf VQI_ODtoD( dVector OD, qiVector X, qiVector X0, ui size );
int  __vf VQI_ODtoFwDark( fVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
int  __vf VQI_ODtoDwDark( dVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
void __vf VQI_setODThresh( quad minX, quad minX0 );
#ifdef __BORLANDC__   /* 80-bit reals supported ? */
int  __vf VQI_ODtoE( eVector OD, qiVector X, qiVector X0, ui size );
int  __vf VQI_ODtoEwDark( eVector OD, qiVector X, qiVector XDark,
                          qiVector X0, qiVector X0Dark, ui size );
#else
    #define VQI_ODtoE      VQI_ODtoD
    #define VQI_ODtoEwDark VQI_ODtoDwDark
#endif

#ifdef __cplusplus
}
#endif

#endif   /*  __VQIMATH_H    */
