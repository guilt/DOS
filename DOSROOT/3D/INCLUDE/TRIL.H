//The Triangle Renderer .
#include "zbuf.h"

#define MIN(a,b) ((a<b)?(a):(b))
#define MAX(a,b) ((a>b)?(a):(b))

//Near and Far Clipping Planes .

#define Hither 30
#define Yon -30

#define zclip(z) (z<=0)?((z<=Yon)?z=Yon:z):((z>=Hither)?z=Hither:z)

int xd1,yd1,xd2,yd2;
int Lx,Rx;
int x;
char z;    //Important For Z-Buffering .
tempp tp;
tempp p1,p2,p3;

#ifdef IHSR
double x1,y1,z1;
double x2,y2,z2;
double x3,y3,z3;
double D;
#endif

texture tex[MAXTEXTURES];

struct textriangle3d
{
triangle3d t;
int texno;
};

void sort(tempp &p1,tempp &p2)
{
if(p1.y>p2.y)
{
tp=p1;
p1=p2;
p2=tp;
}
}

void hline(int x1,int x2,int y,int texno)
{
for(x=x1;x<=x2;x++)
{zbufr(x,y,z,tex[texno].bmpbuf
[x%tex[texno].h.width]
[tex[texno].h.height-(y%tex[texno].h.width)]);}
}

void chline(int x1,int x2,int y)
{
for(x=x1;x<=x2;x++)
{putpixel(x,y,0);}
}

void clear(textriangle3d t)
{
int i;
#ifdef IZCLIP
zclip(t.t.p1.z);zclip(t.t.p2.z);zclip(t.t.p3.z);
#endif
#ifdef IHSR
x1=t.t.p1.x,y1=t.t.p1.y,z1=t.t.p1.z;
x2=t.t.p2.x,y2=t.t.p2.y,z2=t.t.p2.z;
x3=t.t.p3.x,y3=t.t.p3.y,z3=t.t.p3.z;
/*Plane Equation : Ax+By+Cz+D=0 */
D=-x1*(y2*z3-y3*z2)-x2*(y3*z1-y1*z3)-x3*(y1*z2-y2*z1);
if(D>=0)
{
#endif
algo(t.t.p1);algo1(t.t.p2);algo2(t.t.p3);
p1=pg;p2=pg1;p3=pg2;
sort(p1,p2);sort(p2,p3);sort(p1,p2);
xd1=p2.x-p1.x;yd1=p2.y-p1.y;
xd2=p3.x-p1.x;yd2=p3.y-p1.y;
if(yd1)
{for(i=p1.y; i<=p2.y; i++)
{Lx = p1.x + (((i - p1.y) * xd1) / yd1);
Rx = p1.x + (((i - p1.y) * xd2) / yd2);
chline(MIN(Lx,Rx),MAX(Lx,Rx),i);
}}
xd1=p3.x-p2.x;yd1=p3.y-p2.y;
if(yd1)
{for(i=p2.y;i<=p3.y;i++)
{Lx = p1.x + (((i - p1.y) * xd2) / yd2);
Rx = p2.x + (((i - p2.y) * xd1) / yd1);
chline(MIN(Lx,Rx),MAX(Lx,Rx),i);
}}
#ifdef IHSR
}
#endif
}

void render(textriangle3d t)
{
int i;
#ifdef IZCLIP
zclip(t.t.p1.z);zclip(t.t.p2.z);zclip(t.t.p3.z);
#endif
#ifdef IHSR
x1=t.t.p1.x,y1=t.t.p1.y,z1=t.t.p1.z;
x2=t.t.p2.x,y2=t.t.p2.y,z2=t.t.p2.z;
x3=t.t.p3.x,y3=t.t.p3.y,z3=t.t.p3.z;
/*Plane Equation : Ax+By+Cz+D=0 */
D=-x1*(y2*z3-y3*z2)-x2*(y3*z1-y1*z3)-x3*(y1*z2-y2*z1);
if(D>=0)
{
#endif
algo(t.t.p1);algo1(t.t.p2);algo2(t.t.p3);
p1=pg;p2=pg1;p3=pg2;
sort(p1,p2);sort(p2,p3);sort(p1,p2);
xd1=p2.x-p1.x;yd1=p2.y-p1.y;
xd2=p3.x-p1.x;yd2=p3.y-p1.y;
if(yd1)
{for(i=p1.y; i<=p2.y; i++)
{Lx = p1.x + (((i - p1.y) * xd1) / yd1);
Rx = p1.x + (((i - p1.y) * xd2) / yd2);
hline(MIN(Lx,Rx),MAX(Lx,Rx),i,t.texno);
}}
xd1=p3.x-p2.x;yd1=p3.y-p2.y;
if(yd1)
{for(i=p2.y;i<=p3.y;i++)
{Lx = p1.x + (((i - p1.y) * xd2) / yd2);
Rx = p2.x + (((i - p2.y) * xd1) / yd1);
hline(MIN(Lx,Rx),MAX(Lx,Rx),i,t.texno);
}}
#ifdef IHSR
}
#endif
}

