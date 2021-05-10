//Gun Demo .
#include "defs.h"

void main()
{
int i,j;
object o,ob;
object o1,ob1;
char c;
graini();
clearviewport();
readobj("OBJ.TXT",ob);
o=ob;
readobj("OBJB.TXT",ob1);
o1=ob1;
for(j=0;j<=37;j++)
{
for(i=0;i<5;i++)
{
drawobj(o,7);
drawobj(o1,15);
delay(5);
drawobj(o,0);
aorot(o,0,0,7);
drawobj(o,7);
delay(5);
drawobj(o,0);
aorot(o,0,0,-7);
drawobj(o,7);
delay(5);
drawobj(o,0);
drawobj(o1,0);
o1=ob1;
aotrans(o1,(i*20),0,0);
aorot(o1,0,(10*j),0);
}
o=ob;
aorot(o,0,(10*j),0);
}
drawobj(o,7);
drawobj(o1,15);
c=getch();
c++;
graclo();
}