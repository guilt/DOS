/*  MCFstd.h

  matrix management functions:
  manipulations on matrices of data type "fComplex"
  (single-precision complex numbers)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#if !defined( __MATLIB_H )
   #include <MatLib.h>
#endif
#if !defined( __VCFSTD_H )
   #include <VCFstd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

cfMatrix __vf  MCF_matrix(  unsigned ht, unsigned len );
cfMatrix __vf  MCF_matrix0( unsigned ht, unsigned len );
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
     some versions of Borland C++.                                     */

#define MCF_Pelement( MA, ht, len, m, n ) MCFPelement( MA[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MCF_element( MA, ht, len, m, n ) *MCFPelement( MA[0], ht, len, m, n )
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VCFstd.h>, <VCFmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being len * ht.
    For example, initialize all elements of the matrix MA with {1.0, 0.0}
    (this is *NOT* the identity matrix)  by calling
        VCF_equ1( MA[0], len * ht );
*/

#define MCF_equ0( MA, ht, len )            VCF_equ0( MA[0], ((ui)ht)*len )
#define MCF_equ1( MA, len )                MCFequ1( MA[0], len )  /* identity matrix */
#define MCF_equm1( MA, len )               MCFequm1( MA[0], len )  /* neg. identity matrix */
#define MCF_outerprod( MA, X, Y, ht, len ) MCFouterprod( MA[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MCF_Row_equ0( MA, ht, len, iRow ) MCFRow_equ0( MA[0], ht, len, iRow )
#define MCF_Col_equ0( MA, ht, len, iCol ) MCFCol_equ0( MA[0], ht, len, iCol )
#define MCF_Dia_equ0( MA, len )           MCFDia_equ0( MA[0], len )
#define MCF_Row_equC( MA, ht, len, iRow, C ) \
                                        MCFRow_equC( MA[0], ht, len, iRow, C )
#define MCF_Col_equC( MA, ht, len, iCol, C ) \
                                        MCFCol_equC( MA[0], ht, len, iCol, C )
#define MCF_Dia_equC( MA, len, C )       MCFDia_equC( MA[0], len, C )

#define MCF_Row_equV( MA, ht, len, iRow, X ) \
                                        MCFRow_equV( MA[0], ht, len, iRow, X )
#define MCF_Col_equV( MA, ht, len, iCol, X ) \
                                        MCFCol_equV( MA[0], ht, len, iCol, X )
#define MCF_Dia_equV( MA, len, X )       MCFDia_equV( MA[0], len, X )

#define MCF_Trd_equM( MA, MTrd, len )    MCFTrd_equM( MA[0], MTrd[0], len )
#define MCF_Trd_extract( MTrd, MA, len ) MCFTrd_extract( MTrd[0], MA[0], len )

#define MCF_equM( MB, MA, ht, len )  VCF_equV( MB[0], MA[0], ((ui)(len))*(ht) )
#define MCF_neg( MB, MA, ht, len )   VCF_neg( MB[0], MA[0], ((ui)(len))*(ht) )
#define MCF_conj( MB, MA, ht, len )  VCF_conj( MB[0], MA[0], ((ui)(len))*(ht) )

