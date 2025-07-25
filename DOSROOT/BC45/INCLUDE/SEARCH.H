/*  search.h

    Definitions for search functions.

*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1991, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef __SEARCH_H
#define __SEARCH_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn -nak
#endif

#endif  /* !RC_INVOKED */


#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif
void *      _RTLENTRYF _EXPFUNC bsearch(const void * __key, const void * __base, 
                           size_t __nelem, size_t __width,
                           int (_USERENTRY *fcmp)(const void *,
                           const void *));
void *      _RTLENTRY _EXPFUNC lfind(const void * __key, const void * __base, 
                                size_t*__num, size_t __width,
                                int (_USERENTRY *fcmp)(const void *, const void *));
void *      _RTLENTRY _EXPFUNC lsearch(const void * __key, void * __base, 
                                size_t*__num, size_t __width, 
                                int (_USERENTRY *fcmp)(const void *, const void *));
void        _RTLENTRYF _EXPFUNC qsort(void * __base, size_t __nelem, size_t __width,
                         int (_USERENTRY *__fcmp)(const void *, const void *));


#ifdef __cplusplus
}
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  /* !RC_INVOKED */


#endif  /* __SEARCH_H */

