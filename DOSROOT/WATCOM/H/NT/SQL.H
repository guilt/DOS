/*
 *  sql.h       Open Database Connectivity (ODBC) functions
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

#ifndef __SQL
#define __SQL

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <sqltypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Special values */
#define SQL_NULL_DATA       (-1)
#define SQL_DATA_AT_EXEC    (-2)

/* ODBC return codes */
#define SQL_SUCCESS                     0L
#define SQL_SUCCESS_WITH_INFO           1L
#define SQL_STILL_EXECUTING             2L
#define SQL_NEED_DATA                   99L
#if (ODBCVER >= 0x0300)
    #define SQL_NO_DATA                 100L
#endif
#if (ODBCVER >= 0x0380)
    #define SQL_PARAM_DATA_AVAILABLE    101L
#endif
#define SQL_ERROR                       (-1L)
#define SQL_INVALID_HANDLE              (-2L)

/* Macro to test for success of ODBC functions */
#define SQL_SUCCEEDED( x )  (((x) & 0xFFFFFFFEL) == 0x00000000L)

/* Null-terminated string flags */
#define SQL_NTS     (-3L)
#define SQL_NTSL    (-3L)

/* ODBC maximum message length */
#define SQL_MAX_MESSAGE_LENGTH  512

/* ODBC date and time lengths */
#if (ODBCVER >= 0x0300)
    #define SQL_DATE_LEN        10
    #define SQL_TIME_LEN        8
    #define SQL_TIMESTAMP_LEN   19
#endif

/* ODBC handle types */
#if (ODBCVER >= 0x0300)
    #define SQL_HANDLE_ENV  1L
    #define SQL_HANDLE_DBC  2L
    #define SQL_HANDLE_STMT 3L
    #define SQL_HANDLE_DESC 4L
#endif

/* ODBC environment attributes */
#if (ODBCVER >= 0x0300)
    #define SQL_ATTR_OUTPUT_NTS 10001L
#endif

/* ODBC connection attributes */
#if (ODBCVER >= 0x0300)
    #define SQL_ATTR_AUTO_IPD       10001L
    #define SQL_ATTR_METADATA_ID    10014L
#endif

/* ODBC statement attributes */
#if (ODBCVER >= 0x0300)
    #define SQL_ATTR_APP_ROW_DESC       10010L
    #define SQL_ATTR_APP_PARAM_DESC     10011L
    #define SQL_ATTR_IMP_ROW_DESC       10012L
    #define SQL_ATTR_IMP_PARAM_DESC     10013L
    #define SQL_ATTR_CURSOR_SCROLLABLE  (-1L)
    #define SQL_ATTR_CURSOR_SENSITIVITY (-2L)
#endif

/* SQL_CURSOR_SCROLLABLE values */
#if (ODBCVER >= 0x0300)
    #define SQL_NONSCROLLABLE   0L
    #define SQL_SCROLLABLE      1L
#endif

/* ODBC descriptor field identifiers */
#if (ODBCVER >= 0x0300)
    #define SQL_DESC_COUNT                  1001L
    #define SQL_DESC_TYPE                   1002L
    #define SQL_DESC_LENGTH                 1003L
    #define SQL_DESC_OCTET_LENGTH_PTR       1004L
    #define SQL_DESC_PRECISION              1005L
    #define SQL_DESC_SCALE                  1006L
    #define SQL_DESC_DATETIME_INTERVAL_CODE 1007L
    #define SQL_DESC_NULLABLE               1008L
    #define SQL_DESC_INDICATOR_PTR          1009L
    #define SQL_DESC_DATA_PTR               1010L
    #define SQL_DESC_NAME                   1011L
    #define SQL_DESC_UNNAMED                1012L
    #define SQL_DESC_OCTET_LENGTH           1013L
    #define SQL_DESC_ALLOC_TYPE             1099L
#endif

