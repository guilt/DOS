/*  VUSstd.h

  vector management functions for data type "unsigned short".

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VUSSTD_H
#define __VUSSTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
   extern "C" {
#endif

/**********************  Generation *************************************/

usVector  __vf  VUS_vector( ui size );
usVector  __vf  VUS_vector0( ui size );

/***************  Addressing single vector elements ******************/

unsigned short _VFAR * VUS_Pelement( usVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VUS_element( X, n )  (*VUS_Pelement( X, n ))

/****************** Initialization  ******************************/

void  __vf  VUS_equ0( usVector X, ui size );
void  __vf  VUS_equC( usVector X, ui size, unsigned short C );
void  __vf  VUS_equV( usVector Y, usVector X, ui size );
void  __vf  VUSo_ramp( usVector X, ui size, unsigned short Start, short Rise );
#ifdef V_trapIntError
    #define VUS_ramp    VUSo_ramp
#else
    void  __vf  VUS_ramp( usVector X, ui size, unsigned short Start,
                          short Rise );
#endif
long  __vf  VUS_random( usVector X, ui size, long seed,
                        unsigned short MinVal, unsigned short MaxVal );
                              /*  returns new seed */


/**************  Data-type interconversions  **************************/

void __vf  Vo_SItoUS( usVector Y, siVector X, ui size );  /* signed-unsigned */
void __vf  Vo_UStoSI( siVector Y, usVector X, ui size );

void __vf  V_UBtoUS( usVector Y, ubVector X, ui size );  /* up-conversion */
void __vf  V_UStoU(  uVector  Y, usVector  X, ui size );
void __vf  V_UStoUL( ulVector Y, usVector  X, ui size );

void __vf  V_UStoUB(  ubVector Y, usVector X, ui size ); /* down-conversion */
void __vf  Vo_UtoUS(  usVector Y, uVector  X, ui size );
void __vf  Vo_ULtoUS( usVector Y, ulVector X, ui size );
#ifdef V_trapIntError
    #define V_SItoUS  Vo_SItoUS
    #define V_UStoSI  Vo_UStoSI
    #define V_UtoUS   Vo_UtoUS
    #define V_ULtoUS  Vo_ULtoUS
#else
    void  __vf   V_SItoUS( usVector Y, siVector X, ui size );
    void  __vf   V_UStoSI( siVector Y, usVector X, ui size );
    void  __vf   V_UtoUS(  usVector Y, uVector  X, ui size );
    void  __vf   V_ULtoUS( usVector Y, ulVector X, ui size );
#endif

void  __vf   V_UStoF(  fVector Y, usVector X, ui size );
void  __vf   V_UStoD(  dVector Y, usVector X, ui size );
#ifdef __BORLANDC__
    void  __vf   V_UStoE(  eVector Y, usVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ */
    #define V_UStoE V_UStoD
#endif


/************** Index-oriented manipulations ***************************/

void  __vf  VUS_reflect( usVector X, ui size );
void  __vf  VUS_rev( usVector Y, usVector X, ui size );
#ifdef V_HUGE
    void  __vf  VUS_rotate( usVector Y, usVector X, ui size, long pos );
#else
    void  __vf  VUS_rotate( usVector Y, usVector X, ui size, int pos );
#endif

void  __vf  VUS_delete( usVector X, ui size, ui pos );
void  __vf  VUS_insert( usVector X, ui size, ui pos, unsigned short C );

void  __vf  VUS_sort( usVector Y, usVector X, ui size, int dir );
void  __vf  VUS_sortind( uiVector Ind, usVector X, ui size, int dir );

void  __vf  VUS_subvector( usVector Y, ui sizey, usVector X, int samp );
void  __vf  VUS_subvector_equC( usVector Y, ui subsz, unsigned samp,
                                unsigned short C );
void  __vf  VUS_subvector_equV( usVector Y, ui subsz, unsigned samp,
                                usVector X );

void  __vf  VUS_indpick( usVector Y, uiVector Ind, ui sizey, usVector X );
void  __vf  VUS_indput(  usVector Y, usVector X, uiVector Ind, ui sizex );

ui    __vf  VUS_searchC( usVector XTab, ui size, unsigned short C, int mode );
void  __vf  VUS_searchV( uiVector Ind, usVector X, ui sizex,
                         usVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

unsigned short __vf  VUSo_sum( usVector X, ui size );
void           __vf  VUSo_runsum( usVector Y, usVector X, ui size );
#ifdef V_trapIntError
    #define VUS_sum     VUSo_sum
    #define VUS_runsum  VUSo_runsum
#else
    unsigned short __vf  VUS_sum( usVector X, ui size );
    void           __vf  VUS_runsum( usVector Y, usVector X, ui size );
#endif
unsigned short  __vf  VUS_max( usVector X, ui size );
unsigned short  __vf  VUS_min( usVector X, ui size );
unsigned short  __vf  VUS_maxind( ui _VFAR *Ind, usVector X, ui size );
unsigned short  __vf  VUS_minind( ui _VFAR *Ind, usVector X, ui size );
double          __vf  VUS_fsum( usVector X, ui size );
double          __vf  VUS_mean( usVector X, ui size );
void   __vf  VUS_runmax( usVector Y, usVector X, ui size );
void   __vf  VUS_runmin( usVector Y, usVector X, ui size );

int    __vf  VUS_iselementC( usVector Tab, ui size, unsigned short C );
ui     __vf  VUS_iselementV( usVector Y, usVector X, ui sizex,
                             usVector Tab, ui sizetab );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VUS_fprint( st, x, sz, npl, lw ) \
             V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 3 )

#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void __vf  V_icprint(  void _VFAR *X, ui size, unsigned nperline, unsigned vers );
    #define VUS_cprint( x, sz, npl ) V_icprint( (void _VFAR *) (x), sz, npl, 3 )
#endif
#define VUS_print( x, sz, npl ) \
             V_ifprint(  stdout, (void _VFAR *)(x), sz, npl, 80, 3 )

void  __vf   V_setRadix( int radix );
           /* radix to be assumed by all whole-number read functions V??_read */
void  __vf   VUS_read( usVector X, ui size, FILE _VFAR *stream );
void  __vf   VUS_write( FILE _VFAR *stream, usVector X, ui size );
void  __vf   VUS_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VUS_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VUS_setWriteFormat( char _VFAR *FormatString );
                                            /* for VUS_write and VUS_nwrite */
void  __vf   VUS_setWriteSeparate( char _VFAR *SepString ); /* for VUS_write */
void  __vf   VUS_setNWriteSeparate( char _VFAR *SepString ); /* for VUS_nwrite */
#ifdef V_HUGE
    void  __vf   VUS_store(  FILE _VFAR *stream, usVector X, ui size );
    void  __vf   VUS_recall( usVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VUS_store( FILE _VFAR *stream, usVector X, ui size )
         {    fwrite( X, sizeof(unsigned short), size, stream ); 
         }
         void  inline VUS_recall( usVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(unsigned short), size, stream );
         }
    #else
        #define VUS_store( str, X, sz )  \
                     fwrite( X, sizeof(unsigned short), sz, str )
        #define VUS_recall( X, sz, str ) \
                     fread(  X, sizeof(unsigned short), sz, str )
    #endif
#endif      /* VUS_store, VUS_recall in binary format */

#ifdef __cplusplus
}
#endif

#endif   /*  __VUSSTD_H    */
