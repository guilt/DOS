#include <fastgraf.h>

void main(void);

void main()
{
   int lines;
   int old_lines;
   int old_mode;

   old_lines = fg_getlines();
   old_mode = fg_getmode();
   fg_setmode(3);
   fg_cursor(0);

   fg_setcolor(15);
   fg_text("first line",10);
   fg_waitkey();

   if (fg_testmode(16,0)) {
      fg_setlines(43);
      fg_cursor(0);
      fg_waitkey();
      }

   if (fg_testmode(17,0)) {
      fg_setlines(50);
      fg_cursor(0);
      fg_waitkey();
      }

   fg_setmode(old_mode);
   fg_setlines(old_lines);
   fg_reset();
}
