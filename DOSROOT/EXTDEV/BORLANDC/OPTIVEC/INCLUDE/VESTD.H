/*  VEstd.h

  vector management functions:
  manipulations on whole arrays or vectors of data type "extended"
  (real numbers: long double)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VESTD_H
#define __VESTD_H
#if !defined( __VECLIB_H )
#include <VecLib.h>
#endif


#ifdef __BORLANDC__   /* 80-bit IEEE numbers supported:
                         the following 250 lines apply
                         only to Borland C++  */

#ifdef __cplusplus
extern "C" {
#endif

/*************************  Generation  **************************/

eVector   __vf  VE_vector( ui size );
eVector   __vf  VE_vector0( ui size );

/***************  Addressing single vector elements ******************/

extended _VFAR * VE_Pelement( eVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VE_element( X, n )  (*VE_Pelement( X, n ))

/*******************  Initialization **********************************/

void  __vf  VE_equ0( eVector X, ui size );
void  __vf  VE_equ1( eVector X, ui size );
void  __vf  VE_equm1( eVector X, ui size );
void  __vf  VE_equC( eVector X, ui size, extended C );
void  __vf  VE_equV( eVector Y, eVector X, ui size );
void  __vf  VEx_equV( eVector Y, eVector X, ui size,
                                       extended A, extended B );
void  __vf  VE_ramp( eVector X, ui size,
                                    extended Start, extended Rise );
void  __vf  VE_Parzen( eVector X, ui size );
void  __vf  VE_Welch( eVector X, ui size );
void  __vf  VE_Hanning( eVector X, ui size );
void  __vf  VE_comb( eVector X, ui size, unsigned step, extended C );
long  __vf  VE_random( eVector X, ui size, long seed,
                       extended MinVal, extended MaxVal );
long  __vf  VE_noise( eVector X, ui size, long seed, extended Amp );
            /* VE_random and VE_noise return a new seed value.
               random quality of VE_random is much better      */

/***************  Data-type interconversions  *************************/
       /* for rounding functions, see VEmath.h ! */

void  __vf   V_SItoE(  eVector Y, siVector X, ui size );
void  __vf   V_ItoE(   eVector Y, iVector  X, ui size );
void  __vf   V_LItoE(  eVector Y, liVector X, ui size );
void  __vf   V_QItoE(  eVector Y, qiVector X, ui size );

void  __vf   V_UStoE(  eVector Y, usVector X, ui size );
void  __vf   V_UtoE(   eVector Y, uVector  X, ui size );
void  __vf   V_ULtoE(  eVector Y, ulVector X, ui size );

void  __vf   V_FtoE( eVector Y, fVector X, ui size );
void  __vf   V_EtoF( fVector Y, eVector X, ui size );
void  __vf   V_DtoE( eVector Y, dVector X, ui size );
void  __vf   V_EtoD( dVector Y, eVector X, ui size );


/****************  Index-oriented manipulations ***********************/


void  __vf  VE_reflect( eVector X, ui size );
void  __vf  VE_rev( eVector Y, eVector X, ui size );
#if defined (V_HUGE)
    void  __vf  VE_rotate( eVector Y, eVector X, ui size, long pos );
#else
    void  __vf  VE_rotate( eVector Y, eVector X, ui size, int pos );
#endif
void  __vf  VE_delete( eVector X, ui size, ui pos );
void  __vf  VE_insert( eVector X, ui size, ui pos, extended C );
void  __vf  VE_sort( eVector Y, eVector X, ui size, int dir );
void  __vf  VE_sortind( uiVector Ind, eVector X, ui size, int dir );
void  __vf  VE_subvector( eVector Y, ui sizey, eVector X, int step );
void  __vf  VE_indpick( eVector Y, uiVector Ind, ui sizey, eVector X );
void  __vf  VE_indput(  eVector Y, eVector X, uiVector Ind, ui sizex );
void  __vf  VE_indpick( eVector Y, uiVector Ind, ui size, eVector X );
ui    __vf  VE_searchC( eVector X, ui size, extended C, int mode );
void  __vf  VE_searchV( uiVector Ind, eVector X, ui sizex,
                                     eVector Tab, ui sizetab, int mode );

void  __vf  VE_polyinterpol( eVector Y, eVector X, ui sizex,
                   eVector XTab, eVector YTab, ui sizetab, unsigned deg );
void  __vf  VE_ratinterpol( eVector Y, eVector X, ui sizex,
                   eVector XTab, eVector YTab, ui sizetab, unsigned deg );
void  __vf  VE_splinederiv2( eVector Y2, eVector XTab, eVector YTab,
                   ui size, int specify, extended Yp0, extended Ypn );
void  __vf  VE_splineinterpol( eVector Y, eVector X, ui sizex,
                   eVector XTab, eVector YTab, eVector Y2Tab, ui sizetab );


/***************** Functions of a sub-set of elements  ********************/

void  __vf  VE_subvector_equC(  eVector Y, ui subsiz, unsigned samp, extended C );
void  __vf  VE_subvector_equV(  eVector Y, ui subsiz, unsigned samp, eVector X );
    /*   for arithmetic functions of subsets, see <VEmath.h>  */


/**************** One-Dimensional Vector Operations ***********************/

extended      __vf  VE_max( eVector X, ui size );
extended      __vf  VE_min( eVector X, ui size );
extended      __vf  VE_absmax( eVector X, ui size );
extended      __vf  VE_absmin( eVector X, ui size );
int           __vf  VE_maxexp( eVector X, ui size );
int           __vf  VE_minexp( eVector X, ui size );
extended      __vf  VE_maxind( ui _VFAR *Ind, eVector X, ui size );
extended      __vf  VE_minind( ui _VFAR *Ind, eVector X, ui size );
extended      __vf  VE_absmaxind( ui _VFAR *Ind, eVector X, ui size );
extended      __vf  VE_absminind( ui _VFAR *Ind, eVector X, ui size );
ui            __vf  VE_localmaxima( uiVector Ind, eVector X, ui size );
ui            __vf  VE_localminima( uiVector Ind, eVector X, ui size );
void          __vf  VE_runmax( eVector Y, eVector X, ui size );
void          __vf  VE_runmin( eVector Y, eVector X, ui size );
extended      __vf  VE_sum( eVector X, ui size );
extended      __vf  VE_prod( eVector X, ui size );
void          __vf  VE_runsum( eVector Y, eVector X, ui size );
void          __vf  VE_runprod( eVector Y, eVector X, ui size );
int           __vf  VE_iselementC( eVector Tab, ui size, extended C );
ui            __vf  VE_iselementV( eVector Y, eVector X, ui sizex,
                                   eVector Tab, ui sizetab );

/**************** Statistical Functions and Building Blocks *************/

extended __vf  VE_sumabs( eVector X, ui size );
extended __vf  VE_mean( eVector X, ui size );
extended __vf  VE_meanwW( eVector X, eVector Wt, ui size );
extended __vf  VE_meanabs( eVector X, ui size );
extended __vf  VE_selected_mean( ui _VFAR *nsel, eVector X, ui size,
                extended XMin, extended XMax ); /* takes only x with Min<=x<=Max */
extended __vf  VE_median( eVector X, ui size );
extended __vf  VE_sumdevC( eVector X, ui size, extended C );
extended __vf  VE_sumdevV( eVector X, eVector Y, ui size );
extended __vf  VE_avdevC( eVector X, ui size, extended C );
extended __vf  VE_avdevV( eVector X, eVector Y, ui size );
extended __vf  VE_ssq( eVector X, ui size );
extended __vf  VE_rms( eVector X, ui size );
extended __vf  VE_ssqdevC( eVector X, ui size, extended C );
extended __vf  VE_ssqdevV( eVector X, eVector Y, ui size );
extended __vf  VE_meanvar(  extended _VFAR *Var, eVector X, ui size );
extended __vf  VE_meanvarwW(  extended _VFAR *Var, eVector X, eVector Wt, ui size );
extended __vf  VE_varianceC( eVector X, ui size, extended C );
extended __vf  VE_varianceV( eVector X, eVector Y, ui size );
extended __vf  VE_varianceCwW( eVector X, eVector Wt, ui size, extended C );
extended __vf  VE_varianceVwW( eVector X, eVector Y, eVector Wt, ui size );
extended __vf  VE_chi2( eVector X, eVector Y, eVector InvVar, ui size );
extended __vf  VE_chiabs( eVector X, eVector Y, eVector Wt, ui size );
extended __vf  VE_corrcoeff( eVector X, eVector Y, ui size,
                             extended Xmean, extended Ymean );
ui    __vf  VE_distribution( uiVector Abund, eVector Limits, ui nbins,
                             eVector X, ui sizex, int mode );

void  __vf  VE_linregress( eVector Param, eVector X, eVector Y, ui size );
void  __vf  VE_linregresswW( eVector Param, eVector X, eVector Y,
                             eVector InvVar, ui size );
     /* more (linear and nonlinear) data fitting routines need MatrixLib
        and are declared in <MEstd.h> !                                */


/*********  Fourier Transforms, Convolutions, Filtering  ****************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
eComplex  __vf   VE_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf   VE_setRspEdit( eComplex Trunc );
void  __vf    VEl_FFT( eVector Y, eVector X, ui size, int dir );
void  __vf    VEl_filter( eVector Y, eVector X, eVector Flt, ui size );
void  __vf    VEl_autocorr( eVector Y, eVector X, ui size );
void  __vf    VEl_xcorr( eVector Z, eVector X, eVector Y, ui size );
extended __vf VEl_spectrum( eVector Spc, ui specsiz, eVector X, ui xsiz,
                            eVector Win );
                           /* xsiz >= n*specsiz,  Winsiz = 2*specsiz ! */
void  __vf    VEl_convolve( eVector Y, eVector Flt, eVector X,
                            eVector Rsp, ui size );
void  __vf    VEl_deconvolve( eVector Y, eVector Flt, eVector X,
                            eVector Rsp, ui size );

void  __vf    VEs_FFT( eVector Y, eVector X, ui size, int dir );
void  __vf    VEs_filter( eVector Y, eVector X, eVector Flt, ui size );
void  __vf    VEs_autocorr( eVector Y, eVector X, ui size );
void  __vf    VEs_xcorr( eVector Z, eVector X, eVector Y, ui size );
extended __vf VEs_spectrum( eVector Spc, ui specsiz, eVector X, ui xsiz,
                            eVector Win );
void  __vf    VEs_convolve( eVector Y, eVector Flt, eVector X,
                            eVector Rsp, ui size );
void  __vf    VEs_deconvolve( eVector Y, eVector Flt, eVector X,
                            eVector Rsp, ui size );

#if( defined( __LARGE__ ) || defined( __COMPACT__ ) )
   #define VE_FFT         VEl_FFT
   #define VE_convolve    VEl_convolve
   #define VE_deconvolve  VEl_deconvolve
   #define VE_filter      VEl_filter
   #define VE_autocorr    VEl_autocorr
   #define VE_xcorr       VEl_xcorr
   #define VE_spectrum    VEl_spectrum
#else
   #define VE_FFT         VEs_FFT
   #define VE_convolve    VEs_convolve
   #define VE_deconvolve  VEs_deconvolve
   #define VE_filter      VEs_filter
   #define VE_autocorr    VEs_autocorr
   #define VE_xcorr       VEs_xcorr
   #define VE_spectrum    VEs_spectrum
#endif



/********************** Analysis ****************************************/

void        __vf  VE_derivC( eVector Y, eVector X, ui size, extended Deltat );
void        __vf  VE_derivV( eVector Z, eVector X, eVector Y, ui size );
extended __vf  VE_integralC( eVector X, ui size, extended Deltat );
void        __vf  VE_runintegralC( eVector Y, eVector X, ui size, extended Deltat );
extended __vf  VE_integralV( eVector X, eVector Y, ui size );
void        __vf  VE_runintegralV( eVector Z, eVector X, eVector Y, ui size );
void        __vf  VE_smooth( eVector Y, eVector X, ui size, unsigned deg );
int         __vf  VE_ismonoton( eVector X, ui size );


/****************** Geometrical Vector Arithmetics **************************/

extended     __vf  VE_scalprod( eVector X, eVector Y, ui size );
void            __vf  VE_xprod( eVector Z, eVector X, eVector Y );
extended     __vf  VE_Euclid( eVector X, ui size );


/***************************  Input and Output *****************************/

void  __vf    VE_fprint( FILE _VFAR *stream, eVector X, ui size,
                                    unsigned nperline, unsigned linewidth );
#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void  __vf VE_cprint( eVector X, ui size, unsigned nperline );
#endif
#define       VE_print( x, sz, npl )  VE_fprint( stdout, x, sz, npl, 80 )
  /*  VE_print, VE_cprint usable only for DOS, EasyWin, and Win32 console applications! */
void  __vf    VE_write( FILE _VFAR *stream, eVector X, ui size  ); /* in ascii */
void  __vf    VE_read( eVector X, ui size, FILE _VFAR *stream );
void  __vf    VE_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf    VE_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf    VE_setWriteFormat( char _VFAR *FormatString );
                                            /* for VE_write and VE_nwrite */
void  __vf    VE_setWriteSeparate( char _VFAR *SepString ); /* for VE_write */
void  __vf    VE_setNWriteSeparate( char _VFAR *SepString ); /* for VE_nwrite */
#ifdef V_HUGE
    void  __vf    VE_store( FILE _VFAR *stream, eVector X, ui size );
    void  __vf    VE_recall( eVector X, ui size, FILE _VFAR *stream  );
#else
    #ifdef __cplusplus
         void  inline VE_store( FILE _VFAR *stream, eVector X, ui size )
         {    fwrite( X, sizeof(extended), size, stream ); 
         }
         void  inline VE_recall( eVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(extended), size, stream );
         }
    #else
        #define VE_store( str, X, sz )  \
                     fwrite( X, sizeof(extended), sz, str )
        #define VE_recall( X, sz, str ) \
                     fread(  X, sizeof(extended), sz, str )
    #endif
#endif      /* VE_store, VE_recall in binary format */

#ifdef __cplusplus
}  //  end of extern "C"
        // alternative syntax of convolution and deconvolution
    inline void  VEl_convolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEl_convolve( Y, Flt, X, Rsp, size );
    }
    inline void  VEl_deconvolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEl_deconvolve( Y, Flt, X, Rsp, size );
    }
    inline void  VEs_convolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEs_convolve( Y, Flt, X, Rsp, size );
    }
    inline void  VEs_deconvolve( eVector Y, eVector Flt, eVector X, eVector Rsp,
                           ui size, extended TruncRe, extended TruncIm )
    {   VE_setRspEdit( ecplx( TruncRe, TruncIm ) );
        VEs_deconvolve( Y, Flt, X, Rsp, size );
    }
