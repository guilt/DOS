#include <fastgraf.h>

void main(void);

#define COLORS 16
#define WIDTH  40

void main()
{
   int base;
   int color;
   int minx, maxx;
   int mode;

   mode = fg_getmode();
   fg_setmode(16);

   base = 0;
   minx = 0;
   maxx = WIDTH - 1;

   for (color = 0; color < COLORS; color++) {
      fg_palette(color,0);
      fg_setcolor(color);
      fg_rect(minx,maxx,0,349);
      minx = maxx + 1;
      maxx = maxx + WIDTH;
      }

   while (base < COLORS*4) {
      for (color = 0; color < COLORS; color++)
         fg_palette(color,base+color);
      base += COLORS;
      fg_waitkey();
      }

   fg_setmode(mode);
   fg_reset();
}
