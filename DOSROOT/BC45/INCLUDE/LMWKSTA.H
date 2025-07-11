/*++ BUILD Version: 0006    // Increment this if a change has global effects

Module Name:

    lmwksta.h

Abstract:

    This file contains structures, function prototypes, and definitions
    for the NetWorkstation and NetWkstaTransport API.

Author:

    Dan Lafferty (danl) 10-Mar-1991

Environment:

    User Mode - Win32
    Portable to any flat, 32-bit environment.  (Uses Win32 typedefs.)
    Requires ANSI C extensions: slash-slash comments, long external names.

Notes:

    You must include NETCONS.H before this file, since this file depends
    on values defined in NETCONS.H.

Revision History:

    10-Mar-1991 danl
        Created from LM2.0 header files and NT-LAN API Spec.
    14-Mar-91 JohnRo
        Added OPTIONAL keyword again.  Fixed NetWkstaGetInfo parm list
        (it shouldn't have a trailing comma).
    19-Mar-91 ritaw
        Added parm_err to NetWkstaTransportAdd.
        Removed UseOpBatch and PadValue1 fields from WKSTA_INFO_502.
    29-Mar-91 ritaw
        Added NetWkstaUserGetInfo and NetWkstaUserEnum, removed
        WKSTA_INFO_201, and WKSTA_INFO_202.
    14-Apr-91 w-shanku
        Moved oth_domains and lanroot fields to same order as OS/2
        structures, changed ParmNum constants to be consistent with
        OS/2 parmnums.
    1-May-1991  larryo
        Added cached file timeout parameter.
    9-May-1991 ritaw
        Changed LPSTR to LPTSTR.
        Moved oth_domains to DOS and OS/2 specific info structures.
        Added max_threads and char_wait to WKSTA_INFO_502.
        Renamed wki502_session_timeout to wki502_sess_timeout.
        Added lan_root to WKSTA_INFO_101.
    29-Jul-1991 JohnRo
        Implement downlevel NetWksta APIs (set info parm_err is OPTIONAL).
    16-Aug-1991 JohnRo
        NetWksta parmnum changes (for downlevel support).
    18-Sep-1991 ritaw
        Moved oth_domains from DOS and OS/2 specific info structures
        to WKSTA_USER_INFO_1.
    16-Mar-1992 colinw
        Remove wki502_siz_work_buf (now a constant) and wki502_num_work_buf ( Use
        wki502_max_cmds instead).

--*/

/*
 *      C/C++ Run Time Library - Version 6.5
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 */

#ifndef _LMWKSTA_
#define _LMWKSTA_
#define __LMWKSTA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lmuseflg.h>                   // Deletion force level flags

//
// Function Prototypes
//

NET_API_STATUS NET_API_FUNCTION
NetWkstaGetInfo (
    IN  LPTSTR  servername OPTIONAL,
    IN  DWORD   level,
    OUT LPBYTE  *bufptr
    );

NET_API_STATUS NET_API_FUNCTION
NetWkstaSetInfo (
    IN  LPTSTR  servername OPTIONAL,
    IN  DWORD   level,
    IN  LPBYTE  buffer,
    OUT LPDWORD parm_err OPTIONAL
    );

NET_API_STATUS NET_API_FUNCTION
NetWkstaUserGetInfo (
    IN  LPTSTR reserved,
    IN  DWORD   level,
    OUT LPBYTE  *bufptr
    );

NET_API_STATUS NET_API_FUNCTION
NetWkstaUserSetInfo (
    IN  LPTSTR reserved,
    IN  DWORD   level,
    OUT LPBYTE  buf,
    OUT LPDWORD parm_err OPTIONAL
    );

NET_API_STATUS NET_API_FUNCTION
NetWkstaUserEnum (
    IN  LPTSTR      servername OPTIONAL,
    IN  DWORD       level,
    OUT LPBYTE      *bufptr,
    IN  DWORD       prefmaxlen,
    OUT LPDWORD     entriesread,
    OUT LPDWORD     totalentries,
    IN  OUT LPDWORD resumehandle OPTIONAL
    );

