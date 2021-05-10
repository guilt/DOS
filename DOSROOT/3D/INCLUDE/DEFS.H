//Definitions File .

#ifndef IDEF
#define IDEF
#include "mathd.h"

#ifdef IBGI

int bgm,bgd;
char bgpath[]={"..\\BGI"}; //Fix Your Own BGI Path !

#ifndef ISVGA
void graini()
{
clrscr();
bgd=DETECT;
initgraph(&bgd,&bgm,bgpath);
}
#endif

#ifdef ISVGA
#define SVGAPATH "SVGA256"
#include "svga256.h"
char svgapath[]={"SVGA256"};
void setsvgapal()
{
int i;
DacPalette256 PalBuf;
REGPACK reg;
PalBuf[0][0] = PalBuf[0][1] = PalBuf[0][2] = 0;
for(i=1;i<256;i++)
{
PalBuf[i][0] = i/16;
PalBuf[i][1] = i%64;
PalBuf[i][2] = (255-i)/4;
}
reg.r_ax = 0x1013;
reg.r_bx = 0;
reg.r_cx = 256;
reg.r_es = FP_SEG(PalBuf);
reg.r_dx = FP_OFF(PalBuf);
intr(0x10,&reg);
}

void graini(int tm = SVGA640x480x256)
{
bgd=installuserdriver(svgapath,NULL),bgm=tm;
initgraph(&bgd,&bgm,bgpath);
if(graphresult()!=grOk)
{return;}
setsvgapal();
}

#endif

void graclo()
{
closegraph();
restorecrtmode();
clrscr();
}
#define svgraini() graini()
#endif

#ifndef IBGI
void graini()
{
clrscr();
set_mode(VGA_256_COLOR_MODE);      
}

void graclo()
{
set_mode(TEXT_MODE);                					 
}
#endif

#endif