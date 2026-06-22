/* INDENT.C -- Sample autoindentation handler
 *
 * Copyright (C) 1992, Microsoft Corporation, All rights reserved
 *
 * Demonstrates PWB 2.x autoindentation handling
 *
 *Switches:
 *
 *  i_suffixes:.c .h .cxx .hxx .cpp .hpp ;list of suffixes to handle
 *  i_softcr:yes                         ;enable this handler
 *  Simplecr:no                          ;perform only simple indent
 *
 *Functions:
 *
 *  None (all action is performed by an event handler)
 *
 *Remarks:
 *
 *  The i_suffixes switch lists the filename extensions for which
 *  this extension should handle automatic indentation. If '.*' is
 *  specified, handles all files. Note that the wildcard feature is
 *  not supported by the standard language extensions.
 *
 *  The i_softcr switch turns this handler on and off.
 *
 *  When the Simplecr switch is turned on, this handler indents
 *  to the same level as the current line. When turned off,
 *  special indentation for C/C++ is performed.
 *
 */
#pragma warning( disable:4001 )  //Allow single-line comments
#pragma warning( disable:4100 )  //Allow unused arguments
#include <ext.h>

void _cdecl EXPORT WhenLoaded( void );

//  Text switch handler
char far * pascal EXTERNAL GetSetISuffixList( char far *pszISuffixList,
                                              flagType fQuery );

//  Private utilities
static int pascal CKeywordLookup( char far * s );
static flagType pascal parseline( char far *pbuf,
                                  char far * far *ppbegtok,
                                  char far * far *ppendtok );
static flagType pascal IsISuffix( char far *szSuffix );

//  Event handler
flagType pascal EXPORT ISoftcr( EVTargs far *lpevtargs );


//----------------------- Miscellaneous Data -----------------------//

// global common buffer.
//
linebuf lbTmp;

// C/C++ keyword table for ISoftcr routine
// Future enhancement:
//   Change CKeywordLookup and use a text switch for the table.
static char * CKeywords[] =
{
    "if"        ,
    "else"      ,
    "for"       ,
    "while"     ,
    "do"        ,
    "case"      ,
    "default"   ,

    //  C++
    "private"   ,
    "protected" ,
    "public"    ,

    NULL
};

//  Switch names
char SzISuffixes[]  = "i_suffixes";
char SzISoftcr[]    = "i_softcr";
char SzISimplecr[]  = "Simplecr";

// default list of suffixes associated with the <i_suffixes> switch
//
buffer SzISuffixList = ".c .h .cxx .hxx .cpp .hpp";

// storage for Boolean switches
//
flagType fISoftcr   = TRUE;     //handle autoindentation
flagType fISimplecr = FALSE;    //do only simple autoindentation


//------------------- Standard PWB extension data ------------------//

// Command description table. This extension defines no commands.
//
struct cmdDesc cmdTable[] = { { NULL, NULL, 0, 0 } };

// Switch description table.
//
struct swiDesc swiTable[] =
{
    { (char far *)SzISuffixes, GetSetISuffixList, SWI_EXTTEXT },
    { (char far *)SzISoftcr,   toPIF(fISoftcr),   SWI_BOOLEAN },
    { (char far *)SzISimplecr, toPIF(fISimplecr), SWI_BOOLEAN },
    { NULL,                    NULL,              0 }
};

// Event structure to register
static  EVT EvtNewline = { 0, ISoftcr, 0, EVT_NEWLINE, 0 };

void _cdecl EXPORT WhenLoaded( void )
{
    RegisterEvent (&EvtNewline);
}

//------------------------- GetSetISuffixList ---------------------//
//
// Set/get the current value of the <i_suffixes> switch.
//
// Input:
//  pszISuffixList - pointer to suffix text
//  fQuery         - boolean to indicate whether we are getting or setting
//
// Output:
//  fQuery TRUE: return pointer to SzISuffixList
//  fQuery FALSE: return NULL
//
//-----------------------------------------------------------------//

char far * pascal EXTERNAL GetSetISuffixList (
        char far *pszISuffixList,
        flagType fQuery
        )
{
    if( fQuery )
        return ((char far *)SzISuffixList);
    farstrcpy (SzISuffixList, pszISuffixList);
    return (NULL);
}

//------------------------ CKeywordLookup -------------------------//
//
// Locate string in CKeywords table.
//
// Input:
//  s           - pointer to string to search for in CKeyword table
//
// Output:
//  Returns index+1 of first string s that is in table, or zero.
//
//-----------------------------------------------------------------//

static int pascal CKeywordLookup( char far *s )
{
    int i;

    for( i=0; CKeywords[i]; i++ )
        if( !farstricmp( CKeywords[i], s ) )
            return i+1;
    return 0;

} // CKeywordLookup


