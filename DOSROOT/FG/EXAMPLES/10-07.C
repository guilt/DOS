#include <fastgraf.h>

void main(void);

char hello[] = {
   't',1, 'h',2, 'e',3, 'r',4, 'e',5,
   'h',1, 'e',2, 'l',3, 'l',4, 'o',5
   };

char image[] = {
   'T',0, 0,1, 0,1, 0,1, 0,1,
   'H',0, 0,1, 0,1, 0,1, 0,1
   };

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(3);
   fg_cursor(0);

   fg_locate(12,37);
   fg_drwimage(hello,10,2);
   fg_waitkey();

   fg_drwimage(image,10,2);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
