/*    CEMATH.H

      Complex library for the languages C and C++.

      This header file contains all definitions for
      extended-precision complex numbers (complex long double).

      Copyright (c) 1996-2000 by Martin Sander
      Address of the author:
           Dr. Martin Sander Software Dev.
           Steinachstr. 9A
           D-69198 Schriesheim
           Germany
           MartinSander@Bigfoot.com
           http://www.optivec.com

*/


#ifndef __CEMATH_H
#define __CEMATH_H

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
       typedef  double extended; /* No support of 80-bit IEEE numbers.
                                 So make extended equal to double    */
       typedef dComplex  eComplex;
       #pragma pack( pop )
   #endif    /* restore default data packing  */
   typedef fComplex fcomplex;
   typedef dComplex dcomplex;
   typedef eComplex ecomplex;  // tolerate lower case
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
    #if __BORLANDC__ < 0x500
        #define VBOOL int
    #else
        #define VBOOL bool
    #endif
#else  /* Visual C++, Optima++ */
    #define _VFAR
    #define __cmf  __cdecl
    #ifndef __CDMATH_H
        #include <cdmath.h>
    #endif
#endif
#define _VFARC const _VFAR

#ifdef __BORLANDC__   /* 80-bit IEEE numbers supported:
                         the following 340 lines apply
                         only to Borland C++  */
#ifdef __cplusplus
    /*  first the constructors:
      since eComplex is declared as a struct instead of a class,
      the constructor cannot get the name "eComplex" here.     */
  #ifndef _ECPLX_DEFINED
  inline eComplex __cmf ecplx( extended __ReVal )
  {   eComplex Result;
      Result.Re = __ReVal;
      Result.Im = 0.0;
      return Result;
  }

      // up-conversions from single and double precision:
  inline eComplex __cmf ecplx( fComplex _VFARC & __zf )
  {   eComplex Result;
      Result.Re = __zf.Re;
      Result.Im = __zf.Im;
      return Result;
  }

  inline eComplex __cmf ecplx( dComplex _VFARC & __zd )
  {   eComplex Result;
      Result.Re = __zd.Re;
      Result.Im = __zd.Im;
      return Result;
  }

  #ifdef __COMPLEX_H
        // conversion from class complex
     inline eComplex __cmf ecplx( complex _VFARC & __zc )
     {   eComplex Result;
         Result.Re = real(__zc);
         Result.Im = imag(__zc);
         return Result;
     }
  #endif  // __COMPLEX_H
  #define _ECPLX_DEFINED
  #endif  // _ECPLX_DEFINED
#endif   /* __cplusplus */
       /* basic form of constructor for C and C++ : */
eComplex __cmf ecplx( extended __ReVal, extended __ImVal);

     /* conversion from fComplex and dComplex */
#if !defined __NEWCPLX_H
    #if defined __cplusplus
        extern "C" {
    #endif
    eComplex __cmf cftoce( fComplex __zf );
    eComplex __cmf cdtoce( dComplex __zd );
    #if defined __cplusplus
        }
    #endif
#endif

   /* Basic complex operations. They are defined both
   for C and C++. However, for C++ you may as well use the
   overloaded operators and functions defined further below. */