NET_API_STATUS NET_API_FUNCTION
NetWkstaTransportAdd (
    IN  LPTSTR  servername OPTIONAL,
    IN  DWORD   level,
    IN  LPBYTE  buf,
    OUT LPDWORD parm_err
    );

NET_API_STATUS NET_API_FUNCTION
NetWkstaTransportDel (
    IN  LPTSTR  servername OPTIONAL,
    IN  LPTSTR  transportname,
    IN  DWORD   ucond
    );

NET_API_STATUS NET_API_FUNCTION
NetWkstaTransportEnum (
    IN  LPTSTR      servername OPTIONAL,
    IN  DWORD       level,
    OUT LPBYTE      *bufptr,
    IN  DWORD       prefmaxlen,
    OUT LPDWORD     entriesread,
    OUT LPDWORD     totalentries,
    IN  OUT LPDWORD resumehandle OPTIONAL
    );

//
//  Data Structures
//

//
// NetWkstaGetInfo and NetWkstaSetInfo
//

//
// NetWkstaGetInfo only.  System information - guest access
//
typedef struct _WKSTA_INFO_100 {
    DWORD   wki100_platform_id;
    LPTSTR  wki100_computername;
    LPTSTR  wki100_langroup;
    DWORD   wki100_ver_major;
    DWORD   wki100_ver_minor;
}WKSTA_INFO_100, *PWKSTA_INFO_100, *LPWKSTA_INFO_100;

//
// NetWkstaGetInfo only.  System information - user access
//
typedef struct _WKSTA_INFO_101 {
    DWORD   wki101_platform_id;
    LPTSTR  wki101_computername;
    LPTSTR  wki101_langroup;
    DWORD   wki101_ver_major;
    DWORD   wki101_ver_minor;
    LPTSTR  wki101_lanroot;
}WKSTA_INFO_101, *PWKSTA_INFO_101, *LPWKSTA_INFO_101;

//
// NetWkstaGetInfo only.  System information - admin or operator access
//
typedef struct _WKSTA_INFO_102 {
    DWORD   wki102_platform_id;
    LPTSTR  wki102_computername;
    LPTSTR  wki102_langroup;
    DWORD   wki102_ver_major;
    DWORD   wki102_ver_minor;
    LPTSTR  wki102_lanroot;
    DWORD   wki102_logged_on_users;
}WKSTA_INFO_102, *PWKSTA_INFO_102, *LPWKSTA_INFO_102;

//
// Down-level NetWkstaGetInfo and NetWkstaSetInfo.
//
// DOS specific workstation information -
//    admin or domain operator access
//
typedef struct _WKSTA_INFO_302{
    DWORD   wki302_char_wait;
    DWORD   wki302_collection_time;
    DWORD   wki302_maximum_collection_count;
    DWORD   wki302_keep_conn;
    DWORD   wki302_keep_search;
    DWORD   wki302_max_cmds;
    DWORD   wki302_num_work_buf;
    DWORD   wki302_siz_work_buf;
    DWORD   wki302_max_wrk_cache;
    DWORD   wki302_sess_timeout;
    DWORD   wki302_siz_error;
    DWORD   wki302_num_alerts;
    DWORD   wki302_num_services;
    DWORD   wki302_errlog_sz;
    DWORD   wki302_print_buf_time;
    DWORD   wki302_num_char_buf;
    DWORD   wki302_siz_char_buf;
    LPTSTR  wki302_wrk_heuristics;
    DWORD   wki302_mailslots;
    DWORD   wki302_num_dgram_buf;
}WKSTA_INFO_302, *PWKSTA_INFO_302, *LPWKSTA_INFO_302;

