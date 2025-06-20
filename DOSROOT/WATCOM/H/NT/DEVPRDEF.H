/*
 *  devprdef.h / devpropdef.h   Device property definitions
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

#ifndef _DEVPROPDEF_H_
#define _DEVPROPDEF_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Device property primitive data types */
typedef ULONG   DEVPROPTYPE;
typedef ULONG   *PDEVPROPTYPE;
typedef CHAR    DEVPROP_BOOLEAN;
typedef CHAR    *PDEVPROP_BOOLEAN;
typedef GUID    DEVPROPGUID;
typedef GUID    *PDEVPROPGUID;
typedef ULONG   DEVPROPID;
typedef ULONG   *PDEVPROPID;

/* Device property type modifierss */
#define DEVPROP_TYPEMOD_ARRAY   0x00001000L
#define DEVPROP_TYPEMOD_LIST    0x00002000L
#define MAX_DEVPROP_TYPEMOD     0x00002000L
#define DEVPROP_MASK_TYPEMOD    0x0000F000L

/* Device property types */
#define DEVPROP_TYPE_EMPTY                  0x00000000L
#define DEVPROP_TYPE_NULL                   0x00000001L
#define DEVPROP_TYPE_SBYTE                  0x00000002L
#define DEVPROP_TYPE_BYTE                   0x00000003L
#define DEVPROP_TYPE_INT16                  0x00000004L
#define DEVPROP_TYPE_UINT16                 0x00000005L
#define DEVPROP_TYPE_INT32                  0x00000006L
#define DEVPROP_TYPE_UINT32                 0x00000007L
#define DEVPROP_TYPE_INT64                  0x00000008L
#define DEVPROP_TYPE_UINT64                 0x00000009L
#define DEVPROP_TYPE_FLOAT                  0x0000000AL
#define DEVPROP_TYPE_DOUBLE                 0x0000000BL
#define DEVPROP_TYPE_DECIMAL                0x0000000CL
#define DEVPROP_TYPE_GUID                   0x0000000DL
#define DEVPROP_TYPE_CURRENCY               0x0000000EL
#define DEVPROP_TYPE_DATE                   0x0000000FL
#define DEVPROP_TYPE_FILETIME               0x00000010L
#define DEVPROP_TYPE_BOOLEAN                0x00000011L
#define DEVPROP_TYPE_STRING                 0x00000012L
#define DEVPROP_TYPE_STRING_LIST            (DEVPROP_TYPE_STRING | DEVPROP_TYPEMOD_LIST)
#define DEVPROP_TYPE_SECURITY_DESCRIPTOR    0x00000013L
#define DEVPROP_TYPE_SECURITY_DESCRIPTOR_STRING 0x00000014L
#define DEVPROP_TYPE_DEVPROPERTY            0x00000015L
#define DEVPROP_TYPE_DEVPROPTYPE            0x00000016L
#define DEVPROP_TYPE_BINARY                 (DEVPROP_TYPE_BYTE | DEVPROP_TYPEMOD_ARRAY)
#define DEVPROP_TYPE_ERROR                  0x00000017L
#define DEVPROP_TYPE_NTSTATUS               0x00000018L
#define DEVPROP_TYPE_STRING_INDIRECT        0x00000019L
#define MAX_DEVPROP_TYPE                    0x00000019L
#define DEVPROP_MASK_TYPE                   0x00000FFFL

/* Device property boolean values */
#define DEVPROP_TRUE    (-1)
#define DEVPROP_FALSE   0

/* First usable device property identifier */
#define DEVPROPID_FIRST_USABLE  2

/* Device property key */
typedef struct _DEVPROPKEY {
    DEVPROPGUID fmtid;
    DEVPROPID   pid;
} DEVPROPKEY;
typedef DEVPROPKEY  *PDEVPROPKEY;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _DEVPROPDEF_H_ */

/* Macro to define a device property key */
#ifdef DEFINE_DEVPROPKEY
    #undef DEFINE_DEVPROPKEY
#endif
#ifdef INITGUID
    #define DEFINE_DEVPROPKEY( x, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) \
        EXTERN_C const DEVPROPKEY __cdecl x = { { p1, p2, p3, { p4, p5, p6, p7, p8, p9, p10, \
            p11 } }, p12 }
#else
    #define DEFINE_DEVPROPKEY( x, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12 ) \
        EXTERN_C const DEVPROPKEY __cdecl x
#endif