#endif    /*  __cplusplus  */



#else  /* no IEEE number support with Visual C++, Watcom C, and Optima++.
          The following about 200 lines apply only to these compilers */

#define VE_vector   VD_vector
#define VE_vector0  VD_vector0
#define VE_Pelement VD_Pelement
#define VE_element( X, n )  (*VE_Pelement( X, n ))

#define VE_equ0         VD_equ0
#define VE_equ1         VD_equ1
#define VE_equm1        VD_equm1
#define VE_equC         VD_equC
#define VE_equV         VD_equV
#define VEx_equV        VDx_equV
#define VE_ramp         VD_ramp
#define VE_Parzen       VD_Parzen
#define VE_Welch        VD_Welch
#define VE_Hanning      VD_Hanning
#define VE_comb         VD_comb
#define VE_random       VD_random
#define VE_noise        VD_nois
#define V_SItoE         V_SItoD
#define V_ItoE          V_ItoD
#define V_LItoE         V_LItoD
#define V_QItoE         V_QItoD
#define V_UStoE         V_UStoD
#define V_UtoE          V_UtoD
#define V_ULtoE         V_ULtoD

#define V_FtoE          V_FtoD
#define V_EtoF          V_DtoF
#define V_DtoE          VD_equV
#define V_EtoD          VD_equV

