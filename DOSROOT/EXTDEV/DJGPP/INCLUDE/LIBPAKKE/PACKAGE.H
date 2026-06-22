/* $Id: package.h,v 1.25 2003/03/01 19:27:55 richdawe Exp $ */

/*
 *  package.h - Package data structure include file for pakke
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

#ifndef __libpakke_package_h__
#define __libpakke_package_h__

#include <sys/param.h>

#ifdef __cplusplus
extern "C" {
#endif

/* autoconf 2.5x may define PACKAGE_*. Undefine them here, to avoid
 * a clash. PACKAGE_* are ours, so there! */
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

/* - Maxima - */

/* String lengths */
#define PACKAGE_MAXPATH			PATH_MAX
#define PACKAGE_MAXNAMELEN		64
#define PACKAGE_MAXSHORTDESCLEN		80
#define PACKAGE_MAXLONGDESCLEN		1024
#define PACKAGE_MAXGENERICLEN		64
#define PACKAGE_MAXURLLEN		256
#define PACKAGE_MAXSIMTELNETPATH	16
#define PACKAGE_MAXBUILTINLEN		1024

/* Array maxima - these are arbitrarily chosen, but seem reasonable. */
#define PACKAGE_MAX_DEP         64
#define PACKAGE_MAX_ARCHIVE     16
#define PACKAGE_MAX_AUTHOR      4
#define PACKAGE_MAX_SITE        4
#define PACKAGE_MAX_MAINTAINER  8
#define PACKAGE_MAX_PORTER      4
#define PACKAGE_MAX_MAILINGLIST 4
#define PACKAGE_MAX_NEWSGROUP   4
#define PACKAGE_MAX_KEEP_FILE   64

/* --- Package data structs --- */

/* Package version */
typedef struct _PACKAGE_VERSION {
  /* This should cover everything ;) */
  unsigned int has_version:1;
  unsigned int has_major:1;
  unsigned int has_minor:1;
  unsigned int has_subminor:1;
  unsigned int has_subsubminor:1;	
  unsigned int has_alpha:1;
  unsigned int has_beta:1;
  unsigned int has_pre:1;
  unsigned int has_revision:1;	
  unsigned int has_patchlevel:1;  
  unsigned int has_snapshot:1;
  unsigned int has_release:1;
  unsigned int has_platform:1;
  unsigned int has_type:1;

#define PACKAGE_VERSION_N_HAS 14

  /*
   * For the version numbering, '..._l0' is a count of the number of
   * leading zeros in front of the digit. If the version component is
   * 0, then '..._l0' should be too.
   *
   * '-1' in any of the fields except '..._l0' below indicates
   * a version wildcard, i.e. any value of the version component.
   */
#define PACKAGE_VERSION_WILDCARD -1

  int major;
  int minor;
  int minor_l0;
  int subminor;
  int subminor_l0;
  int subsubminor;
  int subsubminor_l0;
  int alpha;
  int beta;
  int pre;
  int revision;
  int patchlevel;  
  int snapshot_year;
  int snapshot_month;
  int snapshot_day;
  int release;

  char *platform_cpu;
  char *platform_manufacturer;
  char *platform_kernel;
  char *platform_os;

  int type;

#define PACKAGE_VERSION_N_DATA 21
} PACKAGE_VERSION;

/* Package dependency */
enum {
  DEP_OP_NONE		=	0x00,
  DEP_OP_EQUAL		=	0x01,
  DEP_OP_NOTEQUAL	=	0x02,
  DEP_OP_LESSEQUAL	=	0x04,
  DEP_OP_GREATEREQUAL	=	0x08,
  DEP_OP_LESS		=	0x10,
  DEP_OP_GREATER        =	0x20
};

/* duplicate-action */
enum {
  DUP_REPLACE		=	0x01,
  DUP_KEEP		=	0x02,
  DUP_BACKUP		=	0x04,
  DUP_SKIP		=	0x08,
  DUP_QUERY		=	0x10,
  DUP_ABORT             =       0x20
};

