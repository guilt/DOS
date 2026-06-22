/*  MCEstd.h

  matrix management functions:
  manipulations on matrices of data type "eComplex"
  (extended-precision complex numbers)

  Copyright (c) 1996-2000 by Martin Sander
  All Rights Reserved.
*/

#if !defined( __MATLIB_H )
   #include <MatLib.h>
#endif
#if !defined( __VCESTD_H )
   #include <VCEstd.h>
#endif

#ifdef __BORLANDC__
       /* the following ca. 550 lines are only for Borland C++,
		  as neither Visual C++ nor Optima++ support 80-bit reals */
#ifdef __cplusplus
extern "C" {
#endif

/*************   Dynamic Generation of Matrices   ************************/

ceMatrix __vf  MCE_matrix(  unsigned ht, unsigned len );
ceMatrix __vf  MCE_matrix0( unsigned ht, unsigned len );
    /*  Notice that, in the memory model HUGE,
        neither len nor ht may exceed 1637            */

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

#define MCE_Pelement( MA, ht, len, m, n ) MCEPelement( MA[0], ht, len, m, n )
                     /* returns a pointer to MA[m][n]. */
#define MCE_element( MA, ht, len, m, n ) *MCEPelement( MA[0], ht, len, m, n )
                     /* dereferenced pointer */

 /****************  Initialization  ***************************************

    To initialize all elements of a matrix with the same value,
    or to perform arithmetic operations on all elements simultaneously,
    refer to the functions of VectorLib, declared in <VCEstd.h>, <VCEmath.h>.
    In order to use the VectorLib functions, utilize the feature that
    the whole matrix occupies one contiguous area in memory: pass the
    address of the first row to the desired vector function, the size
    of the "vector" being len * ht.
    For example, initialize all elements of the matrix MA with {1.0, 0.0}
    (this is *NOT* the identity matrix)  by calling
        VCE_equ1( MA[0], len * ht );
*/

#define MCE_equ0( MA, ht, len )            VCE_equ0( MA[0], ((ui)ht)*len )
#define MCE_equ1( MA, len )                MCEequ1( MA[0], len ) /* identity matrix */
#define MCE_equm1( MA, len )               MCEequm1( MA[0], len ) /* neg. identity matrix */
#define MCE_outerprod( MA, X, Y, ht, len ) MCEouterprod( MA[0], X, Y, ht, len )
                       /* sizX=ht, sizY=len */
#define MCE_Row_equ0( MA, ht, len, iRow ) MCERow_equ0( MA[0], ht, len, iRow )
#define MCE_Col_equ0( MA, ht, len, iCol ) MCECol_equ0( MA[0], ht, len, iCol )
#define MCE_Dia_equ0( MA, len )           MCEDia_equ0( MA[0], len )
#define MCE_Row_equC( MA, ht, len, iRow, C ) \
                                        MCERow_equC( MA[0], ht, len, iRow, C )
#define MCE_Col_equC( MA, ht, len, iCol, C ) \
                                        MCECol_equC( MA[0], ht, len, iCol, C )
#define MCE_Dia_equC( MA, len, C )      MCEDia_equC( MA[0], len, C )

#define MCE_Row_equV( MA, ht, len, iRow, X ) \
                                        MCERow_equV( MA[0], ht, len, iRow, X )
#define MCE_Col_equV( MA, ht, len, iCol, X ) \
                                        MCECol_equV( MA[0], ht, len, iCol, X )
#define MCE_Dia_equV( MA, len, X )      MCEDia_equV( MA[0], len, X )

#define MCE_Trd_equM( MA, MTrd, len )    MCETrd_equM( MA[0], MTrd[0], len )
#define MCE_Trd_extract( MTrd, MA, len ) MCETrd_extract( MTrd[0], MA[0], len )

#define MCE_equM( MB, MA, ht, len )  VCE_equV( MB[0], MA[0], ((ui)(len))*(ht) )
#define MCE_neg( MB, MA, ht, len )   VCE_neg( MB[0], MA[0], ((ui)(len))*(ht) )
#define MCE_conj( MB, MA, ht, len )  VCE_conj( MB[0], MA[0], ((ui)(len))*(ht) )

#define MCE_UequL( MA, len ) MCEUequL( MA[0], len )
#define MCE_LequU( MA, len ) MCELequU( MA[0], len )
         /* copy lower-diagonal elements into upper-diagonal
           (or vice versa) by index-reflection, so as to
           get a symmetric matrix    */

            /* data-type conversions:  */
#define M_CEtoCF( MCF, MCE, ht, len ) V_CEtoCF( MCF[0], MCE[0], ((ui)ht)*len )
#define M_CFtoCE( MCE, MCF, ht, len ) V_CFtoCE( MCE[0], MCF[0], ((ui)ht)*len )
#define M_CEtoCD( MCD, MCE, ht, len ) V_CEtoCD( MCD[0], MCE[0], ((ui)ht)*len )
#define M_CDtoCE( MCE, MCD, ht, len ) V_CDtoCE( MCE[0], MCD[0], ((ui)ht)*len )

/********  Extracting a submatrix and copying a submatrix back  *********/

#define MCE_submatrix( MSub, subHt, subLen, \
                       MSrce, srceHt, srceLen, \
                       firstRowInCol, sampInCol, firstColInRow, sampInRow ) \
               MCEsubmatrix(  MSub[0], subHt, subLen, \
                              MSrce[0], srceHt, srceLen, \
                              firstRowInCol, sampInCol, firstColInRow, sampInRow )

#define MCE_submatrix_equM( MDest, destHt, destLen, \
                            firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                            MSrce, srceHt, srceLen ) \
               MCEsubmatrix_equM(  MDest[0], destHt, destLen, \
                             firstRowInCol, sampInCol, firstColInRow, sampInRow, \
                             MSrce[0], srceHt, srceLen )

