#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

#define VISUAL 0
#define HIDDEN 1

void main()
{
   int new_mode, old_mode;
   int frame, offset;
   int i;

   /* initialize the video environment */

   new_mode = fg_bestmode(320,200,2);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(new_mode);
   fg_allocate(HIDDEN);

   /* draw the background in the upper left corner */

   fg_setpage(HIDDEN);
   fg_setcolor(1);
   fg_rect(0,95,0,49);
   fg_setcolor(15);
   fg_move(48,25);
   fg_ellipse(20,20);

   /* copy it to the center of the visual page */

   fg_transfer(0,95,0,49,112,124,HIDDEN,VISUAL);

   /* slide the object across the background three times */

   fg_setcolor(10);
   for (i = 0; i < 36; i++) {
      frame  = i % 12;
      offset = 10 * frame - 10;
      fg_transfer(0,95,20,29,112,105,HIDDEN,HIDDEN);
      fg_rect(112+offset,131+offset,96,105);
      fg_transfer(112,207,96,105,112,105,HIDDEN,VISUAL);
      fg_waitfor(2);
      }

   /* restore the original video mode and return to DOS */

   fg_freepage(HIDDEN);
   fg_setmode(old_mode);
   fg_reset();
}
