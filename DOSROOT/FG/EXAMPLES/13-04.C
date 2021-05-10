#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(3);
   fg_cursor(0);

   fg_setcolor(7);
   fg_rect(0,79,0,24);
   fg_setattr(10,7,0);
   fg_text("line one",8);
   fg_locate(1,0);
   fg_text("line two",8);
   fg_waitkey();

   fg_setcolor(7);
   fg_scroll(0,7,1,1,1,1);
   fg_waitkey();
   fg_scroll(0,7,2,2,-1,1);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
