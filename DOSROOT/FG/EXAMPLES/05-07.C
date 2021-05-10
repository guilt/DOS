#include <fastgraf.h>

void main(void);

void main()
{
   int mode;

   mode = fg_getmode();
   fg_setmode(15);

   fg_setcolor(4);
   fg_text("Hello",5);
   fg_waitkey();

   fg_palette(4,8);
   fg_waitkey();

   fg_setmode(mode);
   fg_reset();
}