/*****   Extracting a single row or a single column or the diagonal  ******
 *       and storing it into a vector                                     */

#define MCE_Row_extract( Y, MA, ht, len, iRow ) \
                                     MCERow_extract( Y, MA[0], ht, len, iRow )
#define MCE_Col_extract( Y, MA, ht, len, iCol ) \
                                     MCECol_extract( Y, MA[0], ht, len, iCol )
#define MCE_Dia_extract( Y, MA, len ) MCEDia_extract( Y, MA[0], len )


/**************  Deleting or inserting a row or a column   ***************/

#define MCE_Row_delete( MB, MA, htA, lenA, iRow ) \
                           MCERow_delete( MB[0], MA[0], htA, lenA, iRow )
#define MCE_Col_delete( MB, MA, htA, lenA, iCol ) \
                           MCECol_delete( MB[0], MA[0], htA, lenA, iCol )
#define MCE_Row_insert( MB, MA, htB, lenB, iRow, X ) \
                           MCERow_insert( MB[0], MA[0], htB, lenB, iRow, X )
#define MCE_Col_insert( MB, MA, htB, lenB, iCol, X ) \
                           MCECol_insert( MB[0], MA[0], htB, lenB, iCol, X )


/*****************    Basic arithmetic operations *********************
                      performed on one single row,
                      or one single column of any matrix,
                      or on the diagonal of a square matrix

    Note: In contrast to the analogous VectorLib functions, the operations
    are performed in-place, i.e. the input matrix itself is changed  */

#define MCE_Row_addC( MA, ht, len, iRow, C ) \
                                     MCERow_addC( MA[0], ht, len, iRow, C )
#define MCE_Col_addC( MA, ht, len, iCol, C ) \
                                     MCECol_addC( MA[0], ht, len, iCol, C )
#define MCE_Dia_addC( MA, len, C )   MCEDia_addC( MA[0], len, C )

#define MCE_Row_addV( MA, ht, len, iRow, X ) \
                                     MCERow_addV( MA[0], ht, len, iRow, X )
#define MCE_Col_addV( MA, ht, len, iCol, X ) \
                                     MCECol_addV( MA[0], ht, len, iCol, X )
#define MCE_Dia_addV( MA, len, X )   MCEDia_addV( MA[0], len, X )

#define MCE_Row_subC( MA, ht, len, iRow, C ) \
                                     MCERow_subC( MA[0], ht, len, iRow, C )
#define MCE_Col_subC( MA, ht, len, iCol, C ) \
                                     MCECol_subC( MA[0], ht, len, iCol, C )
#define MCE_Dia_subC( MA, len, C )   MCEDia_subC( MA[0], len, C )

#define MCE_Row_subV( MA, ht, len, iRow, X ) \
                                     MCERow_subV( MA[0], ht, len, iRow, X )
#define MCE_Col_subV( MA, ht, len, iCol, X ) \
                                     MCECol_subV( MA[0], ht, len, iCol, X )
#define MCE_Dia_subV( MA, len, X )   MCEDia_subV( MA[0], len, X )

#define MCE_Row_subrC( MA, ht, len, iRow, C ) \
                                     MCERow_subrC( MA[0], ht, len, iRow, C )
#define MCE_Col_subrC( MA, ht, len, iCol, C ) \
                                     MCECol_subrC( MA[0], ht, len, iCol, C )
#define MCE_Dia_subrC( MA, len, C )  MCEDia_subrC( MA[0], len, C )

#define MCE_Row_subrV( MA, ht, len, iRow, X ) \
                                     MCERow_subrV( MA[0], ht, len, iRow, X )
#define MCE_Col_subrV( MA, ht, len, iCol, X ) \
                                     MCECol_subrV( MA[0], ht, len, iCol, X )
#define MCE_Dia_subrV( MA, len, X )  MCEDia_subrV( MA[0], len, X )

#define MCE_Row_mulC( MA, ht, len, iRow, C ) \
                                     MCERow_mulC( MA[0], ht, len, iRow, C )
#define MCE_Col_mulC( MA, ht, len, iCol, C ) \
                                     MCECol_mulC( MA[0], ht, len, iCol, C )
#define MCE_Dia_mulC( MA, len, C )   MCEDia_mulC( MA[0], len, C )

#define MCE_Row_mulV( MA, ht, len, iRow, X ) \
                                     MCERow_mulV( MA[0], ht, len, iRow, X )
#define MCE_Col_mulV( MA, ht, len, iCol, X ) \
                                     MCECol_mulV( MA[0], ht, len, iCol, X )
#define MCE_Dia_mulV( MA, len, X )   MCEDia_mulV( MA[0], len, X )

#define MCE_Row_divC( MA, ht, len, iRow, C ) \
                                     MCERow_divC( MA[0], ht, len, iRow, C )
#define MCE_Col_divC( MA, ht, len, iCol, C ) \
                                     MCECol_divC( MA[0], ht, len, iCol, C )
#define MCE_Dia_divC( MA, len, C )   MCEDia_divC( MA[0], len, C )

#define MCE_Row_divV( MA, ht, len, iRow, X ) \
                                      MCERow_divV( MA[0], ht, len, iRow, X )
#define MCE_Col_divV( MA, ht, len, iCol, X ) \
                                      MCECol_divV( MA[0], ht, len, iCol, X )
#define MCE_Dia_divV( MA, len, X )    MCEDia_divV( MA[0], len, X )

#define MCE_Row_divrC( MA, ht, len, iRow, C ) \
                                      MCERow_divrC( MA[0], ht, len, iRow, C )
#define MCE_Col_divrC( MA, ht, len, iCol, C ) \
                                      MCECol_divrC( MA[0], ht, len, iCol, C )
#define MCE_Dia_divrC( MA, len, C )   MCEDia_divrC( MA[0], len, C )

#define MCE_Row_divrV( MA, ht, len, iRow, X ) \
                                      MCERow_divrV( MA[0], ht, len, iRow, X )
