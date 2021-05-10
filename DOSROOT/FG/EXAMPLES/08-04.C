#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

#define PAGES 4

void main()
{
   int old_mode;
   int page;
   char string[8];

   if (fg_testmode(11,PAGES) == 0) {
      printf("This program requires Hercules ");
      printf("monochrome graphics.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(11);

   for (page = 0; page < PAGES; page++) {
      fg_allocate(page);
      fg_setpage(page);
      fg_setcolor(7);
      fg_rect(0,fg_getmaxx(),0,fg_getmaxy());
      fg_setcolor(0);
      fg_locate(12,37);
      sprintf(string,"page %d",page);
      fg_text(string,6);
      }

   for (page = 0; page < PAGES; page++) {
      fg_setvpage(page);
      fg_waitkey();
      fg_freepage(page);
      }

   fg_setmode(old_mode);
   fg_reset();
}
