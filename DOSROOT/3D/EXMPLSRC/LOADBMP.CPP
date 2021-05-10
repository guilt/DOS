//Simple Bitmap Demo .
#include "bmp.h"

void main()
{
bitmap *b=new bitmap;
graini();
loadbmp("kdemo1.bmp",*b);
drawbmp(*b,0,0);
loadbmp("kdemo2.bmp",*b);
drawbmp(*b,95,30);
loadbmp("kdemo3.bmp",*b);
drawbmp(*b,190,60);
gotoxy(1,24);
printf("SwordFish");
getch();
graclo();
}

