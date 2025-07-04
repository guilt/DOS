/*
 *  codec.h     OS/2 Multimedia Extensions Codec include file.
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

#ifndef __CODEC_H__
#define __CODEC_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack( __push, 4 )

#ifdef INCL_AUDIO_CODEC
 #define INCL_AUDIO_CODEC_ONLY
#endif
#ifndef INCL_AUDIO_CODEC
 #define INCL_AUDIO_CODEC
#endif

#define FOURCC_ULTI mmioFOURCC('U', 'L', 'T', 'I')
#define HEX_FOURCC_ULTI 0x49544C55
#define FOURCC_RT21 mmioFOURCC('R', 'T', '2', '1')
#define HEX_FOURCC_RT21 0x31325452
#define FOURCC_DIB mmioFOURCC('D', 'I', 'B', ' ')
#define HEX_FOURCC_DIB 0x20424944

#define VALID_CODECOPEN_INPUTFLAGS (CODEC_DECOMPRESS|CODEC_WINDOW_CLIPPING | \
   CODEC_PALETTE_TRANS|CODEC_SELFHEAL|CODEC_SCALE_PEL_DOUBLE|CODEC_SCALE_PEL_HALVED| \
   CODEC_SCALE_CONTINUOUS|CODEC_MULAPERTURE|CODEC_HARDWARE|CODEC_DIRECT_DISPLAY)

#ifndef INCL_AUDIO_CODEC_ONLY

#define  MMIO_RGB_5_6_5 0x0001
#define  MMIO_RGB_24 0x0002
#define  MMIO_YUV_4_1_1 0x0004
#define  MMIO_COMPRESSED 0x0008
#define  MMIO_YUV_24 0x0010
#define  MMIO_PALETTIZED 0x0020
#define  MMIO_OS2_BITMAP24 0x0020

#define BLOCK_ORIENTED 1
#define NON_LINEAR 2
#define INIT_CODEC 4

typedef struct _GENPAL {
    ULONG ulStartIndex;
    ULONG ulNumColors;
    PRGB2 prgb2Entries;
} GENPAL, *PGENPAL;

typedef struct _CODECVIDEOHEADER {
    ULONG  ulStructLen;
    ULONG  cx;
    ULONG  cy;
    USHORT cPlanes;
    USHORT cBitCount;
    ULONG  ulColorEncoding;
    GENPAL genpal;
} CODECVIDEOHEADER, *PCODECVIDEOHEADER;

typedef struct _MMVIDEOOPEN {
    ULONG ulStructLen;
    ULONG ulQuality;
    ULONG ulKeyFrameRate;
    ULONG ulScale;
    ULONG ulRate;
    ULONG ulDataConstraint;
    ULONG ulConstraintInterval;
} MMVIDEOOPEN, *PMMVIDEOOPEN;

#endif

typedef struct _MMAUDIOOPEN {
    ULONG ulStructLen;
    ULONG ulSamplesPerBlock;
    ULONG ulBytesPerBlock;
    ULONG ulFlags;
    ULONG ulBestGuess;
    ULONG ulBlockAlignment;
    ULONG ulLength;
    ULONG hCodec;
    PCODECPROC pfnCodec;
} MMAUDIOOPEN, *PMMAUDIOOPEN;

typedef struct _CODECOPEN {
    ULONG ulFlags;
    PVOID pControlHdr;
    PVOID pSrcHdr;
    PVOID pDstHdr;
    PVOID pOtherInfo;
} CODECOPEN, *PCODECOPEN;

#ifdef INCL_AUDIO_CODEC

#define AUDIO_CODEC_INF 1000

typedef struct _AUDIO_CODEC_INFO {
    ULONG ulStructLen;
    ULONG ulBytesPerBlock;
    ULONG ulBlockAlignment;
    ULONG hCodec;
    PCODECPROC pfnCodec;
} AUDIO_CODEC_INFO;

#endif

typedef struct _MMCOMPRESS {
    ULONG ulStructLen;
    ULONG ulFlags;
    ULONG ulSrcBufLen;
    PVOID pSrcBuf;
    ULONG ulDstBufLen;
    PVOID pDstBuf;
    PVOID pRunTimeInfo;
} MMCOMPRESS, *PMMCOMPRESS;

#ifndef INCL_AUDIO_CODEC_ONLY

typedef struct _MMVIDEOCOMPRESS {
    ULONG  ulStructLen;
    GENPAL genpalVideo;
    PVOID  pControlHdr;
} MMVIDEOCOMPRESS, *PMMVIDEOCOMPRESS;

#endif

#ifdef INCL_AUDIO_CODEC

#define START_DECOMPRESSION 1
#define CONTINUE_DECOMPRESSION 2
#define START_SEEK 4
#define CONTINUE_SEEK 8

#endif

#define MMIO_DROP_DELTA_FRAME 0x0001
#define MMIO_IS_KEY_FRAME 0x0002
#define MMIO_IS_PALETTE 0x0004
#define MMIO_PALETTE_CHANGE 0x0008
#define MMIO_ORIGIN_LOWERLEFT 0x0010
#define MMIO_RECTL_CHANGE 0x0020
#define MMIO_ORIGIN_UPPERLEFT 0x0040
#define MMIO_DROP_FRAME_DECODE 0x0080
#define MMIO_HIGH_QUALITY 0x0100
#define MMIO_IGNORE_CLIPPING 0x0200
#define MMIO_OUTPUT_FULL_IMAGE 0x0400

#define VALID_DECOMPRESS_INPUTFLAGS (MMIO_DROP_DELTA_FRAME|MMIO_PALETTE_CHANGE| \
    MMIO_ORIGIN_LOWERLEFT|MMIO_RECTL_CHANGE|MMIO_DROP_FRAME_DECODE|MMIO_ORIGIN_UPPERLEFT| \
    MMIO_HIGH_QUALITY|MMIO_IGNORE_CLIPPING|MMIO_OUTPUT_FULL_IMAGE)

#ifdef INCL_AUDIO_CODEC
#define START_COMPRESSION 1
#define CONTINUE_COMPRESSION 2
#define SOURCE_UNUSED 4
#define TARGET_UNUSED 8
#endif

#define MMIO_INVISIBLE_FRAME 0x1000
#define MMIO_NULL_FRAME 0x2000

typedef struct _MMDECOMPRESS {
    ULONG ulStructLen;
    ULONG ulFlags;
    ULONG ulSrcBufLen;
    PVOID pSrcBuf;
    ULONG ulDstBufLen;
    PVOID pDstBuf;
    PVOID pRunTimeInfo;
} MMDECOMPRESS, *PMMDECOMPRESS;

#ifndef INCL_AUDIO_CODEC_ONLY

typedef struct _MMVIDEODECOMPRESS {
    ULONG  ulStructLen;
    ULONG  ulRectlCount;
    PRECTL prectl;
    ULONG  ulSkipLength;
    ULONG  ulDecodeLines;
    GENPAL genpalPhysical;
    GENPAL genpalVideo;
    RECTL  rectlSrc;
    RECTL  rectlDst;
    ULONG  ulDeltaCount;
    ULONG  ulParm1;
    ULONG  ulParm2;
    ULONG  ulParm3;
    ULONG  ulParm4;
} MMVIDEODECOMPRESS, *PMMVIDEODECOMPRESS;

#endif

typedef struct _RECORDTAB {
    ULONG ulReserved1;
    PVOID pRecord;
    ULONG ulLength;
    ULONG ulReserved2;
    ULONG ulReserved3;
    ULONG ulParm1;
    ULONG ulParm2;
} RECORDTAB, FAR *PRECORDTAB;

typedef struct _RECORDTABWRITE {
    PVOID pRecord;
    ULONG ulReserved1;
    ULONG ulLength;
    ULONG ulReserved2;
    ULONG ulReserved3;
    ULONG ulParm1;
    ULONG ulParm2;
} RECORDTABWRITE, FAR *PRECORDTABWRITE;

typedef struct _TRACKMAP {
    ULONG      ulTrackID;
    ULONG      ulNumEntries;
    PRECORDTAB pRecordTabList;
} TRACKMAP, *PTRACKMAP;

#ifndef INCL_AUDIO_CODEC_ONLY

#ifndef INCL_GPI
#error INCL_GPI is required
#endif

#define MULTITRACKREAD_EXTENDED 4
#define MULTITRACKREAD_NOTDONE 1
#define MULTITRACKREAD_EOF 2

#define MULTITRACKWRITE_MERGE 1

#define MOVIE_HAS_VIDEO 0x0001
#define MOVIE_HAS_AUDIO 0x0002
#define MOVIE_CAN_SEEK 0x0004
#define MOVIE_CAN_SCAN 0x0008
#define MOVIE_HAS_COPYRIGHT 0x0010
#define MOVIE_WAS_CAPTUREFILE 0x0020

#define MMIO_VIDEO_UNKNOWN 0
#define MMIO_VIDEO_DATA 1

typedef struct _MMMULTITRACKREAD {
    ULONG     ulLength;
    PVOID     pBuffer;
    ULONG     ulFlags;
    ULONG     ulNumTracks;
    PTRACKMAP pTrackMapList;
    ULONG     ulBufferLength;
    ULONG     ulReserved;
} MMMULTITRACKREAD, *PMMMULTITRACKREAD;

typedef struct _MMMULTITRACKWRITE {
    ULONG     ulNumTracks;
    PTRACKMAP pTrackMapList;
    ULONG     ulFlags;
    ULONG     ulReserved;
} MMMULTITRACKWRITE, *PMMMULTITRACKWRITE;

typedef struct _MMMOVIEHEADER {
    ULONG ulStructLen;
    ULONG ulContentType;
    ULONG ulMediaType;
    ULONG ulMovieCapsFlags;
    ULONG ulMaxBytesPerSec;
    ULONG ulPaddingGranularity;
    ULONG ulSuggestedBufferSize;
    ULONG ulStart;
    ULONG ulLength;
    ULONG ulNextTrackID;
    ULONG ulNumEntries;
    PMMTRACKINFO pmmTrackInfoList;
    PSZ   pszMovieTitle;
    ULONG ulCountry;
    ULONG ulCodePage;
    ULONG ulAvgBytesPerSec;
} MMMOVIEHEADER, *PMMMOVIEHEADER;

typedef struct _MMVIDEOHEADER {
    ULONG  ulStructLen;
    ULONG  ulContentType;
    ULONG  ulMediaType;
    ULONG  ulVideoCapsFlags;
    ULONG  ulWidth;
    ULONG  ulHeight;
    ULONG  ulScale;
    ULONG  ulRate;
    ULONG  ulStart;
    ULONG  ulLength;
    ULONG  ulTotalFrames;
    ULONG  ulInitialFrames;
    MMTIME mmtimePerFrame;
    ULONG  ulSuggestedBufferSize;
    GENPAL genpalVideo;
    PMMXDIBHEADER pmmXDIBHeader;
    ULONG  ulHHRWidth;
    BOOL   fHHR;
} MMVIDEOHEADER, *PMMVIDEOHEADER;

#endif

#pragma pack( __pop )

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
