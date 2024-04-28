/* FILTER.C - PWB Filter Extension
 *
 * Copyright (C) 1985-1992, Microsoft Corporation, All rights reserved
 * All rights reserved.
 *
 * Demonstrates the following extension functions:
 *
 *  DoMessageBox, DoSpawn, DoStatusBox, FileRead, FileWrite, mgetenv
 *
 * Switches:
 *
 *  FilterCommand        - (Text) Command line for filter program
 *
 * Functions:
 *
 *  Filter:Shift+Ctrl+F  - Pass selected text through filter
 *                       - textarg: Define new filter command
 *
 * Remarks:
 *
 *  The Filter function replaces the text passed to it with text that has
 *  been run through a user-selected filter program. For example, you can
 *  use the DOS SORT command to sort blocks of text.
 *
 *  To use, select the text you want to filter and invoke the filter command
 *  with SHIFT+CTRL+F. The extension prompts you for the name of the filter
 *  program if one has not been defined. You can set the filter program by
 *  giving the new filter as a text argument, as follows::
 *
 *     ALT+A newfilter SHIFT+CTRL+F
 *
 */

#pragma warning( disable:4001 )  //Allow single-line comments
#pragma warning( disable:4100 )  //Allow unused arguments

#include <stdlib.h>         //max macro
#include <dos.h>            //FP_OFF/FP_SEG macros
#include <ext.h>

PWBFUNC Filter( unsigned argData, ARG far *pArg, flagType fMeta );

char far * pascal EXTERNAL SetFilter( char far *Text, flagType fQuery );

void _cdecl EXTERNAL WhenLoaded( void );

void DelTemp( void );
unsigned __pascal DOSDeleteFile( char far * FileName );

//
//  Global data
//
PFILE  pfileFilter    = PNULL;                    //Filter file handle
char   szFilter[]     = "Filter";
buffer FilterCommand  = "";                       //Filter command switch
char   szFilterName[] = "<FILTER>Filter Output";  //Name of pseudofile
char   szTemp1[]      = "filter1.tmp";            //1st temp file
char   szTemp2[]      = "filter2.tmp";            //2nd temp file
buffer szTemp1Path;                               //Path of temp file 1
buffer szTemp2Path;                               //Path of temp file 2
buffer buf;                                       //Work buffer


//  Filter
//
//  Replaces selected text with the same text after being run through an
//  arbitrary filter program.
//
//  Input:
//
//  NOARG       - Filter current line
//  NULLARG     - Filter current line, from cursor to end of line
//  LINEARG     - Filter range of lines
//  BOXARG      - Filter text in the selected box
//  NUMARG      - Converted to LINEARG before extension is called.
//  MARKARG     - Converted to the appropriate ARG form above before
//                extension is called.
//  TEXTARG     - Set new filter command
//
//  Returns: TRUE on successful file update, else FALSE
//

