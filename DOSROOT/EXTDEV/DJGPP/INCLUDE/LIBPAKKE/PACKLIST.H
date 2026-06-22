/* $Id: packlist.h,v 1.11 2002/07/21 18:23:45 richdawe Exp $ */

/*
 *  packlist.h - Package list construction
 *  Copyright (C) 1999-2002 by Richard Dawe
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

#ifndef __libpakke_packlist_h__
#define __libpakke_packlist_h__

#include <libpakke/package.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_PACKAGES 256

/* Different search methods - these can be bitwise ANDed to combine multiple
 * searches. */
#define PACKLIST_FIND_NONE   0x00

#define PACKLIST_FIND_SIMPLE 0x01 /* Simple comparison */
#define PACKLIST_FIND_STEM   0x02 /* Package stem */
#define PACKLIST_FIND_USER   0x04 /* User package string with version spec */
#define PACKLIST_FIND_REGEXP 0x08 /* Use regexps */

#define PACKLIST_FIND_ALL    (  PACKLIST_FIND_SIMPLE \
			      | PACKLIST_FIND_STEM \
                              | PACKLIST_FIND_USER \
			      | PACKLIST_FIND_REGEXP)

/* The type for function to be passed for browse functions. Each package */
/* in the list or dependency tree is passed for this function, it should */
/* return zero if further processing of other packages should be done,   */
/* non-zero otherwise (usually, but not necessarry, due to some error).  */
typedef int (package_browse_fn)(PACKAGE_INFO * p, void * context);

extern int packlist_add    (PACKAGE_INFO *list, PACKAGE_INFO *p);

extern int packlist_remove (PACKAGE_INFO *p);

extern int packlist_free   (PACKAGE_INFO *p);

extern PACKAGE_INFO *packlist_dedupe (PACKAGE_INFO *p);

extern int packlist_browse (PACKAGE_INFO *list, package_browse_fn * browser,
                            void * context);

PACKAGE_INFO **packlist_find (PACKAGE_INFO *packages, const char *str,
			      const int how);

/* This function browses the dependency tree for given package. Returns NULL */
/* for successful browsing, or in the case of dependency loop - pointer to   */
/* first package, which was encountered twice.                               */
extern PACKAGE_INFO * packtree_browse(PACKAGE_INFO *p,
				      package_browse_fn * browser,
                                      void * context);

#ifdef __cplusplus
}
#endif

#endif	/* __libpakke_packlist_h__ */
