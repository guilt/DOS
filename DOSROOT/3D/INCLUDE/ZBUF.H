//The Important Z-Buffering File .
#include "tex.h"

#ifndef IZBUF
#define zbufr(x,y,z,color) putpixel(x,y,color)
#define mkzbuf()
#define rmzbuf()
#define clrzbuf() clearviewport()
#endif

#ifdef IBGI
#define zbufr(x,y,z,color) putpixel(x,y,color)
#define mkzbuf()
#define rmzbuf()
#define clrzbuf() clearviewport()
#endif

#ifdef IHSR
#ifdef IZBUF
#ifndef IBGI
#include "alloc.h"

#define ZMEM screen_height*screen_width
#define ZPARAM 500

int far *zbuffer;
int zerr=0;

void mkzbuf()
{
zbuffer = (int far*)farmalloc(ZMEM);
if(zbuffer==NULL){zerr=1;}
}

void clrzbuf()
{
long i;
for(i=0;i<ZMEM;i++)
{
if(zerr==0)
{
zbuffer[i]=-32768;
}
VGA[i]=0;        //Also Clear The Screen
}
}

void zbufr(int &x,int &y,char z,int color)
{
#ifndef IBGI
check(x,y);
#endif
int offset=(screen_width*y)+x;
if(zerr==0)
{
if((z*ZPARAM)>zbuffer[offset]){zbuffer[offset]=(z*ZPARAM);putpixel(x,y,color);}
}
}

void rmzbuf()
{
if(zerr==0)
{
farfree(zbuffer);
}
}
#endif
#endif
#endif
