 /*
 * QSORT.C   C version of the quicksort algorithm
 *
 * This program is described in Chapters 2 and 3 of the Microsoft Source
 * Profiler User's Guide.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macro to get a random integer within a specified range */
#define getrandom( min, max ) ((rand() % (int)(((max)+1) - (min))) + (min))

/* Maximum number of words to sort */
#define MAXNUMWORDS 1500
/* Maximum word length (in characters) */
#define MAXWORDSIZE 15


char WordArray[MAXNUMWORDS][MAXWORDSIZE];
int  WordIndex[MAXNUMWORDS];

void usage(void);
int  GetWords(char *filename);
void QuickSort(int Low, int High );
void SwapWords( int index1, int index2 );
void OutWords(int NumWords, char *filename);

/* main - The main function calls functions that load the input file,
 * sort it, and save the output to another file. It also calls the usage
 * statement on bad command-line arguments and sets up the index array.
 */
int main (int argc, char *argv[])
{
    int NumWords;
    int index;
    puts( "QSORT.C" );
    if ( argc != 3 )
        usage();
    printf( "Loading %s\n", argv[1] );
    NumWords = GetWords( argv[1] );
    /* Initialize WordIndex array */
    for ( index = 0; index < NumWords; index++ )
        WordIndex[index] = index;
    printf( "Loaded %i words.\n", NumWords );
    puts( "Sorting" );
    if ( NumWords > 0 )
    {
        QuickSort( 0, NumWords-1 );
        OutWords( NumWords, argv[2] );
    }
}

/* GetWords - GetWords loads and parses an ASCII text file and stores each
 * word into WordArray. Returns the number of words read.
 */
int GetWords(char *filename)
{
    FILE    *FileHandle;
    int     WordNumber = 0;
    int     CharNumber = 0;
    char    TempChar   = '\0';

    FileHandle = fopen(filename, "r");
    if (FileHandle == NULL)
        {
        puts("Error opening input file.");
        return 0;
        }

    while ((WordNumber < MAXNUMWORDS) && (TempChar != EOF))
    {
        TempChar = fgetc(FileHandle);
        switch(TempChar)
        {
            /* Word delimiters */
            case ' ' :
            case '\n':
            case '\t':
                /* Start new word unless at beginning */
                if (CharNumber != 0)
                {
                    WordArray[WordNumber][CharNumber] = '\0';
                    CharNumber = 0;
                    WordNumber++;
                }
                break;
            /* Quit if at end of file */
            case EOF:
                break;
            /* Characters to add to word */
            default:
                WordArray[WordNumber][CharNumber] = TempChar;
                /* Truncate word if too long */
                if (++CharNumber >= MAXWORDSIZE)
                {
                    WordArray[WordNumber][CharNumber-1] = '\0';
                    CharNumber = 0;
                    WordNumber++;
                    /* Skip over remaining characters */
                    while ((TempChar != ' ') && (TempChar != '\n') &&
                           (TempChar != '\t'))
                         TempChar = fgetc(FileHandle);
                }
                break;
        }
    }
    fclose( FileHandle );
    return  WordNumber;
}

/* QuickSort - QuickSort works by picking a random "pivot" element,
 * then moving every element that is bigger to one side of the pivot,
 * and every element that is smaller to the other side. QuickSort is
 * then called recursively with the two subdivisions created by the pivot.
 * Once the number of elements in a subdivision reaches two, the recursive
 * calls end and the array is sorted.
 */
void QuickSort( int Low, int High )
{
    int Up, Down;

    char cBreak[MAXWORDSIZE];

    if( Low < High )
    {
        /* Only two elements in this subdivision; swap them if they are
         * out of order, then end recursive calls.
         */
        if( (High - Low) == 1 )
        {
            if( stricmp( WordArray[WordIndex[Low]], WordArray[WordIndex[High]] ) > 0 )
                SwapWords( Low, High );
        }
        else
        {
            /* Pick a pivot element at random, then move it to the end. */
            SwapWords( High, getrandom( Low, High ) );
            strcpy( cBreak, WordArray[WordIndex[High]] );
            do
            {
                /* Move in from both sides towards the pivot element. */
                Up = Low;
                Down = High;
                while( (Up < Down) &&
                       (stricmp( WordArray[WordIndex[Up]], cBreak ) <= 0) )
                        Up++;
                while( (Down > Up) &&
                       (stricmp( WordArray[WordIndex[Down]], cBreak ) >= 0) )
                        Down--;
                /* If we haven't reached the pivot, it means that two
                 * elements on either side are out of order, so swap them.
                 */
                if( Up < Down )
                    SwapWords( Up, Down );
            } while ( Up < Down );

            /* Move pivot element back to its proper place in the array. */
            SwapWords( Up, High );

            /* Recursively call the QuickSort procedure (pass the smaller
             * subdivision first to use less stack space).
             */
            if( (Up - Low) < (High - Up) )
            {
                QuickSort( Low, Up - 1 );
                QuickSort( Up + 1, High );
            }
            else
            {
                QuickSort( Up + 1, High );
                QuickSort( Low, Up - 1 );
            }
        }
    }
}

/* SwapWords - SwapWords swaps the WordIndex index values of two words,
 * thereby swapping the indexed positions of the words.
 */
void SwapWords( int index1, int index2 )
{
    int     TempIndex;
    TempIndex = WordIndex[index1];
    WordIndex[index1] = WordIndex[index2];
    WordIndex[index2] = TempIndex;
}

/* OutWords - OutWords writes the sorted array of words to a file.
 */
void OutWords(int NumWords, char *filename)
{
    FILE *FileHandle;
    int TempIndex;
    FileHandle = fopen(filename, "w");
    if (FileHandle == NULL)
        {
        puts("Error opening output file.");
        return;
        }
    for (TempIndex=0; TempIndex < NumWords; TempIndex++ )
        if ( fputs( WordArray[WordIndex[TempIndex]], FileHandle ) == EOF)
        {
            puts("Error writing output file.");
            break;
        }
        else
            fputs( "\n", FileHandle );
    fclose( FileHandle );
}

/* usage - The usage function displays the syntax of QSORT and exits to the
 * system.
 */
void    usage(void)
{
    puts("Performs QuickSort on a file and sends results to a file.");
    puts("Usage: QSORT <input> <output>");
    puts("Where <input> is the name of the text file to sort and <output> is the");
    puts("name of the file to store the sorted output.");
    exit (0);
}
