#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   fg_musicb("T150 L8 EDCDEEE P DDD P EGG P EDCDEEE L16 P L8 EDDEDC$",1);
   fg_waitkey();

   fg_suspend();
   printf("Music suspended.  Press any key to resume.\n");
   fg_waitkey();

   fg_resume();
   printf("Music resumed.\n");
   while (fg_playing());
   printf("Music finished.\n");
}
