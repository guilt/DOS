#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int status;

   fg_setmode(-1);
   status = fg_mouseini();

   if (status < 0)
      printf("Mouse not available.\n");
   else
      printf("%d button mouse found.\n",status);
}
