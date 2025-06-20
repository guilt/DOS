/*
 *  ntddchgr.h  Changer device I/O control codes
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

#ifndef _NTDDCHGR_H_
#define _NTDDCHGR_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <ntddstor.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Changer device name */
#define DD_CHANGER_DEVICE_NAME  "\\Device\\Changer"

/* Changer device I/O control codes */
#define IOCTL_CHANGER_BASE  FILE_DEVICE_CHANGER
#define IOCTL_CHANGER_GET_PARAMETERS \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x0000, METHOD_BUFFERED, FILE_READ_ACCESS )
#define IOCTL_CHANGER_GET_STATUS \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x0001, METHOD_BUFFERED, FILE_READ_ACCESS )
#define IOCTL_CHANGER_GET_PRODUCT_DATA \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x0002, METHOD_BUFFERED, FILE_READ_ACCESS )
#define IOCTL_CHANGER_SET_ACCESS \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x0004, METHOD_BUFFERED, FILE_READ_ACCESS | \
    FILE_WRITE_ACCESS )
#define IOCTL_CHANGER_GET_ELEMENT_STATUS \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x0005, METHOD_BUFFERED, FILE_READ_ACCESS | \
    FILE_WRITE_ACCESS )
#define IOCTL_CHANGER_INITIALIZE_ELEMENT_STATUS \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x0006, METHOD_BUFFERED, FILE_READ_ACCESS )
#define IOCTL_CHANGER_SET_POSITION \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x0007, METHOD_BUFFERED, FILE_READ_ACCESS )
#define IOCTL_CHANGER_EXCHANGE_MEDIUM \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x0008, METHOD_BUFFERED, FILE_READ_ACCESS )
#define IOCTL_CHANGER_MOVE_MEDIUM \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x0009, METHOD_BUFFERED, FILE_READ_ACCESS )
#define IOCTL_CHANGER_REINITIALIZE_TRANSPORT \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x000A, METHOD_BUFFERED, FILE_READ_ACCESS )
#define IOCTL_CHANGER_QUERY_VOLUME_TAGS \
    CTL_CODE( IOCTL_CHANGER_BASE, 0x000B, METHOD_BUFFERED, FILE_READ_ACCESS | \
    FILE_WRITE_ACCESS )

/* Maximum sizes and lengths */
#define MAX_VOLUME_ID_SIZE          36
#define MAX_VOLUME_TEMPLATE_SIZE    40
#define VENDOR_ID_LENGTH            8
#define PRODUCT_ID_LENGTH           16
#define REVISION_LENGTH             4
#define SERIAL_NUMBER_LENGTH        32

/* Changer features */
#define CHANGER_BAR_CODE_SCANNER_INSTALLED  0x00000001L
#define CHANGER_INIT_ELEM_STAT_WITH_RANGE   0x00000002L
#define CHANGER_CLOSE_IEPORT                0x00000004L
#define CHANGER_OPEN_IEPORT                 0x00000008L
#define CHANGER_STATUS_NON_VOLATILE         0x00000010L
#define CHANGER_EXCHANGE_MEDIA              0x00000020L
#define CHANGER_CLEANER_SLOT                0x00000040L
#define CHANGER_LOCK_UNLOCK                 0x00000080L
#define CHANGER_CARTRIDGE_MAGAZINE          0x00000100L
#define CHANGER_MEDIUM_FLIP                 0x00000200L
#define CHANGER_POSITION_TO_ELEMENT         0x00000400L
#define CHANGER_REPORT_IEPORT_STATE         0x00000800L
#define CHANGER_STORAGE_DRIVE               0x00001000L
#define CHANGER_STORAGE_IEPORT              0x00002000L
#define CHANGER_STORAGE_SLOT                0x00004000L
#define CHANGER_STORAGE_TRANSPORT           0x00008000L
#define CHANGER_DRIVE_CLEANING_REQUIRED     0x00010000L
#define CHANGER_PREDISMOUNT_EJECT_REQUIRED  0x00020000L
#define CHANGER_CLEANER_ACCESS_NOT_VALID    0x00040000L
#define CHANGER_PREMOUNT_EJECT_REQUIRED     0x00080000L
#define CHANGER_VOLUME_IDENTIFICATION       0x00100000L
#define CHANGER_VOLUME_SEARCH               0x00200000L
#define CHANGER_VOLUME_ASSERT               0x00400000L
#define CHANGER_VOLUME_REPLACE              0x00800000L
#define CHANGER_VOLUME_UNDEFINE             0x01000000L
#define CHANGER_SERIAL_NUMBER_VALID         0x04000000L
#define CHANGER_DEVICE_REINITIALIZE_CAPABLE 0x08000000L
#define CHANGER_KEYPAD_ENABLE_DISABLE       0x10000000L
#define CHANGER_DRIVE_EMPTY_ON_DOOR_ACCESS  0x20000000L
#define CHANGER_RESERVED_BIT                0x80000000L
#define CHANGER_PREDISMOUNT_ALIGN_TO_SLOT   0x80000001L
#define CHANGER_PREDISMOUNT_ALIGN_TO_DRIVE  0x80000002L
#define CHANGER_CLEANER_AUTODISMOUNT        0x80000004L
#define CHANGER_TRUE_EXCHANGE_CAPABLE       0x80000008L
#define CHANGER_SLOTS_USE_TRAYS             0x80000010L
#define CHANGER_RTN_MEDIA_TO_ORIGINAL_ADDR  0x80000020L
#define CHANGER_CLEANER_OPS_NOT_SUPPORTED   0x80000040L
#define CHANGER_IEPORT_USER_CONTROL_OPEN    0x80000080L
#define CHANGER_IEPORT_USER_CONTROL_CLOSE   0x80000100L
#define CHANGER_MOVE_EXTENDS_IEPORT         0x80000200L
#define CHANGER_MOVE_RETRACTS_IEPORT        0x80000400L

