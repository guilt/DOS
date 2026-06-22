/**********************************************************************\

FISHTANK.C -- This program demonstrates multi-object non-destructive
animation.  The coral background is displayed on page 2 and copied to
page 0, the visual page.  A packed pixel run file containing the 6 fish
is displayed on page 1, and then fg_getimage is used to load the fish
into the fish bitmaps.

To make the fish move, the background is copied to page 1 and the fish
are put over the background using fg_clpimage and fg_flpimage.  The
fish are clipped at the edge of the screen.  Page 1 is then copied to
page 0 using fg_copypage.  This process is repeated in a loop.

To compile this program and link it with Fastgraph version 3.xx:

   BCC -ms FISHTANK.C FGS.LIB    (Borland C++)

   CL /AS FISHTANK.C /link FGS   (Microsoft C/C++ and Visual C++)

   QCL /AS FISHTANK.C /link FGS  (Microsoft QuickC)

   PC /ms FISHTANK               (Power C)
   PCL FISHTANK ;FGS

   TCC -ms FISHTANK.C FGS.LIB    (Turbo C/C++)

   ZTC -ms FISHTANK.C FGS.LIB    (Zortech C++)

This program also can be linked with Fastgraph/Light (version 3.02 or
later) if you replace the FGS library references with FGLS.

For more examples of animation using Fastgraph, or for an evaluation
copy of Fastgraph/Light, call DDBBS at (702) 796-7134.  For Fastgraph
voice support, call Ted Gruber Software at (702) 735-1980.

\**********************************************************************/

#include <fastgraf.h>
#include <stdio.h>
#include <stdlib.h>

void main(void);
void get_fish(void);
void go_fish(void);
int  irandom(int min,int max);
void put_fish(int fish_no,int x,int y,int fish_dir);
void random_init(void);

#define MAX(x,y) ((x) > (y)) ? (x) : (y)
#define MIN(x,y) ((x) < (y)) ? (x) : (y)

#define NFISH 11

int seed;

/*** fish bitmaps ***/

char fish1[700];
char fish2[1026];
char fish3[884];
char fish4[840];
char fish5[682];
char fish6[1224];

/**********************************************************************\
*                                                                      *
*                                 main                                 *
*                                                                      *
\**********************************************************************/

int colors[] = {0,1,2,3,4,5,6,7,16,0,18,19,20,21,22,23};

void main()
{
   int old_mode;

   /* make sure the system supports video mode 13 with 4 pages */

   if (fg_testmode(13,4) == 0)
   {
      printf("\n");
      printf("This program requires an EGA or VGA card\n");
      printf("with at least 128k.  If an EGA card is\n");
      printf("present, it must be the active adapter.\n");
      exit(0);
   }

   /* initialize the video environment */

   old_mode = fg_getmode();
   fg_setmode(13);
   fg_palettes(colors);
   random_init();

   /* get the coral background from a file and put it on page 2 */

   fg_setpage(2);
   fg_move(0,199);
   fg_dispfile("coral.ppr",320,1);

   /* copy the background from page 2 to page 0, the visual page */

   fg_copypage(2,0);

   /* get the fish */

   get_fish();

   /* make the fish go */

   go_fish();

   /* restore the original video state */

   fg_setmode(old_mode);
   fg_reset();
}

/**********************************************************************\
*                                                                      *
*            get_fish -- fill up the fish bitmap arrays                *
*                                                                      *
\**********************************************************************/

int fish_x1[]  = {0,   64,128,200,  0, 80}; /* location of fish x & y */
int fish_y1[]  = {199,199,199,199,150,150};
int width[]    = { 28, 27, 34, 28, 31, 34}; /* size of fish: width */
int height[]   = { 25, 38, 26, 30, 22, 36}; /* size of fish: height */

char *fishes[] = {fish1, /* for convenience, an array of pointers to fishes */
                  fish2,
                  fish3,
                  fish4,
                  fish5,
                  fish6};

void get_fish()
{
   register int fish_num;

   /* get the fish from a file and put them on page 1 */

   fg_setpage(1);
   fg_move(0,199);
   fg_dispfile("fish.ppr",320,1);

   /* build the fish bitmaps */

   for (fish_num = 0; fish_num < 6; fish_num++)
   {
      fg_move(fish_x1[fish_num],fish_y1[fish_num]);
      fg_getimage(fishes[fish_num],width[fish_num],height[fish_num]);
   }
}

/**********************************************************************\
*                                                                      *
*             go_fish -- make the fish swim around                     *
*                                                                      *
\**********************************************************************/

