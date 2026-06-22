// COUNTBUF.C - Analyze the characters in one buffer.
// Part of the multimodule example program used in the PWB tutorial.
//
// Increment Bytes. For each char, increment Characters, Lines,
// and/or Words if appropriate. For each character, call Analyze.
// (A character is defined as printable ASCII.)
//

#include "count.h"

FLAG CountWords( FLAG InWord, int nChars )
{
    int Scan;
    char curCode;

    Bytes += (long)nChars;

    for( Scan = 0; Scan <= nChars; ++Scan )
    {
        curCode = Buffer[Scan];
        if( curCode == '\n' )
            ++Lines;
        if( !InWord )
        {
            if( curCode > ' ' )
            {
                Analyze( curCode, InWord );
                InWord = TRUE;
                ++Words;
                ++Characters;
            }
        }
        else
        {
            if( curCode <= ' ' )
                InWord = FALSE;
            else
            {
                ++Characters;
                Analyze( curCode, InWord );
            }
        }
    }
    return InWord;
}
