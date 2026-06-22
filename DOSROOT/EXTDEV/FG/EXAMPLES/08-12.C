#include <fastgraf.h>
#include <dos.h>
#ifdef __TURBOC__
#include <alloc.h>
#else
#include <malloc.h>
#define  farfree(p)   _ffree(p)
#define  farmalloc(n) _fmalloc(n)
#endif

void main(void);

void main()
{
   int old_mode;
   unsigned page_addr;
   char far *buffer;

   old_mode = fg_getmode();
   fg_setmode(19);
   buffer = farmalloc(fg_pagesize()+16);
   page_addr = FP_SEG(buffer) + (FP_OFF(buffer)+15)/16;
   fg_setentry(1,page_addr,2);

   fg_setpage(1);
   fg_erase();
   fg_setcolor(9);
   fg_text("This is page 1.",15);
   fg_waitkey();

   fg_copypage(1,0);
   fg_setentry(1,0,0);
   fg_waitkey();

   farfree(buffer);
   fg_setmode(old_mode);
   fg_reset();
}
