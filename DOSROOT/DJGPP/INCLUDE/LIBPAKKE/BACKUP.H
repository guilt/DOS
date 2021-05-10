/* $Id: backup.h,v 1.3 2002/06/23 20:28:30 richdawe Exp $ */

/*
 *  backup.h - Functions for pakke for use in backing up.
 *  Copyright (C) 2001, 2002 by Richard Dawe
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

#ifndef __libpakke_backup_h__
#define __libpakke_backup_h__

#include <libpakke/package.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const char *backup_get_path (PACKAGE_INFO *package,
				    const char *backup_prefix);

extern int backup_file (const char *path,
			const char *prefix,
			const char *backup_prefix);

#ifdef __cplusplus
}
#endif

#endif /* __libpakke_backup_h__ */
