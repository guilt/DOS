/*
 *  lmconfig.h  LAN Manager configuration functions
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */

#ifndef _LMCONFIG_
#define _LMCONFIG_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Configuration information (level 0) */
typedef struct _CONFIG_INFO_0 {
    LPWSTR  cfgi0_key;
    LPWSTR  cfgi0_data;
} CONFIG_INFO_0;
typedef CONFIG_INFO_0   *PCONFIG_INFO_0;
typedef CONFIG_INFO_0   *LPCONFIG_INFO_0;

/* Functions in NETAPI32.DLL */
NET_API_STATUS NET_API_FUNCTION NetConfigGet( LPCWSTR, LPCWSTR, LPCWSTR, LPBYTE * );
NET_API_STATUS NET_API_FUNCTION NetConfigGetAll( LPCWSTR, LPCWSTR, LPBYTE * );
NET_API_STATUS NET_API_FUNCTION NetConfigSet( LPCWSTR, LPCWSTR, LPCWSTR, DWORD, DWORD, LPBYTE, DWORD );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _LMCONFIG_ */
