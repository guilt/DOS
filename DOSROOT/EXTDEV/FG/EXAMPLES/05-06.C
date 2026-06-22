#include <fastgraf.h>

void main(void);

void main()
{
   int mode;

   mode = fg_getmode();
   fg_setmode(13);

   fg_palette(0,1);
   fg_palette(1,22);

   fg_setcolor(1);
   fg_text("Hello",5);
   fg_waitkey();

   fg_palette(1,23);
   fg_waitkey();

   fg_setmode(mode);
   fg_reset();
}
