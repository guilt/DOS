/*  VLIstd.h

  vector management functions for data type "long".

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VLISTD_H
#define __VLISTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/**********************  Generation  ************************************/

liVector  __vf  VLI_vector( ui size );
liVector  __vf  VLI_vector0( ui size );

/***************  Addressing single vector elements ******************/

long _VFAR * VLI_Pelement( liVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VLI_element( X, n )  (*VLI_Pelement( X, n ))

/*********************** Initialization  ******************************/

void  __vf  VLI_equ0( liVector X, ui size );
void  __vf  VLI_equC( liVector X, ui size, long C );
void  __vf  VLI_equV( liVector Y, liVector X, ui size );
void  __vf  VLIo_ramp( liVector X, ui size, long Start, long Rise );
#ifdef V_trapIntError
    #define VLI_ramp   VLIo_ramp
#else
    void  __vf  VLI_ramp( liVector X, ui size, long Start, long Rise );
#endif
long  __vf  VLI_random( liVector X, ui size, long seed,
                        long MinVal, long MaxVal );  /*  returns new seed */


/************** Data-type interconversions  ***************************/

void  __vf  Vo_LItoUL( ulVector Y, liVector X, ui size ); /* signed-unsigned */
void  __vf  Vo_ULtoLI( liVector Y, ulVector X, ui size );

void  __vf  V_BItoLI( liVector Y, biVector X, ui size );  /* up-conversion */
void  __vf  V_SItoLI( liVector Y, siVector X, ui size );
void  __vf  V_ItoLI(  liVector Y, iVector  X, ui size );
void  __vf  V_LItoQI( qiVector Y, liVector X, ui size );

void  __vf  V_LItoBI(  biVector Y, liVector X, ui size ); /* down-conversion */
void  __vf  Vo_LItoSI( siVector Y, liVector X, ui size );
void  __vf  Vo_LItoI(  iVector  Y, liVector X, ui size );
void  __vf  Vo_QItoLI( liVector Y, qiVector X, ui size );
#ifdef V_trapIntError
    #define V_LItoUL    Vo_LItoUL
    #define V_ULtoLI    Vo_ULtoLI
    #define V_LItoSI    Vo_LItoSI
    #define V_LItoI     Vo_LItoI
    #define V_QItoLI    Vo_QItoLI
#else
    void  __vf   V_LItoUL( ulVector Y, liVector X, ui size );
    void  __vf   V_ULtoLI( liVector Y, ulVector X, ui size );
    void  __vf   V_LItoSI( siVector Y, liVector X, ui size );
    void  __vf   V_LItoI(  iVector  Y, liVector X, ui size );
    void  __vf   V_QItoLI( liVector Y, qiVector X, ui size );
#endif

void  __vf   V_LItoF(  fVector Y, liVector X, ui size );
void  __vf   V_LItoD(  dVector Y, liVector X, ui size );
#ifdef __BORLANDC__
    void  __vf   V_LItoE(  eVector Y, liVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ */
    #define V_LItoE V_LItoD
#endif


/************** Index-oriented manipulations ***************************/

void  __vf  VLI_reflect( liVector X, ui size );
void  __vf  VLI_rev( liVector Y, liVector X, ui size );
#ifdef V_HUGE
    void  __vf  VLI_rotate( liVector Y, liVector X, ui size, long pos );
#else
    void  __vf  VLI_rotate( liVector Y, liVector X, ui size, int pos );
#endif

void  __vf  VLI_delete( liVector X, ui size, ui pos );
void  __vf  VLI_insert( liVector X, ui size, ui pos, long C );

void  __vf  VLI_sort( liVector Y, liVector X, ui size, int dir );
void  __vf  VLI_sortind( uiVector Ind, liVector X, ui size, int dir );

void  __vf  VLI_subvector( liVector Y, ui sizey, liVector X, int samp );
void  __vf  VLI_subvector_equC( liVector Y, ui subsz, unsigned samp, long C );
void  __vf  VLI_subvector_equV( liVector Y, ui subsz, unsigned samp,
                                liVector X );

void  __vf  VLI_indpick( liVector Y, uiVector Ind, ui sizey, liVector X );
void  __vf  VLI_indput(  liVector Y, liVector X, uiVector Ind, ui sizex );

ui    __vf  VLI_searchC( liVector XTab, ui size, long C, int mode );
void  __vf  VLI_searchV( uiVector Ind, liVector X, ui sizex,
                         liVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

long  __vf  VLIo_sum( liVector X, ui size );
void  __vf  VLIo_runsum( liVector Y, liVector X, ui size );
#ifdef V_trapIntError
    #define VLI_sum       VLIo_sum
    #define VLI_runsum    VLIo_runsum
#else
    long  __vf  VLI_sum( liVector X, ui size );
    void  __vf  VLI_runsum( liVector Y, liVector X, ui size );
#endif
long   __vf  VLI_max( liVector X, ui size );
long   __vf  VLI_min( liVector X, ui size );
long   __vf  VLI_maxind( ui _VFAR *Ind, liVector X, ui size );
long   __vf  VLI_minind( ui _VFAR *Ind, liVector X, ui size );
void   __vf  VLI_runmax( liVector Y, liVector X, ui size );
void   __vf  VLI_runmin( liVector Y, liVector X, ui size );
double __vf  VLI_fsum( liVector X, ui size );
double __vf  VLI_mean( liVector X, ui size );

int    __vf  VLI_iselementC( liVector Tab, ui size, long C );
ui     __vf  VLI_iselementV( liVector Y, liVector X, ui sizex,
                             liVector Tab, ui sizetab );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VLI_fprint( st, x, sz, npl, lw ) \
             V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 6 )

#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void __vf  V_icprint(  void _VFAR *X, ui size, unsigned nperline, unsigned vers );
    #define VLI_cprint( x, sz, npl ) V_icprint( (void _VFAR *) (x), sz, npl, 6 )
#endif
#define VLI_print( x, sz, npl ) \
             V_ifprint(  stdout, (void _VFAR *)(x), sz, npl, 80, 6 )

void  __vf   V_setRadix( int radix );
           /* radix to be assumed by all whole-number read functions V??_read */
void  __vf   VLI_read( liVector X, ui size, FILE _VFAR *stream );
void  __vf   VLI_write( FILE _VFAR *stream, liVector X, ui size );
void  __vf   VLI_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VLI_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VLI_setWriteFormat( char _VFAR *FormatString );
                                            /* for VLI_write and VLI_nwrite */
void  __vf   VLI_setWriteSeparate( char _VFAR *SepString ); /* for VLI_write */
void  __vf   VLI_setNWriteSeparate( char _VFAR *SepString ); /* for VLI_nwrite */
#ifdef V_HUGE
    void  __vf   VLI_store(  FILE _VFAR *stream, liVector X, ui size );
    void  __vf   VLI_recall( liVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VLI_store( FILE _VFAR *stream, liVector X, ui size )
         {    fwrite( X, sizeof(long), size, stream ); 
         }
         void  inline VLI_recall( liVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(long), size, stream );
         }
    #else
        #define VLI_store( str, X, sz )  \
                     fwrite( X, sizeof(long), sz, str )
        #define VLI_recall( X, sz, str ) \
                     fread(  X, sizeof(long), sz, str )
    #endif
#endif      /* VLI_store, VLI_recall in binary format */

#ifdef __cplusplus
}
#endif

#endif   /*  __VLISTD_H    */
