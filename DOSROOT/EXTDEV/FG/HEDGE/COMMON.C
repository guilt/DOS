/****************************************************************************\
*                                                                            *
*  common.c -- functions we use a lot                                        *
*                                                                            *
\****************************************************************************/

#define common_c
#include "defs.h"

/****************************************************************************\
*                                                                            *
*  abort_game -- exit to DOS if a file or item is not found                  *
*                                                                            *
\****************************************************************************/

void abort_game()
{

   /* free the mouse handler and extra pages */

   fg_mousefin();
   fg_freepage(SPARE);

   /* set the video mode and reset screen attributes */

   fg_setmode(3);
   fg_reset();

   /* print out the abort string and exit */

   printf(abort_string);
   printf("\n");
   exit(0);
}

/****************************************************************************\
*                                                                            *
*  center_string -- use ROM font, center around a point                      *
*                                                                            *
\****************************************************************************/

void center_string(char *string, int x, int y)
{
   int nchar;
   int x1;

   /* measure the length of the string */

   nchar = strlen(string);

   /* calculate the x position */

   x1 = x - nchar*4;
   if (x1 < 0) x1 = 0;

   /* move to the location and print the string */

   fg_move(x1,y);
   fg_print(string,nchar);
}

/****************************************************************************\
*                                                                            *
*  flushkey -- flush out the keystroke buffer                                *
*                                                                            *
\****************************************************************************/

void flushkey()
{
   unsigned char key,aux;

   /* just keep reading keys until there aren't any */

   do
      fg_intkey(&key,&aux);
   while (key+aux > 0);
}

/****************************************************************************\
*                                                                            *
*  init_graphics -- initialize the graphics environment                      *
*                                                                            *
\****************************************************************************/

void init_graphics()
{
    int status;

   /* initialize the SVGA kernel */

   if (fg_svgainit(0) == 0)
   {
      strcpy(abort_string,"This program requires SVGA.");
      abort_game();
   }

   /* make sure an 800x600x256 mode with two pages is available */

   if (fg_testmode(26,2) == 0)
   {
      strcpy(abort_string,"This program requires a 1MB SVGA.");
      abort_game();
   }

   /* find out what the old video mode is */

   old_mode = fg_getmode();

   /* initialize 800x600x256 graphics */

   fg_setmode(26);

   /* find room for another page somewhere (XMS or EMS) */

   status = fg_initxms();
   if (status == 0)
      status = fg_allocxms(SPARE);

   if (status < 0)
   {
      status = fg_initems();
      if (status == 0)
         status = fg_allocems(SPARE);
   }

   if (status < 0)
   {
      strcpy(abort_string,"This program requires XMS or EMS memory.");
      abort_game();
   }

   /* benchmark the microprocessor for consistent stall times */

   clockspeed = fg_measure();

   /* initialize the mouse */

   init_mouse();
}

/****************************************************************************\
*                                                                            *
*  init_mouse -- initialize the mouse if present                             *
*                                                                            *
\****************************************************************************/

void init_mouse()
{
   if (fg_mouseini() > 0)
   {
      mouse = TRUE;
      xmouse = 160;
      ymouse = 100;
      fg_mousemov(xmouse,ymouse);
      fg_mousespd(4,8);
   }
   else
   {
      strcpy(abort_string,"This program requires a mouse.");
      abort_game();
   }
}

/****************************************************************************\
*                                                                            *
*  put_string -- put ROM font at an x and y position on the screen           *
*                                                                            *
\****************************************************************************/

void put_string(char *string,int x,int y)
{
   int nchar;

   /* determine the length of the string */

   nchar = strlen(string);

   /* move to desired location and display it */

   fg_move(x,y);
   fg_print(string,nchar);
}

/****************************************************************************\
*                                                                            *
*  quit_graphics -- return the computer to its original state                *
*                                                                            *
\****************************************************************************/

void quit_graphics()
{
   /* free the mouse handler and allocated page */

   fg_mousefin();
   fg_freepage(SPARE);

   /* reset the mode, fix screen attributes, and exit */

   fg_setmode(old_mode);
   fg_reset();
   exit(0);
}
