/*
 *  odbcinst.h  Open Database Connectivity (ODBC) installation functions
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

#ifndef __ODBCINST_H
#define __ODBCINST_H

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <sql.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Calling convention for ODBC installation functions */
#define INSTAPI __stdcall

/* SQLConfigDataSource() request types */
#define ODBC_ADD_DSN                1
#define ODBC_CONFIG_DSN             2
#define ODBC_REMOVE_DSN             3
#if (ODBCVER >= 0x0250)
    #define ODBC_ADD_SYS_DSN        4
    #define ODBC_CONFIG_SYS_DSN     5
    #define ODBC_REMOVE_SYS_DSN     6
#endif
#if (ODBCVER >= 0x0300)
    #define ODBC_REMOVE_DEFAULT_DSN 7
#endif

/* Install request types */
#if (ODBCVER >= 0x0250)
    #define ODBC_INSTALL_INQUIRY    1
    #define ODBC_INSTALL_COMPLETE   2
#endif

/* Configure request types */
#if (ODBCVER >= 0x0250)
    #define ODBC_INSTALL_DRIVER     1
    #define ODBC_REMOVE_DRIVER      2
    #define ODBC_CONFIG_DRIVER      3
    #define ODBC_CONFIG_DRIVER_MAX  100
#endif

/* SQLGetConfigMode() flags */
#if (ODBCVER >= 0x0300)
    #define ODBC_BOTH_DSN   0L
    #define ODBC_USER_DSN   1L
    #define ODBC_SYSTEM_DSN 2L
#endif

/* SQLInstallerError() error codes */
#if (ODBCVER >= 0x0300)
    #define ODBC_ERROR_GENERAL_ERR              1L
    #define ODBC_ERROR_INVALID_BUFF_LEN         2L
    #define ODBC_ERROR_INVALID_HWND             3L
    #define ODBC_ERROR_INVALID_STR              4L
    #define ODBC_ERROR_INVALID_REQUEST_TYPE     5L
    #define ODBC_ERROR_COMPONENT_NOT_FOUND      6L
    #define ODBC_ERROR_INVALID_NAME             7L
    #define ODBC_ERROR_INVALID_KEYWORD_VALUE    8L
    #define ODBC_ERROR_INVALID_DSN              9L
    #define ODBC_ERROR_INVALID_INF              10L
    #define ODBC_ERROR_REQUEST_FAILED           11L
    #define ODBC_ERROR_INVALID_PATH             12L
    #define ODBC_ERROR_LOAD_LIB_FAILED          13L
    #define ODBC_ERROR_INVALID_PARAM_SEQUENCE   14L
    #define ODBC_ERROR_INVALID_LOG_FILE         15L
    #define ODBC_ERROR_USER_CANCELED            16L
    #define ODBC_ERROR_USAGE_UPDATE_FAILED      17L
    #define ODBC_ERROR_CREATE_DSN_FAILED        18L
    #define ODBC_ERROR_WRITING_SYSINFO_FAILED   19L
    #define ODBC_ERROR_REMOVE_DSN_FAILED        20L
    #define ODBC_ERROR_OUT_OF_MEM               21L
    #define ODBC_ERROR_OUTPUT_STRING_TRUNCATED  22L
    #define ODBC_ERROR_NOTRANINFO               23L
    #define ODBC_ERROR_MAX                      ODBC_ERROR_NOTRANINFO
#endif

