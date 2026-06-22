/*  MDstd.h

  matrix management functions:
  manipulations on matrices of data type "double"
  (double-precision real numbers)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#if !defined( __MDSTD_H )
#define __MDSTD_H
#if !defined( __MATLIB_H )
#include <MatLib.h>
#endif
#if !defined( __VDSTD_H )
#include <VDstd.h>
#endif
#if !defined( __VDMATH_H )
#include <VDmath.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

dMatrix __vf  MD_matrix(  unsigned ht, unsigned len );
dMatrix __vf  MD_matrix0( unsigned ht, unsigned len );
    /*  notice that, in the memory model HUGE,
        neither len nor ht may exceed 4095            */

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

#define MD_Pelement( MA, ht, len, m, n ) MDPelement( MA[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MD_element( MA, ht, len, m, n ) *MDPelement( MA[0], ht, len, m, n )
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VDstd.h>, <VDmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being ht * len.
    For example, initialize all elements of the matrix MA with 1.0
    (this is *NOT* the identity matrix)  by calling
        VD_equ1( MA[0], ht * len );
*/

#define MD_equ0( MA, ht, len )            VD_equ0( MA[0], ((ui)ht)*len )
#define MD_equ1( MA, len )                MDequ1( MA[0], len ) /* identity matrix */
#define MD_equm1( MA, len )               MDequm1( MA[0], len ) /* neg. identity matrix */
#define MD_outerprod( MA, X, Y, ht, len ) MDouterprod( MA[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MD_Row_equ0( MA, ht, len, iRow )  MDRow_equ0( MA[0], ht, len, iRow )
#define MD_Col_equ0( MA, ht, len, iCol )  MDCol_equ0( MA[0], ht, len, iCol )
#define MD_Dia_equ0( MA, len )            MDDia_equ0( MA[0], len )
#define MD_Row_equC( MA, ht, len, iRow, C ) \
                                        MDRow_equC( MA[0], ht, len, iRow, C )
#define MD_Col_equC( MA, ht, len, iCol, C ) \
                                        MDCol_equC( MA[0], ht, len, iCol, C )
#define MD_Dia_equC( MA, len, C )       MDDia_equC( MA[0], len, C )

#define MD_Row_equV( MA, ht, len, iRow, X ) \
                                        MDRow_equV( MA[0], ht, len, iRow, X )
#define MD_Col_equV( MA, ht, len, iCol, X ) \
                                        MDCol_equV( MA[0], ht, len, iCol, X )
#define MD_Dia_equV( MA, len, X )       MDDia_equV( MA[0], len, X )

#define MD_Trd_equM( MA, MTrd, len )    MDTrd_equM( MA[0], MTrd[0], len )
#define MD_Trd_extract( MTrd, MA, len ) MDTrd_extract( MTrd[0], MA[0], len )

#define MD_equM( MB, MA, ht, len )  VD_equV( MB[0], MA[0], (ui)(ht)*(len) )
#define MD_neg( MB, MA, ht, len )   VD_neg( MB[0], MA[0], (ui)(ht)*(len) )

#define MD_UequL( MA, len ) MDUequL( MA[0], len )
#define MD_LequU( MA, len ) MDLequU( MA[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_DtoF( MF, MD, ht, len ) V_DtoF( MF[0], MD[0], ((ui)ht)*len )
#define M_FtoD( MD, MF, ht, len ) V_FtoD( MD[0], MF[0], ((ui)ht)*len )
#define M_EtoD( MD, ME, ht, len ) V_EtoD( MD[0], ME[0], ((ui)ht)*len )
#define M_DtoE( ME, MD, ht, len ) V_DtoE( ME[0], MD[0], ((ui)ht)*len )

            /* suitable windows for MF_spectrum: */
