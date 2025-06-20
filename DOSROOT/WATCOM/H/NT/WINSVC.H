/*
 *  winsvc.h    Win32 service functions
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

#ifndef _WINSVC_
#define _WINSVC_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Service handles */
DECLARE_HANDLE( SC_HANDLE );
DECLARE_HANDLE( SERVICE_STATUS_HANDLE );
typedef SC_HANDLE   *LPSC_HANDLE;

/* Service control lock data type */
typedef LPVOID  SC_LOCK;

/* Service database names */
#define SERVICES_ACTIVE_DATABASEA   "ServicesActive"
#define SERVICES_ACTIVE_DATABASEW   L"ServicesActive"
#define SERVICES_FAILED_DATABASEA   "ServicesFailed"
#define SERVICES_FAILED_DATABASEW   L"ServicesFailed"
#ifdef UNICODE
    #define SERVICES_ACTIVE_DATABASE    SERVICES_ACTIVE_DATABASEW
    #define SERVICES_FAILED_DATABASE    SERVICES_FAILED_DATABASEW
#else
    #define SERVICES_ACTIVE_DATABASE    SERVICES_ACTIVE_DATABASEA
    #define SERVICES_FAILED_DATABASE    SERVICES_FAILED_DATABASEA
#endif

/* Service group identifier */
#define SC_GROUP_IDENTIFIERA    "+"
#define SC_GROUP_IDENTIFIERW    L"+"
#ifdef UNICODE
    #define SC_GROUP_IDENTIFIER SC_GROUP_IDENTIFIERW
#else
    #define SC_GROUP_IDENTIFIER SC_GROUP_IDENTIFIERA
#endif

/* Special value for optional parameters */
#define SERVICE_NO_CHANGE   0xFFFFFFFFL

/* Service state flags */
#define SERVICE_ACTIVE      0x00000001L
#define SERVICE_INACTIVE    0x00000002L
#define SERVICE_STATE_ALL   (SERVICE_ACTIVE | SERVICE_INACTIVE)

/* Service control codes */
#define SERVICE_CONTROL_STOP                    0x00000001L
#define SERVICE_CONTROL_PAUSE                   0x00000002L
#define SERVICE_CONTROL_CONTINUE                0x00000003L
#define SERVICE_CONTROL_INTERROGATE             0x00000004L
#define SERVICE_CONTROL_SHUTDOWN                0x00000005L
#define SERVICE_CONTROL_PARAMCHANGE             0x00000006L
#define SERVICE_CONTROL_NETBINDADD              0x00000007L
#define SERVICE_CONTROL_NETBINDREMOVE           0x00000008L
#define SERVICE_CONTROL_NETBINDENABLE           0x00000009L
#define SERVICE_CONTROL_NETBINDDISABLE          0x0000000AL
#define SERVICE_CONTROL_DEVICEEVENT             0x0000000BL
#define SERVICE_CONTROL_HARDWAREPROFILECHANGE   0x0000000CL
#define SERVICE_CONTROL_POWEREVENT              0x0000000DL
#define SERVICE_CONTROL_SESSIONCHANGE           0x0000000EL
#define SERVICE_CONTROL_PRESHUTDOWN             0x0000000FL
#define SERVICE_CONTROL_TIMECHANGE              0x00000010L
#define SERVICE_CONTROL_TRIGGEREVENT            0x00000020L

/* Service states */
#define SERVICE_STOPPED             0x00000001L
#define SERVICE_START_PENDING       0x00000002L
#define SERVICE_STOP_PENDING        0x00000003L
#define SERVICE_RUNNING             0x00000004L
#define SERVICE_CONTINUE_PENDING    0x00000005L
#define SERVICE_PAUSE_PENDING       0x00000006L
#define SERVICE_PAUSED              0x00000007L

/* Service control acceptance flags */
#define SERVICE_ACCEPT_STOP                     0x00000001L
#define SERVICE_ACCEPT_PAUSE_CONTINUE           0x00000002L
#define SERVICE_ACCEPT_SHUTDOWN                 0x00000004L
#define SERVICE_ACCEPT_PARAMCHANGE              0x00000008L
#define SERVICE_ACCEPT_NETBINDCHANGE            0x00000010L
#define SERVICE_ACCEPT_HARDWAREPROFILECHANGE    0x00000020L
#define SERVICE_ACCEPT_POWEREVENT               0x00000040L
#define SERVICE_ACCEPT_SESSIONCHANGE            0x00000080L
#define SERVICE_ACCEPT_PRESHUTDOWN              0x00000100L
#define SERVICE_ACCEPT_TIMECHANGE               0x00000200L
#define SERVICE_ACCEPT_TRIGGEREVENT             0x00000400L

/* Service Control Manager access rights */
#define SC_MANAGER_CONNECT              0x0001L
#define SC_MANAGER_CREATE_SERVICE       0x0002L
#define SC_MANAGER_ENUMERATE_SERVICE    0x0004L
#define SC_MANAGER_LOCK                 0x0008L
#define SC_MANAGER_QUERY_LOCK_STATUS    0x0010L
#define SC_MANAGER_MODIFY_BOOT_CONFIG   0x0020L
#define SC_MANAGER_ALL_ACCESS \
    (STANDARD_RIGHTS_REQUIRED | SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE | \
    SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_LOCK | SC_MANAGER_QUERY_LOCK_STATUS | \
    SC_MANAGER_MODIFY_BOOT_CONFIG)

