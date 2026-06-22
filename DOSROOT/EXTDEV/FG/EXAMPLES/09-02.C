#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
   int mode, status;
   char header[128];

   status = fg_pcxhead("CORAL.PCX",header);
   if (status == -1)
   {
      printf("Can't open CORAL.PCX.\n");
      exit(1);
   }
   else if (status == -2)
   {
      printf("CORAL.PCX is not a PCX file.\n");
      exit(1);
   }

   mode = fg_pcxmode(header);
   printf("Optimal display mode is %d.\n",mode);
}
