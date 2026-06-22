// COUNTCH.C - Analyze a character.
// Part of the multimodule example program used in the PWB tutorial.
//
// Increment Letters, Vowels, and/or Sentences if appropriate.
//

#include <ctype.h>
#include <string.h>
#include "count.h"

void Analyze( char curChar, FLAG InWord )
{
    if( isalpha( curChar ) )
    {
        ++Letters;
        if( strchr( "AEIOUaeiou", curChar ) ||
            (strchr( "Yy", curChar ) && !InWord) )
            ++Vowels;
    }
    else
    {
        if( strchr( ".!?", curChar ) )
            ++Sentences;
    }

}
