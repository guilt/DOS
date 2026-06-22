#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

int solid[]  = {0xE03F,0xE03F,0xE03F,0x0007,0x0007,0x0007,0x0007,0x0007,
                0x0007,0x0007,0xE03F,0xE03F,0xE03F,0xFFFF,0xFFFF,0xFFFF,
                0x0000,0x0F80,0x0F80,0x0F80,0x7FF0,0x7FF0,0x7FF0,0x7FF0,
                0x7FF0,0x0F80,0x0F80,0x0F80,0x0000,0x0000,0x0000,0x0000};

int hollow[] = {0xE03F,0xEFBF,0xEFBF,0x0F87,0x7FF7,0x7FF7,0x7FF7,0x7FF7,
                0x7FF7,0x0F87,0xEFBF,0xEFBF,0xE03F,0xFFFF,0xFFFF,0xFFFF,
                0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x0000,
                0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};

void main()
{
   int old_mode;
   int column, row, last_row;

   old_mode = fg_getmode();
   fg_setmode(fg_automode());

   if (fg_mouseini() < 0) {
      fg_setmode(old_mode);
      fg_reset();
      exit(1);
      }

   fg_setcolor(15);
   fg_rect(0,fg_getmaxx(),0,fg_getmaxy());

   fg_setcolor(12);
   column = fg_xalpha(fg_getmaxx()/2) - 6;
   last_row = fg_yalpha(fg_getmaxy()) + 1;

   for (row = 0; row < last_row; row++) {
      fg_locate(row,column);
      fg_text("example 14-10",13);
      }

   fg_mousevis(1);
   fg_waitkey();
   fg_mouseptr(solid,6,6);
   fg_waitkey();
   fg_mouseptr(hollow,6,6);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