//
// Down-level NetWkstaGetInfo and NetWkstaSetInfo
//
// OS/2 specific workstation information -
//    admin or domain operator access
//
typedef struct _WKSTA_INFO_402{
    DWORD   wki402_char_wait;
    DWORD   wki402_collection_time;
    DWORD   wki402_maximum_collection_count;
    DWORD   wki402_keep_conn;
    DWORD   wki402_keep_search;
    DWORD   wki402_max_cmds;
    DWORD   wki402_num_work_buf;
    DWORD   wki402_siz_work_buf;
    DWORD   wki402_max_wrk_cache;
    DWORD   wki402_sess_timeout;
    DWORD   wki402_siz_error;
    DWORD   wki402_num_alerts;
    DWORD   wki402_num_services;
    DWORD   wki402_errlog_sz;
    DWORD   wki402_print_buf_time;
    DWORD   wki402_num_char_buf;
    DWORD   wki402_siz_char_buf;
    LPTSTR  wki402_wrk_heuristics;
    DWORD   wki402_mailslots;
    DWORD   wki402_num_dgram_buf;
    DWORD   wki402_max_threads;
}WKSTA_INFO_402, *PWKSTA_INFO_402, *LPWKSTA_INFO_402;

//
// Same-level NetWkstaGetInfo and NetWkstaSetInfo.
//
// NT specific workstation information -
//    admin or domain operator access
//
typedef struct _WKSTA_INFO_502{
    DWORD   wki502_char_wait;
    DWORD   wki502_collection_time;
    DWORD   wki502_maximum_collection_count;
    DWORD   wki502_keep_conn;
    DWORD   wki502_max_cmds;
    DWORD   wki502_sess_timeout;
    DWORD   wki502_siz_char_buf;
    DWORD   wki502_max_threads;

    DWORD   wki502_lock_quota;
    DWORD   wki502_lock_increment;
    DWORD   wki502_lock_maximum;
    DWORD   wki502_pipe_increment;
    DWORD   wki502_pipe_maximum;
    DWORD   wki502_cache_file_timeout;
    DWORD   wki502_dormant_file_limit;
    DWORD   wki502_read_ahead_throughput;

    DWORD   wki502_num_mailslot_buffers;
    DWORD   wki502_num_srv_announce_buffers;
    DWORD   wki502_max_illegal_datagram_events;
    DWORD   wki502_illegal_datagram_event_reset_frequency;
    BOOL    wki502_log_election_packets;

    BOOL    wki502_use_opportunistic_locking;
    BOOL    wki502_use_unlock_behind;
    BOOL    wki502_use_close_behind;
    BOOL    wki502_buf_named_pipes;
    BOOL    wki502_use_lock_read_unlock;
    BOOL    wki502_utilize_nt_caching;
    BOOL    wki502_use_raw_read;
    BOOL    wki502_use_raw_write;
    BOOL    wki502_use_write_raw_data;
    BOOL    wki502_use_encryption;
    BOOL    wki502_buf_files_deny_write;
    BOOL    wki502_buf_read_only_files;
    BOOL    wki502_force_core_create_mode;
    BOOL    wki502_use_512_byte_max_transfer;
}WKSTA_INFO_502, *PWKSTA_INFO_502, *LPWKSTA_INFO_502;


//
// The following info-levels are only valid for NetWkstaSetInfo
//

//
// The following levels are supported on down-level systems (LAN Man 2.x)
// as well as NT systems:
//
typedef struct _WKSTA_INFO_1010 {
     DWORD  wki1010_char_wait;
} WKSTA_INFO_1010, *PWKSTA_INFO_1010, *LPWKSTA_INFO_1010;

typedef struct _WKSTA_INFO_1011 {
     DWORD  wki1011_collection_time;
} WKSTA_INFO_1011, *PWKSTA_INFO_1011, *LPWKSTA_INFO_1011;

typedef struct _WKSTA_INFO_1012 {
     DWORD  wki1012_maximum_collection_count;
} WKSTA_INFO_1012, *PWKSTA_INFO_1012, *LPWKSTA_INFO_1012;

//
// The following level are supported on down-level systems (LAN Man 2.x)
// only:
//
typedef struct _WKSTA_INFO_1027 {
     DWORD  wki1027_errlog_sz;
} WKSTA_INFO_1027, *PWKSTA_INFO_1027, *LPWKSTA_INFO_1027;

typedef struct _WKSTA_INFO_1028 {
     DWORD  wki1028_print_buf_time;
} WKSTA_INFO_1028, *PWKSTA_INFO_1028, *LPWKSTA_INFO_1028;

