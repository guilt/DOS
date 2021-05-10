#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int i;
   int units_per_tick;
   unsigned int seconds;
   unsigned char key, aux;

   seconds = 0;

   printf("Benchmarking system speed...\n");
   units_per_tick = fg_measure();
   printf("Benchmark completed.\n\n");

   do {
      for (i = 0; i < 91; i++)
         fg_stall(units_per_tick);
      seconds += 5;
      printf("%u seconds have elapsed.\n",seconds);
      fg_intkey(&key,&aux);
   }
   while (key+aux == 0);
}
