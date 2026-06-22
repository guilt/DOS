#include <fastgraf.h>

void main(void);

void main()
{
   int old_mode;

   old_mode = fg_getmode();
   fg_setmode(18);
   fg_setcolor(9);
   fg_fillpage();
   fg_setcolor(14);

   fg_move(0,0);
   fg_justify(-1,1);
   fg_print("Fastgraph",9);
   fg_move(320,0);
   fg_justify(0,1);
   fg_print("Fastgraph",9);
   fg_move(639,0);
   fg_justify(1,1);
   fg_print("Fastgraph",9);

   fg_move(0,240);
   fg_justify(-1,0);
   fg_print("Fastgraph",9);
   fg_move(320,240);
   fg_justify(0,0);
   fg_print("Fastgraph",9);
   fg_move(639,240);
   fg_justify(1,0);
   fg_print("Fastgraph",9);

   fg_move(0,479);
   fg_justify(-1,-1);
   fg_print("Fastgraph",9);
   fg_move(320,479);
   fg_justify(0,-1);
   fg_print("Fastgraph",9);
   fg_move(639,479);
   fg_justify(1,-1);
   fg_print("Fastgraph",9);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}
