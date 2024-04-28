/*-------------------------------------------------------------------------*/
/*                                   PARSE.C                               */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Reads a PLIST generated tab-delimited file, parses the file and creates */
/* an ASCII (tab-delimited) report that calculates the percentage of time  */
/* or hits.                                                                */
/*                                                                         */
/*-------------------------------------------------------------------------*/

#include <stdio.h>

FILE  *fpIn;
FILE  *fpOut;

typedef int BOOL;

#define TRUE    1
#define FALSE   0

                                // Def's for identifier tags in input file
#define BANNER      0           // Version & Banner
#define METHOD      1           // Profiling Method
#define TIME        2           // Cumulative Time values
#define HITS        3           // Cumulative Hit values
#define MEMTIME     4           // Time spent in different memory drivers
#define FUNCDETAIL  6           // Function detail line
#define LINEDETAIL  7           // Line detail line

#define LINE_COUNT  321         // Identifier for Line Counting method
#define LINE_TIME   322         // Identifier for Line Timing method
#define LINE_SAMPLE 323         // Identifier for Line Sampling method
#define LINE_COVER  324         // Identifier for Line Coverage method

#define FUNC_COUNT  421         // Identifier for Function Counting method
#define FUNC_TIME   422         // Identifier for Function Timing method
#define FUNC_SAMPLE 423         // Identifier for Function Sampling method
#define FUNC_COVER  424         // Identifier for Function Coverage method

/*--- Input format strings ---*/

#define FMT_BANNER      "%d\t%d\t%s"
#define FMT_METHOD      "%d\t%d\t%s"
#define FMT_TIME        "%d\t%lf\t%lf\t%d"
#define FMT_HITS        "%d\t%ld\t%ld\t%ld"
#define FMT_MEMTIME     "%d\t%ld\t%ld\t%ld\t%ld"
#define FMT_FUNCDETAIL  "%d\t%s\t%s\t%ld\t%ld\t%lf\t%lf\t%s"
#define FMT_LINEDETAIL  "%d\t%s\t%s\t%ld\t%ld\t%lf"

/*--- Output format strings ---*/

#define FMT_LINE_COUNT  "%-12s\t%5ld\t%5ld\t%7.3lf%%\n"
#define FMT_LINE_TIME   "%-12s\t%5ld\t%7.3lf\t%7.3lf%%\n"
#define FMT_LINE_SAMPLE FMT_LINE_COUNT
#define FMT_LINE_COVER  "%-12s\t%ld\t%s\n"
#define FMT_FUNC_COUNT  "%-20s\t%5ld\t%7.3lf%%\n"
#define FMT_FUNC_TIME   "%-20s\t%7.3lf\t%7.3lf%%\n"
#define FMT_FUNC_SAMPLE FMT_FUNC_COUNT
#define FMT_FUNC_COVER  "%-20s\t%s\n"

/*--- Error Messages ---*/

#define FILEOPENERR "\n\nERROR: Unable to open input file %s\n\n"
#define USAGE_MSG   "\n\nUSAGE: PARSE inputfile [outputfile]\n\n"
#define ERR_GENRPT  "\n\nERROR: Error while parsing file, line #%ld\n\n"

/*-------------------------------------------------------------------------*/

#define LINE_ERROR(x,y) if (x!=y) return lInputLineCnt;

/*-------------------------------------------------------------------------*/

BOOL    pascal Initialize     (int argc, char **argv);
void    pascal CleanUp        (void);
BOOL    pascal GenerateReport (void);
void    pascal Header         (char   *szProgName, int iMethod);

/*-------------------------------------------------------------------------*/
/*                                  MAIN                                   */
/*-------------------------------------------------------------------------*/

main (int argc, char **argv)

{
 long ErrorLine;

 if ( Initialize(argc, argv) )
    {
    if ((ErrorLine=GenerateReport()) != 0)
       {
       printf (ERR_GENRPT, ErrorLine);
       }
    CleanUp();
    }
}

