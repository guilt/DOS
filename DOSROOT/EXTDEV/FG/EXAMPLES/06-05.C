#include <fastgraf.h>

void main(void);

void main()
{
   int max_x, max_y;
   int mid_x, mid_y;
   int new_mode, old_mode;

   old_mode = fg_getmode();
   new_mode = fg_automode();
   fg_setmode(new_mode);

   max_x = fg_getmaxx();
   max_y = fg_getmaxy();
   mid_x = max_x / 2;
   mid_y = max_y / 2;

   fg_setclip(0,mid_x,0,mid_y);

   fg_setcolor(15);
   fg_move(mid_x,0);
   fg_draw(mid_x,max_y);
   fg_move(0,mid_y);
   fg_draw(max_x,mid_y);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
