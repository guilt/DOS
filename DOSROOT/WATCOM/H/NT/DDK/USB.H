/*
 *  usb.h       USB driver functions
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

#ifndef __USB_H__
#define __USB_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <usb200.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Kernel data types for use in user mode */
#ifndef _NTDDK_
#ifndef _WDMDDK_
typedef PVOID   PIRP;
typedef PVOID   PMDL;
#endif
#endif

/* Primitive data types */
typedef LONG    USBD_STATUS;
typedef PVOID   USBD_PIPE_HANDLE;
typedef PVOID   USBD_CONFIGURATION_HANDLE;
typedef PVOID   USBD_INTERFACE_HANDLE;

/* USB version */
#define USBDI_VERSION   0x00000600L

/* USB port attributes */
#define USB_PORTATTR_NO_CONNECTOR       0x00000001L
#define USB_PORTATTR_SHARED_USB2        0x00000002L
#define USB_PORTATTR_MINI_CONNECTOR     0x00000004L
#define USB_PORTATTR_OEM_CONNECTOR      0x00000008L
#define USB_PORTATTR_OWNED_BY_CC        0x01000000L
#define USB_PORTATTR_NO_OVERCURRENT_UI  0x02000000L

/* USB default addresses */
#define USB_DEFAULT_DEVICE_ADDRESS      0
#define USB_DEFAULT_ENDPOINT_ADDRESS    0
#define USB_DEFAULT_MAX_PACKET          64

/* URB from IRP macro */
#define URB_FROM_IRP( x ) \
    (IoGetCurrentIrpStackLocation( x )->Parameters.Others.Argument1)

/* URB functions */
#define URB_FUNCTION_SELECT_CONFIGURATION           0x0000
#define URB_FUNCTION_SELECT_INTERFACE               0x0001
#define URB_FUNCTION_ABORT_PIPE                     0x0002
#define URB_FUNCTION_TAKE_FRAME_LENGTH_CONTROL      0x0003
#define URB_FUNCTION_RELEASE_FRAME_LENGTH_CONTROL   0x0004
#define URB_FUNCTION_GET_FRAME_LENGTH               0x0005
#define URB_FUNCTION_SET_FRAME_LENGTH               0x0006
#define URB_FUNCTION_GET_CURRENT_FRAME_NUMBER       0x0007
#define URB_FUNCTION_CONTROL_TRANSFER               0x0008
#define URB_FUNCTION_BULK_OR_INTERRUPT_TRANSFER     0x0009
#define URB_FUNCTION_ISOCH_TRANSFER                 0x000A
#define URB_FUNCTION_GET_DESCRIPTOR_FROM_DEVICE     0x000B
#define URB_FUNCTION_SET_DESCRIPTOR_TO_DEVICE       0x000C
#define URB_FUNCTION_SET_FEATURE_TO_DEVICE          0x000D
#define URB_FUNCTION_SET_FEATURE_TO_INTERFACE       0x000E
#define URB_FUNCTION_SET_FEATURE_TO_ENDPOINT        0x000F
#define URB_FUNCTION_CLEAR_FEATURE_TO_DEVICE        0x0010
#define URB_FUNCTION_CLEAR_FEATURE_TO_INTERFACE     0x0011
#define URB_FUNCTION_CLEAR_FEATURE_TO_ENDPOINT      0x0012
#define URB_FUNCTION_GET_STATUS_FROM_DEVICE         0x0013
#define URB_FUNCTION_GET_STATUS_FROM_INTERFACE      0x0014
#define URB_FUNCTION_GET_STATUS_FROM_ENDPOINT       0x0015
#define URB_FUNCTION_VENDOR_DEVICE                  0x0017
#define URB_FUNCTION_VENDOR_INTERFACE               0x0018
#define URB_FUNCTION_VENDOR_ENDPOINT                0x0019
#define URB_FUNCTION_CLASS_DEVICE                   0x001A
#define URB_FUNCTION_CLASS_INTERFACE                0x001B
#define URB_FUNCTION_CLASS_ENDPOINT                 0x001C
#define URB_FUNCTION_SYNC_RESET_PIPE_AND_CLEAR_STALL    0x001E
#define URB_FUNCTION_CLASS_OTHER                    0x001F
#define URB_FUNCTION_VENDOR_OTHER                   0x0020
#define URB_FUNCTION_GET_STATUS_FROM_OTHER          0x0021
#define URB_FUNCTION_CLEAR_FEATURE_TO_OTHER         0x0022
#define URB_FUNCTION_SET_FEATURE_TO_OTHER           0x0023
#define URB_FUNCTION_GET_DESCRIPTOR_FROM_ENDPOINT   0x0024
#define URB_FUNCTION_SET_DESCRIPTOR_TO_ENDPOINT     0x0025
#define URB_FUNCTION_GET_CONFIGURATION              0x0026
#define URB_FUNCTION_GET_INTERFACE                  0x0027
#define URB_FUNCTION_GET_DESCRIPTOR_FROM_INTERFACE  0x0028
#define URB_FUNCTION_SET_DESCRIPTOR_TO_INTERFACE    0x0029
#if (_WIN32_WINNT >= 0x0501)
    #define URB_FUNCTION_GET_MS_FEATURE_DESCRIPTOR  0x002A
    #define URB_FUNCTION_SYNC_RESET_PIPE            0x0030
    #define URB_FUNCTION_SYNC_CLEAR_STALL           0x0031
