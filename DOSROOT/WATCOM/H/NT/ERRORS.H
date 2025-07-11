/*
 *  errors.h    ActiveMovie error handling functions
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */

#ifndef __ERRORS__
#define __ERRORS__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <vfwmsgs.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Macro to specify ActiveMovie functions */
#define AMOVIEAPI   DECLSPEC_IMPORT

/* ActiveMovie error callback */
typedef BOOL (WINAPI *AMGETERRORTEXTPROCA)( HRESULT, char *, DWORD );
typedef BOOL (WINAPI *AMGETERRORTEXTPROCW)( HRESULT, WCHAR *, DWORD );
#ifdef UNICODE
    #define AMGETERRORTEXTPROC  AMGETERRORTEXTPROCW
#else
    #define AMGETERRORTEXTPROC  AMGETERRORTEXTPROCA
#endif

/* Functions in QUARTZ.DLL */
AMOVIEAPI DWORD WINAPI  AMGetErrorTextA( HRESULT, LPSTR, DWORD );
AMOVIEAPI DWORD WINAPI  AMGetErrorTextW( HRESULT, LPWSTR, DWORD );

/* Map generic function names to the appropriate ANSI or Unicode version. */
#ifdef UNICODE
    #define AMGetErrorText  AMGetErrorTextW
#else
    #define AMGetErrorText  AMGetErrorTextA
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __ERRORS__ */
