/* Header file for QSORTW.C */

/* Function definitions */
BOOL Init(HANDLE hInstance,   HANDLE hPrevInstance,
	  LPSTR  lpszCmdLine, int    CmdShow);

int  DoMain(HANDLE hInstance);
long _export FAR PASCAL OverlappedWindowProc1 (HWND     hWnd,
				       unsigned msgID,
				       unsigned wParam,
				       LONG     lParam);
int _export FAR PASCAL GetIOFiles(
				       HWND  hDlg,
				       WORD  wMsg,
				       WORD  wParam,
				       DWORD lParam);
void SortMain( char * szIn, char * szOut, HANDLE hWnd );
int  GetWords( char *filename );
void QuickSort( int iLow, int iHigh );
void SwapWords( int index1, int index2 );
void OutWords( int NumWords, char *filename );

/* Windows menu and dialog constants */
#define IDM_SORT    101
#define IDM_EXIT    102

#define ID_IN_EDIT      1101
#define ID_INPUT        1100
#define ID_OUT_EDIT     1103
#define ID_OUTPUT       1102


/* Macro to get a random integer within a specified range */
#define getrandom( min, max ) ((rand() % (int)(((max)+1) - (min))) + (min))

/* Maximum number of words to sort */
#define MAXNUMWORDS 1500
/* Maximum word length (in characters) */
#define MAXWORDSIZE 15

/* Global sort array declarations */
char WordArray[MAXNUMWORDS][MAXWORDSIZE];
int  WordIndex[MAXNUMWORDS];