/* ODBC diagnostic field identifiers */
#if (ODBCVER >= 0x0300)
    #define SQL_DIAG_RETURNCODE             1L
    #define SQL_DIAG_NUMBER                 2L
    #define SQL_DIAG_ROWCOUNT               3L
    #define SQL_DIAG_SQLSTATE               4L
    #define SQL_DIAG_NATIVE                 5L
    #define SQL_DIAG_MESSAGE_TEXT           6L
    #define SQL_DIAG_DYNAMIC_FUNCTION       7L
    #define SQL_DIAG_CLASS_ORIGIN           8L
    #define SQL_DIAG_SUBCLASS_ORIGIN        9L
    #define SQL_DIAG_CONNECTION_NAME        10L
    #define SQL_DIAG_SERVER_NAME            11L
    #define SQL_DIAG_DYNAMIC_FUNCTION_CODE  12L
#endif

/* ODBC diagnostic dynamic function codes */
#if (ODBCVER >= 0x0300)
    #define SQL_DIAG_UNKNOWN_STATEMENT      0L
    #define SQL_DIAG_ALTER_DOMAIN           3L
    #define SQL_DIAG_ALTER_TABLE            4L
    #define SQL_DIAG_CREATE_ASSERTION       6L
    #define SQL_DIAG_CALL                   7L
    #define SQL_DIAG_CREATE_CHARACTER_SET   8L
    #define SQL_DIAG_CREATE_COLLATION       10L
    #define SQL_DIAG_DELETE_WHERE           19L
    #define SQL_DIAG_CREATE_DOMAIN          23L
    #define SQL_DIAG_DROP_ASSERTION         24L
    #define SQL_DIAG_DROP_CHARACTER_SET     25L
    #define SQL_DIAG_DROP_COLLATION         26L
    #define SQL_DIAG_DROP_DOMAIN            27L
    #define SQL_DIAG_DROP_SCHEMA            31L
    #define SQL_DIAG_DROP_TABLE             32L
    #define SQL_DIAG_DROP_TRANSLATION       33L
    #define SQL_DIAG_DROP_VIEW              36L
    #define SQL_DIAG_DYNAMIC_DELETE_CURSOR  38L
    #define SQL_DIAG_GRANT                  48L
    #define SQL_DIAG_INSERT                 50L
    #define SQL_DIAG_REVOKE                 59L
    #define SQL_DIAG_CREATE_SCHEMA          64L
    #define SQL_DIAG_CREATE_TABLE           77L
    #define SQL_DIAG_CREATE_TRANSLATION     79L
    #define SQL_DIAG_DYNAMIC_UPDATE_CURSOR  81L
    #define SQL_DIAG_UPDATE_WHERE           82L
    #define SQL_DIAG_CREATE_VIEW            84L
    #define SQL_DIAG_SELECT_CURSOR          85L
    #define SQL_DIAG_CREATE_INDEX           (-1L)
    #define SQL_DIAG_DROP_INDEX             (-2L)
#endif

/* ODBC data type codes */
#define SQL_UNKNOWN_TYPE    0L
#define SQL_CHAR            1L
#define SQL_NUMERIC         2L
#define SQL_DECIMAL         3L
#define SQL_INTEGER         4L
#define SQL_SMALLINT        5L
#define SQL_FLOAT           6L
#define SQL_REAL            7L
#define SQL_DOUBLE          8L
#if (ODBCVER >= 0x0300)
    #define SQL_DATETIME    9L
#endif
#define SQL_VARCHAR         12L

/* ODBC date and time type codes */
#if (ODBCVER >= 0x0300)
    #define SQL_TYPE_DATE       91L
    #define SQL_TYPE_TIME       92L
    #define SQL_TYPE_TIMESTAMP  93L
#endif

/* Cursor sensitivities */
#if (ODBCVER >= 0x0300)
    #define SQL_UNSPECIFIED 0L
    #define SQL_INSENSITIVE 1L
    #define SQL_SENSITIVE   2L
#endif

/* SQLGetTypeInfo() requests */
#define SQL_ALL_TYPES   0L

/* Conversion codes */
#if (ODBCVER >= 0x0300)
    #define SQL_DEFAULT 9L
#endif

