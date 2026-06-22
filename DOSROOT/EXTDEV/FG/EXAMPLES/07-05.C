#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(16);

   fg_setcolor(14);
   fg_text("yellow",6);

   fg_setcolor(10);
   fg_text(" green",6);

   fg_setcolor(7);
   fg_rect(0,127,336,349);
   fg_setcolor(12);
   fg_locate(24,0);
   fg_text(" Press any key. ",16);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
