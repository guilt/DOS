/*  MEstd.h

  matrix management functions:
  manipulations on matrices of data type "extended"
  (extended-precision real numbers)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#if !defined( __MESTD_H )
#define __MESTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VESTD_H )
#include <VEstd.h>
#endif
#if !defined( __VEMATH_H )
#include <VEmath.h>
#endif

#ifdef __BORLANDC__
       /* the following ca. 1000 lines are only for Borland C++,
		  as neither Visual C++ nor Optima++ support 80-bit reals */
#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

eMatrix __vf  ME_matrix(  unsigned ht, unsigned len );
eMatrix __vf  ME_matrix0( unsigned ht, unsigned len );
    /*  notice that, in the memory model HUGE,
        neither len nor ht may exceed 3275             */

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

#define ME_Pelement( MA, ht, len, m, n ) MEPelement( MA[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define ME_element( MA, ht, len, m, n ) *MEPelement( MA[0], ht, len, m, n )
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VEstd.h>, <VEmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VE_equ1( MA[0], ht * len );
*/

#define ME_equ0( MA, ht, len )            VE_equ0( MA[0], ((ui)ht)*len )
#define ME_equ1( MA, len )                MEequ1( MA[0], len ) /* identity matrix */
#define ME_equm1( MA, len )               MEequm1( MA[0], len ) /* neg. identity matrix */
#define ME_outerprod( MA, X, Y, ht, len ) MEouterprod( MA[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define ME_Row_equ0( MA, ht, len, iRow )  MERow_equ0( MA[0], ht, len, iRow )
#define ME_Col_equ0( MA, ht, len, iCol )  MECol_equ0( MA[0], ht, len, iCol )
#define ME_Dia_equ0( MA, len )            MEDia_equ0( MA[0], len )
#define ME_Row_equC( MA, ht, len, iRow, C ) \
                                        MERow_equC( MA[0], ht, len, iRow, C )
#define ME_Col_equC( MA, ht, len, iCol, C ) \
                                        MECol_equC( MA[0], ht, len, iCol, C )
#define ME_Dia_equC( MA, len, C )       MEDia_equC( MA[0], len, C )

#define ME_Row_equV( MA, ht, len, iRow, X ) \
                                        MERow_equV( MA[0], ht, len, iRow, X )
#define ME_Col_equV( MA, ht, len, iCol, X ) \
                                        MECol_equV( MA[0], ht, len, iCol, X )
#define ME_Dia_equV( MA, len, X )       MEDia_equV( MA[0], len, X )

#define ME_Trd_equM( MA, MTrd, len )    METrd_equM( MA[0], MTrd[0], len )
#define ME_Trd_extract( MTrd, MA, len ) METrd_extract( MTrd[0], MA[0], len )

#define ME_equM( MB, MA, ht, len )  VE_equV( MB[0], MA[0], (ui)(ht)*(len) )
#define ME_neg( MB, MA, ht, len )   VE_neg( MB[0], MA[0], (ui)(ht)*(len) )

#define ME_UequL( MA, len ) MEUequL( MA[0], len )
#define ME_LequU( MA, len ) MELequU( MA[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_EtoF( MF, ME, ht, len ) V_EtoF( MF[0], ME[0], ((ui)ht)*len )
#define M_FtoE( ME, MF, ht, len ) V_FtoE( ME[0], MF[0], ((ui)ht)*len )
#define M_EtoD( MD, ME, ht, len ) V_EtoD( MD[0], ME[0], ((ui)ht)*len )
#define M_DtoE( ME, MD, ht, len ) V_DtoE( ME[0], MD[0], ((ui)ht)*len )

            /* suitable windows for ME_spectrum: */
#define ME_Hanning( MA, ht, len )  MEHanning( MA[0], ht, len )
#define ME_Parzen( MA, ht, len )   MEParzen( MA[0], ht, len )
#define ME_Welch( MA, ht, len )    MEWelch( MA[0], ht, len )


/********  Extracting a submatrix and copying a submatrix back  *********/

