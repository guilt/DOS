//Textured Z-Buffered Object Demo .
//Press x/y/z to choose the axis (default z) .Press Left/Right to move
//in Counterclockwise ,along that axis .Press Escape to Quit .

#define IHSR
#define IZBUF
#define IZCLIP
#include "mathtd.h"

void main()
{
char c,d;
int flag=2; //Default Z
int v=1,rot=10;
tobject o,o1;
mkzbuf();
readtobj("texo.txt",o); //Load The Objects .... !
readtobj("texo2.txt",o1);
graini();
loadtex("new.tex");  //Load Common Textures .... !
rinittex();
atotrans(o1,14,14,14);
do
{
clrzbuf();
drawtobj(o);
drawtobj(o1);
c=getch();
if(c=='x'){flag=0;}
if(c=='y'){flag=1;}
if(c=='z'){flag=2;}
if(c==0){d=getch();}
if(d==75)
{
v=1;
if(flag==0){atorot(o,v*rot,0,0);atorot(o1,v*rot,0,0);}
if(flag==1){atorot(o,0,v*rot,0);atorot(o1,0,v*rot,0);}
if(flag==2){atorot(o,0,0,v*rot);atorot(o1,0,0,v*rot);}
}
if(d==77)
{
v=-1;
if(flag==0){atorot(o,v*rot,0,0);atorot(o1,v*rot,0,0);}
if(flag==1){atorot(o,0,v*rot,0);atorot(o1,0,v*rot,0);}
if(flag==2){atorot(o,0,0,v*rot);atorot(o1,0,0,v*rot);}
}
d=-1;
}
while(c!=27);
rmzbuf();
graclo();
}