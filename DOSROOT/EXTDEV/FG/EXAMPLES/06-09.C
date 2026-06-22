#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(fg_automode());
   fg_setcolor(15);

   fg_initw();
   fg_setworld(-100.0,100.0,-100.0,100.0);

   fg_movew(0.0,0.0);
   fg_ellipsew(12.5,12.5);
   fg_circlew(12.5);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
