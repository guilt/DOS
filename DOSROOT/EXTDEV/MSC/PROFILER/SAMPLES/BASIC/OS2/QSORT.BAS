'
' QSORT.BAS   Basic version of the quicksort algorithm
'
' This program is described in Chapters 2 and 3 of the Microsoft Source
' Profiler User's Guide.
'

DEFINT A-Z      ' Default type integer.

' Declare FUNCTION and SUB procedures, and the number and type of arguments:
  DECLARE FUNCTION RandInt% (Lower, Upper)
  DECLARE FUNCTION GetWords (FileName$)
  DECLARE SUB QuickSort (Low, High)
  DECLARE SUB Main ()
  DECLARE SUB Usage ()
  DECLARE SUB OutWords (NumWords,Filename$)
  DECLARE SUB Comline(argc, argv$(), Max)

' Maximum number of words to sort
CONST MAXNUMWORDS = 1500
DIM SHARED WordArray$(MAXNUMWORDS)
DIM SHARED WordIndex(MAXNUMWORDS)

Main

END

' ============================== Main ==================================
'    Initializes the SortBackup and OptionTitle arrays.  It also calls the
'    CheckScreen, BoxInit, and RandInt% procedures.
' ======================================================================
'
SUB Main STATIC

    DIM argv$(1 TO 4)

    PRINT "QSORT.BAS"
    CALL ComLine(argc, argv$(), 3)
    IF argc <> 2 THEN Usage
    PRINT "Loading "; argv$(1)
    NumWords = GetWords( argv$(1))
    ' Initialize WordIndex array
    FOR Index = 0 to NumWords
        WordIndex(Index) = Index
    NEXT Index
    PRINT "Loaded";NumWords;"words."
    PRINT "Sorting"
    IF NumWords > 0 THEN
        QuickSort 0, NumWords-1
        OutWords NumWords, argv$(2)
    END IF
END SUB

' ============================ GetWords ================================
'    Loads the text file given in the Filename$ parameter and parses
'    the output, filling in the WordArray$ array. This function returns
'    the number of words loaded.
' ======================================================================
'
FUNCTION GetWords (Filename$)
    TempChar$ = ""
    CharNumber = 0
    OPEN Filename$ FOR INPUT AS #1

    WHILE (WordNumber < MAXNUMWORDS) AND NOT EOF(1)
        TempChar = ASC(INPUT$(1, #1)):Print TempChar$;
            ' Word delimiters
            IF TempChar = 32 OR TempChar = 13 OR TempChar = 9 OR TempChar = 10 THEN
                ' Start new word unless at beginning
                IF CharNumber <> 0 THEN
                    CharNumber = 0
                    WordNumber = WordNumber + 1
                END IF
            ELSE
                ' Characters to add to word
                WordArray$(WordNumber) = WordArray$(WordNumber) + CHR$(TempChar)
                CharNumber = CharNumber + 1
            END IF
    WEND
    CLOSE #1
    GetWords =  WordNumber
END FUNCTION

' ============================== QuickSort ===================================
'   QuickSort works by picking a random "pivot" element in SortArray, then
'   moving every element that is bigger to one side of the pivot, and every
'   element that is smaller to the other side.  QuickSort is then called
'   recursively with the two subdivisions created by the pivot.  Once the
'   number of elements in a subdivision reaches two, the recursive calls end
'   and the array is sorted.
' ============================================================================
'
SUB QuickSort (Low, High)
   IF Low < High THEN

      ' Only two elements in this subdivision; swap them if they are out of
      ' order, then end recursive calls:
      IF High - Low = 1 THEN
         IF UCASE$(WordArray$(WordIndex(Low))) > UCASE$(WordArray$(WordIndex(High))) THEN
            SWAP    Low, High
         END IF
      ELSE

         ' Pick a pivot element at random, then move it to the end:
         RandIndex = RandInt%(Low, High)
         SWAP   WordIndex(High), WordIndex(RandIndex)
         Partition$ = UCASE$(WordArray$(WordIndex(High)))
         DO

            ' Move in from both sides towards the pivot element:
            I = Low: J = High
            DO WHILE (I < J) AND (UCASE$(WordArray$(WordIndex(I))) <= Partition$)
               I = I + 1
            LOOP
            DO WHILE (J > I) AND (UCASE$(WordArray$(WordIndex(J))) >= Partition$)
               J = J - 1
            LOOP

            ' If we haven't reached the pivot element, it means that two
            ' elements on either side are out of order, so swap them:
            IF I < J THEN
               SWAP WordIndex(I), WordIndex(J)
            END IF
         LOOP WHILE I < J

         ' Move the pivot element back to its proper place in the array:
         SWAP WordIndex(I), WordIndex(High)

         ' Recursively call the QuickSort procedure (pass the smaller
         ' subdivision first to use less stack space):
         IF (I - Low) < (High - I) THEN
            QuickSort Low, I - 1
            QuickSort I + 1, High
         ELSE
            QuickSort I + 1, High
            QuickSort Low, I - 1
         END IF
      END IF
   END IF
END SUB

' ============================= OutWords ==================================
'   Copies the output
'
' =========================================================================
SUB OutWords(NumWords, Filename$)
    OPEN Filename$ FOR OUTPUT AS #1
    FOR TempIndex=0 TO NumWords-1
        PRINT #1, WordArray$(WordIndex(TempIndex))
    NEXT TempIndex
    CLOSE #1
END SUB

SUB Usage
    PRINT "Performs QuickSort on a file and sends results to a file."
    PRINT "Usage: QSORT <input> <output>"
    PRINT "Where <input> is the name of the text file to sort and <output> is the"
    PRINT "name of the file to store the sorted output. "
END
END SUB
' =============================== RandInt% ===================================
'   Returns a random integer greater than or equal to the Lower parameter
'   and less than or equal to the Upper parameter.
' ============================================================================
'
FUNCTION RandInt% (Lower, Upper) STATIC
   RandInt% = INT(RND * (Upper - Lower + 1)) + Lower
END FUNCTION

'SUB procedure to get command line and split into arguments.
'Parameters:  NumArgs : Number of command line args found.
'             Args$() : Array in which to return arguments.
'             MaxArgs : Maximum number of arguments array can return.
SUB Comline(NumArgs,Args$(),MaxArgs) STATIC
CONST TRUE=-1, FALSE=0

   NumArgs=0 : In=FALSE
   'Get the command line using the COMMAND$ function.
   Cl$=COMMAND$
   L=LEN(Cl$)
   'Go through the command line a character at a time.
   FOR I=1 TO L
      C$=MID$(Cl$,I,1)
      'Test for character being a blank or a tab.
      IF (C$<>" " AND C$<>CHR$(9)) THEN
      'Neither blank nor tab. Test if you're already inside an argument.
         IF NOT In THEN
         'You've found the start of a new argument.
            'Test for too many arguments.
            IF NumArgs=MaxArgs THEN EXIT FOR
            NumArgs=NumArgs+1
            In=TRUE
         END IF
         'Add the character to the current argument.
         Args$(NumArgs)=Args$(NumArgs)+C$
      ELSE
      'Found a blank or a tab.
         'Set "Not in an argument" flag to FALSE.
         In=FALSE
      END IF
   NEXT I

END SUB