/* Functions in ODBCCP32.DLL */
BOOL INSTAPI        SQLConfigDataSource( HWND, WORD, LPCSTR, LPCSTR );
BOOL INSTAPI        SQLConfigDataSourceW( HWND, WORD, LPCWSTR, LPCWSTR );
BOOL INSTAPI        SQLCreateDataSource( HWND, LPCSTR );
BOOL INSTAPI        SQLCreateDataSourceW( HWND, LPCWSTR );
BOOL INSTAPI        SQLGetAvailableDrivers( LPCSTR, LPSTR, WORD, WORD * );
BOOL INSTAPI        SQLGetAvailableDriversW( LPCWSTR, LPWSTR, WORD, WORD * );
BOOL INSTAPI        SQLGetInstalledDrivers( LPSTR, WORD, WORD * );
BOOL INSTAPI        SQLGetInstalledDriversW( LPWSTR, WORD, WORD * );
int INSTAPI         SQLGetPrivateProfileString( LPCSTR, LPCSTR, LPCSTR, LPSTR, int, LPCSTR );
int INSTAPI         SQLGetPrivateProfileStringW( LPCWSTR, LPCWSTR, LPCWSTR, LPWSTR, int, LPCWSTR );
BOOL INSTAPI        SQLGetTranslator( HWND, LPSTR, WORD, WORD *, LPSTR, WORD, WORD *, DWORD * );
BOOL INSTAPI        SQLGetTranslatorW( HWND, LPWSTR, WORD, WORD *, LPWSTR, WORD, WORD *, DWORD * );
BOOL INSTAPI        SQLInstallDriver( LPCSTR, LPCSTR, LPSTR, WORD, WORD * );
BOOL INSTAPI        SQLInstallDriverManager( LPSTR, WORD, WORD * );
BOOL INSTAPI        SQLInstallDriverManagerW( LPWSTR, WORD, WORD * );
BOOL INSTAPI        SQLInstallDriverW( LPCWSTR, LPCWSTR, LPWSTR, WORD, WORD * );
BOOL INSTAPI        SQLInstallODBC( HWND, LPCSTR, LPCSTR, LPCSTR );
BOOL INSTAPI        SQLInstallODBCW( HWND, LPCWSTR, LPCWSTR, LPCWSTR );
BOOL INSTAPI        SQLManageDataSources( HWND );
BOOL INSTAPI        SQLRemoveDSNFromIni( LPCSTR );
BOOL INSTAPI        SQLRemoveDSNFromIniW( LPCWSTR );
BOOL INSTAPI        SQLRemoveDefaultDataSource( void );
BOOL INSTAPI        SQLValidDSN( LPCSTR );
BOOL INSTAPI        SQLValidDSNW( LPCWSTR );
BOOL INSTAPI        SQLWriteDSNToIni( LPCSTR, LPCSTR );
BOOL INSTAPI        SQLWriteDSNToIniW( LPCWSTR, LPCWSTR );
BOOL INSTAPI        SQLWritePrivateProfileString( LPCSTR, LPCSTR, LPCSTR, LPCSTR );
BOOL INSTAPI        SQLWritePrivateProfileStringW( LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR );
#if (ODBCVER >= 0x0250)
BOOL INSTAPI        SQLConfigDriver( HWND, WORD, LPCSTR, LPCSTR, LPSTR, WORD, WORD * );
BOOL INSTAPI        SQLConfigDriverW( HWND, WORD, LPCWSTR, LPCWSTR, LPWSTR, WORD, WORD * );
BOOL INSTAPI        SQLInstallTranslator( LPCSTR, LPCSTR, LPCSTR, LPSTR, WORD, WORD *, WORD, LPDWORD );
BOOL INSTAPI        SQLInstallTranslatorW( LPCWSTR, LPCWSTR, LPCWSTR, LPWSTR, WORD, WORD *, WORD, LPDWORD );
BOOL INSTAPI        SQLRemoveDriver( LPCSTR, BOOL, LPDWORD );
BOOL INSTAPI        SQLRemoveDriverManager( LPDWORD );
BOOL INSTAPI        SQLRemoveDriverW( LPCWSTR, BOOL, LPDWORD );
BOOL INSTAPI        SQLRemoveTranslator( LPCSTR, LPDWORD );
BOOL INSTAPI        SQLRemoveTranslatorW( LPCWSTR, LPDWORD );
#endif
#if (ODBCVER >= 0x0300)
BOOL INSTAPI        SQLGetConfigMode( UWORD * );
BOOL INSTAPI        SQLInstallDriverEx( LPCSTR, LPCSTR, LPSTR, WORD, WORD *, WORD, LPDWORD );
BOOL INSTAPI        SQLInstallDriverExW( LPCWSTR, LPCWSTR, LPWSTR, WORD, WORD *, WORD, LPDWORD );
BOOL INSTAPI        SQLInstallTranslatorEx( LPCSTR, LPCSTR, LPSTR, WORD, WORD *, WORD, LPDWORD );
BOOL INSTAPI        SQLInstallTranslatorExW( LPCWSTR, LPCWSTR, LPWSTR, WORD, WORD *, WORD, LPDWORD );
SQLRETURN INSTAPI   SQLInstallerError( WORD, DWORD *, LPSTR, WORD, WORD * );
SQLRETURN INSTAPI   SQLInstallerErrorW( WORD, DWORD *, LPWSTR, WORD, WORD * );
SQLRETURN INSTAPI   SQLPostInstallerError( DWORD, LPCSTR );
SQLRETURN INSTAPI   SQLPostInstallerErrorW( DWORD, LPCWSTR );
BOOL INSTAPI        SQLReadFileDSN( LPCSTR, LPCSTR, LPCSTR, LPSTR, WORD, WORD * );
BOOL INSTAPI        SQLReadFileDSNW( LPCWSTR, LPCWSTR, LPCWSTR, LPWSTR, WORD, WORD * );
BOOL INSTAPI        SQLSetConfigMode( UWORD );
BOOL INSTAPI        SQLWriteFileDSN( LPCSTR, LPCSTR, LPCSTR, LPCSTR );
BOOL INSTAPI        SQLWriteFileDSNW( LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR );
#endif

