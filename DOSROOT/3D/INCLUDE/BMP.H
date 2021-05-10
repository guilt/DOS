//BMP File Renderer .
#ifdef TEX
#error Sorry ,Architecture Does Not Support Both Textures and Bitmaps !
#endif

#ifndef BMP
#define BMP
#include "defs.h"

struct bitmapheader
{
char header[2]; //BM
long fsize;
long reserved;// 0
long offset;//
long headersize;// 40
int width;
int widthreserved;
int height;
int heightreserved;
int planes;// 1
int bpp;// 8
long compression;// 0
long sizeofimage;// Size of Bitmap in Bytes
long xpixelspermetre;
long ypixelspermetre;
int colorsused;
int colorsusedreserved;
long importantcolors;
};

struct rgb
{
char b,g,r,a;
};

struct bitmap
{
bitmapheader h;
rgb pal[256];
char bmpbuf[200][200];
};

void loadbmp(char *fn,bitmap &b)
{
long i,j;
file.open(fn,ios::in|ios::binary);
if(!file){return;}
file.read((char *)&b.h,sizeof(bitmapheader));
if(b.h.header[0]!='B'||b.h.header[1]!='M'){file.close();return;}
//Check for Compression and Bits Per Pixel :
if(b.h.sizeofimage!=(b.h.height*b.h.width)){return;}
if(b.h.height>200||b.h.width>200){return;}
if(b.h.colorsused==0){b.h.colorsused=256;}
for(i=0;i<b.h.colorsused;i++)
{
file.read((char *)&b.pal[i],sizeof(rgb));
}
for(j=0;j<b.h.height;j++)
{
for(i=0;i<b.h.width;i++)
{
file.read((char *)&b.bmpbuf[i][j],sizeof(char));
}
}
file.close();
}

void init_bmp(bitmap &b)
{
int i;
for(i=0;i<NUM_COLORS;i++)
{setrgbpalette(i,0,0,0);}
for(i=0;i<b.h.colorsused;i++)
{setrgbpalette(i,(b.pal[i].r>>2),(b.pal[i].g>>2),(b.pal[i].b>>2));}
}

#ifndef IBGI
#define initbmp(a) init_bmp(a)
#endif

#ifdef IBGI
#ifdef ISVGA
#define initbmp(a) init_bmp(a)
#endif
#ifndef ISVGA
#define initbmp(a)
#endif
#endif


void drawbmp(bitmap &b,int xo,int yo)
{
int i,j;
initbmp(b);
for(i=0;i<b.h.width;i++)
{
for(j=0;j<b.h.height;j++)
{
putpixel(i+xo,b.h.height+yo-j-1,b.bmpbuf[i][j]);
}
}
}
#endif
