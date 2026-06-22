/******************************************************************\
*  common.c -- game editor source code                             *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#define common_c
#include "editdefs.h"
/******************************************************************/
void abort_game()
{
   /* called if a file is missing, mouse not found, etc. */

   /* release the mouse handler */
   fg_mousefin();

   /* reset the video mode to standard text mode (mode 3) */
   fg_setmode(3);

   /* clear the screen */
   fg_reset();

   /* remove the working files */
   if (file_exists("game.01$"))
      remove("game.01$");

   if (file_exists("game.02$"))
      remove("game.02$");

   /* leave the error message string on the screen on exit */
   fg_setcolor(15);
   printf(abort_string);
   printf("\n");
   exit(0);
}
/******************************************************************/
int file_exists(char *filename)
{
   /* check if the file exists in the current directory */

   if (access(filename,0) == 0)
      return(TRUE);
   else
      return(FALSE);
}
/******************************************************************/
void flushkey()
{
   unsigned char key,aux;

   /* empty out the keyboard buffer (get all the keys) */
   do
   {
      fg_intkey(&key,&aux);
   }
   while (key+aux > 0);
}
/******************************************************************/
void init_graphics()
{
   /* set the mode to 320x200x256 mode X */
   fg_setmode(20);

   /* set up visual and hidden pages */
   fg_sethpage(1);
   visual = 0;
   hidden = 1;

   /* initialize the mouse and the colors */
   init_mouse();
   fix_palettes(0);
}
/******************************************************************/
void init_mouse()
{
   /* initialize the mouse, initialize global coordinates */
   if (fg_mouseini() > 0)
   {
      xmouse = 160;
      ymouse = 100;
      fg_mousemov(xmouse,ymouse);
      fg_mousevis(ON);
   }
   else
   {
      sprintf(abort_string,"mouse not found");
      abort_game();
   }
}
/******************************************************************/
void quit_graphics()
{
   /* release the mouse handler, reset the video mode */
   fg_mousefin();
   fg_setmode(3);
   fg_reset();

   /* remove the working files */
   if (file_exists("game.01$"))
      remove("game.01$");

   if (file_exists("game.02$"))
      remove("game.02$");

   exit(0);
}
/******************************************************************/
void fix_palettes(int status)
{
   static char sprite_palette[] = {
       0, 0, 0, 18, 7, 0, 27,13, 3, 36,21,10, 45,31,19, 54,42,32,
      63,55,47,  0, 0, 0, 14,14,14, 21,21,21, 28,28,28, 35,35,35,
      42,42,42, 49,49,49, 56,56,56, 63,63,63,  0, 0,42,  8, 8,52,
      21,21,63, 21,37,61, 21,53,60, 36, 0, 0, 45, 0, 0, 54, 0, 0,
      63, 0, 0, 56,44,47,  0,35, 0,  0,57, 0, 21,63, 0, 63,63, 0,
      63, 0,63, 63, 0,63};

   register int i;
   int color;
   int white_value, black_value;
   int blue_value, grey_value;
   int distance;
   static char game_palette[768];

   /* set the palettes for the first 32 colors (sprite colors) */
   if (status == 1)
      fg_setdacs(0,32,sprite_palette);

   /* get the current palette values */
   fg_getdacs(0,256,game_palette);

   /* find the closest colors to white, black, blue and grey for menus */
   white_value = 0;
   black_value = 189;
   white = 15;
   black = 0;
   blue_value = 63*63*3;
   grey_value = 63*63*3;

   for (i = 0; i < 255*3; i+=3)
   {
      color = game_palette[i]+game_palette[i+1]+game_palette[i+2];

      /* biggest total color value is closest to white */
      if (color > white_value)
      {
         white = i/3;
         white_value = color;
      }

      /* black color is closest to 0 */
      if (color < black_value)
      {
         black = i/3;
         black_value = color;
      }

      /* find closest blue color using least squares method */
      distance =
         (63 - game_palette[i+2]) * (63 - game_palette[i+2]) +
         (21 - game_palette[i+1]) * (21 - game_palette[i+1]) +
         (21 - game_palette[i]) * (21 - game_palette[i]);

      if (distance < blue_value)
      {
         blue = i/3;
         blue_value = distance;
      }

      /* find closest grey color using least squares method */
      distance =
         (42 - game_palette[i+2]) * (42 - game_palette[i+2]) +
         (42 - game_palette[i+1]) * (42 - game_palette[i+1]) +
         (42 - game_palette[i]) * (42 - game_palette[i]);

      if (distance < grey_value)
      {
         grey = i/3;
         grey_value = distance;
      }
   }
}