#endif
#if (_WIN32_WINNT >= 0x0600)
    #define URB_FUNCTION_CONTROL_TRANSFER_EX        0x0032
#endif
#define URB_FUNCTION_RESET_PIPE \
    URB_FUNCTION_SYNC_RESET_PIPE_AND_CLEAR_STALL

/* USBD flags */
#define USBD_TRANSFER_DIRECTION         0x00000001L
#define USBD_SHORT_TRANSFER_OK          0x00000002L
#define USBD_START_ISO_TRANSFER_ASAP    0x00000004L
#define USBD_DEFAULT_PIPE_TRANSFER      0x00000008L
#define VALID_TRANSFER_FLAGS_MASK \
    (USBD_SHORT_TRANSFER_OK | USBD_TRANSFER_DIRECTION | USBD_START_ISO_TRANSFER_ASAP | \
    USBD_DEFAULT_PIPE_TRANSFER)

/* Macro to extract the transfer direction */
#define USBD_TRANSFER_DIRECTION_FLAG( x )   ((x) & USBD_TRANSFER_DIRECTION)

/* USBD transfer directions */
#define USBD_TRANSFER_DIRECTION_OUT 0
#define USBD_TRANSFER_DIRECTION_IN  1

/* USBD ISO start frame range */
#define USBD_ISO_START_FRAME_RANGE  1024

/* USBD status code testing macros */
#define USBD_SUCCESS( x )   ((USBD_STATUS)(x) >= 0)
#define USBD_PENDING( x )   (((ULONG)(x) >> 30) == 1)
#define USBD_ERROR( x )     ((USBD_STATUS)(x) < 0)

