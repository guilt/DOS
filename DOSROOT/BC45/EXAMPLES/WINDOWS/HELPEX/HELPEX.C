/****************************************************************************

   PROGRAM:    HelpEx.c

   Copyright (c) 1991, 1992 Borland International, Inc.

   PURPOSE:    Illustrates calls to WinHelp and context-sensitive help.
         HelpEx loads library MenuHook, which detects F1 keystrokes in
         the HelpEx application menus.

   FUNCTIONS:

   WinMain() - Calls initialization function, processes message loop.
   InitApplication() - Initializes window data and registers window class.
   InitInstance() - Saves instance handle and creates main window.
   MainWndProc() - Processes window messages.
   About() - Processes messages for "About" dialog box.
   MakeHelpPathName() - Derives path name of help file.

****************************************************************************/

#define  STRICT
#include <windows.h>
#pragma hdrstop
#include "helpex.h"
#include "helpids.h"
#include <windowsx.h>

HWND       hWnd;               /* Handle to main window */
HINSTANCE  hInst;              /* Handle to instance data*/
BOOL       bHelp = FALSE;      /* Help mode flag; TRUE = "ON"*/
HCURSOR    hHelpCursor;        /* Cursor displayed when in help mode*/
char       szHelpFileName[EXE_NAME_MAX_SIZE+1];    /* Help file name*/
HACCEL     hAccTable;                              /* handle to accelerator table */

void MakeHelpPathName(char*);  /* Function deriving help file path */


/****************************************************************************

   FUNCTION:   WinMain(HINSTANCE, HINSTANCE, LPSTR, int)

   PURPOSE:    Calls initialization function, processes message loop.

****************************************************************************/
#pragma argsused

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
   MSG msg;

   if (!hPrevInstance)
       if (!InitApplication(hInstance))
       return (FALSE);

   if (!InitInstance(hInstance, nCmdShow))
       return (FALSE);

   while (GetMessage(&msg, NULL, 0, 0)) {

      /* Only translate message if it is not an accelerator message */
      if (!TranslateAccelerator(hWnd, hAccTable, &msg)) {

          TranslateMessage(&msg);
          DispatchMessage(&msg);
      }
   }
   return (msg.wParam);
}


/****************************************************************************

   FUNCTION:   InitApplication(HINSTANCE)

   PURPOSE:    Initializes window data and registers window class.

   RETURNS:    Status of RegisterClass() call.

****************************************************************************/

BOOL InitApplication(HINSTANCE hInstance)
{
   WNDCLASS wc;

   wc.style = 0;
   wc.lpfnWndProc = MainWndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hInstance;
   wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = GetStockObject(WHITE_BRUSH);
   wc.lpszMenuName ="HelpexMenu";
   wc.lpszClassName = "HelpexWClass";

   return (RegisterClass(&wc));
}


/****************************************************************************

   FUNCTION:   InitInstance(HINSTANCE, int)

   PURPOSE:    Saves instance handle in global variable and creates main
               window.

   RETURNS:    Status of CreateWindow() call.

****************************************************************************/

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

   hInst = hInstance;

   hAccTable = LoadAccelerators(hInst, "HelpexAcc");

   hWnd = CreateWindow(
       "HelpexWClass",
       "Help Example ",
       WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT,
       CW_USEDEFAULT,
       CW_USEDEFAULT,
       CW_USEDEFAULT,
       NULL,
       NULL,
       hInstance,
       NULL
       );

   if (!hWnd)
       return (FALSE);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   EnableMenuItem(GetSubMenu(GetMenu(hWnd), 1), IDM_CLEAR, MF_ENABLED);

   MakeHelpPathName(szHelpFileName);
   hHelpCursor = LoadCursor(hInst,"HelpCursor");

   return (TRUE);

}

/****************************************************************************

   FUNCTION:   MainWndProc(HWND, UINT, WORD, LONG)

   PURPOSE:    Processes window messages.

   MESSAGES:

       WM_COMMAND- Application menu item
       WM_DESTROY- Destroy window

****************************************************************************/

