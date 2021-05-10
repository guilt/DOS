/******************************************************************\
*  menu.c -- game editor source code                               *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "editdefs.h"

int (*menu_func)(void);
int selection = 0;
CMD main_menu[] =
{
   {submenu1, "FILE",       2,  76},
   {submenu2, "LEVEL",     80, 156},
   {submenu3, "TILES",    160, 236},
   {submenu4, "SPRITES",  240, 316}
};

CMD menu1[] =
{
   {load_game_file,  "load/save", 2,  76},
   {exit_program,    "Exit",      2,  76}
};

CMD menu2[] =
{
   {edit_level,      "edit",    80, 156},
   {save_level_name, "save",    80, 156}
};

CMD menu3[] =
{
   {do_background, "background",160,236},
   {do_foreground, "foreground",160,236},
   {do_ripper,     "ripper",    160,236}
};

CMD menu4[] =
{
   {edit_sprites,      "edit ",   240, 316},
   {load_edit_sprites, "load",    240, 316},
   {load_sprites,      "save",    240, 316}
};

int mouse_limits[] = {2,80,160,240,320};
/******************************************************************/
horizontal_menu(CMD *cmdtab,int n,int current)
{
   register int i;
   int c;
   int new;
   int ymin, ymax;

   if (current >= abs(n))
      return(ERR);

   ymin = menu_top;
   ymax = ymin + 10;

   fg_mousevis(OFF);
   fg_setpage(0);

   /* set up the list of options */
   if (n < 0)
   {
      for (i = 0; i < abs(n); i++)
      {
         fg_setcolor(white);
         fg_rect(cmdtab[i].x1,cmdtab[i].x2,ymin,ymax);
         fg_setcolor(black);
         center_string(cmdtab[i].menu_item,
                        cmdtab[i].x1,cmdtab[i].x2,ymax-2);
      }
      fg_save(0,319,menu_top,menu_bottom);
   }

   /* highlight the current option */
   i = current;

   fg_setcolor(black);
   fg_rect(cmdtab[i].x1,cmdtab[i].x2,ymin,ymax);
   fg_setcolor(white);
   center_string(cmdtab[i].menu_item,
                  cmdtab[i].x1,cmdtab[i].x2,ymax-2);

   /* if we're just displaying the menu options, return */
   if (n < 0) return(OK);

   flushkey();

   /* choose an option */
   new = current;
   fg_mousevis(ON);
   for(;;)
   {
      /* activate the corresponding vertical menu */
      main_option = i;

#ifdef __TURBOC__
      c = cmdtab[i].menu_func();
#else
      *menu_func = *cmdtab[i].menu_func;
      c = menu_func();
#endif

      /* cycle through the choices */
      if (c == LEFT_ARROW || c == BS)
      {
         selection = 0;
         new = i-1;
         if (new < 0) new = n-1;
      }
      else if (c == RIGHT_ARROW || c == SPACEBAR)
      {
         selection = 0;
         new = i+1;
         if (new >= n) new = 0;
      }

      /* escape exits to DOS */
      else if (c == ESC)
      {
         exit_program();
         return(i);
      }

      else
      {
         main_option = i;
         selection = 0;
         return(i);
      }

      if (i != new)
      {
         /* unmark previous option */
         fg_mousevis(OFF);
         fg_setcolor(white);
         fg_rect(cmdtab[i].x1,cmdtab[i].x2,ymin,ymax);
         fg_setcolor(black);
         center_string(cmdtab[i].menu_item,
                        cmdtab[i].x1,cmdtab[i].x2,ymax-2);

         /* mark new option */
         i = new;
         fg_setcolor(black);
         fg_rect(cmdtab[i].x1,cmdtab[i].x2,ymin,ymax);
         fg_setcolor(white);
         center_string(cmdtab[i].menu_item,
                        cmdtab[i].x1,cmdtab[i].x2,ymax-2);
         fg_mousevis(ON);
      }
   }
}
/******************************************************************/
int submenu1()
{
   return(vertical_menu(menu1,0,2));
}
int submenu2()
{
   return(vertical_menu(menu2,1,2));
}
int submenu3()
{
   return(vertical_menu(menu3,2,3));
}
int submenu4()
{
   return(vertical_menu(menu4,3,3));
}
/******************************************************************/
vertical_menu(CMD *cmdtab,int index,int n)
{
   register int i, j;
   int new;
   int height;
   int left, right;
   int string_x;
   int x1, x2, y1, y2;
   int ymin, ymax;
   int count;
   unsigned char key, aux;

   /* height in pixels of an individual menu item */
   height = 10;

   /* the first menu item determines the x coordinate for the other items */
   string_x = get_center(cmdtab[0].menu_item,cmdtab[0].x1,cmdtab[0].x2);

   /* define the menu extremes */
   x1 = cmdtab[0].x1 - 1;
   x2 = cmdtab[0].x2 + 3;
   y1 = menu_bottom+1;
   y2 = menu_bottom + n*height + 1;

   /* define the associated horizontal mouse limits */
   left  = mouse_limits[index];
   right = mouse_limits[index+1] - 2;

   /* display the vertical menu if necessary */
   fg_setpage(hidden);

   /* draw the menu outline and the shadow around it */
   fg_mousevis(OFF);
   fg_setcolor(white);
   fg_box(x1,x2-2,y1,y2-1);

   fg_setcolor(black);
   fg_box(x1,x2-2,y1,y2);

   /* set up list of options */
   ymax = menu_bottom;
   for (i = 0; i < n; i++)
   {
      ymin = ymax + 1;
      ymax = ymin + height-1;
      fg_setcolor(white);
      fg_rect(cmdtab[i].x1,cmdtab[i].x2,ymin,ymax);
      fg_setcolor(black);
      put_string(cmdtab[i].menu_item,string_x,ymax-2);
   }

   /* highlight first or previously selected option */
   i = selection;
   if (i >= n) i = 0;
   ymin = menu_bottom + i*height;
   ymax = ymin + height;
   fg_setcolor(black);
   fg_rect(cmdtab[i].x1,cmdtab[i].x2,ymin,ymax);
   fg_setcolor(white);
   put_string(cmdtab[i].menu_item,string_x,ymax-2);

   /* restore the menu to the visual page */
   fg_setpage(visual);
   fg_restore(x1,x2,y1,y2+2);
   fg_setpage(hidden);

   /* clear the hidden page under the menu */
   fg_setcolor(blue);
   fg_rect(x1,x2,y1,y2+2);

   fg_setpage(visual);
   fg_mousevis(ON);

   /* choose an option */
   new = i;
   fg_setnum(OFF);
   flushkey();

   for(;;)
   {
      /* read a keystroke */
      fg_mousevis(ON);
      fg_waitfor(1);
      fg_intkey(&key,&aux);

      /* if using a mouse, check its position */
      if (key+aux == 0)
      {
         fg_mousebut(1,&count,&xmouse,&ymouse);

         if (count > 0)
         {
            if (BETWEEN(xmouse,x1,x2) && BETWEEN(ymouse,y1,y2-2))
            {
               new = (ymouse - y1) / height;

               /* check if this is the second click of a double click */
               if (i == new)
                  key = CR;
            }
            else if (!BETWEEN(xmouse,left,right)
                      && BETWEEN(ymouse,menu_top,y1-1))
            {
               fg_mousevis(OFF);
               fg_restore(0,xlimit,menu_bottom,ylimit);
               selection = 0;
               for (j = 0; j <= ITEMS; j++)
               {
                 if (BETWEEN(xmouse,mouse_limits[j],mouse_limits[j+1]))
                    return(j);
               }
            }
            else
            {
               fg_mousevis(OFF);
               fg_restore(0,xlimit,menu_bottom,ylimit);
               selection = 0;
               return(ERR);
            }
         }
      }

      /* cycle through choices */
      if (aux == UP_ARROW || key == BS)
      {
         new = i-1;
         if (new < 0) new = n-1;
      }
      else if (aux == DOWN_ARROW || key == SPACEBAR)
      {
         new = i+1;
         if (new >= n) new = 0;
      }
      else if (aux == HOME || aux == PGUP)
         new = 0;

      else if (aux == END || aux == PGDN)
         new = n - 1;

      else if (aux == LEFT_ARROW || aux == RIGHT_ARROW)
      {
         fg_mousevis(OFF);
         fg_restore(0,xlimit,menu_bottom,ylimit);
         selection = 0;
         return((int)aux);
      }

      /* pick one choice */
      else if (key == CR)
      {
#ifdef __TURBOC__
         cmdtab[i].menu_func();
#else
         (*menu_func) = *cmdtab[i].menu_func;
         menu_func();
#endif
         wait_for_mouse_buttons();
         selection = i;
         return(index);
      }
      else if (key == ESC)
      {
         selection = 0;
         return(ESC);
      }
      else if (key+aux > 0) /* any other key */
      {
         return(ERR);
      }
      if (i != new)
      {
         /* unmark previous option */
         ymin = menu_bottom + i*height;
         ymax = ymin + height;
         fg_mousevis(OFF);
         fg_setcolor(white);
         fg_rect(cmdtab[i].x1,cmdtab[i].x2,ymin,ymax);
         fg_setcolor(black);
         put_string(cmdtab[i].menu_item,string_x,ymax-2);

         /* mark new option */
         i = new;
         ymin = menu_bottom + i*height;
         ymax = ymin + height;
         fg_setcolor(black);
         fg_rect(cmdtab[i].x1,cmdtab[i].x2,ymin,ymax);
         fg_setcolor(white);
         put_string(cmdtab[i].menu_item,string_x,ymax-2);

         /* move mouse cursor to the new option */
         fg_mousepos(&xmouse,&ymouse,&buttons);
         if (BETWEEN(xmouse,x1,x2)) fg_mousemov(xmouse,(ymin+ymax)/2);
         fg_mousevis(ON);
      }
   }
}
/******************************************************************/
void wait_for_keystroke()
{
   int buttons;
   int count;
   int x, y;
   unsigned char key, aux;

   flushkey();
   fg_mousebut(1,&count,&x,&y);
   fg_mousebut(2,&count,&x,&y);

   /* if the mouse is loaded, must loop and wait for button or keystroke */
   fg_mousevis(ON);
   for(;;)
   {
      fg_waitfor(1);
      fg_intkey(&key,&aux);
      if (key+aux > 0) break;
      fg_mousebut(1,&count,&x,&y);
      if (count > 0) break;
      fg_mousebut(2,&count,&x,&y);
      if (count > 0) break;
   }
   do
      fg_mousepos(&x,&y,&buttons);
   while (buttons&3);
   fg_mousevis(OFF);
}
/******************************************************************/
void wait_for_mouse_buttons()
{
   int buttons;
   int x, y;

   do
      fg_mousepos(&x,&y,&buttons);
   while (buttons&3);
}
/******************************************************************/
int exit_program()
{
   /* called from menu. This would be a good place to prompt for
      "save before quitting?" */

   quit_graphics();
   return(0);
}
