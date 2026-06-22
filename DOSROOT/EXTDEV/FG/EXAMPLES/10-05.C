#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char triangle[] = {
   0x11,0x11,0x11,0x11,0x10,
   0x01,0x22,0x22,0x21,0x00,
   0x00,0x12,0x22,0x10,0x00,
   0x00,0x01,0x21,0x00,0x00,
   0x00,0x00,0x10,0x00,0x00
   };

void main()
{
   int old_mode;

   if (fg_testmode(13,1) == 0) {
      printf("This program requires a 320 ");
      printf("x 200 EGA graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(13);

   fg_setcolor(7);
   fg_rect(0,319,0,199);

   fg_move(156,101);
   fg_drwimage(triangle,5,5);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
