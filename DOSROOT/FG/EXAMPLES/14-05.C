#include <fastgraf.h>
#include <stdio.h>

void main(void);

#define ESC    1
#define LEFT  75
#define RIGHT 77
#define UP    72
#define DOWN  80

void main()
{
   fg_kbinit(1);
   printf("Keyboard handler enabled.\n");

   do {
      printf("keys pressed:  ");
      if (fg_kbtest(LEFT))   printf("Left ");
      if (fg_kbtest(RIGHT))  printf("Right ");
      if (fg_kbtest(UP))     printf("Up ");
      if (fg_kbtest(DOWN))   printf("Down ");
      printf("\n");
      fg_waitfor(18);
   } while (fg_kbtest(ESC) == 0);

   fg_kbinit(0);
   printf("Keyboard handler disabled.\n");
}