/* Service access rights */
#define SERVICE_QUERY_CONFIG            0x0001L
#define SERVICE_CHANGE_CONFIG           0x0002L
#define SERVICE_QUERY_STATUS            0x0004L
#define SERVICE_ENUMERATE_DEPENDENTS    0x0008L
#define SERVICE_START                   0x0010L
#define SERVICE_STOP                    0x0020L
#define SERVICE_PAUSE_CONTINUE          0x0040L
#define SERVICE_INTERROGATE             0x0080L
#define SERVICE_USER_DEFINED_CONTROL    0x0100L
#define SERVICE_ALL_ACCESS \
    (STANDARD_RIGHTS_REQUIRED | SERVICE_QUERY_CONFIG | SERVICE_CHANGE_CONFIG | \
    SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS | SERVICE_START | \
    SERVICE_STOP | SERVICE_PAUSE_CONTINUE | SERVICE_INTERROGATE | \
    SERVICE_USER_DEFINED_CONTROL)

/* QueryServiceStatusEx() flags */
#define SERVICE_RUNS_IN_SYSTEM_PROCESS  0x00000001L

/* QueryServiceConfig2() information levels */
#define SERVICE_CONFIG_DESCRIPTION              1L
#define SERVICE_CONFIG_FAILURE_ACTIONS          2L
#define SERVICE_CONFIG_DELAYED_AUTO_START_INFO  3L
#define SERVICE_CONFIG_FAILURE_ACTIONS_FLAG     4L
#define SERVICE_CONFIG_SERVICE_SID_INFO         5L
#define SERVICE_CONFIG_REQUIRED_PRIVILEGES_INFO 6L
#define SERVICE_CONFIG_PRESHUTDOWN_INFO         7L
#define SERVICE_CONFIG_TRIGGER_INFO             8L
#define SERVICE_CONFIG_PREFERRED_NODE           9L

/* NotifyServiceStatusChange() information levels */
#define SERVICE_NOTIFY_STATUS_CHANGE_1  1L
#define SERVICE_NOTIFY_STATUS_CHANGE_2  2L
#define SERVICE_NOTIFY_STATUS_CHANGE    SERVICE_NOTIFY_STATUS_CHANGE_2

/* Service notification flags */
#define SERVICE_NOTIFY_STOPPED          0x00000001L
#define SERVICE_NOTIFY_START_PENDING    0x00000002L
#define SERVICE_NOTIFY_STOP_PENDING     0x00000004L
#define SERVICE_NOTIFY_RUNNING          0x00000008L
#define SERVICE_NOTIFY_CONTINUE_PENDING 0x00000010L
#define SERVICE_NOTIFY_PAUSE_PENDING    0x00000020L
#define SERVICE_NOTIFY_PAUSED           0x00000040L
#define SERVICE_NOTIFY_CREATED          0x00000080L
#define SERVICE_NOTIFY_DELETED          0x00000100L
#define SERVICE_NOTIFY_DELETE_PENDING   0x00000200L

/* Service stop reason flags */
#define SERVICE_STOP_REASON_FLAG_MIN        0x00000000L
#define SERVICE_STOP_REASON_FLAG_UNPLANNED  0x10000000L
#define SERVICE_STOP_REASON_FLAG_CUSTOM     0x20000000L
#define SERVICE_STOP_REASON_FLAG_PLANNED    0x40000000L
#define SERVICE_STOP_REASON_FLAG_MAX        0x80000000L

/* Major service stop reasons */
#define SERVICE_STOP_REASON_MAJOR_MIN               0x00000000L
#define SERVICE_STOP_REASON_MAJOR_OTHER             0x00010000L
#define SERVICE_STOP_REASON_MAJOR_HARDWARE          0x00020000L
#define SERVICE_STOP_REASON_MAJOR_OPERATINGSYSTEM   0x00030000L
#define SERVICE_STOP_REASON_MAJOR_SOFTWARE          0x00040000L
#define SERVICE_STOP_REASON_MAJOR_APPLICATION       0x00050000L
#define SERVICE_STOP_REASON_MAJOR_NONE              0x00060000L
#define SERVICE_STOP_REASON_MAJOR_MAX               0x00070000L
#define SERVICE_STOP_REASON_MAJOR_MIN_CUSTOM        0x00400000L
#define SERVICE_STOP_REASON_MAJOR_MAX_CUSTOM        0x00FF0000L

/* Minor service stop reasons */
#define SERVICE_STOP_REASON_MINOR_MIN                       0x00000000L
#define SERVICE_STOP_REASON_MINOR_OTHER                     0x00000001L
#define SERVICE_STOP_REASON_MINOR_MAINTENANCE               0x00000002L
#define SERVICE_STOP_REASON_MINOR_INSTALLATION              0x00000003L
#define SERVICE_STOP_REASON_MINOR_UPGRADE                   0x00000004L
#define SERVICE_STOP_REASON_MINOR_RECONFIG                  0x00000005L
#define SERVICE_STOP_REASON_MINOR_HUNG                      0x00000006L
#define SERVICE_STOP_REASON_MINOR_UNSTABLE                  0x00000007L
#define SERVICE_STOP_REASON_MINOR_DISK                      0x00000008L
#define SERVICE_STOP_REASON_MINOR_NETWORKCARD               0x00000009L
#define SERVICE_STOP_REASON_MINOR_ENVIRONMENT               0x0000000AL
#define SERVICE_STOP_REASON_MINOR_HARDWARE_DRIVER           0x0000000BL
#define SERVICE_STOP_REASON_MINOR_OTHERDRIVER               0x0000000CL
#define SERVICE_STOP_REASON_MINOR_SERVICEPACK               0x0000000DL
#define SERVICE_STOP_REASON_MINOR_SOFTWARE_UPDATE           0x0000000EL
#define SERVICE_STOP_REASON_MINOR_SECURITYFIX               0x0000000FL
#define SERVICE_STOP_REASON_MINOR_SECURITY                  0x00000010L
#define SERVICE_STOP_REASON_MINOR_NETWORK_CONNECTIVITY      0x00000011L
#define SERVICE_STOP_REASON_MINOR_WMI                       0x00000012L
#define SERVICE_STOP_REASON_MINOR_SERVICEPACK_UNINSTALL     0x00000013L
#define SERVICE_STOP_REASON_MINOR_SOFTWARE_UPDATE_UNINSTALL 0x00000014L
#define SERVICE_STOP_REASON_MINOR_SECURITYFIX_UNINSTALL     0x00000015L
#define SERVICE_STOP_REASON_MINOR_MMC                       0x00000016L
#define SERVICE_STOP_REASON_MINOR_NONE                      0x00000017L
#define SERVICE_STOP_REASON_MINOR_MAX                       0x00000018L
#define SERVICE_STOP_REASON_MINOR_MIN_CUSTOM                0x00000100L
#define SERVICE_STOP_REASON_MINOR_MAX_CUSTOM                0x0000FFFFL

