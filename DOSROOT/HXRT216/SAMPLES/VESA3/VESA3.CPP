
// sample in C using VESA32

#define USECRT 0 /* set this to 0 if CRT should not be used */

// #define WIN32_LEAN_AND_MEAN
// #include <windows.h>
#if USECRT
#include "stdio.h"
#include "malloc.h"
#include "string.h"
#include "conio.h"
#endif
#include "vesa32.h"

#define COLS 640
#define ROWS 480

SVGAINFO svgainfo;

#if USECRT==0
int printf(char * pszOut, ...)
{
    return 0;
}
void * malloc(int dwBytes)
{
void * pRC = 0;
    _asm {
        mov bx,word ptr dwBytes+2
        mov cx,word ptr dwBytes+0
        mov ax,501h
        int 31h
        jc label1
        push bx
        push cx
        pop eax
        mov pRC, eax
        label1:
    }
    return pRC;
}
void free(void * pVoid)
{
    return;
}
void getch()
{
    _asm {
        mov ah,0
        int 16h
    }
    return;
}
int main(int, char * *);
int mainCRTStartup()
{
    main(0,0);
    _asm {
        mov ax,4c00h
        int 21h
    }
}
#endif

//--- fill a screen rectangle with a color

void fill64k(int xpos, int ypos, int xlen, int ylen, int color)
{
    int iOffs;
    short * pScreen;

    iOffs = svgainfo.BytesPerScanLine/2 - xlen;
    pScreen = (short *)(svgainfo.PhysBasePtr + svgainfo.BytesPerScanLine * ypos + 2 * xpos);

    for (int i = 0; i < ylen;i++) {
        for (int j = 0; j < xlen; j++) {
            *pScreen++ = (short)color;
        }
        pScreen = pScreen + iOffs;
    }
    return;
}


int main(int cArgs, char * * pArgs)
{
    int iMode;
    int iPrevMode;
    int iStateSize;
    int iVMemSize;
    void * pSaveBuff;
    void * pSaveBuff2;

#ifdef _VESA32_
    VesaInit(); /* call if the vesa code is linked statically */
#endif
    // search a VESA 16bpp video mode

	if (!(iMode = SearchVesaMode(COLS,ROWS,16))) {
		printf("no support for VESA mode %ux%ux16\n", COLS, ROWS);
		return 0;
    }
    iMode = iMode | 0x4000;      // use LFB
    if (!GetVesaModeInfo(iMode, &svgainfo)) {
        printf("cannot get VESA mode info\n");
        return 0;
    }

    //  save the current video state

    iPrevMode = GetVesaMode();
    iStateSize = GetVesaStateBufferSize();
    pSaveBuff = (void *)malloc(iStateSize);
    if (pSaveBuff) {
        SaveVesaVideoState(pSaveBuff, iStateSize);
        iVMemSize = GetVesaMemoryBufferSize(iPrevMode);
        pSaveBuff2 = (void *)malloc(iVMemSize);
        if (pSaveBuff2) {
	        SaveVesaVideoMemory(pSaveBuff2, iVMemSize);
        }
    }

    // set the 16bpp VESA color mode with LFB

    if (!SetVesaMode(iMode)) {
        printf("cannot switch to VESA mode %X\n", iMode);
        return 0;
    }

    // now do the "real" work: display some rectangles

#if 1
    for (int i = 0; i < 30; i++)
        fill64k(i*8,i*8,640-i*16,480-i*16, i*0x871);
#else
    for (int i = 0; i < 1; i++)
        fill64k(i*8,i*8,640-i*16,480-i*16, 0x33CF);
#endif

    // wait for a key

    getch();

    // and restore previous video state

    iPrevMode = iPrevMode | 0x80;
    SetVesaMode(iPrevMode);
    if (pSaveBuff) {
        RestoreVesaVideoState(pSaveBuff);
        free(pSaveBuff);
        if (pSaveBuff2) {
            RestoreVesaVideoMemory(pSaveBuff2);
            free(pSaveBuff2);
        }
    }
#ifdef _VESA32_
    VesaExit(); /* call if the vesa code is linked statically */
#endif
	return 0;
}

