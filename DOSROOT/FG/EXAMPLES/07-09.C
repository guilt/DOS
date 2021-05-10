#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;
   int minx, maxx, miny, maxy;

   old_mode = fg_getmode();
   fg_setmode(16);

   fg_setcolor(14);
   fg_text("yellow",6);

   fg_setcolor(10);
   fg_text(" green",6);

   fg_setcolor(7);
   minx = fg_xconvert(0);
   maxx = fg_xconvert(16) - 1;
   miny = fg_yconvert(24);
   maxy = fg_yconvert(25) - 1;
   fg_rect(minx,maxx,miny,maxy);
   fg_setcolor(12);
   fg_locate(24,0);
   fg_text(" Press any key. ",16);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
