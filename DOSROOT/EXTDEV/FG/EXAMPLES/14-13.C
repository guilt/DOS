#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   char key, aux;

   fg_initjoy(1);
   fg_initjoy(2);

   while (1) {
      fg_intjoy(1,&key,&aux);
      printf("1: %2d %2d\n",key,aux);
      fg_intjoy(2,&key,&aux);
      printf("2: %2d %2d\n\n",key,aux);
      fg_waitfor(9);
      }
}
