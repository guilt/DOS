/* TEXT.C - Text processing extension
 *
 * Copyright (C) Microsoft Corp. 1991-1992
 * All Rights Reserved
 *
 * Demonstrates the following extension functions:
 *
 *  atou           BadArg        DelLine            DoMessage
 *  DoMessageBox   DoStatusBox   FileNameToHandle   FindSwitch
 *  GetLine        MoveCur       PutLine            ReadChar
 *  SetKey
 *
 * Switches:
 *  J2Space:no  - Boolean; Justify with two spaces after periods (.)
 *  MapA:       - (see WhenLoaded for default value)
 *  MapB:       - (see WhenLoaded for default value)
 *                Character maps for MapA2B and MapB2A
 *
 * Functions:
 *  Ucase   :ALT+U        - Uppercase
 *  Lcase   :ALT+L        - Lowercase
 *  Tcase   :ALT+X        - Toggle case
 *  MapB2A  :SHIFT+CTRL+U - Map B's to A's
 *  MapA2B  :SHIFT+CTRL+L - Map A's to B's
 *  MapSwap :SHIFT+CTRL+X - Exchange characters between maps (toggle)
 *  Justify :ALT+J        - Justify text
 *  Center  :ALT+C        - Center text
 *  Makebox :NUM/         - Draw a box
 *  Goto    :ALT+G        - Goto a specific line/column
 *  OkCancel:(unassigned) - Message box with replies OK or Cancel
 *  YesNo   :(unassigned) - Message box with replies Yes or No
 */

/*  Turn off common warnings for benign extension constructs */
#pragma warning( disable:4001 )  //Allow single-line comments
#pragma warning( disable:4100 )  //Allow unused arguments

//#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ext.h>

//
//  Prototypes
//
void _cdecl EXTERNAL WhenLoaded( void );
PWBFUNC Ucase   ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC Lcase   ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC Tcase   ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC MapA2B  ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC MapB2A  ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC MapSwap ( unsigned argData, ARG _far *pArg, flagType fMeta );