/* SQLGetData() codes */
#if (ODBCVER >= 0x0300)
    #define SQL_ARD_TYPE    (-99L)
#endif
#if (ODBCVER >= 0x0380)
    #define SQL_APD_TYPE    (-100L)
#endif

/* ODBC date and time type subcodes */
#if (ODBCVER >= 0x0300)
    #define SQL_CODE_DATE       1L
    #define SQL_CODE_TIME       2L
    #define SQL_CODE_TIMESTAMP  3L
#endif

/* ODBC Boolean values */
#if (ODBCVER >= 0x0300)
    #define SQL_FALSE   0L
    #define SQL_TRUE    1L
#endif

/* Nullable values */
#define SQL_NO_NULLS            0L
#define SQL_NULLABLE            1L
#define SQL_NULLABLE_UNKNOWN    2L

/* SQLGetTypeInfo() return values */
#if (ODBCVER >= 0x0300)
    #define SQL_PRED_NONE   0L
    #define SQL_PRED_CHAR   1L
    #define SQL_PRED_BASIC  2L
#endif

/* Unnamed field values */
#if (ODBCVER >= 0x0300)
    #define SQL_NAMED       0L
    #define SQL_UNNAMBED    1L
#endif

/* ODBC descriptor allocation types */
#if (ODBCVER >= 0x0300)
    #define SQL_DESC_ALLOC_AUTO 1L
    #define SQL_DESC_ALLOC_USER 2L
#endif

/* SQLFreeStmt() options */
#define SQL_CLOSE           0L
#define SQL_DROP            1L
#define SQL_UNBIND          2L
#define SQL_RESET_PARAMS    3L

/* Fetch orientations */
#define SQL_FETCH_NEXT      1L
#define SQL_FETCH_FIRST     2L
#define SQL_FETCH_LAST      3L
#define SQL_FETCH_PRIOR     4L
#define SQL_FETCH_ABSOLUTE  5L
#define SQL_FETCH_RELATIVE  6L

/* SQLEndTran() options */
#define SQL_COMMIT      0L
#define SQL_ROLLBACK    1L

/* Null handle values */
#define SQL_NULL_HENV       0
#define SQL_NULL_HDBC       0
#define SQL_NULL_HSTMT      0
#if (ODBCVER >= 0x0300)
    #define SQL_NULL_HDESC  0
    #define SQL_NULL_HANDLE 0
#endif

/* ODBC scopes */
#define SQL_SCOPE_CURROW        0
#define SQL_SCOPE_TRANSACTION   1
#define SQL_SCOPE_SESSION       2

/* ODBC pseudocolumns */
#define SQL_PC_UNKNOWN          0
#if (ODBCVER >= 0x0300)
    #define SQL_PC_NON_PSEUDO   1
#endif
#define SQL_PC_PSEUDO           2

/* Identifier type special value */
#if (ODBCVER >= 0x0300)
    #define SQL_ROW_IDENTIFIER  1L
#endif

/* ODBC index special values */
#define SQL_INDEX_UNIQUE    0
#define SQL_INDEX_ALL       1
#define SQL_INDEX_CLUSTERED 1
#define SQL_INDEX_HASHED    2
#define SQL_INDEX_OTHER     3

/* ODBC function identifiers */
#define SQL_API_SQLALLOCCONNECT         1
#define SQL_API_SQLALLOCENV             2
#define SQL_API_SQLALLOCSTMT            3
#define SQL_API_SQLBINDCOL              4
#define SQL_API_SQLCANCEL               5
#if (ODBCVER >= 0x0300)
    #define SQL_API_SQLCOLATTRIBUTE     6
