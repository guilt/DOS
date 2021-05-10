/******************************************************************\

 level.c -- level editor code for side-scrolling games by
             Diana Gruber

 compile using large model
 requires Fastgraph(tm) or Fastgraph/Light(tm) to link

\******************************************************************/

#include <fastgraf.h>     /* header for the Fastgraph lib */
#include <stdio.h>
#include <stdlib.h>

/* standard defines */
#define OFF   0
#define ON    1
#define OK    1
#define FALSE 0
#define TRUE  1

/* define keys */
#define ESC         27
#define SPACE       32
#define UP_ARROW    72
#define LEFT_ARROW  75
#define RIGHT_ARROW 77
#define DOWN_ARROW  80
#define INSERT      82
#define DELETE      83

#define WHITE       255
#define BLACK         0

int xmouse,ymouse;        /* mouse position  */
int buttons;              /* state of mouse buttons */
int tile_xmouse;          /* mouse position on the tile page */
int tile_ymouse;

int tile_orgx;            /* tile coords of upper left corner */
int tile_orgy;
int screen_orgx;          /* screen coords of upper left corner */
int screen_orgy;

int vpo;                  /* visual page offset (0 or 240) */
int hpo;                  /* hidden page offset (240 or 0) */
int tpo;                  /* tile page offset (always 480) */

#define MAXROWS 200       /* maximum number of tile rows in level */
#define MAXCOLS 240       /* maximum number of tile cols in level */
int nrows;                /* actual number of rows in the level */
int ncols;                /* actual number of columns in level */

/* large array containing all the tile information for the level */
unsigned char far level_map[MAXCOLS][MAXROWS];

FILE *stream;             /* file handle for level data */

/**** function declarations */
void  main(void);
void  edit_level(void);               /* main editor loop */
int   get_tile(void);                 /* get tile from tile page */
void  put_tile(int x,int y);          /* put a tile */
void  delete_tiles(void);             /* delete row or column */
void  insert_tiles(void);             /* insert row or column */
void  load_level(void);               /* read level from file */
void  redraw_screen(void);            /* put all tiles on screen */
void  save_level(void);               /* save level to file */
int   scroll_left(int npixels);       /* scrolling functions */
int   scroll_right(int npixels);
int   scroll_down(int npixels);
int   scroll_up(int npixels);
void  swap(void);                     /* flip pages */

/***************************** main *******************************/

void main()
{
   /* set the video mode to Mode X 320x200x256 */
   fg_setmode(20);                  

   /* resize video memory */
   fg_resize(352,727);

   /* initialize the Mode X mouse handler */
   if (fg_mouseini() <= 0)
   {
      fg_setmode(3);
      fg_reset();
      printf("Mouse not found!\n");
      exit(0);
   }

   /* the mouse cursor is invisible throughout the program */
   fg_mousevis(0);

   /* load the level data from a file */
   load_level();

   /* edit the level */
   edit_level();

   /* save the level */
   save_level();

   /* release the Mode X mouse handler */
   fg_mousefin();

   /* reset the video mode and exit */
   fg_setmode(3);
   fg_reset();
   exit(0);
}

/************************** edit_level ****************************/