#define MD_Hanning( MA, ht, len )  MDHanning( MA[0], ht, len )
#define MD_Parzen( MA, ht, len )   MDParzen( MA[0], ht, len )
#define MD_Welch( MA, ht, len )    MDWelch( MA[0], ht, len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MD_submatrix( MSub, subHt, subLen, \
                      MSrce, srceHt, srceLen, \
                      firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MDsubmatrix(  MSub[0], subHt, subLen, \
                             MSrce[0], srceHt, srceLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MD_submatrix_equM( MDest, destHt, destLen, \
                           firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                           MSrce, srceHt, srceLen ) \
               MDsubmatrix_equM(  MDest[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             MSrce[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MD_Row_extract( Y, MA, ht, len, iRow ) \
                                     MDRow_extract( Y, MA[0], ht, len, iRow )
#define MD_Col_extract( Y, MA, ht, len, iCol ) \
                                     MDCol_extract( Y, MA[0], ht, len, iCol )
#define MD_Dia_extract( Y, MA, len ) MDDia_extract( Y, MA[0], len )

/**************  Deleting or inserting a row or a column   ***************/

#define MD_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MDRow_delete( MB[0], MA[0], htA, lenA, iRow )
#define MD_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MDCol_delete( MB[0], MA[0], htA, lenA, iCol )
#define MD_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MDRow_insert( MB[0], MA[0], htB, lenB, iRow, X )
#define MD_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MDCol_insert( MB[0], MA[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MD_Row_addC( MA, ht, len, iRow, C ) \
                                     MDRow_addC( MA[0], ht, len, iRow, C )
#define MD_Col_addC( MA, ht, len, iCol, C ) \
                                     MDCol_addC( MA[0], ht, len, iCol, C )
#define MD_Dia_addC( MA, len, C )    MDDia_addC( MA[0], len, C )

#define MD_Row_addV( MA, ht, len, iRow, X ) \
                                     MDRow_addV( MA[0], ht, len, iRow, X )
#define MD_Col_addV( MA, ht, len, iCol, X ) \
                                     MDCol_addV( MA[0], ht, len, iCol, X )
#define MD_Dia_addV( MA, len, X )    MDDia_addV( MA[0], len, X )

#define MD_Row_subC( MA, ht, len, iRow, C ) \
                                     MDRow_subC( MA[0], ht, len, iRow, C )
#define MD_Col_subC( MA, ht, len, iCol, C ) \
                                     MDCol_subC( MA[0], ht, len, iCol, C )
#define MD_Dia_subC( MA, len, C )    MDDia_subC( MA[0], len, C )

#define MD_Row_subV( MA, ht, len, iRow, X ) \
                                     MDRow_subV( MA[0], ht, len, iRow, X )
#define MD_Col_subV( MA, ht, len, iCol, X ) \
                                     MDCol_subV( MA[0], ht, len, iCol, X )
#define MD_Dia_subV( MA, len, X )    MDDia_subV( MA[0], len, X )

#define MD_Row_subrC( MA, ht, len, iRow, C ) \
                                     MDRow_subrC( MA[0], ht, len, iRow, C )
#define MD_Col_subrC( MA, ht, len, iCol, C ) \
                                     MDCol_subrC( MA[0], ht, len, iCol, C )
#define MD_Dia_subrC( MA, len, C )   MDDia_subrC( MA[0], len, C )

#define MD_Row_subrV( MA, ht, len, iRow, X ) \
                                     MDRow_subrV( MA[0], ht, len, iRow, X )
#define MD_Col_subrV( MA, ht, len, iCol, X ) \
                                     MDCol_subrV( MA[0], ht, len, iCol, X )
#define MD_Dia_subrV( MA, len, X )   MDDia_subrV( MA[0], len, X )

#define MD_Row_mulC( MA, ht, len, iRow, C ) \
                                     MDRow_mulC( MA[0], ht, len, iRow, C )
#define MD_Col_mulC( MA, ht, len, iCol, C ) \
                                     MDCol_mulC( MA[0], ht, len, iCol, C )
#define MD_Dia_mulC( MA, len, C )    MDDia_mulC( MA[0], len, C )

#define MD_Row_mulV( MA, ht, len, iRow, X ) \
                                     MDRow_mulV( MA[0], ht, len, iRow, X )
#define MD_Col_mulV( MA, ht, len, iCol, X ) \
                                     MDCol_mulV( MA[0], ht, len, iCol, X )
#define MD_Dia_mulV( MA, len, X )    MDDia_mulV( MA[0], len, X )

#define MD_Row_divC( MA, ht, len, iRow, C ) \
                                     MDRow_divC( MA[0], ht, len, iRow, C )
#define MD_Col_divC( MA, ht, len, iCol, C ) \
                                     MDCol_divC( MA[0], ht, len, iCol, C )
#define MD_Dia_divC( MA, len, C )    MDDia_divC( MA[0], len, C )

#define MD_Row_divV( MA, ht, len, iRow, X ) \
                                      MDRow_divV( MA[0], ht, len, iRow, X )
#define MD_Col_divV( MA, ht, len, iCol, X ) \
                                      MDCol_divV( MA[0], ht, len, iCol, X )
#define MD_Dia_divV( MA, len, X )     MDDia_divV( MA[0], len, X )

#define MD_Row_divrC( MA, ht, len, iRow, C ) \
                                      MDRow_divrC( MA[0], ht, len, iRow, C )
#define MD_Col_divrC( MA, ht, len, iCol, C ) \
                                      MDCol_divrC( MA[0], ht, len, iCol, C )
#define MD_Dia_divrC( MA, len, C )    MDDia_divrC( MA[0], len, C )

#define MD_Row_divrV( MA, ht, len, iRow, X ) \
                                      MDRow_divrV( MA[0], ht, len, iRow, X )
#define MD_Col_divrV( MA, ht, len, iCol, X ) \
                                      MDCol_divrV( MA[0], ht, len, iCol, X )
#define MD_Dia_divrV( MA, len, X )    MDDia_divrV( MA[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MD_Rows_max( Y, MA, ht, len )     MDRows_max( Y, MA[0], ht, len )
#define MD_Cols_max( Y, MA, ht, len )     MDCols_max( Y, MA[0], ht, len )
#define MD_Dia_max(  MA, len )            MDDia_max(  MA[0], len )
#define MD_Rows_min( Y, MA, ht, len )     MDRows_min( Y, MA[0], ht, len )
#define MD_Cols_min( Y, MA, ht, len )     MDCols_min( Y, MA[0], ht, len )
#define MD_Dia_min(  MA, len )            MDDia_min(  MA[0], len )

#define MD_Rows_absmax( Y, MA, ht, len )  MDRows_absmax( Y, MA[0], ht, len )
#define MD_Cols_absmax( Y, MA, ht, len )  MDCols_absmax( Y, MA[0], ht, len )
#define MD_Dia_absmax(  MA, len )         MDDia_absmax(  MA[0], len )
#define MD_Rows_absmin( Y, MA, ht, len )  MDRows_absmin( Y, MA[0], ht, len )
#define MD_Cols_absmin( Y, MA, ht, len )  MDCols_absmin( Y, MA[0], ht, len )
#define MD_Dia_absmin(  MA, len )         MDDia_absmin(  MA[0], len )

#define MD_Rows_sum( Y, MA, ht, len )     MDRows_sum( Y, MA[0], ht, len )
#define MD_Cols_sum( Y, MA, ht, len )     MDCols_sum( Y, MA[0], ht, len )
#define MD_Dia_sum(  MA, len )            MDDia_sum(  MA[0], len )
#define MD_Rows_prod( Y, MA, ht, len )    MDRows_prod( Y, MA[0], ht, len )
#define MD_Cols_prod( Y, MA, ht, len )    MDCols_prod( Y, MA[0], ht, len )
#define MD_Dia_prod(  MA, len )           MDDia_prod(  MA[0], len )

#define MD_Rows_runsum( MA, ht, len )     MDRows_runsum( MA[0], ht, len )
#define MD_Cols_runsum( MA, ht, len )     MDCols_runsum( MA[0], ht, len )
#define MD_Rows_runprod( MA, ht, len )    MDRows_runprod( MA[0], ht, len )
#define MD_Cols_runprod( MA, ht, len )    MDCols_runprod( MA[0], ht, len )

#define MD_Rows_rotate( MA, ht, len, pos) MDRows_rotate( MA[0], ht, len, pos )
#define MD_Cols_rotate( MA, ht, len, pos) MDCols_rotate( MA[0], ht, len, pos )
#define MD_Rows_reflect( MA, ht, len )    MDRows_reflect( MA[0], ht, len )
#define MD_Cols_reflect( MA, ht, len )    MDCols_reflect( MA[0], ht, len )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MD_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MDRows_exchange( MA[0], ht, len, row1, row2 )
#define MD_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MDCols_exchange( MA[0], ht, len, col1, col2 )

#define MD_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MDRows_add( MA[0], ht, len, destRow, srceRow )
#define MD_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MDCols_add( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MD_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MDRows_sub( MA[0], ht, len, destRow, srceRow )
#define MD_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MDCols_sub( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MD_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MDRows_Cadd( MA[0], ht, len, destRow, srceRow, C )
#define MD_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MDCols_Cadd( MA[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MD_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MDRows_lincomb( MA[0], ht, len, destRow, destC, srceRow, srceC )
#define MD_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MDCols_lincomb( MA[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*************************  Transposing a matrix **********************/

#define MD_transpose( MTr, MA, htTr, lenTr ) \
             MDtranspose( MTr[0], MA[0], htTr, lenTr )
       /*  dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */


/************************ Matrix Arithmetics *************************/

#define MD_addM( MC, MA, MB, htA, lenA ) \
                 VD_addV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MD_addMT( MC, MA, MB, htA, lenA ) \
                 MDaddMT( MC[0], MA[0], MB[0], htA, lenA )
#define MD_subM( MC, MA, MB, htA, lenA ) \
                 VD_subV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MD_subMT( MC, MA, MB, htA, lenA ) \
                 MDsubMT( MC[0], MA[0], MB[0], htA, lenA )
#define MD_subrMT( MC, MA, MB, htA, lenA ) \
                 MDsubrMT( MC[0], MA[0], MB[0], htA, lenA )
#define MD_mulC( MB, MA, htA, lenA, C ) \
                 VD_mulC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MD_divC( MB, MA, htA, lenA, C ) \
                 VD_divC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MDs_addM( MC, MA, MB, htA, lenA, C ) \
                 VDs_addV( MC[0], MA[0], MB[0], ((ui)htA)*lenA, C )
#define MDs_addMT( MC, MA, MB, htA, lenA, C ) \
                 MDsaddMT( MC[0], MA[0], MB[0], htA, lenA, C )
#define MDs_subM( MC, MA, MB, htA, lenA, C ) \
                 VDs_subV( MC[0], MA[0], MB[0], ((ui)htA)*lenA, C )
#define MDs_subMT( MC, MA, MB, htA, lenA, C ) \
                 MDssubMT( MC[0], MA[0], MB[0], htA, lenA, C )
#define MDs_subrMT( MC, MA, MB, htA, lenA, C ) \
                 MDssubrMT( MC[0], MA[0], MB[0], htA, lenA, C )
#define MD_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VD_lincomb( MC[0], MA[0], MB[0], ((ui)htA)*lenA, CA, CB )

#define MD_mulV( Y, MA, X, htA, lenA ) \
                    MDmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MD_TmulV( Y, MA, X, htA, lenA ) \
                    MDTmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VD_mulM( Y, X, MA, htA, lenA ) \
                    VDmulM( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VD_ (not MD_)    */
#define VD_mulMT( Y, X, MA, htA, lenA ) \
                    VDmulMT( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MD_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MDmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MD_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MDmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MD_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MDTmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MD_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MDTmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MDdia_mulM(  MC, MADia, MB, htB, lenB )  MDdiamulM(  MC[0], MADia, MB[0], htB, lenB )
#define MDdia_mulMT( MC, MADia, MB, htB, lenB )  MDdiamulMT( MC[0], MADia, MB[0], htB, lenB )
#define MD_mulMdia(  MC, MA, MBDia, htA, lenA )  MDmulMdia(  MC[0], MA[0], MBDia, htA, lenA )
#define MD_TmulMdia( MC, MA, MBDia, htA, lenA )  MDTmulMdia( MC[0], MA[0], MBDia, htA, lenA )


/*************************  Linear Algebra    *****************************/

   /*  The standard treatment of linear systems is based
       on LUD (matrix decomposition into Upper-triangular
       and Lower-triangular components). The result of the
       decomposition step is used for further operations.  */

#define MD_LUdecompose( MLU, Ind, MA, len ) \
                    MDLUdecompose( MLU[0], Ind, MA[0], len )
            /* returns "permut" = ñ1 which is needed for MD_LUdet.
               for singularities not cured by editing, permut is 0  */
int     __vf MD_LUDresult( void );
    /* returns 0, if MD_LUdecompose was successful;
       returns 1, if MA was (nearly) singular in MD_LUdecompose.   */
void    __vf MD_LUDsetEdit( double Thresh );
double  __vf MD_LUDgetEdit( void );
     /*  Editing threshold valid for MD_LUdecompose;
         may be used to cure singularities           */

#define MD_LUsolve( X, MLU, B, Ind, len ) \
                    MDLUsolve( X, MLU[0], B, Ind, len )
#define MD_LUinv( MInv, MLU, Ind, len ) \
                    MDLUinv( MInv[0], MLU[0], Ind, len )
#define MD_LUdet( MLU, len, permut )  MDLUdet( MLU[0], len, permut )
#define MD_LUimprove( X, B, MA, MLU, Ind, len ) \
                      MDLUimprove( X, B, MA[0], MLU[0], Ind, len )

    /****  Special treatment of over- or under-determined
           linear systems, i.e. of matrices with len != ht
           and of singular matrices:
           SVD (Singular Value Decomposition)       ****/

#define MD_SVdecompose( MU, MV, W, MA, htA, lenA ) \
                    MDSVdecompose( MU[0], MV[0], W, MA[0], htA, lenA )
            /*  sizB = htA,  sizX = sizW = htV = lenV = lenA  */
#define MD_SVsolve( X, MU, MV, W, B, htU, lenU ) \
                    MDSVsolve( X, MU[0], MV[0], W, B, htU, lenU )
            /*  lenU = lenA,  htU = max( lenA, htA ) as fed into
                MD_SVdecompose   */
void    __vf MD_SVDsetEdit( double Thresh );
double  __vf MD_SVDgetEdit( void );
    /* Override of the standard values for editing threshholds
       in MD_SVsolve. Calling MD_setEdit with Thresh=0.0 means
       that you do the necessary editing of W yourself
       before calling MD_SVsolve                           */

 /*****  "Easy-to-use" versions of the matrix functions
          using LUD or SVD.
          They allocate their own working space and rely
          on your setting of the editing threshold. In
          case of memory stress, you might better use the
          two-step methods declared above.            ***/
#define MD_solve( X, MA, B, len ) \
                    MDsolve( X, MA[0], B, len )
#define MD_inv( MInv, MA, len ) \
                    MDinv( MInv[0], MA[0], len )
#define MD_det(  MA, len ) \
                    MDdet( MA[0], len )
#define MD_solveBySVD( X, MA, B, ht, len ) \
                    MDsolveBySVD( X, MA[0], B, ht, len )
         /*  sizX = len,  sizB = ht  */
#define MD_safeSolve( X, MA, B, len ) \
                    MDsafeSolve( X, MA[0], B, len )
        /* MD_safeSolve tries first LUD. If that fails, SVD is done.
           X[i] will be 0.0 instead of INF for those i corresponding
           to singularities. If even SVD fails, all X[i] are set to 0.0.
           return value 0: success via LUD; 1: success via SVD; -1: failure */

      /*********  Eigenvalues and Eigenvectors  ********/
      /*** only the most frequent case of symmetric real matrices
           is covered here! *********/

#define MDsym_eigenvalues( EigV, EigM, MA, len, CalcEigenVec ) \
                    MDs_eigenvalues( EigV, EigM[0], MA[0], len, CalcEigenVec )
                        /*  Eigenvalues are returned in EigV,
                            Eigenvectors are returned as the columns of EigM.
                            CalcEigenVec = 0 means that only eigenvalues
                            are needed; CalcEigenVec != 0 means that
                            also eigenvectors are calculated.
                            Even if eigenvectors are not desired, EigM is
                            needed by the function as working-space. Then, on
                            output, it will contain just rubbish.
                            MA may be overwritten by EigM. */

/***************** Two-Dimensional Fourier-Transform Methods ************/

#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // following function cannot be extern "C"
#endif
dComplex  __vf   VD_getRspEdit( void );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif
void      __vf   VD_setRspEdit( dComplex Trunc );
           /* these are the same functions as used
              in the one-dimensional case */

#define MDl_FFT( MY, MX, ht, len, dir )     MDlFFT( MY[0], MX[0], ht, len, dir )
#define MDs_FFT( MY, MX, ht, len, dir )     MDsFFT( MY[0], MX[0], ht, len, dir )
#define MDl_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDlconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MDl_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDldeconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MDl_filter( MY, MX, MFlt, ht, len ) MDlfilter( MY[0], MX[0], MFlt[0], ht, len )
#define MDl_autocorr( MACorr, MX, ht, len ) MDlautocorr( MACorr[0], MX[0], ht, len )
#define MDl_xcorr( MXCorr, MX, MY, ht, len) MDlxcorr( MXCorr[0], MX[0], MY[0], ht, len )
#define MDl_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MDlspectrum( MSpec[0], htSpec, lenSpec, MX[0], htX, lenX, MWin[0] )
              /*   htSpec, lenSpec must be 2**n,
                   MSpec must be a (htSpec+1)*(lenSpec+1) matrix!!
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec */

#define MDs_convolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDsconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MDs_deconvolve( MY, MFlt, MX, MRsp, ht, len ) \
                  MDsdeconvolve( MY[0], MFlt[0], MX[0], MRsp[0], ht, len )
#define MDs_filter( MY, MX, MFlt, ht, len ) MDsfilter( MY[0], MX[0], MFlt[0], ht, len )
#define MDs_autocorr( MACorr, MX, ht, len ) MDsautocorr( MACorr[0], MX[0], ht, len )
#define MDs_xcorr( MXCorr, MX, MY, ht, len) MDsxcorr( MXCorr[0], MX[0], MY[0], ht, len )
#define MDs_spectrum( MSpec, htSpec, lenSpec, MX, htX, lenX, MWin ) \
              MDsspectrum( MSpec[0], htSpec, lenSpec, MX[0], htX, lenX, MWin[0] )
               /*  htSpec, lenSpec must be 2**n,
                   MSpec has [htSpec+1][lenSpec+1] elements (!)
                   htX >= n*htSpec,  lenX >= n*lenSpec,
                   htWin = 2*htSpec, lenWin = 2*lenSpec     */

#if defined( __LARGE__ ) || defined( __COMPACT__ ) || defined ( __HUGE__ )
   #define MD_FFT         MDl_FFT
   #define MD_convolve    MDl_convolve
   #define MD_deconvolve  MDl_deconvolve
   #define MD_filter      MDl_filter
   #define MD_autocorr    MDl_autocorr
   #define MD_xcorr       MDl_xcorr
   #define MD_spectrum    MDl_spectrum
#else
   #define MD_FFT         MDs_FFT
   #define MD_convolve    MDs_convolve
   #define MD_deconvolve  MDs_deconvolve
   #define MD_filter      MDs_filter
   #define MD_autocorr    MDs_autocorr
   #define MD_xcorr       MDs_xcorr
   #define MD_spectrum    MDs_spectrum
#endif


/************************** Data Fitting *********************************

  Notice that some of these functions have the prefix VD_, others MD_.
  This depends on the form in which the data to be fitted are recorded:
  vectors are fitted by the VD_ functions, matrices by the MD_ functions.
  All of these functions employ matrix methods internally. The weighted
  versions return covariances in a matrix "Covar". So they are all
  contained in MatrixLib and declared here.
*/

void __vf VD_polyfit( dVector ParValues, unsigned deg, dVector X, dVector Y, ui sizex );
#define   VD_polyfitwW( ParValues, Covar, deg, X, Y, InvVar, sizex ) \
          VDpolyfitwW( ParValues, Covar[0], deg, X, Y, InvVar, sizex )
       /* the size of A is deg+1 and Covar has [deg+1][deg+1] elements! */

void __vf VD_linfit( dVector ParValues, iVector ParStatus, unsigned npars,
                     dVector X, dVector Y, ui sizex,
                     void (*funcs)(dVector BasFuncs, double x, unsigned nfuncs) );
#define   VD_linfitwW( ParValues, Covar, ParStatus, npars, X, Y, InvVar, sizex, funcs ) \
          VDlinfitwW( ParValues, Covar[0], ParStatus, npars, X, Y, InvVar, sizex, funcs )
#define   MD_linfit( ParValues, ParStatus, npars, X, Y, MZ, htZ, lenZ, funcs ) \
          MDlinfit( ParValues, ParStatus, npars, X, Y, MZ[0], htZ, lenZ, funcs )
#define   MD_linfitwW( ParValues, Covar, ParStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, funcs ) \
          MDlinfitwW( ParValues, Covar[0], ParStatus, npars, X, Y, MZ[0], MInvVar[0], htZ, lenZ, funcs )

void  __vf VD_setLinfitNeglect( double Thresh );
                   /* neglect A[i]=0, if significance smaller than Thresh */
double __vf VD_getLinfitNeglect( void );

double __vf VD_nonlinfit( dVector ParValues, iVector ParStatus, unsigned npars,
                         dVector X, dVector Y, ui sizex,
                         void (*modelfunc)(dVector YModel, dVector XModel, ui size),
                         void (*derivatives)(dVector dYdPari,dVector X, ui size, unsigned i) );
            /* returns figure-of-merit of best A. If you don't know the partial
               derivatives with respect to ParValues, call with derivatives=NULL */
#define   VD_nonlinfitwW( ParValues, Covar, ParStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv ) \
          VDnonlinfitwW( ParValues, Covar[0], ParStatus, npars, X, Y, InvVar, sizex, modelfunc, deriv )
#define   MD_nonlinfit( ParValues, ParStatus, npars, X, Y, MZ, htZ, lenZ, modelfunc, deriv ) \
          MDnonlinfit( ParValues, ParStatus, npars, X, Y, MZ[0], htZ, lenZ, modelfunc, deriv )
#define   MD_nonlinfitwW( ParValues, Covar, ParStatus, npars, X, Y, MZ, MInvVar, htZ, lenZ, modelfunc, deriv ) \
          MDnonlinfitwW( ParValues, Covar[0], ParStatus, npars, X, Y, MZ[0], MInvVar[0], htZ, lenZ, modelfunc, deriv )

        /* If you know some partial derivatives, you may call these functions
           for those parameters for which you do not know them:           */
void   __vf VD_nonlinfit_autoDeriv( dVector dYdPari, dVector X, ui size, unsigned ipar );
void   __vf VD_nonlinfitwW_autoDeriv( dVector dYdPari, dVector X, ui size, unsigned ipar );
void   __vf MD_nonlinfitwW_autoDeriv( dMatrix dZdAi, unsigned htZ, unsigned lenZ, dVector X, dVector Y, unsigned ipar );
void   __vf MD_nonlinfit_autoDeriv( dMatrix dZdAi, unsigned htZ, unsigned lenZ, dVector X, dVector Y, unsigned ipar );
       /* The following functions allow to monitor the progress of
          a nonlinear fitting procedure or to manually stop it:     */
double   __vf VD_nonlinfit_getChi2( void );
double   __vf VD_nonlinfitwW_getChi2( void );
double   __vf MD_nonlinfit_getChi2( void );
double   __vf MD_nonlinfitwW_getChi2( void );
void     __vf VD_nonlinfit_getBestValues( dVector BestValues );
void     __vf VD_nonlinfitwW_getBestValues( dVector BestValues );
void     __vf MD_nonlinfit_getBestValues( dVector BestValues );
void     __vf MD_nonlinfitwW_getBestValues( dVector BestValues );
unsigned __vf VD_nonlinfit_getTestRun( void );
unsigned __vf VD_nonlinfitwW_getTestRun( void );
unsigned __vf MD_nonlinfit_getTestRun( void );
unsigned __vf MD_nonlinfitwW_getTestRun( void );
unsigned __vf VD_nonlinfit_getTestPar( void );
unsigned __vf VD_nonlinfitwW_getTestPar( void );
unsigned __vf MD_nonlinfit_getTestPar( void );
unsigned __vf MD_nonlinfitwW_getTestPar( void );
int      __vf VD_nonlinfit_getTestDir( void );
int      __vf VD_nonlinfitwW_getTestDir( void );
int      __vf MD_nonlinfit_getTestDir( void );
int      __vf MD_nonlinfitwW_getTestDir( void );
void     __vf VD_nonlinfit_stop( void );
void     __vf VD_nonlinfitwW_stop( void );
void     __vf MD_nonlinfit_stop( void );
void     __vf MD_nonlinfitwW_stop( void );

#ifdef __BORLANDC__
    #pragma option -a-  /* avoid insertion of dummy bytes */
#else   /* MS Visual C++ */
    #pragma pack(push,1)
#endif    /*  Borland or Microsoft */

typedef struct VD_NONLINFITOPTIONS
{
      int        FigureOfMerit;  /*  0:least squares, 1:robust */
             /* Convergence conditions: if the changes achieved
                in successive iterations are lower than any of the
                following values, this signals convergence. Set
                criteria to 0.0, if not applicable              */
      double     AbsTolChi,  /* absolute change of chi */
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
      double     LambdaStart,
                 LambdaMin, LambdaMax,
                 LambdaDiv, LambdaMul;    /* LevMar parameter lambda */
      unsigned   DownhillIterations; /* max.number of successful iterations in Downhill */
      double     DownhillReflection,  /* re-shaping of the simplex */
                 DownhillContraction,
                 DownhillExpansion;
      unsigned   TotalStarts;  /* max. number of LevMar/Downhill pairs */
      dVector    UpperLimits;  /* impose upper limits on parameters */
      dVector    LowerLimits;  /* impose lower limits on parameters */
      void       (*Restrictions)(void);  /* user-defined editing of parameters */
}  VD_NONLINFITOPTIONS;

void __vf VD_setNonlinfitOptions( VD_NONLINFITOPTIONS *Options );
void __vf VD_getNonlinfitOptions( VD_NONLINFITOPTIONS *Options );

typedef struct VD_EXPERIMENT
{
    dVector  X, Y, InvVar;
    ui       size;
    double   WeightOfExperiment;
     /* InvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} VD_EXPERIMENT;

typedef struct MD_EXPERIMENT
{
    dVector    X, Y;
    dMatrix    MZ, MInvVar;  /* here no compatibility with static matrices! */
    unsigned   htZ, lenZ;
    double     WeightOfExperiment;
     /* MInvVar and WeightOfExperiment are needed only for the
        weighted variants of the multifit functions */
} MD_EXPERIMENT;

#ifdef __BORLANDC__
    #pragma option -a.   /* restore default data packing  */
#else   /* MS Visual C++ */
    #pragma pack(pop)
#endif

void __vf VD_multiLinfit( dVector ParValues, iVector ParStatus, unsigned nParameters,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nExperiments,
                void (*funcs)(dVector BasFuncs, double x,
                              unsigned nfuncs, unsigned iexperiment) );
#define   VD_multiLinfitwW( ParValues, Covar, ParStatus, npars, ListOfEx, nexp, funcs ) \
          VDmultiLinfitwW( ParValues, Covar[0], ParStatus, npars, ListOfEx, nexp, funcs )
void __vf MD_multiLinfit( dVector ParValues, iVector ParStatus, unsigned nParameters,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nExperiments,
                void (*funcs)(dVector BasFuncs, double x, double y,
                              unsigned nfuncs, unsigned iexperiment) );
#define   MD_multiLinfitwW( ParValues, Covar, ParStatus, npars, ListOfEx, nexp, funcs ) \
          MDmultiLinfitwW( ParValues, Covar[0], ParStatus, npars, ListOfEx, nexp, funcs )
double __vf VD_multiNonlinfit( dVector ParValues,
                iVector ParStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nExperiments,
                void (*modelfunc)(dVector YModel, dVector XModel,
                                  ui size, unsigned iexperiment),
                void (*derivatives)(dVector dYdPari,dVector X, ui size,
                                   unsigned ipar, unsigned iexperiment) );
            /* returns figure-of-merit of best ParValues. Chi2Detail contains
               the chi2 contribution of each experiment.
               If you don't know the partial derivatives, set derivatives=NULL */
#define   VD_multiNonlinfitwW( ParValues, Covar, ParStatus, npars, ListOfEx, nexp, modfunc, deriv ) \
          VDmultiNonlinfitwW( ParValues, Covar[0], ParStatus, npars, ListOfEx, nexp, modfunc, deriv )
double __vf MD_multiNonlinfit( dVector ParValues, iVector ParStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(dMatrix MZModel, unsigned htZ, unsigned lenZ,
                                  dVector X, dVector Y, unsigned iexperiment),
                void (*derivatives)(dMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    dVector X, dVector Y, unsigned ipar,
                                    unsigned iexperiment) );
#define   MD_multiNonlinfitwW( ParValues, Covar, ParStatus, npars, ListOfEx, nexp, modfunc, deriv ) \
          MDmultiNonlinfitwW( ParValues, Covar[0], ParStatus, npars, ListOfEx, nexp, modfunc, deriv )

void  __vf VD_multiNonlinfit_autoDeriv( dVector dYdPari, dVector X, ui size,
                                        unsigned ipar, unsigned iexperiment);
void  __vf VD_multiNonlinfitwW_autoDeriv( dVector dYdPari, dVector X, ui size,
                                        unsigned ipar, unsigned iexperiment );
void  __vf MD_multiNonlinfit_autoDeriv( dMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    dVector X, dVector Y,
                                    unsigned ipar, unsigned iexperiment );
void  __vf MD_multiNonlinfitwW_autoDeriv( dMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    dVector X, dVector Y,
                                    unsigned ipar, unsigned iexperiment );
double   __vf VD_multiNonlinfit_getChi2( void );
double   __vf VD_multiNonlinfitwW_getChi2( void );
double   __vf MD_multiNonlinfit_getChi2( void );
double   __vf MD_multiNonlinfitwW_getChi2( void );
void     __vf VD_multiNonlinfit_getChi2Detail( dVector Chi2Detail );
void     __vf VD_multiNonlinfitwW_getChi2Detail( dVector Chi2Detail );
void     __vf MD_multiNonlinfit_getChi2Detail( dVector Chi2Detail );
void     __vf MD_multiNonlinfitwW_getChi2Detail( dVector Chi2Detail );
void     __vf VD_multiNonlinfit_getBestValues( dVector BestValues );
void     __vf VD_multiNonlinfitwW_getBestValues( dVector BestValues );
void     __vf MD_multiNonlinfit_getBestValues( dVector BestValues );
void     __vf MD_multiNonlinfitwW_getBestValues( dVector BestValues );
unsigned __vf VD_multiNonlinfit_getTestRun( void );
unsigned __vf VD_multiNonlinfitwW_getTestRun( void );
unsigned __vf MD_multiNonlinfit_getTestRun( void );
unsigned __vf MD_multiNonlinfitwW_getTestRun( void );
unsigned __vf VD_multiNonlinfit_getTestPar( void );
unsigned __vf VD_multiNonlinfitwW_getTestPar( void );
unsigned __vf MD_multiNonlinfit_getTestPar( void );
unsigned __vf MD_multiNonlinfitwW_getTestPar( void );
int      __vf VD_multiNonlinfit_getTestDir( void );
int      __vf VD_multiNonlinfitwW_getTestDir( void );
int      __vf MD_multiNonlinfit_getTestDir( void );
int      __vf MD_multiNonlinfitwW_getTestDir( void );
void     __vf VD_multiNonlinfit_stop( void );
void     __vf VD_multiNonlinfitwW_stop( void );
void     __vf MD_multiNonlinfit_stop( void );
void     __vf MD_multiNonlinfitwW_stop( void );

/**************************  Input and Output  **************************/

#define MD_fprint( stream, MA, ht, len, linewidth ) \
                    MDfprint( stream, MA[0], ht, len, linewidth )
#define MD_print( MA, ht, len )  MDfprint( stdout, MA[0], ht, len, 80 )
#define MD_cprint( MA, ht, len ) MDcprint( MA[0], ht, len )
  /*  MD_print, MD_cprint usable only for DOS, EasyWin, and Win32 console applications! */

#define MD_write( str, MA, ht, len )   MDwrite( str, MA[0], ht, len )
#define MD_read( MA, ht, len, str )    MDread( MA[0], ht, len, str )
#define MD_setWriteFormat              VD_setWriteFormat
#define MD_setWriteSeparate            VD_setNWriteSeparate
                                   /* write and read in ascii format */
#define MD_store( str, MA, ht, len ) \
                           VD_store( str, MA[0], ((ui)(len))*(ht) );
#define MD_recall( MA, ht, len, str) \
                           VD_recall( MA[0], ((ui)(len))*(ht), str);
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

double _VFAR * MDPelement( dPMatrix X, unsigned ht, unsigned len,
                         unsigned m, unsigned n );
                  /* pointer is normalized in memory model HUGE */
#define MDelement( MA, ht, len, m, n ) (*MDPelement( MA, ht, len, m, n ))

#define MDequ0( MA, ht, len )            VD_equ0( MA, ((ui)ht)*len )
void   __vf  MDequ1( dPMatrix MA, unsigned len );  /* identity matrix */
void   __vf  MDequm1( dPMatrix MA, unsigned len );  /* neg. identity matrix */
void   __vf  MDouterprod( dPMatrix MA, dVector X,  dVector Y,
                          unsigned ht, unsigned len );

void   __vf  MDRow_equ0( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow );
void   __vf  MDCol_equ0( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol );
void   __vf  MDDia_equ0( dPMatrix MA, unsigned len );

void   __vf  MDRow_equC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, double C );
void   __vf  MDCol_equC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, double C );
void   __vf  MDDia_equC( dPMatrix MA, unsigned len, double C );

void   __vf  MDRow_equV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dVector X );
void   __vf  MDCol_equV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dVector X );
void   __vf  MDDia_equV( dPMatrix MA, unsigned len, dVector X );

void   __vf  MDTrd_equM( dPMatrix MA, dPMatrix MTrd, unsigned len );
void   __vf  MDTrd_extract( dPMatrix MTrd, dPMatrix MA, unsigned len );

#define MDequM( MB, MA, ht, len )  VD_equV( MB, MA, (ui)(ht)*(len) )
#define MDneg( MB, MA, ht, len )   VD_neg( MB, MA, (ui)(ht)*(len) )
void   __vf  MDUequL( dPMatrix MA, unsigned len );
void   __vf  MDLequU( dPMatrix MA, unsigned len );

void   __vf  MDHanning( dPMatrix MA, unsigned ht, unsigned len );
void   __vf  MDParzen(  dPMatrix MA, unsigned ht, unsigned len );
void   __vf  MDWelch(   dPMatrix MA, unsigned ht, unsigned len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MDsubmatrix( dPMatrix MSub,
                          unsigned subHt,  unsigned subLen,
                          dPMatrix MSrce,
                          unsigned srceHt,  unsigned srceLen,
                          unsigned firstRowInCol,  unsigned sampInCol,
                          unsigned firstColInRow,  unsigned sampInRow );

void  __vf  MDsubmatrix_equM( dPMatrix MDest,
                               unsigned destHt,     unsigned destLen,
                               unsigned firstRowInCol,  unsigned sampInCol,
                               unsigned firstColInRow,  unsigned sampInRow,
                               dPMatrix MSrce,
                               unsigned srceHt,     unsigned srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MDRow_extract( dVector Y, dPMatrix MA, unsigned ht, unsigned len,
                           unsigned iRow );
void __vf MDCol_extract( dVector Y, dPMatrix MA, unsigned ht, unsigned len,
                           unsigned iCol );
void __vf MDDia_extract( dVector Y, dPMatrix MA, unsigned len );

/**********  Deleting or inserting a row or a column *****************/

void __vf MDRow_delete( dPMatrix MB, dPMatrix MA,
                        unsigned htA, unsigned lenA, unsigned iRow );
void __vf MDCol_delete( dPMatrix MB, dPMatrix MA,
                        unsigned htA, unsigned lenA, unsigned iCol );
void __vf MDRow_insert( dPMatrix MB, dPMatrix MA, unsigned htB,
                        unsigned lenB, unsigned iRow, dVector X );
void __vf MDCol_insert( dPMatrix MB, dPMatrix MA, unsigned htB,
                        unsigned lenB, unsigned iCol, dVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MDRow_addC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, double C );
void   __vf  MDCol_addC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, double C );
void   __vf  MDDia_addC( dPMatrix MA, unsigned len, double C );

void   __vf  MDRow_subC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, double C );
void   __vf  MDCol_subC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, double C );
void   __vf  MDDia_subC( dPMatrix MA, unsigned len, double C );

void   __vf  MDRow_addV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dVector X );
void   __vf  MDCol_addV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dVector X );
void   __vf  MDDia_addV( dPMatrix MA, unsigned len, dVector X );

