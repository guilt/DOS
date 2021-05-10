/*    CFMATH.H

      Complex library for the languages C and C++.

      This header file contains all definitions for
      single-precision complex numbers (complex float).

      Copyright (c) 1996-2000 by Martin Sander
      Address of the author:
           Dr. Martin Sander Software Dev.
           Steinachstr. 9A
           D-69198 Schriesheim
           Germany
           MartinSander@Bigfoot.com
           http://www.optivec.com
*/


#ifndef __CFMATH_H
#define __CFMATH_H

#if !defined( _CMATH_DEFS )
   #ifdef __BORLANDC__
       #pragma option -a-
   #else /* Visual C++ */
       #pragma pack( push,1 )
   #endif /* avoid insertion of dummy bytes  */
   typedef struct {float    Re, Im;} fComplex;
   typedef struct {double   Re, Im;} dComplex;
   #ifdef __BORLANDC__
       typedef long double    extended;
       typedef struct {extended Re, Im;} eComplex;
       #pragma option -a.
   #else /* Visual C++ */
       typedef  double extended; /* Visual C++ does not support
                                 80-bit IEEE numbers. So make
                                 extended equal to double    */
       typedef dComplex  eComplex;
       #pragma pack( pop )
   #endif    /* restore default data packing  */
   typedef fComplex fcomplex;
   typedef dComplex dcomplex;
   typedef eComplex ecomplex;  // tolerate all-lower case
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
    #define __cmf __cdecl
#endif
#define _VFARC const _VFAR

/*  first the constructors:  */
#ifdef __cplusplus
   /* since fComplex is declared as a struct instead of a class,
      the constructor cannot get the name "fComplex" here.     */
  #ifndef _FCPLX_DEFINED
  inline fComplex __cmf fcplx( float __ReVal )
  {   fComplex Result;
      Result.Re = __ReVal;
      Result.Im = 0.0f;
      return Result;
  }

      // down-conversions from double and extended precision
      // (with OVERFLOW error handling):
  fComplex __cmf fcplx( dComplex __zd );
  #if defined __COMPLEX_H
      fComplex __cmf fcplx( complex __z );
  #endif
  #ifdef __BORLANDC__
      fComplex __cmf fcplx( eComplex __ze );
  #endif
  #define _FCPLX_DEFINED
  #endif  // _FCPLX_DEFINED
#endif  
	  /* basic form of constructor for C and C++ : */
   fComplex __cmf fcplx( float __ReVal, float __ImVal);
         /* down-conversion with OVERFLOW-handling:  */
#if !defined __NEWCPLX_H
    #if defined __cplusplus
        extern "C" {
    #endif
    fComplex __cmf cdtocf( dComplex __zd );
    fComplex __cmf cetocf( eComplex __ze );
    #if defined __cplusplus
        }
    #endif
#endif

   /* Basic complex operations. They are defined both
   for C and C++. However, for C++ you may as well use the
   overloaded operators and functions defined further below. */
