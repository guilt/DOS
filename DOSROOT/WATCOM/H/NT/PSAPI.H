/*
 *  psapi.h     Process status functions
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

#ifndef _PSAPI_H_
#define _PSAPI_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* PSAPI version number */
#ifndef PSAPI_VERSION
    #if (NTDDI_VERSION >= 0x06010000)
        #define PSAPI_VERSION   2
    #else
        #define PSAPI_VERSION   1
    #endif
#endif

/* EnumProcessModulesEx() filter flags */
#define LIST_MODULES_DEFAULT    0x00000000L
#define LIST_MODULES_32BIT      0x00000001L
#define LIST_MODULES_64BIT      0x00000002L
#define LIST_MODULES_ALL        (LIST_MODULES_32BIT | LIST_MODULES_64BIT)

/* Module information */
typedef struct _MODULEINFO {
    LPVOID  lpBaseOfDll;
    DWORD   SizeOfImage;
    LPVOID  EntryPoint;
} MODULEINFO;
typedef MODULEINFO  *LPMODULEINFO;

/* Working set block */
typedef union _PSAPI_WORKING_SET_BLOCK {
    ULONG_PTR   Flags;
    struct {
        ULONG_PTR   Protection  : 5;
        ULONG_PTR   ShareCount  : 3;
        ULONG_PTR   Shared      : 1;
        ULONG_PTR   Reserved    : 3;
        ULONG_PTR   VirtualPage : 20;
    };
} PSAPI_WORKING_SET_BLOCK;
typedef PSAPI_WORKING_SET_BLOCK *PPSAPI_WORKING_SET_BLOCK;

/* Working set information */
typedef struct _PSAPI_WORKING_SET_INFORMATION {
    ULONG_PTR               NumberOfEntries;
    PSAPI_WORKING_SET_BLOCK WorkingSetInfo[1];
} PSAPI_WORKING_SET_INFORMATION;
typedef PSAPI_WORKING_SET_INFORMATION   *PPSAPI_WORKING_SET_INFORMATION;

/* Working set block (extended version) */
typedef union _PSAPI_WORKING_SET_EX_BLOCK {
    ULONG_PTR   Flags;
    struct {
        ULONG_PTR   Valid           : 1;
        ULONG_PTR   ShareCount      : 3;
        ULONG_PTR   Win32Protection : 11;
        ULONG_PTR   Shared          : 1;
        ULONG_PTR   Node            : 6;
        ULONG_PTR   Locked          : 1;
        ULONG_PTR   LargePage       : 1;
    };
} PSAPI_WORKING_SET_EX_BLOCK;
typedef PSAPI_WORKING_SET_EX_BLOCK  *PPSAPI_WORKING_SET_EX_BLOCK;

/* Working set information (exteneded version) */
typedef struct _PSAPI_WORKING_SET_EX_INFORMATION {
    PVOID                       VirtualAddress;
    PSAPI_WORKING_SET_EX_BLOCK  VirtualAttributes;
} PSAPI_WORKING_SET_EX_INFORMATION;
typedef PSAPI_WORKING_SET_EX_INFORMATION    *PPSAPI_WORKING_SET_EX_INFORMATION;

/* Working set watch information */
typedef struct _PSAPI_WS_WATCH_INFORMATION {
    LPVOID  FaultingPc;
    LPVOID  FaultingVa;
} PSAPI_WS_WATCH_INFORMATION;
typedef PSAPI_WS_WATCH_INFORMATION  *PPSAPI_WS_WATCH_INFORMATION;

/* Working set watch information (extended version) */
typedef struct _PSAPI_WS_WATCH_INFORMATION_EX {
    PSAPI_WS_WATCH_INFORMATION  BasicInfo;
    ULONG_PTR                   FaultingThreadId;
    ULONG_PTR                   Flags;
} PSAPI_WS_WATCH_INFORMATION_EX;
typedef PSAPI_WS_WATCH_INFORMATION_EX   *PPSAPI_WS_WATCH_INFORMATION_EX;

/* Process memory counters */
typedef struct _PROCESS_MEMORY_COUNTERS {
    DWORD   cb;
    DWORD   PageFaultCount;
    SIZE_T  PeakWorkingSetSize;
    SIZE_T  WorkingSetSize;
    SIZE_T  QuotaPeakPagedPoolUsage;
    SIZE_T  QuotaPagedPoolUsage;
    SIZE_T  QuotaPeakNonPagedPoolUsage;
    SIZE_T  QuotaNonPagedPoolUsage;
    SIZE_T  PagefileUsage;
    SIZE_T  PeakPagefileUsage;
} PROCESS_MEMORY_COUNTERS;
typedef PROCESS_MEMORY_COUNTERS *PPROCESS_MEMORY_COUNTERS;

