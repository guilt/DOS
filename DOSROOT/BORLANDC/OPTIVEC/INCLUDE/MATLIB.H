/*  MatLib.h

  two-dimensional-matrix management functions.

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#ifndef __MATLIB_H
#define __MATLIB_H

#define C_MATRIX 1   /* does your compiler follow the C convention
                        of element ordering?
                        if not, change this line into
                        "   #define C_MATRIX 0   "!
                     */

#ifndef __VECLIB_H
    #include <VecLib.h>
#endif
#if defined( V_HUGE )
     #define   V_DATAPTR  huge
#else
     #define   V_DATAPTR
#endif

/**********************************************************************
 *   The following definitions ensure compatibility between           *
 *   dynamically allocated matrices (e.g., by MF_matrix) and          *
 *   static ones (declared, e.g., by float MA[20][20];                *
 *   for details see MFstd.h                                          */

typedef   char   V_DATAPTR  *           biPMatrix;
typedef   short  V_DATAPTR  *           siPMatrix;
typedef   int    V_DATAPTR  *           iPMatrix;
typedef   long   V_DATAPTR  *           liPMatrix;
typedef   quad   V_DATAPTR  *           qiPMatrix;
typedef   unsigned char  V_DATAPTR *    ubPMatrix;
typedef   unsigned short V_DATAPTR *    usPMatrix;
typedef   unsigned int   V_DATAPTR *    uPMatrix;
typedef   unsigned long  V_DATAPTR *    ulPMatrix;
typedef   ui        V_DATAPTR   *       uiPMatrix;   
typedef   float     V_DATAPTR   *       fPMatrix;
typedef   double    V_DATAPTR   *       dPMatrix;
typedef   extended  V_DATAPTR   *       ePMatrix;
typedef   fComplex  V_DATAPTR   *       cfPMatrix;
typedef   dComplex  V_DATAPTR   *       cdPMatrix;
typedef   eComplex  V_DATAPTR   *       cePMatrix;

typedef   biPMatrix  *        biMatrix;
typedef   ubPMatrix  *        ubMatrix;
typedef   siPMatrix  *        siMatrix;
typedef   usPMatrix  *        usMatrix;
typedef   iPMatrix   *        iMatrix;
typedef   uPMatrix   *        uMatrix;
typedef   liPMatrix  *        liMatrix;
typedef   ulPMatrix  *        ulMatrix;
typedef   uiPMatrix  *        uiMatrix;
typedef   qiPMatrix  *        qiMatrix;
typedef   fPMatrix   *        fMatrix;
typedef   dPMatrix   *        dMatrix;
typedef   ePMatrix   *        eMatrix;
typedef   cfPMatrix  *        cfMatrix;
typedef   cdPMatrix  *        cdMatrix;
typedef   cePMatrix  *        ceMatrix;

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************
          defined here only for the integer data types;
          for the floating-point types, see <MFstd.h> etc.
          For integer matrices, these are the only functions
          so far included in VectorLib.                                  */

biMatrix __vf  MBI_matrix(  unsigned ht, unsigned len );
biMatrix __vf  MBI_matrix0( unsigned ht, unsigned len );
ubMatrix __vf  MUB_matrix(  unsigned ht, unsigned len );
ubMatrix __vf  MUB_matrix0( unsigned ht, unsigned len );
siMatrix __vf  MSI_matrix(  unsigned ht, unsigned len );
siMatrix __vf  MSI_matrix0( unsigned ht, unsigned len );
usMatrix __vf  MUS_matrix(  unsigned ht, unsigned len );
usMatrix __vf  MUS_matrix0( unsigned ht, unsigned len );
iMatrix  __vf  MI_matrix(   unsigned ht, unsigned len );
iMatrix  __vf  MI_matrix0(  unsigned ht, unsigned len );
uMatrix  __vf  MU_matrix(   unsigned ht, unsigned len );
uMatrix  __vf  MU_matrix0(  unsigned ht, unsigned len );
liMatrix __vf  MLI_matrix(  unsigned ht, unsigned len );
liMatrix __vf  MLI_matrix0( unsigned ht, unsigned len );
ulMatrix __vf  MUL_matrix(  unsigned ht, unsigned len );
ulMatrix __vf  MUL_matrix0( unsigned ht, unsigned len );
qiMatrix __vf  MQI_matrix(  unsigned ht, unsigned len );
qiMatrix __vf  MQI_matrix0( unsigned ht, unsigned len );
#if defined( V_HUGE )
   #define MUI_matrix  MUL_matrix
   #define MUI_matrix0 MUL_matrix0
#else
   #define MUI_matrix  MU_matrix
   #define MUI_matrix0 MU_matrix0
#endif
    /*  notice that, in the memory model HUGE,
        neither len nor ht may exceed 32767/sizeof(type)            */

 /* the following functions allocate pointer vectors and pointer matrices: */ 
#if defined __COMPACT__ || defined __LARGE__ || defined __HUGE__
    #define VUP_vector  VUL_vector  /* pointer to vector */
    #define MUP_matrix  MUL_matrix  /* pointer to matrix */
#else
    #define VUP_vector  VU_vector
    #define MUP_matrix  MU_matrix
#endif

/*   de-allocation of matrices (common to all data types): */
void    __vf  Mfree( void **M );
#define M_free( M ) Mfree( (void **)(M) )
void    __vf  M_nfree( unsigned n, ... );

#ifdef __cplusplus
}  // end of extern "C"
#endif

#undef V_DATAPTR
#endif   /* __MATLIB_H  */
