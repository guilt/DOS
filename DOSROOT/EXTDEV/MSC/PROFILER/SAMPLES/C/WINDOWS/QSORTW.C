/*
 * QSORTW.C
 *
 * This program is described in Chapters 2 and 3 of the Microsoft Source
 * Profiler User's Guide.
 */

#include <WINDOWS.H>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qsortw.h"

HWND        hWnd1;
WNDCLASS    rClass;
char        szInFile[_MAX_PATH];
char        szOutFile[_MAX_PATH];

/*
 * WinMain:
 *     Parameters:
 *         hInstance     - Handle to current Data Segment
 *         hPrevInstance - Handle to previous Data Segment (NULL if none)
 *         lpszCmdLine   - Long pointer to command line info
 *         nCmdShow      - Integer value specifying how to start program
 *                            (Iconic [7] or Normal [1,5])
 */
int PASCAL WinMain (HANDLE hInstance,
		    HANDLE hPrevInstance,
		    LPSTR  lpszCmdLine,
		    int    nCmdShow)
{
int nReturn;

    if (Init(hInstance, hPrevInstance,lpszCmdLine,nCmdShow))
    {
	nReturn = DoMain(hInstance);
    }
    return nReturn;
}

/*
 * Init
 *     Initialization for the program is done here:
 *     1)  Register the window class (if this is the first instance)
 *     2)  Create the desktop window for the app.
 *     3)  Show the desktop window in the manner requested by the User.
 *
 */
BOOL Init(HANDLE hInstance,   HANDLE hPrevInstance,
	  LPSTR  lpszCmdLine, int    nCmdShow) 
{

    if (!hPrevInstance)
    {
	/*  Register Class for First Overlapped Window  */
	rClass.lpszClassName = "OVERLAPPED:1";
	rClass.hInstance     = hInstance;
	rClass.lpfnWndProc   = OverlappedWindowProc1;
	rClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	rClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	rClass.lpszMenuName  = "SORTMENU";
	rClass.hbrBackground = GetStockObject(WHITE_BRUSH);
	rClass.style         = 0L;
	rClass.cbClsExtra    = 0;
	rClass.cbWndExtra    = 0;

	if (!RegisterClass( &rClass))
	    return FALSE;
    }

    hWnd1 = CreateWindow("OVERLAPPED:1",
	    "Microsoft QSORT for Windows",
	    WS_OVERLAPPEDWINDOW,
	    CW_USEDEFAULT,
	    CW_USEDEFAULT,
	    CW_USEDEFAULT,
	    CW_USEDEFAULT,
	    NULL,
	    NULL,
	    hInstance,
	    NULL);

    ShowWindow(hWnd1,nCmdShow);

    return hWnd1;
}

/*
 * DoMain:
 *     This is the main loop for the application, often called the message
 *     pump.
 */
int  DoMain(HANDLE hInstance)
{
MSG msg;

    while (GetMessage(&msg,NULL,0,0))
    {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }
    return msg.wParam;
}

/* OverlappedWindowProc1 - Handles messages for the main QSORT window.
 *     Parameters:
 *         hWnd    - Handle to Window which message is delivered to.
 *         msgID   - ID number of message
 *         wParam  - 16-bit parameter
 *         lParam  - 32-bit parameter
 *
 */
long _export FAR PASCAL OverlappedWindowProc1 (HWND     hWnd,
				       unsigned wMsgID,
				       unsigned wParam,
				       LONG     lParam)
{
FARPROC lpfnDlgProc;
unsigned    idEnd;

    switch (wMsgID)
    {

    case WM_DESTROY:
	PostQuitMessage(0);
	break;

    case WM_COMMAND:

	switch(wParam) {

	    case IDM_EXIT:
		PostMessage(hWnd,WM_CLOSE,0,0L);
		break;

	    case IDM_SORT:

		lpfnDlgProc = MakeProcInstance((FARPROC) GetIOFiles, rClass.hInstance);
		if(lpfnDlgProc) {

		    /* Ask for the input and output files */
		    idEnd = DialogBox(rClass.hInstance,
				"GETFILE",
				hWnd,
				lpfnDlgProc);
		    FreeProcInstance(lpfnDlgProc);

		    if( idEnd == IDOK )
			SortMain (szInFile, szOutFile, hWnd);
		    }
		break;
	    }
	break;

    default:
	return DefWindowProc(hWnd, wMsgID, wParam, lParam);
    }

return 0;
}

