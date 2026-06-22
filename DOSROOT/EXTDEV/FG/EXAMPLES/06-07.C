#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

#define VERTICES 10

int x[] = {200,300,400,400,300,240,160,160,200,210};
int y[] = {100, 80,100,220,320,320,240,200,160,150};

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
   fg_polygon(x,y,VERTICES);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
