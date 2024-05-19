
// display bitmaps files with DirectDraw

#include "DDClass.h"
#include "stdio.h"

#define class_name "ShowBmp"

// WinProc

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    DD_OBJ * pdd_obj;
    PAINTSTRUCT ps;
    		
    switch(message)
    {
        case WM_MOVE:
            OutputDebugString("WM_MOVE received\r\n");
            InvalidateRect(hwnd, 0, 0);
			return 0;

        case WM_PAINT:
            OutputDebugString("WM_PAINT received\r\n");
            BeginPaint(hwnd, &ps);
            if (pdd_obj = (DD_OBJ *)GetWindowLong(hwnd, 0)) {
                OutputDebugString("calling Draw()\r\n");
                pdd_obj->Draw(hwnd);
            }
            EndPaint(hwnd, &ps);
            return 0;

		case WM_KEYDOWN:

			if((int)LOWORD(wparam) == VK_ESCAPE)
				DestroyWindow(hwnd);
			return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

    }

    return DefWindowProc(hwnd, message, wparam, lparam);
}

// main

int main(int argc, char * * argv)
{
    HWND hwnd;
    HANDLE hFile;
    DWORD dwRead;
    DWORD dwWidth, dwHeight;
    MSG msg;
    BITMAPFILEHEADER bfh;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSEX wndclassex;
    DD_OBJ * pdd_obj;
    BITMAPINFOHEADER * pBM;

    if (argc < 2) {
        printf("usage: ShowBmp filename\n");
        printf("filename must be a .BMP file\n");
        return 1;
    }
    hFile = CreateFile(argv[1],GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == (HANDLE)HFILE_ERROR) {
        printf("error opening %s [%X]\n", argv[1], GetLastError());
        return 1;
    }
    if (!ReadFile(hFile, &bfh, sizeof(bfh), &dwRead, 0)) {
        printf("error reading %s [%X]\n", argv[1], GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    if (dwRead != sizeof(bfh)) {
        printf("error reading %s [%X]\n", argv[1], GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    if (bfh.bfType != 'MB') {
        printf("%s is no bitmap file\n", argv[1]);
        CloseHandle(hFile);
        return 1;
    }
    if (!(pBM = (BITMAPINFOHEADER *)LocalAlloc( LMEM_FIXED, bfh.bfSize))) {
        printf("out of memory\n");
        CloseHandle(hFile);
        return 1;
    }
    if (!ReadFile(hFile, pBM, bfh.bfSize, &dwRead, 0)) {
        printf("error reading %s [%X]\n", argv[1], GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    CloseHandle(hFile);

    if ((pBM->biWidth > 1024) || (pBM->biHeight > 768)) {
        printf("bitmap is too large (%u, %u)\n", pBM->biWidth, pBM->biHeight);
        return 1;
    }
    if ((pBM->biWidth > 800) || (pBM->biHeight > 600)) {
        dwWidth = 1024;
        dwHeight = 768;
    } else {
        if ((pBM->biWidth > 640) || (pBM->biHeight > 480)) {
            dwWidth = 800;
            dwHeight= 600;
        } else {
            if ((pBM->biWidth > 320) || (pBM->biHeight > 240)) {
                dwWidth = 640;
                dwHeight = 480;
            } else {
                dwWidth = 320;
                dwHeight = 240;
            }
        }
    }

    ZeroMemory(&wndclassex, sizeof(WNDCLASSEX));
	wndclassex.cbSize = sizeof(WNDCLASSEX);
    wndclassex.style = CS_HREDRAW | CS_VREDRAW;
    wndclassex.lpfnWndProc = WinProc;
    wndclassex.hInstance = hInstance;
    wndclassex.cbWndExtra = sizeof(DD_OBJ *);
    wndclassex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wndclassex.lpszClassName = class_name;

    RegisterClassEx(&wndclassex);

    hwnd = CreateWindowEx(0,
						  class_name,
						  "",
						  WS_POPUP,
						  0,
						  0,
						  0, //dwWidth,
						  0, //dwHeight,
						  NULL,
						  NULL,
						  hInstance,
						  NULL);

	if(!hwnd) {
		return 1;
	}

    if (!(pdd_obj = new DD_OBJ))
        return 1;

    SetWindowLong(hwnd, 0, (LONG)pdd_obj);

    if(pdd_obj->Init(hwnd, dwWidth, dwHeight) == false)	{
        delete pdd_obj;
        printf("Couldn't init DirectDraw!");
		return 1;
	}

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    OutputDebugString("ShowWindow()\r\n");

	if(pdd_obj->InitSurfaces() == false) {
        delete pdd_obj;
		printf("Couldn't init surfaces!");
		return 1;
	}

	if(pdd_obj->LoadBackSurface(hInstance, hwnd, pBM) == false)
	{
        delete pdd_obj;
		printf("Couldn't load the backSurface!");
		return 1;
	}

	// dont show the cursor
    ShowCursor(0);
   
    while(GetMessage(&msg,hwnd,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

    delete pdd_obj;

	return msg.wParam;
}

