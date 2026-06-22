/* $Id: dsm.h,v 1.20 2003/03/12 19:54:32 richdawe Exp $ */

/*
 *  dsm.h - DSM parsing functions for pakke
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

#ifndef __libpakke_dsm_h__
#define __libpakke_dsm_h__

#include <string.h>

#include <libpakke/package.h>
#include <libpakke/dsm/version.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function defines to make parsing function automatically */
#define DSM_PARSING_FUNC_DECL(p) \
  extern int dsm_parse_##p (const char *directive, \
			    const char *str, \
			    PACKAGE_INFO *package)

/* Declare parsing functions using the above macro */
DSM_PARSING_FUNC_DECL(dsm_author);
DSM_PARSING_FUNC_DECL(dsm_author_email);
DSM_PARSING_FUNC_DECL(dsm_author_im);
DSM_PARSING_FUNC_DECL(dsm_author_web_site);
DSM_PARSING_FUNC_DECL(dsm_author_ftp_site);

DSM_PARSING_FUNC_DECL(dsm_name);
/* See below for dsm_version & dsm_type */

DSM_PARSING_FUNC_DECL(binaries_dsm);
DSM_PARSING_FUNC_DECL(sources_dsm);
DSM_PARSING_FUNC_DECL(documentation_dsm);

DSM_PARSING_FUNC_DECL(name);
DSM_PARSING_FUNC_DECL(manifest);
DSM_PARSING_FUNC_DECL(short_description);
DSM_PARSING_FUNC_DECL(long_description);

DSM_PARSING_FUNC_DECL(license);
DSM_PARSING_FUNC_DECL(organisation);
DSM_PARSING_FUNC_DECL(author);
DSM_PARSING_FUNC_DECL(author_email);
DSM_PARSING_FUNC_DECL(author_im);
DSM_PARSING_FUNC_DECL(web_site);
DSM_PARSING_FUNC_DECL(ftp_site);

DSM_PARSING_FUNC_DECL(maintainer);
DSM_PARSING_FUNC_DECL(maintainer_email);
DSM_PARSING_FUNC_DECL(maintainer_im);
DSM_PARSING_FUNC_DECL(maintainer_web_site);
DSM_PARSING_FUNC_DECL(maintainer_ftp_site);

DSM_PARSING_FUNC_DECL(porter);
DSM_PARSING_FUNC_DECL(porter_email);
DSM_PARSING_FUNC_DECL(porter_im);
DSM_PARSING_FUNC_DECL(porter_web_site);
DSM_PARSING_FUNC_DECL(porter_ftp_site);
DSM_PARSING_FUNC_DECL(porting_web_site);
DSM_PARSING_FUNC_DECL(porting_ftp_site);

DSM_PARSING_FUNC_DECL(mailing_list);
DSM_PARSING_FUNC_DECL(mailing_list_description);
DSM_PARSING_FUNC_DECL(mailing_list_request);
DSM_PARSING_FUNC_DECL(mailing_list_administrator);
DSM_PARSING_FUNC_DECL(mailing_list_administrator_email);
DSM_PARSING_FUNC_DECL(mailing_list_administrator_im);
DSM_PARSING_FUNC_DECL(mailing_list_web_site);
DSM_PARSING_FUNC_DECL(mailing_list_ftp_site);

DSM_PARSING_FUNC_DECL(newsgroup);
DSM_PARSING_FUNC_DECL(newsgroup_description);
DSM_PARSING_FUNC_DECL(newsgroup_email_gateway);
DSM_PARSING_FUNC_DECL(newsgroup_administrator);
DSM_PARSING_FUNC_DECL(newsgroup_administrator_email);
DSM_PARSING_FUNC_DECL(newsgroup_administrator_im);
DSM_PARSING_FUNC_DECL(newsgroup_web_site);
DSM_PARSING_FUNC_DECL(newsgroup_ftp_site);

DSM_PARSING_FUNC_DECL(simtelnet_path);
DSM_PARSING_FUNC_DECL(zip);
DSM_PARSING_FUNC_DECL(zip_options);
DSM_PARSING_FUNC_DECL(tar_gzip);
DSM_PARSING_FUNC_DECL(tar_gzip_options);

DSM_PARSING_FUNC_DECL(changelog);

DSM_PARSING_FUNC_DECL(pre_install_readme);
DSM_PARSING_FUNC_DECL(post_install_readme);
DSM_PARSING_FUNC_DECL(pre_uninstall_readme);
DSM_PARSING_FUNC_DECL(post_uninstall_readme);

/* Built-in scripting. */
DSM_PARSING_FUNC_DECL(builtin_pre_install_script);
DSM_PARSING_FUNC_DECL(builtin_post_install_script);
DSM_PARSING_FUNC_DECL(builtin_pre_uninstall_script);
DSM_PARSING_FUNC_DECL(builtin_post_uninstall_script);

DSM_PARSING_FUNC_DECL(pre_install_script);
DSM_PARSING_FUNC_DECL(post_install_script);
DSM_PARSING_FUNC_DECL(pre_uninstall_script);
DSM_PARSING_FUNC_DECL(post_uninstall_script);

DSM_PARSING_FUNC_DECL(keep_file);

DSM_PARSING_FUNC_DECL(prefix);

DSM_PARSING_FUNC_DECL(install_warning);

/* Version component strings */
#define DSM_COMP_ALPHA           "alpha"
#define DSM_COMP_BETA            "beta"
#define DSM_COMP_PRE             "pre"
#define DSM_COMP_PATCHLEVEL      "patchlevel"
#define DSM_COMP_REVISION        "revision"
#define DSM_COMP_SNAPSHOT        "snapshot"
#define DSM_COMP_RELEASE         "release"
#define DSM_COMP_PLATFORM        "platform"

