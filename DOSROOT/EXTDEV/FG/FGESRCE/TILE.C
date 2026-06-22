/******************************************************************\
*  tile.c -- game editor source code                               *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "editdefs.h"
/********************** activate_tile_editor **********************/
void activate_tile_editor()
{
   register int i;
   int grid_x,grid_y;
   unsigned char key,aux;
   int color;
   static char menu_key[] =
               {'g','p','c','h','v','r','t','f','u','i','s','q'};
   static int ybox[] = {44,54,64,74, 94,104,114,124};

   /* initialize & draw the tile editor screen */
   fg_mousevis(OFF);
   fg_setpage(0);
   draw_tile_editor();
   get_attributes(tilenum);
   set_attributes();
   set_foreground_color(foreground_color);
   set_background_color(background_color);

   /* main tile editor control loop */
   for(;;)
   {
      /* read a keystroke */
      fg_mousevis(ON);
      fg_waitfor(1);
      fg_intkey(&key,&aux);

      /* no key press detected, any mouse buttons pressed? */
      if (key+aux == 0)
      {
         /* mouse button, held down */
         fg_mousepos(&xmouse,&ymouse,&buttons);

         /* left button pressed */
         if (buttons == 1)
         {
            /* on grid -- update foreground color */
            if (BETWEEN(xmouse,24,151) && BETWEEN(ymouse,40,135))
            {
               /* first, save 'undo' information */
               update_old();

               /* continue updating grid until button released */
               while (buttons == 1 && BETWEEN(xmouse,24,151) &&
                                      BETWEEN(ymouse,40,135))
               {
                  grid_x = (xmouse - 24) / 8;
                  grid_y = (ymouse - 40) /6;
                  this_tile[grid_x][grid_y] = (unsigned char)foreground_color;
                  set_grid(grid_x,grid_y,foreground_color);
                  update_tiles();

                  fg_mousevis(ON);
                  fg_waitfor(1);
                  fg_mousepos(&xmouse,&ymouse,&buttons);
               }
            }

            /* change the foreground color */
            else if (BETWEEN(xmouse,290,316) &&
                     BETWEEN(ymouse,25,187))
            {
               fg_mousevis(OFF);
               color = fg_getpixel(xmouse,ymouse);
               set_foreground_color(color);
               fg_waitfor(3);
            }

            /* activate a menu item (map to key press) */
            if (BETWEEN(xmouse,238,279) && BETWEEN(ymouse,40,164))
            {
               i = (ymouse - 44)/10;
               key = menu_key[i];
               fg_waitfor(3);
            }

            /* update attributes: top, bottom, left, right, etc */
            if (BETWEEN(xmouse,164,172) && BETWEEN(ymouse,44,140))
            {
               for (i = 0; i < 8; i++)
               {
                  if (BETWEEN(ymouse,ybox[i],ybox[i]+6))
                  {
                     aux = (char)(59+i);
                     fg_waitfor(3);
                     break;
                  }
               }
            }
         }

         /* right mouse button pressed */
         else if (buttons == 2)
         {
            if (BETWEEN(xmouse,24,150) &&  BETWEEN(ymouse,40,135))
            {
               /* save 'undo' information */
               update_old();

               /* continue updating grid until button released */
               while (buttons == 2 && BETWEEN(xmouse,24,150) &&
                                   BETWEEN(ymouse,40,135))
               {
                  grid_x = (xmouse - 24) / 8;
                  grid_y = (ymouse - 40) /6;
                  this_tile[grid_x][grid_y] = (unsigned char)background_color;
                  set_grid(grid_x,grid_y,background_color);
                  update_tiles();

                  fg_mousevis(ON);
                  fg_waitfor(1);
                  fg_mousepos(&xmouse,&ymouse,&buttons);
               }
            }
            /* change the background color */
            else if (BETWEEN(xmouse,290,316) &&
                     BETWEEN(ymouse,25,187))
            {
               fg_mousevis(OFF);
               color = fg_getpixel(xmouse,ymouse);
               set_background_color(color);
               fg_waitfor(3);
            }
         }
      }

      /* change any upper case keys to lower case */
      if (isupper(key))
         key += 32;

      /* process the key press, if any */
      if (key == ESC || key == 'q')
      {
         if (foreground_changed || background_changed)
            save_tiles();
         foreground_changed = FALSE;
         background_changed = FALSE;
         return;
      }
      else if (key == 'g')
         get_tile();
      else if (key == 'c')
         clear_tile();
      else if (key == 'h')
         horizontal_flip();
      else if (key == 'v')
         vertical_flip();
      else if (key == 'r')
         rotate_tile();
      else if (key == 't')
         transpose_tile_colors();
      else if (key == 'f')
         fill_tile();
      else if (key == 'i')
         import_tiles();
      else if (key == 'u')
         undo_tiles();
      else if (key == 's')
         save_tiles();
      else if (key == 'p')
         tile_put();
      else if (aux >= 59 && aux <= 66)
         set_attribute(aux-59);
   }
}
/******************************************************************/
void clear_tile()
{
   register int i,j;

   /* update undo information */
   update_old();

   for(i = 0; i < 16; i++)
   {
      for(j = 0; j < 16; j++)
      {
         this_tile[i][j] = (unsigned char)background_color;

         /* for speed reasons, draw the grid only if changed */
         if (old_tile[i][j] != this_tile[i][j])
            set_grid(i,j,background_color);
      }
   }
   update_tiles();
}
/******************************************************************/
int do_background()
{
   /* edit background tiles, then return to main menu */

   tile_type = BACKGROUND;
   activate_tile_editor();
   draw_screen();
   return(OK);
}
/******************************************************************/
int do_foreground()
{
   /* edit foreground tiles, then return to main menu */

   tile_type = FOREGROUND;
   activate_tile_editor();
   draw_screen();
   return(OK);
}
/******************************************************************/
void draw_this_tile()
{
   register int i,j;
   int color;

   /* update all the squares on the grid (fat bit editor) */
   for(i = 0; i < 16; i++)
   {
      for(j = 0; j < 16; j++)
      {
         color = (int)this_tile[i][j];
         set_grid(i,j,color);
      }
   }
   update_tiles();
}
/******************************************************************/
void draw_tile_editor()
{
   int x,y;
   int x1,x2,y1,y2;
   register int i;
   char numstring[4];

   static char *string[] = {
      "Get",
      "Put",
      "Clear",
      "Hflip",
      "Vflip",
      "Rot",
      "Trans",
      "Fill",
      "Undo",
      "Import",
      "Save",
      "Quit"
   };

   static char *string1[] = {
      "Top",
      "Bottom",
      "Left",
      "Right"
   };

   static char *string2[] = {
      "Bit 4",
      "Bit 5",
      "Bit 6",
      "Bit 7"
   };

   char temp_string[2];

   /* clear work area */
   fg_setcolor(blue);
   fg_rect(0,319,25,199);
   fg_setcolor(black);
   fg_rect(0,xlimit,menu_bottom,menu_bottom);

   /* grid */
   x1 = 24; x2 = 152;
   y1 = 40; y2 = 136;

   fg_setcolor(grey);
   for (x = x1; x <= x2; x+= 8)
   {
      fg_move(x,y1);
      fg_draw(x,y2);
   }
   for (y = y1; y <= y2; y+= 6)
   {
      fg_move(x1,y);
      fg_draw(x2,y);
   }

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

   /* Get, put, clear, hflip,... */
   x = 242; y = 50;

   fg_setcolor(white);
   fg_rect(238,279,40,164);
   fg_setcolor(black);
   fg_box(238,279,40,164);

   temp_string[1] = '\0';

   for (i = 0; i < 12; i++)
   {
      fg_setcolor(black);
      put_string(string[i],x,y);
      temp_string[0] = string[i][0];
      fg_setcolor(blue);
      put_string(temp_string,x,y);
      y+=10;
   }

   /* top, bottom, left, right */
   x1 = 164; x2 = 172;
   y = 50;

   fg_setcolor(white);
   fg_rect(158,220,40,84);
   fg_setcolor(black);
   fg_box(158,220,40,84);

   for (i = 0; i < 4; i++)
   {
      fg_setcolor(black);
      fg_box(x1,x2,y-6,y);
      put_string(string1[i],180,y);
      y+=10;
   }

   /* four, five, six, seven */
   x1 = 164; x2 = 172;
   y = 100;

   fg_setcolor(white);
   fg_rect(158,220,90,134);
   fg_setcolor(black);
   fg_box(158,220,90,134);

   for (i = 0; i < 4; i++)
   {
      fg_setcolor(black);
      fg_box(x1,x2,y-6,y);
      put_string(string2[i],180,y);
      y+=10;
   }

   /* foreground, background colors */
   fg_setcolor(grey);
   fg_box(120,136,140,155);
   fg_box(136,152,140,155);

   /* single example tile box */
   fg_setcolor(black);
   fg_rect(80,95,140,155);

   /* multiple example tile boxes */
   fg_rect(24,71,140,187);

   /* bottom status bar */
   fg_setcolor(white);
   fg_rect(0,319,189,199);
   fg_setcolor(black);

   if (tile_type == FOREGROUND)
      put_string("foreground", 6,197);
   else
      put_string("background", 6,197);

   itoa(tilenum,numstring,10);
   put_string(numstring,290,197);

   fg_setcolor(black);
   fg_rect(0,319,189,189);
   draw_this_tile();

   fg_setpage(2);
   fg_setcolor(white);
   put_string("foreground",4,7);
   fg_setpage(0);
}
/******************************************************************/
void fill_tile()
{
   register int i,j;
   int x,y;
   int grid_x,grid_y;
   int count;
   int color;
   unsigned char key,aux;

   /* put a message on the status bar */
   fg_mousevis(OFF);
   fg_setcolor(black);
   put_string("Fill",80,197);

   /* clear the mouse buttons */
   fg_waitfor(5);
   fg_mousebut(1,&count,&xmouse,&ymouse);
   fg_mousebut(2,&count,&xmouse,&ymouse);

   for(;;)
   {
      fg_waitfor(1);

      /* escape key pressed? */
      fg_intkey(&key,&aux);
      if (key == ESC)
         break;

      /* left mouse button fills with foreground color */
      fg_mousevis(ON);
      fg_mousebut(1,&count,&xmouse,&ymouse);
      if (count > 0)
      {
         /* clicked on grid? */
         if (BETWEEN(xmouse,24,152) && BETWEEN(ymouse,40,136))
         {
            /* calculate grid position */
            grid_x = (xmouse - 24) /8;
            grid_y = (ymouse - 40) /6;

            /* translate to corresponding pixel on tile area */
            x = grid_x + 80;
            y = grid_y + 140;
            fg_mousevis(OFF);

            /* check if we are filling to the background color */
            if (fg_getpixel(x,y) == blue)
            {
               /* make sure we don't overflow the flood fill! */
               fg_setcolor(black);
               fg_box(79,96,139,156);
            }

            /* fill the small tile area */
            fg_setcolor(foreground_color);
            fg_paint(x,y);

            /* replace the outline */
            fg_setcolor(blue);
            fg_box(79,96,139,156);

            /* copy to fat bit grid */
            for (i = 0; i < 16; i++)
            {
               for (j = 0; j < 16; j++)
               {
                  old_tile[i][j] = this_tile[i][j];
                  x = 80+i;
                  y = 140+j;
                  color = fg_getpixel(x,y);
                  this_tile[i][j] = (unsigned char)color;
                  set_grid(i,j,color);
               }
            }
            update_tiles();
         }

         /* clicked mouse outside of grid -- exit fill function */
         else
            break;
      }

      /* right mouse button fills with background color */
      fg_mousevis(ON);
      fg_mousebut(2,&count,&xmouse,&ymouse);
      if (count > 0)
      {
         /* clicked on grid? */
         if (BETWEEN(xmouse,24,152) && BETWEEN(ymouse,40,136))
         {
            /* calculate grid position */
            grid_x = (xmouse - 24) / 8;
            grid_y = (ymouse - 40) /6;

            /* translate to corresponding pixel on tile area */
            x = grid_x + 80;
            y = grid_y + 140;
            fg_mousevis(OFF);

            /* check if we are filling to the background color */
            if (fg_getpixel(x,y) == blue)
            {
               fg_setcolor(black);
               fg_box(79,96,139,156);
            }

            /* fill the small tile area */
            fg_setcolor(background_color);
            fg_paint(x,y);

            /* replace the outline */
            fg_setcolor(blue);
            fg_box(79,96,139,156);

            /* copy to fat bit grid */
            for (i = 0; i < 16; i++)
            {
               for (j = 0; j < 16; j++)
               {
                  old_tile[i][j] = this_tile[i][j];
                  x = 80+i;
                  y = 140+j;
                  color = fg_getpixel(x,y);
                  this_tile[i][j] = (unsigned char)color;
                  set_grid(i,j,color);
               }
            }
            update_tiles();
         }

         /* clicked mouse outside of grid -- exit fill function */
         else
            break;
      }
   }

   /* clear the status bar */
   fg_mousevis(OFF);
   fg_setcolor(white);
   fg_rect(80,104,190,199);
}
/******************************************************************/
void get_attributes(int tile_num)
{
   register int i;

   for (i = 0; i < 8; i++)
      attribute[i] = test_bit(tile_num,i);
}
/******************************************************************/
void get_tile()
{
   register int i,j;
   int xbox,ybox;
   int x,y;
   int color;
   int oldx,oldy;
   int old_xmouse,old_ymouse;
   int count;
   unsigned char key,aux;
   int tile_num;
   char string[4];
   int page_no;
   int skip;

   if (tile_type == FOREGROUND)
      page_no = 2;
   else
      page_no = 3;

   fg_mousevis(OFF);
   fg_setpage(page_no);
   fg_setvpage(page_no);
   fg_copypage(page_no,1);

   fg_waitfor(3);
   fg_mousepos(&xmouse,&ymouse,&buttons);
   old_xmouse = xmouse;
   old_ymouse = ymouse;

   if (tile_type == FOREGROUND)
   {
      fg_mouselim(0,63,0,111);
      xmouse = fore_xmouse;
      ymouse = fore_ymouse;
   }
   else
   {
      fg_mouselim(0,319,0,183);
      xmouse = back_xmouse;
      ymouse = back_ymouse;
   }

   fg_mousemov(xmouse,ymouse);

   xbox = xmouse&0xfff0;
   ybox = (ymouse&0xfff0)+8;
   oldx = xbox;
   oldy = ybox;

   if (page_no == 2)
   {
      if (xbox < 32)
         tile_num = (ybox/16) * 2 + (xbox/16);
      else
         tile_num = (ybox/16) * 2 + (xbox/16) + 12;
   }
   else
      tile_num = (ybox/16) * 20 + (xbox/16);

   fg_boxx(xbox,xbox+15,ybox, ybox+15);

   skip = FALSE;
   tile_num = tilenum;
   for(;;)
   {
      fg_waitfor(1);
      fg_intkey(&key,&aux);
      if (key == ESC)
      {
         skip = TRUE;
         break;
      }

      /* toggle between background & foreground */
      else if (key == SPACE)
      {
         fg_transfer(oldx,oldx+15,oldy,oldy+15, oldx,oldy+15, 1,page_no);

         if (page_no == 2)
         {
            page_no = 3;
            fg_mouselim(0,319,0,183);
         }
         else
         {
            page_no = 2;
            fg_mouselim(0,63,0,111);
         }
         fg_setpage(page_no);
         fg_setvpage(page_no);
         fg_copypage(page_no,1);
      }

      fg_mousepos(&xmouse,&ymouse,&buttons);
      xbox = xmouse&0xfff0;
      ybox = (ymouse&0xfff0)+8;

      if (xbox != oldx || ybox != oldy)
      {
         fg_transfer(oldx,oldx+15,oldy,oldy+15, oldx,oldy+15, 1,page_no);
         fg_setcolor(white);
         fg_boxx(xbox,xbox+15,ybox, ybox+15);
         oldx = xbox;
         oldy = ybox;

         if (page_no == 2)
         {
            if (xbox < 32)
               tile_num = (ybox/16) * 2 + (xbox/16);
            else
               tile_num = (ybox/16) * 2 + (xbox/16) + 12;
         }
         else
            tile_num = (ybox/16) * 20 + (xbox/16);

         fg_setcolor(black);
         fg_rect(297,319,0,7);
         fg_setcolor(white);
         sprintf(string,"%d",tile_num);
         put_string(string,297,7);
      }

      if (buttons == 2)
      {
         break;
      }
   }

   /* clear the square cursor */
   fg_transfer(oldx,oldx+15,oldy,oldy+15, oldx,oldy+15, 1,page_no);

   if (!skip)
   {
      tilenum = tile_num;
      get_attributes(tile_num);

      /* copy the proper tile to page 0 */
      fg_transfer(xbox,xbox+15,ybox,ybox+15,80,155,1,0);
   }

   fg_setpage(0);

   if (page_no == 2)
   {
      fore_xmouse = xmouse;
      fore_ymouse = ymouse;
   }
   else
   {
      back_xmouse = xmouse;
      back_ymouse = ymouse;
   }

   xmouse = old_xmouse;
   ymouse = old_ymouse;
   fg_mouselim(0,319,0,199);
   fg_mousemov(xmouse,ymouse);

   /* clear the mouse buffer */
   fg_mousebut(1,&count,&xmouse,&ymouse);
   fg_mousebut(2,&count,&xmouse,&ymouse);

   if (!skip)
   {
      for (i = 0; i < 16; i++)
      {
         for (j = 0; j < 16; j++)
         {
            old_tile[i][j] = this_tile[i][j];
            x = 80+i;
            y = 140+j;
            color = fg_getpixel(x,y);
            this_tile[i][j] = (unsigned char)color;
            set_grid(i,j,color);
         }
      }
      draw_this_tile();
      set_attributes();

      /* display the tile number */
      fg_setcolor(white);
      fg_rect(290,319,191,197);
      fg_setcolor(black);
      sprintf(string,"%d",tile_num);
      put_string(string,290,197);
   }
   fg_setvpage(0);
   fg_waitfor(2);
}
/******************************************************************/
void horizontal_flip()
{
   unsigned char temp_grid[16][16];
   register int i,j;

   for(j = 0; j < 16; j++)
   {
      for(i = 0; i < 16; i++)
      {
         old_tile[i][j] = this_tile[i][j];
         temp_grid[i][j] = this_tile[15-i][j];
      }
   }

   for(i = 0; i < 16; i++)
   {
      for(j = 0; j < 16; j++)
      {
         this_tile[i][j] = temp_grid[i][j];
      }
   }

   draw_this_tile();
}
/******************************************************************/
void import_tiles()
{
   unsigned char key,aux;
   char fname[13];
   int error;
   char *strptr;
   int index;
   int buttons,count;
   int old_xmouse,old_ymouse;
   int corner_x,corner_y;
   int xbox,ybox,old_xbox,old_ybox;
   int dx,dy;
   int skip;
   int x2,y2,y3;

   skip = FALSE;
   fg_mousevis(OFF);
   fg_setcolor(black);
   put_string("PCX file name:",80,197);
   put_string(tile_import_fname,170,197);

   fg_getkey(&key,&aux);
   if (key == CR)
      strcpy(fname,tile_import_fname);
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
      else if ((strcmpi(&fname[index],".pcx") == 0) || fname[index+1] == '\0')
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
      strcpy(tile_import_fname,fname);
      fg_setpage(1);
      fg_move(0,0);
      fg_showpcx(fname,0);
      fix_palettes(0);
      fg_setvpage(1);

      fg_mouselim(0,304,0,191);
      fg_mousepos(&xmouse,&ymouse,&buttons);
      old_xmouse = xmouse;
      old_ymouse = ymouse;

      fg_setcolor(white);

      fg_move(0,ymouse);
      fg_drawx(319,ymouse);
      fg_move(xmouse,0);
      fg_drawx(xmouse,199);

      /* move crosshairs around */
      while(buttons == 0)
      {
         fg_waitfor(1);

         fg_mousepos(&xmouse,&ymouse,&buttons);
         xmouse = (xmouse/16)*16;
         ymouse = (ymouse/8)*8;

         if (xmouse != old_xmouse || ymouse != old_ymouse)
         {
            fg_move(0,old_ymouse);
            fg_drawx(319,old_ymouse);
            fg_move(old_xmouse,0);
            fg_drawx(old_xmouse,199);

            fg_move(0,ymouse);
            fg_drawx(319,ymouse);
            fg_move(xmouse,0);
            fg_drawx(xmouse,199);

            old_xmouse = xmouse;
            old_ymouse = ymouse;
         }

         fg_intkey(&key,&aux);
         if (key == ESC)
         {
            skip = TRUE;
            break;
         }
      }
      fg_move(0,ymouse);
      fg_drawx(319,ymouse);
      fg_move(xmouse,0);
      fg_drawx(xmouse,199);

      /* return -- no import */
      if (skip)
      {
         fg_setpage(0);
         fg_setvpage(0);

         fg_mouselim(0,319,0,199);
         fg_setfunc(0);
         fg_setcolor(white);
         fg_rect(80,289,190,199);

         fg_waitfor(3);
         fg_mousebut(1,&count,&xmouse,&ymouse);
         fg_mousebut(2,&count,&xmouse,&ymouse);
         return;
      }

      /* first button is pressed, now enlarge the clip box */
      corner_x = xmouse;
      corner_y = ymouse;

      y2 = MIN(191,ymouse+111);
      if (tile_type == FOREGROUND)
         fg_mouselim(xmouse+1,xmouse+63,ymouse+1,y2);
      else
         fg_mouselim(xmouse+1,311,ymouse+1,191);

      dx = xmouse - ((xmouse/16)*16);
      dy = ymouse - ((ymouse/8)*8);

      xbox = (xmouse/16)*16+15+dx;
      ybox = (ymouse/8)*8+15+dy;

      old_xbox = xbox;
      old_ybox = ybox;

      fg_boxx(corner_x,xbox,corner_y,ybox);

      /* until the button is released */
      while(buttons > 0)
      {
         fg_waitfor(1);

         fg_mousepos(&xmouse,&ymouse,&buttons);

         xbox = (xmouse/16)*16+15+dx;
         ybox = (ymouse/8)*8+15+dy;

         if (xbox != old_xbox || ybox != old_ybox)
         {
            fg_boxx(corner_x,old_xbox,corner_y,old_ybox);
            fg_boxx(corner_x,xbox,corner_y,ybox);

            old_xbox = xbox;
            old_ybox = ybox;
         }

         fg_intkey(&key,&aux);
         if (key == ESC)
         {
            skip = TRUE;
            break;
         }
      }

      /* clear the crosshairs */
      fg_boxx(corner_x,xbox,corner_y,ybox);

      /* return with no import */
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

      dx = xbox - corner_x;
      dy = MIN(191,ybox - corner_y);

      /* put the import area on the foreground or background page */
      fg_mousebut(1,&count,&xmouse,&ymouse);
      if (tile_type == FOREGROUND)
      {
         fg_setpage(2);
         fg_setvpage(2);
         fg_mouselim(0,63,8,111);
      }
      else
      {
         fg_setpage(3);
         fg_setvpage(3);
         fg_mouselim(0,311,8,195);
      }

      fg_mousemov(0,8);
      fg_waitfor(1);
      fg_mousepos(&xmouse,&ymouse,&buttons);

      xbox = (xmouse/16)*16;
      ybox = (ymouse/8)*8;
      fg_boxx(xbox,xbox+dx,ybox,ybox+dy);

      old_xbox = xbox;
      old_ybox = ybox;

      /* move around looking for the right area */
      while(buttons == 0)
      {
         fg_waitfor(1);

         fg_mousepos(&xmouse,&ymouse,&buttons);
         if ((xmouse+dx < 334) && (ymouse + dy < 206))
         {
            xbox = (xmouse/16)*16;
            ybox = (ymouse/8)*8;

            if (xbox != old_xbox || ybox != old_ybox)
            {
               fg_boxx(old_xbox,old_xbox+dx,old_ybox,old_ybox+dy);
               fg_boxx(xbox,xbox+dx,ybox,ybox+dy);
               old_xbox = xbox;
               old_ybox = ybox;
            }
         }
         else
         {
            if (xmouse+dx > 334)
               xmouse = 319 - dx;
            if (ymouse+dy > 206)
               ymouse = 206 - dy;
            fg_mousemov(xmouse,ymouse);
         }

         fg_intkey(&key,&aux);
         if (key == ESC)
         {
            skip = TRUE;
            break;
         }
         fg_mousebut(1,&count,&xmouse,&ymouse);
         if (count > 0)
         {
             x2 = corner_x+dx;
             y2 = MIN(corner_y+dy,199);
             y3 = MIN(ybox+dy,199);
             fg_boxx(xbox,xbox+dx,ybox,ybox+dy);
             if (tile_type == FOREGROUND)
                fg_transfer(corner_x,x2,corner_y,y2,xbox,y3,1,2);
             else
                fg_transfer(corner_x,x2,corner_y,y2,xbox,y3,1,3);
             break;
         }
      }

      /* last chance to skip the whole thing */
      if (skip)
         fg_boxx(xbox,xbox+dx,ybox,ybox+dy);

      fg_setpage(0);
      fg_setvpage(0);
   }

   if (tile_type == FOREGROUND)
      foreground_changed = TRUE;
   else
      background_changed = TRUE;

   fg_mouselim(0,319,0,199);
   fg_setcolor(white);
   fg_rect(80,289,190,199);

   fg_waitfor(3);
   fg_mousebut(1,&count,&xmouse,&ymouse);
   fg_mousebut(2,&count,&xmouse,&ymouse);
}
/******************************************************************/
void init_tiles()
{
   fore_xmouse  = 0;
   fore_ymouse  = 0;
   foreground_color = white;
   background_color = black;
   tilenum = 0;
   strcpy(tile_import_fname,foreground_fname);
   foreground_changed = FALSE;

   memset(attribute,0,8);
   if ((tstream = fopen(foreattr_fname,"rb")) != NULL)
   {
      fread(foreground_attributes,sizeof(char),28,tstream);
      fclose(tstream);
   }
   else
      memset(foreground_attributes,0,28);

   if ((tstream = fopen(backattr_fname,"rb")) != NULL)
   {
      fread(background_attributes,sizeof(char),240,tstream);
      fclose(tstream);
   }
   else
      memset(background_attributes,0,240);

   memset(old_tile,foreground_color,16*16);
   memset(this_tile,background_color,16*16);

   fg_setpage(2);
   fg_move(0,8);
   fg_showpcx(foreground_fname,1);
   fg_setcolor(black);
   fg_rect(0,319,0,7);
   fg_setcolor(white);
   put_string("foreground",4,7);
   put_string("0",297,7);

   fg_setpage(3);
   fg_move(0,8);
   fg_showpcx(background_fname,0);
   fix_palettes(0);
   fg_setcolor(black);
   fg_rect(0,319,0,7);
   fg_setcolor(white);
   put_string("background",4,7);
   put_string("0",297,7);

   fg_setpage(0);
   fg_setvpage(0);
}
/******************************************************************/
void rotate_tile()
{
   unsigned char temp_grid[16][16];
   register int i,j;

   for(j = 0; j < 16; j++)
   {
      for(i = 0; i < 16; i++)
      {
         old_tile[i][j] = this_tile[i][j];
         temp_grid[i][j] = this_tile[15-j][i];
      }
   }

   for(i = 0; i < 16; i++)
   {
      for(j = 0; j < 16; j++)
      {
         this_tile[i][j] = temp_grid[i][j];
      }
   }

   draw_this_tile();
}
/******************************************************************/
void save_tiles()
{
   unsigned char key,aux;
   char fname[13];
   char string[80];
   int error;
   char *strptr;
   int index;

   if (tile_type == FOREGROUND)
      strcpy(fname,foreground_fname);
   else
      strcpy(fname,background_fname);

   fg_mousevis(OFF);
   fg_setcolor(black);
   put_string("save in PCX file:",72,197);
   put_string(fname,180,197);

   fg_getkey(&key,&aux);
   if (key != CR)
   {
      if (get_string(fname,180,197,12,key,0) == ESC)
      {
         fg_setpage(0);
         fg_setcolor(white);
         fg_rect(72,289,190,199);
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
         strcat(fname,"pcx");
      }
   }

   /* no period in string */
   else
   {
      index = strlen(fname);
      if (index > 8)
         error = TRUE;
      if (!error)
         strcat(fname,".pcx");
   }

   if (!error)
   {
      if (file_exists(fname))
      {
         fg_setcolor(white);
         fg_rect(72,289,190,199);
         fg_setcolor(black);
         sprintf (string,"%s exists. Overwrite it?",fname);
         put_string(string,72,197);
         fg_getkey(&key,&aux);

         if ((key|32) == 'y')
            error = FALSE;
         else
            error = TRUE;
      }
   }

   if (!error)
   {
      if (tile_type == FOREGROUND)
      {
         strcpy(foreground_fname,fname);
         fg_setpage(2);
         foreground_changed = FALSE;
         fg_makepcx (0,63,8,119,fname);
      }
      else
      {
         fg_setpage(3);
         strcpy(background_fname,fname);
         background_changed = FALSE;
         fg_makepcx (0,319,8,199,fname);
      }

      fname[index+1] = '\0';
      strcat(fname,"att");
      if ((tstream = fopen(fname,"wb")) != NULL)
      {
         if (tile_type == FOREGROUND)
         {
            strcpy(foreattr_fname,fname);
            fwrite(foreground_attributes,sizeof(char),28,tstream);
         }
         else
         {
            strcpy(backattr_fname,fname);
            fwrite(background_attributes,sizeof(char),240,tstream);
         }
         fclose(tstream);
      }
   }

   fg_setpage(0);
   fg_setcolor(white);
   fg_rect(72,289,190,199);
}
/******************************************************************/
void set_attribute(int num)
{
   static int y[] = {45,55,65,75, 95,105,115,125};

   fg_mousevis(OFF);

   attribute[num] = !attribute[num];

   if (attribute[num])
      fg_setcolor(grey);
   else
      fg_setcolor(white);

   fg_rect(165,171,y[num],y[num]+4);
}
/******************************************************************/
void set_attributes()
{
   register int i;
   static int y[] = {45,55,65,75, 95,105,115,125};

   for (i = 0; i < 8; i++)
   {
      if (attribute[i])
         fg_setcolor(grey);
      else
         fg_setcolor(white);

      fg_rect(165,171,y[i],y[i]+4);
   }
}
/******************************************************************/
void set_background_color(int color)
{
   fg_mousevis(OFF);
   background_color = color;
   fg_setcolor(background_color);
   fg_rect(137,151,141,154);
}
/******************************************************************/
void set_bit(int tile_num,int bit,int value)
{
   unsigned int item;

   if (tile_type == FOREGROUND)
   {
      item = (unsigned int)foreground_attributes[tile_num];
      item = (_rotr(item,bit) & 0xFFFE) | (unsigned int)value;
      foreground_attributes[tile_num] = (char)_rotl(item,bit);
   }
   else
   {
      item = (unsigned int)background_attributes[tile_num];
      item = (_rotr(item,bit) & 0xFFFE) | (unsigned int)value;
      background_attributes[tile_num] = (char)_rotl(item,bit);
   }
}
/******************************************************************/
void set_foreground_color(int color)
{
   fg_mousevis(OFF);
   foreground_color = color;
   fg_setcolor(foreground_color);
   fg_rect(121,135,141,154);
}
/******************************************************************/
void set_grid(int i,int j,int color)
{
   /* fat bit editor: draw a tiny little rectangle on the grid */

   register int x,y;

   fg_mousevis(OFF);
   x = (i * 8) + 24;
   y = (j * 6) + 40;

   fg_setcolor(color);
   fg_rect(x+1,x+7,y+1,y+5);

   /* also update the tile */
   fg_point(80+i,140+j);

   /* foreground blocks: highlight the transparent color */
   if (tile_type == FOREGROUND && color == 0)
   {
      fg_setcolor(grey);
      fg_box(x+2,x+6,y+2,y+4);
   }
}
/******************************************************************/
int test_bit(int tile_num,int bit)
{
   if (tile_type == FOREGROUND)
      return((_rotr(foreground_attributes[tile_num],bit)) & 1);
   else
      return((_rotr(background_attributes[tile_num],bit)) & 1);
}
/******************************************************************/
void tile_put()
{
   /* "put" the currently edited tile on the tile page, saving it */

   int xbox,ybox;
   int oldx,oldy;
   int old_xmouse,old_ymouse;
   int count;
   unsigned char key,aux;
   int tile_num;
   char string[4];
   int skip;
   int pageno;

   /* which page we use depends on what kind of tile it is */
   if (tile_type == FOREGROUND)
   {
      pageno = 2;
      fg_mouselim(0,63,0,111);
   }
   else
   {
      pageno = 3;
      fg_mouselim(0,319,0,191);
   }

   /* set the page and make a copy of it on page 1 */
   fg_mousevis(OFF);
   fg_setpage(pageno);
   fg_setvpage(pageno);
   fg_copypage(pageno,1);

   /* give us time to get our finger off the mouse */
   fg_waitfor(3);

   /* where is the mouse now? */
   fg_mousepos(&xmouse,&ymouse,&buttons);
   old_xmouse = xmouse;
   old_ymouse = ymouse;

   /* move to where the mouse was the last time we were on this page */
   if (tile_type == BACKGROUND)
   {
      xmouse = back_xmouse;
      ymouse = back_ymouse;
   }
   else
   {
      xmouse = fore_xmouse;
      ymouse = fore_ymouse;
   }

   fg_mousemov(xmouse,ymouse);

   xbox = xmouse&0xfff0;
   ybox = (ymouse&0xfff0)+8;
   oldx = xbox;
   oldy = ybox;
   if (tile_type == FOREGROUND)
   {
      if (xbox < 32)
         tile_num = (ybox/16) * 2 + (xbox/16);
      else
         tile_num = (ybox/16) * 2 + (xbox/16) + 12;
   }
   else
      tile_num = (ybox/16) * 20 + (xbox/16);

   fg_setcolor(white);
   fg_boxx(xbox,xbox+15,ybox, ybox+15);

   skip = FALSE;
   for(;;)
   {
      fg_waitfor(1);
      fg_intkey(&key,&aux);
      if (key == ESC)
      {
         skip = TRUE;
         break;
      }
      fg_mousepos(&xmouse,&ymouse,&buttons);
      xbox = xmouse&0xfff0;
      ybox = (ymouse&0xfff0)+8;

      if (xbox != oldx || ybox != oldy)
      {
         fg_transfer(oldx,oldx+15,oldy,oldy+15, oldx,oldy+15, 1,pageno);
         fg_setcolor(white);
         fg_boxx(xbox,xbox+15,ybox, ybox+15);
         oldx = xbox;
         oldy = ybox;

         if (tile_type == FOREGROUND)
         {
            if (xbox < 32)
               tile_num = (ybox/16) * 2 + (xbox/16);
            else
               tile_num = (ybox/16) * 2 + (xbox/16) + 12;
         }
         else
            tile_num = (ybox/16) * 20 + (xbox/16);

         fg_setcolor(black);
         fg_rect(297,319,0,7);
         fg_setcolor(white);
         sprintf(string,"%d",tile_num);
         put_string(string,297,7);
      }

      if (buttons == 1)
      {
         fg_transfer(80,95,140,155, xbox,ybox+15,0,pageno);
         break;
      }
   }

   if (!skip)
   {
      update_attributes(tile_num);
      if (tile_type == FOREGROUND)
         foreground_changed = TRUE;
      else
         background_changed = TRUE;
   }
   fg_setpage(0);

   fore_xmouse = xmouse;
   fore_ymouse = ymouse;

   xmouse = old_xmouse;
   ymouse = old_ymouse;
   fg_mouselim(0,319,0,199);
   fg_mousemov(xmouse,ymouse);

   /* clear the mouse buffer */
   fg_mousebut(1,&count,&xmouse,&ymouse);
   fg_mousebut(2,&count,&xmouse,&ymouse);

   fg_setvpage(0);
   fg_waitfor(2);
}
/******************************************************************/
void transpose_tile_colors()
{
   register int i,j;

   for(i = 0; i < 16; i++)
   {
      for(j = 0; j < 16; j++)
      {
         old_tile[i][j] = this_tile[i][j];
         if (this_tile[i][j] == (unsigned char)background_color)
         {
            this_tile[i][j] = (unsigned char)foreground_color;
            set_grid(i,j,foreground_color);
         }
      }
   }

   update_tiles();
}
/******************************************************************/
void undo_tiles()
{
   register int i,j;
   unsigned char temp_grid;

   for(j = 0; j < 16; j++)
   {
      for(i = 0; i < 16; i++)
      {
         temp_grid = this_tile[i][j];
         this_tile[i][j] = old_tile[i][j];
         old_tile[i][j] = temp_grid;
      }
   }

   draw_this_tile();
}
/******************************************************************/
void update_attributes(int tile_num)
{
   register int i;

   for (i = 0; i < 8; i++)
      set_bit(tile_num,i,attribute[i]);
}
/******************************************************************/
void update_old()
{
   memcpy(old_tile,this_tile,16*16);
}
/******************************************************************/
void update_tiles()
{
   /* multiple tile display area (9 tiles in 3x3 grid */

   fg_transfer(80,95,140,155, 24,155, 0,0);
   fg_transfer(80,95,140,155, 40,155, 0,0);
   fg_transfer(80,95,140,155, 56,155, 0,0);

   fg_transfer(80,95,140,155, 24,171, 0,0);
   fg_transfer(80,95,140,155, 40,171, 0,0);
   fg_transfer(80,95,140,155, 56,171, 0,0);

   fg_transfer(80,95,140,155, 24,187, 0,0);
   fg_transfer(80,95,140,155, 40,187, 0,0);
   fg_transfer(80,95,140,155, 56,187, 0,0);
}
/******************************************************************/
void vertical_flip()
{
   unsigned char temp_grid[16][16];
   register int i,j;

   for(j = 0; j < 16; j++)
   {
      for(i = 0; i < 16; i++)
      {
         old_tile[i][j] = this_tile[i][j];
         temp_grid[i][j] = this_tile[i][15-j];
      }
   }
   memcpy(this_tile,temp_grid,16*16);
   draw_this_tile();
}
