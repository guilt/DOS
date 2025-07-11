/*
 *  wdefwin.h   default windowing calls
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
#ifndef _WDEFWIN_H_INCLUDED
#define _WDEFWIN_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef __SW_BW
 #error wdefwin.h is for use the default windowing system, use the /bw switch
#endif

#ifndef __COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined( __WINDOWS__ ) || defined( __NT__ ) || defined( __OS2__ ) && !defined( _M_I86 )
_WCRTLINK extern int _dwDeleteOnClose( int handle );
_WCRTLINK extern int _dwSetAboutDlg( const char *title, const char *text );
_WCRTLINK extern int _dwSetAppTitle( const char *title );
_WCRTLINK extern int _dwSetConTitle( int handle, const char *title );
_WCRTLINK extern int _dwYield( void );
_WCRTLINK extern int _dwShutDown( void );
#else
 #error You cannot use the default windowing system in a non GUI environment
 #error Make sure you use the /bt= switch to select the target system
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
