/*
 *  zmouse.h    Mouse wheel definitions
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

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Mouse wheel registered message strings */
#ifdef UNICODE
    #define MSH_MOUSEWHEEL      L"MSWHEEL_ROLLMSG"
    #define MSH_WHEELSUPPORT    L"MSH_WHEELSUPPORT_MSG"
    #define MSH_SCROLL_LINES    L"MSH_SCROLL_LINES_MSG"
#else
    #define MSH_MOUSEWHEEL      "MSWHEEL_ROLLMSG"
    #define MSH_WHEELSUPPORT    "MSH_WHEELSUPPORT_MSG"
    #define MSH_SCROLL_LINES    "MSH_SCROLL_LINES_MSG"
#endif

/* Constant used with WM_MOUSEWHEEL */
#define WHEEL_DELTA 120

/* Mouse wheel window message */
#ifndef WM_MOUSEWHEEL
    #define WM_MOUSEWHEEL   (WM_MOUSELAST + 1)
#endif

/* Strings related to MSWHEEL.EXE */
#ifdef UNICODE
    #define MOUSEZ_CLASSNAME    L"MouseZ"
    #define MOUSEZ_TITLE        L"Magellan MSWHEEL"
#else
    #define MOUSEZ_CLASSNAME    "MouseZ"
    #define MOUSEZ_TITLE        "Magellan MSWHEEL"
#endif
#define MSH_WHEELMODULE_CLASS   MOUSEZ_CLASSNAME
#define MSH_WHEELMODULE_TITLE   MOUSEZ_TITLE

/* Constant used with SPI_GETWHEELSCROLLLINES and SPI_SETWHEELSCROLLLINES */
#ifndef WHEEL_PAGESCROLL
    #define WHEEL_PAGESCROLL    UINT_MAX
#endif

/* Mouse wheel SystemParametersInfo() command */
#ifndef SPI_SETWHEELSCROLLLINES
    #define SPI_SETWHEELSCROLLLINES 0x0069
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
