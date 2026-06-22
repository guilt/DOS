/*  MCDstd.h

  matrix management functions:
  manipulations on matrices of data type "dComplex"
  (double-precision complex numbers)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#if !defined( __MATLIB_H )
   #include <MatLib.h>
#endif
#if !defined( __VCDSTD_H )
   #include <VCDstd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

cdMatrix __vf  MCD_matrix(  unsigned ht, unsigned len );
cdMatrix __vf  MCD_matrix0( unsigned ht, unsigned len );
    /*  notice that, in the memory model HUGE,
        neither len nor ht may exceed 2047                */

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
     some versions of Borland C++.                                     */

#define MCD_Pelement( MA, ht, len, m, n ) MCDPelement( MA[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MCD_element( MA, ht, len, m, n ) *MCDPelement( MA[0], ht, len, m, n )
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VCDstd.h>, <VCDmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being len * ht.
    For example, initialize all elements of the matrix MA with {1.0, 0.0}
    (this is *NOT* the identity matrix)  by calling
        VCD_equ1( MA[0], len * ht );
*/

#define MCD_equ0( MA, ht, len )            VCD_equ0( MA[0], ((ui)ht)*len )
#define MCD_equ1( MA, len )                MCDequ1( MA[0], len )  /* identity matrix */
#define MCD_equm1( MA, len )               MCDequm1( MA[0], len )  /* neg. identity matrix */
#define MCD_outerprod( MA, X, Y, ht, len ) MCDouterprod( MA[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MCD_Row_equ0( MA, ht, len, iRow ) MCDRow_equ0( MA[0], ht, len, iRow )
#define MCD_Col_equ0( MA, ht, len, iCol ) MCDCol_equ0( MA[0], ht, len, iCol )
#define MCD_Dia_equ0( MA, len )           MCDDia_equ0( MA[0], len )
#define MCD_Row_equC( MA, ht, len, iRow, C ) \
                                        MCDRow_equC( MA[0], ht, len, iRow, C )
#define MCD_Col_equC( MA, ht, len, iCol, C ) \
                                        MCDCol_equC( MA[0], ht, len, iCol, C )
#define MCD_Dia_equC( MA, len, C )       MCDDia_equC( MA[0], len, C )

#define MCD_Row_equV( MA, ht, len, iRow, X ) \
                                        MCDRow_equV( MA[0], ht, len, iRow, X )
#define MCD_Col_equV( MA, ht, len, iCol, X ) \
                                        MCDCol_equV( MA[0], ht, len, iCol, X )
#define MCD_Dia_equV( MA, len, X )      MCDDia_equV( MA[0], len, X )

#define MCD_Trd_equM( MA, MTrd, len )    MCDTrd_equM( MA[0], MTrd[0], len )
#define MCD_Trd_extract( MTrd, MA, len ) MCDTrd_extract( MTrd[0], MA[0], len )

#define MCD_equM( MB, MA, ht, len )  VCD_equV( MB[0], MA[0], ((ui)(len))*(ht) )
#define MCD_neg( MB, MA, ht, len )   VCD_neg( MB[0], MA[0], ((ui)(len))*(ht) )
#define MCD_conj( MB, MA, ht, len )  VCD_conj( MB[0], MA[0], ((ui)(len))*(ht) )

