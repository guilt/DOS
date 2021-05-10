/*    CDMATH.H

      Complex library for the languages C and C++.

      This header file contains all definitions for
      double-precision complex numbers (complex double).

      Copyright (c) 1996-2000 by Martin Sander
      Address of the author:
           Dr. Martin Sander Software Dev.
           Steinachstr. 9A
           D-69198 Schriesheim
           Germany
           MartinSander@Bigfoot.com
           http://www.optivec.com
*/


#ifndef __CDMATH_H
#define __CDMATH_H

#if !defined( _CMATH_DEFS )
   #ifdef __BORLANDC__
       #pragma option -a-
   #else /* Visual C++, Optima++ */
       #pragma pack( push,1 )
   #endif /* avoid insertion of dummy bytes  */
   typedef struct {float    Re, Im;} fComplex;
   typedef struct {double   Re, Im;} dComplex;
   #ifdef __BORLANDC__
       typedef long double    extended;
       typedef struct {extended Re, Im;} eComplex;
       #pragma option -a.
   #else /* Visual C++, Optima++ */
       typedef  double extended; /* Visual C++ does not support
                                 80-bit IEEE numbers. So make
                                 extended equal to double    */
       typedef dComplex  eComplex;
       #pragma pack( pop )
   #endif    /* restore default data packing  */
   typedef fComplex fcomplex;
   typedef dComplex dcomplex;
   typedef eComplex ecomplex;  // tolerate all-minuscule
   #define _CMATH_DEFS
#endif
#ifdef __BORLANDC__
    #include <_defs.h>
    #if defined __TINY || defined __SMALL__ || defined __MEDIUM__
        #if defined(_RTLDLL) || defined(_CLASSDLL)
            #error Must use static BC Runtime Library with OptiVec and CMATH in models TINY, SMALL, MEDIUM
        #endif
        #define   _VFAR  near   /* even in case of DS!=SS  */
    #elif defined __FLAT__
        #define  _VFAR
    #else
        #define   _VFAR  far
    #endif
    #if (__BORLANDC__ >= 0x450)
         #define __cmf _RTLENTRY _EXPFUNC
    #else
         #define __cmf  _Cdecl _FARFUNC
    #endif
#else  /* Visual C++, Optima++ */
    #define _VFAR
    #define __cmf  __cdecl
#endif
#define _VFARC const _VFAR

/*  first the constructors:  */
#ifdef __cplusplus
   /* since dComplex is declared as a struct instead of a class,
      the constructor cannot get the name "dComplex" here.     */
  #ifndef _DCPLX_DEFINED
  inline dComplex __cmf dcplx( double __ReVal )
  {   dComplex Result;
      Result.Re = __ReVal;
      Result.Im = 0.0;
      return Result;
  }

      // up-conversions from single precision
  inline dComplex __cmf dcplx( fComplex _VFARC & __zf )
  {   dComplex Result;
      Result.Re = __zf.Re;
      Result.Im = __zf.Im;
      return Result;
  }
      // down-conversion from extended precision
      // (with OVERFLOW error handling):
  #ifdef __BORLANDC__
      dComplex __cmf dcplx( eComplex __ze );
  #else
      inline dComplex _VFAR & __cmf dcplx( dComplex _VFAR & __zd )
      {   return __zd;  }  // necessary because eComplex=dComplex
  #endif
  #define _DCPLX_DEFINED
  #endif  // _DCPLX_DEFINED
#endif   /* basic form of constructor for C and C++ : */
   dComplex __cmf dcplx( double __ReVal, double __ImVal);
         /* conversion from fComplex and eComplex (with OVERFLOW handling) */
#if !defined __NEWCPLX_H
    #if defined __cplusplus
        extern "C" {
    #endif
    dComplex __cmf cftocd( fComplex __zf );
    dComplex __cmf cetocd( eComplex __ze );
    #if defined __cplusplus
        }
    #endif
#endif

   /* Basic complex operations. They are defined both
   for C and C++. However, for C++ you may as well use the
   overloaded operators and functions defined further below. */
