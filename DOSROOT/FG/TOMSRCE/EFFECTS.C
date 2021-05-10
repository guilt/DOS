/******************************************************************\
*  effects.c -- Tommy game source code file                        *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "gamedefs.h"
/******************************************************************/
void get_blinkmap(OBJp objp)
{
   /* create a bitmap based on the sprite bitmap. If the pixel is
      any color except 0, make it black. 0 colors are transparent */

   register int i;
   register int nchar;
   char *p;

   /* p points to the bitmap of the object we want to copy */
   p = objp->sprite->bitmap;

   /* figure out the width and height */
   nchar = objp->sprite->width * objp->sprite->height;

   /* make the silhouette copy */
   for (i = 0; i < nchar; i++)
   {
      if (p[i] == 0)
         blink_map[i] = 0;
      else
         blink_map[i] = 7;
   }
}
/******************************************************************/
void load_status_screen()
{
   /* read in the slide projector screen */
   long filesize;

   if ((stream = fopen("slide.spr","rb")) == NULL)
   {
      strcpy(abort_string,"slide.spr not found");
      terminate_game();
   }
   /* allocate room for the slide projector screen */
   filesize = filelength(fileno(stream));
   slide_array = malloc((int)filesize);
   if (slide_array == (char *)NULL)
   {
      strcpy(abort_string,"Out of memory: slide_array");
      terminate_game();
   }
   fread(slide_array,sizeof(char),(unsigned int)filesize,stream);
   slide_arraysize = (int)filesize;
   fclose(stream);
}
/******************************************************************/
void redraw_screen()
{
   OBJp node;
   register int i,j;

   for (i = 0; i < 22; i++)       /* draw background tiles */
      for (j = 0; j < 15; j++)
            put_tile(i,j);

   apply_sprite(player);         /* draw the sprites */
   for (node=bottom_node; node!=(OBJp)NULL; node=node->next)
      apply_sprite(node);
                                 /* draw foreground tiles */
   for (i = 0; i < 22; i++)
         if (layout[hidden][i][j])
            put_foreground_tile(i,j);

   if (show_score)               /* draw the score sprite */
      apply_sprite(score);
}
/******************************************************************/
int status_screen()
{
   /* assemble a slide projector screen (special effect) */

   int nruns;
   unsigned char key,aux;
   register int y;
   static char *string[] = {
   "Tommy's",
   "Adventures",
   "Q - Quit",
   "W - Warp",
   "copyright 1994",
   "Diana Gruber"};

   /* display the RLE in off-screen memory */
   nruns = slide_arraysize/2;
   fg_move(0,726);
   fg_display(slide_array,nruns,320);
   fg_tcmask(1);

   redraw_screen();            /* frame 1: screen & legs folded */
   status_shape(3,156,150);
   status_shape(7,160,110);
   status_shape(4,160,91);
   status_shape(5,160,142);
   status_shape(6,160,99);
   swap();
   fg_waitfor(1);

   redraw_screen();            /* frame 2: legs open */
   status_shape(2,128,168);
   status_shape(7,160,136);
   status_shape(7,160,110);
   status_shape(4,160,91);
   status_shape(5,160,142);
   status_shape(6,160,99);
   swap();
   fg_waitfor(1);

   redraw_screen();            /* frame 3: screen turns 90 degrees */
   status_shape(2,128,168);
   status_shape(7,160,136);
   status_shape(7,160,110);
   status_shape(4,160,91);
   status_shape(1,100,128);
   swap();

   fg_waitfor(1);              /* frame 4: top goes up */
   redraw_screen();
   status_shape(2,128,168);
   status_shape(7,160,136);
   status_shape(7,160,110);
   status_shape(4,160,74);
   status_shape(1,100,128);
   swap();

   for (y = 123; y > 50; y-= 8) /* move the screen up */
   {
      fg_tcxfer(0,127,683,695,100+screen_orgx,y+vpo+screen_orgy,0,0);
      fg_waitfor(1);
   }
   fg_tcxfer(0,127,683,695,100+screen_orgx,48+vpo+screen_orgy,0,0);

   fg_setcolor(black);
   center_string(string[0],105+screen_orgx,219+screen_orgx,
                    50+vpo+screen_orgy);
   center_string(string[1],105+screen_orgx,219+screen_orgx,
                    60+vpo+screen_orgy);

   fg_setcolor(blue);
   center_string(string[2],105+screen_orgx,219+screen_orgx,
                    77+vpo+screen_orgy);
   center_string(string[3],105+screen_orgx,219+screen_orgx,
                    87+vpo+screen_orgy);

   fg_setcolor(black);
   center_string(string[4],105+screen_orgx,219+screen_orgx,
                    105+vpo+screen_orgy);
   center_string(string[5],105+screen_orgx,219+screen_orgx,
                    115+vpo+screen_orgy);

   fg_kbinit(0);               /* turn off the keyboard handler */
   flushkey();
   fg_getkey(&key,&aux);       /* wait for a keypress */


   if ((key|32) == 'q')        /* quit */
   {
      fg_kbinit(1);
      return (TRUE);
   }
   else if ((key|32) == 'w')   /* warp */
   {
      fg_kbinit(1);
      warp_to_next_level = TRUE;
      return (TRUE);
   }
   else                        /* don't quit */
   {
      redraw_screen();
      swap();
      redraw_screen();
      fg_kbinit(1);
      return (FALSE);
   }
}
/******************************************************************/
void status_shape(int shape,int x,int y)
{
   /* pieces of the slide projector screen */
   static int x1[] = {  0,  0,128,196,208,216,232,208};
   static int x2[] = {127,127,195,207,215,223,247,215};
   static int y1[] = {683,697,683,683,683,683,683,689};
   static int y2[] = {695,704,714,723,725,726,726,725};

   fg_tcxfer(x1[shape],x2[shape],y1[shape],y2[shape],
             x+screen_orgx,y+screen_orgy+hpo,0,0);
}