typedef struct _WKSTA_INFO_1032 {
     DWORD  wki1032_wrk_heuristics;
} WKSTA_INFO_1032, *PWKSTA_INFO_1032, *LPWKSTA_INFO_1032;

//
// The following levels are settable on NT systems, and have no
// effect on down-level systems (i.e. LANMan 2.x) since these
// fields cannot be set on them:
//
typedef struct _WKSTA_INFO_1013 {
     DWORD  wki1013_keep_conn;
} WKSTA_INFO_1013, *PWKSTA_INFO_1013, *LPWKSTA_INFO_1013;

typedef struct _WKSTA_INFO_1018 {
     DWORD  wki1018_sess_timeout;
} WKSTA_INFO_1018, *PWKSTA_INFO_1018, *LPWKSTA_INFO_1018;

typedef struct _WKSTA_INFO_1023 {
     DWORD  wki1023_siz_char_buf;
} WKSTA_INFO_1023, *PWKSTA_INFO_1023, *LPWKSTA_INFO_1023;

typedef struct _WKSTA_INFO_1033 {
     DWORD  wki1033_max_threads;
} WKSTA_INFO_1033, *PWKSTA_INFO_1033, *LPWKSTA_INFO_1033;

//
// The following levels are only supported on NT systems:
//
typedef struct _WKSTA_INFO_1041 {
    DWORD   wki1041_lock_quota;
} WKSTA_INFO_1041, *PWKSTA_INFO_1041, *LPWKSTA_INFO_1041;

typedef struct _WKSTA_INFO_1042 {
    DWORD   wki1042_lock_increment;
} WKSTA_INFO_1042, *PWKSTA_INFO_1042, *LPWKSTA_INFO_1042;

typedef struct _WKSTA_INFO_1043 {
    DWORD   wki1043_lock_maximum;
} WKSTA_INFO_1043, *PWKSTA_INFO_1043, *LPWKSTA_INFO_1043;

typedef struct _WKSTA_INFO_1044 {
    DWORD   wki1044_pipe_increment;
} WKSTA_INFO_1044, *PWKSTA_INFO_1044, *LPWKSTA_INFO_1044;

typedef struct _WKSTA_INFO_1045 {
    DWORD   wki1045_pipe_maximum;
} WKSTA_INFO_1045, *PWKSTA_INFO_1045, *LPWKSTA_INFO_1045;

typedef struct _WKSTA_INFO_1046 {
    DWORD   wki1046_dormant_file_limit;
} WKSTA_INFO_1046, *PWKSTA_INFO_1046, *LPWKSTA_INFO_1046;

typedef struct _WKSTA_INFO_1047 {
    DWORD    wki1047_cache_file_timeout;
} WKSTA_INFO_1047, *PWKSTA_INFO_1047, *LPWKSTA_INFO_1047;

typedef struct _WKSTA_INFO_1048 {
    BOOL     wki1048_use_opportunistic_locking;
} WKSTA_INFO_1048, *PWKSTA_INFO_1048, *LPWKSTA_INFO_1048;

typedef struct _WKSTA_INFO_1049 {
    BOOL     wki1049_use_unlock_behind;
} WKSTA_INFO_1049, *PWKSTA_INFO_1049, *LPWKSTA_INFO_1049;

typedef struct _WKSTA_INFO_1050 {
    BOOL     wki1050_use_close_behind;
} WKSTA_INFO_1050, *PWKSTA_INFO_1050, *LPWKSTA_INFO_1050;

typedef struct _WKSTA_INFO_1051 {
    BOOL     wki1051_buf_named_pipes;
} WKSTA_INFO_1051, *PWKSTA_INFO_1051, *LPWKSTA_INFO_1051;

typedef struct _WKSTA_INFO_1052 {
    BOOL     wki1052_use_lock_read_unlock;
} WKSTA_INFO_1052, *PWKSTA_INFO_1052, *LPWKSTA_INFO_1052;

typedef struct _WKSTA_INFO_1053 {
    BOOL     wki1053_utilize_nt_caching;
} WKSTA_INFO_1053, *PWKSTA_INFO_1053, *LPWKSTA_INFO_1053;

