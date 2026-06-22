#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(16);
   fg_setcolor(10);
   fg_initw();
   fg_setworld(0.0,6.39,0.0,3.49);
   fg_setratio(2.0);
   fg_setsizew(0.21);

   fg_movew(3.2,3.0);
   fg_swchar("cos\\^2\\h\\ + sin\\^2\\h\\ = 1",25,0);

   fg_movew(3.2,2.0);
   fg_swchar("H\\v2O   U\\v2\\v3\\v2",18,0);

   fg_movew(3.2,1.0);
   fg_setratio(1.0);
   fg_swchar("One _word_ is underlined.",25,0);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