/* Dependency enumeration */
enum {
  PACKAGE_DEP_NONE              =       0x00,
  PACKAGE_DEP_REQUIRES		=	0x01,
  PACKAGE_DEP_DEPENDS_ON	=	0x02,
  PACKAGE_DEP_CONFLICTS_WITH	=	0x04,
  PACKAGE_DEP_REPLACES		=	0x08,
  PACKAGE_DEP_PROVIDES		=	0x10,

  PACKAGE_DEP_INSTALL_BEFORE	=	0x20,
  PACKAGE_DEP_INSTALL_AFTER	=	0x40
};

struct _PACKAGE_INFO;

typedef struct _PACKAGE_DEP {
  int                     dep_type;
  struct _PACKAGE_INFO   *dep;       /* The package satisfying the dep. */
  char                    name[PACKAGE_MAXNAMELEN];
  int                     op;
  PACKAGE_VERSION         version;
  char                   *qualifier; /* Dependency qualifier */
} PACKAGE_DEP;

/* Package info */
enum {
  /* TYPE_WILDCARD is like PACKAGE_VERSION_WILDCARD. */
  TYPE_WILDCARD      = -1,

  TYPE_NONE          =  0,
  TYPE_BINARIES      =  1,
  TYPE_SOURCES       =  2,
  TYPE_DOCUMENTATION =  3,
  TYPE_VIRTUAL       =  4,
  TYPE_GROUP         =  5
};

