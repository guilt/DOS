/*
 *  _comdef.h   Common Macro Definitions
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
#ifndef __COMDEF_H_INCLUDED
#define __COMDEF_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

 #ifdef _WCDATA
  #error The macro _WCDATA is reserved for use by the runtime library.
 #endif
 #ifdef _WCNEAR
  #error The macro _WCNEAR is reserved for use by the runtime library.
 #endif
 #ifdef _WCFAR
  #error The macro _WCFAR is reserved for use by the runtime library.
 #endif
 #ifdef _WCHUGE
  #error The macro _WCHUGE is reserved for use by the runtime library.
 #endif
 #ifdef _WCI86NEAR
  #error The macro _WCI86NEAR is reserved for use by the runtime library.
 #endif
 #ifdef _WCI86FAR
  #error The macro _WCI86FAR is reserved for use by the runtime library.
 #endif
 #ifdef _WCI86HUGE
  #error The macro _WCI86HUGE is reserved for use by the runtime library.
 #endif
 #ifdef _WCINTERRUPT
  #error The macro _WCINTERRUPT is reserved for use by the runtime library.
 #endif
 #ifdef _WCUNALIGNED
  #error The macro _WCUNALIGNED is reserved for use by the runtime library.
 #endif
 #ifdef _WCNORETURN
  #error The macro _WCNORETURN is reserved for use by the runtime library.
 #endif
 #ifdef _WCCALLBACK
  #error The macro _WCCALLBACK is reserved for use by the runtime library.
 #endif
 #ifdef _WCHANDLER
  #error The macro _WCHANDLER is reserved for use by the runtime library.
 #endif
 #define _WRTLFCONV __declspec(__watcall)
 #define _WRTLDCONV __declspec(__watcall)
  #define _WCCALLBACK __watcall
  #define _WCNORETURN __declspec(aborts)
  #define _WCNEAR __near
  #define _WCFAR __far
  #define _WCHUGE __huge
  #define _WCINTERRUPT __interrupt
  #define _WCUNALIGNED
  #define _WCI86NEAR
  #define _WCI86FAR
  #define _WCI86HUGE
 #if defined(__SW_ND) || defined(__FUNCTION_DATA_ACCESS)
  #define _WCDATA
 #else
  #define _WCDATA _WCNEAR
 #endif
 #ifdef __SW_BR
   #define _WCRTLINK _WRTLFCONV
   #define _WCRTDATA _WRTLDCONV
   #define _WMRTLINK _WRTLFCONV
   #define _WMRTDATA _WRTLDCONV
   #define _WPRTLINK _WRTLFCONV
   #define _WPRTDATA _WRTLDCONV
   #define _WCHANDLER __declspec(_WCCALLBACK)
 #else
  #ifndef _WCRTLINK
   #define _WCRTLINK _WRTLFCONV
  #endif
  #ifndef _WCRTDATA
   #define _WCRTDATA _WRTLDCONV
  #endif
  #ifndef _WMRTLINK
   #define _WMRTLINK _WRTLFCONV
  #endif
  #ifndef _WMRTDATA
   #define _WMRTDATA _WRTLDCONV
  #endif
  #ifndef _WPRTLINK
   #define _WPRTLINK _WRTLFCONV
  #endif
  #ifndef _WPRTDATA
   #define _WPRTDATA _WRTLDCONV
  #endif
  #ifndef _WCHANDLER
   #define _WCHANDLER __declspec(_WCCALLBACK)
  #endif
 #endif
 /* control import modifier on intrinsic functions */
 #ifndef _WCIRTLINK
  #ifdef __INLINE_FUNCTIONS__
   #define _WCIRTLINK _WRTLFCONV
  #else
   #define _WCIRTLINK _WCRTLINK
  #endif
 #endif
 #ifndef _WMIRTLINK
  #if defined(__NO_MATH_OPS)
   #define _WMIRTLINK _WMRTLINK
  #else
   #define _WMIRTLINK _WRTLFCONV
  #endif
 #endif
 #ifndef _WPIRTLINK
  #define _WPIRTLINK _WPRTLINK
 #endif
 /* for MS compatibility */
 #ifndef _CRTAPI1
  #define _CRTAPI1
 #endif
 #ifndef _CRTAPI2
  #define _CRTAPI2
 #endif
 #ifndef _CRTIMP
  #define _CRTIMP _WCRTLINK
 #endif
#endif
