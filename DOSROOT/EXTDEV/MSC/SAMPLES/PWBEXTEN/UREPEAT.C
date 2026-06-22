/* UREPEAT.C -- Emacs-style universal repeat function
 *
 * Copyright <C> 1992, Microsoft Corporation, All rights reserved
 * All rights reserved.
 *
 * Demonstrates the following extension functions:
 *
 *  DoMessage, DoStatusBox, ReadCmd, SetKey
 *
 * Switches:
 *
 *  Unit:2            - Numeric; initial count for URepeat
 *
 * Functions:
 *
 *  NRepeat:SHIFT+F12 - Accepts arg count or textarg: repeat <n> times
 *  URepeat:F12       - Prompt for function or macro to repeat
 *      If function is Cancel, quit
 *      else if function is Meta, toggle meta state
 *      else if function is URepeat, increment count
 *      else repeat the function or macro the specified number of
 *          times, or until it fails (returns FALSE).
 *
 */
#pragma warning( disable:4001 )  //Allow single-line comments
#pragma warning( disable:4100 )  //Allow unused arguments

#include <stdlib.h>
#include <ext.h>

static int iUnit = 2;
char szURepeat[] = "URepeat";
char szNRepeat[] = "NRepeat";

static buffer temp; //common buffer

void _cdecl EXTERNAL WhenLoaded( void );

PWBFUNC URepeat( unsigned int argData, ARG far * pArg, flagType fMeta );
PWBFUNC NRepeat( unsigned int argData, ARG far * pArg, flagType fMeta );


// URepeat - universal repeat prefix function
//
// Purpose:
//  Repeat the subsequent command according to the number of
//  times the universal repeat prefix is executed.
//
// Future Enhancement:
//  Re-create current argument (arg count, selection ) for each repetition.
//

PWBFUNC URepeat( unsigned int argData, ARG far * pArg, flagType fMeta )
{
    PCMD pcmd;
    int count = iUnit;
    static char Prompt[] = "URepeat:";
    static char szCount[15];

    do {
        farstrcpy( temp, Prompt );
        itoa( count, szCount, 10 );
        farstradd( temp, szCount );

        DoMessage( temp );

        pcmd = ReadCmd();
        if( farstricmp( pcmd->name, "cancel" ) == 0 )
        {
            DoMessage( NULL );
            return FALSE;
        }
        else
        if( farstricmp( pcmd->name, "meta" ) == 0 )
            fMeta = (flagType)!fMeta;
        else
            count <<= 1;
    } while( farstricmp( pcmd->name, szURepeat ) == 0 );

    while( count-- )
    {
        if( fMeta ) fExecute( "Meta" );
        if( !fExecute( pcmd->name ) )
        {
            DoMessage( NULL );
            return FALSE;
        }
    }

    DoMessage( NULL );
    return TRUE;
}


//  NRepeat - Repeat next command <n> times
//
// Input:
//
//  NOARG:   Prompt for repeat count
//  NULLARG: Repeat for Arg count
//  TEXTARG: Repeat for specified count
//
PWBFUNC NRepeat( unsigned int argData, ARG far * pArg, flagType fMeta )
{
    unsigned count;
    static char szCount[15];
    PCMD pcmd;

    switch( pArg->argType )
    {
    case NOARG:
        farstrcpy( temp, "4" );
        if( GetString( temp, "Repeat Count:", TRUE ) )
            return FALSE;
        count = atou( temp );
        break;

    case NULLARG:
        count = pArg->arg.nullarg.cArg;
        break;

    case TEXTARG:
        count = atou( pArg->arg.textarg.pText );
        if( count == 0 )
            return BadArg();
        break;

    default:
        return BadArg();
        break;
    }
    for(;;)
    {
        farstrcpy( temp, "NRepeat:" );
        itoa( count, szCount, 10 );
        farstradd( temp, szCount );
        DoMessage( temp );

        pcmd = ReadCmd();
        if( farstricmp( pcmd->name, "cancel" ) == 0 )
        {
            DoMessage( NULL );
            return FALSE;
        }
        else
        if( farstricmp( pcmd->name, "meta" ) == 0 )
            fMeta = (flagType)!fMeta;
        else
            break;
    }

    while( count-- )
    {
        if( fMeta ) fExecute( "Meta" );
        if( !fExecute( pcmd->name ) )
        {
            DoMessage( NULL );
            return FALSE;
        }
    }
    return TRUE;

}

//-------------------< Standard Extension Information >--------------------

void _cdecl EXTERNAL WhenLoaded( void )
{
    DoStatusBox( "Universal Repeat Extension", NULL );

    SetKey( szURepeat, "F12" );
    SetKey( szNRepeat, "SHIFT+F12" );

    DoStatusBox( NULL, NULL );
}

//
// Command description table.
//
struct cmdDesc  cmdTable[] =
{
    {szURepeat, URepeat, 0, CURSORFUNC|KEEPMETA|ICONFOCUS|NOWINDOWS },
    {szNRepeat, NRepeat, 0, NOARG|NULLARG|TEXTARG|ICONFOCUS|NOWINDOWS },
    { NULL, NULL, 0, 0 }
};

//
// Switch description table.
//
struct swiDesc swiTable[] =
{
    { "Unit", toPIF(iUnit), SWI_NUMERIC|RADIX10 },
    { NULL, NULL, 0 }
};
