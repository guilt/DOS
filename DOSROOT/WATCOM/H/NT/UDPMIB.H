/*
 *  udpmib.h    UDP Management Information Base (MIB) definitions
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

#ifndef _UDPMIB_
#define _UDPMIB_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Value used to declare an array of an unknown size */
#ifndef ANY_SIZE
    #define ANY_SIZE    1
#endif

/* TCP/IP owning module size */
#ifndef TCPIP_OWNING_MODULE_SIZE
    #define TCPIP_OWNING_MODULE_SIZE    16
#endif

/* MIB UDP row */
typedef struct _MIB_UDPROW {
    DWORD   dwLocalAddr;
    DWORD   dwLocalPort;
} MIB_UDPROW;
typedef MIB_UDPROW  *PMIB_UDPROW;

/* MIB UDP table */
typedef struct _MIB_UDPTABLE {
    DWORD       dwNumEntries;
    MIB_UDPROW  table[ANY_SIZE];
} MIB_UDPTABLE;
typedef MIB_UDPTABLE    *PMIB_UDPTABLE;

/* MIB UDP row owner protocol identifier */
typedef struct _MIB_UDPROW_OWNER_PID {
    DWORD   dwLocalAddr;
    DWORD   dwLocalPort;
    DWORD   dwOwningPid;
} MIB_UDPROW_OWNER_PID;
typedef MIB_UDPROW_OWNER_PID    *PMIB_UDPROW_OWNER_PID;

/* MIB UDP table owner protocol identifier */
typedef struct _MIB_UDPTABLE_OWNER_PID {
    DWORD                   dwNumEntries;
    MIB_UDPROW_OWNER_PID    table[ANY_SIZE];
} MIB_UDPTABLE_OWNER_PID;
typedef MIB_UDPTABLE_OWNER_PID  *PMIB_UDPTABLE_OWNER_PID;

/* MIB UDP row owner module */
typedef struct _MIB_UDPROW_OWNER_MODULE {
    DWORD           dwLocalAddr;
    DWORD           dwLocalPort;
    DWORD           dwOwningPid;
    LARGE_INTEGER   liCreateTimestamp;
    union {
        struct {
            int SpecificPortBind    : 1;
        };
        int dwFlags;
    };
    ULONGLONG       OwningModuleInfo[TCPIP_OWNING_MODULE_SIZE];
} MIB_UDPROW_OWNER_MODULE;
typedef MIB_UDPROW_OWNER_MODULE *PMIB_UDPROW_OWNER_MODULE;

/* MIB UDP table owner module */
typedef struct _MIB_UDPTABLE_OWNER_MODULE {
    DWORD                   dwNumEntries;
    MIB_UDPROW_OWNER_MODULE table[ANY_SIZE];
} MIB_UDPTABLE_OWNER_MODULE;
typedef MIB_UDPTABLE_OWNER_MODULE   *PMIB_UDPTABLE_OWNER_MODULE;

/* MIB UDPv6 row */
#ifdef _WINSOCK2API_
typedef struct _MIB_UDP6ROW {
    IN6_ADDR    dwLocalAddr;
    DWORD       dwLocalScopeId;
    DWORD       dwLocalPort;
} MIB_UDP6ROW;
typedef MIB_UDP6ROW *PMIB_UDP6ROW;
#endif

/* MIB UDPv6 table */
#ifdef _WINSOCK2API_
typedef struct _MIB_UDP6TABLE {
    DWORD       dwNumEntries;
    MIB_UDP6ROW table[ANY_SIZE];
} MIB_UDP6TABLE;
typedef MIB_UDP6TABLE   *PMIB_UDP6TABLE;
#endif

/* MIB UDPv6 row owner protocol identifier */
#ifdef _WINSOCK2API_
typedef struct _MIB_UDP6ROW_OWNER_PID {
    UCHAR   ucLocalAddr[16];
    DWORD   dwLocalScopeId;
    DWORD   dwLocalPort;
    DWORD   dwOwningPid;
} MIB_UDP6ROW_OWNER_PID;
typedef MIB_UDP6ROW_OWNER_PID   *PMIB_UDP6ROW_OWNER_PID;
#endif

/* MIB UDPv6 table owner protocol identifier */
#ifdef _WINSOCK2API_
typedef struct _MIB_UDP6TABLE_OWNER_PID {
    DWORD                   dwNumEntries;
    MIB_UDP6ROW_OWNER_PID   table[ANY_SIZE];
} MIB_UDP6TABLE_OWNER_PID;
typedef MIB_UDP6TABLE_OWNER_PID *PMIB_UDP6TABLE_OWNER_PID;
#endif

/* MIB UDPv6 row owner module */
#ifdef _WINSOCK2API_
typedef struct _MIB_UDP6ROW_OWNER_MODULE {
    UCHAR           ucLocalAddr[16];
    DWORD           dwLocalScopeId;
    DWORD           dwLocalPort;
    DWORD           dwOwningPid;
    LARGE_INTEGER   liCreateTimestamp;
    union {
        struct {
            int SpecificPortBind    : 1;
        };
        int dwFlags;
    };
    ULONGLONG       OwningModuleInfo[TCPIP_OWNING_MODULE_SIZE];
} MIB_UDP6ROW_OWNER_MODULE;
typedef MIB_UDP6ROW_OWNER_MODULE    *PMIB_UDP6ROW_OWNER_MODULE;
#endif

/* MIB UDPv6 table owner module */
#ifdef _WINSOCK2API_
typedef struct _MIB_UDP6TABLE_OWNER_MODULE {
    DWORD                       dwNumEntries;
    MIB_UDP6ROW_OWNER_MODULE    table[ANY_SIZE];
} MIB_UDP6TABLE_OWNER_MODULE;
typedef MIB_UDP6TABLE_OWNER_MODULE  *PMIB_UDP6TABLE_OWNER_MODULE;
#endif

/* MIB UDP statistics */
typedef struct _MIB_UDPSTATS {
    DWORD   dwInDatagrams;
    DWORD   dwNoPorts;
    DWORD   dwInErrors;
    DWORD   dwOutDatagrams;
    DWORD   dwNumAddrs;
} MIB_UDPSTATS;
typedef MIB_UDPSTATS    *PMIB_UDPSTATS;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _UDPMIB_ */
