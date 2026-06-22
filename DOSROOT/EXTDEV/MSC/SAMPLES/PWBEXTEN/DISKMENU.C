/* DISKMENU.C - Disk menu: multifile open, touch, delete
 *
 * Copyright <C> 1992, Microsoft Corporation, All rights reserved
 * All rights reserved.
 *
 * Demonstrates the following extension functions:
 *
 * IdAddPwbMenuItem     IdFindPwbMenuItem   DoMessageBox    DoStatusBox
 * fExecute             FileNameToHandle    FindSwitch      ForFile
 * fSetWindowWithFile   GetLine             GetListHandle   GetPfileFromName
 * ScanList             SelectFiles
 *
 * Switches: None
 *
 * Functions:
 *
 *  See each function's header comment for the details on the arguments
 *  accepted by each.
 *
 *  OpenFiles        Open multiple files
 *  TouchFiles       Touch files (set file modification time to current time
 *                   and date)
 *  DeleteFiles      Delete files
 *
 * Macros:
 *
 *  Macro            Menu Command
 *  ---------------  -----------------
 *  DiskOpenFiles    Disk.Open Files
 *  DiskDeleteFiles  Disk.Delete Files
 *  DiskTouchFiles   Disk.Touch Files
 *
 * Special Macros (similar to Mgreplist):
 *
 *  Mopenlist        List of files to open
 *  Mdellist         List of files to delete
 *  Mtouchlist       List of files to touch
 *
 */

#pragma warning( disable:4001 )  //Allow single-line comments
#pragma warning( disable:4100 )  //Allow unused arguments

#include <dos.h>
#include <string.h>
#include "ext.h"

//  Special macros
//
static char *szOpenList  = "Mopenlist";
static char *szTouchList = "Mtouchlist";
static char *szDelList   = "Mdellist";

//  fExecute strings to define the Disk menu's macros
//
static char *DefineDiskOpenFiles   = "arg \"DiskOpenFiles:=cancel OpenFiles <\" assign";
static char *DefineDiskTouchFiles  = "arg \"DiskTouchFiles:=cancel TouchFiles <\" assign";
static char *DefineDiskDeleteFiles = "arg \"DiskDeleteFiles:=cancel meta DeleteFiles <\" assign";

//  Miscellaneous strings
static char *Banner    = "Multifile Example Extension";
static char *ReadOnly  = "File is read-only";
static char *QContinue = "Continue?";


void _cdecl EXTERNAL WhenLoaded( void );

//
//  Exported functions
//

PWBFUNC OpenFiles  ( unsigned argData, ARG far *pArg, flagType fMeta );
PWBFUNC TouchFiles ( unsigned argData, ARG far *pArg, flagType fMeta );
PWBFUNC DeleteFiles( unsigned argData, ARG far *pArg, flagType fMeta );

//
//  Local functions
//

//  Void-return shells for ForFile
void __pascal EXPORT DoTouchFile ( char far *FileName );
void __pascal EXPORT DoDeleteFile( char far *FileName );
void __pascal EXPORT DoOpenFile  ( char far *FileName );

flagType DoOpenFilesBox  ( void );
flagType DoTouchFilesBox ( flagType fConfirm );
flagType DoDeleteFilesBox( flagType fConfirm );

flagType TouchFile( char far *FileName );
flagType __pascal DeleteFile( char far *FileName );

char far *ParseFileName( LINE y, COL x );

//  Low-level DOS file functions
//
//  Some of these simulate _dos_... functions from DOS.H, that cannot be
//  used in an extension
//
unsigned __pascal DOSGetCurDate( void );
unsigned __pascal DOSGetCurTime( void );
unsigned __pascal DOSGetFileAttr( char far *FileName, unsigned * attrib );
unsigned __pascal DOSOpenFile( char far *FileName, BYTE flags, int *iFile );
unsigned __pascal DOSCloseFile( int iFile );
unsigned __pascal DOSSetFileTime( int iFile, unsigned date, unsigned time );


//--------------------------<  Implementations  >------------------------//