typedef struct _WKSTA_INFO_1054 {
    BOOL     wki1054_use_raw_read;
} WKSTA_INFO_1054, *PWKSTA_INFO_1054, *LPWKSTA_INFO_1054;

typedef struct _WKSTA_INFO_1055 {
    BOOL     wki1055_use_raw_write;
} WKSTA_INFO_1055, *PWKSTA_INFO_1055, *LPWKSTA_INFO_1055;

typedef struct _WKSTA_INFO_1056 {
    BOOL     wki1056_use_write_raw_data;
} WKSTA_INFO_1056, *PWKSTA_INFO_1056, *LPWKSTA_INFO_1056;

typedef struct _WKSTA_INFO_1057 {
    BOOL     wki1057_use_encryption;
} WKSTA_INFO_1057, *PWKSTA_INFO_1057, *LPWKSTA_INFO_1057;

typedef struct _WKSTA_INFO_1058 {
    BOOL     wki1058_buf_files_deny_write;
} WKSTA_INFO_1058, *PWKSTA_INFO_1058, *LPWKSTA_INFO_1058;

typedef struct _WKSTA_INFO_1059 {
    BOOL     wki1059_buf_read_only_files;
} WKSTA_INFO_1059, *PWKSTA_INFO_1059, *LPWKSTA_INFO_1059;

typedef struct _WKSTA_INFO_1060 {
    BOOL     wki1060_force_core_create_mode;
} WKSTA_INFO_1060, *PWKSTA_INFO_1060, *LPWKSTA_INFO_1060;

typedef struct _WKSTA_INFO_1061 {
    BOOL     wki1061_use_512_byte_max_transfer;
} WKSTA_INFO_1061, *PWKSTA_INFO_1061, *LPWKSTA_INFO_1061;

typedef struct _WKSTA_INFO_1062 {
    DWORD   wki1062_read_ahead_throughput;
} WKSTA_INFO_1062, *PWKSTA_INFO_1062, *LPWKSTA_INFO_1062;


//
// NetWkstaUserGetInfo (local only) and NetWkstaUserEnum -
//     no access restrictions.
//
typedef struct _WKSTA_USER_INFO_0 {
    LPTSTR  wkui0_username;
}WKSTA_USER_INFO_0, *PWKSTA_USER_INFO_0, *LPWKSTA_USER_INFO_0;

//
// NetWkstaUserGetInfo (local only) and NetWkstaUserEnum -
//     no access restrictions.
//
typedef struct _WKSTA_USER_INFO_1 {
    LPTSTR  wkui1_username;
    LPTSTR  wkui1_logon_domain;
    LPTSTR  wkui1_oth_domains;
    LPTSTR  wkui1_logon_server;
}WKSTA_USER_INFO_1, *PWKSTA_USER_INFO_1, *LPWKSTA_USER_INFO_1;

//
// NetWkstaUserSetInfo - local access.
//
typedef struct _WKSTA_USER_INFO_1101 {
     LPTSTR  wkui1101_oth_domains;
} WKSTA_USER_INFO_1101, *PWKSTA_USER_INFO_1101,
  *LPWKSTA_USER_INFO_1101;


//
// NetWkstaTransportAdd - admin access
//
typedef struct _WKSTA_TRANSPORT_INFO_0 {
    DWORD   wkti0_quality_of_service;
    DWORD   wkti0_number_of_vcs;
    LPTSTR  wkti0_transport_name;
    LPTSTR  wkti0_transport_address;
    BOOL    wkti0_wan_ish;
}WKSTA_TRANSPORT_INFO_0, *PWKSTA_TRANSPORT_INFO_0,
 *LPWKSTA_TRANSPORT_INFO_0;


//
// Special Values and Constants
//

//
//  Identifiers for use as NetWkstaSetInfo parmnum parameter
//

//
// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetWkstaSetInfo.
//

