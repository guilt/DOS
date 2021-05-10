/*  VQIstd.h

  vector management functions for data type "quad".

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VQISTD_H
#define __VQISTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/************  Making the data type quad available   *********************
 *        The following definitions are necessary only if                *
 *        the compiler does not support 64 bit integers.                 */

quad        __vf  setquad( long double x );
double      __vf  quadtod( quad x );
long double __vf  _quadtold( quad x );

/************************  Generation ******************************/

qiVector  __vf  VQI_vector( ui size );
qiVector  __vf  VQI_vector0( ui size );

/***************  Addressing single vector elements ******************/

quad _VFAR * VQI_Pelement( qiVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VQI_element( X, n ) (*VQI_Pelement( X, n ))

/****************** Initialization  ******************************/

void  __vf  VQI_equ0( qiVector X, ui size );
void  __vf  VQI_equC( qiVector X, ui size, quad C );
void  __vf  VQI_equV( qiVector Y, qiVector X, ui size );
void  __vf  VQI_ramp( qiVector X, ui size, quad Start, quad Rise );
long  __vf  VQI_random( qiVector X, ui size, long seed,
                        quad MinVal, quad MaxVal );  /*  returns new seed */


/************** Data-type interconversions  ***************************/
        /* no conversion signed-unsigned for quad available, because
           no data-type "unsigned quad" exists */

void  __vf  V_BItoQI( qiVector Y, biVector X, ui size );  /* up-conversion */
void  __vf  V_SItoQI( qiVector Y, siVector X, ui size );
void  __vf  V_ItoQI(  qiVector Y, iVector  X, ui size );
void  __vf  V_LItoQI( qiVector Y, liVector X, ui size );

void  __vf  V_QItoBI(  biVector Y, qiVector X, ui size ); /* down-conversion */
void  __vf  Vo_QItoSI( siVector Y, qiVector X, ui size );
void  __vf  Vo_QItoI(  iVector  Y, qiVector X, ui size );
void  __vf  Vo_QItoLI( liVector Y, qiVector X, ui size );
#ifdef V_trapIntError
    #define V_QItoSI   Vo_QItoSI
    #define V_QItoI    Vo_QItoI
    #define V_QItoLI   Vo_QItoLI
#else
    void  __vf   V_QItoSI( siVector Y, qiVector X, ui size );
    void  __vf   V_QItoI(  iVector  Y, qiVector X, ui size );
    void  __vf   V_QItoLI( liVector Y, qiVector X, ui size );
#endif

void  __vf   V_QItoF(  fVector Y, qiVector X, ui size );
void  __vf   V_QItoD(  dVector Y, qiVector X, ui size );
#ifdef __BORLANDC__
    void  __vf   V_QItoE(  eVector Y, qiVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ */
    #define V_QItoE V_QItoD
#endif



/************** Index-oriented manipqiations ***************************/

void  __vf  VQI_reflect( qiVector X, ui size );
void  __vf  VQI_rev( qiVector Y, qiVector X, ui size );
#ifdef V_HUGE
    void  __vf  VQI_rotate( qiVector Y, qiVector X, ui size, long pos );
#else
    void  __vf  VQI_rotate( qiVector Y, qiVector X, ui size, int pos );
#endif

void  __vf  VQI_delete( qiVector X, ui size, ui pos );
void  __vf  VQI_insert( qiVector X, ui size, ui pos, quad C );

void  __vf  VQI_sort( qiVector Y, qiVector X, ui size, int dir );
void  __vf  VQI_sortind( uiVector Ind, qiVector X, ui size, int dir );

void  __vf  VQI_subvector( qiVector Y, ui sizey, qiVector X, int samp );
void  __vf  VQI_subvector_equC( qiVector Y, ui subsz, unsigned samp, quad C );
void  __vf  VQI_subvector_equV( qiVector Y, ui subsz, unsigned samp,
                                qiVector X );

void  __vf  VQI_indpick( qiVector Y, uiVector Ind, ui sizey, qiVector X );
void  __vf  VQI_indput(  qiVector Y, qiVector X, uiVector Ind, ui sizex );

ui    __vf  VQI_searchC( qiVector XTab, ui size, quad C, int mode );
void  __vf  VQI_searchV( uiVector Ind, qiVector X, ui sizex,
                         qiVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

quad   __vf  VQI_sum( qiVector X, ui size );
quad   __vf  VQI_max( qiVector X, ui size );
quad   __vf  VQI_min( qiVector X, ui size );
quad   __vf  VQI_maxind( ui _VFAR *Ind, qiVector X, ui size );
quad   __vf  VQI_minind( ui _VFAR *Ind, qiVector X, ui size );
void   __vf  VQI_runsum( qiVector Y, qiVector X, ui size );
void   __vf  VQI_runmax( qiVector Y, qiVector X, ui size );
void   __vf  VQI_runmin( qiVector Y, qiVector X, ui size );
extended __vf  VQI_fsum( qiVector X, ui size );
extended __vf  VQI_mean( qiVector X, ui size );

int    __vf  VQI_iselementC( qiVector Tab, ui size, quad C );
ui     __vf  VQI_iselementV( qiVector Y, qiVector X, ui sizex,
                             qiVector Tab, ui sizetab );


/************************ Input / Output ******************************/

void  __vf   VQI_fprint(  FILE _VFAR *stream, qiVector X, ui size,
                  unsigned nperline, unsigned linewidth );

#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void __vf  VQI_cprint( qiVector X, ui size, unsigned nperline );
#endif
#define VQI_print( x, sz, npl ) VQI_fprint( stdout, x, sz, npl, 80 )

/* note that V_setRadix does not act on VQI_read. Here, the radix is always 10 */
void  __vf   VQI_read( qiVector X, ui size, FILE _VFAR *stream );
void  __vf   VQI_write( FILE _VFAR *stream, qiVector X, ui size );
void  __vf   VQI_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VQI_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VQI_setWriteFormat( char _VFAR *FormatString );
                                            /* for VQI_write and VQI_nwrite */
void  __vf   VQI_setWriteSeparate( char _VFAR *SepString ); /* for VQI_write */
void  __vf   VQI_setNWriteSeparate( char _VFAR *SepString ); /* for VQI_nwrite */
#ifdef V_HUGE
    void  __vf   VQI_store(  FILE _VFAR *stream, qiVector X, ui size );
    void  __vf   VQI_recall( qiVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VQI_store( FILE _VFAR *stream, qiVector X, ui size )
         {    fwrite( X, sizeof(quad), size, stream ); 
         }
         void  inline VQI_recall( qiVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(quad), size, stream );
         }
    #else
        #define VQI_store( str, X, sz )  \
                     fwrite( X, sizeof(quad), sz, str )
        #define VQI_recall( X, sz, str ) \
                     fread(  X, sizeof(quad), sz, str )
    #endif
#endif      /* VQI_store, VQI_recall in binary format */

#ifdef __cplusplus
}
#endif

#endif   /*  __VQISTD_H    */