/*-------------------------------------------------------------------------*/
/*                            GenerateReport                               */
/*                                                                         */
/* Reads input file (line-by-line).  Each line must have the appropriate   */
/* line indicator tag as the first element.  If the line indicator tag     */
/* differs from the expected value, and error is issued.                   */
/*                                                                         */
/* Once the cumulative header information is parsed (identifier 0-4), this */
/* function outputs information based on the type of input file on a line  */
/* by line basis.                                                          */
/*-------------------------------------------------------------------------*/

#define BUFLEN  256

BOOL pascal GenerateReport ()

{
 int    iRetValue;
 int    iIdentTag=0;
 long   lInputLineCnt=0;
 BOOL   fFirstTime = TRUE;
 int    iLineIdent, iVersion, iMethod;
 char   szBuffer[BUFLEN];
 int    iCallDepth;
 double dTotalTime, dOutsideTime;
 long   lTotalHits, lUnits, lUnitsHit;
 long   lDOSSamples, lEMSSamples, lXMSSamples, lUnknownSamples;
 long   lLineNo, lCount;
 double dTime, dChildTime;
 char   szProgName[15], szSource[15], szFuncName[128];

 while (!feof(fpIn))
    {
    lInputLineCnt++;

    switch ( iIdentTag )
       {
       case BANNER:
          fscanf(fpIn, FMT_BANNER, &iLineIdent,
                                   &iVersion,
                                   szBuffer);
          fgets (szBuffer, BUFLEN, fpIn);           //--- Clean off EOL
          LINE_ERROR (iIdentTag, iLineIdent);
          iIdentTag++;
          break;

       case METHOD:
          fscanf(fpIn, FMT_METHOD, &iLineIdent,
                                   &iMethod,
                                   szBuffer);
          fgets (szBuffer, BUFLEN, fpIn);           //--- Clean off EOL
          LINE_ERROR (iIdentTag, iLineIdent);
          iIdentTag++;
          break;

       case TIME:
          iRetValue = fscanf (fpIn, FMT_TIME, &iLineIdent,
                                  &dTotalTime,
                                  &dOutsideTime,
                                  &iCallDepth);
          LINE_ERROR (iIdentTag, iLineIdent);
          iIdentTag++;
          break;

       case HITS:
          fscanf (fpIn, FMT_HITS, &iLineIdent,
                                  &lTotalHits,
                                  &lUnits,
                                  &lUnitsHit);
          LINE_ERROR (iIdentTag, iLineIdent);
          iIdentTag++;
          break;

       case MEMTIME:
          fscanf (fpIn, FMT_MEMTIME, &iLineIdent,
                                     &lDOSSamples,
                                     &lEMSSamples,
                                     &lXMSSamples,
                                     &lUnknownSamples);
          LINE_ERROR (iIdentTag, iLineIdent);
          iIdentTag += (iMethod >= 400) ? 2 : 3;
          break;

       case FUNCDETAIL:
          iRetValue = fscanf (fpIn, FMT_FUNCDETAIL, &iLineIdent,
                                                    szProgName,
                                                    szSource,
                                                    &lLineNo,
                                                    &lCount,
                                                    &dTime,
                                                    &dChildTime,
                                                    szFuncName);
          if (iRetValue != 8) break;
          LINE_ERROR (iIdentTag, iLineIdent);

          if (fFirstTime)
             {
             Header (szProgName, iMethod);
             fFirstTime = FALSE;
             }

          switch (iMethod)
             {
             case FUNC_COUNT:
             case FUNC_SAMPLE:
                fprintf (fpOut, FMT_FUNC_COUNT, szFuncName, lCount, ((double)lCount/(double)lTotalHits)*100.0);
                break;

             case FUNC_TIME:
                fprintf (fpOut, FMT_FUNC_TIME,  szFuncName, dTime,  (dTime/dTotalTime)*100.0);
                break;

             case FUNC_COVER:
                fprintf (fpOut, FMT_FUNC_COVER, szFuncName, (lCount)?"HIT":"NOT HIT");
                break;

             }
          break;

       case LINEDETAIL:
          iRetValue = fscanf (fpIn, FMT_LINEDETAIL, &iLineIdent,
                                                    szProgName,
                                                    szSource,
                                                    &lLineNo,
                                                    &lCount,
                                                    &dTime);
          if (iRetValue != 6) break;
          LINE_ERROR (iIdentTag, iLineIdent);

          if (fFirstTime)
             {
             Header (szProgName, iMethod);
             fFirstTime = FALSE;
             }

          switch (iMethod)
             {
             case LINE_COUNT:
             case LINE_SAMPLE:
                fprintf (fpOut, FMT_LINE_COUNT, szSource, lLineNo, lCount, ((double)lCount/(double)lTotalHits)*100.0);
                break;

             case LINE_TIME:
                fprintf (fpOut, FMT_LINE_TIME,  szSource, lLineNo, dTime, (dTime/dTotalTime)*100.0);
                break;

             case LINE_COVER:
                fprintf (fpOut, FMT_LINE_COVER, szSource, lLineNo, (lCount)?"HIT":"NOT HIT");
                break;

             default:
                break;
             }
          break;

       default:
          return -1;
          break;
       }
    }
 return 0;
}

