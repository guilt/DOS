/*
 *  tlhelp32.h  Tool help functions
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

#ifndef _INC_TOOLHELP32
#define _INC_TOOLHELP32

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Maximum string lengths */
#define MAX_MODULE_NAME32   255

/* CreateToolhelp32Snapshot() flags */
#define TH32CS_SNAPHEAPLIST 0x00000001L
#define TH32CS_SNAPPROCESS  0x00000002L
#define TH32CS_SNAPTHREAD   0x00000004L
#define TH32CS_SNAPMODULE   0x00000008L
#define TH32CS_SNAPMODULE32 0x00000010L
#define TH32CS_SNAPALL \
    (TH32CS_SNAPHEAPLIST | TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD | TH32CS_SNAPMODULE)
#define TH32CS_INHERIT      0x80000000L

/* Heap list flags */
#define HF32_DEFAULT    0x00000001L
#define HF32_SHARED     0x00000002L

/* Heap entry flags */
#define LF32_FIXED      0x00000001L
#define LF32_FREE       0x00000002L
#define LF32_MOVEABLE   0x00000004L

/* Heap list */
typedef struct tagHEAPLIST32 {
    SIZE_T      dwSize;
    DWORD       th32ProcessID;
    ULONG_PTR   th32HeapID;
    DWORD       dwFlags;
} HEAPLIST32;
typedef HEAPLIST32  *PHEAPLIST32;
typedef HEAPLIST32  *LPHEAPLIST32;

/* Heap entry */
typedef struct tagHEAPENTRY32 {
    SIZE_T      dwSize;
    HANDLE      hHandle;
    ULONG_PTR   dwAddress;
    SIZE_T      dwBlockSize;
    DWORD       dwFlags;
    DWORD       dwLockCount;
    DWORD       dwResvd;
    DWORD       th32ProcessID;
    ULONG_PTR   th32HeapID;
} HEAPENTRY32;
typedef HEAPENTRY32 *PHEAPENTRY32;
typedef HEAPENTRY32 *LPHEAPENTRY32;

/* Process entry */
typedef struct tagPROCESSENTRY32 {
    DWORD       dwSize;
    DWORD       cntUsage;
    DWORD       th32ProcessID;
    ULONG_PTR   th32DefaultHeapID;
    DWORD       th32ModuleID;
    DWORD       cntThreads;
    DWORD       th32ParentProcessID;
    LONG        pcPriClassBase;
    DWORD       dwFlags;
    CHAR        szExeFile[MAX_PATH];
} PROCESSENTRY32;
typedef PROCESSENTRY32  *PPROCESSENTRY32;
typedef PROCESSENTRY32  *LPPROCESSENTRY32;

/* Process entry (Unicode version) */
typedef struct tagPROCESSENTRY32W {
    DWORD       dwSize;
    DWORD       cntUsage;
    DWORD       th32ProcessID;
    ULONG_PTR   th32DefaultHeapID;
    DWORD       th32ModuleID;
    DWORD       cntThreads;
    DWORD       th32ParentProcessID;
    LONG        pcPriClassBase;
    DWORD       dwFlags;
    WCHAR       szExeFile[MAX_PATH];
} PROCESSENTRY32W;
typedef PROCESSENTRY32W *PPROCESSENTRY32W;
typedef PROCESSENTRY32W *LPPROCESSENTRY32W;
#ifdef UNICODE
    #define PROCESSENTRY32      PROCESSENTRY32W
    #define PPROCESSENTRY32     PPROCESSENTRY32W
    #define LPPROCESSENTRY32    LPPROCESSENTRY32W
#endif

/* Thread entry */
typedef struct tagTHREADENTRY32 {
    DWORD   dwSize;
    DWORD   cntUsage;
    DWORD   th32ThreadID;
    DWORD   th32OwnerProcessID;
    LONG    tpBasePri;
    LONG    tpDeltaPri;
    DWORD   dwFlags;
} THREADENTRY32;
typedef THREADENTRY32   *PTHREADENTRY32;
typedef THREADENTRY32   *LPTHREADENTRY32;

/* Module entry */
typedef struct tagMODULEENTRY32 {
    DWORD   dwSize;
    DWORD   th32ModuleID;
    DWORD   th32ProcessID;
    DWORD   GlblcntUsage;
    DWORD   ProccntUsage;
    BYTE    *modBaseAddr;
    DWORD   modBaseSize;
    HMODULE hModule;
    char    szModule[MAX_MODULE_NAME32 + 1];
    char    szExePath[MAX_PATH];
} MODULEENTRY32;
typedef MODULEENTRY32   *PMODULEENTRY32;
typedef MODULEENTRY32   *LPMODULEENTRY32;

/* Module entry (Unicode version) */
typedef struct tagMODULEENTRY32W {
    DWORD   dwSize;
    DWORD   th32ModuleID;
    DWORD   th32ProcessID;
    DWORD   GlblcntUsage;
    DWORD   ProccntUsage;
    BYTE    *modBaseAddr;
    DWORD   modBaseSize;
    HMODULE hModule;
    WCHAR   szModule[MAX_MODULE_NAME32 + 1];
    WCHAR   szExePath[MAX_PATH];
} MODULEENTRY32W;
typedef MODULEENTRY32W  *PMODULEENTRY32W;
typedef MODULEENTRY32W  *LPMODULEENTRY32W;
#ifdef UNICODE
    #define MODULEENTRY32   MODULEENTRY32W
    #define PMODULEENTRY32  PMODULEENTRY32W
    #define LPMODULEENTRY32 LPMODULEENTRY32W
#endif

/* Functions in KERNEL32.DLL */
HANDLE WINAPI   CreateToolhelp32Snapshot( DWORD, DWORD );
BOOL WINAPI     Heap32First( LPHEAPENTRY32, DWORD, ULONG_PTR );
BOOL WINAPI     Heap32ListFirst( HANDLE, LPHEAPLIST32 );
BOOL WINAPI     Heap32ListNext( HANDLE, LPHEAPLIST32 );
BOOL WINAPI     Heap32Next( LPHEAPENTRY32 );
BOOL WINAPI     Module32First( HANDLE, LPMODULEENTRY32 );
BOOL WINAPI     Module32FirstW( HANDLE, LPMODULEENTRY32W );
BOOL WINAPI     Module32Next( HANDLE, LPMODULEENTRY32 );
BOOL WINAPI     Module32NextW( HANDLE, LPMODULEENTRY32W );
BOOL WINAPI     Process32First( HANDLE, LPPROCESSENTRY32 );
BOOL WINAPI     Process32FirstW( HANDLE, LPPROCESSENTRY32W );
BOOL WINAPI     Process32Next( HANDLE, LPPROCESSENTRY32 );
BOOL WINAPI     Process32NextW( HANDLE, LPPROCESSENTRY32W );
BOOL WINAPI     Thread32First( HANDLE, LPTHREADENTRY32 );
BOOL WINAPI     Thread32Next( HANDLE, LPTHREADENTRY32 );
BOOL WINAPI     Toolhelp32ReadProcessMemory( DWORD, LPCVOID, LPVOID, SIZE_T, SIZE_T * );

/* Map generic function names to the appropriate ANSI or Unicode version. */
#ifdef UNICODE
    #define Module32First   Module32FirstW
    #define Module32Next    Module32NextW
    #define Process32First  Process32FirstW
    #define Process32Next   Process32NextW
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _INC_TOOLHELP32 */