void edit_level()
{
   register int i,j;
   unsigned char key,aux;
   int xbox,ybox,oldx,oldy;       /* mouse coordinates */
   int cursor_flag;               /* flag for mouse cursor */
   int tile;                      /* tile to get or put */

   /* start with the mouse at the center of the visual screen */
   fg_mousemov(160,100+vpo);
   fg_mousepos(&xmouse,&ymouse,&buttons);

   /* normalize the x and y coordinates to a tile boundary */
   xbox = xmouse&0xfff0;
   ybox = ymouse&0xfff0;

   /* update oldx and oldy */
   oldx = xbox;
   oldy = ybox;

   fg_setcolor(WHITE);
   fg_boxx(xbox,xbox+15,ybox, ybox+15);
   cursor_flag = ON;
   tile = 0;

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
            /* xor the old cursor box to get rid of it */
            fg_setcolor(WHITE);
            if (cursor_flag) 
               fg_boxx(oldx,oldx+15,oldy,oldy+15);

            /* draw the cursor box at new position */
            fg_boxx(xbox,xbox+15,ybox,ybox+15);

            /* update the cursor flag */
            cursor_flag = ON;

            /* the new coordinates become the old coordinates */
            oldx = xbox;
            oldy = ybox;
         }

         /* if the mouse cursor is off, turn it on */
         else if (!cursor_flag)
         {
            fg_setcolor(WHITE);
            fg_boxx(xbox,xbox+15,ybox,ybox+15);
            cursor_flag = ON;
         }

         /* the left mouse button puts down a tile */
         if (buttons == 1)
         {
            /* first turn off the mouse cursor */
            fg_setcolor(WHITE);
            fg_boxx(xbox,xbox+15,ybox,ybox+15);

            /* set the cursor flag */
            cursor_flag = OFF;

            /* calculate the level array indices */
            i = xbox/16;
            j = (ybox-vpo)/16;

            /* update the level array */
            level_map[i+tile_orgx][j+tile_orgy]=(unsigned char)tile;

            /* draw the tile */
            put_tile(i,j);
         }

         /* right button picks up a tile */
         else if (buttons == 2)
         {
            /* calculate the level array indices */
            i = tile_orgx + xmouse/16;
            j = tile_orgy + (ymouse-vpo)/16;

            /* find the tile in the tile map */
            tile = level_map[i][j];
         }
      }

      /* key press detected -- process the key */
      else 
      {
         /* turn off the mouse cursor and set the flag to off */
         if (cursor_flag)
         {
            fg_setcolor(WHITE);
            fg_boxx(xbox,xbox+15,ybox,ybox+15);
            cursor_flag = OFF;
         }

         /* Escape key pressed, we are finished */
         if (key == ESC)
            return;

         /* arrow keys pressed -- scroll around */
         else if (aux == LEFT_ARROW)
            scroll_left(16);
         else if (aux == RIGHT_ARROW)
            scroll_right(16);
         else if (aux == UP_ARROW)
            scroll_up(16);
         else if (aux == DOWN_ARROW)
            scroll_down(16);

         /* space bar gets at tile from the tile page */
         else if (key == SPACE)
            tile = get_tile();

         /* insert a row or column of tiles */
         else if (aux == INSERT)
            insert_tiles();

         /* delete a row or column of tiles */
         else if (aux == DELETE)
            delete_tiles();
      }
   }
}

/*************************** get_tile *****************************/

int get_tile()
{
   int xbox,ybox;
   int oldx,oldy;
   int old_xmouse, old_ymouse;
   int tile_num;
   unsigned char key, aux;

   /* keep track of the current mouse position */
   old_xmouse = xmouse;
   old_ymouse = ymouse;

   /* pan to the tile page area */
   fg_pan(0,tpo);

   /* change the mouse limits and move the mouse */
   fg_mouselim(0,319,tpo,tpo+176);
   fg_mousemov(tile_xmouse,tile_ymouse);

   /* calculate the mouse cursor position */       
   xbox = tile_xmouse&0xfff0;
   ybox = tile_ymouse&0xfff0;
   oldx = xbox;
   oldy = ybox;

   /* draw the mouse cursor */
   fg_setcolor(WHITE);
   fg_boxx(xbox,xbox+15,ybox,ybox+15);

   for(;;)
   {
      fg_intkey(&key,&aux);
      if (key == ESC)
         break;

      /* check the mouse position and normalize for tile space */
      fg_mousepos(&xmouse,&ymouse,&buttons);
      xbox = xmouse&0xfff0;
      ybox = ymouse&0xfff0;

      /* mouse has moved, redraw the mouse cursor */
      if (xbox != oldx || ybox != oldy)
      {
         /* clear the old cursor */
         fg_boxx(oldx,oldx+15,oldy,oldy+15);

         /* draw the new cursor */
         fg_boxx(xbox,xbox+15,ybox,ybox+15);

         /* update the old x and y values */
         oldx = xbox; oldy = ybox;
      }

      /* button_press detected, we have chosen our tile */
      if (buttons == 1)
         break;
   }

   /* calculate the tile number from the mouse position */
   tile_num = ((ybox-tpo)/16) * 20 + (xbox/16);

   /* clear the mouse cursor */
   fg_boxx(xbox,xbox+15,ybox,ybox+15);

   /* keep track of the position for the next time */
   tile_xmouse = xbox;
   tile_ymouse = ybox;

   /* pan back to the visual page */
   fg_pan(screen_orgx,screen_orgy+vpo);

   /* reset mouse limits and move the mouse back where it was */
   fg_mouselim(0,336,vpo,vpo+224);
   fg_mousemov(old_xmouse,old_ymouse);

   /* give yourself enough time to get your finger off the button */
   fg_waitfor(5); 
   return(tile_num);
}

/*************************** put_tile *****************************/

