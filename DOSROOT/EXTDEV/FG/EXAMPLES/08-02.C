#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

#define PAGES 4

void main()
{
   int color;
   int old_mode;
   int page;
   char string[8];

   if (fg_testmode(13,PAGES) == 0) {
      printf("This program requires a ");
      printf("320 x 200 EGA graphics mode.\n");
      exit(1);
      }

   old_mode = fg_getmode();
   fg_setmode(13);

   for (page = 0; page < PAGES; page++) {
      fg_setpage(page);
      color = page + 1;
      fg_setcolor(color);
      fg_rect(0,fg_getmaxx(),0,fg_getmaxy());
      fg_setcolor(0);
      fg_locate(12,17);
      sprintf(string,"page %d",page);
      fg_text(string,6);
      }

   for (page = 0; page < PAGES; page++) {
      fg_setvpage(page);
      fg_waitkey();
      }

   fg_setmode(old_mode);
   fg_reset();
}
