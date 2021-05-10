#include <fastgraf.h>

void main(void);

void main()
{
   int mode;

   mode = fg_getmode();
   fg_setmode(11);

   fg_setcolor(1);
   fg_text("Hello",5);
   fg_waitkey();

   fg_setmode(mode);
   fg_reset();
}
