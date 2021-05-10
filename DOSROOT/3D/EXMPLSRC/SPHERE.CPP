//Draws a Sphere With Spherical Coordinates .
#include "defs.h"

void main()
{
double ro,o,p,or,pr,asp=1.2;
point3d p1;
graini();
clearviewport();
ro=8;
for(o=0;o<=360;o++)
{
or=rad(o);
for(p=0;p<=180;p++)
{
pr=rad(p);
p1.y=ro*cos(pr);
p1.z=ro*sin(pr)*sin(or);
p1.x=asp*ro*sin(pr)*cos(or);
sconplot(p1,14,o,p);
}
}
drawaxis(1);
getch();
graclo();
}