/* ControlServiceEx() information levels */
#define SERVICE_CONTROL_STATUS_REASON_INFO  1L

/* Service SID types */
#define SERVICE_SID_TYPE_NONE           0x00000000L
#define SERVICE_SID_TYPE_UNRESTRICTED   0x00000001L
#define SERVICE_SID_TYPE_RESTRICTED     (0x00000002L | SERVICE_SID_TYPE_UNRESTRICTED)

/* Service trigger types */
#define SERVICE_TRIGGER_TYPE_DEVICE_INTERFACE_ARRIVAL   1L
#define SERVICE_TRIGGER_TYPE_IP_ADDRESS_AVAILABILITY    2L
#define SERVICE_TRIGGER_TYPE_DOMAIN_JOIN                3L
#define SERVICE_TRIGGER_TYPE_FIREWALL_PORT_EVENT        4L
#define SERVICE_TRIGGER_TYPE_GROUP_POLICY               5L
#define SERVICE_TRIGGER_TYPE_CUSTOM                     20L

/* Service trigger data types */
#define SERVICE_TRIGGER_DATA_TYPE_BINARY    1L
#define SERVICE_TRIGGER_DATA_TYPE_STRING    2L

/* Service trigger actions */
#define SERVICE_TRIGGER_ACTION_SERVICE_START    1L
#define SERVICE_TRIGGER_ACTION_SERVICE_STOP     2L

/* Trigger-started service argument */
#define SERVICE_TRIGGER_STARTED_ARGUMENT    L"TriggerStarted"

/* Service description */
typedef struct _SERVICE_DESCRIPTIONA {
    LPSTR   lpDescription;
} SERVICE_DESCRIPTIONA;
typedef SERVICE_DESCRIPTIONA    *LPSERVICE_DESCRIPTIONA;
typedef struct _SERVICE_DESCRIPTIONW {
    LPWSTR  lpDescription;
} SERVICE_DESCRIPTIONW;
typedef SERVICE_DESCRIPTIONW    *LPSERVICE_DESCRIPTIONW;
#ifdef UNICODE
typedef SERVICE_DESCRIPTIONW    SERVICE_DESCRIPTION;
typedef LPSERVICE_DESCRIPTIONW  LPSERVICE_DESCRIPTION;
#else
typedef SERVICE_DESCRIPTIONA    SERVICE_DESCRIPTION;
typedef LPSERVICE_DESCRIPTIONA  LPSERVICE_DESCRIPTION;
#endif

/* Service control action types */
typedef enum _SC_ACTION_TYPE {
    SC_ACTION_NONE          = 0,
    SC_ACTION_RESTART       = 1,
    SC_ACTION_REBOOT        = 2,
    SC_ACTION_RUN_COMMAND   = 3
} SC_ACTION_TYPE;

/* Service control action */
typedef struct _SC_ACTION {
    SC_ACTION_TYPE  Type;
    DWORD           Delay;
} SC_ACTION;
typedef SC_ACTION   *LPSC_ACTION;

/* Service failure actions */
typedef struct _SERVICE_FAILURE_ACTIONSA {
    DWORD       dwResetPeriod;
    LPSTR       lpRebootMsg;
    LPSTR       lpCommand;
    DWORD       cActions;
    SC_ACTION   *lpsaActions;
} SERVICE_FAILURE_ACTIONSA;
typedef SERVICE_FAILURE_ACTIONSA    *LPSERVICE_FAILURE_ACTIONSA;
typedef struct _SERVICE_FAILURE_ACTIONSW {
    DWORD       dwResetPeriod;
    LPWSTR      lpRebootMsg;
    LPWSTR      lpCommand;
    DWORD       cActions;
    SC_ACTION   *lpsaActions;
} SERVICE_FAILURE_ACTIONSW;
typedef SERVICE_FAILURE_ACTIONSW    *LPSERVICE_FAILURE_ACTIONSW;
#ifdef UNICODE
typedef SERVICE_FAILURE_ACTIONSW    SERVICE_FAILURE_ACTIONS;
typedef LPSERVICE_FAILURE_ACTIONSW  LPSERVICE_FAILURE_ACTIONS;
#else
typedef SERVICE_FAILURE_ACTIONSA    SERVICE_FAILURE_ACTIONS;
typedef LPSERVICE_FAILURE_ACTIONSA  LPSERVICE_FAILURE_ACTIONS;
#endif

/* Service delayed automatic start information */
typedef struct _SERVICE_DELAYED_AUTO_START_INFO {
    BOOL    fDelayedAutoStart;
} SERVICE_DELAYED_AUTO_START_INFO;
typedef SERVICE_DELAYED_AUTO_START_INFO *LPSERVICE_DELAYED_AUTO_START_INFO;

/* Service failure actions flags */
typedef struct _SERVICE_FAILURE_ACTIONS_FLAG {
    BOOL    fFailureActionsOnNonCrashFailures;
} SERVICE_FAILURE_ACTIONS_FLAG;
typedef SERVICE_FAILURE_ACTIONS_FLAG    *LPSERVICE_FAILURE_ACTIONS_FLAG;

