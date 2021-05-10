/* $Id: user.h,v 1.3 2002/06/23 20:28:30 richdawe Exp $ */

/*
 *  user.h - Functions for pakke for use in user interface code.
 *  Copyright (C) 2000-2002 by Richard Dawe
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __libpakke_user_h__
#define __libpakke_user_h__

#include <libpakke/package.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int user_parse_package_string (const char *str,
				      char *buf, size_t buflen,
				      PACKAGE_VERSION *ver);

#ifdef __cplusplus
}
#endif

#endif /* __libpakke_user_h__ */
