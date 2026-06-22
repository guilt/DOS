/******************************************************************\
*  ripper.c -- game editor source code                             *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "editdefs.h"
/******************************************************************/
int do_ripper()
{
   register int i,j;
   int y;
   char string[13];
   int current;

   static char *string1[] = {
      "      Fastgraph tile ripper",
      " ",
      "PCX in file name:",
      "PCX out file name:",
      "Level file name:",
      " ",
      "      Press F10 to start"
   };

   static char *string2[] = {
      ripper_inpcx,
      ripper_outpcx,
      ripper_outlvl
   };

   static int y1[] = {90,100,110};

   /* initialize some globals */
   tile_index = 0;
   col = 0;
   ncols = 0;
   nrows = 12;

   /* set all the tiles in the level map to 255 */
   for (i = 0; i< MAXCOLS; i++)
   {
      for (j = 0; j < MAXROWS; j++)
      {
         level_map[i][j] = 255;
         foreground_map[i][j] = 255;
      }
   }

   fg_setpage(3);
   fg_erase();
   fg_setpage(0);

   for(;;)
   {
      fg_mousevis(OFF);
      fg_setcolor(blue);
      fg_rect(0,319,25,199);

      fg_setcolor(black);
      fg_rect(0,319,24,24);

      /* draw the dialog box */
      fg_setcolor(white);
      fg_rect(32,288,55,145);
      fg_setcolor(black);
      fg_box(32,288,55,145);

      y = 70;
      for (i = 0; i < 7; i++)
      {
         put_string(string1[i],60,y);
         y+= 10;
      }

      for (i = 0; i < 3; i++)
         put_string(string2[i],180,y1[i]);

      current = 0;
      for(;;)
      {
         strcpy(string,string2[current]);
         fg_setcolor(blue);
         j = get_string(string,180,y1[current],12,0,0);

         if (j == ESC)
         {
            /* write the level data and tiles out to disk */
            write_level();
            fg_setpage(0);
            fg_setcolor(blue);
            fg_rect(0,319,25,199);
            redraw = TRUE;
            return(OK);
         }
         if (j == UP_ARROW || j == DOWN_ARROW || j == ENTER)
         {
            check_ripper_suffixes(string,current);
            strcpy(string2[current],string);
            fg_setcolor(white);
            fg_rect(180,287,y1[current]-9,y1[current]);
            fg_setcolor(black);
            put_string(string2[current],180,y1[current]);
         }
         if (j == DOWN_ARROW)
         {
            current++;
            if (current > 2)
               current = 0;
         }
         else if (j == UP_ARROW)
         {
            current--;
            if (current < 0)
               current = 2;
         }
         else if (j == F10)
         {
            check_ripper_suffixes(string,current);
            strcpy(string2[current],string);
            fg_setcolor(white);
            fg_rect(180,287,y1[current]-9,y1[current]);
            fg_setcolor(black);
            put_string(string2[current],180,y1[current]);
            break;
         }
      }

      if (!file_exists(ripper_inpcx))
      {
         fg_setcolor(white);
         fg_rect(33,287,56,144);
         fg_setcolor(black);
         center_string("file not found",33,287,100);
         fg_waitkey();
         fg_setcolor(blue);
         fg_rect(0,319,25,199);
         redraw = TRUE;
         return(OK);
      }

      fg_showpcx(ripper_inpcx,0);
      fix_palettes(1);

      ripit();
      ncols = col;

      fg_setpage(0);
      fg_setvpage(0);

      fg_setcolor(blue);
      fg_rect(0,319,25,199);
      draw_screen();
   }
}
/******************************************************************/
int ripit()
{
   register int i,n;
   char new_tile[TILESIZE];
   int x,y,x1,y1;

   row = 0;

   /* if you already have a full screen tiles, return an error */
   if (tile_index >= TILELIMIT)
      return(ERR);

   /* loop on the pcx file, starting at upper left corner, moving
      down the columns in sequence */

   for (n = 0; n < TILELIMIT; n++)
   {
      x = (n/12)*16;
      y = (n%12)*16 + 15;

      /* get the new tile bitmap */
      fg_move(x,y);
      fg_getimage(new_tile,16,16);

      /* compare the new tile to all the ripper tiles */
      for (i = 0; i < tile_index; i++)
      {
         if (memcmp(new_tile,ripper_tiles[i],TILESIZE) == 0)
         {
            /* a duplicate tile is found, update the level map */
            level_map[col][row] = (unsigned char)i;

            /* black out the duplicate tile */
            fg_setcolor(0);
            fg_rect(x,x+15,y-15,y);
            break;
         }
      }

      /* no match was found, therefore the tile must be unique */
      if (level_map[col][row] == 255)
      {
         /* copy the new tile to the hidden page */
         x1 = (tile_index%20)*16;
         y1 = (tile_index/20)*16 + 23;
         fg_transfer(x,x+15,y-15,y,x1,y1,0,3);

         /* build the level map with the tile index */
         level_map[col][row] = (unsigned char)tile_index;

         /* hold the array in RAM for later comparisons */
         memcpy(ripper_tiles[tile_index],new_tile,TILESIZE);

         /* we can't have more than 240 unique tiles */
         tile_index++;
         if (tile_index >= TILELIMIT)
            break;
      }
      row++;
      if (row >= 12)
      {
         row = 0;
         col++;
      }
   }
   return(OK);
}
/******************************************************************/
check_ripper_suffixes(char *fname, int file_type)
{
   char *strptr;
   int index;
   int error;

   error = FALSE;
   strptr = strchr(fname,'.');

   /* period in string */
   if (strptr > 0)
   {
      index = (int)(strptr - fname);
      if (index > 8)
      error = TRUE;
   }

   /* no period in string */
   else
   {
      index = strlen(fname);
      if (index > 8)
         error = TRUE;
      else
         fname[index] = '.';
   }
   if (error) return(ERR);

   fname[index+1] = '\0';
   if (file_type == 0 || file_type == 1)
      strcat(fname,"pcx");
   else
      strcat(fname,"lev");
   return(OK);
}
/******************************************************************/
void write_level(void)
{
   register int i,j;
   unsigned char buffer[12];

   /* make a pcx file out of the tile page */
   fg_setpage(3);
   fg_makepcx(0,319,8,199,ripper_outpcx);

   /* open a binary file for the level array */
   stream = fopen(ripper_outlvl,"wb");

   fwrite(&ncols,sizeof(int),1,stream);
   fwrite(&nrows,sizeof(int),1,stream);

   /* write out all the columns, 12 tiles per column */
   j = 0;
   for (i = 0; i < ncols; i++)
   {
      fwrite(&level_map[i][0],sizeof(char),12,stream);
   }

   /* foreground tiles */
   for (j = 0; j < 12; j++)
      buffer[j] = 255;
   for (i = 0; i < ncols; i++)
      fwrite(buffer,sizeof(char),12,stream);

   fclose(stream);

   strcpy(level_fname,ripper_outlvl);
   strcpy(background_fname,ripper_outpcx);
}
