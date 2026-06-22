#include <fastgraf.h>

void main(void);

#define ESC 27

void main()
{
   int color;
   int old_mode;
   unsigned char key, aux;

   old_mode = fg_getmode();
   fg_setmode(fg_automode());
   color = 0;

   fg_musicb("O4 L16 CC#DD#EFF#GG#AA#B O+ CC#DD#EFF#GG#AA#B$",-1);

   while (fg_playing())
   {
      color = (color + 1) & 15;
      fg_setcolor(color);
      fg_rect(0,fg_getmaxx(),0,fg_getmaxy());

      fg_waitfor(4);
      fg_intkey(&key,&aux);
      if (key == ESC)
         fg_hush();
      else if (key+aux != 0)
         fg_hushnext();
   }

   fg_setmode(old_mode);
   fg_reset();
}
