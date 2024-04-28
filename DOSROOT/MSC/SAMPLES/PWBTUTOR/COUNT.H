// count.h - Global definitions for the COUNT program.
// Part of the multimodule example program used in the PWB tutorial.
//

typedef enum { FALSE = 0, TRUE = 1 } FLAG;

FLAG CountWords( FLAG InWord, int nMax );
void Analyze( char code, FLAG InWord );
float Syllables( long cVowels, long cWords );

#define BUFFSIZE 512    // Small buffer for debugging
extern char Buffer[BUFFSIZE];
extern long Bytes, Characters, Words, Lines, Letters, Vowels, Sentences;