/* USBD status codes */
#define USBD_STATUS_SUCCESS                         0x00000000L
#define USBD_STATUS_PENDING                         0x40000000L
#define USBD_STATUS_CRC                             0xC0000001L
#define USBD_STATUS_BTSTUFF                         0xC0000002L
#define USBD_STATUS_DATA_TOGGLE_MISMATCH            0xC0000003L
#define USBD_STATUS_STALL_PID                       0xC0000004L
#define USBD_STATUS_DEV_NOT_RESPONDING              0xC0000005L
#define USBD_STATUS_PID_CHECK_FAILURE               0xC0000006L
#define USBD_STATUS_UNEXPECTED_PID                  0xC0000007L
#define USBD_STATUS_DATA_OVERRUN                    0xC0000008L
#define USBD_STATUS_DATA_UNDERRUN                   0xC0000009L
#define USBD_STATUS_BUFFER_OVERRUN                  0xC000000CL
#define USBD_STATUS_BUFFER_UNDERRUN                 0xC000000DL
#define USBD_STATUS_NOT_ACCESSED                    0xC000000FL
#define USBD_STATUS_FIFO                            0xC0000010L
#define USBD_STATUS_XACT_ERROR                      0xC0000011L
#define USBD_STATUS_BABBLE_DETECTED                 0xC0000012L
#define USBD_STATUS_DATA_BUFFER_ERROR               0xC0000013L
#define USBD_STATUS_ENDPOINT_HALTED                 0xC0000030L
#define USBD_STATUS_INVALID_URB_FUNCTION            0x80000200L
#define USBD_STATUS_INVALID_PARAMETER               0x80000300L
#define USBD_STATUS_ERROR_BUSY                      0x80000400L
#define USBD_STATUS_INVALID_PIPE_HANDLE             0x80000600L
#define USBD_STATUS_NO_BANDWIDTH                    0x80000700L
#define USBD_STATUS_INTERNAL_HC_ERROR               0x80000800L
#define USBD_STATUS_ERROR_SHORT_TRANSFER            0x80000900L
#define USBD_STATUS_BAD_START_FRAME                 0xC0000A00L
#define USBD_STATUS_ISOCH_REQUEST_FAILED            0xC0000B00L
#define USBD_STATUS_FRAME_CONTROL_OWNED             0xC0000C00L
#define USBD_STATUS_FRAME_CONTROL_NOT_OWNED         0xC0000D00L
#define USBD_STATUS_NOT_SUPPORTED                   0xC0000E00L
#define USBD_STATUS_INVALID_CONFIGURATION_DESCRIPTOR    0xC0000F00L
#define USBD_STATUS_INSUFFICIENT_RESOURCES          0xC0001000L
#define USBD_STATUS_SET_CONFIG_FAILED               0xC0002000L
#define USBD_STATUS_BUFFER_TOO_SMALL                0xC0003000L
#define USBD_STATUS_INTERFACE_NOT_FOUND             0xC0004000L
#define USBD_STATUS_INAVLID_PIPE_FLAGS              0xC0005000L
#define USBD_STATUS_TIMEOUT                         0xC0006000L
#define USBD_STATUS_DEVICE_GONE                     0xC0007000L
#define USBD_STATUS_STATUS_NOT_MAPPED               0xC0008000L
#define USBD_STATUS_HUB_INTERNAL_ERROR              0xC0009000L
#define USBD_STATUS_CANCELED                        0xC0010000L
#define USBD_STATUS_ISO_NOT_ACCESSED_BY_HW          0xC0020000L
#define USBD_STATUS_ISO_TD_ERROR                    0xC0030000L
#define USBD_STATUS_ISO_NA_LATE_USBPORT             0xC0040000L
#define USBD_STATUS_ISO_NOT_ACCESSED_LATE           0xC0050000L
#define USBD_STATUS_BAD_DESCRIPTOR                  0xC0100000L
#define USBD_STATUS_BAD_DESCRIPTOR_BLEN             0xC0100001L
#define USBD_STATUS_BAD_DESCRIPTOR_TYPE             0xC0100002L
#define USBD_STATUS_BAD_INTERFACE_DESCRIPTOR        0xC0100003L
#define USBD_STATUS_BAD_ENDPOINT_DESCRIPTOR         0xC0100004L
#define USBD_STATUS_BAD_INTERFACE_ASSOC_DESCRIPTOR  0xC0100005L
#define USBD_STATUS_BAD_CONFIG_DESC_LENGTH          0xC0100006L
#define USBD_STATUS_BAD_NUMBER_OF_INTERFACES        0xC0100007L
#define USBD_STATUS_BAD_NUMBER_OF_ENDPOINTS         0xC0100008L
#define USBD_STATUS_BAD_ENDPOINT_ADDRESS            0xC0100009L

/* USBD default maximum transfer size */
#if (_WIN32_WINNT >= 0x0501)
    #define USBD_DEFAULT_MAXIMUM_TRANSFER_SIZE  0xFFFFFFFFL
