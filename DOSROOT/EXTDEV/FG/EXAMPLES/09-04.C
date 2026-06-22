#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int new_mode, old_mode;
   int read_status, write_status;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(new_mode);
   fg_move(0,199);

   read_status = fg_showspr("CORAL.SPR",320);
   fg_waitkey();
   if (read_status == 0)
      write_status = fg_makespr(0,319,80,99,"NEW.SPR");
   else
      write_status = 1;

   fg_setmode(old_mode);
   fg_reset();

   if (read_status == 1)
      printf("CORAL.SPR not found.\n");
   if (write_status == 1)
      printf("NEW.SPR not created.\n");
}
