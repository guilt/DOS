/*
 *  dhcpcsdk.h  Dynamic Host Control Protocol (DHCP) client functions
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

#ifndef _DHCPCSDK_
#define _DHCPCSDK_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* DHCP options */
#define OPTION_PAD                      0L
#define OPTION_SUBNET_MASK              1L
#define OPTION_TIME_OFFSET              2L
#define OPTION_ROUTER_ADDRESS           3L
#define OPTION_TIME_SERVERS             4L
#define OPTION_IEN116_NAME_SERVERS      5L
#define OPTION_DOMAIN_NAME_SERVERS      6L
#define OPTION_LOG_SERVERS              7L
#define OPTION_COOKIE_SERVERS           8L
#define OPTION_LPR_SERVERS              9L
#define OPTION_IMPRESS_SERVERS          10L
#define OPTION_RLP_SERVERS              11L
#define OPTION_HOST_NAME                12L
#define OPTION_BOOT_FILE_SIZE           13L
#define OPTION_MERIT_DUMP_FILE          14L
#define OPTION_DOMAIN_NAME              15L
#define OPTION_SWAP_SERVER              16L
#define OPTION_ROOT_DISK                17L
#define OPTION_EXTENSIONS_PATH          18L
#define OPTION_BE_A_ROUTER              19L
#define OPTION_NON_LOCAL_SOURCE_ROUTING 20L
#define OPTION_POLICY_FILTER_FOR_NLSR   21L
#define OPTION_MAX_REASSEMBLY_SIZE      22L
#define OPTION_DEFAULT_TTL              23L
#define OPTION_PMTU_AGING_TIMEOUT       24L
#define OPTION_PMTU_PLATEAU_TABLE       25L
#define OPTION_MTU                      26L
#define OPTION_ALL_SUBNETS_MTU          27L
#define OPTION_BROADCAST_ADDRESS        28L
#define OPTION_PERFORM_MASK_DISCOVERY   29L
#define OPTION_BE_A_MASK_SUPPLIER       30L
#define OPTION_PERFORM_ROUTER_DISCOVERY 31L
#define OPTION_ROUTER_SOLICITATION_ADDR 32L
#define OPTION_STATIC_ROUTES            33L
#define OPTION_TRAILERS                 34L
#define OPTION_ARP_CACHE_TIMEOUT        35L
#define OPTION_ETHERNET_ENCAPSULATION   36L
#define OPTION_TTL                      37L
#define OPTION_KEEP_ALIVE_INTERVAL      38L
#define OPTION_KEEP_ALIVE_DATA_SIZE     39L
#define OPTION_NETWORK_INFO_SERVICE_DOM 40L
#define OPTION_NETWORK_INFO_SERVERS     41L
#define OPTION_NETWORK_TIME_SERVERS     42L
#define OPTION_VENDOR_SPECIFIC_INFO     43L
#define OPTION_NETBIOS_NAME_SERVER      44L
#define OPTION_NETBIOS_DATAGRAM_SERVER  45L
#define OPTION_NETBIOS_NODE_TYPE        46L
#define OPTION_NETBIOS_SCOPE_OPTION     47L
#define OPTION_XWINDOW_FONT_SERVER      48L
#define OPTION_XWINDOW_DISPLAY_MANAGER  49L
#define OPTION_REQUESTED_ADDRESS        50L
#define OPTION_LEASE_TIME               51L
#define OPTION_OK_TO_OVERLAY            52L
#define OPTION_MESSAGE_TYPE             53L
#define OPTION_SERVER_IDENTIFIER        54L
#define OPTION_PARAMETER_REQUEST_LIST   55L
#define OPTION_MESSAGE                  56L
#define OPTION_MESSAGE_LENGTH           57L
#define OPTION_RENEWAL_TIME             58L
#define OPTION_REBIND_TIME              59L
#define OPTION_CLIENT_CLASS_INFO        60L
#define OPTION_CLIENT_ID                61L
#define OPTION_TFTP_SERVER_NAME         66L
#define OPTION_BOOTFILE_NAME            67L
#define OPTION_END                      255L

/* DhcpRequestParams() flags */
#define DHCPCAPI_REQUEST_PERSISTENT     0x00000001L
#define DHCPCAPI_REQUEST_SYNCHRONOUS    0x00000002L
#define DHCPCAPI_REQUEST_ASYNCHRONOUS   0x00000004L
#define DHCPCAPI_REQUEST_CANCEL         0x00000008L
#define DHCPCAPI_REQUEST_MASK           0x0000000FL

/* DhcpRegisterParamChange() flags */
#define DHCPCAPI_REGISTER_HANDLE_EVENT  0x00000001L

/* DhcpDeRegisterParamChange() flags */
#define DHCPCAPI_DEREGISTER_HANDLD_EVENT    0x00000001L

/* DHCP API parameters */
typedef struct _DHCPAPI_PARAMS {
    ULONG   Flags;
    ULONG   OptionId;
    BOOL    IsVendor;
    LPBYTE  Data;
    DWORD   nBytesData;
} DHCPAPI_PARAMS;
typedef DHCPAPI_PARAMS  *PDHCPAPI_PARAMS;
typedef DHCPAPI_PARAMS  *LPDHCPAPI_PARAMS;
typedef DHCPAPI_PARAMS  DHCPCAPI_PARAMS;
typedef DHCPAPI_PARAMS  *PDHCPCAPI_PARAMS;
typedef DHCPAPI_PARAMS  *LPDHCPCAPI_PARAMS;

/* DHCP client API parameters array */
typedef struct _DHCPCAPI_PARAMS_ARRAY {
    ULONG               nParams;
    LPDHCPCAPI_PARAMS   Params;
} DHCPCAPI_PARAMS_ARRAY;
typedef DHCPCAPI_PARAMS_ARRAY   *PDHCPCAPI_PARAMS_ARRAY;
typedef DHCPCAPI_PARAMS_ARRAY   *LPDHCPCAPI_PARAMS_ARRAY;

/* DHCP client API class identifier */
typedef struct _DHCPCAPI_CLASSID {
    ULONG   Flags;
    LPBYTE  Data;
    ULONG   nBytesData;
} DHCPCAPI_CLASSID;
typedef DHCPCAPI_CLASSID    *PDHCPCAPI_CLASSID;
typedef DHCPCAPI_CLASSID    *LPDHCPCAPI_CLASSID;

/* Functions in DHCPCSVC.DLL */
VOID APIENTRY   DhcpCApiCleanup( VOID );
DWORD APIENTRY  DhcpCApiInitialize( LPDWORD );
DWORD APIENTRY  DhcpDeRegisterParamChange( DWORD, LPVOID, LPVOID );
DWORD APIENTRY  DhcpRegisterParamChange( DWORD, LPVOID, LPWSTR, LPDHCPCAPI_CLASSID, DHCPCAPI_PARAMS_ARRAY, LPVOID );
DWORD APIENTRY  DhcpRemoveDNSRegistrations( VOID );
DWORD APIENTRY  DhcpRequestParams( DWORD, LPVOID, LPWSTR, LPDHCPCAPI_CLASSID, DHCPCAPI_PARAMS_ARRAY, DHCPCAPI_PARAMS_ARRAY, LPBYTE, LPDWORD, LPWSTR );
DWORD APIENTRY  DhcpUndoRequestParams( DWORD, LPVOID, LPWSTR, LPWSTR );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _DHCPCSDK_ */
