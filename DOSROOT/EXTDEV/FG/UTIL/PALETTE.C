/******************************************************************\
*                                                                  *
*  palette.c -- palette reduction and merging source code          *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
*                                                                  *
\******************************************************************/

#define palette_c
#include "paldefs.h"
   char *menu_string[]= {
   "Fastgraph Palette Matching/Reduction",
   "PCX File Name:",
   "Image type is:", "Sprite",  "Background",
   "Type of color reduction is:",
   "Choose best colors",
   "Match colors",
   "Merge colors",
   "output pcx file name:",
   "Press F10 to begin the color reduction.",
   "Match First 32 colors in pcx file:",
   "Match last 224 colors in pcx file:",
   "Merge First 32 colors in pcx file:",
   "Merge last 224 colors in pcx file:"};

   int menu_x[] = 
            {10,             /* title */
             10,             /* pcx file name */
             10,130,190,     /* image type is sprite/background */
             10,             /* type of reduction is: */
             10,             /* Choose best colors */
             135,            /* Match colors */
             225,            /* Merge colors */
             10,             /* output pcx file name */
             10,             /* Press F10 */
             10,             /* match 32 pcx file name */
             10,             /* match 224 pcx file name */
             };

   int menu_y[] = 
            { 7,             /* title */
             27,             /* pcx file name */
             47,47,47,       /* image type is sprite/background */
             67,             /* type of reduction is: */
             80,             /* Choose best colors */
             80,             /* Match colors */
             80,             /* Merge colors */
             117,            /* output pcx file name */
             197,            /* Press F10 */
             97,             /* match 32 pcx file name*/
             97,             /* match 224 pcx file name */
             };

