#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int maxx, maxy;
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(fg_automode());

   if (fg_mouseini() < 0) {
      fg_setmode(old_mode);
      fg_reset();
      exit(1);
      }

   maxx = fg_getmaxx();
   maxy = fg_getmaxy();
   fg_setcolor(15);
   fg_rect(0,maxx,0,maxy);

   fg_mousevis(1);
   fg_mouselim(maxx/4,3*maxx/4,maxy/4,3*maxy/4);
   fg_waitkey();

   fg_mousemov(0,0);
   fg_waitfor(36);
   fg_mousemov(maxx,0);
   fg_waitfor(36);
   fg_mousemov(maxx,maxy);
   fg_waitfor(36);
   fg_mousemov(0,maxy);
   fg_waitfor(36);
   fg_mousemov(maxx/2,maxy/2);
   fg_mousespd(16,32);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
