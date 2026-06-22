#include <fastgraf.h>

void main(void);

void main()
{
   int new_mode, old_mode;

   old_mode = fg_getmode();
   new_mode = fg_automode();
   fg_setmode(new_mode);
   fg_initw();
   fg_setworld(-10.0,10.0,-10.0,10.0);

   fg_setcolor(15);
   fg_movew(0.0,10.0);
   fg_draww(0.0,-10.0);
   fg_movew(-10.0,0.0);
   fg_draww(10.0,0.0);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