#define MCD_UequL( MA, len ) MCDUequL( MA[0], len )
#define MCD_LequU( MA, len ) MCDLequU( MA[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_CDtoCF( MCF, MCD, ht, len ) V_CDtoCF( MCF[0], MCD[0], ((ui)ht)*len )
#define M_CFtoCD( MCD, MCF, ht, len ) V_CFtoCD( MCD[0], MCF[0], ((ui)ht)*len )
#define M_CEtoCD( MCD, MCE, ht, len ) V_CEtoCD( MCD[0], MCE[0], ((ui)ht)*len )
#define M_CDtoCE( MCE, MCD, ht, len ) V_CDtoCE( MCE[0], MCD[0], ((ui)ht)*len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MCD_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MCDsubmatrix(  MSub[0], subHt, subLen, \
                              MSrce[0], srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MCD_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               MCDsubmatrix_equM(  MDest[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             MSrce[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MCD_Row_extract( Y, MA, ht, len, iRow ) \
                                     MCDRow_extract( Y, MA[0], ht, len, iRow )
#define MCD_Col_extract( Y, MA, ht, len, iCol ) \
                                     MCDCol_extract( Y, MA[0], ht, len, iCol )
#define MCD_Dia_extract( Y, MA, len ) MCDDia_extract( Y, MA[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MCD_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MCDRow_delete( MB[0], MA[0], htA, lenA, iRow )
#define MCD_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MCDCol_delete( MB[0], MA[0], htA, lenA, iCol )
#define MCD_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MCDRow_insert( MB[0], MA[0], htB, lenB, iRow, X )
#define MCD_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MCDCol_insert( MB[0], MA[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MCD_Row_addC( MA, ht, len, iRow, C ) \
                                     MCDRow_addC( MA[0], ht, len, iRow, C )
#define MCD_Col_addC( MA, ht, len, iCol, C ) \
                                     MCDCol_addC( MA[0], ht, len, iCol, C )
#define MCD_Dia_addC( MA, len, C )   MCDDia_addC( MA[0], len, C )

#define MCD_Row_addV( MA, ht, len, iRow, X ) \
                                     MCDRow_addV( MA[0], ht, len, iRow, X )
#define MCD_Col_addV( MA, ht, len, iCol, X ) \
                                     MCDCol_addV( MA[0], ht, len, iCol, X )
#define MCD_Dia_addV( MA, len, X )   MCDDia_addV( MA[0], len, X )

#define MCD_Row_subC( MA, ht, len, iRow, C ) \
                                     MCDRow_subC( MA[0], ht, len, iRow, C )
#define MCD_Col_subC( MA, ht, len, iCol, C ) \
                                     MCDCol_subC( MA[0], ht, len, iCol, C )
#define MCD_Dia_subC( MA, len, C )   MCDDia_subC( MA[0], len, C )

#define MCD_Row_subV( MA, ht, len, iRow, X ) \
                                     MCDRow_subV( MA[0], ht, len, iRow, X )
#define MCD_Col_subV( MA, ht, len, iCol, X ) \
                                     MCDCol_subV( MA[0], ht, len, iCol, X )
#define MCD_Dia_subV( MA, len, X )   MCDDia_subV( MA[0], len, X )

#define MCD_Row_subrC( MA, ht, len, iRow, C ) \
                                     MCDRow_subrC( MA[0], ht, len, iRow, C )
#define MCD_Col_subrC( MA, ht, len, iCol, C ) \
                                     MCDCol_subrC( MA[0], ht, len, iCol, C )
#define MCD_Dia_subrC( MA, len, C )  MCDDia_subrC( MA[0], len, C )

#define MCD_Row_subrV( MA, ht, len, iRow, X ) \
                                     MCDRow_subrV( MA[0], ht, len, iRow, X )
#define MCD_Col_subrV( MA, ht, len, iCol, X ) \
                                     MCDCol_subrV( MA[0], ht, len, iCol, X )
#define MCD_Dia_subrV( MA, len, X )  MCDDia_subrV( MA[0], len, X )

#define MCD_Row_mulC( MA, ht, len, iRow, C ) \
                                     MCDRow_mulC( MA[0], ht, len, iRow, C )
#define MCD_Col_mulC( MA, ht, len, iCol, C ) \
                                     MCDCol_mulC( MA[0], ht, len, iCol, C )
#define MCD_Dia_mulC( MA, len, C )   MCDDia_mulC( MA[0], len, C )

#define MCD_Row_mulV( MA, ht, len, iRow, X ) \
                                     MCDRow_mulV( MA[0], ht, len, iRow, X )
#define MCD_Col_mulV( MA, ht, len, iCol, X ) \
                                     MCDCol_mulV( MA[0], ht, len, iCol, X )
#define MCD_Dia_mulV( MA, len, X )   MCDDia_mulV( MA[0], len, X )

#define MCD_Row_divC( MA, ht, len, iRow, C ) \
                                     MCDRow_divC( MA[0], ht, len, iRow, C )
#define MCD_Col_divC( MA, ht, len, iCol, C ) \
                                     MCDCol_divC( MA[0], ht, len, iCol, C )
#define MCD_Dia_divC( MA, len, C )   MCDDia_divC( MA[0], len, C )

#define MCD_Row_divV( MA, ht, len, iRow, X ) \
                                      MCDRow_divV( MA[0], ht, len, iRow, X )
#define MCD_Col_divV( MA, ht, len, iCol, X ) \
                                      MCDCol_divV( MA[0], ht, len, iCol, X )
#define MCD_Dia_divV( MA, len, X )    MCDDia_divV( MA[0], len, X )

#define MCD_Row_divrC( MA, ht, len, iRow, C ) \
                                      MCDRow_divrC( MA[0], ht, len, iRow, C )
#define MCD_Col_divrC( MA, ht, len, iCol, C ) \
                                      MCDCol_divrC( MA[0], ht, len, iCol, C )
#define MCD_Dia_divrC( MA, len, C )   MCDDia_divrC( MA[0], len, C )

#define MCD_Row_divrV( MA, ht, len, iRow, X ) \
                                      MCDRow_divrV( MA[0], ht, len, iRow, X )
#define MCD_Col_divrV( MA, ht, len, iCol, X ) \
                                      MCDCol_divrV( MA[0], ht, len, iCol, X )
#define MCD_Dia_divrV( MA, len, X )   MCDDia_divrV( MA[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MCD_Rows_absmax( Y, MA, ht, len )  MCDRows_absmax( Y, MA[0], ht, len )
#define MCD_Cols_absmax( Y, MA, ht, len )  MCDCols_absmax( Y, MA[0], ht, len )
#define MCD_Dia_absmax( MA, len )          MCDDia_absmax( MA[0], len )
#define MCD_Rows_absmin( Y, MA, ht, len )  MCDRows_absmin( Y, MA[0], ht, len )
#define MCD_Cols_absmin( Y, MA, ht, len )  MCDCols_absmin( Y, MA[0], ht, len )
#define MCD_Dia_absmin( MA, len )          MCDDia_absmin( MA[0], len )

#define MCD_Rows_maxReIm( Y, MA, ht, len ) MCDRows_maxReIm( Y, MA[0], ht, len )
#define MCD_Cols_maxReIm( Y, MA, ht, len ) MCDCols_maxReIm( Y, MA[0], ht, len )
#define MCD_Dia_maxReIm( MA, len )         MCDDia_maxReIm( MA[0], len )
#define MCD_Rows_minReIm( Y, MA, ht, len ) MCDRows_minReIm( Y, MA[0], ht, len )
#define MCD_Cols_minReIm( Y, MA, ht, len ) MCDCols_minReIm( Y, MA[0], ht, len )
#define MCD_Dia_minReIm( MA, len )         MCDDia_minReIm( MA[0], len )

#define MCD_Rows_absmaxReIm( Y, MA, ht, len ) MCDRows_absmaxReIm( Y, MA[0], ht, len )
#define MCD_Cols_absmaxReIm( Y, MA, ht, len ) MCDCols_absmaxReIm( Y, MA[0], ht, len )
#define MCD_Dia_absmaxReIm( MA, len )         MCDDia_absmaxReIm( MA[0], len )
#define MCD_Rows_absminReIm( Y, MA, ht, len ) MCDRows_absminReIm( Y, MA[0], ht, len )
#define MCD_Cols_absminReIm( Y, MA, ht, len ) MCDCols_absminReIm( Y, MA[0], ht, len )
#define MCD_Dia_absminReIm( MA, len )         MCDDia_absminReIm( MA[0], len )

#define MCD_Rows_sum( Y, MA, ht, len )     MCDRows_sum( Y, MA[0], ht, len )
#define MCD_Cols_sum( Y, MA, ht, len )     MCDCols_sum( Y, MA[0], ht, len )
#define MCD_Dia_sum(  MA, len )            MCDDia_sum( MA[0], len )
#define MCD_Rows_prod( Y, MA, ht, len )    MCDRows_prod( Y, MA[0], ht, len )
#define MCD_Cols_prod( Y, MA, ht, len )    MCDCols_prod( Y, MA[0], ht, len )
#define MCD_Dia_prod(  MA, len )           MCDDia_prod( MA[0], len )

#define MCD_Rows_runsum( MA, ht, len )     MCDRows_runsum( MA[0], ht, len )
#define MCD_Cols_runsum( MA, ht, len )     MCDCols_runsum( MA[0], ht, len )
#define MCD_Rows_runprod( MA, ht, len )    MCDRows_runprod( MA[0], ht, len )
#define MCD_Cols_runprod( MA, ht, len )    MCDCols_runprod( MA[0], ht, len )

#define MCD_Rows_rotate( MA, ht, len, pos) MCDRows_rotate( MA[0], ht, len, pos )
#define MCD_Cols_rotate( MA, ht, len, pos) MCDCols_rotate( MA[0], ht, len, pos )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MCD_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MCDRows_exchange( MA[0], ht, len, row1, row2 )
#define MCD_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MCDCols_exchange( MA[0], ht, len, col1, col2 )

#define MCD_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MCDRows_add( MA[0], ht, len, destRow, srceRow )
#define MCD_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MCDCols_add( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MCD_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MCDRows_sub( MA[0], ht, len, destRow, srceRow )
#define MCD_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MCDCols_sub( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MCD_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MCDRows_Cadd( MA[0], ht, len, destRow, srceRow, C )
#define MCD_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MCDCols_Cadd( MA[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MCD_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MCDRows_lincomb( MA[0], ht, len, destRow, destC, srceRow, srceC )
#define MCD_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MCDCols_lincomb( MA[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*************************  Transposing a matrix **********************/

#define MCD_transpose( MTr, MA, htTr, lenTr ) \
             MCDtranspose( MTr[0], MA[0], htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */


/************************ Matrix Arithmetics *************************/

#define MCD_addM( MC, MA, MB, htA, lenA ) \
                 VCD_addV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MCD_addMT( MC, MA, MB, htA, lenA ) \
                 MCDaddMT( MC[0], MA[0], MB[0], htA, lenA )
#define MCD_subM( MC, MA, MB, htA, lenA ) \
                 VCD_subV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MCD_subMT( MC, MA, MB, htA, lenA ) \
                 MCDsubMT( MC[0], MA[0], MB[0], htA, lenA )
#define MCD_subrMT( MC, MA, MB, htA, lenA ) \
                 MCDsubrMT( MC[0], MA[0], MB[0], htA, lenA )
#define MCD_mulC( MB, MA, htA, lenA, C ) \
                 VCD_mulC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MCD_divC( MB, MA, htA, lenA, C ) \
                 VCD_divC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MCD_mulReC( MB, MA, htA, lenA, CRe ) \
                 VCD_mulReC( MB[0], MA[0], ((ui)htA)*lenA, CRe )
#define MCD_divReC( MB, MA, htA, lenA, CRe ) \
                 VCD_divReC( MB[0], MA[0], ((ui)htA)*lenA, CRe )
#define MCD_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCD_lincomb( MC[0], MA[0], MB[0], ((ui)htA)*lenA, CA, CB )

#define MCD_mulV( Y, MA, X, htA, lenA ) \
                    MCDmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MCD_TmulV( Y, MA, X, htA, lenA ) \
                    MCDTmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VCD_mulM( Y, X, MA, htA, lenA ) \
                    VCDmulM( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VCD_ (not MCD_)    */
#define VCD_mulMT( Y, X, MA, htA, lenA ) \
                    VCDmulMT( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MCD_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCDmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MCD_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCDmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MCD_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCDTmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCD_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCDTmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MCDdia_mulM(  MC, MADia, MB, htB, lenB )  MCDdiamulM(  MC[0], MADia, MB[0], htB, lenB )
#define MCDdia_mulMT( MC, MADia, MB, htB, lenB )  MCDdiamulMT( MC[0], MADia, MB[0], htB, lenB )
#define MCD_mulMdia(  MC, MA, MBDia, htA, lenA )  MCDmulMdia(  MC[0], MA[0], MBDia, htA, lenA )
#define MCD_TmulMdia( MC, MA, MBDia, htA, lenA )  MCDTmulMdia( MC[0], MA[0], MBDia, htA, lenA )


/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MCDl_FFT( MY, MX, ht, len, dir )     MCDlFFT( MY[0], MX[0], ht, len, dir )
#define MCDl_filter( MY, MX, MFlt, ht, len ) MCDlfilter( MY[0], MX[0], MFlt[0], ht, len )

#define MCDs_FFT( MY, MX, ht, len, dir )     MCDsFFT( MY[0], MX[0], ht, len, dir )
#define MCDs_filter( MY, MX, MFlt, ht, len ) MCDsfilter( MY[0], MX[0], MFlt[0], ht, len )

#if defined( __LARGE__ ) || defined( __COMPACT__ ) || defined ( __HUGE__ )
   #define MCD_FFT         MCDl_FFT
   #define MCD_filter      MCDl_filter
#else
   #define MCD_FFT         MCDs_FFT
   #define MCD_filter      MCDs_filter
#endif

/**************************  Input and Output  **************************/

#define MCD_fprint( stream, MA, ht, len, linewidth ) \
                    MCDfprint( stream, MA[0], ht, len, linewidth )
#define MCD_print( MA, ht, len )  MCDfprint( stdout, MA[0], ht, len, 80 )
#define MCD_cprint( MA, ht, len ) MCDcprint( MA[0], ht, len )
  /*  MCD_print, MCD_cprint usable only for DOS, EasyWin, and Win32 console applications! */

#define MCD_write( str, MA, ht, len )   MCDwrite( str, MA[0], ht, len )
#define MCD_read( MA, ht, len, str )    MCDread( MA[0], ht, len, str )
#define MCD_setWriteFormat              VCD_setWriteFormat
#define MCD_setWriteSeparate            VCD_setNWriteSeparate
                                   /* write and read in ascii format */
#define MCD_store( str, MA, ht, len ) \
                           VCD_store( str, MA[0], ((ui)(len))*(ht) );
#define MCD_recall( MA, ht, len, str) \
                           VCD_recall( MA[0], ((ui)(len))*(ht), str);
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

dComplex _VFAR * MCDPelement( cdPMatrix X, unsigned ht, unsigned len,
                              unsigned m, unsigned n );
                  /* pointer is normalized in memory model HUGE */
#define MCDelement( MA, ht, len, m, n ) (*MCDPelement( MA, ht, len, m, n ))

#define MCDequ0( MA, ht, len )    VCD_equ0( MA, ((ui)ht)*len )
void   __vf  MCDequ1( cdPMatrix MA, unsigned len );  /* identity matrix */
void   __vf  MCDequm1( cdPMatrix MA, unsigned len );  /* neg. identity matrix */
void   __vf  MCDouterprod( cdPMatrix MA, cdVector X,  cdVector Y,
                           unsigned ht, unsigned len );

void   __vf  MCDRow_equ0( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow );
void   __vf  MCDCol_equ0( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol );
void   __vf  MCDDia_equ0( cdPMatrix MA, unsigned len );

void   __vf  MCDRow_equC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dComplex C );
void   __vf  MCDCol_equC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dComplex C );
void   __vf  MCDDia_equC( cdPMatrix MA, unsigned len, dComplex C );

void   __vf  MCDRow_equV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cdVector X );
void   __vf  MCDCol_equV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cdVector X );
void   __vf  MCDDia_equV( cdPMatrix MA, unsigned len, cdVector X );

void   __vf  MCDTrd_equM( cdPMatrix MA, cdPMatrix MTrd, unsigned len );
void   __vf  MCDTrd_extract( cdPMatrix MTrd, cdPMatrix MA, unsigned len );

#define MCDequM( MB, MA, ht, len )  VCD_equV( MB, MA, (ui)(ht)*(len) )
#define MCDneg( MB, MA, ht, len )   VCD_neg( MB, MA, (ui)(ht)*(len) )
#define MCDconj( MB, MA, ht, len )  VCD_conj( MB, MA, (ui)(ht)*(len) )

void   __vf  MCDUequL( cdPMatrix MA, unsigned len );
void   __vf  MCDLequU( cdPMatrix MA, unsigned len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MCDsubmatrix( cdPMatrix MSub,
                          unsigned subHt,  unsigned subLen,
                          cdPMatrix MSrce,
                          unsigned srceHt,  unsigned srceLen,
                          unsigned firstRowInCol,  unsigned sampInCol,
                          unsigned firstColInRow,  unsigned sampInRow );

void  __vf  MCDsubmatrix_equM( cdPMatrix MDest,
                               unsigned destHt,     unsigned destLen,
                               unsigned firstRowInCol,  unsigned sampInCol,
                               unsigned firstColInRow,  unsigned sampInRow,
                               cdPMatrix MSrce,
                               unsigned srceHt,     unsigned srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MCDRow_extract( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len,
                           unsigned iRow );
void __vf MCDCol_extract( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len,
                           unsigned iCol );
void __vf MCDDia_extract( cdVector Y, cdPMatrix MA, unsigned len );

/**********  Deleting or inserting a row or a column *****************/

void __vf MCDRow_delete( cdPMatrix MB, cdPMatrix MA,
                         unsigned htA, unsigned lenA, unsigned iRow );
void __vf MCDCol_delete( cdPMatrix MB, cdPMatrix MA,
                         unsigned htA, unsigned lenA, unsigned iCol );
void __vf MCDRow_insert( cdPMatrix MB, cdPMatrix MA, unsigned htB,
                         unsigned lenB, unsigned iRow, cdVector X );
void __vf MCDCol_insert( cdPMatrix MB, cdPMatrix MA, unsigned htB,
                         unsigned lenB, unsigned iCol, cdVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MCDRow_addC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dComplex C );
void   __vf  MCDCol_addC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dComplex C );
void   __vf  MCDDia_addC( cdPMatrix MA, unsigned len, dComplex C );

void   __vf  MCDRow_subC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dComplex C );
void   __vf  MCDCol_subC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dComplex C );
void   __vf  MCDDia_subC( cdPMatrix MA, unsigned len, dComplex C );

void   __vf  MCDRow_addV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cdVector X );
void   __vf  MCDCol_addV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cdVector X );
void   __vf  MCDDia_addV( cdPMatrix MA, unsigned len, cdVector X );