PWBFUNC Justify ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC Center  ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC MakeBox ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC Goto    ( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC OkCancel( unsigned argData, ARG _far *pArg, flagType fMeta );
PWBFUNC YesNo   ( unsigned argData, ARG _far *pArg, flagType fMeta );

//
//  SWI_EXTTEXT functions to set/query MapA and MapB switches
//
char _far * _pascal EXTERNAL DoMapA( char _far *pszVal, flagType fQuery );
char _far * _pascal EXTERNAL DoMapB( char _far *pszVal, flagType fQuery );

//
//  Internal functions for this extension
//
char _far *ParseString( char _far * Dest, char _far * Src );
char _far *SetMap( char *pszMap, char *pszSwi, char _far *pszVal, char chMap );
int     HexDigit( int ch );
char    *Swi2Map( char * pszMap, char *pszSwi );
void    DoGenMap( char *pchChar, int Action );
PWBFUNC MapChars( ARG _far *pArg, int fAction, int fCase );
void EXTERNAL DumpLine( char _far *, PFILE, COL, COL, LINE, char _far *, int );
int     NextLine( char _far *, PFILE, LINE, LINE, char _far * );
void    GetMinLine( LINE y, COL xMin, char *pch, PFILE pFile );
LINE    GetXY( char *pchVal, LINE current );

//
//  Constants
//

//  Column 'infinity'
#define MAXCOL 32765

//
//  Global variables for switches - initialized to default values,
//  but switch overrides.
//
flagType J2Space = FALSE;

//
//  Switches initialized by WhenLoaded()
//
char achSwiA[BUFLEN];  //value of CharMapA switch
char achSwiB[BUFLEN];  //value of CharMapB switch
char achMapA[BUFLEN];  //translation map A
char achMapB[BUFLEN];  //translation map B

enum eMappings { UPPER, LOWER, TOGGLE };

enum eCorners { NW, EW, NE, SW, SE, NS, WW, EE, NN, SS, CE };
char *achBox[] =
{
    "⁄ƒø¿Ÿ≥√¥¬¡≈",
    "…Õª»º∫ÃπÀ Œ",
    "’Õ∏‘æ≥∆µ—œÿ",
    "÷ƒ∑”Ω∫«∂“–◊",
    "+-+++|+++++",
    "=====|=====",
    "∞∞∞∞∞∞∞∞∞∞∞",
    "±±±±±±±±±±±",
    "≤≤≤≤≤≤≤≤≤≤≤",
    "€€€€€€€€€€€",
    "˛˛˛˛˛˛˛˛˛˛˛",
    "???????????"   //buffer for any other char
};
#define LENBOXCHARS 11  //number of characters in an achBox entry

char achBoxMenu[] =
    "Key(Box):0(≈)1(Œ)2(ÿ)3(◊)4(+)5(=)6(∞)7(±)8(≤)9(€)A(˛)?(?)";
char achMenuChar[] = "0123456789A";



//  Ucase
//  Convert argument to upper case
//
PWBFUNC Ucase( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    return MapChars( pArg, UPPER, TRUE );
}

//  Lcase
//  Convert argument to lower case.
//
PWBFUNC Lcase( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    return MapChars( pArg, LOWER, TRUE );
}

//  Tcase
//  Toggle case of argument
//
PWBFUNC Tcase( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    return MapChars( pArg, TOGGLE, TRUE );
}

//
//  Map characters between the maps specified by the MapA and MapB
//  switches
//

//  MapA2B
//  Map char in MapA to corresponding char in MapB
//
PWBFUNC MapA2B( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    return MapChars( pArg, UPPER, FALSE );
}

//  MapB2A
//  Map char in MapB to corresponding char in MapA
//
PWBFUNC MapB2A( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    return MapChars( pArg, UPPER, FALSE );
}

//  MapSwap
//  Swap chars between maps
//
PWBFUNC MapSwap( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    return MapChars( pArg, TOGGLE, FALSE );
}

//  Swi2Map
//  Convert switch to character map
//
char *Swi2Map( char * pszMap, char *pszSwi )
{
    if( ParseString( pszMap, pszSwi ) == NULL )
        return NULL;
    farmemset( pszMap + farstrlen(pszMap),
            *(pszMap + farstrlen(pszMap) -1 ),
            BUFLEN - farstrlen(pszMap) -1 );
    pszMap[BUFLEN-1] = '\0';
    return pszMap;

}//  Swi2Map


//  DoGenMap
//  Perform a general mapping of *pchChar
//
//  Action specifies the direction of mapping:
//
//      TOGGLE  bidirectional: A's go to B's and B's go to A's
//      UPPER   A's go to B's
//      LOWER   B's go to A's
//
void DoGenMap( char *pchChar, int Action )
{
    char *pchScan;

    switch( Action )
    {
    case TOGGLE:
        if( (pchScan = strchr( achMapB, *pchChar )) != NULL )
        {
            *pchChar = achMapA[pchScan - achMapB];
            break;
        }
        //else fall-through to UPPER case

    case UPPER:
        if( (pchScan = strchr( achMapA, *pchChar )) != NULL )
            *pchChar = achMapB[pchScan - achMapA];
        break;

    case LOWER:
        if( (pchScan = strchr( achMapB, *pchChar )) != NULL )
            *pchChar = achMapA[pchScan - achMapB];
        break;
    }

}//  DoGenMap



//  MapChars
//  Map characters
//
PWBFUNC MapChars
    (
    ARG _far *pArg, //Argument record from PWB
    int fAction,    //Direction of mapping: UPPER, LOWER, or TOGGLE
    int fCase       //Case mapping (TRUE) or general mapping (FALSE)
    )
{
    PFILE   pFile;
    COL     xStart = 0;
    COL     xEnd   = 0;
    COL     xTemp  = 0;
    LINE    yStart = 0;
    LINE    yEnd   = 0;
    int     i      = 0;
    char    buf[BUFLEN];

    if( (pFile = FileNameToHandle( "", "" )) == PNULL )
        return FALSE;               //No file

    //  Handle strictly vertical BOXARG: treat it as a LINEARG.
    if( pArg->argType == BOXARG &&
        (pArg->arg.boxarg.xLeft == pArg->arg.boxarg.xRight) )
        pArg->argType = LINEARG;

    switch( pArg->argType )
    {
        case NOARG:                 //Switch case at cursor
            xStart = xEnd = pArg->arg.noarg.x;
            yStart = yEnd = pArg->arg.noarg.y;
            MoveCur( xStart + 1, yStart );
            break;

        case NULLARG:               //One arg: switch case to end of word
            if( pArg->arg.nullarg.cArg == 1 )
            {
                xStart = pArg->arg.nullarg.x;
                yStart = pArg->arg.nullarg.y;
                fExecute( "pword" );
                GetCursor( &xEnd, &yEnd );
                if( yEnd > yStart )
                {
                    --yEnd;
                    xEnd = MAXCOL;
                }
                else
                    xEnd--;
                break;
            }
            else
            {                       //Two args: switch case to end of line
                xStart = pArg->arg.nullarg.x;
                xEnd = MAXCOL;
                yStart = yEnd = pArg->arg.nullarg.y;
                break;
            }


        case LINEARG:               //Switch case of line range
            xStart = 0;
            xEnd = MAXCOL;
            yStart = pArg->arg.linearg.yStart;
            yEnd = pArg->arg.linearg.yEnd;
            break;

        case BOXARG:                //Switch case of box
            xStart = pArg->arg.boxarg.xLeft;
            xEnd   = pArg->arg.boxarg.xRight;
            yStart = pArg->arg.boxarg.yTop;
            yEnd   = pArg->arg.boxarg.yBottom;
            break;
    }

    //
    // Get each line. Convert characters from starting to ending column.
    // Put modified line back in file.
    //
    while( yStart <= yEnd )
    {
        i = GetLine( yStart, buf, pFile );
        xTemp = xStart;
        while( (xTemp <= i) && (xTemp <= xEnd) )
        {
            if( fCase )
                switch( fAction )
                {
                case TOGGLE:
                    if( buf[xTemp] >= 'A' && buf[xTemp] <= 'Z' )
                    {
                        buf[xTemp] += 'a' - 'A';   //Convert to lower
                        break;
                    }
                    //else fall through
                case UPPER:
                    if( buf[xTemp] >= 'a' && buf[xTemp] <= 'z' )
                        buf[xTemp] += 'A' - 'a';   //Convert to upper
                    break;
                case LOWER:
                    if( buf[xTemp] >= 'A' && buf[xTemp] <= 'Z' )
                        buf[xTemp] += 'a' - 'A';   //Convert to lower
                    break;
                }
            else
                DoGenMap( &buf[xTemp], fAction );
            xTemp++;
        }
        PutLine( yStart++, buf, pFile );
    }

    return TRUE;

}//  MapChars



//  Justify  -   Justify text
//
//  NOARG:       Justify between first nonspace column and rmargin,
//               from the current line to blank line.
//
//  NULLARG:     Justify between current column and rmargin,
//               from the current line to blank line.
//
//  LINEARG:     Justify between column 0 and rmargin,
//               the specified lines.
//
//  STREAMARG:   Justify between specified columns
//               from current line to blank (handled by boxarg).
//
//  BOXARG:      Justify between specified columns
//               the specified rows.
//
//  TEXTARG:     Justify between columns 0 and rmargin,
//               from the current line to a blank line, prepending each
//               line with <textarg>.
//               If the line already begins with <textarg>, only one
//               copy is used.

// Terminating line value flags justification to the next blank line
#define fBLANKLINE -1

PWBFUNC Justify( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    static char inbuf[512];     //Input buffer
    PFILE       pFile;          //File handle
    char _far   *pText = NULL;  //Pointer to prepending text
    COL         x1 = 0;         //Justify to left column
    COL         x2 = 0;         //Justify to right column
    LINE        y1 = 0;         //Start line
    LINE        y2 = 0;         //End line
    LINE        yOut = 0;       //Output line
    char        buf[BUFLEN];
    int         i = 0;
    PSWI        pswi;

    if( (pswi = FindSwitch( "rmargin" )) == NULL )
        return FALSE;                   //No switch

    if( (pFile = FileNameToHandle( "", "" )) == PNULL )
        return FALSE;                   //No file

    //  Handle strictly vertical BOXARG: treat it as a LINEARG.
    if( pArg->argType == BOXARG &&
        (pArg->arg.boxarg.xLeft == pArg->arg.boxarg.xRight) )
        pArg->argType = LINEARG;

    switch( pArg->argType )
    {
    case NOARG:                         //Justify paragraph
        y1 = pArg->arg.noarg.y;         //from current line...
        y2 = fBLANKLINE;                // ...to blank line
        i = GetLine( y1, buf, pFile );
        for( x1 = 0; (buf[x1] == ' ') && (x1 < i); x1++ )
            ;                           //from first nonspace to
        x2 = *(pswi->act.ival);         // ...right margin
        pText = 0;                      //no text to prepend
        break;

    case NULLARG:                       //Justify indented
        x1 = pArg->arg.nullarg.x;       //between cur col...
        x2 = *(pswi->act.ival);         // ...and right margin
        y1 = pArg->arg.nullarg.y;       //current line...
        y2 = fBLANKLINE;                // ...to blank line
        pText = 0;                      //no text to prepend
        break;

    case LINEARG:                       //Justify line range
        x1 = 0;                         //between cols 0...
        x2 = *(pswi->act.ival);         // ...and right margin
        y1 = pArg->arg.linearg.yStart;  //and range of lines
        y2 = pArg->arg.linearg.yEnd;
        pText = 0;                      //no text to prepend
        break;

    case BOXARG:                        //Justify box
        x1 = pArg->arg.boxarg.xLeft;    //from left corner...
        x2 = pArg->arg.boxarg.xRight;   //     ...to right
        y1 = pArg->arg.boxarg.yTop;     //from top...
        y2 = pArg->arg.boxarg.yBottom;  //    ...to bottom
        pText = 0;                      //no text to prepend
        break;

    case TEXTARG:                       //Justify & prepend
        x1 = 0;                         //between 0...
        x2 = *(pswi->act.ival);         //   ...and right margin
        y1 = pArg->arg.textarg.y;       //current line...
        y2 = fBLANKLINE;                //    ...to blank line
        pText = pArg->arg.textarg.pText;//text to prepend
        break;
    }

    if( y1 == y2 )                      //If same line, then
        y2 = fBLANKLINE;                //justify to blank line

    if( x1 == x2 )                      //If same column
        x2 = *(pswi->act.ival);         //then justify to Rmargin

    if( x2 < x1 )                       //If backwards
    {
        x1 = 0;                         //revert to default
        x2 = *(pswi->act.ival);
    }

    //
    // While we can get data within the specified limits, format each
    // new line and output back to the file.
    //
    inbuf[0] = 0;
    yOut = y1;                                  //line being output
                                                //while data to get
    while( NextLine( inbuf, pFile, y1, y2, pText ) )
    {
        if( y2 != fBLANKLINE )                  //end moves with deletion
            y2--;

        while( farstrlen( inbuf ) > (x2 - x1) )
        {                                       //while data to output
            y1++;                               //line moves with insert
            if( y2 != fBLANKLINE )
                y2++;
            DumpLine( inbuf, pFile, x1, x2, yOut++, pText, fMeta );
        }
    }

    // Dump remaining text
    while( inbuf[0] )
        DumpLine( inbuf, pFile, x1, x2, yOut++, pText, 0 );

    // If we were formatting to a blank line, dump out one of those too.
    if( y2 == fBLANKLINE )                      //dump blank line
        DumpLine( "", pFile, x1, x2, yOut++, "", 0 );

    return TRUE;

}//  Justify

//
//  NextLine
//  Get next line from file.
//
//  Like GetLine, except removes leading and trailing spaces.
//
int NextLine(
    char _far  *pBuf,           //Input buffer
    PFILE      pFile,           //File pointer
    LINE       StartLine,       //Line # to read
    LINE       EndLine,         //Line # to stop at
    char _far  *pPrefix         //Prefix to strip (NULL if none)
    )
{
    char _far  *pchScan;        //Scanning pointer
    char _far  *pchPoke;        //Copying pointer
    int        Ret;             //Return value
    char       achWork[512];    //Working buffer
    int        cbPrefix = 0;    //Length of prefix

    achWork[0] = 0;
    Ret = 0;
    if( (EndLine == -1) || (StartLine <= EndLine) )
    {
        Ret = GetLine( StartLine, achWork, pFile ); //Get a line
        DelLine( pFile, StartLine, StartLine );     //Remove it
    }

    //If there was data, strip prefix (if any) and leading spaces in
    //new input line.
    if( Ret )
    {
        if( pPrefix )
        {
            cbPrefix = farstrlen(pPrefix);
            if( farstrncmp( pPrefix, achWork, cbPrefix ) )
                pchScan = achWork;
            else
                pchScan = achWork + cbPrefix;
        }
        else
            pchScan = achWork;
        while( *pchScan == ' ' )
            pchScan++;                              //Skip leading spaces

        // If existing buffer is non-empty, append a space and set
        // pointer to end.
        //
        pchPoke = pBuf;
        if( *pchPoke )                              //If non-null string
        {
            pchPoke += farstrlen( pchPoke );        //point to null
            *pchPoke++ = ' ';                       //append space
            if( J2Space && (*(pchPoke - 2) == '.') )//If period...
                *pchPoke++ = ' ';                   //append another
        }

        // Append new line, but compress multiple spaces into one.
        while( *pchScan )                           //Copy line over
        {
            if( J2Space & (*pchScan == '.') )       //If period...
            {
                if( *(pchScan + 1) == ' ' )         // ...space
                {
                    *pchPoke++ = *pchScan++;        //Copy period
                    *pchPoke++ = *pchScan;          //Copy space
                }
            }
            if( (*pchPoke++ = *pchScan++) == ' ' )  //Copy a char
            {
                while( *pchScan == ' ' )
                    pchScan++;                      //Skip multiple spaces
            }
        }
        while( *(pchPoke-1) == ' ' )                //Remove trailing spaces
            pchPoke--;
        *pchPoke = 0;

        if( pPrefix )
            return( farstrlen(pBuf) - cbPrefix );

    }
    return Ret;

}// NextLine

//  DumpLine
//  Dump one line of text to the file.
//  Prepend any required text or spaces, and perform word break/cut at
//  right hand column.

void EXPORT DumpLine(
    char _far *pBuf,    //Data to output
    PFILE     pFile,    //File to output to
    COL       x1,       //Left-hand column
    COL       x2,       //Right-hand column
    LINE      yOut,     //Line to output to
    char _far *pText,   //Text to prepend
    int       fFlush    //Flush both sides
    )
{
    int  i;
    char _far *pchScan;
    char _far *pchPoke;
    char achWork[512];  //Working buffer
    char achFlush[512]; //Working buffer

    //  Start by prepending any text or padding to the left margin
    //
    achWork[0] = 0;                             //Start with null
    if( pText )                                 //If prefix
    {
        farstrcpy( achWork, pText );            //copy prefix
        x1 = farstrlen( pText );                //set left margin at prefix
    }
    else
    {
        farmemset( achWork, ' ', x1 );             //pad with spaces
        achWork[x1] = '\0';
    }
    farstrcat( achWork, pBuf );

    //
    //  Starting at the right column, scan back for a space to break at.
    //  If one is not found before the left hand column, then break at
    //  the right hand column. Copy any leftover line back to the
    //  passed-in buffer.

    *pBuf = 0;                                  //Empty input buffer
    if( farstrlen( achWork ) > x2 )             //If we need to cut
    {
        pchScan = &achWork[x2];                 //Point at potential cut
        while( (pchScan > achWork + x1) && (*pchScan != ' ') )
            pchScan--;                          //Back up to space

        if( pchScan <= achWork + x1 )           //If no space found
        {
            farstrcpy( pBuf, &achWork[x2] );    //copy remainder
            achWork[x2] = 0;                    //terminate this line
            fFlush = FALSE;                     //suppress right-justify
        }
        else
        {
            *pchScan = 0;                       //terminate this line
            while( *++pchScan == ' ' )          //skip leading spaces
                ;
            farstrcpy( pBuf, pchScan );         //copy remainder
        }
    }


    // This code is invoked when the user wants to justify both right
    // and left sides of his text. We determine how many spaces we need
    // to add, and scan through and add one space to each run of spaces
    // until we've added enough.

    if( fFlush )                                    //right justify
    {
        while( (i = x2 - farstrlen(achWork)) > 0 )  //count of spaces to add
        {
            farstrncpy( achFlush, achWork, x1 );    //start with prefix
            pchScan = achWork  + x1;                //skip fixed part
            pchPoke = achFlush + x1;
            while( *pchScan )                       //while data to copy
            {
                if( (*pchScan == ' ') && i )        //time to insert a space
                {
                    i--;
                    *pchPoke++ = ' ';               //insert space
                    while( *pchScan == ' ' )
                        *pchPoke++ = *pchScan++;    //copy spaces
                }
                if( *pchScan )
                    *pchPoke++ = *pchScan++;        //copy next char
            }
            *pchPoke = 0;
            farstrcpy( achWork, achFlush );         //copy back
        }
    }

    // Create new line and put it out.
    CopyLine( PNULL, pFile, yOut, yOut, yOut );
    PutLine( yOut, achWork, pFile );

}//  DumpLine


//  Center - Center text
//

PWBFUNC Center( unsigned int argData, ARG _far *pArg, flagType fMeta )
{
    PFILE pFile;
    LINE  yStart = 0;
    LINE  yEnd   = 0;
    COL   xStart = 0;
    COL   xStartThisLine= 0;
    COL   xEnd   = 0;
    COL   xMidField = 0;
    COL   xMidText  = 0;
    COL   xLen      = 0;
    char  *pBuf;
    char  buf[BUFLEN];
    PSWI  pswi;

    pswi = FindSwitch( "rmargin" );
    xEnd = *(pswi->act.ival);

    if( (pFile = FileNameToHandle( "", "" )) == PNULL )
        return FALSE;               //No file

    //  Handle strictly vertical BOXARG: treat it as a LINEARG.
    if( pArg->argType == BOXARG &&
        (pArg->arg.boxarg.xLeft == pArg->arg.boxarg.xRight) )
        pArg->argType = LINEARG;

    switch( pArg->argType )
    {
    // If the user has the cursor on a line with nothing marked and asks
    // to center, center that line only.

    case NOARG:
        yStart = yEnd = pArg->arg.noarg.y;
        break;

    // If the user has marked one or more lines, and asks to center,
    // center the range of lines that are marked.

    case LINEARG:
        yStart = pArg->arg.linearg.yStart;
        yEnd   = pArg->arg.linearg.yEnd;
        break;

    // If the user has block-marked one or more lines, Center the range
    // of lines within the block. Note that the block marks only the
    // field to center in, not the text to be centered.

    case BOXARG:
        yStart = pArg->arg.boxarg.yTop;
        yEnd   = pArg->arg.boxarg.yBottom;
        xStart = pArg->arg.boxarg.xLeft;
        xEnd   = pArg->arg.boxarg.xRight;
        break;

    }

    // Loop across the range of lines
    for( ; yStart <= yEnd; yStart++ )
    {
        xLen = GetLine( yStart, buf, pFile );

        // Don't perform any action on zero-length lines
        if( xLen > 0 )
        {
            // Scan for the first non-whitespace character
            pBuf = buf + strspn( buf, " \t" );

            xLen = farstrlen( pBuf );
            xMidField = xStart + ((xEnd - xStart) / 2);
            xMidText = xLen / 2;
            xStartThisLine = xMidField - xMidText;
            xStartThisLine = (xStartThisLine > 0) ? xStartThisLine : 0;

            // Move the text to the correct place on the line
            memmove( buf + xStartThisLine, pBuf, xLen + 1 );

            // Blank fill the area in front of the text
            if( xStartThisLine )
                farmemset( buf, ' ', xStartThisLine );

            // Put the line back
            PutLine( yStart, buf, pFile );
        }
    }

    return TRUE;
}//  Center


//  MakeBox
//  Draw a box
//
PWBFUNC MakeBox( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    PFILE    pFile;
    COL      xStart;
    COL      xEnd;
    COL      xTemp;
    LINE     yStart;
    LINE     yEnd;
    LINE     yTemp;
    char     buf[BUFLEN];
    char     *pchBox;
    unsigned i;
    unsigned ch;
    unsigned fBox;

    if( (pFile = FileNameToHandle( "", "" )) == PNULL )
        return FALSE;           //No file

    DoMessage( achBoxMenu );
    ch = (int)ReadChar() & 0x00ff;
    DoMessage( NULL );  //restore message line

    if( ch == 27 )      //ESC => cancel
        return FALSE;

    if( (pchBox = strchr( achMenuChar, toupper( ch ) )) == NULL )
    {
        // Character not in menu, so use it as the drawing character
        i = sizeof (achMenuChar) - 1;
        farmemset( achBox[i], ch, LENBOXCHARS );
    }
    else
        i = pchBox - achMenuChar;

    pchBox = achBox[i];

    //  Handle strictly vertical BOXARG: treat it as a LINEARG.
    if( pArg->argType == BOXARG &&
        (pArg->arg.boxarg.xLeft == pArg->arg.boxarg.xRight) )
        pArg->argType = LINEARG;

    switch( pArg->argType )
    {
        case NOARG:
            xStart = pArg->arg.noarg.x;
            yStart = pArg->arg.noarg.y;
            GetMinLine( yStart, xStart, buf, pFile );
            buf[xStart] = pchBox[CE];
            PutLine( yStart, buf, pFile );
            MoveCur( xStart + 1, yStart );
            break;

        case BOXARG:
            fBox   = (pArg->arg.boxarg.cArg == 1) ? TRUE : FALSE;
            xStart = xTemp = pArg->arg.boxarg.xLeft;
            xEnd   = pArg->arg.boxarg.xRight;
            yStart = yTemp = pArg->arg.boxarg.yTop;
            yEnd   = pArg->arg.boxarg.yBottom;


            if( xStart == xEnd+1 || xStart == xEnd-1 ) //Vertical line.
            {
                GetMinLine( yTemp, xTemp, buf, pFile );
                if( (buf[xTemp] == pchBox[EW]) && fBox )
                    buf[xTemp] = pchBox[NN];
                else
                    buf[xTemp] = pchBox[NS];
                PutLine( yTemp++, buf, pFile );

                while( yTemp < yEnd )
                {
                    GetMinLine( yTemp, xTemp, buf, pFile );
                    buf[xTemp] = pchBox[NS];
                    PutLine( yTemp++, buf, pFile );
                }

                GetMinLine( yTemp, xTemp, buf, pFile );
                if( (buf[xTemp] == pchBox[EW]) && fBox )
                    buf[xTemp] = pchBox[SS];
                else
                    buf[xTemp] = pchBox[NS];
                PutLine( yTemp, buf, pFile );
            }
            else if( yStart == yEnd )       //Horizontal line.
            {
                GetMinLine( yStart, xEnd, buf, pFile );
                if( (buf[xTemp] == pchBox[NS]) && fBox )
                    buf[xTemp++] = pchBox[WW];
                else
                    buf[xTemp++] = pchBox[EW];

                while( xTemp < xEnd )
                    buf[xTemp++] = pchBox[EW];

                if( (buf[xTemp] == pchBox[NS]) && fBox )
                    buf[xTemp++] = pchBox[EE];
                else
                    buf[xTemp++] = pchBox[EW];
                PutLine( yStart, buf, pFile );
            }
            else    //Box.
            {
                GetMinLine( yTemp, xEnd, buf, pFile );
                buf[xTemp++] = pchBox[NW];
                while( xTemp < xEnd )
                    buf[xTemp++] = pchBox[EW];
                buf[xTemp++] = pchBox[NE];
                PutLine( yTemp++, buf, pFile );

                while( yTemp < yEnd )
                {
                    xTemp = xStart;
                    GetMinLine( yTemp, xEnd, buf, pFile );
                    buf[xTemp++] = pchBox[NS];
                    while( xTemp < xEnd )
                    {
                        if( pArg->arg.boxarg.cArg > 1 )
                            buf[xTemp++] = pchBox[CE];
                        else
                            xTemp++;
                    }
                    buf[xTemp] = pchBox[NS];
                    PutLine( yTemp++, buf, pFile );
                }

                xTemp = xStart;
                GetMinLine( yTemp, xEnd, buf, pFile );
                buf[xTemp++] = pchBox[SW];
                while( xTemp < xEnd )
                    buf[xTemp++] = pchBox[EW];
                buf[xTemp] = pchBox[SE];
                PutLine( yTemp, buf, pFile );
            }
            break;

        default:
            break;
    }

    DoMessage( NULL );  //restore message line
    return TRUE;
}//  MakeBox


//  GetMinLine
//  Get the specified line, blank-padded on the right to fill
//  the minimum width.
//
//  Used by MakeBox
//
void GetMinLine( LINE y, COL xMin, char *pch, PFILE pFile )
{
    COL x;

    x = GetLine( y, pch, pFile );
    if( x <= xMin )
    {
        while( x <= xMin )
            pch[x++] = ' ';
        pch[x] = '\0';
    }
}//  GetMinLine


//  GetXY
//  Parse relative or absolute coordinate from string.
//
//  If the string is not numeric or the name of a numeric switch, return
//  the current location.
//
//  Used by Goto.
//
LINE GetXY( char *pchVal, LINE current )
{
    LINE t;
    PSWI pswi;

    if( pchVal == NULL )
        return current;

    if( (t = atou( pchVal )) == 0 )     //Number?
    {                                   //Not a number or 0
        // Numeric switch?
        if( isalpha( *pchVal ) &&
            ((pswi = FindSwitch( pchVal )) != NULL) &&
            ((pswi->type & 0xff) == SWI_NUMERIC) )  //mask radix in high byte
        {
            t = *(pswi->act.ival);
            t--;
        }
        else                            //not a numeric switch
            return current;             //return current location
    }
    else                                //Number
    {
        if( (*pchVal == '+') || (*pchVal == '-') )
            t += current;   //Relative
        else
            t--;            //Absolute:convert 1-based to internal 0-based
    }

    return t;

}//  GetXY

//  Goto
//  Go to the indicated line:column
//
//  TEXTARG
//  syntax: [lead]...[[+|-]line][sep...[+|-]column]
//
//  <lead>  One of [ (<[{] or tab
//
//  <sep>   One of [ .,/;:\|=_] or tab
//
//  +|-     Specifies a location relative to the current position
//
//  If <line> is omitted, move to <column> on the same line
//
//  If no <column>, keep same column
//
//  <line> and <column> can be specified by a numeric switch which gives
//  an absolute coordinate.
//
//  Returns:
//      TRUE : Cursor moved
//      FALSE: Cursor not moved or bad argument.
//
PWBFUNC Goto( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    char achSkip[] = " \t(<[{";         //Leading characters
    char achSep[]  = " \t.,/;:\\|=_";
    char *pszLine;
    char *pszCol;
    COL  x;
    LINE y;

    if( pArg->argType == TEXTARG || pArg->argType == BOXSTR )
    {

        pszLine = pArg->arg.textarg.pText;

        // Find line number (if any)
        pszLine += strspn( pszLine, achSkip );
        y = GetXY( pszLine, pArg->arg.textarg.y );

        // Find column number (if any)
        if( (pszLine = strpbrk( pszLine, achSep )) != NULL )
        {
            pszCol = pszLine + strspn( pszLine, achSep );
            x = (COL)GetXY( pszCol, (LINE)pArg->arg.textarg.x );
        }
        else
            x = pArg->arg.textarg.x;

        if( x == pArg->arg.textarg.x && y == pArg->arg.textarg.y )
            return FALSE;   //no movement

        MoveCur( x, y );
        return TRUE;
    }
    else
    {
        BadArg();
        return FALSE;
    }

}//  Goto


//  SetMap
//  Set Charmap switches
//
char _far *SetMap
    (
    char *pszMap,       //Map buffer to set
    char *pszSwi,       //CharMap<x> switch
    char _far *pszVal,  //Value to set switch to
    char chMap          //Letter <x> for error message
    )
{
    static char achErrMsg[] = "MapX: Error in string format.";

    if( Swi2Map( pszMap, pszVal ) == NULL )    //Syntax error
    {
        Swi2Map( pszMap, achSwiA );            //restore map
        achErrMsg[3] = chMap;
        return (char _far *)achErrMsg;
    }

    farstrcpy( pszSwi, pszVal );              //set switch value
    return NULL;
}//  SetMap


//  DoMapA
//  Set or query the CharMapA switch
//
char _far * _pascal EXTERNAL DoMapA( char _far *pszVal, flagType fQuery )
{
    if( fQuery )
        return (char _far *)achSwiA;
    else
        return SetMap( achMapA, achSwiA, pszVal, 'A' );
}//  DoMapA



//  DoMapB
//  Set or query the CharMapB switch
//
char _far * _pascal EXTERNAL DoMapB( char _far *pszVal, flagType fQuery )
{
    if( fQuery )
        return (char _far *)achSwiB;
    else
        return SetMap( achMapB, achSwiB, pszVal, 'B' );
}//  DoMapB


//  HexDigit
//  Convert hex digit ch to it's numeric value
//
//  Used by ParseString
//
int HexDigit( int ch )
{
    if( isdigit( ch ) )
        return ch - '0';

    ch = tolower(ch);
    if( ch >= 'a' && ch <= 'f' )
        return (ch - 'a') + 10;
    else
        return 0; //silently ignore out of range chars

}//  HexDigit


//  ParseString
//  Copy quoted string in Src to Dest, translating escape sequences.
//
//  Hex sequences use 'classic' C syntax, not ANSI (always two hex digits).
//
//  Returns:
//      Pointer to char past end of parsed string
//      NULL if no quoted string found or syntax error
//
//  Assumes:
//      Destination contains enough space for result.
//      Octal and Hex sequences are properly formed

#define CHFNULL (char _far *)NULL

//  Check for unexpected null character
#define NULLCHECK if( *Src == '\0' ) return CHFNULL

//  Beware of aliasing: Src may also be Dest
#pragma optimize( "a", off)

char _far * ParseString( char _far * Dest, char _far * Src )
{

    while( *Src && *Src++ != '"' )  //scan for starting quote
        ;
    NULLCHECK;
    while( *Src && *Src != '"' )    //up to end or quote
    {
        if( *Src == '\\' )
        {
            switch( *++Src )
            {
            case '\0': return NULL; //error: escaped end-of-string

            //  Escape codes
            case 'a' :
                *Dest++ = '\a' ;    //alert (bell)
                Src++;
                break;

            case 'b' :
                *Dest++ = '\b' ;    //backspace
                Src++;
                break;

            case 'f' :
                *Dest++ = '\f' ;    //formfeed
                Src++;
                break;

            case 'n' :
                *Dest++ = '\n' ;    //linefeed
                Src++;
                break;

            case 'r' :
                *Dest++ = '\r' ;    //carriage return
                Src++;
                break;

            case 't' :
                *Dest++ = '\t' ;    //tab
                Src++;
                break;

            case 'v' :
                *Dest++ = '\v' ;    //vertical tab
                Src++;
                break;

            case '\'':
                *Dest++ = '\'' ;    //single quotation mark
                Src++;
                break;

            case '"' :
                *Dest++ = '\"' ;    //double quotation mark
                Src++;
                break;

            case '\\':
                *Dest++ = '\\' ;    //backslash
                Src++;
                break;

            //  Octal
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                *Dest  = (char)((*Src++ - '0') * 64);
                NULLCHECK;
                if( *Src < '0' || *Src > '7' )
                    return CHFNULL;
                *Dest += (char)((*Src++ - '0') * 8);
                NULLCHECK;
                if( *Src < '0' || *Src > '7' )
                    return CHFNULL;
                *Dest += (char)(*Src++ - '0');
                if( *Src < '0' || *Src > '7' )
                    return CHFNULL;
                Dest++;
                break;

            //  Hexadecimal (K&R C, not ANSI C)
            case 'x':
                Src++;
                NULLCHECK;
                if( !isxdigit(*Src) )
                    return CHFNULL;
                *Dest  = (char)(HexDigit( *Src++ ) * 16);
                NULLCHECK;
                if( !isxdigit(*Src) )
                    return CHFNULL;
                *Dest += (char)HexDigit( *Src++ );
                Dest++;
                break;

            default:
                *Dest++ = *Src++;   //copy anything else
                break;
            }
        }
        else
            *Dest++ = *Src++;   //any other character
    }
    *Dest = '\0';
    return Src;

}//  ParseString
#pragma optimize( "", on )


//  OkCancel
//
//  Displays text argument and prompts for OK or Cancel.
//
//  Returns: TRUE  user chose OK
//           FALSE user chose Cancel
//  Usage:
//      Like the Prompt function, this function is not useful interactively,
//      but is nice to have for writing macros.
//
//  Example:
//      Arg "message" OkCancel ->can ... :>can
//

PWBFUNC OkCancel( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    return (flagType)(DoMessageBox( pArg->arg.textarg.pText, NULL, NULL,
                                    MBOX_OKCANCEL | MBOX_NOHELP, 0 )
                      == MBOX_IDOK);
}// OkCancel


//  YesNo
//
//  Displays text argument and prompts for Yes or No.
//
//  Returns: TRUE  user chose Yes
//           FALSE user chose No or Cancel
//  Usage:
//      Like the Prompt function, this function is not useful interactively,
//      but is nice to have for writing macros.
//
//  Example:
//      Arg "message" YesNo ->no ... :>no
//

PWBFUNC YesNo( unsigned argData, ARG _far *pArg, flagType fMeta )
{
    return (flagType)(DoMessageBox( pArg->arg.textarg.pText, NULL, NULL,
                                    MBOX_YESNO | MBOX_NOHELP, 0 )
                      == MBOX_IDYES);
}// YesNo


//-------------------< Standard Extension Information >--------------------

struct swiDesc swiTable[] =
{
    //  Switches for Justify
    { "J2Space",  toPIF(J2Space), SWI_BOOLEAN },

    //  Switches for MapChars
    { "CharMapA", DoMapA,         SWI_EXTTEXT },
    { "CharMapB", DoMapB,         SWI_EXTTEXT },

    //  End of table
    { NULL,       NULL,           0 }
};

struct cmdDesc cmdTable[] =
{
    {"Ucase",    Ucase,    0, KEEPMETA|NOARG|LINEARG|NULLARG|BOXARG|MODIFIES },
    {"Lcase",    Lcase,    0, KEEPMETA|NOARG|LINEARG|NULLARG|BOXARG|MODIFIES },
    {"Tcase",    Tcase,    0, KEEPMETA|NOARG|LINEARG|NULLARG|BOXARG|MODIFIES },
    {"MapA2B" ,  MapA2B ,  0, KEEPMETA|NOARG|LINEARG|NULLARG|BOXARG|MODIFIES },
    {"MapB2A" ,  MapB2A ,  0, KEEPMETA|NOARG|LINEARG|NULLARG|BOXARG|MODIFIES },
    {"MapSwap",  MapSwap,  0, KEEPMETA|NOARG|LINEARG|NULLARG|BOXARG|MODIFIES },
    {"Justify",  Justify,  0, TEXTARG|NOARG|LINEARG|NULLARG|BOXARG|MODIFIES },
    {"Center",   Center,   0, NOARG|LINEARG|BOXARG|MODIFIES},
    {"MakeBox",  MakeBox,  0, NOARG|BOXARG|MODIFIES},
    {"Goto",     Goto,     0, NULLEOW|TEXTARG|BOXSTR|KEEPMETA|WINDOWFUNC },
    {"YesNo",    YesNo   , 0, TEXTARG|NOWINDOWS|ICONFOCUS },
    {"OkCancel", OkCancel, 0, TEXTARG|NOWINDOWS|ICONFOCUS },
    { NULL, NULL, 0, 0 }
};

void _cdecl EXTERNAL WhenLoaded( void )
{
    DoStatusBox( "Text Utilities Extension", NULL );

    SetKey( "Ucase",   "ALT+U" );
    SetKey( "Lcase",   "ALT+L" );
    SetKey( "Tcase",   "ALT+X" );

    SetKey( "MapB2A" , "Shift+Ctrl+U" );
    SetKey( "MapA2B" , "Shift+Ctrl+L" );
    SetKey( "MapSwap", "Shift+Ctrl+X" );

    SetKey( "Justify", "ALT+J" );
    SetKey( "Center",  "ALT+C" );
    SetKey( "Makebox", "NUM/"  );
    SetKey( "Goto",    "ALT+G" );

    //  Character maps
    //
    //  The default mapping is from full PC characters to the plain
    //  ASCII chars that approximate their meaning or graphic shape.
    //  This PC/ASCII mapping is only useful in the A->B direction
    //  because characters in CharMapB are not unique.
    //
    //  Toggling works well for mappings that are unique in both maps such
    //  as the following definitions, which toggle case, including
    //  international characters:
    //
    //  CharMapA:"abcdefghijklmnopqrstuvwxyzáëÑÜ§îÅÇ®->ÆÚõ ©ˆ|([{'"
    //  CharMapB:"ABCDEFGHIJKLMNOPQRSTUVWXYZÄíéè•ôöê?+<ØÛ$ ™˘=&)]}\""

    farstrcpy( achSwiA,
               "\"˛˛\\t\\n  \\r  " "\\x1a" "<"
               "ÄÅÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûü†°¢£§•¶ß®©™´¨≠ÆØ∞≤"
               "≥≈¥µ∂∑∏π∫ªºΩæø¿¡¬√ƒ∆«»… ÀÃÕŒœ–—“”‘’÷◊ÿŸ⁄€"
               "ÊÁËÍÎÏÌÓÔÒÚÛÙıˆ˜¯˘˙˚¸˝˛\"" );
    Swi2Map( achMapA, achSwiA );

    farstrcpy( achSwiB,
               "\"..........MF..*><V!PS=V^v><-H^v"
               "^CueaaaaceeeiiiAaEaaooouuyOUcLYRfaiounNao?....i<>##"
               "|+++++++|+++++++++-+++++++-+++++++++++++#"
               "mlPODI.EN=...SS/=d...n2*\"" );
    Swi2Map( achMapB, achSwiB );

    DoStatusBox( NULL, NULL );
    return;
}
