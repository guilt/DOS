#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   int buttons, count;
   int x, y;
   char string[25];

   old_mode = fg_getmode();
   fg_setmode(fg_automode());

   if (fg_mouseini() < 0) {
      fg_setmode(old_mode);
      fg_reset();
      exit(1);
      }

   fg_setcolor(15);
   fg_rect(0,fg_getmaxx(),0,fg_getmaxy());
   fg_mousevis(1);

   do {
      fg_waitfor(54);
      fg_mousebut(1,&count,&x,&y);
      fg_mousepos(&x,&y,&buttons);
      sprintf(string,"X=%3d  Y=%3d  count=%4d",x,y,count);
      fg_mousevis(0);
      fg_setcolor(15);
      fg_rect(0,fg_xconvert(25),0,fg_yconvert(1));
      fg_setcolor(0);
      fg_locate(0,0);
      fg_text(string,24);
      fg_mousevis(1);
      fg_mousebut(2,&count,&x,&y);
      }
   while (count == 0);

   fg_setmode(old_mode);
   fg_reset();
}
