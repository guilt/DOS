/*
 *  sys/timeb.h     timeb structure used with ftime()
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
#ifndef _SYS_TIMEB_H_INCLUDED
#define _SYS_TIMEB_H_INCLUDED

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
 #ifndef _STDTIME_T_DEFINED
 #define _STDTIME_T_DEFINED
  namespace std {
    typedef signed long time_t;
  }
  typedef std::time_t __w_time_t;
 #endif
 #ifndef _TIME_T_DEFINED
 #define _TIME_T_DEFINED
  #define _TIME_T_DEFINED_
  using std::time_t;
 #endif
#else  /* __cplusplus not defined */
 #ifndef _TIME_T_DEFINED
 #define _TIME_T_DEFINED
  #define _TIME_T_DEFINED_
  typedef signed long time_t;
  typedef time_t __w_time_t;
 #endif
#endif /* __cplusplus not defined */

#pragma pack( __push, 8 )

struct timeb {
    time_t              time;           /* seconds since Jan 1, 1970 UTC */
    unsigned short      millitm;        /* milliseconds */
    short               timezone;       /* difference in minutes from UTC */
    short               dstflag;        /* nonzero if daylight savings time */
};
struct _timeb {
    time_t              time;           /* seconds since Jan 1, 1970 UTC */
    unsigned short      millitm;        /* milliseconds */
    short               timezone;       /* difference in minutes from UTC */
    short               dstflag;        /* nonzero if daylight savings time */
};

#pragma pack( __pop )

_WCRTLINK extern int ftime( struct timeb *__timeptr );
_WCRTLINK extern int _ftime( struct _timeb *__timeptr );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
