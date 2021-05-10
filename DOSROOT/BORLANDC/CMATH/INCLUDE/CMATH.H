/*    CMATH.H

      Complex library for the languages C and C++.

      Copyright (c) 1996-2000 by Martin Sander
      Address of the author:
           Dr. Martin Sander Software Dev.
           Steinachstr. 9A
           D-69198 Schriesheim
           Germany
           MartinSander@Bigfoot.com
           http://www.optivec.com

      Some features:
      *  All three precision levels (single, double, extended)
      *  Not only for C++, but also for C.
      *  Uses C++ features only where it really makes sense:
         for the overloading of basic operators and for
         alternative function names independent of data type.
      *  Mathematical functions are implemented in Assembler
         and much more accurate and efficient than those
         of the complex library of normal C++ compilers.
      *  Vectorized versions of all functions are contained
         in VectorLib, separately available from the same
         author.

      Tips:
      1. If you are using only one of the three precision
         levels, you should not include this header file cmath.h,
         but only the one for the precision you chose:
         cfmath.h  for single precision (complex float)
         cdmath.h  for double precision (complex double)
         cemath.h  for extended precision (complex long double)
         This will save you some compile time and some compiler
         buffer memory.
      2. If you want to use the class complex, or the classes
         complex<float>, complex<double>, or complex<long double>
         of the Standard C++ Library, include <newcplx.h> before (!)
         <cmath.h>. Do  n o t  include <complex.h>, which is replaced
         here by <newcplx.h>.

*/

#ifndef __CMATH_H
#define __CMATH_H

#include "cfmath.h"
#include "cdmath.h"
#include "cemath.h"

#endif /*  __CMATH_H  */


