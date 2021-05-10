/*  VUstd.h

  vector management functions for data type "unsigned".

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __VUSTD_H
#define __VUSTD_H

#if !defined( __VECLIB_H )
   #include <VecLib.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/*********************  Generation ***********************************/

uVector  __vf  VU_vector( ui size );
uVector  __vf  VU_vector0( ui size );

/***************  Addressing single vector elements ******************/

unsigned _VFAR * VU_Pelement( uVector X, ui n );
      /* returns a pointer to the n'th element of X. For the memory model
         HUGE, the pointer is normalized. */
#define VU_element( X, n )  (*VU_Pelement( X, n ))

/****************** Initialization  ******************************/

void  __vf  VU_equ0( uVector X, ui size );
void  __vf  VU_equC( uVector X, ui size, unsigned C );
void  __vf  VU_equV( uVector Y, uVector X, ui size );
void  __vf  VUo_ramp( uVector X, ui size, unsigned Start, int Rise );
#ifdef V_trapIntError
    #define VU_ramp   VUo_ramp
#else
    void  __vf  VU_ramp( uVector X, ui size, unsigned Start, int Rise );
#endif
long  __vf  VU_random( uVector X, ui size, long seed,
                       unsigned MinVal, unsigned MaxVal );
                              /*  returns new seed */


/************** Data-type interconversions  ***************************/

void  __vf   Vo_ItoU( uVector Y, iVector X, ui size );  /* signed-unsigned */
void  __vf   Vo_UtoI( iVector Y, uVector X, ui size );

void  __vf   V_UStoU(  uVector  Y, usVector X, ui size );  /* up-conversion */
void  __vf   V_UtoUL(  ulVector Y, uVector  X, ui size );

void  __vf   Vo_UtoUS( usVector Y, uVector  X, ui size ); /* down-conversion */
void  __vf   Vo_ULtoU( uVector  Y, ulVector X, ui size );
#ifdef V_trapIntError
    #define V_ItoU    Vo_ItoU
    #define V_UtoI    Vo_UtoI
    #define V_UtoUS   Vo_UtoUS
    #define V_ULtoU   Vo_ULtoU
#else
    void  __vf   V_ItoU( uVector Y, iVector X, ui size );
    void  __vf   V_UtoI( iVector Y, uVector X, ui size );
    void  __vf   V_UtoUS( usVector Y, uVector  X, ui size );
    void  __vf   V_ULtoU( uVector  Y, ulVector X, ui size );
#endif

void  __vf   V_UtoF(   fVector Y, uVector  X, ui size );
void  __vf   V_UtoD(   dVector Y, uVector  X, ui size );
#ifdef __BORLANDC__
    void  __vf   V_UtoE(   eVector Y, uVector  X, ui size );
#else  /* no 80-bit IEEE reals with Visual C++ */
    #define V_UtoE V_UtoD
#endif


/************** Index-oriented manipulations ***************************/

void  __vf  VU_reflect( uVector X, ui size );
void  __vf  VU_rev( uVector Y, uVector X, ui size );
#ifdef V_HUGE
    void  __vf  VU_rotate( uVector Y, uVector X, ui size, long pos );
#else
    void  __vf  VU_rotate( uVector Y, uVector X, ui size, int pos );
#endif

void  __vf  VU_delete( uVector X, ui size, ui pos );
void  __vf  VU_insert( uVector X, ui size, ui pos, unsigned C );

void  __vf  VU_sort( uVector Y, uVector X, ui size, int dir );
void  __vf  VU_sortind( uiVector Ind, uVector X, ui size, int dir );

void  __vf  VU_subvector( uVector Y, ui sizey, uVector X, int samp );
void  __vf  VU_subvector_equC( uVector Y, ui subsz, unsigned samp,
                               unsigned C );
void  __vf  VU_subvector_equV( uVector Y, ui subsz, unsigned samp,
                               uVector X );
void  __vf  VU_indpick( uVector Y, uiVector Ind, ui sizey, uVector X );
void  __vf  VU_indput(  uVector Y, uVector X, uiVector Ind, ui sizex );

