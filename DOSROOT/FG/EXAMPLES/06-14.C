#include <fastgraf.h>

void main(void);

void main()
{
   char matrix[4];
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(4);

   matrix[0] = matrix[2] = 0xDD;
   matrix[1] = matrix[3] = 0x77;
   fg_drect(0,49,0,49,matrix);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
