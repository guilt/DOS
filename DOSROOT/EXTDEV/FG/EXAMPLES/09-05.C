#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode, new_mode;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);

   fg_move(0,199);
   fg_dispfile("CORAL.SPR",320,0);
   fg_waitkey();

   fg_erase();
   fg_dispfile("CORAL.PPR",320,1);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
