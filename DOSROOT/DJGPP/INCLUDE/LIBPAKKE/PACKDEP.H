/* $Id: packdep.h,v 1.6 2002/06/23 20:28:30 richdawe Exp $ */

/*
 *  packdep.h - Package dependency include file for pakke
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

#ifndef __libpakke_packdep_h__
#define __libpakke_packdep_h__

#include <libpakke/package.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int packlist_xref (PACKAGE_INFO *p);

extern int package_xref (PACKAGE_INFO *packages, PACKAGE_INFO *package);

extern int package_check_deps (const PACKAGE_INFO *package,
                               const int deptype,
                               PACKAGE_DEP **failed_dep,
			       const int failed_dep_max);

extern int package_dep_exists (PACKAGE_INFO *packages,
			       PACKAGE_INFO *package,
			       const int dep_type,
			       PACKAGE_INFO **matched_package,
			       PACKAGE_DEP **matched_dep,
			       const int matched_dep_max);

#ifdef __cplusplus
}
#endif

#endif /* __libpakke_packdep_h__ */
