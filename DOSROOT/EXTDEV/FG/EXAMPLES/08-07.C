#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(3);
   fg_cursor(0);
   fg_setattr(10,0,0);

   fg_locate(1,0);
   fg_text("Page ",5);
   fg_waitkey();

   fg_setpage(1);
   fg_locate(23,0);
   fg_text("Page 1",6);

   fg_setpage(0);
   fg_text("0",1);
   fg_waitkey();

   fg_setvpage(1);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
