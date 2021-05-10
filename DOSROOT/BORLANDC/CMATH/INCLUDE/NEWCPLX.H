/* newcmplx.h

    Include-File for the CMATH Complex Number Library
    replaces <complex.h>.

    Copyright (c) 1996-2000 by Martin Sander
    Address of the author:
           Dr. Martin Sander Software Dev.
           Steinachstr. 9A
           D-69198 Schriesheim
           Germany
           MartinSander@Bigfoot.com
           http://www.optivec.com

    for C++, the following classes are defined:
    a) if you choose the "classic" Borland C++ style:  class complex;
    b) otherwise:
       classes complex<float>, complex<double>, and complex<long double>.
    fComplex, dComplex, and eComplex are defined as synonyms for these classes.

    Fo plain C, use <cmath.h> instead, which declares fComplex, dComplex,
    and eComplex as structs, along with the same range of functions as
    present in the complex C++ classes.

    The classes complex and complex<double> are binary compatible with
    the C struct dComplex. Similarly, complex<float> and struct fComplex
    as well as class complex<long double> and struct eComplex are mutually
    compatible. This is important if one has programs with some modules
    written in C, others in C++.

    All mathematical complex functions are implemented as a library
    written in Assembler language. In comparison to C++ inline functions,
    this leads to greater precision, greater speed and best security due
    to complete error handling via the standard C error handling functions
    _matherr() (for complex<float> and complex<double>)
    and _matherrl() (for complex<long double>).

    The declarations for the Standard Library complex classes have
    partly been adapted from the implementation by Rogue Wave Software, Inc.
    The function bodies, however, are completely new.

    Note the following important differences between this implementation
    and the one contained in <complex.h>:
    -  The real and imaginary parts are declared as public and are referred
       to as  Re and Im, so that you may always access them as z.Re and z.Im
       in addition to the member functions real(z) and imag(z);
    -  The argument of all mathematical functions is a value, not a reference.
    -  The following functions and operators have been added:
       friend complex  cubic(complex);  //   third power
       friend complex  inv(complex);    //   1.0 / z
       friend complex  ipow(complex __base, int __expo);  // integer power
       friend complex  log2(complex);
       friend complex  powReExpo(complex __base, double __expoRe);
                                       // explicit power with real exponent
       friend complex  powReBase(double __baseRe, complex __expo);
                                       // explicit power of real base
       friend complex  quartic(complex);  // fourth power
       friend complex  square(complex);
       friend int      operator==(complex &, double);
       friend int      operator!=(complex &, double);
       Also new are many of the mixed-accuracy level binary operators.
*/

#ifndef __cplusplus
#error Must use C++ for complex classes. Include <cmath.h> for the plain-C version
#endif
#if !defined(__NEWCPLX_H)
#define __NEWCPLX_H
#ifdef complex 
#undef complex
#endif


#if defined __TINY || defined __SMALL__ || defined __MEDIUM__
    #if defined(_RTLDLL) || defined(_CLASSDLL)
        #error Must use static BC Runtime Library with CMATH in models TINY, SMALL, MEDIUM
    #endif
    #define   _VFAR  near   /* even in case of DS!=SS  */
       /* define _VFAR to get around Borland's buggy definition of _FAR */
#elif defined __FLAT__ || defined _WIN32
    #define  _VFAR
#else
    #define   _VFAR  far
#endif
#ifdef __BORLANDC__
     #pragma option -a-
     #if (__BORLANDC__ >= 0x450)
         #define __cmf _RTLENTRY _EXPFUNC
         #define __cmo _RTLENTRY
    #else
         #define __cmf  _Cdecl _FARFUNC
         #define __cmo  _Cdecl
    #endif
    #if __BORLANDC__ < 0x500
        #define VBOOL int
    #else
        #define VBOOL bool
    #endif
#else /* Visual C++, Watcom */
     #pragma pack( push,1 )
     #define VBOOL int
     #define __cmf _cdecl
     #define __cmo _cdecl
#endif /* avoid insertion of dummy bytes  */
#define _VFARC const _VFAR

#if !defined(__IOSTREAM_H)
#include <iostream.h>
#endif

#if defined( CMATH_CLASSIC_COMPLEX )
      // classic Borland C++ class complex only. This has double precision.
      // complex numbers of float and of long double precision are
      // implemented as structs. So there is no constructor! Moreover, there
      // are no functions defined for the float and long double complex numbers.
#if !defined(__IOSTREAM_H)
#include <iostream.h>
#endif

#if !defined(RC_INVOKED)

#pragma option -Vo-

#if defined(__STDC__)
#pragma warn -nak
#endif

#endif  /* !RC_INVOKED */

#if(__BORLANDC__ >= 0x450)
class _EXPCLASS complex {
#else
_CLASSDEF(complex)
class _CLASSTYPE complex {
#endif
  public:
    // constructors
    complex( double Re_part, double Im_part ) {Re=Re_part; Im=Im_part;}
    complex( double Re_part )  {Re=Re_part; Im=0;}
    complex() {}; // more efficient to have these three separate variants
    // Cartesian complex from polar coordinates:
    friend complex __cmf polar(double _mag, double _angle=0);
    // basic operations:
    double real() { return Re; }                     // real part
    friend double  __cmf real(complex _VFARC &_z);
    double imag() { return Im; }                     // imaginary part
    friend complex __cmf neg(complex _VFARC &);   // same as unary operator -
    friend complex __cmf conj(complex _VFARC &);  // complex conjugate
    friend double  __cmf norm(complex);          // square of the magnitude
    friend double  __cmf arg(complex);           // angle in the plane

     // Unary operators
    complex _VFAR & __cmo operator+();
    friend complex __cmf operator-( complex _VFARC &);

    // Binary operators
    friend complex __cmf operator+(complex _VFARC &, complex _VFARC &);
    friend complex __cmf operator+(double, complex _VFARC &);
    friend complex __cmf operator+(complex _VFARC &, double);
    friend complex __cmf operator-(complex _VFARC &, complex _VFARC &);
    friend complex __cmf operator-(double, complex _VFARC &);
    friend complex __cmf operator-(complex _VFARC &, double);
    friend complex __cmf operator*(complex _VFARC &, complex _VFARC &);
    friend complex __cmf operator*(complex _VFARC &, double);
    friend complex __cmf operator*(double, complex _VFARC &);
    friend complex __cmf operator/(complex _VFARC &, complex _VFARC &);
    friend complex __cmf operator/(complex _VFARC &, double);
    friend complex __cmf operator/(double, complex _VFARC &);

    friend VBOOL __cmf operator==(complex _VFARC &, complex _VFARC &);
    friend VBOOL __cmf operator==(complex _VFARC &, double);
    friend VBOOL __cmf operator!=(complex _VFARC &, complex _VFARC &);
    friend VBOOL __cmf operator!=(complex _VFARC &, double);

    complex _VFAR & __cmo operator+=(complex _VFARC &);
    complex _VFAR & __cmo operator+=(double);
    complex _VFAR & __cmo operator-=(complex _VFARC &);
    complex _VFAR & __cmo operator-=(double);
    complex _VFAR & __cmo operator*=(complex _VFARC &);
    complex _VFAR & __cmo operator*=(double);
    complex _VFAR & __cmo operator/=(complex _VFARC &);
    complex _VFAR & __cmo operator/=(double);

    // Overloaded ANSI C math functions with error handling via matherr():
    friend double  __cmf abs(complex);    // complex pointer magnitude
    friend complex __cmf acos(complex);
    friend complex __cmf asin(complex);
    friend complex __cmf atan(complex);
    friend complex __cmf cos(complex);
    friend complex __cmf cosh(complex);
    friend complex __cmf cubic(complex);  // raise to the third power
    friend complex __cmf exp(complex);
    friend complex __cmf inv(complex);    //   1.0 / z
    friend complex __cmf ipow(complex _base, int _IntExpo);  // integer power
    friend complex __cmf ln(complex);
    friend complex __cmf log(complex); // same as ln
    friend complex __cmf log2(complex);
    friend complex __cmf log10(complex);
    friend complex __cmf pow(complex _base, double _expoRe);
    friend complex __cmf powReExpo(complex _base, double _expoRe);
    friend complex __cmf pow(double _baseRe, complex _expo);
    friend complex __cmf powReBase(double _baseRe, complex _expo);
    friend complex __cmf pow(complex _base, complex _expo);
    friend complex __cmf quartic(complex);  // raise to the fourth power
    friend complex __cmf sin(complex);
    friend complex __cmf sinh(complex);
    friend complex __cmf sqrt(complex);
    friend complex __cmf square(complex);
    friend complex __cmf tan(complex);
    friend complex __cmf tanh(complex);

