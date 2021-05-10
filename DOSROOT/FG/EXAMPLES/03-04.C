#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   int new_mode;

   old_mode = fg_getmode();
   new_mode = fg_bestmode(80,25,1);

   if (new_mode < 0) {
      printf("This program requires\n");
      printf("an 80-column display.\n");
      exit(1);
      }

   fg_setmode(new_mode);
   fg_cursor(0);

   fg_setcolor(15);
   fg_text("Hello, world.",13);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
