/* $Id: util.h,v 1.17 2003/02/22 14:44:33 richdawe Exp $ */

/*
 *  util.h - Utility functions for pakke
 *  Copyright (C) 1999-2003 by Richard Dawe
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

#ifndef __libpakke_util_h__
#define __libpakke_util_h__

#include <sys/types.h>
#include <glob.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void die (const char *msg);
extern void warn (const char *msg);
extern void info (const char *msg);
extern void chomp (char *str);
extern void rtrim (char *str);

#ifdef __GNUC__
#define PAKKE_UTIL_ATTRIBUTE __attribute__((format (printf, 1, 2)))
#else
#define PAKKE_UTIL_ATTRIBUTE
#endif

extern void dief  (const char *fmt, ...) PAKKE_UTIL_ATTRIBUTE ;
extern void infof (const char *fmt, ...) PAKKE_UTIL_ATTRIBUTE ;
extern void warnf (const char *fmt, ...) PAKKE_UTIL_ATTRIBUTE ;

#undef PAKKE_UTIL_ATTRIBUTE

extern void backslashify (char *p);
extern void forwardslashify (char *p);
extern void addforwardslash (char *p);

extern char *strdupnx (const char *str, const int n);

extern int has_extension (const char *path, const char *ext);
extern int iszip (const char *path);
extern int istargz (const char *path);
extern int istarbz2 (const char *path);
extern int isarchive (const char *path);
extern int isurl (const char *path);
extern int isdsm (const char *path);

extern int ends_with_slash (const char *d);

extern int isdir (const char *path);

extern int isabspath (const char *path);
extern int isrelpath (const char *path);
extern int isspecialpath (const char *path);

extern int recursive_mkdir (const char *pathname, const mode_t mode);

extern char *find_in_paths (const char *name,
			    const char **paths, 
                            const int case_sensitivity);

extern char *find_in_paths_with_suffixes (const char *name,
					  const char **paths,
					  const char **suffixes,
					  const int case_sensitivity);

extern int glob_in_paths (const char *pattern,
			  const char **paths,
			  int flags,
			  int (*errfunc)(const char *epath, int eerrno),
			  glob_t *pglob);

extern int glob_in_paths_with_suffixes (const char *pattern,
					const char **paths,
					const char **suffixes,
					int flags,
					int (*errfunc)(const char *epath,
						       int eerrno),
					glob_t *pglob);

extern char *read_text_file_to_memory (const char *file);

extern int copy_file (const char *src, const char *dest);

extern int count_l0 (const char *v);

extern char *find_archive (const char *name,
			   const char *req_name,
			   const char **archive_paths);

/* URL component parsing */
typedef enum {
  URL_COMP_NONE = 0,
  URL_COMP_SCHEME,
  URL_COMP_USER,
  URL_COMP_PASSWORD,
  URL_COMP_HOST,
  URL_COMP_PORT,
  URL_COMP_PATH
} url_comp_t;

int get_url_component (const url_comp_t comp,
		       const char *url,
		       char *buf,
		       const size_t buflen);

int is_ftp_url (const char *url);
int is_http_url (const char *url);

#ifdef __cplusplus
}
#endif

#endif	/* __libpakke_util_h__ */
