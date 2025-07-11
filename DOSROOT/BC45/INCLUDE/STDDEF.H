/*  stddef.h

    Definitions for common types, and NULL

*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1987, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef __STDDEF_H
#define __STDDEF_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef NULL
#include <_null.h>
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn -nak
#endif

#endif  /* !RC_INVOKED */


#ifndef _PTRDIFF_T
#define _PTRDIFF_T
#if     defined(__LARGE__) || defined(__HUGE__) || defined(__COMPACT__)
typedef long    ptrdiff_t;
#else
typedef int     ptrdiff_t;
#endif
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#define offsetof( s_name, m_name )  (size_t)&(((s_name _FAR *)0)->m_name)

#ifndef __cplusplus
#ifndef _WCHAR_T
#define _WCHAR_T
#define _WCHAR_T_DEFINED  /* For WINDOWS.H */
typedef unsigned short wchar_t;
#endif
#endif

#if defined(__OS2__) || defined(__WIN32__)
#ifdef __cplusplus
extern "C" {
#endif
extern unsigned long _RTLENTRY _EXPFUNC __threadid(void);
#define _threadid (__threadid())

#ifdef  __cplusplus
}
#endif
#endif  /* __OS2__ or __WIN32__ */


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  /* !RC_INVOKED */


#endif  /* __STDDEF_H */