#define ME_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MEsubmatrix(  MSub[0], subHt, subLen, \
                             MSrce[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define ME_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MEsubmatrix_equM(  MDest[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             MSrce[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define ME_Row_extract( Y, MA, ht, len, iRow ) \
                                     MERow_extract( Y, MA[0], ht, len, iRow )
#define ME_Col_extract( Y, MA, ht, len, iCol ) \
                                     MECol_extract( Y, MA[0], ht, len, iCol )
#define ME_Dia_extract( Y, MA, len ) MEDia_extract( Y, MA[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define ME_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MERow_delete( MB[0], MA[0], htA, lenA, iRow )
#define ME_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MECol_delete( MB[0], MA[0], htA, lenA, iCol )
#define ME_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MERow_insert( MB[0], MA[0], htB, lenB, iRow, X )
#define ME_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MECol_insert( MB[0], MA[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define ME_Row_addC( MA, ht, len, iRow, C ) \
                                     MERow_addC( MA[0], ht, len, iRow, C )
#define ME_Col_addC( MA, ht, len, iCol, C ) \
                                     MECol_addC( MA[0], ht, len, iCol, C )
#define ME_Dia_addC( MA, len, C )    MEDia_addC( MA[0], len, C )

#define ME_Row_addV( MA, ht, len, iRow, X ) \
                                     MERow_addV( MA[0], ht, len, iRow, X )
#define ME_Col_addV( MA, ht, len, iCol, X ) \
                                     MECol_addV( MA[0], ht, len, iCol, X )
#define ME_Dia_addV( MA, len, X )    MEDia_addV( MA[0], len, X )

#define ME_Row_subC( MA, ht, len, iRow, C ) \
                                     MERow_subC( MA[0], ht, len, iRow, C )
#define ME_Col_subC( MA, ht, len, iCol, C ) \
                                     MECol_subC( MA[0], ht, len, iCol, C )
#define ME_Dia_subC( MA, len, C )    MEDia_subC( MA[0], len, C )

#define ME_Row_subV( MA, ht, len, iRow, X ) \
                                     MERow_subV( MA[0], ht, len, iRow, X )
#define ME_Col_subV( MA, ht, len, iCol, X ) \
                                     MECol_subV( MA[0], ht, len, iCol, X )
#define ME_Dia_subV( MA, len, X )    MEDia_subV( MA[0], len, X )

#define ME_Row_subrC( MA, ht, len, iRow, C ) \
                                     MERow_subrC( MA[0], ht, len, iRow, C )
#define ME_Col_subrC( MA, ht, len, iCol, C ) \
                                     MECol_subrC( MA[0], ht, len, iCol, C )
#define ME_Dia_subrC( MA, len, C )   MEDia_subrC( MA[0], len, C )

#define ME_Row_subrV( MA, ht, len, iRow, X ) \
                                     MERow_subrV( MA[0], ht, len, iRow, X )
#define ME_Col_subrV( MA, ht, len, iCol, X ) \
                                     MECol_subrV( MA[0], ht, len, iCol, X )
#define ME_Dia_subrV( MA, len, X )   MEDia_subrV( MA[0], len, X )

#define ME_Row_mulC( MA, ht, len, iRow, C ) \
                                     MERow_mulC( MA[0], ht, len, iRow, C )
#define ME_Col_mulC( MA, ht, len, iCol, C ) \
                                     MECol_mulC( MA[0], ht, len, iCol, C )
#define ME_Dia_mulC( MA, len, C )    MEDia_mulC( MA[0], len, C )

#define ME_Row_mulV( MA, ht, len, iRow, X ) \
                                     MERow_mulV( MA[0], ht, len, iRow, X )
#define ME_Col_mulV( MA, ht, len, iCol, X ) \
                                     MECol_mulV( MA[0], ht, len, iCol, X )
#define ME_Dia_mulV( MA, len, X )    MEDia_mulV( MA[0], len, X )

#define ME_Row_divC( MA, ht, len, iRow, C ) \
                                     MERow_divC( MA[0], ht, len, iRow, C )
#define ME_Col_divC( MA, ht, len, iCol, C ) \
                                     MECol_divC( MA[0], ht, len, iCol, C )
#define ME_Dia_divC( MA, len, C )    MEDia_divC( MA[0], len, C )

#define ME_Row_divV( MA, ht, len, iRow, X ) \
                                      MERow_divV( MA[0], ht, len, iRow, X )
#define ME_Col_divV( MA, ht, len, iCol, X ) \
                                      MECol_divV( MA[0], ht, len, iCol, X )
#define ME_Dia_divV( MA, len, X )     MEDia_divV( MA[0], len, X )

#define ME_Row_divrC( MA, ht, len, iRow, C ) \
                                      MERow_divrC( MA[0], ht, len, iRow, C )
#define ME_Col_divrC( MA, ht, len, iCol, C ) \
                                      MECol_divrC( MA[0], ht, len, iCol, C )
#define ME_Dia_divrC( MA, len, C )    MEDia_divrC( MA[0], len, C )

#define ME_Row_divrV( MA, ht, len, iRow, X ) \
                                      MERow_divrV( MA[0], ht, len, iRow, X )
#define ME_Col_divrV( MA, ht, len, iCol, X ) \
                                      MECol_divrV( MA[0], ht, len, iCol, X )
#define ME_Dia_divrV( MA, len, X )    MEDia_divrV( MA[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define ME_Rows_max( Y, MA, ht, len )     MERows_max( Y, MA[0], ht, len )
#define ME_Cols_max( Y, MA, ht, len )     MECols_max( Y, MA[0], ht, len )
#define ME_Dia_max(  MA, len )            MEDia_max(  MA[0], len )
#define ME_Rows_min( Y, MA, ht, len )     MERows_min( Y, MA[0], ht, len )
#define ME_Cols_min( Y, MA, ht, len )     MECols_min( Y, MA[0], ht, len )
#define ME_Dia_min(  MA, len )            MEDia_min(  MA[0], len )

#define ME_Rows_absmax( Y, MA, ht, len )  MERows_absmax( Y, MA[0], ht, len )
#define ME_Cols_absmax( Y, MA, ht, len )  MECols_absmax( Y, MA[0], ht, len )
#define ME_Dia_absmax(  MA, len )         MEDia_absmax(  MA[0], len )
#define ME_Rows_absmin( Y, MA, ht, len )  MERows_absmin( Y, MA[0], ht, len )
#define ME_Cols_absmin( Y, MA, ht, len )  MECols_absmin( Y, MA[0], ht, len )
#define ME_Dia_absmin(  MA, len )         MEDia_absmin(  MA[0], len )

#define ME_Rows_sum( Y, MA, ht, len )     MERows_sum( Y, MA[0], ht, len )
#define ME_Cols_sum( Y, MA, ht, len )     MECols_sum( Y, MA[0], ht, len )
#define ME_Dia_sum(  MA, len )            MEDia_sum(  MA[0], len )
#define ME_Rows_prod( Y, MA, ht, len )    MERows_prod( Y, MA[0], ht, len )
#define ME_Cols_prod( Y, MA, ht, len )    MECols_prod( Y, MA[0], ht, len )
#define ME_Dia_prod(  MA, len )           MEDia_prod(  MA[0], len )

#define ME_Rows_runsum( MA, ht, len )     MERows_runsum( MA[0], ht, len )
#define ME_Cols_runsum( MA, ht, len )     MECols_runsum( MA[0], ht, len )
#define ME_Rows_runprod( MA, ht, len )    MERows_runprod( MA[0], ht, len )
#define ME_Cols_runprod( MA, ht, len )    MECols_runprod( MA[0], ht, len )

#define ME_Rows_rotate( MA, ht, len, pos) MERows_rotate( MA[0], ht, len, pos )
#define ME_Cols_rotate( MA, ht, len, pos) MECols_rotate( MA[0], ht, len, pos )
#define ME_Rows_reflect( MA, ht, len )    MERows_reflect( MA[0], ht, len )
#define ME_Cols_reflect( MA, ht, len )    MECols_reflect( MA[0], ht, len )

/********  Operations involving two rows or two colums of one matrix  *****/

#define ME_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MERows_exchange( MA[0], ht, len, row1, row2 )
#define ME_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MECols_exchange( MA[0], ht, len, col1, col2 )

#define ME_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MERows_add( MA[0], ht, len, destRow, srceRow )
#define ME_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MECols_add( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define ME_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MERows_sub( MA[0], ht, len, destRow, srceRow )
#define ME_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MECols_sub( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define ME_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MERows_Cadd( MA[0], ht, len, destRow, srceRow, C )
#define ME_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MECols_Cadd( MA[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define ME_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MERows_lincomb( MA[0], ht, len, destRow, destC, srceRow, srceC )
#define ME_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MECols_lincomb( MA[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*************************  Transposing a matrix **********************/

#define ME_transpose( MTr, MA, htTr, lenTr ) \
             MEtranspose( MTr[0], MA[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */


/************************ Matrix Arithmetics *************************/

#define ME_addM( MC, MA, MB, htA, lenA ) \
                 VE_addV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define ME_addMT( MC, MA, MB, htA, lenA ) \
                 MEaddMT( MC[0], MA[0], MB[0], htA, lenA )
#define ME_subM( MC, MA, MB, htA, lenA ) \
                 VE_subV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define ME_subMT( MC, MA, MB, htA, lenA ) \
                 MEsubMT( MC[0], MA[0], MB[0], htA, lenA )
#define ME_subrMT( MC, MA, MB, htA, lenA ) \
                 MEsubrMT( MC[0], MA[0], MB[0], htA, lenA )
#define ME_mulC( MB, MA, htA, lenA, C ) \
                 VE_mulC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define ME_divC( MB, MA, htA, lenA, C ) \
                 VE_divC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MEs_addM( MC, MA, MB, htA, lenA, C ) \
                 VEs_addV( MC[0], MA[0], MB[0], ((ui)htA)*lenA, C )
#define MEs_addMT( MC, MA, MB, htA, lenA, C ) \
                 MEsaddMT( MC[0], MA[0], MB[0], htA, lenA, C )
#define MEs_subM( MC, MA, MB, htA, lenA, C ) \
                 VEs_subV( MC[0], MA[0], MB[0], ((ui)htA)*lenA, C )
#define MEs_subMT( MC, MA, MB, htA, lenA, C ) \
                 MEssubMT( MC[0], MA[0], MB[0], htA, lenA, C )
#define MEs_subrMT( MC, MA, MB, htA, lenA, C ) \
                 MEssubrMT( MC[0], MA[0], MB[0], htA, lenA, C )
#define ME_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VE_lincomb( MC[0], MA[0], MB[0], ((ui)htA)*lenA, CA, CB )

#define ME_mulV( Y, MA, X, htA, lenA ) \
                    MEmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define ME_TmulV( Y, MA, X, htA, lenA ) \
                    METmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VE_mulM( Y, X, MA, htA, lenA ) \
                    VEmulM( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VE_ (not ME_)    */
#define VE_mulMT( Y, X, MA, htA, lenA ) \
                    VEmulMT( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define ME_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MEmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define ME_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MEmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define ME_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    METmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define ME_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    METmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MEdia_mulM(  MC, MADia, MB, htB, lenB )  MEdiamulM(  MC[0], MADia, MB[0], htB, lenB )
#define MEdia_mulMT( MC, MADia, MB, htB, lenB )  MEdiamulMT( MC[0], MADia, MB[0], htB, lenB )
#define ME_mulMdia(  MC, MA, MBDia, htA, lenA )  MEmulMdia(  MC[0], MA[0], MBDia, htA, lenA )
#define ME_TmulMdia( MC, MA, MBDia, htA, lenA )  METmulMdia( MC[0], MA[0], MBDia, htA, lenA )


/*************************  Linear Algebra    *****************************/

   /*  The standard treatment of linear systems is based
       on LUD (matrix decomposition into Upper-triangular
       and Lower-triangular components). The result of the
       decomposition step is used for further operations.  */

#define ME_LUdecompose( MLU, Ind, MA, len ) \
                    MELUdecompose( MLU[0], Ind, MA[0], len )
            /* returns "permut" = ñ1 which is needed for ME_LUdet.
               for singularities not cured by editing, permut is 0  */
int     __vf ME_LUDresult( void );
    /* returns 0, if ME_LUdecompose was successful;
       returns 1, if MA was (nearly) singular in ME_LUdecompose.   */
void       __vf ME_LUDsetEdit( extended Thresh );
extended   __vf ME_LUDgetEdit( void );
     /*  Editing threshold valid for ME_LUdecompose;
         may be used to cure singularities           */

#define ME_LUsolve( X, MLU, B, Ind, len ) \
                    MELUsolve( X, MLU[0], B, Ind, len )
#define ME_LUinv( MInv, MLU, Ind, len ) \
                    MELUinv( MInv[0], MLU[0], Ind, len )
#define ME_LUdet( MLU, len, permut )  MELUdet( MLU[0], len, permut )
#define ME_LUimprove( X, B, MA, MLU, Ind, len ) \
                      MELUimprove( X, B, MA[0], MLU[0], Ind, len )

    /****  Special treatment of over- or under-determined
           linear systems, i.e. of matrices with len != ht
           and of singular matrices:
           SVD (Singular Value Decomposition)       ****/

#define ME_SVdecompose( MU, MV, W, MA, htA, lenA ) \
                    MESVdecompose( MU[0], MV[0], W, MA[0], htA, lenA )
            /*  sizB = htA,  sizX = sizW = htV = lenV = lenA  */
#define ME_SVsolve( X, MU, MV, W, B, htU, lenU ) \
                    MESVsolve( X, MU[0], MV[0], W, B, htU, lenU )
            /*  lenU = lenA,  htU = max( lenA, htA ) as fed into
                MD_SVdecompose   */
void    __vf ME_SVDsetEdit( extended Thresh );
extended   __vf ME_SVDgetEdit( void );
    /* Override of the standard values for editing threshholds
       in ME_SVsolve. Calling ME_setEdit with Thresh=0.0 means
       that you do the necessary editing of W yourself
       before calling MD_SVsolve                           */

 /*****  "Easy-to-use" versions of the matrix functions
          using LUD or SVD.
          They allocate their own working space and rely
          on your setting of the editing threshold. In
          case of memory stress, you might better use the
          two-step methods declared above.            ***/
#define ME_solve( X, MA, B, len ) \
                    MEsolve( X, MA[0], B, len )
#define ME_inv( MInv, MA, len ) \
                    MEinv( MInv[0], MA[0], len )
#define ME_det(  MA, len ) \
                    MEdet( MA[0], len )
#define ME_solveBySVD( X, MA, B, ht, len ) \
                    MEsolveBySVD( X, MA[0], B, ht, len )
         /*  sizX = len,  sizB = ht  */
#define ME_safeSolve( X, MA, B, len ) \
                    MEsafeSolve( X, MA[0], B, len )
        /* ME_safeSolve tries first LUD. If that fails, SVD is done.
           X[i] will be 0.0 instead of INF for those i corresponding
           to singularities. If even SVD fails, all X[i] are set to 0.0.
           return value 0: success via LUD; 1: success via SVD; -1: failure */

      /*********  Eigenvalues and Eigenvectors  ********/
      /*** only the most frequent case of symmetric real matrices
           is covered here! *********/

#define MEsym_eigenvalues( EigV, EigM, MA, len, CalcEigenVec ) \
                    MEs_eigenvalues( EigV, EigM[0], MA[0], len, CalcEigenVec )
                        /*  Eigenvalues are returned in EigV,
                            Eigenvectors are returned as the columns of EigM.
                            CalcEigenVec = 0 means that only eigenvalues
                            are needed; CalcEigenVec != 0 means that
                            also eigenvectors are calculated.
                            Even if eigenvectors are not desired, EigM is
                            needed by the function as working-space. The, on
                            output, it will contain just rubbish.
                            MA may be overwritten by EigM. */


/***************** Two-Dimensional Fourier-Transform Methods ************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
eComplex  __vf   VE_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf   VE_setRspEdit( eComplex Trunc );
           /* these are the same functions as used
              in the one-dimensional case */

#define MEl_FFT( MY, MX, ht, len, dir )     MElFFT( MY[0], MX[0], ht, len, dir )
#define MEs_FFT( MY, MX, ht, len, dir )     MEsFFT( MY[0], MX[0], ht, len, dir )
#define MEl_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MElconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MEl_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MEldeconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MEl_filter( MY, MX, MFlt, ht, len ) MElfilter( MY[0], MX[0], MFlt[0], ht, len )
#define MEl_autocorr( MACorr, MX, ht, len ) MElautocorr( MACorr[0], MX[0], ht, len )
#define MEl_xcorr( MXCorr, MX, MY, ht, len) MElxcorr( MXCorr[0], MX[0], MY[0], ht, len )
#define MEl_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MElspectrum( MSpec[0], htSpec, lenSpec, MX[0], htX, lenX, MWin[0] )
                /* htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */

#define MEs_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MEsconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MEs_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MEsdeconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MEs_filter( MY, MX, MFlt, ht, len ) MEsfilter( MY[0], MX[0], MFlt[0], ht, len )
#define MEs_autocorr( MACorr, MX, ht, len ) MEsautocorr( MACorr[0], MX[0], ht, len )
#define MEs_xcorr( MXCorr, MX, MY, ht, len) MEsxcorr( MXCorr[0], MX[0], MY[0], ht, len )
#define MEs_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MEsspectrum( MSpec[0], htSpec, lenSpec, MX[0], htX, lenX, MWin[0] )
                /* htSpec, lenSpec must be 2**n,
                   MSpec has [htSpec+1][lenSpec+1] elements (!)
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec     */

#if defined( __LARGE__ ) || defined( __COMPACT__ ) || defined ( __HUGE__ )
   #define ME_FFT         MEl_FFT
   #define ME_convolve    MEl_convolve
   #define ME_deconvolve  MEl_deconvolve
   #define ME_filter      MEl_filter
   #define ME_autocorr    MEl_autocorr
   #define ME_xcorr       MEl_xcorr
   #define ME_spectrum    MEl_spectrum
#else
   #define ME_FFT         MEs_FFT
   #define ME_convolve    MEs_convolve
   #define ME_deconvolve  MEs_deconvolve
   #define ME_filter      MEs_filter
   #define ME_autocorr    MEs_autocorr
   #define ME_xcorr       MEs_xcorr
   #define ME_spectrum    MEs_spectrum
#endif


/************************** Data Fitting *********************************

  Notice that some of these functions have the prefix VE_, others ME_.
  This depends on the form in which the data to be fitted are recorded:
  vectors are fitted by the VE_ functions, matrices by the ME_ functions.
  All of these functions employ matrix methods internally. The weighted
  versions return covariances in a matrix "Covar". So they are all
  contained in MatrixLib and declared here.
*/

void __vf VE_polyfit( eVector A, unsigned deg, eVector X, eVector Y, ui sizex );
#define   VE_polyfitwW( A, Covar, deg, X, Y, InvVar, sizex ) \
          VEpolyfitwW( A, Covar[0], deg, X, Y, InvVar, sizex )
       /* the size of A is deg+1 and Covar has [deg+1][deg+1] elements! */

void __vf VE_linfit( eVector A, iVector AStatus, unsigned npars,
                     eVector X, eVector Y, ui sizex,
                     void (*funcs)(eVector BasFuncs, extended x, unsigned nfuncs) );
#define   VE_linfitwW( A, Covar, AStatus, npars, X, Y, InvVar, sizex, funcs ) \
          VElinfitwW( A, Covar[0], AStatus, npars, X, Y, InvVar, sizex, funcs )
#define   ME_linfit( A, AStatus, npars, X, Y, MZ, htZ, lenZ, funcs ) \
          MElinfit( A, AStatus, npars, X, Y, MZ[0], htZ, lenZ, funcs )
#define   ME_linfitwW( A, Covar, AStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, funcs ) \
          MElinfitwW( A, Covar[0], AStatus, npars, X, Y, MZ[0], MInvVar[0], htZ, lenZ, funcs )

void  __vf VE_setLinfitNeglect( extended Thresh );
                   /* neglect A[i]=0, if significance smaller than Thresh */
extended __vf VE_getLinfitNeglect( void );

extended __vf VE_nonlinfit( eVector A, iVector AStatus, unsigned npars,
                    eVector X, eVector Y, ui sizex,
                    void (*modelfunc)(eVector YModel, eVector XModel, ui size),
                    void (*derivatives)(eVector dYdAi,eVector X, ui size, unsigned i) );
            /* returns figure-of-merit of best A. If you don't know the partial
               derivatives with respect to A, call with derivatives=NULL */
#define   VE_nonlinfitwW( A, Covar, AStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv ) \
          VEnonlinfitwW( A, Covar[0], AStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv )
#define   ME_nonlinfit( A, AStatus, npars, X, Y, MZ, htZ, lenZ, modelfunc, deriv ) \
          MEnonlinfit( A, AStatus, npars, X, Y, MZ[0], htZ, lenZ, modelfunc, deriv )
#define   ME_nonlinfitwW( A, Covar, AStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, modelfunc, deriv ) \
          MEnonlinfitwW( A, Covar[0], AStatus, npars, X, Y, MZ[0], MInvVar[0], htZ, lenZ, modelfunc, deriv )

        /* If you know some partial derivatives, you may call these functions
           for those parameters for which you do not know them:           */
void     __vf VE_nonlinfit_autoDeriv( eVector dYdAi, eVector X, ui size, unsigned ipar );
void     __vf VE_nonlinfitwW_autoDeriv( eVector dYdAi, eVector X, ui size, unsigned ipar );
void     __vf ME_nonlinfitwW_autoDeriv( eMatrix dZdAi, unsigned htZ, unsigned lenZ, eVector X, eVector Y, unsigned ipar );
void     __vf ME_nonlinfit_autoDeriv( eMatrix dZdAi, unsigned htZ, unsigned lenZ, eVector X, eVector Y, unsigned ipar );
       /* The following functions allow to monitor the progress of
          a nonlinear fitting procedure or to manually stop it:     */
extended __vf VE_nonlinfit_getChi2( void );
extended __vf VE_nonlinfitwW_getChi2( void );
extended __vf ME_nonlinfit_getChi2( void );
extended __vf ME_nonlinfitwW_getChi2( void );
void     __vf VE_nonlinfit_getBestValues( eVector ABest );
void     __vf VE_nonlinfitwW_getBestValues( eVector ABest );
void     __vf ME_nonlinfit_getBestValues( eVector ABest );
void     __vf ME_nonlinfitwW_getBestValues( eVector ABest );
unsigned __vf VE_nonlinfit_getTestRun( void );
unsigned __vf VE_nonlinfitwW_getTestRun( void );
unsigned __vf ME_nonlinfit_getTestRun( void );
unsigned __vf ME_nonlinfitwW_getTestRun( void );
unsigned __vf VE_nonlinfit_getTestPar( void );
unsigned __vf VE_nonlinfitwW_getTestPar( void );
unsigned __vf ME_nonlinfit_getTestPar( void );
unsigned __vf ME_nonlinfitwW_getTestPar( void );
int      __vf VE_nonlinfit_getTestDir( void );
int      __vf VE_nonlinfitwW_getTestDir( void );
int      __vf ME_nonlinfit_getTestDir( void );
int      __vf ME_nonlinfitwW_getTestDir( void );
void     __vf VE_nonlinfit_stop( void );
void     __vf VE_nonlinfitwW_stop( void );
void     __vf ME_nonlinfit_stop( void );
void     __vf ME_nonlinfitwW_stop( void );

#ifdef __BORLANDC__
    #pragma option -a-  /* avoid insertion of dummy bytes */
#else   /* MS Visual C++ */
    #pragma pack(push,1)
#endif    /*  Borland or Microsoft */
typedef struct VE_NONLINFITOPTIONS
{
      int        FigureOfMerit;  /*  0:least squares, 1:robust */
             /* Convergence conditions: if the changes achieved
                in successive iterations are lower than any of the
                following values, this signals convergence. Set
                criteria to 0.0, if not applicable              */
      extended   AbsTolChi,  /* absolute change of chi */
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
      extended   LambdaStart,
                 LambdaMin, LambdaMax,
                 LambdaDiv, LambdaMul;    /* LevMar parameter lambda */
      unsigned   DownhillIterations; /* max.number of successful iterations in Downhill */
      extended   DownhillReflection,  /* re-shaping of the simplex */
                 DownhillContraction,
                 DownhillExpansion;
      unsigned   TotalStarts;  /* max. number of LevMar/Downhill pairs */
      eVector    UpperLimits;  /* impose upper limits on parameters */
      eVector    LowerLimits;  /* impose lower limits on parameters */
      void       (*Restrictions)(void);  /* user-defined editing of parameters */
}  VE_NONLINFITOPTIONS;

void __vf VE_setNonlinfitOptions( VE_NONLINFITOPTIONS *Options );
void __vf VE_getNonlinfitOptions( VE_NONLINFITOPTIONS *Options );

typedef struct VE_EXPERIMENT
{
    eVector    X, Y, InvVar;
    ui         size;
    extended   WeightOfExperiment;
     /* InvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} VE_EXPERIMENT;

typedef struct ME_EXPERIMENT
{
    eVector      X, Y;
    eMatrix      MZ, MInvVar;  /* here no compatibility with static matrices! */
    unsigned     htZ, lenZ;
    extended     WeightOfExperiment;
     /* MInvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} ME_EXPERIMENT;
#ifdef __BORLANDC__
    #pragma option -a.   /* restore default data packing  */
#else   /* MS Visual C++ */
    #pragma pack(pop)
#endif


void __vf VE_multiLinfit( eVector A, iVector AStatus, unsigned ma,
                VE_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(eVector BasFuncs, extended x,
                              unsigned nfuncs, unsigned iexperiment) );
#define   VE_multiLinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, funcs ) \
          VEmultiLinfitwW( A, Covar[0], AStatus, npars, ListOfEx, nexp, funcs )
void __vf ME_multiLinfit( eVector A, iVector AStatus, unsigned ma,
                ME_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(eVector BasFuncs, extended x, extended y,
                              unsigned nfuncs, unsigned iexperiment) );
#define   ME_multiLinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, funcs ) \
          MEmultiLinfitwW( A, Covar[0], AStatus, npars, ListOfEx, nexp, funcs )
extended __vf VE_multiNonlinfit( eVector A, iVector AStatus, unsigned npars,
                VE_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(eVector YModel, eVector XModel,
                                  ui size, unsigned iexperiment),
                void (*derivatives)(eVector dYdAi,eVector X, ui size,
                                   unsigned ipar, unsigned iexperiment) );
            /* returns figure-of-merit of best A. If you don't know the
               partial derivatives, set derivatives=NULL */
#define   VE_multiNonlinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, modfunc, deriv ) \
          VEmultiNonlinfitwW( A, Covar[0], AStatus, npars, ListOfEx, nexp, modfunc, deriv )
extended __vf ME_multiNonlinfit( eVector A, iVector AStatus, unsigned npars,
                ME_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(eMatrix MZModel, unsigned htZ, unsigned lenZ,
                                  eVector X, eVector Y, unsigned iexperiment),
                void (*derivatives)(eMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    eVector X, eVector Y, unsigned ipar,
                                    unsigned iexperiment) );
#define   ME_multiNonlinfitwW( A, Covar, AStatus, npars, ListOfEx, nexp, modfunc, deriv ) \
          MEmultiNonlinfitwW( A, Covar[0], AStatus, npars, ListOfEx, nexp, modfunc, deriv )

void  __vf VE_multiNonlinfit_autoDeriv( eVector dYdAi, eVector X, ui size,
                                        unsigned ipar, unsigned iexperiment );
void  __vf VE_multiNonlinfitwW_autoDeriv( eVector dYdAi, eVector X, ui size,
                                        unsigned ipar, unsigned iexperiment );
void  __vf ME_multiNonlinfit_autoDeriv( eMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    eVector X, eVector Y,
                                    unsigned ipar, unsigned iexperiment );
void  __vf ME_multiNonlinfitwW_autoDeriv( eMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    eVector X, eVector Y,
                                    unsigned ipar, unsigned iexperiment );
extended __vf VE_multiNonlinfit_getChi2( void );
extended __vf VE_multiNonlinfitwW_getChi2( void );
extended __vf ME_multiNonlinfit_getChi2( void );
extended __vf ME_multiNonlinfitwW_getChi2( void );
void     __vf VE_multiNonlinfit_getBestValues( eVector ABest );
void     __vf VE_multiNonlinfitwW_getBestValues( eVector ABest );
void     __vf ME_multiNonlinfit_getBestValues( eVector ABest );
void     __vf ME_multiNonlinfitwW_getBestValues( eVector ABest );
unsigned __vf VE_multiNonlinfit_getTestRun( void );
unsigned __vf VE_multiNonlinfitwW_getTestRun( void );
unsigned __vf ME_multiNonlinfit_getTestRun( void );
unsigned __vf ME_multiNonlinfitwW_getTestRun( void );
unsigned __vf VE_multiNonlinfit_getTestPar( void );
unsigned __vf VE_multiNonlinfitwW_getTestPar( void );
unsigned __vf ME_multiNonlinfit_getTestPar( void );
unsigned __vf ME_multiNonlinfitwW_getTestPar( void );
int      __vf VE_multiNonlinfit_getTestDir( void );
int      __vf VE_multiNonlinfitwW_getTestDir( void );
int      __vf ME_multiNonlinfit_getTestDir( void );
int      __vf ME_multiNonlinfitwW_getTestDir( void );
void     __vf VE_multiNonlinfit_stop( void );
void     __vf VE_multiNonlinfitwW_stop( void );
void     __vf ME_multiNonlinfit_stop( void );
void     __vf ME_multiNonlinfitwW_stop( void );

/**************************  Input and Output  **************************/

#define ME_fprint( stream, MA, ht, len, linewidth ) \
                    MEfprint( stream, MA[0], ht, len, linewidth )
#define ME_print( MA, ht, len )  MEfprint( stdout, MA[0], ht, len, 80 )
#define ME_cprint( MA, ht, len ) MEcprint( MA[0], ht, len )
  /*  ME_print, ME_cprint usable only for DOS, EasyWin, and Win32 console applications! */

#define ME_write( str, MA, ht, len )   MEwrite( str, MA[0], ht, len )
#define ME_read( MA, ht, len, str )    MEread( MA[0], ht, len, str )
#define ME_setWriteFormat              VE_setWriteFormat
#define ME_setWriteSeparate            VE_setNWriteSeparate
                                   /* write and read in ascii format */
#define ME_store( str, MA, ht, len ) \
                           VE_store( str, MA[0], ((ui) (len))*(ht) );
#define ME_recall( MA, ht, len, str) \
                           VE_recall( MA[0], ((ui) (len))*(ht), str);
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

extended _VFAR * MEPelement( ePMatrix X, unsigned ht, unsigned len,
                             unsigned m, unsigned n );
                  /* pointer is normalized in memory model HUGE */
#define MEelement( MA, ht, len, m, n ) (*MEPelement( MA, ht, len, m, n ))

#define MEequ0( MA, ht, len )            VE_equ0( MA, ((ui)ht)*len )
void   __vf  MEequ1( ePMatrix MA, unsigned len );  /* identity matrix */
void   __vf  MEequm1( ePMatrix MA, unsigned len );  /* neg. identity matrix */
void   __vf  MEouterprod( ePMatrix MA, eVector X,  eVector Y,
                          unsigned ht, unsigned len );

void   __vf  MERow_equ0( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow );
void   __vf  MECol_equ0( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol );
void   __vf  MEDia_equ0( ePMatrix MA, unsigned len );

void   __vf  MERow_equC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, extended C );
void   __vf  MECol_equC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, extended C );
void   __vf  MEDia_equC( ePMatrix MA, unsigned len, extended C );

void   __vf  MERow_equV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eVector X );
void   __vf  MECol_equV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eVector X );
void   __vf  MEDia_equV( ePMatrix MA, unsigned len, eVector X );

void   __vf  METrd_equM( ePMatrix MA, ePMatrix MTrd, unsigned len );
void   __vf  METrd_extract( ePMatrix MTrd, ePMatrix MA, unsigned len );

#define MEequM( MB, MA, ht, len )  VE_equV( MB, MA, (ui)(ht)*(len) )
#define MEneg( MB, MA, ht, len )   VE_neg( MB, MA, (ui)(ht)*(len) )
void   __vf  MEUequL( ePMatrix MA, unsigned len );
void   __vf  MELequU( ePMatrix MA, unsigned len );

void   __vf  MEHanning( ePMatrix MA, unsigned ht, unsigned len );
void   __vf  MEParzen(  ePMatrix MA, unsigned ht, unsigned len );
void   __vf  MEWelch(   ePMatrix MA, unsigned ht, unsigned len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MEsubmatrix( ePMatrix MSub,
                          unsigned subHt,  unsigned subLen,
                          ePMatrix MSrce,
                          unsigned srceHt,  unsigned srceLen,
                          unsigned firstRowInCol,  unsigned sampInCol,
                          unsigned firstColInRow,  unsigned sampInRow );

void  __vf  MEsubmatrix_equM( ePMatrix MDest,
                               unsigned destHt,     unsigned destLen,
                               unsigned firstRowInCol,  unsigned sampInCol,
                               unsigned firstColInRow,  unsigned sampInRow,
                               ePMatrix MSrce,
                               unsigned srceHt,     unsigned srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MERow_extract( eVector Y, ePMatrix MA, unsigned ht, unsigned len,
                           unsigned iRow );
void __vf MECol_extract( eVector Y, ePMatrix MA, unsigned ht, unsigned len,
                           unsigned iCol );
void __vf MEDia_extract( eVector Y, ePMatrix MA, unsigned len );

/**********  Deleting or inserting a row or a column *****************/

void __vf MERow_delete( ePMatrix MB, ePMatrix MA,
                        unsigned htA, unsigned lenA, unsigned iRow );
void __vf MECol_delete( ePMatrix MB, ePMatrix MA,
                        unsigned htA, unsigned lenA, unsigned iCol );
void __vf MERow_insert( ePMatrix MB, ePMatrix MA, unsigned htB,
                        unsigned lenB, unsigned iRow, eVector X );
void __vf MECol_insert( ePMatrix MB, ePMatrix MA, unsigned htB,
                        unsigned lenB, unsigned iCol, eVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MERow_addC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, extended C );
void   __vf  MECol_addC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, extended C );
void   __vf  MEDia_addC( ePMatrix MA, unsigned len, extended C );

void   __vf  MERow_subC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, extended C );
void   __vf  MECol_subC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, extended C );
void   __vf  MEDia_subC( ePMatrix MA, unsigned len, extended C );

void   __vf  MERow_addV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eVector X );
void   __vf  MECol_addV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eVector X );
void   __vf  MEDia_addV( ePMatrix MA, unsigned len, eVector X );

void   __vf  MERow_subV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eVector X );
void   __vf  MECol_subV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eVector X );
void   __vf  MEDia_subV( ePMatrix MA, unsigned len, eVector X );

