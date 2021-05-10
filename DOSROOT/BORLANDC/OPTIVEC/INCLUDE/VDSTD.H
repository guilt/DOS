/*  VDstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type "double"
  (real numbers)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VDSTD_H
#define __VDSTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

dVector   __vf  VD_vector( ui size );
dVector   __vf  VD_vector0( ui size );

/***************  Addressing single vector elements ******************/

double _VFAR * VD_Pelement( dVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VD_element( X, n )  (*VD_Pelement( X, n ))

/*******************  Initialization **********************************/

void  __vf  VD_equ0( dVector X, ui size );
void  __vf  VD_equ1( dVector X, ui size );
void  __vf  VD_equm1( dVector X, ui size );
void  __vf  VD_equC( dVector X, ui size, double C );
void  __vf  VD_equV( dVector Y, dVector X, ui size );
void  __vf  VDx_equV( dVector Y, dVector X, ui size, double A, double B );
void  __vf  VD_ramp( dVector X, ui size, double Start, double Rise );
void  __vf  VD_Parzen( dVector X, ui size );
void  __vf  VD_Welch( dVector X, ui size );
void  __vf  VD_Hanning( dVector X, ui size );
void  __vf  VD_comb( dVector X, ui size, unsigned step, double C );
long  __vf  VD_random( dVector X, ui size, long seed,
                       double MinVal, double MaxVal );
long  __vf  VD_noise( dVector X, ui size, long seed, double Amp );
            /* VD_random and VD_noise return a new seed value.
               random quality of VD_random is much better      */


/***************  Data-type interconversions  *************************/
       /* for rounding functions, see VDmath.h ! */

void  __vf   V_SItoD(  dVector Y, siVector X, ui size );
void  __vf   V_ItoD(   dVector Y, iVector  X, ui size );
void  __vf   V_LItoD(  dVector Y, liVector X, ui size );
void  __vf   V_QItoD(  dVector Y, qiVector X, ui size );

void  __vf   V_UStoD(  dVector Y, usVector X, ui size );
void  __vf   V_UtoD(   dVector Y, uVector  X, ui size );
void  __vf   V_ULtoD(  dVector Y, ulVector X, ui size );

void  __vf   V_FtoD( dVector Y, fVector X, ui size );
void  __vf   V_DtoF( fVector Y, dVector X, ui size );
#ifdef __BORLANDC__   /* 80-bit IEEE numbers supported */
    void  __vf   V_DtoE( eVector Y, dVector X, ui size );
    void  __vf   V_EtoD( dVector Y, eVector X, ui size );
#else  /* no IEEE number support with Visual C++ */
    #define V_DtoE VD_equV
    #define V_EtoD VD_equV
#endif


/****************  Index-oriented manipulations ***********************/


void  __vf  VD_reflect( dVector X, ui size );
void  __vf  VD_rev( dVector Y, dVector X, ui size );
#if defined (V_HUGE)
    void  __vf  VD_rotate( dVector Y, dVector X, ui size, long pos );
#else
    void  __vf  VD_rotate( dVector Y, dVector X, ui size, int pos );
#endif
void  __vf  VD_delete( dVector X, ui size, ui pos );
void  __vf  VD_insert( dVector X, ui size, ui pos, double C );
void  __vf  VD_sort( dVector Y, dVector X, ui size, int dir );
void  __vf  VD_sortind( uiVector Ind, dVector X, ui size, int dir );
void  __vf  VD_subvector( dVector Y, ui sizey, dVector X, int step );
void  __vf  VD_indpick( dVector Y, uiVector Ind, ui sizey, dVector X );
void  __vf  VD_indput(  dVector Y, dVector X, uiVector Ind, ui sizex );
void  __vf  VD_indpick( dVector Y, uiVector Ind, ui size, dVector X );
ui    __vf  VD_searchC( dVector X, ui size, double C, int mode );
void  __vf  VD_searchV( uiVector Ind, dVector X, ui sizex,
                                     dVector Tab, ui sizetab, int mode );

void  __vf  VD_polyinterpol( dVector Y, dVector X, ui sizex,
                        dVector XTab, dVector YTab, ui sizetab, unsigned deg );
void  __vf  VD_ratinterpol( dVector Y, dVector X, ui sizex,
                        dVector XTab, dVector YTab, ui sizetab, unsigned deg );
void  __vf  VD_splinederiv2( dVector Y2, dVector XTab, dVector YTab,
                            ui size, int specify, double Yp0, double Ypn );
void  __vf  VD_splineinterpol( dVector Y, dVector X, ui sizex,
                    dVector XTab, dVector YTab, dVector Y2Tab, ui sizetab );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VD_subvector_equC(  dVector Y, ui subsiz, unsigned samp, double C );
void  __vf  VD_subvector_equV(  dVector Y, ui subsiz, unsigned samp, dVector X );
    /*   for arithmetic functions of subsets, see <VDmath.h>  */

/**************** One-Dimensional Vector Operations ***********************/

double     __vf  VD_max( dVector X, ui size );
double     __vf  VD_min( dVector X, ui size );
double     __vf  VD_absmax( dVector X, ui size );
double     __vf  VD_absmin( dVector X, ui size );
int        __vf  VD_maxexp( dVector X, ui size );
int        __vf  VD_minexp( dVector X, ui size );
double     __vf  VD_maxind( ui _VFAR *Ind, dVector X, ui size );
double     __vf  VD_minind( ui _VFAR *Ind, dVector X, ui size );
double     __vf  VD_absmaxind( ui _VFAR *Ind, dVector X, ui size );
double     __vf  VD_absminind( ui _VFAR *Ind, dVector X, ui size );
ui         __vf  VD_localmaxima( uiVector Ind, dVector X, ui size );
ui         __vf  VD_localminima( uiVector Ind, dVector X, ui size );
void       __vf  VD_runmax( dVector Y, dVector X, ui size );
void       __vf  VD_runmin( dVector Y, dVector X, ui size );
double     __vf  VD_sum( dVector X, ui size );
double     __vf  VD_prod( dVector X, ui size );
void       __vf  VD_runsum( dVector Y, dVector X, ui size );
void       __vf  VD_runprod( dVector Y, dVector X, ui size );
int        __vf  VD_iselementC( dVector Tab, ui size, double C );
ui         __vf  VD_iselementV( dVector Y, dVector X, ui sizex,
                                dVector Tab, ui sizetab );

/**************** Statistical Functions and Building Blocks *************/

double  __vf  VD_sumabs( dVector X, ui size );
double  __vf  VD_mean( dVector X, ui size );
double  __vf  VD_meanwW( dVector X, dVector Wt, ui size );
double  __vf  VD_meanabs( dVector X, ui size );
double  __vf  VD_selected_mean( ui _VFAR *nsel, dVector X, ui size,
                 double XMin, double XMax ); /* takes only x with Min<=x<=Max */
double  __vf  VD_median( dVector X, ui size );
double  __vf  VD_sumdevC( dVector X, ui size, double C );
double  __vf  VD_sumdevV( dVector X, dVector Y, ui size );
double  __vf  VD_avdevC( dVector X, ui size, double C );
double  __vf  VD_avdevV( dVector X, dVector Y, ui size );
double  __vf  VD_ssq( dVector X, ui size );  /* sum-of-squares */
double  __vf  VD_rms( dVector X, ui size );  /* root of the mean square */
double  __vf  VD_ssqdevC( dVector X, ui size, double C );
double  __vf  VD_ssqdevV( dVector X, dVector Y, ui size );
double  __vf  VD_meanvar( double _VFAR *Var, dVector X, ui size );
double  __vf  VD_meanvarwW( double _VFAR *Var, dVector X, dVector Wt, ui size );
double  __vf  VD_varianceC( dVector X, ui size, double C );
double  __vf  VD_varianceV( dVector X, dVector Y, ui size );
double  __vf  VD_varianceCwW( dVector X, dVector Wt, ui size, double C );
double  __vf  VD_varianceVwW( dVector X, dVector Y, dVector Wt, ui size );
double  __vf  VD_chi2( dVector X, dVector Y, dVector InvVar, ui size );
double  __vf  VD_chiabs( dVector X, dVector Y, dVector Wt, ui size );
double  __vf  VD_corrcoeff( dVector X, dVector Y, ui size,
                            double Xmean, double Ymean );
ui    __vf  VD_distribution( uiVector Abund, dVector Limits, ui nbins,
                             dVector X, ui sizex, int mode );

void  __vf  VD_linregress( dVector Param, dVector X, dVector Y, ui size );
void  __vf  VD_linregresswW( dVector Param, dVector X, dVector Y,
                             dVector InvVar, ui size );
     /* more linear and nonlinear data fitting routines need MatrixLib
        and are declared in <MDstd.h> !                                */


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
dComplex  __vf   VD_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf   VD_setRspEdit( dComplex Trunc );
void  __vf   VDl_FFT( dVector Y, dVector X, ui size, int dir );
void  __vf   VDl_filter( dVector Y, dVector X, dVector Flt, ui size );
void  __vf   VDl_autocorr( dVector Y, dVector X, ui size );
void  __vf   VDl_xcorr( dVector Z, dVector X, dVector Y, ui size );
double __vf  VDl_spectrum( dVector Spc, ui specsiz, dVector X, ui xsiz,
                           dVector Win );
                           /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! */
void  __vf   VDl_convolve( dVector Y, dVector Flt, dVector X,
                           dVector Rsp, ui size );
void  __vf   VDl_deconvolve( dVector Y, dVector Flt, dVector X,
                             dVector Rsp, ui size );

void  __vf   VDs_FFT( dVector Y, dVector X, ui size, int dir );
void  __vf   VDs_filter( dVector Y, dVector X, dVector Flt, ui size );
void  __vf   VDs_autocorr( dVector Y, dVector X, ui size );
void  __vf   VDs_xcorr( dVector Z, dVector X, dVector Y, ui size );
double __vf  VDs_spectrum( dVector Spc, ui specsiz, dVector X, ui xsiz,
                           dVector Win );
void  __vf   VDs_convolve( dVector Y, dVector Flt, dVector X,
                           dVector Rsp, ui size );
void  __vf   VDs_deconvolve( dVector Y, dVector Flt, dVector X,
                             dVector Rsp, ui size );

#if( defined( __LARGE__ ) || defined( __COMPACT__ ) )
   #define VD_FFT         VDl_FFT
   #define VD_convolve    VDl_convolve
   #define VD_deconvolve  VDl_deconvolve
   #define VD_filter      VDl_filter
   #define VD_autocorr    VDl_autocorr
   #define VD_xcorr       VDl_xcorr
   #define VD_spectrum    VDl_spectrum
#else
   #define VD_FFT         VDs_FFT
   #define VD_convolve    VDs_convolve
   #define VD_deconvolve  VDs_deconvolve
   #define VD_filter      VDs_filter
   #define VD_autocorr    VDs_autocorr
   #define VD_xcorr       VDs_xcorr
   #define VD_spectrum    VDs_spectrum
#endif


/********************** Analysis ****************************************/

void    __vf  VD_derivC( dVector Y, dVector X, ui size, double Deltat );
void    __vf  VD_derivV( dVector Z, dVector X, dVector Y, ui size );
double  __vf  VD_integralC( dVector X, ui size, double Deltat );
void    __vf  VD_runintegralC( dVector Y, dVector X, ui size, double Deltat );
double  __vf  VD_integralV( dVector X, dVector Y, ui size );
void    __vf  VD_runintegralV( dVector Z, dVector X, dVector Y, ui size );
void    __vf  VD_smooth( dVector Y, dVector X, ui size, unsigned deg );
int     __vf  VD_ismonoton( dVector X, ui size );

/****************** Geometrical Vector Arithmetics **************************/

double    __vf  VD_scalprod( dVector X, dVector Y, ui size );
void      __vf  VD_xprod( dVector Z, dVector X, dVector Y );
double    __vf  VD_Euclid( dVector X, ui size );


/***************************  Input and Output *****************************/

void  __vf    VD_fprint( FILE _VFAR *stream, dVector X, ui size, unsigned nperline, unsigned linewidth );
#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void  __vf    VD_cprint( dVector X, ui size, unsigned nperline );
#endif
#define       VD_print( x, sz, npl )  VD_fprint( stdout, x, sz, npl, 80 )
  /*  VD_print, VD_cprint usable only for DOS and Win32 console applications! */
void  __vf    VD_write( FILE _VFAR *stream, dVector X, ui size  ); /* in ascii */
void  __vf    VD_read( dVector X, ui size, FILE _VFAR *stream );
void  __vf    VD_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf    VD_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf    VD_setWriteFormat( char _VFAR *FormatString );
                                            /* for VD_write and VD_nwrite */
void  __vf    VD_setWriteSeparate( char _VFAR *SepString ); /* for VD_write */
void  __vf    VD_setNWriteSeparate( char _VFAR *SepString ); /* for VD_nwrite */
#ifdef V_HUGE
    void  __vf    VD_store( FILE _VFAR *stream, dVector X, ui size );
    void  __vf    VD_recall( dVector X, ui size, FILE _VFAR *stream  );
#else
    #ifdef __cplusplus
         void  inline VD_store( FILE _VFAR *stream, dVector X, ui size )
         {    fwrite( X, sizeof(double), size, stream ); 
         }
         void  inline VD_recall( dVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(double), size, stream );
         }
    #else
        #define VD_store( str, X, sz )  \
                     fwrite( X, sizeof(double), sz, str )
        #define VD_recall( X, sz, str ) \
                     fread(  X, sizeof(double), sz, str )
    #endif
