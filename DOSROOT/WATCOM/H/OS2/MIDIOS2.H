/*
 *  midios2.h   OS/2 Multimedia Extensions MIDI include file.
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

#ifndef __MIDIOS2_H__
#define __MIDIOS2_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define STATUS_BIT 0x80
#define TRACK_OFF 0
#define TRACK_ON 1
#define NORMAL_SYSEX 0xf0
#define ESCAPE_SYSEX 0xf7
#define META 0xff

#define MMIO_SEQ MMIOM_USER+1
#define MMIO_MERGE MMIOM_USER+2
#define MMIO_FROM_SEQ MMIOM_USER+3
#define MMIO_TIMED_READ MMIOM_USER+4
#define MMIO_SET_TRACKS MMIOM_USER+5
#define MMIO_FORMAT_0 MMIOM_USER+6
#define MMIO_GETHEADER MMIOM_GETHEADER
#define MMIOM_GETFILELENGTH MMIOM_USER+10
#define MMIOM_GETTRACKLENGTH MMIOM_USER+11

#pragma pack( __push, 1 )

typedef struct _MIDIHEADER {
    CHAR   chHeaderChunk[4];
    ULONG  ulHeaderLength;
    USHORT usFormat;
    USHORT usNumTracks;
    USHORT usDivision;
    VOID   *vpAdditionalInformation;
} MIDIHEADER;

typedef struct _MMMIDIHEADER {
    ULONG      ulHeaderLength;
    ULONG      ulContentType;
    ULONG      ulMediaType;
    MIDIHEADER midiheader;
} MMMIDIHEADER, *PMMMIDIHEADER;

#pragma pack( __pop )

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