/* Service SID information */
typedef struct _SERVICE_SID_INFO {
    DWORD   dwServiceSidType;
} SERVICE_SID_INFO;
typedef SERVICE_SID_INFO    *LPSERVICE_SID_INFO;

/* Service required privileges information */
typedef struct _SERVICE_REQUIRED_PRIVILEGES_INFOA {
    LPSTR   pmszRequiredPrivileges;
} SERVICE_REQUIRED_PRIVILEGES_INFOA;
typedef SERVICE_REQUIRED_PRIVILEGES_INFOA   *LPSERVICE_REQUIRED_PRIVILEGES_INFOA;
typedef struct _SERVICE_REQUIRED_PRIVILEGES_INFOW {
    LPWSTR  pmszRequiredPrivileges;
} SERVICE_REQUIRED_PRIVILEGES_INFOW;
typedef SERVICE_REQUIRED_PRIVILEGES_INFOW   *LPSERVICE_REQUIRED_PRIVILEGES_INFOW;
#ifdef UNICODE
typedef SERVICE_REQUIRED_PRIVILEGES_INFOW   SERVICE_REQUIRED_PRIVILEGES_INFOW;
typedef LPSERVICE_REQUIRED_PRIVILEGES_INFOW LPSERVICE_REQUIRED_PRIVILEGES_INFOW;
#else
typedef SERVICE_REQUIRED_PRIVILEGES_INFOA   SERVICE_REQUIRED_PRIVILEGES_INFOA;
typedef LPSERVICE_REQUIRED_PRIVILEGES_INFOA LPSERVICE_REQUIRED_PRIVILEGES_INFOA;
#endif

/* Service preshutdown information */
typedef struct _SERVICE_PRESHUTDOWN_INFO {
    DWORD   dwPreshutdownTimeout;
} SERVICE_PRESHUTDOWN_INFO;
typedef SERVICE_PRESHUTDOWN_INFO    *LPSERVICE_PRESHUTDOWN_INFO;

/* Service trigger-specific data item */
typedef struct _SERVICE_TRIGGER_SPECIFIC_DATA_ITEM {
    DWORD   dwDataType;
    DWORD   cbData;
    PBYTE   pData;
} SERVICE_TRIGGER_SPECIFIC_DATA_ITEM;
typedef SERVICE_TRIGGER_SPECIFIC_DATA_ITEM  *PSERVICE_TRIGGER_SPECIFIC_DATA_ITEM;

/* Service trigger */
typedef struct _SERVICE_TRIGGER {
    DWORD                               dwTriggerType;
    DWORD                               dwAction;
    GUID                                *pTriggerSubtype;
    DWORD                               cDataItems;
    PSERVICE_TRIGGER_SPECIFIC_DATA_ITEM pDataItems;
} SERVICE_TRIGGER;
typedef SERVICE_TRIGGER *PSERVICE_TRIGGER;

/* Service trigger information */
typedef struct _SERVICE_TRIGGER_INFO {
    DWORD               cTriggers;
    PSERVICE_TRIGGER    pTriggers;
    PBYTE               pReserved;
} SERVICE_TRIGGER_INFO;
typedef SERVICE_TRIGGER_INFO    *PSERVICE_TRIGGER_INFO;

/* Service preferred node information */
typedef struct _SERVICE_PREFERRED_NODE_INFO {
    USHORT  usPreferredNode;
    BOOLEAN fDelete;
} SERVICE_PREFERRED_NODE_INFO;
typedef SERVICE_PREFERRED_NODE_INFO *PSERVICE_PREFERRED_NODE_INFO;

/* Service time change information */
typedef struct _SERVICE_TIMECHANGE_INFO {
    LARGE_INTEGER   liNewTime;
    LARGE_INTEGER   liOldTime;
} SERVICE_TIMECHANGE_INFO;
typedef SERVICE_TIMECHANGE_INFO *PSERVICE_TIMECHANGE_INFO;

/* Service control status types */
typedef enum _SC_STATUS_TYPE {
    SC_STATUS_PROCESS_INFO  = 0
} SC_STATUS_TYPE;

/* Service control enumeration types */
typedef enum _SC_ENUM_TYPE {
    SC_ENUM_PROCESS_INFO    = 0
} SC_ENUM_TYPE;

/* Service status */
typedef struct _SERVICE_STATUS {
    DWORD   dwServiceType;
    DWORD   dwCurrentState;
    DWORD   dwControlsAccepted;
    DWORD   dwWin32ExitCode;
    DWORD   dwServiceSpecificExitCode;
    DWORD   dwCheckPoint;
    DWORD   dwWaitHint;
} SERVICE_STATUS;
typedef SERVICE_STATUS  *LPSERVICE_STATUS;

/* Service status process */
typedef struct _SERVICE_STATUS_PROCESS {
    DWORD   dwServiceType;
    DWORD   dwCurrentState;
    DWORD   dwControlsAccepted;
    DWORD   dwWin32ExitCode;
    DWORD   dwServiceSpecificExitCode;
    DWORD   dwCheckpoint;
    DWORD   dwWaitHint;
    DWORD   dwProcessId;
    DWORD   dwServiceFlags;
} SERVICE_STATUS_PROCESS;
typedef SERVICE_STATUS_PROCESS  *LPSERVICE_STATUS_PROCESS;

