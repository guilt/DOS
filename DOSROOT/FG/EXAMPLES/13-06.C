#include <fastgraf.h>

void main(void);

#define DELAY 2
#define JUMP  4

void main()
{
   int i;
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(fg_automode());

   fg_setcolor(15);
   fg_move(0,JUMP);
   fg_draw(fg_getmaxx(),JUMP);
   fg_draw(fg_getmaxx(),fg_getmaxy()-JUMP);
   fg_draw(0,fg_getmaxy()-JUMP);
   fg_draw(0,JUMP);
   fg_waitkey();

   for (i = 0; i < 6; i++) {
      fg_pan(0,JUMP);
      fg_waitfor(DELAY);
      fg_pan(0,0);
      fg_waitfor(DELAY);
      }

   fg_setmode(old_mode);
   fg_reset();
}