ui    __vf  VU_searchC( uVector XTab, ui size, unsigned C, int mode );
void  __vf  VU_searchV( uiVector Ind, uVector X, ui sizex,
                        uVector Tab, ui sizetab, int mode );

/********************   One-dimensional Vector Operations  ********/

unsigned __vf  VUo_sum( uVector X, ui size );
void     __vf  VUo_runsum( uVector Y, uVector X, ui size );
#ifdef V_trapIntError
    #define VU_sum       VUo_sum
    #define VU_runsum    VUo_runsum
#else
    unsigned __vf  VU_sum( uVector X, ui size );
    void     __vf  VU_runsum( uVector Y, uVector X, ui size );
#endif
unsigned  __vf  VU_max( uVector X, ui size );
unsigned  __vf  VU_min( uVector X, ui size );
unsigned  __vf  VU_maxind( ui _VFAR *Ind, uVector X, ui size );
unsigned  __vf  VU_minind( ui _VFAR *Ind, uVector X, ui size );
double    __vf  VU_fsum( uVector X, ui size );
double    __vf  VU_mean( uVector X, ui size );
void      __vf  VU_runmax( uVector Y, uVector X, ui size );
void      __vf  VU_runmin( uVector Y, uVector X, ui size );

int       __vf  VU_iselementC( uVector Tab, ui size, unsigned  C );
ui        __vf  VU_iselementV( uVector Y, uVector X, ui sizex,
                               uVector Tab, ui sizetab );


/************************ Input / Output ******************************/

void  __vf   V_ifprint(  FILE _VFAR *stream, void _VFAR *X, ui size,
                  unsigned nperline, unsigned linewidth, unsigned vers );
#define VU_fprint( st, x, sz, npl, lw )  \
             V_ifprint(  st, (void _VFAR *)(x), sz, npl, lw, 5 )

#if !defined _Windows || defined __FLAT__ || defined _WIN32
    void __vf  V_icprint(  void _VFAR *X, ui size, unsigned nperline, unsigned vers );
    #define VU_cprint( x, sz, npl )  V_icprint( (void _VFAR *) (x), sz, npl, 5 )
#endif
#define VU_print( x, sz, npl )  \
             V_ifprint(  stdout, (void _VFAR *)(x), sz, npl, 80, 5 )

void  __vf   V_setRadix( int radix );
           /* radix to be assumed by all whole-number read functions V??_read */
void  __vf   VU_read( uVector X, ui size, FILE _VFAR *stream );
void  __vf   VU_write( FILE _VFAR *stream, uVector X, ui size );
void  __vf   VU_nwrite( FILE _VFAR *stream, unsigned n, ui size, ... );
void  __vf   VU_nread( unsigned n, ui size, FILE _VFAR *stream, ... );
void  __vf   VU_setWriteFormat( char _VFAR *FormatString );
                                            /* for VU_write and VU_nwrite */
void  __vf   VU_setWriteSeparate( char _VFAR *SepString ); /* for VU_write */
void  __vf   VU_setNWriteSeparate( char _VFAR *SepString ); /* for VU_nwrite */
#ifdef V_HUGE
    void  __vf   VU_store(  FILE _VFAR *stream, uVector X, ui size );
    void  __vf   VU_recall( uVector X, ui size, FILE _VFAR *stream );
#else
    #ifdef __cplusplus
         void  inline VU_store( FILE _VFAR *stream, uVector X, ui size )
         {    fwrite( X, sizeof(unsigned), size, stream ); 
         }
         void  inline VU_recall( uVector X, ui size, FILE _VFAR *stream )
         {    fread(  X, sizeof(unsigned), size, stream );
         }
    #else
        #define VU_store( str, X, sz )  \
                     fwrite( X, sizeof(unsigned), sz, str )
        #define VU_recall( X, sz, str ) \
                     fread(  X, sizeof(unsigned), sz, str )
    #endif
#endif      /* VU_store, VU_recall in binary format */

#ifdef __cplusplus
}
#endif
#endif   /*  __VUSTD_H    */
