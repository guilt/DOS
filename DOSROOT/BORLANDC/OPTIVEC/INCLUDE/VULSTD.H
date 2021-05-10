/*  VULstd.h

  vector management functions for data type "unsigned long".

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VULSTD_H
#define __VULSTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/*****************************  Generation ******************************/

ulVector  __vf  VUL_vector( ui size );
ulVector  __vf  VUL_vector0( ui size );

/***************  Addressing single vector elements ******************/

unsigned long _VFAR * VUL_Pelement( ulVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VUL_element( X, n ) (*VUL_Pelement( X, n ))

/****************** Initialization  ******************************/

void  __vf  VUL_equ0( ulVector X, ui size );
void  __vf  VUL_equC( ulVector X, ui size, unsigned long C );
void  __vf  VUL_equV( ulVector Y, ulVector X, ui size );
void  __vf  VULo_ramp( ulVector X, ui size, unsigned long Start, long Rise );
#ifdef V_trapIntError
    #define VUL_ramp    VULo_ramp
#else
    void __vf  VUL_ramp( ulVector X, ui size, unsigned long Start, long Rise );
#endif
long  __vf  VUL_random( ulVector X, ui size, long seed,
                        unsigned long MinVal, unsigned long MaxVal );
                              /*  returns new seed */

/**************  Data-type interconversions  **************************/

void __vf  Vo_LItoUL( ulVector Y, liVector X, ui size );  /* signed-unsigned */
void __vf  Vo_ULtoLI( liVector Y, ulVector X, ui size );

void __vf  V_UBtoUL( ulVector Y, ubVector X, ui size );  /* up-conversion */
void __vf  V_UStoUL( ulVector Y, usVector X, ui size );
void __vf  V_UtoUL(  ulVector Y, uVector  X, ui size );

void __vf  V_ULtoUB(  ubVector Y, ulVector X, ui size ); /* down-conversion */
void __vf  Vo_ULtoUS( usVector Y, ulVector X, ui size );
void __vf  Vo_ULtoU(  uVector  Y, ulVector X, ui size );
#ifdef V_trapIntError
    #define V_LItoUL    Vo_LItoUL
    #define V_ULtoLI    Vo_ULtoLI
    #define V_ULtoUS    Vo_ULtoUS
    #define V_ULtoU     Vo_ULtoU
#else
    void  __vf   V_LItoUL( ulVector Y, liVector X, ui size );
    void  __vf   V_ULtoLI( liVector Y, ulVector X, ui size );
    void  __vf   V_ULtoUS( usVector Y, ulVector X, ui size );
    void  __vf   V_ULtoU(  uVector  Y, ulVector X, ui size );
#endif

void  __vf   V_ULtoF(  fVector Y, ulVector X, ui size );
void  __vf   V_ULtoD(  dVector Y, ulVector X, ui size );
#ifdef __BORLANDC__
    void  __vf   V_ULtoE(  eVector Y, ulVector X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ */
    #define V_ULtoE V_ULtoD
#endif


/************** Index-oriented manipulations ***************************/

void  __vf  VUL_reflect( ulVector X, ui size );
void  __vf  VUL_rev( ulVector Y, ulVector X, ui size );
#ifdef V_HUGE
    void  __vf  VUL_rotate( ulVector Y, ulVector X, ui size, long pos );
#else
    void  __vf  VUL_rotate( ulVector Y, ulVector X, ui size, int pos );
#endif

void  __vf  VUL_delete( ulVector X, ui size, ui pos );
void  __vf  VUL_insert( ulVector X, ui size, ui pos, unsigned long C );

void  __vf  VUL_sort( ulVector Y, ulVector X, ui size, int dir );
void  __vf  VUL_sortind( uiVector Ind, ulVector X, ui size, int dir );

void  __vf  VUL_subvector( ulVector Y, ui sizey, ulVector X, int samp );
void  __vf  VUL_subvector_equC( ulVector Y, ui subsz, unsigned samp,
                                unsigned long C );
void  __vf  VUL_subvector_equV( ulVector Y, ui subsz, unsigned samp,
                                ulVector X );

void  __vf  VUL_indpick( ulVector Y, uiVector Ind, ui sizey, ulVector X );
void  __vf  VUL_indput(  ulVector Y, ulVector X, uiVector Ind, ui sizex );

ui    __vf  VUL_searchC( ulVector XTab, ui size, unsigned long C, int mode );
void  __vf  VUL_searchV( uiVector Ind, ulVector X, ui sizex,
                         ulVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

unsigned long  __vf  VULo_sum( ulVector X, ui size );
void           __vf  VULo_runsum( ulVector Y, ulVector X, ui size );
#ifdef V_trapIntError
    #define VUL_sum       VULo_sum
    #define VUL_runsum    VULo_runsum
#else
    unsigned long  __vf  VUL_sum( ulVector X, ui size );
    void           __vf  VUL_runsum( ulVector Y, ulVector X, ui size );
#endif
unsigned long  __vf  VUL_max( ulVector X, ui size );
unsigned long  __vf  VUL_min( ulVector X, ui size );
unsigned long  __vf  VUL_maxind( ui _VFAR *Ind, ulVector X, ui size );
unsigned long  __vf  VUL_minind( ui _VFAR *Ind, ulVector X, ui size );
double         __vf  VUL_fsum( ulVector X, ui size );
double         __vf  VUL_mean( ulVector X, ui size );
void   __vf  VUL_runmax( ulVector Y, ulVector X, ui size );
void   __vf  VUL_runmin( ulVector Y, ulVector X, ui size );

int    __vf  VUL_iselementC( ulVector Tab, ui size, unsigned long  C );
ui     __vf  VUL_iselementV( ulVector Y, ulVector X, ui sizex,
                             ulVector Tab, ui sizetab );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VUL_fprint( st, x, sz, npl, lw ) \
             V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 7 )

#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void __vf  V_icprint(  void _VFAR *X, ui size, unsigned nperline, unsigned vers );
    #define VUL_cprint( x, sz, npl ) V_icprint( (void _VFAR *) (x), sz, npl, 7 )
#endif
#define VUL_print( x, sz, npl ) \
             V_ifprint(  stdout, (void _VFAR *)(x), sz, npl, 80, 7 )

void  __vf   V_setRadix( int radix );
           /* radix to be assumed by all whole-number read functions V??_read */
void  __vf   VUL_read( ulVector X, ui size, FILE _VFAR *stream );
void  __vf   VUL_write( FILE _VFAR *stream, ulVector X, ui size );
void  __vf   VUL_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VUL_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VUL_setWriteFormat( char _VFAR *FormatString );
                                            /* for VUL_write and VUL_nwrite */
void  __vf   VUL_setWriteSeparate( char _VFAR *SepString ); /* for VUL_write */
void  __vf   VUL_setNWriteSeparate( char _VFAR *SepString ); /* for VUL_nwrite */
#ifdef V_HUGE
    void  __vf   VUL_store(  FILE _VFAR *stream, ulVector X, ui size );
    void  __vf   VUL_recall( ulVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VUL_store( FILE _VFAR *stream, ulVector X, ui size )
         {    fwrite( X, sizeof(unsigned long), size, stream ); 
         }
         void  inline VUL_recall( ulVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(unsigned long), size, stream );
         }
    #else
        #define VUL_store( str, X, sz )  \
                     fwrite( X, sizeof(unsigned long), sz, str )
        #define VUL_recall( X, sz, str ) \
                     fread(  X, sizeof(unsigned long), sz, str )
    #endif
#endif      /* VUL_store, VUL_recall in binary format */

#ifdef __cplusplus
}
#endif

#endif   /*  __VULSTD_H    */