#define WKSTA_PLATFORM_ID_PARMNUM               100
#define WKSTA_COMPUTERNAME_PARMNUM              1
#define WKSTA_LANGROUP_PARMNUM                  2
#define WKSTA_VER_MAJOR_PARMNUM                 4
#define WKSTA_VER_MINOR_PARMNUM                 5
#define WKSTA_LOGGED_ON_USERS_PARMNUM           6
#define WKSTA_LANROOT_PARMNUM                   7
#define WKSTA_LOGON_DOMAIN_PARMNUM              8
#define WKSTA_LOGON_SERVER_PARMNUM              9
#define WKSTA_CHARWAIT_PARMNUM                  10  // Supported by down-level.
#define WKSTA_CHARTIME_PARMNUM                  11  // Supported by down-level.
#define WKSTA_CHARCOUNT_PARMNUM                 12  // Supported by down-level.
#define WKSTA_KEEPCONN_PARMNUM                  13
#define WKSTA_KEEPSEARCH_PARMNUM                14
#define WKSTA_MAXCMDS_PARMNUM                   15
#define WKSTA_NUMWORKBUF_PARMNUM                16
#define WKSTA_MAXWRKCACHE_PARMNUM               17
#define WKSTA_SESSTIMEOUT_PARMNUM               18
#define WKSTA_SIZERROR_PARMNUM                  19
#define WKSTA_NUMALERTS_PARMNUM                 20
#define WKSTA_NUMSERVICES_PARMNUM               21
#define WKSTA_NUMCHARBUF_PARMNUM                22
#define WKSTA_SIZCHARBUF_PARMNUM                23
#define WKSTA_ERRLOGSZ_PARMNUM                  27  // Supported by down-level.
#define WKSTA_PRINTBUFTIME_PARMNUM              28  // Supported by down-level.
#define WKSTA_SIZWORKBUF_PARMNUM                29
#define WKSTA_MAILSLOTS_PARMNUM                 30
#define WKSTA_NUMDGRAMBUF_PARMNUM               31
#define WKSTA_WRKHEURISTICS_PARMNUM             32  // Supported by down-level.
#define WKSTA_MAXTHREADS_PARMNUM                33

#define WKSTA_LOCKQUOTA_PARMNUM                 41
#define WKSTA_LOCKINCREMENT_PARMNUM             42
#define WKSTA_LOCKMAXIMUM_PARMNUM               43
#define WKSTA_PIPEINCREMENT_PARMNUM             44
#define WKSTA_PIPEMAXIMUM_PARMNUM               45
#define WKSTA_DORMANTFILELIMIT_PARMNUM          46
#define WKSTA_CACHEFILETIMEOUT_PARMNUM          47
#define WKSTA_USEOPPORTUNISTICLOCKING_PARMNUM   48
#define WKSTA_USEUNLOCKBEHIND_PARMNUM           49
#define WKSTA_USECLOSEBEHIND_PARMNUM            50
#define WKSTA_BUFFERNAMEDPIPES_PARMNUM          51
#define WKSTA_USELOCKANDREADANDUNLOCK_PARMNUM   52
#define WKSTA_UTILIZENTCACHING_PARMNUM          53
#define WKSTA_USERAWREAD_PARMNUM                54
#define WKSTA_USERAWWRITE_PARMNUM               55
#define WKSTA_USEWRITERAWWITHDATA_PARMNUM       56
#define WKSTA_USEENCRYPTION_PARMNUM             57
#define WKSTA_BUFFILESWITHDENYWRITE_PARMNUM     58
#define WKSTA_BUFFERREADONLYFILES_PARMNUM       59
#define WKSTA_FORCECORECREATEMODE_PARMNUM       60
#define WKSTA_USE512BYTESMAXTRANSFER_PARMNUM    61
#define WKSTA_READAHEADTHRUPUT_PARMNUM          62


//
// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetWkstaUserSetInfo.
//

#define WKSTA_OTH_DOMAINS_PARMNUM              101


//
// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetWkstaTransportAdd.
//

#define TRANSPORT_QUALITYOFSERVICE_PARMNUM     201
#define TRANSPORT_NAME_PARMNUM                 202

#ifdef __cplusplus
}
#endif

#endif // _LMWKSTA_