PWBFUNC Filter( unsigned argData, ARG far *pArg, flagType fMeta )
{
    int      cbLineMax;     //Max line length in filtered output
    LINE     cLines;        //Count of lines in file
    LINE     iLineCur;      //Line being read
    PFILE    pFile;         //File handle of current file
    unsigned uRCode;        //Return code from DoSpawn
    char far *TMPPath;      //TMP environment variable
    char far *pchPoke;

    // Get handle to current file and discard the contents of <FILTER>
    if( (pFile = FileNameToHandle( "", "" )) == PNULL )
        return FALSE;
    DelFile( pfileFilter );

    // Handle the special case of a TEXTARG to set the name of the filter
    // command to be used. If no filter command is specified, prompt for
    // one.

    if( pArg->argType == TEXTARG )
    {
        SetFilter( pArg->arg.textarg.pText, FALSE );
        return TRUE;
    }
    else
    if( *FilterCommand == '\0' )
    {
        farstrcpy( FilterCommand, "SORT" );
        if( GetString( FilterCommand, "Filter program to use:", TRUE ) )
            return FALSE;
    }

    //
    // Step 1, based on the argument type, copy the selected region into the
    // upper-left position of <FILTER>.
    //

    //  Handle strictly vertical BOXARG: treat it as a LINEARG.
    if( pArg->argType == BOXARG &&
        (pArg->arg.boxarg.xLeft == pArg->arg.boxarg.xRight) )
        pArg->argType = LINEARG;

    switch( pArg->argType )
    {
    case NOARG:     //Filter entire line
        CopyLine( pFile, pfileFilter,
                  pArg->arg.noarg.y, pArg->arg.noarg.y, (LINE)0 );
        break;

    case NULLARG:   //Filter to end of line
        CopyStream( pFile, pfileFilter,
                    pArg->arg.nullarg.x, pArg->arg.nullarg.y,
                    255,                 pArg->arg.nullarg.y,
                    (COL)0,              (LINE)0 );
        break;

    case LINEARG:   //Filter line range
        CopyLine( pFile, pfileFilter,
                  pArg->arg.linearg.yStart,
                  pArg->arg.linearg.yEnd,
                  (LINE)0 );
        break;

    case BOXARG:    //Filter box
        CopyBox( pFile, pfileFilter,
                 pArg->arg.boxarg.xLeft,  pArg->arg.boxarg.yTop,
                 pArg->arg.boxarg.xRight, pArg->arg.boxarg.yBottom,
                 (COL)0,                  (LINE)0 );
        break;

    }

    szTemp1Path[0] = '\0';
    szTemp2Path[0] = '\0';
    if( (TMPPath = mgetenv( "TMP" )) != NULL )
    {
        farstrcpy( szTemp1Path, TMPPath );
        if( (pchPoke = farstrchr( szTemp1Path, ';' )) != NULL )
            *pchPoke = '\0';
        else
            pchPoke = szTemp1Path + farstrlen( szTemp1Path );
        if( *--pchPoke != '\\' )
        {
            *++pchPoke = '\\';
            *++pchPoke = '\0';
        }
        farstrcpy( szTemp2Path, szTemp1Path );
    }
    farstrcat( szTemp1Path, szTemp1 );
    farstrcat( szTemp2Path, szTemp2 );

    //
    // Step 2, write the selected text to disk.
    //
    if( !FileWrite( szTemp1Path, pfileFilter ) )
    {
        DoMessageBox( szFilter, "Error writing temporary file:", szTemp1Path, MBOX_OK|MBOX_CAPTION|MBOX_NOHELP|MBOX_BEEP, 0  );
        return FALSE;
    }

    //
    // Step 3, create the command to be executed
    //
    farstrcpy( buf, FilterCommand );
    farstradd( buf, "<" );
    farstradd( buf, szTemp1Path );
    if( !DoSpawn( buf, szTemp2Path, EXTCMD_REDIR|EXTCMD_ASKERR, &uRCode ) )
    {
        DoMessageBox( szFilter, "Error executing command", NULL, MBOX_OK|MBOX_CAPTION|MBOX_NOHELP|MBOX_BEEP, 0  );
        return FALSE;
    }

    //
    // Step 4, delete the contents of <FILTER>, and replace it by reading in
    // the contents of the second temp file.
    //

    DelFile( pfileFilter );
    if( !FileRead( szTemp2Path, pfileFilter ) )
    {
        DoMessageBox( szFilter, "Error reading temporary file:", szTemp2Path, MBOX_OK|MBOX_CAPTION|MBOX_NOHELP|MBOX_BEEP, 0  );
        return FALSE;
    }

    //
    // Step 5, calculate the maximum width of the data we got back from the
    // filter. Then, based on the type of selected region, DISCARD the
    // region, and copy the contents of the filter file in the equivalent
    // selection.
    //

    cLines = FileLength( pfileFilter );
    cbLineMax = 0;
    for( iLineCur = 0; iLineCur < cLines; iLineCur++ )
        cbLineMax = max( cbLineMax, GetLine( iLineCur, buf, pfileFilter ) );

    switch( pArg->argType)
    {
    case NOARG:     //Filter entire line
        DelLine( pFile, pArg->arg.noarg.y, pArg->arg.noarg.y );
        CopyLine( pfileFilter, pFile, (LINE)0, (LINE)0, pArg->arg.noarg.y );
        break;

    case NULLARG:   //Filter to end of line
        DelStream( pFile,
                   pArg->arg.nullarg.x, pArg->arg.nullarg.y,
                   255,                 pArg->arg.nullarg.y );
        CopyStream( pfileFilter, pFile,
                    (COL)0, (LINE)0, cbLineMax, (LINE)0,
                    pArg->arg.nullarg.x, pArg->arg.nullarg.y );
        break;

    case LINEARG:   //Filter line range
        DelLine( pFile, pArg->arg.linearg.yStart, pArg->arg.linearg.yEnd );
        CopyLine( pfileFilter, pFile,
                  (LINE)0, cLines-1, pArg->arg.linearg.yStart );
        break;

    case BOXARG:    //Filter box
        DelBox( pFile,
                pArg->arg.boxarg.xLeft,  pArg->arg.boxarg.yTop,
                pArg->arg.boxarg.xRight, pArg->arg.boxarg.yBottom );
        CopyBox( pfileFilter, pFile, (COL)0, (LINE)0, cbLineMax-1, cLines-1,
                 pArg->arg.boxarg.xLeft, pArg->arg.boxarg.yTop );
        break;

    }

    //
    // Clean up: delete the temporary files we've created
    //
    DelTemp();
    return TRUE;

}

