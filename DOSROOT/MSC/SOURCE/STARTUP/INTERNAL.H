/***
*internal.h - contains declarations of internal routines and variables
*
*	Copyright (c) 1985-1992, Microsoft Corporation. All rights reserved.
*
*Purpose:
*	Declares routines and variables used internally by the C run-time.
*	These variables are declared "near" for efficiency.
*	[Internal]
*
****/

#ifdef __cplusplus
extern "C" {
#endif

/* no _FAR_ in internal builds */		/* _FAR_DEFINED */
#undef _FAR_					/* _FAR_DEFINED */
#define _FAR_					/* _FAR_DEFINED */

#define _LOAD_DS		/* _LOAD_DGROUP */
				/* _LOAD_DGROUP */
#define _NEAR_ __near
#define _PASCAL_ __pascal

#if (_MSC_VER <= 600)
#define __cdecl     _cdecl
#define __far       _far
#define __near      _near
#define __pascal    _pascal
#endif

/* conditionally define macro for Windows DLL libs */
#ifdef	_WINDLL
#define _WINSTATIC	static
#else
#define _WINSTATIC
#endif

extern char __near _commode;	/* default file commit mode */

extern int __near _nfile;	/* # of OS file handles */
#ifdef _QWIN
extern int __near _wfile;	/* # of QWIN file handles */
extern int __near _wnfile;	/* total # of file handles */
#endif

extern char __near _osfile[];

extern char __near __dnames[];
extern char __near __mnames[];

extern int __near _days[];
extern int __near _lpdays[];

#ifdef _QWIN
extern int __near _qwinused;	  /* QWIN system in use flag */
#endif

#ifdef _WINDOWS
/* Underlying DOS version */
extern unsigned int __near __cdecl _dosversion;
extern unsigned char __near __cdecl _dosmajor;
extern unsigned char __near __cdecl _dosminor;
#endif

/*
#ifdef	_WINDOWS
#ifdef _WINDLL
extern unsigned int _hModule;
extern unsigned int _wDataSeg;
extern unsigned int _wHeapSize;
extern char __far * _lpszCmdLine;
#else
extern unsigned int _hInstance;
extern unsigned int _hPrevInstance;
extern char __far * _lpszCmdLine;
extern int _cmdShow;
#endif
#endif
*/

#ifndef _TIME_T_DEFINED
typedef unsigned long time_t;	/* time value */
#define _TIME_T_DEFINED 	/* avoid multiple def's of time_t */
#endif

extern time_t _dtoxtime(int, int, int, int, int, int);

#ifdef _TM_DEFINED
extern int _isindst(struct tm *);
#endif

extern void __tzset(void);

/**
** This variable is in the C start-up; the length must be kept synchronized
**  It is used by the *cenvarg.c modules
**/

extern char __near _acfinfo[]; /* "_C_FILE_INFO=" */

#define CFI_LENGTH  12	/* "_C_FILE_INFO" is 12 bytes long */

/* functions used by exec/spawn family */

extern int _cenvarg(const char * const *, const char * const *,
		char **, char **, char *, const char *, const char *);
extern int _doexec(int, const char *, int, char *, char *, int, int, int, int, int, int, unsigned int);
extern int _dospawn(int, const char *, char *, char *);
extern int _execload(const char *, const char * const *, const char * const *);


extern char *_find(char *);


#ifdef	_FILE_DEFINED

extern FILE * __near _lastiob;

FILE *_getstream(void);

FILE *_openfile(const char *, const char *, int, FILE *);

void __near _getbuf(FILE *);

void __near _freebuf(FILE *);

int __near _stbuf(FILE *);

void __near _ftbuf(int, FILE *);

int __near _flush(FILE *);

/* input and output are the guts of the scanf/printf family */

#ifndef _VA_LIST_DEFINED
typedef char _FAR_ *va_list;
#define _VA_LIST_DEFINED
#endif

extern int _input(FILE *, const unsigned char *, va_list);
extern int _output(FILE *, const char *, void *);

#endif

extern int __near _cflush;

extern unsigned int __near _tmpoff;

extern unsigned int __near _tempoff;

extern unsigned int __near _old_pfxlen;

char * __near _getpath(const char *, char *, unsigned);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <new.h>

extern "C" {
    extern _PNH _pnhNearHeap;
    extern _PNH _pnhFarHeap;
    extern _PNHH _pnhhHugeHeap;
    extern _PNHB _pnhbBasedHeap;
    }

#endif	// __cplusplus
