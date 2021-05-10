#include <fastgraf.h>

void main(void);

void main()
{
   int decreasing;
   int i;
   int old_mode;
   char RGBvalues[21];

   old_mode = fg_getmode();
   fg_setmode(19);

   for (i = 9; i <= 15; i++) {
      fg_setcolor(i);
      fg_text("*",1);
      }

   fg_getdacs(9,7,RGBvalues);
   fg_waitfor(18);

   do {
      decreasing = 0;
      for (i = 0; i < 21; i++)
         if (RGBvalues[i] > 0) {
            RGBvalues[i]--;
            decreasing = 1;
            }
      fg_setdacs(9,7,RGBvalues);
      fg_waitfor(1);
      }
   while (decreasing);
      
   fg_setmode(old_mode);
   fg_reset();
}
