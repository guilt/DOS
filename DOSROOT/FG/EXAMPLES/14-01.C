#include <fastgraf.h>
#include <stdio.h>

void main(void);

#define ESC 27

void main()
{
   unsigned char key, aux;

   do {
      fg_getkey(&key,&aux);
      printf("key = %3d  aux = %3d\n",key,aux);
      }
   while (key != ESC);
}
