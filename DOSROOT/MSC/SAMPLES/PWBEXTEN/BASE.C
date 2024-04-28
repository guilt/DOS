/* (FILE).C - (Summary)
 *
 * (Purpose)
 *
 * Switches:
 *
 * Functions:
 *
 *
 */

#pragma warning( disable:4001 )  //Allow single-line comments
#pragma warning( disable:4100 )  //Allow unused arguments

#include "ext.h"

void _cdecl EXTERNAL WhenLoaded( void );

PWBFUNC Func( unsigned argData, ARG far *pArg, flagType fMeta );

// Func - (Summary)
//
// Purpose:
//
// Input:
//
// Output:
//
//
PWBFUNC Func( unsigned argData, ARG far *pArg, flagType fMeta )
{
    return TRUE;
}

//-----------------< Standard Extension Information >----------------//

// WhenLoaded
//
//
//
//
void _cdecl EXTERNAL WhenLoaded( void )
{
    //DoStatusBox( "Banner", NULL );

    //Initialize extension

    //DoStatusBox( NULL, NULL );   //Close status box
}

//
// Command description table.
//
//
struct cmdDesc cmdTable[] =
{
    { "Func", Func, 0, NOARG },

    { NULL,   NULL, 0, 0     }   //end-of-table
};

//
// Switch description table.
//
//
struct swiDesc swiTable[] =
{

    { NULL, NULL, 0 }   //end-of-table
};
