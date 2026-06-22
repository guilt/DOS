/******************************************************************\
*  fge.c -- game editor source code                                *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "editdefs.h"
/******************************************************************/
void main()
{
   register int i;

   if (fg_testmode(20,4) == 0)
   {
      printf("\nvga required\n");
      exit(0);
   }

   /* dstream = fopen("debug.dat","wt"); */

   /* open the game file, load up the file names */
   current_level = 0;
   strcpy(game_fname,"game.dat");
   if ((tstream = fopen(game_fname,"rt")) != NULL)
   {
      /* get the file list */
      fscanf(tstream,"%d",&nlevels);
      for (i = 0; i< nlevels; i++)
      {
         fscanf(tstream,"%s",level_fname);
         fscanf(tstream,"%s",background_fname);
         fscanf(tstream,"%s",backattr_fname);
         fscanf(tstream,"%s",foreground_fname);
         fscanf(tstream,"%s",foreattr_fname);
         fscanf(tstream,"%s",sprite_fname);
         level_to_array(i);
      }
      fclose(tstream);
      array_to_level(current_level);
   }
   else
   {
      nlevels = 1;
      strcpy(level_fname,"");
      strcpy(background_fname,"");
      strcpy(backattr_fname,"");
      strcpy(foreground_fname,"");
      strcpy(foreattr_fname,"");
      strcpy(sprite_fname,"");
      level_to_array(current_level);
   }

   /* initialize the ripper file names */
   strcpy(ripper_inpcx,"infile.pcx");
   strcpy(ripper_outpcx,"outfile.pcx");
   strcpy(ripper_outlvl,"ripper.lev");

   init_graphics();

   /* initialize some globals */
   level_xmouse = 0;
   level_ymouse = 0;
   back_xmouse  = 0;
   back_ymouse  = 0;
   block_rows = 1;
   block_cols = 1;
   block[0][0] = 0;

   xlimit = 319;
   ylimit = 199;

   editing_sprite_files = FALSE;
   current_spritelist = 1;

   /* initialize background, foreground, and sprites */
   init_tiles();
   init_sprite();

   /* start editing */
   edit_menu();
}
/******************************************************************/
void edit_menu()
{
   unsigned char key,aux;
   int mousex, mousey, count;
   register int i;

   main_option = 0; /* this is a global value */

   /* draw the screen on the hidden page and copy it to the visual page */
   draw_screen();

   /* begin the main program loop */
   for(;;)
   {
      fg_mousevis(ON);
      fg_waitfor(2);

      /* intercept a keystroke */
      fg_intkey(&key,&aux);
      if (key == ESC)
      {
         exit_program();
         continue;
      }
      else if (aux == RIGHT_ARROW)
      {
         main_option++;
         if (main_option == ITEMS)
            main_option = 0;
      }
      else if (aux == LEFT_ARROW)
      {
         main_option--;
         if (main_option < 0)
            main_option = ITEMS - 1;
      }

      /* display menu according to keystroke pressed */
      if (key+aux > 0)
      {
         fg_mousevis(OFF);
         fg_restore(0,319,menu_top,menu_bottom);
         horizontal_menu(main_menu,4,main_option);
         if (main_option == ESC)
         {
            exit_program();
            main_option = 0;
         }
         fg_setpage(0);
         fg_mousevis(OFF);
         fg_restore(0,xlimit,menu_top,ylimit);
         horizontal_menu(main_menu,-4,main_option);
         fg_mousevis(ON);
      }

      /* intercept a mouse click */
      fg_mousebut(1,&count,&mousex,&mousey);
      if (count > 0 && BETWEEN(mousey,menu_top,menu_bottom))
      {
         for (i = 0; i < ITEMS; i++)
         {
            if (BETWEEN(mousex, mouse_limits[i], mouse_limits[i+1]))
            {
               fg_restore(0,319,menu_top,menu_bottom);
               if (horizontal_menu(main_menu,4,i) == ESC)
                  exit_program();
               fg_mousevis(OFF);
               fg_restore(0,xlimit,menu_top,ylimit);
               horizontal_menu(main_menu,-4,main_option);
               fg_mousevis(ON);
               break;
            }
         }
      }
   }
}
/******************************************************************/
void draw_screen()
{
   static char *string[] =
   {
      "Fastgraph Game Editor",
      "Copyright 1994 Ted Gruber Software"
   };
   int y2, y3;

   y2 = 12; y3 = 23;
   menu_top = 13;
   menu_bottom  = 24;
   fg_mousevis(OFF);
   hidden = 1;
   visual = 0;
   fg_sethpage(1);
   fg_setpage(1);

   /* erase the hidden page */
   fg_erase();

   /* draw some rectangles */
   fg_setcolor(white);
   fg_rect(0,xlimit,0,ylimit);

   fg_setcolor(grey);
   fg_rect(0,xlimit,0,y2);

   /* "Fastgraph Game Editor" at top */
   fg_setcolor(black);
   center_string(string[0],0,317,y2-5);
   fg_setcolor(white);
   center_string(string[0],0,319,y2-4);

   fg_setcolor(blue);
   fg_rect(0,xlimit,y3+1,ylimit);

   /* copyright notice at bottom */
   fg_setcolor(black);
   center_string(string[1],0,317,196);
   fg_setcolor(white);
   center_string(string[1],0,319,197);

   fg_setcolor(black);
   fg_rect(0,xlimit,menu_bottom,menu_bottom);
   fg_rect(0,xlimit,y2,y2);

   /* copy from hidden page to visual page */
   fg_copypage(hidden,visual);
   fg_setpage(visual);

   /* draw the menu, but don't activate it yet */
   horizontal_menu(main_menu,-4,main_option);
}
/******************************************************************/
load_game_file()
{
   register int i,j;
   int k;
   char fname[13];
   unsigned char key,aux;
   int error;
   char string[50];
   static char *stringlist[] =
   {
      game_fname,
      level_fname,
      background_fname,
      foreground_fname,
      sprite_fname
   };

   static int y[] = {52,62,72, 92,112,132};

   /* copy the level information from the semi-permanent array to the
      temporary working copy */

   array_to_level(current_level);
   strcpy(fname,game_fname);

   /* draw some rectangles */
   fg_mousevis(OFF);
   fg_setcolor(blue);
   fg_rect(0,319,25,199);

   fg_setcolor(white);
   fg_rect(48,271,40,170);

   fg_setcolor(black);
   fg_rect(0,319,24,24);
   fg_box(48,271,40,170);

   /* display the information */
   fg_setcolor(black);
   put_string("Game file:",76,52);
   put_string("level:",76,62);
   put_string("background:",76,72);
   put_string("foreground:",76, 92);
   put_string("sprite list:",76,112);

   fg_setcolor(blue);
   put_string("F10:DONE",204,152);
   put_string("F1:HELP",210,162);

   /* display the current file names */
   show_level_names();

   /* change the file names */
   i = 0;
   error = FALSE;
   for(;;)
   {
      strcpy(string,stringlist[i]);
      fg_setcolor(blue);
      j = get_string(string,160,y[i],12,0,0);

      /* abandon file editing */
      if (j == ESC)
      {
         error = TRUE;
         break;
      }

      /* done */
      else if (j == F10)
         break;

      /* press F1 for help */
      else if (j == F1)
         file_help_screen();

      else if (j == DOWN_ARROW || j == UP_ARROW || j == ENTER)
      {
         /* load a different game file */
         if (i == GAMEFILE  && strcmpi(string,game_fname)!=0)
         {
            strcpy(game_fname,string);
            if ((tstream = fopen(game_fname,"rt")) != NULL)
            {
               fscanf(tstream,"%d",&nlevels);
               for (k = 0; k < nlevels; k++)
               {
                  fscanf(tstream,"%s",level_fname);
                  fscanf(tstream,"%s",background_fname);
                  fscanf(tstream,"%s",backattr_fname);
                  fscanf(tstream,"%s",foreground_fname);
                  fscanf(tstream,"%s",foreattr_fname);
                  fscanf(tstream,"%s",sprite_fname);
                  level_to_array(k);
               }
               fclose(tstream);
               current_level = 0;
            }
         }
         else
         {
            check_suffixes(string,i);
            level_to_array(current_level);
         }
         show_level_names();
      }

      /* edit the sprite list */
      if (j == F2)
      {
         fg_copypage(0,1);
         load_sprites();
         fg_copypage(1,0);
         fg_setpage(0);
         fg_setcolor(white);
         fg_rect(160,270,y[4]-8,y[4]);
         fg_setcolor(black);
         put_string(stringlist[4],160,y[4]);
      }

      /* next field */
      else if (j == DOWN_ARROW || j == TAB)
      {
         i++;
         if (i > 4) i = 0;
      }

      /* previous field */
      else if (j == UP_ARROW)
      {
         i--;
         if (i < 0) i = 4;
      }

      /* next level */
      else if (j == PGDN && current_level < MAXLEVELS-1)
      {
         level_to_array(current_level);
         current_level++;
         if (current_level >= nlevels)
         {
            fg_setcolor(white);
            fg_rect(48,271,180,192);
            fg_setcolor(black);
            fg_box(48,271,180,192);
            sprintf(string,"add level %d?",current_level);
            center_string(string,48,271,188);
            fg_getkey(&key,&aux);
            fg_setcolor(blue);
            fg_rect(48,271,180,192);

            if ((key|32) == 'y')
               nlevels++;
            else
               current_level--;
         }
         show_level_names();
      }

      /* previous level */
      else if (j == PGUP && current_level > 0)
      {
         level_to_array(current_level);
         current_level--;
         show_level_names();
      }

      /* insert a new level */
      else if (j == INSERT && current_level < MAXLEVELS-1)
      {
         fg_setcolor(white);
         fg_rect(48,271,180,192);
         fg_setcolor(black);
         fg_box(48,271,180,192);
         sprintf(string,"insert level %d?",current_level);
         center_string(string,48,271,188);

         fg_getkey(&key,&aux);
         fg_setcolor(blue);
         fg_rect(48,271,180,192);

         if ((key|32) == 'y')
            nlevels++;
         else
            continue;

         for (k = nlevels-1; k > current_level+1; k--)
         {
            array_to_level(k-1);
            level_to_array(k);
         }
         show_level_names();
      }

      /* delete the current level */
      else if (j == DELETE && nlevels > 1)
      {
         fg_setcolor(white);
         fg_rect(48,271,180,192);
         fg_setcolor(black);
         fg_box(48,271,180,192);
         sprintf(string,"delete level %d?",current_level);
         center_string(string,48,271,188);

         fg_getkey(&key,&aux);
         fg_setcolor(blue);
         fg_rect(48,271,180,192);

         if ((key|32) == 'y')
            nlevels--;
         else
            continue;

         if (current_level >= nlevels)
            current_level--;
         else
         {
            for (k = current_level; k < nlevels; k++)
            {
               array_to_level(k+1);
               level_to_array(k);
            }
         }
         show_level_names();
      }
   }

   /* if we have changed the file names, save the information */
   if (!error)
   {
      /* update the array */
      level_to_array(current_level);

      /* display new background and foreground tiles */
      init_tiles();
      init_sprite();

      /* write the game data out to a file */
      tstream = fopen(game_fname,"wt");
      if (tstream != NULL)
      {
         fprintf(tstream,"%d\n",nlevels);
         for (i = 0; i< nlevels; i++)
         {
            array_to_level(i);
            fprintf(tstream,"%s\n",level_fname);
            fprintf(tstream,"%s\n",background_fname);
            fprintf(tstream,"%s\n",backattr_fname);
            fprintf(tstream,"%s\n",foreground_fname);
            fprintf(tstream,"%s\n",foreattr_fname);
            fprintf(tstream,"%s\n",sprite_fname);
         }
         fclose(tstream);
      }
   }

   /* now, put the current level back */
   array_to_level(current_level);

   /* clear the dialog box and return */
   fix_palettes(1);
   draw_screen();
   return(0);
}
/******************************************************************/
check_suffixes(char *fname, int file_type)
{
   /* make sure file name suffixes match: pcx, lev, etc. */
   char *strptr;
   int index;
   int error;

   error = FALSE;
   strptr = strchr(fname,'.');

   /* period in string */
   if (strptr > 0)
   {
      index = (int)(strptr - fname);
      if (index > 8)
         error = TRUE;
   }

   /* no period in string */
   else
   {
      index = strlen(fname);
      if (index > 8)
         error = TRUE;
      else
         fname[index] = '.';
   }
   if (error) return(ERR);

   if (file_type == GAMEFILE)
   {
      fname[index+1] = '\0';
      strcat(fname,"dat");
   }
   else if (file_type == LEVELFILE)
   {
      fname[index+1] = '\0';
      strcat(fname,"lev");
      strcpy(level_fname,fname);
   }
   else if (file_type == BACKFILE)
   {
      fname[index+1] = '\0';
      strcat(fname,"pcx");
      strcpy(background_fname,fname);

      fname[index+1] = '\0';
      strcat(fname,"att");
      strcpy(backattr_fname,fname);

      background_changed = TRUE;
   }
   else if (file_type == FOREFILE)
   {
      fname[index+1] = '\0';
      strcat(fname,"pcx");
      strcpy(foreground_fname,fname);

      fname[index+1] = '\0';
      strcat(fname,"att");
      strcpy(foreattr_fname,fname);

      foreground_changed = TRUE;
   }
   else if (file_type == SPRITEFILE)
   {
      fname[index+1] = '\0';
      strcat(fname,"dat");
      strcpy(sprite_fname,fname);
   }
   return(OK);
}
/******************************************************************/
void file_help_screen()
{
   register int i,y;
   static char *string[] = {
      "    Editing Game files",
      " ",
      "Arrows: Move between fields",
      "PGDN:   Next level",
      "PGUP:   Prev level",
      "INS:    Insert level",
      "DEL:    Delete level",
      "F2:     Edit sprite list",
      "F10:    Save and Load",
      "Esc:    Abort"
   };

   static char *string1[] = {
      " ",
      "    Editing sprite files",
      " ",
      "Arrows: Move between fields",
      "INS:    Insert sprite list",
      "DEL:    Delete sprite list",
      "F10:    Save and Load",
      "Esc:    Abort",
      " ",
      " "
   };

   /* draw the help screen */
   fg_setpage(0);
   fg_mousevis(OFF);
   fg_save(48,271,40,170);

   fg_setcolor(white);
   fg_rect(56,263,45,165);
   fg_setcolor(black);
   fg_box(56,263,45,165);

   /* display the text information */
   y = 60;
   for (i = 0; i < 10; i++)
   {
      if (editing_sprite_files)
         put_string(string1[i], 80,y);
      else
         put_string(string[i], 80,y);
      y += 10;
   }

   /* clear the dialog box and return */
   fg_waitkey();
   fg_restore(48,271,40,170);
   fg_setpage(1);
   fg_setcolor(blue);
   fg_rect(48,271,40,170);
   fg_setpage(0);
}
/******************************************************************/
void level_to_array(int n)
{
   /* level information is stored in a semi-permanent RAM array,
      and copied to some temporary working variables. This function
      copies from the variables to the array */

   strcpy(level[n].level_fname,     level_fname);
   strcpy(level[n].background_fname,background_fname);
   strcpy(level[n].backattr_fname,  backattr_fname);
   strcpy(level[n].foreground_fname,foreground_fname);
   strcpy(level[n].foreattr_fname,  foreattr_fname);
   strcpy(level[n].sprite_fname,sprite_fname);
}
/******************************************************************/
void array_to_level(int n)
{
   /* copy from the array into the temporary working variables */

   strcpy(level_fname,     level[n].level_fname);
   strcpy(background_fname,level[n].background_fname);
   strcpy(backattr_fname,  level[n].backattr_fname);
   strcpy(foreground_fname,level[n].foreground_fname);
   strcpy(foreattr_fname,  level[n].foreattr_fname);
   strcpy(sprite_fname,level[n].sprite_fname);
}
/******************************************************************/
void show_level_names()
{
   /* the load/save game function repeatedly shows the file names
      for all the files in the level. This function just displays
      them */

   register int i;

   char string[50];
   static char *stringlist[] =
   {
      game_fname,
      level_fname,
      background_fname,
      foreground_fname,
      sprite_fname
   };

   static int y[] = {52,62,72, 92,112,132};  /* y coordinates */
   array_to_level(current_level);

   /* draw a rectangle to clear the area */
   fg_setcolor(white);
   fg_rect(160,270,53,132);

   /* write all the strings */
   fg_setcolor(black);
   for (i = 0; i < 5; i++)
      put_string(stringlist[i],160,y[i]);

   put_string(backattr_fname,160, 82);
   put_string(foreattr_fname,160,102);

   /* clear a rectangle at the bottom */
   fg_setcolor(white);
   fg_rect(76,178,143,162);
   fg_setcolor(black);

   /* also display which level and how many total levels */
   sprintf(string,"level number: %d",current_level);
   put_string(string,76,152);

   sprintf(string,"total levels: %d",nlevels);
   put_string(string,76,162);
}
