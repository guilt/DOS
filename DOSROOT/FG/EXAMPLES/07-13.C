#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;
   double half;
   double fg_swlength();

   old_mode = fg_getmode();
   fg_setmode(16);
   fg_initw();
   fg_setworld(0.0,6.39,0.0,3.49);
   fg_setsizew(0.21);

   fg_setcolor(7);
   half = fg_swlength(" Hello there. ",14) * 0.5;
   fg_rectw(3.2-half,3.2+half,1.6,1.9);

   fg_setcolor(10);
   fg_movew(3.2,1.65);
   fg_swtext("Hello there.",12,0);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
