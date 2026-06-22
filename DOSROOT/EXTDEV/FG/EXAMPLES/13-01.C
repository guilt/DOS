#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(fg_automode());

   fg_setcolor(2);
   fg_rect(0,fg_getmaxx(),0,fg_getmaxy());
   fg_waitkey();

   fg_setcolor(15);
   fg_fadeout(0);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
