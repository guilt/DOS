/*
 *  usbdi.h     Old USB header for compatibility
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

#ifndef __USBDI_H__
#define __USBDI_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <usb.h>
#include <usbioctl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* USBD status values */
#define USBD_STATUS_CANCELLING      0x00020000L
#define USBD_STATUS_CANCELING       0x00020000L
#define USBD_STATUS_NO_MEMORY       0x80000100L
#define USBD_STATUS_ERROR           0x80000000L
#define USBD_STATUS_REQUEST_FAILED  0x80000500L
#define USBD_STATUS_HALTED          0xC0000000L

/* USBD status testing macros */
#define USBD_HALTED( x )    (((ULONG)(x) >> 30) == 3)
#define USBD_STATUS( x )    ((ULONG)(x) & 0x0FFFFFFFL)

/* URB functions */
#define URB_FUNCTION_LAST   0x0029

/* USBD pipe flags */
#define USBD_PF_DOUBLE_BUFFER   0x00000002L
#ifdef USBD_PF_VALID_MASK
    #undef USBD_PF_VALID_MASK
#endif
#define USBD_PF_VALID_MASK \
    (USBD_PF_CHANGE_MAX_PACKET | USBD_PF_DOUBLE_BUFFER | \
    USBD_PF_ENABLE_RT_THREAD_ACCESS | USBD_PF_MAP_ADD_TRANSFERS)

/* USBD transfer bits */
#define USBD_TRANSFER_DIRECTION_BIT         0
#define USBD_SHORT_TRANSFER_OK_BIT          1
#define USBD_START_ISO_TRANSFER_ASAP_BIT    2

/* Macro to extract the transfer direction */
#ifdef USBD_TRANSFER_DIRECTION
    #undef USBD_TRANSFER_DIRECTION
#endif
#define USBD_TRANSFER_DIRECTION( x )    ((x) & USBD_TRANSFER_DIRECTION_IN)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __USBDI_H__ */
