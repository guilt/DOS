#include <fastgraf.h>
#include <stdio.h>

void main(void);

#define ESC 27

void main()
{
   unsigned long start, ticks;
   unsigned char key, aux;

   start = fg_getclock();

   do {
      ticks = fg_getclock();
      printf("%lu ticks since midnight.\n",ticks);
      printf("%lu ticks since start of program.\n\n",ticks-start);
      fg_getkey(&key,&aux);
   }
   while (key != ESC);
}