/* EnumServiceStatus() parameters */
typedef struct _ENUM_SERVICE_STATUSA {
    LPSTR           lpServiceName;
    LPSTR           lpDisplayName;
    SERVICE_STATUS  ServiceStatus;
} ENUM_SERVICE_STATUSA;
typedef ENUM_SERVICE_STATUSA    *LPENUM_SERVICE_STATUSA;
typedef struct _ENUM_SERVICE_STATUSW {
    LPWSTR          lpServiceName;
    LPWSTR          lpDisplayName;
    SERVICE_STATUS  ServiceStatus;
} ENUM_SERVICE_STATUSW;
typedef ENUM_SERVICE_STATUSW    *LPENUM_SERVICE_STATUSW;
#ifdef UNICODE
typedef ENUM_SERVICE_STATUSW    ENUM_SERVICE_STATUS;
typedef LPENUM_SERVICE_STATUSW  LPENUM_SERVICE_STATUS;
#else
typedef ENUM_SERVICE_STATUSA    ENUM_SERVICE_STATUS;
typedef LPENUM_SERVICE_STATUSA  LPENUM_SERVICE_STATUS;
#endif

/* EnumServiceStatusEx() parameters */
typedef struct _ENUM_SERVICE_STATUS_PROCESSA {
    LPSTR                   lpServiceName;
    LPSTR                   lpDisplayName;
    SERVICE_STATUS_PROCESS  ServiceStatusProcess;
} ENUM_SERVICE_STATUS_PROCESSA;
typedef ENUM_SERVICE_STATUS_PROCESSA    *LPENUM_SERVICE_STATUS_PROCESSA;
typedef struct _ENUM_SERVICE_STATUS_PROCESSW {
    LPWSTR                  lpServiceName;
    LPWSTR                  lpDisplayName;
    SERVICE_STATUS_PROCESS  ServiceStatusProcess;
} ENUM_SERVICE_STATUS_PROCESSW;
typedef ENUM_SERVICE_STATUS_PROCESSW    *LPENUM_SERVICE_STATUS_PROCESSW;
#ifdef UNICODE
typedef ENUM_SERVICE_STATUS_PROCESSW    ENUM_SERVICE_STATUS_PROCESS;
typedef LPENUM_SERVICE_STATUS_PROCESSW  LPENUM_SERVICE_STATUS_PROCESS;
#else
typedef ENUM_SERVICE_STATUS_PROCESSA    ENUM_SERVICE_STATUS_PROCESS;
typedef LPENUM_SERVICE_STATUS_PROCESSA  LPENUM_SERVICE_STATUS_PROCESS;
#endif

/* QueryServiceLockStatus() parameters */
typedef struct _QUERY_SERVICE_LOCK_STATUSA {
    DWORD   fIsLocked;
    LPSTR   lpLockOwner;
    DWORD   dwLockDuration;
} QUERY_SERVICE_LOCK_STATUSA;
typedef QUERY_SERVICE_LOCK_STATUSA      *LPQUERY_SERVICE_LOCK_STATUSA;
typedef struct _QUERY_SERVICE_LOCK_STATUSW {
    DWORD   fIsLocked;
    LPWSTR  lpLockOwner;
    DWORD   dwLockDuration;
} QUERY_SERVICE_LOCK_STATUSW;
typedef QUERY_SERVICE_LOCK_STATUSW      *LPQUERY_SERVICE_LOCK_STATUSW;
#ifdef UNICODE
typedef QUERY_SERVICE_LOCK_STATUSW      QUERY_SERVICE_LOCK_STATUS;
typedef LPQUERY_SERVICE_LOCK_STATUSW    LPQUERY_SERVICE_LOCK_STATUS;
#else
typedef QUERY_SERVICE_LOCK_STATUSA      QUERY_SERVICE_LOCK_STATUS;
typedef LPQUERY_SERVICE_LOCK_STATUSA    LPQUERY_SERVICE_LOCK_STATUS;
#endif

/* QueryServiceConfig() parameters */
typedef struct _QUERY_SERVICE_CONFIGA {
    DWORD   dwServiceType;
    DWORD   dwStartType;
    DWORD   dwErrorControl;
    LPSTR   lpBinaryPathName;
    LPSTR   lpLoadOrderGroup;
    DWORD   dwTagId;
    LPSTR   lpDependencies;
    LPSTR   lpServiceStartName;
    LPSTR   lpDisplayName;
} QUERY_SERVICE_CONFIGA;
typedef QUERY_SERVICE_CONFIGA   *LPQUERY_SERVICE_CONFIGA;
typedef struct _QUERY_SERVICE_CONFIGW {
    DWORD   dwServiceType;
    DWORD   dwStartType;
    DWORD   dwErrorControl;
    LPWSTR  lpBinaryPathName;
    LPWSTR  lpLoadOrderGroup;
    DWORD   dwTagId;
    LPWSTR  lpDependencies;
    LPWSTR  lpServiceStartName;
    LPWSTR  lpDisplayName;
} QUERY_SERVICE_CONFIGW;
typedef QUERY_SERVICE_CONFIGW   *LPQUERY_SERVICE_CONFIGW;
#ifdef UNICODE
typedef QUERY_SERVICE_CONFIGW   QUERY_SERVICE_CONFIG;
typedef LPQUERY_SERVICE_CONFIGW LPQUERY_SERVICE_CONFIG;
#else
typedef QUERY_SERVICE_CONFIGA   QUERY_SERVICE_CONFIG;
typedef LPQUERY_SERVICE_CONFIGA LPQUERY_SERVICE_CONFIG;
#endif

/* Service callbacks */
typedef VOID (WINAPI *LPSERVICE_MAIN_FUNCTIONA)( DWORD, LPSTR * );
typedef VOID (WINAPI *LPSERVICE_MAIN_FUNCTIONW)( DWORD, LPWSTR * );
typedef VOID (WINAPI *LPHANDLER_FUNCTION)( DWORD );
typedef DWORD (WINAPI *LPHANDLER_FUNCTION_EX)( DWORD, DWORD, LPVOID, LPVOID );
#ifdef UNICODE
    #define LPSERVICE_MAIN_FUNCTION LPSERVICE_MAIN_FUNCTIONW
#else
    #define LPSERVICE_MAIN_FUNCTION LPSERVICE_MAIN_FUNCTIONA
