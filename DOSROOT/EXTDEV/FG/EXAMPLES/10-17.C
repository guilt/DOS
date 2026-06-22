#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char arrow[] = {6,1,9,2,2,9,1,19,7,2,8,1};

void main()
{
   int old_mode;

   if (fg_testmode(4,1) == 0) {
      printf("This program requires a 320 ");
      printf("x 200 CGA graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(4);
   fg_setclip(0,15,0,199);

   fg_setcolor(3);
   fg_rect(0,319,0,199);

   fg_move(10,10);
   fg_drawmask(arrow,12,10);
   fg_move(10,20);
   fg_clipmask(arrow,12,10);
   fg_move(10,30);
   fg_revmask(arrow,12,10);
   fg_move(10,40);
   fg_flipmask(arrow,12,10);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