/* Changer position capabilities */
#define CHANGER_TO_TRANSPORT    0x01
#define CHANGER_TO_SLOT         0x02
#define CHANGER_TO_IEPORT       0x04
#define CHANGER_TO_DRIVE        0x08

/* Changer lock/unlock capabilities */
#define LOCK_UNLOCK_IEPORT  0x01
#define LOCK_UNLOCK_DOOR    0x02
#define LOCK_UNLOCK_KEYPAD  0x04

/* IOCTL_CHANGER_SET_ACCESS operations */
#define LOCK_ELEMENT    0L
#define UNLOCK_ELEMENT  1L
#define EXTEND_IEPORT   2L
#define RETRACT_IEPORT  3L

/* Changer element status flags */
#define ELEMENT_STATUS_FULL         0x00000001L
#define ELEMENT_STATUS_IMPEXP       0x00000002L
#define ELEMENT_STATUS_EXCEPT       0x00000004L
#define ELEMENT_STATUS_ACCESS       0x00000008L
#define ELEMENT_STATUS_EXENAB       0x00000010L
#define ELEMENT_STATUS_INENAB       0x00000020L
#define ELEMENT_STATUS_PRODUCT_DATA 0x00000040L
#define ELEMENT_STATUS_LUN_VALID    0x00001000L
#define ELEMENT_STATUS_ID_VALID     0x00002000L
#define ELEMENT_STATUS_NOT_BUS      0x00008000L
#define ELEMENT_STATUS_INVERT       0x00400000L
#define ELEMENT_STATUS_SVALID       0x00800000L
#define ELEMENT_STATUS_PVOLTAG      0x10000000L
#define ELEMENT_STATUS_AVOLTAG      0x20000000L

/* Changer element status exception codes */
#define ERROR_LABEL_UNREADABLE      0x00000001L
#define ERROR_LABEL_QUESTIONABLE    0x00000002L
#define ERROR_SLOT_NOT_PRESENT      0x00000004L
#define ERROR_DRIVE_NOT_INSTALLED   0x00000008L
#define ERROR_TRAY_MALFUNCTION      0x00000010L
#define ERROR_INIT_STATUS_NEEDED    0x00000011L
#define ERROR_UNHANDLED_ERROR       0xFFFFFFFFL

/* IOCTL_CHANGER_QUERY_VOLUME_TAGS action codes */
#define SEARCH_ALL          0x00000000L
#define SEARCH_PRIMARY      0x00000001L
#define SEARCH_ALTERNATE    0x00000002L
#define SEARCH_ALL_NO_SEQ   0x00000004L
#define SEARCH_PRI_NO_SEQ   0x00000005L
#define SEARCH_ALT_NO_SEQ   0x00000006L
#define ASSERT_PRIMARY      0x00000008L
#define ASSERT_ALTERNATE    0x00000009L
#define REPLACE_PRIMARY     0x0000000AL
#define REPLACE_ALTERNATE   0x0000000BL
#define UNDEFINE_PRIMARY    0x0000000CL
#define UNDEFINE_ALTERNATE  0x0000000DL

