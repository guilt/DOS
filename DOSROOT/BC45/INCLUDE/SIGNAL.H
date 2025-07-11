/*  signal.h

    Definitions for ANSI defined signaling capability

*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1988, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef __SIGNAL_H
#define __SIGNAL_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn -nak
#endif

#endif  /* !RC_INVOKED */


typedef int sig_atomic_t;   /* Atomic entity type (ANSI) */

#ifdef __cplusplus
typedef void _USERENTRY (_EXPFUNC * _CatcherPTR)(int);
#else
typedef void _USERENTRY (_EXPFUNC * _CatcherPTR)();
#endif

#define SIG_DFL ((_CatcherPTR)0)   /* Default action   */
#define SIG_IGN ((_CatcherPTR)1)   /* Ignore action    */
#define SIG_ERR ((_CatcherPTR)-1)  /* Error return     */

#define SIGABRT         22
#define SIGFPE           8              /* Floating point trap  */
#define SIGILL           4              /* Illegal instruction  */
#define SIGINT           2
#define SIGSEGV         11              /* Memory access violation */
#define SIGTERM         15
#ifdef __FLAT__
#define SIGUSR1         16              /* User-defined signal 1 */
#define SIGUSR2         17              /* User-defined signal 2 */
#define SIGUSR3         20              /* User-defined signal 3 */
#define SIGBREAK        21              /* Control-Break interrupt */
#endif  /* __FLAT__ */


#ifdef __cplusplus
extern "C" {
#endif
int _RTLENTRY _EXPFUNC raise(int __sig);
#ifdef __cplusplus
void (_USERENTRY * _RTLENTRY _EXPFUNC32 signal(int __sig, void (_USERENTRY * __func)(int))) (int);
}
#else
void (_USERENTRY * _RTLENTRY _EXPFUNC32 signal(int __sig, void (_USERENTRY * __func)())) (int);
#endif

#if !__STDC__
#define NSIG   23      /* highest defined signal no. + 1 */
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  /* !RC_INVOKED */


#endif  /* __SIGNAL_H */
