#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   int row;

   old_mode = fg_getmode();
   fg_setmode(3);

   if (fg_mouseini() < 0) {
      fg_setmode(old_mode);
      fg_reset();
      exit(1);
      }

   fg_setattr(7,0,0);
   fg_rect(0,fg_getmaxx(),0,fg_getmaxy());

   fg_setattr(12,7,0);
   for (row = 0; row < 25; row++) {
      fg_locate(row,34);
      fg_text("example 14-9",12);
      }

   fg_mousevis(1);
   fg_waitkey();
   fg_mousecur(0x7FFF,0x7F00);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
