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

   fg_setcolor(7);
   fg_rect(0,159,0,99);
   fg_setcolor(9);
   fg_locate(6,6);
   fg_text("quadrant",8);
   fg_waitkey();

   fg_tcmask(0x0202);
   fg_tcxfer(0,159,0,99,160, 99,0,0);
   fg_tcxfer(0,319,0,99,  0,199,0,0);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
