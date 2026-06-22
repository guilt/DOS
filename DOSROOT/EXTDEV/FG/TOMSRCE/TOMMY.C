/******************************************************************\
*  Tommy.c -- Tommy game source code file                          *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#define tommy_c
#include "gamedefs.h"
#include "action.c"

/* #define debug */
/******************************************************************/
void main()
{
   register int i;
   char *bitmap;
   SPRITE *score_sprite;
   OBJp node;
   OBJp next_node;

   if (fg_testmode(20,4) == 0)        /* VGA or better required */
   {
      printf("\nVGA required\n");
      exit(0);
   }

#ifdef debug
   /* text file used for debugging purposes */
   dstream = fopen("debug.dat","wt");
#endif

#ifdef __TURBOC__
   oldhandler = getvect(0x1C);         /* get the vector for 0X1C */
   setvect(0x1C,increment_timer);      /* set timer interrupt function */
#else
   oldhandler = _dos_getvect(0x1C);    /* get the vector for 0X1C */
   _dos_setvect(0x1C,increment_timer); /* set timer interrupt function */
#endif

   /* open the game data file */
   if ((stream = fopen("game.dat","rt")) == NULL)
   {
      sprintf(abort_string,"Bad or missing file: Game.dat.");
      terminate_game();
   }

   /* read all the file names, store in structures */
   fscanf(stream,"%d",&nlevels);
   for (i = 0; i < nlevels; i++)
   {
      fscanf(stream,"%s",level_fname);
      fscanf(stream,"%s",background_fname);
      fscanf(stream,"%s",backattr_fname);
      fscanf(stream,"%s",foreground_fname);
      fscanf(stream,"%s",foreattr_fname);
      fscanf(stream,"%s",sprite_fname);
      level_to_array(i);
   }
   fclose(stream);

   current_level = 0;               /* start with the first level */
   array_to_level(current_level);   /* get level data from array */

   init_graphics();                 /* initialize the VGA graphics */
   fg_showpcx("tommy.pcx",0);       /* display intro screen */
   fg_waitkey();                    /* wait for a keystroke */
   fg_setcolor(0);                  /* clear the screen */
   fg_rect(0,351,0,479);
   load_level();                    /* load the level data */
   load_sprite();                   /* load the sprite data */
   load_status_screen();            /* load the status screen data */

   player = (OBJp)malloc(sizeof(OBJ));  /* allocate the player */
   player->tile_xmin = 4;
   player->tile_xmax = 14;
   player->tile_ymin = 5;
   player->tile_ymax = 11;

   /* initialize the score sprite */
   if ((bitmap = (char *)malloc(160*42)) == (char *) NULL)
   {
       sprintf(abort_string,"Out of sprite memory.");
       terminate_game();
   }

   if ((score_sprite = (SPRITE *)malloc(sizeof(SPRITE)))
      == (SPRITE *)NULL)
   {
       sprintf(abort_string,"Out of sprite memory.");
       terminate_game();
   }
   score_sprite->bitmap  = bitmap;
   score_sprite->width   = 160;
   score_sprite->height  = 42;
   score_sprite->xoffset = 0;
   score_sprite->yoffset = 0;

   /* initialize the score object */
   score = (OBJp)malloc(sizeof(OBJ));
   score->sprite = score_sprite;
   score->action = update_score;
   score->direction = RIGHT;

   /* start the linked list */
   bottom_node = (OBJp)NULL;
   top_node = (OBJp)NULL;
   next_node = (OBJp)NULL;

   /* initialize some global variables */
   max_time = 500L;
   player_score = 0L;
   show_score = TRUE;

   fg_tcmask(1);                       /* mask for fg_tcxfer */

   fg_kbinit(1);                       /* start the keyboard handler */
   game_time = 0;                      /* start the timer */
   set_rate(8);                        /* speed up the clock rate */

   for (;;)                            /* main program loop */
   {
      /* initialize some global variables */
      nbullets = 0;
      nenemies = 0;
      player_blink = FALSE;
      nblinks = 0;
      nhits = 0;
      nlives = 3;
      blink_time = 0;
      kicking = FALSE;

      warp(16,80);                     /* warp to starting position */
      swap();                          /* swap pages */
      page_copy(vpo);                  /* copy visual page to hidden */

      player->x = 32;                  /* initialize player */
      player->y = 200;
      player->frame = 0;
      player->time = 0;
      player->xspeed = 0;
      player->yspeed = 0;
      player->sprite = tom_stand[0];
      player->direction = RIGHT;
      player->action = player_run;

      launch_enemy(120,120,0);         /* launch some enemies */
      launch_enemy(900,120,1);
      score->action(score);            /* start the score */

      warp_to_next_level = FALSE;
      do                               /* continuous loop */
      {                                /* activate the level */
         activate_level();
         if (warp_to_next_level)
            break;
      }
      while(!status_screen());         /* check for program exit */

      if (!warp_to_next_level)         /* done -- exit */
      {
         abort_string[0] = '\n';
         terminate_game();
      }

      for (node=bottom_node; node!=(OBJp)NULL; node=next_node)
      {
          next_node = node->next;
          kill_object(node);
      }
      current_level++;                 /* do the next level */
      if (current_level == nlevels)
         current_level = 0;
      array_to_level(current_level);

      fg_setcolor(0);                  /* clear the screen */
      fg_rect(0,351,0,479);
      set_rate(0);                     /* set the clock rate to normal */
      load_level();                    /* load the level */
      set_rate(8);                     /* reset the clock rate */
   }
}
/******************************************************************/
void activate_level()
{
   register int i,j;
   unsigned long time;
   OBJp node; /* index for linked list */
   OBJp next_node; /* pointer to next node */

   next_node = (OBJp)NULL;
   for(;;)  /* loop continuously */
   {
      /* determine how much time has passed since the last frame */
      time = game_time;
      delta_time = time - last_time;
      delta_time = MAX(1L,delta_time);
      last_time = time;

      if (fg_kbtest(KB_ESC))  /* check for escape key */
         return;

      if (fg_kbtest(KB_F1))   /* check for the score board toggle */
         show_score = TRUE;
      else if (fg_kbtest(KB_F2))
         show_score = FALSE;
      else if (fg_kbtest(KB_W))
      {
         warp_to_next_level = TRUE;
         fg_waitfor(10);
         return;
      }

      /* do the action function for the player */
      player->action(player);

      /* if any scrolling occurred, adjust the screen & arrays */
      page_fix();

      /* do the action functions for all the sprites */
      for (node=bottom_node; node!=(OBJp)NULL; node=next_node)
      {
         next_node = node->next;
         node->action(node);        /* do the action function */
      }

      /* do the action function for the score */
      score->action(score);

      /* rebuild all the background tiles on the hidden page */
      rebuild_background();
      rebuild_foreground();
      for (i = 0; i < 22; i++)
         for (j = 0; j < 15; j++)
            layout[hidden][i][j] = FALSE;

      /* apply all the sprites on the hidden page */
      for (node=bottom_node; node!=(OBJp)NULL; node=node->next)
         apply_sprite(node);

      /* apply the player sprite */
      apply_sprite(player);

      /* apply any foreground tiles */
      rebuild_foreground();

      /* if the scoreboard is visible, put it on last */
      if (show_score)
         apply_sprite(score);

      /* swap the pages */
      swap();

      /* if the page has scrolled, copy the visual page to the
         hidden page */

      if (scrolled_left || scrolled_right || scrolled_up ||
          scrolled_down || warped)
         page_copy(vpo);

      /* reset all the scrolling globals to false */
      scrolled_left = FALSE;
      scrolled_right = FALSE;
      scrolled_up = FALSE;
      scrolled_down = FALSE;
      warped = FALSE;
   }
}
/******************************************************************/
void apply_sprite(OBJp objp)
{
   register int i,j;
   int x,y;
   int tile_x1,tile_y2;
   int tile_x2,tile_y1;
   int width, height;
   char *p;

   /* calculate the location, width and height */
   x = objp->x + objp->sprite->xoffset;
   y = objp->y + objp->sprite->yoffset;
   width = objp->sprite->width;
   height = objp->sprite->height;

   /* which tiles are going to be covered up? */
   tile_x1 = x/16 - tile_orgx;
   tile_y2 = y/16 - tile_orgy;
   tile_x2 = (x+width)/16 - tile_orgx;
   tile_y1 = (y-height)/16 - tile_orgy;

   /* if we are off the screen, forget it */
   if (tile_x2 < 0 || tile_x1 > 21 || tile_y1 > 14 || tile_y2 < 0)
      return;

   tile_x1 = MAX(tile_x1,0);
   tile_x2 = MIN(21,tile_x2);
   tile_y1 = MAX(tile_y1,0);
   tile_y2 = MIN(14,tile_y2);

   /* update the layout array */
   for (i = tile_x1; i <= tile_x2; i++)
   {
      p = layout[hidden][i] + tile_y1;
      for (j = tile_y1; j <= tile_y2; j++)
      {
         *p++ = TRUE;
      }
   }

   /* convert world space coordinates to screen space */
   x = x - (tile_orgx*16);
   y = y - (tile_orgy*16) + hpo;

   /* set the clipping limits */
   fg_setclip(0,351,hpo,hpb);
   fg_move(x,y);

   /* if the player is blinking, alternate black and regular */
   if (objp == player && player_blink)
   {
      blink_time += delta_time;
      if (blink_time > 5)
      {
         blink_time = 0;
         nblinks++;
         if (nblinks == 30)
         {
           player_blink = FALSE;
           nblinks = 0;
           blink_time = 0;
         }
      }
      if (nblinks%2 == 0)
      {
         get_blinkmap(objp);
         if (objp->direction == RIGHT)
             fg_clpimage(blink_map,width,height);
         else
             fg_flpimage(blink_map,width,height);
         fg_setclip(0,351,0,726);
         return;
      }
   }

   /* not blinking, just display the bitmap */
   if (objp->direction == RIGHT)
      fg_clpimage(objp->sprite->bitmap,width,height);
   else
      fg_flpimage(objp->sprite->bitmap,width,height);

   fg_setclip(0,351,0,726);
}
/******************************************************************/
void array_to_level(int n)
{
   /* update the current level */
   strcpy(level_fname,     level[n].level_fname);
   strcpy(background_fname,level[n].background_fname);
   strcpy(backattr_fname,  level[n].backattr_fname);
   strcpy(foreground_fname,level[n].foreground_fname);
   strcpy(foreattr_fname,  level[n].foreattr_fname);
   strcpy(sprite_fname,    level[n].sprite_fname);
}
/******************************************************************/
void fix_palettes()
{
   /* the first 32 palettes are fixed sprite colors */
   static char game_palette[] = {
    0, 0, 0, 18, 7, 0, 27,13, 3, 36,21,10, 45,31,19, 54,42,32, 63,55,47,
    0, 0, 0, 14,14,14, 21,21,21, 28,28,28, 35,35,35, 42,42,42, 49,49,49,
   56,56,56, 63,63,63,  0, 0,42,  8, 8,52, 21,21,63, 21,37,61, 21,53,60,
   36, 0, 0, 45, 0, 0, 54, 0, 0, 63, 0, 0, 56,44,47,  0,35, 0,  0,57, 0,
   21,63, 0, 63,63, 0, 51, 0,51, 63, 0,63};

   register int i;
   int color;
   int white_value,black_value;
   int blue_value;
   int distance;

   /* set the palettes for the first 32 colors (sprite colors) */
   fg_setdacs(0,32,game_palette);

   /* find the closest colors to white, black and blue. */
   white_value = 0;
   black_value = 63*63;
   white = 15;
   black = 0;
   blue_value = 63*63*3;

   for (i = 0; i < 32*3; i+=3)
   {
      color = game_palette[i]+game_palette[i+1]+game_palette[i+2];
      if (color > white_value) /* biggest total color is white */
      {
         white = i/3;
         white_value = color;
      }
      if (color < black_value) /* smallest total color is black */
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
   }
}
/******************************************************************/
void flushkey()
{
   unsigned char key,aux;

   /* clear out the keystroke buffer */
   do {
         fg_intkey(&key,&aux);
      }
      while (key+aux > 0);
}
/******************************************************************/
void getseed()
{
   /* get a seed for the random number generator */
   seed = (int)(fg_getclock() & 0x7FFF);
}
/*****************************************************************/
void interrupt increment_timer()
{
   game_time++;
}
/******************************************************************/
void init_graphics()
{
   fg_setmode(20);            /* set the video mode to Mode X */
   fg_resize(352,744);        /* resize video memory */
   fg_setclip(0,351,0,726);   /* set the clipping limits */
   getseed();                 /* start the random number generator */
   fix_palettes();            /* get the palette information */
}
/******************************************************************/
int irandom(int min, int max) /* random number generator */
{
   register int temp;

   temp = seed ^ (seed >> 7);
   seed = ((temp << 8) ^ temp) & 0x7FFF;
   return((seed % (max-min+1)) + min);
}
/******************************************************************/
void level_to_array(int n)    /* update all the levels */
{
   strcpy(level[n].level_fname,     level_fname);
   strcpy(level[n].background_fname,background_fname);
   strcpy(level[n].backattr_fname,  backattr_fname);
   strcpy(level[n].foreground_fname,foreground_fname);
   strcpy(level[n].foreattr_fname,  foreattr_fname);
   strcpy(level[n].sprite_fname,    sprite_fname);
}
/******************************************************************/
void load_sprite()            /* load sprite data from files */
{
   SPRITE *new_sprite;
   register int i,j;
   int n,nbytes;
   int width,height;
   int xorg,yorg;
   int bound_x,bound_y;
   int bound_width,bound_height;
   char far *bitmap;

   if ((stream = fopen(sprite_fname,"rt")) == NULL)
   {
      sprintf(abort_string,"%s not found",sprite_fname);
      terminate_game();
   }

   i = 0;
   fscanf(stream,"%d",&nspritelists);
   for (j = 0; j < nspritelists; j++)
   {
      fscanf(stream,"%s",list_fname);

      if ((sprite_stream = fopen(list_fname,"rb")) == NULL)
      {
         sprintf(abort_string,"%s not found",list_fname);
         terminate_game();
      }

      fread(&nsprites,sizeof(int),1,sprite_stream);
      for (n = 0; n < nsprites; n++)
      {
         fread(&width,sizeof(int),1,sprite_stream);
         fread(&height,sizeof(int),1,sprite_stream);
         nbytes = width * height;

         if ((bitmap = (char far *)malloc(nbytes)) == (char *)NULL)
         {
            sprintf(abort_string,"out of bitmap memory");
            terminate_game();
         }

         if ((new_sprite = (SPRITE *)malloc(sizeof(SPRITE)))
            == (SPRITE *)NULL)
         {
            sprintf(abort_string,"out of sprite memory");
            terminate_game();
         }

         sprite[i] = new_sprite;
         fread(&xorg,sizeof(int),1,sprite_stream);
         fread(&yorg,sizeof(int),1,sprite_stream);
         fread(&bound_x,sizeof(int),1,sprite_stream);
         fread(&bound_y,sizeof(int),1,sprite_stream);
         fread(&bound_width,sizeof(int),1,sprite_stream);
         fread(&bound_height,sizeof(int),1,sprite_stream);

         fread(bitmap,sizeof(char),nbytes,sprite_stream);

         sprite[i]->bitmap = bitmap;
         sprite[i]->width = width;
         sprite[i]->height = height;
         sprite[i]->bound_x = bound_x;
         sprite[i]->bound_y = bound_y;
         sprite[i]->bound_width = bound_width;
         sprite[i]->bound_height = bound_height;
         sprite[i]->xoffset = 0;
         sprite[i]->yoffset = 0;
         i++;
      }
      fclose(sprite_stream);
   }
   fclose(stream);

   /* assign the sprites to some more meaningful names */
   j = 0;
   for (i = 0; i < STANDFRAMES; i++)
      tom_stand[i] = sprite[j++];
   for (i = 0; i < RUNFRAMES; i++)
      tom_run[i] = sprite[j++];
   for (i = 0; i < JUMPFRAMES; i++)
      tom_jump[i] = sprite[j++];
   for (i = 0; i < KICKFRAMES; i++)
      tom_kick[i] = sprite[j++];
   for (i = 0; i < SHOOTFRAMES; i++)
      tom_shoot[i] = sprite[j++];
   for (i = 0; i < SCOREFRAMES; i++)
      tom_score[i] = sprite[j++];
   for (i = 0; i < ENEMYFRAMES; i++)
      enemy_sprite[i] = sprite[j++];
}
/******************************************************************/
void terminate_game()
{
   /* clean up and exit to DOS */
   fg_kbinit(0);         /* turn off the low-level keyboard handler */

   fg_setmode(3);        /* reset the video mode */
   fg_reset();           /* reset screen attributes */

   fg_setcolor(15);      /* print the exit string */
   printf(abort_string);
   printf("\n");

   set_rate(0);          /* put the clock speed back to a normal rate */
#ifdef __TURBOC__
   setvect(0x1C,oldhandler);      /* restore the interrupt */
#else
   _dos_setvect(0x1C,oldhandler); /* restore the interrupt */
#endif

   exit(0);
}