void   __vf  MCDRow_subV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cdVector X );
void   __vf  MCDCol_subV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cdVector X );
void   __vf  MCDDia_subV( cdPMatrix MA, unsigned len, cdVector X );

void   __vf  MCDRow_subrC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dComplex C );
void   __vf  MCDCol_subrC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dComplex C );
void   __vf  MCDDia_subrC( cdPMatrix MA, unsigned len, dComplex C );

void   __vf  MCDRow_subrV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cdVector X );
void   __vf  MCDCol_subrV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cdVector X );
void   __vf  MCDDia_subrV( cdPMatrix MA, unsigned len, cdVector X );

void   __vf  MCDRow_mulC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dComplex C );
void   __vf  MCDCol_mulC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dComplex C );
void   __vf  MCDDia_mulC( cdPMatrix MA, unsigned len, dComplex C );

void   __vf  MCDRow_mulV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cdVector X );
void   __vf  MCDCol_mulV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cdVector X );
void   __vf  MCDDia_mulV( cdPMatrix MA, unsigned len, cdVector X );

void   __vf  MCDRow_divC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dComplex C );
void   __vf  MCDCol_divC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dComplex C );
void   __vf  MCDDia_divC( cdPMatrix MA, unsigned len, dComplex C );

void   __vf  MCDRow_divV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cdVector X );
void   __vf  MCDCol_divV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cdVector X );
void   __vf  MCDDia_divV( cdPMatrix MA, unsigned len, cdVector X );

