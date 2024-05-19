
// Win32 sample using 2 threads

#include "windows.h"
#include "stdio.h"

HANDLE g_hConOut   = 0;
HANDLE g_hConInp   = 0;
HANDLE g_hThread1  = 0;
HANDLE g_hThread2  = 0;
int g_PosX		= 2;
int g_PosY		= 7;
int g_bCancel	= 0;

DWORD _stdcall thread1proc(void * lParam);
DWORD _stdcall thread2proc(void * lParam);

int main()
{
    DWORD threadid1;
    DWORD threadid2;
    DWORD dwWritten;
    DWORD dwNum;
    DWORD dwRead;
    int i;
    COORD coord;
    INPUT_RECORD ir;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    char str1[80];

    g_hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
    g_hConInp = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(g_hConInp, 0);
        
    GetConsoleScreenBufferInfo(g_hConOut, &csbi);
        
//--- clear the screen

	coord.X = 0;
    coord.Y = 0;
    for (i = csbi.dwSize.Y;i;i--) {
   	    FillConsoleOutputAttribute(g_hConOut, 7, csbi.dwSize.X, coord, &dwRead);
   	    FillConsoleOutputCharacter(g_hConOut, '±', csbi.dwSize.X, coord, &dwRead);
        coord.Y++;
    }

//--- now write a blue rectangle as "text window"

//--- first calculate its position so it is centered

		i = csbi.dwSize.X;
        i = i - 60;
        if (i > 0)
          g_PosX = i / 2;

        i = csbi.dwSize.Y;
        i = i - 7;
        if (i > 0)
            g_PosY = i / 2;

		coord.X = g_PosX;
		coord.Y = g_PosY;
		i = 7;
        while (i) {
    	   FillConsoleOutputAttribute( g_hConOut, 0x17, 60, coord, &dwWritten);
    	   FillConsoleOutputCharacter( g_hConOut, ' ', 60, coord, &dwWritten);
           i--;
           coord.Y++;
        }

//--- set cursor to screen bottom

		i = csbi.dwSize.Y;
        i--;
		coord.X = 0;
		coord.Y = i;
        SetConsoleCursorPosition(g_hConOut, coord);

//--- create 2 threads

        g_hThread1 = CreateThread(0, 0x4000, thread1proc, 0, 0, &threadid1);
        g_hThread2 = CreateThread(0, 0x4000, thread2proc, 0, 0, &threadid2);
        if ((g_hThread1 == 0) || (g_hThread2 == 0)) {
            printf("creating threads failed\n");
            exit(1);
        }

//--- wait for ESC to be pressed

        dwNum = 0;
		coord.X = g_PosX + 1;
        coord.Y = g_PosY + 5;
        while (1) {
			GetNumberOfConsoleInputEvents(g_hConInp, &dwRead);
	        i = wsprintf(str1, "main thread: %u loops, con events: %u", dwNum, dwRead);
	        WriteConsoleOutputCharacter( g_hConOut, str1, i, coord, &dwWritten);
    	    dwNum++;
        	if (dwRead)
                while (dwRead) {
					ReadConsoleInput( g_hConInp, &ir, 1, &dwWritten);
                    if ((ir.EventType == KEY_EVENT) && (ir.Event.KeyEvent.bKeyDown)) {
                        if (ir.Event.KeyEvent.uChar.AsciiChar == 0x1b)
                            goto endloop;
                    }
                    dwRead--;
                }
            else
            	Sleep(0);
        };
    endloop:

//--- request threads to terminate

		g_bCancel = TRUE;
        
//--- wait till they are terminated

        WaitForMultipleObjects(2, &g_hThread2, TRUE, 1000);

        return 0;

};

// *** 1. thread ***

DWORD _stdcall thread1proc(void * lParam)
{
    DWORD num;
    COORD coord;
    DWORD dwWritten;
    int i;
    char szText[80];

		coord.X = g_PosX + 1;
        coord.Y = g_PosY + 1;
        num = 0;
        do {
    	   i = wsprintf(szText, "thread 1: %u loops", num);
    	   WriteConsoleOutputCharacter( g_hConOut, szText, i, coord, &dwWritten);
	       num++;
        } while (g_bCancel == 0);
        return 0;
};

// *** 2. thread ***

DWORD _stdcall thread2proc(void * lParam)
{
    DWORD num;
    COORD coord;
    DWORD dwWritten;
    int i;
    char szText[80];

		coord.X = g_PosX + 1;
        coord.Y = g_PosY + 3;
        num = 0;
        do {
    	    i = wsprintf( szText, "thread 2: %u loops", num);
    	    WriteConsoleOutputCharacter(g_hConOut, szText, i, coord, &dwWritten);
        	num++;
        } while (g_bCancel == 0);
        return 0;
};