//  DOSGetCurDate - Get current DOS date
//
//  Returns the current DOS date in packed format
//
unsigned __pascal DOSGetCurDate( void )
{
    unsigned rv;
    _asm
    {
        mov ah, 2ah
        int 21h
        sub cx, 1980
#ifdef _M_I8086
        shl cx, 1
        shl cx, 1
        shl cx, 1
        shl cx, 1
        shl cx, 1
        shl cx, 1
        shl cx, 1
        shl cx, 1
        shl cx, 1
#else
        shl cx, 9
#endif
        or  cl, dl
#ifdef _M_I8086
        shl dh, 1
        shl dh, 1
        shl dh, 1
        shl dh, 1
        shl dh, 1
#else
        shl dh, 5
#endif
        or  cl, dh
        mov rv, cx
    }
    return rv;
}

//  DOSGetCurTime - Get current DOS time
//
//  Returns the current DOS time in packed format
//

unsigned __pascal DOSGetCurTime( void )
{
    unsigned rv;
    __asm
    {
        mov ah, 0x2c
        int 21h
        xor ax, ax
        mov al, ch
#ifdef _M_I8086
        mov cl, 11
        shl ax, cl
#else
        shl ax, 11
#endif
#ifdef _M_I8086
        mov cl, 5
        shl dh, cl
#else
        shl dh, 5
#endif
        or  al, dh
        mov rv, ax
    }
    return rv;
}

//  DOSGetFileAttr - Get a file's attributes
//
//  simulate _dos_getfileattr
//

unsigned __pascal DOSGetFileAttr( char far *FileName, unsigned *attrib )
{
    BYTE cflag = 0;
    unsigned status;
    unsigned offName = _FP_OFF(FileName);
    unsigned segName = _FP_SEG(FileName);

    // Int 21, Function 43h: Get file attributes
    __asm
    {
        push ds
        mov ah, 43h
        mov al, 0
        mov dx, offName
        mov ds, segName
        int 21h
        pop ds
        jc  Error
        mov status, cx
        jmp end_block

    Error:
        mov status, ax
        mov cflag, 1

    end_block:
    }
    if( cflag )
        return status;
    else
    {
        *attrib = status;
        return 0;
    }
}

//  DOSOpenFile - Open specified file, return file handle
//
//  simulate _dos_open
//

unsigned __pascal DOSOpenFile( char far *FileName, BYTE flags, int *iFile )
{
    unsigned status;
    BYTE cflag = 0;
    unsigned offName = _FP_OFF(FileName);
    unsigned segName = _FP_SEG(FileName);

    // Int 21, Function 3dh: Open file handle
    __asm
    {
        push ds
        mov ah, 3dh
        mov al, flags
        mov dx, offName
        mov ds, segName
        int 21h
        pop ds
        mov status, ax
        jnc end_block
        mov cflag, 1
    end_block:
    }

    if( cflag )
        return status;
    else
    {
        *iFile = status;
        return 0;
    }

}

//  DOSCloseFile - Close file specified by handle
//
//  simulate _dos_close
//
unsigned __pascal DOSCloseFile( int iFile )
{
    int status;
    BYTE cflag = 0;

    // Int 21, Function 3eh: Close file handle
    __asm
    {
        mov ah, 0x3e
        mov bx, iFile
        int 21h
        jnc end_block
        mov status, ax
        mov cflag, 1
    end_block:
    }

    if( cflag )
        return status;
    else
        return 0;
}

//  DOSSetFileTime - Set file's timestamp
//
//  simulate _dos_setftime
//

unsigned __pascal DOSSetFileTime( int iFile, unsigned date, unsigned time )
{
    unsigned status;
    BYTE cflag = 0;

    // Int 21, Function 57h: Set file date/time
    __asm
    {
        mov ah, 57h
        mov al, 01h
        mov bx, iFile
        mov cx, time
        mov dx, date
        int 21h
        jnc end_block
        mov cflag, 1
        mov status, ax
    end_block:
    }

    if( cflag )
        return status;
    else
        return 0;

}

//  Shell for ForFile
void __pascal EXPORT DoTouchFile( char far *FileName )
{
    TouchFile( FileName );
}

//  TouchFile - Change modification date of file to the current time
//
//  Returns:
//  TRUE    File touched
//  FALSE   Error
//

