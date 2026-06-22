#include <fastgraf.h>

void main(void);

void main()
{
   int mode;

   mode = fg_getmode();
   fg_setmode(17);

   fg_setrgb(0,0,0,42);
   fg_setrgb(1,63,63,21);

   fg_setcolor(1);
   fg_text("Hello",5);
   fg_waitkey();

   fg_palette(1,15);
   fg_waitkey();

   fg_setmode(mode);
   fg_reset();
}