/******************************************************************/
void main()
{
   /* set the video mode to Mode X 320x200x256 */
   fg_setmode(20);

   /* get the default palette set */
   fg_getdacs(0,255,default_colors);

   /* initialize file names (null strings) */
   infile[0] = '\0';
   matchfile[0] = '\0';
   outfile[0] = '\0';

   /* initialize global variables */
   file_type =      SPRITE;
   reduction_type = CHOOSE;
   field = 0;

   /* loop until ESC key is pressed */
   for (;;)
   {
      /* draw the user input screen */
      redraw_screen();

      /* collect input */
      if (activate_screen() == QUIT)
         quit_graphics();
      else
      {
         /* do the color reduction */
         do_reduction();
         fg_waitkey();
      }
   }
}
/******************************************************************/
int activate_screen()
{
   /* activate all the fields on the menu screen */
   unsigned char key,aux;
   int ret;
   char tempstring[13];

   for (;;)
   {
      if (field == 0)                     /* enter pcx file name */
      {
         fg_setcolor(14);                 /* highlight in yellow */
         put_string(menu_string[1],menu_x[1],menu_y[1]);
         key = 0;
         aux = 0;
         strcpy(tempstring,infile);
         ret = get_string(tempstring,103,27,12,key,aux); /* get the string */
         if (ret == ESC)
            return(QUIT);
         if (fix_suffix(tempstring) == ERR)
         {
            fg_setcolor(0);
            fg_rect(100,176,20,30);       /* input file name */
            fg_setcolor(15);
            put_string(tempstring,103,27);
            error_message("Invalid file name!");
         }
         else 
         {
            if (!file_exists(tempstring))
            {

               fg_setcolor(0);
               fg_rect(100,176,20,30);    /* input file name */
               fg_setcolor(15);
               put_string(tempstring,103,27);
               error_message("File not found!");
            }
            else  /* file name okay */
               strcpy(infile,tempstring);
         }
         if (ret == F10)
            return(OK); 
         else if (ret == DOWN_ARROW || ret == UP_ARROW)
         {
            fg_setcolor(15);              /* unhighlight */
            put_string(menu_string[1],menu_x[1],menu_y[1]);
            fg_setcolor(0);
            fg_rect(100,176,20,30);       /* input file name */
            fg_setcolor(15);
            put_string(infile,103,27);

            if (ret == UP_ARROW)
               field=4;
            else
               field++;
         }
      }
      else if (field == 1)                /* sprite or background? */
      {
         fg_setcolor(14);
         put_string(menu_string[2],menu_x[2],menu_y[2]);
         for (;;)
         {
            fg_getkey(&key,&aux);
            if (aux == LEFT_ARROW)
            {
               file_type = SPRITE;
               fg_setcolor(12);
               fg_box(127,167,40,50);

               fg_setcolor(9);
               fg_box(187,251,40,50);
               if (reduction_type == MATCH || reduction_type == MERGE)
               {
                  show_match_string();
                  fg_setcolor(15);
                  put_string(matchfile,223,97);
               }
               else
               {
                  fg_setcolor(9);
                  fg_rect(0,319,90,100);
               }

            }
            else if (aux == RIGHT_ARROW)
            {
               file_type = BACKGROUND;
               fg_setcolor(9);
               fg_box(127,167,40,50);

               fg_setcolor(12);
               fg_box(187,251,40,50);
               if (reduction_type == MATCH || reduction_type == MERGE)
               {
                  show_match_string();
                  fg_setcolor(15);
                  put_string(matchfile,223,97);
               }
               else
               {
                  fg_setcolor(9);
                  fg_rect(0,319,90,100);
               }
            }
            else
            {
               fg_setcolor(15);           /*unhighlight */
               put_string(menu_string[2],menu_x[2],menu_y[2]);
               if (key == ESC)
                  return(QUIT);
               else if (aux == F10)
                  return(OK); 
               else if (aux == UP_ARROW)
                  field--;
               else
                  field++;
               break;
            }
         }
      }
      else if (field == 2)                /* match, merge or choose? */
      {
         fg_setcolor(14);
         put_string(menu_string[5],menu_x[5],menu_y[5]);
         for (;;)
         {
            fg_getkey(&key,&aux);
            if (aux == LEFT_ARROW || aux == RIGHT_ARROW)
            {
               if (aux == LEFT_ARROW)
               {
                  if (reduction_type == MATCH)
                     reduction_type = CHOOSE;
                  else if (reduction_type == MERGE)
                     reduction_type = MATCH;
               }
               else if (aux == RIGHT_ARROW)
               {
                  if (reduction_type == CHOOSE)
                     reduction_type = MATCH;
                  else if (reduction_type == MATCH)
                     reduction_type = MERGE;
               }
               fg_setcolor(9);
               fg_box(7,119,73,83);       /* unhighlight all */
               fg_box(132,208,73,83);
               fg_box(223,298,73,83);

               fg_setcolor(12);
               if (reduction_type == MATCH)
                  fg_box(132,208,73,83);
               else if (reduction_type == MERGE)
                  fg_box(223,298,73,83);
               else /* choose */
                  fg_box(7,119,73,83);

               fg_setcolor(9);
               fg_rect(0,319,90,100);
               if (reduction_type == MATCH || reduction_type == MERGE)
               {
                  show_match_string();
                  fg_setcolor(15);
                  put_string(matchfile,223,97);
               }
            }
            else
            {
               if (key == ESC)
                  return(QUIT);
               else if (aux == F10)
                  return(OK); 
               else if (aux == UP_ARROW)
                  field--;
               else
                  field++;
               break;
            }
         }
         fg_setcolor(15);                 /* unhighlight */
         put_string(menu_string[5],menu_x[5],menu_y[5]);
      }
      else if (field == 3)                /* match file name */
      {
         if (reduction_type == CHOOSE)
         {
            field++;
            continue;
         }
         fg_setcolor(9);
         fg_rect(10,319,90,100);
         fg_setcolor(14);
         if (file_type == BACKGROUND && reduction_type == MATCH)
            /* match 224 color pcx name */
            put_string(menu_string[12],10,97);
         else if (file_type == BACKGROUND && reduction_type == MERGE)
            /* match 32 color pcx name */
            put_string(menu_string[13],10,97);
         else if (file_type == SPRITE && reduction_type == MATCH)
            /* match 32 color pcx name */
            put_string(menu_string[11],10,97);
         else if (file_type == SPRITE && reduction_type == MERGE)
           /* match 32 color pcx name */
            put_string(menu_string[14],10,97);
         fg_setcolor(0);
         fg_rect(220,296,90,100);
         fg_setcolor(15);
         put_string(matchfile,223,97);

         key = 0;
         aux = 0;
         strcpy(tempstring,matchfile);
         /* get the match file name */
         ret = get_string(tempstring,223,97,12,key,aux); 
         if (ret == ESC)
            return(QUIT);

         if (fix_suffix(tempstring) == ERR)
         {
            fg_setcolor(0);
            fg_rect(220,296,90,100);
            fg_setcolor(15);
            put_string(tempstring,223,97);
            error_message("Invalid file name!");
         }
         else 
         {
            if (!file_exists(tempstring))
            {
               fg_setcolor(0);
               fg_rect(220,296,90,100);
               fg_setcolor(15);
               put_string(tempstring,223,97);
               error_message("file not found!");
            }
            else  /* file name okay */
            {
               strcpy(matchfile,tempstring);
               show_match_string();
               fg_setcolor(15);
               put_string(matchfile,223,97);

            }
         }
         if (ret == F10)
            return(OK); 
         else if (ret == UP_ARROW || ret == DOWN_ARROW)
         {
            show_match_string();
            fg_setcolor(15);
            put_string(matchfile,223,97);

            if (ret == UP_ARROW)
               field--;
            else
               field++;
         }
      }

      else if (field == 4)                /* output file name */
      {
         fg_setcolor(14);
         put_string(menu_string[9],menu_x[9],menu_y[9]);

         key = 0;
         aux = 0;
         strcpy(tempstring,outfile);

         /* get the output file name string */
         ret = get_string(tempstring,145,117,12,key,aux); 
         if (ret == ESC)
            return(QUIT);

         if (fix_suffix(tempstring) == ERR)
         {
            fg_setcolor(0);
            fg_rect(142,218,110,120);
            fg_setcolor(15);
            put_string(tempstring,145,117);
            error_message("Invalid file name!");
         }
         else 
         {
            if (file_exists(tempstring) && (strcmpi(tempstring,outfile)!=0))
            {

               fg_setcolor(0);
               fg_rect(142,218,110,120);
               fg_setcolor(15);
               put_string(tempstring,145,117);

               fg_setcolor(15);
               fg_rect(0,319,130,140);
               fg_setcolor(12);
               center_string("File exists. Okay to overwrite? y/n",0,319,137);
               fg_getkey(&key,&aux);
               fg_setcolor(9);
               fg_rect(0,319,130,140);
               if (key == 'y' || key == 'Y')
               {
                  strcpy(outfile,tempstring);
               }
            }
            else  /* file name okay */
            {
               strcpy(outfile,tempstring);
            }
         }
         if (ret == F10)
            return(OK); 
         else if (ret == UP_ARROW || ret == DOWN_ARROW)
         {
            fg_setcolor(15);              /* unhighlight */
            put_string(menu_string[9],menu_x[9],menu_y[9]);
            fg_setcolor(0);
            fg_rect(142,218,110,120);  /* output file name */
            fg_setcolor(15);
            put_string(outfile,145,117);

            if (ret == UP_ARROW)
            {
               if (reduction_type == CHOOSE)
                  field-=2;
               else
                  field--;
            }
            else
               field=0;
         }
      }
   }
}
/******************************************************************/
do_reduction()
{
   /* display the input file */

   if (fg_showpcx(infile,0) != 0)
   {
      field = 0;
      return(ERR);
   }

   /* get the palette colors */
   fg_getdacs(0,256,input_colors);

   /* call the appropriate function */
   if (reduction_type == CHOOSE)
   {   
      if (file_type == BACKGROUND)
         reduce(224);
      else
         reduce(32);
   }
   else if (reduction_type == MATCH)
   {
      if (file_type == BACKGROUND)
         match(224);
      else
         match(32);
   }
   else /* merge */
   {
      if (file_type == BACKGROUND)
         merge(32);
      else
         merge(224);
   }
   if (fix_suffix(outfile))
      fg_makepcx(0,319,0,199,outfile);
}
/******************************************************************/
void error_message(char *string)
{
   fg_setcolor(15);
   fg_rect(0,319,130,140);
   fg_setcolor(12);
   center_string(string,0,319,137);
   fg_waitkey();
   fg_setcolor(9);
   fg_rect(0,319,130,140);
}
/******************************************************************/
int file_exists(char *filename)
{
   /* does the file exist? */
   if (access(filename,0) == 0)
      return(TRUE);
   else
      return(FALSE);
}
/******************************************************************/
int fix_suffix(char *fname)
{
   /* check for pcx file extension, append if necessary */

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
      if (index > 8 || index < 1)
         error = TRUE;
      else
         fname[index] = '.';
   }
   if (error) return(ERR);
   
   fname[index+1] = '\0';
   strcat(fname,"pcx");

   return(OK);
}
/******************************************************************/
void match(int ncolors)
{
    unsigned long target,distance;
    int color,match;
    unsigned int i,j;
    unsigned int start, end;

    fg_setpage(1);
    fg_showpcx(matchfile,0);
    fg_setpage(0);
    fg_move(0,199);
    fg_getimage(buffer1,320,200);

    if (ncolors == 32)
    {
       start = 0;
       end = 32*3;
    }
    else
    {
       start = 32*3;
       end = 256*3;
    }

    fg_getdacs(0,256,match_colors);
    for (i = 0; i < 256*3; i+= 3)
    {
      target = 63L*63L*63L;
      for (j = start; j < end; j+= 3)
      {
         distance = 
         (input_colors[i+2] - match_colors[j+2]) *
         (input_colors[i+2] - match_colors[j+2]) 
         +
         (input_colors[i+1] - match_colors[j+1]) *
         (input_colors[i+1] - match_colors[j+1]) 
         +
         (input_colors[i] - match_colors[j]) *
         (input_colors[i] - match_colors[j]); 

         if (distance < target)
         {
            match = j/3;
            target = distance;
         }
      }
      match_palette[i/3] = (unsigned char)match;
   }
   for (i = 0; i < 320*200; i++)
      buffer2[i] = match_palette[buffer1[i]];

   fg_move(0,199);
   fg_putimage(buffer2,320,200);
   return;
}
/******************************************************************/
int merge(int ncolors)
{
   register int i;

   if (!file_exists(matchfile))
      return(ERR);

   fg_setpage(1);
   fg_showpcx(matchfile,0);
   fg_setpage(0);
   fg_getdacs(0,256,match_colors);

   if (ncolors == 32)
   {
      for (i = 0; i < 32*3; i+=3)
      {
        output_colors[i] =   match_colors[i];  
        output_colors[i+1] = match_colors[i+1];
        output_colors[i+2] = match_colors[i+2];
      }
      for (i = 32*3; i < 256*3; i+=3)
      {
        output_colors[i] =   input_colors[i];
        output_colors[i+1] = input_colors[i+1];
        output_colors[i+2] = input_colors[i+2];
      }
   }
   else
   {
      for (i = 0; i < 32*3; i+=3)
      {
        output_colors[i] =   input_colors[i];  
        output_colors[i+1] = input_colors[i+1];
        output_colors[i+2] = input_colors[i+2];
      }
      for (i = 32*3; i < 256*3; i+=3)
      {
        output_colors[i] =   match_colors[i];  
        output_colors[i+1] = match_colors[i+1];
        output_colors[i+2] = match_colors[i+2];
      }
   }
   fg_setdacs(0,256,output_colors);
   return(OK);
}
/******************************************************************/
void quit_graphics()
{
   /* return the system to text mode and exit */
   fg_setmode(3);
   fg_reset();
   exit(0);
}
/******************************************************************/
void redraw_screen()
{
   register int i;

   /* draw some rectangles */
   fg_setcolor(9);
   fg_rect(0,319,0,199);
   fg_setdacs(0,255,default_colors);

   fg_setcolor(15);
   fg_rect(0,319,0,12);
   fg_rect(0,319,190,199);

   /* title at top */
   fg_setcolor(12);
   center_string(menu_string[0],0,319,8);

   /* other strings */
   fg_setcolor(15);
   for (i = 1; i < 10; i++)
      put_string(menu_string[i],menu_x[i],menu_y[i]);

   fg_setcolor(12);
   center_string(menu_string[10],0,319,197);  /* Press F10 to begin */

   /* boxes for file names */

   fg_setcolor(0);
   fg_rect(100,176,20,30);    /* input file name */
   fg_rect(142,218,110,120);  /* output file name */

   fg_setcolor(15);
   put_string(infile,103,27);
   put_string(outfile,145,117);


   if (file_type == SPRITE)
   {
      fg_setcolor(12);
      fg_box(127,167,40,50);

      fg_setcolor(15);
      if (reduction_type == MATCH)
         put_string(menu_string[11],menu_x[11],menu_y[11]); /* match 32 color pcx name */
      else if (reduction_type == MERGE)
         put_string(menu_string[14],menu_x[11],menu_y[11]); /* match 32 color pcx name */
   }
   else
   {
      fg_setcolor(12);
      fg_box(187,251,40,50);

      fg_setcolor(15);
      if (reduction_type == MATCH)
         put_string(menu_string[12],menu_x[12],menu_y[12]);  /* match 224 color pcx name */
      else if (reduction_type == MERGE)
         put_string(menu_string[13],menu_x[11],menu_y[11]);  /* match 32 color pcx name */
   }

   if (reduction_type == MATCH || reduction_type == MERGE)
   {
      fg_setcolor(0);
      fg_rect(220,296,90,100);
      fg_setcolor(15);
      put_string(matchfile,223,97);
   }

   fg_setcolor(12);
   if (reduction_type == MATCH)
   {
      fg_box(132,208,73,83);
   }
   else if (reduction_type == MERGE)
   {
      fg_box(223,298,73,83);
   }
   else /* choose */
   {
      fg_box(7,119,73,83);
   }
}
/******************************************************************/
void reduce(int ncolors)
{
   unsigned long target,distance;
   unsigned long max_target;
   int color,match;
   unsigned int i,j,k;
   int empty;
   int nmatches;
   int nzeros;

   if (ncolors == 224)
      nmatches = 32;
   else
      nmatches = 225;

   fg_move(0,199);
   fg_getimage(buffer1,320,200);

   for (i = 0; i < 256; i++)
   {
      pixel_count[i] = 0L;

      /* start with everything matching itself */
      match_palette[i] = (unsigned char)i;
   }

   /* count how many of each color */
   for (i = 0; i < 320*200; i++)
      pixel_count[buffer1[i]]++;

   empty = 0;
   for (i = 0; i < 256; i++)
      if (pixel_count[i] == 0L) empty++;

   /* find two colors that are close to each other */
   for (max_target = 1; max_target < 63L*63L*63L; max_target*=2)
   {
      /* compare every color to every color greater than it */
      for (i = 0; i < 256*3; i+=3)
      {
         if (pixel_count[i/3] != 0)
         {
            target = 63L*63L*63L;
            for (j = i+3; j < 256*3; j+= 3)
            {
               if (pixel_count[j/3] != 0L)
               {
                  distance = 
                  (input_colors[i+2] - input_colors[j+2]) *
                  (input_colors[i+2] - input_colors[j+2]) 
                  +
                  (input_colors[i+1] - input_colors[j+1]) *
                  (input_colors[i+1] - input_colors[j+1]) 
                  +
                  (input_colors[i] - input_colors[j]) *
                  (input_colors[i] - input_colors[j]); 

                  if (distance < target)  /* closest match so far */
                  {
                     match = j/3;         
                     target = distance;   /* how close is it? */
                  }
               }
            }
            if (target < max_target)      /* within tolerance */
            {

               /* set all i colors to whichever j color matched */
               pixel_count[i/3] = 0L;     
               match_palette[i/3] = (unsigned char)match;

               /* if any colors matched i, match them to j */
               for (k = 0; k < j/3; k++)
               {
                  if (match_palette[k] == (unsigned char)(i/3))
                     match_palette[k] = (unsigned char)match;
               }
               empty++;
               if (empty >= nmatches) break;
            }
         }
      }

      /* update the image for this pass */
      for (i = 0; i < 64000; i++)
         buffer2[i] = match_palette[buffer1[i]];
      memcpy (buffer1,buffer2,(unsigned int)64000);
      fg_move(0,199);
      fg_putimage(buffer1,320,200);

      /* tally the pixels again */
      for (i = 0; i < 256; i++)
      {
         pixel_count[i] = 0L;

         /* each color matches itself again */
         match_palette[i] = (unsigned char)i;
      }

      /* count how many of each color */
      for (i = 0; i < 320*200; i++)
         pixel_count[buffer1[i]]++;

      /* we have reached our target -- enough empty palettes */
      if (empty >= nmatches) break;
   }

   if (ncolors == 224)
   {
      /* move all the colors to the last 224 */
      j = 32;
      for (i = 0; i < 256; i++)
      {
         if (pixel_count[i] > 0L)
         {
            match_palette[i] = (unsigned char)j;
      
            fg_setrgb(j,input_colors[i*3],
                        input_colors[i*3+1],
                     input_colors[i*3+2]);
            j++;
         }
      }
      /* set the first 32 colors to 0 */
      for (i = 0; i < 32; i++)
          fg_setrgb(i,0,0,0);
   }
   else
   {
      /* move all the colors to the first 32 */
      j = 1;
      for (i = 0; i < 256; i++)
      {
         if (pixel_count[i] > 0L)
         {
            match_palette[i] = (unsigned char)j;

            fg_setrgb(j,input_colors[i*3],
                        input_colors[i*3+1],
                        input_colors[i*3+2]);
            j++;
         }
      }
      /* set the first 224 colors to 0 */
      for (i = 32; i < 256; i++)
          fg_setrgb(i,0,0,0);
   }

   /* update the image one last time */
   for (i = 0; i < 64000; i++)
      buffer2[i] = match_palette[buffer1[i]];
   memcpy (buffer1,buffer2,(unsigned int)64000);
   fg_move(0,199);

   /* display the new image */
   fg_putimage(buffer1,320,200);
   return;
}
/******************************************************************/
void show_match_string()
{
   fg_setcolor(9);
   fg_rect(10,319,90,100);
   fg_setcolor(15);

   if (file_type == BACKGROUND && reduction_type == MATCH)
      /* match 224 color pcx name */
      put_string(menu_string[12],10,97);  
   else if (file_type == BACKGROUND && reduction_type == MERGE)
      /* match 32 color pcx name */
      put_string(menu_string[13],10,97);  
   else if (file_type == SPRITE && reduction_type == MATCH)
      /* match 32 color pcx name */
      put_string(menu_string[11],10,97);  
   else if (file_type == SPRITE && reduction_type == MERGE)
      /* match 32 color pcx name */
      put_string(menu_string[14],10,97);  

   fg_setcolor(0);
   fg_rect(220,296,90,100);
}