#define MCF_UequL( MA, len ) MCFUequL( MA[0], len )
#define MCF_LequU( MA, len ) MCFLequU( MA[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_CEtoCF( MCF, MCE, ht, len ) V_CEtoCF( MCF[0], MCE[0], ((ui)ht)*len )
#define M_CFtoCE( MCE, MCF, ht, len ) V_CFtoCE( MCE[0], MCF[0], ((ui)ht)*len )
#define M_CDtoCF( MCF, MCD, ht, len ) V_CDtoCF( MCF[0], MCD[0], ((ui)ht)*len )
#define M_CFtoCD( MCD, MCF, ht, len ) V_CFtoCD( MCD[0], MCF[0], ((ui)ht)*len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MCF_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MCFsubmatrix(  MSub[0], subHt, subLen, \
                              MSrce[0], srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MCF_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               MCFsubmatrix_equM(  MDest[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             MSrce[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MCF_Row_extract( Y, MA, ht, len, iRow ) \
                                     MCFRow_extract( Y, MA[0], ht, len, iRow )
#define MCF_Col_extract( Y, MA, ht, len, iCol ) \
                                     MCFCol_extract( Y, MA[0], ht, len, iCol )
#define MCF_Dia_extract( Y, MA, len ) MCFDia_extract( Y, MA[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MCF_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MCFRow_delete( MB[0], MA[0], htA, lenA, iRow )
#define MCF_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MCFCol_delete( MB[0], MA[0], htA, lenA, iCol )
#define MCF_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MCFRow_insert( MB[0], MA[0], htB, lenB, iRow, X )
#define MCF_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MCFCol_insert( MB[0], MA[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MCF_Row_addC( MA, ht, len, iRow, C ) \
                                     MCFRow_addC( MA[0], ht, len, iRow, C )
#define MCF_Col_addC( MA, ht, len, iCol, C ) \
                                     MCFCol_addC( MA[0], ht, len, iCol, C )
#define MCF_Dia_addC( MA, len, C )   MCFDia_addC( MA[0], len, C )

#define MCF_Row_addV( MA, ht, len, iRow, X ) \
                                     MCFRow_addV( MA[0], ht, len, iRow, X )
#define MCF_Col_addV( MA, ht, len, iCol, X ) \
                                     MCFCol_addV( MA[0], ht, len, iCol, X )
#define MCF_Dia_addV( MA, len, X )   MCFDia_addV( MA[0], len, X )

#define MCF_Row_subC( MA, ht, len, iRow, C ) \
                                     MCFRow_subC( MA[0], ht, len, iRow, C )
#define MCF_Col_subC( MA, ht, len, iCol, C ) \
                                     MCFCol_subC( MA[0], ht, len, iCol, C )
#define MCF_Dia_subC( MA, len, C )   MCFDia_subC( MA[0], len, C )

#define MCF_Row_subV( MA, ht, len, iRow, X ) \
                                     MCFRow_subV( MA[0], ht, len, iRow, X )
#define MCF_Col_subV( MA, ht, len, iCol, X ) \
                                     MCFCol_subV( MA[0], ht, len, iCol, X )
#define MCF_Dia_subV( MA, len, X )   MCFDia_subV( MA[0], len, X )

#define MCF_Row_subrC( MA, ht, len, iRow, C ) \
                                     MCFRow_subrC( MA[0], ht, len, iRow, C )
#define MCF_Col_subrC( MA, ht, len, iCol, C ) \
                                     MCFCol_subrC( MA[0], ht, len, iCol, C )
#define MCF_Dia_subrC( MA, len, C )  MCFDia_subrC( MA[0], len, C )

#define MCF_Row_subrV( MA, ht, len, iRow, X ) \
                                     MCFRow_subrV( MA[0], ht, len, iRow, X )
#define MCF_Col_subrV( MA, ht, len, iCol, X ) \
                                     MCFCol_subrV( MA[0], ht, len, iCol, X )
#define MCF_Dia_subrV( MA, len, X )  MCFDia_subrV( MA[0], len, X )

#define MCF_Row_mulC( MA, ht, len, iRow, C ) \
                                     MCFRow_mulC( MA[0], ht, len, iRow, C )
#define MCF_Col_mulC( MA, ht, len, iCol, C ) \
                                     MCFCol_mulC( MA[0], ht, len, iCol, C )
#define MCF_Dia_mulC( MA, len, C )   MCFDia_mulC( MA[0], len, C )

#define MCF_Row_mulV( MA, ht, len, iRow, X ) \
                                     MCFRow_mulV( MA[0], ht, len, iRow, X )
#define MCF_Col_mulV( MA, ht, len, iCol, X ) \
                                     MCFCol_mulV( MA[0], ht, len, iCol, X )
#define MCF_Dia_mulV( MA, len, X )   MCFDia_mulV( MA[0], len, X )

#define MCF_Row_divC( MA, ht, len, iRow, C ) \
                                     MCFRow_divC( MA[0], ht, len, iRow, C )
#define MCF_Col_divC( MA, ht, len, iCol, C ) \
                                     MCFCol_divC( MA[0], ht, len, iCol, C )
#define MCF_Dia_divC( MA, len, C )   MCFDia_divC( MA[0], len, C )

#define MCF_Row_divV( MA, ht, len, iRow, X ) \
                                      MCFRow_divV( MA[0], ht, len, iRow, X )
#define MCF_Col_divV( MA, ht, len, iCol, X ) \
                                      MCFCol_divV( MA[0], ht, len, iCol, X )
#define MCF_Dia_divV( MA, len, X )    MCFDia_divV( MA[0], len, X )

#define MCF_Row_divrC( MA, ht, len, iRow, C ) \
                                      MCFRow_divrC( MA[0], ht, len, iRow, C )
#define MCF_Col_divrC( MA, ht, len, iCol, C ) \
                                      MCFCol_divrC( MA[0], ht, len, iCol, C )
#define MCF_Dia_divrC( MA, len, C )   MCFDia_divrC( MA[0], len, C )

#define MCF_Row_divrV( MA, ht, len, iRow, X ) \
                                      MCFRow_divrV( MA[0], ht, len, iRow, X )
#define MCF_Col_divrV( MA, ht, len, iCol, X ) \
                                      MCFCol_divrV( MA[0], ht, len, iCol, X )
#define MCF_Dia_divrV( MA, len, X )   MCFDia_divrV( MA[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MCF_Rows_absmax( Y, MA, ht, len )  MCFRows_absmax( Y, MA[0], ht, len )
#define MCF_Cols_absmax( Y, MA, ht, len )  MCFCols_absmax( Y, MA[0], ht, len )
#define MCF_Dia_absmax( MA, len )          MCFDia_absmax( MA[0], len )
#define MCF_Rows_absmin( Y, MA, ht, len )  MCFRows_absmin( Y, MA[0], ht, len )
#define MCF_Cols_absmin( Y, MA, ht, len )  MCFCols_absmin( Y, MA[0], ht, len )
#define MCF_Dia_absmin( MA, len )          MCFDia_absmin( MA[0], len )

#define MCF_Rows_maxReIm( Y, MA, ht, len ) MCFRows_maxReIm( Y, MA[0], ht, len )
#define MCF_Cols_maxReIm( Y, MA, ht, len ) MCFCols_maxReIm( Y, MA[0], ht, len )
#define MCF_Dia_maxReIm( MA, len )         MCFDia_maxReIm( MA[0], len )
#define MCF_Rows_minReIm( Y, MA, ht, len ) MCFRows_minReIm( Y, MA[0], ht, len )
#define MCF_Cols_minReIm( Y, MA, ht, len ) MCFCols_minReIm( Y, MA[0], ht, len )
#define MCF_Dia_minReIm( MA, len )         MCFDia_minReIm( MA[0], len )

#define MCF_Rows_absmaxReIm( Y, MA, ht, len ) MCFRows_absmaxReIm( Y, MA[0], ht, len )
#define MCF_Cols_absmaxReIm( Y, MA, ht, len ) MCFCols_absmaxReIm( Y, MA[0], ht, len )
#define MCF_Dia_absmaxReIm( MA, len )         MCFDia_absmaxReIm( MA[0], len )
#define MCF_Rows_absminReIm( Y, MA, ht, len ) MCFRows_absminReIm( Y, MA[0], ht, len )
#define MCF_Cols_absminReIm( Y, MA, ht, len ) MCFCols_absminReIm( Y, MA[0], ht, len )
#define MCF_Dia_absminReIm( MA, len )         MCFDia_absminReIm( MA[0], len )

#define MCF_Rows_sum( Y, MA, ht, len )     MCFRows_sum( Y, MA[0], ht, len )
#define MCF_Cols_sum( Y, MA, ht, len )     MCFCols_sum( Y, MA[0], ht, len )
#define MCF_Dia_sum(  MA, len )            MCFDia_sum( MA[0], len )
#define MCF_Rows_prod( Y, MA, ht, len )    MCFRows_prod( Y, MA[0], ht, len )
#define MCF_Cols_prod( Y, MA, ht, len )    MCFCols_prod( Y, MA[0], ht, len )
#define MCF_Dia_prod(  MA, len )           MCFDia_prod( MA[0], len )

#define MCF_Rows_runsum( MA, ht, len )     MCFRows_runsum( MA[0], ht, len )
#define MCF_Cols_runsum( MA, ht, len )     MCFCols_runsum( MA[0], ht, len )
#define MCF_Rows_runprod( MA, ht, len )    MCFRows_runprod( MA[0], ht, len )
#define MCF_Cols_runprod( MA, ht, len )    MCFCols_runprod( MA[0], ht, len )

#define MCF_Rows_rotate( MA, ht, len, pos) MCFRows_rotate( MA[0], ht, len, pos )
#define MCF_Cols_rotate( MA, ht, len, pos) MCFCols_rotate( MA[0], ht, len, pos )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MCF_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MCFRows_exchange( MA[0], ht, len, row1, row2 )
#define MCF_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MCFCols_exchange( MA[0], ht, len, col1, col2 )

#define MCF_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MCFRows_add( MA[0], ht, len, destRow, srceRow )
#define MCF_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MCFCols_add( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MCF_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MCFRows_sub( MA[0], ht, len, destRow, srceRow )
#define MCF_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MCFCols_sub( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MCF_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MCFRows_Cadd( MA[0], ht, len, destRow, srceRow, C )
#define MCF_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MCFCols_Cadd( MA[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MCF_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MCFRows_lincomb( MA[0], ht, len, destRow, destC, srceRow, srceC )
#define MCF_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MCFCols_lincomb( MA[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*************************  Transposing a matrix **********************/

#define MCF_transpose( MTr, MA, htTr, lenTr ) \
             MCFtranspose( MTr[0], MA[0], htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */


/************************ Matrix Arithmetics *************************/

#define MCF_addM( MC, MA, MB, htA, lenA ) \
                 VCF_addV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MCF_addMT( MC, MA, MB, htA, lenA ) \
                 MCFaddMT( MC[0], MA[0], MB[0], htA, lenA )
#define MCF_subM( MC, MA, MB, htA, lenA ) \
                 VCF_subV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MCF_subMT( MC, MA, MB, htA, lenA ) \
                 MCFsubMT( MC[0], MA[0], MB[0], htA, lenA )
#define MCF_subrMT( MC, MA, MB, htA, lenA ) \
                 MCFsubrMT( MC[0], MA[0], MB[0], htA, lenA )
#define MCF_mulC( MB, MA, htA, lenA, C ) \
                 VCF_mulC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MCF_divC( MB, MA, htA, lenA, C ) \
                 VCF_divC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MCF_mulReC( MB, MA, htA, lenA, CRe ) \
                 VCF_mulReC( MB[0], MA[0], ((ui)htA)*lenA, CRe )
#define MCF_divReC( MB, MA, htA, lenA, CRe ) \
                 VCF_divReC( MB[0], MA[0], ((ui)htA)*lenA, CRe )
#define MCF_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCF_lincomb( MC[0], MA[0], MB[0], ((ui)htA)*lenA, CA, CB )

#define MCF_mulV( Y, MA, X, htA, lenA ) \
                    MCFmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MCF_TmulV( Y, MA, X, htA, lenA ) \
                    MCFTmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VCF_mulM( Y, X, MA, htA, lenA ) \
                    VCFmulM( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VCF_ (not MCF_)    */
#define VCF_mulMT( Y, X, MA, htA, lenA ) \
                    VCFmulMT( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MCF_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCFmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MCF_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCFmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MCF_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCFTmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCF_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCFTmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MCFdia_mulM(  MC, MADia, MB, htB, lenB )  MCFdiamulM(  MC[0], MADia, MB[0], htB, lenB )
#define MCFdia_mulMT( MC, MADia, MB, htB, lenB )  MCFdiamulMT( MC[0], MADia, MB[0], htB, lenB )
#define MCF_mulMdia(  MC, MA, MBDia, htA, lenA )  MCFmulMdia(  MC[0], MA[0], MBDia, htA, lenA )
#define MCF_TmulMdia( MC, MA, MBDia, htA, lenA )  MCFTmulMdia( MC[0], MA[0], MBDia, htA, lenA )


/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MCFl_FFT( MY, MX, ht, len, dir )     MCFlFFT( MY[0], MX[0], ht, len, dir )
#define MCFl_filter( MY, MX, MFlt, ht, len ) MCFlfilter( MY[0], MX[0], MFlt[0], ht, len )

#define MCFs_FFT( MY, MX, ht, len, dir )     MCFsFFT( MY[0], MX[0], ht, len, dir )
#define MCFs_filter( MY, MX, MFlt, ht, len ) MCFsfilter( MY[0], MX[0], MFlt[0], ht, len )

#if defined( __LARGE__ ) || defined( __COMPACT__ ) || defined ( __HUGE__ )
   #define MCF_FFT         MCFl_FFT
   #define MCF_filter      MCFl_filter
#else
   #define MCF_FFT         MCFs_FFT
   #define MCF_filter      MCFs_filter
#endif

/**************************  Input and Output  **************************/

#define MCF_fprint( stream, MA, ht, len, linewidth ) \
                    MCFfprint( stream, MA[0], ht, len, linewidth )
#define MCF_print( MA, ht, len )  MCFfprint( stdout, MA[0], ht, len, 80 )
#define MCF_cprint( MA, ht, len ) MCFcprint( MA[0], ht, len )
  /*  MCF_print, MCF_cprint usable only for DOS, EasyWin, and Win32 console applications! */

#define MCF_write( str, MA, ht, len )   MCFwrite( str, MA[0], ht, len )
#define MCF_read( MA, ht, len, str )    MCFread( MA[0], ht, len, str )
#define MCF_setWriteFormat              VCF_setWriteFormat
#define MCF_setWriteSeparate            VCF_setNWriteSeparate
                                   /* write and read in ascii format */
#define MCF_store( str, MA, ht, len ) \
                           VCF_store( str, MA[0], ((ui)(len))*(ht) );
#define MCF_recall( MA, ht, len, str) \
                           VCF_recall( MA[0], ((ui)(len))*(ht), str);
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

fComplex _VFAR * MCFPelement( cfPMatrix X, unsigned ht, unsigned len,
                              unsigned m, unsigned n );
                  /* pointer is normalized in memory model HUGE */
#define MCFelement( MA, ht, len, m, n ) (*MCFPelement( MA, ht, len, m, n ))

#define MCFequ0( MA, ht, len )    VCF_equ0( MA, ((ui)ht)*len )
void   __vf  MCFequ1( cfPMatrix MA, unsigned len );  /* identity matrix */
void   __vf  MCFequm1( cfPMatrix MA, unsigned len );  /* neg. identity matrix */
void   __vf  MCFouterprod( cfPMatrix MA, cfVector X,  cfVector Y,
                           unsigned ht, unsigned len );

void   __vf  MCFRow_equ0( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow );
void   __vf  MCFCol_equ0( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol );
void   __vf  MCFDia_equ0( cfPMatrix MA, unsigned len );

void   __vf  MCFRow_equC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fComplex C );
void   __vf  MCFCol_equC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fComplex C );
void   __vf  MCFDia_equC( cfPMatrix MA, unsigned len, fComplex C );

void   __vf  MCFRow_equV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cfVector X );
void   __vf  MCFCol_equV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cfVector X );
void   __vf  MCFDia_equV( cfPMatrix MA, unsigned len, cfVector X );

void   __vf  MCFTrd_equM( cfPMatrix MA, cfPMatrix MTrd, unsigned len );
void   __vf  MCFTrd_extract( cfPMatrix MTrd, cfPMatrix MA, unsigned len );

#define MCFequM( MB, MA, ht, len )  VCF_equV( MB, MA, (ui)(ht)*(len) )
#define MCFneg( MB, MA, ht, len )   VCF_neg( MB, MA, (ui)(ht)*(len) )
#define MCFconj( MB, MA, ht, len )  VCF_conj( MB, MA, (ui)(ht)*(len) )

void   __vf  MCFUequL( cfPMatrix MA, unsigned len );
void   __vf  MCFLequU( cfPMatrix MA, unsigned len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MCFsubmatrix( cfPMatrix MSub,
                          unsigned subHt,  unsigned subLen,
                          cfPMatrix MSrce,
                          unsigned srceHt,  unsigned srceLen,
                          unsigned firstRowInCol,  unsigned sampInCol,
                          unsigned firstColInRow,  unsigned sampInRow );

void  __vf  MCFsubmatrix_equM( cfPMatrix MDest,
                               unsigned destHt,     unsigned destLen,
                               unsigned firstRowInCol,  unsigned sampInCol,
                               unsigned firstColInRow,  unsigned sampInRow,
                               cfPMatrix MSrce,
                               unsigned srceHt,     unsigned srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MCFRow_extract( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len,
                           unsigned iRow );
void __vf MCFCol_extract( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len,
                           unsigned iCol );
void __vf MCFDia_extract( cfVector Y, cfPMatrix MA, unsigned len );

/**********  Deleting or inserting a row or a column *****************/

void __vf MCFRow_delete( cfPMatrix MB, cfPMatrix MA,
                         unsigned htA, unsigned lenA, unsigned iRow );
void __vf MCFCol_delete( cfPMatrix MB, cfPMatrix MA,
                         unsigned htA, unsigned lenA, unsigned iCol );
void __vf MCFRow_insert( cfPMatrix MB, cfPMatrix MA, unsigned htB,
                         unsigned lenB, unsigned iRow, cfVector X );
void __vf MCFCol_insert( cfPMatrix MB, cfPMatrix MA, unsigned htB,
                         unsigned lenB, unsigned iCol, cfVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MCFRow_addC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fComplex C );
void   __vf  MCFCol_addC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fComplex C );
void   __vf  MCFDia_addC( cfPMatrix MA, unsigned len, fComplex C );

void   __vf  MCFRow_subC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fComplex C );
void   __vf  MCFCol_subC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fComplex C );
void   __vf  MCFDia_subC( cfPMatrix MA, unsigned len, fComplex C );

void   __vf  MCFRow_addV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cfVector X );
void   __vf  MCFCol_addV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cfVector X );
void   __vf  MCFDia_addV( cfPMatrix MA, unsigned len, cfVector X );