#define         cd_real( z )  (z).Re
#define         cd_imag( z )  (z).Im
#if defined __cplusplus && !defined _CMATH_CLASSDEFS 
extern "C" {  // the following functions cannot be "extern C",
#endif        // if dComplex identical to complex<double>
dComplex __cmf  cd_neg(  dComplex __z );
dComplex __cmf  cd_conj( dComplex __z );
#ifdef __cplusplus  // even if _CMATH_CLASSDEFS
    extern "C" double   __cmf  cd_norm( dComplex __z );
    extern "C" double   __cmf  cd_arg(  dComplex __z );
#else
    double   __cmf  cd_norm( dComplex __z );
    double   __cmf  cd_arg(  dComplex __z );
#endif
dComplex __cmf  cd_polar( double __mag, double __angle );

dComplex __cmf  cd_add(   dComplex __x, dComplex __y );
dComplex __cmf  cd_addRe( dComplex __x, double __yRe );
dComplex __cmf  cd_sub(   dComplex __x, dComplex __y );
dComplex __cmf  cd_subRe( dComplex __x, double __yRe );  /*  x - yRe  */
dComplex __cmf  cd_subrRe( dComplex __x, double __yRe ); /*  yRe - x  */
dComplex __cmf  cd_mul(   dComplex __x, dComplex __y );
dComplex __cmf  cd_mulRe( dComplex __x, double __yRe );
dComplex __cmf  cd_div(   dComplex __x, dComplex __y );
dComplex __cmf  cd_divRe( dComplex __x, double __yRe );   /*  x / yRe  */
dComplex __cmf  cd_divrRe( dComplex __x, double __yRe );  /*  yRe / x  */

/*  mathematical functions with error handling through _matherr: */
#ifdef __cplusplus 
    extern "C" double   __cmf  cd_abs(  dComplex __z );
#else
	double   __cmf  cd_abs(  dComplex __z );
#endif
dComplex __cmf  cd_acos( dComplex __z );
dComplex __cmf  cd_asin( dComplex __z );
dComplex __cmf  cd_atan( dComplex __z );
dComplex __cmf  cd_cos(  dComplex __z );
dComplex __cmf  cd_cosh( dComplex __z );
dComplex __cmf  cd_cubic( dComplex __z );  /* raise to the third power */
dComplex __cmf  cd_exp(  dComplex __z );
dComplex __cmf  cd_inv(  dComplex __z );    /*   1.0 / z   */
dComplex __cmf  cd_ipow( dComplex __z, int __exponent );
                                             /* raise z to integer power */
dComplex __cmf  cd_ln(   dComplex __z );
dComplex __cmf  cd_log(   dComplex __z );  /* sane as cd_ln */
dComplex __cmf  cd_log2(  dComplex __z );
dComplex __cmf  cd_log10( dComplex __z );
dComplex __cmf  cd_pow( dComplex __base, dComplex __exponent );
dComplex __cmf  cd_powReBase( double __base, dComplex __exponent ); /* power of real base */
dComplex __cmf  cd_powReExpo( dComplex __base, double __exponent ); /* raise z to real power */
                         /* for integer exponents, use cd_ipow ! */
dComplex __cmf  cd_quartic( dComplex __z );  /* raise to the fourth power */
dComplex __cmf  cd_sin(  dComplex __z );
dComplex __cmf  cd_sinh( dComplex __z );
dComplex __cmf  cd_square( dComplex __z );
dComplex __cmf  cd_sqrt( dComplex __z );
dComplex __cmf  cd_tan(  dComplex __z );
dComplex __cmf  cd_tanh( dComplex __z );


#if defined __cplusplus && !defined _CMATH_CLASSDEFS
}    //  end of the extern "C" statement
#endif

