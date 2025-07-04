/*  time.h

    Struct and function declarations for dealing with time.

*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1987, 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef __TIME_H
#define __TIME_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif


#if !defined(RC_INVOKED)

#if defined(__STDC__)
#pragma warn -nak
#endif

#pragma option -a-

#endif  /* !RC_INVOKED */


#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifndef  _TIME_T
#define  _TIME_T
typedef long time_t;
#endif

#ifndef  _CLOCK_T
#define  _CLOCK_T
typedef long clock_t;
#endif

#define CLOCKS_PER_SEC 1000.0
#define CLK_TCK        1000.0

struct tm
{
  int   tm_sec;
  int   tm_min;
  int   tm_hour;
  int   tm_mday;
  int   tm_mon;
  int   tm_year;
  int   tm_wday;
  int   tm_yday;
  int   tm_isdst;
};

#ifdef __cplusplus
extern "C" {
#endif
char _FAR * _RTLENTRY _EXPFUNC   asctime(const struct tm _FAR *__tblock);
char _FAR * _RTLENTRY _EXPFUNC   ctime(const time_t _FAR *__time);
double      _RTLENTRY _EXPFUNC32 difftime(time_t __time2, time_t __time1);
struct tm _FAR * _RTLENTRY _EXPFUNC gmtime(const time_t _FAR *__timer);
struct tm _FAR * _RTLENTRY _EXPFUNC localtime(const time_t _FAR *__timer);
time_t      _RTLENTRY _EXPFUNC32 time(time_t _FAR *__timer);
time_t      _RTLENTRY _EXPFUNC   mktime(struct tm _FAR *__timeptr);
clock_t     _RTLENTRY _EXPFUNC32 clock(void);
size_t      _RTLENTRY _EXPFUNC   strftime(char _FAR *__s, size_t __maxsize,
                        const char _FAR *__fmt, const struct tm _FAR *__t);
size_t      _RTLENTRY _EXPFUNC   _lstrftime(char _FAR *__s, size_t __maxsize,
                        const char _FAR *__fmt, const struct tm _FAR *__t);

#if !defined(__STDC__)  /* NON-ANSI */
#define daylight  _daylight
#define timezone  _timezone
#define tzname    _tzname
#endif

#if !defined(_RTLDLL) || defined(__FLAT__)

extern int               _RTLENTRY _EXPDATA _daylight;
extern long              _RTLENTRY _EXPDATA _timezone;
extern char _FAR * const _RTLENTRY _EXPDATA _tzname[2];

#else

int  _FAR *        _RTLENTRY _EXPFUNC __getDaylight(void);
long _FAR *        _RTLENTRY _EXPFUNC __getTimezone(void);
char _FAR * _FAR * _RTLENTRY _EXPFUNC __getTzname(void);

#define _daylight (*__getDaylight())
#define _tzname   ( __getTzname())
#define _timezone (*__getTimezone())

#endif  /* _RTLDLL */

int         _RTLENTRY           stime(time_t _FAR *__tp);
void        _RTLENTRY  _EXPFUNC tzset(void);
char _FAR * _RTLENTRY  _EXPFUNC _strdate(char _FAR *datestr);
char _FAR * _RTLENTRY  _EXPFUNC _strtime(char _FAR *timestr);

#ifdef __cplusplus
}
#endif


#if !defined(__STDC__)

#if defined( __USELOCALES__ )

#define strftime   _lstrftime

#endif

#endif  /* __STDC__  */


#if !defined(RC_INVOKED)

#pragma option -a. /* restore default packing */

#if defined(__STDC__)
#pragma warn .nak
#endif

#endif  /* !RC_INVOKED */


#endif  /* __TIME_H */
