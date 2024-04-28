/* SKEL.C - Skeleton for PWB extension
 *
 * Purpose: Commented outline for a PWB extension
 *
 * Switches: none
 *
 * Functions:
 *
 *  Func        - does nothing
 *
 *
 */

//  Turn off common warnings for benign extension constructs
//
#pragma warning( disable:4001 )  //Allow single-line comments
#pragma warning( disable:4100 )  //Allow unused arguments

#include "ext.h"

void _cdecl EXTERNAL WhenLoaded( void );

PWBFUNC Func( unsigned argData, ARG far *pArg, flagType fMeta );

// Func - Sample extension function
//
// Purpose:
//  Sample extension function entry point.
//
// Input:
//  argData = Keystroke used to invoke the function. This argument is not
//            used in extensions.
//
//  pArg    = Far pointer to a structure which defines the argument for the
//            function.
//
//  fMeta   = Boolean indicating whether the Meta modifier was turned on at
//            the time the function was executed.
//
// Output:
//  Extension functions are expected to return a Boolean value indicating
//  success or failure. Typically, TRUE is returned in the normal case.
//  These values can be tested inside of macros.
//

PWBFUNC Func( unsigned argData, ARG far *pArg, flagType fMeta )
{
    return TRUE;
}

//-----------------< Standard Extension Information >----------------//

// WhenLoaded - Extension initialization (required)
//
// Purpose:
//  This function is called when the extension is loaded.
//  Extension initialization may occur here. This function must be defined
//  even if the extension does not require initialization code.
//
// Input: none
// Output:none
//

void _cdecl EXTERNAL WhenLoaded( void )
{
    DoStatusBox( "Banner", NULL );//Display extension banner

    //Initialize extension
    //
    SetKey( "Func", "Shift+Ctrl+F" );

    DoStatusBox( NULL, NULL );    //Close status box
}

//
// Command description table.
//
//  This is an array of command descriptions that contain the text name of
//  the function (for key assignment and use in macros), a pointer to the
//  function to be called, and a set of flags that describe the types of
//  arguments that the function accepts.
//
//  This table is required, even if no functions are defined. In this case,
//  the table consists of the terminating empty structure.
//

struct cmdDesc cmdTable[] =
{
    //name,   func, 0, argType

    { "Func", Func, 0, NOARG },
    { NULL,   NULL, 0, 0     }   //end-of-table
};

//
// Switch description table.
//
//  This is an array of switch descriptions that contain the text name of
//  the switch (for assignment), a pointer to the switch variable for
//  numeric and Boolean switches or a function for text switches, and a set
//  of flags that describe the type of switch.
//
//  This table is required, even if no switches are defined. In this case,
//  the table consists of the terminating empty structure.
//
//  The switch types are:
//
//      SWI_BOOLEAN             Boolean
//      SWI_NUMERIC | RADIX10   Decimal numeric
//      SWI_NUMERIC | RADIX16   Hexadecimal numeric
//      SWI_EXTTEXT:            Text (act is a function to get/set value)
//
//  Use toPIF(act) to suppress compiler warnings for Boolean and numeric
//  switches. For example:
//
//      { "Switchname", toPIF(switchvar), SWI_BOOLEAN },
//

struct swiDesc swiTable[] =
{
    //name, act,  type

    { NULL, NULL, 0 }   //end-of-table
};