#if defined __cplusplus && !defined __STD_COMPLEX && !defined __COMPLEX_H && !defined __NEWCPLX_H
   /* in addition to the basic operations defined above for C,
      here is the same complete set of overloaded operators and
      functions as offered by <newcplx.h> for the complex classes.  */

    inline double real( dComplex _VFARC & __z )
    {
        return __z.Re;
    }

    inline double imag( dComplex _VFARC & __z )
    {
        return __z.Im;
    }

    inline dComplex neg( dComplex _VFARC & __z1 )
    {   dComplex Result;
        Result.Re = -__z1.Re;
        Result.Im = -__z1.Im;
        return Result;
    }

    inline dComplex conj( dComplex _VFARC & __z)
    {   dComplex Result;
        Result.Re =  __z.Re;
        Result.Im = -__z.Im;
        return Result;
    }

    double   __cmf  norm( dComplex __z );
    double   __cmf  arg(  dComplex __z );
    dComplex __cmf  polar( double Mag, double Angle );

  //  unary operators:

  inline dComplex _VFAR & operator +( dComplex _VFAR & __z1 )
  {
      return __z1;
  }

  inline dComplex operator -( dComplex _VFARC & __z1 )
  {   dComplex Result;
      Result.Re = -__z1.Re;
      Result.Im = -__z1.Im;
      return Result;
  }


  //  binary operators:

  inline dComplex operator +( dComplex _VFARC & __z1, dComplex _VFARC & __z2 )
  {   dComplex Result;
      Result.Re = __z1.Re + __z2.Re;
      Result.Im = __z1.Im + __z2.Im;
      return Result;
  }

  inline dComplex operator +( dComplex _VFARC & __z1, double __z2Re )
  {   dComplex Result;
      Result.Re = __z1.Re + __z2Re;
      Result.Im = __z1.Im;
      return Result;
  }

  inline dComplex operator +( double __z1Re, dComplex _VFARC & __z2 )
  {   dComplex Result;
      Result.Re = __z1Re + __z2.Re;
      Result.Im = __z2.Im;
      return Result;
  }

  inline dComplex operator -( dComplex _VFARC & __z1, dComplex _VFARC & __z2 )
  {   dComplex Result;
      Result.Re = __z1.Re - __z2.Re;
      Result.Im = __z1.Im - __z2.Im;
      return Result;
  }

  inline dComplex operator -( dComplex _VFARC & __z1, double __z2Re )
  {   dComplex Result;
      Result.Re = __z1.Re - __z2Re;
      Result.Im = __z1.Im;
      return Result;
  }

  inline dComplex operator -( double __z1Re, dComplex _VFARC & __z2 )
  {   dComplex Result;
      Result.Re = __z1Re - __z2.Re;
      Result.Im = -__z2.Im;
      return Result;
  }

  inline dComplex operator *( dComplex _VFARC & __z1, dComplex _VFARC & __z2 )
  {   dComplex Result;
      Result.Re  = __z1.Re * __z2.Re - __z1.Im * __z2.Im;
      Result.Im  = __z1.Re * __z2.Im + __z1.Im * __z2.Re;
      return Result;
  }

  inline dComplex operator *( dComplex _VFARC & __z1, double __z2Re )
  {   dComplex Result;
      Result.Re = __z1.Re * __z2Re;
      Result.Im = __z1.Im * __z2Re;
      return Result;
  }

  inline dComplex operator *( double __z1Re, dComplex _VFARC & __z2 )
  {   dComplex Result;
      Result.Re  = __z1Re * __z2.Re;
      Result.Im  = __z1Re * __z2.Im;
      return Result;
  }

  inline dComplex operator /( dComplex _VFARC & __z1, double __z2Re )
  {   dComplex Result;
      Result.Re = __z1.Re / __z2Re;
      Result.Im = __z1.Im / __z2Re;
      return Result;
  }


  dComplex operator /( dComplex _VFARC & __z1, dComplex _VFARC & __z2 );
  dComplex operator /( double __z1Re, dComplex _VFARC & __z2 );

    /* most versions of BC will ignore the definitions of
       compound-assignment operators; they are needed for
	   MSVC and Optima++                                  */
  inline dComplex _VFAR & operator +=( dComplex _VFAR & __z1, dComplex _VFARC & __z2 )
  {
      __z1.Re += __z2.Re;
      __z1.Im += __z2.Im;
      return __z1;
  }

  inline dComplex _VFAR & operator +=( dComplex _VFAR & __z1, double __z2Re )
  {
      __z1.Re += __z2Re;
      return __z1;
  }

  inline dComplex _VFAR & operator -=( dComplex _VFAR & __z1, dComplex _VFARC & __z2 )
  {
      __z1.Re -= __z2.Re;
      __z1.Im -= __z2.Im;
      return __z1;
  }

  inline dComplex _VFAR & operator -=( dComplex _VFAR & __z1, double __z2Re )
  {
      __z1.Re -= __z2Re;
      return __z1;
  }

  inline dComplex _VFAR & operator *=( dComplex _VFAR & __z1, dComplex _VFARC & __z2 )
  {
      double tmpRe;
      tmpRe   = __z1.Re * __z2.Re - __z1.Im * __z2.Im;
      __z1.Im = __z1.Re * __z2.Im + __z1.Im * __z2.Re;
      __z1.Re = tmpRe;
      return __z1;
  }

  inline dComplex _VFAR & operator *=( dComplex _VFAR & __z1, double __z2Re )
  {
      __z1.Re *= __z2Re;
      __z1.Im *= __z2Re;
      return __z1;
  }

  dComplex _VFAR & operator /=( dComplex _VFAR & __z1, dComplex _VFARC & __z2 );

  inline dComplex _VFAR & operator /=( dComplex _VFAR & __z1, double __z2Re )
  {
      __z1.Re /= __z2Re;
      __z1.Im /= __z2Re;
      return __z1;
  }


  inline int operator ==( dComplex _VFARC & __z1, dComplex _VFARC & __z2 )
  {
      return (__z1.Re == __z2.Re) && (__z1.Im == __z2.Im );
  }

  inline int operator ==( dComplex _VFARC & __z1, double __z2Re )
  {
      return (__z1.Re == __z2Re) && (__z1.Im == 0.0 );
  }

  inline int operator !=( dComplex _VFARC & __z1, dComplex _VFARC & __z2 )
  {
      return (__z1.Re != __z2.Re) || (__z1.Im != __z2.Im );
  }

  inline int operator !=( dComplex _VFARC & __z1, double __z2Re )
  {
      return (__z1.Im != 0.0 ) || (__z1.Re != __z2Re);
  }


  /*  C++ version of the mathematical functions defined above.
      They use the same code as the C versions. In case of an error,
      you get a message in which the name of the C version is
      stated.
      Note that these functions require complex arguments to be
      passed by value, not by reference, as it is done in the member
      functions of the class complex. In terms of efficiency, this
      is about the same. (The math functions of the class complex
      store complex results at intermediate addresses and copy them
      to the desired address afterwards. This final copy is not
      necessary here.)                                             */

  double    __cmf  abs(  dComplex __z );
  dComplex __cmf  acos( dComplex __z );
  dComplex __cmf  asin( dComplex __z );
  dComplex __cmf  atan( dComplex __z );
  dComplex __cmf  cos(  dComplex __z );
  dComplex __cmf  cosh( dComplex __z );
  dComplex __cmf  cubic( dComplex __z );  /* raise to the third power */
  dComplex __cmf  exp(  dComplex __z );
  dComplex __cmf  inv(  dComplex __z );    /*   1.0 / z   */
  dComplex __cmf  ipow( dComplex __z, int __exponent );
                                            /* raise z to integer power */
  dComplex __cmf  ln(  dComplex __z );
  dComplex __cmf  log(  dComplex __z );  /* sane as ln */
  dComplex __cmf  log2( dComplex __z );
  dComplex __cmf  log10( dComplex __z );
  dComplex __cmf  pow( dComplex __z, dComplex __exponent );
  dComplex __cmf  pow( dComplex __z,  double __exponent ); // identical to powReExpo
  dComplex __cmf  pow( double __base,  dComplex __exponent ); // identical to powReBase
  dComplex __cmf  powReBase( double __base, dComplex __exponent ); // power of real base
  dComplex __cmf  powReExpo( dComplex __z, double __exponent );    // raise z to real power
                            // for integer exponents, use ipow !
  dComplex __cmf  quartic( dComplex __z );  // raise to the fourth power
  dComplex __cmf  sin(  dComplex __z );
  dComplex __cmf  sinh( dComplex __z );
  dComplex __cmf  square( dComplex __z );
  dComplex __cmf  sqrt( dComplex __z );
  dComplex __cmf  tan(  dComplex __z );
  dComplex __cmf  tanh( dComplex __z );
#endif //  __cplusplus, not __STD_COMPLEX , __COMPLEX_H, __NEWCPLX_H


/***  user-accessible error handling functions, borrowed from VectorLib  ****/

#ifdef __cplusplus
extern "C" {
#endif
void  __cmf  V_noteError( char _VFAR *fname, unsigned why );
void  __cmf  V_printErrorMsg( char _VFAR *ErrMsg );
void  __cmf  V_setErrorEventFile( char _VFAR *filename,  unsigned ScreenAndFile );
void  __cmf  V_closeErrorEventFile( void );

/*** translation of calls to matherr() into _matherr() for BorlandC 4.0+ ***/

#if (__BORLANDC__ >= 0x450) && !defined (__FLAT__)
     #if !defined( __MATH_H )
            #include <math.h>
     #endif
     int  _Cdecl _FARFUNC matherr (struct exception _VFAR *__e);
     #define NEWMATHERR  \
         int matherr( struct exception _VFAR *__e ) \
         {  return( _matherr( __e )); }
#else
     #define NEWMATHERR
#endif

#ifdef __cplusplus
}   // end of extern "C"
#endif
#endif   /*  __CDMATH_H  */
