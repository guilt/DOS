/*
 *  sys/un.h      Sockets for local interprocess communication (AF_UNIX)
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
 * Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */
#ifndef _SYS_UN_H_INCLUDED
#define _SYS_UN_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack( __push, 4 )

#define UNIX_PATH_MAX   108

#ifndef _SA_FAMILY_T_DEFINED_
#define _SA_FAMILY_T_DEFINED_
typedef unsigned short sa_family_t;
#endif

struct sockaddr_un {
    sa_family_t  sun_family;              /* AF_UNIX */
    char         sun_path[UNIX_PATH_MAX]; /* pathname */
};

#pragma pack( __pop )

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !_SYS_UN_H_INCLUDED */
