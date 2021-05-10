//BMP Texture Renderer .
#ifdef BMP
#error Sorry ,Architecture Does Not Support Both Textures and Bitmaps !
#endif

#ifndef TEX
#define TEX
#include "defs.h"

#define wfa 40 //40x40 Textures Only

#define MAXTEXTURES 35 //35 Such Textures Permissible

struct textureheader
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

int ncu=-1;
rgb pal[256];

struct texture
{
textureheader h;
char bmpbuf[wfa][wfa];
};

void loadbmp(char *fn,texture &b)
{
long i,j;
int wflag=0;
char ct;
file.open(fn,ios::in|ios::binary);
if(!file){return;}
file.read((char *)&b.h,sizeof(textureheader));
if(b.h.header[0]!='B'||b.h.header[1]!='M'){file.close();return;}
//Check for Compression and Bits Per Pixel :
if(b.h.sizeofimage!=(b.h.height*b.h.width)){return;}
if(b.h.height>wfa){b.h.height=wfa;}
if(b.h.width>wfa){wflag=1;}
if(b.h.colorsused==0){b.h.colorsused=256;}
if(b.h.colorsused>=ncu){ncu=b.h.colorsused;}
for(i=0;i<b.h.colorsused;i++)
{
file.read((char *)&pal[i],sizeof(rgb));
}
for(j=0;j<b.h.height;j++)
{
if(wflag==0)
{
for(i=0;i<b.h.width;i++)
{
file.read((char *)&b.bmpbuf[i][j],sizeof(char));
}
}
else if(wflag==1)
{
for(i=0;i<wfa;i++)
{
file.read((char *)&b.bmpbuf[i][j],sizeof(char));
}
for(i=wfa;i<b.h.width;i++)
{
file.read((char *)&ct,sizeof(char));
}
}
}
if(wflag==1){b.h.width=wfa;}
file.close();
}
void init_tex()
{
int i;
for(i=0;i<NUM_COLORS;i++)
{setrgbpalette(i,0,0,0);}
for(i=0;i<NUM_COLORS;i++)
{setrgbpalette(i,(pal[i].r>>2),(pal[i].g>>2),(pal[i].b>>2));}
}

#ifndef IBGI
#define inittex() init_tex()
#endif

#ifdef IBGI
#ifdef ISVGA
#define inittex() init_tex()
#endif
#ifndef ISVGA
#define inittex()
#endif
#endif

#endif

