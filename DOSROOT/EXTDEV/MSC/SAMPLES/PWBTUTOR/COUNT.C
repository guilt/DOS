// COUNT.C - Generate text statistics for text file.
// Multimodule example program used in the PWB tutorial.
//

#include <stdio.h>
#include <string.h>
#include "count.h"

// Conditional operator prevents divide by zero
#define NONZERO(val) (val ? val : 1)

// Vowels per syllable in typical English text
#define FACTOR 1.1

char Buffer[BUFFSIZE];
long Bytes      = 0;
long Characters = 0;
long Words      = 0;
long Lines      = 0;
long Letters    = 0;
long Vowels     = 0;
long Consonants = 0;
long Sentences  = 0;

int main( int argc, char *argv[] );
int CountFile( char *name );
float Syllables( long cVowels, long cWords );

int main( int argc, char *argv[] )
{
    char FileName[65];
    int curArg;

    if( argc > 1 )
    {
        for( curArg = 1; curArg < argc; curArg++ )
        {
            if( CountFile( argv[curArg] ) )
                return( 1 );

            // Reinitialize counters
            Bytes      = 0;
            Characters = 0;
            Words      = 0;
            Lines      = 0;
            Letters    = 0;
            Vowels     = 0;
            Sentences  = 0;
        }
    }
    else
    {
        // Get a file when one was not specified as an argument.
        printf( "\n\nEnter file name: " );
        if( gets( FileName ) != NULL )
            return( CountFile( FileName ) );
        else
            return 1;
    }


}

int CountFile( char *name )
{
    FILE *File;
    int nMax;
    FLAG InWord;

    // Open file in binary mode.
    if( (File = fopen( name, "rb" )) == NULL )
    {
        printf( "\nCan't open %s\n", name );
        return ( 1 );
    }

    InWord = FALSE;
    // Read file buffers
    while( ( nMax = fread( Buffer, 1, BUFFSIZE, File ) ) != 0 )
        InWord = CountWords( InWord, nMax );

    // Calculate and print the results.
    printf( "\n\nFile statistics for %s\n\n", name );
    printf( "\tBytes:      %6ld\n", Bytes );
    printf( "\tCharacters: %6ld\n", Characters );
    printf( "\tLetters:    %6ld\n", Letters );
    printf( "\tVowels:     %6ld\n", Vowels );
    printf( "\tConsonants: %6ld\n", Letters - Vowels );
    printf( "\tWords:      %6ld\n", Words );
    printf( "\tLines:      %6ld\n", Lines ? Lines : 1 );
    printf( "\tSentences:  %6ld\n\n", Sentences );

    printf( "\tWords per sentence:           %4.1f\n",
        (float)Words / NONZERO(Sentences) );

    printf( "\tLetters per word:             %4.1f\n",
        (float)Letters / NONZERO(Words) );

    printf( "\tEstimated syllables per word: %4.1f\n\n",
        (Vowels * FACTOR) / NONZERO(Words) );

    return fclose( File );

}

float Syllables( long cVowels, long cWords )
{
    return (float)((cVowels * FACTOR) / NONZERO(cWords));
}
