/*
 *  tvout.h     TV output definitions
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

#ifndef __TVOUT__
#define __TVOUT__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Video parameter commands */
#define VP_COMMAND_GET  0x00000001L
#define VP_COMMAND_SET  0x00000002L

/* Video parameter flags */
#define VP_FLAGS_TV_MODE        0x00000001L
#define VP_FLAGS_TV_STANDARD    0x00000002L
#define VP_FLAGS_FLICKER        0x00000004L
#define VP_FLAGS_OVERSCAN       0x00000008L
#define VP_FLAGS_MAX_UNSCALED   0x00000010L
#define VP_FLAGS_POSITION       0x00000020L
#define VP_FLAGS_BRIGHTNESS     0x00000040L
#define VP_FLAGS_CONTRAST       0x00000080L
#define VP_FLAGS_COPYPROTECT    0x00000100L

/* Video parameter modes */
#define VP_MODE_WIN_GRAPHICS    0x00000001L
#define VP_MODE_TV_PLAYBACK     0x00000002L

/* Video parameter TV standards */
#define VP_TV_STANDARD_NTSC_M   0x00000001L
#define VP_TV_STANDARD_NTSC_M_J 0x00000002L
#define VP_TV_STANDARD_PAL_B    0x00000004L
#define VP_TV_STANDARD_PAL_D    0x00000008L
#define VP_TV_STANDARD_PAL_H    0x00000010L
#define VP_TV_STANDARD_PAL_I    0x00000020L
#define VP_TV_STANDARD_PAL_M    0x00000040L
#define VP_TV_STANDARD_PAL_N    0x00000080L
#define VP_TV_STANDARD_SECAM_B  0x00000100L
#define VP_TV_STANDARD_SECAM_D  0x00000200L
#define VP_TV_STANDARD_SECAM_G  0x00000400L
#define VP_TV_STANDARD_SECAM_H  0x00000800L
#define VP_TV_STANDARD_SECAM_K  0x00001000L
#define VP_TV_STANDARD_SECAM_K1 0x00002000L
#define VP_TV_STANDARD_SECAM_L  0x00004000L
#define VP_TV_STANDARD_WIN_VGA  0x00008000L
#define VP_TV_STANDARD_NTSC_433 0x00010000L
#define VP_TV_STANDARD_PAL_G    0x00020000L
#define VP_TV_STANDARD_PAL_60   0x00040000L
#define VP_TV_STANDARD_SECAM_L1 0x00080000L

/* Video parameter copy protection types */
#define VP_CP_TYPE_APS_TRIGGER  0x00000001L
#define VP_CP_TYPE_MACROVISION  0x00000002L

/* Video parameter copy protection commands */
#define VP_CP_CMD_ACTIVATE      0x00000001L
#define VP_CP_CMD_DEACTIVATE    0x00000002L
#define VP_CP_CMD_CHANGE        0x00000004L

/* Video parameters */
typedef struct _VIDEOPARAMETERS {
    GUID    Guid;
    ULONG   dwOffset;
    ULONG   dwCommand;
    ULONG   dwFlags;
    ULONG   dwMode;
    ULONG   dwTVStandard;
    ULONG   dwAvailableModes;
    ULONG   dwAvailableTVStandard;
    ULONG   dwFlickerFilter;
    ULONG   dwOverScanX;
    ULONG   dwOverScanY;
    ULONG   dwMaxUnscaledX;
    ULONG   dwMaxUnscaledY;
    ULONG   dwPositionX;
    ULONG   dwPositionY;
    ULONG   dwBrightness;
    ULONG   dwContrast;
    ULONG   dwCPType;
    ULONG   dwCPCommand;
    ULONG   dwCPStandard;
    ULONG   dwCPKey;
    ULONG   bCP_APSTriggerBits;
    UCHAR   bOEMCopyProtection[256];
} VIDEOPARAMETERS;
typedef VIDEOPARAMETERS *PVIDEOPARAMETERS;
typedef VIDEOPARAMETERS *LPVIDEOPARAMETERS;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __TVOUT__ */