void   __vf  MCDRow_divrC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, dComplex C );
void   __vf  MCDCol_divrC( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, dComplex C );
void   __vf  MCDDia_divrC( cdPMatrix MA, unsigned len, dComplex C );

void   __vf  MCDRow_divrV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cdVector X );
void   __vf  MCDCol_divrV( cdPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cdVector X );
void   __vf  MCDDia_divrV( cdPMatrix MA, unsigned len, cdVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void     __vf  MCDRows_absmax( dVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDCols_absmax( dVector Y, cdPMatrix MA, unsigned ht, unsigned len );
double   __vf  MCDDia_absmax(  cdPMatrix MA, unsigned len );
void     __vf  MCDRows_absmin( dVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDCols_absmin( dVector Y, cdPMatrix MA, unsigned ht, unsigned len );
double   __vf  MCDDia_absmin(  cdPMatrix MA, unsigned len );

void     __vf  MCDRows_maxReIm( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDCols_maxReIm( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDRows_minReIm( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDCols_minReIm( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );

void     __vf  MCDRows_absmaxReIm( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDCols_absmaxReIm( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDRows_absminReIm( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDCols_absminReIm( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );

void     __vf  MCDRows_sum( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDCols_sum( cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDRows_prod(cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCDCols_prod(cdVector Y, cdPMatrix MA, unsigned ht, unsigned len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if dComplex is a class
#endif
dComplex __vf  MCDDia_maxReIm(  cdPMatrix MA, unsigned len );
dComplex __vf  MCDDia_minReIm(  cdPMatrix MA, unsigned len );
dComplex __vf  MCDDia_absmaxReIm(  cdPMatrix MA, unsigned len );
dComplex __vf  MCDDia_absminReIm(  cdPMatrix MA, unsigned len );
dComplex __vf  MCDDia_sum(  cdPMatrix MA, unsigned len );
dComplex __vf  MCDDia_prod( cdPMatrix MA, unsigned len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif


void  __vf  MCDRows_runsum( cdPMatrix MA, unsigned ht, unsigned len );
void  __vf  MCDCols_runsum( cdPMatrix MA, unsigned ht, unsigned len );
void  __vf  MCDRows_runprod( cdPMatrix MA, unsigned ht, unsigned len );
void  __vf  MCDCols_runprod( cdPMatrix MA, unsigned ht, unsigned len );

void  __vf  MCDRows_rotate( cdPMatrix MA, unsigned ht, unsigned len, int pos );
void  __vf  MCDCols_rotate( cdPMatrix MA, unsigned ht, unsigned len, int pos );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MCDRows_exchange( cdPMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );
void   __vf  MCDCols_exchange( cdPMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );

void   __vf  MCDRows_add( cdPMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MCDCols_add( cdPMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MCDRows_sub( cdPMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MCDCols_sub( cdPMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MCDRows_Cadd( cdPMatrix MA, unsigned ht, unsigned len,
                           unsigned destRow, unsigned sourceRow, dComplex C );
void   __vf  MCDCols_Cadd( cdPMatrix MA, unsigned ht, unsigned len,
                           unsigned destCol, unsigned sourceCol, dComplex C );

void   __vf  MCDRows_lincomb( cdPMatrix MA, unsigned ht, unsigned len,
                              unsigned destRow,  dComplex  destC,
                              unsigned srceRow,  dComplex  srceC );
void   __vf  MCDCols_lincomb( cdPMatrix MA, unsigned ht, unsigned len,
                              unsigned destCol,  dComplex  destC,
                              unsigned srceCol,  dComplex  srceC );


/*************************  Transposing a matrix **********************/

void  __vf  MCDtranspose( cdPMatrix MTr, cdPMatrix MA,
                          unsigned htTr, unsigned lenTr );


/************************ Matrix Arithmetics *************************/

#define MCDaddM( MC, MA, MB, htA, lenA ) \
                 VCD_addV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MCDaddMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                     unsigned htA, unsigned lenA );
#define MCDsubM( MC, MA, MB, htA, lenA ) \
                 VCD_subV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MCDsubMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                     unsigned htA, unsigned lenA );
void __vf  MCDsubrMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                     unsigned htA, unsigned lenA );
#define MCDmulC( MB, MA, htA, lenA, C ) \
                 VCD_mulC( MB, MA, ((ui)htA)*lenA, C )
#define MCDdivC( MB, MA, htA, lenA, C ) \
                 VCD_divC( MB, MA, ((ui)htA)*lenA, C )
#define MCDmulReC( MB, MA, htA, lenA, CRe ) \
                 VCD_mulReC( MB, MA, ((ui)htA)*lenA, CRe )
#define MCDdivReC( MB, MA, htA, lenA, CRe ) \
                 VCD_divReC( MB, MA, ((ui)htA)*lenA, CRe )
#define MCDlincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCD_lincomb( MC, MA, MB, ((ui)htA)*lenA, CA, CB )
void  __vf  MCDmulV( cdVector Y, cdPMatrix MA, cdVector X,
                    unsigned htA, unsigned lenA );
void  __vf  MCDTmulV( cdVector Y, cdPMatrix MA, cdVector X,
                     unsigned htA, unsigned lenA );
void  __vf  VCDmulM( cdVector Y, cdVector X, cdPMatrix MA,
                    unsigned htA, unsigned lenA );
void  __vf  VCDmulMT( cdVector Y, cdVector X, cdPMatrix MA,
                     unsigned htA, unsigned lenA );
void  __vf  MCDmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MCDmulMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MCDTmulM( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MCDTmulMT( cdPMatrix MC, cdPMatrix MA, cdPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MCDdiamulM( cdPMatrix MC, cdPMatrix MADia, cdPMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MCDdiamulMT( cdPMatrix MC, cdPMatrix MADia, cdPMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MCDmulMdia( cdPMatrix MC, cdPMatrix MA, cdPMatrix MBDia,
                    unsigned htA, unsigned lenA );
void  __vf  MCDTmulMdia( cdPMatrix MC, cdPMatrix MA, cdPMatrix MBDia,
                    unsigned htA, unsigned lenA );


/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf   MCDlFFT( cdPMatrix MY, cdPMatrix MX,
                      unsigned ht, unsigned len, int dir );
void  __vf   MCDlfilter( cdPMatrix MY, cdPMatrix MX, cdPMatrix MFlt,
                         unsigned ht, unsigned len );
void  __vf   MCDsFFT( cdPMatrix MY, cdPMatrix MX,
                      unsigned ht, unsigned len, int dir );
void  __vf   MCDsfilter( cdPMatrix MY, cdPMatrix MX, cdPMatrix MFlt,
                         unsigned ht, unsigned len );

      /*************  Input and Output  ****************/

void __vf MCDfprint( FILE _VFAR *stream, cdPMatrix MA, unsigned ht,
                     unsigned len, unsigned linewidth );
void __vf MCDcprint( cdPMatrix MA, unsigned ht, unsigned len );
void  __vf    MCDwrite( FILE _VFAR *stream, cdPMatrix X, unsigned ht, unsigned len  );
void  __vf    MCDread( cdPMatrix X, unsigned ht, unsigned len, FILE _VFAR *stream );

#ifdef __cplusplus
}
#endif
