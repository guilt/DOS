/******************************************************************\
*                                                                  *
*  Char.c -- Source code for displaying text, used in Fastgraph    *
*  Game Editor                                                     *
*                                                                  *
*  copyright 1994 Diana Gruber                                     *
*                                                                  *
*  compile using large model, link with Fastgraph (tm)             *
*                                                                  *
\******************************************************************/

#include "paldefs.h"

/* the 5x5 characters are stored in RAM as bitmaps. For convenience,
   they are put in a header file and compiled into the exe. Font5.h
   is the header file containing the font data. */

#include "font5.h"
   
/******************************************************************/

void center_string(char *string,int x1,int x2,int y)
{
   /* center a string between x1 and x2 */

   register int nchar,x;

   nchar = strlen(string);
   x = ((x1 + x2) / 2) - nchar*3;
   put_string(string,x,y);
}
   
/******************************************************************/

void erase_char(int x,int y)
{
   /* erase a character (when doing character input) */

   register int color;

   color = fg_getcolor();
   fg_setcolor(0);
   fg_rect(x,x+5,y-5,y);
   fg_setcolor(color);
}

/**********************************************************************/

get_center(char *string,int x1,int x2)
{
   return(((x1 + x2) / 2) - strlen(string)*3);
}

/******************************************************************/

void put_char(unsigned char key,int x,int y)
{
   /* just put one character */

   int index;

   index = (char)(key-33) * 5;

   fg_move(x,y);
   fg_drawmap(&font5[index],1,5);
}

/******************************************************************/

void put_cursor(int x,int y,int cursor_color)
{
   /* the text cursor is just a little rectangle */

   register int color;

   color = fg_getcolor();
   fg_setcolor(cursor_color);
   fg_rect(x,x+5,y,y);
   fg_setcolor(color);
}

/******************************************************************/

get_string(char *string,int x,int y,int max_length,
          unsigned char key,unsigned char aux)
{
   /* input a field (as in file names) where special characters
      are allowed, such as arrow keys to get to the next 
      field, etc. */

   register int i;
   int color;
   int cursor_timer;
   int foreground;
   int background;
   int xmax, ymin;
   int first;
   
   first = TRUE;

   foreground = fg_getcolor();
   background = 0;

   xmax = x + 6*max_length;
   ymin = y - 6;

   i = 0;
   cursor_timer = 16;
   color = foreground;
   fg_setcolor(foreground);

   for (;;)
   {
      cursor_timer--;
      if (cursor_timer == 8)
         color = background;
      else if (cursor_timer == 0)
      {
         cursor_timer = 16;
         color = foreground;
      }
      if (i < max_length) put_cursor(x,y+1,color);
      if (key+aux > 0)
         if (i < max_length) put_cursor(x,y+1,background);

      if (i == 0 && islower(key)) key ^= 32;

      /* printable character or space bar */
      if ((isalnum(key) || key == SPACE || ispunct(key)) && i < max_length)
      {
         if (first)
         {
            string[i] = '\0';
            fg_setcolor(background);
            fg_rect(x-2,xmax+1,ymin,y+1);
            first = FALSE;
            fg_setcolor(foreground);
         }

         put_cursor(x,y+1,background);
         if (!(key == SPACE)) put_char(key,x,y);
         x += 6;
         string[i++] = key;
         string[i] = '\0';
      }

      /* backspace deletes previous character */
      else if (key == BS && i > 0)
      {
         if (i < max_length) put_cursor(x,y+1,background);
         x -= 6;
         erase_char(x,y);
         i--;
         string[i] = '\0';
      }

      /* done entering string */
      else if (key == ESC || key == ENTER || key == TAB || aux > 0)
      {
         if (i < max_length) put_cursor(x,y+1,background);
         return(key+aux);
      }

      fg_waitfor(1);
      fg_intkey(&key,&aux);
   }
}

/******************************************************************/

void put_string(unsigned char *string,int ix,int iy)
{
   /* draw the letters one at a time as bitmaps. This is neither the
      fastest nor the most convenient way to display a font, but it
      is "RAM efficient". Character strings aren't used much in this
      program, so we choose this primitive font technique. */

   register int i;
   int index, nchar;
   char ch;
   
   nchar = strlen(string);

   for (i = 0; i < nchar; i++)
   {
      ch = (char)(string[i]-33);
      if (ch >= 0)
      {
         index = ch*5;

         /* move to the x,y location */
         fg_move(ix,iy);

         /* display one letter */
         fg_drawmap(&font5[index],1,5);
      }
      ix += 6;
   }
}



