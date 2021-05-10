//Planes and Bitmapsizing Demo .
#include "bmp.h"

void main()
{
int x,y;
point3d p;
int color;
bitmap b;
int w;
int h;
double cf=2; //Compression Factor of Image .
loadbmp("demog.bmp",b);
w = b.h.width/2;
h = b.h.height/2;
graini();
initbmp(b);
clearviewport();
for(x=-1*w;x<w;x++)
{
p.x=x/(xscale*cf);
for(y=-1*h;y<h;y++)
{
p.y=y/(yscale*cf);
p.z=0;
color=b.bmpbuf[(x+w)%b.h.width][(y+h)%b.h.height];
drawpoint(p,color);
}
}
getch();
clearviewport();
for(x=-1*w;x<w;x++)
{
p.z=x/(zscale*cf);
for(y=-1*h;y<h;y++)
{
p.x=y/(xscale*cf);
p.y=0;
color=b.bmpbuf[(x+w)%b.h.width][(y+h)%b.h.height];
drawpoint(p,color);
}
}
getch();
clearviewport();
for(x=-1*w;x<w;x++)
{
p.y=x/(yscale*cf);
for(y=-1*h;y<h;y++)
{
p.z=y/(zscale*cf);
p.x=0;
color=b.bmpbuf[(x+w)%b.h.width][(y+h)%b.h.height];
drawpoint(p,color);
}
}
getch();
graclo();
}
