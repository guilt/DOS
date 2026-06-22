#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(19);

   fg_setcolor(14);
   fg_text("yellow",6);

   fg_locate(0,0);
   fg_setcolor(10);
   fg_text(" green",6);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
