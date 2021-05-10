#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(16);
   fg_initw();
   fg_setworld(0.0,6.39,0.0,3.49);
   fg_setsizew(0.21);

   fg_setcolor(15);
   fg_locate(0,26);
   fg_text("Software characters - font 1",28);

   fg_setcolor(10);
   fg_movew(0.0,3.1);
   fg_swchar("ABCDEFGHIJKLMNOPQRSTUVWXYZ",26,-1);
   fg_movew(0.0,2.8);
   fg_swchar("abcdefghijklmnopqrstuvwxyz",26,-1);
   fg_movew(0.0,2.5);
   fg_swchar("0123456789",10,-1);
   fg_movew(0.0,2.2);
   fg_swchar("!\"#$%&'()*+,-./:;<=>?[]^`{|}~",29,-1);

   fg_setcolor(15);
   fg_locate(12,26);
   fg_text("Software characters - font 2",28);

   fg_setcolor(10);
   fg_movew(0.0,1.4);
   fg_swchar("\\ABCDEFGHIJKLMNOPRSTUWXYZ",25,-1);
   fg_movew(0.0,1.1);
   fg_swchar("\\abcdefghijklmnoprstuwxyz",25,-1);
   fg_movew(0.0,0.4);
   fg_swchar("\\012345678#$%&()*+/<=>?[]{}",27,-1);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