flagType TouchFile( char far *FileName )
{
    unsigned attrib;
    unsigned date;
    unsigned time;
    int ifile;

    if( DOSGetFileAttr( FileName, &attrib) )
        return FALSE;

    if( attrib & _A_RDONLY )
    {
        DoMessageBox( "Can't touch", FileName, ReadOnly, MBOX_OK|MBOX_BEEP|MBOX_NOHELP, 0 );
        return FALSE;
    }

    if( attrib & (_A_SUBDIR|_A_VOLID|_A_SYSTEM) )
    {
        DoMessageBox( "Can't touch", FileName, "File is a directory or system file", MBOX_OK|MBOX_BEEP|MBOX_NOHELP, 0 );
        return FALSE;
    }

    if( DOSOpenFile( FileName, 0x0002, &ifile ) )
    {
        DoMessageBox( "Can't touch", FileName, "Can't open file", MBOX_OK|MBOX_BEEP|MBOX_NOHELP, 0 );
        return FALSE;
    }

    date = DOSGetCurDate();
    time = DOSGetCurTime();
    DOSSetFileTime( ifile, date, time );
    DOSCloseFile( ifile );

    return TRUE;

}

//  Shell for ForFile
void __pascal EXPORT DoDeleteFile( char far *FileName )
{
    DeleteFile( FileName );
}

//  DeleteFile - Delete the specified file from disk
//
//  Returns:
//  TRUE    File deleted
//  FALSE   File not deleted
//

flagType __pascal DeleteFile( char far *FileName )
{
    static char msgErr[] = "Can't delete";

    unsigned attrib;
    unsigned status;
    unsigned offName;
    unsigned segName;
    flagType fError = FALSE;
    BYTE Function;

    if( DOSGetFileAttr( FileName, &attrib) )
        return FALSE;
    if( attrib & _A_RDONLY )
    {
        DoMessageBox( msgErr, FileName, ReadOnly, MBOX_OK|MBOX_BEEP|MBOX_NOHELP, 0 );
        return FALSE;
    }
    if( attrib & (_A_VOLID|_A_SYSTEM) )
    {
        DoMessageBox( msgErr, FileName, "File is a volume ID or system file", MBOX_OK|MBOX_BEEP|MBOX_NOHELP, 0 );
        return FALSE;
    }
    offName = _FP_OFF(FileName);
    segName = _FP_SEG(FileName);
    if( attrib & _A_SUBDIR )
        Function = 0x3a; //Function 3ah -- remove directory
    else
        Function = 0x41; //Function 41h -- delete file
    __asm
    {
        mov ah, Function
        mov dx, offName
        mov ds, segName
        int 21h
        jnc end_block
        mov fError, 1
        mov status, ax
    end_block:
    }

    if( fError )   //error
    {
        switch( status )
        {
        case 0x02:
        case 0x03:
            DoMessageBox( msgErr, FileName, "File not found", MBOX_OK|MBOX_BEEP|MBOX_NOHELP, 0 );
            return FALSE;

        case 0x05:
            DoMessageBox( msgErr, FileName, "Access denied", MBOX_OK|MBOX_BEEP|MBOX_NOHELP, 0 );
            return FALSE;

        case 0x10:
            if( Function == 0x3a )
            {
                DoMessageBox( msgErr, FileName, "Directory is the current directory", MBOX_OK|MBOX_BEEP|MBOX_NOHELP, 0 );
                return FALSE;
            }
            //else fall through
        default:
            DoMessageBox( msgErr, FileName, NULL, MBOX_OK|MBOX_BEEP|MBOX_NOHELP, 0 );
            return FALSE;
        }
    }

    return TRUE;
}


//  ParseFileName - Parse filename or wildcard at cursor
//
//  Return NULL on failure, else pointer to filename
//
char far *ParseFileName( LINE y, COL x )
{
    static buffer temp;
    static char *FileChars =
        ":\\abcdefghijklmnopqrstuvwxyz0123456789.*?`~!@#$%^-_=/',[]{}()";

    PFILE pfile;
    char far *FileName;
    char far *FileNameEnd;

    if( (pfile = FileNameToHandle( NULL, NULL )) == PNULL )
    {
        //no file
        bell();
        return NULL;
    }

    //  Parse filename or wildcard at cursor
    //
    GetLine( y, temp, pfile );
    FileName = temp + x;

    //  Trim to the longest span of legal characters
    farstrlwr( FileName );
    FileNameEnd = FileName + _fstrspn( FileName, FileChars );
    if( FileNameEnd )
        *FileNameEnd = '\0';
    return FileName;

}

