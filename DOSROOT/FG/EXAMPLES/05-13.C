#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int new_mode, old_mode;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 4 || new_mode == 12) {
      printf("This program requires a 320 x 200 ");
      printf("16-color or 256-color graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(new_mode);

   fg_setcolor(1);
   if (new_mode <= 16)
      fg_palette(1,fg_maprgb(45,49,63));
   else
      fg_setrgb(1,45,49,63);
   fg_text("Hello",5);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
