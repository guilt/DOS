#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

#define VISUAL 0
#define HIDDEN 1

int xmin[] = {  0, 96,192,  0, 96,192,  0, 96,192,  0, 96,192};
int ymax[] = { 49, 49, 49, 99, 99, 99,149,149,149,199,199,199};

void main()
{
   int new_mode, old_mode;
   int frame, offset;
   int i, x, y;

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

   /* display the animated object against each background */

   fg_setcolor(10);
   offset = -10;
   for (i = 1; i < 12; i++) {
      x = xmin[i];
      y = ymax[i];
      fg_transfer(0,95,0,49,x,y,HIDDEN,HIDDEN);
      fg_setclip(x,x+95,0,199);
      fg_clprect(x+offset,x+offset+19,y-29,y-20);
      offset += 10;
      }

   /* slide the object across the background three times */

   for (i = 0; i < 36; i++) {
      frame = i % 12;
      x = xmin[frame];
      y = ymax[frame];
      fg_transfer(x,x+95,y-49,y,112,124,HIDDEN,VISUAL);
      fg_waitfor(2);
      }

   /* restore the original video mode and return to DOS */

   fg_freepage(HIDDEN);
   fg_setmode(old_mode);
   fg_reset();
}
