/* ISEARCH.C - Emacs-style incremental search
 *
 * Copyright (C) 1988-1992, Microsoft Corporation
 * All rights reserved.
 *
 * Demonstrates the following extension functions and features:
 *
 * Callback functions:
 *  DoMessage, GetCursor, GetEditorObject, MoveCur, ReadChar, search
 *
 * Types:
 *  SearchInfo, fl
 *
 * Switches: none
 *
 * Functions:
 *  ISearch:Ctrl+I
 *
 */

/*  Turn off common warnings for benign extension constructs */
#pragma warning( disable:4001 )  //Allow single-line comments
#pragma warning( disable:4100 )  //Allow unused arguments

#include <stdlib.h>
#include <ext.h>
#include <readchar.h>

//  Exported functions
//
void _cdecl EXTERNAL WhenLoaded( void );
PWBFUNC ISearch( unsigned int, ARG far *, flagType );

//  Private functions
//
void GetKey( WORD *shift, WORD *vk, WORD*code );
void Adjust_fl( fl *Loc, flagType fDir );

//
//  Stack of locations
//
#define LOC_MAX 50
#define LOC_TOP LOC_MAX-1
#define LOC_EMPTY -1
#define LOC_END -2
static fl  flStack[LOC_MAX];
static int iTop = LOC_EMPTY;

void     PushLoc( void );
flagType PopLoc( void  );
void     ClearLoc( void );

static char szISearch[]    = "ISearch";
static char szISearchKey[] = "Ctrl+I";


void PushLoc( void )
{
    if( iTop == LOC_EMPTY )
        iTop = 0;

    GetCursor( &flStack[iTop].col, &flStack[iTop].lin );
    if( ++iTop > LOC_TOP )
        iTop = 0;
    flStack[iTop].col = LOC_END;  //set sentinel

}

flagType PopLoc( void )
{
    if( iTop == LOC_EMPTY )
        return FALSE;

    if( --iTop < 0 )
        iTop = LOC_TOP;

    if( flStack[iTop].col == LOC_END )
    {
        iTop = LOC_EMPTY;
        return FALSE;
    }

    MoveCur( flStack[iTop].col, flStack[iTop].lin );

}

void ClearLoc( void )
{
    iTop = LOC_EMPTY;
    flStack[0].col = LOC_END;
    flStack[LOC_TOP].col = LOC_END;

}


//  GetKey
//  Read a keystroke and extract its component fields.
//
void GetKey( WORD *shift, WORD *vk, WORD*code )
{
    long Key = ReadChar();

    *shift = HIWORD(Key) & ~KK_VK;  //shift state
    *vk    = HIWORD(Key) & KK_VK;   //virtual key code
    *code  = LOWORD(Key) & KK_VK;   //ASCII/virtual key code
}

//  Adjust_fl
//  Adjust a file location such that search() does not match the current
//  location.
//
void Adjust_fl( fl *Loc, flagType fDir )
{
    if( fDir )
    {
        Loc->col++;
        if( Loc->col >= BUFLEN )
        {
            Loc->lin++;
            Loc->col = 0;
        }
    }
    else
    {
        if( Loc->col > 0 )
            Loc->col--;
        else
        {
            Loc->lin--;
            Loc->col = BUFLEN-1;
        }
    }

}

// ISearch - Incremental search function
//
// Input:
//
//  nullarg     - Default entry state
//  textarg     - Initial search string
//  arg arg...  - Reverse search
//  meta...     - Case-insensitive
//
// Output:
//  TRUE : cursor moved
//  FALSE: cursor not moved: ISearch cancelled
//
// Description:
//
//  On entry:
//      The status bar shows "+ ³ISearch:" and waits for keystrokes.
//      If reverse search,   "- ³ISearch:"
//
//  Status Bar:
//      After each search, if found: "+þ³ISearch:<pattern>"
//                         else:     "+ ³ISearch:<pattern>"
//
//  CTRL+I(entry) - Display the last search string and go to the next
//                  occurrence.
//
//  CTRL+I, F3    - Move to the next occurrence
//
//  F4            - Move to the previous occurrence
//
//  Any character - Append to the search string, display it on the message
//                  line, and go to the first occurrence.
//
//  BKSP          - If last action was find, return to each previous
//                  occurrence in order.
//
//                  If a character was typed, remove the character from the
//                  string and show the cursor before that character was
//                  added.
//
//  ENTER:          Exit and leave the cursor at the last location.
//
//  ESC, CTRL+G   - Exit and return the cursor to the position on entry to
//                  ISearch.
//