#pragma warn -eff
LRESULT CALLBACK _export MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   DLGPROC lpProcAbout;
   DWORD   dwHelpContextId;

   switch (message) {

       case WM_COMMAND:
           /* Was F1 just pressed in a menu, or are we in help mode */
           /* (Shift-F1)? */

     if (bHelp) {
         UINT  id = GET_WM_COMMAND_ID(wParam, lParam);

         dwHelpContextId =
       (id == IDM_NEW)    ? (DWORD) HELPID_FILE_NEW     :
       (id == IDM_OPEN)   ? (DWORD) HELPID_FILE_OPEN    :
       (id == IDM_SAVE)   ? (DWORD) HELPID_FILE_SAVE    :
       (id == IDM_SAVEAS) ? (DWORD) HELPID_FILE_SAVE_AS :
       (id == IDM_PRINT)  ? (DWORD) HELPID_FILE_PRINT   :
       (id == IDM_EXIT)   ? (DWORD) HELPID_FILE_EXIT    :
       (id == IDM_UNDO)   ? (DWORD) HELPID_EDIT_UNDO    :
       (id == IDM_CUT)    ? (DWORD) HELPID_EDIT_CUT     :
       (id == IDM_CLEAR)  ? (DWORD) HELPID_EDIT_CLEAR   :
       (id == IDM_COPY)   ? (DWORD) HELPID_EDIT_COPY    :
       (id == IDM_PASTE)  ? (DWORD) HELPID_EDIT_PASTE   :
              (DWORD) 0L;

         if (!dwHelpContextId)
         {
       MessageBox( hWnd, "Help not available for Help Menu item",
             "Help Example", MB_OK                          );
       return (DefWindowProc(hWnd, message, wParam, lParam));
         }

         bHelp = FALSE;
         WinHelp(hWnd,szHelpFileName,HELP_CONTEXT,dwHelpContextId);
         break;
     }

     switch (GET_WM_COMMAND_ID(wParam, lParam)) {
         case IDM_NEW:
         case IDM_OPEN:
         case IDM_SAVE:
         case IDM_SAVEAS:
         case IDM_PRINT:
         case IDM_UNDO:
         case IDM_CUT:
         case IDM_CLEAR:
         case IDM_COPY:
         case IDM_PASTE:
       MessageBox(hWnd,
       "Command not implemented",
       "Help Example",
       MB_OK);
       break;

         case IDM_EXIT:
        DestroyWindow(hWnd);
        break;

         case IDM_HELP_INDEX:
       WinHelp(hWnd,szHelpFileName,HELP_INDEX,0L);
       break;

         case IDM_HELP_KEYBOARD:
       WinHelp(hWnd,szHelpFileName,HELP_KEY,(DWORD)(LPSTR)"keys");
       break;

         case IDM_HELP_HELP:
       WinHelp(hWnd,"WINHELP.HLP",HELP_INDEX,0L);
       break;

         case IDM_ABOUT:
       lpProcAbout = (DLGPROC)MakeProcInstance((FARPROC)About, hInst);
       DialogBox(hInst,
           "AboutBox",
           hWnd,
           lpProcAbout);
       FreeProcInstance((FARPROC)lpProcAbout);
       break;

         default:
       return (DefWindowProc(hWnd, message, wParam, lParam));
     }

     break;

       case WM_LBUTTONDOWN:
     if (bHelp)
     {
         bHelp = FALSE;
         WinHelp( hWnd, szHelpFileName, HELP_CONTEXT,
      (DWORD) HELPID_EDIT_WINDOW          );
         break;
     }

           return (DefWindowProc(hWnd, message, wParam, lParam));

       case WM_NCLBUTTONDOWN:
           /* If we are in help mode (Shift-F1) then display context- */
           /* sensitive help for non-client area. */

           if (bHelp) {
               dwHelpContextId =
                   (wParam == HTCAPTION)     ? (DWORD) HELPID_TITLE_BAR     :
                   (wParam == HTREDUCE)      ? (DWORD) HELPID_MINIMIZE_ICON :
                   (wParam == HTZOOM)        ? (DWORD) HELPID_MAXIMIZE_ICON :
                   (wParam == HTSYSMENU)     ? (DWORD) HELPID_SYSTEM_MENU   :
                   (wParam == HTBOTTOM)      ? (DWORD) HELPID_SIZING_BORDER :
                   (wParam == HTBOTTOMLEFT)  ? (DWORD) HELPID_SIZING_BORDER :
                   (wParam == HTBOTTOMRIGHT) ? (DWORD) HELPID_SIZING_BORDER :
                   (wParam == HTTOP)         ? (DWORD) HELPID_SIZING_BORDER :
                   (wParam == HTLEFT)        ? (DWORD) HELPID_SIZING_BORDER :
                   (wParam == HTRIGHT)       ? (DWORD) HELPID_SIZING_BORDER :
                   (wParam == HTTOPLEFT)     ? (DWORD) HELPID_SIZING_BORDER :
                   (wParam == HTTOPRIGHT)    ? (DWORD) HELPID_SIZING_BORDER :
                                               (DWORD) 0L;

               if (!((BOOL)dwHelpContextId))
                   return (DefWindowProc(hWnd, message, wParam, lParam));

               bHelp = FALSE;
               WinHelp(hWnd,szHelpFileName,HELP_CONTEXT,dwHelpContextId);
               break;
           }

           return (DefWindowProc(hWnd, message, wParam, lParam));

       case WM_KEYDOWN:
           if (wParam == VK_F1) {

               /* If Shift-F1, turn help mode on and set help cursor */

               if (GetKeyState(VK_SHIFT)<0) {
                   bHelp = TRUE;
                   SetCursor(hHelpCursor);
                   return (DefWindowProc(hWnd, message, wParam, lParam));
               }

               /* If F1 without shift, then call up help main index topic */
               else {
                   WinHelp(hWnd,szHelpFileName,HELP_INDEX,0L);
               }
           }

           else if (wParam == VK_ESCAPE && bHelp) {

               /* Escape during help mode: turn help mode off */
               bHelp = FALSE;
             #if defined(__WIN32__)
               SetCursor((HCURSOR)GetClassLong(hWnd,GCL_HCURSOR));
             #else
               SetCursor((HCURSOR)GetClassWord(hWnd,GCW_HCURSOR));
             #endif
           }

           break;

       case WM_SETCURSOR:
           /* In help mode it is necessary to reset the cursor in response */
           /* to every WM_SETCURSOR message.Otherwise, by default, Windows */
           /* will reset the cursor to that of the window class. */

           if (bHelp) {
               SetCursor(hHelpCursor);
               break;
           }
           return (DefWindowProc(hWnd, message, wParam, lParam));

       case WM_INITMENU:
           if (bHelp) {
               SetCursor(hHelpCursor);
           }
           return (TRUE);

       case WM_ENTERIDLE:
           if ((wParam == MSGF_MENU) && (GetKeyState(VK_F1) & 0x8000)) {
               bHelp = TRUE;
               PostMessage(hWnd, WM_KEYDOWN, VK_RETURN, 0L);
           }
           break;

       case WM_DESTROY:
           WinHelp(hWnd,szHelpFileName,HELP_QUIT,0L);
           PostQuitMessage(0);
           break;

       default:
           return (DefWindowProc(hWnd, message, wParam, lParam));
   }

   return 0L;
}
#pragma warn .eff

