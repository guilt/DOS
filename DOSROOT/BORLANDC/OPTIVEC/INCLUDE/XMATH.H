/*  xmath.h

  extended math library  belonging to OptiVec.

  will contain more functions in future releases.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#if !defined( __XMATH_H )
#define __XMATH_H
#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#if defined __FLAT__ || defined _WIN32
    #define VF_tabsz2 4096
    #define VD_tabsz2 4096
    #define VE_tabsz2 4096
    #define VF_log2tabsz2 12
    #define VD_log2tabsz2 12
    #define VE_log2tabsz2 12
    #define VF_tabsz3   720
    #define VD_tabsz3   720
    #define VE_tabsz3   720
#else  /* 16-bit models */
    #define VF_tabsz2 2048
    #define VD_tabsz2 1024
    #define VE_tabsz2 1024
    #define VF_log2tabsz2 11
    #define VD_log2tabsz2 10
    #define VE_log2tabsz2 10
    #define VF_tabsz3  360
    #define VD_tabsz3  180
    #define VE_tabsz3  180
#endif
#ifdef __BORLANDC__
    #define _VCDAT _cdecl
#else
    #define _VCDAT
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern float    _VCDAT _VFAR   VF_sintab2[ VF_tabsz2+1 ];
extern float    _VCDAT _VFAR   VF_sintab3[ VF_tabsz3+1 ];
extern float    _VCDAT _VFAR   VF_tantab2[ VF_tabsz2+1 ];
extern float    _VCDAT _VFAR   VF_tantab3[ VF_tabsz3+1 ];
extern float    _VCDAT _VFAR   VF_cosectab2[ VF_tabsz2+1 ];
extern float    _VCDAT _VFAR   VF_cosectab3[ VF_tabsz3+1 ];
extern double   _VCDAT _VFAR   VD_sintab2[ VD_tabsz2+1 ];
extern double   _VCDAT _VFAR   VD_sintab3[ VD_tabsz3+1 ];
extern double   _VCDAT _VFAR   VD_tantab2[ VD_tabsz2+1 ];
extern double   _VCDAT _VFAR   VD_tantab3[ VD_tabsz3+1 ];
extern double   _VCDAT _VFAR   VD_cosectab2[ VD_tabsz2+1 ];
extern double   _VCDAT _VFAR   VD_cosectab3[ VD_tabsz3+1 ];
#ifdef __BORLANDC__  /* only Borland C++ support 80-bit reals */
extern extended _VCDAT _VFAR   VE_sintab2[ VE_tabsz2+1 ];
extern extended _VCDAT _VFAR   VE_sintab3[ VE_tabsz3+1 ];
extern extended _VCDAT _VFAR   VE_tantab2[ VE_tabsz2+1 ];
extern extended _VCDAT _VFAR   VE_tantab3[ VE_tabsz3+1 ];
extern extended _VCDAT _VFAR   VE_cosectab2[ VE_tabsz2+1 ];
extern extended _VCDAT _VFAR   VE_cosectab3[ VE_tabsz3+1 ];
extended    __vf  log2l( extended x );
#else
    #ifdef _MSC_VER
       #define log2l log2
    #endif
#endif
#if defined __BORLANDC__ || defined _MSC_VER
    double      __vf  log2( double x );
#endif   /* Optima++ has log2 already built in */

int         __vf  isint( double x );
int         __vf  isintl( extended x );
#define           iseven( x )  !(x & 1)    /* for all integer types */
#define           sispositive( x )  !(x & HIBITS)  /* for short int */
#define           ispositive( x )   !(x & HIBITI)  /* for int */
#define           lispositive( x )  !(x & HIBITL)  /* for long int */
int         __vf  sisipow2( unsigned short x );
int         __vf  isipow2( unsigned x );
int         __vf  lisipow2( unsigned long x );

#ifdef __cplusplus
}
#endif
#endif /* __XMATH_H */