#define MCE_Col_divrV( MA, ht, len, iCol, X ) \
                                      MCECol_divrV( MA[0], ht, len, iCol, X )
#define MCE_Dia_divrV( MA, len, X )   MCEDia_divrV( MA[0], len, X )


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

#define MCE_Rows_absmax( Y, MA, ht, len )  MCERows_absmax( Y, MA[0], ht, len )
#define MCE_Cols_absmax( Y, MA, ht, len )  MCECols_absmax( Y, MA[0], ht, len )
#define MCE_Dia_absmax( MA, len )          MCEDia_absmax( MA[0], len )
#define MCE_Rows_absmin( Y, MA, ht, len )  MCERows_absmin( Y, MA[0], ht, len )
#define MCE_Cols_absmin( Y, MA, ht, len )  MCECols_absmin( Y, MA[0], ht, len )
#define MCE_Dia_absmin( MA, len )          MCEDia_absmin( MA[0], len )

#define MCE_Rows_maxReIm( Y, MA, ht, len ) MCERows_maxReIm( Y, MA[0], ht, len )
#define MCE_Cols_maxReIm( Y, MA, ht, len ) MCECols_maxReIm( Y, MA[0], ht, len )
#define MCE_Dia_maxReIm( MA, len )         MCEDia_maxReIm( MA[0], len )
#define MCE_Rows_minReIm( Y, MA, ht, len ) MCERows_minReIm( Y, MA[0], ht, len )
#define MCE_Cols_minReIm( Y, MA, ht, len ) MCECols_minReIm( Y, MA[0], ht, len )
#define MCE_Dia_minReIm( MA, len )         MCEDia_minReIm( MA[0], len )

#define MCE_Rows_absmaxReIm( Y, MA, ht, len ) MCERows_absmaxReIm( Y, MA[0], ht, len )
#define MCE_Cols_absmaxReIm( Y, MA, ht, len ) MCECols_absmaxReIm( Y, MA[0], ht, len )
#define MCE_Dia_absmaxReIm( MA, len )         MCEDia_absmaxReIm( MA[0], len )
#define MCE_Rows_absminReIm( Y, MA, ht, len ) MCERows_absminReIm( Y, MA[0], ht, len )
#define MCE_Cols_absminReIm( Y, MA, ht, len ) MCECols_absminReIm( Y, MA[0], ht, len )
#define MCE_Dia_absminReIm( MA, len )         MCEDia_absminReIm( MA[0], len )

#define MCE_Rows_sum( Y, MA, ht, len )     MCERows_sum( Y, MA[0], ht, len )
#define MCE_Cols_sum( Y, MA, ht, len )     MCECols_sum( Y, MA[0], ht, len )
#define MCE_Dia_sum(  MA, len )            MCEDia_sum( MA[0], len )
#define MCE_Rows_prod( Y, MA, ht, len )    MCERows_prod( Y, MA[0], ht, len )
#define MCE_Cols_prod( Y, MA, ht, len )    MCECols_prod( Y, MA[0], ht, len )
#define MCE_Dia_prod(  MA, len )           MCEDia_prod( MA[0], len )

#define MCE_Rows_runsum( MA, ht, len )     MCERows_runsum( MA[0], ht, len )
#define MCE_Cols_runsum( MA, ht, len )     MCECols_runsum( MA[0], ht, len )
#define MCE_Rows_runprod( MA, ht, len )    MCERows_runprod( MA[0], ht, len )
#define MCE_Cols_runprod( MA, ht, len )    MCECols_runprod( MA[0], ht, len )

#define MCE_Rows_rotate( MA, ht, len, pos) MCERows_rotate( MA[0], ht, len, pos )
#define MCE_Cols_rotate( MA, ht, len, pos) MCECols_rotate( MA[0], ht, len, pos )

/********  Operations involving two rows or two colums of one matrix  *****/

#define MCE_Rows_exchange( MA, ht, len, row1, row2 ) \
                             MCERows_exchange( MA[0], ht, len, row1, row2 )
#define MCE_Cols_exchange( MA, ht, len, col1, col2 ) \
                             MCECols_exchange( MA[0], ht, len, col1, col2 )

#define MCE_Rows_add( MA, ht, len, destRow, srceRow ) \
                             MCERows_add( MA[0], ht, len, destRow, srceRow )
#define MCE_Cols_add( MA, ht, len, destCol, srceCol ) \
                             MCECols_add( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] += source[i]  */

#define MCE_Rows_sub( MA, ht, len, destRow, srceRow ) \
                             MCERows_sub( MA[0], ht, len, destRow, srceRow )
#define MCE_Cols_sub( MA, ht, len, destCol, srceCol ) \
                             MCECols_sub( MA[0], ht, len, destCol, srceCol )
                         /* dest[i] -= source[i]  */

#define MCE_Rows_Cadd( MA, ht, len, destRow, srceRow, C ) \
                          MCERows_Cadd( MA[0], ht, len, destRow, srceRow, C )
#define MCE_Cols_Cadd( MA, ht, len, destCol, srceCol, C ) \
                          MCECols_Cadd( MA[0], ht, len, destCol, srceCol, C )
                         /* dest[i] += C * source[i]  */

#define MCE_Rows_lincomb( MA, ht, len, destRow, destC, srceRow, srceC ) \
            MCERows_lincomb( MA[0], ht, len, destRow, destC, srceRow, srceC )
#define MCE_Cols_lincomb( MA, ht, len, destCol, destC, srceCol, srceC ) \
            MCECols_lincomb( MA[0], ht, len, destCol, destC, srceCol, srceC )
  /*  linear combination: dest[i] = destC * dest[i] + sourceC * source[i] */


/*************************  Transposing a matrix **********************/

#define MCE_transpose( MTr, MA, htTr, lenTr ) \
             MCEtranspose( MTr[0], MA[0], htTr, lenTr )
       /*  the dimensions htTr, lenTr are those of the transposed matrix,
           not of the original!                */