/* Element types */
typedef enum _ELEMENT_TYPE {
    AllElements         = 0,
    ChangerTransport    = 1,
    ChangerSlot         = 2,
    ChangerIEPort       = 3,
    ChangerDrive        = 4,
    ChangerDoor         = 5,
    ChangerKeypad       = 6,
    ChangerMaxElement   = 7
} ELEMENT_TYPE;
typedef ELEMENT_TYPE    *PELEMENT_TYPE;

/* Changer element */
typedef struct _CHANGER_ELEMENT {
    ELEMENT_TYPE    ElementType;
    ULONG           ElementAddress;
} CHANGER_ELEMENT;
typedef CHANGER_ELEMENT *PCHANGER_ELEMENT;

/* Changer element list */
typedef struct _CHANGER_ELEMENT_LIST {
    CHANGER_ELEMENT Element;
    ULONG           NumberOfElements;
} CHANGER_ELEMENT_LIST;
typedef CHANGER_ELEMENT_LIST    *PCHANGER_ELEMENT_LIST;

/* IOCTL_CHANGER_GET_PARAMETERS returned data */
typedef struct _GET_CHANGER_PARAMETERS {
    ULONG   Size;
    USHORT  NumberTransportElements;
    USHORT  NumberStorageElements;
    USHORT  NumberCleanerSlots;
    USHORT  NumberIEElements;
    USHORT  NumberDataTransferElements;
    USHORT  NumberOfDoors;
    USHORT  FirstSlotNumber;
    USHORT  FirstDriveNumber;
    USHORT  FirstTransportNumber;
    USHORT  FirstIEPortNumber;
    USHORT  FirstCleanerSlotAddress;
    USHORT  MagazineSize;
    ULONG   DriveCleanTimeout;
    ULONG   Features0;
    ULONG   Features1;
    UCHAR   MoveFromTransport;
    UCHAR   MoveFromSlot;
    UCHAR   MoveFromIePort;
    UCHAR   MoveFromDrive;
    UCHAR   ExchangeFromTransport;
    UCHAR   ExchangeFromSlot;
    UCHAR   ExchangeFromIePort;
    UCHAR   ExchangeFromDrive;
    UCHAR   LockUnlockCapabilities;
    UCHAR   PositionCapabilities;
    UCHAR   Reserved1[2];
    ULONG   Reserved2[2];
} GET_CHANGER_PARAMETERS;
typedef GET_CHANGER_PARAMETERS  *PGET_CHANGER_PARAMETERS;

/* Changer product data */
typedef struct _CHANGER_PRODUCT_DATA {
    UCHAR   VendorId[VENDOR_ID_LENGTH];
    UCHAR   ProductId[PRODUCT_ID_LENGTH];
    UCHAR   Revision[REVISION_LENGTH];
    UCHAR   SerialNumber[SERIAL_NUMBER_LENGTH];
    UCHAR   DeviceType;
} CHANGER_PRODUCT_DATA;
typedef CHANGER_PRODUCT_DATA    *PCHANGER_PRODUCT_DATA;

/* IOCTL_CHANGER_SET_ACCESS parameters */
typedef struct _CHANGER_SET_ACCESS {
    CHANGER_ELEMENT Element;
    ULONG           Control;
} CHANGER_SET_ACCESS;
typedef CHANGER_SET_ACCESS  *PCHANGER_SET_ACCESS;

/* IOCTL_CHANGER_GET_ELEMENT_STATUS parameters */
typedef struct _CHANGER_READ_ELEMENT_STATUS {
    CHANGER_ELEMENT_LIST    ElementList;
    BOOLEAN                 VolumeTagInfo;
} CHANGER_READ_ELEMENT_STATUS;
typedef CHANGER_READ_ELEMENT_STATUS *PCHANGER_READ_ELEMENT_STATUS;

/* Changer element status */
typedef struct _CHANGER_ELEMENT_STATUS {
    CHANGER_ELEMENT Element;
    CHANGER_ELEMENT SrcElementAddress;
    ULONG           Flags;
    ULONG           ExceptionCode;
    UCHAR           TargetId;
    UCHAR           Lun;
    USHORT          Reserved;
    UCHAR           PrimaryVolumeID[MAX_VOLUME_ID_SIZE];
    UCHAR           AlternateVolumeID[MAX_VOLUME_ID_SIZE];
} CHANGER_ELEMENT_STATUS;
typedef CHANGER_ELEMENT_STATUS  *PCHANGER_ELEMENT_STATUS;

