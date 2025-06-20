/*
 *  usbcamdi.h  USB camera definitions
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

#ifndef __USBCAMDI_H__
#define __USBCAMDI_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Pipe flags */
#define USBCAMD_DATA_PIPE       0x0001
#define USBCAMD_MULTIPLEX_PIPE  0x0002
#define USBCAMD_SYNC_PIPE       0x0004
#define USBCAMD_DONT_CARE_PIPE  0x0008

/* Stream association values */
#define USBCAMD_VIDEO_STREAM        0x01
#define USBCAMD_STILL_STREAM        0x02
#define USBCAMD_VIDEO_STILL_STREAM  (USBCAMD_VIDEO_STREAM | USBCAMD_STILL_STREAM)

/* Packet flags */
#define USBCAMD_PROCESSPACKETEX_DropFrame           0x0002
#define USBCAMD_PROCESSPACKETEX_NextFrameIsStill    0x0004
#define USBCAMD_PROCESSPACKETEX_CurrentFrameIsStill 0x0008

/* Pipe state flags */
#define USBCAMD_STOP_STREAM     0x00000001L
#define USBCAMD_START_STREAM    0x00000000L

/* USB camera version number */
#define USBCAMD_VERSION_200 0x0200

/* Pipe configuration descriptor */
typedef struct _pipe_config_descriptor {
    CHAR    StreamAssociation;
    UCHAR   PipeConfigFlags;
} USBCAMD_Pipe_Config_Descriptor;
typedef USBCAMD_Pipe_Config_Descriptor  *PUSBCAMD_Pipe_Config_Descriptor;

/* Camera control flags */
typedef enum {
    USBCAMD_CamControlFlag_NoVideoRawProcessing = 0x0001,
    USBCAMD_CamControlFlag_NoStillRawProcessing = 0x0002,
    USBCAMD_CamControlFlag_AssociatedFormat     = 0x0004,
    USBCAMD_CamControlFlag_EnableDeviceEvents   = 0x0008
} USBCAMD_CamControlFlags;

