/* TWOKEY.C -- Popular two-keystroke editor sequences.
 *
 * Functions illustrated include:
 *
 *      ReadChar    DoMessage    fExecute    SetKey
 *
 */

#pragma warning( disable:4001 )  //Allow single-line comments
#pragma warning( disable:4100 )  //Allow unused arguments

#include <stdlib.h>
#include <ext.h>

void _cdecl EXTERNAL WhenLoaded( void );

PWBFUNC CtrlQ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC CtrlK( unsigned argData, ARG _far *pArg, flagType fMeta );
flagType DoSecondKey( char *table[] );

// Handle second key of sequence.
flagType DoSecondKey( char *table[] )
{
    int c;

    // Get key and clear status bar
    c = toupper( (unsigned char)ReadChar() );
    DoMessage( NULL );

    // Adjust so that CTRL+A, 'A', and 'a' are the same index.
    if( c < 27 )
        --c;
    else if( (c < 'A') || (c > 'Z') )
        return FALSE;
    else
        c -= 'A';

    // Look up the command in a table of command strings and execute it.
    if( table[c] )
        return fExecute( table[c] );
    return TRUE;
}

// Handle CTRL+Q commands
PWBFUNC CtrlQ( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    static char *CtrlQKeys[] =
    {
    /* A Query replace    */ "qreplace",
    /* B                  */ "",
    /* C End of file      */ "endfile",
    /* D End of line      */ "endline",
    /* E Top of window    */ "meta up",
    /* F Query search     */ "arg \"Search String\" prompt -> psearch",
    /* G                  */ "",
    /* H                  */ "",
    /* I                  */ "",
    /* J                  */ "",
    /* K                  */ "",
    /* L                  */ "",
    /* M                  */ "",
    /* N Goto mark        */ "restcur",
    /* O                  */ "",
    /* P                  */ "",
    /* Q                  */ "",
    /* R Start of file    */ "begfile",
    /* S Left of window   */ "meta left",
    /* T                  */ "",
    /* U                  */ "",
    /* V                  */ "",
    /* W                  */ "",
    /* X Bottom of window */ "meta down",
    /* Y Delete to EOL    */ "arg ldelete",
    /* Z                  */ ""
    };

    DoMessage( "Second key: A C D E F N R S X Y" );
    return DoSecondKey( CtrlQKeys );
}

// Handle CTRL+K sequence.
PWBFUNC CtrlK( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    static char *CtrlKKeys[] =
    {
    /* A                       */ "",
    /* B Begin selection       */ "arg",
    /* C                       */ "copy paste",
    /* D Exit, no autosave     */ "meta exit <",
    /* E                       */ "",
    /* F                       */ "",
    /* G                       */ "",
    /* H                       */ "",
    /* I                       */ "",
    /* J                       */ "",
    /* K                       */ "",
    /* L                       */ "",
    /* M                       */ "",
    /* N Set mark              */ "savecur",
    /* O                       */ "",
    /* P Print current file    */ "print",
    /* Q Exit all, no autosave */ "arg meta exit <",
    /* R Insert file           */ "arg arg \"Filename: \" prompt -> paste",
    /* S Save file             */ "arg arg setfile <",
    /* T Select word           */ "pword ->e mword arg meta pword => :>e mword pword arg meta pword",
    /* U                       */ "",
    /* V                       */ "",
    /* W                       */ "",
    /* X Save all and exit     */ "_pwbsaveall exit",
    /* Y Yank                  */ "delete",
    /* Z                       */ ""
    };

    DoMessage( "Second key: B C D N P Q R S T X Y" );
    return DoSecondKey( CtrlKKeys );
}

// Initialize the command keys.
void _cdecl EXTERNAL WhenLoaded( void )
{
    DoStatusBox( "TwoKey Sample Extensions", NULL );

    SetKey( "CtrlQ", "ctrl+q" );
    SetKey( "CtrlK", "ctrl+k" );

    DoStatusBox( NULL, NULL );
}

// No switches
struct swiDesc swiTable[] = { { NULL, NULL, 0 } };

// Commands
struct cmdDesc cmdTable[] =
{
    { "CtrlQ", CtrlQ, 0, CURSORFUNC },
    { "CtrlK", CtrlK, 0, CURSORFUNC },
    { NULL,    NULL,  0, 0 }
};
