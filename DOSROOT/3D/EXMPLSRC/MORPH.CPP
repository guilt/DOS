//Morphology .
//Can Use for Generic Pictures .
#define I24BIT
#include "image.h"

#define MT 80

#define min(a,b) a<b?a:b

void morph(int x,int y,image &i1,byte pal1[768],image &i2,byte pal2[768])
{
int i,j,t,h1,w1,h2,w2,hm,wm,c1,c2,r1,g1,b1,r2,g2,b2,r,g,b;
h1=i1.height(),w1=i1.width(),h2=i2.height(),w2=i2.width();
hm=min(h1,h2);wm=min(w1,w2);
for(t=0;t<=MT;t++)
{
for(i=0;i<hm;i++)
{
for(j=0;j<wm;j++)
{
c1=i1.getvpixel(j,i);c2=i2.getvpixel(j,i);
r1=pal1[(c1*3)  ],g1=pal1[(c1*3)+1],b1=pal1[(c1*3)+2];
r2=pal2[(c2*3)  ],g2=pal2[(c2*3)+1],b2=pal2[(c2*3)+2];
r=((r1*(MT-t))+(r2*t))/MT,g=((g1*(MT-t))+(g2*t))/MT,
b=((b1*(MT-t))+(b2*t))/MT;put24pixel(x+j,y+i,r,g,b);
}
}
}
}

void main()
{
image i1,i2;
byte pal1[768],pal2[768];
//Cheetah and The Suzuki .
i1.load("che.im",196);loadfilepalette("che.pal",pal1);
i2.load("suz.im");loadfilepalette("suz.pal",pal2);
graini();
set24pal(b24palette);
while(!kbhit())
{
morph(110,30,i1,pal1,i2,pal2);
morph(110,30,i2,pal2,i1,pal1);
}
graclo();
}