#define VE_reflect      VD_reflect
#define VE_rev          VD_rev
#define VE_rotate       VD_rotate
#define VE_delete       VD_delete
#define VE_insert       VD_insert
#define VE_sort         VD_sort
#define VE_sortind      VD_sortind
#define VE_subvector    VD_subvector
#define VE_indpick      VD_indpick
#define VE_indput       VD_indput

#define VE_searchC      VD_searchC
#define VE_searchV      VD_searchV
#define VE_polyinterpol VD_polyinterpol
#define VE_ratinterpol  VD_ratinterpol
#define VE_splinederiv2 VD_splinederiv2
#define VE_splineinterpol VD_splineinterpol

#define VE_subvector_equC  VD_subvector_equC
#define VE_subvector_equV  VD_subvector_equV

#define VE_max          VD_max
#define VE_min          VD_min
#define VE_absmax       VD_absmax
#define VE_absmin       VD_absmin
#define VE_maxind       VD_maxind
#define VE_minind       VD_minind
#define VE_absmaxind    VD_absmaxind
#define VE_absminind    VD_absminind

#define VE_localmaxima  VD_localmaxima
#define VE_localminima  VD_localminima
#define VE_runmax       VD_runmax
#define VE_runmin       VD_runmin
#define VE_sum          VD_sum
#define VE_prod         VD_prod
#define VE_runsum       VD_runsum
#define VE_runprod      VD_runprod
#define VE_iselementC   VD_iselementC
#define VE_iselementV   VD_iselementC

