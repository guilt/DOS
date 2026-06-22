#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

int CGApatterns[] = {
   0x0000,0x00FF,0x00FF,0x00FF,
   0x02BB,0x0000,0x0222,0x0255,
   0x00FF,0x00FF,0x00FF,0x0055,
   0x00AA,0x00AA,0x00FF,0x0277
   };

void main()
{
   int color;
   int old_mode, new_mode;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);

   if (new_mode == 4) {
      fg_palette(0,0);
      for (color = 0; color < 16; color++)
         fg_pattern(color,CGApatterns[color]);
      }
   else if (new_mode == 9 || new_mode == 13)
      fg_pattern(15,0x04F7);
   else
      fg_setrgb(15,38,38,38);

   fg_move(0,199);
   fg_showppr("CORAL.PPR",320);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
