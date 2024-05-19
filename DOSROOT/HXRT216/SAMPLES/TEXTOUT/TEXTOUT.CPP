
// display some text in a DirectDraw fullscreen window

#include "DDClass.h"
#include "stdio.h"

#define class_name "TextOut"

// WinProc

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    DD_OBJ * pdd_obj;
    PAINTSTRUCT ps;
    		
    switch(message)
    {
        case WM_ACTIVATE:
            if (LOWORD(wparam) == WA_INACTIVE)
                return 0;
            break;
        case WM_MOVE:
            InvalidateRect(hwnd, 0, 0);
			return 0;

        case WM_PAINT:
            BeginPaint(hwnd, &ps);
            if (pdd_obj = (DD_OBJ *)GetWindowLong(hwnd, 0))
                pdd_obj->Draw(hwnd);
            EndPaint(hwnd, &ps);
            return 0;

		case WM_KEYDOWN:

			if((int)wparam == VK_ESCAPE)
				PostMessage(hwnd, WM_CLOSE, 0, 0);
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

    // in DOS there is only a fixed font available.
    // Therefore try to load the windows system font 8514sys.fon.
    // It will then be returned by GetStockObject(SYSTEM_FONT)
    // and be used as default font in a device context.

    if (GetProcAddress(GetModuleHandle("kernel32"),"GetDKrnl32Version"))
        AddFontResource("8514sys.fon");

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

    // show the window now, before Init, to avoid DD errors
    // if running in fullscreen text mode

    ShowWindow(hwnd, SW_SHOWDEFAULT);

	if(pdd_obj->Init(hwnd, 800, 600) == false)	{
        delete pdd_obj;
        printf("Couldn't init DirectDraw!");
		return 1;
	}

	if(pdd_obj->InitSurfaces("Hello, world!") == false) {
        delete pdd_obj;
		printf("Couldn't init surfaces!");
		return 1;
	}

	// hide the cursor
    ShowCursor(0);
   
    while(GetMessage(&msg,hwnd,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

    delete pdd_obj;

	return msg.wParam;
}

