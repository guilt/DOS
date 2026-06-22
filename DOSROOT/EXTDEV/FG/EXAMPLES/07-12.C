#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   char string[24];
   int angle;
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(16);
   fg_setcolor(10);
   fg_initw();
   fg_setworld(0.0,6.39,0.0,3.49);
   fg_setsizew(0.21);

   for (angle = 0; angle < 360; angle += 15) {
      fg_movew(3.2,1.75);
      fg_setangle((double)angle);
      sprintf(string,"     %3d degrees",angle);
      fg_swtext(string,16,-1);
      }
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
