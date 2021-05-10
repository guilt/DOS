#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(3);
   fg_cursor(0);

   fg_setattr(7,0,0);
   fg_text("hello",5);
   fg_waitkey();

   fg_locate(0,0);
   fg_setattr(0,7,0);
   fg_chgattr(5);
   fg_waitkey();

   fg_locate(0,0);
   fg_chgtext("H",1);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
