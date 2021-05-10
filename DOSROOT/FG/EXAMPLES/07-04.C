#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int attr, value;
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(3);
   fg_cursor(0);

   fg_setattr(9,7,0);
   fg_locate(24,0);
   fg_text("Test",4);
   value = fg_getchar(24,0);
   attr  = fg_getattr(24,0);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
   printf("%c %2.2X\n",value,attr);
}
