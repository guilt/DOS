//Surfaces with Textures on them ....

#include "bmp.h"

void main()
{
int x,y;
point3d p;
int color;
bitmap b;
int w;
int h;
int bzcf=4; //Plane Compression Factors .
int bxcf=1;
loadbmp("ietex.bmp",b);
w = b.h.width/2;
h = b.h.height/2;
graini();
initbmp(b);
clearviewport();
for(x=-1*w;x<w;x++)
{
p.z=x/(zscale*bzcf);
for(y=-1*h;y<h;y++)
{
p.x=y/(xscale*bxcf);
color=b.bmpbuf[(x+w)%b.h.width][(y+h)%b.h.height];
p.y=0.015*(-1*(p.z*p.z)+(p.x*p.x));
drawpoint(p,color);
}
}
getch();
graclo();
}
