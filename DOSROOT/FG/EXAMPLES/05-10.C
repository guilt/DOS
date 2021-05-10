#include <fastgraf.h>

void main(void);

#define COLORS 256

void main()
{
   int base;
   int color;
   int mode;
   int x;

   mode = fg_getmode();
   fg_setmode(19);

   x = 0;

   for (color = 0; color < COLORS; color++) {
      fg_setcolor(color);
      fg_rect(x,x,0,199);
      x++;
      }
   fg_waitkey();

   fg_setmode(mode);
   fg_reset();
}
