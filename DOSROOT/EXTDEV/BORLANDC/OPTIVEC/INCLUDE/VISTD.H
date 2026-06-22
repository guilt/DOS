/*  VIstd.h

  vector management functions for data type "int".

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VISTD_H
#define __VISTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/***********  Generation of Arrays and Vectors  *************************/

iVector  __vf  VI_vector( ui size );
iVector  __vf  VI_vector0( ui size );

/***************  Addressing single vector elements ******************/

int _VFAR * VI_Pelement( iVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VI_element( X, n )  (*VI_Pelement( X, n ))

/****************** Initialization  ******************************/

void  __vf  VI_equ0( iVector X, ui size );
void  __vf  VI_equC( iVector X, ui size, int C );
void  __vf  VI_equV( iVector Y, iVector X, ui size );
void  __vf  VIo_ramp( iVector X, ui size, int Start, int Rise );
#ifdef V_trapIntError
    #define VI_ramp    VIo_ramp
#else
    void  __vf  VI_ramp( iVector X, ui size, int Start, int Rise );
#endif
long  __vf  VI_random( iVector X, ui size, long seed,
                       int MinVal, int MaxVal );  /*  returns new seed */


/************** Data-type interconversions  ***************************/

void  __vf   V_BItoI(  iVector  Y, biVector X, ui size );  /* up-conversion */
void  __vf   V_SItoI(  iVector  Y, siVector X, ui size );
void  __vf   V_ItoLI(  liVector Y, iVector  X, ui size );
void  __vf   V_ItoQI(  qiVector Y, iVector  X, ui size );

void  __vf   Vo_ItoU( uVector Y, iVector X, ui size );  /* signed-unsigned */
void  __vf   Vo_UtoI( iVector Y, uVector X, ui size );

void  __vf   V_ItoBI(  biVector Y, iVector  X, ui size ); /* down-conversion */
void  __vf   Vo_ItoSI( siVector Y, iVector  X, ui size );
void  __vf   Vo_LItoI( iVector  Y, liVector X, ui size );
void  __vf   Vo_QItoI( iVector  Y, qiVector X, ui size );
#ifdef V_trapIntError
    #define V_ItoU    Vo_ItoU
    #define V_UtoI    Vo_UtoI
    #define V_ItoSI   Vo_ItoSI
    #define V_LItoI   Vo_LItoI
    #define V_QItoI   Vo_QItoI
#else
    void  __vf   V_ItoU( uVector Y, iVector X, ui size );
    void  __vf   V_UtoI( iVector Y, uVector X, ui size );
    void  __vf   V_ItoSI( siVector Y, iVector  X, ui size );
    void  __vf   V_LItoI( iVector  Y, liVector X, ui size );
    void  __vf   V_QItoI( iVector  Y, qiVector X, ui size );
#endif

void  __vf   V_ItoF(   fVector Y, iVector  X, ui size );
void  __vf   V_ItoD(   dVector Y, iVector  X, ui size );
#ifdef __BORLANDC__
    void  __vf   V_ItoE(   eVector Y, iVector  X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ */
    #define V_ItoE V_ItoD
#endif

/************** Index-oriented manipulations ***************************/

void  __vf  VI_reflect( iVector X, ui size );
void  __vf  VI_rev( iVector Y, iVector X, ui size );
#ifdef V_HUGE
    void  __vf  VI_rotate( iVector Y, iVector X, ui size, long pos );
#else
    void  __vf  VI_rotate( iVector Y, iVector X, ui size, int pos );
#endif

void  __vf  VI_delete( iVector X, ui size, ui pos );
void  __vf  VI_insert( iVector X, ui size, ui pos, int C );

void  __vf  VI_sort( iVector Y, iVector X, ui size, int dir );
void  __vf  VI_sortind( uiVector Ind, iVector X, ui size, int dir );

void  __vf  VI_subvector( iVector Y, ui sizey, iVector X, int samp );
void  __vf  VI_subvector_equC( iVector Y, ui subsz, unsigned samp, int C );
void  __vf  VI_subvector_equV( iVector Y, ui subsz, unsigned samp, iVector X );

void  __vf  VI_indpick( iVector Y, uiVector Ind, ui sizey, iVector X );
void  __vf  VI_indput(  iVector Y, iVector X, uiVector Ind, ui sizex );

ui    __vf  VI_searchC( iVector XTab, ui size, int C, int mode );
void  __vf  VI_searchV( uiVector Ind, iVector X, ui sizex,
                        iVector Tab, ui sizetab, int mode );


/********************   One-dimensional Vector Operations  ********/

int  __vf  VIo_sum( iVector X, ui size );
void __vf  VIo_runsum( iVector Y, iVector X, ui size );
#ifdef V_trapIntError
    #define VI_sum     VIo_sum
    #define VI_runsum  VIo_runsum
#else
    int  __vf  VI_sum( iVector X, ui size );
    void __vf  VI_runsum( iVector Y, iVector X, ui size );
#endif
int    __vf  VI_max( iVector X, ui size );
int    __vf  VI_min( iVector X, ui size );
int    __vf  VI_maxind( ui _VFAR *Ind, iVector X, ui size );
int    __vf  VI_minind( ui _VFAR *Ind, iVector X, ui size );
void   __vf  VI_runmax( iVector Y, iVector X, ui size );
void   __vf  VI_runmin( iVector Y, iVector X, ui size );
double __vf  VI_fsum( iVector X, ui size );
double __vf  VI_mean( iVector X, ui size );

int    __vf  VI_iselementC( iVector Tab, ui size, int  C );
ui     __vf  VI_iselementV( iVector Y, iVector X, ui sizex,
                             iVector Tab, ui sizetab );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VI_fprint( st, x, sz, npl, lw )  \
             V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 4 )

#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void __vf  V_icprint(  void _VFAR *X, ui size, unsigned nperline, unsigned vers );
    #define VI_cprint( x, sz, npl ) V_icprint( (void _VFAR *) (x), sz, npl, 4 )
#endif
#define VI_print( x, sz, npl )  \
             V_ifprint(  stdout, (void _VFAR *)(x), sz, npl, 80, 4 )

void  __vf   V_setRadix( int radix );
           /* radix to be assumed by all whole-number read functions V??_read */
void  __vf   VI_read( iVector X, ui size, FILE _VFAR *stream );
void  __vf   VI_write( FILE _VFAR *stream, iVector X, ui size );
void  __vf   VI_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VI_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VI_setWriteFormat( char _VFAR *FormatString );
                                            /* for VI_write and VI_nwrite */
void  __vf   VI_setWriteSeparate( char _VFAR *SepString ); /* for VI_write */
void  __vf   VI_setNWriteSeparate( char _VFAR *SepString ); /* for VI_nwrite */
#ifdef V_HUGE
    void  __vf   VI_store(  FILE _VFAR *stream, iVector X, ui size );
    void  __vf   VI_recall( iVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VI_store( FILE _VFAR *stream, iVector X, ui size )
         {    fwrite( X, sizeof(int), size, stream ); 
         }
         void  inline VI_recall( iVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(int), size, stream );
         }
    #else
        #define VI_store( str, X, sz )  \
                     fwrite( X, sizeof(int), sz, str )
        #define VI_recall( X, sz, str ) \
                     fread(  X, sizeof(int), sz, str )
    #endif
#endif      /* VI_store, VI_recall in binary format */

#ifdef __cplusplus
}
#endif

#endif   /*  __VISTD_H    */