void   __vf  MDRow_subV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dVector X );
void   __vf  MDCol_subV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dVector X );
void   __vf  MDDia_subV( dPMatrix MA, unsigned len, dVector X );

void   __vf  MDRow_subrC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, double C );
void   __vf  MDCol_subrC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, double C );
void   __vf  MDDia_subrC( dPMatrix MA, unsigned len, double C );

void   __vf  MDRow_subrV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dVector X );
void   __vf  MDCol_subrV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dVector X );
void   __vf  MDDia_subrV( dPMatrix MA, unsigned len, dVector X );

void   __vf  MDRow_mulC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, double C );
void   __vf  MDCol_mulC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, double C );
void   __vf  MDDia_mulC( dPMatrix MA, unsigned len, double C );

void   __vf  MDRow_mulV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dVector X );
void   __vf  MDCol_mulV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dVector X );
void   __vf  MDDia_mulV( dPMatrix MA, unsigned len, dVector X );

void   __vf  MDRow_divC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, double C );
void   __vf  MDCol_divC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, double C );
void   __vf  MDDia_divC( dPMatrix MA, unsigned len, double C );

void   __vf  MDRow_divV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dVector X );
void   __vf  MDCol_divV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dVector X );
void   __vf  MDDia_divV( dPMatrix MA, unsigned len, dVector X );