#endif
#define SQL_API_SQLCONNECT              7
#define SQL_API_SQLDESCRIBECOL          8
#define SQL_API_SQLDISCONNECT           9
#define SQL_API_SQLERROR                10
#define SQL_API_SQLEXECDIRECT           11
#define SQL_API_SQLEXECUTE              12
#define SQL_API_SQLFETCH                13
#define SQL_API_SQLFREECONNECT          14
#define SQL_API_SQLFREEENV              15
#define SQL_API_SQLFREESTMT             16
#define SQL_API_SQLGETCURSORNAME        17
#define SQL_API_SQLNUMRESULTCOLS        18
#define SQL_API_SQLPREPARE              19
#define SQL_API_SQLROWCOUNT             20
#define SQL_API_SQLSETCURSORNAME        21
#define SQL_API_SQLSETPARAM             22
#define SQL_API_SQLTRANSACT             23
#define SQL_API_SQLCOLUMNS              40
#define SQL_API_SQLGETCONNECTOPTION     42
#define SQL_API_SQLGETDATA              43
#define SQL_API_SQLGETFUNCTIONS         44
#define SQL_API_SQLGETINFO              45
#define SQL_API_SQLGETSTMTOPTION        46
#define SQL_API_SQLGETTYPEINFO          47
#define SQL_API_SQLPARAMDATA            48
#define SQL_API_SQLPUTDATA              49
#define SQL_API_SQLSETCONNECTOPTION     50
#define SQL_API_SQLSETSTMTOPTION        51
#define SQL_API_SQLSPECIALCOLUMNS       52
#define SQL_API_SQLSTATISTICS           53
#define SQL_API_SQLTABLES               54
#define SQL_API_SQLDATASOURCES          57
#if (ODBCVER >= 0x0300)
    #define SQL_API_SQLALLOCHANDLE      1001
    #define SQL_API_SQLBINDPARAM        1002
    #define SQL_API_SQLCLOSECURSOR      1003
    #define SQL_API_SQLCOPYDESC         1004
    #define SQL_API_SQLENDTRAN          1005
    #define SQL_API_SQLFREEHANDLE       1006
    #define SQL_API_SQLGETCONNECTATTR   1007
    #define SQL_API_SQLGETDESCFIELD     1008
    #define SQL_API_SQLGETDESCREC       1009
    #define SQL_API_SQLGETDIAGFIELD     1010
    #define SQL_API_SQLGETDIAGREC       1011
    #define SQL_API_SQLGETENVATTR       1012
    #define SQL_API_SQLGETSTMTATTR      1014
    #define SQL_API_SQLSETCONNECTATTR   1016
    #define SQL_API_SQLSETDESCFIELD     1017
    #define SQL_API_SQLSETDESCREC       1018
    #define SQL_API_SQLSETENVATTR       1019
    #define SQL_API_SQLSETSTMTATTR      1020
    #define SQL_API_SQLFETCHSCROLL      1021
#endif
#if (ODBCVER >= 0x0380)
    #define SQL_API_SQLCANCELHANDLE     1022
#endif

/* SQLGetInfo() indices */
#if (ODBCVER >= 0x0300)
    #define SQL_MAX_DRIVER_CONNECTIONS          0
    #define SQL_MAXIMUM_DRIVER_CONNECTIONS      SQL_MAX_DRIVER_CONNECTIONS
    #define SQL_MAX_CONCURRENT_ACTIVITIES       1
    #define SQL_MAXIMUM_CONCURRENT_ACTIVITIES   SQL_MAX_CONCURRENT_ACTIVITIES