/************************ Matrix Arithmetics *************************/

#define MCE_addM( MC, MA, MB, htA, lenA ) \
                 VCE_addV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MCE_addMT( MC, MA, MB, htA, lenA ) \
                 MCEaddMT( MC[0], MA[0], MB[0], htA, lenA )
#define MCE_subM( MC, MA, MB, htA, lenA ) \
                 VCE_subV( MC[0], MA[0], MB[0], ((ui)htA)*lenA )
#define MCE_subMT( MC, MA, MB, htA, lenA ) \
                 MCEsubMT( MC[0], MA[0], MB[0], htA, lenA )
#define MCE_subrMT( MC, MA, MB, htA, lenA ) \
                 MCEsubrMT( MC[0], MA[0], MB[0], htA, lenA )
#define MCE_mulC( MB, MA, htA, lenA, C ) \
                 VCE_mulC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MCE_divC( MB, MA, htA, lenA, C ) \
                 VCE_divC( MB[0], MA[0], ((ui)htA)*lenA, C )
#define MCE_mulReC( MB, MA, htA, lenA, CRe ) \
                 VCE_mulReC( MB[0], MA[0], ((ui)htA)*lenA, CRe )
#define MCE_divReC( MB, MA, htA, lenA, CRe ) \
                 VCE_divReC( MB[0], MA[0], ((ui)htA)*lenA, CRe )
#define MCE_lincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCE_lincomb( MC[0], MA[0], MB[0], ((ui)htA)*lenA, CA, CB )

#define MCE_mulV( Y, MA, X, htA, lenA ) \
                    MCEmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MA * X.  sizX=lenA, sizY=htA
                              both X and Y are column-vectors    */
#define MCE_TmulV( Y, MA, X, htA, lenA ) \
                    MCETmulV( Y, MA[0], X, htA, lenA )
                          /*  Y = MAT * X.  sizX=htA, sizY=lenA
                              both X and Y are column-vectors    */
#define VCE_mulM( Y, X, MA, htA, lenA ) \
                    VCEmulM( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MA.  sizX=htA, sizY=lenA
                             both X and Y are row-vectors.
                             Mind the prefix: VCE_ (not MCE_)    */
#define VCE_mulMT( Y, X, MA, htA, lenA ) \
                    VCEmulMT( Y, X, MA[0], htA, lenA )
                         /*  Y = X * MAT.  sizX=lenA, sizY=htA
                             both X and Y are row-vectors.   */
#define MCE_mulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCEmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MA * MB.  htB=lenA, htC=htA, lenC=lenB */
#define MCE_mulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCEmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MA * MBT.  lenB=lenA, htC=htA, lenC=htB */
#define MCE_TmulM( MC, MA, MB, htA, lenA, lenB ) \
                    MCETmulM( MC[0], MA[0], MB[0], htA, lenA, lenB )
                         /*  MC = MAT * MB.  htB=htA, htC=lenA, lenC=lenB */
#define MCE_TmulMT( MC, MA, MB, htA, lenA, htB ) \
                    MCETmulMT( MC[0], MA[0], MB[0], htA, lenA, htB )
                         /*  MC = MAT * MBT.  lenB=htA, htC=lenA, lenC=htB */
#define MCEdia_mulM(  MC, MADia, MB, htB, lenB )  MCEdiamulM(  MC[0], MADia, MB[0], htB, lenB )
#define MCEdia_mulMT( MC, MADia, MB, htB, lenB )  MCEdiamulMT( MC[0], MADia, MB[0], htB, lenB )
#define MCE_mulMdia(  MC, MA, MBDia, htA, lenA )  MCEmulMdia(  MC[0], MA[0], MBDia, htA, lenA )
#define MCE_TmulMdia( MC, MA, MBDia, htA, lenA )  MCETmulMdia( MC[0], MA[0], MBDia, htA, lenA )


/***************** Two-Dimensional Fourier-Transform Methods ************/

#define MCEl_FFT( MY, MX, ht, len, dir )     MCElFFT( MY[0], MX[0], ht, len, dir )
#define MCEl_filter( MY, MX, MFlt, ht, len ) MCElfilter( MY[0], MX[0], MFlt[0], ht, len )

#define MCEs_FFT( MY, MX, ht, len, dir )     MCEsFFT( MY[0], MX[0], ht, len, dir )
#define MCEs_filter( MY, MX, MFlt, ht, len ) MCEsfilter( MY[0], MX[0], MFlt[0], ht, len )

#if defined( __LARGE__ ) || defined( __COMPACT__ ) || defined ( __HUGE__ )
   #define MCE_FFT         MCEl_FFT
   #define MCE_filter      MCEl_filter
#else
   #define MCE_FFT         MCEs_FFT
   #define MCE_filter      MCEs_filter
#endif


/**************************  Input and Output  **************************/

#define MCE_fprint( stream, MA, ht, len, linewidth ) \
                    MCEfprint( stream, MA[0], ht, len, linewidth )
#define MCE_print( MA, ht, len )  MCEfprint( stdout, MA[0], ht, len, 80 )
#define MCE_cprint( MA, ht, len ) MCEcprint( MA[0], ht, len )
  /*  MCE_print, MCE_cprint usable only for DOS, EasyWin, and Win32 console applications! */

#define MCE_write( str, MA, ht, len )   MCEwrite( str, MA[0], ht, len )
#define MCE_read( MA, ht, len, str )    MCEread( MA[0], ht, len, str )
#define MCE_setWriteFormat              VCE_setWriteFormat
#define MCE_setWriteSeparate            VCE_setNWriteSeparate
                                   /* write and read in ascii format */
#define MCE_store( str, MA, ht, len ) \
                           VCE_store( str, MA[0], ((ui)(len))*(ht) );
#define MCE_recall( MA, ht, len, str) \
                           VCE_recall( MA[0], ((ui)(len))*(ht), str);
                                  /* store and recall in binary format */


/*************************************************************************
 * Here are now the actual declarations of the functions used internally.*
 * These declarations may change in future versions of MatrixLib!        *
 * You should not care too much about them, except in the case you need  *
 * the actual address of a run-time function (see above). Under all      *
 * "normal" circumstances, use only the names defined above in the       *
 * macro section!                                                        *
 *************************************************************************/

eComplex _VFAR * MCEPelement( cePMatrix X, unsigned ht, unsigned len,
                         unsigned m, unsigned n );
                  /* pointer is normalized in memory model HUGE */
#define MCEelement( MA, ht, len, m, n ) (*MCEPelement( MA, ht, len, m, n ))

#define MCEequ0( MA, ht, len )    VCE_equ0( MA, ((ui)ht)*len )
void   __vf  MCEequ1( cePMatrix MA, unsigned len );  /* identity matrix */
void   __vf  MCEequm1( cePMatrix MA, unsigned len );  /* neg. identity matrix */
void   __vf  MCEouterprod( cePMatrix MA, ceVector X,  ceVector Y,
                           unsigned ht, unsigned len );

void   __vf  MCERow_equ0( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow );
void   __vf  MCECol_equ0( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol );
void   __vf  MCEDia_equ0( cePMatrix MA, unsigned len );

void   __vf  MCERow_equC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eComplex C );
void   __vf  MCECol_equC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eComplex C );
void   __vf  MCEDia_equC( cePMatrix MA, unsigned len, eComplex C );