#endif

/* Service table entry */
typedef struct _SERVICE_TABLE_ENTRYA {
    LPSTR                       lpServiceName;
    LPSERVICE_MAIN_FUNCTIONA    lpServiceProc;
} SERVICE_TABLE_ENTRYA;
typedef SERVICE_TABLE_ENTRYA    *LPSERVICE_TABLE_ENTRYA;
typedef struct _SERVICE_TABLE_ENTRYW {
    LPWSTR                      lpServiceName;
    LPSERVICE_MAIN_FUNCTIONW    lpServiceProc;
} SERVICE_TABLE_ENTRYW;
typedef SERVICE_TABLE_ENTRYW    *LPSERVICE_TABLE_ENTRYW;
#ifdef UNICODE
typedef SERVICE_TABLE_ENTRYW    SERVICE_TABLE_ENTRY;
typedef LPSERVICE_TABLE_ENTRYW  LPSERVICE_TABLE_ENTRY;
#else
typedef SERVICE_TABLE_ENTRYA    SERVICE_TABLE_ENTRY;
typedef LPSERVICE_TABLE_ENTRYA  LPSERVICE_TABLE_ENTRY;
#endif

/* Service control notification callback */
typedef VOID (CALLBACK *PFN_SC_NOTIFY_CALLBACK)( PVOID );

/* Service notification information (level 1) */
typedef struct _SERVICE_NOTIFY_1 {
    DWORD                   dwVersion;
    PFN_SC_NOTIFY_CALLBACK  pfnNotifyCallback;
    PVOID                   pContext;
    DWORD                   dwNotificationStatus;
    SERVICE_STATUS_PROCESS  ServiceStatus;
} SERVICE_NOTIFY_1;
typedef SERVICE_NOTIFY_1    *PSERVICE_NOTIFY_1;

/* Service notification information (level 2) */
typedef struct _SERVICE_NOTIFY_2A {
    DWORD                   dwVersion;
    PFN_SC_NOTIFY_CALLBACK  pfnNotifyCallback;
    PVOID                   pContext;
    DWORD                   dwNotificationStatus;
    SERVICE_STATUS_PROCESS  ServiceStatus;
    DWORD                   dwNotificationTriggered;
    LPSTR                   pszServiceNames;
} SERVICE_NOTIFY_2A;
typedef SERVICE_NOTIFY_2A   *PSERVICE_NOTIFY_2A;
typedef SERVICE_NOTIFY_2A   SERVICE_NOTIFYA;
typedef SERVICE_NOTIFY_2A   *PSERVICE_NOTIFYA;
typedef struct _SERVICE_NOTIFY_2W {
    DWORD                   dwVersion;
    PFN_SC_NOTIFY_CALLBACK  pfnNotifyCallback;
    PVOID                   pContext;
    DWORD                   dwNotificationStatus;
    SERVICE_STATUS_PROCESS  ServiceStatus;
    DWORD                   dwNotificationTriggered;
    LPWSTR                  pszServiceNames;
} SERVICE_NOTIFY_2W;
typedef SERVICE_NOTIFY_2W   *PSERVICE_NOTIFY_2W;
typedef SERVICE_NOTIFY_2W   SERVICE_NOTIFYW;
typedef SERVICE_NOTIFY_2W   *PSERVICE_NOTIFYW;
#ifdef UNICODE
typedef SERVICE_NOTIFY_2W   SERVICE_NOTIFY_2;
typedef PSERVICE_NOTIFY_2W  PSERVICE_NOTIFY_2;
typedef SERVICE_NOTIFYW     SERVICE_NOTIFY;
typedef PSERVICE_NOTIFYW    PSERVICE_NOTIFY;
#else
typedef SERVICE_NOTIFY_2A   SERVICE_NOTIFY_2;
typedef PSERVICE_NOTIFY_2A  PSERVICE_NOTIFY_2;
typedef SERVICE_NOTIFYA     SERVICE_NOTIFY;
typedef PSERVICE_NOTIFYA    PSERVICE_NOTIFY;
#endif

/* Service control status reason parameters */
typedef struct _SERVICE_CONTROL_STATUS_REASON_PARAMSA {
    DWORD                   dwReason;
    LPSTR                   pszComment;
    SERVICE_STATUS_PROCESS  ServiceStatus;
} SERVICE_CONTROL_STATUS_REASON_PARAMSA;
typedef SERVICE_CONTROL_STATUS_REASON_PARAMSA   *PSERVICE_CONTROL_STATUS_REASON_PARAMSA;
typedef struct _SERVICE_CONTROL_STATUS_REASON_PARAMSW {
    DWORD                   dwReason;
    LPWSTR                  pszComment;
    SERVICE_STATUS_PROCESS  ServiceStatus;
} SERVICE_CONTROL_STATUS_REASON_PARAMSW;
typedef SERVICE_CONTROL_STATUS_REASON_PARAMSW   *PSERVICE_CONTROL_STATUS_REASON_PARAMSW;
#ifdef UNICODE
typedef SERVICE_CONTROL_STATUS_REASON_PARAMSW   SERVICE_CONTROL_STATUS_REASON_PARAMS;
typedef PSERVICE_CONTROL_STATUS_REASON_PARAMSW  PSERVICE_CONTROL_STATUS_REASON_PARAMS;
#else
typedef SERVICE_CONTROL_STATUS_REASON_PARAMSA   SERVICE_CONTROL_STATUS_REASON_PARAMS;
typedef PSERVICE_CONTROL_STATUS_REASON_PARAMSA  PSERVICE_CONTROL_STATUS_REASON_PARAMS;
#endif