void put_tile(int xtile, int ytile)
{
   int tile_num;
   int x,y;
   int x1,x2,y1,y2;

   /* get the tile information from the tile map */
   tile_num = (int)level_map[xtile+tile_orgx][ytile+tile_orgy];

   /* calculate the destination coordinates */
   x = xtile * 16;
   y = ytile * 16 + 15 + vpo;

   /* calculate the source coordinates */
   x1 = (tile_num%20)*16;
   x2 = x1+15;
   y1 = (tile_num/20)*16 + tpo;
   y2 = y1+15;

   /* copy the tile */
   fg_transfer(x1,x2,y1,y2,x,y,0,0);
}

/************************* delete tiles ***************************/

void delete_tiles()
{
   register int i,j;
   unsigned char key,aux;
   int tile;

   /* pop up a message: what do you want to delete? */
   fg_setcolor(WHITE);
   fg_rect(screen_orgx+60,screen_orgx+260,
           screen_orgy+90+vpo,screen_orgy+110+vpo);
   fg_setcolor(BLACK);
   fg_move(screen_orgx+80,screen_orgy+105+vpo);
   fg_print("Delete Row or Column?",21);

   /* wait for a key press */
   fg_getkey(&key,&aux);

   /* delete a column at the current mouse position */
   if ((key == 'c' || key == 'C') && ncols > 22)
   {
      /* calculate the current tile column */
      tile = tile_orgx + xmouse/16;

      /* shift all the tiles left by one column */
      for (j = 0; j < nrows; j++)
         for (i = tile; i < ncols-1; i++)
            level_map[i][j] = level_map[i+1][j];

      /* zero out the last column */
      i = ncols-1;
      for (j = 0; j < nrows; j++)
         level_map[i][j] = 0;

      /* decrement the number of columns */
      ncols--;
   }

   /* delete a row at the current mouse position */
   else if ((key == 'r' || key == 'R') && nrows > 15)
   {
      /* calculate the current tile row */
      tile = tile_orgy + (ymouse-vpo)/16;

      /* shift all the tiles up by one row */
      for (j = tile; j < nrows-1; j++)
         for (i = 0; i < ncols; i++)
            level_map[i][j] = level_map[i][j+1];

      /* zerow out the last row */
      j = nrows-1;
      for (i = 0; i < ncols; i++)
          level_map[i][j] = 0;

      /* decrement the number of rows */
      nrows--;
   }

   /* fix the screen by redrawing all the tiles */
   redraw_screen();
   return;
}

/************************* insert_tiles ***************************/

void insert_tiles()
{
   register int i,j;
   unsigned char key,aux;
   int tile;

   /* pop up a message: what do you want to insert? */
   fg_setcolor(WHITE);
   fg_rect(screen_orgx+60,screen_orgx+260,
           screen_orgy+90+vpo,screen_orgy+110+vpo);
   fg_setcolor(BLACK);
   fg_move(screen_orgx+80,screen_orgy+105+vpo);
   fg_print("Insert Row or Column?",21);

   /* wait for a key press */
   fg_getkey(&key,&aux);

   /* insert a column at the current mouse position */
   if (key == 'c' || key == 'C' && ncols < MAXCOLS)
   {
      /* increment the number of columns */
      ncols++;

      /* calculate the current column */
      tile = tile_orgx + xmouse/16;

      /* shift all the columns right by one */
      for (j = 0; j < nrows; j++)
         for (i = ncols-1; i > tile; i--)
            level_map[i][j] = level_map[i-1][j];
   }

   /* insert a row at the current mouse position */
   else if (key == 'r' || key == 'R' && nrows < MAXROWS)
   {
      /* increment the number of rows */
      nrows++;

      /* calculate the current row */
      tile = tile_orgy + (ymouse-vpo)/16;

      /* shift all the rows down by one */
      for (j = nrows-1; j > tile; j--)
         for (i = 0; i < ncols; i++)
            level_map[i][j] = level_map[i][j-1];
   }

   /* fix the screen by redrawing all the tiles */
   redraw_screen();
   return;
}

/************************** load_level ****************************/

void load_level()
{
   register int i,j;

   /* initialize some global variables */
   tile_orgx = 0;
   tile_orgy = 0;
   screen_orgx = 0;
   screen_orgy = 0;
   vpo = 0;
   hpo = 240;
   tpo = 480;
   tile_xmouse = 0;
   tile_ymouse = 480;
 
   /* set the mouse limits */
   fg_mouselim(0,336,vpo,vpo+224);

   /* display the tiles in the tile area */
   fg_move(0,tpo);
   fg_showpcx("castle.pcx",2);

   /* open the level file and read the level information */
   if ((stream = fopen("castle.lev","rb")) != NULL)
   {
      fread(&ncols,sizeof(int),1,stream);
      fread(&nrows,sizeof(int),1,stream);

      for (i = 0; i < ncols; i++)
         fread(&level_map[i][0],sizeof(char),nrows,stream);
      fclose(stream);
   }

   /* if you didn't find the file, just initialize the tiles to 0 */
   else
   {
      ncols = 22;
      nrows = 15;
      for (i = 0; i < ncols; i++)
         for (j = 0; j < nrows; j++)
            level_map[i][j] = 0;
   }

   /* fix the screen by redrawing all the tiles */
   redraw_screen();
}

