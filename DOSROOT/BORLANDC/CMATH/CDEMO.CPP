/*************************   CDEMO.CPP   *********************************
*                                                                        *
*                Simple Demo Program for                                 *
*                       C M A T H                                        *
*                                                                        *
*       Copyright 1996-2000 by Martin Sander                             *
*                                                                        *
*       This sample program provides a very basic test                   *
*       for the correct installation of CMATH                            *
*       and for correct error handling.                                  *
*                                                                        *
**************************************************************************/
/*
Borland C++, 32-bit command-line compiler:
    1. Go to your CMATH or OptiVec directory.
    2. Be sure, your Borland C++ BIN directory is contained in the
       PATH statement in your AUTOEXEC.BAT.
    3. a) 32-bit: type
               BCC32 -Iinclude cdemo.cpp lib\cmathf3w.lib
          If you got CMATH as a part of OptiVec, use vcf3w.lib
          instead of cmathf3w.lib.
       b) 16-bit DOS: type
               BCC -ml -Iinclude cdemo.cpp lib\cmathl3.lib
    4. Run the program by typing:  cdemo

    In the 32-bit Windows version, don't wonder about the math
    error message being displayed in a message box, rather than
    being printed to the console. This is because there is only
    one version of CMATH, simultaneously for GUI and console
    applications.

Borland C++ or Visual C++ IDE:
    Create a project with the following entries:
    CDEMO.CPP
    CMATHL3.LIB (Borland C++, DOS),
    or CMATHL3W.LIB (Borland C++, Windows 3.x, EasyWin),
    or VCF3W.LIB or CMATHF3W.LIB (Borland C++, Win32, console model;
                            choose static linking and single-thread)
    or OVVCSD.LIB or CMVCSD.LIB (Microsoft Visual C++; Win32 console app;
                            choose single-thread debug)

    Additionally, you have to link in the standard run-time libraries
    (BC++ 3.x:            use Options/Linker/Libraries;
     BC++ 4.x, 5.x, etc.: use TargetExpert;
     MSVC:                done automatically)

    The include-file search path must contain
    \YourCMATHDirectory\include;
    The library search path must contain
    \YourCMATHDirectory\lib;
    (in addition to the compiler's default settings).
*/

#include <newcplx.h>
#include <stdio.h>

NEWMATHERR    // this macro has an effect only in BC, 16-bit 
int main( void )
{
    fComplex x, y;
    x = sin( fComplex( 3, 5));
    y = inv( fComplex(0,0));  // will produce an error message
    printf( "The sine of  { 3.0, 5.0 } is {%f, %f}\n"
            "Complex 1/0 situations yield {%g, %g}\n",
            x.Re, x.Im, y.Re, y.Im );
    return 0;
}
