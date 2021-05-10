#include <fastgraf.h>

void main(void);

void main()
{
   unsigned char key, aux;
   int old_mode;
   int x, y;

   old_mode = fg_getmode();
   fg_setmode(13);
   fg_resize(640,400);

   fg_setcolor(2);
   fg_rect(0,fg_getmaxx(),0,fg_getmaxy());
   fg_setcolor(15);
   fg_box(0,fg_getmaxx(),0,fg_getmaxy());
   fg_locate(24,28);
   fg_text("Press arrow keys to pan.",24);

   x = 0;
   y = 0;

   do {
      fg_getkey(&key,&aux);
      if (aux == 72 && y < 200)
         y++;
      else if (aux == 75 && x < 320)
         x++;
      else if (aux == 77 && x > 0)
         x--;
      else if (aux == 80 && y > 0)
         y--;
      fg_pan(x,y);
   } while (key != 27);

   fg_setmode(old_mode);
   fg_reset();
}