#define         cf_real( z )  (z).Re
#define         cf_imag( z )  (z).Im
#if defined __cplusplus && !defined _CMATH_CLASSDEFS 
extern "C" {  // the following functions cannot be "extern C",
#endif       // if fComplex identical with complex<float>

fComplex __cmf  cf_neg(  fComplex __z );
fComplex __cmf  cf_conj( fComplex __z );

#ifdef __cplusplus  // even if _CMATH_CLASSDEFS
    extern "C" float __cmf  cf_norm( fComplex __z );
    extern "C" float __cmf  cf_arg(  fComplex __z );
#else
    float __cmf  cf_norm( fComplex __z );
    float __cmf  cf_arg(  fComplex __z );
#endif
fComplex __cmf  cf_polar( float __mag, float __angle );

fComplex __cmf  cf_add(   fComplex __x, fComplex __y );
fComplex __cmf  cf_addRe( fComplex __x, float __yRe );
fComplex __cmf  cf_sub(   fComplex __x, fComplex __y );
fComplex __cmf  cf_subRe( fComplex __x, float __yRe );  /* x - yRe */
fComplex __cmf  cf_subrRe( fComplex __x, float __yRe ); /* yRe - x */
fComplex __cmf  cf_mul(   fComplex __x, fComplex __y );
fComplex __cmf  cf_mulRe( fComplex __x, float __yRe );
fComplex __cmf  cf_div(   fComplex __x, fComplex __y );
fComplex __cmf  cf_divRe( fComplex __x, float __yRe );   /*  x / yRe  */
fComplex __cmf  cf_divrRe( fComplex __x, float __yRe );  /*  yRe / x  */

/*  mathematical functions with error handling through _matherr: */
#ifdef __cplusplus  // even if _CMATH_CLASSDEFS
    extern "C" float  __cmf  cf_abs(  fComplex __z );
#else
    float  __cmf  cf_abs(  fComplex __z );
#endif
fComplex __cmf  cf_acos( fComplex __z );
fComplex __cmf  cf_asin( fComplex __z );
fComplex __cmf  cf_atan( fComplex __z );
fComplex __cmf  cf_cos(  fComplex __z );
fComplex __cmf  cf_cosh( fComplex __z );
fComplex __cmf  cf_cubic( fComplex __z );  /* raise to the third power */
fComplex __cmf  cf_exp(  fComplex __z );
fComplex __cmf  cf_inv(  fComplex __z );    /*   1.0 / z   */
fComplex __cmf  cf_ipow( fComplex __z, int __exponent );
                                             /* raise z to integer power */
fComplex __cmf  cf_ln(    fComplex __z );
fComplex __cmf  cf_log(   fComplex __z ); /* same as cf_ln */
fComplex __cmf  cf_log2(  fComplex __z );
fComplex __cmf  cf_log10( fComplex __z );
fComplex __cmf  cf_pow( fComplex __base, fComplex __exponent );
fComplex __cmf  cf_powReBase( float __base, fComplex __exponent ); /* power of real base */
fComplex __cmf  cf_powReExpo( fComplex __base, float __exponent ); /* raise z to real power */
                         /* for integer exponents, use cf_ipow ! */
fComplex __cmf  cf_quartic( fComplex __z );  /* raise to the fourth power */
fComplex __cmf  cf_sin(  fComplex __z );
fComplex __cmf  cf_sinh( fComplex __z );
fComplex __cmf  cf_square( fComplex __z );
fComplex __cmf  cf_sqrt( fComplex __z );
fComplex __cmf  cf_tan(  fComplex __z );
fComplex __cmf  cf_tanh( fComplex __z );


#if defined __cplusplus && !defined _CMATH_CLASSDEFS
}    //  end of the extern "C" statement
#endif

