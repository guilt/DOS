#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char arrow[] = {
   0x00,0x0C,0x00, 0x00,0x0F,0x00, 0xFF,0xFF,0xC0,
   0xFF,0xFF,0xF0, 0xFF,0xFF,0xC0, 0x00,0x0F,0x00,
   0x00,0x0C,0x00
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
   fg_setcolor(1);
   fg_fillpage();
   fg_setclip(0,15,0,199);

   fg_move(10,10);
   fg_drwimage(arrow,3,7);
   fg_move(10,20);
   fg_clpimage(arrow,3,7);
   fg_move(8,30);
   fg_revimage(arrow,3,7);
   fg_move(8,40);
   fg_flpimage(arrow,3,7);
   fg_move(8,50);
   fg_putimage(arrow,3,7);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