void   __vf  MERow_subrC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, extended C );
void   __vf  MECol_subrC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, extended C );
void   __vf  MEDia_subrC( ePMatrix MA, unsigned len, extended C );

void   __vf  MERow_subrV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eVector X );
void   __vf  MECol_subrV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eVector X );
void   __vf  MEDia_subrV( ePMatrix MA, unsigned len, eVector X );

void   __vf  MERow_mulC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, extended C );
void   __vf  MECol_mulC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, extended C );
void   __vf  MEDia_mulC( ePMatrix MA, unsigned len, extended C );

void   __vf  MERow_mulV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eVector X );
void   __vf  MECol_mulV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eVector X );
void   __vf  MEDia_mulV( ePMatrix MA, unsigned len, eVector X );

void   __vf  MERow_divC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, extended C );
void   __vf  MECol_divC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, extended C );
void   __vf  MEDia_divC( ePMatrix MA, unsigned len, extended C );

void   __vf  MERow_divV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eVector X );
void   __vf  MECol_divV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eVector X );
void   __vf  MEDia_divV( ePMatrix MA, unsigned len, eVector X );

void   __vf  MERow_divrC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, extended C );
void   __vf  MECol_divrC( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, extended C );
void   __vf  MEDia_divrC( ePMatrix MA, unsigned len, extended C );