void   __vf  MCFRow_subV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cfVector X );
void   __vf  MCFCol_subV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cfVector X );
void   __vf  MCFDia_subV( cfPMatrix MA, unsigned len, cfVector X );

void   __vf  MCFRow_subrC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fComplex C );
void   __vf  MCFCol_subrC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fComplex C );
void   __vf  MCFDia_subrC( cfPMatrix MA, unsigned len, fComplex C );

void   __vf  MCFRow_subrV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cfVector X );
void   __vf  MCFCol_subrV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cfVector X );
void   __vf  MCFDia_subrV( cfPMatrix MA, unsigned len, cfVector X );

void   __vf  MCFRow_mulC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fComplex C );
void   __vf  MCFCol_mulC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fComplex C );
void   __vf  MCFDia_mulC( cfPMatrix MA, unsigned len, fComplex C );

void   __vf  MCFRow_mulV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cfVector X );
void   __vf  MCFCol_mulV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cfVector X );
void   __vf  MCFDia_mulV( cfPMatrix MA, unsigned len, cfVector X );

void   __vf  MCFRow_divC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fComplex C );
void   __vf  MCFCol_divC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fComplex C );
void   __vf  MCFDia_divC( cfPMatrix MA, unsigned len, fComplex C );

void   __vf  MCFRow_divV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cfVector X );
void   __vf  MCFCol_divV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cfVector X );
void   __vf  MCFDia_divV( cfPMatrix MA, unsigned len, cfVector X );

