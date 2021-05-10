/* $Id: mft.h,v 1.9 2002/06/23 20:28:30 richdawe Exp $ */

/*
 *  mft.h - .mft & .ver file parsing functions
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

#ifndef __libpakke_mft_h__
#define __libpakke_mft_h__

#include <libpakke/package.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Version component strings */
#define MFT_COMP_ALPHA		"alpha"
#define MFT_COMP_BETA		"beta"
#define MFT_COMP_REVISION	"revision"
#define MFT_COMP_PATCHLEVEL	"patchlevel"
#define MFT_COMP_RELEASE	"release"

/* Error codes */
#define MFT_OK			1
#define MFT_NONEXISTENT		2
#define MFT_BAD			3
#define MFT_BAD_VERSION_FORMAT	4

#define MFT_INTERNAL_ERROR	255

/* Functions */
extern int ver_parse (const char *buf, PACKAGE_INFO *package);

extern int ver_get_and_parse (const char *filename,
			      PACKAGE_INFO *package,
			      char **ver);

extern int ver_parse_version_l0 (const char *v);
extern int ver_parse_version (const char *str, PACKAGE_VERSION *ver);
extern PACKAGE_INFO *ver_load_all (const char **path, PACKAGE_INFO *packages);

extern char *mft_get (const char **mft_path, PACKAGE_INFO *package);
extern char *mft_get_from_archive (PACKAGE_INFO *package);

extern char **mft_get_list (const char **mft_path, PACKAGE_INFO *package);

#ifdef __cplusplus
}
#endif

#endif	/* __libpakke_mft_h__ */
