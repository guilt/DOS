#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode, new_mode;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 19) {
      printf("This program requires a ");
      printf("256-color graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);

   fg_setcolor(9);
   fg_text("text",4);
   fg_waitkey();

   fg_transfer(0,31,0,7,4,15,0,0);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
