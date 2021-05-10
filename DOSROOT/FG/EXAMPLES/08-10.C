#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;

   if (fg_testmode(13,1) == 0) {
      printf("This program requires a 320 ");
      printf("x 200 EGA graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(13);

   fg_setcolor(9);
   fg_locate(0,38);
   fg_text("resize",6);
   fg_waitkey();

   fg_erase();
   fg_resize(640,200);
   fg_setcolor(10);
   fg_locate(0,38);
   fg_text("resize",6);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