/* Functions in ADVAPI32.DLL */
WINADVAPI BOOL WINAPI       ChangeServiceConfig2A( SC_HANDLE, DWORD, LPVOID );
WINADVAPI BOOL WINAPI       ChangeServiceConfig2W( SC_HANDLE, DWORD, LPVOID );
WINADVAPI BOOL WINAPI       ChangeServiceConfigA( SC_HANDLE, DWORD, DWORD, DWORD, LPCSTR, LPCSTR, LPDWORD, LPCSTR, LPCSTR, LPCSTR, LPCSTR );
WINADVAPI BOOL WINAPI       ChangeServiceConfigW( SC_HANDLE, DWORD, DWORD, DWORD, LPCWSTR, LPCWSTR, LPDWORD, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR );
WINADVAPI BOOL WINAPI       CloseServiceHandle( SC_HANDLE );
WINADVAPI BOOL WINAPI       ControlService( SC_HANDLE, DWORD, LPSERVICE_STATUS );
WINADVAPI SC_HANDLE WINAPI  CreateServiceA( SC_HANDLE, LPCSTR, LPCSTR, DWORD, DWORD, DWORD, DWORD, LPCSTR, LPCSTR, LPDWORD, LPCSTR, LPCSTR, LPCSTR );
WINADVAPI SC_HANDLE WINAPI  CreateServiceW( SC_HANDLE, LPCWSTR, LPCWSTR, DWORD, DWORD, DWORD, DWORD, LPCWSTR, LPCWSTR, LPDWORD, LPCWSTR, LPCWSTR, LPCWSTR );
WINADVAPI BOOL WINAPI       DeleteService( SC_HANDLE );
WINADVAPI BOOL WINAPI       EnumDependentServicesA( SC_HANDLE, DWORD, LPENUM_SERVICE_STATUSA, DWORD, LPDWORD, LPDWORD );
WINADVAPI BOOL WINAPI       EnumDependentServicesW( SC_HANDLE, DWORD, LPENUM_SERVICE_STATUSW, DWORD, LPDWORD, LPDWORD );
WINADVAPI BOOL WINAPI       EnumServicesStatusA( SC_HANDLE, DWORD, DWORD, LPENUM_SERVICE_STATUSA, DWORD, LPDWORD, LPDWORD, LPDWORD );
WINADVAPI BOOL WINAPI       EnumServicesStatusExA( SC_HANDLE, SC_ENUM_TYPE, DWORD, DWORD, LPBYTE, DWORD, LPDWORD, LPDWORD, LPDWORD, LPCSTR );
WINADVAPI BOOL WINAPI       EnumServicesStatusExW( SC_HANDLE, SC_ENUM_TYPE, DWORD, DWORD, LPBYTE, DWORD, LPDWORD, LPDWORD, LPDWORD, LPCWSTR );
WINADVAPI BOOL WINAPI       EnumServicesStatusW( SC_HANDLE, DWORD, DWORD, LPENUM_SERVICE_STATUSW, DWORD, LPDWORD, LPDWORD, LPDWORD );
WINADVAPI BOOL WINAPI       GetServiceDisplayNameA( SC_HANDLE, LPCSTR, LPSTR, LPDWORD );
WINADVAPI BOOL WINAPI       GetServiceDisplayNameW( SC_HANDLE, LPCWSTR, LPWSTR, LPDWORD );
WINADVAPI BOOL WINAPI       GetServiceKeyNameA( SC_HANDLE, LPCSTR, LPSTR, LPDWORD );
WINADVAPI BOOL WINAPI       GetServiceKeyNameW( SC_HANDLE, LPCWSTR, LPWSTR, LPDWORD );
WINADVAPI SC_LOCK WINAPI    LockServiceDatabase( SC_HANDLE );
WINADVAPI BOOL WINAPI       NotifyBootConfigStatus( BOOL );
WINADVAPI SC_HANDLE WINAPI  OpenSCManagerA( LPCSTR, LPCSTR, DWORD );
WINADVAPI SC_HANDLE WINAPI  OpenSCManagerW( LPCWSTR, LPCWSTR, DWORD );
WINADVAPI SC_HANDLE WINAPI  OpenServiceA( SC_HANDLE, LPCSTR, DWORD );
WINADVAPI SC_HANDLE WINAPI  OpenServiceW( SC_HANDLE, LPCWSTR, DWORD );
WINADVAPI BOOL WINAPI       QueryServiceConfig2A( SC_HANDLE, DWORD, LPBYTE, DWORD, LPDWORD );
WINADVAPI BOOL WINAPI       QueryServiceConfig2W( SC_HANDLE, DWORD, LPBYTE, DWORD, LPDWORD );
WINADVAPI BOOL WINAPI       QueryServiceConfigA( SC_HANDLE, LPQUERY_SERVICE_CONFIGA, DWORD, LPDWORD );
WINADVAPI BOOL WINAPI       QueryServiceConfigW( SC_HANDLE, LPQUERY_SERVICE_CONFIGW, DWORD, LPDWORD );
WINADVAPI BOOL WINAPI       QueryServiceLockStatusA( SC_HANDLE, LPQUERY_SERVICE_LOCK_STATUSA, DWORD, LPDWORD );
WINADVAPI BOOL WINAPI       QueryServiceLockStatusW( SC_HANDLE, LPQUERY_SERVICE_LOCK_STATUSW, DWORD, LPDWORD );
WINADVAPI BOOL WINAPI       QueryServiceObjectSecurity( SC_HANDLE, SECURITY_INFORMATION, PSECURITY_DESCRIPTOR, DWORD, LPDWORD );
WINADVAPI BOOL WINAPI       QueryServiceStatus( SC_HANDLE, LPSERVICE_STATUS );
WINADVAPI BOOL WINAPI       QueryServiceStatusEx( SC_HANDLE, SC_STATUS_TYPE, LPBYTE, DWORD, LPDWORD );
WINADVAPI SERVICE_STATUS_HANDLE WINAPI  RegisterServiceCtrlHandlerA( LPCSTR, LPHANDLER_FUNCTION );
WINADVAPI SERVICE_STATUS_HANDLE WINAPI  RegisterServiceCtrlHandlerExA( LPCSTR, LPHANDLER_FUNCTION_EX, LPVOID );
WINADVAPI SERVICE_STATUS_HANDLE WINAPI  RegisterServiceCtrlHandlerExW( LPCWSTR, LPHANDLER_FUNCTION_EX, LPVOID );
WINADVAPI SERVICE_STATUS_HANDLE WINAPI  RegisterServiceCtrlHandlerW( LPCWSTR, LPHANDLER_FUNCTION );
WINADVAPI BOOL WINAPI       SetServiceObjectSecurity( SC_HANDLE, SECURITY_INFORMATION, PSECURITY_DESCRIPTOR );
WINADVAPI BOOL WINAPI       SetServiceStatus( SERVICE_STATUS_HANDLE, LPSERVICE_STATUS );
WINADVAPI BOOL WINAPI       StartServiceA( SC_HANDLE, DWORD, LPCSTR * );
WINADVAPI BOOL WINAPI       StartServiceCtrlDispatcherA( CONST SERVICE_TABLE_ENTRYA * );
WINADVAPI BOOL WINAPI       StartServiceCtrlDispatcherW( CONST SERVICE_TABLE_ENTRYW * );
WINADVAPI BOOL WINAPI       StartServiceW( SC_HANDLE, DWORD, LPCWSTR * );
WINADVAPI BOOL WINAPI       UnlockServiceDatabase( SC_LOCK );
#if (NTDDI_VERSION >= 0x06000000)
WINADVAPI BOOL WINAPI       ControlServiceExA( SC_HANDLE, DWORD, DWORD, PVOID );
WINADVAPI BOOL WINAPI       ControlServiceExW( SC_HANDLE, DWORD, DWORD, PVOID );
WINADVAPI DWORD WINAPI      NotifyServiceStatusChangeA( SC_HANDLE, DWORD, PSERVICE_NOTIFYA );
WINADVAPI DWORD WINAPI      NotifyServiceStatusChangeW( SC_HANDLE, DWORD, PSERVICE_NOTIFYW );
#endif

