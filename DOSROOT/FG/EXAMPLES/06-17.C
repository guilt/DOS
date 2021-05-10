#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode, new_mode;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0) {
      printf("This program requires a 320 x 200 ");
      printf("graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);

   fg_setcolor(10);
   fg_move(100,50);
   fg_drawrel(120,0);
   fg_drawrel(0,100);
   fg_drawrel(-120,0);
   fg_drawrel(0,-100);

   fg_setcolor(9);
   fg_move(160,80);
   fg_drawrel(30,20);
   fg_drawrel(-30,20);
   fg_drawrel(-30,-20);
   fg_drawrel(30,-20);
   fg_waitkey();

   fg_setcolor(10);
   fg_paint(160,70);
   fg_waitkey();

   fg_setcolor(15);
   fg_paint(160,100);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
