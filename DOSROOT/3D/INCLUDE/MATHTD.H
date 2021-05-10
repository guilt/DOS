//File That Can Draw Textured Objects .
#include "tril.h"

int i;
textriangle3d t,clt;

struct tpm
{
int p1,p2,p3,texno;
};

struct trimesh
{
tpm td[50];
int no;
};

struct tobject
{
point3d p[50];
int no;
point3d cr;
trimesh t;
};

void atotrans(tobject &o,double x,double y,double z)
{
int i;
for(i=0;i<o.no;i++)
{
trans(o.p[i],x,y,z);
}
}

void atorot(tobject &o,int degx,int degy,int degz)
{
int i;
for(i=0;i<o.no;i++)
{
rot(o.p[i],degx,degy,degz);
}
}

int readtobj(char *fn,tobject &o)
{
char c;
int i;
o.no=0;
file.open(fn,ios::in);
if(!file){return -1;}
file>>o.no;
o.cr.x=0,o.cr.y=0,o.cr.z=0;
for(i=0;i<o.no;i++)
{
file>>o.p[i].x;
o.cr.x+=o.p[i].x;
file.get(c);
file>>o.p[i].y;
o.cr.y+=o.p[i].y;
file.get(c);
file>>o.p[i].z;
o.cr.z+=o.p[i].z;
}
o.cr.x/=o.no,o.cr.y/=o.no,o.cr.z/=o.no;
file>>o.t.no;
for(i=0;i<o.t.no;i++)
{
file>>o.t.td[i].p1;
file.get(c);
file>>o.t.td[i].p2;
file.get(c);
file>>o.t.td[i].p3;
file.get(c);
file>>o.t.td[i].texno;
o.t.td[i].texno%=MAXTEXTURES;
}
file.close();
return 0;
}

int texlno;
char texname[MAXTEXTURES][60];

void loadtex(char *fn)
{
int i;
file.open(fn,ios::in);
if(!file){return ;}
file>>texlno;
texlno%=MAXTEXTURES+1;
for(i=0;i<texlno;i++)
{
file>>texname[i];
}
file.close();
}

void rinittex()
{
int i;
for(i=0;i<texlno;i++){loadbmp(texname[i],tex[i]);}
inittex();
}

void drawtobj(tobject &o)
{
for(i=0;i<o.t.no;i++)
{
t.t.p1=o.p[o.t.td[i].p1];
t.t.p2=o.p[o.t.td[i].p2];
t.t.p3=o.p[o.t.td[i].p3];
t.texno=o.t.td[i].texno;
render(t);
}
}

void clrtobj(tobject &o)
{
for(i=0;i<o.t.no;i++)
{
clt.t.p1=o.p[o.t.td[i].p1];
clt.t.p2=o.p[o.t.td[i].p2];
clt.t.p3=o.p[o.t.td[i].p3];
clt.texno=0;
clear(clt);
}
}