#else
    #define USBD_DEFAULT_MAXIMUM_TRANSFER_SIZE  PAGE_SIZE
#endif

/* USBD pipe direction testing macro */
#define USBD_PIPE_DIRECTION_IN( x ) ((x)->EndpointAddress & USB_ENDPOINT_DIRECTION_MASK)

/* USBD pipe flags */
#define USBD_PF_CHANGE_MAX_PACKET       0x00000001L
#define USBD_PF_SHORT_PACKET_OPT        0x00000002L
#define USBD_PF_ENABLE_RT_THREAD_ACCESS 0x00000004L
#define USBD_PF_MAP_ADD_TRANSFERS       0x00000008L
#define USBD_PF_VALID_MASK \
    (USBD_PF_CHANGE_MAX_PACKET | USBD_PF_SHORT_PACKET_OPT | \
    USBD_PF_ENABLE_RT_THREAD_ACCESS | USBD_PF_MAP_ADD_TRANSFERS)

/* OS string descriptor index */
#if (_WIN32_WINNT >= 0x0501)
    #define OS_STRING_DESCRIPTOR_INDEX  0xEE
#endif

/* Microsoft descriptor indices */
#if (_WIN32_WINNT >= 0x0501)
    #define MS_GENRE_DESCRIPTOR_INDEX   0x0001
    #define MS_POWER_DESCRIPTOR_INDEX   0x0002
#endif

/* Microsoft OS string signature */
#if (_WIN32_WINNT >= 0x0501)
    #define MS_OS_STRING_SIGNATURE  L"MSFT100"
#endif

/* Microsoft OS flags */
#if (_WIN32_WINNT >= 0x0501)
    #define MS_OS_FLAGS_CONTAINERID 0x02
#endif

/* USB controller flavors */
typedef enum _USB_CONTROLLER_FLAVOR {
    USB_HcGeneric       = 0,
    OHCI_Generic        = 100,
    OHCI_Hydra          = 101,
    OHCI_NEC            = 102,
    UHCI_Generic        = 200,
    UHCI_Piix4          = 201,
    UHCI_Piix3          = 202,
    UHCI_Ich2           = 203,
    UHCI_Ich1           = 205,
    UHCI_Ich3m          = 206,
    UHCI_Ich4           = 207,
    UHCI_Ich5           = 208,
    UHCI_Ich6           = 209,
    UHCI_Intel          = 249,
    UHCI_VIA            = 250,
    UHCI_VIA_x01        = 251,
    UHCI_VIA_x02        = 252,
    UHCI_VIA_x03        = 253,
    UHCI_VIA_x04        = 254,
    UHCI_VIA_x0E_FIFO   = 264,
    EHCI_Generic        = 1000,
    EHCI_NEC            = 2000,
    EHCI_Lucent         = 3000
} USB_CONTROLLER_FLAVOR;

/* USBD version information */
typedef struct _USBD_VERSION_INFORMATION {
    ULONG   USBDI_Version;
    ULONG   Supported_USB_Version;
} USBD_VERSION_INFORMATION;
typedef USBD_VERSION_INFORMATION    *PUSBD_VERSION_INFORMATION;

/* USBD pipe types */
typedef enum _USBD_PIPE_TYPE {
    UsbdPipeTypeControl     = 0,
    UsbdPipeTypeIsochronous = 1,
    UsbdPipeTypeBulk        = 2,
    UsbdPipeTypeInterrupt   = 3
} USBD_PIPE_TYPE;

/* USBD device information */
typedef struct _USBD_DEVICE_INFORMATION {
    ULONG                   OffsetNext;
    PVOID                   UsbdDeviceHandle;
    USB_DEVICE_DESCRIPTOR   DeviceDescriptor;
} USBD_DEVICE_INFORMATION;
typedef USBD_DEVICE_INFORMATION *PUSBD_DEVICE_INFORMATION;