//  Shell for ForFile

void __pascal EXPORT DoOpenFile( char far *FileName )
{
    fSetWindowWithFile( FileName );
}

//  DoOpenFilesBox - Display the Open Files dialog box
//
flagType DoOpenFilesBox( void )
{
    PCMD FileList;
    char far *FileName;
    flagType ret = TRUE;

    FileList = GetListHandle( szOpenList, TRUE );
    if( !SelectFiles( FileList, "Open Files", "Selected Files to ~Open",
                      "*.*", FALSE, 0 ) )
        return FALSE;
    FileName = ScanList( FileList, TRUE );
    while( FileName != NULL )
    {
        if( farstrchr( FileName, '*' ) || farstrchr( FileName, '?' ) )
        {
            //wildcard
            if( !ForFile( FileName, FORFILE_ALL, DoOpenFile ) )
                ret = FALSE;
        }
        else
            fSetWindowWithFile( FileName );
        FileName = ScanList( PNULL, TRUE );
    }

    return ret;

}

//  DoTouchFilesBox - Display the Touch Files dialog box
//

flagType DoTouchFilesBox( flagType fConfirm )
{
    PCMD FileList;
    char far *FileName;
    flagType ret = TRUE;

    FileList = GetListHandle( szTouchList, TRUE );
    if( !SelectFiles( FileList, "Touch Files", "~Selected Files to Touch",
                 "*.*", FALSE, 0 ) )
        return FALSE;
    FileName = ScanList( FileList, TRUE );
    while( FileName != NULL )
    {
        if( fConfirm )
        {
            switch( DoMessageBox( "About to touch file:", FileName,
                                  "Are you sure you want to touch it?",
                                  MBOX_YESNOCANCEL|MBOX_NOHELP, 0 ) )
            {
            case MBOX_IDYES:    break;
            case MBOX_IDNO:     FileName = ScanList( PNULL, TRUE );
                                continue;
            case MBOX_IDCANCEL: return FALSE;
            }
        }
        if( farstrchr( FileName, '*' ) || farstrchr( FileName, '?' ) )
        {
            //wildcard
            if( !ForFile( FileName, FORFILE_ALL, DoTouchFile ) )
                ret = FALSE;
        }
        else
        if( !TouchFile( FileName ) )
        {
            if( DoMessageBox( "Can't touch file:", FileName,
                              "Continue processing list?",
                              MBOX_YESNO|MBOX_BEEP|MBOX_NOHELP, 0 )
                == MBOX_IDNO )
                return FALSE;
        }
        FileName = ScanList( PNULL, TRUE );
    }

    return ret;

}

//  DoDeleteFilesBox - Display the Delete Files dialog box
//

flagType DoDeleteFilesBox( flagType fConfirm )
{
    PCMD FileList;
    char far *FileName;
    flagType ret = TRUE;

    FileList = GetListHandle( szDelList, TRUE );
    if( !SelectFiles( FileList, "Delete Files", "~Selected Files to Delete",
                 "*.*", FALSE, 0 ) )
        return FALSE;
    FileName = ScanList( FileList, TRUE );
    while( FileName != NULL )
    {
        if( fConfirm )
        {
            switch( DoMessageBox( "About to delete:", FileName,
                                  QContinue,
                                  MBOX_YESNOCANCEL|MBOX_NOHELP, 0 ) )
            {
            case MBOX_IDYES:    break;
            case MBOX_IDNO:     FileName = ScanList( PNULL, TRUE );
                                continue;
            case MBOX_IDCANCEL: return FALSE;
            }
        }
        if( farstrchr( FileName, '*' ) || farstrchr( FileName, '?' ) )
        {
            //wildcard
            if( !ForFile( FileName, FORFILE_ALL, DoDeleteFile ) )
                ret = FALSE;
        }
        else
        if( !DeleteFile( FileName ) )
        {
            if( DoMessageBox( "Can't delete file:", FileName,
                              "Continue processing list?",
                              MBOX_YESNO|MBOX_BEEP|MBOX_NOHELP, 0 )
                == MBOX_IDNO )
                return FALSE;
        }
        FileName = ScanList( PNULL, TRUE );
    }

    return ret;

}

