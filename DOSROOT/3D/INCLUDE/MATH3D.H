//File That Does 3D Point Manipulation .

#ifdef IBGI
#define rad(o) (o*M_PI)/180
#define NUM_COLORS getmaxcolor()+1
#include "ctype.h"
#include "math.h"
#include "string.h"
#include "bios.h"
#include "dos.h"
#include "fstream.h"
#include "iomanip.h"
#include "graphics.h"
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#endif

#ifndef IBGI
#include "vga.h"
#endif

double mod(double a)
{
if(a<0)
{a*=-1;}
return a;
}

struct tempp
{
double x,y;
}pg,pg1,pg2;

struct point3d
{
double x,y,z;
};

struct point3dc
{
double r,o,z;
};

struct line3d
{
point3d p1,p2;
};

struct triangle3d
{
point3d p1,p2,p3;
};

void trans(point3d &p,double x,double y,double z)
{
p.x+=x;
p.y+=y;
p.z+=z;
}

void altrans(line3d &l,double x,double y,double z)
{
trans(l.p1,x,y,z);
trans(l.p2,x,y,z);
}

void attrans(triangle3d &t,double x,double y,double z)
{
trans(t.p1,x,y,z);
trans(t.p2,x,y,z);
trans(t.p3,x,y,z);
}

void rtrans(double &x,double &y,int deg)
{
double r = rad(deg);
double x1,y1;
x1=x*cos(r)-y*sin(r);
y1=x*sin(r)+y*cos(r);
x=x1;
y=y1;
}

void rot(point3d &p,int degx,int degy,int degz)
{
rtrans(p.y,p.z,degx);
rtrans(p.z,p.x,degy);
rtrans(p.x,p.y,degz);
}

void alrot(line3d &l,int degx,int degy,int degz)
{
rot(l.p1,degx,degy,degz);
rot(l.p2,degx,degy,degz);
}

void atrot(triangle3d &t,int degx,int degy,int degz)
{
rot(t.p1,degx,degy,degz);
rot(t.p2,degx,degy,degz);
rot(t.p3,degx,degy,degz);
}