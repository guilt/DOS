#include <fastgraf.h>

void main(void);

void main()
{
   int mid_x, mid_y;
   int old_mode;
   int x, y;

   old_mode = fg_getmode();
   fg_setmode(fg_automode());
   fg_setcolor(15);

   mid_x = fg_getmaxx() / 2;
   mid_y = fg_getmaxy() / 2;
   x = mid_x / 8;
   y = mid_y / 8;

   fg_move(mid_x,mid_y);
   fg_ellipse(x,y);
   fg_circle(x);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