/* Camera callbacks */
typedef NTSTATUS    (NTAPI *PCOMMAND_COMPLETE_FUNCTION)( PVOID, PVOID, NTSTATUS );
typedef VOID        (NTAPI *PSTREAM_RECEIVE_PACKET)( PVOID, PVOID, PBOOLEAN );
typedef NTSTATUS    (NTAPI *PCAM_INITIALIZE_ROUTINE)( PDEVICE_OBJECT, PVOID );
typedef NTSTATUS    (NTAPI *PCAM_CONFIGURE_ROUTINE)( PDEVICE_OBJECT, PVOID, PUSBD_INTERFACE_INFORMATION, PUSB_CONFIGURATION_DESCRIPTOR, PLONG, PLONG );
typedef NTSTATUS    (NTAPI *PCAM_CONFIGURE_ROUTINE_EX)( PDEVICE_OBJECT, PVOID, PUSBD_INTERFACE_INFORMATION, PUSB_CONFIGURATION_DESCRIPTOR, ULONG, PUSBCAMD_Pipe_Config_Descriptor, PUSB_DEVICE_DESCRIPTOR );
typedef NTSTATUS    (NTAPI *PCAM_START_CAPTURE_ROUTINE)( PDEVICE_OBJECT, PVOID );
typedef NTSTATUS    (NTAPI *PCAM_START_CAPTURE_ROUTINE_EX)( PDEVICE_OBJECT, PVOID, ULONG );
typedef NTSTATUS    (NTAPI *PCAM_ALLOCATE_BW_ROUTINE)( PDEVICE_OBJECT, PVOID, PULONG, PVOID );
typedef NTSTATUS    (NTAPI *PCAM_ALLOCATE_BW_ROUTINE_EX)( PDEVICE_OBJECT, PVOID, PULONG, PVOID, ULONG );
typedef NTSTATUS    (NTAPI *PCAM_FREE_BW_ROUTINE)( PDEVICE_OBJECT, PVOID );
typedef NTSTATUS    (NTAPI *PCAM_FREE_BW_ROUTINE_EX)( PDEVICE_OBJECT, PVOID, ULONG );
typedef VOID        (NTAPI *PADAPTER_RECEIVE_PACKET_ROUTINE)( struct _HW_STREAM_REQUEST_BLOCK * );
typedef NTSTATUS    (NTAPI *PCAM_STOP_CAPTURE_ROUTINE)( PDEVICE_OBJECT, PVOID );
typedef NTSTATUS    (NTAPI *PCAM_STOP_CAPTURE_ROUTINE_EX)( PDEVICE_OBJECT, PVOID, ULONG );
typedef ULONG       (NTAPI *PCAM_PROCESS_PACKET_ROUTINE)( PDEVICE_OBJECT, PVOID, PVOID, PUSBD_ISO_PACKET_DESCRIPTOR, PVOID, PUSBD_ISO_PACKET_DESCRIPTOR, PVOID, PBOOLEAN, PBOOLEAN );
typedef ULONG       (NTAPI *PCAM_PROCESS_PACKET_ROUTINE_EX)( PDEVICE_OBJECT, PVOID, PVOID, PUSBD_ISO_PACKET_DESCRIPTOR, PVOID, PUSBD_ISO_PACKET_DESCRIPTOR, PVOID, PBOOLEAN, PULONG, PULONG );
typedef VOID        (NTAPI *PCAM_NEW_FRAME_ROUTINE)( PVOID, PVOID );
typedef VOID        (NTAPI *PCAM_NEW_FRAME_ROUTINE_EX)( PVOID, PVOID, ULONG, PULONG );
typedef NTSTATUS    (NTAPI *PCAM_PROCESS_RAW_FRAME_ROUTINE)( PDEVICE_OBJECT, PVOID, PVOID, PVOID, ULONG, PVOID, ULONG, ULONG, PULONG );
typedef NTSTATUS    (NTAPI *PCAM_PROCESS_RAW_FRAME_ROUTINE_EX)( PDEVICE_OBJECT, PVOID, PVOID, PVOID, ULONG, PVOID, ULONG, ULONG, PULONG, ULONG, ULONG );
typedef NTSTATUS    (NTAPI *PCAM_STATE_ROUTINE)( PDEVICE_OBJECT, PVOID );

/* USB camera device data */
typedef struct _USBCAMD_DEVICE_DATA {
    ULONG                           Sig;
    PCAM_INITIALIZE_ROUTINE         CamInitialize;
    PCAM_INITIALIZE_ROUTINE         CamUnInitialize;
    PCAM_PROCESS_PACKET_ROUTINE     CamProcessUSBPacket;
    PCAM_NEW_FRAME_ROUTINE          CamNewVideoFrame;
    PCAM_PROCESS_RAW_FRAME_ROUTINE  CamProcessRawVideoFrame;
    PCAM_START_CAPTURE_ROUTINE      CamStartCapture;
    PCAM_STOP_CAPTURE_ROUTINE       CamStopCapture;
    PCAM_CONFIGURE_ROUTINE          CamConfigure;
    PCAM_STATE_ROUTINE              CamSaveState;
    PCAM_STATE_ROUTINE              CamRestoreState;
    PCAM_ALLOCATE_BW_ROUTINE        CamAllocateBandwidth;
    PCAM_FREE_BW_ROUTINE            CamFreeBandwidth;
} USBCAMD_DEVICE_DATA;
typedef USBCAMD_DEVICE_DATA *PUSBCAMD_DEVICE_DATA;

