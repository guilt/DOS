#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0
#define OK    1
#define ERR   0

void main(argc,argv)
int argc;
char *argv[];
{
   char *pcxheader;
   char pcxname[13];

   pcxheader = malloc(128);
   strncpy(pcxname,argv[1],13);
   if (!check_suffix(pcxname))
   {
      printf("unable to open pcx file: %s",argv[1]);
      exit(1);
   }
   if (fg_pcxhead(pcxname,pcxheader) != 0)
   {
      printf("unable to open pcx file: %s",argv[1]);
      exit(1);
   }
   fg_svgainit(0);
   fg_setmode(fg_pcxmode(pcxheader));
   fg_showpcx(pcxname,0);

   fg_waitkey();
   fg_setmode(3);
   fg_reset();
   exit(0);
}

check_suffix(char *fname)
{
   char *strptr;
   int index;
   int error;

   error = FALSE;
   strptr = strchr(fname,'.');

   /* period in string */
   if (strptr > 0)
   {
      index = (int)(strptr - fname);
      if (index > 8)
      error = TRUE;
   }

   /* no period in string */
   else
   {
      index = strlen(fname);
      if (index > 8)
        error = TRUE;
      else
      {
        fname[index] = '.';
        strcat(fname,"pcx");
      }
   }
   if (error) return(ERR);
   return(OK);
}