void   __vf  MCERow_equV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, ceVector X );
void   __vf  MCECol_equV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, ceVector X );
void   __vf  MCEDia_equV( cePMatrix MA, unsigned len, ceVector X );

void   __vf  MCETrd_equM( cePMatrix MA, cePMatrix MTrd, unsigned len );
void   __vf  MCETrd_extract( cePMatrix MTrd, cePMatrix MA, unsigned len );

#define MCEequM( MB, MA, ht, len )  VCE_equV( MB, MA, (ui)(ht)*(len) )
#define MCEneg( MB, MA, ht, len )   VCE_neg( MB, MA, (ui)(ht)*(len) )
#define MCEconj( MB, MA, ht, len )  VCE_conj( MB, MA, (ui)(ht)*(len) )

void   __vf  MCEUequL( cePMatrix MA, unsigned len );
void   __vf  MCELequU( cePMatrix MA, unsigned len );

/********  Extracting a submatrix and copying a submatrix back  *********/

void  __vf  MCEsubmatrix( cePMatrix MSub,
                          unsigned subHt,  unsigned subLen,
                          cePMatrix MSrce,
                          unsigned srceHt,  unsigned srceLen,
                          unsigned firstRowInCol,  unsigned sampInCol,
                          unsigned firstColInRow,  unsigned sampInRow );

void  __vf  MCEsubmatrix_equM( cePMatrix MDest,
                               unsigned destHt,     unsigned destLen,
                               unsigned firstRowInCol,  unsigned sampInCol,
                               unsigned firstColInRow,  unsigned sampInRow,
                               cePMatrix MSrce,
                               unsigned srceHt,     unsigned srceLen );


/*****   Extracting a single row or a single column or the diagonal  *****
 *       and storing it into a vector                                    */

void __vf MCERow_extract( ceVector Y, cePMatrix MA, unsigned ht, unsigned len,
                           unsigned iRow );
void __vf MCECol_extract( ceVector Y, cePMatrix MA, unsigned ht, unsigned len,
                           unsigned iCol );
void __vf MCEDia_extract( ceVector Y, cePMatrix MA, unsigned len );


/**********  Deleting or inserting a row or a column *****************/

void __vf MCERow_delete( cePMatrix MB, cePMatrix MA,
                         unsigned htA, unsigned lenA, unsigned iRow );
void __vf MCECol_delete( cePMatrix MB, cePMatrix MA,
                         unsigned htA, unsigned lenA, unsigned iCol );
void __vf MCERow_insert( cePMatrix MB, cePMatrix MA, unsigned htB,
                         unsigned lenB, unsigned iRow, ceVector X );
void __vf MCECol_insert( cePMatrix MB, cePMatrix MA, unsigned htB,
                         unsigned lenB, unsigned iCol, ceVector X );


/*****************    Basic arithmetic operations ***********************
     performed on one single row,  or one single column of any matrix,
     or on the diagonal of a square matrix                              */

void   __vf  MCERow_addC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eComplex C );
void   __vf  MCECol_addC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eComplex C );
void   __vf  MCEDia_addC( cePMatrix MA, unsigned len, eComplex C );

void   __vf  MCERow_subC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eComplex C );
void   __vf  MCECol_subC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eComplex C );
void   __vf  MCEDia_subC( cePMatrix MA, unsigned len, eComplex C );

void   __vf  MCERow_addV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, ceVector X );
void   __vf  MCECol_addV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, ceVector X );
void   __vf  MCEDia_addV( cePMatrix MA, unsigned len, ceVector X );

void   __vf  MCERow_subV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, ceVector X );
void   __vf  MCECol_subV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, ceVector X );
void   __vf  MCEDia_subV( cePMatrix MA, unsigned len, ceVector X );

void   __vf  MCERow_subrC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eComplex C );
void   __vf  MCECol_subrC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eComplex C );
void   __vf  MCEDia_subrC( cePMatrix MA, unsigned len, eComplex C );

void   __vf  MCERow_subrV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, ceVector X );
void   __vf  MCECol_subrV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, ceVector X );
void   __vf  MCEDia_subrV( cePMatrix MA, unsigned len, ceVector X );

void   __vf  MCERow_mulC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eComplex C );
void   __vf  MCECol_mulC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eComplex C );
void   __vf  MCEDia_mulC( cePMatrix MA, unsigned len, eComplex C );