/* USBD pipe information */
typedef struct _USBD_PIPE_INFORMATION {
    USHORT              MaximumPacketSize;
    UCHAR               EndpointAddress;
    UCHAR               Interval;
    USBD_PIPE_TYPE      PipeType;
    USBD_PIPE_HANDLE    PipeHandle;
    ULONG               MaximumTransferSize;
    ULONG               PipeFlags;
} USBD_PIPE_INFORMATION;
typedef USBD_PIPE_INFORMATION   *PUSBD_PIPE_INFORMATION;

/* USBD interface information */
typedef struct _USBD_INTERFACE_INFORMATION {
    USHORT                  Length;
    UCHAR                   InterfaceNumber;
    UCHAR                   AlternateSetting;
    UCHAR                   Class;
    UCHAR                   SubClass;
    UCHAR                   Protocol;
    UCHAR                   Reserved;
    USBD_INTERFACE_HANDLE   InterfaceHandle;
    ULONG                   NumberOfPipes;
    USBD_PIPE_INFORMATION   Pipes[1];
} USBD_INTERFACE_INFORMATION;
typedef USBD_INTERFACE_INFORMATION  *PUSBD_INTERFACE_INFORMATION;

/* URB HCD area */
struct _URB_HCD_AREA {
    PVOID   Reserved8[8];
};

/* URB header */
struct _URB_HEADER {
    USHORT      Length;
    USHORT      Function;
    USBD_STATUS Status;
    PVOID       UsbdDeviceHandle;
    ULONG       UsbdFlags;
};

/* URB select interface */
struct _URB_SELECT_INTERFACE {
    struct _URB_HEADER          Hdr;
    USBD_CONFIGURATION_HANDLE   ConfigurationHandle;
    USBD_INTERFACE_INFORMATION  Interface;
};

/* URB select configuration */
struct _URB_SELECT_CONFIGURATION {
    struct _URB_HEADER              Hdr;
    PUSB_CONFIGURATION_DESCRIPTOR   ConfigurationDescriptor;
    USBD_CONFIGURATION_HANDLE       ConfigurationHandle;
    USBD_INTERFACE_INFORMATION      Interface;
};

/* URB pipe request */
struct _URB_PIPE_REQUEST {
    struct _URB_HEADER  Hdr;
    USBD_PIPE_HANDLE    PipeHandle;
    ULONG               Reserved;
};

/* URB frame length control */
struct _URB_FRAME_LENGTH_CONTROL {
    struct _URB_HEADER  Hdr;
};

/* URB get frame length */
struct _URB_GET_FRAME_LENGTH {
    struct _URB_HEADER  Hdr;
    ULONG               FrameLength;
    ULONG               FrameNumber;
};

/* URB set frame length */
struct _URB_SET_FRAME_LENGTH {
    struct _URB_HEADER  Hdr;
    LONG                FrameLengthDelta;
};

/* URB get current frame number */
struct _URB_GET_CURRENT_FRAME_NUMBER {
    struct _URB_HEADER  Hdr;
    ULONG               FrameNumber;
};

/* URB control descriptor request */
struct _URB_CONTROL_DESCRIPTOR_REQUEST {
    struct _URB_HEADER      Hdr;
    PVOID                   Reserved;
    ULONG                   Reserved0;
    ULONG                   TransferBufferLength;
    PVOID                   TransferBuffer;
    PMDL                    TransferBufferMDL;
    struct _URB             *UrbLink;
    struct _URB_HCD_AREA    hca;
    USHORT                  Reserved1;
    UCHAR                   Index;
    UCHAR                   DescriptorType;
    USHORT                  LanguageId;
    USHORT                  Reserved2;
};

/* URB control get status request */
struct _URB_CONTROL_GET_STATUS_REQUEST {
    struct _URB_HEADER      Hdr;
    PVOID                   Reserved;
    ULONG                   Reserved0;
    ULONG                   TransferBufferLength;
    PVOID                   TransferBuffer;
    PMDL                    TransferBufferMDL;
    struct _URB             *UrbLink;
    struct _URB_HCD_AREA    hca;
    UCHAR                   Reserved1[4];
    USHORT                  Index;
    USHORT                  Reserved2;
};

