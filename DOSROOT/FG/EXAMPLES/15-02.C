#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int volume;

   if (fg_testmode(9,0) == 0) {
      printf("This program requires a PCjr or ");
      printf("a Tandy 1000 system.\n");
      exit(1);
      }

   printf("2048 Hz periodic noise...\n");
   fg_voice(4,2,15,3);
   fg_waitfor(18);

   printf("2048 Hz white noise...\n");
   fg_voice(5,2,15,3);
   fg_waitfor(18);

   printf("500 Hz tone of increasing volume...\n");
   for (volume = 1; volume <= 15; volume++) {
      fg_voice(1,500,volume,0);
      fg_waitfor(4);
      }

   fg_quiet();
}
