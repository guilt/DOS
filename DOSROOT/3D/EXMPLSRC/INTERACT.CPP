//User Interactive Triangle Rotation and Revolution .

//Notice that when one of the Vertices is the Origin ,Revolution changes
//to Rotation .But anyway ,to Rotate a triangle ,none of the vertices being
//the Origin ,fix a point ,such as the Vertex/Centroid as the Origin
//and proceed .

//Press x/y/z to choose the axis (default z) .Press Up/Down to move
//in Counterclockwise ,along that axis .Press Escape to Quit .

#include "defs.h"

void main()
{
char c,d;
int flag=2;
int degx=0,degy=0,degz=0;
triangle3d t1,t2,t3,t4;
t1.p1.x=0,t1.p1.y=0,t1.p1.z=0;
t1.p2.x=0,t1.p2.y=0,t1.p2.z=5;
t1.p3.x=5,t1.p3.y=0,t1.p3.z=0;
t3.p1.x=10,t3.p1.y=10,t3.p1.z=10;
t3.p2.x=10,t3.p2.y=10,t3.p2.z=15;
t3.p3.x=15,t3.p3.y=10,t3.p3.z=10;
graini();
clearviewport();
t2=t1;
t4=t3;
do
{
drawaxis(LIGHTBLUE);
drawtriangle(t2,RED);
drawtriangle(t4,GREEN);
c=getch();
if(c=='x'){flag=0;}
if(c=='y'){flag=1;}
if(c=='z'){flag=2;}
if(c==0){d=getch();}
if(d==72)
{
if(flag==0){degx+=10;}
if(flag==1){degy+=10;}
if(flag==2){degz+=10;}
}
if(d==80)
{
if(flag==0){degx-=10;}
if(flag==1){degy-=10;}
if(flag==2){degz-=10;}
}
drawtriangle(t2,BLACK);
drawtriangle(t4,BLACK);
drawaxis(BLACK);
t2=t1;
t4=t3;
atrot(t2,degx,degy,degz);
atrot(t4,degx,degy,degz);
d=-1;
}
while(c!=27);
graclo();
}