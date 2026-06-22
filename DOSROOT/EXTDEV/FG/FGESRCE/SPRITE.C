/******************************************************************\
*  sprite.c -- game editor source code                             *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "editdefs.h"
/******************************************************************/
int edit_sprites()
{
   /* function called from main menu or from load_edit_sprites() */
   fg_mousevis(OFF);
   fg_setpage(0);
   grid_boundary = OFF;

   /* draw the sprite editor */
   fix_palettes(1);
   draw_sprite_editor();

   /* activate the sprite editor */
   activate_sprite_editor();

   /* clean up the screen */
   fg_mousevis(OFF);
   draw_screen();

   /* return to main menu */
   fg_waitfor(3);
   return(OK);
}
/******************************************************************/
int activate_sprite_editor()
{
   /* main controlling function for the sprite editor */

   register int i;
   int x,y;
   int grid_x,grid_y;
   int old_grid_x,old_grid_y;
   unsigned char key,aux;
   int count;
   int color;
   static char menu_key[] = {'c','h','t','f','u','m','b',
                             'i','s','d','n','p','q'};
   old_grid_x = 0;
   old_grid_y = 0;
   for(;;)
   {
      fg_mousevis(ON);
      set_grid_boundary(ON);
      fg_waitfor(1);
      fg_intkey(&key,&aux);
      flushkey();
      if (key + aux == 0)
      {
         /* mouse button, held down */
         fg_mousepos(&xmouse,&ymouse,&buttons);

         /* mouse over grid -- show grid coordinates */
         if (buttons == 0 && BETWEEN(xmouse,8,135)
                          && BETWEEN(ymouse,26,185))
         {
            grid_x = (xmouse - 8) / 4;
            grid_y = (ymouse - 26) /4;
            if (grid_x != old_grid_x || grid_y != old_grid_y)
            {
               x = grid_x+x_offset;
               y = grid_y+y_offset;
               show_sprite_coords(x,y);
               old_grid_x = grid_x;
               old_grid_y = grid_y;
            }
         }

         /* mouse over sprite -- show sprite coordinate */
         else if (buttons == 0 && BETWEEN(xmouse,144,239)
                               && BETWEEN(ymouse,26,121))
         {
            grid_x = xmouse - 144;
            grid_y = ymouse - 26;
            if (grid_x != old_grid_x || grid_y != old_grid_y)
            {
               show_sprite_coords(grid_x,grid_y);
               old_grid_x = grid_x;
               old_grid_y = grid_y;
            }
         }
         /* left butten pressed */
         else if (buttons == 1 && BETWEEN(xmouse,8,135)
                               && BETWEEN(ymouse,26,185))
         {
           /* update the undo information */
            update_sprite_old();

            /* continue updating pixels while the button is held down */
            while (buttons == 1)
            {
               /* update the fat-bit editor */
               if (BETWEEN(xmouse,8,135) && BETWEEN(ymouse,26,185))
               {
                  grid_x = (xmouse - 8) / 4;
                  grid_y = (ymouse - 26) /4;
                  if (grid_x != old_grid_x || grid_y != old_grid_y)
                  {
                     /* set pixels to the foreground color */
                     set_sprite_grid(grid_x,grid_y,foreground_color);

                     /* also update the sprite coordinates */
                     x = grid_x+x_offset;
                     y = grid_y+y_offset;
                     show_sprite_coords(x,y);

                     /* simultaneously update the sprite */
                     x += 144;
                     y += 26;

                     /* be sure the grid boundary is off */
                     set_grid_boundary(OFF);
                     set_sprite_point(x,y,foreground_color);
                     old_grid_x = grid_x;
                     old_grid_y = grid_y;
                     fg_mousebut(1,&count,&xmouse,&ymouse);
                  }
               }
               /* poll the mouse again */
               fg_mousevis(ON);
               fg_mousepos(&xmouse,&ymouse,&buttons);
            }
            /* set flag for saving sprite information */
            sprite_changed = TRUE;
         }
         /* move the grid bounding box */
         else if (buttons == 1 && xmouse >= 144+x_offset
                               && xmouse <= 144+x_limit
                               && ymouse >= 26+y_offset
                               && ymouse <= 26+y_limit)
            move_grid_boundary();

         /* right button pressed, mouse on fat-bit grid */
         else if (buttons == 2 && BETWEEN(xmouse,8,135)
                               && BETWEEN(ymouse,26,185))
         {
            /* update the undo information */
            update_sprite_old();

            /* loop while the right button is pressed */
            while (buttons == 2)
            {
               if (BETWEEN(xmouse,8,135) && BETWEEN(ymouse,26,185))
               {
                  grid_x = (xmouse - 8) / 4;
                  grid_y = (ymouse - 26) /4;
                  if (grid_x != old_grid_x || grid_y != old_grid_y)
                  {

                     /* update the fat-bit grid */
                     set_sprite_grid(grid_x,grid_y,background_color);

                     /* show the coordinates */
                     x = grid_x+x_offset;
                     y = grid_y+y_offset;
                     show_sprite_coords(x,y);

                     /* simultaneously update the sprite */
                     x += 144;
                     y += 26;
                     set_grid_boundary(OFF);
                     set_sprite_point(x,y,background_color);
                     old_grid_x = grid_x;
                     old_grid_y = grid_y;
                     fg_mousebut(2,&count,&xmouse,&ymouse);
                  }
               }
               /* continue polling the mouse */
               fg_mousevis(ON);
               fg_mousepos(&xmouse,&ymouse,&buttons);
            }
            /* set the flag for saving the sprite */
            sprite_changed = TRUE;
         }
         /* left mouse button, clicked, not on grid */
         fg_mousebut(1,&count,&xmouse,&ymouse);

         if (count > 0)
         {
            /* set the foreground color */
            if (BETWEEN(xmouse,291,315) && BETWEEN(ymouse,26,185))
            {
               fg_mousevis(OFF);
               color = fg_getpixel(xmouse,ymouse);
               set_sprite_foreground_color(color);
            }
            /* menu */
            if (BETWEEN(xmouse,248,289) && BETWEEN(ymouse,26,155))
            {
               i = (ymouse - 26)/10;
               key = menu_key[i];
            }
            /* animate */
            if (BETWEEN(xmouse,160,223) && BETWEEN(ymouse,131,139))
            {
               key = 'a';
            }
            /* grid */
            if (BETWEEN(xmouse,8,135) && BETWEEN(ymouse,26,185))
            {
               grid_x = (xmouse - 8) / 4;
               grid_y = (ymouse - 26) /4;
               set_sprite_grid(grid_x,grid_y,foreground_color);
               x = grid_x+x_offset;
               y = grid_y+y_offset;
               show_sprite_coords(x,y);
               x += 144;
               y += 26;
               set_grid_boundary(OFF);
               set_sprite_point(x,y,foreground_color);
               old_grid_x = grid_x; old_grid_y = grid_y;
               sprite_changed = TRUE;
            }
         }
         /* right mouse button */
         fg_mousebut(2,&count,&xmouse,&ymouse);

         if (count > 0)
         {
            /* set the background color */
            if (BETWEEN(xmouse,291,315) && BETWEEN(ymouse,26,185))
            {
               fg_mousevis(OFF);
               color = fg_getpixel(xmouse,ymouse);
               set_sprite_background_color(color);
            }
            /* grid */
            if (BETWEEN(xmouse,8,135) && BETWEEN(ymouse,26,185))
            {
               grid_x = (xmouse - 8) / 4;
               grid_y = (ymouse - 26) /4;
               set_sprite_grid(grid_x,grid_y,background_color);
               x = grid_x+x_offset;
               y = grid_y+y_offset;
               show_sprite_coords(x,y);
               x += 144;
               y += 26;
               set_grid_boundary(OFF);
               set_sprite_point(x,y,background_color);
               old_grid_x = grid_x;
               old_grid_y = grid_y;
               sprite_changed = TRUE;
            }
         }
      }

      /* convert key to lower case */
      if (isupper(key))
         key += 32;

      /* Escap key exits */
      if (key == ESC || key == 'q')
      {
         if (sprite_changed)
            save_sprite();
         sprite_changed = FALSE;
         return(OK);
      }

      /* other keys trigger menu functions */
      else if (key == 'c')
         clear_sprite();
      else if (key == 'h')
         flip_sprite();
      else if (key == 't')
         transpose_sprite_colors();
      else if (key == 'f')
         flood_fill_sprite();
      else if (key == 'u')
         undo_sprite();
      else if (key == 'm')
         mask_sprite();
      else if (key == 'b')
         bounding_box();
      else if (key == 'i')
         import_sprite();
      else if (key == 's')
         save_sprite();
      else if (key == 'd')
         delete_sprite();
      else if (key == 'n')
         next_sprite();
      else if (key == 'p')
         previous_sprite();
      else if (key == 'a')
         animate_sprite_list();
   }
}
/******************************************************************/
void animate_sprite_list()
{
   register int i;
   unsigned char key,aux;
   int count;

   fg_mousevis(OFF);
   if (nsprites <= 1) return;
   set_grid_boundary(OFF);
   get_sprite();
   bitmap_to_grid();
   get_minimal_sprite();

   /* save the current sprite */
   sprite_to_array(current_sprite);

   /* display all the sprites in the list, in sequence */
   for(;;)
   {
      for (i = 0; i < nsprites; i++)
      {
         fg_setcolor(0);
         fg_rect(144,239,26,121);
         fg_move(sprite[i].xorg,sprite[i].yorg);
         fg_drwimage(sprite[i].bitmap,sprite[i].width,sprite[i].height);
         fg_waitfor(2);
         fg_intkey(&key,&aux);
         fg_mousebut(1,&count,&xmouse,&ymouse);
         if (key+aux+count > 0)
            break;
      }
      if (key+aux+count > 0)
         break;
   }

   /* restore the sprite area */
   fg_setcolor(0);
   fg_rect(144,239,26,121);
   fg_move(sprite_xorg,sprite_yorg);
   fg_drwimage(bitmap,sprite_width,sprite_height);
   set_grid_boundary(ON);
   fg_waitfor(3);
}
/******************************************************************/
void array_to_sprite(int n)
{
   int nbytes;

   /* copy sprite from far structure array to working variables */
   sprite_width       = sprite[n].width;
   sprite_height      = sprite[n].height;
   sprite_xorg        = sprite[n].xorg;
   sprite_yorg        = sprite[n].yorg;
   sprite_boundx      = sprite[n].bound_x;
   sprite_boundy      = sprite[n].bound_y;
   sprite_boundwidth  = sprite[n].bound_width;
   sprite_boundheight = sprite[n].bound_height;

   /* make sure sprite has a positive width & height */
   if (sprite_width <= 0) sprite_width = 1;
   if (sprite_height <= 0) sprite_height = 1;

   /* copy the bitmap */
   nbytes = sprite_width*sprite_height;
   memcpy(bitmap,sprite[n].bitmap,nbytes);
}
/******************************************************************/
void bitmap_to_grid()
{
   register int i,j;
   int color;
   int x,y;
   int byte_ptr;

   fg_mousevis(OFF);
   get_sprite();

   /* copy to fat bit grid */
   byte_ptr = 0;
   for (j = 95; j >= 0; j--)
   {
      for (i = 0; i < 96; i++)
         this_sprite[i][j] = bitmap[byte_ptr++];
   }
   /* set the points in the fat bit, if they have changed */
   for (i = 0; i < 32; i++)
   {
      for (j = 0; j < 40; j++)
      {
         x = x_offset+i;
         y = y_offset+j;

         if (this_sprite[x][y] != old_sprite[x][y])
         {
            color = (int)this_sprite[x][y];
            set_sprite_grid(i,j,color);
         }
      }
   }
}
/******************************************************************/
void bounding_box()
{
   /* the bounding box is used for collision detection */
   unsigned char key,aux;
   int buttons;
   int old_xmouse,old_ymouse;
   int corner_x,corner_y;
   int skip;
   int x,y;

   skip = FALSE;
   set_grid_boundary(OFF);
   fg_mousevis(OFF);
   fg_mousemov(164,46);
   fg_mouselim(144,239,26,121);

   fg_waitfor(4);
   fg_mousepos(&xmouse,&ymouse,&buttons);
   old_xmouse = xmouse;
   old_ymouse = ymouse;

   /* draw the crosshairs */
   fg_setcolor(white);
   xor_horiz_line(144,239,ymouse);
   xor_vert_line(xmouse,26,121);

   x = xmouse - 144;
   y = ymouse - 26;
   show_sprite_coords(x,y);

   while(buttons == 0)
   {
      /* check the current mouse position */
      fg_waitfor(1);
      fg_mousepos(&xmouse,&ymouse,&buttons);

      /* if mouse has moved, move the crosshairs */
      if (xmouse != old_xmouse || ymouse != old_ymouse)
      {
         fg_setcolor(white);
         xor_horiz_line(144,239,old_ymouse);
         xor_vert_line(old_xmouse,26,121);

         xor_horiz_line(144,239,ymouse);
         xor_vert_line(xmouse,26,121);

         old_xmouse = xmouse;
         old_ymouse = ymouse;
         x = xmouse - 144;
         y = ymouse - 26;
         show_sprite_coords(x,y);
      }

      /* check for Escape key */
      fg_intkey(&key,&aux);
      if (key == ESC)
      {
         skip = TRUE;
         break;
      }
   }
   /* xor the crosshairs to remove them */
   fg_setcolor(white);
   xor_horiz_line(144,239,ymouse);
   xor_vert_line(xmouse,26,121);

   if (skip)
   {
      fg_mouselim(0,319,0,199);
      return;
   }
   /* now we are drawing a box instead of crosshairs */
   corner_x = xmouse;
   corner_y = ymouse;
   fg_mouselim(corner_x,239,corner_y,121);

   fg_setcolor(white);
   fg_boxx(corner_x,xmouse,corner_y,ymouse);

   /* move the box around */
   while(buttons > 0)
   {
      fg_waitfor(1);
      fg_mousepos(&xmouse,&ymouse,&buttons);

      if (xmouse != old_xmouse || ymouse != old_ymouse)
      {
         fg_setcolor(white);
         fg_boxx(corner_x,old_xmouse,corner_y,old_ymouse);
         fg_boxx(corner_x,xmouse,corner_y,ymouse);

         old_xmouse = xmouse;
         old_ymouse = ymouse;

         x = xmouse - corner_x + 1;
         y = ymouse - corner_y + 1;
         show_sprite_coords(x,y);
      }
   }

   calculate_sprite_size();
   sprite_boundx = corner_x - sprite_xorg;
   sprite_boundy = ymouse - sprite_yorg;
   sprite_boundwidth = x;
   sprite_boundheight = y;

   /* clear the box */
   fg_setcolor(white);
   fg_boxx(corner_x,xmouse,corner_y,ymouse);

   /* reset the mouse limits */
   fg_mouselim(0,319,0,199);
   sprite_changed = TRUE;
}
/******************************************************************/
void calculate_sprite_size()
{
   /*  Figures out the smallest rectangle containing the entire sprite */
   int x,y;
   int bottom,top,left,right;
   char *sprite;

   bottom = 95; top = 0;  /* impossible values for the edges */
   left = 95; right = 0;

   sprite = bitmap;
   for (y = 0; y < 96; y++)
      for (x = 0; x < 96; x++)
         if (*sprite++)   /* found a non-transparent pixel! */
         {
            if (x<left) left = x;     /* if (further left) new left edge */
            if (x>right) right = x;   /* if (further right) new right edge */
            if (y<bottom) bottom = y; /* if (further down) new bottom edge */
            if (y>top) top = y;       /* if (further up) new top edge */
         }

   if (left == 95) /* if (left edge still impossible) sprite must be empty */
   {
      sprite_width = 1;  /* give empty sprites a 1-pixel size for grins */
      sprite_height = 1;
      sprite_xorg = 144;
      sprite_yorg = 122;
   }
   else
   {
      sprite_width = right - left + 1;
      sprite_height = top - bottom + 1;
      sprite_xorg = 144 + left;
      sprite_yorg = 122 - bottom - 1;
   }

}
/******************************************************************/
check_sprite_suffixes(char *fname, int file_type)
{
   /* sprite files have a "lst" extension, sprite list files have
      a "lst" extension */

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

   /* main sprite list file */
   if (file_type == 0)
   {
      fname[index+1] = '\0';
      strcat(fname,"lst");
      strcpy(sprite_fname,fname);
   }
   /* sprite file */
   else
   {
      fname[index+1] = '\0';
      strcat(fname,"lst");
      strcpy(list_fnames[file_type-1],fname);
   }
   return(OK);
}
/******************************************************************/
void clear_sprite()
{
   register int i,j;

   /* clear the sprite to the background color */

   update_sprite_old();
   for(i = 0; i < 96; i++)
   {
      for(j = 0; j < 96; j++)
      {
         this_sprite[i][j] = (char)background_color;
      }
   }
   /* also set the fat-bit grid */
   for (i = 0; i < 32; i++)
   {
      for (j = 0; j < 40; j++)
      {
         set_sprite_grid(i,j,background_color);
      }
   }
   set_grid_boundary(OFF);
   fg_setcolor(background_color);
   fg_rect(144,239,26,121);
   set_grid_boundary(ON);

   sprite_changed = TRUE;
}
/******************************************************************/
void delete_sprite()
{
   /* delete the current sprite from the sprite list */

   register int i;
   unsigned char key,aux;

   if (nsprites == 1)
      return;
   fg_mousevis(OFF);
   fg_setcolor(black);
   put_string("delete this frame?",80,197);

   fg_getkey(&key,&aux);
   if ((key|32) == 'y')
   {
      /* save the undo information */
      update_sprite_old();

      /* is it the last sprite in the list? */
      if (current_sprite == nsprites-1)
      {
         free(sprite[current_sprite].bitmap);
         current_sprite--;
         nsprites--;
      }
      else
      {
         /* move all the other sprites forward in the array */
         for (i = current_sprite; i < nsprites-1; i++)
         {
            sprite[i].bitmap = sprite[i+1].bitmap;
            sprite[i].width = sprite[i+1].width;
            sprite[i].height = sprite[i+1].height;
            sprite[i].xorg = sprite[i+1].xorg;
            sprite[i].yorg = sprite[i+1].yorg;
         }
         nsprites--;
         free(sprite[nsprites].bitmap);
      }

      /* draw the new sprite */
      set_grid_boundary(OFF);
      array_to_sprite(current_sprite);

      fg_setcolor(0);
      fg_rect(144,239,26,121);
      fg_move(sprite_xorg,sprite_yorg);
      fg_drwimage(bitmap,sprite_width,sprite_height);
      get_sprite();
      bitmap_to_grid();
      put_spritenum();
   }

   /* clear the status bar area */
   fg_setcolor(white);
   fg_rect(80,187,190,199);

   sprite_changed = TRUE;
}
/******************************************************************/
void draw_sprite_editor()
{
   /* draw the screen */

   register int i,j;
   int x,y;
   char temp_string[2];

   static char *string[] = {
      "Clear",
      "Hflip",
      "Trans",
      "Fill",
      "Undo",
      "Mask",
      "Bound",
      "Import",
      "Save",
      "Del",
      "Next",
      "Prev",
      "Quit"
   };

   /* clear the area below the menu */
   fg_mousevis(OFF);
   fg_setcolor(blue);
   fg_rect(0,319,25,199);

   fg_setcolor(black);
   fg_rect(0,xlimit,menu_bottom,menu_bottom);

   /* draw the background for the fat bit grid */
   fg_setcolor(0);
   fg_rect(8,136,26,186);

   /* use vertical bars to divide into 32 horizontal grid boxes */
   x = 8;
   fg_setcolor(grey);
   for (i = 0; i <= 32; i++)
   {
      fg_rect(x,x,26,186);
      x += 4;
   }

   /* use horizontal bars to divide into 40 vertical grid boxes */
   y = 26;
   for (j = 0; j <= 40; j++)
   {
      fg_rect(8,136,y,y);
      y += 4;
   }

   /* fill the squares with grey dots */
   for(i = 0; i < 32; i++)
   {
      for(j = 0; j < 40; j++)
      {
         x = (i * 4) + 10;
         y = (j * 4) + 28;
         fg_setcolor(grey);
         fg_point(x,y);
      }
   }

   /* draw the sprite area, which is 96 wide x 96 tall */
   fg_setcolor(0);
   fg_rect(144,239,26,121);

   /* draw the menu area in white and outline it in black */
   fg_setcolor(white);
   fg_rect(248,289,26,156);
   fg_setcolor(black);
   fg_box(248,289,26,156);

   /* null terminate the temporary string, which will hold the
      first letter of each menu item */

   temp_string[1] = '\0';

   x = 252;
   y = 34;
   for (i = 0; i < 13; i++)
   {
      /* draw the menu item */
      fg_setcolor(black);
      put_string(string[i],x,y);

      /* highlight the first letter of the menu item in blue */
      temp_string[0] = string[i][0];
      fg_setcolor(blue);
      put_string(temp_string,x,y);
      y+=10;
   }

   /* 'animate' menu item */
   fg_setcolor(white);
   fg_rect(161,222,131,139);
   fg_setcolor(black);
   fg_box(160,223,130,140);
   put_string("Animate",171,137);
   fg_setcolor(blue);
   put_string("A",171,137);

   /* palettes */
   y = 26;
   for (i = 0; i < 32; i++)
   {
      fg_setcolor(i);
      fg_rect(291,293,y,y+4);

      fg_setcolor(i+32);
      fg_rect(294,296,y,y+4);

      fg_setcolor(i+64);
      fg_rect(297,299,y,y+4);

      fg_setcolor(i+96);
      fg_rect(300,302,y,y+4);

      fg_setcolor(i+128);
      fg_rect(303,305,y,y+4);

      fg_setcolor(i+160);
      fg_rect(306,308,y,y+4);

      fg_setcolor(i+192);
      fg_rect(309,311,y,y+4);

      fg_setcolor(i+224);
      fg_rect(312,315,y,y+4);

      y += 5;
   }

   /* foreground, background colors */
   fg_setcolor(grey);
   fg_box(256,272,170,186);
   fg_box(272,288,170,186);

   /* bottom status area */
   fg_setcolor(white);
   fg_rect(0,319,189,199);
   fg_setcolor(black);
   fg_rect(0,319,189,189);

   put_string("Sprite", 6,197);
   put_spritenum();

   set_sprite_foreground_color(foreground_color);
   set_sprite_background_color(background_color);

   /* display sprite sprite area */
   fg_move(sprite_xorg,sprite_yorg);
   fg_drwimage(bitmap,sprite_width,sprite_height);
   get_sprite();

   /* update arrays */
   memset(old_sprite,0,96*96);
   bitmap_to_grid();
   update_sprite_old();
}
/******************************************************************/
void flip_sprite()
{
   /* rotate by 180 degrees */

   char temp_grid[96];
   register int i,j;

   for(j = 0; j < 96; j++)
   {
      for(i = 0; i < 96; i++)
      {
         old_sprite[i][j] = this_sprite[i][j];
         temp_grid[i] = this_sprite[95-i][j];
      }
      for(i = 0; i < 96; i++)
         this_sprite[i][j] = temp_grid[i];
   }
   restore_this_sprite();
   sprite_changed = TRUE;
}
/******************************************************************/
void flood_fill_sprite()
{
   int x,y;
   int grid_x,grid_y;
   int old_gridx,old_gridy;
   int count;
   unsigned char key,aux;

   /* put a message on the status bar */
   fg_mousevis(OFF);
   fg_setcolor(black);
   put_string("Fill",80,197);

   /* clear the mouse buttons */
   fg_waitfor(5);
   fg_mousebut(1,&count,&xmouse,&ymouse);
   fg_mousebut(2,&count,&xmouse,&ymouse);

   old_gridx = 0;
   old_gridy = 0;

   for(;;)
   {
      fg_mousepos(&xmouse,&ymouse,&buttons);

      /* no buttons pressed, on fat bit grid */
      if (buttons == 0 && BETWEEN(xmouse,8,135) && BETWEEN(ymouse,26,185))
      {
         grid_x = (xmouse - 8) /4;
         grid_y = (ymouse - 26)/4;

         /* update coordinates */
         if (grid_x != old_gridx || grid_y != old_gridy)
         {
            x = grid_x+x_offset;
            y = grid_y+y_offset;
            show_sprite_coords(x,y);
            old_gridx = grid_x;
            old_gridy = grid_y;
         }
      }

      /* escape key pressed? */
      fg_waitfor(1);
      fg_intkey(&key,&aux);
      if (key == ESC)
         break;

      /* fill with the foreground color */
      fg_mousevis(ON);
      fg_mousebut(1,&count,&xmouse,&ymouse);

      if (count > 0)
      {
         set_grid_boundary(OFF);
         if (BETWEEN(xmouse,8,135) && BETWEEN(ymouse,26,185))
         {
            fg_mousevis(OFF);
            grid_x = (xmouse - 8) /4;
            grid_y = (ymouse - 26)/4;

            x = grid_x + 144 + x_offset;
            y = grid_y + 26 + y_offset;

            /* check if we are filling to the background color */
            if (fg_getpixel(x,y) == blue)
            {
               fg_setcolor(black);
               fg_box(143,241,25,122);
            }

            /* move to and fill the small area */
            fg_setcolor(foreground_color);
            fg_paint(x,y);

            fg_setcolor(blue);
            fg_box(143,241,25,122);
            update_sprite_old();
            bitmap_to_grid();
            set_grid_boundary(ON);
         }
         else
            break;
      }

      /* fill with the background color */
      fg_mousevis(ON);
      fg_mousebut(2,&count,&xmouse,&ymouse);
      if (count > 0)
      {
         set_grid_boundary(OFF);
         if (BETWEEN(xmouse,8,135) && BETWEEN(ymouse,26,185))
         {
            fg_mousevis(OFF);
            grid_x = (xmouse - 8) /4;
            grid_y = (ymouse - 26)/4;

            x = grid_x + 144 + x_offset;
            y = grid_y + 26 + y_offset;

            /* check if we are filling to the background color */
            if (fg_getpixel(x,y) == blue)
            {
               fg_setcolor(black);
               fg_box(143,241,25,122);
            }

            /* move to and fill the small area */
            fg_setcolor(background_color);
            fg_paint(x,y);

            fg_setcolor(blue);
            fg_box(143,241,25,122);

            update_sprite_old();
            bitmap_to_grid();
            set_grid_boundary(ON);
         }
         else
            break;
      }
   }

   /* clear the status bar */
   fg_mousevis(OFF);
   fg_setcolor(white);
   fg_rect(80,104,190,199);

   fg_waitfor(2);
   sprite_changed = TRUE;
}
/******************************************************************/
void get_minimal_sprite()
{
   /* get the smallest possible sprite */
   get_sprite();
   calculate_sprite_size();

   fg_move(sprite_xorg,sprite_yorg);
   fg_getimage(bitmap,sprite_width,sprite_height);
}
/******************************************************************/
void get_sprite()
{
   /* get the sprite from the sprite area, store in a RAM bitmap */

   sprite_width = 96;
   sprite_height = 96;

   sprite_xorg = 144;
   sprite_yorg = 121;

   fg_move(sprite_xorg,sprite_yorg);
   fg_getimage(bitmap,sprite_width,sprite_height);
}
/******************************************************************/
void import_sprite()
{
   /* import a PCX file */
   unsigned char key,aux;
   char fname[13];
   int error;
   char *strptr;
   int index;
   int buttons,count;
   int old_xmouse,old_ymouse;
   int corner_x,corner_y;
   int dx,dy;
   int skip;
   int x,y,x2,y2;

   skip = FALSE;
   fg_mousevis(OFF);
   fg_setcolor(black);
   put_string("PCX file name:",80,197);
   put_string(sprite_pcxname,170,197);

   /* try to read in a file name */
   fg_getkey(&key,&aux);
   if (key == CR)
      strcpy(fname,sprite_pcxname);
   else
      get_string(fname,170,197,12,key,0);

   error = FALSE;
   strptr = strchr(fname,'.');

   /* period in string */
   if (strptr > 0)
   {
      index = (int)(strptr - fname);
      if (index > 8)
         error = TRUE;
      else if ((strcmpi(&fname[index],".pcx") == 0)
                || fname[index+1] == '\0')
         error = FALSE;
      if (!error && fname[index+1] == '\0')
         strcat(fname,"pcx");
   }
   /* no period in string */
   else
   {
      if (strlen(fname) > 8)
         error = TRUE;
      if (!error)
         strcat(fname,".pcx");
   }
   if (!error)
   {
      if (!file_exists(fname))
         error = TRUE;
   }
   if (error)
   {
      fg_setcolor(white);
      fg_rect(80,289,190,199);
      fg_setcolor(black);
      put_string("File not found.",80,197);
      wait_for_keystroke();
   }
   else
   {
      set_grid_boundary(OFF);
      strcpy(sprite_pcxname,fname);

      /* display the pcx file on page 1 */
      fg_setpage(1);
      fg_move(0,0);
      fg_showpcx(fname,1);
      fg_setvpage(1);

      fg_mousepos(&xmouse,&ymouse,&buttons);
      old_xmouse = xmouse;
      old_ymouse = ymouse;

      /* draw crosshairs */
      fg_setcolor(white);
      xor_horiz_line(0,319,ymouse);
      xor_vert_line(xmouse,0,199);

      /* move the crosshairs around until the left button is pressed */
      while(buttons == 0)
      {
         fg_waitfor(1);
         fg_mousepos(&xmouse,&ymouse,&buttons);
         if (xmouse != old_xmouse || ymouse != old_ymouse)
         {
            xor_horiz_line(0,319,old_ymouse);
            xor_vert_line(old_xmouse,0,199);

            xor_horiz_line(0,319,ymouse);
            xor_vert_line(xmouse,0,199);

            old_xmouse = xmouse;
            old_ymouse = ymouse;
         }

         /* check for the Escape key */
         fg_intkey(&key,&aux);
         if (key == ESC)
         {
            skip = TRUE;
            break;
         }
      }

      /* clear the crosshairs */
      xor_horiz_line(0,319,ymouse);
      xor_vert_line(xmouse,0,199);

      /* return to sprite editor if Escape was pressed */
      if (skip)
      {
         fg_setpage(0);
         fg_setvpage(0);

         fg_mouselim(0,319,0,199);
         fg_setcolor(white);
         fg_rect(80,289,190,199);

         fg_waitfor(3);
         fg_mousebut(1,&count,&xmouse,&ymouse);
         fg_mousebut(2,&count,&xmouse,&ymouse);
         return;
      }

      /* no more crosshairs, now draw a box around the sprite */
      corner_x = xmouse;
      corner_y = ymouse;

      y2 = MIN(199,ymouse+95);
      x2 = MIN(319,xmouse+95);
      fg_mouselim(xmouse+2,x2,ymouse+2,y2);

      /* move the box around until a button is pressed */
      while(buttons > 0)
      {
         fg_waitfor(1);
         fg_mousepos(&xmouse,&ymouse,&buttons);
         if (xmouse != old_xmouse || ymouse != old_ymouse)
         {
            fg_boxx(corner_x,old_xmouse,corner_y,old_ymouse);
            fg_boxx(corner_x,xmouse,corner_y,ymouse);

            old_xmouse = xmouse;
            old_ymouse = ymouse;
         }
         /* check for the Escape key */
         fg_intkey(&key,&aux);
         if (key == ESC)
         {
            skip = TRUE;
            break;
         }
      }

      /* clear the box */
      fg_boxx(corner_x,xmouse,corner_y,ymouse);

      /* make sure it is a non-zero sprite */
      if (corner_x >= xmouse || corner_y >= ymouse)
         skip = TRUE;

      /* sprite not imported */
      if (skip)
      {
         fg_setpage(0);
         fg_setvpage(0);

         fg_mouselim(0,319,0,199);
         fg_setcolor(white);
         fg_rect(80,289,190,199);

         fg_waitfor(3);
         fg_mousebut(1,&count,&xmouse,&ymouse);
         fg_mousebut(2,&count,&xmouse,&ymouse);
         return;
      }

      /* sprite imported, calculate width and height */
      dx = xmouse - corner_x;
      dy = ymouse - corner_y;

      /* get the sprite */
      fg_move(corner_x,ymouse);
      fg_getimage(bitmap,dx,dy);

      /* back to sprite editor */
      fg_setpage(0);
      fg_setvpage(0);

      /* clear the old sprite */
      fg_setcolor(0);
      fg_rect(144,239,26,121);

      x = 144 + (96 - dx)/2;
      y = 122 - (96 - dy)/2;
      fg_move(x,y);

      /* draw the new sprite */
      fg_drwimage(bitmap,dx,dy);

      sprite_boundx = x;
      sprite_boundy = y;
      sprite_boundwidth = dx;
      sprite_boundheight = dy;

      update_sprite_old();
      bitmap_to_grid();
   }

   /* fix the mouse limits */
   fg_mouselim(0,319,0,199);

   /* clear the status bar */
   fg_setcolor(white);
   fg_rect(80,289,190,199);

   /* clear the mouse buttons */
   fg_waitfor(3);
   fg_mousebut(1,&count,&xmouse,&ymouse);
   fg_mousebut(2,&count,&xmouse,&ymouse);

   sprite_changed = TRUE;
}
/******************************************************************/
void init_sprite()
{
   /* read the spritelist file, get the sprite file names */

   if ((tstream = fopen(sprite_fname,"rt")) != NULL)
   {
      fscanf(tstream,"%d",&nspritelists);
      if (nspritelists < 1 || nspritelists > MAXSPRITELISTS)
      {
         strcpy(spritelist_fname,"");
         strcpy(list_fnames[0],"untitled.lst");
         nspritelists = 1;
      }
      else
         fscanf(tstream,"%s",spritelist_fname);
      fclose(tstream);
   }
   else
   {
      strcpy(spritelist_fname,"");
      strcpy(list_fnames[0],"untitled.lst");
      nspritelists = 1;
   }
   init_this_spritelist();
}
/******************************************************************/
void init_this_spritelist()
{
   /* read the sprites from disk into RAM */

   register int i;
   int nbytes;

   /* free all the old sprite bitmaps, if there are any */
   for (i = 0; i < nsprites; i++)
      free(sprite[i].bitmap);

   sprite_changed = FALSE;
   nsprites = 1;
   x_offset = 32;
   x_limit = x_offset+31;
   y_offset = 24;
   y_limit = y_offset+39;

   sprite_boundx = 0;
   sprite_boundy = 0;
   sprite_boundwidth = 96;
   sprite_boundheight = 96;

   memset(this_sprite,0,9216);
   memset(old_sprite,0,9216);

   /* open the file */
   if ((tstream = fopen(spritelist_fname,"rb")) != NULL)
   {
      /* how many sprites are there? */
      fread(&nsprites,sizeof(int),1,tstream);

      /* read one sprite at a time */
      for (i = 0; i < nsprites; i++)
      {
         fread(&sprite_width,sizeof(int),1,tstream);
         fread(&sprite_height,sizeof(int),1,tstream);
         if (sprite_width <= 0) sprite_width = 1;
         if (sprite_height <= 0) sprite_height = 1;
         nbytes = sprite_width*sprite_height;

         fread(&sprite_xorg,sizeof(int),1,tstream);
         fread(&sprite_yorg,sizeof(int),1,tstream);

         fread(&sprite_boundx,sizeof(int),1,tstream);
         fread(&sprite_boundy,sizeof(int),1,tstream);
         fread(&sprite_boundwidth,sizeof(int),1,tstream);
         fread(&sprite_boundheight,sizeof(int),1,tstream);

         fread(bitmap,sizeof(char),nbytes,tstream);

         /* is there room for another sprite in RAM? */
         if ((sprite[i].bitmap = malloc(9220)) != NULL)
         {
            /* store the sprite in a RAM array */
            sprite_to_array(i);
         }

         /* out of room -- that was the last sprite! */
         else
         {
            nsprites = i;
            break;
         }
      }
      fclose(tstream);

      /* current sprite is sprite 0 */
      current_sprite = 0;
      array_to_sprite(current_sprite);
   }

   /* no file open */
   else
   {
      memset(bitmap,0,9216);
      sprite_xorg = 144;
      sprite_yorg = 121;
      sprite_width = 96;
      sprite_height = 96;

      sprite_boundx = 0;
      sprite_boundy = 0;
      sprite_boundwidth = 96;
      sprite_boundheight = 96;

      current_sprite = 0;
      sprite[current_sprite].bitmap = malloc(9220);
   }
}
/******************************************************************/
load_edit_sprites()
{
   /* called from sprite menu */
   if (load_sprites() != ERR)
      edit_sprites();
   return(OK);
}
/******************************************************************/
load_sprites()
{
   /* display and edit the sprite list file  (called from sprite
      menu and also file menu) */

   register int i,j;
   char string[50];
   int current;
   int spritelist_changed;
   int error;

   /* file name locations */
   static int x[] = { 158,
      20,120,220,
      20,120,220,
      20,120,220,
      20,120,220,
      20,120,220,
      20,120,220
   };

   static int y[] = { 40,
       55,  55,   55,
       65,  65,   65,
       75,  75,   75,
       85,  85,   85,
       95,  95,   95,
      105, 105,  105,
   };

   editing_sprite_files = TRUE;
   current = current_spritelist;

   fg_mousevis(OFF);
   fg_setcolor(blue);
   fg_rect(0,319,25,199);

   fg_setcolor(black);
   fg_rect(0,319,24,24);

   fg_setcolor(white);
   fg_rect(5,315,30,185);

   fg_setcolor(black);
   fg_box(5,315,30,185);

   sprintf(string,"sprite list file name: %s",sprite_fname);
   put_string(string,20,40);

   fg_setcolor(blue);
   put_string("F1:HELP",20,180);
   put_string("F10:SAVE",220,180);

   fg_setcolor(black);
   if ((tstream = fopen (sprite_fname,"rt")) != NULL)
   {
      fscanf(tstream,"%d",&nspritelists);
      nspritelists = MIN(nspritelists, MAXSPRITELISTS);
      if (nspritelists < 1)
      {
         nspritelists = 1;
         strcpy(list_fnames[0],"untitled.lst");
      }
      for (i = 0; i < nspritelists; i++)
      {
         if (fscanf(tstream,"%s",list_fnames[i]) == 0)
            break;
      }
      fclose(tstream);
   }
   if (list_fnames[0][0] == '\0')
      strcpy(list_fnames[0],"untitled.lst");

   for (i = 1; i <= nspritelists; i++)
      put_string(list_fnames[i-1],x[i],y[i]);

   if (current_spritelist > 0)
      strcpy(spritelist_fname,list_fnames[current_spritelist-1]);
   else
      strcpy(spritelist_fname,list_fnames[0]);

   current = MIN(current,nspritelists);
   error = FALSE;
   spritelist_changed = FALSE;
   for(;;)
   {
      if (current == 0)
         strcpy(string, sprite_fname);
      else
         strcpy(string,list_fnames[current-1]);
      fg_setcolor(blue);
      j = get_string(string,x[current],y[current],12,0,0);
      if (j == ESC)
      {
         error = TRUE;
         break;
      }

      if (j == ENTER && current > 0
          && strcmpi(string,list_fnames[current-1]) == 0)
      {
         if (current > 0)
         {
            strcpy(spritelist_fname,list_fnames[current-1]);
            init_this_spritelist();
         }
         else
            strcpy(spritelist_fname,list_fnames[0]);
         break;
      }

      /* open a new spritelist file */
      if (j == ENTER && current == 0
          && strcmpi(string, sprite_fname) != 0)
      {
         check_sprite_suffixes(string,current);
         strcpy(sprite_fname,string);

         fg_setcolor(white);
         fg_rect(x[0],x[0]+77,y[0]-9,y[0]);
         fg_setcolor(black);
         put_string(sprite_fname,x[0],y[0]);

         fg_setcolor(white);
         fg_rect(6,314,45,165);
         fg_setcolor(black);
         if ((tstream = fopen (sprite_fname,"rt")) != NULL)
         {
            fscanf(tstream,"%d",&nspritelists);
            nspritelists = MIN(nspritelists, MAXSPRITELISTS);
            if (nspritelists < 1)
            {
               nspritelists = 1;
               strcpy(list_fnames[0],"untitled.lst");
            }
            for (i = 0; i < nspritelists; i++)
            {
               if (fscanf(tstream,"%s",list_fnames[i]) == 0)
                  break;
            }
            fclose(tstream);
         }
         else
         {
            nspritelists = 1;
            strcpy(list_fnames[0],"untitled.lst");
         }
         if (list_fnames[0][0] == '\0')
            strcpy(list_fnames[0],"untitled.lst");

         for (i = 1; i <= nspritelists; i++)
            put_string(list_fnames[i-1],x[i],y[i]);

         if (current_spritelist > 0)
            strcpy(spritelist_fname,list_fnames[current_spritelist-1]);
         else
            strcpy(spritelist_fname,list_fnames[0]);

         current = MIN(current,nspritelists);
      }
      else if (current > 0 && (j == RIGHT_ARROW || j == LEFT_ARROW
                || j == UP_ARROW || j == DOWN_ARROW || j == ENTER
                || j == TAB))
      {
         check_sprite_suffixes(string,current);
         fg_setcolor(white);
         fg_rect(x[current],x[current]+77,y[current]-9,y[current]);
         fg_setcolor(black);
         if (current == 0)
            put_string(sprite_fname,x[current],y[current]);
         else
            put_string(list_fnames[current-1],x[current],y[current]);
         spritelist_changed = TRUE;
      }

      if (j == RIGHT_ARROW || j == TAB)
      {
         current++;
         if (current > nspritelists)
            current = 0;
      }
      else if (j == DOWN_ARROW)
      {
         if (current == 0)
            current++;
         else if (nspritelists < 3)
         {
            current++;
            if (current > nspritelists)
               current = 0;
         }
         else
         {
            current+=3;
            if (current > nspritelists)
               current -= nspritelists;
         }
      }
      else if (j == LEFT_ARROW)
      {
         current--;
         if (current < 0)
            current = nspritelists;
      }
      else if (j == UP_ARROW)
      {
         if (nspritelists < 3)
         {
            current--;
            if (current < 0)
               current = nspritelists;
         }
         else
         {
            current-=3;
            if (current < 0)
               current += nspritelists;
         }
      }
      else if (j == F1)
      {
         file_help_screen();
      }
      else if (j == F10)
      {
         if (current > 0)
            strcpy(spritelist_fname,list_fnames[current-1]);
         else
            strcpy(spritelist_fname,list_fnames[0]);
         init_sprite();
         break;
      }
      else if (j == DELETE && current > 0)
      {
         if (nspritelists > 0)
         {
            nspritelists--;

            for (i = current-1; i < nspritelists; i++)
               strcpy(list_fnames[i],list_fnames[i+1]);

            for (i = nspritelists+1 ; i >= current; i--)
            {
               fg_setcolor(white);
               fg_rect(x[i],x[i]+77,y[i]-9,y[i]);
               fg_setcolor(black);
               if (i <= nspritelists)
                  put_string(list_fnames[i-1],x[i],y[i]);
            }

            if (current > nspritelists)
               current --;
            spritelist_changed = TRUE;
         }
         if (nspritelists == 0)
         {
             strcpy(list_fnames[0],"untitled.lst");
             fg_setcolor(white);
             fg_rect(x[1],x[1]+77,y[1]-9,y[1]);
             fg_setcolor(black);
             put_string(list_fnames[0],x[1],y[1]);
             nspritelists = 1;
         }
      }

      else if (j == INSERT && current > 0 && nspritelists < MAXSPRITELISTS)
      {
         nspritelists++;
         for (i = nspritelists; i >= current; i--)
            strcpy(list_fnames[i],list_fnames[i-1]);
         strcpy(list_fnames[current-1],"untitled.lst");

         for (i = nspritelists ; i >= current; i--)
         {
            fg_setcolor(white);
            fg_rect(x[i],x[i]+77,y[i]-9,y[i]);
            fg_setcolor(black);
            if (i <= nspritelists)
               put_string(list_fnames[i-1],x[i],y[i]);
         }
         spritelist_changed = TRUE;
      }
   }

   if (spritelist_changed && !error)
   {
      if ((tstream = fopen(sprite_fname,"wt")) != NULL)
      {
         fprintf(tstream,"%d\n",nspritelists);
         for (i = 0; i < nspritelists; i++)
         {
            fprintf(tstream,"%s\n",list_fnames[i]);
         }
         fclose(tstream);
      }
   }

   current_spritelist = current;
   fg_setcolor(blue);
   fg_rect(0,319,25,199);
   editing_sprite_files = FALSE;

   if (error)
      return(ERR);
   else
      return(OK);
}
/******************************************************************/
void mask_sprite()
{
   /* show the sprite against a blue background instead of black */

   set_grid_boundary(OFF);
   fg_mousevis(OFF);

   /* get the sprite */
   get_sprite();

   /* clear the background */
   fg_setcolor(blue);
   fg_rect(144,239,26,121);

   /* draw the sprite */
   fg_move(144,121);
   fg_drwimage(bitmap,96,96);

   wait_for_keystroke();

   /* put the sprite back the way it was */
   fg_setcolor(0);
   fg_rect(144,239,26,121);

   fg_move(144,121);
   fg_drwimage(bitmap,96,96);
   set_grid_boundary(ON);
}
/******************************************************************/
void move_grid_boundary()
{
   register int i,j;
   int old_xmouse, old_ymouse;
   int buttons;
   int old_xoffset, old_yoffset;
   int color,old_color;
   int x,y;
   int dx,dy;

   old_xoffset = x_offset;
   old_yoffset = y_offset;

   fg_mousepos(&xmouse,&ymouse,&buttons);
   old_xmouse = xmouse;
   old_ymouse = ymouse;

   /* drag the box while the mouse button is pressed */
   while(buttons == 1)
   {
      fg_mousepos(&xmouse,&ymouse,&buttons);
      if (xmouse > old_xmouse)
      {
         dx = xmouse - old_xmouse;
         if (x_offset + dx <= 64)
         {
            set_grid_boundary(OFF);
            x_offset += dx;
            x_limit  += dx;
            set_grid_boundary(ON);
            fg_mousevis(ON);
            old_xmouse = xmouse;
         }
      }
      if (ymouse > old_ymouse)
      {
         dy = ymouse - old_ymouse;
         if (y_offset + dy <= 56)
         {
            set_grid_boundary(OFF);
            y_offset += dy;
            y_limit  += dy;
            set_grid_boundary(ON);
            fg_mousevis(ON);
            old_ymouse = ymouse;
         }
      }
      if (xmouse < old_xmouse)
      {
         dx = old_xmouse - xmouse;
         if (x_offset - dx >= 0)
         {
            set_grid_boundary(OFF);
            x_offset -= dx;
            x_limit -= dx;
            set_grid_boundary(ON);
            fg_mousevis(ON);
            old_xmouse = xmouse;
         }
      }
      if (ymouse < old_ymouse)
      {
         dy = old_ymouse - ymouse;
         if (y_offset - dy >= 0)
         {
            set_grid_boundary(OFF);
            y_offset-= dy;
            y_limit -= dy;
            set_grid_boundary(ON);
            fg_mousevis(ON);
            old_ymouse = ymouse;
         }
      }
   }

   /* update the fat bit grid */
   if (old_xoffset != x_offset || old_yoffset != y_offset)
   {
      fg_mousevis(OFF);
      for(i = 0; i < 32; i++)
      {
         for(j = 0; j < 40; j++)
         {
            color = this_sprite[i+x_offset][j+y_offset];
            old_color = this_sprite[i+old_xoffset][j+old_yoffset];
            if (color != old_color)
            {
               fg_setcolor(color);
               x = (i * 4) + 8;
               y = (j * 4) + 26;
               fg_rect(x+1,x+3,y+1,y+3);
               if (color == 0)
               {
                   fg_setcolor(grey);
                   fg_point(x+2,y+2);
               }
            }
         }
      }
   }
}
/******************************************************************/
void next_sprite()
{
   /* display the next sprite, if there is one */

   fg_mousevis(OFF);
   update_sprite_old();
   set_grid_boundary(OFF);
   get_sprite();
   bitmap_to_grid();
   get_minimal_sprite();

   /* save the current sprite */
   sprite_to_array(current_sprite);

   /* increment the current sprite */
   current_sprite++;

   /* add a sprite */
   if (current_sprite >= nsprites)
   {
      if ((sprite[current_sprite].bitmap = malloc(9220)) != NULL)
      {
         memset(sprite[current_sprite].bitmap,0,96*96);
         sprite[current_sprite].width = 96;
         sprite[current_sprite].height = 96;
         sprite[current_sprite].xorg = 144;
         sprite[current_sprite].yorg = 121;
         nsprites++;
         fg_setcolor(0);
         fg_rect(144,239,26,121);
         get_sprite();
         bitmap_to_grid();
      }

      /* unable to allocate room for another sprite */
      else
         current_sprite--;
   }

   /* just display the next sprite */
   else
   {
      array_to_sprite(current_sprite);
      fg_mousevis(OFF);
      fg_setcolor(0);
      fg_rect(144,239,26,121);
      fg_move(sprite_xorg,sprite_yorg);
      fg_drwimage(bitmap,sprite_width,sprite_height);
      get_sprite();
      bitmap_to_grid();
   }

   /* update status bar */
   put_spritenum();
}
/******************************************************************/
void previous_sprite()
{
   /* display the previous sprite */

   if (current_sprite > 0)
   {
      update_sprite_old();
      set_grid_boundary(OFF);
      get_minimal_sprite();

      sprite_to_array(current_sprite);
      current_sprite--;
      array_to_sprite(current_sprite);

      fg_mousevis(OFF);
      fg_setcolor(0);
      fg_rect(144,239,26,121);
      fg_move(sprite_xorg,sprite_yorg);
      fg_drwimage(bitmap,sprite_width,sprite_height);
      get_sprite();
      bitmap_to_grid();
      put_spritenum();
   }
}
/******************************************************************/
void put_spritenum()
{
   char string[6];

   fg_mousevis(OFF);

   sprintf(string,"%d:%d",current_sprite+1,nsprites);
   fg_setcolor(white);
   fg_rect(46,76,190,199);
   fg_setcolor(black);
   put_string(string,46,197);
}
/******************************************************************/
void restore_this_sprite()
{
   register int i,j;
   int color;
   int x,y;

   for (i = 0; i < 32; i++)
   {
      for (j = 0; j < 40; j++)
      {
         x = x_offset+i;
         y = y_offset+j;

         if (this_sprite[x][y] != old_sprite[x][y])
         {
            color = (int)this_sprite[x][y];
            set_sprite_grid(i,j,color);
         }
      }
   }

   set_grid_boundary(OFF);
   fg_mousevis(OFF);
   for(i = 0; i < 96; i++)
   {
      for(j = 0; j < 96; j++)
      {
         if (this_sprite[i][j] != old_sprite[i][j])
         {
            color = (int)this_sprite[i][j];
            fg_setcolor(color);
            fg_point(144+i,26+j);
         }
      }
   }
   set_grid_boundary(ON);
}
/******************************************************************/
void save_sprite()
{
   /* save your work in a file */

   register int i;
   int nbytes;

   unsigned char key,aux;
   char fname[13];
   char string[80];
   int error;
   int index;
   char *strptr;

   /* prompt on status bar */
   fg_mousevis(OFF);
   fg_setcolor(black);
   put_string("save in lst file:",72,197);

   put_string(spritelist_fname,180,197);

   /* use the current sprite name */
   fg_getkey(&key,&aux);
   if (key == CR)
      strcpy(fname,spritelist_fname);

   /* get a new sprite name */
   else
   {
      if (get_string(fname,180,197,12,key,0) == ESC)
      {
         fg_setpage(0);
         fg_setcolor(white);
         fg_rect(72,279,190,199);
         return;
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
      else
      {
         fname[index+1] = '\0';
         strcat(fname,"lst");
      }
   }

   /* no period in string */
   else
   {
      index = strlen(fname);
      if (index > 8)
         error = TRUE;
      if (!error)
         strcat(fname,".lst");
   }

   if (!error)
   {
      if (file_exists(fname))
      {
         fg_setcolor(white);
         fg_rect(72,279,190,199);
         fg_setcolor(black);
         sprintf(string,"%s exists. Overwrite it?",fname);
         put_string(string,72,197);
         fg_getkey(&key,&aux);

         if (key == 'y' || key == 'Y')
            error = FALSE;
         else
            error = TRUE;
      }
   }

   /* valid file name specified */
   if (!error)
   {
      strcpy(spritelist_fname,fname);
      set_grid_boundary(OFF);
      get_minimal_sprite();

      sprite_to_array(current_sprite);

      /* open a file */
      if ((tstream = fopen(spritelist_fname,"wb")) != NULL)
      {
         /* first integer value is the number of sprites */
         fwrite(&nsprites,sizeof(int),1,tstream);

         /* write sprite information for each sprite */
         for (i = 0; i < nsprites; i++)
         {
            array_to_sprite(i);

            fwrite(&sprite_width,sizeof(int),1,tstream);
            fwrite(&sprite_height,sizeof(int),1,tstream);
            fwrite(&sprite_xorg,sizeof(int),1,tstream);
            fwrite(&sprite_yorg,sizeof(int),1,tstream);
            fwrite(&sprite_boundx,sizeof(int),1,tstream);
            fwrite(&sprite_boundy,sizeof(int),1,tstream);
            fwrite(&sprite_boundwidth,sizeof(int),1,tstream);
            fwrite(&sprite_boundheight,sizeof(int),1,tstream);
            nbytes = sprite_width*sprite_height;
            fwrite(bitmap,sizeof(char),nbytes,tstream);
         }
         fclose(tstream);

         /* restore this sprite */
         array_to_sprite(current_sprite);
      }
      sprite_changed = FALSE;
   }

   /* clear the status bar */
   fg_setpage(0);
   fg_setcolor(white);
   fg_rect(72,279,190,199);
}
/******************************************************************/
void set_grid_boundary(int status)
{
   /* turn the grid boundary on if it is off */
   if (status == ON && grid_boundary == OFF)
   {
      fg_mousevis(OFF);
      fg_setcolor(white);

      /* use an xor box to draw the grid boundary */
      fg_boxx(144+x_offset,144+x_limit,26+y_offset,26+y_limit);
      grid_boundary = ON;
   }

   /* turn the grid boundary off if it is on */
   else if (status == OFF && grid_boundary == ON)
   {
      fg_mousevis(OFF);
      fg_setcolor(white);

      /* use an xor box to erase the grid boundary */
      fg_boxx(144+x_offset,144+x_limit,26+y_offset,26+y_limit);
      grid_boundary = OFF;
   }
}
/******************************************************************/
void set_sprite_background_color(int color)
{
   /* highlight the current background color */
   fg_mousevis(OFF);
   background_color = color;

   /* draw a rectangle in the background color area */
   fg_setcolor(background_color);
   fg_rect(273,287,171,185);

   /* color 0 is transparent (usually black) */
   if (color == 0)
   {
      fg_setcolor(grey);
      fg_boxx(274,286,172,184);
   }
}
/******************************************************************/
void set_sprite_foreground_color(int color)
{
   /* highlight the current foreground color */
   fg_mousevis(OFF);
   foreground_color = color;

   /* draw a rectangle in the foreground color area */
   fg_setcolor(foreground_color);
   fg_rect(257,271,171,185);

   /* color 0 is transparent (usually black) */
   if (color == 0)
   {
      fg_setcolor(grey);
      fg_boxx(258,270,172,184);
   }
}
/******************************************************************/
void set_sprite_grid(int i,int j,int color)
{
   /* draw a little rectangle on the fat bit editor */
   int x,y;

   fg_mousevis(OFF);
   x = (i * 4) + 8;
   y = (j * 4) + 26;

   this_sprite[i+x_offset][j+y_offset] = (char)color;

   fg_setcolor(color);
   fg_rect(x+1,x+3,y+1,y+3);

   if (color == 0)
   {
      fg_setcolor(grey);
      fg_point(x+2,y+2);
   }
}
/******************************************************************/
void set_sprite_point(int x,int y,int color)
{
   /* just set a point to the current color */
   fg_mousevis(OFF);
   fg_setcolor(color);
   fg_point(x,y);
}
/******************************************************************/
void show_sprite_coords(int x,int y)
{
   /* display the sprite coordinates on the status bar */
   char string[6];

   fg_mousevis(OFF);
   fg_setcolor(white);
   fg_rect(280,319,190,199);

   fg_setcolor(black);
   sprintf(string,"%2d,%2d",x,y);
   put_string(string,280,197);
}
/******************************************************************/
void sprite_to_array(int n)
{
   int nbytes;

   sprite[n].width        = sprite_width;
   sprite[n].height       = sprite_height;
   sprite[n].xorg         = sprite_xorg;
   sprite[n].yorg         = sprite_yorg;
   sprite[n].bound_x      = sprite_boundx;
   sprite[n].bound_y      = sprite_boundy;
   sprite[n].bound_width  = sprite_boundwidth;
   sprite[n].bound_height = sprite_boundheight;

   nbytes = sprite_width*sprite_height;
   memcpy(sprite[n].bitmap,bitmap,nbytes);
}
/******************************************************************/
void transpose_sprite_colors()
{
   /* set everything that is the background color to the foreground
      color */
   register int i,j;

   for(i = 0; i < 96; i++)
   {
      for(j = 0; j < 96; j++)
      {
         old_sprite[i][j] = this_sprite[i][j];
         if (this_sprite[i][j] == (char)background_color)
            this_sprite[i][j] = (char)foreground_color;
      }
   }

   restore_this_sprite();
   sprite_changed = TRUE;
}
/******************************************************************/
void undo_sprite()
{
   /* restore the sprite from the old_sprite buffer */
   char temp;
   register int i,j;

   for(i = 0; i < 96; i++)
   {
      for(j = 0; j < 96; j++)
      {
         temp = this_sprite[i][j];
         this_sprite[i][j] = old_sprite[i][j];
         old_sprite[i][j] = temp;
      }
   }
   restore_this_sprite();
}
/******************************************************************/
void update_sprite_old()
{
   memcpy(old_sprite,this_sprite,96*96);
}
/******************************************************************/
void xor_horiz_line(int x1,int x2,int y)
{
   fg_move(x1,y);
   fg_drawx(x2,y);
}
/******************************************************************/
void xor_vert_line(int x,int y1,int y2)
{
   fg_move(x,y1);
   fg_drawx(x,y2);
}