//------------------------<  Exported Functions  >-----------------------//

// OpenFiles - Open multiple files
//
// Input:
//  No args              - Display Open Files dialog box
//  Meta                 - Toggle NewWindow switch
//  Arg                  - Parse name at cursor
//  textarg              - Open specified files(s)
//  stream, one-line-box - Open selected file(s)
//
// Output:
//      TRUE : All specified files opened
//      FALSE: At least one file was not opened
//
PWBFUNC OpenFiles( unsigned argData, ARG far *pArg, flagType fMeta )
{
    char far *FileName = NULL;
    flagType ret = TRUE;
    flagType NewWindow;
    PSWI pswi;
    static char *ChangeSwitch1 = "arg \"newwindow:";
    static char *ChangeSwitch2 = "\" assign";
    static char ChangeSwitch[25];

    if( fMeta ) //Toggle NewWindow switch
    {
        pswi = FindSwitch( "newwindow" );
        NewWindow = *(pswi->act.fval);
        farstrcpy( ChangeSwitch, ChangeSwitch1 );
        farstrcat( ChangeSwitch, NewWindow ? "0" : "1" );
        farstrcat( ChangeSwitch, ChangeSwitch2 );
        fExecute( ChangeSwitch );
        //  Build string to restore NewWindow
        farstrcpy( ChangeSwitch, ChangeSwitch1 );
        farstrcat( ChangeSwitch, NewWindow ? "1" : "0" );
        farstrcat( ChangeSwitch, ChangeSwitch2 );
    }

    switch( pArg->argType )
    {
    case NOARG:
        ret = DoOpenFilesBox();
        //  Restore NewWindow if toggled
        if( fMeta )
            fExecute( ChangeSwitch );
        if( !ret )
            bell();
        return ret;
        break;

    case NULLARG:
        FileName = ParseFileName( pArg->arg.nullarg.y, pArg->arg.nullarg.x );
        break;

    case TEXTARG:
        FileName = pArg->arg.textarg.pText;
        break;

    }

    if( farstrchr( FileName, '*' ) || farstrchr( FileName, '?' ) )
    {
        //wildcard
        if( !ForFile( FileName, FORFILE_ALL, DoOpenFile ) )
            ret = FALSE;
    }
    else
        fSetWindowWithFile( FileName );

    //  Restore NewWindow if toggled
    if( fMeta )
        fExecute( ChangeSwitch );
    bell();
    return ret;

}

// TouchFiles - Change modification date of file or wildcard files
//
// Input:
//  No args              - Display Touch Files dialog box
//  Meta                 - Confirm at each file or wildcard
//  Arg                  - Parse name at cursor
//  textarg              - Touch specified file or wildcard
//  stream, one-line-box - Touch selected file or wildcard
//
// Output:
//      TRUE : All specified files opened
//      FALSE: At least one file was not opened
//

PWBFUNC TouchFiles( unsigned argData, ARG far *pArg, flagType fMeta )
{
    char far *FileName = NULL;

    switch( pArg->argType )
    {
    case NOARG:
        return DoTouchFilesBox( fMeta );

    case NULLARG:
        FileName = ParseFileName( pArg->arg.nullarg.y, pArg->arg.nullarg.x );
        break;

    case TEXTARG:
        FileName = pArg->arg.textarg.pText;

    }

    if( fMeta )
    {
        if( DoMessageBox( "About to Touch file:", FileName, QContinue,
                          MBOX_YESNO|MBOX_NOHELP, 0 )
            == MBOX_IDNO )
            return FALSE;
    }
    if( farstrchr( FileName, '*' ) || farstrchr( FileName, '?' ) )
    {
        //wildcard
        if( !ForFile( FileName, FORFILE_ALL, DoTouchFile ) )
            return FALSE;
    }
    else
        return TouchFile( FileName );

}


