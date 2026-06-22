#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(19);
   fg_setcolor(9);
   fg_rect(0,159,0,199);
   fg_setcolor(15);
   fg_rect(160,319,0,199);
   fg_waitkey();

   fg_boxx(80,239,50,149);
   fg_waitkey();
   fg_boxx(80,239,50,149);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
