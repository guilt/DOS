#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

char triangle[] = {
   0xFF,0x80, 0x7F,0x00, 0x3E,0x00,
   0x1C,0x00, 0x08,0x00
   };

void main()
{
   int old_mode;

   if (fg_testmode(6,1) == 0) {
      printf("This program requires a ");
      printf("CGA graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(6);

   fg_move(316,101);
   fg_drwimage(triangle,2,5);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