/*  There are 11 fish total, and 6 different kinds of fish.  These
*   arrays keep track of what kind of fish each fish is, and how each
*   fish moves:
*
*   fish[]   -- which fish bitmap applies to this fish?
*   x[]      -- starting x coordinate
*   y[]      -- starting y coordinate
*
*   xmin[]   -- how far left (off screen) the fish can go
*   xmax[]   -- how far right (off screen) the fish can go
*   xinc[]   -- how fast the fish goes left and right
*   dir[]    -- starting direction for each fish
*
*   ymin[]   -- how far up this fish can go
*   ymax[]   -- how far down this fish can go
*   yinc[]   -- how fast the fish moves up or down
*   yturn[]  -- how long fish can go in the vertical direction
*               before stopping or turning around
*   ycount[] -- counter to compare to yturn
*/

int fish[]   = {   1,   1,   2,   3,   3,   0,   0,   5,   4,   2,   3};
int x[]      = {-100,-150,-450,-140,-200, 520, 620,-800, 800, 800,-300};
int y[]      = {  40,  60, 150,  80,  70, 190, 180, 100,  30, 130,  92};

int xmin[]   = {-300,-300,-800,-200,-200,-200,-300,-900,-900,-900,-400};
int xmax[]   = { 600, 600,1100,1000,1000, 750, 800,1200,1400,1200, 900};
int xinc[]   = {   2,   2,   8,   5,   5,  -3,  -3,   7,  -8,  -9,   6};
int dir[]    = {   0,   0,   0,   0,   0,   1,   1,   0,   1,   1,   0};

int ymin[]   = {  40,  60, 120,  70,  60, 160, 160,  80,  30, 110,  72};
int ymax[]   = {  80, 100, 170, 110, 100, 199, 199, 120,  70, 150, 122};
int yturn[]  = {  50,  30,  10,  30,  20,  10,  10,  10,  30,   20, 10};
int ycount[] = {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};
int yinc[]   = {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};

void go_fish()
{
   register int i;
   unsigned char key, aux;

   /* make the fish swim around */

   do
   {
      /* copy the background from page 2 to page 1 */

      fg_copypage(2,1);

      /* put all the fish on the background */

      for (i = 0; i < NFISH; i++)
      {
         fg_setpage(1);
         ycount[i]++;
         if (ycount[i] > yturn[i])
         {
            ycount[i] = 0;
            yinc[i] = irandom(-1,1);
         }
         y[i] += yinc[i];
         y[i] = MIN(ymax[i],MAX(y[i],ymin[i]));

         if (x[i] >= 0 && x[i] < 320)
         {
            put_fish(fish[i],x[i],y[i],dir[i]);
         }
         else if (x[i] < 0 && x[i] > -72)
         {
            fg_transfer(0,71,0,199,104,199,1,3);
            fg_setpage(3);
            put_fish(fish[i],x[i]+104,y[i],dir[i]);
            fg_transfer(104,175,0,199,0,199,3,1);
         }
         x[i] += xinc[i];
         if (x[i] <= xmin[i] || x[i] >= xmax[i])
         {
            xinc[i] = -xinc[i];
            dir[i] = 1 - dir[i];
         }
      }

      /* copy page 1 to page 0 */

      fg_setpage(0);
      fg_copypage(1,0);

      /* intercept a keystroke, if it is escape exit the program */

      fg_intkey(&key,&aux);
   }
   while (key != 27);
}

/**********************************************************************\
*                                                                      *
*                irandom -- random number generator                    *
*                                                                      *
\**********************************************************************/

irandom(min,max)
int min,max;
{
   int temp;

   temp = seed ^ (seed >> 7);
   seed = ((temp << 8) ^ temp) & 0x7FFF;
   return((seed % (max-min+1)) + min);
}

/**********************************************************************\
*                                                                      *
*      put_fish -- draw one of the six fish anywhere you want          *
*                                                                      *
\**********************************************************************/

void put_fish(fish_num,x,y,fish_dir)
int fish_num,x,y,fish_dir;
{
   /* move to position where the fish will appear */

   fg_move(x,y);

   /* draw a left- or right-facing fish, depending on fish_dir */

   if (fish_dir == 0)
      fg_flpimage(fishes[fish_num],width[fish_num],height[fish_num]);
   else
      fg_clpimage(fishes[fish_num],width[fish_num],height[fish_num]);
}

/**********************************************************************\
*                                                                      *
*      random_init -- get a seed for the random number generator       *
*                                                                      *
\**********************************************************************/

void random_init()
{
   long fg_getclock();

   seed = (int)(fg_getclock() & 0x7FFF);
}
