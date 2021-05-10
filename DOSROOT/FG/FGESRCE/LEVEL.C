/******************************************************************\
*  level.c -- game editor source code                              *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "editdefs.h"
/******************************************************************/
edit_level()
{
   int count;

   fg_mousevis(OFF);
   fg_setpage(0);
   fg_setcolor(white);
   fg_rect(48,272,95,107);
   fg_setcolor(black);
   fg_box(48,272,95,107);
   center_string("resizing video memory, please wait",48,272,103);

   /* write out the background tiles to temp files */
   fg_setpage(3);
   fg_makepcx(0,319,8,199,"game.01$");
   fg_setpage(2);
   fg_makepcx(0,63,8,119,"game.02$");

   /* resize the page to bigger size for level scrolling */
   fg_mousevis(OFF);
   fg_setpage(0);
   fg_erase();
   fg_setvpage(0);
   fg_mousefin();
   fg_setmode(20);
   fg_resize(352,744);

   fg_sethpage(0);
   init_mouse();
   fg_mousevis(OFF);

   fg_tcmask(1);
   load_level();

   /* do the level editing tasks */
   activate_level_editor();

   /* return screen to default size and re-init Fastgraph */
   fg_mousefin();
   fg_setmode(20);
   init_mouse();
   draw_screen();

   /* restore the background and foreground tiles */
   fg_setpage(3);
   fg_move(0,8);
   fg_showpcx("game.01$",0);
   fg_setpage(2);
   fg_move(0,8);
   fg_showpcx("game.02$",0);
   fix_palettes(0);
   fg_setpage(0);

   /* clear the mouse buttons and return to the main menu */
   fg_mousebut(1,&count,&xmouse,&ymouse);
   fg_mousebut(2,&count,&xmouse,&ymouse);
   return(OK);
}
/******************************************************************/
void activate_level_editor()
{
   register int i,j;
   int k,l;
   int xbox,ybox;
   int x,y;
   int oldx,oldy;
   unsigned char key,aux;
   int cursor_flag;
   int changed;
   int tile;

   fg_waitfor(3);

   /* put the mouse where it was the last time we were editing */
   fg_mousemov(level_xmouse,level_ymouse);
   fg_mousepos(&xmouse,&ymouse,&buttons);

   /* normalize the x and y coordinates to a tile boundary */
   xbox = xmouse&0xfff0;
   ybox = ymouse&0xfff0;

   /* update oldx and oldy */
   oldx = xbox;
   oldy = ybox;

   /* draw the cursor box */
   fg_setcolor(white);
   fg_boxx(xbox,xbox+15,ybox, ybox+15);
   cursor_flag = ON;

   /* initialize the undo information */
   update_level_undo();
   changed = FALSE;

   /* loop continuously */
   for(;;)
   {
      fg_intkey(&key,&aux);

      /* no key press detected, take care of mouse functions */
      if (key+aux == 0)
      {
         /* get the current mouse position */
         fg_mousepos(&xmouse,&ymouse,&buttons);

         /* normalize for tile space (divide by 16) */
         xbox = xmouse&0xfff0;
         ybox = ymouse&0xfff0;

         /* mouse has moved to a new tile position */
         if (xbox != oldx || ybox != oldy)
         {
            fg_setcolor(white);

            /* xor the old cursor box to get rid of it */
            if (cursor_flag)
               fg_boxx(oldx,oldx+15,oldy,oldy+15);

            /* draw cursor box at new position */
            fg_boxx(xbox,xbox+15,ybox,ybox+15);
            cursor_flag = ON;

            oldx = xbox;
            oldy = ybox;
         }

         /* if the mouse cursor is off, turn it on */
         else if (!cursor_flag)
         {
            fg_setcolor(white);
            fg_boxx(xbox,xbox+15,ybox,ybox+15);
            cursor_flag = ON;
         }

         /* the left mouse button puts down a block of tiles */
         if (buttons == 1)
         {
            if (!changed)
            {
               update_level_undo();
               changed = TRUE;
            }

            /* first turn off the mouse cursor */
            fg_setcolor(white);
            fg_boxx(xbox,xbox+15,ybox,ybox+15);

            /* set the cursor flag */
            cursor_flag = OFF;

            i = xbox/16;
            j = (ybox-vpo)/16;
            for (k = 0; k < block_rows; k++)
            {
               for (l = 0; l < block_cols; l++)
               {
                  if (i > 21)
                     break;
                  if (tile_type == BACKGROUND)
                     level_map[i+tile_orgx][j+tile_orgy] = block[l][k];
                  else
                     foreground_map[i+tile_orgx][j+tile_orgy] = block[l][k];
                  put_tile(i,j,visual);
                  put_foreground_tile(i,j,visual);
                  i++;
               }
               i = xbox/16;
               j++;
               if (j > 14) break;
            }
         }

         /* right button picks up a tile */
         else if (buttons == 2)
         {
            fg_setcolor(white);
            if (cursor_flag)
               fg_boxx(xbox,xbox+15,ybox,ybox+15);
            cursor_flag = OFF;
            get_block();
         }
         else if (changed && buttons == 0)
         {
            changed = FALSE;
         }
      }
      else
      {
         if (isupper(key))
            key+=32;

         flushkey();
         if (cursor_flag)
         {
            fg_setcolor(white);
            fg_boxx(xbox,xbox+15,ybox,ybox+15);
            cursor_flag = OFF;
         }
         if (key == ESC)
         {
            level_xmouse = xmouse;
            level_ymouse = ymouse;
            return;
         }

         /* delete foreground block */
         else if (key == 'd')
         {
            i = xbox/16;
            j = (ybox-vpo)/16;
            foreground_map[i+tile_orgx][j+tile_orgy] = 255;
            put_tile(i,j,visual);
         }

         /* show foreground blocks */
         else if (key == 'f')
         {
            fg_setcolor(0);
            for (i = 0; i < 22; i++)
            {
               for (j = 0; j < 15; j++)
               {
                  if (foreground_map[i+tile_orgx][j+tile_orgy] < 28)
                  {
                     x = i*16; y = j*16+vpo;
                     fg_rect(x,x+15,y,y+15);
                  }
               }
            }
            fg_waitkey();

            for (i = 0; i < 22; i++)
            {
               for (j = 0; j < 15; j++)
               {
                  put_tile(i,j,visual);
                  put_foreground_tile(i,j,visual);
               }
            }

         }

         /* show background blocks */
         else if (key == 'k')
         {
            for (i = 0; i < 22; i++)
            {
               for (j = 0; j < 15; j++)
               {
                  put_tile(i,j,visual);
               }
            }
            fg_waitkey();

            for (i = 0; i < 22; i++)
            {
               for (j = 0; j < 15; j++)
               {
                  put_foreground_tile(i,j,visual);
               }
            }

         }

         /* show attributes */
         else if (key == 'a')
         {
            fg_setcolor(white);
            for (i = 0; i < 22; i++)
            {
               for (j = 0; j < 15; j++)
               {
                  tile = level_map[i+tile_orgx][j+tile_orgy];
                  if (test_bit(tile,0))
                     put_char('t',i*16,j*16+7+vpo);
                  if (test_bit(tile,1))
                     put_char('b',i*16+8,j*16+7+vpo);
                  if (test_bit(tile,2))
                     put_char('l',i*16,j*16+15+vpo);
                  if (test_bit(tile,3))
                     put_char('r',i*16+8,j*16+15+vpo);
               }
            }
            fg_waitkey();

            for (i = 0; i < 22; i++)
            {
               for (j = 0; j < 15; j++)
               {
                  put_tile(i,j,visual);
                  put_foreground_tile(i,j,visual);
               }
            }
         }
         else if (aux == LEFT_ARROW)
            scroll_left(16);
         else if (aux == RIGHT_ARROW)
            scroll_right(16);
         else if (aux == UP_ARROW)
            scroll_up(16);
         else if (aux == DOWN_ARROW)
            scroll_down(16);
         else if (aux == CTRL_RIGHT_ARROW)
            page_right();
         else if (aux == PGUP)
            page_up();
         else if (aux == CTRL_LEFT_ARROW)
            page_left();
         else if (aux == PGDN)
            page_down();
         else if (key == SPACE)
            get_a_tile();
         else if (aux == INSERT)
            insert_tiles();
         else if (key == 'u')
            undo_level();
         else if (key == 't')
            set_top();
         else if (key == 'b')
            set_bottom();
         else if (key == 'l')
            set_left();
         else if (key == 'r')
            set_right();
         else if (key == 'c')
            clear_tile_attributes();
         else if (aux == DELETE)
            delete_tiles();
         else if (aux == F1)
            level_help();
         else if (aux == F2)
            show_coords();
         else if (key == 's')
            save_level();
      }
   }
}
/******************************************************************/
void delete_tiles()
{
   register int i,j;
   unsigned char key,aux;
   int tile;
   char *string = "Delete Row or Column?";

   /* ask, do we want to delete a row or column? */
   popup_message(string);
   fg_getkey(&key,&aux);
   popdown();

   /* delete a column */
   if ((key|32) == 'c' && ncols > 22)
   {
      /* which column are we going to delete? */
      tile = tile_orgx + xmouse/16;

      /* shift all the tiles left by one column */
      for (j = 0; j < nrows; j++)
      {
         for (i = tile; i < ncols-1; i++)
         {
            level_map[i][j] = level_map[i+1][j];
            foreground_map[i][j] = foreground_map[i+1][j];
         }
      }

      /* set the last column to 0 */
      i = ncols-1;
      for (j = 0; j < nrows; j++)
      {
         level_map[i][j] = 0;
         foreground_map[i][j] = 0;
      }

      /* decrement the number of columns */
      ncols--;

      /* redraw the remaining columns, shifted left by one */
      tile = xmouse/16;
      for(i = tile; i< 22; i++)
      {
         for (j = 0; j < 15; j++)
         {
            put_tile(i,j,visual);
            put_foreground_tile(i,j,visual);
         }
      }

      /* update the undo information */
      update_level_undo();
   }

   /* delete a row -- note: key|32 handles upper and lower case */
   else if ((key|32) == 'r' && nrows > 15)
   {
      /* which row are we going to delete? */
      tile = tile_orgy + (ymouse-vpo)/16;

      /* shift all the tiles up by one row */
      for (j = tile; j < nrows-1; j++)
      {
         for (i = 0; i < ncols; i++)
         {
            level_map[i][j] = level_map[i][j+1];
            foreground_map[i][j] = foreground_map[i][j+1];
         }
      }

      /* set all the tiles in the last row to 0 */
      j = nrows-1;
      for (i = 0; i < ncols; i++)
      {
          level_map[i][j] = 0;
          foreground_map[i][j] = 0;
      }

      /* decrement the number of rows */
      nrows--;

      /* redraw the remaining rows, shifted up by one */
      tile = (ymouse-vpo)/16;
      for(i = 0; i< 22; i++)
      {
         for (j = tile; j < 15; j++)
         {
            put_tile(i,j,visual);
            put_foreground_tile(i,j,visual);
         }
      }

      /* update the undo information */
      update_level_undo();
   }
}
/******************************************************************/
void get_block()
{
   /* Use the right mouse button to get a block of tiles right off
      the level map. */

   register int i,j;
   int xbox,ybox;
   int oldx,oldy;
   int corner_x,corner_y;
   unsigned char key,aux;
   int row,col;
   unsigned char tile;

   /* We only pick up the background tiles this way */
   tile_type = BACKGROUND;

   /* get the current mouse position */
   fg_mousepos(&xmouse,&ymouse,&buttons);

   /* keep track of the level position */
   level_xmouse = xmouse;
   level_ymouse = ymouse;

   /* current row and column */
   col = tile_orgx + xmouse/16;
   row = tile_orgy + (ymouse-vpo)/16;

   /* first tile in block: upper left corrner is current tile */
   tile = level_map[col][row];
   block[0][0] = tile;

   /* limit mouse movement to down and right */
   xbox = xmouse&0xfff0;
   ybox = ymouse&0xfff0;

   corner_x = xbox;
   corner_y = ybox;

   xbox += 16;
   ybox += 16;
   fg_mouselim(xbox,mouse_limx2+16,ybox,mouse_limy2+vpo+16);

   /* draw an xor box to highlight the current tile */
   fg_boxx(corner_x,xbox,corner_y,ybox);

   /* add more tiles to block until button is released */
   oldx = xbox;
   oldy = ybox;
   for(;;)
   {
      fg_intkey(&key,&aux);
      if (key == ESC)
         break;

      fg_mousepos(&xmouse,&ymouse,&buttons);

      /* has the button been released? */
      if (buttons != 2)
         break;

      /* normalize the mouse position to tile boundaries */
      xbox = xmouse&0xfff0;
      ybox = ymouse&0xfff0;

      /* has the mouse moved? */
      if (xbox != oldx || ybox != oldy)
      {
         /* xor the old box to remove it */
         fg_boxx(corner_x,oldx,corner_y,oldy);

         /* draw the new xor box */
         fg_boxx(corner_x,xbox,corner_y,ybox);
         oldx = xbox;
         oldy = ybox;
      }
   }

   /* total number of tiles outlined by the xor box */
   block_cols = (xbox - corner_x)/16;
   block_rows = (ybox - corner_y)/16;

   /* fill the block with the tiles just highlighted */
   for (j = 0; j < block_rows; j++)
   {
     for (i = 0; i < block_cols; i++)
     {
        block[i][j] = level_map[col+i][row+j];
     }
   }

   /* draw the xor box again to make it go away*/
   fg_boxx(corner_x,oldx,corner_y,oldy);

   /* reset the mouse limits */
   fg_mouselim(mouse_limx1,mouse_limx2,mouse_limy1+vpo,mouse_limy2+vpo);

   /* put the mouse back where it was */
   fg_mousemov(level_xmouse,level_ymouse);
}
/******************************************************************/
void get_a_tile()
{
   /* get a single tile or block of tiles from the offscreen video
      memory */

   register int i,j;
   int xbox,ybox;
   int oldx,oldy;
   int count;
   unsigned char key,aux;
   int tile_num;
   int x1,x2,y1,y2;
   int err;

   /* wait a bit to allow for release of the mouse button */
   fg_waitfor(3);

   /* where is the mouse now? */
   fg_mousepos(&xmouse,&ymouse,&buttons);
   level_xmouse = xmouse;
   level_ymouse = ymouse;

   /* we start by picking up background tiles */
   tile_type = BACKGROUND;

   /* pan to the background tile area */
   fg_pan(0,tpo);

   /* set the mouse limits so only background tiles can be reached */
   fg_mouselim(0,319,tpo,tpo+176);

   /* move the mouse to where it was the last time we got a tile */
   xmouse = back_xmouse;
   ymouse = back_ymouse;
   fg_mousemov(xmouse,ymouse);

   /* normalize the mouse position to a tile boundary */
   xbox = xmouse&0xfff0;
   ybox = ymouse&0xfff0;
   oldx = xbox;
   oldy = ybox;

   /* draw an xor box to highlight the tile */
   fg_setcolor(white);
   fg_boxx(xbox,xbox+15,ybox, ybox+15);
   err = FALSE;

   for(;;)
   {
      /* intercept a key press, if any */
      fg_intkey(&key,&aux);

      /* Escape key abandons this function */
      if (key == ESC)
      {
         x1 = xbox;
         x2 = xbox + 15;
         y1 = ybox;
         y2 = ybox + 15;
         err = TRUE;
         break;
      }

      /* space bar toggles between background and foreground tiles */
      else if (key == SPACE)
      {
         /* currently looking at background files, change to foreground */
         if (tile_type == BACKGROUND)
         {
            tile_type = FOREGROUND;

            /* shift our view over so we can see the foreground tiles */
            fg_pan(32,tpo);

            /* change the mouse limits to foreground tile area */
            fg_mouselim(320,351,tpo,tpo+176);
            xmouse = 320;
            ymouse = 480;
            fg_mousemov(xmouse,ymouse);
         }

         /* currently looking at foreground tiles, change to background */
         else
         {
            tile_type = BACKGROUND;

            /* change view so all background tiles are visible */
            fg_pan(0,tpo);

            /* set mouse limits to access background tiles */
            fg_mouselim(0,319,tpo,tpo+176);
            xmouse = 0;
            ymouse = 480;
            fg_mousemov(xmouse,ymouse);
         }
      }

      /* get the mouse coordinates again */
      fg_mousepos(&xmouse,&ymouse,&buttons);

      xbox = xmouse&0xfff0;
      ybox = ymouse&0xfff0;

      /* has the mouse moved ? */
      if (xbox != oldx || ybox != oldy)
      {

         /* xor out the old box, draw a new box on the current tile */
         fg_setcolor(white);
         fg_boxx(oldx,oldx+15,oldy,oldy+15);
         fg_boxx(xbox,xbox+15,ybox,ybox+15);
         oldx = xbox;
         oldy = ybox;

         /* get the tile number of the background or foreground tile */
         if (tile_type == BACKGROUND)
            tile_num = ((ybox-tpo)/16) * 20 + (xbox/16);
         else
            tile_num = (ybox-480)/8 + (xbox-320)/16;
      }

      /* button_press: pick up one or more tiles */
      if (buttons == 2)
      {
         x1 = xbox;
         x2 = xbox + 15;
         y1 = ybox;
         y2 = ybox + 15;

         /* set the mouse limits: mouse can move right and down only */
         if (tile_type == BACKGROUND)
            fg_mouselim(x1,319,y1,tpo+176);
         else
            fg_mouselim(x1,351,y1,687);

         /* expand or contract the box as long as the button is held */
         while (buttons == 2)
         {
            /* xor the old box */
            fg_setcolor(white);
            fg_boxx(x1,x2,y1,y2);

            /* move the mouse */
            fg_mousepos(&xmouse,&ymouse,&buttons);

            /* xor the new box */
            x2 = (xmouse&0xfff0) + 15;
            y2 = (ymouse&0xfff0) + 15;
            fg_boxx(x1,x2,y1,y2);
         }

         /* we got our block, quit looping */
         break;
      }
   }

   /* clear the xor'd box */
   fg_setcolor(white);
   fg_boxx(x1,x2,y1,y2);

   if (!err)
   {
      /* calculate the number or rows and columns in the block */
      block_cols = ((x2+1) - x1)/16;
      block_rows = ((y2+1) - y1)/16;

      /* fill up the block with the tiles we just highlighted */
      for (j = 0; j < block_rows; j++)
      {
         for (i = 0; i < block_cols; i++)
         {
            if (tile_type == BACKGROUND)
               block[i][j] = (unsigned char)(tile_num+j*20+i);
            else
               block[i][j] = (unsigned char)(tile_num+j*2+i);
         }
      }
   }

   /* keep track of the mouse position for next time */
   if (tile_type == BACKGROUND)
   {
      back_xmouse = xbox;
      back_ymouse = ybox;
   }

   /* pan back to the level map area */
   fg_pan(screen_orgx,screen_orgy+vpo);

   /* reset the mouse limits and move the mouse to where it was */
   fg_mouselim(mouse_limx1,mouse_limx2,mouse_limy1+vpo,mouse_limy2+vpo);
   fg_mousemov(level_xmouse,level_ymouse);

   /* give us time to get our finger off the button */
   fg_waitfor(3);
   fg_mousebut(1,&count,&xmouse,&ymouse);
   fg_mousebut(2,&count,&xmouse,&ymouse);
   fg_waitfor(3);
}
/******************************************************************/
void insert_tiles()
{
   register int i,j;
   int tile;
   unsigned char key,aux;
   char *string = "Insert Row or Column?";

   /* ask, do we want to insert a row or column? */
   popup_message(string);
   fg_getkey(&key,&aux);
   popdown();

   /* insert a row (note: key|32 handles upper and lower case) */
   if ((key|32) == 'c' && ncols < MAXCOLS)
   {
      /* increment the number of columns */
      ncols++;

      /* what column are we on now? */
      tile = tile_orgx + xmouse/16;

      /* shift all the tiles right by one */
      for (j = 0; j < nrows; j++)
      {
         for (i = ncols-1; i > tile; i--)
         {
            level_map[i][j] = level_map[i-1][j];
            foreground_map[i][j] = foreground_map[i-1][j];
         }
      }

      /* draw the tiles, shifted right */
      tile = xmouse/16;
      for(i = tile; i< 22; i++)
      {
         for (j = 0; j < 15; j++)
         {
            put_tile(i,j,visual);
            put_foreground_tile(i,j,visual);
         }
      }

     /* update the undo information */
     update_level_undo();
   }

   /* insert a row */
   else if ((key|32) == 'r' && nrows < MAXROWS)
   {
      /* increment the number of rows */
      nrows++;

      /* what row are we currently on? */
      tile = tile_orgy + (ymouse-vpo)/16;

      /* move all the rows down by one */
      for (j = nrows-1; j > tile; j--)
      {
         for (i = 0; i < ncols; i++)
         {
            level_map[i][j] = level_map[i][j-1];
            foreground_map[i][j] = foreground_map[i][j-1];
         }
      }

      /* draw the rows, shifted down by one */
      tile = (ymouse-vpo)/16;
      for(i = 0; i< 22; i++)
      {
         for (j = tile; j < 15; j++)
         {
            put_tile(i,j,visual);
            put_foreground_tile(i,j,visual);
         }
      }

      /* update the undo information */
      update_level_undo();
   }
}
/******************************************************************/
void level_help()
{
   /* three help screens for displaying information about editing
      the level */

   register int i,j;
   unsigned char key,aux;
   int x1,x2,y1,y2;
   int xmin,ymin;
   int x,y;

   static char *string[] = {
      "F1    - Help",
      "F2    - Show coordinates",
      "U     - Undo",
      "S     - Save level",
      "Ins   - Insert row or column",
      "Del   - Delete row or column",
      "Space - Get a tile",
      "Esc   - Exit",
      "Use Arrows, Ctrl-arrows, PGUP",
      "and PGDN to move around.   More...",

      " A - show tile attributes",
      " T - solid on top",
      " B - solid on bottom",
      " L - solid on left",
      " R - solid on right",
      " C - clear tile attributes",
      " K - show background tiles",
      " F - show foreground tiles",
      " D - delete foreground tile",
      "                          More...",


      "Use the right mouse button to",
      "pick up blocks of tiles on the",
      "level map or the tile page.",
      "Press the space bar to get to",
      "the tile page. Foreground",
      "tiles are at the far right of the",
      "tile page. Press the space bar",
      "a second time to get to them.",
      " ",
      "* Level editor by Diana Gruber *"
   };

   fg_setfunc(0);
   xmin = screen_orgx&0xfff0;
   ymin = screen_orgy&0xfff0;

   x1 = xmin+48;
   x2 = x1 + 223;

   y1 = ymin + 32;
   y2 = y1 + 120;

   /* copy the visual page to the hidden page */
   fg_transfer(x1,x2,y1+vpo,y2+vpo,x1,y2+hpo,0,0);

   for (i = 0; i < 3; i++)
   {
      fg_setcolor(white);
      fg_rect(x1,x2,y1+vpo,y2+vpo);
      fg_setcolor(black);
      fg_box(x1,x2,y1+vpo,y2+vpo);

      x = x1+15;
      y = y1+16;

      for (j = i*10; j < (i+1)*10; j++)
      {
         put_string(string[j],x,y+vpo);
         y += 10;
      }
      fg_getkey(&key,&aux);
      if (key == ESC) break;
   }

   /* copy the hidden page back to the visual page */
   fg_transfer(x1,x2,y1+hpo,y2+hpo,x1,y2+vpo,0,0);
   fg_setfunc(3);
}
/******************************************************************/
void load_level()
{
   /* load level data from a file */

   register int i,j;

   /* initialize some globals */
   tile_orgx = 0;
   tile_orgy = 0;
   screen_orgx = 0;
   screen_orgy = 0;
   vpo = 0;
   hpo = 240;
   visual = 0;
   hidden = 1;
   back_xmouse = 0;
   back_ymouse = 480;
   tpo = 480;
   tile_type = BACKGROUND;

   /* set the mouse limits */
   mouse_limx1 = screen_orgx;
   mouse_limx2 = mouse_limx1+336;
   mouse_limy1 = screen_orgy;
   mouse_limy2 = mouse_limy1+192;
   fg_mouselim(mouse_limx1,mouse_limx2,mouse_limy1+vpo,mouse_limy2+vpo);

   /* display the temporary pcx files, foreground tiles first */
   fg_move(0,480);
   fg_showpcx("game.02$",2);

   /* move the foreground tiles over to the right */
   fg_transfer(0,31,480,591,320,591,0,0);
   fg_transfer(32,63,480,591,320,703,0,0);

   /* background tiles */
   fg_move(0,480);
   fg_showpcx("game.01$",2);

   /* fix the menu colors */
   fix_palettes(0);

   /* set the background tiles to 0 and foreground tiles to "unused" */
   for (i = 0; i< MAXCOLS; i++)
   {
      for (j = 0; j < MAXROWS; j++)
      {
         level_map[i][j] = 0;
         foreground_map[i][j] = 255;
      }
   }

   /* try to get the level data from a file */
   if ((tstream = fopen(level_fname,"rb")) != NULL)
   {
      fread(&ncols,sizeof(int),1,tstream);
      fread(&nrows,sizeof(int),1,tstream);

      for (i = 0; i < ncols; i++)
         fread(&level_map[i][0],sizeof(char),nrows,tstream);
      for (i = 0; i < ncols; i++)
         fread(&foreground_map[i][0],sizeof(char),nrows,tstream);

      fclose(tstream);
   }
   else
   {
      ncols = 22;
      nrows = 15;
   }

   /* display all the tiles */
   for (i = 0; i < 22; i++)
   {
      for (j = 0; j < 15; j++)
      {
         put_tile(i,j,visual);
         put_foreground_tile(i,j,visual);
      }
   }
}
/******************************************************************/
int page_left()
{
   /* ctrl-left arrow moves the screen left */

   register int i,j;

   /* can't move left */
   if (tile_orgx == 0 && screen_orgx == 0)
   {
      return(ERR);
   }
   /* move as far left as we can */
   else if (tile_orgx == 0 && screen_orgx < 16)
   {
      while(screen_orgx > 0)
         scroll_left(16);
   }
   /* move left 17 columns */
   else
   {
      tile_orgx = MAX(0,tile_orgx-17);
      screen_orgx = 0;

      for (i = 0; i < 22; i++)
      {
         for (j = 0; j < 15; j++)
         {
            put_tile(i,j,hidden);
            put_foreground_tile(i,j,visual);
         }
      }
      swap();
      set_mouse_limx();
   }
   return(OK);
}

