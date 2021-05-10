#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int b, x, y;

   fg_initjoy(1);
   fg_initjoy(2);

   while (1) {
      x = fg_getxjoy(1);
      y = fg_getyjoy(1);
      b = fg_button(1);
      printf("1:  %3d %3d %1d\n",x,y,b);
      x = fg_getxjoy(2);
      y = fg_getyjoy(2);
      b = fg_button(2);
      printf("2:  %3d %3d %1d\n\n",x,y,b);
      fg_waitfor(9);
      }
}
