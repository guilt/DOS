/***
* moveapi.h - MOVE definitions and prototypes
*
*	Copyright (c) 1990-1992, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*	This is a header file for the MOVE API.
*
*******************************************************************************/

#if (_MSC_VER <= 600)
#define __cdecl     _cdecl
#define __far       _far
#define __pascal	_pascal
#endif

/* linker constructs */
extern void __far __pascal $$MAIN(void);
extern void __far __pascal $$OVLTHUNKBEG(void);
extern void __far __pascal $$OVLTHUNKEND(void);
extern unsigned short __pascal $$CGSN;
extern unsigned short __pascal $$COVL;
extern unsigned short __pascal $$MPGSNBASE[];
extern unsigned short __pascal $$MPGSNOVL[];
extern unsigned long __pascal $$MPOVLLFA[];
extern unsigned long __pascal $$MPOVLSIZE[];
extern unsigned char __pascal $$INTNO;

/* callback init */
extern void __far __cdecl _moveinit(void);

/* heap/cache allocation */
extern unsigned short __far __cdecl _movesetheap(unsigned short, unsigned short, unsigned short);
extern void __far __cdecl _movegetcache(unsigned short __far *, unsigned short __far *);
extern unsigned short __far __cdecl _movesetcache(unsigned short, unsigned short);
extern unsigned short __far __cdecl _moveckbxms;
extern unsigned short __far __cdecl _moveckbems;

#define __MOVESETCACHE_ERR_NO	0
#define __MOVESETCACHE_ERR_XMS	1
#define __MOVESETCACHE_ERR_EMS	2

/* pause / resume */
extern void __far __cdecl _movepause(void);
extern void __far __cdecl _moveresume(void);
extern unsigned short __far __cdecl _movefpause;
extern unsigned short __far __cdecl _movefpaused;

#define _MOVE_PAUSE_DISK    2
#define _MOVE_PAUSE_CACHE   4

/* tracing support */
#ifdef TRACE
extern void __far __cdecl _movetraceon(void);
extern void __far __cdecl _movetraceoff(void);
#endif  /* TRACE */

#ifdef MOVE_ENV
/* environment support */
extern unsigned short __far __cdecl _movesegenv;
#endif  /* MOVE_ENV */
