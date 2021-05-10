/******************************************************************\
*                                                                  *
*  Fade.C -- palette fade program                                  *
*                                                                  *
*  Written by Eric W. Lund (CIS:74041,1147) with thanks to Ted     *
*  Gruber and Randy Dryburgh. Copyright (C) 1994 by Eric "Please   *
*  use and share this code" Lund.                                  *
*                                                                  *
\******************************************************************/

#include <fastgraf.h>
#ifdef __TURBOC__
  #include <mem.h>
#else
  #include <memory.h>
#endif

#define FADE_COLORS   256 /* Number of screen colors    */
#define FADE_CHANNELS 768 /* Colors x 3 (for R, G, & B) */

/* global variables */
char fade_pal[FADE_CHANNELS];
char fade_keyhalt=0;
int fade_steps=32;
int fade_delay=0;
void fade (int dir, int start, int count);
void fade_blackout (void);

/* macros */
#define fade_init()           fg_getdacs (0, FADE_COLORS, fade_pal);
#define fade_in_all()         fade(1,0,FADE_COLORS)
#define fade_out_all()        fade(0,0,FADE_COLORS)
#define fade_in(start,count)  fade(1,start,count);
#define fade_out(start,count) fade(0,start,count);
/******************************************************************/
void main (void)
{
   int x;
   char pal[768];

   fg_setmode(20);           /* Set mode to 320x200 Mode X */
   fg_setvpage(1);           /* Look at a blank screen */

   /* adjust the palettes */
   for (x=0; x<256; x++)
   {
       pal[x*3]  =x/16;      /* Set reds */
       pal[x*3+1]=x%64;      /* Set greens */
       pal[x*3+2]=(255-x)/4; /* Set blues */
   }
   pal[0]=0; pal[1]=0; pal[2]=0; /* Color 0 is background, keep it black */
   fg_setdacs (0,256,pal);

   /* Draw colorful shapes on hidden page */
   for (x=0; x<256; x++)
   {
       fg_setcolor(x);
       fg_move(319-x,199);
       fg_draw (x,0);
   }

   /* Illustrate fading routines: */
   fade_keyhalt=1;     /* Allow a keyhit to abort fading */
   fade_init();        /* Make copy of screen palette to RAM */
   fade_blackout();    /* Blackout screen palette */
   fg_setvpage(0);     /* Look at page with graphic (now blacked out) */

   fade_steps=128;     /* Very smooth, slow fade */
   fade_in_all();      /* Fade in screen palette to match RAM copy */
   fade_out_all();     /* Fade out screen palette to blackout */

   fade_steps=64;      /* Slow fade */
   fade_in_all();      /* Fade in screen palette to match RAM copy */
   fade_out_all();     /* Fade out screen palette to blackout */

   fade_steps=32;      /* Restore normal fading speed */
   fade_in(64,64);     /* Fade in selected portion of palette */
   fade_in(128,64);    /* Fade in selected portion of palette */
   fade_in(0,64);      /* Fade in selected portion of palette */
   fade_in(192,64);    /* Fade in selected portion of palette */

   fade_steps=16;      /* Very fast fade */
   fade_out(128,64);   /* Fade out selected portion of palette */
   fade_out(64,64);    /* Fade out selected portion of palette */
   fade_out(192,64);   /* Fade out selected portion of palette */
   fade_out(0,64);     /* Fade out selected portion of palette */

   fg_setmode(3);       /* Back to our regular DOS video mode! */
   fg_reset();         /* Reset any ANSI attributes */
}
/******************************************************************/
void fade (int dir,int start,int count)
{
   register int k,n;
   int i,j;                           /* loop variables */
   char fade_pal_new [FADE_CHANNELS]; /* modified (faded) palette */
   unsigned char key1,key2;           /* used for for keycheck */

   /* loop through all gradations of the fade */
   for (i=dir?1:fade_steps-1; dir?i<=fade_steps:i>=0; dir?i++:i--)
   {
      if (fade_keyhalt) /* default is do not halt on keyhit */
      {
         fg_intkey (&key1, &key2);
         if (key1+key2>0)
         {
             fade_keyhalt++; /* let user detect aborted fade */
             break;          /* halt fade on keyhit */
         }
      }
      /* create new (faded) palette */
      for (k=0, n=start*3, j=0; j<count; j++)
      {
         fade_pal_new[k++] = (char)(((int)fade_pal[n++] * i)/fade_steps);
         fade_pal_new[k++] = (char)(((int)fade_pal[n++] * i)/fade_steps);
         fade_pal_new[k++] = (char)(((int)fade_pal[n++] * i)/fade_steps);
      }
      fg_setdacs(start,count,fade_pal_new); /* install new palette */
      if (fade_delay) 
         fg_waitfor (fade_delay);           /* pause if needed */
   }
}
/******************************************************************/
void fade_blackout(void)
{
   /* empty palette for quick clearing */
   char empty_palette[FADE_CHANNELS];   

   /* set all palette entries to 0 */
   memset (empty_palette,0,FADE_CHANNELS);

   /* set dacs to zero */
   fg_setdacs(0,FADE_COLORS,empty_palette); 
}

