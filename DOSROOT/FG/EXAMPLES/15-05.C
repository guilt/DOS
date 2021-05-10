#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int voice_array[61];
   int i;
   int volume;

   if (fg_testmode(9,0) == 0) {
      printf("This program requires a PCjr or ");
      printf("a Tandy 1000 system.\n");
      exit(1);
      }

   i = 0;

   for (volume = 1; volume <= 15; volume++) {
      voice_array[i++] = 1;      /* use channel 1 */
      voice_array[i++] = 500;    /* 500 Hz frequency */
      voice_array[i++] = volume; /* variable volume */
      voice_array[i++] = 16;     /* duration */
      }
   voice_array[i] = 0;

   fg_voices(voice_array,1);

   while(fg_playing())
      printf("Still playing...\n");
}
