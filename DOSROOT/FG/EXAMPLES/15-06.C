#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   fg_musicb("T150 L8 EDCDEEE P DDD P EGG P EDCDEEE L16 P L8 EDDEDC$",1);
   while (fg_playing())
      printf("Mary Had a Little Lamb...\n");
   fg_waitfor(18);

   fg_musicb("L16 CC#DD#EFF#GG#AA#B O+$",2);
   while (fg_playing())
      printf("up the scale in two octaves...\n");
   fg_waitfor(18);

   fg_musicb("T180 O2 L2 P L8 P GGG L2 D# L24 P L8 P FFF L2 D$",1);
   while (fg_playing())
      printf("Beethoven's Fifth Symphony...\n");
}