#define DSM_COMP_BINARIES        "binaries"
#define DSM_COMP_SOURCES         "sources"
#define DSM_COMP_DOCUMENTATION   "documentation"
#define DSM_COMP_GROUP           "group"
#define DSM_COMP_VIRTUAL         "virtual"

/* Wildcard a single version component */
#define DSM_COMP_SINGLE_WILDCARD "?"

/* Wildcard this and subsequent version components */
#define DSM_COMP_MULTI_WILDCARD  "*"

/* Error codes */
#define DSM_FAILED		  0x00
#define DSM_OK			  0x01
#define DSM_NONEXISTENT		  0x02
#define DSM_EMPTY		  0x03
#define DSM_BAD_ARCHIVE           0x04
#define DSM_ARCHIVE_HAS_NO_DSM    0x05

#define DSM_BAD_VERSION_FORMAT	  0x10
#define DSM_BAD_TYPE		  0x11
#define DSM_BAD_ESCAPE		  0x12
#define DSM_BAD_VALUE             0x13

#define DSM_BAD_DIRECTIVE	  0x21
#define DSM_UNKNOWN_DIRECTIVE	  0x22
#define DSM_REQUIRED_DIRECTIVE	  0x23
#define DSM_TOO_MANY              0x24 /* Too many occurrences - array full */
#define DSM_CONFLICTING_DIRECTIVE 0x25
#define DSM_SUGGESTED_DIRECTIVE   0x26 /* Suggest that directive
                                        * should be present */
#define DSM_GENERIC               0x27 /* Generic DSM parser message -
                                        * meant for warnings only! */

#define DSM_PACKAGE_UNSUPPORTED	  0x30
#define DSM_TAR_GZ_UNSUPPORTED    0x31
#define DSM_TAR_BZ2_UNSUPPORTED   0x32
#define DSM_URL_UNSUPPORTED       0x3E
#define DSM_NOT_UNDERSTOOD        0x3F

#define DSM_INTERNAL_ERROR	  0xFF

/* Error handling structures */
typedef struct _DSM_ERROR {
  /* Linked-list bizness */
  struct _DSM_ERROR *q_forw;
  struct _DSM_ERROR *q_back;

  int ret;		/* Parsing error code code                */
  int fatal;		/* Fatal error? 0 => no, otherwise => yes */
  int line_number;	/* Line number of error                   */
  char *directive;    	/* Directive which caused error           */
  char *data;		/* Any data for error message             */
} DSM_ERROR;

typedef struct _DSM_FILE_ERROR {
  /* Linked-list bizness */
  struct _DSM_FILE_ERROR *q_forw;
  struct _DSM_FILE_ERROR *q_back;
	
  char      *name;	/* File name for error list. */
  DSM_ERROR *de;       	/* List of parsing errors.   */
} DSM_FILE_ERROR;

/* "Normally" defined functions */
extern int dsm_parse_version (const char *directive, const char *str,
			      PACKAGE_VERSION *ver);

extern int dsm_parse_wildcard_version (const char *str, PACKAGE_VERSION *ver);

extern int dsm_parse_dsm_file_version (const char *directive, const char *str,
				       PACKAGE_INFO *package);

extern int dsm_parse_dsm_version (const char *directive, const char *str,
				  PACKAGE_INFO *package);

extern int dsm_parse_package_version (const char *directive, const char *str,
				      PACKAGE_INFO *package);

extern int dsm_parse_type (const char *directive, const char *str,
			   PACKAGE_INFO *package);

extern int dsm_parse_wildcard_type (const char *directive, const char *str,
				    PACKAGE_INFO *package);

extern int dsm_parse_multiple (const char *directive, const char *str,
			       char **aa, const int max);

extern int dsm_parse_duplicate_action (const char *directive, const char *str,
				       PACKAGE_INFO *package);

extern int dsm_parse_operator (const char *str);

extern int dsm_parse_deps (const char *directive, const char *str,
			   PACKAGE_INFO *package);

extern int dsm_parse_short_description (const char *directive, const char *str,
					PACKAGE_INFO *package);

extern int dsm_parse_long_description (const char *directive, const char *str,
				       PACKAGE_INFO *package);

extern int dsm_parse_escapes (const char *str);

extern int dsm_parse (const char *buf,
		      PACKAGE_INFO *package,
		      DSM_ERROR **de);

extern int dsm_check (PACKAGE_INFO *package, DSM_ERROR **de);

extern PACKAGE_INFO *dsm_load_dir (const char *dir,
                                   PACKAGE_INFO *packages,
                                   DSM_FILE_ERROR **dfe);

extern PACKAGE_INFO *dsm_load_all (const char **path,
				   PACKAGE_INFO *packages,
				   DSM_FILE_ERROR **dfe);

extern int dsm_errors_fatal (const DSM_ERROR *de);

extern int dsm_file_errors_fatal (const DSM_FILE_ERROR *dfe);

extern void dsm_perror (const char *str, const DSM_ERROR *de);

extern int dsm_free_error_list (const DSM_ERROR *de);

extern int dsm_free_file_error_list (const DSM_FILE_ERROR *dfe);

extern int dsm_get_and_parse (const char *where,
			      PACKAGE_INFO *package,
			      char **dsm,
			      DSM_ERROR **de);

#ifdef __cplusplus
}
#endif

#endif	/* __libpakke_dsm_h__ */
