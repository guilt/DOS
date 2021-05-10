#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   char string[4];

   old_mode = fg_getmode();
   fg_svgainit(1);

   if (fg_testmode(27,1))
      fg_setmode(27);
   else if (fg_testmode(26,1))
      fg_setmode(26);
   else if (fg_testmode(25,1))
      fg_setmode(25);
   else {
      printf("This program requires an SVGA ");
      printf("with at least 512K video memory.\n");
      exit(1);
      }

   fg_setcolor(15);
   fg_text("I'm running in mode ",20);
   sprintf(string,"%d.",fg_getmode());
   fg_text(string,3);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
