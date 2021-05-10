//Basic VGA Library Routines .
#include "svga.h"
#include "ctype.h"
#include "math.h"
#include "string.h"
#include "bios.h"
#include "fstream.h"
#include "iomanip.h"
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"

#define setcolorpal() set_palette(dpalette);
#define fadeout() set_palette(dpalette);

byte curcolor=0,tpalette[768],dpalette[768];

void check(int &x,int &y)
{
if(x<0){x=0;}
if(y<0){y=0;}
if(x>screen_width-1){x=screen_width-1;}
if(y>screen_height-1){y=screen_height-1;}
}

void putpixel(int x,int y,byte color)
{
check(x,y);
VGA[y*screen_width+x]=color;
}

char getpixel(int x,int y)
{
check(x,y);
return VGA[y*screen_width+x];
}

void line(int x1, int y1, int x2, int y2, byte color = curcolor)
{
check(x1,y1);
check(x2,y2);
int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;
dx=x2-x1;dy=y2-y1;
dxabs=abs(dx);dyabs=abs(dy);
sdx=sgn(dx);sdy=sgn(dy);
x=dyabs>>1;y=dxabs>>1;
px=x1;py=y1;
putpixel(px,py,color);
if(dxabs>=dyabs)
{for(i=0;i<dxabs;i++)
{y+=dyabs;
if(y>=dxabs)
{y-=dxabs;
py+=sdy;}
px+=sdx;
putpixel(px,py,color);
}}else
{for(i=0;i<dyabs;i++){x+=dxabs;if(x>=dyabs)
{x-=dyabs;px+=sdx;}
py+=sdy;
putpixel(px,py,color);}}
}

void rectangle(int left,int top, int right, int bottom,
	       byte color = curcolor)
{
line(left,top,right,top,color);
line(left,top,left,bottom,color);
line(right,top,right,bottom,color);
line(left,bottom,right,bottom,color);
}

void circle(int x,int y, int radius, byte color = curcolor)
{
check(x,y);
int o;double rx,ry;
for(o=0;o<360;o++)
{rx=radius*cos(rad(o));
ry=radius*sin(rad(o));
putpixel(x+rx,y+ry,color);
}}

void set_palette(byte *palette)
{
int i;
outp(PALETTE_INDEX,0);
for(i=0;i<256*3;i++)
{outp(PALETTE_DATA,palette[i]);}
}

//Specially for the 3D Graphics Library !
void setbwpal()
{
int i;
for(i=0;i<NUM_COLORS;i++)
{
tpalette[i*3]=tpalette[(i*3)+1]=tpalette[(i*3)+2]=
(dpalette[i*3]+dpalette[(i*3)+1]+dpalette[(i*3)+2])/3;
}
set_palette(tpalette);
}

//Specially for the 3D Graphics Library !
void fadein()
{
int i;
for(i=0;i<NUM_COLORS;i++)
{
tpalette[i*3]=tpalette[(i*3)+1]=tpalette[(i*3)+2]=0;
}
set_palette(tpalette);
}

void setcolor(byte color)
{
curcolor=color;
}

byte getcolor()
{
return curcolor;
}

word getmaxx()
{return screen_width-1;
}

word getmaxy()
{return screen_height-1;
}

void clearviewport()
{
int i,j;
for(i=0;i<320;i++)
{for(j=0;j<200;j++)
{putpixel(i,j,0);
}}
}

void setrgbpalette(int color,int r,int g,int b)
{
dpalette[(color*3)]=r;
dpalette[(color*3)+1]=g;
dpalette[(color*3)+2]=b;
set_palette(dpalette);
}