/* Map generic function names to the appropriate ANSI or Unicode version. */
#ifdef UNICODE
    #define ChangeServiceConfig             ChangeServiceConfigW
    #define ChangeServiceConfig2            ChangeServiceConfig2W
    #define CreateService                   CreateServiceW
    #define EnumDependentServices           EnumDependentServicesW
    #define EnumServicesStatus              EnumServicesStatusW
    #define EnumServicesStatusEx            EnumServicesStatusExW
    #define GetServiceDisplayName           GetServiceDisplayNameW
    #define GetServiceKeyName               GetServiceKeyNameW
    #define OpenSCManager                   OpenSCManagerW
    #define OpenService                     OpenServiceW
    #define QueryServiceConfig              QueryServiceConfigW
    #define QueryServiceConfig2             QueryServiceConfig2W
    #define QueryServiceLockStatus          QueryServiceLockStatusW
    #define RegisterServiceCtrlHandler      RegisterServiceCtrlHandlerW
    #define RegisterServiceCtrlHandlerEx    RegisterServiceCtrlHandlerExW
    #define StartService                    StartServiceW
    #define StartServiceCtrlDispatcher      StartServiceCtrlDispatcherW
    #if (NTDDI_VERSION >= 0x06000000)
        #define ControlServiceEx            ControlServiceExW
        #define NotifyServiceStatusChange   NotifyServiceStatusChangeW
    #endif
#else
    #define ChangeServiceConfig             ChangeServiceConfigA
    #define ChangeServiceConfig2            ChangeServiceConfig2A
    #define CreateService                   CreateServiceA
    #define EnumDependentServices           EnumDependentServicesA
    #define EnumServicesStatus              EnumServicesStatusA
    #define EnumServicesStatusEx            EnumServicesStatusExA
    #define GetServiceDisplayName           GetServiceDisplayNameA
    #define GetServiceKeyName               GetServiceKeyNameA
    #define OpenSCManager                   OpenSCManagerA
    #define OpenService                     OpenServiceA
    #define QueryServiceConfig              QueryServiceConfigA
    #define QueryServiceConfig2             QueryServiceConfig2A
    #define QueryServiceLockStatus          QueryServiceLockStatusA
    #define RegisterServiceCtrlHandler      RegisterServiceCtrlHandlerA
    #define RegisterServiceCtrlHandlerEx    RegisterServiceCtrlHandlerExA
    #define StartService                    StartServiceA
    #define StartServiceCtrlDispatcher      StartServiceCtrlDispatcherA
    #if (NTDDI_VERSION >= 0x06000000)
        #define ControlServiceEx            ControlServiceExA
        #define NotifyServiceStatusChange   NotifyServiceStatusChangeA
    #endif
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* GUIDs */
EXTERN_C const GUID __cdecl NETWORK_MANAGER_FIRST_IP_ADDRESS_ARRIVAL_GUID;
EXTERN_C const GUID __cdecl NETWORK_MANAGER_LAST_IP_ADDRESS_REMOVAL_GUID;
EXTERN_C const GUID __cdecl DOMAIN_JOIN_GUID;
EXTERN_C const GUID __cdecl DOMAIN_LEAVE_GUID;
EXTERN_C const GUID __cdecl FIREWALL_PORT_OPEN_GUID;
EXTERN_C const GUID __cdecl FIREWALL_PORT_CLOSE_GUID;
EXTERN_C const GUID __cdecl MACHINE_POLICY_PRESENT_GUID;
EXTERN_C const GUID __cdecl USER_POLICY_PRESENT_GUID;

#endif /* _WINSVC_ */
