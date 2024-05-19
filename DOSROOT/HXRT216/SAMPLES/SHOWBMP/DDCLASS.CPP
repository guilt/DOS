
#include "DDClass.h"

DDSURFACEDESC g_surfaceDesc = {0};

// IID_IDirectDraw2 GUID {0xb3a6f3e0, 0x2b43, 0x11cf, {0xa2, 0xde, 0, 0xaa, 0, 0xb9, 0x33, 0x56}};

bool DD_OBJ::Init(HWND hwnd, DWORD reqWidth, DWORD reqHeight)
{
	HRESULT result;
    char szText[64];

	LPDIRECTDRAW temp_lpdd = NULL;

	result = DirectDrawCreate(NULL,&temp_lpdd,NULL);
    if(result != DD_OK) {
        wsprintf(szText, "DirectDrawCreate() failed [%X]\r\n", result);
        OutputDebugString(szText);
        return false;
    }
	result = temp_lpdd->QueryInterface(IID_IDirectDraw2,(void**)&lpDD);
	temp_lpdd->Release();
    if(result != DD_OK) {
        wsprintf(szText, "QueryInterface() failed [%X]\r\n", result);
        OutputDebugString(szText);
        return false;
    }

	result = lpDD->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if(result != DD_OK) {
        wsprintf(szText, "SetCooperativeLevel() failed [%X]\r\n", result);
        OutputDebugString(szText);
        return false;
    }

    // first try a 32bpp mode, then a 24bpp mode.
    // and if 320x240 doesn't exist, use 640x480 instead

    wsprintf(szText, "SetDisplayMode(%u, %u)\r\n", reqWidth, reqHeight);
    OutputDebugString(szText);
	result = lpDD->SetDisplayMode(reqWidth, reqHeight, 32, 0, 0);
    if(result != DD_OK) {
        result = lpDD->SetDisplayMode(reqWidth, reqHeight, 24, 0, 0);
        if(result != DD_OK) {
            if (reqWidth < 640) {
                result = lpDD->SetDisplayMode(640, 480, 32, 0, 0);
                if (result != DD_OK)
                    result = lpDD->SetDisplayMode(640, 480, 24, 0, 0);
                if (result == DD_OK) {
                    reqWidth = 640;
                    reqHeight = 480;
                }
            }
            if(result != DD_OK) {
                wsprintf(szText, "SetDisplayMode(%u, %u, 32/24) failed [%X]\r\n", reqWidth, reqHeight, result);
                OutputDebugString(szText);
                return false;
            }
        }
    }
    dwWidth = reqWidth;
    dwHeight = reqHeight;

	return TRUE;

}


// This will init our primary and back surfaces

bool DD_OBJ::InitSurfaces()
{
	HRESULT result; // For the return codes from DirectDraw function/method calls
	DDSURFACEDESC surfaceDesc = {0};
    char szText[64];

    /* init primary surface */

	g_surfaceDesc.dwSize = sizeof(DDSURFACEDESC);
	g_surfaceDesc.dwFlags = DDSD_CAPS;
	g_surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_PRIMARYSURFACE;
		
	result = lpDD->CreateSurface(&g_surfaceDesc,&primarySurface,NULL);
    wsprintf(szText, "lpDD->CreateSurface()=%X\r\n", result);
    OutputDebugString(szText);
    if(result != DD_OK) {
		return false;
    }

    /* init back surface */
	surfaceDesc.dwSize = sizeof(DDSURFACEDESC);
	surfaceDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	surfaceDesc.dwHeight = dwHeight;
	surfaceDesc.dwWidth = dwWidth;
	surfaceDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	result = lpDD->CreateSurface(&surfaceDesc,&backSurface,NULL);
    wsprintf(szText, "lpDD->CreateSurface()=%X\r\n", result);
    OutputDebugString(szText);
    if(result != DD_OK) {
		return false;
    }
	// Now we'll get the backSurface's HDC
	HDC hSurfDC = NULL;

	result = backSurface->GetDC(&hSurfDC);
    wsprintf(szText, "backSurface->GetDC()=%X\r\n", result);
    OutputDebugString(szText);
    if(result != DD_OK) {
		return false;
    }
	// Create a rect defining the backSurface
	RECT rect = {0,0,dwWidth,dwHeight};

	result = FillRect(hSurfDC,&rect,(HBRUSH)GetStockObject(LTGRAY_BRUSH));
    wsprintf(szText, "FillRect()=%X\r\n", result);
    OutputDebugString(szText);

	// Unlock the backSurface (if you don't do this BAD THINGS HAPPEN :)
	result = backSurface->ReleaseDC(hSurfDC);
    wsprintf(szText, "backSurface->ReleaseDC()=%X\r\n", result);
    OutputDebugString(szText);
    if(result != DD_OK) {
		return false;
    }
	return true; // Surfaces created successfully
}

// This will load the backSurface with our bitmap from cmdline

