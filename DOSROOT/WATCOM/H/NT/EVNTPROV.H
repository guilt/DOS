/*
 *  evntprov.h  Event provider functions
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

#ifndef _EVNTPROV_H_
#define _EVNTPROV_H_

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Macro to specify event functions */
#define EVNTAPI DECLSPEC_IMPORT __stdcall

/* Primitive data types */
typedef ULONGLONG   REGHANDLE;
typedef ULONGLONG   *PREGHANDLE;

/* Event levels */
#define EVENT_MIN_LEVEL 0x00
#define EVENT_MAX_LEVEL 0xFF

/* Event activity control codes */
#define EVENT_ACTIVITY_CTRL_GET_ID          1
#define EVENT_ACTIVITY_CTRL_SET_ID          2
#define EVENT_ACTIVITY_CTRL_CREATE_ID       3
#define EVENT_ACTIVITY_CTRL_GET_SET_ID      4
#define EVENT_ACTIVITY_CTRL_CREATE_SET_ID   5

/* Maximum values */
#define MAX_EVENT_DATA_DESCRIPTORS  128
#define MAX_EVENT_FILTER_DATA_SIZE  1024

/* Event filter types */
#define EVENT_FILTER_TYPE_SCHEMATIZED   0x80000000L

/* Event data descriptor */
typedef struct _EVENT_DATA_DESCRIPTOR {
    ULONGLONG   Ptr;
    ULONG       Size;
    ULONG       Reserved;
} EVENT_DATA_DESCRIPTOR;
typedef EVENT_DATA_DESCRIPTOR   *PEVENT_DATA_DESCRIPTOR;

/* Event descriptor */
typedef struct _EVENT_DESCRIPTOR {
    USHORT      Id;
    UCHAR       Version;
    UCHAR       Channel;
    UCHAR       Level;
    UCHAR       Opcode;
    USHORT      Task;
    ULONGLONG   Keyword;
} EVENT_DESCRIPTOR;
typedef EVENT_DESCRIPTOR        *PEVENT_DESCRIPTOR;
typedef const EVENT_DESCRIPTOR  *PCEVENT_DESCRIPTOR;

/* Event filter descriptor */
typedef struct _EVENT_FILTER_DESCRIPTOR {
    ULONGLONG   Ptr;
    ULONG       Size;
    ULONG       Type;
} EVENT_FILTER_DESCRIPTOR;
typedef EVENT_FILTER_DESCRIPTOR *PEVENT_FILTER_DESCRIPTOR;

/* Event filter header */
typedef struct _EVENT_FILTER_HEADER {
    USHORT      Id;
    UCHAR       Version;
    UCHAR       Reserved[5];
    ULONGLONG   InstanceId;
    ULONG       Size;
    ULONG       NextOffset;
} EVENT_FILTER_HEADER;
typedef EVENT_FILTER_HEADER *PEVENT_FILTER_HEADER;

/* Enable callback */
#ifndef _ETW_KM_
typedef VOID (NTAPI *PENABLECALLBACK)( LPCGUID, ULONG, UCHAR, ULONGLONG, ULONGLONG, PEVENT_FILTER_DESCRIPTOR, PVOID );
#endif

/* Functions in ADVAPI32.DLL */
#ifndef _ETW_KM_
#if (WINVER >= 0x0600)
ULONG EVNTAPI   EventActivityIdControl( ULONG, LPGUID );
BOOLEAN EVNTAPI EventEnabled( REGHANDLE, PCEVENT_DESCRIPTOR );
BOOLEAN EVNTAPI EventProviderEnabled( REGHANDLE, UCHAR, ULONGLONG );
ULONG EVNTAPI   EventRegister( LPCGUID, PENABLECALLBACK, PVOID, PREGHANDLE );
ULONG EVNTAPI   EventUnregister( REGHANDLE );
ULONG EVNTAPI   EventWrite( REGHANDLE, PCEVENT_DESCRIPTOR, ULONG, PEVENT_DATA_DESCRIPTOR );
ULONG EVNTAPI   EventWriteString( REGHANDLE, UCHAR, ULONGLONG, PCWSTR );
ULONG EVNTAPI   EventWriteTransfer( REGHANDLE, PCEVENT_DESCRIPTOR, LPCGUID, LPCGUID, ULONG, PEVENT_DATA_DESCRIPTOR );
#endif
#if (WINVER >= 0x0601)
ULONG EVNTAPI   EventWriteEx( REGHANDLE, PCEVENT_DESCRIPTOR, ULONG64, ULONG, LPCGUID, LPCGUID, ULONG, PEVENT_DATA_DESCRIPTOR );
#endif
#endif

