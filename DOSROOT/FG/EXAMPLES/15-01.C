#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int freq;

   printf("20 Hz tone...\n");
   fg_sound(20,3);
   fg_waitfor(18);

   printf("100 Hz tone...\n");
   fg_sound(100,3);
   fg_waitfor(18);

   printf("1000 Hz tone...\n");
   fg_sound(1000,3);
   fg_waitfor(18);

   printf("warble...\n");
   fg_sound(400,1);
   fg_sound(410,1);
   fg_sound(400,1);
   fg_sound(410,1);
   fg_waitfor(18);

   printf("sliding tone from 100 to 500 Hz...\n");
   for (freq = 100; freq <= 500; freq+=10)
      fg_sound(freq,2);
}
