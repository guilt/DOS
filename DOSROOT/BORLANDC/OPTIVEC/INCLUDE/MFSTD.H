/*  MFstd.h

  matrix management functions:
  manipulations on matrices of data type "float"
  (single-precision real numbers)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#if !defined( __MFSTD_H )
#define __MFSTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VFSTD_H )
#include <VFstd.h>
#endif
#if !defined( __VFMATH_H )
#include <VFmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

fMatrix __vf  MF_matrix(  unsigned ht, unsigned len );
fMatrix __vf  MF_matrix0( unsigned ht, unsigned len );
    /*  notice that, in the memory model HUGE,
        neither len nor ht may exceed 8191            */

/***************************************************************************
 *  The following definitions ensure compatibility between dynamically     *
 *  and statically allocated matrices. The definitions are somewhat        *
 *  cumbersome, but the result for you is that you need not care about     *
 *  the differences between the two types.                                 *
 *  (Internally, the address of the first element of any matrix is needed; *
 *  the expression "MA[0]" is evaluated in a different way for both types, *
 *  but yields in either case the correct address to be passed to the      *
 *  function you wish to call.)                                            *
 *  Only in the rare case that you need to pass the address of one of      *
 *  these functions as an argument to another function, you have to use    *
 *  the actual run-time functions defined further below. Be careful with   *
 *  this: future development of compilers may allow us to avoid this un-   *
 *  handy scheme of macros. So future versions of MatrixLib may no longer  *
 *  use these run-time names.                                              *
 ***************************************************************************/


/***  Addressing single elements of dynamically allocated matrices: ******
     These two functions are for compatibility with Pascal
     (where elements of dynamically allocated matrices are not directly
     accessible), and for getting around the pointer arithmetics bug in
     some versions of Borland C++.                                         */

#define MF_Pelement( MA, ht, len, m, n ) MFPelement( MA[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MF_element( MA, ht, len, m, n ) (*MFPelement( MA[0], ht, len, m, n ))
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VFstd.h>, <VFmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VF_equ1( MA[0], ht * len );
*/

#define MF_equ0( MA, ht, len )            VF_equ0( MA[0], ((ui)ht)*len )
#define MF_equ1( MA, len )                MFequ1( MA[0], len ) /* identity matrix */
#define MF_equm1( MA, len )               MFequm1( MA[0], len ) /* neg. identity matrix */
#define MF_outerprod( MA, X, Y, ht, len ) MFouterprod( MA[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MF_Row_equ0( MA, ht, len, iRow )  MFRow_equ0( MA[0], ht, len, iRow )
#define MF_Col_equ0( MA, ht, len, iCol )  MFCol_equ0( MA[0], ht, len, iCol )
#define MF_Dia_equ0( MA, len )            MFDia_equ0( MA[0], len )
#define MF_Row_equC( MA, ht, len, iRow, C ) \
                                        MFRow_equC( MA[0], ht, len, iRow, C )
#define MF_Col_equC( MA, ht, len, iCol, C ) \
                                        MFCol_equC( MA[0], ht, len, iCol, C )
#define MF_Dia_equC( MA, len, C )       MFDia_equC( MA[0], len, C )

#define MF_Row_equV( MA, ht, len, iRow, X ) \
                                        MFRow_equV( MA[0], ht, len, iRow, X )
#define MF_Col_equV( MA, ht, len, iCol, X ) \
                                        MFCol_equV( MA[0], ht, len, iCol, X )
#define MF_Dia_equV( MA, len, X )       MFDia_equV( MA[0], len, X )

#define MF_Trd_equM( MA, MTrd, len )    MFTrd_equM( MA[0], MTrd[0], len )
#define MF_Trd_extract( MTrd, MA, len ) MFTrd_extract( MTrd[0], MA[0], len )

#define MF_equM( MB, MA, ht, len )  VF_equV( MB[0], MA[0], (ui)(ht)*(len) )
#define MF_neg( MB, MA, ht, len )   VF_neg( MB[0], MA[0], ((ui)ht)*len )

#define MF_UequL( MA, len ) MFUequL( MA[0], len )
#define MF_LequU( MA, len ) MFLequU( MA[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_DtoF( MF, MD, ht, len ) V_DtoF( MF[0], MD[0], ((ui)ht)*len )
#define M_EtoF( MF, ME, ht, len ) V_EtoF( MF[0], ME[0], ((ui)ht)*len )
#define M_FtoD( MD, MF, ht, len ) V_FtoD( MD[0], MF[0], ((ui)ht)*len )
#define M_FtoE( ME, MF, ht, len ) V_FtoE( ME[0], MF[0], ((ui)ht)*len )

            /* suitable windows for MF_spectrum: */
