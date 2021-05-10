#include <fastgraf.h>

void main(void);

void main()
{
   int mode;

   mode = fg_getmode();
   fg_setmode(4);

   fg_defcolor(0,1);
   fg_defcolor(255,1);

   fg_setcolor(0);
   fg_text("0",1);
   fg_setcolor(1);
   fg_text(" 1",2);
   fg_setcolor(255);
   fg_text(" 255",4);
   fg_waitkey();

   fg_setmode(mode);
   fg_reset();
}
