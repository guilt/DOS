/*******************************   VDEMO.CPP *****************************
*                                                                        *
*                    Sample program for the demonstration                *
*                    of VectorLib for Borland C/C++                      *
*                    for DOS                                             *
*                                                                        *
*       Copyright 1993-1998 by Martin Sander                             *
*                                                                        *
**************************************************************************/
#define BGIDIR "..\\BGI\\"  // this must be the path to the BGI directory!
#include <VEstd.h>
#include <VEmath.h>
#include <VCEstd.h>
#include <VCEmath.h>
#include <Vgraph.h>
#include <math.h>
#include <DOS.h>
#include <conio.h>
#include <stdlib.h>

struct time    t1, t2;
void starttime( void )
{
   gettime( &t1 );
}

double stoptime( void )
{
   double         tBegin, tEnd;
   gettime( &t2 );
   tBegin = t1.ti_min * 60L + t1.ti_sec + t1.ti_hund * 0.01;
   tEnd   = t2.ti_min * 60L + t2.ti_sec + t2.ti_hund * 0.01;

   return( tEnd - tBegin );
}

extern unsigned _ovrbuffer = 0x0800;
void main( void )
{
   ui             xsize=1024, specsiz=128, csize = 200, i, j;
   eVector        X, Y, Win, Spc, Time, Freq;
   extended       a, b, c;
   ceVector       CX, CY;

   X = VE_vector( xsize );
   Y = VE_vector( xsize );
   printf( "\n\nThis is a short demonstration of VectorLib for C/C++"
   	     "\nin DOS real mode."
           "\nHit any key to continue  or abort with [ESC] !" );
   if( getch() == 27 ) exit(0);

   Spc  = VE_vector( specsiz+1);
   Win  = VE_vector( 2*specsiz );
   Time = VE_vector( xsize );
   Freq = VE_vector( specsiz+1 );

   VE_ramp( Time, xsize, 0, 80*M_PI/xsize );
   VE_ramp( Freq, specsiz+1, 0, (xsize / (80*M_PI)) / specsiz );
            /* get a time axis from 0 to 80 Pi and a corresponding
               frequency axis from 0 to the Nyquist frequency */
   VE_sin( X, Time, xsize );
   VE_cmpC( X, X, xsize, 0.7 ); /* get an asymmetric square wave */
               /* instead of the last two lines, try also, e.g.:
                  VE_noise( X, xsize, 1, 1 );
                  VE_smooth( X, X, xsize, 3 );  */
   V_initGraph( BGIDIR );  /* this must be your correct path! */

   VE_Welch( Win, 2*specsiz );
               /* You might as well take VE_Parzen or VE_Hanning  */
   Spc[specsiz] = VE_spectrum( Spc, specsiz, X, xsize, Win );

   VE_xyAutoPlot( Time, X, 101, PS_SOLID, GREEN );
   printf( "This is a\nPortion of\nan asymmetric\nsquare wave" );
   if( getch() == 27 ) exit(0);
   VE_xyAutoPlot( Freq, Spc, specsiz+1, PS_SOLID | SY_CROSS, GREEN );
   printf( "Power Density\nSpectrum of\nthe same\nsquare wave" );
   if( getch() == 27 ) exit(0);
   V_nfree( 4, Spc, Win, Time, Freq );

   /* let's have a look at complex arithmetics  */
   CX = VCE_vector( csize );
   CY = VCE_vector( csize );
   VCE_ramp( CX, csize, ecplx(M_PI, 0), ecplx(0.2, 0.0005) );
   VCE_sin( CY, CX, csize );
   VCE_cos( CX, CX, csize );
        /*  Try also with other complex functions! */

   VCE_2AutoPlot( CY, csize, PS_SOLID, GREEN,
                  CX, csize, PS_SOLID, RED );
   printf( "Playing with\nfunctions in\nthe complex plane:\n\nGreen: sine,\nRed:   cosine." ); getch();
   V_nfree( 2, CX, CY );
   closegraph();

   VE_ramp( X, xsize, -10, 0.020 );
   a = 1.1;  b = -0.15;  c = 0.02;   /* or any other arbitrary values... */
   printf( "\nTo end this short program, let us make a crude speed comparison"
           "\nbetween compiled code and VectorLib functions."
           "\nE.g., evaluate the exponential function for a whole vector"
           "\n\n          y[i] = c * exp( a * x[i] + b ),     i=0,..,size-1"
           "\n\n(10 runs of 1024 elements each).      Please wait...\n" );
   starttime();
   for( i=0; i<100; i++ )   /* repeat enough times to see the difference */
      for( j=0; j<xsize; j++ )  Y[j] = c * exp( a * X[j] + b );
   printf( "\nExecution Time compiled code:      %lf sec", stoptime() );
      /* now the VectorLib solution to the same simple problem:  */
   starttime();
   for( i=0; i<100; i++ )
      VEx_exp( Y, X, xsize, a, b, c );
   printf( "\nExecution Time VectorLib function: %lf sec", stoptime() );

   printf( "\n\nNormally, the VectorLib function is about two times faster"
   	     "\nthan compiled code. In some environments, up to a factor of 10"
	     "\nmay be gained."
	     "\n\nChange the source code of this example program and try also"
            "\nother mathematical functions, like the sine, the hyperbolic"
		"\nsine, and so on..." );
            getch();
   V_nfree( 2, X, Y );
}

