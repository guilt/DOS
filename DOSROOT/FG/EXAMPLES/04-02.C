#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int maxx;
   int maxy;
   int mode;

   mode = fg_getmode();
   fg_setmode(4);

   maxx = fg_getmaxx();
   maxy = fg_getmaxy();

   fg_setmode(mode);
   fg_reset();

   printf("(%d,%d)\n",maxx,maxy);
}
