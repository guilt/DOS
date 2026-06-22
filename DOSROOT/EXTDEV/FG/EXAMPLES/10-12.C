#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   char bitmap[256];
   int old_mode, new_mode;
   int width;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);
   width = (int)fg_imagesiz(32,1);

   fg_setcolor(7);
   fg_rect(0,31,0,7);
   fg_setcolor(9);
   fg_text("text",4);
   fg_waitkey();

   fg_move(0,7);
   fg_getimage(bitmap,width,8);
   fg_move(4,15);
   fg_drwimage(bitmap,width,8);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
