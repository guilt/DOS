#include <fastgraf.h>

void main(void);

void main()
{
   char matrix[8];
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(19);

   matrix[0] = matrix[3] = matrix[4] = matrix[7] = 15;
   matrix[1] = matrix[2] = matrix[5] = matrix[6] =  9;
   fg_drect(0,49,0,49,matrix);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
