/******************************************************************\
*  Char.c -- Source code for displaying text, used in Tommy game   *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "gamedefs.h"
#include "font5.h"        /* header file containing 5x5 font data */
/******************************************************************/
void put_string(char *string,int ix,int iy)
{
   register int i;
   int index, nchar;
   char ch;

   nchar = strlen(string);

   /* display a character string of 5x5 characters */
   for (i = 0; i < nchar; i++)
   {
      ch = (char)(string[i]-33);
      if (ch >= 0)
      {
         index = ch*5;

         /* move to the x,y location */
         fg_move(ix,iy);

         /* display one letter */
         fg_drawmap((char *)&font5[index],1,5);
      }
      ix += 6;
   }
}
/******************************************************************/
void center_string(char *string,int x1,int x2,int y)
{
   int nchar;
   int x;

   /* center a string between x1 and x2 */
   nchar = strlen(string);
   x = ((x1 + x2) / 2) - nchar*3;
   put_string(string,x,y);
}
