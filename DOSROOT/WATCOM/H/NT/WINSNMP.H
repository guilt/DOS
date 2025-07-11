/*
 *  winsnmp.h   Win32 SNMP functions
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

#ifndef _INC_WINSNMP
#define _INC_WINSNMP

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* SNMP calling convention */
#define SNMPAPI_CALL    WINAPI

/* SNMP primitive data types */
typedef HANDLE          HSNMP_SESSION;
typedef HANDLE          *LPHSNMP_SESSION;
typedef HANDLE          HSNMP_ENTITY;
typedef HANDLE          *LPHSNMP_ENTITY;
typedef HANDLE          HSNMP_CONTEXT;
typedef HANDLE          *LPHSNMP_CONTEXT;
typedef HANDLE          HSNMP_PDU;
typedef HANDLE          *LPHSNMP_PDU;
typedef HANDLE          HSNMP_VBL;
typedef HANDLE          *LPHSNMP_VBL;
typedef unsigned char   smiBYTE;
typedef unsigned char   *smiLPBYTE;
typedef signed long     smiINT;
typedef signed long     *smiLPINT;
typedef smiINT          smiINT32;
typedef smiINT          *smiLPINT32;
typedef unsigned long   smiUINT32;
typedef unsigned long   *smiLPUINT32;
typedef smiUINT32       smiCNTR32;
typedef smiUINT32       *smiLPCNTR32;
typedef smiUINT32       smiGAUGE32;
typedef smiUINT32       *smiLPGAUGE32;
typedef smiUINT32       smiTIMETICKS;
typedef smiUINT32       *smiLPTIMETICKS;
typedef smiUINT32       SNMPAPI_STATUS;

/* ASN base types */
#define ASN_UNIVERSAL   0x00
#define ASN_APPLICATION 0x40
#define ASN_CONTEXT     0x80
#define ASN_PRIVATE     0xC0
#define ASN_PRIMITIVE   0x00
#define ASN_CONSTRUCTOR 0x20

/* SNMP object syntax values */
#define SNMP_SYNTAX_SEQUENCE        (ASN_UNIVERSAL | ASN_CONSTRUCTOR | 0x10)
#define SNMP_SYNTAX_INT             (ASN_UNIVERSAL | ASN_PRIMITIVE | 0x02)
#define SNMP_SYNTAX_BITS            (ASN_UNIVERSAL | ASN_PRIMITIVE | 0x03)
#define SNMP_SYNTAX_OCTETS          (ASN_UNIVERSAL | ASN_PRIMITIVE | 0x04)
#define SNMP_SYNTAX_NULL            (ASN_UNIVERSAL | ASN_PRIMITIVE | 0x05)
#define SNMP_SYNTAX_OID             (ASN_UNIVERSAL | ASN_PRIMITIVE | 0x06)
#define SNMP_SYNTAX_INT32           SNMP_SYNTAX_INT
#define SNMP_SYNTAX_IPADDR          (ASN_APPLICATION | ASN_PRIMITIVE | 0x00)
#define SNMP_SYNTAX_CNTR32          (ASN_APPLICATION | ASN_PRIMITIVE | 0x01)
#define SNMP_SYNTAX_GAUGE32         (ASN_APPLICATION | ASN_PRIMITIVE | 0x02)
#define SNMP_SYNTAX_TIMETICKS       (ASN_APPLICATION | ASN_PRIMITIVE | 0x03)
#define SNMP_SYNTAX_OPAQUE          (ASN_APPLICATION | ASN_PRIMITIVE | 0x04)
#define SNMP_SYNTAX_NSAPADDR        (ASN_APPLICATION | ASN_PRIMITIVE | 0x05)
#define SNMP_SYNTAX_CNTR64          (ASN_APPLICATION | ASN_PRIMITIVE | 0x06)
#define SNMP_SYNTAX_UINT32          (ASN_APPLICATION | ASN_PRIMITIVE | 0x07)
#define SNMP_SYNTAX_UNSIGNED32      SNMP_SYNTAX_GAUGE32
#define SNMP_SYNTAX_NOSUCHOBJECT    (ASN_CONTEXT | ASN_PRIMITIVE | 0x00)
#define SNMP_SYNTAX_NOSUCHINSTANCE  (ASN_CONTEXT | ASN_PRIMITIVE | 0x01)
#define SNMP_SYNTAX_ENDOFMIBVIEW    (ASN_CONTEXT | ASN_PRIMITIVE | 0x02)

/* Size limits */
#define MAXOBJIDSIZE        128
#define MAXOBJIDSTRSIZE     1408
#define MAXVENDORINFO       32