#endif      /* VD_store, VD_recall in binary format */

#ifdef __cplusplus
}    //  end of extern "C"
         // alternative syntax of convolution and deconvolution:
    inline void VDl_convolve( dVector Y, dVector Flt, dVector X, dVector Rsp,
                              ui size, double TruncRe, double TruncIm )
    {   VD_setRspEdit( dcplx( TruncRe, TruncIm ) );
        VDl_convolve( Y, Flt, X, Rsp, size );
    }
    inline void VDl_deconvolve( dVector Y, dVector Flt, dVector X, dVector Rsp,
                                ui size, double TruncRe, double TruncIm )
    {   VD_setRspEdit( dcplx( TruncRe, TruncIm ) );
        VDl_deconvolve( Y, Flt, X, Rsp, size );
    }
    inline void VDs_convolve( dVector Y, dVector Flt, dVector X, dVector Rsp,
                              ui size, double TruncRe, double TruncIm )
    {   VD_setRspEdit( dcplx( TruncRe, TruncIm ) );
        VDs_convolve( Y, Flt, X, Rsp, size );
    }
    inline void VDs_deconvolve( dVector Y, dVector Flt, dVector X, dVector Rsp,
                                ui size, double TruncRe, double TruncIm )
    {   VD_setRspEdit( dcplx( TruncRe, TruncIm ) );
        VDs_deconvolve( Y, Flt, X, Rsp, size );
    }
#endif   /*  __cplusplus   */

#endif   /*  __VDSTD_H  */
