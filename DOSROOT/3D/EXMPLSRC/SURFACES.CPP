//3D Graphs with Normal Contours .

#include "defs.h"

void main()
{
double r,s;
point3d p1;
graini();
clearviewport();
for(r=-8;r<=8;r+=0.01)
{
p1.x=r;
for(s=-8;s<=8;s+=0.01)
{
p1.z=s;

//Deselect the Required Sections .

//p1.y=((p1.z*p1.x)*((p1.x*p1.x)-(p1.z*p1.z))/((p1.x*p1.x)+(p1.z*p1.z)));

//p1.y=0.1*(p1.z*p1.z)-0.5*(p1.x*p1.x);

p1.y=0.3*(p1.z*p1.z)+0.3*(p1.x*p1.x);

//p1.y=(p1.x*p1.z)/((p1.z*p1.z)+(p1.x*p1.x))*20;

//p1.y=(((p1.x*p1.x)+1)/((p1.z*p1.z)+1))*0.4;

conplot(p1,14);
}
}
drawaxis(1);
getch();
graclo();
}