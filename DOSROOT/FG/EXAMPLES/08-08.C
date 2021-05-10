#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int old_mode;
   int active, visual;
   int page0, page1;

   old_mode = fg_getmode();
   fg_setmode(4);
   fg_allocate(1);
   fg_setpage(1);

   active = fg_getpage();
   visual = fg_getvpage();

   fg_setpage(0);
   page0 = fg_getaddr();
   fg_setpage(1);
   page1 = fg_getaddr();

   fg_freepage(1);
   fg_setmode(old_mode);
   fg_reset();

   printf("Active page is %d.\n",active);
   printf("Visual page is %d.\n",visual);
   printf("Page 0 address is %4X\n",page0);
   printf("Page 1 address is %4X\n",page1);
}
