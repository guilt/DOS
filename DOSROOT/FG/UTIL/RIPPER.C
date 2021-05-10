/******************************************************************\

  ripper.c -- tile ripper for preprocessing background tiles
              by Diana Gruber

  compile using large memory model
  requires Fastgraph(tm) or Fastgraph/Light(tm) to link

\******************************************************************/

#include <fastgraf.h>    /* standard include files                */
#include <stdio.h>
#include <stdlib.h>
#ifdef __TURBOC__
   #include <mem.h>
#else
   #include <memory.h>
#endif

int rip(char *filename); /* function declarations                 */
void write_level(void);
void display_level(int col);

FILE *stream;            /* level output data file                */

int tile_index;          /* keep track of current tile            */
int level_index;         /* keep track of level position          */
int ncols;               /* total columns in level map            */

#define TILESIZE  256    /* tiles are 16 pixels x 16 pixels       */
#define TILELIMIT 240    /* only 240 unique tiles                 */
#define MAXTILES  1440   /* up to 6 screens of art, 240 tiles each*/

/* the ripper_tiles array is used to store the unique tiles as 
   bitmaps RAM in for easy tile comparisons */

unsigned char far ripper_tiles[TILELIMIT][TILESIZE];

/* the level_map array stores the information needed to rebuild
   the level from tiles */

unsigned char level_map[MAXTILES]; 

/**************************** main ********************************/

void main(int argc, char *argv[])
{
   register int i;

   /* check that an input file was specified                      */
   if (argc < 2)
   {
      printf("Command syntax is: RIPPER infile1 <infile2>...\n");
      exit(1);
   }

   /* initialize the video mode to Mode X: 320x200x256            */
   fg_setmode(20);

   /* initialize some globals                                     */
   tile_index = 0;
   level_index = 0;
   ncols = 0;

   /* set all the tiles in the level map to 255                   */
   memset(level_map, 255, MAXTILES);

   /* rip all the files specified on the command line             */
   for (i = 1; i <= argc; i++)
     rip(argv[i]); 

   /* have a look at page 1 to see what the tiles look like       */
   fg_setvpage(1);

   /* write the level data and tiles out to disk                  */
   write_level();

   /* check your work -- reconstruct the pictures from the tiles  */
   for (i = 0; i < ncols; i+=20)
      display_level(i);

   /* restore the text video mode and exit                        */
   fg_setmode(3);
   fg_reset();
   exit(0);
}

/***************************** rip ********************************/

int rip(char *filename)
{
   register int i,n;
   unsigned char new_tile[TILESIZE];
   int x,y,x1,y1;
   int status;

   /* if you already have a full screen tiles, return an error    */
   if (tile_index >= TILELIMIT) 
      return(-1);

   /* display the PCX file on the visual page                     */
   fg_setpage(0);
   fg_setvpage(0);
   fg_move(0,0);
   status = fg_showpcx(filename,0);

   /* return an error code if the pcx file is bad or missing      */
   if (status > 0) 
      return (status);

   /* loop on the pcx file, starting at upper left corner, moving
      down the columns in sequence                                */
   for (n = 0; n < TILELIMIT; n++)
   { 
      x = (n/12)*16;
      y = (n%12)*16 + 15;

      /* get the new tile bitmap                                  */
      fg_move(x,y);
      fg_getimage(new_tile,16,16);

      /* compare the new tile to all the ripper tiles             */
      for (i = 0; i < tile_index; i++)
      {
         if (memcmp(new_tile,ripper_tiles[i],TILESIZE) == 0)
         {
            /* a duplicate tile is found, update the level map    */
            level_map[level_index] = (unsigned char)i;

            /* black out the duplicate tile                       */
            fg_setcolor(0);
            fg_rect(x,x+15,y-15,y);
            break;
         }
      }

      /* no match was found, therefore the tile must be unique    */
      if (level_map[level_index] == 255)
      {
         /* copy the new tile to the hidden page                  */
         x1 = (tile_index%20)*16;
         y1 = (tile_index/20)*16 + 23;
         fg_transfer(x,x+15,y-15,y,x1,y1,0,1);

         /* build the level map with the tile index               */
         level_map[level_index] = (unsigned char)tile_index;

         /* hold the array in RAM for later comparisons           */
         memcpy(ripper_tiles[tile_index],new_tile,TILESIZE);

         /* we can't have more than 240 unique tiles              */
         tile_index++;
         if (tile_index >= TILELIMIT)
            break;
      }
      level_index++;
   }

   /* increment the column count                                  */
   ncols += 20;
   return (0);
}

/************************* write level ****************************/

void write_level(void)
{
   register int i,j;

   /* make a pcx file out of the tile page                        */
   fg_setpage(1);
   fg_setvpage(1);
   fg_makepcx(0,319,8,199,"tiles.pcx");

   /* open a binary file for the level array                      */
   stream = fopen("ripper.lev","wb");

   /* write out all the columns, 12 tiles per column              */
   j = 0;
   for (i = 0; i < ncols; i++)
   {
      fwrite(&level_map[j],sizeof(char),12,stream);
      j+=12;
   }
   fclose(stream);
}

/************************ display level ***************************/

void display_level(int col)
{
   register int i,n;
   int x,y,x1,y1;
   int tile;

   /* set the visual page to page 0 and erase whatever is on it   */
   fg_setpage(0);
   fg_setvpage(0);
   fg_erase();

   /* display the tiles starting at the top of the first column   */
   n = 0;
   for (i = 0; i < 240; i++)
   {
      tile = level_map[col*12+n];
      x = (tile%20)*16;
      y = (tile/20)*16 + 23;

      x1 = (i/12)*16;
      y1 = (i%12)*16 + 15;

      fg_transfer(x,x+15,y-15,y,x1,y1,1,0);
      n++;
   }

   /* wait a bit so you can see what you did                      */
   fg_waitfor(20);
}
