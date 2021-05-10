#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int old_mode;
   char image[8];

   old_mode = fg_getmode();

   if (fg_testmode(3,1))
      fg_setmode(3);
   else if (fg_testmode(7,1))
      fg_setmode(7);
   else {
      printf("This program requires\n");
      printf("an 80-column display.\n");
      exit(1);
      }

   fg_cursor(0);

   fg_setattr(9,7,0);
   fg_text("text",4);
   fg_waitkey();

   fg_locate(0,0);
   fg_getimage(image,8,1);
   fg_locate(1,1);
   fg_drwimage(image,8,1);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