void   __vf  MERow_divrV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eVector X );
void   __vf  MECol_divrV( ePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eVector X );
void   __vf  MEDia_divrV( ePMatrix MA, unsigned len, eVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void  __vf  MERows_max( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MECols_max( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
extended __vf  MEDia_max(  ePMatrix MA, unsigned len );
void  __vf  MERows_min( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MECols_min( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
extended __vf  MEDia_min(  ePMatrix MA, unsigned len );

void  __vf  MERows_absmax( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MECols_absmax( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
extended __vf  MEDia_absmax(  ePMatrix MA, unsigned len );
void  __vf  MERows_absmin( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MECols_absmin( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
extended __vf  MEDia_absmin(  ePMatrix MA, unsigned len );

void  __vf  MERows_sum( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MECols_sum( eVector Y, ePMatrix MA, unsigned ht, unsigned len );
extended __vf  MEDia_sum(  ePMatrix MA, unsigned len );
void  __vf  MERows_prod(eVector Y, ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MECols_prod(eVector Y, ePMatrix MA, unsigned ht, unsigned len );
extended __vf  MEDia_prod( ePMatrix MA, unsigned len );

void  __vf  MERows_runsum( ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MECols_runsum( ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MERows_runprod( ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MECols_runprod( ePMatrix MA, unsigned ht, unsigned len );

void  __vf  MERows_rotate( ePMatrix MA, unsigned ht, unsigned len, int pos );
void  __vf  MECols_rotate( ePMatrix MA, unsigned ht, unsigned len, int pos );
void  __vf  MERows_reflect( ePMatrix MA, unsigned ht, unsigned len );
void  __vf  MECols_reflect( ePMatrix MA, unsigned ht, unsigned len );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MERows_exchange( ePMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );
void   __vf  MECols_exchange( ePMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );

void   __vf  MERows_add( ePMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MECols_add( ePMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MERows_sub( ePMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MECols_sub( ePMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MERows_Cadd( ePMatrix MA, unsigned ht, unsigned len,
                           unsigned destRow, unsigned sourceRow, extended C );
void   __vf  MECols_Cadd( ePMatrix MA, unsigned ht, unsigned len,
                           unsigned destCol, unsigned sourceCol, extended C );

void   __vf  MERows_lincomb( ePMatrix MA, unsigned ht, unsigned len,
                              unsigned destRow,  extended  destC,
                              unsigned srceRow,  extended  srceC );
void   __vf  MECols_lincomb( ePMatrix MA, unsigned ht, unsigned len,
                              unsigned destCol,  extended  destC,
                              unsigned srceCol,  extended  srceC );


/*************************  Transposing a matrix **********************/

void  __vf  MEtranspose( ePMatrix MTr, ePMatrix MA,
                          unsigned htTr, unsigned lenTr );


/************************ Matrix Arithmetics *************************/

#define MEaddM( MC, MA, MB, htA, lenA ) \
                 VE_addV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MEaddMT( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA );
#define MEsubM( MC, MA, MB, htA, lenA ) \
                 VE_subV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MEsubMT( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA );
void __vf  MEsubrMT( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA );
#define MEmulC( MB, MA, htA, lenA, C ) \
                 VE_mulC( MB, MA, ((ui)htA)*lenA, C )
#define MEdivC( MB, MA, htA, lenA, C ) \
                 VE_divC( MB, MA, ((ui)htA)*lenA, C )
#define MEsaddM( MC, MA, MB, htA, lenA, C ) \
                 VEs_addV( MC, MA, MB, ((ui)htA)*lenA, C )
void __vf  MEsaddMT( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA, extended C );
#define MEssubM( MC, MA, MB, htA, lenA, C ) \
                 VEs_subV( MC, MA, MB, ((ui)htA)*lenA, C )
void __vf  MEssubMT( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA, extended C );
void __vf  MEssubrMT( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA, extended C );
#define MElincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VE_lincomb( MC, MA, MB, ((ui)htA)*lenA, CA, CB )
void  __vf  MEmulV( eVector Y, ePMatrix MA, eVector X,
                    unsigned htA, unsigned lenA );
void  __vf  METmulV( eVector Y, ePMatrix MA, eVector X,
                     unsigned htA, unsigned lenA );
void  __vf  VEmulM( eVector Y, eVector X, ePMatrix MA,
                    unsigned htA, unsigned lenA );
void  __vf  VEmulMT( eVector Y, eVector X, ePMatrix MA,
                     unsigned htA, unsigned lenA );
void  __vf  MEmulM( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MEmulMT( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  METmulM( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  METmulMT( ePMatrix MC, ePMatrix MA, ePMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MEdiamulM( ePMatrix MC, ePMatrix MADia, ePMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MEdiamulMT( ePMatrix MC, ePMatrix MADia, ePMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MEmulMdia( ePMatrix MC, ePMatrix MA, ePMatrix MBDia,
                    unsigned htA, unsigned lenA );
void  __vf  METmulMdia( ePMatrix MC, ePMatrix MA, ePMatrix MBDia,
                    unsigned htA, unsigned lenA );


/*************************  Linear Algebra    *****************************/

int    __vf  MELUdecompose( ePMatrix MLU,  uVector Ind, ePMatrix MA,
                            unsigned len );

void     __vf  MELUsolve( eVector X, ePMatrix MLU, eVector B, uVector Ind,
                          unsigned len );
void     __vf  MELUinv( ePMatrix MInv, ePMatrix MLU, uVector Ind,
                        unsigned len );
extended __vf  MELUdet( ePMatrix MLU, unsigned len, int permut );
void     __vf  MELUimprove( eVector X, eVector B, ePMatrix MA, ePMatrix MLU,
                            uVector Ind, unsigned len );

int   __vf  MESVdecompose( ePMatrix MU, ePMatrix MV, eVector W, ePMatrix MA,
                           unsigned htA, unsigned lenA );
void  __vf  MESVsolve( eVector X, ePMatrix MU, ePMatrix MV, eVector W,
                       eVector B, unsigned htU, unsigned lenU );

          /*  functions using LUD or SVD     */
int    __vf  MEsolve( eVector X, ePMatrix MA, eVector B, unsigned len );
                  /* ret.value != 0 signals error */
int    __vf  MEinv( ePMatrix MInv, ePMatrix MA, unsigned len );
                 /* ret.value != 0 signals error */
extended  __vf  MEdet( ePMatrix MA, unsigned len );

int    __vf  MEsolveBySVD( eVector X, ePMatrix MA, eVector B,
                           unsigned ht, unsigned len );
                 /*  ret.value != 0 signals failure */
int    __vf  MEsafeSolve( eVector X, ePMatrix MA, eVector B, unsigned len );
              /* ret.value 0: success via LUD; 1: success via SVD; -1: error */

       /*********  Eigenvalues and Eigenvectors  ********/

void __vf MEs_eigenvalues( eVector EigV, ePMatrix EigM, ePMatrix MA, unsigned len,
                        int CalcEigenVec );

/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf   MElFFT( ePMatrix MY, ePMatrix MX,
                     unsigned ht, unsigned len, int dir );
void  __vf   MElconvolve( ePMatrix MY, ePMatrix MFlt, ePMatrix MX,
                          ePMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MEldeconvolve( ePMatrix MY, ePMatrix MFlt, ePMatrix MX,
                            ePMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MElfilter( ePMatrix MY, ePMatrix MX, ePMatrix MFlt,
                        unsigned ht, unsigned len );
void  __vf   MElautocorr( ePMatrix MACorr, ePMatrix MX,
                          unsigned ht, unsigned len );
void  __vf   MElxcorr( ePMatrix MXCorr, ePMatrix MX, ePMatrix MY,
                       unsigned ht, unsigned len );
void  __vf   MElspectrum( ePMatrix MSpec, unsigned htSpec, unsigned lenSpec,
                          ePMatrix MX, unsigned htX, unsigned lenX,
                          ePMatrix MWin );

void  __vf   MEsFFT( ePMatrix MY, ePMatrix MX,
                     unsigned ht, unsigned len, int dir );
void  __vf   MEsconvolve( ePMatrix MY, ePMatrix MFlt, ePMatrix MX,
                          ePMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MEsdeconvolve( ePMatrix MY, ePMatrix MFlt, ePMatrix MX,
                            ePMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MEsfilter( ePMatrix MY, ePMatrix MX, ePMatrix MFlt,
                        unsigned ht, unsigned len );
void  __vf   MEsautocorr( ePMatrix MACorr, ePMatrix MX,
                          unsigned ht, unsigned len );
void  __vf   MEsxcorr( ePMatrix MXCorr, ePMatrix MX, ePMatrix MY,
                       unsigned ht, unsigned len );
void  __vf   MEsspectrum( ePMatrix MSpec, unsigned htSpec, unsigned lenSpec,
                          ePMatrix MX, unsigned htX, unsigned lenX,
                          ePMatrix MWin );

      /***************  Data Fitting    ******************/

void __vf VEpolyfitwW( eVector A, ePMatrix Covar, unsigned deg,
                        eVector X, eVector Y, eVector InvVar, ui sizex );
void __vf VElinfitwW( eVector A, ePMatrix Covar, iVector AStatus, unsigned npars,
                    eVector X, eVector Y, eVector InvVar, ui sizex,
                    void (*funcs)(eVector BasFuncs, extended x, unsigned nfuncs) );
extended __vf VEnonlinfitwW( eVector A, ePMatrix Covar, iVector AStatus, unsigned npars,
                    eVector X, eVector Y, eVector InvVar, ui sizex,
                    void (*modelfunc)(eVector YModel, eVector X, ui size),
                    void (*derivatives)(eVector dYdAi, eVector X, ui size, unsigned i) );
void __vf MElinfit( eVector A, iVector AStatus, unsigned npars,
                    eVector X, eVector Y, ePMatrix MZ, unsigned htZ, unsigned lenZ,
                    void (*funcs)(eVector BasFuncs, extended x, extended y, unsigned nfuncs) );
extended __vf MEnonlinfit( eVector A, iVector AStatus, unsigned npars,
                    eVector X, eVector Y, ePMatrix MZ, unsigned htZ, unsigned lenZ,
                    void (*modelfunc)(eMatrix MZModel, unsigned htZ, unsigned lenZ, eVector X, eVector Y ),
                    void (*derivatives)(eMatrix dZdAi, unsigned htZ, unsigned lenZ, eVector X, eVector Y, unsigned i) );
void __vf MElinfitwW( eVector A, ePMatrix Covar, iVector AStatus, unsigned npars,
                      eVector X, eVector Y, ePMatrix MZ, ePMatrix MInvVar, unsigned htZ, unsigned lenZ,
                      void (*funcs)(eVector BasFuncs, extended x, extended y, unsigned nfuncs) );
extended __vf MEnonlinfitwW( eVector A, ePMatrix Covar, iVector AStatus, unsigned npars,
                    eVector X, eVector Y, ePMatrix MZ, ePMatrix MInvVar, unsigned htZ, unsigned lenZ,
                    void (*modelfunc)(eMatrix MZModel, unsigned htZ, unsigned lenZ, eVector X, eVector Y ),
                    void (*derivatives)(eMatrix dZdAi, unsigned htZ, unsigned lenZ, eVector X, eVector Y, unsigned i) );

void __vf VEmultiLinfitwW( eVector A, ePMatrix Covar, iVector AStatus, unsigned ma,
                VE_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(eVector BasFuncs, extended x,
                              unsigned nfuncs, unsigned nexperiment) );
void __vf MEmultiLinfitwW( eVector A, ePMatrix Covar,
                iVector AStatus, unsigned npars,
                ME_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(eVector BasFuncs, extended x, extended y,
                              unsigned nfuncs, unsigned nexperiment) );
extended __vf VEmultiNonlinfitwW( eVector A, ePMatrix Covar,
                iVector AStatus, unsigned npars,
                VE_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(eVector YModel, eVector X, ui size,
                                  unsigned iexperiment),
                void (*derivatives)(eVector dYdAi, eVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) );
extended __vf MEmultiNonlinfitwW( eVector A, ePMatrix Covar,
                iVector AStatus, unsigned npars,
                ME_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(eMatrix MZModel, unsigned htZ, unsigned lenZ,
                                  eVector X, eVector Y, unsigned iexperiment ),
                void (*derivatives)(eMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    eVector X, eVector Y,
                                    unsigned ipar, unsigned iexperiment) );

      /*************  Input and Output  ****************/

void __vf MEfprint( FILE _VFAR *stream, ePMatrix MA, unsigned ht,
                    unsigned len, unsigned linewidth );
void __vf MEcprint( ePMatrix MA, unsigned ht, unsigned len );
void  __vf    MEwrite( FILE _VFAR *stream, ePMatrix X, unsigned ht, unsigned len  );
void  __vf    MEread( ePMatrix X, unsigned ht, unsigned len, FILE _VFAR *stream );
#define MEstore( str, MA, ht, len ) \
                           VE_store( str, MA, ((ui) (len))*(ht) );
#define MErecall( MA, ht, len, str) \
                           VE_recall( MA, ((ui) (len))*(ht), str);

#ifdef __cplusplus
}
#endif


#else   /* MSVC, Powersoft: ME_ functions are identical to MD_ */
#define ME_matrix   MD_matrix
#define ME_matrix0  MD_matrix0
#define ME_Pelement MD_Pelement
#define ME_element  MD_element
#define ME_equ0     MD_equ0
#define ME_equ1     MD_equ1
#define ME_equm1    MD_equm1
#define ME_outerprod MD_outerprod
#define ME_Row_equC  MD_Row_equC
#define ME_Col_equC  MD_col_equC
#define ME_Dia_equC  MD_Dia_equC
#define ME_Row_equV  MD_Row_equV
#define ME_Col_equV  MD_col_equV
#define ME_Dia_equV  MD_Dia_equV
#define ME_equM      MD_equM
#define ME_neg       MD_neg
#define ME_UequL     MD_UequL
#define ME_LequU     MD_LequU
#define M_EtoF( MF, ME, ht, len ) V_EtoF( MF[0], ME[0], ((ui)ht)*len )
#define M_FtoE( ME, MF, ht, len ) V_FtoE( ME[0], MF[0], ((ui)ht)*len )
#define M_EtoD( MD, ME, ht, len ) V_EtoD( MD[0], ME[0], ((ui)ht)*len )
#define M_DtoE( ME, MD, ht, len ) V_DtoE( ME[0], MD[0], ((ui)ht)*len )
#define ME_Hanning   MD_Hanning
#define ME_Parzen    MD_Parzen
#define ME_Welch     MD_Welch
#define ME_submatrix MD_submatrix
#define ME_submatrix_equM MD_submatrix_equM
#define ME_Row_extract MD_Row_extract
#define ME_Col_extract MD_Col_extract
#define ME_Dia_extract MD_Dia_extract
#define ME_Trd_equM    MD_Trd_equM
#define ME_Trd_extract MD_Trd_extract
#define ME_Row_insert  MD_Row_insert
#define ME_Col_insert  MD_Col_insert
#define ME_Row_delete  MD_Row_delete
#define ME_Col_delete  MD_Col_delete
#define ME_Row_addC    MD_Row_addC
#define ME_Col_addC    MD_Col_addC
#define ME_Dia_addC    MD_Dia_addC
#define ME_Row_addV    MD_Row_addV
#define ME_Col_addV    MD_Col_addV
#define ME_Dia_addV    MD_Dia_addV
#define ME_Row_subC    MD_Row_subC
#define ME_Col_subC    MD_Col_subC
#define ME_Dia_subC    MD_Dia_subC
#define ME_Row_subV    MD_Row_subV
#define ME_Col_subV    MD_Col_subV
#define ME_Dia_subV    MD_Dia_subV
#define ME_Row_subrC   MD_Row_subrC
#define ME_Col_subrC   MD_Col_subrC
#define ME_Dia_subrC   MD_Dia_subrC
#define ME_Row_subrV   MD_Row_subrV
#define ME_Col_subrV   MD_Col_subrV
#define ME_Dia_subrV   MD_Dia_subrV
#define ME_Row_mulC    MD_Row_mulC
#define ME_Col_mulC    MD_Col_mulC
#define ME_Dia_mulC    MD_Dia_mulC
#define ME_Row_mulV    MD_Row_mulV
#define ME_Col_mulV    MD_Col_mulV
#define ME_Dia_divV    MD_Dia_divV
#define ME_Row_divC    MD_Row_divC
#define ME_Col_divC    MD_Col_divC
#define ME_Dia_divC    MD_Dia_divC
#define ME_Row_divV    MD_Row_divV
#define ME_Col_divV    MD_Col_divV
#define ME_Dia_divV    MD_Dia_divV
#define ME_Row_divrC   MD_Row_divrC
#define ME_Col_divrC   MD_Col_divrC
#define ME_Dia_divrC   MD_Dia_divrC
#define ME_Row_divrV   MD_Row_divrV
#define ME_Col_divrV   MD_Col_divrV
#define ME_Dia_divrV   MD_Dia_divrV
#define ME_Rows_max    MD_Cols_max
#define ME_Cols_max    MD_Rows_max
#define ME_Dia_max     MD_Dia_max
#define ME_Rows_min    MD_Cols_min
#define ME_Cols_min    MD_Rows_min
#define ME_Dia_min     MD_Dia_min
#define ME_Rows_absmax MD_Cols_absmax
#define ME_Cols_absmax MD_Rows_absmax
#define ME_Dia_absmax  MD_Dia_absmax
#define ME_Rows_absmin MD_Cols_absmin
#define ME_Cols_absmin MD_Rows_absmin
#define ME_Dia_absmin  MD_Dia_absmin
#define ME_Rows_sum    MD_Cols_sum
#define ME_Cols_sum    MD_Rows_sum
#define ME_Dia_sum     MD_Dia_sum
#define ME_Rows_prod   MD_Cols_prod
#define ME_Cols_prod   MD_Rows_prod
#define ME_Dia_prod    MD_Dia_prod
#define ME_Rows_runsum MD_Cols_runsum
#define ME_Cols_runsum MD_Rows_runsum
#define ME_Rows_runprod  MD_Cols_runprod
#define ME_Cols_runprod  MD_Rows_runprod
#define ME_Rows_rotate   MD_Cols_rotate
#define ME_Cols_rotate   MD_Rows_rotate
#define ME_Rows_reflect  MD_Cols_reflect
#define ME_Cols_reflect  MD_Rows_reflect
#define ME_Rows_exchange MD_Rows_exchange
#define ME_Cols_exchange MD_Cols_exchange
#define ME_Rows_add      MD_Cols_add
#define ME_Cols_add      MD_Rows_add
#define ME_Rows_sub      MD_Cols_sub
#define ME_Cols_sub      MD_Rows_sub
#define ME_Rows_Cadd     MD_Cols_Cadd
#define ME_Cols_Cadd     MD_Rows_Cadd
#define ME_Rows_lincomb  MD_Cols_lincomb
#define ME_Cols_lincomb  MD_Rows_lincomb
#define ME_transpose     MD_transpowe
#define ME_addM          MD_addM
#define ME_addMT         MD_addMT
#define ME_subM          MD_subM
#define ME_subMT         MD_subMT
#define ME_subrMT        MD_subrMT
#define ME_mulC          MD_mulC
#define ME_divC          MD_divC
#define MEs_addM         MDs_addM
#define MEs_addMT        MDs_addMT
#define MEs_subM         MDs_subM
#define MEs_subMT        MDs_subMT
#define MEs_subrMT       MDs_subrMT
#define ME_lincomb       MD_lincomb
#define ME_mulV          MD_mulV
#define ME_TmulV         MD_TmulV
#define VE_mulM          VD_mulM
#define VE_mulMT         VD_mulMT
#define ME_mulM          MD_mulM
#define ME_mulMT         MD_mulMT
#define ME_TmulM         MD_TmulM
#define ME_TmulMT        MD_TmulMT
#define MEdia_mulM       MDdia_mulM
#define MEdia_mulMT      MDdia_mulMT
#define ME_mulMdia       MD_mulMdia
#define ME_TmulMdia      MD_TmulMdia
#define ME_LUdecompose   MD_LUdecompose
#define ME_LUDresult     MD_LUDresult
#define ME_LUDsetEdit    MD_LUDsetEdit
#define ME_LUDgetEdit    MD_LUDgetEdit
#define ME_LUsolve       MD_LUsolve
#define ME_LUinv         MD_LUinv
#define ME_LUdet         MD_LUdet
#define ME_LUimprove     MD_LUimprove
#define ME_SVdecompose   MD_SVdecompose
#define ME_SVsolve       MD_SVsolve
#define ME_SVimprove     MD_SVimprove
#define ME_SVDsetEdit    MD_SVDsetEdit
#define ME_SVDgetEdit    MD_SVDgetEdit
#define ME_solve         MD_solve
#define ME_inv           MD_inv
#define ME_det           MD_det
#define ME_solveBySVD    MD_solveBySVD
#define ME_safeSolve     MD_safeSolve
#define MEsym_eigenvalues MDsym_eigenvalues
#define VE_getRspEdit    VD_getRspEdit 
#define VE_setRspEdit    VD_setRspEdit 
#define MEl_FFT          MDl_FFT
#define MEs_FFT          MDs_FFT
#define MEl_convolve     MDl_convolve
#define MEl_deconvolve   MDl_deconvolve
#define MEl_filter       MDl_filter
#define MEl_autocorr     MDl_autocorr
#define MEl_xcorr        MDl_xcorr
#define MEl_spectrum     MDl_spectrum
#define MEs_convolve     MDs_convolve
#define MEs_deconvolve   MDs_deconvolve
#define MEs_filter       MDs_filter
#define MEs_autocorr     MDs_autocorr
#define MEs_xcorr        MDs_xcorr
#define MEs_spectrum     MDs_spectrum
#define ME_FFT           MD_FFT
#define ME_convolve      MD_convolve
#define ME_deconvolve    MD_deconvolve
#define ME_filter        MD_filter
#define ME_autocorr      MD_autocorr
#define ME_xcorr         MD_xcorr
#define ME_spectrum      MD_spectrum
#define VE_polyfit       VD_polyfit
#define VE_polyfitwW     VD_polyfitwW
#define VE_linfit        VD_linfit
#define VE_linfitwW      VD_linfitwW
#define ME_linfit        MD_linfit
#define ME_linfitwW      MD_linfitwW
#define VE_setLinfitNeglect VD_setLinfitneglect
#define VE_getLinfitNeglect VD_getLinfitneglect
#define VE_nonlinfit     VD_nonlinfit
#define VE_nonlinfitwW   VD_nonlinfitwW
#define ME_nonlinfit     MD_nonlinfit
#define ME_nonlinfitwW   MD_nonlinfitwW
#define VE_nonlinfit_autoDeriv    VD_nonlinfit_autoDeriv
#define VE_nonlinfitwW_autoDeriv  VD_nonlinfitwW_autoDeriv
#define ME_nonlinfitwW_autoDeriv  MD_nonlinfitwW_autoDeriv
#define ME_nonlinfit_autoDeriv    MD_nonlinfit_autoDeriv
#define VE_nonlinfit_getChi2      VD_nonlinfit_getChi2
#define VE_nonlinfitwW_getChi2    VD_nonlinfitwW_getChi2
#define ME_nonlinfit_getChi2      MD_nonlinfit_getChi2
#define ME_nonlinfitwW_getChi2    MD_nonlinfitwW_getChi2
#define VE_nonlinfit_getBestValues     VD_nonlinfit_getBestValues
#define VE_nonlinfitwW_getBestValues   VD_nonlinfitwW_getBestValues
#define ME_nonlinfit_getBestValues     MD_nonlinfit_getBestValues
#define ME_nonlinfitwW_getBestValues   MD_nonlinfitwW_getBestValues
#define VE_nonlinfit_getTestRun   VD_nonlinfit_getTestRun
#define VE_nonlinfitwW_getTestRun VD_nonlinfitwW_getTestRun
#define ME_nonlinfit_getTestRun   MD_nonlinfit_getTestRun
#define ME_nonlinfitwW_getTestRun MD_nonlinfitwW_getTestRun
#define VE_nonlinfit_getTestPar   VD_nonlinfit_getTestPar
#define VE_nonlinfitwW_getTestPar VD_nonlinfitwW_getTestPar 
#define ME_nonlinfit_getTestPar   MD_nonlinfit_getTestPar
#define ME_nonlinfitwW_getTestPar MD_nonlinfitwW_getTestPar
#define VE_nonlinfit_getTestDir   VD_nonlinfit_getTestDir
#define VE_nonlinfitwW_getTestDir VD_nonlinfitwW_getTestDir
#define ME_nonlinfit_getTestDir   MD_nonlinfit_getTestDir
#define ME_nonlinfitwW_getTestDir MD_nonlinfitwW_getTestDir
#define VE_nonlinfit_stop         VD_nonlinfit_stop
#define VE_nonlinfitwW_stop       VD_nonlinfitwW_stop
#define ME_nonlinfit_stop         MD_nonlinfit_stop
#define ME_nonlinfitwW_stop       MD_nonlinfitwW_stop
#define VE_NONLINFITOPTIONS       VD_NONLINFITOPTIONS
#define VE_setNonlinfitOptions    VD_setNonlinfitOptions
#define VE_getNonlinfitOptions    VD_getNonlinfitOptions
#define VE_EXPERIMENT             VD_EXPERIMENT
#define ME_EXPERIMENT             MD_EXPERIMENT
#define VE_multiLinfit            VD_multiLinfit 
#define VE_multiLinfitwW          VD_multiLinfitwW
#define ME_multiLinfit            MD_multiLinfit
#define ME_multiLinfitwW          MD_multiLinfitwW 
#define VE_multiNonlinfit         VD_multiNonlinfit 
#define VE_multiNonlinfitwW       VD_multiNonlinfitwW
#define ME_multiNonlinfit         MD_multiNonlinfit
#define ME_multiNonlinfitwW       MD_multoNonlinfitwW
#define VE_multiNonlinfit_autoDeriv     VD_multiNonlinfit_autoDeriv
#define VE_multiNonlinfitwW_autoDeriv   VD_multiNonlinfitwW_autoDeriv 
#define ME_multiNonlinfit_autoDeriv     MD_multiNonlinfit_autoDeriv  
#define ME_multiNonlinfitwW_autoDeriv   MD_multiNonlinfitwW_autoDeriv
#define VE_multiNonlinfit_getChi2       VD_multiNonlinfit_getChi2
#define VE_multiNonlinfitwW_getChi2     VD_multiNonlinfitwW_getChi2 
#define ME_multiNonlinfit_getChi2       MD_multiNonlinfit_getChi2
#define ME_multiNonlinfitwW_getChi2     MD_multiNonlinfitwW_getChi2
#define VE_multiNonlinfit_getBestValues      VD_multiNonlinfit_getBestValues
#define VE_multiNonlinfitwW_getBestValues    VD_multiNonlinfitwW_getBestValues
#define ME_multiNonlinfit_getBestValues      MD_multiNonlinfit_getBestValues
#define ME_multiNonlinfitwW_getBestValues    MD_multiNonlinfitwW_getBestValues
#define VE_multiNonlinfit_getTestRun    VD_multiNonlinfit_getTestRun
#define VE_multiNonlinfitwW_getTestRun  VD_multiNonlinfitwW_getTestRun
#define ME_multiNonlinfit_getTestRun    MD_multiNonlinfit_getTestRun
#define ME_multiNonlinfitwW_getTestRun  MD_multiNonlinfitwW_getTestRun
#define VE_multiNonlinfit_getTestPar    VD_multiNonlinfit_getTestPar
#define VE_multiNonlinfitwW_getTestPar  VD_multiNonlinfitwW_getTestPar
#define ME_multiNonlinfit_getTestPar    MD_multiNonlinfit_getTestPar
#define ME_multiNonlinfitwW_getTestPar  MD_multiNonlinfitwW_getTestPar
#define VE_multiNonlinfit_getTestDir    VD_multiNonlinfit_getTestDir
#define VE_multiNonlinfitwW_getTestDir  VD_multiNonlinfitwW_getTestDir
#define ME_multiNonlinfit_getTestDir    MD_multiNonlinfit_getTestDir
#define ME_multiNonlinfitwW_getTestDir  MD_multiNonlinfitwW_getTestDir
#define VE_multiNonlinfit_stop          VD_multiNonlinfit_stop
#define VE_multiNonlinfitwW_stop        VD_multiNonlinfitwW_stop
#define ME_multiNonlinfit_stop          MD_multiNonlinfit_stop
#define ME_multiNonlinfitwW_stop        MD_multiNonlinfitwW_stop
#define ME_fprint    MD_fprint
#define ME_print     MD_print
#define ME_cprint    MD_cprint
#define ME_write     MD_write
#define ME_read      MD_read
#define ME_setWriteFormat    VE_setWriteFormat
#define ME_setWriteSeparate  VE_setNWriteSeparate
#define ME_store     MD_store
#define ME_recall    MD_recall

#endif  /* Borland, Microsoft, Powersoft  */

#endif /* __MESTD_H */
