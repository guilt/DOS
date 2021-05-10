/*  VUBstd.h

  vector management functions for data type "unsigned char".

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VUBSTD_H
#define __VUBSTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/**********************  Generation *************************************/

ubVector  __vf  VUB_vector( ui size );
ubVector  __vf  VUB_vector0( ui size );

/***************  Addressing single vector elements ******************/

unsigned char _VFAR * VUB_Pelement( ubVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VUB_element( X, n )  (*VUB_Pelement( X, n ))

/****************** Initialization  ******************************/

void  __vf  VUB_equ0( ubVector X, ui size );
void  __vf  VUB_equC( ubVector X, ui size, unsigned char C );
void  __vf  VUB_equV( ubVector Y, ubVector X, ui size );
void  __vf  VUB_ramp( ubVector X, ui size, unsigned char Start, char Rise );
long  __vf  VUB_random( ubVector X, ui size, long seed,
                        unsigned char MinVal, unsigned char MaxVal );
                              /*  returns new seed */


/**************  Data-type interconversions  **************************/

void __vf  V_BItoUB( ubVector Y, biVector X, ui size );  /* signed-unsigned */
void __vf  V_UBtoBI( biVector Y, ubVector X, ui size );

void __vf  V_UBtoU(  uVector  Y, ubVector X, ui size );  /* up-conversion */
void __vf  V_UBtoUS( usVector Y, ubVector X, ui size );
void __vf  V_UBtoUL( ulVector Y, ubVector X, ui size );

void  __vf   V_UStoUB( ubVector Y, usVector X, ui size );/* down-conversion */
void  __vf   V_UtoUB(  ubVector Y, uVector  X, ui size );
void  __vf   V_ULtoUB( ubVector Y, ulVector X, ui size );

void  __vf   V_UBtoF(  fVector Y, ubVector X, ui size );
void  __vf   V_UBtoD(  dVector Y, ubVector X, ui size );
#ifdef __BORLANDC__
    void  __vf   V_UBtoE(  eVector Y, ubVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ and Optima++ */
    #define V_UBtoE V_UBtoD
#endif


/************** Index-oriented manipulations ***************************/

void  __vf  VUB_reflect( ubVector X, ui size );
void  __vf  VUB_rev( ubVector Y, ubVector X, ui size );
#ifdef V_HUGE
    void  __vf  VUB_rotate( ubVector Y, ubVector X, ui size, long pos );
#else
    void  __vf  VUB_rotate( ubVector Y, ubVector X, ui size, int pos );
#endif

void  __vf  VUB_delete( ubVector X, ui size, ui pos );
void  __vf  VUB_insert( ubVector X, ui size, ui pos, unsigned char C );

void  __vf  VUB_sort( ubVector Y, ubVector X, ui size, int dir );
void  __vf  VUB_sortind( uiVector Ind, ubVector X, ui size, int dir );

void  __vf  VUB_subvector( ubVector Y, ui sizey, ubVector X, int samp );
void  __vf  VUB_subvector_equC( ubVector Y, ui subsz, unsigned samp,
                                unsigned char C );
void  __vf  VUB_subvector_equV( ubVector Y, ui subsz, unsigned samp,
                                ubVector X );

void  __vf  VUB_indpick( ubVector Y, uiVector Ind, ui sizey, ubVector X );
void  __vf  VUB_indput(  ubVector Y, ubVector X, uiVector Ind, ui sizex );

ui    __vf  VUB_searchC( ubVector XTab, ui size, unsigned char C, int mode );
void  __vf  VUB_searchV( uiVector Ind, ubVector X, ui sizex,
                         ubVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

unsigned char  __vf  VUB_sum( ubVector X, ui size );
void           __vf  VUB_runsum( ubVector Y, ubVector X, ui size );
unsigned char  __vf  VUB_max( ubVector X, ui size );
unsigned char  __vf  VUB_min( ubVector X, ui size );
unsigned char  __vf  VUB_maxind( ui _VFAR *Ind, ubVector X, ui size );
unsigned char  __vf  VUB_minind( ui _VFAR *Ind, ubVector X, ui size );
double         __vf  VUB_mean( ubVector X, ui size );
void           __vf  VUB_runmax( ubVector Y, ubVector X, ui size );
void           __vf  VUB_runmin( ubVector Y, ubVector X, ui size );

int    __vf  VUB_iselementC( ubVector Tab, ui size, unsigned char C );
ui     __vf  VUB_iselementV( ubVector Y, ubVector X, ui sizex,
                             ubVector Tab, ui sizetab );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VUB_fprint( st, x, sz, npl, lw ) \
             V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 1 )

#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void __vf  V_icprint(  void _VFAR *X, ui size, unsigned nperline, unsigned vers );
    #define VUB_cprint( x, sz, npl ) V_icprint( (void _VFAR *) (x), sz, npl, 1 )
#endif
#define VUB_print( x, sz, npl ) \
             V_ifprint(  stdout, (void _VFAR *)(x), sz, npl, 80, 1 )

void  __vf   V_setRadix( int radix );
           /* radix to be assumed by all whole-number read functions V??_read */
void  __vf   VUB_read( ubVector X, ui size, FILE _VFAR *stream );
void  __vf   VUB_write( FILE _VFAR *stream, ubVector X, ui size );
void  __vf   VUB_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VUB_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VUB_setWriteFormat( char _VFAR *FormatString );
  /* for VUB_write and VUB_nwrite. The format must be a format for unsigned short ! */
void  __vf   VUB_setWriteSeparate( char _VFAR *SepString ); /* for VUB_write */
void  __vf   VUB_setNWriteSeparate( char _VFAR *SepString ); /* for VUB_nwrite */
#ifdef V_HUGE
    void  __vf   VUB_store(  FILE _VFAR *stream, ubVector X, ui size );
    void  __vf   VUB_recall( ubVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VUB_store( FILE _VFAR *stream, ubVector X, ui size )
         {    fwrite( X, sizeof(unsigned char), size, stream );
         }
         void  inline VUB_recall( ubVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(unsigned char), size, stream );
         }
    #else
        #define VUB_store( str, X, sz )  \
                     fwrite( X, sizeof(unsigned char), sz, str )
        #define VUB_recall( X, sz, str ) \
                     fread(  X, sizeof(unsigned char), sz, str )
    #endif
#endif      /* VUB_store, VUB_recall in binary format */

#ifdef __cplusplus
}
#endif

#endif   /*  __VUBSTD_H    */
