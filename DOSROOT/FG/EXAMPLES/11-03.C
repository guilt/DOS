#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int row;
   int new_mode, old_mode;
   char string[21];

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

   for (row = 0; row < 25; row++) {
      sprintf(string,"   This is row %2d   ",row);
      fg_locate(row,0);
      fg_text(string,20);
      fg_text(string,20);
      }
   fg_waitkey();

   fg_allocate(1);
   fg_sethpage(1);
   fg_save(96,223,88,111);
   fg_setcolor(1);
   fg_rect(96,223,88,111);
   fg_setcolor(15);
   fg_locate(12,13);
   fg_text("Press any key.",14);
   fg_waitkey();

   fg_restore(96,223,88,111);
   fg_waitkey();

   fg_freepage(1);
   fg_setmode(old_mode);
   fg_reset();
}
