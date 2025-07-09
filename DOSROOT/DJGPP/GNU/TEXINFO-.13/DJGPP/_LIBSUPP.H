/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2009 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2008 DJ Delorie, see COPYING.DJ for details */

#ifndef __libsupp_h__
#define __libsupp_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/version.h>  /*  gcc 4.3.0 no longer includes this by default.  */


/*
 *  Functions implemented in libsupp 6.1.
 */

#include <wchar.h>

/*  Conversion state information.  */
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;  /*  Value so far.  */
} libsupp_mbstate_t;

#undef  mbstate_t
#define mbstate_t  libsupp_mbstate_t

int    libsupp_mblen(const char *_s, size_t _n);
int    libsupp_mbsinit(const libsupp_mbstate_t *_ps);
size_t libsupp_mbrtowc(wchar_t *_pwc, const char *_s, size_t _n, libsupp_mbstate_t *_ps);
int    libsupp_mbtowc(wchar_t *_pwc, const char *_s, size_t _n);
wint_t libsupp_towlower(wint_t _c);
wint_t libsupp_towupper(wint_t _c);


/*---------------------------------------------------------------------------*/


/*
 *  Make them visible.
 */

#undef  mblen
#define mblen     libsupp_mblen
#undef  mbrtowc
#define mbrtowc   libsupp_mbrtowc
#undef  mbtowc
#define mbtowc    libsupp_mbtowc
#undef  mbsinit
#define mbsinit   libsupp_mbsinit
#undef  towlower
#define towlower  libsupp_towlower
#undef  towupper
#define towupper  libsupp_towupper


#ifdef __cplusplus
}
#endif

#endif /* !__libsupp_h__ */
