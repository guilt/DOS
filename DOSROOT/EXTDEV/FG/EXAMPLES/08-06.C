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

   new_mode = fg_bestmode(320,200,PAGES);
   if (new_mode < 0) {
      printf("This program requires a ");
      printf("320 x 200 graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(new_mode);

   for (page = 0; page < PAGES; page++) {
      fg_allocate(page);
      fg_setpage(page);
      fg_setcolor(15);
      fg_rect(0,fg_getmaxx(),0,fg_getmaxy());
      fg_setcolor(0);
      fg_locate(12,17);
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