/* SNMP PDU types */
#define SNMP_PDU_GET        (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x00)
#define SNMP_PDU_GETNEXT    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x01)
#define SNMP_PDU_RESPONSE   (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x02)
#define SNMP_PDU_SET        (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x03)
#define SNMP_PDU_V1TRAP     (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x04)
#define SNMP_PDU_GETBULK    (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x05)
#define SNMP_PDU_INFORM     (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x06)
#define SNMP_PDU_TRAP       (ASN_CONTEXT | ASN_CONSTRUCTOR | 0x07)

/* SnmpListenEx() flags */
#define SNMPLISTEN_USEENTITY_ADDR   0
#define SNMPLISTEN_ALL_ADDR         1

/* SNMP trap values */
#define SNMP_TRAP_COLDSTART             0
#define SNMP_TRAP_WARMSTART             1
#define SNMP_TRAP_LINKDOWN              2
#define SNMP_TRAP_LINKUP                3
#define SNMP_TRAP_AUTHFAIL              4
#define SNMP_TRAP_EGPNEIGHBORLOSS       5
#define SNMP_TRAP_ENTERPRISESPECIFIC    6

/* SNMP error codes */
#define SNMP_ERROR_NOERROR              0
#define SNMP_ERROR_TOOBIG               1
#define SNMP_ERROR_NOSUCHNAME           2
#define SNMP_ERROR_BADVALUE             3
#define SNMP_ERROR_READONLY             4
#define SNMP_ERROR_GENERR               5
#define SNMP_ERROR_NOACCESS             6
#define SNMP_ERROR_WRONGTYPE            7
#define SNMP_ERROR_WRONGLENGTH          8
#define SNMP_ERROR_WRONGENCODING        9
#define SNMP_ERROR_WRONGVALUE           10
#define SNMP_ERROR_NOCREATION           11
#define SNMP_ERROR_INCONSISTENTVALUE    12
#define SNMP_ERROR_RESOURCEUNAVAILABLE  13
#define SNMP_ERROR_COMMITFAILED         14
#define SNMP_ERROR_UNDOFAILED           15
#define SNMP_ERROR_AUTHORIZATIONERROR   16
#define SNMP_ERROR_NOTWRITABLE          17
#define SNMP_ERROR_INCONSISTENTNAME     18

/* SNMP API values */
#define SNMPAPI_TRANSLATED      0
#define SNMPAPI_UNTRANSLATED_V1 1
#define SNMPAPI_UNTRANSLATED_V2 2
#define SNMPAPI_NO_SUPPORT      0
#define SNMPAPI_V1_SUPPORT      1
#define SNMPAPI_V2_SUPPORT      2
#define SNMPAPI_M2M_SUPPORT     3
#define SNMPAPI_OFF             0
#define SNMPAPI_ON              1

/* SNMP API status values */
#define SNMPAPI_FAILURE             0L
#define SNMPAPI_SUCCESS             1L
#define SNMPAPI_ALLOC_ERROR         2L
#define SNMPAPI_CONTEXT_INVALID     3L
#define SNMPAPI_CONTEXT_UNKNOWN     4L
#define SNMPAPI_ENTITY_INVALID      5L
#define SNMPAPI_ENTITY_UNKNOWN      6L
#define SNMPAPI_INDEX_INVALID       7L
#define SNMPAPI_NOOP                8L
#define SNMPAPI_OID_INVALID         9L
#define SNMPAPI_OPERATION_INVALID   10L
#define SNMPAPI_OUTPUT_TRUNCATED    11L
#define SNMPAPI_PDU_INVALID         12L
#define SNMPAPI_SESSION_INVALID     13L
#define SNMPAPI_SYNTAX_INVALID      14L
#define SNMPAPI_VBL_INVALID         15L
#define SNMPAPI_MODE_INVALID        16L
#define SNMPAPI_SIZE_INVALID        17L
#define SNMPAPI_NOT_INITIALIZED     18L
#define SNMPAPI_MESSAGE_INVALID     19L
#define SNMPAPI_HWND_INVALID        20L
#define SNMPAPI_OTHER_ERROR         99L
#define SNMPAPI_TL_NOT_INITIALIZED  100L
#define SNMPAPI_TL_NOT_SUPPORTED    101L
#define SNMPAPI_TL_NOT_AVAILABLE    102L
#define SNMPAPI_TL_RESOURCE_ERROR   103L
#define SNMPAPI_TL_UNDELIVERABLE    104L
#define SNMPAPI_TL_SRC_INVALID      105L
#define SNMPAPI_TL_INVALID_PARAM    106L
#define SNMPAPI_TL_IN_USE           107L
#define SNMPAPI_TL_TIMEOUT          108L
#define SNMPAPI_TL_PDU_TOO_BIG      109L
#define SNMPAPI_TL_OTHER            199L

