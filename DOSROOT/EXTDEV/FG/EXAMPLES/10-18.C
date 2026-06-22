#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char arrow_white[] = {
   0x00,0x0C,0x00, 0x00,0x0F,0x00, 0xFF,0xFC,0xC0,
   0xC0,0x00,0x30, 0xFF,0xFC,0xC0, 0x00,0x0F,0x00,
   0x00,0x0C,0x00
   };

char arrow_black[] = {6,1,9,2,2,9,1,19,7,2,8,1};

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

   fg_setcolor(2);
   fg_rect(0,319,0,199);

   fg_move(10,10);
   fg_drawmask(arrow_black,12,10);
   fg_drwimage(arrow_white,3,7);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
