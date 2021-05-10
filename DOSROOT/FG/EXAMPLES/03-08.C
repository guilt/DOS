#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   char string[4];

   old_mode = fg_getmode();

   if (fg_testmode(13,1))
      fg_setmode(13);
   else if (fg_testmode(19,1))
      fg_setmode(19);
   else if (fg_testmode(4,1))
      fg_setmode(4);
   else {
      printf("This program requires an EGA, MCGA, or CGA.\n");
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