/* Octets */
typedef struct {
    smiUINT32   len;
    smiLPBYTE   ptr;
} smiOCTETS;
typedef smiOCTETS       *smiLPOCTETS;
typedef const smiOCTETS *smiLPCOCTETS;
typedef smiOCTETS       smiBITS;
typedef smiOCTETS       *smiLPBITS;
typedef smiOCTETS       smiIPADDR;
typedef smiOCTETS       *smiLPIPADDR;
typedef smiOCTETS       smiOPAQUE;
typedef smiOCTETS       *smiLPOPAQUE;
typedef smiOCTETS       smiNSAPADDR;
typedef smiOCTETS       *smiLPNSAPADDR;

/* Object identifier */
typedef struct {
    smiUINT32   len;
    smiLPUINT32 ptr;
} smiOID;
typedef smiOID          *smiLPOID;
typedef const smiOID    *smiLPCOID;

/* Counter (64-bit version) */
typedef struct {
    smiUINT32   hipart;
    smiUINT32   lopart;
} smiCNTR64;
typedef smiCNTR64   *smiLPCNTR64;

/* Value */
typedef struct {
    smiUINT32   syntax;
    union {
        smiINT      sNumber;
        smiUINT32   uNumber;
        smiCNTR64   hNumber;
        smiOCTETS   string;
        smiOID      oid;
        smiBYTE     empty;
    } value;
} smiVALUE;
typedef smiVALUE        *smiLPVALUE;
typedef const smiVALUE  *smiLPCVALUE;

/* Vendor information */
typedef struct {
    char        vendorName[MAXVENDORINFO * 2];
    char        vendorContact[MAXVENDORINFO * 2];
    char        vendorVersionId[MAXVENDORINFO];
    char        vendorVersionDate[MAXVENDORINFO];
    smiUINT32   vendorEnterprise;
} smiVENDORINFO;
typedef smiVENDORINFO   *smiLPVENDORINFO;

/* SNMP API callback */
typedef SNMPAPI_STATUS (CALLBACK *SNMPAPI_CALLBACK)( HSNMP_SESSION, HWND, UINT, WPARAM, LPARAM, LPVOID );

/* Function pointer prototypes for some SNMP functions */
typedef SNMPAPI_STATUS (SNMPAPI_CALL *PFNSNMPSTARTUPEX)( smiLPUINT32, smiLPUINT32, smiLPUINT32, smiLPUINT32, smiLPUINT32 );
typedef SNMPAPI_STATUS (SNMPAPI_CALL *PFNSNMPCLEANUPEX)( void );

