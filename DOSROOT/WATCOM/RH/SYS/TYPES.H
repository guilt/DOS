/*
 *  sys/types.h Defined system types
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
#ifndef _SYS_TYPES_H_INCLUDED
#define _SYS_TYPES_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef __COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack( __push, 1 )

/* 
 *  ISO C types
 */
#ifdef __cplusplus
 #ifndef _STDTIME_T_DEFINED
 #define _STDTIME_T_DEFINED
  namespace std {
    typedef unsigned long time_t;
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
  typedef unsigned long time_t;
  typedef time_t __w_time_t;
 #endif
#endif /* __cplusplus not defined */
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
/* Exact-width types. */
#ifndef _EXACT_WIDTH_INTS
 #define _EXACT_WIDTH_INTS
 typedef signed char         int8_t;
 typedef unsigned char       uint8_t;
 typedef short               int16_t;
 typedef unsigned short      uint16_t;
 typedef int                 int32_t;
 typedef unsigned int        uint32_t;
 typedef long long           int64_t;
 typedef unsigned long long  uint64_t;
#endif /* _EXACT_WIDTH_INTS */

/*
 *  POSIX 1003.1 types
 */
#ifndef _SSIZE_T_DEFINED_
 #define _SSIZE_T_DEFINED_
 typedef signed         ssize_t;
#endif
#ifndef _PID_T_DEFINED_
 #define _PID_T_DEFINED_
 typedef int            pid_t;  /* Used for process IDs & group IDs */
#endif
#ifndef _OFF_T_DEFINED_
 #define _OFF_T_DEFINED_
 typedef long long      off_t;  /* Used for file sizes, offsets     */
#endif
#ifndef _TIMER_T_DEFINED_
 #define _TIMER_T_DEFINED_
 typedef int            timer_t;
#endif
#ifndef _CLOCKID_T_DEFINED_
 #define _CLOCKID_T_DEFINED_
 typedef int            clockid_t;
#endif
#ifndef SCHED_PARAM_DEFINED
 #define SCHED_PARAM_DEFINED
 struct sched_param {
     int sched_priority;
 };
#endif /* SCHED_PARAM_DEFINED */
typedef long    suseconds_t;
#ifndef _DEV_T_DEFINED_
 #define _DEV_T_DEFINED_
 typedef int            dev_t;  /* device code (drive #) */
#endif
#ifndef _INO_T_DEFINED_
 #define _INO_T_DEFINED_
 typedef unsigned int   ino_t;  /* i-node # type */
#endif
#ifndef _MODE_T_DEFINED_
 #define _MODE_T_DEFINED_
 typedef unsigned short mode_t; /* Used for some file attributes    */
#endif
#ifndef _NLINK_T_DEFINED_
 #define _NLINK_T_DEFINED_
 typedef unsigned short nlink_t;/* Used for link counts             */
#endif
#ifndef _UID_T_DEFINED_
 #define _UID_T_DEFINED_
 typedef long           uid_t;  /* user identifier */
#endif
#ifndef _GID_T_DEFINED_
 #define _GID_T_DEFINED_
 typedef short          gid_t;  /* group identifier */
#endif
#ifndef _ID_T_DEFINED_
 #define _ID_T_DEFINED_
 typedef long           id_t;   /* Generic ID, may be uid, gid, pid */
#endif

#define major(__device)             ((int)(((__device) >> 8) & 0xFF))
#define minor(__device)             ((int)((__device) & 0xff))
#define makedev(__major,__minor)    ((dev_t)(((__major) << 8) | (__minor)))

#pragma pack( __pop )

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
