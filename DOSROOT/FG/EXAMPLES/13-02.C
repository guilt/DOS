#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int new_mode, old_mode;

   new_mode = fg_bestmode(320,200,2);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(new_mode);
   fg_allocate(1);
   fg_sethpage(1);

   fg_setcolor(2);
   fg_rect(0,319,0,199);
   fg_setpage(1);
   fg_setcolor(1);
   fg_rect(0,319,0,199);
   fg_waitkey();

   fg_fadein(0);
   fg_waitkey();

   fg_freepage(1);
   fg_setmode(old_mode);
   fg_reset();
}