void   __vf  MCFRow_divrC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, fComplex C );
void   __vf  MCFCol_divrC( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, fComplex C );
void   __vf  MCFDia_divrC( cfPMatrix MA, unsigned len, fComplex C );

void   __vf  MCFRow_divrV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, cfVector X );
void   __vf  MCFCol_divrV( cfPMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, cfVector X );
void   __vf  MCFDia_divrV( cfPMatrix MA, unsigned len, cfVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void     __vf  MCFRows_absmax( fVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFCols_absmax( fVector Y, cfPMatrix MA, unsigned ht, unsigned len );
float    __vf  MCFDia_absmax(  cfPMatrix MA, unsigned len );
void     __vf  MCFRows_absmin( fVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFCols_absmin( fVector Y, cfPMatrix MA, unsigned ht, unsigned len );
float    __vf  MCFDia_absmin(  cfPMatrix MA, unsigned len );

void     __vf  MCFRows_maxReIm( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFCols_maxReIm( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFRows_minReIm( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFCols_minReIm( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );

void     __vf  MCFRows_absmaxReIm( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFCols_absmaxReIm( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFRows_absminReIm( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFCols_absminReIm( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );

void     __vf  MCFRows_sum( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFCols_sum( cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFRows_prod(cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
void     __vf  MCFCols_prod(cfVector Y, cfPMatrix MA, unsigned ht, unsigned len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if fComplex is a class
#endif
fComplex __vf  MCFDia_maxReIm(  cfPMatrix MA, unsigned len );
fComplex __vf  MCFDia_minReIm(  cfPMatrix MA, unsigned len );
fComplex __vf  MCFDia_absmaxReIm(  cfPMatrix MA, unsigned len );
fComplex __vf  MCFDia_absminReIm(  cfPMatrix MA, unsigned len );
fComplex __vf  MCFDia_sum(  cfPMatrix MA, unsigned len );
fComplex __vf  MCFDia_prod( cfPMatrix MA, unsigned len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" {
#endif


void  __vf  MCFRows_runsum( cfPMatrix MA, unsigned ht, unsigned len );
void  __vf  MCFCols_runsum( cfPMatrix MA, unsigned ht, unsigned len );
void  __vf  MCFRows_runprod( cfPMatrix MA, unsigned ht, unsigned len );
void  __vf  MCFCols_runprod( cfPMatrix MA, unsigned ht, unsigned len );

void  __vf  MCFRows_rotate( cfPMatrix MA, unsigned ht, unsigned len, int pos );
void  __vf  MCFCols_rotate( cfPMatrix MA, unsigned ht, unsigned len, int pos );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MCFRows_exchange( cfPMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );
void   __vf  MCFCols_exchange( cfPMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );

void   __vf  MCFRows_add( cfPMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MCFCols_add( cfPMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MCFRows_sub( cfPMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MCFCols_sub( cfPMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MCFRows_Cadd( cfPMatrix MA, unsigned ht, unsigned len,
                           unsigned destRow, unsigned sourceRow, fComplex C );
void   __vf  MCFCols_Cadd( cfPMatrix MA, unsigned ht, unsigned len,
                           unsigned destCol, unsigned sourceCol, fComplex C );

void   __vf  MCFRows_lincomb( cfPMatrix MA, unsigned ht, unsigned len,
                              unsigned destRow,  fComplex  destC,
                              unsigned srceRow,  fComplex  srceC );
void   __vf  MCFCols_lincomb( cfPMatrix MA, unsigned ht, unsigned len,
                              unsigned destCol,  fComplex  destC,
                              unsigned srceCol,  fComplex  srceC );


/*************************  Transposing a matrix **********************/

void  __vf  MCFtranspose( cfPMatrix MTr, cfPMatrix MA,
                          unsigned htTr, unsigned lenTr );


/************************ Matrix Arithmetics *************************/

#define MCFaddM( MC, MA, MB, htA, lenA ) \
                 VCF_addV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MCFaddMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                     unsigned htA, unsigned lenA );
#define MCFsubM( MC, MA, MB, htA, lenA ) \
                 VCF_subV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MCFsubMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                     unsigned htA, unsigned lenA );
void __vf  MCFsubrMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                     unsigned htA, unsigned lenA );
#define MCFmulC( MB, MA, htA, lenA, C ) \
                 VCF_mulC( MB, MA, ((ui)htA)*lenA, C )
#define MCFdivC( MB, MA, htA, lenA, C ) \
                 VCF_divC( MB, MA, ((ui)htA)*lenA, C )
#define MCFmulReC( MB, MA, htA, lenA, CRe ) \
                 VCF_mulReC( MB, MA, ((ui)htA)*lenA, CRe )
#define MCFdivReC( MB, MA, htA, lenA, CRe ) \
                 VCF_divReC( MB, MA, ((ui)htA)*lenA, CRe )
#define MCFlincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCF_lincomb( MC, MA, MB, ((ui)htA)*lenA, CA, CB )
void  __vf  MCFmulV( cfVector Y, cfPMatrix MA, cfVector X,
                    unsigned htA, unsigned lenA );
void  __vf  MCFTmulV( cfVector Y, cfPMatrix MA, cfVector X,
                     unsigned htA, unsigned lenA );
void  __vf  VCFmulM( cfVector Y, cfVector X, cfPMatrix MA,
                    unsigned htA, unsigned lenA );
void  __vf  VCFmulMT( cfVector Y, cfVector X, cfPMatrix MA,
                     unsigned htA, unsigned lenA );
void  __vf  MCFmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MCFmulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MCFTmulM( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MCFTmulMT( cfPMatrix MC, cfPMatrix MA, cfPMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MCFdiamulM( cfPMatrix MC, cfPMatrix MADia, cfPMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MCFdiamulMT( cfPMatrix MC, cfPMatrix MADia, cfPMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MCFmulMdia( cfPMatrix MC, cfPMatrix MA, cfPMatrix MBDia,
                    unsigned htA, unsigned lenA );
void  __vf  MCFTmulMdia( cfPMatrix MC, cfPMatrix MA, cfPMatrix MBDia,
                    unsigned htA, unsigned lenA );


/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf   MCFlFFT( cfPMatrix MY, cfPMatrix MX,
                      unsigned ht, unsigned len, int dir );
void  __vf   MCFlfilter( cfPMatrix MY, cfPMatrix MX, cfPMatrix MFlt,
                         unsigned ht, unsigned len );
void  __vf   MCFsFFT( cfPMatrix MY, cfPMatrix MX,
                      unsigned ht, unsigned len, int dir );
void  __vf   MCFsfilter( cfPMatrix MY, cfPMatrix MX, cfPMatrix MFlt,
                         unsigned ht, unsigned len );

      /*************  Input and Output  ****************/

void __vf MCFfprint( FILE _VFAR *stream, cfPMatrix MA, unsigned ht,
                     unsigned len, unsigned linewidth );
void __vf MCFcprint( cfPMatrix MA, unsigned ht, unsigned len );
void  __vf    MCFwrite( FILE _VFAR *stream, cfPMatrix X, unsigned ht, unsigned len  );
void  __vf    MCFread( cfPMatrix X, unsigned ht, unsigned len, FILE _VFAR *stream );

#ifdef __cplusplus
}
#endif