int _export FAR PASCAL GetIOFiles(
HWND  hDlg,
WORD  wMsg,
WORD  wParam,
DWORD lParam
)

{

switch(wMsg) {

    case WM_INITDIALOG:
	szInFile[0] = '\0';
	szOutFile[0] = '\0';
	SetFocus(hDlg);
	break;

    case WM_COMMAND:

	switch(wParam) {

	    // copy the string to the buffer originally pointed to by lParam
	    case IDOK:
		GetDlgItemText(hDlg, ID_IN_EDIT, szInFile, sizeof(szInFile));
		GetDlgItemText(hDlg, ID_OUT_EDIT, szOutFile, sizeof(szOutFile));
		EndDialog(hDlg, IDOK);
		return(TRUE);
		break;

	    case IDCANCEL:
		EndDialog(hDlg, IDCANCEL);
		return(TRUE);
		break;
	    }
	break;
    }

return(FALSE);
}

int _export FAR PASCAL StubDlgProc(
HWND  hDlg,
WORD  wMsg,
WORD  wParam,
DWORD lParam
) {

switch(wMsg) {

    case WM_INITDIALOG:
	return(TRUE);
	break;
    }

return(FALSE);
}


/*
 * SortMain
 *
 * This function is equivalent to the main function of QSORT.C
 *
 */

void SortMain (char * szIn, char * szOut, HANDLE hWnd)
{
    int NumWords;
    int index;
    HWND    hWndDlg;
    FARPROC lpfnDlgProc;

    /* loading the file */
    hWndDlg = NULL;
    lpfnDlgProc = MakeProcInstance((FARPROC) StubDlgProc, rClass.hInstance);
    if(lpfnDlgProc) {

	/* Ask for the input and output files */
	hWndDlg = CreateDialog(rClass.hInstance,
		    "LOADING",
		    hWnd,
		    lpfnDlgProc);
	}

    NumWords = GetWords( szIn );

    /* end load */
    if(hWndDlg)
	DestroyWindow(hWndDlg);
    if(lpfnDlgProc)
	FreeProcInstance(lpfnDlgProc);

    /* Initialize WordIndex array */
    for ( index = 0; index < NumWords; index++ )
	WordIndex[index] = index;
    if ( NumWords > 0 )
    {
	/* sorting the file */
	hWndDlg = NULL;
	lpfnDlgProc = MakeProcInstance((FARPROC) StubDlgProc, rClass.hInstance);
	if(lpfnDlgProc) {

	    /* Ask for the input and output files */
	    hWndDlg = CreateDialog(rClass.hInstance,
			"SORTING",
			hWnd,
			lpfnDlgProc);
	    }

	QuickSort( 0, NumWords-1 );
	OutWords( NumWords, szOut );

	/* end sort */
	if(hWndDlg)
	    DestroyWindow(hWndDlg);
	if(lpfnDlgProc)
	    FreeProcInstance(lpfnDlgProc);
    }
}

/* GetWords - GetWords loads and parses an ASCII text file and stores each
 * word into WordArray. Returns the number of words read.
 */
int GetWords(char *filename)
{
    FILE    *FileHandle;
    int     WordNumber = 0;
    int     CharNumber = 0;
    char    TempChar   = '\0';

    FileHandle = fopen(filename, "r");
    if (FileHandle == NULL)
	{
	MessageBox(hWnd1, (char far *) "Error opening input file.",
		      (char far *) "Error", MB_ICONSTOP | MB_OK);
	return 0;
	}

    while ((WordNumber < MAXNUMWORDS) && (TempChar != EOF))
    {
	TempChar = fgetc(FileHandle);
	switch(TempChar)
	{
	    /* Word delimiters */
	    case ' ' :
	    case '\n':
	    case '\t':
		/* Start new word unless at beginning */
		if (CharNumber != 0)
		{
		    WordArray[WordNumber][CharNumber] = '\0';
		    CharNumber = 0;
		    WordNumber++;
		}
		break;
	    /* Quit if at end of file */
	    case EOF:
		break;
	    /* Characters to add to word */
	    default:
		WordArray[WordNumber][CharNumber] = TempChar;
		/* Truncate word if too long */
		if (++CharNumber >= MAXWORDSIZE)
		{
		    WordArray[WordNumber][CharNumber-1] = '\0';
		    CharNumber = 0;
		    WordNumber++;
		    /* Skip over remaining characters */
		    while ((TempChar != ' ') && (TempChar != '\n') &&
			   (TempChar != '\t'))
			 TempChar = fgetc(FileHandle);
		}
		break;
	}
    }
    fclose( FileHandle );
    return  WordNumber;
}

