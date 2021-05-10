#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;
   int page_addr, page_type;

   old_mode = fg_getmode();
   fg_setmode(18);
   fg_alloccms(2);
   fg_getentry(2,&page_addr,&page_type);

   fg_setcolor(9);
   fg_fillpage();
   fg_setcolor(15);
   fg_box(0,639,0,479);
   fg_waitkey();

   fg_copypage(0,2);
   fg_setmode(old_mode);
   fg_cursor(0);
   fg_setcolor(15);
   fg_text("Press any key.",14);
   fg_waitkey();

   fg_setmode(18);
   fg_setentry(2,page_addr,page_type);
   fg_copypage(2,0);
   fg_waitkey();

   fg_freepage(2);
   fg_setmode(old_mode);
   fg_reset();
}
