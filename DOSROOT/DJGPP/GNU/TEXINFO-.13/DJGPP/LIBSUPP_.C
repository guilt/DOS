/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2009 DJ Delorie, see COPYING.DJ for details */
#include <ctype.h>
#include "_libsupp.h"

wint_t
libsupp_towupper(wint_t c)
{
  return (c < 0x00ff) ? (wint_t)toupper((int)c) : c;
}
