/*
 *  mountdev.h  Mount device definitions
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

#ifndef _MOUNTDEV_
#define _MOUNTDEV_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#include <mountmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Mount device I/O control codes */
#if (NTDDI_VERSION >= 0x05000000)
    #define IOCTL_MOUNTDEV_QUERY_UNIQUE_ID \
        CTL_CODE( MOUNTDEVCONTROLTYPE, 0, METHOD_BUFFERED, FILE_ANY_ACCESS )
    #define IOCTL_MOUNTDEV_QUERY_SUGGESTED_LINK_NAME \
        CTL_CODE( MOUNTDEVCONTROLTYPE, 3, METHOD_BUFFERED, FILE_ANY_ACCESS )
    #define IOCTL_MOUNTDEV_LINK_CREATED \
        CTL_CODE( MOUNTDEVCONTROLTYPE, 4, METHOD_BUFFERED, FILE_READ_ACCESS | \
        FILE_WRITE_ACCESS )
    #define IOCTL_MOUNTDEV_LINK_DELETED \
        CTL_CODE( MOUNTDEVCONTROLTYPE, 5, METHOD_BUFFERED, FILE_READ_ACCESS | \
        FILE_WRITE_ACCESS )
#endif
#if (NTDDI_VERSION >= 0x05010000)
    #define IOCTL_MOUNTDEV_QUERY_STABLE_GUID \
        CTL_CODE( MOUNTDEVCONTROLTYPE, 6, METHOD_BUFFERED, FILE_ANY_ACCESS )
#endif

/* Mount device unique identifier */
#if (NTDDI_VERSION >= 0x05000000)
typedef struct _MOUNTDEV_UNIQUE_ID {
    USHORT  UniqueIdLength;
    UCHAR   UniqueId[1];
} MOUNTDEV_UNIQUE_ID;
typedef MOUNTDEV_UNIQUE_ID  *PMOUNTDEV_UNIQUE_ID;
#endif

/* IOCTL_MOUNTDEV_QUERY_SUGGESTED_LINK_NAME output parameters */
#if (NTDDI_VERSION >= 0x05000000)
typedef struct _MOUNTDEV_SUGGESTED_LINK_NAME {
    BOOLEAN UseOnlyIfThereAreNoOtherLinks;
    USHORT  NameLength;
    WCHAR   Name[1];
} MOUNTDEV_SUGGESTED_LINK_NAME;
typedef MOUNTDEV_SUGGESTED_LINK_NAME    *PMOUNTDEV_SUGGESTED_LINK_NAME;
#endif

/* IOCTL_MOUNTDEV_QUERY_STABLE_GUID output parameters */
#if (NTDDI_VERSION >= 0x05010000)
typedef struct _MOUNTDEV_STABLE_GUID {
    GUID    StableGuid;
} MOUNTDEV_STABLE_GUID;
typedef MOUNTDEV_STABLE_GUID    *PMOUNTDEV_STABLE_GUID;
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _MOUNTDEV_ */