/* Functions in WSNMP32.DLL */
SNMPAPI_STATUS SNMPAPI_CALL SnmpCancelMsg( HSNMP_SESSION, smiINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpCleanup( void );
SNMPAPI_STATUS SNMPAPI_CALL SnmpCleanupEx( void );
SNMPAPI_STATUS SNMPAPI_CALL SnmpClose( HSNMP_SESSION );
SNMPAPI_STATUS SNMPAPI_CALL SnmpContextToStr( HSNMP_CONTEXT, smiLPOCTETS );
SNMPAPI_STATUS SNMPAPI_CALL SnmpCountVbl( HSNMP_VBL );
HSNMP_PDU SNMPAPI_CALL      SnmpCreatePdu( HSNMP_SESSION, smiINT, smiINT32, smiINT, smiINT, HSNMP_VBL );
HSNMP_SESSION SNMPAPI_CALL  SnmpCreateSession( HWND, UINT, SNMPAPI_CALLBACK, LPVOID );
HSNMP_VBL SNMPAPI_CALL      SnmpCreateVbl( HSNMP_SESSION, smiLPCOID, smiLPCVALUE );
SNMPAPI_STATUS SNMPAPI_CALL SnmpDecodeMsg( HSNMP_SESSION, LPHSNMP_ENTITY, LPHSNMP_ENTITY, LPHSNMP_CONTEXT, LPHSNMP_PDU, smiLPCOCTETS );
SNMPAPI_STATUS SNMPAPI_CALL SnmpDeleteVb( HSNMP_VBL, smiUINT32 );
HSNMP_PDU SNMPAPI_CALL      SnmpDuplicatePdu( HSNMP_SESSION, HSNMP_PDU );
HSNMP_VBL SNMPAPI_CALL      SnmpDuplicateVbl( HSNMP_SESSION, HSNMP_PDU );
SNMPAPI_STATUS SNMPAPI_CALL SnmpEncodeMsg( HSNMP_SESSION, HSNMP_ENTITY, HSNMP_ENTITY, HSNMP_CONTEXT, HSNMP_PDU, smiLPOCTETS );
SNMPAPI_STATUS SNMPAPI_CALL SnmpEntityToStr( HSNMP_ENTITY, smiUINT32, LPSTR );
SNMPAPI_STATUS SNMPAPI_CALL SnmpFreeContext( HSNMP_CONTEXT );
SNMPAPI_STATUS SNMPAPI_CALL SnmpFreeDescriptor( smiUINT32, smiLPOPAQUE );
SNMPAPI_STATUS SNMPAPI_CALL SnmpFreeEntity( HSNMP_ENTITY );
SNMPAPI_STATUS SNMPAPI_CALL SnmpFreePdu( HSNMP_PDU );
SNMPAPI_STATUS SNMPAPI_CALL SnmpFreeVbl( HSNMP_VBL );
SNMPAPI_STATUS SNMPAPI_CALL SnmpGetLastError( HSNMP_SESSION );
SNMPAPI_STATUS SNMPAPI_CALL SnmpGetPduData( HSNMP_PDU, smiLPINT, smiLPINT32, smiLPINT, smiLPINT, LPHSNMP_VBL );
SNMPAPI_STATUS SNMPAPI_CALL SnmpGetRetransmitMode( smiLPUINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpGetRetry( HSNMP_ENTITY, smiLPUINT32, smiLPUINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpGetTimeout( HSNMP_ENTITY, smiLPTIMETICKS, smiLPTIMETICKS );
SNMPAPI_STATUS SNMPAPI_CALL SnmpGetTranslateMode( smiLPUINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpGetVb( HSNMP_VBL, smiUINT32, smiLPOID, smiLPVALUE );
SNMPAPI_STATUS SNMPAPI_CALL SnmpGetVendorInfo( smiLPVENDORINFO );
SNMPAPI_STATUS SNMPAPI_CALL SnmpListen( HSNMP_ENTITY, SNMPAPI_STATUS );
SNMPAPI_STATUS SNMPAPI_CALL SnmpListenEx( HSNMP_ENTITY, SNMPAPI_STATUS, smiUINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpOidCompare( smiLPCOID, smiLPCOID, smiUINT32, smiLPINT );
SNMPAPI_STATUS SNMPAPI_CALL SnmpOidCopy( smiLPCOID, smiLPOID );
SNMPAPI_STATUS SNMPAPI_CALL SnmpOidToStr( smiLPCOID, smiUINT32, LPSTR );
HSNMP_SESSION SNMPAPI_CALL  SnmpOpen( HWND, UINT );
SNMPAPI_STATUS SNMPAPI_CALL SnmpRecvMsg( HSNMP_SESSION, LPHSNMP_ENTITY, LPHSNMP_ENTITY, LPHSNMP_CONTEXT, LPHSNMP_PDU );
SNMPAPI_STATUS SNMPAPI_CALL SnmpRegister( HSNMP_SESSION, HSNMP_ENTITY, HSNMP_ENTITY, HSNMP_CONTEXT, smiLPCOID, smiUINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpSendMsg( HSNMP_SESSION, HSNMP_ENTITY, HSNMP_ENTITY, HSNMP_CONTEXT, HSNMP_PDU );
SNMPAPI_STATUS SNMPAPI_CALL SnmpSetPduData( HSNMP_PDU, const smiINT *, const smiINT32 *, const smiINT *, const smiINT *, const HSNMP_VBL * );
SNMPAPI_STATUS SNMPAPI_CALL SnmpSetPort( HSNMP_ENTITY, UINT );
SNMPAPI_STATUS SNMPAPI_CALL SnmpSetRetransmitMode( smiUINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpSetRetry( HSNMP_ENTITY, smiUINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpSetTimeout( HSNMP_ENTITY, smiTIMETICKS );
SNMPAPI_STATUS SNMPAPI_CALL SnmpSetTranslateMode( smiUINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpSetVb( HSNMP_VBL, smiUINT32, smiLPCOID, smiLPCVALUE );
SNMPAPI_STATUS SNMPAPI_CALL SnmpStartup( smiLPUINT32, smiLPUINT32, smiLPUINT32, smiLPUINT32, smiLPUINT32 );
SNMPAPI_STATUS SNMPAPI_CALL SnmpStartupEx( smiLPUINT32, smiLPUINT32, smiLPUINT32, smiLPUINT32, smiLPUINT32 );
HSNMP_CONTEXT SNMPAPI_CALL  SnmpStrToContext( HSNMP_SESSION, smiLPCOCTETS );
HSNMP_ENTITY SNMPAPI_CALL   SnmpStrToEntity( HSNMP_SESSION, LPCSTR );
SNMPAPI_STATUS SNMPAPI_CALL SnmpStrToOid( LPCSTR, smiLPOID );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _INC_WINSNMP */