#define MF_Hanning( MA, ht, len )  MFHanning( MA[0], ht, len )
#define MF_Parzen( MA, ht, len )   MFParzen( MA[0], ht, len )
#define MF_Welch( MA, ht, len )    MFWelch( MA[0], ht, len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MF_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MFsubmatrix(  MSub[0], subHt, subLen, \
                             MSrce[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MF_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MFsubmatrix_equM(  MDest[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             MSrce[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MF_Row_extract( Y, MA, ht, len, iRow ) \
                                     MFRow_extract( Y, MA[0], ht, len, iRow )
#define MF_Col_extract( Y, MA, ht, len, iCol ) \
                                     MFCol_extract( Y, MA[0], ht, len, iCol )
#define MF_Dia_extract( Y, MA, len ) MFDia_extract( Y, MA[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MF_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MFRow_delete( MB[0], MA[0], htA, lenA, iRow )
#define MF_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MFCol_delete( MB[0], MA[0], htA, lenA, iCol )
#define MF_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MFRow_insert( MB[0], MA[0], htB, lenB, iRow, X )
#define MF_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MFCol_insert( MB[0], MA[0], htB, lenB, iCol, X )

/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MF_Row_addC( MA, ht, len, iRow, C ) \
                                     MFRow_addC( MA[0], ht, len, iRow, C )
#define MF_Col_addC( MA, ht, len, iCol, C ) \
                                     MFCol_addC( MA[0], ht, len, iCol, C )
#define MF_Dia_addC( MA, len, C )    MFDia_addC( MA[0], len, C )

#define MF_Row_addV( MA, ht, len, iRow, X ) \
                                     MFRow_addV( MA[0], ht, len, iRow, X )
#define MF_Col_addV( MA, ht, len, iCol, X ) \
                                     MFCol_addV( MA[0], ht, len, iCol, X )
#define MF_Dia_addV( MA, len, X )    MFDia_addV( MA[0], len, X )

#define MF_Row_subC( MA, ht, len, iRow, C ) \
                                     MFRow_subC( MA[0], ht, len, iRow, C )
#define MF_Col_subC( MA, ht, len, iCol, C ) \
                                     MFCol_subC( MA[0], ht, len, iCol, C )
#define MF_Dia_subC( MA, len, C )    MFDia_subC( MA[0], len, C )

#define MF_Row_subV( MA, ht, len, iRow, X ) \
                                     MFRow_subV( MA[0], ht, len, iRow, X )
#define MF_Col_subV( MA, ht, len, iCol, X ) \
                                     MFCol_subV( MA[0], ht, len, iCol, X )
#define MF_Dia_subV( MA, len, X )    MFDia_subV( MA[0], len, X )

#define MF_Row_subrC( MA, ht, len, iRow, C ) \
                                     MFRow_subrC( MA[0], ht, len, iRow, C )
#define MF_Col_subrC( MA, ht, len, iCol, C ) \
                                     MFCol_subrC( MA[0], ht, len, iCol, C )
#define MF_Dia_subrC( MA, len, C )   MFDia_subrC( MA[0], len, C )

#define MF_Row_subrV( MA, ht, len, iRow, X ) \
                                     MFRow_subrV( MA[0], ht, len, iRow, X )
#define MF_Col_subrV( MA, ht, len, iCol, X ) \
                                     MFCol_subrV( MA[0], ht, len, iCol, X )
#define MF_Dia_subrV( MA, len, X )   MFDia_subrV( MA[0], len, X )

#define MF_Row_mulC( MA, ht, len, iRow, C ) \
                                     MFRow_mulC( MA[0], ht, len, iRow, C )
#define MF_Col_mulC( MA, ht, len, iCol, C ) \
                                     MFCol_mulC( MA[0], ht, len, iCol, C )
#define MF_Dia_mulC( MA, len, C )    MFDia_mulC( MA[0], len, C )

#define MF_Row_mulV( MA, ht, len, iRow, X ) \
                                     MFRow_mulV( MA[0], ht, len, iRow, X )
#define MF_Col_mulV( MA, ht, len, iCol, X ) \
                                     MFCol_mulV( MA[0], ht, len, iCol, X )
#define MF_Dia_mulV( MA, len, X )    MFDia_mulV( MA[0], len, X )

#define MF_Row_divC( MA, ht, len, iRow, C ) \
                                     MFRow_divC( MA[0], ht, len, iRow, C )
#define MF_Col_divC( MA, ht, len, iCol, C ) \
                                     MFCol_divC( MA[0], ht, len, iCol, C )
#define MF_Dia_divC( MA, len, C )    MFDia_divC( MA[0], len, C )

#define MF_Row_divV( MA, ht, len, iRow, X ) \
                                      MFRow_divV( MA[0], ht, len, iRow, X )
#define MF_Col_divV( MA, ht, len, iCol, X ) \
                                      MFCol_divV( MA[0], ht, len, iCol, X )
#define MF_Dia_divV( MA, len, X )     MFDia_divV( MA[0], len, X )

#define MF_Row_divrC( MA, ht, len, iRow, C ) \
                                      MFRow_divrC( MA[0], ht, len, iRow, C )
#define MF_Col_divrC( MA, ht, len, iCol, C ) \
                                      MFCol_divrC( MA[0], ht, len, iCol, C )
#define MF_Dia_divrC( MA, len, C )    MFDia_divrC( MA[0], len, C )

#define MF_Row_divrV( MA, ht, len, iRow, X ) \
                                      MFRow_divrV( MA[0], ht, len, iRow, X )
#define MF_Col_divrV( MA, ht, len, iCol, X ) \
                                      MFCol_divrV( MA[0], ht, len, iCol, X )
#define MF_Dia_divrV( MA, len, X )    MFDia_divrV( MA[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MF_Rows_max( Y, MA, ht, len )     MFRows_max( Y, MA[0], ht, len )
#define MF_Cols_max( Y, MA, ht, len )     MFCols_max( Y, MA[0], ht, len )
#define MF_Dia_max(  MA, len )            MFDia_max(  MA[0], len )
#define MF_Rows_min( Y, MA, ht, len )     MFRows_min( Y, MA[0], ht, len )
#define MF_Cols_min( Y, MA, ht, len )     MFCols_min( Y, MA[0], ht, len )
#define MF_Dia_min(  MA, len )            MFDia_min(  MA[0], len )

#define MF_Rows_absmax( Y, MA, ht, len )  MFRows_absmax( Y, MA[0], ht, len )
#define MF_Cols_absmax( Y, MA, ht, len )  MFCols_absmax( Y, MA[0], ht, len )
#define MF_Dia_absmax(  MA, len )         MFDia_absmax(  MA[0], len )
#define MF_Rows_absmin( Y, MA, ht, len )  MFRows_absmin( Y, MA[0], ht, len )
#define MF_Cols_absmin( Y, MA, ht, len )  MFCols_absmin( Y, MA[0], ht, len )
#define MF_Dia_absmin(  MA, len )         MFDia_absmin(  MA[0], len )

#define MF_Rows_sum( Y, MA, ht, len )     MFRows_sum( Y, MA[0], ht, len )
#define MF_Cols_sum( Y, MA, ht, len )     MFCols_sum( Y, MA[0], ht, len )
#define MF_Dia_sum(  MA, len )            MFDia_sum(  MA[0], len )
#define MF_Rows_prod( Y, MA, ht, len )    MFRows_prod( Y, MA[0], ht, len )
#define MF_Cols_prod( Y, MA, ht, len )    MFCols_prod( Y, MA[0], ht, len )
#define MF_Dia_prod(  MA, len )           MFDia_prod( MA[0], len )

#define MF_Rows_runsum( MA, ht, len )     MFRows_runsum( MA[0], ht, len )
#define MF_Cols_runsum( MA, ht, len )     MFCols_runsum( MA[0], ht, len )
#define MF_Rows_runprod( MA, ht, len )    MFRows_runprod( MA[0], ht, len )
#define MF_Cols_runprod( MA, ht, len )    MFCols_runprod( MA[0], ht, len )

#define MF_Rows_rotate( MA, ht, len, pos) MFRows_rotate( MA[0], ht, len, pos )
#define MF_Cols_rotate( MA, ht, len, pos) MFCols_rotate( MA[0], ht, len, pos )
#define MF_Rows_reflect( MA, ht, len)     MFRows_reflect( MA[0], ht, len )
#define MF_Cols_reflect( MA, ht, len)     MFCols_reflect( MA[0], ht, len )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MF_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MFRows_exchange( MA[0], ht, len, row1, row2 )
#define MF_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MFCols_exchange( MA[0], ht, len, col1, col2 )

#define MF_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MFRows_add( MA[0], ht, len, destRow, srceRow )
#define MF_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MFCols_add( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MF_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MFRows_sub( MA[0], ht, len, destRow, srceRow )
#define MF_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MFCols_sub( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MF_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MFRows_Cadd( MA[0], ht, len, destRow, srceRow, C )
#define MF_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MFCols_Cadd( MA[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MF_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MFRows_lincomb( MA[0], ht, len, destRow, destC, srceRow, srceC )
#define MF_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MFCols_lincomb( MA[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*************************  Transposing a matrix **********************/

#define MF_transpose( MTr, MA, htTr, lenTr ) \
             MFtranspose( MTr[0], MA[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */


/************************ Matrix Arithmetics *************************/

#define MF_addM( MC, MA, MB, htA, lenA ) \
                 VF_addV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MF_addMT( MC, MA, MB, htA, lenA ) \
                 MFaddMT( MC[0], MA[0], MB[0], htA, lenA )
#define MF_subM( MC, MA, MB, htA, lenA ) \
                 VF_subV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MF_subMT( MC, MA, MB, htA, lenA ) \
                 MFsubMT( MC[0], MA[0], MB[0], htA, lenA )
#define MF_subrMT( MC, MA, MB, htA, lenA ) \
                 MFsubrMT( MC[0], MA[0], MB[0], htA, lenA )
#define MF_mulC( MB, MA, htA, lenA, C ) \
                 VF_mulC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MF_divC( MB, MA, htA, lenA, C ) \
                 VF_divC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MFs_addM( MC, MA, MB, htA, lenA, C ) \
                 VFs_addV( MC[0], MA[0], MB[0], ((ui)htA)*lenA, C )
#define MFs_addMT( MC, MA, MB, htA, lenA, C ) \
                 MFsaddMT( MC[0], MA[0], MB[0], htA, lenA, C )
#define MFs_subM( MC, MA, MB, htA, lenA, C ) \
                 VFs_subV( MC[0], MA[0], MB[0], ((ui)htA)*lenA, C )
#define MFs_subMT( MC, MA, MB, htA, lenA, C ) \
                 MFssubMT( MC[0], MA[0], MB[0], htA, lenA, C )
#define MFs_subrMT( MC, MA, MB, htA, lenA, C ) \
                 MFssubrMT( MC[0], MA[0], MB[0], htA, lenA, C )
#define MF_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VF_lincomb( MC[0], MA[0], MB[0], ((ui)htA)*lenA, CA, CB )

#define MF_mulV( Y, MA, X, htA, lenA ) \
                    MFmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MF_TmulV( Y, MA, X, htA, lenA ) \
                    MFTmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VF_mulM( Y, X, MA, htA, lenA ) \
                    VFmulM( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VF_ (not MF_)    */
#define VF_mulMT( Y, X, MA, htA, lenA ) \
                    VFmulMT( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MF_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MFmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MF_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MFmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MF_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MFTmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MF_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MFTmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MFdia_mulM(  MC, MADia, MB, htB, lenB )  MFdiamulM(  MC[0], MADia, MB[0], htB, lenB )
#define MFdia_mulMT( MC, MADia, MB, htB, lenB )  MFdiamulMT( MC[0], MADia, MB[0], htB, lenB )
#define MF_mulMdia(  MC, MA, MBDia, htA, lenA )  MFmulMdia(  MC[0], MA[0], MBDia, htA, lenA )
#define MF_TmulMdia( MC, MA, MBDia, htA, lenA )  MFTmulMdia( MC[0], MA[0], MBDia, htA, lenA )


/*************************  Linear Algebra    *****************************/

   /*  The standard treatment of linear systems is based
       on LUD (matrix decomposition into Upper-triangular
       and Lower-triangular components). The result of the
       decomposition step is used for further operations.  */

#define MF_LUdecompose( MLU, Ind, MA, len ) \
                    MFLUdecompose( MLU[0], Ind, MA[0], len )
            /* returns "permut" = +-1 which is needed for MF_LUdet.
               for singularities not cured by editing, permut is 0  */
int     __vf MF_LUDresult( void );
    /* returns 0, if MF_LUdecompose was successful;
       returns 1, if MA was (nearly) singular in MF_LUdecompose.   */
void    __vf MF_LUDsetEdit( float Thresh );
float   __vf MF_LUDgetEdit( void );
     /*  Editing threshold valid for MF_LUdecompose;
         may be used to cure singularities           */

#define MF_LUsolve( X, MLU, B, Ind, len ) \
                    MFLUsolve( X, MLU[0], B, Ind, len )
#define MF_LUinv( MInv, MLU, Ind, len ) \
                    MFLUinv( MInv[0], MLU[0], Ind, len )
#define MF_LUdet( MLU, len, permut ) MFLUdet( MLU[0], len, permut )
#define MF_LUimprove( X, B, MA, MLU, Ind, len ) \
                      MFLUimprove( X, B, MA[0], MLU[0], Ind, len )

    /****  Special treatment of over- or under-determined
           linear systems, i.e. of matrices with len != ht
           and of singular matrices:
           SVD (Singular Value Decomposition)       ****/

#define MF_SVdecompose( MU, MV, W, MA, htA, lenA ) \
                    MFSVdecompose( MU[0], MV[0], W, MA[0], htA, lenA )
            /*  sizB = htA,  sizX = sizW = htV = lenV = lenA  */
#define MF_SVsolve( X, MU, MV, W, B, htU, lenU ) \
                    MFSVsolve( X, MU[0], MV[0], W, B, htU, lenU )
            /*  lenU = lenA,  htU = max( lenA, htA ) as fed into
                MD_SVdecompose   */
void    __vf MF_SVDsetEdit( float Thresh );
float   __vf MF_SVDgetEdit( void );
    /* Override of the standard values for editing threshholds
       in MF_SVsolve. Calling MF_setEdit with Thresh=0.0 means
       that you do the necessary editing of W yourself
       before calling MD_SVsolve                           */

 /*****  "Easy-to-use" versions of the matrix functions
          using LUD or SVD.
          They allocate their own working space and rely
          on your setting of the editing threshold. In
          case of memory stress, you should better use the
          two-step methods declared above.            ***/
#define MF_solve( X, MA, B, len ) \
                    MFsolve( X, MA[0], B, len )
#define MF_inv( MInv, MA, len ) \
                    MFinv( MInv[0], MA[0], len )
#define MF_det(  MA, len ) \
                    MFdet( MA[0], len )
#define MF_solveBySVD( X, MA, B, ht, len ) \
                    MFsolveBySVD( X, MA[0], B, ht, len )
         /*  sizX = len,  sizB = ht  */
#define MF_safeSolve( X, MA, B, len ) \
                    MFsafeSolve( X, MA[0], B, len )
        /* MF_safeSolve tries first LUD. If that fails, SVD is done.
           X[i] will be 0.0 instead of INF for those i corresponding
           to singularities. If even SVD fails, all X[i] are set to 0.0.
           return value 0: success via LUD; 1: success via SVD; -1: failure */

      /*********  Eigenvalues and Eigenvectors  ********/
      /*** only the most frequent case of symmetric real matrices
           is covered here! *********/

#define MFsym_eigenvalues( EigV, EigM, MA, len, CalcEigenVec ) \
                    MFs_eigenvalues( EigV, EigM[0], MA[0], len, CalcEigenVec )
                        /*  Eigenvalues are returned in EigV.
                            CalcEigenVec = 0 means that only eigenvalues
                            are needed; CalcEigenVec != 0 means that
                            also eigenvectors are calculated. If so,
                            eigenvectors are returned as the columns of EigM.
                            Even if eigenvectors are not desired, EigM is
                            needed by the function as working-space. Then, on
                            output, it will contain just rubbish.
                            MA may be overwritten by EigM. */

/***************** Two-Dimensional Fourier-Transform Methods ************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
fComplex  __vf   VF_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf   VF_setRspEdit( fComplex Trunc );
           /* these are the same functions as used
              in the one-dimensional case */

#define MFl_FFT( MY, MX, ht, len, dir )     MFlFFT( MY[0], MX[0], ht, len, dir )
#define MFs_FFT( MY, MX, ht, len, dir )     MFsFFT( MY[0], MX[0], ht, len, dir )
#define MFl_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFlconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MFl_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFldeconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MFl_filter( MY, MX, MFlt, ht, len ) MFlfilter( MY[0], MX[0], MFlt[0], ht, len )
#define MFl_autocorr( MACorr, MX, ht, len ) MFlautocorr( MACorr[0], MX[0], ht, len )
#define MFl_xcorr( MXCorr, MX, MY, ht, len) MFlxcorr( MXCorr[0], MX[0], MY[0], ht, len )
#define MFl_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MFlspectrum( MSpec[0], htSpec, lenSpec, MX[0], htX, lenX, MWin[0] )
                  /* htSpec, lenSpec must be 2**n,
                     MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                     htX >= n*htSpec,  lenX >= n*lenSpec,
                     htWin = 2*htSpec, lenWin = 2*lenSpec */

#define MFs_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFsconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MFs_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MFsdeconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MFs_filter( MY, MX, MFlt, ht, len ) MFsfilter( MY[0], MX[0], MFlt[0], ht, len )
#define MFs_autocorr( MACorr, MX, ht, len ) MFsautocorr( MACorr[0], MX[0], ht, len )
#define MFs_xcorr( MXCorr, MX, MY, ht, len) MFsxcorr( MXCorr[0], MX[0], MY[0], ht, len )
#define MFs_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MFsspectrum( MSpec[0], htSpec, lenSpec, MX[0], htX, lenX, MWin[0] )
                /*   htSpec, lenSpec must be 2**n,
                     MSpec has [htSpec+1][lenSpec+1] elements (!)
                     htX >= n*htSpec,  lenX >= n*lenSpec,
                     htWin = 2*htSpec, lenWin = 2*lenSpec     */

#if defined( __LARGE__ ) || defined( __COMPACT__ ) || defined ( __HUGE__ )
   #define MF_FFT         MFl_FFT
   #define MF_convolve    MFl_convolve
   #define MF_deconvolve  MFl_deconvolve
   #define MF_filter      MFl_filter
   #define MF_autocorr    MFl_autocorr
   #define MF_xcorr       MFl_xcorr
   #define MF_spectrum    MFl_spectrum
#else
   #define MF_FFT         MFs_FFT
   #define MF_convolve    MFs_convolve
   #define MF_deconvolve  MFs_deconvolve
   #define MF_filter      MFs_filter
   #define MF_autocorr    MFs_autocorr
   #define MF_xcorr       MFs_xcorr
   #define MF_spectrum    MFs_spectrum
#endif


/************************** Data Fitting *********************************

  Notice that some of these functions have the prefix VF_, others MF_.
  This depends on the form in which the data to be fitted are recorded:
  vectors are fitted by the VF_ functions, matrices by the MF_ functions.
  All of these functions employ matrix methods internally. The weighted
  versions return covariances in a matrix "Covar". So they are all
  contained in MatrixLib and declared here.
*/

void __vf VF_polyfit( fVector A, unsigned deg, fVector X, fVector Y, ui sizex );
#define   VF_polyfitwW( A, Covar, deg, X, Y, InvVar, sizex ) \
          VFpolyfitwW( A, Covar[0], deg, X, Y, InvVar, sizex )
       /* the size of A is deg+1 and Covar has [deg+1][deg+1] elements! */

void __vf VF_linfit( fVector A, iVector AStatus, unsigned npars,
                     fVector X, fVector Y, ui sizex,
                     void (*funcs)(fVector BasFuncs, float x, unsigned nfuncs) );
#define   VF_linfitwW( A, Covar, AStatus, npars, X, Y, InvVar, sizex, funcs ) \
          VFlinfitwW( A, Covar[0], AStatus, npars, X, Y, InvVar, sizex, funcs )
#define   MF_linfit( A, AStatus, npars, X, Y, MZ, htZ, lenZ, funcs ) \
          MFlinfit( A, AStatus, npars, X, Y, MZ[0], htZ, lenZ, funcs )
#define   MF_linfitwW( A, Covar, AStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, funcs ) \
          MFlinfitwW( A, Covar[0], AStatus, npars, X, Y, MZ[0], MInvVar[0], htZ, lenZ, funcs )

void  __vf VF_setLinfitNeglect( float Thresh );
                   /* neglect A[i]=0, if significance smaller than Thresh */
float __vf VF_getLinfitNeglect( void );

float __vf VF_nonlinfit( fVector A, iVector AStatus, unsigned npars,
                         fVector X, fVector Y, ui sizex,
                         void (*modelfunc)(fVector YModel, fVector XModel, ui size),
                         void (*derivatives)(fVector dYdAi,fVector X, ui size, unsigned iPar) );
            /* returns figure-of-merit of best A. If you don't know the partial
               derivatives with respect to A, call with derivatives=NULL */
#define   VF_nonlinfitwW( A, Covar, AStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv ) \
          VFnonlinfitwW( A, Covar[0], AStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv )
#define   MF_nonlinfit( A, AStatus, npars, X, Y, MZ, htZ, lenZ, modelfunc, deriv ) \
          MFnonlinfit( A, AStatus, npars, X, Y, MZ[0], htZ, lenZ, modelfunc, deriv )
#define   MF_nonlinfitwW( A, Covar, AStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, modelfunc, deriv ) \
          MFnonlinfitwW( A, Covar[0], AStatus, npars, X, Y, MZ[0], MInvVar[0], htZ, lenZ, modelfunc, deriv )

        /* If you know some partial derivatives, you may call these functions
           for those parameters for which you do not know them:           */
void     __vf VF_nonlinfit_autoDeriv( fVector dYdAi, fVector X, ui size, unsigned ipar );
void     __vf VF_nonlinfitwW_autoDeriv( fVector dYdAi, fVector X, ui size, unsigned ipar );
void     __vf MF_nonlinfit_autoDeriv( fMatrix dZdAi, unsigned htZ, unsigned lenZ, fVector X, fVector Y, unsigned ipar );
void     __vf MF_nonlinfitwW_autoDeriv( fMatrix dZdAi, unsigned htZ, unsigned lenZ, fVector X, fVector Y, unsigned ipar );
       /* The following functions allow to monitor the progress of
          a nonlinear fitting procedure or to manually stop it:     */
float    __vf VF_nonlinfit_getChi2( void );
float    __vf VF_nonlinfitwW_getChi2( void );
float    __vf MF_nonlinfit_getChi2( void );
float    __vf MF_nonlinfitwW_getChi2( void );
void     __vf VF_nonlinfit_getBestValues( fVector ABest );
void     __vf VF_nonlinfitwW_getBestValues( fVector ABest );
void     __vf MF_nonlinfit_getBestValues( fVector ABest );
void     __vf MF_nonlinfitwW_getBestValues( fVector ABest );
unsigned __vf VF_nonlinfit_getTestRun( void );
unsigned __vf VF_nonlinfitwW_getTestRun( void );
unsigned __vf MF_nonlinfit_getTestRun( void );
unsigned __vf MF_nonlinfitwW_getTestRun( void );
unsigned __vf VF_nonlinfit_getTestPar( void );
unsigned __vf VF_nonlinfitwW_getTestPar( void );
unsigned __vf MF_nonlinfit_getTestPar( void );
unsigned __vf MF_nonlinfitwW_getTestPar( void );
int      __vf VF_nonlinfit_getTestDir( void );
int      __vf VF_nonlinfitwW_getTestDir( void );
int      __vf MF_nonlinfit_getTestDir( void );
int      __vf MF_nonlinfitwW_getTestDir( void );
void     __vf VF_nonlinfit_stop( void );
void     __vf VF_nonlinfitwW_stop( void );
void     __vf MF_nonlinfit_stop( void );
void     __vf MF_nonlinfitwW_stop( void );

#ifdef __BORLANDC__
    #pragma option -a-  /* avoid insertion of dummy bytes */
#else   /* MS Visual C++ */
    #pragma pack(push,1)
#endif    /*  Borland or Microsoft */
typedef struct VF_NONLINFITOPTIONS
{
      int        FigureOfMerit;  /*  0:least squares, 1:robust */
             /* Convergence conditions: if the changes achieved
                in successive iterations are lower than any of the
                following values, this signals convergence. Set
                criteria to 0.0, if not applicable              */
      float      AbsTolChi,  /* absolute change of chi */
                 FracTolChi, /* fractional change of chi */
                 AbsTolPar,  /* absolute change of all parameters */
                 FracTolPar; /* fractional change of all parameters */
      unsigned   HowOftenFulfill; /* how often fulfill the above conditions? */
      unsigned   LevelOfMethod;  /* 1: Levenberg-Marquardt method,
                                    2: Downhill Simplex (Nelder and Mead) method,
                                    3: both methods alternating;
                                       add 4 to this in order to try
                                       breaking out of local minima;
                                    0: no fit, calculate only chi2 (and Covar) */
      unsigned   LevMarIterations; /* max.number of successful iterations of LevMar */
      unsigned   LevMarStarts; /* number of starts per LevMar run */
      float      LambdaStart,
                 LambdaMin, LambdaMax,
                 LambdaDiv, LambdaMul;    /* LevMar parameter lambda */
      unsigned   DownhillIterations; /* max.number of successful iterations in Downhill */
      float      DownhillReflection,  /* re-shaping of the simplex */
                 DownhillContraction,
                 DownhillExpansion;
      unsigned   TotalStarts;  /* max. number of LevMar/Downhill pairs */
      fVector    UpperLimits;  /* impose upper limits on parameters */
      fVector    LowerLimits;  /* impose lower limits on parameters */
      void       (*Restrictions)(void);  /* user-defined editing of parameters */
}  VF_NONLINFITOPTIONS;

void __vf VF_setNonlinfitOptions( VF_NONLINFITOPTIONS _VFAR *Options );
void __vf VF_getNonlinfitOptions( VF_NONLINFITOPTIONS _VFAR *Options );

typedef struct VF_EXPERIMENT
{
    fVector X, Y, InvVar;
    ui      size;
    float   WeightOfExperiment;
     /* InvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} VF_EXPERIMENT;

typedef struct MF_EXPERIMENT
{
    fVector   X, Y;
    fMatrix   MZ, MInvVar;  /* here no compatibility with static matrices! */
    unsigned  htZ, lenZ;
    float     WeightOfExperiment;
     /* MInvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} MF_EXPERIMENT;
#ifdef __BORLANDC__
    #pragma option -a.   /* restore default data packing  */
#else   /* MS Visual C++ */
    #pragma pack(pop)
#endif


void __vf VF_multiLinfit( fVector A, iVector AStatus, unsigned ma,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(fVector BasFuncs, float x,
                              unsigned nfuncs, unsigned iexperiment) );
#define   VF_multiLinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, funcs ) \
          VFmultiLinfitwW( A, Covar[0], AStatus, npars, ListOfEx, nexp, funcs )
void __vf MF_multiLinfit( fVector A, iVector AStatus, unsigned ma,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(fVector BasFuncs, float x, float y,
                              unsigned nfuncs, unsigned iexperiment) );
#define   MF_multiLinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, funcs ) \
          MFmultiLinfitwW( A, Covar[0], AStatus, npars, ListOfEx, nexp, funcs )
float __vf VF_multiNonlinfit( fVector A, iVector AStatus, unsigned npars,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(fVector YModel, fVector XModel,
                                  ui size, unsigned iexperiment),
                void (*derivatives)(fVector dYdAi,fVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) );
            /* returns figure-of-merit of best A. If you don't know the
               partial derivatives, set derivatives=NULL */
#define   VF_multiNonlinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, modfunc, deriv ) \
          VFmultiNonlinfitwW( A, Covar[0], AStatus, npars, ListOfEx, nexp, modfunc, deriv )
float __vf MF_multiNonlinfit( fVector A, iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(fMatrix MZModel, unsigned htZ, unsigned lenZ,
                                  fVector X, fVector Y, unsigned iexperiment),
                void (*derivatives)(fMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    fVector X, fVector Y, unsigned ipar,
                                    unsigned iexperiment) );
#define   MF_multiNonlinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, modfunc, deriv ) \
          MFmultiNonlinfitwW( A, Covar[0], AStatus, npars, ListOfEx, nexp, modfunc, deriv )

void  __vf VF_multiNonlinfit_autoDeriv( fVector dYdAi, fVector X, ui size,
                                       unsigned ipar, unsigned iexperiment );
void  __vf VF_multiNonlinfitwW_autoDeriv( fVector dYdAi, fVector X, ui size,
                                        unsigned ipar, unsigned iexperiment );
void  __vf MF_multiNonlinfit_autoDeriv( fMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    fVector X, fVector Y,
                                    unsigned ipar, unsigned iexperiment );
void  __vf MF_multiNonlinfitwW_autoDeriv( fMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    fVector X, fVector Y,
                                    unsigned ipar, unsigned iexperiment );
float    __vf VF_multiNonlinfit_getChi2( void );
float    __vf VF_multiNonlinfitwW_getChi2( void );
float    __vf MF_multiNonlinfit_getChi2( void );
float    __vf MF_multiNonlinfitwW_getChi2( void );
void     __vf VF_multiNonlinfit_getBestValues( fVector ABest );
void     __vf VF_multiNonlinfitwW_getBestValues( fVector ABest );
void     __vf MF_multiNonlinfit_getBestValues( fVector ABest );
void     __vf MF_multiNonlinfitwW_getBestValues( fVector ABest );
unsigned __vf VF_multiNonlinfit_getTestRun( void );
unsigned __vf VF_multiNonlinfitwW_getTestRun( void );
unsigned __vf MF_multiNonlinfit_getTestRun( void );
unsigned __vf MF_multiNonlinfitwW_getTestRun( void );
unsigned __vf VF_multiNonlinfit_getTestPar( void );
unsigned __vf VF_multiNonlinfitwW_getTestPar( void );
unsigned __vf MF_multiNonlinfit_getTestPar( void );
unsigned __vf MF_multiNonlinfitwW_getTestPar( void );
int      __vf VF_multiNonlinfit_getTestDir( void );
int      __vf VF_multiNonlinfitwW_getTestDir( void );
int      __vf MF_multiNonlinfit_getTestDir( void );
int      __vf MF_multiNonlinfitwW_getTestDir( void );
void     __vf VF_multiNonlinfit_stop( void );
void     __vf VF_multiNonlinfitwW_stop( void );
void     __vf MF_multiNonlinfit_stop( void );
void     __vf MF_multiNonlinfitwW_stop( void );

/**************************  Input and Output  **************************/

#define MF_fprint( stream, MA, ht, len, linewidth ) \
                    MFfprint( stream, MA[0], ht, len, linewidth )
#define MF_print( MA, ht, len )  MFfprint( stdout, MA[0], ht, len, 80 )
#define MF_cprint( MA, ht, len ) MFcprint( MA[0], ht, len )
  /*  MF_print, MF_cprint usable only for DOS, EasyWin, and Win32 console applications! */

#define MF_write( str, MA, ht, len )   MFwrite( str, MA[0], ht, len )
#define MF_read( MA, ht, len, str )    MFread( MA[0], ht, len, str )
#define MF_setWriteFormat              VF_setWriteFormat
#define MF_setWriteSeparate            VF_setNWriteSeparate
                                   /* write and read in ascii format */
#define MF_store( str, MA, ht, len ) \
                           VF_store( str, MA[0], ((ui) (len))*(ht) );
#define MF_recall( MA, ht, len, str) \
                           VF_recall( MA[0], ((ui) (len))*(ht), str);
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

float _VFAR * MFPelement( fPMatrix X, unsigned ht, unsigned len,
                          unsigned m, unsigned n );
                  /* pointer is normalized in memory model HUGE */
#define MFelement( MA, ht, len, m, n ) (*MFPelement( MA, ht, len, m, n ))

#define MFequ0( MA, ht, len )            VF_equ0( MA, ((ui)ht)*len )
void   __vf  MFequ1( fPMatrix MA, unsigned len );  /* identity matrix */
void   __vf  MFequm1( fPMatrix MA, unsigned len );  /* neg. identity matrix */
void   __vf  MFouterprod( fPMatrix MA, fVector X,  fVector Y,
                          unsigned ht, unsigned len );

void   __vf  MFRow_equ0( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow );
void   __vf  MFCol_equ0( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol );
void   __vf  MFDia_equ0( fPMatrix MA, unsigned len );

void   __vf  MFRow_equC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, float C );
void   __vf  MFCol_equC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, float C );
void   __vf  MFDia_equC( fPMatrix MA, unsigned len, float C );

void   __vf  MFRow_equV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fVector X );
void   __vf  MFCol_equV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fVector X );
void   __vf  MFDia_equV( fPMatrix MA, unsigned len, fVector X );

void   __vf  MFTrd_equM( fPMatrix MA, fPMatrix MTrd, unsigned len );
void   __vf  MFTrd_extract( fPMatrix MTrd, fPMatrix MA, unsigned len );

#define MFequM( MB, MA, ht, len )  VF_equV( MB, MA, (ui)(ht)*(len) )
#define MFneg( MB, MA, ht, len )   VF_neg( MB, MA, (ui)(ht)*(len) )
void   __vf  MFUequL( fPMatrix MA, unsigned len );
void   __vf  MFLequU( fPMatrix MA, unsigned len );

void   __vf  MFHanning( fPMatrix MA, unsigned ht, unsigned len );
void   __vf  MFParzen(  fPMatrix MA, unsigned ht, unsigned len );
void   __vf  MFWelch(   fPMatrix MA, unsigned ht, unsigned len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MFsubmatrix( fPMatrix MSub,
                          unsigned subHt,  unsigned subLen,
                          fPMatrix MSrce,
                          unsigned srceHt,  unsigned srceLen,
                          unsigned firstRowInCol,  unsigned sampInCol,
                          unsigned firstColInRow,  unsigned sampInRow );

void  __vf  MFsubmatrix_equM( fPMatrix MDest,
                               unsigned destHt,     unsigned destLen,
                               unsigned firstRowInCol,  unsigned sampInCol,
                               unsigned firstColInRow,  unsigned sampInRow,
                               fPMatrix MSrce,
                               unsigned srceHt,     unsigned srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MFRow_extract( fVector Y, fPMatrix MA, unsigned ht, unsigned len,
                           unsigned iRow );
void __vf MFCol_extract( fVector Y, fPMatrix MA, unsigned ht, unsigned len,
                           unsigned iCol );
void __vf MFDia_extract( fVector Y, fPMatrix MA, unsigned len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MFRow_delete( fPMatrix MB, fPMatrix MA,
                        unsigned htA, unsigned lenA, unsigned iRow );
void __vf MFCol_delete( fPMatrix MB, fPMatrix MA,
                        unsigned htA, unsigned lenA, unsigned iCol );
void __vf MFRow_insert( fPMatrix MB, fPMatrix MA, unsigned htB,
                        unsigned lenB, unsigned iRow, fVector X );
void __vf MFCol_insert( fPMatrix MB, fPMatrix MA, unsigned htB,
                        unsigned lenB, unsigned iCol, fVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MFRow_addC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, float C );
void   __vf  MFCol_addC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, float C );
void   __vf  MFDia_addC( fPMatrix MA, unsigned len, float C );

void   __vf  MFRow_subC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, float C );
void   __vf  MFCol_subC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, float C );
void   __vf  MFDia_subC( fPMatrix MA, unsigned len, float C );

void   __vf  MFRow_addV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fVector X );
void   __vf  MFCol_addV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fVector X );
void   __vf  MFDia_addV( fPMatrix MA, unsigned len, fVector X );

void   __vf  MFRow_subV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fVector X );
void   __vf  MFCol_subV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fVector X );
void   __vf  MFDia_subV( fPMatrix MA, unsigned len, fVector X );

void   __vf  MFRow_subrC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, float C );
void   __vf  MFCol_subrC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, float C );
void   __vf  MFDia_subrC( fPMatrix MA, unsigned len, float C );

