/******************************************************************\
*  map.c -- Tommy game map/level source code                       *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "gamedefs.h"
/******************************************************************/
void load_level()
{
   register int i;

   tile_orgx = 0;         /* initialize global level variables */
   tile_orgy = 0;
   screen_orgx = 0;
   screen_orgy = 0;
   vpo = 0;
   hpo = 240;
   vpb = vpo+239;
   hpb = hpo+239;
   visual = 0;
   hidden = 1;
   tpo = 480;

   /* display the foreground tiles */
   fg_move(0,tpo);
   fg_showpcx(foreground_fname,2);

   /* re-organize the foreground tiles to conserve video memory */
   fg_transfer(0,31,480,591,320,591,0,0);
   fg_transfer(32,63,480,591,320,703,0,0);

   /* display the background tiles */
   fg_move(0,480);
   fg_showpcx(background_fname,2);

   /* fix the foreground palettes */
   fix_palettes();

   /* load the level information */
   if ((level_stream = fopen(level_fname,"rb")) == NULL)
   {
      sprintf(abort_string,"%s not found",level_fname);
      terminate_game();
   }

   /* get the rows and columns */
   fread(&ncols,sizeof(int),1,level_stream);
   fread(&nrows,sizeof(int),1,level_stream);

   /* load the background tiles */
   for (i = 0; i < ncols; i++)
      fread(&background_tile[i][0],sizeof(char),nrows,level_stream);

   /* load the foreground tiles */
   for (i = 0; i < ncols; i++)
      fread(&foreground_tile[i][0],sizeof(char),nrows,level_stream);
   fclose(level_stream);

   /* load the background tile attributes */
   if ((level_stream = fopen(backattr_fname,"rb")) == NULL)
   {
      sprintf(abort_string,"%s not found",backattr_fname);
      terminate_game();
   }
   fread(background_attributes,sizeof(char),240,level_stream);
   fclose(level_stream);

   /* calculate the maximum tile origin */
   world_maxx = (ncols - 20) * 16;
   world_maxy = (nrows - 12) * 16 - 8;
}
/******************************************************************/
void page_copy(int ymin)
{
   /* copy both the video memory and the layout array */

   if (ymin == vpo)         /* visual to hidden */
   {
      fg_transfer(0,351,vpo,vpb,0,hpb,0,0);
      memcpy(layout[hidden],layout[visual],22*15);
   }
   else                    /* hidden to visual */
   {
      fg_transfer(0,351,hpo,hpb,0,vpb,0,0);
      memcpy(layout[visual],layout[hidden],22*15);
   }
}
/******************************************************************/
void page_fix()
{
   /* if the scrolling flags were set, do the video blits and
      update the layout array */

   register int i;

   if (warped)            /* warped -- just replace all the tiles */
   {
      warp(world_x,world_y);
      return;
   }
   else if (scrolled_left && scrolled_up)    /* diagonal scrolls */
   {
      fg_transfer(0,335,vpo,223+vpo,16,hpb,0,0);
      for(i = 0; i< 15; i++)
      {
         put_tile(0,i);
         put_foreground_tile(0,i);
      }
      for(i = 0; i< 22; i++)
      {
         put_tile(i,0);
         put_foreground_tile(i,0);
      }
      for (i = 0; i < 21; i++)
         memcpy(&layout[hidden][i+1][1],layout[visual][i],14);
   }
   else if (scrolled_left && scrolled_down)
   {
      fg_transfer(0,335,16+vpo,vpb,16,223+hpb,0,0);
      for(i = 0; i< 15; i++)
      {
         put_tile(0,i);
         put_foreground_tile(0,i);
      }
      for(i = 0; i< 22; i++)
      {
         put_tile(i,14);
         put_foreground_tile(i,14);
      }
      for (i = 0; i < 21; i++)
         memcpy(layout[hidden][i+1],&layout[visual][i][1],14);
   }
   else if (scrolled_right && scrolled_up)
   {
      fg_transfer(16,351,vpo,223+vpo,0,hpb,0,0);
      for(i = 0; i< 15; i++)
      {
         put_tile(21,i);
         put_foreground_tile(21,i);
      }
      for(i = 0; i< 22; i++)
      {
         put_tile(i,0);
         put_foreground_tile(i,0);
      }

      for (i = 0; i < 21; i++)
         memcpy(&layout[hidden][i][1],layout[visual][i+1],14);
   }
   else if (scrolled_right && scrolled_down)
   {
      fg_transfer(16,351,16+vpo,vpb,0,223+hpo,0,0);
      for(i = 0; i< 15; i++)
      {
         put_tile(21,i);
         put_foreground_tile(21,i);
      }
      for(i = 0; i< 22; i++)
      {
         put_tile(i,14);
         put_foreground_tile(i,14);
      }

      for (i = 0; i < 21; i++)
         memcpy(layout[hidden][i],&layout[visual][i+1][1],14);
   }
   else if (scrolled_left)               /* horizontal scrolls */
   {
      fg_transfer(0,335,vpo,vpb,16,hpb,0,0);
      for(i = 0; i< 15; i++)
      {
         put_tile(0,i);
         put_foreground_tile(0,i);
      }
      for (i = 0; i < 21; i++)
         memcpy(layout[hidden][i+1],layout[visual][i],15);
   }
   else if (scrolled_right)
   {
      fg_transfer(16,351,vpo,vpb,0,hpb,0,0);
      for(i = 0; i< 15; i++)
      {
         put_tile(21,i);
         put_foreground_tile(21,i);
      }
      for (i = 0; i < 21; i++)
         memcpy(layout[hidden][i],layout[visual][i+1],15);
   }
   else if (scrolled_up)                /* vertical scrolls */
   {
      fg_transfer(0,351,vpo,223+vpo,0,hpb,0,0);
      for(i = 0; i< 22; i++)
      {
         put_tile(i,0);
         put_foreground_tile(i,0);
      }
      for (i = 0; i < 22; i++)
         memcpy(&layout[hidden][i][1],layout[visual][i],14);
   }
   else if (scrolled_down)
   {
      fg_transfer(0,351,16+vpo,vpb,0,223+hpo,0,0);
      for(i = 0; i< 22; i++)
      {
         put_tile(i,14);
         put_foreground_tile(i,14);
      }
      for (i = 0; i < 22; i++)
         memcpy(layout[hidden][i],&layout[visual][i][1],14);
   }
}
/******************************************************************/
void put_foreground_tile(int xtile,int ytile)
{
   int tile_num;
   int x,y;
   int x1,x2,y1,y2;

   /* get the tile number */
   tile_num = (int)foreground_tile[xtile+tile_orgx][ytile+tile_orgy];

   /* 28 or greater == no foreground tile here */
   if (tile_num <= 27)
   {

      /* calculate the source and destination coordinates */
      y1 = (tile_num/2)*16+480;
      y2 = y1+15;
      x1 = 320+tile_num%2 * 16;
      x2 = x1 + 15;
      x = xtile*16;
      y = ytile*16+15;

      /* transfer the foreground tile (transparent video-video blit) */
      fg_tcxfer(x1,x2,y1,y2,x,y+hpo,0,0);
   }
}
/******************************************************************/
void put_tile(int xtile,int ytile)
{
   int tile_num;
   int x,y;
   int x1,x2,y1,y2;

   /* get the tile number from the background array */
   tile_num = (int)background_tile[xtile+tile_orgx][ytile+tile_orgy];

   /* calculate source and destination coordinates */
   x1 = (tile_num%20)*16;
   x2 = x1+15;
   y1 = (tile_num/20)*16 + tpo;
   y2 = y1+15;
   x = xtile*16;
   y = ytile*16+15;

   /* transfer the tile */
   fg_transfer(x1,x2,y1,y2,x,y+hpo,0,0);
}
/******************************************************************/
void rebuild_background()
{
   /* put all the necessary background tiles on the hidden page */
   register int i,j;

   for (i = 0; i < 22; i++)
   {
      for (j = 0; j < 15; j++)
      {
         /* check and make sure you need a tile there */
         if (layout[hidden][i][j])
            put_tile(i,j);
      }
   }
}
/******************************************************************/
void rebuild_foreground()
{
   /* put all the necessary foreground tiles on the hidden page */
   register int i,j;

   for (i = 0; i < 22; i++)
   {
      for (j = 0; j < 15; j++)
      {
         /* check and make sure you need a tile there */
         if (layout[hidden][i][j])
            put_foreground_tile(i,j);
      }
   }
}
/******************************************************************/
int scroll_down(int npixels)
{
   /* scroll more than one column, just redraw the whole screen */
   if (npixels >= 16)
   {
      world_y = tile_orgy*16 + screen_orgy;
      world_y = MIN(world_maxy,world_y+npixels);
      world_x = tile_orgx*16 + screen_orgx;
      warped = TRUE;
   }

   /* less than one column, no need to draw new tiles */
   else if (screen_orgy <= 40-npixels)
   {
      screen_orgy+=npixels;
   }

   /* need to scroll one row down */
   else if (tile_orgy < nrows - 15)
   {
      tile_orgy++;
      screen_orgy-=(16-npixels);
      scrolled_down = TRUE;
   }
   else /* can't scroll down */
   {
      return(ERR);
   }
   return(OK);
}
/******************************************************************/
int scroll_left(int npixels)
{
   /* scroll more than one column, just redraw the whole screen */
   if (npixels > 16)
   {
      world_x = tile_orgx*16 + screen_orgx;
      world_x = MAX(0,world_x-npixels);
      world_y = tile_orgy*16 + screen_orgy;
      warped = TRUE;
   }

   /* less than one column, no need to draw new tiles */
   else if (screen_orgx >= npixels)
   {
      screen_orgx-= npixels;
   }

   /* need to scroll one column to the left */
   else if (tile_orgx > 0)
   {
      tile_orgx--;
      screen_orgx+=(16-npixels);
      scrolled_left = TRUE;
   }

   /* can't scroll left */
   else
      return(ERR);

   return(OK);
}
/******************************************************************/
int scroll_right(int npixels)
{
   /* scroll more than one column, just redraw the whole screen */
   if (npixels > 16)
   {
      world_x = tile_orgx*16 + screen_orgx;
      world_x = MIN(world_maxx,world_x+npixels);
      world_y = tile_orgy*16 + screen_orgy;
      warped = TRUE;
   }

   /* less than one column, no need to draw new tiles */
   else if (screen_orgx <= 32-npixels)
   {
      screen_orgx+=npixels;
   }

   /* need to scroll one column to the right */
   else if (tile_orgx < ncols - 22)
   {
      tile_orgx++;
      screen_orgx-=(16-npixels);
      scrolled_right = TRUE;
   }
   else /* can't scroll right */
   {
      return(ERR);
   }
   return(OK);
}
/******************************************************************/
int scroll_up(int npixels)
{
   /* scroll more than one column, just redraw the whole screen */
   if (npixels >= 16)
   {
      world_y = tile_orgy*16 + screen_orgy;
      world_y = MAX(0,world_y-npixels);
      world_x = tile_orgx*16 + screen_orgx;
      warped = TRUE;
   }

   /* less than one column, no need to draw new tiles */
   else if (screen_orgy >= npixels)
   {
      screen_orgy-=npixels;
   }

   /* need to scroll one row up */
   else if (tile_orgy > 0)
   {
      tile_orgy--;
      screen_orgy+=(16-npixels);
      scrolled_up = TRUE;
   }
   else /* can't scroll up */
   {
      return(ERR);
   }
   return(OK);
}
/******************************************************************/
void swap()
{
   /* vpo = visual page offset, vpb = visual page bottom */
   /* hpo = hidden page offset, vpb = hidden page bottom */

   vpo = 240 - vpo;  /* toggle between 0 and 240 */
   hpo = 240 - hpo;

   vpb = vpo+239;
   hpb = hpo+239;

   /* toggle hidden and visual page */
   visual = !visual;
   hidden = !hidden;

   /* pan to the new visual page */
   fg_pan(screen_orgx,screen_orgy+vpo);
}
/******************************************************************/
void warp(int x,int y)
{
   register int i,j;

   if (x < 16)                 /* calculate the tile X origin */
   {
      tile_orgx = 0;
      screen_orgx = x;
   }
   else if (x >= world_maxx)
   {
      x = world_maxx;
      tile_orgx = x/16-2;
      screen_orgx = 32;
   }
   else
   {
      tile_orgx = x/16 - 1;
      screen_orgx = x%16 + 16;
   }

   if (y < 16)                 /* calculate the tile Y origin */
   {
      tile_orgy = 0;
      screen_orgy = y;
   }
   else if (y >= world_maxy)
   {
      y = world_maxy;
      tile_orgy = y/16-2;
      screen_orgy = 40;
   }
   else
   {
      tile_orgy = y/16 - 1;
      screen_orgy = y%16 + 16;
   }

   for (i = 0; i < 22; i++)    /* draw all the tiles */
   {
      for (j = 0; j < 15; j++)
      {
         put_tile(i,j);
         put_foreground_tile(i,j);
      }
   }
   /* update the layout array */
   memset(layout[hidden],0,15*22);
}