/* URB control feature request */
struct _URB_CONTROL_FEATURE_REQUEST {
    struct _URB_HEADER      Hdr;
    PVOID                   Reserved;
    ULONG                   Reserved2;
    ULONG                   Reserved3;
    PVOID                   Reserved4;
    PMDL                    Reserved5;
    struct _URB             *UrbLink;
    struct _URB_HCD_AREA    hca;
    USHORT                  Reserved0;
    USHORT                  FeatureSelector;
    USHORT                  Index;
    USHORT                  Reserved1;
};

/* URB control vendor or class request */
struct _URB_CONTROL_VENDOR_OR_CLASS_REQUEST {
    struct _URB_HEADER      Hdr;
    PVOID                   Reserved;
    ULONG                   TransferFlags;
    ULONG                   TransferBufferLength;
    PVOID                   TransferBuffer;
    PMDL                    TransferBufferMDL;
    struct _URB             *UrbLink;
    struct _URB_HCD_AREA    hca;
    UCHAR                   RequestTypeReservedBits;
    UCHAR                   Request;
    USHORT                  Value;
    USHORT                  Index;
    USHORT                  Reserved1;
};

/* URB control get interface request */
struct _URB_CONTROL_GET_INTERFACE_REQUEST {
    struct _URB_HEADER      Hdr;
    PVOID                   Reserved;
    ULONG                   Reserved0;
    ULONG                   TransferBufferLength;
    PVOID                   TransferBuffer;
    PMDL                    TransferBufferMDL;
    struct _URB             *UrbLink;
    struct _URB_HCD_AREA    hca;
    UCHAR                   Reserved1[4];
    USHORT                  Interface;
    USHORT                  Reserved2;
};

/* URB control get configuration request */
struct _URB_CONTROL_GET_CONFIGURATION_REQUEST {
    struct _URB_HEADER      Hdr;
    PVOID                   Reserved;
    ULONG                   Reserved0;
    ULONG                   TransferBufferLength;
    PVOID                   TransferBuffer;
    PMDL                    TransferBufferMDL;
    struct _URB             *UrbLink;
    struct _URB_HCD_AREA    hca;
    UCHAR                   Reserved1[8];
};

/* OS string */
#if (_WIN32_WINNT >= 0x0501)
typedef struct _OS_STRING {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    WCHAR   MicrosoftString[7];
    UCHAR   bVendorCode;
    union {
        UCHAR   bPad;
        UCHAR   bFlags;
    };
} OS_STRING;
typedef OS_STRING   *POS_STRING;
#endif

/* URB OS feature descriptor request */
#if (_WIN32_WINNT >= 0x0501)
struct _URB_OS_FEATURE_DESCRIPTOR_REQUEST {
    struct _URB_HEADER      Hdr;
    PVOID                   Reserved;
    ULONG                   Reserved0;
    ULONG                   TransferBufferLength;
    PVOID                   TransferBuffer;
    PMDL                    TransferBufferMDL;
    struct _URB             *UrbLink;
    struct _URB_HCD_AREA    hca;
    UCHAR                   Recipient   : 5;
    UCHAR                   Reserved1   : 3;
    UCHAR                   Reserved2;
    UCHAR                   InterfaceNumber;
    UCHAR                   MS_PageIndex;
    USHORT                  MS_FeatureDescriptorIndex;
    USHORT                  Reserved3;
};
#endif

/* URB control transfer */
struct _URB_CONTROL_TRANSFER {
    struct _URB_HEADER      Hdr;
    USBD_PIPE_HANDLE        PipeHandle;
    ULONG                   TransferFlags;
    ULONG                   TransferBufferLength;
    PVOID                   TransferBuffer;
    PMDL                    TransferBufferMDL;
    struct _URB             *UrbLink;
    struct _URB_HCD_AREA    hca;
    UCHAR                   SetupPacket[8];
};