/*-------------------------------------------------------------------------*/
/*                                  Header                                 */
/*                                                                         */
/* Prints out base information at the top of each run.  The information is */
/* based on the profiling method.                                          */
/*-------------------------------------------------------------------------*/

void pascal Header (char *szProgName, int iMethod)

{
 fprintf (fpOut, "Microsoft Source Profiler v1.00 - Sample PLIST /T program\n\n");
 if (iMethod >= 400)
    fprintf (fpOut, "Profiling program %s for function ", szProgName);
 else
    fprintf (fpOut, "Profiling program %s for line ", szProgName);

 switch (iMethod)
    {
    case FUNC_COUNT:
    case LINE_COUNT:
        fprintf (fpOut, "counts\n");
        break;
    case FUNC_TIME:
    case LINE_TIME:
        fprintf (fpOut, "times\n");
        break;
    case FUNC_SAMPLE:
    case LINE_SAMPLE:
        fprintf (fpOut, "sampling\n");
        break;
    case FUNC_COVER:
    case LINE_COVER:
        fprintf (fpOut, "coverage\n");
        break;
    }
 fprintf (fpOut, "\n");
}

/*-------------------------------------------------------------------------*/
/*                               Initialize                                */
/*                                                                         */
/* Opens the file pointers for input and output.  If only an input file    */
/* is entered, the output is STDOUT, by default.                           */
/*-------------------------------------------------------------------------*/

BOOL pascal Initialize (int argc, char **argv)

{
 switch (argc)
    {
    case 2:   //--- Open input, write output to screen
        if ( (fpIn=fopen(*(argv+1), "r")) == NULL )
           {
           printf (FILEOPENERR, *(argv+1));
           return FALSE;
           }
        fpOut = stdout;
        break;

    case 3:   //--- Open input, write output to file
        if ( (fpIn=fopen(*(argv+1), "r")) == NULL )
           {
           printf (FILEOPENERR, *(argv+1));
           return FALSE;
           }

        if ( (fpOut=fopen(*(argv+2), "w")) == NULL )
           {
           printf (FILEOPENERR, *(argv+2));
           return FALSE;
           }

        break;

    default:  //--- Print usage message
       printf (USAGE_MSG);
       return FALSE;
       break;
    }

 return TRUE;
}


/*-------------------------------------------------------------------------*/
/*                                CleanUp                                  */
/*-------------------------------------------------------------------------*/

void pascal CleanUp()

{
 fflush (fpIn);
 fflush (fpOut);
 fclose (fpIn);
 fclose (fpOut);

 return;
}
/*-------------------------------------------------------------------------*/
/*                              End of PARSE.C                             */
/*-------------------------------------------------------------------------*/