#endif
#define SQL_DATA_SOURCE_NAME                    2
#define SQL_FETCH_DIRECTION                     8
#define SQL_SERVER_NAME                         13
#define SQL_SEARCH_PATTERN_ESCAPE               14
#define SQL_DBMS_NAME                           17
#define SQL_DBMS_VER                            18
#define SQL_ACCESSIBLE_TABLES                   19
#define SQL_ACCESSIBLE_PROCEDURES               20
#define SQL_CURSOR_COMMIT_BEHAVIOR              23
#define SQL_DATA_SOURCE_READ_ONLY               25
#define SQL_DEFAULT_TXN_ISOLATION               26
#define SQL_IDENTIFIER_CASE                     28
#define SQL_IDENTIFIER_QUOTE_CHAR               29
#define SQL_MAX_COLUMN_NAME_LEN                 30
#define SQL_MAXIMUM_COLUMN_NAME_LENGTH          SQL_MAX_COLUMN_NAME_LEN
#define SQL_MAX_CURSOR_NAME_LEN                 31
#define SQL_MAXIMUM_CURSOR_NAME_LENGTH          SQL_MAX_CURSOR_NAME_LEN
#define SQL_MAX_SCHEMA_NAME_LEN                 32
#define SQL_MAXIMUM_SCHEMA_NAME_LENGTH          SQL_MAX_SCHEMA_NAME_LEN
#define SQL_MAX_CATALOG_NAME_LEN                34
#define SQL_MAXIMUM_CATALOG_NAME_LEN            SQL_MAX_CATALOG_NAME_LEN
#define SQL_MAX_TABLE_NAME_LEN                  35
#define SQL_SCROLL_CONCURRENCY                  43
#define SQL_TXN_CAPABLE                         46
#define SQL_TRANSACTION_CAPABLE                 SQL_TXN_CAPABLE
#define SQL_USER_NAME                           47
#define SQL_TXN_ISOLATION_OPTION                72
#define SQL_TRANSACTION_ISOLATION_OPTION        SQL_TXN_ISOLATION_OPTION
#define SQL_INTEGRITY                           73
#define SQL_GETDATA_EXTENSIONS                  81
#define SQL_NULL_COLLATION                      85
#define SQL_ALTER_TABLE                         86
#define SQL_ORDER_BY_COLUMNS_IN_SELECT          90
#define SQL_SPECIAL_CHARACTERS                  94
#define SQL_MAX_COLUMNS_IN_GROUP_BY             97
#define SQL_MAXIMUM_COLUMNS_IN_GROUP_BY         SQL_MAX_COLUMNS_IN_GROUP_BY
#define SQL_MAX_COLUMNS_IN_INDEX                98
#define SQL_MAXIMUM_COLUMNS_IN_INDEX            SQL_MAX_COLUMNS_IN_INDEX
#define SQL_MAX_COLUMNS_IN_ORDER_BY             99
#define SQL_MAXIMUM_COLUMNS_IN_ORDER_BY         SQL_MAX_COLUMNS_IN_ORDER_BY
#define SQL_MAX_COLUMNS_IN_SELECT               100
#define SQL_MAXIMUM_COLUMNS_IN_SELECT           SQL_MAX_COLUMNS_IN_SELECT
#define SQL_MAX_COLUMNS_IN_TABLE                101
#define SQL_MAX_INDEX_SIZE                      102
#define SQL_MAXIMUM_INDEX_SIZE                  SQL_MAX_INDEX_SIZE
#define SQL_MAX_ROW_SIZE                        104
#define SQL_MAXIMUM_ROW_SIZE                    SQL_MAX_ROW_SIZE
#define SQL_MAX_STATEMENT_LEN                   105
#define SQL_MAXIMUM_STATEMENT_LEN               SQL_MAX_STATEMENT_LEN
#define SQL_MAX_TABLES_IN_SELECT                106
#define SQL_MAXIMUM_TABLES_IN_SELECT            SQL_MAX_TABLES_IN_SELECT
#define SQL_MAX_USER_NAME_LEN                   107
#define SQL_MAXIMUM_USER_NAME_LENGTH            SQL_MAX_USER_NAME_LEN
#if (ODBCVER >= 0x0300)
    #define SQL_OJ_CAPABILITIES                 115
    #define SQL_OUTER_JOIN_CAPABILITIES         SQL_OJ_CAPABILITIES
    #define SQL_XOPEN_CLI_YEAR                  10000
    #define SQL_CURSOR_SENSITIVITY              10001
    #define SQL_DESCRIBE_PARAMETER              10002
    #define SQL_CATALOG_NAME                    10003
    #define SQL_COLLATION_SEQ                   10004
    #define SQL_MAX_IDENTIFIER_LEN              10005
    #define SQL_MAXIMUM_IDENTIFIER_LENGTH       SQL_MAX_IDENTIFIER_LEN
#endif

