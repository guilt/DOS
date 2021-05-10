#include <fastgraf.h>
#include <stdlib.h>

void main(void);

void main()
{
   int area;
   int color, old_color;
   int left;
   int max_color, max_x, max_y;
   int new_mode, old_mode;
   int x, y;

   old_mode = fg_getmode();
   new_mode = fg_automode();
   fg_setmode(new_mode);

   if (new_mode == 4)
      max_color = 3;
   else if (new_mode == 11 || new_mode == 17)
      max_color = 1;
   else if (new_mode == 19)
      max_color = 255;
   else
      max_color = 15;

   left = 100;
   max_x = fg_getmaxx() - 1;
   max_y = fg_getmaxy() - 1;

   while (left > 0) {

      x = rand() % max_x + 1;
      y = rand() % max_y + 1;

      area = fg_getpixel(x-1,y-1) + fg_getpixel(x,y-1) + fg_getpixel(x+1,y-1)
           + fg_getpixel(x-1,y)   + fg_getpixel(x,y)   + fg_getpixel(x+1,y)
           + fg_getpixel(x-1,y+1) + fg_getpixel(x,y+1) + fg_getpixel(x+1,y+1);

      if (area == 0) {
         color = rand() % max_color + 1;
         fg_setcolor(color);
         fg_point(x,y);
         left--;
         }
      }

   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
