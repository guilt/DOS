#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char far buffer[20000];

void main()
{
   int old_mode;

   if (fg_testmode(19,1) == 0) {
      printf("This program requires a 320 ");
      printf("x 200 MCGA graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(19);
   fg_imagebuf(buffer,20000);
   fg_showpcx("CORAL.PCX",0);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