/* Process memory counters (extended version) */
#if (_WIN32_WINNT >= 0x0501)
typedef struct _PROCESS_MEMORY_COUNTERS_EX {
    DWORD   cb;
    DWORD   PageFaultCount;
    SIZE_T  PeakWorkingSetSize;
    SIZE_T  WorkingSetSize;
    SIZE_T  QuotaPeakPagedPoolUsage;
    SIZE_T  QuotaPagedPoolUsage;
    SIZE_T  QuotaPeakNonPagedPoolUsage;
    SIZE_T  QuotaNonPagedPoolUsage;
    SIZE_T  PagefileUsage;
    SIZE_T  PeakPagefileUsage;
    SIZE_T  PrivateUsage;
} PROCESS_MEMORY_COUNTERS_EX;
typedef PROCESS_MEMORY_COUNTERS_EX  *PPROCESS_MEMORY_COUNTERS_EX;
#endif

/* Performance information */
typedef struct _PERFORMANCE_INFORMATION {
    DWORD   cb;
    SIZE_T  CommitTotal;
    SIZE_T  CommitLimit;
    SIZE_T  CommitPeak;
    SIZE_T  PhysicalTotal;
    SIZE_T  PhysicalAvailable;
    SIZE_T  SystemCache;
    SIZE_T  KernelTotal;
    SIZE_T  KernelPaged;
    SIZE_T  KernelNonpaged;
    SIZE_T  PageSize;
    DWORD   HandleCount;
    DWORD   ProcessCount;
    DWORD   ThreadCount;
} PERFORMANCE_INFORMATION;
typedef PERFORMANCE_INFORMATION *PPERFORMANCE_INFORMATION;
typedef PERFORMANCE_INFORMATION PERFORMACE_INFORMATION;
typedef PERFORMANCE_INFORMATION *PPERFORMACE_INFORMATION;

/* Page file enumeration information */
typedef struct _ENUM_PAGE_FILE_INFORMATION {
    DWORD   cb;
    DWORD   Reserved;
    SIZE_T  TotalSize;
    SIZE_T  TotalInUse;
    SIZE_T  PeakUsage;
} ENUM_PAGE_FILE_INFORMATION;
typedef ENUM_PAGE_FILE_INFORMATION  *PENUM_PAGE_FILE_INFORMATION;

/* Page file enumeration callback */
typedef BOOL (*PENUM_PAGE_FILE_CALLBACKA)( LPVOID, PENUM_PAGE_FILE_INFORMATION, LPCSTR );
typedef BOOL (*PENUM_PAGE_FILE_CALLBACKW)( LPVOID, PENUM_PAGE_FILE_INFORMATION, LPCWSTR );
#ifdef UNICODE
    #define ENUM_PAGE_FILE_CALLBACK ENUM_PAGE_FILE_CALLBACKW
#else
    #define ENUM_PAGE_FILE_CALLBACK ENUM_PAGE_FILE_CALLBACKA
#endif

/* Internal names of functions in KERNEL32.DLL */
#if (PSAPI_VERSION > 1)
    #define EmptyWorkingSet             K32EmptyWorkingSet
    #define EnumDeviceDrivers           K32EnumDeviceDrivers
    #define EnumPageFilesA              K32EnumPageFilesA
    #define EnumPageFilesW              K32EnumPageFilesW
    #define EnumProcessModules          K32EnumProcessModules
    #define EnumProcessModulesEx        K32EnumProcessModulesEx
    #define EnumProcesses               K32EnumProcesses
    #define GetDeviceDriverBaseNameA    K32GetDeviceDriverBaseNameA
    #define GetDeviceDriverBaseNameW    K32GetDeviceDriverBaseNameW
    #define GetDeviceDriverFileNameA    K32GetDeviceDriverFileNameA
    #define GetDeviceDriverFileNameW    K32GetDeviceDriverFileNameW
    #define GetMappedFileNameA          K32GetMappedFileNameA
    #define GetMappedFileNameW          K32GetMappedFileNameW
    #define GetModuleBaseNameA          K32GetModuleBaseNameA
    #define GetModuleBaseNameW          K32GetModuleBaseNameW
    #define GetModuleFileNameExA        K32GetModuleFileNameExA
    #define GetModuleFileNameExW        K32GetModuleFileNameExW
    #define GetModuleInformation        K32GetModuleInformation
    #define GetPerformanceInfo          K32GetPerformanceInfo
    #define GetProcessImageFileNameA    K32GetProcessImageFileNameA
    #define GetProcessImageFileNameW    K32GetProcessImageFileNameW
    #define GetProcessMemoryInfo        K32GetProcessMemoryInfo
    #define GetWsChanges                K32GetWsChanges
    #define GetWsChangesEx              K32GetWsChangesEx
    #define InitializeProcessForWsWatch K32InitializeProcessForWsWatch
    #define QueryWorkingSet             K32QueryWorkingSet
    #define QueryWorkingSetEx           K32QueryWorkingSetEx
