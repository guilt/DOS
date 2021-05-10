//Easy to Use Image Converter .
//With : Mini BMP File Loader .
#include "fstream.h"
#include "malloc.h"

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
}h;

struct rgb
{
char b,g,r,a;
}pal[256];

char *bmpbuf=NULL;

void bmp2ima
(char *bmpfilename,char *imfilename,int tflag=0,
unsigned char enkey=0,char *palfilename="default.pal")
{
long i,j;
fstream bmpfile,file;
bmpfile.open(bmpfilename,ios::in|ios::binary);
if(!bmpfile){cout<<"\nInp\n";return;}
bmpfile.read((char *)&h,sizeof(bitmapheader));
if(h.header[0]!='B'||h.header[1]!='M'){cout<<"\nSig\n";bmpfile.close();return;}
//Check for Compression and Bits Per Pixel :
if(h.sizeofimage!=(h.height*h.width)){cout<<"\nCmp\n";return;}
if(h.colorsused==0){h.colorsused=256;}
bmpbuf=new char[h.height*h.width];
if(bmpbuf==NULL){cout<<"\nMAL\n";bmpfile.close();return;}
for(i=0;i<h.colorsused;i++)
{bmpfile.read((char *)&pal[i],sizeof(rgb));}
for(j=0;j<h.height;j++){for(i=0;i<h.width;i++)
{bmpfile.read((char *)&bmpbuf[(j*h.width)+i],sizeof(char));
bmpbuf[(j*h.width)+i]^=enkey;}}
bmpfile.close();
file.open(imfilename,ios::out|ios::binary);
if(!file){cout<<"\nOut\n";return;}
file<<"IM";
if(!tflag)
{
file<<"B";
file.write((char *)&h.height,sizeof(int));
file.write((char *)&h.width,sizeof(int));
}
else
{
file<<"T\n";
file<<h.height<<" "<<h.width<<"\n";
}
for(j=0;j<h.height;j++)
{
for(i=0;i<h.width;i++)
{
if(!tflag)
{
file.write((char *)&
bmpbuf[((h.height-1-j)*h.width)+i],sizeof(char));
}
else
{
file<<((unsigned int)
(bmpbuf[((h.height-1-j)*h.width)+i])%256)<<" ";
}
}
if(tflag){file<<"\n";}
}
free(bmpbuf);
file.close();
file.open(palfilename,ios::out|ios::binary);
if(!file){cout<<"\nPOu\n";return;}
file<<"PL";
if(!tflag){file<<"B";}
else {file<<"T\n";}
for(i=0;i<256;i++)
{
pal[i].r>>=2;
pal[i].g>>=2;
pal[i].b>>=2;
pal[i].r&=63;
pal[i].g&=63;
pal[i].b&=63;
if(!tflag)
{
file.write((char *)&pal[i].r,sizeof(char));
file.write((char *)&pal[i].g,sizeof(char));
file.write((char *)&pal[i].b,sizeof(char));
}
else
{
file<<((unsigned int)pal[i].r)%256<<" "
    <<((unsigned int)pal[i].g)%256<<" "
    <<((unsigned int)pal[i].b)%256<<"\n";
}
}
cout<<"\nOK!\n";
file.close();
}