void   __vf  MCERow_mulV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, ceVector X );
void   __vf  MCECol_mulV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, ceVector X );
void   __vf  MCEDia_mulV( cePMatrix MA, unsigned len, ceVector X );

void   __vf  MCERow_divC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eComplex C );
void   __vf  MCECol_divC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eComplex C );
void   __vf  MCEDia_divC( cePMatrix MA, unsigned len, eComplex C );

void   __vf  MCERow_divV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, ceVector X );
void   __vf  MCECol_divV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, ceVector X );
void   __vf  MCEDia_divV( cePMatrix MA, unsigned len, ceVector X );

void   __vf  MCERow_divrC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, eComplex C );
void   __vf  MCECol_divrC( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, eComplex C );
void   __vf  MCEDia_divrC( cePMatrix MA, unsigned len, eComplex C );

void   __vf  MCERow_divrV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iRow, ceVector X );
void   __vf  MCECol_divrV( cePMatrix MA, unsigned ht, unsigned len,
                         unsigned iCol, ceVector X );
void   __vf  MCEDia_divrV( cePMatrix MA, unsigned len, ceVector X );


/******  One-dimensional vector operations **********************
         performed along all rows or all columns simultaneously,
         or along the diagonal of a square matrix                */

void     __vf  MCERows_absmax( eVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCECols_absmax( eVector Y, cePMatrix MA, unsigned ht, unsigned len );
extended __vf  MCEDia_absmax(  cePMatrix MA, unsigned len );
void     __vf  MCERows_absmin( eVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCECols_absmin( eVector Y, cePMatrix MA, unsigned ht, unsigned len );
extended __vf  MCEDia_absmin(  cePMatrix MA, unsigned len );

void     __vf  MCERows_maxReIm( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCECols_maxReIm( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCERows_minReIm( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCECols_minReIm( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );

void     __vf  MCERows_absmaxReIm( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCECols_absmaxReIm( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCERows_absminReIm( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCECols_absminReIm( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );

void     __vf  MCERows_sum( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCECols_sum( ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCERows_prod(ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
void     __vf  MCECols_prod(ceVector Y, cePMatrix MA, unsigned ht, unsigned len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
} // the following functions cannot be extern "C", if eComplex is a class
#endif
eComplex __vf  MCEDia_maxReIm(  cePMatrix MA, unsigned len );
eComplex __vf  MCEDia_minReIm(  cePMatrix MA, unsigned len );
eComplex __vf  MCEDia_absmaxReIm(  cePMatrix MA, unsigned len );
eComplex __vf  MCEDia_absminReIm(  cePMatrix MA, unsigned len );
eComplex __vf  MCEDia_sum(  cePMatrix MA, unsigned len );
eComplex __vf  MCEDia_prod( cePMatrix MA, unsigned len );
#if defined __cplusplus && defined _CMATH_CLASSDEFS
extern "C" { 
#endif
void  __vf  MCERows_runsum( cePMatrix MA, unsigned ht, unsigned len );
void  __vf  MCECols_runsum( cePMatrix MA, unsigned ht, unsigned len );
void  __vf  MCERows_runprod( cePMatrix MA, unsigned ht, unsigned len );
void  __vf  MCECols_runprod( cePMatrix MA, unsigned ht, unsigned len );

void  __vf  MCERows_rotate( cePMatrix MA, unsigned ht, unsigned len, int pos );
void  __vf  MCECols_rotate( cePMatrix MA, unsigned ht, unsigned len, int pos );

/********  Operations involving two rows or two colums of one matrix  *****/

void   __vf  MCERows_exchange( cePMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );
void   __vf  MCECols_exchange( cePMatrix MA, unsigned ht, unsigned len,
                              unsigned i1, unsigned i2 );

void   __vf  MCERows_add( cePMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MCECols_add( cePMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MCERows_sub( cePMatrix MA, unsigned ht, unsigned len,
                          unsigned destRow, unsigned sourceRow );
void   __vf  MCECols_sub( cePMatrix MA, unsigned ht, unsigned len,
                          unsigned destCol, unsigned sourceCol );

void   __vf  MCERows_Cadd( cePMatrix MA, unsigned ht, unsigned len,
                           unsigned destRow, unsigned sourceRow, eComplex C );
void   __vf  MCECols_Cadd( cePMatrix MA, unsigned ht, unsigned len,
                           unsigned destCol, unsigned sourceCol, eComplex C );

void   __vf  MCERows_lincomb( cePMatrix MA, unsigned ht, unsigned len,
                              unsigned destRow,  eComplex  destC,
                              unsigned srceRow,  eComplex  srceC );
void   __vf  MCECols_lincomb( cePMatrix MA, unsigned ht, unsigned len,
                              unsigned destCol,  eComplex  destC,
                              unsigned srceCol,  eComplex  srceC );


/*************************  Transposing a matrix **********************/

void  __vf  MCEtranspose( cePMatrix MTr, cePMatrix MA,
                          unsigned htTr, unsigned lenTr );


/************************ Matrix Arithmetics *************************/

#define MCEaddM( MC, MA, MB, htA, lenA ) \
                 VCE_addV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MCEaddMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                     unsigned htA, unsigned lenA );
#define MCEsubM( MC, MA, MB, htA, lenA ) \
                 VCE_subV( MC, MA, MB, ((ui)htA)*lenA )
void __vf  MCEsubMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                     unsigned htA, unsigned lenA );
void __vf  MCEsubrMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                     unsigned htA, unsigned lenA );
#define MCEmulC( MB, MA, htA, lenA, C ) \
                 VCE_mulC( MB, MA, ((ui)htA)*lenA, C )
#define MCEdivC( MB, MA, htA, lenA, C ) \
                 VCE_divC( MB, MA, ((ui)htA)*lenA, C )
#define MCEmulReC( MB, MA, htA, lenA, CRe ) \
                 VCE_mulReC( MB, MA, ((ui)htA)*lenA, CRe )
#define MCEdivReC( MB, MA, htA, lenA, CRe ) \
                 VCE_divReC( MB, MA, ((ui)htA)*lenA, CRe )
#define MCElincomb( MC, MA, MB, htA, lenA, CA, CB ) \
                 VCE_lincomb( MC, MA, MB, ((ui)htA)*lenA, CA, CB )
void  __vf  MCEmulV( ceVector Y, cePMatrix MA, ceVector X,
                    unsigned htA, unsigned lenA );
void  __vf  MCETmulV( ceVector Y, cePMatrix MA, ceVector X,
                     unsigned htA, unsigned lenA );
void  __vf  VCEmulM( ceVector Y, ceVector X, cePMatrix MA,
                    unsigned htA, unsigned lenA );
void  __vf  VCEmulMT( ceVector Y, ceVector X, cePMatrix MA,
                     unsigned htA, unsigned lenA );
void  __vf  MCEmulM( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MCEmulMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MCETmulM( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    unsigned htA, unsigned lenA, unsigned lenB );
void  __vf  MCETmulMT( cePMatrix MC, cePMatrix MA, cePMatrix MB,
                    unsigned htA, unsigned lenA, unsigned htB );
void  __vf  MCEdiamulM( cePMatrix MC, cePMatrix MADia, cePMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MCEdiamulMT( cePMatrix MC, cePMatrix MADia, cePMatrix MB,
                    unsigned htB, unsigned lenB );
void  __vf  MCEmulMdia( cePMatrix MC, cePMatrix MA, cePMatrix MBDia,
                    unsigned htA, unsigned lenA );
void  __vf  MCETmulMdia( cePMatrix MC, cePMatrix MA, cePMatrix MBDia,
                    unsigned htA, unsigned lenA );

/*************  Two-Dimensional Fourier-Transform Methods *****************/

void  __vf   MCElFFT( cePMatrix MY, cePMatrix MX,
                      unsigned ht, unsigned len, int dir );
void  __vf   MCElfilter( cePMatrix MY, cePMatrix MX, cePMatrix MFlt,
                         unsigned ht, unsigned len );
void  __vf   MCEsFFT( cePMatrix MY, cePMatrix MX,
                      unsigned ht, unsigned len, int dir );
void  __vf   MCEsfilter( cePMatrix MY, cePMatrix MX, cePMatrix MFlt,
                         unsigned ht, unsigned len );

      /*************  Input and Output  ****************/

void __vf MCEfprint( FILE _VFAR *stream, cePMatrix MA, unsigned ht,
                    unsigned len, unsigned linewidth );
void __vf MCEcprint( cePMatrix MA, unsigned ht, unsigned len );
void  __vf    MCEwrite( FILE _VFAR *stream, cePMatrix X, unsigned ht, unsigned len  );
void  __vf    MCEread( cePMatrix X, unsigned ht, unsigned len, FILE _VFAR *stream );

#ifdef __cplusplus
}
#endif

#else  /*  MSVC, Optima++:  MCE_ functions are identical to MCD_ */
#define MCE_matrix     MCD_matrix
#define MCE_matrix0    MCD_matrix0
#define MCE_Pelement   MCD_Pelement 
#define MCE_element    MCD_element
#define MCE_equ1       MCD_equ1 
#define MCE_outerprod  MCD_outerprod
#define MCE_Row_equC   MCD_Row_equC
#define MCE_Col_equC   MCD_Col_equC
#define MCE_Dia_equC   MCD_Dia_equC
#define MCE_Row_equV   MCD_Row_equV
#define MCE_Col_equV   MCD_Col_equV
#define MCE_Dia_equV   MCD_Dia_equV
#define MCE_equM       MCD_equM
#define MCE_UequL      MCD_UequL
#define MCE_LequU      MCD_LequU
#define M_CEtoCF( MCF, MCE, ht, len ) V_CEtoCF( MCF[0], MCE[0], ((ui)ht)*len )
#define M_CFtoCE( MCE, MCF, ht, len ) V_CFtoCE( MCE[0], MCF[0], ((ui)ht)*len )
#define M_CEtoCD( MCD, MCE, ht, len ) V_CEtoCD( MCD[0], MCE[0], ((ui)ht)*len )
#define M_CDtoCE( MCE, MCD, ht, len ) V_CDtoCE( MCE[0], MCD[0], ((ui)ht)*len )
#define MCE_submatrix           MCD_submatrix
#define MCE_submatrix_equM      MCD_submatrix_equM
#define MCE_Row_extract         MCD_Row_extract 
#define MCE_Col_extract         MCD_Col_extract
#define MCE_Dia_extract         MCD_Dia_extract
#define MCE_Trd_equM            MCD_Trd_equM
#define MCE_Trd_extract         MCD_Trd_extract
#define MCE_Row_insert          MCD_Row_insert
#define MCE_Col_insert          MCD_Col_insert
#define MCE_Row_delete          MCD_Row_delete
#define MCE_Col_delete          MCD_Col_delete
#define MCE_Row_addC            MCD_Row_addC
#define MCE_Col_addC            MCD_Col_addC 
#define MCE_Dia_addC            MCD_Dia_addC 
#define MCE_Row_addV            MCD_Row_addV
#define MCE_Col_addV            MCD_Col_addV 
#define MCE_Dia_addV            MCD_Dia_addV
#define MCE_Row_subC            MCD_Row_subC 
#define MCE_Col_subC            MCD_Col_subC
#define MCE_Dia_subC            MCD_Dia_subC
#define MCE_Row_subV            MCD_Row_subV
#define MCE_Col_subV            MCD_Col_subV
#define MCE_Dia_subV            MCD_Dia_subV
#define MCE_Row_subrC           MCD_Row_subrC
#define MCE_Col_subrC           MCD_Col_subrC
#define MCE_Dia_subrC           MCD_Dia_subrC 
#define MCE_Row_subrV           MCD_Row_subrV 
#define MCE_Col_subrV           MCD_Col_subrV
#define MCE_Dia_subrV           MCD_Dia_subrV
#define MCE_Row_mulC            MCD_Row_mulC 
#define MCE_Col_mulC            MCD_Col_mulC
#define MCE_Dia_mulC            MCD_Dia_mulC 
#define MCE_Row_mulV            MCD_Row_mulV
#define MCE_Col_mulV            MCD_Col_mulV
#define MCE_Dia_mulV            MCD_Dia_mulV
#define MCE_Row_divC            MCD_Row_divC
#define MCE_Col_divC            MCD_Col_divC   
#define MCE_Dia_divC            MCD_Dia_divC
#define MCE_Row_divV            MCD_Row_divV
#define MCE_Col_divV            MCD_Col_divV
#define MCE_Dia_divV            MCD_Dia_divV
#define MCE_Row_divrC           MCD_Row_divrC
#define MCE_Col_divrC           MCD_Col_divrC 
#define MCE_Dia_divrC           MCD_Dia_divrC 
#define MCE_Row_divrV           MCD_Row_divrV
#define MCE_Col_divrV           MCD_Col_divrV
#define MCE_Dia_divrV           MCD_Dia_divrV
#define MCE_Rows_absmax         MCD_Rows_absmax
#define MCE_Cols_absmax         MCD_Cols_absmax  
#define MCE_Dia_absmax          MCD_Dia_absmax
#define MCE_Rows_absmin         MCD_Rows_absmin
#define MCE_Cols_absmin         MCD_Cols_absmin
#define MCE_Dia_absmin          MCD_Dia_absmin
#define MCE_Rows_maxReIm        MCD_Rows_maxReIm
#define MCE_Cols_maxReIm        MCD_Cols_maxReIm
#define MCE_Dia_maxReIm         MCD_Dia_maxReIm
#define MCE_Rows_minReIm        MCD_Rows_minReIm
#define MCE_Cols_minReIm        MCD_Cols_minReIm
#define MCE_Dia_minReIm         MCD_Dia_minReIm
#define MCE_Rows_absmaxReIm     MCD_Rows_absmaxReIm 
#define MCE_Cols_absmaxReIm     MCD_Cols_absmaxReIm
#define MCE_Dia_absmaxReIm      MCD_Dia_absmaxReIm
#define MCE_Rows_absminReIm     MCD_Rows_absminReIm
#define MCE_Cols_absminReIm     MCD_Cols_absminReIm  
#define MCE_Dia_absminReIm      MCD_Dia_absminReIm
#define MCE_Rows_sum            MCD_Rows_sum
#define MCE_Cols_sum            MCD_Cols_sum
#define MCE_Dia_sum             MCD_Dia_sum
#define MCE_Rows_prod           MCD_Rows_prod 
#define MCE_Cols_prod           MCD_Cols_prod
#define MCE_Dia_prod            MCD_Dia_prod
#define MCE_Rows_runsum         MCD_Rows_runsum
#define MCE_Cols_runsum         MCD_Cols_runsum
#define MCE_Rows_runprod        MCD_Rows_runprod
#define MCE_Cols_runprod        MCD_Cols_runprod
#define MCE_Rows_rotate         MCD_Rows_rotate
#define MCE_Cols_rotate         MCD_Cols_rotate
#define MCE_Rows_exchange       MCD_Rows_exchange
#define MCE_Cols_exchange       MCD_Cols_exchange
#define MCE_Rows_add            MCD_Rows_add
#define MCE_Cols_add            MCD_Cols_add
#define MCE_Rows_sub            MCD_Rows_sub
#define MCE_Cols_sub            MCD_Cols_sub
#define MCE_Rows_Cadd           MCD_Rows_Cadd
#define MCE_Cols_Cadd           MCD_Cols_Cadd
#define MCE_Rows_lincomb        MCD_Rows_lincomb
#define MCE_Cols_lincomb        MCD_Cols_lincomb
#define MCE_transpose           MCD_transpose
#define MCE_addM                MCD_addM
#define MCE_addMT               MCD_addMT
#define MCE_subM                MCD_subM
#define MCE_subMT               MCD_subMT
#define MCE_subrMT              MCD_subrMT
#define MCE_mulC                MCD_mulC
#define MCE_divC                MCD_divC
#define MCE_mulReC              MCD_mulReC
#define MCE_divReC              MCD_divReC
#define MCE_lincomb             MCD_lincomb
#define MCE_mulV                MCD_mulV
#define MCE_TmulV               MCD_TmulV
#define VCE_mulM                VCD_mulM
#define VCE_mulMT               VCD_mulMT
#define MCE_mulM                MCD_mulM
#define MCE_mulMT               MCD_mulMT
#define MCE_TmulM               MCD_TmulM
#define MCE_TmulMT              MCD_TmulMT
#define MCEdia_mulM             MCDdia_mulM
#define MCEdia_mulMT            MCDdia_mulMT
#define MCE_mulMdia             MCD_mulMdia
#define MCE_TmulMdia            MCD_TmulMdia
#define MCEl_FFT                MCDl_FFT
#define MCEl_filter             MCDl_filter
#define MCEs_FFT                MCDs_FFT  
#define MCEs_filter             MCDs_filter
#define MCE_FFT                 MCD_FFT 
#define MCE_filter              MCD_filter
#define MCE_fprint              MCD_fprint
#define MCE_print               MCD_print
#define MCE_cprint              MCD_cprint 
#define MCE_write               MCD_write 
#define MCE_read                MCD_read
#define MCE_setWriteFormat      VCE_setWriteFormat
#define MCE_setWriteSeparate    VCE_setNWriteSeparate
#define MCE_store               MCD_store
#define MCE_recall              MCD_recall

#endif  /*  Borland, Microsoft, Powersoft */