PWBFUNC ISearch( unsigned int argData, ARG far *pArg, flagType fMeta )
{
    SearchInfo *si;                     //previous search information
    flagType fForward;                  //direction
    flagType fCase = (flagType)!fMeta;  //case
    fl       flStart;                   //starting location
    fl       flCur;                     //current location
    WORD vk;                            //keycode
    WORD shift;                         //shift state
    WORD code;                          //ASCII or virtual key code
    PFILE pfile;                        //current file
                                        //incremental search state
    enum { ssERROR, ssENTRY, ssFIND, ssCHAR } iss;
    static buffer Pattern;              //search pattern
    char far *pchPatEnd;                //end of pattern
    #define PROMPT "  ³ISearch:"        //prompt string
    static buffer Prompt;               //prompt buffer
    char far *pchPatPrompt = Prompt+11; //position of pattern in buffer

    if( (pfile = FileNameToHandle( "", "" )) == PNULL ) //no file
        return FALSE;

    GetEditorObject( RQ_SEARCHINFO, 0, &si ); //get current search state

    GetCursor( &flStart.col, &flStart.lin );  //get starting location
    flCur.col = flStart.col;
    flCur.lin = flStart.lin;
    ClearLoc();                               //clear location stack
    PushLoc();                                //push starting position

    iss = ssENTRY;
    switch( pArg->argType )
    {
    case NOARG:
        fForward = TRUE;
        Pattern[0] = 0;
        break;

    case NULLARG:
        fForward = (flagType)(pArg->arg.nullarg.cArg <= 1);
        Pattern[0] = 0;
        break;

    case TEXTARG:
        fForward = (flagType)(pArg->arg.textarg.cArg <= 1);
        farstrcpy( Pattern, pArg->arg.textarg.pText );
        if( search( pfile, fForward, FALSE, fCase, si->swit.fSrchWrap,
                    Pattern, &flCur ) == -1 )
            Prompt[1] = ' ';
        else
        {
            Prompt[1] = 'þ';
            MoveCur( flCur.col, flCur.lin );
            PushLoc();
        }
        iss = ssFIND;
        break;

    default:
        return BadArg();
    }

    farstrcpy( Prompt, PROMPT );
    Prompt[0] = (char)(fForward ? '+' : '-');
    pchPatEnd = Pattern + farstrlen( Pattern );

    for(;;)
    {
        farstrcpy( pchPatPrompt, Pattern );
        DoMessage( Prompt );
        GetKey( &shift, &vk, &code );

        //  ENTER: done
        if( vk == VK_RETURN )
        {
            DoMessage( NULL );
            return TRUE;
        }

        //  ESC, CTRL+G : return to starting position and stop
        if( (vk == VK_ESCAPE) || (shift & KK_CONTROL && vk == VK_G) )
        {
            MoveCur( flStart.col, flStart.lin );
            DoMessage( NULL );

            //  Set global SearchInfo
            farstrcpy( si->prev.szSrch, Pattern );
            si->prev.fSrchDir  = fForward;
            si->prev.fSrchCase = fCase;
            si->prev.fSrchRe   = FALSE;

            return FALSE;
        }

        //  CTRL+I, F3 : repeat search
        if( (vk == VK_F3) || (shift & KK_CONTROL && vk == VK_I) )
        {
            if( iss == ssENTRY ) //Search for previous search string
            {
                //get current search state
                GetEditorObject( RQ_SEARCHINFO, 0, &si );
                farstrcpy( Pattern, si->prev.szSrch );
                pchPatEnd = Pattern + farstrlen( Pattern );
                farstrcpy( pchPatPrompt, Pattern );
                DoMessage( Prompt );
            }

            PushLoc();
            Adjust_fl( &flCur, (flagType)fForward );
            if( search( pfile, fForward, FALSE, fCase, si->swit.fSrchWrap,
                        Pattern, &flCur ) == -1 )
            {
                Prompt[1] = ' ';
                // restore unadjusted location
                GetCursor( &flCur.col, &flCur.lin );
            }
            else
            {
                Prompt[1] = 'þ';
                MoveCur( flCur.col, flCur.lin );
            }
            iss = ssFIND;
            continue;
        }

        if( vk == VK_F4 )   //reverse search
        {
            PushLoc();
            Adjust_fl( &flCur, (flagType)!fForward );
            if( search( pfile, (flagType)!fForward, FALSE, fCase,
                        si->swit.fSrchWrap, Pattern, &flCur ) == -1 )
            {
                Prompt[1] = ' ';
                // restore unadjusted location
                GetCursor( &flCur.col, &flCur.lin );
            }
            else
            {
                Prompt[1] = 'þ';
                MoveCur( flCur.col, flCur.lin );
            }
            iss = ssFIND;
            continue;
        }

        if( vk == VK_BACK ) //BKSP: back up
        {
            if( iss == ssCHAR )
                if( pchPatEnd > Pattern )
                {
                    *--pchPatEnd = '\0';
                    farstrcpy( pchPatPrompt, Pattern );
                }
                else
                    bell();
            if( PopLoc() )
                GetCursor( &flCur.col, &flCur.lin );
            continue;
        }

        if( (code < VK_MIN) || (code >= VK_A && code <= VK_Z) )
        {
            *pchPatEnd++ = (char)code;
            *pchPatEnd = '\0';
            farstrcpy( pchPatPrompt, Pattern );
            DoMessage( Prompt );

            PushLoc();
            if( search( pfile, fForward, FALSE, fCase, si->swit.fSrchWrap,
                Pattern, &flCur ) == -1 )
            {
                Prompt[1] = ' ';
            }
            else
            {
                Prompt[1] = 'þ';
                MoveCur( flCur.col, flCur.lin );
            }
            iss = ssCHAR;
            continue;
        }

        // Illegal key
        bell();

    }

}


//-------------------< Standard Extension Information >--------------------

//  WhenLoaded - Extension initialization
void _cdecl EXTERNAL WhenLoaded( void )
{
    DoStatusBox( "Incremental Search Extension", NULL );

    SetKey( szISearch, szISearchKey );

    DoStatusBox( NULL, NULL );
}

//
// Command description table.
//
struct cmdDesc cmdTable[] =
{
    {szISearch, ISearch, 0, NOARG|NULLARG|TEXTARG },
    {NULL, NULL, 0, 0 }
};

//
// Switch description table.
//
struct swiDesc swiTable[] =
{
    { NULL, NULL, 0 }
};