/******************************************************************/

int page_right()
{
   register int i,j;
   int tile_xmax;

   tile_xmax = ncols - 22;

   /* can't move right */
   if (tile_orgx == tile_xmax && screen_orgx == 32)
   {
      return(ERR);
   }
   /* move right as far as we can */
   else if (tile_orgx == tile_xmax && screen_orgx < 32)
   {
      while(screen_orgx < 32)
         scroll_right(16);
   }
   /* move right 17 columns */
   else
   {
      tile_orgx = MIN(tile_xmax,tile_orgx+17);
      screen_orgx = 32;
      for (i = 0; i < 22; i++)
      {
         for (j = 0; j < 15; j++)
         {
            put_tile(i,j,hidden);
            put_foreground_tile(i,j,visual);
         }
      }
      swap();
      set_mouse_limx();
   }
   return(OK);
}
/******************************************************************/
int page_down()
{
   /* PGDN moves the screen down */
   register int i,j;
   int tile_ymax;

   tile_ymax = nrows - 15;

   /* can't move down */
   if (tile_orgy == tile_ymax && screen_orgy == 24)
   {
      return(ERR);
   }

   /* move down as far as we can */
   else if (tile_orgy == tile_ymax && screen_orgy < 24)
   {
      while(screen_orgy < 24)
         scroll_down(16);
   }

   /* move down 12 rows */
   else
   {
      tile_orgy = MIN(tile_ymax,tile_orgy+12);
      screen_orgy = 40;

      for (i = 0; i < 22; i++)
      {
         for (j = 0; j < 15; j++)
         {
            put_tile(i,j,hidden);
            put_foreground_tile(i,j,visual);
         }
      }

      swap();
      set_mouse_limy();
   }
   return(OK);
}
/******************************************************************/
int page_up()
{
   /* PGUP moves the screen up */

   register int i,j;

   /* can't move up */
   if (tile_orgy == 0 && screen_orgy == 0)
   {
      return(ERR);
   }
   /* move up as far as we can */
   else if (tile_orgy == 0 && screen_orgy < 16)
   {
      while(screen_orgy > 0)
      scroll_up(16);
   }
   /* move up 14 rows */
   else
   {
      tile_orgy = MAX(0,tile_orgy-14);
      screen_orgy = 0;

      for (i = 0; i < 22; i++)
      {
         for (j = 0; j < 15; j++)
         {
            put_tile(i,j,hidden);
            put_foreground_tile(i,j,visual);
         }
      }
      swap();
      set_mouse_limy();
   }
   return(OK);
}
/******************************************************************/
void popup_message(char *string)
{
   /* pop up a message in a information window */

   int xmin,ymin;
   int nchar;

   /* calculate the size and position of the window */
   nchar = strlen(string);
   xmin = screen_orgx&0xfff0;
   popup_x1 = xmin + (340 - nchar*6)/2 ;
   popup_x2 = popup_x1+nchar*6 + 10;

   ymin = screen_orgy&0xfff0;
   popup_y1 = ymin + 90;
   popup_y2 = popup_y1 + 12;

   /* save the tiles under the popup window */
   fg_transfer(popup_x1,popup_x2,popup_y1+vpo,popup_y2+vpo,
               popup_x1,popup_y2+hpo,0,0);
   fg_setcolor(white);

   /* draw the rectangles */
   fg_rect(popup_x1,popup_x2,popup_y1+vpo,popup_y2+vpo);
   fg_setcolor(black);
   fg_box(popup_x1,popup_x2,popup_y1+vpo,popup_y2+vpo);

   /* center the string in the window */
   center_string(string,popup_x1,popup_x2,popup_y2+vpo-4);
}
/******************************************************************/
void popdown()
{
   /* pop down the information window */
   fg_transfer(popup_x1,popup_x2,popup_y1+hpo,popup_y2+hpo,
               popup_x1,popup_y2+vpo,0,0);
}
/******************************************************************/
void put_tile(int xtile, int ytile, int page)
{
   int tile_num;
   int x,y;
   int x1,x2,y1,y2;

   /* get the tile information from the tile map */
   tile_num = (int)level_map[xtile+tile_orgx][ytile+tile_orgy];

   /* calculate the destination coordinates */
   x = xtile * 16;
   if (page == hidden)
      y = ytile * 16 + 15 + hpo;
   else
      y = ytile * 16 + 15 + vpo;

   /* calculate the source coordinates */
   x1 = (tile_num%20)*16;
   x2 = x1+15;
   y1 = (tile_num/20)*16 + tpo;
   y2 = y1+15;

   /* copy the tile */
   fg_transfer(x1,x2,y1,y2,x,y,0,0);
}
/******************************************************************/
void put_foreground_tile(int xtile,int ytile,int page)
{
   int tile_num;
   int x,y;
   int x1,x2,y1,y2;

   tile_num = (int)foreground_map[xtile+tile_orgx][ytile+tile_orgy];

   /* total of 28 valid foreground tiles (0-27) */
   if (tile_num <= 27)
   {
      /* calculate source coordinates */
      y1 = (tile_num/2)*16+480;
      y2 = y1+15;
      x1 = 320+tile_num%2 * 16;
      x2 = x1 + 15;

      /* calculate destination coordinates */
      x = xtile*16;
      y = ytile*16+15;

      /* transparent video-video blit */
      if (page == hidden)
         fg_tcxfer(x1,x2,y1,y2,x,y+hpo,0,0);
      else
         fg_tcxfer(x1,x2,y1,y2,x,y+vpo,0,0);
   }
}
/******************************************************************/
void save_level()
{
   /* save while editing level */

   register int i;
   char string[50];
   unsigned char key,aux;

   /* prompt for level name */
   sprintf(string,"save level: %s?",level_fname);
   popup_message(string);
   fg_getkey(&key,&aux);
   popdown();

   /* wrong answer -- skip it */
   if ((key|32) != 'y')
      return;

   /* open a file and write out the level information */
   if ((tstream = fopen(level_fname,"wb")) != NULL)
   {
      fwrite(&ncols,sizeof(int),1,tstream);
      fwrite(&nrows,sizeof(int),1,tstream);

      for (i = 0; i < ncols; i++)
         fwrite(&level_map[i][0],sizeof(char),nrows,tstream);

      for (i = 0; i < ncols; i++)
         fwrite(&foreground_map[i][0],sizeof(char),nrows,tstream);

      fclose(tstream);
   }

   /* also write the background attributes and foreground attributes */
   if ((tstream = fopen(backattr_fname,"wb")) != NULL)
   {
      fwrite(background_attributes,sizeof(char),240,tstream);
      fclose(tstream);
   }
   if ((tstream = fopen(foreattr_fname,"wb")) != NULL)
   {
      fwrite(foreground_attributes,sizeof(char),28,tstream);
      fclose(tstream);
   }
}
/******************************************************************/
int save_level_name()
{
   char fname[13];
   unsigned char key,aux;
   char *strptr;
   int index;
   int error;
   register int i;

   /* draw an information box */
   fg_mousevis(OFF);
   fg_setcolor(white);
   fg_rect(48,272,100,112);
   fg_setcolor(black);
   fg_box(48,272,100,112);

   /* display the default file name */
   put_string("Level file name:",72,108);
   put_string(level_fname,170,108);

   /* wait for a keystroke */
   fg_getkey(&key,&aux);
   if (key == CR)
      strcpy(fname,level_fname);

   /* get a new file name */
   else
   {
      if (get_string(fname,170,108,12,key,0) == ESC)
      {
         fg_setcolor(blue);
         fg_rect(48,272,100,112);
         return(0);
      }
   }
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
   strcat(fname,"lev");
   strcpy(level_fname,fname);

   /* clear the information window */
   fg_setcolor(blue);
   fg_rect(48,272,100,112);

   /* save the level data */
   if ((tstream = fopen(level_fname,"wb")) != NULL)
   {
      fwrite(&ncols,sizeof(int),1,tstream);
      fwrite(&nrows,sizeof(int),1,tstream);

      for (i = 0; i < ncols; i++)
         fwrite(&level_map[i][0],sizeof(char),nrows,tstream);

      for (i = 0; i < ncols; i++)
         fwrite(&foreground_map[i][0],sizeof(char),nrows,tstream);

      fclose(tstream);
   }
   if ((tstream = fopen(backattr_fname,"wb")) != NULL)
   {
      fwrite(background_attributes,sizeof(char),240,tstream);
      fclose(tstream);
   }
   return(0);
}
/******************************************************************/
int scroll_left(int npixels)
{
   register int i;

   /* no tiles need to be redrawn */
   if (screen_orgx >= npixels)
   {
      screen_orgx-= npixels;
      fg_pan(screen_orgx,screen_orgy+vpo);
   }
   /* redraw one column of tiles and do a page swap */
   else if (tile_orgx > 0)
   {
      tile_orgx--;
      screen_orgx+=(16-npixels);
      fg_transfer(0,335,vpo,vpo+239,16,hpo+239,0,0);
      swap();
      for(i = 0; i< 15; i++)
         put_tile(0,i,visual);
   }
   /* can't scroll left */
   else
      return(ERR);

   /* fix the mouse limits */
   set_mouse_limx();
   return(OK);
}
/******************************************************************/
int scroll_right(int npixels)
{
   register int i;

   /* no tiles need to be redrawn */
   if (screen_orgx <= 32-npixels)
   {
      screen_orgx+=npixels;
      fg_pan(screen_orgx,screen_orgy+vpo);
   }
   /* redraw one column of tiles and do a page swap */
   else if (tile_orgx < ncols - 22)
   {
      tile_orgx++;
      screen_orgx-=(16-npixels);
      fg_transfer(16,351,vpo,vpo+239,0,hpo+239,0,0);
      swap();
      for(i = 0; i< 15; i++)
         put_tile(21,i,visual);
   }
   /* can't scroll right */
   else
      return(ERR);

   /* set the mouse limits */
   set_mouse_limx();
   return(OK);
}
/******************************************************************/
int scroll_up(int npixels)
{
   register int i;

   /* no tiles need to be redrawn */
   if (screen_orgy >= npixels)
   {
      screen_orgy-=npixels;
      fg_pan(screen_orgx,screen_orgy+vpo);
   }

   /* redraw one row of tiles and do a page swap */
   else if (tile_orgy > 0)
   {
      tile_orgy--;
      screen_orgy+=(16-npixels);
      fg_transfer(0,351,vpo,223+vpo,0,hpo+239,0,0);
      swap();
      for(i = 0; i< 22; i++)
         put_tile(i,0,visual);
   }

   /* can't scroll up */
   else
      return(ERR);

   /* set the mouse limits */
   set_mouse_limy();
   return(OK);
}
/******************************************************************/
int scroll_down(int npixels)
{
   register int i;

   /* no tiles need to be redrawn */
   if (screen_orgy <= 40-npixels)
   {
      screen_orgy+=npixels;
      fg_pan(screen_orgx,screen_orgy+vpo);
   }
   /* redraw one row of tiles and do a page swap */
   else if (tile_orgy < nrows - 15)
   {
      tile_orgy++;
      screen_orgy-=(16-npixels);
      fg_transfer(0,351,16+vpo,vpo+239,0,223+hpo,0,0);
      swap();
      for(i = 0; i< 22; i++)
         put_tile(i,14,visual);
   }
   /* can't scroll down */
   else
      return(ERR);

   /* set the mouse limits */
   set_mouse_limy();
   return(OK);
}
/******************************************************************/
void set_mouse_limx()
{
   /* keep the mouse within the visible screen area */
   mouse_limx1 = screen_orgx;
   mouse_limx2 = mouse_limx1+304;
   fg_mouselim(mouse_limx1,mouse_limx2,mouse_limy1+vpo,mouse_limy2+vpo);
}
/******************************************************************/
void set_mouse_limy()
{
   /* keep the mouse within the visible screen area */
   mouse_limy1 = screen_orgy;
   mouse_limy2 = mouse_limy1+192;
   fg_mouselim(mouse_limx1,mouse_limx2,mouse_limy1+vpo,mouse_limy2+vpo);
}
/******************************************************************/
void set_top()
{
   /* set tile attribute: solid on top */
   int row,col;
   int tile;

   col = tile_orgx + xmouse/16;
   row = tile_orgy + (ymouse-vpo)/16;
   tile = level_map[col][row];
   set_bit(tile,0,1);
}
/******************************************************************/
void set_bottom()
{
   /* set tile attribute: solid on bottom */

   int row,col;
   int tile;

   col = tile_orgx + xmouse/16;
   row = tile_orgy + (ymouse-vpo)/16;
   tile = level_map[col][row];
   set_bit(tile,1,1);
}
/******************************************************************/
void set_left()
{
   /* set tile attribute: solid on left */

   int row,col;
   int tile;
   col = tile_orgx + xmouse/16;
   row = tile_orgy + (ymouse-vpo)/16;
   tile = level_map[col][row];
   set_bit(tile,2,1);
}
/******************************************************************/
void set_right()
{
   /* set tile attribute: solid on right */

   int row,col;
   int tile;
   col = tile_orgx + xmouse/16;
   row = tile_orgy + (ymouse-vpo)/16;
   tile = level_map[col][row];
   set_bit(tile,3,1);
}
/******************************************************************/
void clear_tile_attributes()
{
   int row,col;
   int tile;

   col = tile_orgx + xmouse/16;
   row = tile_orgy + (ymouse-vpo)/16;
   tile = level_map[col][row];
   background_attributes[tile] = 0;
}
/******************************************************************/
void show_coords()
{
   /* press F2 to show the coordinates, tile number and tile
      attributes of the current tile */

   char string[50];
   char string1[9];

   int x,y,row,col;
   int tile;

   /* what tile is the mouse on now? */
   x = tile_orgx * 16 + xmouse&0xfff0;
   y = tile_orgy * 16 + (ymouse-vpo)&0xfff0;

   col = tile_orgx + xmouse/16;
   row = tile_orgy + (ymouse-vpo)/16;

   tile = level_map[col][row];

   sprintf(string,"x=%d y=%d  row=%d col=%d  tile=%d ", x,y,row,col,tile);
   sprintf(string1,"%1d%1d%1d%1d%1d%1d%1d%1d",
      test_bit(tile,0),
      test_bit(tile,1),
      test_bit(tile,2),
      test_bit(tile,3),
      test_bit(tile,4),
      test_bit(tile,5),
      test_bit(tile,6),
      test_bit(tile,7));

   string1[8] = 0;
   strcat(string,string1);

   /* display the message, wait for a key, clear the message */
   popup_message(string);
   fg_waitkey();
   popdown();
}
/******************************************************************/
void swap()
{
   /* hidden & visual page offset toggles between 0 and 240 */
   vpo = 240 - vpo;
   hpo = 240 - hpo;
   visual = !visual;
   hidden = !hidden;

   /* move to new screen origin */
   fg_pan(screen_orgx,screen_orgy+vpo);

   ymouse -= hpo;
   ymouse += vpo;

   /* reset the mouse limits and move the mouse to the other page */
   fg_mouselim(mouse_limx1,mouse_limx2,mouse_limy1+vpo,mouse_limy2+vpo);
   fg_mousemov(xmouse,ymouse);
}
/******************************************************************/
void update_level_undo()
{
   /* update the undo information */
   register int i,j;

   for (j = 0; j < nrows; j++)
   {
     for (i = 0; i < ncols; i++)
     {
         level_undo[i][j] = level_map[i][j];
         foreground_undo[i][j] = foreground_map[i][j];
     }
   }
}
/******************************************************************/
void undo_level()
{
   /* put the level back the way it was */
   register int i,j;
   unsigned char temp;

   /* toggle the undo maps and the foreground/background maps */
   for (j = 0; j < nrows; j++)
   {
     for (i = 0; i < ncols; i++)
     {
         temp = level_map[i][j];
         level_map[i][j] = level_undo[i][j];
         level_undo[i][j] = temp;

         temp = foreground_map[i][j];
         foreground_map[i][j] = foreground_undo[i][j];
         foreground_undo[i][j] = temp;
     }
   }

   /* display the tiles */
   for (i = 0; i < 22; i++)
   {
      for (j = 0; j < 15; j++)
      {
         put_tile(i,j,visual);
         put_foreground_tile(i,j,visual);
      }
   }
}
