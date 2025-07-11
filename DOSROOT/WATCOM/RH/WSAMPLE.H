/*
 *  wsample.h   Open Watcom Execution Sampler include file
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
#ifndef _WSAMPLE_H_INCLUDED
#define _WSAMPLE_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MARK_ON
   extern void __mark( char __far * );
   #pragma aux __mark = 0xcc __parm __nomemory [__dx __eax] __modify __exact __nomemory []
 #define _MARK_( x )   __mark( x )
#else
 #define _MARK_( x )
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