/* Functions exported by ODBC drivers */
BOOL INSTAPI    ConfigDSN( HWND, WORD, LPCSTR, LPCSTR );
BOOL INSTAPI    ConfigDSNW( HWND, WORD, LPCWSTR, LPCWSTR );
BOOL INSTAPI    ConfigTranslator( HWND, DWORD * );
#if (ODBCVER >= 0x0250)
BOOL INSTAPI    ConfigDriver( HWND, WORD, LPCSTR, LPCSTR, LPSTR, WORD, WORD * );
BOOL INSTAPI    ConfigDriverW( HWND, WORD, LPCWSTR, LPCWSTR, LPWSTR, WORD, WORD * );
#endif

/* Map generic function names to the appropriate ANSI or Unicode version. */
#ifndef SQL_NOUNICODEMAP
    #ifdef UNICODE
        #define SQLConfigDataSource             SQLConfigDataSourceW
        #define SQLConfigDriver                 SQLConfigDriverW
        #define SQLCreateDataSource             SQLCreateDataSourceW
        #define SQLGetAvailableDrivers          SQLGetAvailableDriversW
        #define SQLGetInstalledDrivers          SQLGetInstalledDriversW
        #define SQLGetPrivateProfileString      SQLGetPrivateProfileStringW
        #define SQLGetTranslator                SQLGetTranslatorW
        #define SQLInstallDriver                SQLInstallDriverW
        #define SQLInstallDriverEx              SQLInstallDriverExW
        #define SQLInstallDriverManager         SQLInstallDriverManagerW
        #define SQLInstallODBC                  SQLInstallODBCW
        #define SQLInstallTranslator            SQLInstallTranslatorW
        #define SQLInstallTranslatorEx          SQLInstallTranslatorExW
        #define SQLInstallerError               SQLInstallerErrorW
        #define SQLPostInstallerError           SQLPostInstallerErrorW
        #define SQLReadFileDSN                  SQLReadFileDSNW
        #define SQLRemoveDSNFromIni             SQLRemoveDSNFromIniW
        #define SQLRemoveDriver                 SQLRemoveDriverW
        #define SQLRemoveTranslator             SQLRemoveTranslatorW
        #define SQLValidDSN                     SQLValidDSNW
        #define SQLWriteDSNToIni                SQLWriteDSNToIniW
        #define SQLWriteFileDSN                 SQLWriteFileDSNW
        #define SQLWritePrivateProfileString    SQLWritePrivateProfileStringW
    #endif
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __ODBCINST_H */
