#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int i;
   int freq;
   int sound_array[83];

   i = 0;

   for (freq = 100; freq <= 500; freq+=10) {
      sound_array[i++] = freq;
      sound_array[i++] = 8;
      }
   sound_array[i] = 0;

   fg_sounds(sound_array,1);

   while(fg_playing())
      printf("Still playing...\n");
}