__inline VOID EventDataDescCreate( PEVENT_DATA_DESCRIPTOR x, const VOID * p1,
                                   ULONG p2 )
{
    x->Ptr = (ULONGLONG)p1;
    x->Size = p2;
    x->Reserved = 0;
}

__inline VOID EventDescCreate( PEVENT_DESCRIPTOR x, USHORT p1, UCHAR p2, UCHAR p3,
                               UCHAR p4, USHORT p5, UCHAR p6, ULONGLONG p7 )
{
    x->Id = p1;
    x->Version = p2;
    x->Channel = p3;
    x->Level = p4;
    x->Task = p5;
    x->Opcode = p6;
    x->Keyword = p7;
}

__inline VOID EventDescZero( PEVENT_DESCRIPTOR x )
{
    memset( x, 0, sizeof( EVENT_DESCRIPTOR ) );
}

__inline USHORT EventDescGetId( PCEVENT_DESCRIPTOR x )
{
    return( x->Id );
}

__inline UCHAR EventDescGetVersion( PCEVENT_DESCRIPTOR x )
{
    return( x->Version );
}

__inline USHORT EventDescGetTask( PCEVENT_DESCRIPTOR x )
{
    return( x->Task );
}

__inline UCHAR EventDescGetOpcode( PCEVENT_DESCRIPTOR x )
{
    return( x->Opcode );
}

__inline UCHAR EventDescGetChannel( PCEVENT_DESCRIPTOR x )
{
    return( x->Channel );
}

__inline UCHAR EventDescGetLevel( PCEVENT_DESCRIPTOR x )
{
    return( x->Level );
}

__inline ULONGLONG EventDescGetKeyword( PCEVENT_DESCRIPTOR x )
{
    return( x->Keyword );
}

__inline PEVENT_DESCRIPTOR EventDescSetId( PEVENT_DESCRIPTOR x, USHORT p )
{
    x->Id = p;
    return( x );
}

__inline PEVENT_DESCRIPTOR EventDescSetVersion( PEVENT_DESCRIPTOR x, UCHAR p )
{
    x->Version = p;
    return( x );
}

__inline PEVENT_DESCRIPTOR EventDescSetTask( PEVENT_DESCRIPTOR x, USHORT p )
{
    x->Task = p;
    return( x );
}

__inline PEVENT_DESCRIPTOR EventDescSetOpcode( PEVENT_DESCRIPTOR x, UCHAR p )
{
    x->Opcode = p;
    return( x );
}

__inline PEVENT_DESCRIPTOR EventDescSetLevel( PEVENT_DESCRIPTOR x, UCHAR p )
{
    x->Level = p;
    return( x );
}

__inline PEVENT_DESCRIPTOR EventDescSetChannel( PEVENT_DESCRIPTOR x, UCHAR p )
{
    x->Channel = p;
    return( x );
}

__inline PEVENT_DESCRIPTOR EventDescSetKeyword( PEVENT_DESCRIPTOR x, ULONGLONG p )
{
    x->Keyword = p;
    return( x );
}

__inline PEVENT_DESCRIPTOR EventDescOrKeyword( PEVENT_DESCRIPTOR x, ULONGLONG p )
{
    x->Keyword |= p;
    return( x );
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _EVNTPROV_H_ */
