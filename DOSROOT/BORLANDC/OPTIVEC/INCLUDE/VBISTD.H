/*  VBIstd.h

  vector management functions for byte-size integers.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VBISTD_H
#define __VBISTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/*************************  Generation ***************************/

biVector  __vf  VBI_vector( ui size );
biVector  __vf  VBI_vector0( ui size );


/***************  Addressing single vector elements ******************/

char _VFAR * VBI_Pelement( biVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VBI_element( X, n )  (*VBI_Pelement( X, n ))

/****************** Initialization  ******************************/

void  __vf  VBI_equ0( biVector X, ui size );
void  __vf  VBI_equC( biVector X, ui size, char C );
void  __vf  VBI_equV( biVector Y, biVector X, ui size );
void  __vf  VBI_ramp( biVector X, ui size, char Start, char Rise );
long  __vf  VBI_random( biVector X, ui size, long seed,
                        char MinVal, char MaxVal );  /*  returns new seed */


/************** Data-type interconversions  ****************************/

void  __vf  V_BItoUB( ubVector Y, biVector X, ui size ); /* signed-unsigned */
void  __vf  V_UBtoBI( biVector Y, ubVector X, ui size );

void  __vf  V_BItoI(  iVector  Y, biVector X, ui size );  /* up-conversion */
void  __vf  V_BItoSI( siVector Y, biVector X, ui size );
void  __vf  V_BItoLI( liVector Y, biVector X, ui size );
void  __vf  V_BItoQI( qiVector Y, biVector X, ui size );

void  __vf   V_SItoBI( biVector Y, siVector  X, ui size );/* down-conversion */
void  __vf   V_ItoBI(  biVector Y, iVector  X, ui size );
void  __vf   V_LItoBI( biVector Y, liVector X, ui size );
void  __vf   V_QItoBI( biVector Y, qiVector X, ui size );

void  __vf   V_BItoF(  fVector Y, biVector X, ui size );
void  __vf   V_BItoD(  dVector Y, biVector X, ui size );
#ifdef __BORLANDC__
    void  __vf   V_BItoE(  eVector Y, biVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ and Optima++ */
    #define V_BItoE V_BItoD
#endif

/************** Index-oriented manipulations ***************************/

void  __vf  VBI_reflect( biVector X, ui size );
void  __vf  VBI_rev( biVector Y, biVector X, ui size );
#ifdef V_HUGE
    void  __vf  VBI_rotate( biVector Y, biVector X, ui size, long pos );
#else
    void  __vf  VBI_rotate( biVector Y, biVector X, ui size, int pos );
#endif

void  __vf  VBI_delete( biVector X, ui size, ui pos );
void  __vf  VBI_insert( biVector X, ui size, ui pos, char C );

void  __vf  VBI_sort( biVector Y, biVector X, ui size, int dir );
void  __vf  VBI_sortind( uiVector Ind, biVector X, ui size, int dir );

void  __vf  VBI_subvector( biVector Y, ui sizey, biVector X, int samp );
void  __vf  VBI_subvector_equC( biVector Y, ui subsz, unsigned samp, char C );
void  __vf  VBI_subvector_equV( biVector Y, ui subsz, unsigned samp,
                                biVector X );

void  __vf  VBI_indpick( biVector Y, uiVector Ind, ui sizey, biVector X );
void  __vf  VBI_indput(  biVector Y, biVector X, uiVector Ind, ui sizex );

ui    __vf  VBI_searchC( biVector XTab, ui size, char C, int mode );
void  __vf  VBI_searchV( uiVector Ind, biVector X, ui sizex,
                         biVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

char  __vf  VBI_sum( biVector X, ui size );
void  __vf  VBI_runsum( biVector Y, biVector X, ui size );
char  __vf  VBI_max( biVector X, ui size );
char  __vf  VBI_min( biVector X, ui size );
char  __vf  VBI_maxind( ui _VFAR *Ind, biVector X, ui size );
char  __vf  VBI_minind( ui _VFAR *Ind, biVector X, ui size );
void   __vf  VBI_runmax( biVector Y, biVector X, ui size );
void   __vf  VBI_runmin( biVector Y, biVector X, ui size );
double __vf  VBI_mean( biVector X, ui size );

int    __vf  VBI_iselementC( biVector Tab, ui size, char C );
ui     __vf  VBI_iselementV( biVector Y, biVector X, ui sizex,
                             biVector Tab, ui sizetab );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VBI_fprint( st, x, sz, npl, lw ) \
             V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 0 )

#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void __vf  V_icprint(  void _VFAR *X, ui size, unsigned nperline, unsigned vers );
    #define VBI_cprint( x, sz, npl ) V_icprint( (void _VFAR *) (x), sz, npl, 0 )
#endif
#define VBI_print(  x, sz, npl ) \
             V_ifprint(  stdout, (void _VFAR *)(x), sz, npl, 80, 0 )

void  __vf   V_setRadix( int radix );
           /* radix to be assumed by all whole-number read functions V??_read */
void  __vf   VBI_read( biVector X, ui size, FILE _VFAR *stream );
void  __vf   VBI_write( FILE _VFAR *stream, biVector X, ui size );
void  __vf   VBI_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VBI_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VBI_setWriteFormat( char _VFAR *FormatString );
        /* for VBI_write and VBI_nwrite. The format must be a format for short int ! */
void  __vf   VBI_setWriteSeparate( char _VFAR *SepString ); /* for VBI_write */
void  __vf   VBI_setNWriteSeparate( char _VFAR *SepString ); /* for VBI_nwrite */
#ifdef V_HUGE
    void  __vf   VBI_store(  FILE _VFAR *stream, biVector X, ui size );
    void  __vf   VBI_recall( biVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VBI_store( FILE _VFAR *stream, biVector X, ui size )
         {    fwrite( X, sizeof(char), size, stream );
         }
         void  inline VBI_recall( biVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(char), size, stream );
         }
    #else
        #define VBI_store( str, X, sz )  \
                     fwrite( X, sizeof(char), sz, str )
        #define VBI_recall( X, sz, str ) \
                     fread(  X, sizeof(char), sz, str )
    #endif
#endif      /* VBI_store, VBI_recall in binary format */

#ifdef __cplusplus
}
#endif

#endif   /*  __VBISTD_H    */