/* USB camera device data (version 2) */
typedef struct _USBCAMD_DEVICE_DATA2 {
    ULONG                               Sig;
    PCAM_INITIALIZE_ROUTINE             CamInitialize;
    PCAM_INITIALIZE_ROUTINE             CamUnInitialize;
    PCAM_PROCESS_PACKET_ROUTINE_EX      CamProcessUSBPacketEx;
    PCAM_NEW_FRAME_ROUTINE_EX           CamNewVideoFrameEx;
    PCAM_PROCESS_RAW_FRAME_ROUTINE_EX   CamProcessRawVideoFrameEx;
    PCAM_START_CAPTURE_ROUTINE_EX       CamStartCaptureEx;
    PCAM_STOP_CAPTURE_ROUTINE_EX        CamStopCaptureEx;
    PCAM_CONFIGURE_ROUTINE_EX           CamConfigureEx;
    PCAM_STATE_ROUTINE                  CamSaveState;
    PCAM_STATE_ROUTINE                  CamRestoreState;
    PCAM_ALLOCATE_BW_ROUTINE_EX         CamAllocateBandwidthEx;
    PCAM_FREE_BW_ROUTINE_EX             CamFreeBandwidthEx;
} USBCAMD_DEVICE_DATA2;
typedef USBCAMD_DEVICE_DATA2    *PUSBCAMD_DEVICE_DATA2;

/* USB camera interface callbacks */
typedef NTSTATUS    (NTAPI *PFNUSBCAMD_SetVideoFormat)( PVOID, struct _HW_STREAM_REQUEST_BLOCK * );
typedef NTSTATUS    (NTAPI *PFNUSBCAMD_WaitOnDeviceEvent)( PVOID, ULONG, PVOID, ULONG, PCOMMAND_COMPLETE_FUNCTION, PVOID, BOOLEAN );
typedef NTSTATUS    (NTAPI *PFNUSBCAMD_CancelBulkReadWrite)( PVOID, ULONG );
typedef NTSTATUS    (NTAPI *PFNUSBCAMD_SetIsoPipeState)( PVOID, ULONG );
typedef NTSTATUS    (NTAPI *PFNUSBCAMD_BulkReadWrite)( PVOID, USHORT, PVOID, ULONG, PCOMMAND_COMPLETE_FUNCTION, PVOID );

/* USB camera interface */
typedef struct {
    INTERFACE                       Interface;
    PFNUSBCAMD_WaitOnDeviceEvent    USBCAMD_WaitOnDeviceEvent;
    PFNUSBCAMD_BulkReadWrite        USBCAMD_BulkReadWrite;
    PFNUSBCAMD_SetVideoFormat       USBCAMD_SetVideoFormat;
    PFNUSBCAMD_SetIsoPipeState      USBCAMD_SetIsoPipeState;
    PFNUSBCAMD_CancelBulkReadWrite  USBCAMD_CancelBulkReadWrite;
} USBCAMD_INTERFACE;
typedef USBCAMD_INTERFACE   *PUSBCAMD_INTERFACE;

/* Functions in USBCAMD.SYS */
PVOID       NTAPI USBCAMD_AdapterReceivePacket( struct _HW_STREAM_REQUEST_BLOCK *, PUSBCAMD_DEVICE_DATA, PDEVICE_OBJECT *, BOOLEAN );
NTSTATUS    NTAPI USBCAMD_ControlVendorCommand( PVOID, UCHAR, USHORT, USHORT, PVOID, PULONG, BOOLEAN, PCOMMAND_COMPLETE_FUNCTION, PVOID );
ULONG       NTAPI USBCAMD_DriverEntry( PVOID, PVOID, ULONG, ULONG, PADAPTER_RECEIVE_PACKET_ROUTINE );
NTSTATUS    NTAPI USBCAMD_GetRegistryKeyValue( HANDLE, PWCHAR, ULONG, PVOID, ULONG );
ULONG       NTAPI USBCAMD_InitializeNewInterface( PVOID, PVOID, ULONG, ULONG );
NTSTATUS    NTAPI USBCAMD_SelectAlternateInterface( PVOID, PUSBD_INTERFACE_INFORMATION );
#ifdef DEBUG_LOG
VOID        NTAPI USBCAMD_Debug_LogEntry( CHAR *, ULONG, ULONG, ULONG );
#endif

/* Other macros */
#ifdef DEBUG_LOG
    #define ILOGENTRY( p1, p2, p3, p4 ) \
        USBCAMD_Debug_LogEntry( p1, (ULONG)(p1), (ULONG)(p2), (ULONG)(p3) )
#else
    #define ILOGENTRY( p1, p2, p3, p4 )
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __USBCAMDI_H__ */
