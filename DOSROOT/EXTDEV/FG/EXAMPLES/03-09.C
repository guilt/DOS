#include <fastgraf.h>
#include <stdio.h>

void main(void);

char *description[] =
{
   "cannot be determined",
   "VESA",
   "Ahead A",
   "Ahead B",
   "ATI 18800",
   "ATI 18800-1",
   "ATI 28800",
   "Chips & Technologies 82c451/455/456",
   "Chips & Technologies 82c452",
   "Chips & Technologies 82c453",
   "Genoa 6000 series",
   "Oak OTI-067",
   "Paradise PVGA1a",
   "Paradise WD90C00/WD90C10",
   "Paradise WD90C11/WD90C30/WD90C31",
   "Trident 8800",
   "Trident 8900",
   "Tseng ET3000",
   "Tseng ET4000",
   "Video7",
   "Cirrus Logic 5400 series",
   "S3",
   "Trident 8900B/8900C/9000"
};

void main()
{
   int id, major, minor;

   id = fg_svgainit(0);
   printf("SVGA chipset:  %s\n",description[id]);
   printf("video memory:  %d kilobytes\n",fg_memory());
   fg_svgaver(&major,&minor);
   printf("SVGA version:  %d.%2.2d\n",major,minor);
}
