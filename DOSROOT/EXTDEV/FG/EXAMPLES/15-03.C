#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   printf("Mary Had a Little Lamb...\n");
   fg_music("T150 L8 EDCDEEE P DDD P EGG P EDCDEEE L16 P L8 EDDEDC$");
   fg_waitfor(18);

   printf("up the scale in two octaves...\n");
   fg_music("L16 CC#DD#EFF#GG#AA#B O+ CC#DD#EFF#GG#AA#B$");
   fg_waitfor(18);

   printf("Beethoven's Fifth Symphony...\n");
   fg_music("T180 O2 L2 P L8 P GGG L2 D# L24 P L8 P FFF L2 D$");
}
