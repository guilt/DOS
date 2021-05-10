#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   if (fg_initjoy(1) < 0)
      printf("Joystick 1 not available.\n");
   else
      printf("Joystick 1 found.\n");

   if (fg_initjoy(2) < 0)
      printf("Joystick 2 not available.\n");
   else
      printf("Joystick 2 found.\n");
}