/* Changer element status (extended version) */
typedef struct _CHANGER_ELEMENT_STATUS_EX {
    CHANGER_ELEMENT Element;
    CHANGER_ELEMENT SrcElementAddress;
    ULONG           Flags;
    ULONG           ExceptionCode;
    UCHAR           TargetId;
    UCHAR           Lun;
    USHORT          Reserved;
    UCHAR           PrimaryVolumeID[MAX_VOLUME_ID_SIZE];
    UCHAR           AlternateVolumeID[MAX_VOLUME_ID_SIZE];
    UCHAR           VendorIdentification[VENDOR_ID_LENGTH];
    UCHAR           ProductIdentification[PRODUCT_ID_LENGTH];
    UCHAR           SerialNumber[SERIAL_NUMBER_LENGTH];
} CHANGER_ELEMENT_STATUS_EX;
typedef CHANGER_ELEMENT_STATUS_EX   *PCHANGER_ELEMENT_STATUS_EX;

/* IOCTL_CHANGER_INITIALIZE_ELEMENT_STATUS parameters */
typedef struct _CHANGER_INITIALIZE_ELEMENT_STATUS {
    CHANGER_ELEMENT_LIST    ElementList;
    BOOLEAN                 BarCodeScan;
} CHANGER_INITIALIZE_ELEMENT_STATUS;
typedef CHANGER_INITIALIZE_ELEMENT_STATUS   *PCHANGER_INITIALIZE_ELEMENT_STATUS;

/* IOCTL_CHANGER_SET_POSITION parameters */
typedef struct _CHANGER_SET_POSITION {
    CHANGER_ELEMENT Transport;
    CHANGER_ELEMENT Destination;
    BOOLEAN         Flip;
} CHANGER_SET_POSITION;
typedef CHANGER_SET_POSITION    *PCHANGER_SET_POSITION;

/* IOCTL_CHANGER_EXCHANGE_MEDIUM parameters */
typedef struct _CHANGER_EXCHANGE_MEDIUM {
    CHANGER_ELEMENT Transport;
    CHANGER_ELEMENT Source;
    CHANGER_ELEMENT Destination1;
    CHANGER_ELEMENT Destination2;
    BOOLEAN         Flip1;
    BOOLEAN         Flip2;
} CHANGER_EXCHANGE_MEDIUM;
typedef CHANGER_EXCHANGE_MEDIUM *PCHANGER_EXCHANGE_MEDIUM;

/* IOCTL_CHANGER_MOVE_MEDIUM parameters */
typedef struct _CHANGER_MOVE_MEDIUM {
    CHANGER_ELEMENT Transport;
    CHANGER_ELEMENT Source;
    CHANGER_ELEMENT Destination;
    BOOLEAN         Flip;
} CHANGER_MOVE_MEDIUM;
typedef CHANGER_MOVE_MEDIUM *PCHANGER_MOVE_MEDIUM;

/* IOCTL_CHANGER_QUERY_VOLUME_TAGS parameters */
typedef struct _CHANGER_SEND_VOLUME_TAG_INFORMATION {
    CHANGER_ELEMENT StartingElement;
    ULONG           ActionCode;
    UCHAR           VolumeIDTemplate[MAX_VOLUME_TEMPLATE_SIZE];
} CHANGER_SEND_VOLUME_TAG_INFORMATION;
typedef CHANGER_SEND_VOLUME_TAG_INFORMATION *PCHANGER_SEND_VOLUME_TAG_INFORMATION;

/* IOCTL_CHANGER_QUERY_VOLUME_TAG returned data */
typedef struct _READ_ELEMENT_ADDRESS_INFO {
    ULONG                   NumberOfElements;
    CHANGER_ELEMENT_STATUS  ElementStatus[1];
} READ_ELEMENT_ADDRESS_INFO;
typedef READ_ELEMENT_ADDRESS_INFO   *PREAD_ELEMENT_ADDRESS_INFO;

/* Changer device problem types */
typedef enum _CHANGER_DEVICE_PROBLEM_TYPE {
    DeviceProblemNone                   = 0,
    DeviceProblemHardware               = 1,
    DeviceProblemCHMError               = 2,
    DeviceProblemDoorOpen               = 3,
    DeviceProblemCalibrationError       = 4,
    DeviceProblemTargetFailure          = 5,
    DeviceProblemCHMMoveError           = 6,
    DeviceProblemCHMZeroError           = 7,
    DeviceProblemCartridgeInsertError   = 8,
    DeviceProblemPositionError          = 9,
    DeviceProblemSensorError            = 10,
    DeviceProblemCartridgeEjectError    = 11,
    DeviceProblemGripperError           = 12,
    DeviceProblemDriveError             = 13
} CHANGER_DEVICE_PROBLEM_TYPE;
typedef CHANGER_DEVICE_PROBLEM_TYPE *PCHANGER_DEVICE_PROBLEM_TYPE;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _NTDDCHGR_H_ */