/****************************************************************************

   FUNCTION:   About(HWND, UINT, WORD, LONG)

   PURPOSE:    Processes messages for "About" dialog box

   MESSAGES:

       WM_INITDIALOG - Initialize dialog box
       WM_COMMAND- Input received

****************************************************************************/
#pragma argsused

BOOL FAR PASCAL _export About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
       case WM_INITDIALOG:
           return (TRUE);

       case WM_COMMAND:
     if (GET_WM_COMMAND_ID(wParam, lParam) == IDOK) {
               EndDialog(hDlg, TRUE);
               return (TRUE);
           }
           break;
   }

   return (FALSE);
}


/****************************************************************************

   FUNCTION:   MakeHelpPathName

   PURPOSE:    HelpEx assumes that the .HLP help file is in the same
               directory as the HelpEx executable.This function derives
               the full path name of the help file from the path of the
               executable.

****************************************************************************/

void MakeHelpPathName(char* szFileName)
{
   char *  pcFileName;
   int     nFileNameLen;

   nFileNameLen = GetModuleFileName(hInst,szFileName,EXE_NAME_MAX_SIZE);
   pcFileName = szFileName + nFileNameLen;

   while (pcFileName > szFileName) {
       if (*pcFileName == '\\' || *pcFileName == ':') {
           *(++pcFileName) = '\0';
           break;
       }
   nFileNameLen--;
   pcFileName--;
   }

   if ((nFileNameLen+13) < EXE_NAME_MAX_SIZE) {
       lstrcat(szFileName, "helpex.hlp");
   }

   else {
       lstrcat(szFileName, "?");
   }

   return;
}
