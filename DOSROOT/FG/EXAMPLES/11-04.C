#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int row;
   int old_mode;
   char string[17];

   old_mode = fg_getmode();

   if (fg_testmode(3,2))
      fg_setmode(3);
   else if (fg_testmode(7,2))
      fg_setmode(7);
   else {
      printf("This program requires\n");
      printf("an 80-column display.\n");
      exit(1);
      }

   fg_cursor(0);
   fg_setattr(9,7,0);

   for (row = 0; row < 25; row++) {
      sprintf(string," This is row %2d ",row);
      fg_locate(row,0);
      fg_text(string,16);
      fg_text(string,16);
      fg_text(string,16);
      fg_text(string,16);
      fg_text(string,16);
      }
   fg_waitkey();

   fg_allocate(1);
   fg_transfer(32,47,11,13,0,24,0,1);
   fg_setcolor(1);
   fg_rect(32,47,11,13);
   fg_setattr(15,1,0);
   fg_locate(12,33);
   fg_text("Press any key.",14);
   fg_waitkey();

   fg_transfer(0,15,22,24,32,13,1,0);
   fg_waitkey();

   fg_freepage(1);
   fg_setmode(old_mode);
   fg_reset();
}