//  DOSDeleteFile - Delete a file from disk
//
//  Input: Name of file to delete
//
//  Returns:
//      0 on success
//      DOS INT 21h, function 41h error code on failure
//

unsigned __pascal DOSDeleteFile( char far * FileName )
{
    flagType fError = FALSE;
    unsigned offName = _FP_OFF(FileName);
    unsigned segName = _FP_SEG(FileName);
    unsigned status;

    __asm
    {
        mov ah, 41h
        mov dx, offName
        mov ds, segName
        int 21h
        jnc end_block
        mov fError, 1
        mov status, ax
    end_block:
    }

    if( fError ) return status;
    else         return 0;

}

//  DelTemp - Delete temporary files from disk
//

void DelTemp( void )
{
    DOSDeleteFile( szTemp1Path );
    DOSDeleteFile( szTemp2Path );
}


//  SetFilter - Sets the filter program to be used
//
//  Save the Text string as the filter command to be used by the Filter
//  function. Called either because the FilterCommand switch has been set,
//  or because Filter received a TEXTARG.
//

char far * pascal EXTERNAL SetFilter( char far *Text, flagType fQuery )
{
    if( fQuery )
        return FilterCommand;
    else
    {
        farstrcpy( FilterCommand, Text );
        return NULL;
    }
}

//-----------------< Standard Extension Information >----------------//

void _cdecl EXTERNAL WhenLoaded( void )
{
    DoStatusBox( "Text filter extension", NULL );

    pfileFilter = FileNameToHandle( szFilterName, NULL );
    if( !pfileFilter )
    {
        pfileFilter = AddFile( szFilterName );
        FileRead( szFilterName, pfileFilter );
    }
    SetKey( szFilter, "Shift+Ctrl+F" );

    DoStatusBox( NULL, NULL );
}

struct swiDesc swiTable[] =
{
    { "FilterCommand", SetFilter, SWI_EXTTEXT },
    { NULL, NULL, 0 }
};

struct cmdDesc cmdTable[] =
{
    { szFilter, Filter, 0, KEEPMETA|NOARG|BOXARG|NULLARG|LINEARG|
                           MARKARG|NUMARG|TEXTARG|MODIFIES },
    { NULL, NULL, 0, 0 }
};
