#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;
   int row;

   old_mode = fg_getmode();
   fg_setmode(18);

   fg_setcolor(9);
   fg_fillpage();
   fg_setcolor(15);
   fg_fontsize(8);

   for (row = 0; row < 60; row++) {
      fg_locate(row,34);
      fg_text("8x8 ROM font",12);
      }
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
