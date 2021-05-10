//Easy Image Routines .
#include "fonts.h"

#define I_ORD_DRAW 0
#define I_OR_DRAW 1
#define I_XOR_DRAW 2
#define I_AND_DRAW 3

#define unchar unsigned char
#define unint unsigned int

fstream ifile;

void setfilepalette(char palfilename[] = "default.pal")
{
int i,r,g,b,tflag=0;
unsigned int tmp;char a;
ifile.open(palfilename,ios::in|ios::binary);
if(!ifile){return;}
if(ifile.get()!='P'||ifile.get()!='L'){ifile.close();return;}
if(ifile.get()=='T'){tflag=1;ifile.get();}
for(i=0;i<256;i++)
{
if(!tflag)
{
ifile.read((char *)&r,sizeof(char));
ifile.read((char *)&g,sizeof(char));
ifile.read((char *)&b,sizeof(char));
}
else
{
ifile>>r;ifile.get();
ifile>>g;ifile.get();
ifile>>b;ifile.get();
}
setrgbpalette(i,r,g,b);
}
ifile.close();
}

//Special Function !
#ifndef IBGI
void loadfilepalette(char palfilename[] = "default.pal",
					 byte palette[768] = dpalette)
{
int i,r,g,b,tflag=0;unsigned int tmp;char a;
ifile.open(palfilename,ios::in|ios::binary);
if(!ifile){return;}
if(ifile.get()!='P'||ifile.get()!='L'){ifile.close();return;}
if(ifile.get()=='T'){tflag=1;ifile.get();}
for(i=0;i<256;i++)
{
if(!tflag)
{
ifile.read((char *)&r,sizeof(char));
ifile.read((char *)&g,sizeof(char));
ifile.read((char *)&b,sizeof(char));
}
else
{
ifile>>r;ifile.get();
ifile>>g;ifile.get();
ifile>>b;ifile.get();
}
palette[(i*3)  ]=r;
palette[(i*3)+1]=g;
palette[(i*3)+2]=b;
}
ifile.close();
}
#endif

class image
{

unint h,w,i,j,k,l;
unchar *bmpbuf;

void ballocate()
{
if(!h||!w){return;}
bmpbuf=new unchar[(h*w)];
}

public :

unint height(){return h;}

unint width(){return w;}

void setpixel(unint c,unint r,unchar val) /*X,Y*/
{
if(bmpbuf==NULL||r>=h||c>=w){return;}
else bmpbuf[(r*w)+c]=val;
}

unchar getvpixel(unint c,unint r) /*X,Y*/
{
if(bmpbuf==NULL||r>=h||c>=w){return 0;}
else return bmpbuf[(r*w)+c];
}

void load(char [],unchar);
void draw(unint ,unint);
void sdraw(unint ,unint ,unint);
void stdraw(unint ,unint ,unint ,unint);

image()
{
bmpbuf=NULL;h=w=0;
}

image(char filename[],unchar enkey = 0)
{
load(filename,enkey);
}

~image()
{
if(bmpbuf!=NULL)
{delete []bmpbuf;h=w=0;}
}

};

void image :: draw(unint x = 0,unint y = 0)
{
unchar igl;
for(i=0;i<h;i++)
{
for(j=0;j<w;j++)
{
igl=getvpixel(j,i);
#ifdef IBGI
putpixel(x+j,y+i,igl);
#endif
#ifndef IBGI
#ifdef I24BIT
put24pixel(x+j,y+i,
dpalette[(igl*3)  ],dpalette[(igl*3)+1],dpalette[(igl*3)+2]);
#endif
#ifndef I24BIT
putpixel(x+j,y+i,igl);
#endif
#endif
}
}
}

void image :: sdraw(unint x = 0,unint y = 0,unint mode=I_ORD_DRAW)
{
unchar igl;
for(i=0;i<h;i++)
{
for(j=0;j<w;j++)
{
igl=getvpixel(j,i);
if     (mode==I_OR_DRAW ){igl=(getpixel(x+j,y+i)|igl);}
else if(mode==I_AND_DRAW){igl=(getpixel(x+j,y+i)&igl);}
else if(mode==I_XOR_DRAW){igl=(getpixel(x+j,y+i)^igl);}
#ifdef IBGI
putpixel(x+j,y+i,igl);
#endif
#ifndef IBGI
#ifdef I24BIT
put24pixel(x+j,y+i,
dpalette[(igl*3)  ],dpalette[(igl*3)+1],dpalette[(igl*3)+2]);
#endif
#ifndef I24BIT
putpixel(x+j,y+i,igl);
#endif
#endif
}
}
}