#endif

/* Functions in PSAPI.DLL and KERNEL32.DLL */
BOOL WINAPI     EmptyWorkingSet( HANDLE );
BOOL WINAPI     EnumDeviceDrivers( LPVOID *, DWORD, LPDWORD );
BOOL WINAPI     EnumPageFilesA( PENUM_PAGE_FILE_CALLBACKA, LPVOID );
BOOL WINAPI     EnumPageFilesW( PENUM_PAGE_FILE_CALLBACKW, LPVOID );
BOOL WINAPI     EnumProcessModules( HANDLE, HMODULE *, DWORD, LPDWORD );
BOOL WINAPI     EnumProcessModulesEx( HANDLE, HMODULE *, DWORD, LPDWORD, DWORD );
BOOL WINAPI     EnumProcesses( DWORD *, DWORD, LPDWORD );
DWORD WINAPI    GetDeviceDriverBaseNameA( LPVOID, LPSTR, DWORD );
DWORD WINAPI    GetDeviceDriverBaseNameW( LPVOID, LPWSTR, DWORD );
DWORD WINAPI    GetDeviceDriverFileNameA( LPVOID, LPSTR, DWORD );
DWORD WINAPI    GetDeviceDriverFileNameW( LPVOID, LPWSTR, DWORD );
DWORD WINAPI    GetMappedFileNameA( HANDLE, LPVOID, LPSTR, DWORD );
DWORD WINAPI    GetMappedFileNameW( HANDLE, LPVOID, LPWSTR, DWORD );
DWORD WINAPI    GetModuleBaseNameA( HANDLE, HMODULE, LPSTR, DWORD );
DWORD WINAPI    GetModuleBaseNameW( HANDLE, HMODULE, LPWSTR, DWORD );
DWORD WINAPI    GetModuleFileNameExA( HANDLE, HMODULE, LPSTR, DWORD );
DWORD WINAPI    GetModuleFileNameExW( HANDLE, HMODULE, LPWSTR, DWORD );
BOOL WINAPI     GetModuleInformation( HANDLE, HMODULE, LPMODULEINFO, DWORD );
BOOL WINAPI     GetPerformanceInfo( PPERFORMANCE_INFORMATION, DWORD );
DWORD WINAPI    GetProcessImageFileNameA( HANDLE, LPSTR, DWORD );
DWORD WINAPI    GetProcessImageFileNameW( HANDLE, LPWSTR, DWORD );
BOOL WINAPI     GetProcessMemoryInfo( HANDLE, PPROCESS_MEMORY_COUNTERS, DWORD );
BOOL WINAPI     GetWsChanges( HANDLE, PPSAPI_WS_WATCH_INFORMATION, DWORD );
BOOL WINAPI     GetWsChangesEx( HANDLE, PPSAPI_WS_WATCH_INFORMATION_EX, PDWORD );
BOOL WINAPI     InitializeProcessForWsWatch( HANDLE );
BOOL WINAPI     QueryWorkingSet( HANDLE, PVOID, DWORD );
BOOL WINAPI     QueryWokringSetEx( HANDLE, PVOID, DWORD );

/* Map generic function names to the appropriate ANSI or Unicode version. */
#ifdef UNICODE
    #define EnumPageFiles           EnumPageFilesW
    #define GetDeviceDriverBaseName GetDeviceDriverBaseNameW
    #define GetDeviceDriverFileName GetDeviceDriverFileNameW
    #define GetMappedFileName       GetMappedFileNameW
    #define GetModuleBaseName       GetModuleBaseNameW
    #define GetModuleFileNameEx     GetModuleFileNameExW
    #define GetProcessImageFileName GetProcessImageFileNameW
#else
    #define EnumPageFiles           EnumPageFilesA
    #define GetDeviceDriverBaseName GetDeviceDriverBaseNameA
    #define GetDeviceDriverFileName GetDeviceDriverFileNameA
    #define GetMappedFileName       GetMappedFileNameA
    #define GetModuleBaseName       GetModuleBaseNameA
    #define GetModuleFileNameEx     GetModuleFileNameExA
    #define GetProcessImageFileName GetProcessImageFileNameA
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _PSAPI_H_ */
