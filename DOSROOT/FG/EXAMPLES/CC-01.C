#include <fastgraf.h>
#include <stdio.h>

void main(void);

#define ESC 27

int status1, status2;

void main()
{
   unsigned char key, aux;

   int1C(1);

   status1 = 0;
   status2 = 0;

   do {
      printf("\n");
      printf("Joystick 1 status: %d\n",status1);
      printf("Joystick 2 status: %d\n",status2);
      status1 = 0;
      status2 = 0;
      fg_getkey(&key,&aux);
      }
   while (key != ESC);

   int1C(0);
}
