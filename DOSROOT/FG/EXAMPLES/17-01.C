#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);

void main()
{
   long original, mem0, mem1, mem2;
   int  mode, old_mode;

   printf("Which video mode? ");
   scanf("%d",&mode);

   if (fg_testmode(mode,0) == 0) {
      printf("Your system does not support that video mode.\n");
      exit(1);
      }
   if (fg_testmode(mode,3) == 0) {
      printf("Your system does not have enough memory.\n");
      exit(1);
      }

   original = fg_memavail();
   old_mode = fg_getmode();
   fg_setmode(mode);
   mem0 = fg_memavail();
   fg_allocate(1);
   mem1 = fg_memavail();
   fg_allocate(2);
   mem2 = fg_memavail();

   fg_freepage(1);
   fg_freepage(2);
   fg_setmode(old_mode);
   fg_reset();

   printf("originally     = %ld\n",original);
   printf("after setmode  = %ld\n",mem0);
   printf("after 1st page = %ld\n",mem1);
   printf("after 2nd page = %ld\n",mem2);
   printf("at end         = %ld\n",fg_memavail());
}
