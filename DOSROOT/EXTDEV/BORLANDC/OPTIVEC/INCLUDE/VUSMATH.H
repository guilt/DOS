/*  VUSmath.h

  vector management functions for data type "unsigned short":
  integer arithmetics and mathematics.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VUSMATH_H
#define __VUSMATH_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/******************   Basic  Arithmetics   *************************/

void  __vf  VUSo_addC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUSo_subC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUSo_subrC( usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUSo_mulC(  usVector Y, usVector X, ui size, unsigned short C );
#ifdef V_trapIntError
    #define VUS_addC     VUSo_addC
    #define VUS_subC     VUSo_subC
    #define VUS_subrC    VUSo_subrC
    #define VUS_mulC     VUSo_mulC
#else
    void  __vf  VUS_addC(  usVector Y, usVector X, ui size, unsigned short C );
    void  __vf  VUS_subC(  usVector Y, usVector X, ui size, unsigned short C );
    void  __vf  VUS_subrC( usVector Y, usVector X, ui size, unsigned short C );
    void  __vf  VUS_mulC(  usVector Y, usVector X, ui size, unsigned short C );
#endif

void  __vf  VUS_divC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUS_divrC( usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUS_modC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUS_maxC(  usVector Y, usVector X, ui size, unsigned short C );
void  __vf  VUS_minC(  usVector Y, usVector X, ui size, unsigned short C );

void  __vf  VUSo_addV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUSo_subV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUSo_subrV( usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUSo_mulV(  usVector Z, usVector X, usVector Y, ui size );
#ifdef V_trapIntError
    #define VUS_addV    VUSo_addV
    #define VUS_subV    VUSo_subV
    #define VUS_subrV   VUSo_subrV
    #define VUS_mulV    VUSo_mulV
#else
    void __vf  VUS_addV(  usVector Z, usVector X, usVector Y, ui size );
    void __vf  VUS_subV(  usVector Z, usVector X, usVector Y, ui size );
    void __vf  VUS_subrV( usVector Z, usVector X, usVector Y, ui size );
    void __vf  VUS_mulV(  usVector Z, usVector X, usVector Y, ui size );
#endif
void  __vf  VUS_divV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUS_divrV( usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUS_modV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUS_maxV(  usVector Z, usVector X, usVector Y, ui size );
void  __vf  VUS_minV(  usVector Z, usVector X, usVector Y, ui size );


/******************** Accumulation (Y += X) ******************************/

void __vf VUS_accV(   usVector Y, usVector  X, ui size );
void __vf VUS_accVUB( usVector Y, ubVector  X, ui size );


/*****************   Bit-wise operations  *********************/

void    __vf  VUS_shl( usVector Y, usVector X, ui size, unsigned C );
void    __vf  VUS_shr( usVector Y, usVector X, ui size, unsigned C );

void    __vf  VUS_and( usVector Y, usVector X, ui size, unsigned short C );
void    __vf  VUS_or(  usVector Y, usVector X, ui size, unsigned short C );
void    __vf  VUS_xor( usVector Y, usVector X, ui size, unsigned short C );
void    __vf  VUS_not( usVector Y, usVector X, ui size );

/************  Optical Density Y = log10( X0 / X ) *********************/

int  __vf VUS_ODtoF( fVector OD, usVector X, usVector X0, ui size );
int  __vf VUS_ODtoD( dVector OD, usVector X, usVector X0, ui size );
int  __vf VUS_ODtoFwDark( fVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
int  __vf VUS_ODtoDwDark( dVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
void __vf VUS_setODThresh( unsigned short minX, unsigned short minX0 );
#ifdef __BORLANDC__   /* 80-bit reals supported ? */
int  __vf VUS_ODtoE( eVector OD, usVector X, usVector X0, ui size );
int  __vf VUS_ODtoEwDark( eVector OD, usVector X, usVector XDark,
                          usVector X0, usVector X0Dark, ui size );
#else
    #define VUS_ODtoE      VUS_ODtoD
    #define VUS_ODtoEwDark VUS_ODtoDwDark
#endif

#ifdef __cplusplus
}
#endif

#endif   /*  __VUSMATH_H    */
