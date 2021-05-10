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

   fg_setcolor(7);
   fg_rect(0,319,0,199);
   fg_setcolor(9);
   fg_locate(12,18);
   fg_text("test",4);
   fg_waitkey();

   fg_allocate(1);
   fg_copypage(0,1);
   fg_erase();
   fg_waitkey();

   fg_copypage(1,0);
   fg_waitkey();

   fg_freepage(1);
   fg_setmode(old_mode);
   fg_reset();
}
