#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   char bitmap[32];
   int old_mode, new_mode;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);

   fg_setcolor(9);
   fg_text("text",4);
   fg_waitkey();

   fg_move(0,7);
   fg_getmap(bitmap,4,8);
   fg_move(4,15);
   fg_drawmap(bitmap,4,8);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