#define         ce_real( z )  (z).Re
#define         ce_imag( z )  (z).Im
#if defined __cplusplus && !defined _CMATH_CLASSDEFS 
extern "C" {  // the following functions cannot be "extern C",
#endif       // if eComplex identical with complex<extended>
eComplex __cmf  ce_neg(  eComplex __z );
eComplex __cmf  ce_conj( eComplex __z );
#ifdef __cplusplus  // even if _CMATH_CLASSDEFS
    extern "C" extended __cmf  ce_norm( eComplex __z );
    extern "C" extended __cmf  ce_arg(  eComplex __z );
#else
    extended __cmf  ce_norm( eComplex __z );
    extended __cmf  ce_arg(  eComplex __z );
#endif
eComplex __cmf  ce_polar( extended __mag, extended __angle );

eComplex __cmf  ce_add(   eComplex __x, eComplex __y );
eComplex __cmf  ce_addRe( eComplex __x, extended __yRe );
eComplex __cmf  ce_sub(   eComplex __x, eComplex __y );
eComplex __cmf  ce_subRe( eComplex __x, extended __yRe );  /* x - yRe */
eComplex __cmf  ce_subrRe( eComplex __x, extended __yRe ); /* yRe - x */
eComplex __cmf  ce_mul(   eComplex __x, eComplex __y );
eComplex __cmf  ce_mulRe( eComplex __x, extended __yRe );
eComplex __cmf  ce_div(   eComplex __x, eComplex __y );
eComplex __cmf  ce_divRe( eComplex __x, extended __yRe );  /*  x / yRe  */
eComplex __cmf  ce_divrRe( eComplex __x, extended __yRe ); /* yRe / x   */

/*  mathematical functions with error handling through _matherr: */
#ifdef __cplusplus  // even if _CMATH_CLASSDEFS
    extern "C" extended __cmf  ce_abs(  eComplex __z );
#else
    extended __cmf  ce_abs(  eComplex __z );
#endif
eComplex __cmf  ce_acos( eComplex __z );
eComplex __cmf  ce_asin( eComplex __z );
eComplex __cmf  ce_atan( eComplex __z );
eComplex __cmf  ce_cos(  eComplex __z );
eComplex __cmf  ce_cosh( eComplex __z );
eComplex __cmf  ce_cubic( eComplex __z );  /* raise to the third power */
eComplex __cmf  ce_exp(  eComplex __z );
eComplex __cmf  ce_inv(  eComplex __z );    /*   1.0 / z   */
eComplex __cmf  ce_ipow( eComplex __z, int __exponent );
                                             /* raise z to integer power */
eComplex __cmf  ce_ln(    eComplex __z );
eComplex __cmf  ce_log(   eComplex __z ); /* same as ce_ln */
eComplex __cmf  ce_log2(  eComplex __z );
eComplex __cmf  ce_log10( eComplex __z );
eComplex __cmf  ce_pow( eComplex __base, eComplex __exponent );
eComplex __cmf  ce_powReBase( extended __base, eComplex __exponent ); /* power of real base */
eComplex __cmf  ce_powReExpo( eComplex __base, extended __exponent ); /* raise z to real power */
                         /* for integer exponents, use ce_ipow ! */
eComplex __cmf  ce_quartic( eComplex __z );  /* raise to the fourth power */
eComplex __cmf  ce_sin(  eComplex __z );
eComplex __cmf  ce_sinh( eComplex __z );
eComplex __cmf  ce_square( eComplex __z );
eComplex __cmf  ce_sqrt( eComplex __z );
eComplex __cmf  ce_tan(  eComplex __z );
eComplex __cmf  ce_tanh( eComplex __z );

#if defined __cplusplus && !defined _CMATH_CLASSDEFS
}    //  end of the extern "C" statement
#endif

