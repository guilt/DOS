/*
 *  GL/pgl.h    OS/2 PGL interface.
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

#ifndef __PGL_H__
#define __PGL_H__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define INCL_DOSPROCESS
#define INCL_32
#define INCL_DEV
#define INCL_WIN
#define INCL_DOS
#define INCL_GRE_PALETTE
#define INCL_GPI
#define INCL_PM
#include <os2.h>

#include "gl.h"

#define  PGL_None 0

#define  PGL_USE_GL           1
#define  PGL_BUFFER_SIZE      2
#define  PGL_LEVEL            3
#define  PGL_RGBA             4
#define  PGL_DOUBLEBUFFER     5
#define  PGL_STEREO           6
#define  PGL_AUX_BUFFERS      7
#define  PGL_RED_SIZE         8
#define  PGL_GREEN_SIZE       9
#define  PGL_BLUE_SIZE        10
#define  PGL_ALPHA_SIZE       11
#define  PGL_DEPTH_SIZE       12
#define  PGL_STENCIL_SIZE     13
#define  PGL_ACCUM_RED_SIZE   14
#define  PGL_ACCUM_GREEN_SIZE 15
#define  PGL_ACCUM_BLUE_SIZE  16
#define  PGL_ACCUM_ALPHA_SIZE 17
#define  PGL_SINGLEBUFFER     18

typedef LHANDLE HGC;

typedef struct visualconfig {
    ULONG vid;
    BOOL  rgba;
    int   redSize, greenSize, blueSize, alphaSize;
    ULONG redMask, greenMask, blueMask;
    int   accumRedSize, accumGreenSize, accumBlueSize, accumAlphaSize;
    BOOL  doubleBuffer;
    BOOL  stereo;
    int   bufferSize;
    int   depthSize;
    int   stencilSize;
    int   auxBuffers;
    int   level;
    PVOID reserved;
    struct visualconfig *next;
} VISUALCONFIG, *PVISUALCONFIG;

extern PVISUALCONFIG APIENTRY pglChooseConfig(HAB hab, int *attriblist);
extern PVISUALCONFIG* APIENTRY pglQueryConfigs(HAB hab);
extern HGC APIENTRY pglCreateContext(HAB hab, PVISUALCONFIG pVisualConfig, HGC Sharelist, BOOL IsDirect);
extern BOOL APIENTRY pglMakeCurrent(HAB hab,HGC hgc, HWND hwnd);
extern BOOL APIENTRY pglDestroyContext(HAB hab, HGC hgc);
extern BOOL APIENTRY pglCopyContext(HAB hab, HGC hgc_src, HGC hgc_dst, GLuint attrib_mask);
extern int APIENTRY pglSelectColorIndexPalette(HAB hab, HPAL hpal, HGC hgc);
extern LONG APIENTRY pglIsIndirect(HAB hab, HGC hgc);
extern HGC  APIENTRY pglGetCurrentContext(HAB hab);
extern HWND APIENTRY pglGetCurrentWindow(HAB hab);
extern HPS  APIENTRY pglWaitGL(HAB hab);
extern void APIENTRY pglWaitPM(HAB hab);
extern void APIENTRY pglSwapBuffers(HAB hab, HWND hwnd);
extern LONG APIENTRY pglQueryCapability(HAB hab);
extern void APIENTRY pglQueryVersion(HAB hab, int *major, int *minor);
extern BOOL APIENTRY pglUsePMBitmapFont(HAB hab, LONG id, int first, int count, int listbase);
extern BOOL APIENTRY pglGrabFrontBitmap(HAB hab,HPS *phps,HBITMAP *phbitmap);
extern BOOL APIENTRY pglReleaseFrontBitmap(HAB hab);
extern BOOL APIENTRY pglUseFont(HAB,HPS,FATTRS *,long,int,int,int);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
