#include <fastgraf.h>

void main(void);

int zeroes[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void main()
{
   int mode;

   mode = fg_getmode();
   fg_setmode(13);

   fg_palettes(zeroes);

   fg_setmode(mode);
   fg_reset();
}
