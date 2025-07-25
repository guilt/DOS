/*
 *  rpcnsi.h    RPC Name Service Independent functions
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

#ifndef __RPCNSI_H__
#define __RPCNSI_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* RPC Name Service handle data type */
typedef void    *RPC_NS_HANDLE;

/* RPC name syntaxes */
#define RPC_C_NS_SYNTAX_DEFAULT 0L
#define RPC_C_NS_SYNTAX_DCE     3L

/* RPC profile inquiry types */
#define RPC_C_PROFILE_DEFAULT_ELT   0L
#define RPC_C_PROFILE_ALL_ELT       1L
#define RPC_C_PROFILE_ALL_ELTS      RPC_C_PROFILE_ALL_ELT
#define RPC_C_PROFILE_MATCH_BY_IF   2L
#define RPC_C_PROFILE_MATCH_BY_MBR  3L
#define RPC_C_PROFILE_MATCH_BY_BOTH 4L

/* Expriation age special value */
#define RPC_C_NS_DEFAULT_EXP_AGE    (-1L)

/* Functions in RPCNS4.DLL */
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingExportA( unsigned long, RPC_CSTR, RPC_IF_HANDLE, RPC_BINDING_VECTOR *, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingExportPnPA( unsigned long, RPC_CSTR, RPC_IF_HANDLE, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingExportPnPW( unsigned long, RPC_WSTR, RPC_IF_HANDLE, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingExportW( unsigned long, RPC_WSTR, RPC_IF_HANDLE, RPC_BINDING_VECTOR *, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingImportBeginA( unsigned long, RPC_CSTR, RPC_IF_HANDLE, UUID *, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingImportBeginW( unsigned long, RPC_WSTR, RPC_IF_HANDLE, UUID *, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingImportDone( RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingImportNext( RPC_NS_HANDLE, RPC_BINDING_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingLookupBeginA( unsigned long, RPC_CSTR, RPC_IF_HANDLE, UUID *, unsigned long, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingLookupBeginW( unsigned long, RPC_WSTR, RPC_IF_HANDLE, UUID *, unsigned long, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingLookupDone( RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingLookupNext( RPC_NS_HANDLE, RPC_BINDING_VECTOR ** );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingSelect( RPC_BINDING_VECTOR *, RPC_BINDING_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingUnexportA( unsigned long, RPC_CSTR, RPC_IF_HANDLE, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingUnexportPnPA( unsigned long, RPC_CSTR, RPC_IF_HANDLE, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingUnexportPnPW( unsigned long, RPC_WSTR, RPC_IF_HANDLE, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsBindingUnexportW( unsigned long, RPC_WSTR, RPC_IF_HANDLE, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsEntryExpandNameA( unsigned long, RPC_CSTR, RPC_CSTR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsEntryExpandNameW( unsigned long, RPC_WSTR, RPC_WSTR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsEntryObjectInqBeginA( unsigned long, RPC_CSTR, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsEntryObjectInqBeginW( unsigned long, RPC_WSTR, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsEntryObjectInqDone( RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsEntryObjectInqNext( RPC_NS_HANDLE, UUID * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupDeleteA( unsigned long, RPC_CSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupDeleteW( unsigned long, RPC_WSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupMbrAddA( unsigned long, RPC_CSTR, unsigned long, RPC_CSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupMbrAddW( unsigned long, RPC_WSTR, unsigned long, RPC_WSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupMbrInqBeginA( unsigned long, RPC_CSTR, unsigned long, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupMbrInqBeginW( unsigned long, RPC_WSTR, unsigned long, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupMbrInqDone( RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupMbrInqNextA( RPC_NS_HANDLE, RPC_CSTR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupMbrInqNextW( RPC_NS_HANDLE, RPC_WSTR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupMbrRemoveA( unsigned long, RPC_CSTR, unsigned long, RPC_CSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsGroupMbrRemoveW( unsigned long, RPC_WSTR, unsigned long, RPC_WSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtBindingUnexportA( unsigned long, RPC_CSTR, RPC_IF_ID *, unsigned long, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtBindingUnexportW( unsigned long, RPC_WSTR, RPC_IF_ID *, unsigned long, UUID_VECTOR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtEntryCreateA( unsigned long, RPC_CSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtEntryCreateW( unsigned long, RPC_WSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtEntryDeleteA( unsigned long, RPC_CSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtEntryDeleteW( unsigned long, RPC_WSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtEntryInqIfIdsA( unsigned long, RPC_CSTR, RPC_IF_ID_VECTOR ** );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtEntryInqIfIdsW( unsigned long, RPC_WSTR, RPC_IF_ID_VECTOR ** );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtHandleSetExpAge( RPC_NS_HANDLE, unsigned long );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtInqExpAge( unsigned long * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsMgmtSetExpAge( unsigned long );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileDeleteA( unsigned long, RPC_CSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileDeleteW( unsigned long, RPC_WSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileEltAddA( unsigned long, RPC_CSTR, RPC_IF_ID *, unsigned long, RPC_CSTR, unsigned long, RPC_CSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileEltAddW( unsigned long, RPC_WSTR, RPC_IF_ID *, unsigned long, RPC_WSTR, unsigned long, RPC_WSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileEltInqBeginA( unsigned long, RPC_CSTR, unsigned long, RPC_IF_ID *, unsigned long, unsigned long, RPC_CSTR, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileEltInqBeginW( unsigned long, RPC_WSTR, unsigned long, RPC_IF_ID *, unsigned long, unsigned long, RPC_WSTR, RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileEltInqDone( RPC_NS_HANDLE * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileEltInqNextA( RPC_NS_HANDLE, RPC_IF_ID *, RPC_CSTR *, unsigned long *, RPC_CSTR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileEltInqNextW( RPC_NS_HANDLE, RPC_IF_ID *, RPC_WSTR *, unsigned long *, RPC_WSTR * );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileEltRemoveA( unsigned long, RPC_CSTR, RPC_IF_ID *, unsigned long, RPC_CSTR );
RPCNSAPI RPC_STATUS RPC_ENTRY   RpcNsProfileEltRemoveW( unsigned long, RPC_WSTR, RPC_IF_ID *, unsigned long, RPC_WSTR );

/* Map generic function names to the appropriate ANSI or Unicode version. */
#ifdef UNICODE
    #define RpcNsBindingExport          RpcNsBindingExportW
    #define RpcNsBindingExportPnP       RpcNsBindingExportPnPW
    #define RpcNsBindingImportBegin     RpcNsBindingImportBeginW
    #define RpcNsBindingLookupBegin     RpcNsBindingLookupBeginW
    #define RpcNsBindingUnexport        RpcNsBindingUnexportW
    #define RpcNsBindingUnexportPnP     RpcNsBindingUnexportPnPW
    #define RpcNsEntryExpandName        RpcNsEntryExpandNameW
    #define RpcNsEntryObjectInqBegin    RpcNsEntryObjectInqBeginW
    #define RpcNsGroupDelete            RpcNsGroupDeleteW
    #define RpcNsGroupMbrAdd            RpcNsGroupMbrAddW
    #define RpcNsGroupMbrInqBegin       RpcNsGroupMbrInqBeginW
    #define RpcNsGroupMbrInqNext        RpcNsGroupMbrInqNextW
    #define RpcNsGroupMbrRemove         RpcNsGroupMbrRemoveW
    #define RpcNsMgmtBindingUnexport    RpcNsMgmtBindingUnexportW
    #define RpcNsMgmtEntryCreate        RpcNsMgmtEntryCreateW
    #define RpcNsMgmtEntryDelete        RpcNsMgmtEntryDeleteW
    #define RpcNsMgmtEntryInqIfIds      RpcNsMgmtEntryInqIfIfsW
    #define RpcNsProfileDelete          RpcNsProfileDeleteW
    #define RpcNsProfileEltAdd          RpcNsProfileEltAddW
    #define RpcNsProfileEltInqBegin     RpcNsProfileEltInqBeginW
    #define RpcNsProfileEltInqNext      RpcNsProfileEltInqNextW
    #define RpcNsProfileEltRemove       RpcNsProfileEltRemoveW
#else
    #define RpcNsBindingExport          RpcNsBindingExportA
    #define RpcNsBindingExportPnP       RpcNsBindingExportPnPA
    #define RpcNsBindingImportBegin     RpcNsBindingImportBeginA
    #define RpcNsBindingLookupBegin     RpcNsBindingLookupBeginA
    #define RpcNsBindingUnexport        RpcNsBindingUnexportA
    #define RpcNsBindingUnexportPnP     RpcNsBindingUnexportPnpA
    #define RpcNsEntryExpandName        RpcNsEntryExpandNameA
    #define RpcNsEntryObjectInqBegin    RpcNsEntryObjectInqBeginA
    #define RpcNsGroupDelete            RpcNsGroupDeleteA
    #define RpcNsGroupMbrAdd            RpcNsGroupMbrAddA
    #define RpcNsGroupMbrInqBegin       RpcNsGroupMbrInqBeginA
    #define RpcNsGroupMbrInqNext        RpcNsGroupMbrInqNextA
    #define RpcNsGroupMbrRemove         RpcNsGroupMbrRemoveA
    #define RpcNsMgmtBindingUnexport    RpcNsMgmtBindingUnexportA
    #define RpcNsMgmtEntryCreate        RpcNsMgmtEntryCreateA
    #define RpcNsMgmtEntryDelete        RpcNsMgmtEntryDeleteA
    #define RpcNsMgmtEntryInqIfIds      RpcNsMgmtEntryInqIfIdsA
    #define RpcNsProfileDelete          RpcNsProfileDeleteA
    #define RpcNsProfileEltAdd          RpcNsProfileEltAddA
    #define RpcNsProfileEltInqBegin     RpcNsProfileEltInqBeginA
    #define RpcNsProfileEltInqDone      RpcNsProfileEltInqDoneA
    #define RpcNsProfileEltRemove       RpcNsProfileEltRemoveA
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __RPCNSI_H__ */