#if defined __cplusplus && !defined __STD_COMPLEX && !defined __NEWCPLX_H
   /* in addition to the basic operations defined above for C,
      here is the same complete set of overloaded operators and
      functions as offered by <newcplx.h> for the complex classes.  */

    inline extended real( eComplex _VFARC & __z )
    {
        return __z.Re;
    }

    inline extended imag( eComplex _VFARC & __z )
    {
        return __z.Im;
    }

    inline eComplex neg( eComplex _VFARC & __z1 )
    {   eComplex Result;
        Result.Re = -__z1.Re;
        Result.Im = -__z1.Im;
        return Result;
    }

    inline eComplex conj( eComplex _VFARC & __z)
    {   eComplex Result;
        Result.Re =  __z.Re;
        Result.Im = -__z.Im;
        return Result;
    }

    extended __cmf  norm( eComplex __z );
    extended __cmf  arg(  eComplex __z );
    eComplex __cmf  polar( extended Mag, extended Angle );
      //  unary operators:

    inline eComplex _VFAR & operator +( eComplex _VFAR & __z1 )
    {
        return __z1;
    }

    inline eComplex operator -( eComplex _VFARC & __z1 )
    {   eComplex Result;
        Result.Re = -__z1.Re;
        Result.Im = -__z1.Im;
        return Result;
    }

      //  binary operators:

    inline eComplex operator +( eComplex _VFARC & __z1, eComplex _VFARC & __z2 )
    {   eComplex Result;
        Result.Re = __z1.Re + __z2.Re;
        Result.Im = __z1.Im + __z2.Im;
        return Result;
    }

    inline eComplex operator +( eComplex _VFARC & __z1, extended __z2Re )
    {   eComplex Result;
        Result.Re = __z1.Re + __z2Re;
        Result.Im = __z1.Im;
        return Result;
    }

    inline eComplex operator +( extended __z1Re, eComplex _VFARC & __z2 )
    {   eComplex Result;
        Result.Re = __z1Re + __z2.Re;
        Result.Im = __z2.Im;
        return Result;
    }

    inline eComplex operator -( eComplex _VFARC & __z1, eComplex _VFARC & __z2 )
    {   eComplex Result;
        Result.Re = __z1.Re - __z2.Re;
        Result.Im = __z1.Im - __z2.Im;
        return Result;
    }

    inline eComplex operator -( eComplex _VFARC & __z1, extended __z2Re )
    {   eComplex Result;
        Result.Re = __z1.Re - __z2Re;
        Result.Im = __z1.Im;
        return Result;
    }

    inline eComplex operator -( extended __z1Re, eComplex _VFARC & __z2 )
    {   eComplex Result;
        Result.Re = __z1Re - __z2.Re;
        Result.Im = -__z2.Im;
        return Result;
    }

    inline eComplex operator *( eComplex _VFARC & __z1, eComplex _VFARC & __z2 )
    {   eComplex Result;
        Result.Re  = __z1.Re * __z2.Re - __z1.Im * __z2.Im;
        Result.Im  = __z1.Re * __z2.Im + __z1.Im * __z2.Re;
        return Result;
    }

    inline eComplex operator *( eComplex _VFARC & __z1, extended __z2Re )
    {   eComplex Result;
        Result.Re = __z1.Re * __z2Re;
        Result.Im = __z1.Im * __z2Re;
        return Result;
    }

    inline eComplex operator *( extended __z1Re, eComplex _VFARC & __z2 )
    {   eComplex Result;
        Result.Re  = __z1Re * __z2.Re;
        Result.Im  = __z1Re * __z2.Im;
        return Result;
    }

    eComplex operator /( eComplex _VFARC & __z1, eComplex _VFARC & __z2 );
    eComplex operator /( extended __z1Re, eComplex _VFARC & __z2 );
           // cannot be safely inlined for extended precision
    
    inline eComplex operator /( eComplex _VFARC & __z1, extended __z2Re )
    {   eComplex Result;
        Result.Re = __z1.Re / __z2Re;
        Result.Im = __z1.Im / __z2Re;
        return Result;
    }

    /* most versions of BC will ignore the definitions of
       compound-assignment operators; include them to be
       on the safe side with future versions          */
    inline eComplex _VFAR & operator +=( eComplex _VFAR & __z1, eComplex _VFARC & __z2 )
    {
        __z1.Re += __z2.Re;
        __z1.Im += __z2.Im;
        return __z1;
    }

    inline eComplex _VFAR & operator +=( eComplex _VFAR & __z1, extended __z2Re )
    {
        __z1.Re += __z2Re;
        return __z1;
    }

    inline eComplex _VFAR & operator -=( eComplex _VFAR & __z1, eComplex _VFARC & __z2 )
    {
        __z1.Re -= __z2.Re;
        __z1.Im -= __z2.Im;
        return __z1;
    }

    inline eComplex _VFAR & operator -=( eComplex _VFAR & __z1, extended __z2Re )
    {
        __z1.Re -= __z2Re;
        return __z1;
    }

    inline eComplex _VFAR & operator *=( eComplex _VFAR & __z1, eComplex _VFARC & __z2 )
    {
        extended tmpRe;
        tmpRe   = __z1.Re * __z2.Re - __z1.Im * __z2.Im;
        __z1.Im = __z1.Re * __z2.Im + __z1.Im * __z2.Re;
        __z1.Re = tmpRe;
        return __z1;
    }

    inline eComplex _VFAR & operator *=( eComplex _VFAR & __z1, extended __z2Re )
    {
        __z1.Re *= __z2Re;
        __z1.Im *= __z2Re;
        return __z1;
    }

    eComplex _VFAR & operator /=( eComplex _VFAR & __z1, eComplex _VFARC & __z2 );

    inline eComplex _VFAR & operator /=( eComplex _VFAR & __z1, extended __z2Re )
    {
        __z1.Re /= __z2Re;
        __z1.Im /= __z2Re;
        return __z1;
    }


    inline VBOOL operator ==( eComplex _VFARC & __z1, eComplex _VFARC & __z2 )
    {
        return (__z1.Re == __z2.Re) && (__z1.Im == __z2.Im );
    }

    inline VBOOL operator ==( eComplex _VFARC & __z1, extended __z2Re )
    {
        return (__z1.Re == __z2Re) && (__z1.Im == 0.0 );
    }

    inline VBOOL operator !=( eComplex _VFARC & __z1, eComplex _VFARC & __z2 )
    {
        return (__z1.Re != __z2.Re) || (__z1.Im != __z2.Im );
    }

    inline VBOOL operator !=( eComplex _VFARC & __z1, extended __z2Re )
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
      necessary here.)

  */

  extended __cmf  abs(  eComplex __z );
  eComplex __cmf  acos( eComplex __z );
  eComplex __cmf  asin( eComplex __z );
  eComplex __cmf  atan( eComplex __z );
  eComplex __cmf  cos(  eComplex __z );
  eComplex __cmf  cosh( eComplex __z );
  eComplex __cmf  cubic( eComplex __z );  /* raise to the third power */
  eComplex __cmf  exp(  eComplex __z );
  eComplex __cmf  inv(  eComplex __z );    /*   1.0 / z   */
  eComplex __cmf  ipow( eComplex __z, int __exponent );
                                            /* raise z to integer power */
  eComplex __cmf  ln(   eComplex __z );
  eComplex __cmf  log(  eComplex __z );  /* same as ln */
  eComplex __cmf  log2( eComplex __z );
  eComplex __cmf  log10( eComplex __z );
  eComplex __cmf  pow( eComplex __z,  eComplex __exponent );
  eComplex __cmf  pow( eComplex __z,  extended __exponent ); // identical to powReExpo
  eComplex __cmf  pow( extended __base,  eComplex __exponent ); // identical to powReBase
  eComplex __cmf  powReBase( extended __base, eComplex __exponent ); // power of real base
  eComplex __cmf  powReExpo( eComplex __z, extended __exponent );    // raise z to real power
                            // for integer exponents, use ipow !
  eComplex __cmf  quartic( eComplex __z );  // raise to the fourth power
  eComplex __cmf  sin(  eComplex __z );
  eComplex __cmf  sinh( eComplex __z );
  eComplex __cmf  square( eComplex __z );
  eComplex __cmf  sqrt( eComplex __z );
  eComplex __cmf  tan(  eComplex __z );
  eComplex __cmf  tanh( eComplex __z );
