#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   int hidden;
   int x;

   /* initialize the video environment */

   if (fg_testmode(13,3) == 0) {
      printf("This program requires EGA.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(13);

   /* draw the background on page two */

   fg_setpage(2);
   fg_setcolor(1);
   fg_rect(0,319,0,199);
   fg_setcolor(15);
   fg_move(160,100);
   fg_ellipse(20,20);

   /* slide the object across the screen */

   hidden = 1;
   fg_setcolor(10);
   for (x = -10; x < 320; x+=4) {
      fg_setpage(hidden);
      fg_transfer(0,319,0,199,0,199,2,hidden);
      fg_clprect(x,x+19,96,105);
      fg_setvpage(hidden);
      hidden = 1 - hidden;
      fg_waitfor(1);
      }

   /* restore the original video mode and return to DOS */

   fg_setmode(old_mode);
   fg_reset();
}