#if defined __cplusplus && !defined __STD_COMPLEX && !defined __NEWCPLX_H
   /* in addition to the basic operations defined above for C,
      here is the same complete set of overloaded operators and
      functions as offered by <newcplx.h> for the complex classes.  */

    inline float real( fComplex _VFARC & __z )
    {
        return __z.Re;
    }

    inline float imag( fComplex _VFARC & __z )
    {
        return __z.Im;
    }

    inline fComplex neg( fComplex _VFARC & __z1 )
    {   fComplex Result;
        Result.Re = -__z1.Re;
        Result.Im = -__z1.Im;
        return Result;
    }

    inline fComplex conj( fComplex _VFARC & __z)
    {   fComplex Result;
        Result.Re =  __z.Re;
        Result.Im = -__z.Im;
        return Result;
    }

    float    __cmf norm( fComplex __z );
    float    __cmf arg(  fComplex __z );
    fComplex __cmf polar( float Mag, float Angle );

  //  unary operators:

  inline fComplex _VFAR & operator +( fComplex _VFAR & __z1 )
  {
      return __z1;
  }

  inline fComplex operator -( fComplex _VFARC & __z1 )
  {   fComplex Result;
      Result.Re = -__z1.Re;
      Result.Im = -__z1.Im;
      return Result;
  }

  //  binary operators:

  inline fComplex operator +( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {   fComplex Result;
      Result.Re = __z1.Re + __z2.Re;
      Result.Im = __z1.Im + __z2.Im;
      return Result;
  }

  inline fComplex operator +( fComplex _VFARC & __z1, float __z2Re )
  {   fComplex Result;
      Result.Re = __z1.Re + __z2Re;
      Result.Im = __z1.Im;
      return Result;
  }

  inline fComplex operator +( float __z1Re, fComplex _VFARC & __z2 )
  {   fComplex Result;
      Result.Re = __z1Re + __z2.Re;
      Result.Im = __z2.Im;
      return Result;
  }

  inline fComplex operator -( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {   fComplex Result;
      Result.Re = __z1.Re - __z2.Re;
      Result.Im = __z1.Im - __z2.Im;
      return Result;
  }

  inline fComplex operator -( fComplex _VFARC & __z1, float __z2Re )
  {   fComplex Result;
      Result.Re = __z1.Re - __z2Re;
      Result.Im = __z1.Im;
      return Result;
  }

  inline fComplex operator -( float __z1Re, fComplex _VFARC & __z2 )
  {   fComplex Result;
      Result.Re = __z1Re - __z2.Re;
      Result.Im = -__z2.Im;
      return Result;
  }

  inline fComplex operator *( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {   fComplex Result;
      Result.Re  = __z1.Re * __z2.Re - __z1.Im * __z2.Im;
      Result.Im  = __z1.Re * __z2.Im + __z1.Im * __z2.Re;
      return Result;
  }

  inline fComplex operator *( fComplex _VFARC & __z1, float __z2Re )
  {   fComplex Result;
      Result.Re = __z1.Re * __z2Re;
      Result.Im = __z1.Im * __z2Re;
      return Result;
  }

  inline fComplex operator *( float __z1Re, fComplex _VFARC & __z2 )
  {   fComplex Result;
      Result.Re  = __z1Re * __z2.Re;
      Result.Im  = __z1Re * __z2.Im;
      return Result;
  }

  inline fComplex operator /( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {   fComplex Result;
      double denom;
      Result.Re = (float)((__z1.Re * __z2.Re + __z1.Im * __z2.Im) /
        (denom = (double)(__z2.Re) * __z2.Re + (double)(__z2.Im) * __z2.Im));
      Result.Im = (float)((__z1.Im * __z2.Re - __z1.Re * __z2.Im ) / denom);
      return Result;
  }

  inline fComplex operator /( fComplex _VFARC & __z1, float __z2Re )
  {   fComplex Result;
      Result.Re = __z1.Re / __z2Re;
      Result.Im = __z1.Im / __z2Re;
      return Result;
  }

  inline fComplex operator /( float __z1Re, fComplex _VFARC & __z2 )
  {   fComplex Result;
      double denom;
      Result.Re = (float)((__z1Re * __z2.Re) /
        (denom = (double)(__z2.Re) * __z2.Re + (double)(__z2.Im) * __z2.Im));
      Result.Im = -(float)((__z1Re * __z2.Im ) / denom);
      return Result;
  }

    /* most versions of BC will ignore the definitions of
       compound-assignment operators; they are needed for
	   MSVC and Optima++                                  */
  inline fComplex _VFAR & operator +=( fComplex _VFAR & __z1, fComplex _VFARC & __z2 )
  {
      __z1.Re += __z2.Re;
      __z1.Im += __z2.Im;
      return __z1;
  }

  inline fComplex _VFAR & operator +=( fComplex _VFAR & __z1, float __z2Re )
  {
      __z1.Re += __z2Re;
      return __z1;
  }

  inline fComplex _VFAR & operator -=( fComplex  _VFAR & __z1, fComplex _VFARC & __z2 )
  {
      __z1.Re -= __z2.Re;
      __z1.Im -= __z2.Im;
      return __z1;
  }

  inline fComplex _VFAR & operator -=( fComplex _VFAR & __z1, float __z2Re )
  {
      __z1.Re -= __z2Re;
      return __z1;
  }

  inline fComplex _VFAR & operator *=( fComplex _VFAR & __z1, fComplex _VFARC & __z2 )
  {
      float tmpRe;
      tmpRe   = __z1.Re * __z2.Re - __z1.Im * __z2.Im;
      __z1.Im = __z1.Re * __z2.Im + __z1.Im * __z2.Re;
      __z1.Re = tmpRe;
      return __z1;
  }

  inline fComplex _VFAR & operator *=( fComplex _VFAR & __z1, float __z2Re )
  {
      __z1.Re *= __z2Re;
      __z1.Im *= __z2Re;
      return __z1;
  }

  inline fComplex _VFAR & operator /=( fComplex _VFAR & __z1, fComplex _VFARC & __z2 )
  {   double denom;
      float  tmpRe;
      tmpRe = (float)((__z1.Re * __z2.Re + __z1.Im * __z2.Im) /
        (denom = (double)(__z2.Re) * __z2.Re + (double)(__z2.Im) * __z2.Im));
      __z1.Im = (float)((__z1.Im * __z2.Re - __z1.Re * __z2.Im ) / denom);
      __z1.Re = tmpRe;
      return __z1;
  }

  inline fComplex _VFAR & operator /=( fComplex _VFAR & __z1, float __z2Re )
  {
      __z1.Re /= __z2Re;
      __z1.Im /= __z2Re;
      return __z1;
  }

  inline int operator ==( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {
      return (__z1.Re == __z2.Re) && (__z1.Im == __z2.Im );
  }

  inline int operator ==( fComplex _VFARC & __z1, float __z2Re )
  {
      return (__z1.Re == __z2Re) && (__z1.Im == 0.0 );
  }

  inline int operator !=( fComplex _VFARC & __z1, fComplex _VFARC & __z2 )
  {
      return (__z1.Re != __z2.Re) || (__z1.Im != __z2.Im );
  }

  inline int operator !=( fComplex _VFARC & __z1, float __z2Re )
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

  float    __cmf  abs(  fComplex __z );
  fComplex __cmf  acos( fComplex __z );
  fComplex __cmf  asin( fComplex __z );
  fComplex __cmf  atan( fComplex __z );
  fComplex __cmf  cos(  fComplex __z );
  fComplex __cmf  cosh( fComplex __z );
  fComplex __cmf  cubic( fComplex __z );  /* raise to the third power */
  fComplex __cmf  exp(  fComplex __z );
  fComplex __cmf  inv(  fComplex __z );    /*   1.0 / z   */
  fComplex __cmf  ipow( fComplex __z, int __exponent );
                                            /* raise z to integer power */
  fComplex __cmf  ln(  fComplex __z );
  fComplex __cmf  log(  fComplex __z );  /* same as ln */
  fComplex __cmf  log2( fComplex __z );
  fComplex __cmf  log10( fComplex __z );
  fComplex __cmf  pow( fComplex __z, fComplex __exponent );
  fComplex __cmf  pow( fComplex __z,  float __exponent ); // identical to powReExpo
  fComplex __cmf  pow( float __base,  fComplex __exponent ); // identical to powReBase
  fComplex __cmf  powReBase( float __base, fComplex __exponent ); // power of real base
  fComplex __cmf  powReExpo( fComplex __z, float __exponent );    // raise z to real power
                            // for integer exponents, use ipow !
  fComplex __cmf  quartic( fComplex __z );  // raise to the fourth power
  fComplex __cmf  sin(  fComplex __z );
  fComplex __cmf  sinh( fComplex __z );
  fComplex __cmf  square( fComplex __z );
  fComplex __cmf  sqrt( fComplex __z );
  fComplex __cmf  tan(  fComplex __z );
  fComplex __cmf  tanh( fComplex __z );
#endif //  __cplusplus, not __STD_COMPLEX , __NEWCPLX_H


/***  user-accessible error handling functions, borrowed from VectorLib  ****/

#ifdef __cplusplus
extern "C" {
#endif

void  __cmf  V_noteError( char _VFAR *fname, unsigned why );
void  __cmf  V_printErrorMsg( char _VFAR *ErrMsg );
void  __cmf  V_setErrorEventFile( char _VFAR *filename,  unsigned ScreenAndFile );
void  __cmf  V_closeErrorEventFile( void );

/*** translation of calls to matherr() into _matherr() for BorlandC 4.0+ ***/

#if defined __BORLANDC__ && (__BORLANDC__ >= 0x450) && !defined (__FLAT__)
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
#endif /*  __CFMATH_H  */