// DeleteFiles - Delete file, directory, or wildcard
//
// Input:
//  No arg               - Display Delete Files dialog box
//  Meta                 - Confirm at each file or wildcard
//  Arg                  - Parse name at cursor
//  textarg              - Delete specified file or wildcard
//  stream, one-line-box - Delete selected file or wildcard
//
// Output:
//      TRUE : All specified files deleted
//      FALSE: At least one file was not deleted
//

PWBFUNC DeleteFiles( unsigned argData, ARG far *pArg, flagType fMeta )
{
    char far *FileName = NULL;
    flagType ret = TRUE;

    switch( pArg->argType )
    {
    case NOARG:
        ret = DoDeleteFilesBox( fMeta );
        return ret;

    case NULLARG:
        FileName = ParseFileName( pArg->arg.nullarg.y, pArg->arg.nullarg.x );
        break;

    case TEXTARG:
        FileName = pArg->arg.textarg.pText;
        break;
    }
    if( fMeta )
    {
        if( DoMessageBox( "About to delete:", FileName, QContinue,
                          MBOX_YESNO|MBOX_NOHELP, 0 )
            == MBOX_IDNO )
            return FALSE;
    }
    if( farstrchr( FileName, '*' ) || farstrchr( FileName, '?' ) )
    {
        //wildcard
        if( !ForFile( FileName, FORFILE_ALL, DoDeleteFile ) )
            ret = FALSE;
    }
    else
        ret = DeleteFile( FileName );

    return ret;
}


//-----------------< Standard Extension Information >----------------//

// WhenLoaded
//
//
//
//
void _cdecl EXTERNAL WhenLoaded( void )
{
    WORD idEditMenu;
    WORD idDiskMenu;

    DoStatusBox( Banner, NULL );

    //Initialize extension

    //  Define macros for menus
    fExecute( DefineDiskOpenFiles   );
    fExecute( DefineDiskDeleteFiles );
    fExecute( DefineDiskTouchFiles  );

    //  Add Disk menu
    idEditMenu = IdFindPwbMenuItem( "~Edit", 0, FALSE );
    if( (idDiskMenu = IdAddPwbMenuItem(
                      TM_ENABLED|TM_UNCHECKED|TM_SUBMENU|TM_NORECORD,
                      0, idEditMenu,
                      "~Disk",
                      "Disk operations menu", NULL, NULL )
        ) == 0 )
    {
        DoStatusBox( NULL, NULL );   //Close status box
        DoMessageBox( Banner, "Can't add Disk menu!", NULL, MBOX_OK|MBOX_NOHELP|MBOX_CAPTION, 0 );
        return;
    }

    //  Assume that once there is a Disk menu, none of the other items
    //  will fail to add.

    //  Open Files...
    IdAddPwbMenuItem( TM_ENABLED|TM_COMMAND, idDiskMenu, 0,
                      "~Open Files...",
                      "Open multiple files", NULL,
                      "DiskOpenFiles" );
    //  Touch Files...
    IdAddPwbMenuItem( TM_ENABLED|TM_COMMAND, idDiskMenu, 0,
                      "~Touch Files...",
                      "Touch multiple files", NULL,
                      "DiskTouchFiles" );
    //  separator bar
    IdAddPwbMenuItem( TM_SEPARATOR|TM_NORECORD, idDiskMenu, 0, NULL, NULL, NULL, NULL );

    //  Delete Files...
    IdAddPwbMenuItem( TM_ENABLED|TM_COMMAND, idDiskMenu, 0,
                      "~Delete Files...",
                      "Delete multiple files", NULL,
                      "DiskDeleteFiles" );

    DoStatusBox( NULL, NULL );   //Close status box

}

//
// Command description table.
//
struct cmdDesc cmdTable[] =
{
    { "OpenFiles",   OpenFiles,   0, NOARG|NULLARG|TEXTARG|BOXSTR|NOWINDOWS|ICONFOCUS },
    { "TouchFiles",  TouchFiles,  0, NOARG|NULLARG|TEXTARG|BOXSTR|NOWINDOWS|ICONFOCUS },
    { "DeleteFiles", DeleteFiles, 0, NOARG|NULLARG|TEXTARG|BOXSTR|NOWINDOWS|ICONFOCUS },
    { NULL, NULL, 0, 0 } //end-of-table
};

//
// Switch description table.
//
struct swiDesc swiTable[] = { { NULL, NULL, 0 } };
