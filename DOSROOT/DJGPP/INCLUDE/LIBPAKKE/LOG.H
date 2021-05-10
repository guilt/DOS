/* $Id: log.h,v 1.6 2002/06/23 20:28:30 richdawe Exp $ */

/*
 *  log.h - Include file for logging functions for pakke
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

#ifndef __libpakke_log_h__
#define __libpakke_log_h__

#include <libpakke/package.h>

#ifdef __cplusplus
extern "C" {
#endif
	
enum {
  LOG_OP_NONE		= 0x0,
  LOG_OP_INSTALL	= 0x1,
  LOG_OP_UNINSTALL	= 0x2,
  LOG_OP_SYNCDB		= 0x3
};

/* Typedefs */
typedef struct {
  FILE *fp;
} LZ_LOG;

/* Functions */
int lz_loginit (LZ_LOG * /*log*/);
int lz_logopen (LZ_LOG * /*log*/, const char * /*name*/);
int lz_logclose (LZ_LOG * /*log*/);

int lz_logf (LZ_LOG * /*log*/, int /*op*/, PACKAGE_INFO * /*package*/,
	     const char * /*fmt*/, ...)
  __attribute__((format (printf, 4, 5)));

#ifdef __cplusplus
}
#endif
	
#endif	/* __libpakke_log_h__ */
