#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);
void redraw(void);

void main()
{
   int new_mode, old_mode;
   double xmin, xmax, ymin, ymax;

   old_mode = fg_getmode();
   new_mode = fg_automode();

   if (new_mode == 0) {
      printf("This program requires graphics.\n");
      exit(1);
      }

   fg_setmode(new_mode);
   fg_initw();

   fg_setworld(0.0,40.0,0.0,30.0);
   redraw();
   fg_waitkey();

   fg_getworld(&xmin,&xmax,&ymin,&ymax);
   fg_setworld(0.0,xmax*0.5,0.0,ymax*0.5);
   redraw();
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}

void redraw()
{
   fg_erase();
   fg_setcolor(1);

   fg_movew(0.0,0.0);
   fg_draww(0.0,10.0);
   fg_draww(10.0,10.0);
   fg_draww(10.0,0.0);
   fg_draww(0.0,0.0);
}