void   __vf  MFRow_subrV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fVector X );
void   __vf  MFCol_subrV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fVector X );
void   __vf  MFDia_subrV( fPMatrix MA, unsigned len, fVector X );

void   __vf  MFRow_mulC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, float C );
void   __vf  MFCol_mulC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, float C );
void   __vf  MFDia_mulC( fPMatrix MA, unsigned len, float C );

void   __vf  MFRow_mulV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fVector X );
void   __vf  MFCol_mulV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fVector X );
void   __vf  MFDia_mulV( fPMatrix MA, unsigned len, fVector X );

void   __vf  MFRow_divC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, float C );
void   __vf  MFCol_divC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, float C );
void   __vf  MFDia_divC( fPMatrix MA, unsigned len, float C );

void   __vf  MFRow_divV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fVector X );
void   __vf  MFCol_divV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fVector X );
void   __vf  MFDia_divV( fPMatrix MA, unsigned len, fVector X );

void   __vf  MFRow_divrC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, float C );
void   __vf  MFCol_divrC( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, float C );
void   __vf  MFDia_divrC( fPMatrix MA, unsigned len, float C );

void   __vf  MFRow_divrV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fVector X );
void   __vf  MFCol_divrV( fPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fVector X );
void   __vf  MFDia_divrV( fPMatrix MA, unsigned len, fVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MFRows_max( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFCols_max( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
float __vf  MFDia_max(  fPMatrix MA, unsigned len );
void  __vf  MFRows_min( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFCols_min( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
float __vf  MFDia_min(  fPMatrix MA, unsigned len );

void  __vf  MFRows_absmax( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFCols_absmax( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
float __vf  MFDia_absmax(  fPMatrix MA, unsigned len );
void  __vf  MFRows_absmin( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFCols_absmin( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
float __vf  MFDia_absmin(  fPMatrix MA, unsigned len );

void  __vf  MFRows_sum( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFCols_sum( fVector Y, fPMatrix MA, unsigned ht, unsigned len );
float __vf  MFDia_sum(  fPMatrix MA, unsigned len );
void  __vf  MFRows_prod(fVector Y, fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFCols_prod(fVector Y, fPMatrix MA, unsigned ht, unsigned len );
float __vf  MFDia_prod( fPMatrix MA, unsigned len );

void  __vf  MFRows_runsum( fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFCols_runsum( fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFRows_runprod( fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFCols_runprod( fPMatrix MA, unsigned ht, unsigned len );

void  __vf  MFRows_rotate( fPMatrix MA, unsigned ht, unsigned len, int pos );
void  __vf  MFCols_rotate( fPMatrix MA, unsigned ht, unsigned len, int pos );
void  __vf  MFRows_reflect( fPMatrix MA, unsigned ht, unsigned len );
void  __vf  MFCols_reflect( fPMatrix MA, unsigned ht, unsigned len );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MFRows_exchange( fPMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );
void   __vf  MFCols_exchange( fPMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );

void   __vf  MFRows_add( fPMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MFCols_add( fPMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MFRows_sub( fPMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MFCols_sub( fPMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MFRows_Cadd( fPMatrix MA, unsigned ht, unsigned len,
                           unsigned destRow, unsigned sourceRow, float C );
void   __vf  MFCols_Cadd( fPMatrix MA, unsigned ht, unsigned len,
                           unsigned destCol, unsigned sourceCol, float C );

void   __vf  MFRows_lincomb( fPMatrix MA, unsigned ht, unsigned len,
                              unsigned destRow,  float  destC,
                              unsigned srceRow,  float  srceC );
void   __vf  MFCols_lincomb( fPMatrix MA, unsigned ht, unsigned len,
                              unsigned destCol,  float  destC,
                              unsigned srceCol,  float  srceC );


/*************************  Transposing a matrix **********************/

void  __vf  MFtranspose( fPMatrix MTr, fPMatrix MA,
                          unsigned htTr, unsigned lenTr );


/************************ Matrix Arithmetics *************************/

#define MFaddM( MC, MA, MB, htA, lenA ) \
                 VF_addV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MFaddMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA );
#define MFsubM( MC, MA, MB, htA, lenA ) \
                 VF_subV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MFsubMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA );
void __vf  MFsubrMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA );
#define MFmulC( MB, MA, htA, lenA, C ) \
                 VF_mulC( MB, MA, ((ui)htA)*lenA, C )
#define MFdivC( MB, MA, htA, lenA, C ) \
                 VF_divC( MB, MA, ((ui)htA)*lenA, C )
#define MFsaddM( MC, MA, MB, htA, lenA, C ) \
                 VFs_addV( MC, MA, MB, ((ui)htA)*lenA, C )
void __vf  MFsaddMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA, float C );
#define MFssubM( MC, MA, MB, htA, lenA, C ) \
                 VFs_subV( MC, MA, MB, ((ui)htA)*lenA, C )
void __vf  MFssubMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA, float C );
void __vf  MFssubrMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA, float C );
#define MFlincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VF_lincomb( MC, MA, MB, ((ui)htA)*lenA, CA, CB )
void  __vf  MFmulV( fVector Y, fPMatrix MA, fVector X,
                    unsigned htA, unsigned lenA );
void  __vf  MFTmulV( fVector Y, fPMatrix MA, fVector X,
                     unsigned htA, unsigned lenA );
void  __vf  VFmulM( fVector Y, fVector X, fPMatrix MA,
                    unsigned htA, unsigned lenA );
void  __vf  VFmulMT( fVector Y, fVector X, fPMatrix MA,
                     unsigned htA, unsigned lenA );
void  __vf  MFmulM( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MFmulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MFTmulM( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MFTmulMT( fPMatrix MC, fPMatrix MA, fPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MFdiamulM( fPMatrix MC, fPMatrix MADia, fPMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MFdiamulMT( fPMatrix MC, fPMatrix MADia, fPMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MFmulMdia( fPMatrix MC, fPMatrix MA, fPMatrix MBDia,
                    unsigned htA, unsigned lenA );
void  __vf  MFTmulMdia( fPMatrix MC, fPMatrix MA, fPMatrix MBDia,
                    unsigned htA, unsigned lenA );


/*************************  Linear Algebra    *****************************/

int    __vf  MFLUdecompose( fPMatrix MLU,  uVector Ind, fPMatrix MA,
                            unsigned len );

void   __vf  MFLUsolve( fVector X, fPMatrix MLU, fVector B, uVector Ind,
                        unsigned len );
void   __vf  MFLUinv( fPMatrix MInv, fPMatrix MLU, uVector Ind,
                      unsigned len );
float  __vf  MFLUdet( fPMatrix MLU, unsigned len, int permut );
void   __vf  MFLUimprove( fVector X, fVector B, fPMatrix MA, fPMatrix MLU,
                          uVector Ind, unsigned len );

int   __vf  MFSVdecompose( fPMatrix MU, fPMatrix MV, fVector W, fPMatrix MA,
                           unsigned htA, unsigned lenA );
void  __vf  MFSVsolve( fVector X, fPMatrix MU, fPMatrix MV, fVector W,
                       fVector B, unsigned htU, unsigned lenU );

          /*  functions using LUD or SVD     */
int    __vf  MFsolve( fVector X, fPMatrix MA, fVector B, unsigned len );
                  /* ret.value != 0 signals error */
int    __vf  MFinv( fPMatrix MInv, fPMatrix MA, unsigned len );
                 /* ret.value != 0 signals error */
float  __vf  MFdet( fPMatrix MA, unsigned len );

int    __vf  MFsolveBySVD( fVector X, fPMatrix MA, fVector B,
                           unsigned htA, unsigned lenA );
              /*  sizX = lenA,  sizB = htA.  ret.value != 0 signals failure */
int    __vf  MFsafeSolve( fVector X, fPMatrix MA, fVector B, unsigned len );
              /* ret.value 0: success via LUD; 1: success via SVD; -1: error */

       /*********  Eigenvalues and Eigenvectors  ********/

void __vf MFs_eigenvalues( fVector EigV, fPMatrix EigM, fPMatrix MA, unsigned len,
                        int CalcEigenVec );

/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf   MFlFFT( fPMatrix MY, fPMatrix MX,
                     unsigned ht, unsigned len, int dir );
void  __vf   MFlconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                          fPMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MFldeconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                            fPMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MFlfilter( fPMatrix MY, fPMatrix MX, fPMatrix MFlt,
                        unsigned ht, unsigned len );
void  __vf   MFlautocorr( fPMatrix MACorr, fPMatrix MX,
                          unsigned ht, unsigned len );
void  __vf   MFlxcorr( fPMatrix MXCorr, fPMatrix MX, fPMatrix MY,
                       unsigned ht, unsigned len );
void  __vf   MFlspectrum( fPMatrix MSpec, unsigned htSpec, unsigned lenSpec,
                          fPMatrix MX, unsigned htX, unsigned lenX,
                          fPMatrix MWin );

void  __vf   MFsFFT( fPMatrix MY, fPMatrix MX,
                     unsigned ht, unsigned len, int dir );
void  __vf   MFsconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                          fPMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MFsdeconvolve( fPMatrix MY, fPMatrix MFlt, fPMatrix MX,
                            fPMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MFsfilter( fPMatrix MY, fPMatrix MX, fPMatrix MFlt,
                        unsigned ht, unsigned len );
void  __vf   MFsautocorr( fPMatrix MACorr, fPMatrix MX,
                          unsigned ht, unsigned len );
void  __vf   MFsxcorr( fPMatrix MXCorr, fPMatrix MX, fPMatrix MY,
                       unsigned ht, unsigned len );
void  __vf   MFsspectrum( fPMatrix MSpec, unsigned htSpec, unsigned lenSpec,
                          fPMatrix MX, unsigned htX, unsigned lenX,
                          fPMatrix MWin );

/*************************  Data Fitting    *******************************/

void __vf VFpolyfitwW( fVector A, fPMatrix Covar, unsigned deg,
                        fVector X, fVector Y, fVector InvVar, ui sizex );
void __vf VFlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fVector InvVar, ui sizex,
                    void (*funcs)(fVector BasFuncs, float x, unsigned nfuncs) );
float __vf VFnonlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fVector InvVar, ui sizex,
                    void (*modelfunc)(fVector YModel, fVector X, ui size),
                    void (*derivatives)(fVector dYdAi, fVector X, ui size, unsigned i) );
void __vf MFlinfit( fVector A, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fPMatrix MZ, unsigned htZ, unsigned lenZ,
                    void (*funcs)(fVector BasFuncs, float x, float y, unsigned nfuncs) );
float __vf MFnonlinfit( fVector A, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fPMatrix MZ, unsigned htZ, unsigned lenZ,
                    void (*modelfunc)(fMatrix MZModel, unsigned htZ, unsigned lenZ, fVector X, fVector Y ),
                    void (*derivatives)(fMatrix dZdAi, unsigned htZ, unsigned lenZ, fVector X, fVector Y, unsigned ipar) );
void __vf MFlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                      fVector X, fVector Y, fPMatrix MZ, fPMatrix MInvVar, unsigned htZ, unsigned lenZ,
                      void (*funcs)(fVector BasFuncs, float x, float y, unsigned nfuncs) );
float __vf MFnonlinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned npars,
                    fVector X, fVector Y, fPMatrix MZ, fPMatrix MInvVar, unsigned htZ, unsigned lenZ,
                    void (*modelfunc)(fMatrix MZModel, unsigned htZ, unsigned lenZ, fVector X, fVector Y ),
                    void (*derivatives)(fMatrix dZdAi, unsigned htZ, unsigned lenZ, fVector X, fVector Y, unsigned ipar) );

void __vf VFmultiLinfitwW( fVector A, fPMatrix Covar, iVector AStatus, unsigned ma,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(fVector BasFuncs, float x,
                              unsigned nfuncs, unsigned nexperiment) );
void __vf MFmultiLinfitwW( fVector A, fPMatrix Covar,
                iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(fVector BasFuncs, float x, float y,
                              unsigned nfuncs, unsigned nexperiment) );
float __vf VFmultiNonlinfitwW( fVector A, fPMatrix Covar,
                iVector AStatus, unsigned npars,
                VF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(fVector YModel, fVector X, ui size,
                                  unsigned iexperiment),
                void (*derivatives)(fVector dYdAi, fVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) );
float __vf MFmultiNonlinfitwW( fVector A, fPMatrix Covar,
                iVector AStatus, unsigned npars,
                MF_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(fMatrix MZModel, unsigned htZ, unsigned lenZ,
                                  fVector X, fVector Y, unsigned iexperiment ),
                void (*derivatives)(fMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    fVector X, fVector Y,
                                    unsigned ipar, unsigned iexperiment) );

      /*************  Input and Output  ****************/

void __vf MFfprint( FILE _VFAR *stream, fPMatrix MA, unsigned ht,
                     unsigned len, unsigned linewidth );
void __vf MFcprint( fPMatrix MA, unsigned ht, unsigned len );
void  __vf    MFwrite( FILE _VFAR *stream, fPMatrix X, unsigned ht, unsigned len  );
void  __vf    MFread( fPMatrix X, unsigned ht, unsigned len, FILE _VFAR *stream );
#define MFstore( str, MA, ht, len ) \
                           VF_store( str, MA, ((ui) (len))*(ht) );
#define MFrecall( MA, ht, len, str) \
                           VF_recall( MA, ((ui) (len))*(ht), str);

#ifdef __cplusplus
}
#endif
#endif 
