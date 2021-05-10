/******************************************************************\
*  MAKEFONT.C -- source code to turn a PCX file into a header file *
*                containing 5x5 font data.                         *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <Fastgraf.h>

FILE *stream;
unsigned char font5[480];

void main()
{
   unsigned char i,j;
   int x,y;
   int index;

   /* set the video mode to 320x200x256 VGA */
   fg_setmode(19);

   /* display the pcx file */
   fg_showpcx("font5.pcx",0);

   /* open the header file */
   stream = fopen("font5.h","wt");

   /* write the array declaration in the header file */
   fprintf(stream,"static unsigned char font5[] = {\n");

   /* get the characters */
   fg_setcolor(15);
   index = 0;
   x = 16;
   y = 16;

   /* move down the columns */
   for (i = 33; i <= 126; i++)
   {
      fg_move(x,y);
      fg_getmap(&font5[index],1,5);
      for (j = 0; j<5; j++)
      {
        fprintf(stream," 0x%4.4X,",font5[index++]);
      }
      fprintf(stream,"  /* %c */",i);
      fprintf(stream,"\n");
      y+= 16;

      /* end of column, go to next column */
      if (y > 199)
      {
         y = 16;
         x += 16;
      }
   }

   fprintf(stream,"};\n\n");
   fclose(stream);

   fg_waitkey();
   fg_setmode(3);
   fg_reset();
   exit(0);
}
