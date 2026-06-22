#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char triangle[] = {
   0x17,9,1, 0x12,1,5, 0x17,1,3, 0x12,1,3,
   0x17,1,5, 0x12,1,1, 0x17,1,7, 0x17,1,4
   };

void main()
{
   int old_mode, new_mode;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);

   fg_setcolor(7);
   fg_rect(0,319,0,199);

   fg_move(156,101);
   fg_displayp(triangle,16,9);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
