/*
 *  drivinit.h  Printer driver definitions
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

#ifndef _INC_DRIVINIT
#define _INC_DRIVINIT

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef _INC_WINDOWS
    #include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack( __push, 1 )

/* Device mode constants */
#define DM_UPDATE           1
#define DM_COPY             2
#define DM_PROMPT           4
#define DM_MODIFY           8
#define DM_IN_BUFFER        DM_MODIFY
#define DM_IN_PROMPT        DM_PROMPT
#define DM_OUT_BUFFER       DM_COPY
#define DM_OUT_DEFAULT      DM_UPDATE

/* Maximum length of a device name */
#define CCHDEVICENAME 32

/* Maximum length of a paper name */
#define CCHPAPERNAME  64

/* Device mode */
typedef struct tagDEVMODE {
    char    dmDeviceName[CCHDEVICENAME];
    UINT    dmSpecVersion;
    UINT    dmDriverVersion;
    UINT    dmSize;
    UINT    dmDriverExtra;
    DWORD   dmFields;
    int     dmOrientation;
    int     dmPaperSize;
    int     dmPaperLength;
    int     dmPaperWidth;
    int     dmScale;
    int     dmCopies;
    int     dmDefaultSource;
    int     dmPrintQuality;
    int     dmColor;
    int     dmDuplex;
    int     dmYResolution;
    int     dmTTOption;
} DEVMODE;
typedef DEVMODE         *PDEVMODE;
typedef DEVMODE NEAR    *NPDEVMODE;
typedef DEVMODE FAR     *LPDEVMODE;

#pragma pack( __pop )

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _INC_DRIVINIT */
