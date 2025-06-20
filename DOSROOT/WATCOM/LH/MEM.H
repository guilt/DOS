/*
 *  mem.h       Memory manipulation functions
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
#ifndef _MEM_H_INCLUDED
#define _MEM_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
 #ifndef _STDPTRDIFF_T_DEFINED
 #define _STDPTRDIFF_T_DEFINED
  namespace std {
    typedef int ptrdiff_t;
  }
 #endif
 #ifndef _PTRDIFF_T_DEFINED
 #define _PTRDIFF_T_DEFINED
  #define _PTRDIFF_T_DEFINED_
  using std::ptrdiff_t;
 #endif
#else  /* __cplusplus not defined */
 #ifndef _PTRDIFF_T_DEFINED
 #define _PTRDIFF_T_DEFINED
  #define _PTRDIFF_T_DEFINED_
   typedef int ptrdiff_t;
 #endif
#endif /* __cplusplus not defined */

#ifndef _STRING_H_INCLUDED
 #include <string.h>
#endif

#endif
