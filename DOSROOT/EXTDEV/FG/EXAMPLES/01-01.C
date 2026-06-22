#include <fastgraf.h>
#include <stdio.h>

void main(void);

void main()
{
   int major;
   int minor;

   fg_version(&major,&minor);
   printf("This is version %d.%2.2d of Fastgraph.\n",major,minor);
}
