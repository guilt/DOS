#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int new_mode, old_mode;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(new_mode);

   fg_setcolor(15);
   fg_rect(0,319,0,199);
   fg_setcolor(10);
   fg_text("line one",8);
   fg_locate(1,0);
   fg_text("line two",8);
   fg_waitkey();

   fg_setcolor(15);
   fg_scroll(0,63,8,15,4,1);
   fg_waitkey();
   fg_scroll(0,63,12,19,-4,1);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
