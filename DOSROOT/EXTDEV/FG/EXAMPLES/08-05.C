#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

#define PAGES 4

void main()
{
   int old_mode, new_mode;
   int page;
   char string[8];

   new_mode = fg_bestmode(80,25,PAGES);
   if (new_mode < 0) {
      printf("This program requires ");
      printf("an 80-column display.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);
   fg_cursor(0);

   for (page = 0; page < PAGES; page++) {
      fg_allocate(page);
      fg_setpage(page);
      fg_setcolor(7);
      fg_rect(0,fg_getmaxx(),0,fg_getmaxy());
      fg_setattr(0,7,0);
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