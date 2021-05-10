#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   int x;

   /* initialize the video environment */

   if (fg_testmode(13,1) == 0) {
      printf("This program requires EGA.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(13);
   fg_setfunc(3);

   /* draw some type of background */

   fg_setcolor(15);
   fg_rect(0,319,0,199);

   /* move the object across the screen */

   fg_setcolor(10^15);
   for (x = -20; x < 320; x+=5) {
      fg_clprect(x,x+19,95,104);
      fg_waitfor(1);
      fg_clprect(x,x+19,95,104);
      }

   /* restore the original video mode and return to DOS */

   fg_setmode(old_mode);
   fg_reset();
}