/* QuickSort - QuickSort works by picking a random "pivot" element,
 * then moving every element that is bigger to one side of the pivot,
 * and every element that is smaller to the other side. QuickSort is
 * then called recursively with the two subdivisions created by the pivot.
 * Once the number of elements in a subdivision reaches two, the recursive
 * calls end and the array is sorted.
 */
void QuickSort( int iLow, int iHigh )
{
    int iUp, iDown;

    char cBreak[MAXWORDSIZE];

    if( iLow < iHigh )
    {
	/* Only two elements in this subdivision; swap them if they are
	 * out of order, then end recursive calls.
	 */
	if( (iHigh - iLow) == 1 )
	{
	    if( stricmp( WordArray[WordIndex[iLow]], WordArray[WordIndex[iHigh]] ) > 0 )
		SwapWords( iLow, iHigh );
	}
	else
	{
	    /* Pick a pivot element at random, then move it to the end. */
	    SwapWords( iHigh, getrandom( iLow, iHigh ) );
	    strcpy( cBreak, WordArray[WordIndex[iHigh]] );
	    do
	    {
		/* Move in from both sides towards the pivot element. */
		iUp = iLow;
		iDown = iHigh;
		while( (iUp < iDown) &&
		       (stricmp( WordArray[WordIndex[iUp]], cBreak ) <= 0) )
			iUp++;
		while( (iDown > iUp) &&
		       (stricmp( WordArray[WordIndex[iDown]], cBreak ) >= 0) )
			iDown--;
		/* If we haven't reached the pivot, it means that two
		 * elements on either side are out of order, so swap them.
		 */
		if( iUp < iDown )
		    SwapWords( iUp, iDown );
	    } while ( iUp < iDown );

	    /* Move pivot element back to its proper place in the array. */
	    SwapWords( iUp, iHigh );

	    /* Recursively call the QuickSort procedure (pass the smaller
	     * subdivision first to use less stack space).
	     */
	    if( (iUp - iLow) < (iHigh - iUp) )
	    {
		QuickSort( iLow, iUp - 1 );
		QuickSort( iUp + 1, iHigh );
	    }
	    else
	    {
		QuickSort( iUp + 1, iHigh );
		QuickSort( iLow, iUp - 1 );
	    }
	}
    }
}


/* SwapWords - SwapWords swaps the WordIndex index values of two words,
 * thereby swapping the indexed positions of the words.
 */
void SwapWords( int index1, int index2 )
{
    int     TempIndex;
    TempIndex = WordIndex[index1];
    WordIndex[index1] = WordIndex[index2];
    WordIndex[index2] = TempIndex;
}

/* OutWords - OutWords writes the sorted array of words to a file.
 */
void OutWords(int NumWords, char *filename)
{
    FILE *FileHandle;
    int TempIndex;
    FileHandle = fopen(filename, "w");
    if (FileHandle == NULL)
	{
	MessageBox(hWnd1, (char far *) "Error opening output file.",
		      (char far *) "Error", MB_ICONSTOP | MB_OK);
	return;
	}
    for (TempIndex=0; TempIndex < NumWords; TempIndex++ )
	if ( fputs( WordArray[WordIndex[TempIndex]], FileHandle ) == EOF)
	{
	    MessageBox(hWnd1, (char far *) "Error writing output file.",
		      (char far *) "Error", MB_ICONSTOP | MB_OK);
	    break;
	}
	else
	    fputs( "\n", FileHandle );
    fclose( FileHandle );
}
