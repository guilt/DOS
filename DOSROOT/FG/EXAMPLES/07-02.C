#include <fastgraf.h>
#include <string.h>

void main(void);
void put_string(char*,int,int);

void main()
{
   int old_mode;
   int row, column;

   old_mode = fg_getmode();
   fg_setmode(3);
   fg_cursor(0);

   fg_setattr(14,0,0);
   put_string("yellow",0,0);

   fg_setattr(10,0,0);
   fg_where(&row,&column);
   put_string("green",row,column+1);

   fg_setattr(12,0,1);
   fg_where(&row,&column);
   put_string("blinking",row,column+1);

   fg_setattr(12,7,0);
   put_string(" Press any key. ",24,0);
   fg_waitkey();

   fg_setmode(old_mode);
   fg_reset();
}

void put_string(string,row,column)
char *string;
int row, column;
{
   fg_locate(row,column);
   fg_text(string,strlen(string));
}