void   __vf  MDRow_divrC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, double C );
void   __vf  MDCol_divrC( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, double C );
void   __vf  MDDia_divrC( dPMatrix MA, unsigned len, double C );

void   __vf  MDRow_divrV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dVector X );
void   __vf  MDCol_divrV( dPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dVector X );
void   __vf  MDDia_divrV( dPMatrix MA, unsigned len, dVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void   __vf  MDRows_max( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
void   __vf  MDCols_max( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
double __vf  MDDia_max(  dPMatrix MA, unsigned len );
void   __vf  MDRows_min( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
void   __vf  MDCols_min( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
double __vf  MDDia_min(  dPMatrix MA, unsigned len );

void   __vf  MDRows_absmax( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
void   __vf  MDCols_absmax( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
double __vf  MDDia_absmax(  dPMatrix MA, unsigned len );
void   __vf  MDRows_absmin( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
void   __vf  MDCols_absmin( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
double __vf  MDDia_absmin(  dPMatrix MA, unsigned len );

void   __vf  MDRows_sum( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
void   __vf  MDCols_sum( dVector Y, dPMatrix MA, unsigned ht, unsigned len );
double __vf  MDDia_sum(  dPMatrix MA, unsigned len );
void   __vf  MDRows_prod(dVector Y, dPMatrix MA, unsigned ht, unsigned len );
void   __vf  MDCols_prod(dVector Y, dPMatrix MA, unsigned ht, unsigned len );
double __vf  MDDia_prod( dPMatrix MA, unsigned len );

void  __vf  MDRows_runsum( dPMatrix MA, unsigned ht, unsigned len );
void  __vf  MDCols_runsum( dPMatrix MA, unsigned ht, unsigned len );
void  __vf  MDRows_runprod( dPMatrix MA, unsigned ht, unsigned len );
void  __vf  MDCols_runprod( dPMatrix MA, unsigned ht, unsigned len );

void  __vf  MDRows_rotate( dPMatrix MA, unsigned ht, unsigned len, int pos );
void  __vf  MDCols_rotate( dPMatrix MA, unsigned ht, unsigned len, int pos );
void  __vf  MDRows_reflect( dPMatrix MA, unsigned ht, unsigned len );
void  __vf  MDCols_reflect( dPMatrix MA, unsigned ht, unsigned len );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MDRows_exchange( dPMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );
void   __vf  MDCols_exchange( dPMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );

void   __vf  MDRows_add( dPMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MDCols_add( dPMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MDRows_sub( dPMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MDCols_sub( dPMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MDRows_Cadd( dPMatrix MA, unsigned ht, unsigned len,
                           unsigned destRow, unsigned sourceRow, double C );
void   __vf  MDCols_Cadd( dPMatrix MA, unsigned ht, unsigned len,
                           unsigned destCol, unsigned sourceCol, double C );

void   __vf  MDRows_lincomb( dPMatrix MA, unsigned ht, unsigned len,
                              unsigned destRow,  double  destC,
                              unsigned srceRow,  double  srceC );
void   __vf  MDCols_lincomb( dPMatrix MA, unsigned ht, unsigned len,
                              unsigned destCol,  double  destC,
                              unsigned srceCol,  double  srceC );


/*************************  Transposing a matrix **********************/

void  __vf  MDtranspose( dPMatrix MTr, dPMatrix MA,
                          unsigned htTr, unsigned lenTr );


/************************ Matrix Arithmetics *************************/

#define MDaddM( MC, MA, MB, htA, lenA ) \
                 VD_addV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MDaddMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA );
#define MDsubM( MC, MA, MB, htA, lenA ) \
                 VD_subV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MDsubMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA );
void __vf  MDsubrMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA );
#define MDmulC( MB, MA, htA, lenA, C ) \
                 VD_mulC( MB, MA, ((ui)htA)*lenA, C )
#define MDdivC( MB, MA, htA, lenA, C ) \
                 VD_divC( MB, MA, ((ui)htA)*lenA, C )
#define MDsaddM( MC, MA, MB, htA, lenA, C ) \
                 VDs_addV( MC, MA, MB, ((ui)htA)*lenA, C )
void __vf  MDsaddMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA, double C );
#define MDssubM( MC, MA, MB, htA, lenA, C ) \
                 VDs_subV( MC, MA, MB, ((ui)htA)*lenA, C )
void __vf  MDssubMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA, double C );
void __vf  MDssubrMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA, double C );
#define MDlincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VD_lincomb( MC, MA, MB, ((ui)htA)*lenA, CA, CB )
void  __vf  MDmulV( dVector Y, dPMatrix MA, dVector X,
                    unsigned htA, unsigned lenA );
void  __vf  MDTmulV( dVector Y, dPMatrix MA, dVector X,
                     unsigned htA, unsigned lenA );
void  __vf  VDmulM( dVector Y, dVector X, dPMatrix MA,
                    unsigned htA, unsigned lenA );
void  __vf  VDmulMT( dVector Y, dVector X, dPMatrix MA,
                     unsigned htA, unsigned lenA );
void  __vf  MDmulM( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MDmulMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MDTmulM( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MDTmulMT( dPMatrix MC, dPMatrix MA, dPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MDdiamulM( dPMatrix MC, dPMatrix MADia, dPMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MDdiamulMT( dPMatrix MC, dPMatrix MADia, dPMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MDmulMdia( dPMatrix MC, dPMatrix MA, dPMatrix MBDia,
                    unsigned htA, unsigned lenA );
void  __vf  MDTmulMdia( dPMatrix MC, dPMatrix MA, dPMatrix MBDia,
                    unsigned htA, unsigned lenA );


/*************************  Linear Algebra    *****************************/

int    __vf  MDLUdecompose( dPMatrix MLU,  uVector Ind, dPMatrix MA,
                            unsigned len );

void   __vf  MDLUsolve( dVector X, dPMatrix MLU, dVector B, uVector Ind,
                        unsigned len );
void   __vf  MDLUinv( dPMatrix MInv, dPMatrix MLU, uVector Ind,
                      unsigned len );
double __vf  MDLUdet( dPMatrix MLU, unsigned len, int permut );
void   __vf  MDLUimprove( dVector X, dVector B, dPMatrix MA, dPMatrix MLU,
                          uVector Ind, unsigned len );

int    __vf  MDSVdecompose( dPMatrix MU, dPMatrix MV, dVector W, dPMatrix MA,
                           unsigned htMA, unsigned lenA );
void   __vf  MDSVsolve( dVector X, dPMatrix MU, dPMatrix MV, dVector W,
                       dVector B, unsigned htU, unsigned lenU );

          /*  functions using LUD or SVD     */
int    __vf  MDsolve( dVector X, dPMatrix MA, dVector B, unsigned len );
                  /* ret.value != 0 signals error */
int    __vf  MDinv( dPMatrix MInv, dPMatrix MA, unsigned len );
                 /* ret.value != 0 signals error */
double __vf  MDdet( dPMatrix MA, unsigned len );

int    __vf  MDsolveBySVD( dVector X, dPMatrix MA, dVector B,
                           unsigned ht, unsigned len );
              /*  sizX = lenMA,  sizB = htA.  ret.value != 0 signals failure */
int    __vf  MDsafeSolve( dVector X, dPMatrix MA, dVector B, unsigned len );
              /* ret.value 0: success via LUD; 1: success via SVD; -1: error */

       /*********  Eigenvalues and Eigenvectors  ********/

void __vf MDs_eigenvalues( dVector EigV, dPMatrix EigM, dPMatrix MA, unsigned len,
                        int CalcEigenVec );

/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf   MDlFFT( dPMatrix MY, dPMatrix MX,
                     unsigned ht, unsigned len, int dir );
void  __vf   MDlconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                          dPMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MDldeconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                            dPMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MDlfilter( dPMatrix MY, dPMatrix MX, dPMatrix MFlt,
                        unsigned ht, unsigned len );
void  __vf   MDlautocorr( dPMatrix MACorr, dPMatrix MX,
                          unsigned ht, unsigned len );
void  __vf   MDlxcorr( dPMatrix MXCorr, dPMatrix MX, dPMatrix MY,
                       unsigned ht, unsigned len );
void  __vf   MDlspectrum( dPMatrix MSpec, unsigned htSpec, unsigned lenSpec,
                          dPMatrix MX, unsigned htX, unsigned lenX,
                          dPMatrix MWin );

void  __vf   MDsFFT( dPMatrix MY, dPMatrix MX,
                     unsigned ht, unsigned len, int dir );
void  __vf   MDsconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                          dPMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MDsdeconvolve( dPMatrix MY, dPMatrix MFlt, dPMatrix MX,
                            dPMatrix MRsp, unsigned ht, unsigned len );
void  __vf   MDsfilter( dPMatrix MY, dPMatrix MX, dPMatrix MFlt,
                        unsigned ht, unsigned len );
void  __vf   MDsautocorr( dPMatrix MACorr, dPMatrix MX,
                          unsigned ht, unsigned len );
void  __vf   MDsxcorr( dPMatrix MXCorr, dPMatrix MX, dPMatrix MY,
                       unsigned ht, unsigned len );
void  __vf   MDsspectrum( dPMatrix MSpec, unsigned htSpec, unsigned lenSpec,
                          dPMatrix MX, unsigned htX, unsigned lenX,
                          dPMatrix MWin );

      /***************  Data Fitting    ******************/

void __vf VDpolyfitwW( dVector ParValues, dPMatrix Covar, unsigned deg,
                        dVector X, dVector Y, dVector InvVar, ui sizex );
void __vf VDlinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dVector InvVar, ui sizex,
                    void (*funcs)(dVector BasFuncs, double x, unsigned nfuncs) );
double __vf VDnonlinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dVector InvVar, ui sizex,
                    void (*modelfunc)(dVector YModel, dVector X, ui size),
                    void (*derivatives)(dVector dYdPari, dVector X, ui size, unsigned i) );
void __vf MDlinfit( dVector ParValues, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dPMatrix MZ, unsigned htZ, unsigned lenZ,
                    void (*funcs)(dVector BasFuncs, double x, double y, unsigned nfuncs) );
double __vf MDnonlinfit( dVector ParValues, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dPMatrix MZ, unsigned htZ, unsigned lenZ,
                    void (*modelfunc)(dMatrix MZModel, unsigned htZ, unsigned lenZ, dVector X, dVector Y ),
                    void (*derivatives)(dMatrix dZdAi, unsigned htZ, unsigned lenZ, dVector X, dVector Y, unsigned i) );
void __vf MDlinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                      dVector X, dVector Y, dPMatrix MZ, dPMatrix MInvVar, unsigned htZ, unsigned lenZ,
                      void (*funcs)(dVector BasFuncs, double x, double y, unsigned nfuncs) );
double __vf MDnonlinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                    dVector X, dVector Y, dPMatrix MZ, dPMatrix MInvVar, unsigned htZ, unsigned lenZ,
                    void (*modelfunc)(dMatrix MZModel, unsigned htZ, unsigned lenZ, dVector X, dVector Y ),
                    void (*derivatives)(dMatrix dZdAi, unsigned htZ, unsigned lenZ, dVector X, dVector Y, unsigned i) );

void __vf VDmultiLinfitwW( dVector ParValues, dPMatrix Covar, iVector ParStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(dVector BasFuncs, double x,
                              unsigned nfuncs, unsigned nexperiment) );
void __vf MDmultiLinfitwW( dVector ParValues, dPMatrix Covar,
                iVector ParStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*funcs)(dVector BasFuncs, double x, double y,
                              unsigned nfuncs, unsigned nexperiment) );
double __vf VDmultiNonlinfitwW( dVector ParValues, dPMatrix Covar,
                iVector ParStatus, unsigned npars,
                VD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(dVector YModel, dVector X, ui size,
                                  unsigned iexperiment),
                void (*derivatives)(dVector dYdPari, dVector X, ui size,
                                  unsigned ipar, unsigned iexperiment) );
double __vf MDmultiNonlinfitwW( dVector ParValues, dPMatrix Covar,
                iVector ParStatus, unsigned npars,
                MD_EXPERIMENT _VFAR *ListOfExperiments, unsigned nexperiments,
                void (*modelfunc)(dMatrix MZModel, unsigned htZ, unsigned lenZ,
                                  dVector X, dVector Y, unsigned iexperiment ),
                void (*derivatives)(dMatrix dZdAi, unsigned htZ, unsigned lenZ,
                                    dVector X, dVector Y,
                                    unsigned ipar, unsigned iexperiment) );

      /*************  Input and Output  ****************/

void __vf MDfprint( FILE _VFAR *stream, dPMatrix MA, unsigned ht,
                     unsigned len, unsigned linewidth );
void __vf MDcprint( dPMatrix MA, unsigned ht, unsigned len );
void  __vf    MDwrite( FILE _VFAR *stream, dPMatrix X, unsigned ht, unsigned len  );
void  __vf    MDread( dPMatrix X, unsigned ht, unsigned len, FILE _VFAR *stream );
#define MDstore( str, MA, ht, len ) \
                           VD_store( str, MA, ((ui)(len))*(ht) );
#define MDrecall( MA, ht, len, str) \
                           VD_recall( MA, ((ui)(len))*(ht), str);

#ifdef __cplusplus
}
#endif
#endif /* __MDSTD_H */
