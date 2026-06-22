/* $Id: archive.h,v 1.8 2002/06/23 20:28:30 richdawe Exp $ */

/*
 *  archive.h - Archive handling functions for pakke
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

#ifndef __libpakke_archive_h__
#define __libpakke_archive_h__

#include <limits.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* --- Data structures --- */

typedef struct {
  char          name[PATH_MAX];
  unsigned long size;
  struct tm     modtime; /* modification time */
} ARCHIVE_FILE_INFO;

/* --- Functions --- */
extern char **archive_get_toc       (const char *archive);
extern int    archive_extract_file  (const char *archive, const char *file, 
                                     const char *dest);
extern int    archive_get_file_info (const char *archive, const char *file,
                                     ARCHIVE_FILE_INFO *afi);

extern char *archive_extract_file_to_memory      (const char *archive, 
                                                  const char *file);
extern char *archive_extract_text_file_to_memory (const char *archive, 
                                                  const char *file);

extern int archive_check_integrity (const char *archive);

#ifdef __cplusplus
}
#endif

#endif	/* __libpakke_archive_h__ */