/************************ redraw_screen ***************************/

void redraw_screen()
{
   register int i,j;

   /* copy all the tiles to the visual page */

   for (i = 0; i < 22; i++)
      for (j = 0; j < 15; j++)
         put_tile(i,j);
}

/************************** save_level ****************************/

void save_level()
{
   register int i;

   /* open a binary file for writing */
   if ((stream = fopen("level.out","wb")) != NULL)
   {
      /* write out the number of columns and rows */
      fwrite(&ncols,sizeof(int),1,stream);
      fwrite(&nrows,sizeof(int),1,stream);

      /* write each column, in sequence */
      for (i = 0; i < ncols; i++)
         fwrite(&level_map[i][0],sizeof(char),nrows,stream);
      fclose(stream);
   }
}

/************************* scroll_left ****************************/

int scroll_left(int npixels)
{
   register int i;

   /* no tiles need to be redrawn */
   if (screen_orgx >= npixels)
   {
      screen_orgx-= npixels;
      fg_pan(screen_orgx,screen_orgy);
   }

   /* redraw one column of tiles and do a page swap */
   else if (tile_orgx > 0)
   {
      tile_orgx--;
      screen_orgx+=(16-npixels);
      fg_transfer(0,335,vpo,vpo+239,16,hpo+239,0,0);
      swap();
      for(i = 0; i< 15; i++)
         put_tile(0,i);
   }
   else   /* can't scroll left */
      return(-1);
   return(OK);
}

/************************* scroll_right ***************************/

int scroll_right(int npixels)
{
   register int i;

   /* no tiles need to be redrawn */
   if (screen_orgx <= 32-npixels)
   {
      screen_orgx+=npixels;
      fg_pan(screen_orgx,screen_orgy);
   }

   /* redraw one column of tiles and do a page swap */
   else if (tile_orgx < ncols - 22)
   {
      tile_orgx++;
      screen_orgx-=(16-npixels);
      fg_transfer(16,351,vpo,vpo+239,0,hpo+239,0,0);
      swap();
      for(i = 0; i< 15; i++)
         put_tile(21,i);
   }
   else   /* can't scroll right */
      return(-1);
   return(OK);
}

/************************* scroll_up ******************************/

int scroll_up(int npixels)
{
   register int i;

   /* no tiles need to be redrawn */
   if (screen_orgy >= npixels)
   {
      screen_orgy-=npixels;
      fg_pan(screen_orgx,screen_orgy);
   }
   /* redraw one row of tiles and do a page swap */
   else if (tile_orgy > 0)
   {
      tile_orgy--;
      screen_orgy+=(16-npixels);
      fg_transfer(0,351,vpo,223+vpo,0,hpo+239,0,0);
      swap();
      for(i = 0; i< 22; i++)
         put_tile(i,0);
   }
   else   /* can't scroll up */
      return(-1);
   return(OK);
}

/************************* scroll_down ****************************/

int scroll_down(int npixels)
{
   register int i;

   /* no tiles need to be redrawn */
   if (screen_orgy <= 40-npixels)
   {
      screen_orgy+=npixels;
      fg_pan(screen_orgx,screen_orgy);
   }

   /* redraw one row of tiles and do a page swap */
   else if (tile_orgy < nrows - 15)
   {
      tile_orgy++;
      screen_orgy-=(16-npixels);
      fg_transfer(0,351,16+vpo,vpo+239,0,223+hpo,0,0);
      swap();
      for(i = 0; i< 22; i++)
         put_tile(i,14);
   }
   else   /* can't scroll down */
      return(-1);
   return(OK);
}

/***************************** swap *******************************/

void swap()
{
   /* reverse the hidden page and visual page offsets */
   vpo = 240 - vpo;
   hpo = 240 - hpo;

   /* set the origin to the visual page */
   fg_pan(screen_orgx,screen_orgy+vpo);

   /* calculate the new mouse position */
   ymouse -= hpo;
   ymouse += vpo;

   /* reset the mouse limits and move the mouse */
   fg_mouselim(0,336,vpo,vpo+224);
   fg_mousemov(xmouse,ymouse);
}
