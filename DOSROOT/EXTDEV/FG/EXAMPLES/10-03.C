#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char triangle[] = {
   0x55,0x55,0x40, 0x1A,0xA9,0x00, 0x06,0xA4,0x00,
   0x01,0x90,0x00, 0x00,0x40,0x00
   };

void main()
{
   int old_mode;

   if (fg_testmode(4,1) == 0) {
      printf("This program requires a 320 ");
      printf("x 200 CGA graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(4);

   fg_setcolor(7);
   fg_rect(0,319,0,199);

   fg_move(156,101);
   fg_drwimage(triangle,3,5);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
