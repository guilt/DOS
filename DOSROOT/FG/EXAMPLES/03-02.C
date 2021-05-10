#include <fastgraf.h>

void main(void);

void main()
{
   fg_setmode(3);
   fg_cursor(0);

   fg_setcolor(15);
   fg_text("Hello, world.",13);
   fg_waitkey();

   fg_reset();
}