#define VE_sumabs       VD_sumabs
#define VE_mean         VD_mean
#define VE_meanwW       VD_meanwW
#define VE_meanabs      VD_meanabs
#define VE_selected_mean VD_selected_mean
#define VE_median       VD_median
#define VE_sumdevC      VD_sumdevC
#define VE_sumdevV      VD_sumdevV
#define VE_avdevC       VD_avdevC
#define VE_avdevV       VD_avdevV
#define VE_ssq          VD_ssq
#define VE_rms          VD_rms
#define VE_ssqdevC      VD_ssqdevC
#define VE_ssqdevV      VD_ssqdevV
#define VE_meanvar      VD_meanvar
#define VE_meanvarwW    VD_meanvarwW
#define VE_varianceC    VD_varianceC
#define VE_varianceV    VD_varianceV
#define VE_varianceCwW  VD_varianceCwW
#define VE_varianceVwW  VD_varianceVwW
#define VE_chi2         VD_chi2
#define VE_chiabs       VD_chiabs
#define VE_corrcoeff    VD_corrcoeff
#define VE_distribution VD_distribution
#define VE_linregress   VD_linregress
#define VE_linregresswW VD_linregresswW

#define VE_setRspEdit   VD_setRspEdit
#define VE_getRspEdit   VD_getRspEdit
#define VEl_FFT         VDl_FFT
#define VEl_filter      VDl_filter
#define VEl_autocorr    VDl_autocorr
#define VEl_xcorr       VDl_xcorr
#define VEl_spectrum    VDl_spectrum
#define VEl_convolve    VDl_convolve
#define VEl_deconvolve  VDl_deconvolve
#define VEs_FFT         VDs_FFT
#define VEs_filter      VDs_filter
#define VEs_autocorr    VDs_autocorr
#define VEs_xcorr       VDs_xcorr
#define VEs_spectrum    VDs_spectrum
#define VEs_convolve    VDs_convolve
#define VEs_deconvolve  VDs_deconvolve
#define VEl_FFT         VDl_FFT
#define VEl_filter      VDl_filter
#define VEl_autocorr    VDl_autocorr
#define VEl_xcorr       VDl_xcorr
#define VEl_spectrum    VDl_spectrum
#define VEl_convolve    VDl_convolve
#define VEl_deconvolve  VDl_deconvolve
#define VE_FFT          VEs_FFT
#define VE_convolve     VEs_convolve
#define VE_deconvolve   VEs_deconvolve
#define VE_filter       VEs_filter
#define VE_autocorr     VEs_autocorr
#define VE_xcorr        VEs_xcorr
#define VE_spectrum     VEs_spectrum

#define VE_derivC       VD_derivC
#define VE_derivV       VD_derivV
#define VE_integralC    VD_integralC
#define VE_runintegralC VD_runintegralC
#define VE_integralV    VD_integralV
#define VE_runintegralV VD_runintegralV
#define VE_smooth       VD_smooth
#define VE_ismonoton    VD_ismonoton

#define VE_scalprod     VD_scalprod
#define VE_xprod        VD_xprod
#define VE_Euclid       VD_Euclid

#define VE_fprint       VD_fprint
#define VE_cprint       VD_cprint
#define VE_print        VD_print
#define VE_write        VD_write
#define VE_read         VD_read
#define VE_nwrite       VD_nwrite
#define VE_nread        VD_nread
#define VE_setWriteFormat   VD_setWriteFormat
#define VE_setWriteSeparate VD_setWriteSeparate   
#define VE_store        VD_store
#define VE_recall       VD_recall


#endif   /*  Borland, Microsoft, or Powersoft  */


#endif   /*  __VESTD_H  */
