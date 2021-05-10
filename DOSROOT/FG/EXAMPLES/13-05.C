#include <conio.h>
#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   int new_mode, old_mode;

   new_mode = fg_bestmode(320,200,2);
   if (new_mode < 0 || new_mode == 12) {
      printf("This program requires a 320 ");
      printf("x 200 color graphics mode.\n");
      exit(1);
      }
   old_mode = fg_getmode();
   fg_setmode(new_mode);
   fg_allocate(1);
   fg_sethpage(1);

   fg_setcolor(9);
   fg_rect(0,319,0,199);
   fg_setcolor(15);
   fg_rect(132,188,50,150);

   fg_setcolor(10);
   fg_move(160,67);
   fg_draw(175,107);
   fg_draw(140,82);
   fg_draw(180,82);
   fg_draw(145,107);
   fg_draw(160,67);
   fg_paint(160,77);
   fg_paint(150,87);
   fg_paint(160,87);
   fg_paint(170,87);
   fg_paint(155,97);
   fg_paint(165,97);

   while (kbhit() == 0) {
      fg_waitfor(1);
      fg_scroll(136,184,50,150,-4,0);
      }
   fg_waitkey();

   fg_freepage(1);
   fg_setmode(old_mode);
   fg_reset();
}
