#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;
   int red, green, blue;

   old_mode = fg_getmode();
   fg_setmode(19);

   fg_setcolor(103);
   fg_text("Hello",5);
   fg_waitfor(18);

   fg_getrgb(103,&red,&green,&blue);

   while (red+green+blue > 0) {
      if (red > 0) red--;
      if (green > 0) green--;
      if (blue > 0) blue--;
      fg_setrgb(103,red,green,blue);
      fg_waitfor(1);
      }

   fg_setmode(old_mode);
   fg_reset();
}
