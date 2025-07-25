/*
 *  mbctype.h   Multi-Byte Character functions
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
 * Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */
#ifndef _MBCTYPE_H_INCLUDED
#define _MBCTYPE_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef __COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
 #ifndef _STDSIZE_T_DEFINED
 #define _STDSIZE_T_DEFINED
  namespace std {
    typedef unsigned size_t;
  }
  typedef std::size_t __w_size_t;
 #endif
 #ifndef _SIZE_T_DEFINED
 #define _SIZE_T_DEFINED
  #define _SIZE_T_DEFINED_
  using std::size_t;
 #endif
#else  /* __cplusplus not defined */
 #ifndef _SIZE_T_DEFINED
 #define _SIZE_T_DEFINED
  #define _SIZE_T_DEFINED_
  typedef unsigned size_t;
  typedef size_t   __w_size_t;
 #endif
#endif /* __cplusplus not defined */

#ifndef NULL
#ifdef __cplusplus
 #if !defined(_M_I86) || defined(__SMALL__) || defined(__MEDIUM__)
  #define NULL 0
 #else
  #define NULL 0L
 #endif
#else
 #ifdef __RDOSDEV__
  #define NULL 0
 #else
  #define NULL ((void *)0)
 #endif
#endif
#endif

#ifndef MB_CUR_MAX
 #define MB_CUR_MAX     2
#endif
#ifndef MB_LEN_MAX
 #define MB_LEN_MAX     2
#endif

/* _setmbcp parameter defines */
#define _MB_CP_SBCS     0
#define _MB_CP_OEM      (-2)
#define _MB_CP_ANSI     (-3)

/* MB control routines */
_WCRTLINK extern int _setmbcp( int );
_WCRTLINK extern int _getmbcp( void );

/*
 * Routines applicable to all code pages.
 */
_WCRTLINK extern int    (_ismbblead)( unsigned int __ch );
_WCRTLINK extern int    _ismbbtrail( unsigned int __ch );

_WCRTLINK extern int    _ismbbalnum( unsigned int __ch );
_WCRTLINK extern int    _ismbbalpha( unsigned int __ch );
_WCRTLINK extern int    _ismbbgraph( unsigned int __ch );
_WCRTLINK extern int    _ismbbpunct( unsigned int __ch );
_WCRTLINK extern int    _ismbbprint( unsigned int __ch );

_WCRTLINK extern int    _ismbcalnum( unsigned int __ch );
_WCRTLINK extern int    _ismbcalpha( unsigned int __ch );
_WCRTLINK extern int    _ismbccntrl( unsigned int __ch );
_WCRTLINK extern int    _ismbcdigit( unsigned int __ch );
_WCRTLINK extern int    _ismbcgraph( unsigned int __ch );
_WCRTLINK extern int    _ismbclegal( unsigned int __ch );
_WCRTLINK extern int    _ismbclower( unsigned int __ch );
_WCRTLINK extern int    _ismbcprint( unsigned int __ch );
_WCRTLINK extern int    _ismbcpunct( unsigned int __ch );
_WCRTLINK extern int    _ismbcspace( unsigned int __ch );
_WCRTLINK extern int    _ismbcupper( unsigned int __ch );
_WCRTLINK extern int    _ismbcxdigit( unsigned int __ch );

/*
 * Routines specific to code page 932 (Japanese).
 */
_WCRTLINK extern int    _ismbbkalnum( unsigned int __ch );
_WCRTLINK extern int    _ismbbkalpha( unsigned int __ch );
_WCRTLINK extern int    _ismbbkana( unsigned int __ch );
_WCRTLINK extern int    _ismbbkprint( unsigned int __ch );
_WCRTLINK extern int    _ismbbkpunct( unsigned int __ch );

_WCRTLINK extern int    _ismbchira( unsigned int __ch );
_WCRTLINK extern int    _ismbckata( unsigned int __ch );
_WCRTLINK extern int    _ismbcsymbol( unsigned int __ch );
_WCRTLINK extern int    _ismbcl0( unsigned int __ch);
_WCRTLINK extern int    _ismbcl1( unsigned int __ch);
_WCRTLINK extern int    _ismbcl2( unsigned int __ch);

_WCRTLINK extern int    _ismbdalnum( unsigned int __ch );
_WCRTLINK extern int    _ismbdalpha( unsigned int __ch );
_WCRTLINK extern int    _ismbddigit( unsigned int __ch );
_WCRTLINK extern int    _ismbdgraph( unsigned int __ch );
_WCRTLINK extern int    _ismbdhira( unsigned int __ch );
_WCRTLINK extern int    _ismbdkana( unsigned int __ch );
_WCRTLINK extern int    _ismbdlower( unsigned int __ch );
_WCRTLINK extern int    _ismbdprint( unsigned int __ch );
_WCRTLINK extern int    _ismbdpunct( unsigned int __ch );
_WCRTLINK extern int    _ismbdspace( unsigned int __ch );
_WCRTLINK extern int    _ismbdupper( unsigned int __ch );
_WCRTLINK extern int    _ismbdxdigit( unsigned int __ch );

/* Global data */
#if defined(__SW_BR) || defined(_RTDLL)
 #define __MBCSIsTable __MBCSIsTable_br
 #define __IsDBCS      __IsDBCS_br
#endif
_WCRTDATA extern unsigned char _WCDATA __MBCSIsTable[257];
_WCRTDATA extern int           _WCDATA __IsDBCS;

/* Flag used in __MBCSIsTable table */
#ifndef _MB_TABLE_FLAGS_DEFINED
    #define _MB_LEAD            0x01
    #define _MB_TABLE_FLAGS_DEFINED
#endif

/* Implement small functions as macros for speed */
#ifndef __FUNCTION_DATA_ACCESS
 #ifndef _ismbblead
 #define _ismbblead(__b) ( __IsDBCS \
                        ? ( __MBCSIsTable[(unsigned char)(__b)+1] & _MB_LEAD ) \
                        : ( 0 ) )
 #endif
#endif
#ifndef _mbisblead
 #define _mbislead(__b) _ismbblead(__b)
#endif

/**
 *  define bit masks for multi-byte characters type
 **/
#define _M1ST    1      /* 漢字第 1 バイト      MBCS 1st byte */
#define _M2ND    2      /* 漢字第 2 バイト      MBCS 2nd byte */
#define _MSYMB   4      /* 1 バイト仮名文字     MBCS single-byte kana */
#define _MPUNCT  8      /* 仮名句切文字         MBCS single-byte kana punct */

/**
 * character byte types
 **/
#define _MBC_SINGLE     0       /* valid single-byte char */
#define _MBC_LEAD       1       /* MBSC 1st byte(lead byte) */
#define _MBC_TRAIL      2       /* MBSC 2nd byte(trailing byte) */
#define _MBC_ILLEGAL    (-1)    /* illegal character byte type */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
