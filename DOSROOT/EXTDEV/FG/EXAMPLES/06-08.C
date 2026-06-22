#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

#define VERTICES 10

int xy[] = {200,100, 300, 80, 400,100, 400,220, 300,320,
            240,320, 160,240, 160,200, 200,160, 210,150};
int work_array[700];

void main()
{
   int old_mode;

   old_mode = fg_getmode();

   if (fg_testmode(16,1))
      fg_setmode(16);
   else if (fg_testmode(15,1))
      fg_setmode(15);
   else {
      printf("This program requires a 640 x 350 ");
      printf("EGA graphics mode.\n");
      exit(1);
      }

   fg_setcolor(1);
   fg_polyoff(-120,-25);
   fg_polyline(xy,VERTICES);
   fg_polyoff(200,-25);
   fg_polyfill(xy,work_array,VERTICES);
   fg_waitkey();

   fg_setcolor(2);
   fg_setclip(480,639,175,349);
   fg_polyfill(xy,work_array,VERTICES);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
