#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int old_mode;
   int new_mode;
   char string[4];

   old_mode = fg_getmode();
   new_mode = fg_automode();
   fg_setmode(new_mode);

   fg_setcolor(15);
   fg_text("I'm running in mode ",20);
   sprintf(string,"%d.",new_mode);
   fg_text(string,3);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
