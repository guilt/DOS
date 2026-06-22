#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int new_mode, old_mode;
   int x;

   /* initialize the video environment */

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(new_mode);

   /* move the object across the screen */

   for (x = -20; x < 320; x+=5) {
      fg_setcolor(10);
      fg_clprect(x,x+19,95,104);
      fg_waitfor(1);
      fg_setcolor(0);
      fg_clprect(x,x+19,95,104);
      }

   /* restore the original video mode and return to DOS */

   fg_setmode(old_mode);
   fg_reset();
}
