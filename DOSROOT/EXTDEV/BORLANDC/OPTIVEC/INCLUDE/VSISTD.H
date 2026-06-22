/*  VSIstd.h

  vector management functions for data type "short int".

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VSISTD_H
#define __VSISTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/*************************  Generation ***************************/

siVector  __vf  VSI_vector( ui size );
siVector  __vf  VSI_vector0( ui size );


/***************  Addressing single vector elements ******************/

short _VFAR * VSI_Pelement( siVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VSI_element( X, n )  (*VSI_Pelement( X, n ))

/****************** Initialization  ******************************/

void  __vf  VSI_equ0( siVector X, ui size );
void  __vf  VSI_equC( siVector X, ui size, short C );
void  __vf  VSI_equV( siVector Y, siVector X, ui size );
void  __vf  VSIo_ramp( siVector X, ui size, short Start, short Rise );
#ifdef V_trapIntError
    #define VSI_ramp   VSIo_ramp
#else
    void  __vf  VSI_ramp( siVector X, ui size, short Start, short Rise );
#endif
long  __vf  VSI_random( siVector X, ui size, long seed,
                        short MinVal, short MaxVal );  /*  returns new seed */


/************** Data-type interconversions  ****************************/

void  __vf  Vo_SItoUS( usVector Y, siVector X, ui size ); /* signed-unsigned */
void  __vf  Vo_UStoSI( siVector Y, usVector X, ui size );

void  __vf  V_BItoSI( siVector Y, biVector X, ui size );  /* up-conversion */
void  __vf  V_SItoI(  iVector  Y, siVector X, ui size );
void  __vf  V_SItoLI( liVector Y, siVector X, ui size );
void  __vf  V_SItoQI( qiVector Y, siVector X, ui size );

void  __vf  V_SItoBI(  biVector Y, siVector X, ui size ); /* down-conversion */
void  __vf  Vo_ItoSI(  siVector Y, iVector  X, ui size );
void  __vf  Vo_LItoSI( siVector Y, liVector X, ui size );
void  __vf  Vo_QItoSI( siVector Y, qiVector X, ui size );
#ifdef V_trapIntError
    #define V_SItoUS  Vo_SItoUS
    #define V_UStoSI  Vo_UStoSI
    #define V_ItoSI   Vo_ItoSI
    #define V_LItoSI  Vo_LItoSI
    #define V_QItoSI  Vo_QItoSI
#else
    void  __vf   V_SItoUS( usVector Y, siVector X, ui size );
    void  __vf   V_UStoSI( siVector Y, usVector X, ui size );
    void  __vf   V_ItoSI(  siVector Y, iVector  X, ui size );
    void  __vf   V_LItoSI( siVector Y, liVector X, ui size );
    void  __vf   V_QItoSI( siVector Y, qiVector X, ui size );
#endif

void  __vf   V_SItoF(  fVector Y, siVector X, ui size );
void  __vf   V_SItoD(  dVector Y, siVector X, ui size );
#ifdef __BORLANDC__
    void  __vf   V_SItoE(  eVector Y, siVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ */
    #define V_SItoE V_SItoD
#endif

/************** Index-oriented manipulations ***************************/

void  __vf  VSI_reflect( siVector X, ui size );
void  __vf  VSI_rev( siVector Y, siVector X, ui size );
#ifdef V_HUGE
    void  __vf  VSI_rotate( siVector Y, siVector X, ui size, long pos );
#else
    void  __vf  VSI_rotate( siVector Y, siVector X, ui size, int pos );
#endif

void  __vf  VSI_delete( siVector X, ui size, ui pos );
void  __vf  VSI_insert( siVector X, ui size, ui pos, short C );

void  __vf  VSI_sort( siVector Y, siVector X, ui size, int dir );
void  __vf  VSI_sortind( uiVector Ind, siVector X, ui size, int dir );

void  __vf  VSI_subvector( siVector Y, ui sizey, siVector X, int samp );
void  __vf  VSI_subvector_equC( siVector Y, ui subsz, unsigned samp, short C );
void  __vf  VSI_subvector_equV( siVector Y, ui subsz, unsigned samp,
                                siVector X );

void  __vf  VSI_indpick( siVector Y, uiVector Ind, ui sizey, siVector X );
void  __vf  VSI_indput(  siVector Y, siVector X, uiVector Ind, ui sizex );

ui    __vf  VSI_searchC( siVector XTab, ui size, short C, int mode );
void  __vf  VSI_searchV( uiVector Ind, siVector X, ui sizex,
                         siVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

short __vf  VSIo_sum( siVector X, ui size );
void  __vf  VSIo_runsum( siVector Y, siVector X, ui size );
#ifdef V_trapIntError
    #define VSI_sum     VSIo_sum
    #define VSI_runsum  VSIo_runsum
#else
    short __vf  VSI_sum( siVector X, ui size );
    void  __vf  VSI_runsum( siVector Y, siVector X, ui size );
#endif
short  __vf  VSI_max( siVector X, ui size );
short  __vf  VSI_min( siVector X, ui size );
short  __vf  VSI_maxind( ui _VFAR *Ind, siVector X, ui size );
short  __vf  VSI_minind( ui _VFAR *Ind, siVector X, ui size );
void   __vf  VSI_runmax( siVector Y, siVector X, ui size );
void   __vf  VSI_runmin( siVector Y, siVector X, ui size );
double __vf  VSI_fsum( siVector X, ui size );
double __vf  VSI_mean( siVector X, ui size );

int    __vf  VSI_iselementC( siVector Tab, ui size, short C );
ui     __vf  VSI_iselementV( siVector Y, siVector X, ui sizex,
                             siVector Tab, ui sizetab );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VSI_fprint( st, x, sz, npl, lw ) \
             V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 2 )

#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void __vf  V_icprint(  void _VFAR *X, ui size, unsigned nperline, unsigned vers );
    #define VSI_cprint( x, sz, npl ) V_icprint( (void _VFAR *) (x), sz, npl, 2 )
#endif
#define VSI_print(  x, sz, npl ) \
             V_ifprint(  stdout, (void _VFAR *)(x), sz, npl, 80, 2 )

void  __vf   V_setRadix( int radix );
           /* radix to be assumed by all whole-number read functions V??_read */
void  __vf   VSI_read( siVector X, ui size, FILE _VFAR *stream );
void  __vf   VSI_write( FILE _VFAR *stream, siVector X, ui size );
void  __vf   VSI_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VSI_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VSI_setWriteFormat( char _VFAR *FormatString );
                                            /* for VSI_write and VSI_nwrite */
void  __vf   VSI_setWriteSeparate( char _VFAR *SepString ); /* for VSI_write */
void  __vf   VSI_setNWriteSeparate( char _VFAR *SepString ); /* for VSI_nwrite */
#ifdef V_HUGE
    void  __vf   VSI_store(  FILE _VFAR *stream, siVector X, ui size );
    void  __vf   VSI_recall( siVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VSI_store( FILE _VFAR *stream, siVector X, ui size )
         {    fwrite( X, sizeof(short), size, stream ); 
         }
         void  inline VSI_recall( siVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(short), size, stream );
         }
    #else
        #define VSI_store( str, X, sz )  \
                     fwrite( X, sizeof(short), sz, str )
        #define VSI_recall( X, sz, str ) \
                     fread(  X, sizeof(short), sz, str )
    #endif
#endif      /* VSI_store, VSI_recall in binary format */

#ifdef __cplusplus
}
#endif

#endif   /*  __VSISTD_H    */