#endif //  __cplusplus, not __STD_COMPLEX , __NEWCPLX_H

#else /* no 80-bit IEEE number support:
        The following 50 lines apply only to
        Visual C++ and Optima++:          */

#define ecplx     dcplx
#define cftoce    cftocd
#define cdtoce(z) (z)
#define ce_real( z )  (z).Re
#define ce_imag( z )  (z).Im
#define ce_neg      cd_neg
#define ce_conj     cd_conj
#define ce_norm     cd_norm
#define ce_arg      cd_arg
#define ce_polar    cd_polar
#define ce_add      cd_add
#define ce_addRe    cd_addRe
#define ce_sub      cd_sub
#define ce_subRe    cd_subRe
#define ce_subrRe   cd_subrRe
#define ce_mul      cd_mul
#define ce_mulRe    cd_mulRe
#define ce_div      cd_div
#define ce_divRe    cd_divRe
#define ce_divrRe   cd_divrRe

#define ce_abs      cd_abs
#define ce_acos     cd_acos
#define ce_asin     cd_asin
#define ce_atan     cd_atan
#define ce_cos      cd_cos
#define ce_cosh     cd_cosh
#define ce_cubic    cd_cubic
#define ce_exp      cd_exp
#define ce_inv      cd_inv
#define ce_ipow     cd_ipow
#define ce_log      cd_log
#define ce_log2     cd_log2
#define ce_log10    cd_log10
#define ce_pow      cd_pow
#define ce_powReBase    cd_powReBase
#define ce_powReExpo    cd_powReExpo
#define ce_quartic  cd_quartic
#define ce_sin      cd_sin
#define ce_sinh     cd_sinh
#define ce_square   cd_square
#define ce_sqrt     cd_sqrt
#define ce_tan      cd_tan
#define ce_tanh     cd_tanh

#endif  /* Borland C++, Visual C++, or Optima++ */


/***  user-accessible error handling functions, borrowed from VectorLib  ****/

#ifdef __cplusplus
extern "C" {
#endif

void  __cmf  V_noteError( char _VFAR *fname, unsigned why );
void  __cmf  V_printErrorMsg( char _VFAR *ErrMsg );
void  __cmf  V_setErrorEventFile( char _VFAR *filename,  unsigned ScreenAndFile );
void  __cmf  V_closeErrorEventFile( void );

#ifdef __cplusplus
}   // end of extern "C"
#endif

#endif /*  __CEMATH_H  */
