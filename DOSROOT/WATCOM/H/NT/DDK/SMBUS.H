/*
 *  smbus.h     SMBus functions
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

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Macro to specify SMBus functions */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
    #define SMBCLASSAPI DECLSPEC_IMPORT
#endif

/* SMBus maximum data size */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
    #define SMB_MAX_DATA_SIZE   32
#endif

/* SMBus protocols */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
    #define SMB_WRITE_QUICK         0x00
    #define SMB_READ_QUICK          0x01
    #define SMB_SEND_BYTE           0x02
    #define SMB_RECEIVE_BYTE        0x03
    #define SMB_WRITE_BYTE          0x04
    #define SMB_READ_BYTE           0x05
    #define SMB_WRITE_WORD          0x06
    #define SMB_READ_WORD           0x07
    #define SMB_WRITE_BLOCK         0x08
    #define SMB_READ_BLOCK          0x09
    #define SMB_PROCESS_CALL        0x0A
    #define SMB_BLOCK_PROCESS_CALL  0x0B
    #define SMB_MAXIMUM_PROTOCOL    0x0B
#endif

/* SMBus status codes */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
    #define SMB_STATUS_OK                   0x00
    #define SMB_UNKNOWN_FAILURE             0x07
    #define SMB_ADDRESS_NOT_ACKNOWLEDGED    0x10
    #define SMB_DEVICE_ERROR                0x11
    #define SMB_COMMAND_ACCESS_DENIED       0x12
    #define SMB_UNKNOWN_ERROR               0x13
    #define SMB_DEVICE_ACCESS_DENIED        0x17
    #define SMB_TIMEOUT                     0x18
    #define SMB_UNSUPPORTED_PROTOCOL        0x19
    #define SMB_BUS_BUSY                    0x1A
#endif

/* SMBus device I/O control codes */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
    #define SMB_BUS_REQUEST \
        CTL_CODE( FILE_DEVICE_UNKNOWN, 0, METHOD_NEITHER, FILE_ANY_ACCESS )
    #define SMB_REGISTER_ALARM_NOTIFY \
        CTL_CODE( FILE_DEVICE_UNKNOWN, 1, METHOD_NEITHER, FILE_ANY_ACCESS )
    #define SMB_DEREGISTER_ALARM_NOTIFY \
        CTL_CODE( FILE_DEVICE_UNKNOWN, 2, METHOD_NEITHER, FILE_ANY_ACCESS )
#endif

/* SMBus class version numbers */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
    #define SMB_CLASS_MAJOR_VERSION 0x0001
    #define SMB_CLASS_MINOR_VERSION 0x0000
#endif

/* SMBus request */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
typedef struct {
    UCHAR   Status;
    UCHAR   Protocol;
    UCHAR   Address;
    UCHAR   Command;
    UCHAR   BlockLength;
    UCHAR   Data[SMB_MAX_DATA_SIZE];
} SMB_REQUEST;
typedef SMB_REQUEST *PSMB_REQUEST;
#endif

/* SMBus alaram notification callback */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
typedef VOID (NTAPI *SMB_ALARM_NOTIFY)( PVOID, UCHAR, USHORT );
typedef NTSTATUS (NTAPI *SMB_RESET_DEVICE)( struct _SMB_CLASS *, PVOID );
typedef VOID (NTAPI *SMB_START_IO)( struct _SMB_CLASS *, PVOID );
typedef NTSTATUS (NTAPI *SMB_STOP_DEVICE)( struct _SMB_CLASS *, PVOID );
#endif

/* SMBus alarm registration parameters */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
typedef struct {
    UCHAR               MinAddress;
    UCHAR               MaxAddress;
    SMB_ALARM_NOTIFY    NotifyFunction;
    PVOID               NotifyContext;
} SMB_REGISTER_ALARM;
typedef SMB_REGISTER_ALARM  *PSMB_REGISTER_ALARM;
#endif

/* SMBus class */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
typedef struct _SMB_CLASS {
    USHORT              MajorVersion;
    USHORT              MinorVersion;
    PVOID               Miniport;
    PDEVICE_OBJECT      DeviceObject;
    PDEVICE_OBJECT      PDO;
    PDEVICE_OBJECT      LowerDeviceObject;
    PIRP                CurrentIrp;
    PSMB_REQUEST        CurrentSmb;
    SMB_RESET_DEVICE    ResetDevice;
    SMB_START_IO        StartIo;
    SMB_STOP_DEVICE     StopDevice;
} SMB_CLASS;
typedef SMB_CLASS   *PSMB_CLASS;
#endif

/* SMBus miniport initialization callback */
#if (NTDDI_VERSION >= 0x05010000) && (NTDDI_VERSION < 0x06000000)
typedef NTSTATUS (NTAPI *PSMB_INITIALIZE_MINIPORT)( PSMB_CLASS, PVOID, PVOID );
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
