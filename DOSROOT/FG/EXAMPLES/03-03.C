#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();

   if (fg_testmode(3,1))
      fg_setmode(3);
   else if (fg_testmode(7,1))
      fg_setmode(7);
   else {
      printf("This program requires\n");
      printf("an 80-column display.\n");
      exit(1);
      }

   fg_cursor(0);

   fg_setcolor(15);
   fg_text("Hello, world.",13);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
