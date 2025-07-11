/*
 *  setjmp.h/csetjmp
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
#ifndef _SETJMP_H_INCLUDED
#define _SETJMP_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef __COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __PPC__
 typedef unsigned int   jmp_buf[1];
#elif defined(__AXP__)
 typedef double         jmp_buf[24];
#elif defined(__MIPS__)
 typedef unsigned long  jmp_buf[26];
#elif defined(_M_IX86)
 typedef unsigned int   jmp_buf[13];
#endif

_WCRTLINK extern int    _setjmp( jmp_buf __env );
_WCRTLINK _WCNORETURN extern void   longjmp( jmp_buf __env, int __val );

#ifndef _SETJMPEX_H_INCLUDED_
 #define setjmp(__env)  _setjmp(__env)
#endif

#ifdef _M_IX86
 #ifdef _M_I86
  #pragma aux _setjmp __modify [__8087]
 #else
  #if defined(__COMPACT__) || defined(__LARGE__)
   #pragma aux _setjmp __parm __caller [__dx __eax] __modify [__8087]
  #else
   #pragma aux _setjmp __parm __caller [__eax] __modify [__8087]
  #endif
 #endif
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
