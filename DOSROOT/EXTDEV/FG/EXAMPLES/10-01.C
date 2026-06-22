#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char perimeter[] = {
   0xFF,0x80,0x41,0x00,0x22,0x00,0x14,0x00,0x08,0x00
   };
char interior[] = {
   0x00,0x00,0x3E,0x00,0x1C,0x00,0x08,0x00,0x00,0x00
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
   fg_setcolor(1);
   fg_drawmap(perimeter,2,5);
   fg_setcolor(2);
   fg_drawmap(interior,2,5);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
