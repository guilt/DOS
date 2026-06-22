#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   unsigned int seconds;
   unsigned char key, aux;

   seconds = 0;

   do {
      fg_waitfor(91);
      seconds += 5;
      printf("%u seconds have elapsed.\n",seconds);
      fg_intkey(&key,&aux);
   }
   while (key+aux == 0);
}
