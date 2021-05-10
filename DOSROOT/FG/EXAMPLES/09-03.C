#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   int read_status, write_status;

   if (fg_testmode(19,1) == 0) {
      printf("This program requires a 320 ");
      printf("x 200 MCGA graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(19);

   read_status = fg_showgif("CORAL.GIF",0);
   fg_waitkey();
   if (read_status == 0)
      write_status = fg_makegif(0,319,80,99,"NEW.GIF");
   else
      write_status = 1;

   fg_setmode(old_mode);
   fg_reset();

   if (read_status == 1)
      printf("CORAL.GIF not found.\n");
   else if (read_status == 2)
      printf("CORAL.GIF is not a GIF file.\n");
   if (write_status == 1)
      printf("NEW.GIF not created.\n");
}
