/*
 *  varargs.h   Variable argument macros (UNIX System V definition)
 *              definitions for use with variable argument lists
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
#ifndef _VARARGS_H_INCLUDED
#define _VARARGS_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef __COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifndef _STDARG_H_INCLUDED
 #include <stdarg.h>
#else
 #error stdarg.h has already been included
#endif

#ifdef __cplusplus
extern "C" {
#endif

#undef va_start

#ifdef __PPC__
 extern void *__builtin_va_start(va_list *, ...);
 #pragma intrinsic(__builtin_va_start)
 #define va_alist       void *__alist, ...
 #define va_dcl
 #define va_start(__ap) (__builtin_va_start(&__ap,__alist,0))
#elif defined(__AXP__)
 extern void *__builtin_va_start(va_list *, ...);
 #pragma intrinsic(__builtin_va_start)
 #define va_alist       void *__alist, ...
 #define va_dcl
 #define va_start(__ap) (__builtin_va_start(&__ap,__alist,0))
#elif defined(__MIPS__)
 extern void *__builtin_va_start(va_list *, ...);
 #pragma intrinsic(__builtin_va_start)
 #define va_alist       void *__alist, ...
 #define va_dcl
 #define va_start(__ap) (__builtin_va_start(&__ap,__alist,0))
#elif defined(_M_IX86)
 #define va_alist       void *__alist, ...
 #define va_dcl
 #if defined(__HUGE__) || defined(__SW_ZU)
  #define va_start(__ap)    ((__ap)=(char _WCFAR*)&__alist,(void)0)
 #else
  #define va_start(__ap)    ((__ap)=(char *)&__alist,(void)0)
 #endif
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
