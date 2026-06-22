#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   int new_mode;
   char string[4];

   old_mode = fg_getmode();
   new_mode = fg_bestmode(320,200,1);

   if (new_mode < 0) {
      printf("This program requires a 320 by 200 graphics mode.\n");
      exit(1);
      }

   fg_setmode(new_mode);

   fg_setcolor(15);
   fg_text("I'm running in mode ",20);
   sprintf(string,"%d.",new_mode);
   fg_text(string,3);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