static flagType pascal parseline (
        char far *pbuf,
        char far * far *ppbegtok,
        char far * far *ppendtok
        )
{
    char far *p1, far *p2;

    p1 = pbuf;
    while( *p1 == ' ' )
        p1++;                           // skip whitespace

    if( !*p1 )
        return FALSE;
    if( (p2 = farstrchr( p1, ' ' )) != NULL ) // find blank
    {
        *p2++ = 0;
        p2 += farstrlen( p2 ) - 1;
        while( *p2 )
            if( *p2 == ' ' )
                break;
            else
                p2--;
        if( !*++p2 )
            p2 = p1;    //no other token on line, end same as begin
    }
    else
        p2 = p1;
    *ppbegtok = p1;
    *ppendtok = p2;
    return TRUE;
}


//----------------------------- IsISuffix -------------------------//
//
// Determine whether a file suffix occurs in the list of "known"
// suffixes given by the <i_suffixes> switch.
//
// Input:
//  szSuffix    - the suffix we are testing for.
//
// Output:
//      TRUE:  file suffix recognized.
//      FALSE: file suffix not recognized.
//
//-----------------------------------------------------------------//

static flagType pascal IsISuffix( char far *szSuffix )
{
    char far *pbeg, far *pend;

    // check suffix to determine whether szSuffix matches a suffix given
    // by the <i_suffixes> switch.

    // if list contains .*, match all extensions
    if( farstrstr( SzISuffixList, ".*" ) != NULL )
        return TRUE;

    pend = SzISuffixList;
    do {
        if( (pbeg = farstrchr( pend, '.' )) != NULL )
            return FALSE;
        if( (pend = farstrchr( pbeg, ' ' )) != NULL )
            pend = pbeg + farstrlen( pbeg );

    } while(    farstrlen( szSuffix ) != (pend - pbeg )
             || farstrnicmp( pbeg, szSuffix, pend - pbeg ) );

    return TRUE;

} // IsISuffix

//----------------------------- ISoftcr ---------------------------//
//
// Perform C soft CR processing.
//
// Algorithm:
//
//  Given that you have just entered a newline at the end of a line:
//      If file suffix is found in <i_suffixes> switch then:
//      If Simple flag set, indent same as current
//      else if the original line begins with "}", tab out
//      else if the original line ends with "{" or begins with a keyword,
//              tab in
//      else if the line preceding the original line doen't end with "{"
//           but does begin with a keyword, tab out
//
// Input:
//  lpevtargs  FAR pointer to event arguments
//
// Output:
//      TRUE:  File suffix recognized. Tab as indicated by tabmode.
//      FALSE: File suffix not recognized. Let another extension or
//             PWB handle the autoindent.
//
//------------------------------------------------------------------//

flagType pascal EXPORT ISoftcr( EVTargs far *lpevtargs )
{

    char far *pbeg, far *pend, far *p;
    flagType fEmpty = TRUE;

    // check suffix to determine whether we are interested in this file.
    // if current file's suffix matches a suffix given by the
    // <i_suffixes> switch, then process the EVT_NEWLINE.
    //
    if( fISoftcr && IsISuffix( lpevtargs->EvtNewline.lpszSuffix ) )
    {

        GetLine( lpevtargs->EvtNewline.line, (char far *)lbTmp,
                 lpevtargs->EvtNewline.pFile );

        // Skip whitespace.
        // GetLine translates tabs to spaces...
        //
        p = lbTmp;
        while( *p == ' ' )
            p++;
        if( !*p )
        {
            p = lbTmp;
            fEmpty = TRUE;
        }

        // calculate new column position based on current line.
        //
        lpevtargs->EvtNewline.newcol = p - (char far *)lbTmp;

        // determine whether to tab forward or backward from there based
        // on a lookup of certain C keywords...
        //
        if( !fISimplecr && parseline( lbTmp, &pbeg, &pend ) )
        {
            if( *pbeg == '}' )
            {
                lpevtargs->EvtNewline.tabmode = TM_BACKWARD;
                return TRUE;
            }
            else
            if(  (pend && *pend == '{' ) || CKeywordLookup( pbeg ) )
            {
                lpevtargs->EvtNewline.tabmode = TM_FORWARD;
                return TRUE;
            }
            else
            if( lpevtargs->EvtNewline.line )
            {
                GetLine( lpevtargs->EvtNewline.line-1, (char far *)lbTmp,
                         lpevtargs->EvtNewline.pFile );
                if( parseline( lbTmp, &pbeg, &pend ) )
                {
                    if(  !(pend && *pend == '{') && CKeywordLookup( pbeg ) )
                    {
                        lpevtargs->EvtNewline.tabmode = TM_BACKWARD;
                        return TRUE;
                    }
                }
            }
        }

        // Simple flag set or fell through special conditions: Indent to
        // same level as previous line, or cursor column if blank
        //
        if( fEmpty )    // current line empty
        {
            COL x; LINE y;
            GetCursor( (COL far *)&x, (LINE far *)&y );
            lpevtargs->EvtNewline.newcol = x;
        }
        lpevtargs->EvtNewline.tabmode = TM_NONE;
        return TRUE;
    }
    return FALSE;

}
