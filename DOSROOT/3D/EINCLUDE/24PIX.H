//My Own Funky 24-BPP Palette .
#include "defs.h"

#ifdef IBGI
#define byte unsigned char
#define word unsigned int
#define dword unsigned long
#endif

#ifndef IBGI
#ifdef I24BIT

byte b24palette[768];

void set24pal(byte palette[768])
{
int i,j,k;
for(i=216;i<256;i++) //Other Colors are Black ,Baby !
{
palette[(i*3)  ]=palette[(i*3)+1]=palette[(i*3)+2]=0;
}
for(i=0;i<6;i++) //R
{
for(j=0;j<6;j++) //G 
{
for(k=0;k<6;k++) //B
{
//Set Approximate Index Values .
palette[(((i*36) + (j*6) + k)*3)  ]=(i*10); //R
palette[(((i*36) + (j*6) + k)*3)+1]=(j*10); //G
palette[(((i*36) + (j*6) + k)*3)+2]=(k*10); //B
}
}
}
set_palette(palette);
}

//Fast 24-Bit Converter .
void put24pixel
(
int x,int y,
unsigned int r,unsigned int g,unsigned int b
)
{
//Truncate to 6-Bit .(Not 8-Bit !) .
r%=64;b%=64;g%=64;
//Derive Respective Color Indexes .
if(r>45){r=45;}r=(r+5)/10;
if(g>45){g=45;}g=(g+5)/10;
if(b>45){b=45;}b=(b+5)/10;
//Render Directly with the Calculated Indexes .
putpixel(x,y,((r*36) + (g*6) + b)%256);
}
#endif
#endif

#ifdef IBGI
#ifdef I24BIT
#error BGI Must Not be Used with 24-Bit reduction !
#endif
#endif

