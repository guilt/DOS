#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(3);
   fg_cursor(0);

   fg_setattr(14,0,0);
   fg_text("yellow",6);

   fg_setattr(10,0,0);
   fg_text(" green",6);

   fg_setattr(12,0,1);
   fg_text(" blinking",9);

   fg_setattr(12,7,0);
   fg_locate(24,0);
   fg_text(" Press any key. ",16);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
