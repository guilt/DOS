/*
 *  objsel.h    Object picker interfaces
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

#ifndef __OBJSEL_H_
#define __OBJSEL_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Selection list clipboard format */
#define CFSTR_DSOP_DS_SELECTION_LIST    TEXT("CFSTR_DSOP_DS_SELECTION_LIST")

/* Scope types */
#define DSOP_SCOPE_TYPE_TARGET_COMPUTER                 0x00000001L
#define DSOP_SCOPE_TYPE_UPLEVEL_JOINED_DOMAIN           0x00000002L
#define DSOP_SCOPE_TYPE_DOWNLEVEL_JOINED_DOMAIN         0x00000004L
#define DSOP_SCOPE_TYPE_ENTERPRISE_DOMAIN               0x00000008L
#define DSOP_SCOPE_TYPE_GLOBAL_CATALOG                  0x00000010L
#define DSOP_SCOPE_TYPE_EXTERNAL_UPLEVEL_DOMAIN         0x00000020L
#define DSOP_SCOPE_TYPE_EXTERNAL_DOWNLEVEL_DOMAIN       0x00000040L
#define DSOP_SCOPE_TYPE_WORKGROUP                       0x00000080L
#define DSOP_SCOPE_TYPE_USER_ENTERED_UPLEVEL_SCOPE      0x00000100L
#define DSOP_SCOPE_TYPE_USER_ENTERED_DOWNLEVEL_SCOPE    0x00000200L

/* Scope flags */
#define DSOP_SCOPE_FLAG_STARTING_SCOPE                  0x00000001L
#define DSOP_SCOPE_FLAG_WANT_PROVIDER_WINNT             0x00000002L
#define DSOP_SCOPE_FLAG_WANT_PROVIDER_LDAP              0x00000004L
#define DSOP_SCOPE_FLAG_WANT_PROVIDER_GC                0x00000008L
#define DSOP_SCOPE_FLAG_WANT_SID_PATH                   0x00000010L
#define DSOP_SCOPE_FLAG_WANT_DOWNLEVEL_BUILTIN_PATH     0x00000020L
#define DSOP_SCOPE_FLAG_DEFAULT_FILTER_USERS            0x00000040L
#define DSOP_SCOPE_FLAG_DEFAULT_FILTER_GROUPS           0x00000080L
#define DSOP_SCOPE_FLAG_DEFAULT_FILTER_COMPUTERS        0x00000100L
#define DSOP_SCOPE_FLAG_DEFAULT_FILTER_CONTACTS         0x00000200L
#define DSOP_SCOPE_FLAG_DEFAULT_FILTER_SERVICE_ACCOUNTS 0x00000400L

/* Filter flags */
#define DSOP_FILTER_INCLUDE_ADVANCED_VIEW   0x00000001L
#define DSOP_FILTER_USERS                   0x00000002L
#define DSOP_FILTER_BUILTIN_GROUPS          0x00000004L
#define DSOP_FILTER_WELL_KNOWN_PRINCIPALS   0x00000008L
#define DSOP_FILTER_UNIVERSAL_GROUPS_DL     0x00000010L
#define DSOP_FILTER_UNIVERSAL_GROUPS_SE     0x00000020L
#define DSOP_FILTER_GLOBAL_GROUPS_DL        0x00000040L
#define DSOP_FILTER_GLOBAL_GROUPS_SE        0x00000080L
#define DSOP_FILTER_DOMAIN_LOCAL_GROUPS_DL  0x00000100L
#define DSOP_FILTER_DOMAIN_LOCAL_GROUPS_SE  0x00000200L
#define DSOP_FILTER_CONTACTS                0x00000400L
#define DSOP_FILTER_COMPUTERS               0x00000800L
#define DSOP_FILTER_SERVICE_ACCOUNT         0x00001000L

/* Downlevel filter flags */
#define DSOP_DOWNLEVEL_FILTER_USERS                     0x80000001L
#define DSOP_DOWNLEVEL_FILTER_LOCAL_GROUPS              0x80000002L
#define DSOP_DOWNLEVEL_FILTER_GLOBAL_GROUPS             0x80000004L
#define DSOP_DOWNLEVEL_FILTER_COMPUTERS                 0x80000008L
#define DSOP_DOWNLEVEL_FILTER_WORLD                     0x80000010L
#define DSOP_DOWNLEVEL_FILTER_AUTHENTICATED_USER        0x80000020L
#define DSOP_DOWNLEVEL_FILTER_ANONYMOUS                 0x80000040L
#define DSOP_DOWNLEVEL_FILTER_BATCH                     0x80000080L
#define DSOP_DOWNLEVEL_FILTER_CREATOR_OWNER             0x80000100L
#define DSOP_DOWNLEVEL_FILTER_CREATOR_GROUP             0x80000200L
#define DSOP_DOWNLEVEL_FILTER_DIALUP                    0x80000400L
#define DSOP_DOWNLEVEL_FILTER_INTERACTIVE               0x80000800L
#define DSOP_DOWNLEVEL_FILTER_NETWORK                   0x80001000L
#define DSOP_DOWNLEVEL_FILTER_SERVICE                   0x80002000L
#define DSOP_DOWNLEVEL_FILTER_SYSTEM                    0x80004000L
#define DSOP_DOWNLEVEL_FILTER_EXCLUDE_BUILTIN_GROUPS    0x80008000L
#define DSOP_DOWNLEVEL_FILTER_TERMINAL_SERVER           0x80010000L
#define DSOP_DOWNLEVEL_FILTER_ALL_WELLKNOWN_SIDS        0x80020000L
#define DSOP_DOWNLEVEL_FILTER_LOCAL_SERVICE             0x80040000L
#define DSOP_DOWNLEVEL_FILTER_NETWORK_SERVICE           0x80080000L
#define DSOP_DOWNLEVEL_FILTER_REMOTE_LOGON              0x80100000L
#define DSOP_DOWNLEVEL_FILTER_INTERNET_USER             0x80200000L
#define DSOP_DOWNLEVEL_FILTER_OWNER_RIGHTS              0x80400000L
#define DSOP_DOWNLEVEL_FILTER_SERVICES                  0x80800000L
#define DSOP_DOWNLEVEL_FILTER_LOCAL_LOGON               0x81000000L
#define DSOP_DOWNLEVEL_FILTER_THIS_ORG_CERT             0x82000000L
#define DSOP_DOWNLEVEL_FILTER_IIS_APP_POOL              0x84000000L