/* URB control transfer (extended version) */
#if (_WIN32_WINNT >= 0x0600)
struct _URB_CONTROL_TRANSFER_EX {
    struct _URB_HEADER      Hdr;
    USBD_PIPE_HANDLE        PipeHandle;
    ULONG                   TransferFlags;
    ULONG                   TransferBufferLength;
    PVOID                   TransferBuffer;
    PMDL                    TransferBufferMDL;
    ULONG                   Timeout;
    struct _URB_HCD_AREA    hca;
    UCHAR                   SetupPacket[8];
};
#endif

/* URB bulk or interrupt transfer */
struct _URB_BULK_OR_INTERRUPT_TRANSFER {
    struct _URB_HEADER      Hdr;
    USBD_PIPE_HANDLE        PipeHandle;
    ULONG                   TransferFlags;
    ULONG                   TransferBufferLength;
    PVOID                   TransferBuffer;
    PMDL                    TransferBufferMDL;
    struct _URB             *UrbLink;
    struct _URB_HCD_AREA    hca;
};

/* USBD ISO packet descriptor */
typedef struct _USBD_ISO_PACKET_DESCRIPTOR {
    ULONG       Offset;
    ULONG       Length;
    USBD_STATUS Status;
} USBD_ISO_PACKET_DESCRIPTOR;
typedef USBD_ISO_PACKET_DESCRIPTOR  *PUSBD_ISO_PACKET_DESCRIPTOR;

/* URB ISOCH transfer */
struct _URB_ISOCH_TRANSFER {
    struct _URB_HEADER          Hdr;
    USBD_PIPE_HANDLE            PipeHandle;
    ULONG                       TransferFlags;
    ULONG                       TransferBufferLength;
    PVOID                       TransferBuffer;
    PMDL                        TransferBufferMDL;
    struct _URB                 *UrbLink;
    struct _URB_HCD_AREA        hca;
    ULONG                       StartFrame;
    ULONG                       NumberOfPackets;
    ULONG                       ErrorCount;
    USBD_ISO_PACKET_DESCRIPTOR  IsoPacket[1];
};

/* URB */
typedef struct _URB {
    union {
        struct _URB_HEADER                          UrbHeader;
        struct _URB_SELECT_INTERFACE                UrbSelectInterface;
        struct _URB_SELECT_CONFIGURATION            UrbSelectConfiguration;
        struct _URB_PIPE_REQUEST                    UrbPipeRequest;
        struct _URB_FRAME_LENGTH_CONTROL            UrbFrameLengthControl;
        struct _URB_GET_FRAME_LENGTH                UrbGetFrameLength;
        struct _URB_SET_FRAME_LENGTH                UrbSetFrameLength;
        struct _URB_GET_CURRENT_FRAME_NUMBER        UrbGetCurrentFrameNumber;
        struct _URB_CONTROL_TRANSFER                UrbControlTransfer;
#if (_WIN32_WINNT >= 0x0600)
        struct _URB_CONTROL_TRANSFER_EX             UrbControlTransferEx;
#endif
        struct _URB_BULK_OR_INTERRUPT_TRANSFER      UrbBulkOrInterruptTransfer;
        struct _URB_ISOCH_TRANSFER                  UrbIsochronousTransfer;
        struct _URB_CONTROL_DESCRIPTOR_REQUEST      UrbControlDescriptorRequest;
        struct _URB_CONTROL_GET_STATUS_REQUEST      UrbControlGetStatusRequest;
        struct _URB_CONTROL_FEATURE_REQUEST         UrbControlFeatureRequest;
        struct _URB_CONTROL_VENDOR_OR_CLASS_REQUEST UrbControlVendorClassRequest;
        struct _URB_CONTROL_GET_INTERFACE_REQUEST   UrbControlGetInterfaceRequest;
        struct _URB_CONTROL_GET_CONFIGURATION_REQUEST   UrbControlGetConfigurationRequest;
#if (_WIN32_WINNT >= 0x0501)
        struct _URB_OS_FEATURE_DESCRIPTOR_REQUEST   UrbOSFeatureDescriptorRequest;
#endif
    };
} URB;
typedef URB *PURB;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __USB_H__ */
