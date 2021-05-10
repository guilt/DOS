#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int new_mode, old_mode;
   int status;

   new_mode = fg_bestmode(320,200,1);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(new_mode);

   status = fg_initxms();
   if (status == 0) status = fg_allocxms(8);
   if (status < 0) {
      status = fg_initems();
      if (status == 0) status = fg_allocems(8);
      }
   if (status < 0) status = fg_alloccms(8);

   if (status < 0) {
      fg_setmode(old_mode);
      fg_reset();
      printf("Unable to create logical page.\n");
      exit(1);
      }

   fg_setcolor(7);
   fg_rect(0,319,0,199);
   fg_setcolor(9);
   fg_locate(12,18);
   fg_text("test",4);
   fg_waitkey();

   fg_copypage(0,8);
   fg_erase();
   fg_waitkey();

   fg_copypage(8,0);
   fg_waitkey();

   fg_freepage(8);
   fg_setmode(old_mode);
   fg_reset();
}
