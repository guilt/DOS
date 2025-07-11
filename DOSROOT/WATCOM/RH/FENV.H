/***************************************************************************
 * FILE: fenv.h (Floating-point environment)
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
 *
 * Description: This header is part of the C99 standard library. It
 *              describes the floating-point environment
 ***************************************************************************/
#ifndef _FENV_H_INCLUDED
#define _FENV_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ >= 199901L

#ifndef __COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack( __push, 1 )

/* type for holding FPU environment */
typedef struct {
    unsigned short control_word;
    unsigned short pad0;
    unsigned short status_word;
    unsigned short pad1;
    unsigned short tag_word;
    unsigned short pad2;
    unsigned int   ins_ptr_offset;
    unsigned short ins_ptr_seg;
    unsigned short opcode;
    unsigned int   op_ptr_offset;
    unsigned short op_ptr_seg;
    unsigned short pad3;
} fenv_t;

#pragma pack( __pop )

/* type for holding FPU exception flags */
typedef unsigned short fexcept_t;

/* exception flags */
#define FE_INVALID   1
#define FE_DENORMAL  2
#define FE_DIVBYZERO 4
#define FE_OVERFLOW  8
#define FE_UNDERFLOW 16
#define FE_INEXACT   32

#define FE_ALL_EXCEPT (FE_DIVBYZERO|FE_INEXACT|FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW|FE_DENORMAL)

/* rounding modes */
#define FE_TONEAREST  0x0000
#define FE_DOWNWARD   0x0400
#define FE_TOWARDZERO 0x0C00
#define FE_UPWARD     0x0800

/* default FPU setup */
_WCRTDATA extern const fenv_t __fenv_h_default_environment;
#define FE_DFL_ENV &__fenv_h_default_environment

/* exception handling functions */
_WCRTLINK extern int  feclearexcept( int __excepts );
_WCRTLINK extern int  fegetexceptflag( fexcept_t *__flagp, int __excepts );
_WCRTLINK extern int  feraiseexcept( int __excepts );
_WCRTLINK extern int  fesetexceptflag( const fexcept_t *__flagp, int __excepts );
_WCRTLINK extern int  fetestexcept( int __excepts );

#if !defined( _NO_EXT_KEYS ) /* extensions enabled */
_WCRTLINK extern void feenableexcept( int __excepts );
_WCRTLINK extern void __feenableexcept( int __excepts );
_WCRTLINK extern void fedisableexcept( int __excepts );
_WCRTLINK extern void __fedisableexcept( int __excepts );
#endif /* extensions enabled */

/* rounding mode functions */
_WCRTLINK extern int  fegetround( void );
_WCRTLINK extern int  fesetround( int __round );

/* FPU environment functions */
_WCRTLINK extern int  fegetenv( fenv_t *__envp );
_WCRTLINK extern int  feholdexcept( fenv_t *__envp );
_WCRTLINK extern int  fesetenv( const fenv_t *__envp );
_WCRTLINK extern int  feupdateenv( const fenv_t *__envp );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
#endif