    friend ostream _VFAR & __cmf operator<<(ostream _VFAR &, complex _VFAR &);
    friend istream _VFAR & __cmf operator>>(istream _VFAR &, complex _VFARC &);

// Implementation
    double Re, Im;   // still public!
};
#if !defined( _CMATH_DEFS )
   #define _CMATH_DEFS
   typedef struct {float  Re, Im;} fComplex;
   typedef complex  dComplex;
   #ifdef __BORLANDC__
       typedef long double  extended;
       typedef struct {extended Re, Im;} eComplex;
   #else /* Visual C++ */
       typedef  double extended; /* Visual C++ does not support
                                 80-bit IEEE numbers. So make
                                 extended equal to double    */
       typedef dComplex  eComplex;
   #endif    /* restore default data packing  */
#endif

// Inline implementation of the simplest functions and operators
// basic operations:
inline double __cmf real( complex _VFARC & __z)
{ return __z.Re; }

inline double __cmf imag( complex _VFARC & __z)
{ return __z.Im; }

inline complex __cmo conj(complex _VFARC & __z)
{    return complex(__z.Re, -__z.Im); }

inline complex __cmo neg(complex _VFARC & __z)
{    return complex(-__z.Re, -__z.Im); }

// unary operators:
inline complex _VFAR & __cmo complex::operator+()
{    return *this; }

inline complex __cmf operator-( complex _VFARC & __z)
{    return complex(-__z.Re, -__z.Im); }


// binary operators:
inline complex __cmo operator+(complex _VFARC & __z1, complex _VFARC & __z2)
{    return complex(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex __cmo operator+(double __z1Re, complex _VFARC & __z2)
{    return complex(__z1Re + __z2.Re, __z2.Im); }

inline complex __cmo operator+(complex _VFARC & __z1, double __z2Re)
{    return complex(__z1.Re + __z2Re, __z1.Im); }

inline complex __cmo operator-(complex _VFARC & __z1, complex _VFARC & __z2)
{    return complex(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex __cmo operator-(double __z1Re, complex _VFARC & __z2)
{    return complex(__z1Re - __z2.Re, -__z2.Im); }

inline complex __cmo operator-(complex _VFARC & __z1, double __z2Re)
{    return complex(__z1.Re - __z2Re, __z1.Im); }

inline complex __cmo operator*(complex _VFARC & __z1, complex _VFARC & __z2)
{   return complex( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                    __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}

inline complex __cmo operator*(complex _VFARC & __z1, double __z2Re)
{    return complex(__z1.Re*__z2Re, __z1.Im*__z2Re); }

inline complex __cmo operator*(double __z1Re, complex _VFARC & __z2)
{    return complex(__z2.Re*__z1Re, __z2.Im*__z1Re); }

inline complex __cmo operator /(complex _VFARC & __dividend,
                                complex _VFARC & __divisor )
{     complex     Result;
      long double denom;
      Result.Re = (double)((__dividend.Re *__divisor.Re +
                            __dividend.Im *__divisor.Im) /
         (denom = (long double)(__divisor.Re) * __divisor.Re +
                  (long double)(__divisor.Im) * __divisor.Im));
      Result.Im = (double)((__dividend.Im * __divisor.Re -
                            __dividend.Re * __divisor.Im ) / denom);
      return Result;
}

inline complex __cmo operator/(complex _VFARC & __dividend, double __divisorRe)
{    return complex(__dividend.Re/__divisorRe, __dividend.Im/__divisorRe); }

inline complex __cmo operator /( double __dividendRe, complex _VFARC & __divisor )
{     complex     Result;
      long double denom;
      Result.Re = (double)((__dividendRe * __divisor.Re) /
         (denom = (long double)(__divisor.Re) * __divisor.Re +
                  (long double)(__divisor.Im) * __divisor.Im));
      Result.Im = -(double)((__dividendRe * __divisor.Im ) / denom);
      return Result;
}

inline complex _VFAR & __cmo complex::operator+=(complex _VFARC & __z2)
{   Re += __z2.Re;
    Im += __z2.Im;
    return *this;
}

inline complex _VFAR & __cmo complex::operator+=(double __z2Re)
{   Re += __z2Re;
    return *this;
}

inline complex _VFAR & __cmo complex::operator-=(complex _VFARC & __z2)
{   Re -= __z2.Re;
    Im -= __z2.Im;
    return *this;
}

inline complex _VFAR & __cmo complex::operator-=(double __z2Re)
{   Re -= __z2Re;
    return *this;
}

inline complex _VFAR & __cmo complex::operator*=(double __z2Re)
{   Re *= __z2Re;
    Im *= __z2Re;
    return *this;
}

inline complex _VFAR & __cmo complex::operator *=(complex _VFARC & __z2)
{     double tmpRe = Re * __z2.Re - Im * __z2.Im;
             Im    = Re * __z2.Im + Im * __z2.Re;
      Re = tmpRe;
      return *this;
}

inline complex _VFAR & __cmo complex::operator /=( complex _VFARC & __divisor )
{     long double denom;
      double tmpRe = (double)((Re * __divisor.Re + Im * __divisor.Im) /
        (denom = (long double)(__divisor.Re) * __divisor.Re +
                 (long double)(__divisor.Im) * __divisor.Im));
      Im = (Im * __divisor.Re - Re * __divisor.Im ) / denom;
      Re = tmpRe;
      return *this;
}

inline complex _VFAR & __cmo complex::operator/=(double __z2Re)
{   Re /= __z2Re;
    Im /= __z2Re;
    return *this;
}

inline VBOOL __cmo operator==(complex _VFARC & __z1, complex _VFARC & __z2)
{   return __z1.Re == __z2.Re && __z1.Im == __z2.Im; }

inline VBOOL __cmo operator==(complex _VFARC & __z1, double __z2Re)
{   return __z1.Re == __z2Re && __z1.Im == 0.0; }

inline VBOOL __cmo operator!=(complex _VFARC & __z1, complex _VFARC & __z2)
{   return __z1.Re != __z2.Re || __z1.Im != __z2.Im; }

inline VBOOL __cmo operator!=(complex _VFARC & __z1, double __z2Re)
{   return __z1.Re != __z2Re || __z1.Im != 0.0; }


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn .nak
#endif

#pragma option -Vo.

#endif  /* !RC_INVOKED */
#if !defined( _CMATH_DEFS )
   #define _CMATH_DEFS
   typedef struct {float  Re, Im;} fComplex;
   typedef complex  dComplex;
   #ifdef __BORLANDC__
       typedef long double  extended;
       typedef struct {extended Re, Im;} eComplex;
   #else /* Watcom, Visual C++ */
       typedef  double extended; /* Visual C++ and Optima++ do 
                            not support 80-bit IEEE numbers. So 
                            make extended equal to double    */
       typedef dComplex  eComplex;
   #endif    /* restore default data packing  */
#endif

#else   // declare the complex classes for all three levels of precision
        // Although these classes are fully compatible to the complex
        // classes of the Standard C++ Library, keep them out of the
        // standard namespace.

#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x540)
            // new syntax for explicit specialization of templates
    #define CMATH_NEW_TEMPLATE template<>
#else
    #define CMATH_NEW_TEMPLATE
#endif

template <class T>
class complex;
CMATH_NEW_TEMPLATE class complex<float>;
CMATH_NEW_TEMPLATE class complex<double>;
CMATH_NEW_TEMPLATE class complex<long double>;

CMATH_NEW_TEMPLATE class complex<float>
{
  public:
         // constructors:
    #if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
        complex( float Re_part, float Im_part ) {Re=Re_part; Im=Im_part;}
        complex( float Re_part )  {Re=Re_part; Im=0;}
        complex() {}; // most efficient to have these as three different constructors!
            // interconversions between the three levels of accuracy:
            // with OVERFLOW error handling for the down-conversions
    #else // problems with the template definitions in older BC versions
        complex<float>( float Re_part, float Im_part ) {Re=Re_part; Im=Im_part;}
        complex<float>( float Re_part )  {Re=Re_part; Im=0;}
        complex<float>() {};
    #endif
    #if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
        complex (complex<float> _VFARC &);
    #endif
    friend complex<float> __cmf cdtocf( complex<double> cd );
    friend complex<float> __cmf cetocf( complex<long double> ce );
    #if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
        explicit complex (complex<double> _VFARC &);
        explicit complex (complex<long double> _VFARC &);
    #else
        #ifdef __BORLANDC__   // prior to v5.0
            complex<float> (complex<double> _VFARC & zd) {*this = cdtocf( zd );}
            complex<float> (complex<long double> _VFARC & ze) {*this = cetocf( ze );}
        #else // Optima++ doesn't like "explicit"
            complex (complex<double> _VFARC & zd);
            complex (complex<long double> _VFARC & ze);
        #endif
    #endif
       // simple assignments: no OVERFLOW error handling
    complex<float> _VFAR & __cmo  operator= (complex<float> _VFARC &);
    complex<float> _VFAR & __cmo  operator= (complex<double> _VFARC &);
    complex<float> _VFAR & __cmo  operator= (complex<long double> _VFARC &);
    complex<float> _VFAR & __cmo  operator= (float);
    complex<float> _VFAR & __cmo  operator= (double);
    complex<float> _VFAR & __cmo  operator= (long double);

    // Cartesian complex from polar coordinates:
    friend complex<float> __cmf polar(float _mag, float _angle=0);

    // basic operations:
    float real() { return Re; }                              // real part
    friend float __cmf real(complex<float> _VFARC &_z);
    float imag() { return Im; }                              // imaginary part
    friend float __cmf imag(complex<float> _VFARC &_z);
    friend complex<float> __cmf neg(complex<float> _VFARC &); // same as unary operator -
    friend complex<float> __cmf conj(complex<float> _VFARC &);// complex conjugate
    friend float  __cmf norm(complex<float>);          // square of the magnitude
    friend float  __cmf arg(complex<float>);           // angle in the plane

     // Unary operators
    complex<float> _VFAR & __cmo operator+();
    friend complex<float> __cmf operator-( complex<float> _VFARC &);

    // Binary operators:
    friend complex<float> __cmf operator+(complex<float> _VFARC &, complex<float> _VFARC &);
    friend complex<float> __cmf operator+(float, complex<float> _VFARC &);
    friend complex<float> __cmf operator+(complex<float> _VFARC &, float);
    friend complex<float> __cmf operator-(complex<float> _VFARC &, complex<float> _VFARC &);
    friend complex<float> __cmf operator-(float, complex<float> _VFARC &);
    friend complex<float> __cmf operator-(complex<float> _VFARC &, float);
    friend complex<float> __cmf operator*(complex<float> _VFARC &, complex<float> _VFARC &);
    friend complex<float> __cmf operator*(complex<float> _VFARC &, float);
    friend complex<float> __cmf operator*(float, complex<float> _VFARC &);
    friend complex<float> __cmf operator/(complex<float> _VFARC &, complex<float> _VFARC &);
    friend complex<float> __cmf operator/(complex<float> _VFARC &, float);
    friend complex<float> __cmf operator/(float, complex<float> _VFARC &);
       // mixed-accuracy binary operators are declared at the higher-accuracy classes

    friend VBOOL __cmf operator==(complex<float> _VFARC &, complex<float> _VFARC &);
    friend VBOOL __cmf operator==(complex<float> _VFARC &, float);
    friend VBOOL __cmf operator!=(complex<float> _VFARC &, complex<float> _VFARC &);
    friend VBOOL __cmf operator!=(complex<float> _VFARC &, float);

       //  Compound-assignment operators:
    complex<float> _VFAR & __cmo  operator+= (complex<float> _VFARC &);
    complex<float> _VFAR & __cmo  operator-= (complex<float> _VFARC &);
    complex<float> _VFAR & __cmo  operator*= (complex<float> _VFARC &);
    complex<float> _VFAR & __cmo  operator/= (complex<float> _VFARC &);

    complex<float> _VFAR & __cmo  operator+= (complex<double> _VFARC &);
    complex<float> _VFAR & __cmo  operator-= (complex<double> _VFARC &);
    complex<float> _VFAR & __cmo  operator*= (complex<double> _VFARC &);
    complex<float> _VFAR & __cmo  operator/= (complex<double> _VFARC &);

    complex<float> _VFAR & __cmo  operator+= (complex<long double> _VFARC &);
    complex<float> _VFAR & __cmo  operator-= (complex<long double> _VFARC &);
    complex<float> _VFAR & __cmo  operator*= (complex<long double> _VFARC &);
    complex<float> _VFAR & __cmo  operator/= (complex<long double> _VFARC &);

    // Overloaded ANSI C math functions
    friend float          __cmf abs(complex<float>);
    friend complex<float> __cmf acos(complex<float>);
    friend complex<float> __cmf asin(complex<float>);
    friend complex<float> __cmf atan(complex<float>);
    friend complex<float> __cmf cos(complex<float>);
    friend complex<float> __cmf cosh(complex<float>);
    friend complex<float> __cmf cubic(complex<float>);  // raise to the third power
    friend complex<float> __cmf exp(complex<float>);
    friend complex<float> __cmf inv(complex<float>);    //   1.0 / z
    friend complex<float> __cmf ipow(complex<float> __base, int __expon);  // integer power
    friend complex<float> __cmf ln(complex<float>);
    friend complex<float> __cmf log(complex<float>); // same as ln
    friend complex<float> __cmf log2(complex<float>);
    friend complex<float> __cmf log10(complex<float>);
    friend complex<float> __cmf pow(complex<float> __base, float __expon);
    friend complex<float> __cmf powReExpo(complex<float> __base, float __expon);
    friend complex<float> __cmf pow(float __base, complex<float> __expon);
    friend complex<float> __cmf powReBase(float __base, complex<float> __expon);
    friend complex<float> __cmf pow(complex<float> __base, complex<float> __expon);
    friend complex<float> __cmf quartic(complex<float>);  // raise to the fourth power
    friend complex<float> __cmf sin(complex<float>);
    friend complex<float> __cmf sinh(complex<float>);
    friend complex<float> __cmf sqrt(complex<float>);
    friend complex<float> __cmf square(complex<float>);
    friend complex<float> __cmf tan(complex<float>);
    friend complex<float> __cmf tanh(complex<float>);

    friend istream _VFAR & __cmf operator>> (istream _VFAR &, complex<float> _VFAR &);
    friend ostream _VFAR & __cmf operator<< (ostream _VFAR &, complex<float> _VFARC &);

    float Re, Im;  // still public!
};

CMATH_NEW_TEMPLATE class  complex<double>
{
  public:
         // constructors:
    #if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
        complex( double Re_part, double Im_part ) {Re=Re_part; Im=Im_part;}
        complex( double Re_part )  {Re=Re_part; Im=0;}
        complex() {};
            // interconversions between the three levels of accuracy:
            // with OVERFLOW error handling for the down-conversions
        complex (complex<float> _VFARC &);
    #else // problems with the template definitions in older BC versions
        complex<double>( double Re_part, double Im_part ) {Re=Re_part; Im=Im_part;}
        complex<double>( double Re_part )  {Re=Re_part; Im=0;}
        complex<double>() {};
        complex<double> (complex<float> _VFARC & zf) {Re = zf.Re; Im = zf.Im;}
    #endif
    #if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
            complex (complex<double> _VFARC &);
    #endif
    friend complex<double> __cmf cetocd( complex<long double> ce );
    #if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
        explicit complex (complex<long double> _VFARC &);
    #else
        #ifdef __BORLANDC__  // prior to v5.0
            complex<double> (complex<long double> _VFARC & ze) {*this = cetocd( ze );}
        #else  // Optima++ doesn't like "explicit"
            complex (complex<long double> _VFARC & ze);
        #endif
    #endif
		  // simple assignments: no OVERFLOW error handling
    complex<double> _VFAR & __cmo  operator= (complex<float> _VFARC &);
    complex<double> _VFAR & __cmo  operator= (complex<double> _VFARC &);
    complex<double> _VFAR & __cmo  operator= (complex<long double> _VFARC &);
    complex<double> _VFAR & __cmo  operator= (float);
    complex<double> _VFAR & __cmo  operator= (double);
    complex<double> _VFAR & __cmo  operator= (long double);

    // Cartesian complex from polar coordinates:
    friend complex<double> __cmf polar(double __mag, double __angle=0);

    // basic operations:
    double real() { return Re; }                              // real part
    friend double __cmf real(complex<double> _VFARC &_z);
    double imag() { return Im; }                              // imaginary part
    friend double __cmf imag(complex<double> _VFARC &_z);
    friend complex<double> __cmf neg(complex<double> _VFARC &); // same as unary operator -
    friend complex<double> __cmf conj(complex<double> _VFARC &);// complex conjugate
    friend double  __cmf norm(complex<double>);         // square of the magnitude
    friend double  __cmf arg(complex<double>);          // the angle in the plane

     // Unary operators
    complex<double> _VFAR & __cmo operator+();
    friend complex<double>  __cmf operator-( complex<double> _VFARC &);

        // Binary operators:
    friend complex<double> __cmf operator+(complex<double> _VFARC &, complex<double> _VFARC &);
    friend complex<double> __cmf operator+(double, complex<double> _VFARC &);
    friend complex<double> __cmf operator+(complex<double> _VFARC &, double);
    friend complex<double> __cmf operator-(complex<double> _VFARC &, complex<double> _VFARC &);
    friend complex<double> __cmf operator-(double, complex<double> _VFARC &);
    friend complex<double> __cmf operator-(complex<double> _VFARC &, double);
    friend complex<double> __cmf operator*(complex<double> _VFARC &, complex<double> _VFARC &);
    friend complex<double> __cmf operator*(complex<double> _VFARC &, double);
    friend complex<double> __cmf operator*(double, complex<double> _VFARC &);
    friend complex<double> __cmf operator/(complex<double> _VFARC &, complex<double> _VFARC &);
    friend complex<double> __cmf operator/(complex<double> _VFARC &, double);
    friend complex<double> __cmf operator/(double, complex<double> _VFARC &);
        // float-double mixed-accuracy versions:
    friend complex<double> __cmf operator+(complex<float> _VFARC &, complex<double> _VFARC &);
    friend complex<double> __cmf operator+(complex<double> _VFARC &, complex<float> _VFARC &);
    friend complex<double> __cmf operator-(complex<float> _VFARC &, complex<double> _VFARC &);
    friend complex<double> __cmf operator-(complex<double> _VFARC &, complex<float> _VFARC &);
    friend complex<double> __cmf operator*(complex<float> _VFARC &, complex<double> _VFARC &);
    friend complex<double> __cmf operator*(complex<double> _VFARC &, complex<float> _VFARC &);
    friend complex<double> __cmf operator/(complex<float> _VFARC &, complex<double> _VFARC &);
    friend complex<double> __cmf operator/(complex<double> _VFARC &, complex<float> _VFARC &);

    friend VBOOL __cmf operator==(complex<double> _VFARC &, complex<double> _VFARC &);
    friend VBOOL __cmf operator==(complex<double> _VFARC &, double);
    friend VBOOL __cmf operator!=(complex<double> _VFARC &, complex<double> _VFARC &);
    friend VBOOL __cmf operator!=(complex<double> _VFARC &, double);

       //  Compound-assignment operators:
    complex<double> _VFAR & __cmo  operator+= (complex<float> _VFARC &);
    complex<double> _VFAR & __cmo  operator-= (complex<float> _VFARC &);
    complex<double> _VFAR & __cmo  operator*= (complex<float> _VFARC &);
    complex<double> _VFAR & __cmo  operator/= (complex<float> _VFARC &);

    complex<double> _VFAR & __cmo  operator+= (complex<double> _VFARC &);
    complex<double> _VFAR & __cmo  operator-= (complex<double> _VFARC &);
    complex<double> _VFAR & __cmo  operator*= (complex<double> _VFARC &);
    complex<double> _VFAR & __cmo  operator/= (complex<double> _VFARC &);

    complex<double> _VFAR & __cmo  operator+= (complex<long double> _VFARC &);
    complex<double> _VFAR & __cmo  operator-= (complex<long double> _VFARC &);
    complex<double> _VFAR & __cmo  operator*= (complex<long double> _VFARC &);
    complex<double> _VFAR & __cmo  operator/= (complex<long double> _VFARC &);

    // Overloaded ANSI C math functions
    friend double          __cmf abs(complex<double>);
    friend complex<double> __cmf acos(complex<double>);
    friend complex<double> __cmf asin(complex<double>);
    friend complex<double> __cmf atan(complex<double>);
    friend complex<double> __cmf cos(complex<double>);
    friend complex<double> __cmf cosh(complex<double>);
    friend complex<double> __cmf cubic(complex<double>);  // raise to the third power
    friend complex<double> __cmf exp(complex<double>);
    friend complex<double> __cmf inv(complex<double>);    //   1.0 / z
    friend complex<double> __cmf ipow(complex<double> __base, int __expon);  // integer power
    friend complex<double> __cmf ln(complex<double>);
    friend complex<double> __cmf log(complex<double>); // same as ln
    friend complex<double> __cmf log2(complex<double>);
    friend complex<double> __cmf log10(complex<double>);
    friend complex<double> __cmf pow(complex<double> __base, double __expon);
    friend complex<double> __cmf powReExpo(complex<double> __base, double __expon);
    friend complex<double> __cmf pow(double __base, complex<double> __expon);
    friend complex<double> __cmf powReBase(double __base, complex<double> __expon);
    friend complex<double> __cmf pow(complex<double> __base, complex<double> __expon);
    friend complex<double> __cmf quartic(complex<double>);  // raise to the fourth power
    friend complex<double> __cmf sin(complex<double>);
    friend complex<double> __cmf sinh(complex<double>);
    friend complex<double> __cmf sqrt(complex<double>);
    friend complex<double> __cmf square(complex<double>);
    friend complex<double> __cmf tan(complex<double>);
    friend complex<double> __cmf tanh(complex<double>);

    friend istream _VFAR & __cmf operator>> (istream _VFAR &, complex<double> _VFAR &);
    friend ostream _VFAR & __cmf operator<< (ostream _VFAR &, complex<double> _VFARC &);

    double Re, Im;  // still public!
};

CMATH_NEW_TEMPLATE class complex<long double>
{
  public:
         // constructors:
    #if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
        complex( long double Re_part, long double Im_part ) {Re=Re_part; Im=Im_part;}
        complex( long double Re_part )  {Re=Re_part; Im=0;}
        complex() {};
            // interconversions between the three levels of accuracy:
        complex (complex<float> _VFARC &);
        complex (complex<double> _VFARC &);
    #else // problems with the template definitions in older BC versions
        complex<long double>( long double Re_part, long double Im_part ) {Re=Re_part; Im=Im_part;}
        complex<long double>( long double Re_part )  {Re=Re_part; Im=0;}
        complex<long double>() {};
				// interconversions between the three levels of accuracy:
        complex<long double> (complex<float> _VFARC & zf) {Re = zf.Re; Im = zf.Im;}
        complex<long double> (complex<double> _VFARC & zd) {Re = zd.Re; Im = zd.Im;}
    #endif
    #if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
        complex (complex<long double> _VFARC &);
    #endif
		  // simple assignments do the same:
    complex<long double> _VFAR & __cmo  operator=  (complex<float> _VFARC &);
    complex<long double> _VFAR & __cmo  operator=  (complex<double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator=  (complex<long double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator=  (float);
    complex<long double> _VFAR & __cmo  operator=  (double);
    complex<long double> _VFAR & __cmo  operator=  (long double);

		  // Cartesian complex from polar coordinates:
    friend complex<long double> __cmf polar(long double __mag, long double __angle=0);
        // basic operations:
    long double real() { return Re; }                              // real part
    friend long double __cmf real(complex<long double> _VFARC &_z);
    long double imag() { return Im; }                              // imaginary part
    friend long double __cmf imag(complex<long double> _VFARC &_z);
    friend complex<long double> __cmf neg(complex<long double> _VFARC &); // same as unary operator -
    friend complex<long double> __cmf conj(complex<long double> _VFARC &);// complex conjugate
    friend long double  __cmf norm(complex<long double>);         // square of the magnitude
    friend long double  __cmf arg(complex<long double>);          // the angle in the plane

     // Unary operators
    complex<long double> _VFAR & __cmo operator+();
    friend complex<long double>  __cmf operator-( complex<long double> _VFARC &);

        // Binary operators:
    friend complex<long double> __cmf operator+(complex<long double> _VFARC &, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator+(long double, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator+(complex<long double> _VFARC &, long double);
    friend complex<long double> __cmf operator-(complex<long double> _VFARC &, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator-(long double, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator-(complex<long double> _VFARC &, long double);
    friend complex<long double> __cmf operator*(complex<long double> _VFARC &, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator*(complex<long double> _VFARC &, long double);
    friend complex<long double> __cmf operator*(long double, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator/(complex<long double> _VFARC & __dividend,
                                                complex<long double> _VFARC & __divisor);
    friend complex<long double> __cmf operator/(complex<long double> _VFARC &, long double );
    friend complex<long double> __cmf operator/(long double __dividend,
                                                complex<long double> _VFARC &__divisor);
        // mixed-accuracy versions:
    friend complex<long double> __cmf operator+(complex<float> _VFARC &, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator+(complex<long double> _VFARC &, complex<float> _VFARC &);
    friend complex<long double> __cmf operator+(complex<double> _VFARC &, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator+(complex<long double> _VFARC &, complex<double> _VFARC &);
    friend complex<long double> __cmf operator-(complex<float> _VFARC &, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator-(complex<long double> _VFARC &, complex<float> _VFARC &);
    friend complex<long double> __cmf operator-(complex<double> _VFARC &, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator-(complex<long double> _VFARC &, complex<double> _VFARC &);
    friend complex<long double> __cmf operator*(complex<float> _VFARC &, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator*(complex<long double> _VFARC &, complex<float> _VFARC &);
    friend complex<long double> __cmf operator*(complex<double> _VFARC &, complex<long double> _VFARC &);
    friend complex<long double> __cmf operator*(complex<long double> _VFARC &, complex<double> _VFARC &);
    friend complex<long double> __cmf operator/(complex<long double> _VFARC & __dividend,
                                                complex<float> _VFARC & __divisor);
    friend complex<long double> __cmf operator/(complex<long double> _VFARC & __dividend,
                                                complex<double> _VFARC & __divisor);
    friend complex<long double> __cmf operator/(complex<float> _VFARC & __dividend,
                                                complex<long double> _VFARC & __divisor);
    friend complex<long double> __cmf operator/(complex<double> _VFARC & __dividend,
                                                complex<long double> _VFARC & __divisor);

    friend VBOOL __cmf operator==(complex<long double> _VFARC &, complex<long double> _VFARC &);
    friend VBOOL __cmf operator==(complex<long double> _VFARC &, long double);
    friend VBOOL __cmf operator!=(complex<long double> _VFARC &, complex<long double> _VFARC &);
    friend VBOOL __cmf operator!=(complex<long double> _VFARC &, long double);

       //  Compound-assignment operators:
    complex<long double> _VFAR & __cmo  operator+= (complex<float> _VFARC &);
    complex<long double> _VFAR & __cmo  operator-= (complex<float> _VFARC &);
    complex<long double> _VFAR & __cmo  operator*= (complex<float> _VFARC &);
    complex<long double> _VFAR & __cmo  operator/= (complex<float> _VFARC &);

    complex<long double> _VFAR & __cmo  operator+= (complex<double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator-= (complex<double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator*= (complex<double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator/= (complex<double> _VFARC &);

    complex<long double> _VFAR & __cmo  operator+= (complex<long double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator-= (complex<long double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator*= (complex<long double> _VFARC &);
    complex<long double> _VFAR & __cmo  operator/= (complex<long double> _VFARC &);

    // Overloaded ANSI C math functions
    friend long double          __cmf abs(complex<long double>);
    friend complex<long double> __cmf acos(complex<long double>);
    friend complex<long double> __cmf asin(complex<long double>);
    friend complex<long double> __cmf atan(complex<long double>);
    friend complex<long double> __cmf cos(complex<long double>);
    friend complex<long double> __cmf cosh(complex<long double>);
    friend complex<long double> __cmf cubic(complex<long double>);  // raise to the third power
    friend complex<long double> __cmf exp(complex<long double>);
    friend complex<long double> __cmf inv(complex<long double>);    //   1.0 / z
    friend complex<long double> __cmf ipow(complex<long double> __base, int __expon);  // integer power
    friend complex<long double> __cmf ln(complex<long double>);
    friend complex<long double> __cmf log(complex<long double>); // same as ln
    friend complex<long double> __cmf log2(complex<long double>);
    friend complex<long double> __cmf log10(complex<long double>);
    friend complex<long double> __cmf pow(complex<long double> __base, long double __expon);
    friend complex<long double> __cmf powReExpo(complex<long double> __base, long double __expon);
    friend complex<long double> __cmf pow(long double __base, complex<long double> __expon);
    friend complex<long double> __cmf powReBase(long double __base, complex<long double> __expon);
    friend complex<long double> __cmf pow(complex<long double> __base, complex<long double> __expon);
    friend complex<long double> __cmf quartic(complex<long double>);  // raise to the fourth power
    friend complex<long double> __cmf sin(complex<long double>);
    friend complex<long double> __cmf sinh(complex<long double>);
    friend complex<long double> __cmf sqrt(complex<long double>);
    friend complex<long double> __cmf square(complex<long double>);
    friend complex<long double> __cmf tan(complex<long double>);
    friend complex<long double> __cmf tanh(complex<long double>);

    friend istream _VFAR & __cmf operator>> (istream _VFAR &,
                                             complex<long double> _VFAR &);
    friend ostream _VFAR & __cmf operator<< (ostream _VFAR &,
                                             complex<long double> _VFARC &);
    long double Re, Im; // still public!
};
#ifndef _CMATH_DEFS
    #ifdef __BORLANDC__
        typedef long double extended;
    #else
        typedef double extended;
    #endif
    typedef complex<float>      fComplex;
    typedef complex<double>     dComplex;
    typedef complex<extended>   eComplex; // for MSVC, this will be complex<double>, not complex<long double> !
    #define _CMATH_DEFS
    #define _CMATH_CLASSDEFS
#endif  // _CMATH_DEFS

// inline-implementation of the simple functions and operators
// cannot use templates here, as several compilers do not allow template
// implementations of functions already declared specialized

//  data-type interconverting constructors:
//  in the down-conversions, OVERFLOW errors are handled via _matherr
#if !defined __BORLANDC__ || __BORLANDC__ >= 0x450
    inline complex<float>::complex (complex<double> _VFARC & zd){ *this = cdtocf( zd ); }
    inline complex<float>::complex (complex<long double> _VFARC & ze){*this = cetocf( ze );}
    inline complex<double>::complex (complex<float> _VFARC & zf){Re = zf.Re; Im = zf.Im; }
    inline complex<double>::complex (complex<long double> _VFARC & ze){*this = cetocd( ze );}
    inline complex<long double>::complex (complex<float> _VFARC & zf){Re=zf.Re; Im=zf.Im;}
    inline complex<long double>::complex (complex<double> _VFARC & zd){Re=zd.Re; Im=zd.Im;}
#endif
#if !defined _MSC_VER && (!defined __BORLANDC__ || __BORLANDC__ > 0x500)
    inline complex<float>::complex (complex<float> _VFARC & zf){ Re = zf.Re; Im = zf.Im;}
    inline complex<double>::complex (complex<double> _VFARC & zd){Re = zd.Re; Im = zd.Im; }
    inline complex<long double>::complex (complex<long double> _VFARC & ze){Re=ze.Re; Im=ze.Im;}
#endif

//  simple assignments:
inline complex<float> _VFAR & __cmo complex<float>::operator= (complex<float> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<float> _VFAR & complex<float>::operator= (complex<double> _VFARC & __z)
{   Re = (float) __z.Re; Im = (float) __z.Im; return *this; }
inline complex<float> _VFAR & complex<float>::operator= (complex<long double> _VFARC & __z)
{   Re = (float) __z.Re; Im = (float) __z.Im; return *this; }
inline complex<float> _VFAR & __cmo complex<float>::operator= (float __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<float> _VFAR & complex<float>::operator= (double __zRe)
{   Re = (float) __zRe; Im = 0; return *this; }
inline complex<float> _VFAR & complex<float>::operator= (long double __zRe)
{   Re = (float) __zRe; Im = 0; return *this; }
inline complex<double> _VFAR & complex<double>::operator= (complex<float> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<double> _VFAR & complex<double>::operator= (complex<double> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<double> _VFAR & complex<double>::operator= (complex<long double> _VFARC & __z)
{   Re = (double) __z.Re; Im = (double) __z.Im; return *this; }
inline complex<double> _VFAR & complex<double>::operator= (float __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<double> _VFAR & complex<double>::operator= (double __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<double> _VFAR & complex<double>::operator= (long double __zRe)
{   Re = (double) __zRe; Im = 0; return *this; }
inline complex<long double> _VFAR & complex<long double>::operator= (complex<float> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<long double> _VFAR & complex<long double>::operator= (complex<double> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<long double> _VFAR & complex<long double>::operator= (complex<long double> _VFARC & __z)
{   Re = __z.Re; Im = __z.Im; return *this; }
inline complex<long double> _VFAR & complex<long double>::operator= (float __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<long double> _VFAR & complex<long double>::operator= (double __zRe)
{   Re = __zRe; Im = 0; return *this; }
inline complex<long double> _VFAR & complex<long double>::operator= (long double __zRe)
{   Re = __zRe; Im = 0; return *this; }

// basic operations:
inline float       __cmf real( complex<float> _VFARC & __z) { return __z.Re; }
inline double      __cmf real( complex<double> _VFARC & __z) { return __z.Re; }
inline long double __cmf real( complex<long double> _VFARC & __z) { return __z.Re; }
inline float       __cmf imag( complex<float> _VFARC & __z) { return __z.Im; }
inline double      __cmf imag( complex<double> _VFARC & __z) { return __z.Im; }
inline long double __cmf imag( complex<long double> _VFARC & __z) { return __z.Im; }

inline complex<float>     __cmf neg( complex<float> _VFARC & __z )
{   return complex<float>(-__z.Re, -__z.Im); }

inline complex<double>     __cmf neg( complex<double> _VFARC & __z )
{   return complex<double>(-__z.Re, -__z.Im); }

inline complex<long double> __cmf neg( complex<long double> _VFARC & __z )
{   return complex<long double>(-__z.Re, -__z.Im); }

inline complex<float>     __cmf conj( complex<float> _VFARC & __z )
{   return complex<float>(__z.Re, -__z.Im); }

inline complex<double>     __cmf conj( complex<double> _VFARC & __z )
{   return complex<double>(__z.Re, -__z.Im); }

inline complex<long double> __cmf conj( complex<long double> _VFARC & __z )
{   return complex<long double>(__z.Re, -__z.Im); }

         // Unary operators:
inline complex<float> _VFAR & __cmo complex<float>::operator+()
{   return (*this); }

inline complex<double> _VFAR & __cmo complex<double>::operator+()
{   return (*this); }

inline complex<long double> _VFAR & __cmo complex<long double>::operator+()
{   return (*this); }

inline complex<float> __cmf operator-( complex<float> _VFARC & __z)
{   return complex<float>(-__z.Re, -__z.Im); }

inline complex<double> __cmf operator-( complex<double> _VFARC & __z)
{   return complex<double>(-__z.Re, -__z.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z)
{   return complex<long double>(-__z.Re, -__z.Im); }

                // Binary operators:
inline complex<float> __cmf operator+( complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<float>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<float> __cmf operator+( complex<float> _VFARC & __z1, float __z2Re )
{   return complex<float>(__z1.Re+__z2Re, __z1.Im); }

inline complex<float> __cmf operator+( float __z1Re, complex<float> _VFARC & __z2 )
{   return complex<float>(__z1Re + __z2.Re, __z2.Im); }

inline complex<float> __cmf operator-( complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<float>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<float> __cmf operator-( complex<float> _VFARC & __z1, float __z2Re )
{   return complex<float>(__z1.Re - __z2Re, __z1.Im); }

inline complex<float> __cmf operator-( float __z1Re, complex<float> _VFARC & __z2 )
{   return complex<float>(__z1Re - __z2.Re, -__z2.Im); }

inline complex<float> __cmf operator*( complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<float>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                           __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<float> __cmf operator*( complex<float> _VFARC & __z1, float __z2Re )
{   return complex<float>( __z1.Re * __z2Re, __z1.Im * __z2Re ); }

inline complex<float> __cmf operator*( float __z1Re, complex<float> _VFARC & __z2 )
{   return complex<float>( __z1Re * __z2.Re, __z1Re * __z2.Im ); }

inline complex<float> __cmf operator/( complex<float> _VFARC & __dividend,
                                       complex<float> _VFARC & __divisor )
{     complex<float> Result;
      double denom;
      Result.Re = (float)((__dividend.Re *__divisor.Re +
                           __dividend.Im *__divisor.Im) /
         (denom = (double)(__divisor.Re) * __divisor.Re +
                  (double)(__divisor.Im) * __divisor.Im));
      Result.Im = (float)((__dividend.Im * __divisor.Re -
                           __dividend.Re * __divisor.Im ) / denom);
      return Result;
}
inline complex<float> __cmf operator/( complex<float> _VFARC & __dividend, float __divisorRe)
{   return complex<float>( __dividend.Re / __divisorRe, __dividend.Im / __divisorRe ); }

inline complex<float> __cmf operator /( float __dividendRe,
                                        complex<float> _VFARC & __divisor )
{     complex<float> Result;
      double         denom;
      Result.Re = (float)((__dividendRe * __divisor.Re) /
        (denom = (double)(__divisor.Re) * __divisor.Re +
                 (double)(__divisor.Im) * __divisor.Im));
      Result.Im = -(float)((__dividendRe * __divisor.Im ) / denom);
      return Result;
}

inline complex<double> __cmf operator+( complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<double> __cmf operator+( complex<double> _VFARC & __z1, double __z2Re )
{   return complex<double>(__z1.Re+__z2Re, __z1.Im); }

inline complex<double> __cmf operator+( double __z1Re, complex<double> _VFARC & __z2 )
{   return complex<double>(__z1Re + __z2.Re, __z2.Im); }

inline complex<double> __cmf operator-( complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<double> __cmf operator-( complex<double> _VFARC & __z1, double __z2Re )
{   return complex<double>(__z1.Re - __z2Re, __z1.Im); }

inline complex<double> __cmf operator-( double __z1Re, complex<double> _VFARC & __z2 )
{   return complex<double>(__z1Re - __z2.Re, -__z2.Im); }

inline complex<double> __cmf operator*( complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                           __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<double> __cmf operator*( complex<double> _VFARC & __z1, double __z2Re )
{   return complex<double>( __z1.Re * __z2Re, __z1.Im * __z2Re ); }

inline complex<double> __cmf operator*( double __z1Re, complex<double> _VFARC & __z2 )
{   return complex<double>( __z1Re * __z2.Re, __z1Re * __z2.Im ); }

inline complex<double> __cmf operator/( complex<double> _VFARC & __dividend, double __divisorRe)
{   return complex<double>( __dividend.Re / __divisorRe, __dividend.Im / __divisorRe ); }

inline complex<long double> __cmf operator+( complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<long double> _VFARC & __z1, long double __z2Re )
{   return complex<long double>(__z1.Re+__z2Re, __z1.Im); }

inline complex<long double> __cmf operator+( long double __z1Re, complex<long double> _VFARC & __z2 )
{   return complex<long double>(__z1Re + __z2.Re, __z2.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z1, long double __z2Re )
{   return complex<long double>(__z1.Re - __z2Re, __z1.Im); }

inline complex<long double> __cmf operator-( long double __z1Re, complex<long double> _VFARC & __z2 )
{   return complex<long double>(__z1Re - __z2.Re, -__z2.Im); }

inline complex<long double> __cmf operator*( complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                           __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<long double> _VFARC & __z1, long double __z2Re )
{   return complex<long double>( __z1.Re * __z2Re, __z1.Im * __z2Re ); }

inline complex<long double> __cmf operator*( long double __z1Re, complex<long double> _VFARC & __z2 )
{   return complex<long double>( __z1Re * __z2.Re, __z1Re * __z2.Im ); }

inline complex<long double> __cmf operator/( complex<long double> _VFARC & __dividend, long double __divisorRe)
{   return complex<long double>( __dividend.Re / __divisorRe, __dividend.Im / __divisorRe ); }
    //  operator / (complex<double>, complex<double> ) and
    //  operator / (complex<long double>, complex<long double> ) 
    //  cannot safely be inlined

    // Mixed-accuracy level binary operators:
inline complex<double> __cmf operator+( complex<float> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<double> __cmf operator+( complex<double> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<float> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<long double> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<long double> __cmf operator+( complex<long double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<long double>(__z1.Re + __z2.Re, __z1.Im + __z2.Im); }

inline complex<double> __cmf operator-( complex<float> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<double> __cmf operator-( complex<double> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<float> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<long double> __cmf operator-( complex<long double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return complex<long double>(__z1.Re - __z2.Re, __z1.Im - __z2.Im); }

inline complex<double> __cmf operator*( complex<float> _VFARC & __z1, complex<double> _VFARC & __z2 )
{   return complex<double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                            __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<double> __cmf operator*( complex<double> _VFARC & __z1, complex<float> _VFARC & __z2 )
{   return complex<double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                            __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<float> _VFARC & __z1, complex<long double> _VFARC & __z2 )
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                                 __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<long double> _VFARC & __z1, complex<float> _VFARC & __z2 )
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                                 __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<double> _VFARC & __z1, complex<long double> _VFARC & __z2 )
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                                 __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}
inline complex<long double> __cmf operator*( complex<long double> _VFARC & __z1, complex<double> _VFARC & __z2 )
{   return complex<long double>( __z1.Re * __z2.Re - __z1.Im * __z2.Im,
                                 __z1.Re * __z2.Im + __z1.Im * __z2.Re );
}

inline complex<double> __cmf operator/( complex<double> _VFARC & __dividend,
                                        complex<float>  _VFARC & __divisor )
{     complex<double> Result;
      double          denom;
      Result.Re = (__dividend.Re *__divisor.Re +
                   __dividend.Im *__divisor.Im) /
         (denom = (double)(__divisor.Re) * __divisor.Re +
                  (double)(__divisor.Im) * __divisor.Im);
      Result.Im = (__dividend.Im * __divisor.Re -
                   __dividend.Re * __divisor.Im ) / denom;
      return Result;
}

inline complex<long double> __cmf operator/( complex<long double> _VFARC & __dividend,
                                             complex<float>  _VFARC & __divisor )
{     complex<long double> Result;
      double               denom;
      Result.Re = (__dividend.Re *__divisor.Re +
                   __dividend.Im *__divisor.Im) /
         (denom = (double)(__divisor.Re) * __divisor.Re +
                  (double)(__divisor.Im) * __divisor.Im);
      Result.Im = (__dividend.Im * __divisor.Re -
                   __dividend.Re * __divisor.Im ) / denom;
      return Result;
}

inline VBOOL __cmf operator== (complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return __z1.Re == __z2.Re && __z1.Im == __z2.Im; }

inline VBOOL __cmf operator== (float __z1Re, complex<float> _VFARC & __z2)
{   return __z1Re == __z2.Re && __z2.Im == 0; }

inline VBOOL __cmf operator== (complex<float> _VFARC & __z1, float __z2Re)
{   return __z1.Re == __z2Re && __z1.Im == 0; }

inline VBOOL __cmf operator!= (complex<float> _VFARC & __z1, complex<float> _VFARC & __z2)
{   return __z1.Re != __z2.Re || __z1.Im != __z2.Im; }

inline VBOOL __cmf operator!= (float __z1Re, complex<float> _VFARC & __z2)
{   return __z1Re != __z2.Re || __z2.Im != 0; }

inline VBOOL __cmf operator!= (complex<float> _VFARC & __z1, float __z2Re)
{   return __z1.Re != __z2Re || __z1.Im != 0; }

inline VBOOL __cmf operator== (complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return __z1.Re == __z2.Re && __z1.Im == __z2.Im; }

inline VBOOL __cmf operator== (double __z1Re, complex<double> _VFARC & __z2)
{   return __z1Re == __z2.Re && __z2.Im == 0; }

inline VBOOL __cmf operator== (complex<double> _VFARC & __z1, double __z2Re)
{   return __z1.Re == __z2Re && __z1.Im == 0; }

inline VBOOL __cmf operator!= (complex<double> _VFARC & __z1, complex<double> _VFARC & __z2)
{   return __z1.Re != __z2.Re || __z1.Im != __z2.Im; }

inline VBOOL __cmf operator!= (double __z1Re, complex<double> _VFARC & __z2)
{   return __z1Re != __z2.Re || __z2.Im != 0; }

inline VBOOL __cmf operator!= (complex<double> _VFARC & __z1, double __z2Re)
{   return __z1.Re != __z2Re || __z1.Im != 0; }

inline VBOOL __cmf operator== (complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return __z1.Re == __z2.Re && __z1.Im == __z2.Im; }

inline VBOOL __cmf operator== (long double __z1Re, complex<long double> _VFARC & __z2)
{   return __z1Re == __z2.Re && __z2.Im == 0; }

inline VBOOL __cmf operator== (complex<long double> _VFARC & __z1, long double __z2Re)
{   return __z1.Re == __z2Re && __z1.Im == 0; }

inline VBOOL __cmf operator!= (complex<long double> _VFARC & __z1, complex<long double> _VFARC & __z2)
{   return __z1.Re != __z2.Re || __z1.Im != __z2.Im; }

inline VBOOL __cmf operator!= (long double __z1Re, complex<long double> _VFARC & __z2)
{   return __z1Re != __z2.Re || __z2.Im != 0; }

inline VBOOL __cmf operator!= (complex<long double> _VFARC & __z1, long double __z2Re)
{   return __z1.Re != __z2Re || __z1.Im != 0; }

      // Compound-assignment operators:
inline complex<float> _VFAR & __cmo complex<float>::operator+= (complex<float> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator+= (complex<double> _VFARC & __s2)
{   Re = (float)(Re + __s2.Re); Im = (float) (Im + __s2.Im); return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator+= (complex<long double> _VFARC & __s2)
{   Re = (float)(Re + __s2.Re); Im = (float) (Im + __s2.Im); return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator+= (complex<float> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator+= (complex<double> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator+= (complex<long double> _VFARC & __s2)
{   Re = (double)(Re + __s2.Re); Im = (double) (Im + __s2.Im); return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator+= (complex<float> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator+= (complex<double> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator+= (complex<long double> _VFARC & __s2)
{   Re += __s2.Re; Im += __s2.Im; return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator-= (complex<float> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator-= (complex<double> _VFARC & __s2)
{   Re = (float)(Re - __s2.Re); Im = (float) (Im - __s2.Im); return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator-= (complex<long double> _VFARC & __s2)
{   Re = (float)(Re - __s2.Re); Im = (float) (Im - __s2.Im); return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator-= (complex<float> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator-= (complex<double> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<double> _VFAR & __cmo complex<double>::operator-= (complex<long double> _VFARC & __s2)
{   Re = (double)(Re - __s2.Re); Im = (double) (Im - __s2.Im); return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator-= (complex<float> _VFARC & __s2)
{    Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator-= (complex<double> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<long double> _VFAR & __cmo complex<long double>::operator-= (complex<long double> _VFARC & __s2)
{   Re -= __s2.Re; Im -= __s2.Im; return *this; }

inline complex<float> _VFAR & __cmo complex<float>::operator*= (complex<float> _VFARC & __fac2)
{   float tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im          = Im * __fac2.Re + Re * __fac2.Im;
    Re          = tmpRe;
    return *this;
}

inline complex<float> _VFAR & __cmo complex<float>::operator*= (complex<double> _VFARC & __fac2)
{   float tmpRe = (float) (Re * __fac2.Re - Im * __fac2.Im);
    Im          = (float) (Im * __fac2.Re + Re * __fac2.Im);
    Re          = tmpRe;
    return *this;
}

inline complex<float> _VFAR & __cmo complex<float>::operator*= (complex<long double> _VFARC & __fac2)
{   float tmpRe = (float) (Re * __fac2.Re - Im * __fac2.Im);
    Im          = (float) (Im * __fac2.Re + Re * __fac2.Im);
    Re          = tmpRe;
    return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator*= (complex<float> _VFARC & __fac2)
{   double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im           = Im * __fac2.Re + Re * __fac2.Im;
    Re           = tmpRe;
    return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator*= (complex<double> _VFARC & __fac2)
{   double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im           = Im * __fac2.Re + Re * __fac2.Im;
    Re           = tmpRe;
    return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator*= (complex<long double> _VFARC & __fac2)
{   double tmpRe = (double) (Re * __fac2.Re - Im * __fac2.Im);
    Im           = (double) (Im * __fac2.Re + Re * __fac2.Im);
    Re           = tmpRe;
    return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator*= (complex<float> _VFARC & __fac2)
{   long double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im                = Im * __fac2.Re + Re * __fac2.Im;
    Re                = tmpRe;
    return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator*= (complex<double> _VFARC & __fac2)
{   long double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im                = Im * __fac2.Re + Re * __fac2.Im;
    Re                = tmpRe;
    return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator*= (complex<long double> _VFARC & __fac2)
{   long double tmpRe = Re * __fac2.Re - Im * __fac2.Im;
    Im                = Im * __fac2.Re + Re * __fac2.Im;
    Re                = tmpRe;
    return *this;
}

inline complex<float> _VFAR & __cmo complex<float>::operator/= (complex<float> _VFARC & __divisor)
{     double denom;
      float  tmpRe = (float)((Re * __divisor.Re + Im * __divisor.Im) /
            (denom = (double)(__divisor.Re) * __divisor.Re +
                     (double)(__divisor.Im) * __divisor.Im));
      Im = (float)((Im * __divisor.Re - Re * __divisor.Im ) / denom);
      Re = tmpRe;
      return *this;
}

inline complex<double> _VFAR & __cmo complex<double>::operator/= (complex<float> _VFARC & __divisor)
{     double denom;
      double tmpRe = (double)((Re * __divisor.Re + Im * __divisor.Im) /
            (denom = (double)(__divisor.Re) * __divisor.Re +
                     (double)(__divisor.Im) * __divisor.Im));
      Im = (Im * __divisor.Re - Re * __divisor.Im ) / denom;
      Re = tmpRe;
      return *this;
}

inline complex<long double> _VFAR & __cmo complex<long double>::operator/= (complex<float> _VFARC & __divisor)
{     double denom;
      long double tmpRe = (Re * __divisor.Re + Im * __divisor.Im) /
                 (denom = (double)(__divisor.Re) * __divisor.Re +
                          (double)(__divisor.Im) * __divisor.Im);
      Im = (Im * __divisor.Re - Re * __divisor.Im ) / denom;
      Re = tmpRe;
      return *this;
}

inline istream _VFAR &  __cmf operator>> (istream _VFAR & is, complex<float> _VFAR & __z)
{   // read a complex number __z in the form r or (r) or {r, i} or (r, i)
    float     r = 0, i = 0;
    char  c;

    is >> c;
    if (c == '(' || c == '{')  // notations (r), (r,i), or {r,i}
    {
        is >> r >> c;
        if (c == ',') { is >> i  >> c;}
        if (c != ')' && c != '}')   is.clear(ios::failbit);
    }
    else  // only real part
    {
        is.putback(c);
        is >> r;
    }
    if (is) { __z.Re = r; __z.Im = i; }
    return is;
}

inline ostream _VFAR &  __cmf operator<< (ostream _VFAR & os, complex<float> _VFARC & __z)
{   return (os << "{" << __z.Re << "," << __z.Im << "}"); }

inline istream _VFAR &  __cmf operator>> (istream _VFAR & is, complex<double> _VFAR & __z)
{   // read a complex number __z in the form r or (r) or {r, i} or (r, i)
    double     r = 0, i = 0;
    char  c;

    is >> c;
    if (c == '(' || c == '{')  // notations (r), (r,i), or {r,i}
    {
        is >> r >> c;
        if (c == ',') { is >> i  >> c;}
        if (c != ')' && c != '}')   is.clear(ios::failbit);
    }
    else  // only real part
    {
        is.putback(c);
        is >> r;
    }
    if (is) { __z.Re = r; __z.Im = i; }
    return is;
}

inline ostream _VFAR &  __cmf operator<< (ostream _VFAR & os, complex<double> _VFARC & __z)
{   return (os << "{" << __z.Re << "," << __z.Im << "}"); }

inline istream _VFAR &  __cmf operator>> (istream _VFAR & is, complex<long double> _VFAR & __z)
{   // read a complex number __z in the form r or (r) or {r, i} or (r, i)
    long double     r = 0, i = 0;
    char  c;

    is >> c;
    if (c == '(' || c == '{')  // notations (r), (r,i), or {r,i}
    {
        is >> r >> c;
        if (c == ',') { is >> i  >> c;}
        if (c != ')' && c != '}')   is.clear(ios::failbit);
    }
    else  // only real part
    {
        is.putback(c);
        is >> r;
    }
    if (is) { __z.Re = r; __z.Im = i; }
    return is;
}

inline ostream _VFAR &  __cmf operator<< (ostream _VFAR & os, complex<long double> _VFARC & __z)
{   return (os << "{" << __z.Re << "," << __z.Im << "}"); }

#endif // CMATH_CLASSIC_COMPLEX
#ifdef __BORLANDC__
      #pragma option -a.
#else /* Visual C++ */
      #pragma pack( pop )
#endif    /* restore default data packing  */

       // error handling functions, borrowed from VectorLib:
extern "C" {
void  __cmf  V_noteError( char _VFAR *fname, unsigned why );
void  __cmf  V_printErrorMsg( char _VFAR *ErrMsg );
void  __cmf  V_setErrorEventFile( char _VFAR *filename,  unsigned ScreenAndFile );
void  __cmf  V_closeErrorEventFile( void );

/*** translation of calls to matherr() into _matherr() for BorlandC 4.0+ ***
 ***  (necessary only to maintain compatibility with BorlandC 3.x)       ***/

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
}  // end of extern "C" statement

#undef VBOOL
#undef CMATH_NEW_TEMPLATE
#undef __cmf
#undef __cmo
typedef fComplex fcomplex;
typedef dComplex dcomplex;
typedef eComplex ecomplex;  // tolerate all-lower case
#endif  // __NEWCPLX_H