/* SQL_ALTER_TABLE flags */
#if (ODBCVER >= 0x0300)
    #define SQL_AT_ADD_COLUMN       0x00000001L
    #define SQL_AT_DROP_COLUMN      0x00000002L
    #define SQL_AT_ADD_CONSTRAINT   0x00000004L
#endif

/* SQL_ASYNC_MODE values */
#if (ODBCVER >= 0x0300)
    #define SQL_AM_NONE         0L
    #define SQL_AM_CONNECTION   1L
    #define SQL_AM_STATEMENT    2L
#endif

/* SQL_CURSOR_COMMIT_BEHAVIOR values */
#define SQL_CB_DELETE   0L
#define SQL_CB_CLOSE    1L
#define SQL_CB_PRESERVE 2L

/* SQL_FETCH_DIRECTION flags */
#define SQL_FD_FETCH_NEXT       0x00000001L
#define SQL_FD_FETCH_FIRST      0x00000002L
#define SQL_FD_FETCH_LAST       0x00000004L
#define SQL_FD_FETCH_PRIOR      0x00000008L
#define SQL_FD_FETCH_ABSOLUTE   0x00000010L
#define SQL_FD_FETCH_RELATIVE   0x00000020L

/* SQL_GETDATA_EXTENSIONS flags */
#define SQL_GD_ANY_COLUMN   0x00000001L
#define SQL_GD_ANY_ORDER    0x00000002L

/* SQL_IDENTIFIER_CASE values */
#define SQL_IC_UPPER        1
#define SQL_IC_LOWER        2
#define SQL_IC_SENSITIVE    3
#define SQL_IC_MIXED        4

/* SQL_OJ_CAPABILITIES flags */
#if (ODBCVER >= 0x0201)
    #define SQL_OJ_LEFT                 0x00000001L
    #define SQL_OJ_RIGHT                0x00000002L
    #define SQL_OJ_FULL                 0x00000004L
    #define SQL_OJ_NESTED               0x00000008L
    #define SQL_OJ_NOT_ORDERED          0x00000010L
    #define SQL_OJ_INNER                0x00000020L
    #define SQL_OJ_ALL_COMPARISON_OPS   0x00000040L
#endif

/* SQL_SCROLL_CONCURRENCY flags */
#define SQL_SCCO_READ_ONLY  0x00000001L
#define SQL_SCCO_LOCK       0x00000002L
#define SQL_SCCO_OPT_ROWVER 0x00000004L
#define SQL_SCCO_OPT_VALUES 0x00000008L

/* SQL_TXN_CAPABLE values */
#define SQL_TC_NONE         0
#define SQL_TC_DML          1
#define SQL_TC_ALL          2
#define SQL_TC_DDL_COMMIT   3
#define SQL_TC_DDL_IGNORE   4

/* SQL_TXN_ISOLATION_OPTION flags */
#define SQL_TXN_READ_UNCOMMITTED            0x00000001L
#define SQL_TRANSACTION_READ_UNCOMMITTED    SQL_TXN_READ_UNCOMMITTED
#define SQL_TXN_READ_COMMITTED              0x00000002L
#define SQL_TRANSACTION_READ_COMMITTED      SQL_TXN_READ_COMMITTED
#define SQL_TXN_REPEATABLE_READ             0x00000004L
#define SQL_TRANSACTION_REPEATABLE_READ     SQL_TXN_REPEATABLE_READ
#define SQL_TXN_SERIALIZABLE                0x00000008L
#define SQL_TRANSACTION_SERIALIZABLE        SQL_TXN_SERIALIZABLE

/* SQL_NULL_COLLATION values */
#define SQL_NC_HIGH 0
#define SQL_NC_LOW  1