void image :: stdraw(unint x1,unint y1,unint x2,unint y2)
{
unchar igl = 0;
unint nx = (x2+1)-x1,ny = (y2+1)-y1;
float xr,yr;
if((x1>=x2)||(y1>=y2)){return;}
if(!h||!w){return;}
xr = nx/w,yr = ny/h;
for(i=0;i<h;i++)
{
for(j=0;j<w;j++)
{
igl=getvpixel(j,i);
if(xr<=1)
{
 if(yr<=1)
 {
 #ifdef IBGI
 putpixel(x1+j,y1+i,igl);
 #endif
 #ifndef IBGI
 #ifdef I24BIT
 put24pixel(x1+j,y1+i,
 dpalette[(igl*3)  ],dpalette[(igl*3)+1],dpalette[(igl*3)+2]);
 #endif
 #ifndef I24BIT
 putpixel(x1+j,y1+i,igl);
 #endif
 #endif
 }
 else
 {
 for(k=0;k<(unint)(yr+0.5);k++)
 {
 #ifdef IBGI
 putpixel(x1+j,y1+((i*yr)+k),igl);
 #endif
 #ifndef IBGI
 #ifdef I24BIT
 put24pixel(x1+j,y1+((i*yr)+k),
 dpalette[(igl*3)  ],dpalette[(igl*3)+1],dpalette[(igl*3)+2]);
 #endif
 #ifndef I24BIT
 putpixel(x1+j,y1+((i*yr)+k),igl);
 #endif
 #endif
 }
 }
}
else
{
 if(yr<=1)
 {
 for(l=0;l<(unint)(xr+0.5);l++)
 {
 #ifdef IBGI
 putpixel(x1+((j*xr)+l),y1+i,igl);
 #endif
 #ifndef IBGI
 #ifdef I24BIT
 put24pixel(x1+((j*xr)+l),y1+i,
 dpalette[(igl*3)  ],dpalette[(igl*3)+1],dpalette[(igl*3)+2]);
 #endif
 #ifndef I24BIT
 putpixel(x1+((j*xr)+l),y1+i,igl);
 #endif
 #endif
 }
 }
 else
 {
 for(k=0;k<(unint)(yr+0.5);k++)
 {
 for(l=0;l<(unint)(xr+0.5);l++)
 {
 #ifdef IBGI
 putpixel(x1+((j*xr)+l),y1+((i*yr)+k),igl);
 #endif
 #ifndef IBGI
 #ifdef I24BIT
 put24pixel(x1+((j*xr)+l),y1+((i*yr)+k),
 dpalette[(igl*3)  ],dpalette[(igl*3)+1],dpalette[(igl*3)+2]);
 #endif
 #ifndef I24BIT
 putpixel(x1+((j*xr)+l),y1+((i*yr)+k),igl);
 #endif
 #endif
 }
 }
 }
}
}
}
}


void image :: load(char imafilename[],unchar enkey = 0)
{
unint tmp,tflag=0;
unchar c;
if(bmpbuf!=NULL){delete []bmpbuf;}
h=w=0;
ifile.open(imafilename,ios::in|ios::binary);
if(!ifile){return;}
if(ifile.get()!='I'||ifile.get()!='M'){ifile.close();return;}
if(ifile.get()=='T'){tflag=1;}
if(!tflag)
{
ifile.read((char *)&h,sizeof(unint));
ifile.read((char *)&w,sizeof(unint));
}
else
{
ifile.get();ifile>>h;ifile.get();ifile>>w;ifile.get();
}
ballocate();
if(bmpbuf==NULL){h=w=0;return;}
for(i=0;i<h;i++)
{
for(j=0;j<w;j++)
{
if(!tflag)
{
ifile.read((char *)&c,sizeof(unchar));
}
else
{
ifile>>tmp;c=(unchar)tmp;ifile.get();
}
c^=enkey;
setpixel(j,i,c);
}
if(tflag){ifile.get();}
}
ifile.close();
}
