#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

#define RECTANGLES 200
#define SWAP(a,b,temp) { temp = a; a = b; b = temp; }

void main()
{
   int i;
   int minx, maxx, miny, maxy;
   int old_mode;
   int temp;
   int xres, yres;

   if (fg_egacheck() == 0) {
      printf("This program requires EGA or VGA.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(fg_automode());
   fg_setfunc(3);

   xres = fg_getmaxx() + 1;
   yres = fg_getmaxy() + 1;

   for (i = 0; i < RECTANGLES; i++) {
      minx = rand() % xres;
      maxx = rand() % xres;
      miny = rand() % yres;
      maxy = rand() % yres;
      if (minx > maxx)
         SWAP(minx,maxx,temp);
      if (miny > maxy)
         SWAP(miny,maxy,temp);
      fg_setcolor(rand()%16);
      fg_rect(minx,maxx,miny,maxy);
      }

   fg_setmode(old_mode);
   fg_reset();
}