bool DD_OBJ::LoadBackSurface(HINSTANCE hinstance, HWND hwnd, BITMAPINFOHEADER * pBM)
{
    char szText[64];
    int iColors;
    char * pData;

    if (!pBM->biClrUsed) {
        switch (pBM->biBitCount) {
        case 1:
            iColors = 2;
            break;
        case 4:
            iColors = 16;
            break;
        case 8:
            iColors = 256;
            break;
        case 15:
        case 16:
        case 32:
            if (pBM->biCompression == BI_BITFIELDS)
                iColors = 3;
            else
                iColors = 0;
            break;
        default:
            iColors = 0;
        }
    } else
        iColors = pBM->biClrUsed;

    pData = (char *)pBM + pBM->biSize + iColors * 4;

    HDC win_hdc = GetDC(hwnd);
    wsprintf(szText, "GetDC(%X)=%X\r\n", hwnd, win_hdc);
    OutputDebugString(szText);
    if(!win_hdc) {
		return false;
    }
    hdc = CreateCompatibleDC(win_hdc);
    wsprintf(szText, "CreateCompatibleDC()=%X\r\n", hdc);
    OutputDebugString(szText);
    if (!hdc) {
        return false;
    }

	ReleaseDC(hwnd,win_hdc);
    wsprintf(szText, "ReleaseDC(%X,%X)\r\n", hwnd, win_hdc);
    OutputDebugString(szText);

    // create the bitmap

	HDC hdcScrn = GetDC(NULL);
    wsprintf(szText, "GetDC(0)=%X\r\n", hdcScrn);
    OutputDebugString(szText);
    HBITMAP hbitmap = (HBITMAP)CreateDIBitmap(hdcScrn, pBM, CBM_INIT, pData, (BITMAPINFO *)pBM, DIB_RGB_COLORS);
    wsprintf(szText, "CreateDIBitmap()=%X\r\n", hbitmap);
    OutputDebugString(szText);
    ReleaseDC(NULL, hdcScrn);
    wsprintf(szText, "ReleaseDC(0, %X)=%X\r\n", hdcScrn);
    OutputDebugString(szText);
    if(hbitmap == NULL) {
		return false;
    }
	// Select the object into our compatible HDC
    HBITMAP old_bitmap = (HBITMAP)SelectObject(hdc,hbitmap);
    wsprintf(szText, "SelectObject(%X, %X)=%X\r\n", hdc, hbitmap, old_bitmap);
    OutputDebugString(szText);

    HDC surfaceDC = NULL;

	HRESULT result = backSurface->GetDC(&surfaceDC);
    wsprintf(szText, "backSurface->GetDC()=%X\r\n", result);
    OutputDebugString(szText);
	if(result != DD_OK)	{
		SelectObject(hdc,old_bitmap);
		DeleteObject(hbitmap);
		return false;
	}


    int i = BitBlt(surfaceDC,
                   (dwWidth - pBM->biWidth) / 2,
                   (dwHeight - pBM->biHeight) / 2,
                   pBM->biWidth,
                   pBM->biHeight,hdc,0,0,SRCCOPY);

    wsprintf(szText, "BitBlt()=%X (copies bitmap to back surface)\r\n", i);
    OutputDebugString(szText);

	result = backSurface->ReleaseDC(surfaceDC);
    wsprintf(szText, "backSurface->ReleaseDC()=%X\r\n", result);
    OutputDebugString(szText);
	
	SelectObject(hdc,old_bitmap);
	DeleteObject(hbitmap);
	return i;

}

// This draws the backSurface to the primarySurface

bool DD_OBJ::Draw(HWND hwnd)
{
    HRESULT result;
    HRESULT result2;
    char szText[64];

    DDBLTFX ddbltfx = {0};

	ddbltfx.dwSize = sizeof(DDBLTFX); // This has to be initialized
	ddbltfx.dwDDFX = DDBLTFX_NOTEARING; // This should avoid tearing

	result = DDERR_WASSTILLDRAWING;
    while(result == DDERR_WASSTILLDRAWING) {
        OutputDebugString("DDS->Blt()\r\n");
        result = primarySurface->Blt(0,backSurface,NULL,DDBLT_WAIT,&ddbltfx) ;
        if (result == DDERR_SURFACELOST) {
            if (DD_OK != (result2 = primarySurface->Restore())) {
                wsprintf(szText, "Restore for primary surface failed [%X]\r\n", result2);
                OutputDebugString(szText);
            }
            if (DD_OK != (result2 = backSurface->Restore())) {
                wsprintf(szText, "Restore for back surface failed [%X]\r\n", result2);
                OutputDebugString(szText);
            }
            if (result2 == DD_OK)
                result = DDERR_WASSTILLDRAWING;
        }
    };

    wsprintf(szText, "primarySurface->Blt()=%X\r\n", result);
    OutputDebugString(szText);
    if(result != DD_OK) {
		return false;
    }
	return true;
}

// Free all memory associated with DD_OBJ

void DD_OBJ::Free()
{
	// If an IDirectDraw2 interface has been instantiated
	if(lpDD)
        lpDD->RestoreDisplayMode();

	// If a backSurface has been allocated
    if(backSurface) {
		backSurface->Release();
		backSurface = NULL;
	}

	// If a primarySurface has been allocated
	if(primarySurface) {
		primarySurface->Release();
		primarySurface = NULL;
	}

	// If an IDirectDraw2 interface has been instantiated
	if(lpDD) {
		lpDD->Release();
		lpDD = NULL;
	}

	// If the hdc has been filled
	if(hdc)	{
		DeleteDC(hdc);
		hdc = NULL;
	}

} // end of DD_OBJ::Free()

// The deconstructor -- When a DD_OBJ is "destroyed" be sure all the memory is freed

DD_OBJ::~DD_OBJ() { Free(); }
