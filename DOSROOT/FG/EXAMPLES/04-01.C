#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int max_col;
   int max_row;
   int mode;

   mode = fg_getmode();
   fg_setmode(3);

   max_col = fg_getmaxx();
   max_row = fg_getmaxy();

   fg_setmode(mode);
   fg_reset();

   printf("Last col = %d\n",max_col);
   printf("Last row = %d\n",max_row);
}
