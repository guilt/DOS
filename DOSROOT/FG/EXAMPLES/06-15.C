#include <fastgraf.h>

void main(void);

void main()
{
   char matrix[4];
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(13);

   matrix[0] = matrix[2] = 0x55;
   matrix[1] = matrix[3] = 0xAA;
   fg_setcolor(9);
   fg_drect(0,49,0,49,matrix);

   matrix[0] = matrix[2] = 0xAA;
   matrix[1] = matrix[3] = 0x55;
   fg_setcolor(15);
   fg_drect(0,49,0,49,matrix);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