typedef struct _PACKAGE_INFO {
  /* Linked-list pointers */
  struct _PACKAGE_INFO *q_forw;
  struct _PACKAGE_INFO *q_back;

  /* Arbitrary information provided by library user. */
  void * info;
	
  /* Status */
  unsigned int has_manifest:1;	     /* Has a .mft file */  
  unsigned int has_version:1;	     /* Has a .ver file */
  unsigned int has_faked_version:1; /* Has a version faked from .ver file */
  unsigned int has_dsm:1;	     /* Has a .dsm file */
  /* TODO: Move the internal flags into a private data structure. */
  /* Internal status flags - DO NOT USE */
  unsigned int visited:1;
  /* End internal status flags */

  char path[PACKAGE_MAXPATH];	/* Path to .mft or .dsm or archive */

  /* DSM header details  */
  char *dsm_author;
  char *dsm_author_email;
  char *dsm_author_im;
  char *dsm_author_web_site;
  char *dsm_author_ftp_site;

  char dsm_name[PACKAGE_MAXNAMELEN];
  PACKAGE_VERSION dsm_file_version; /* File revision    */
  PACKAGE_VERSION dsm_version;      /* DSM spec version */

  char *binaries_dsm;
  char *sources_dsm;
  char *documentation_dsm;

  /* Cross-references to other versions. */
  struct _PACKAGE_INFO *binaries;
  struct _PACKAGE_INFO *sources;
  struct _PACKAGE_INFO *documentation;
  
  /* Descriptive details */
  char name[PACKAGE_MAXNAMELEN];
  PACKAGE_VERSION version;
  char manifest[PACKAGE_MAXNAMELEN];
  char short_description[PACKAGE_MAXSHORTDESCLEN];
  char *long_description;

  char *license;
  char *organisation;

  /* + 1 for NULL list terminator */
  char *author[PACKAGE_MAX_AUTHOR + 1];
  char *author_email[PACKAGE_MAX_AUTHOR + 1];
  char *author_im[PACKAGE_MAX_AUTHOR + 1];

  /* + 1 for NULL list terminator */
  char *web_site[PACKAGE_MAX_SITE + 1];
  char *ftp_site[PACKAGE_MAX_SITE + 1];

  /* + 1 for NULL list terminator */
  char *maintainer[PACKAGE_MAX_MAINTAINER + 1];
  char *maintainer_email[PACKAGE_MAX_MAINTAINER + 1];
  char *maintainer_im[PACKAGE_MAX_MAINTAINER + 1];
  char *maintainer_web_site[PACKAGE_MAX_MAINTAINER + 1];
  char *maintainer_ftp_site[PACKAGE_MAX_MAINTAINER + 1];
	
  /* + 1 for NULL list terminator */
  char *porter[PACKAGE_MAX_PORTER + 1];
  char *porter_email[PACKAGE_MAX_PORTER + 1];
  char *porter_im[PACKAGE_MAX_PORTER + 1];
  char *porter_web_site[PACKAGE_MAX_PORTER + 1];
  char *porter_ftp_site[PACKAGE_MAX_PORTER + 1];
  char *porting_web_site[PACKAGE_MAX_PORTER + 1];
  char *porting_ftp_site[PACKAGE_MAX_PORTER + 1];
  
  /* + 1 for NULL list terminator */
  char *mailing_list[PACKAGE_MAX_MAILINGLIST + 1]; 
  char *mailing_list_description[PACKAGE_MAX_MAILINGLIST + 1];
  char *mailing_list_request[PACKAGE_MAX_MAILINGLIST + 1];
  char *mailing_list_administrator[PACKAGE_MAX_MAILINGLIST + 1];
  char *mailing_list_administrator_email[PACKAGE_MAX_MAILINGLIST + 1];
  char *mailing_list_administrator_im[PACKAGE_MAX_MAILINGLIST + 1];
  char *mailing_list_web_site[PACKAGE_MAX_MAILINGLIST + 1];
  char *mailing_list_ftp_site[PACKAGE_MAX_MAILINGLIST + 1];

  char *newsgroup[PACKAGE_MAX_NEWSGROUP + 1];
  char *newsgroup_description[PACKAGE_MAX_NEWSGROUP + 1];
  char *newsgroup_email_gateway[PACKAGE_MAX_NEWSGROUP + 1];
  char *newsgroup_administrator[PACKAGE_MAX_NEWSGROUP + 1];
  char *newsgroup_administrator_email[PACKAGE_MAX_NEWSGROUP + 1];
  char *newsgroup_administrator_im[PACKAGE_MAX_NEWSGROUP + 1];
  char *newsgroup_web_site[PACKAGE_MAX_NEWSGROUP + 1];
  char *newsgroup_ftp_site[PACKAGE_MAX_NEWSGROUP + 1];

  /* Package file details */
  char simtelnet_path[PACKAGE_MAXSIMTELNETPATH];
  char *zip[PACKAGE_MAX_ARCHIVE + 1]; /* + 1 for NULL list terminator */
  char *zip_options;
  char *tar_gzip[PACKAGE_MAX_ARCHIVE + 1]; /* +1 for NULL list term. */
  char *tar_gzip_options;

  /* TODO: Implement support for tar-gzip-* */

  /* Changelog */
  char *changelog;
	
  /* Installation */
  char *pre_install_readme;
  char *post_install_readme;
  char *pre_uninstall_readme;
  char *post_uninstall_readme;

  char *builtin_pre_install_script;
  char *builtin_post_install_script;
  char *builtin_pre_uninstall_script;
  char *builtin_post_uninstall_script;

  char *pre_install_script;
  char *post_install_script;
  char *pre_uninstall_script;
  char *post_uninstall_script;

  /* Files that should not be overwritten on installation or removed
   * on uninstallation. */
  char *keep_file[PACKAGE_MAX_KEEP_FILE];

  char *prefix;

  /* Leave space for NULL terminating list. */
  PACKAGE_DEP *deps[PACKAGE_MAX_DEP + 1];
  int duplicate_action;

  char *install_warning;
} PACKAGE_INFO;

/* Functions */

extern char *package_operator_string (const int op);
extern char *package_version_l0_string (const int n);
extern char *package_version_string (const PACKAGE_VERSION *ver);
extern char *package_type_string (const PACKAGE_VERSION *ver);
extern char *package_dep_string (const PACKAGE_DEP *dep);
extern const char *package_dep_type_string (const int dep_type);

extern int package_version_wildcard (PACKAGE_VERSION *ver);

extern int package_namecmp (const char *name1, const char *name2);

extern int package_vercmp (const PACKAGE_VERSION *ver1, 
                           const PACKAGE_VERSION *ver2);

extern int package_vercmp_partial (const PACKAGE_VERSION *ver1,
				   const PACKAGE_VERSION *ver2);

extern int package_free (PACKAGE_INFO *p);

extern int package_set_defaults (PACKAGE_INFO *package);

#ifdef __cplusplus
}
#endif

#endif	/* __libpakke_package_h__ */