/* Functions in ODBC32.DLL */
SQLRETURN SQL_API   SQLAllocConnect( SQLHENV, SQLHDBC * );
SQLRETURN SQL_API   SQLAllocEnv( SQLHENV * );
SQLRETURN SQL_API   SQLAllocStmt( SQLHDBC, SQLHSTMT * );
SQLRETURN SQL_API   SQLBindCol( SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN * );
SQLRETURN SQL_API   SQLCancel( SQLHSTMT );
SQLRETURN SQL_API   SQLColumns( SQLHSTMT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT );
SQLRETURN SQL_API   SQLConnect( SQLHDBC, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT );
SQLRETURN SQL_API   SQLDataSources( SQLHENV, SQLUSMALLINT, SQLCHAR *, SQLSMALLINT, SQLSMALLINT *, SQLCHAR *, SQLSMALLINT, SQLSMALLINT * );
SQLRETURN SQL_API   SQLDescribeCol( SQLHSTMT, SQLUSMALLINT, SQLCHAR *, SQLSMALLINT, SQLSMALLINT *, SQLSMALLINT *, SQLULEN *, SQLSMALLINT *, SQLSMALLINT * );
SQLRETURN SQL_API   SQLDisconnect( SQLHDBC );
SQLRETURN SQL_API   SQLError( SQLHENV, SQLHDBC, SQLHSTMT, SQLCHAR *, SQLINTEGER *, SQLCHAR *, SQLSMALLINT, SQLSMALLINT * );
SQLRETURN SQL_API   SQLExecDirect( SQLHSTMT, SQLCHAR *, SQLINTEGER );
SQLRETURN SQL_API   SQLExecute( SQLHSTMT );
SQLRETURN SQL_API   SQLFetch( SQLHSTMT );
SQLRETURN SQL_API   SQLFreeConnect( SQLHDBC );
SQLRETURN SQL_API   SQLFreeEnv( SQLHENV );
SQLRETURN SQL_API   SQLFreeStmt( SQLHSTMT, SQLUSMALLINT );
SQLRETURN SQL_API   SQLGetConnectOption( SQLHDBC, SQLUSMALLINT, SQLPOINTER );
SQLRETURN SQL_API   SQLGetCursorName( SQLHSTMT, SQLCHAR *, SQLSMALLINT, SQLSMALLINT * );
SQLRETURN SQL_API   SQLGetData( SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN, SQLLEN * );
SQLRETURN SQL_API   SQLGetFunctions( SQLHDBC, SQLUSMALLINT, SQLUSMALLINT * );
SQLRETURN SQL_API   SQLGetInfo( SQLHDBC, SQLUSMALLINT, SQLPOINTER, SQLSMALLINT, SQLSMALLINT * );
SQLRETURN SQL_API   SQLGetStmtOption( SQLHSTMT, SQLUSMALLINT, SQLPOINTER );
SQLRETURN SQL_API   SQLGetTypeInfo( SQLHSTMT, SQLSMALLINT );
SQLRETURN SQL_API   SQLNumResultCols( SQLHSTMT, SQLSMALLINT * );
SQLRETURN SQL_API   SQLParamData( SQLHSTMT, SQLPOINTER * );
SQLRETURN SQL_API   SQLPrepare( SQLHSTMT, SQLCHAR *, SQLINTEGER );
SQLRETURN SQL_API   SQLPutData( SQLHSTMT, SQLPOINTER, SQLLEN );
SQLRETURN SQL_API   SQLRowCount( SQLHSTMT, SQLLEN * );
SQLRETURN SQL_API   SQLSetConnectOption( SQLHDBC, SQLUSMALLINT, SQLULEN );
SQLRETURN SQL_API   SQLSetCursorName( SQLHSTMT, SQLCHAR *, SQLSMALLINT );
SQLRETURN SQL_API   SQLSetParam( SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLULEN, SQLSMALLINT, SQLPOINTER, SQLLEN * );
SQLRETURN SQL_API   SQLSetStmtOption( SQLHSTMT, SQLUSMALLINT, SQLULEN );
SQLRETURN SQL_API   SQLSpecialColumns( SQLHSTMT, SQLUSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLUSMALLINT, SQLUSMALLINT );
SQLRETURN SQL_API   SQLStatistics( SQLHSTMT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLUSMALLINT, SQLUSMALLINT );
SQLRETURN SQL_API   SQLTables( SQLHSTMT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLCHAR *, SQLSMALLINT );
SQLRETURN SQL_API   SQLTransact( SQLHENV, SQLHDBC, SQLUSMALLINT );
#if (ODBCVER >= 0x0300)
SQLRETURN SQL_API   SQLAllocHandle( SQLSMALLINT, SQLHANDLE, SQLHANDLE * );
SQLRETURN SQL_API   SQLBindParam( SQLHSTMT, SQLUSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLULEN, SQLSMALLINT, SQLPOINTER, SQLLEN * );
SQLRETURN SQL_API   SQLCloseCursor( SQLHSTMT );
SQLRETURN SQL_API   SQLColAttribute( SQLHSTMT, SQLUSMALLINT, SQLUSMALLINT, SQLPOINTER, SQLSMALLINT, SQLSMALLINT *, SQLPOINTER );
SQLRETURN SQL_API   SQLCopyDesc( SQLHDESC, SQLHDESC );
SQLRETURN SQL_API   SQLEndTran( SQLSMALLINT, SQLHANDLE, SQLSMALLINT );
SQLRETURN SQL_API   SQLFetchScroll( SQLHSTMT, SQLSMALLINT, SQLLEN );
SQLRETURN SQL_API   SQLFreeHandle( SQLSMALLINT, SQLHANDLE );
SQLRETURN SQL_API   SQLGetConnectAttr( SQLHDBC, SQLINTEGER, SQLPOINTER, SQLINTEGER, SQLINTEGER * );
SQLRETURN SQL_API   SQLGetDescField( SQLHDESC, SQLSMALLINT, SQLSMALLINT, SQLPOINTER, SQLINTEGER, SQLINTEGER * );
SQLRETURN SQL_API   SQLGetDescRec( SQLHDESC, SQLSMALLINT, SQLCHAR *, SQLSMALLINT, SQLSMALLINT *, SQLSMALLINT *, SQLSMALLINT *, SQLLEN *, SQLSMALLINT *, SQLSMALLINT *, SQLSMALLINT * );
SQLRETURN SQL_API   SQLGetDiagField( SQLSMALLINT, SQLHANDLE, SQLSMALLINT, SQLSMALLINT, SQLPOINTER, SQLSMALLINT, SQLSMALLINT * );
SQLRETURN SQL_API   SQLGetDiagRec( SQLSMALLINT, SQLHANDLE, SQLSMALLINT, SQLCHAR *, SQLINTEGER *, SQLCHAR *, SQLSMALLINT, SQLSMALLINT * );
SQLRETURN SQL_API   SQLGetEnvAttr( SQLHENV, SQLINTEGER, SQLPOINTER, SQLINTEGER, SQLINTEGER * );
SQLRETURN SQL_API   SQLGetStmtAttr( SQLHSTMT, SQLINTEGER, SQLPOINTER, SQLINTEGER, SQLINTEGER * );
SQLRETURN SQL_API   SQLSetConnectAttr( SQLHDBC, SQLINTEGER, SQLPOINTER, SQLINTEGER );
SQLRETURN SQL_API   SQLSetDescField( SQLHDESC, SQLSMALLINT, SQLSMALLINT, SQLPOINTER, SQLINTEGER );
SQLRETURN SQL_API   SQLSetDescRec( SQLHDESC, SQLSMALLINT, SQLSMALLINT, SQLSMALLINT, SQLLEN, SQLSMALLINT, SQLSMALLINT, SQLPOINTER, SQLLEN *, SQLLEN * );
SQLRETURN SQL_API   SQLSetEnvAttr( SQLHENV, SQLINTEGER, SQLPOINTER, SQLINTEGER );
SQLRETURN SQL_API   SQLSetStmtAttr( SQLHSTMT, SQLINTEGER, SQLPOINTER, SQLINTEGER );
#endif
#if (ODBCVER >= 0x0380)
SQLRETURN SQL_API   SQLCancelHandle( SQLSMALLINT, SQLHANDLE );
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __SQL */