/* Initialization flags */
#define DSOP_FLAG_MULTISELECT                   0x00000001L
#define DSOP_FLAG_SKIP_TARGET_COMPUTER_DC_CHECK 0x00000002L

/* Uplevel filter flags */
typedef struct _DSOP_UPLEVEL_FILTER_FLAGS {
    ULONG   flBothModes;
    ULONG   flMixedModeOnly;
    ULONG   flNativeModeOnly;
} DSOP_UPLEVEL_FILTER_FLAGS;

/* Filter flags */
typedef struct _DSOP_FILTER_FLAGS {
    DSOP_UPLEVEL_FILTER_FLAGS   Uplevel;
    ULONG                       flDownlevel;
} DSOP_FILTER_FLAGS;

/* Scope initialization information */
typedef struct _DSOP_SCOPE_INIT_INFO {
    ULONG               cbSize;
    ULONG               flType;
    ULONG               flScope;
    DSOP_FILTER_FLAGS   FilterFlags;
    PCWSTR              pwzDcName;
    PCWSTR              pwzADsPath;
    HRESULT             hr;
} DSOP_SCOPE_INIT_INFO;
typedef DSOP_SCOPE_INIT_INFO        *PDSOP_SCOPE_INIT_INFO;
typedef const DSOP_SCOPE_INIT_INFO  *PCDSOP_SCOPE_INIT_INFO;

/* Initialization information */
typedef struct _DSOP_INIT_INFO {
    ULONG                   cbSize;
    PCWSTR                  pwzTargetComputer;
    ULONG                   cDsScopeInfos;
    PDSOP_SCOPE_INIT_INFO   aDsScopeInfos;
    ULONG                   flOptions;
    ULONG                   cAttributesToFetch;
    PCWSTR                  *apwzAttributeNames;
} DSOP_INIT_INFO;
typedef DSOP_INIT_INFO          *PDSOP_INIT_INFO;
typedef const DSOP_INIT_INFO    *PCDSOP_INIT_INFO;

/* Selection */
typedef struct _DS_SELECTION {
    PWSTR   pwzName;
    PWSTR   pwzADsPath;
    PWSTR   pwzClass;
    PWSTR   pwzUPN;
    VARIANT *pvarFetchedAttributes;
    ULONG   flScopeType;
} DS_SELECTION;
typedef DS_SELECTION    *PDS_SELECTION;

/* Selection list */
typedef struct _DS_SELECTION_LIST {
    ULONG           cItems;
    ULONG           cFetchedAttributes;
    DS_SELECTION    aDsSelection[ANYSIZE_ARRAY];
} DS_SELECTION_LIST;
typedef DS_SELECTION_LIST   *PDS_SELECTION_LIST;

/* IDsObjectPicker interface */
#undef INTERFACE
#define INTERFACE   IDsObjectPicker
DECLARE_INTERFACE_( IDsObjectPicker, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IDsObjectPicker methods */
    STDMETHOD( Initialize )( THIS_ DSOP_INIT_INFO ) PURE;
    STDMETHOD( InvokeDialog )( THIS_ HWND, IDataObject ** ) PURE;
};

/* IDsObjectPickerCredentials interface */
#undef INTERFACE
#define INTERFACE   IDsObjectPickerCredentials
DECLARE_INTERFACE_( IDsObjectPickerCredentials, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IDsObjectPickerCredentials methods */
    STDMETHOD( SetCredentials )( THIS_ LPCWSTR, LPCWSTR ) PURE;
};

#ifdef __cplusplus
} /* extern "C" */
#endif

/* GUIDs */
EXTERN_C const IID      __cdecl IID_IDsObjectPicker =
    { 0x0C87E64E, 0x3B7A, 0x11D2, { 0xB9, 0xE0, 0x00, 0xC0, 0x4F, 0xD8, 0xDB, 0xF7 } };
EXTERN_C const IID      __cdecl IID_IDsObjectPickerCredentials =
    { 0xE2D3EC9B, 0xD041, 0x445A, { 0x8F, 0x16, 0x47, 0x48, 0xDE, 0x8F, 0xB1, 0xCF } };
EXTERN_C const CLSID    __cdecl CLSID_DsObjectPicker =
    { 0x17D6CCD8, 0x3B7B, 0x11D2, { 0xB9, 0xE0, 0x00, 0xC0, 0x4F, 0xD8, 0xDB, 0xF7 } };

#endif /* __OBJSEL_H_ */
