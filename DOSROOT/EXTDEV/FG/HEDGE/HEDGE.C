/****************************************************************************\
*                                                                            *
*  Hedge.c                                                                   *
*                                                                            *
*  Copyright 1993 Diana Gruber. All rights reserved.                         *
*                                                                            *
*  This program is copyrighted freeware, distributed with source code.       *
*  Code is provided "as is" without any warranties. You may use portions     *
*  of this code in your own programs as long as you do not use more than     *
*  50% of the code in any one program.                                       *
*                                                                            *
*  This code is provided for instructional purposes. It requires Fastgraph   *
*  or Fastgraph/Light to link.                                               *
*                                                                            *
*  For more information, including the compilation and linking commands for  *
*  all supported compilers, please see the HEDGE.DOC file.                   *
*                                                                            *
\****************************************************************************/

#include "defs.h"
#define NMAZES 7

/****************************************************************************\
*                                                                            *
*  main -- all functions are in alphabetical order except this one           *
*                                                                            *
\****************************************************************************/

void main()
{
   register int i,j;
   int n;

   char *maze_name[] =
   {
      "maze001.lev",
      "maze002.lev",
      "maze003.lev",
      "maze004.lev",
      "maze005.lev",
      "maze006.lev",
      "maze007.lev"
   };

   /* open the attribute file and read the attributes */

   if ((tstream = fopen("hedge.att","rb")) == NULL)
   {
      sprintf(abort_string,"HEDGE.ATT not found.");
      abort_game();
   }
   fread(attributes,sizeof(char),240,tstream);
   fclose(tstream);

   /* initialize SVGA graphics */

   init_graphics();
   fg_tcmask(1);

   intro_screen();

   /* load the dub diner file on the hidden page */

   fg_setpage(HIDDEN);
   fg_erase();
   fg_move(80,60);
   fg_showpcx("DUBDINER.PCX",2);

   /* copy it to the logical page (EMS or XMS) */

   fg_copypage(HIDDEN,SPARE);

   /* display the maze file on the hidden page */

   fg_move(0,0);
   fg_showpcx("HEDGE.PCX",1);

   fg_setpage(VISUAL);
   for (n = 0; n < NMAZES; n++)
   {
      fg_setrgb(15,63,63,63);
      fg_setrgb(20,63,63,63);
      fg_mousevis(OFF);
      fg_copypage(SPARE,VISUAL);

      load_maze(maze_name[n]);

      for (i = 0; i <50; i++)
      {
         for (j = 0; j <37; j++)
            visited[i][j] = 0;
      }

      for (i = 0; i < 2000; i++)
         path[i] = -1;
      path_index = 1;

      flushkey();
      if (n == 0) help_window();

      fg_mousevis(ON);
      run_maze();
   }
   quit_graphics();
}

/****************************************************************************\
*                                                                            *
*  calc_truepath -- recursive algorithm to solve maze                        *
*                                                                            *
\****************************************************************************/

int calc_truepath(int i,int j)
{
   int tile,nexttile;
   int attr,nextattr;
   int x1,x2,y1,y2;
   int found;
   int index;
   int stall_time;
   int left,right,top,bottom;
   int horizontal,vertical;
   int nextcross;

   stall_time = clockspeed/4;
   visited[i][j] = TRUE;
   index = path_index;

   while(1)
   {
      fg_stall(stall_time);

      tile = layout[i][j];
      attr = attributes[tile];
      found = FALSE;

      x1 = i*16 + 6;
      x2 = x1 + 4;
      y1 = j*16 + 6;
      y2 = y1 + 4;

      left       = attr&LEFT;
      right      = attr&RIGHT;
      top        = attr&TOP;
      bottom     = attr&BOTTOM;
      vertical   = attr&VERTICAL;
      horizontal = attr&HORIZONTAL;

      if (horizontal || vertical)
      {
         if (path[index-1] == LEFT || path[index-1] == RIGHT)
         {
            top = FALSE; bottom = FALSE;
         }
         else if (path[index-1] == TOP || path[index-1] == BOTTOM)
         {
            left = FALSE; right = FALSE;
         }
      }

      /* check right */

      if (j < MAXCOLS-1 && !found && !(path[index-1] == LEFT))
      {
         nexttile = layout[i+1][j];
         nextattr = attributes[nexttile];
         nextcross = ((nextattr&VERTICAL) + (nextattr&HORIZONTAL));
         if (!visited[i+1][j] || (nextcross && (visited[i+1][j] != HORIZONTAL)))
         {
            if (right && nextattr&LEFT)
            {
               found = TRUE;
               path[index++] = RIGHT;
               i++;
               visited[i][j] = HORIZONTAL;
               x2 = i*16 + 10;
               if (vertical)
                 x1 += 9;
               if (nextattr&VERTICAL)
                 x2 -= 9;
            }
         }
      }

      /* check UP */

      if (j > 0 && !found && !(path[index-1] == BOTTOM))
      {
         nexttile = layout[i][j-1];
         nextattr = attributes[nexttile];
         nextcross = ((nextattr&VERTICAL) + (nextattr&HORIZONTAL));
         if (!visited[i][j-1] || (nextcross && (visited[i][j-1] != VERTICAL)))
         {
            if (top && nextattr&BOTTOM)
            {
               found = TRUE;
               path[index++] = TOP;
               j--;
               visited[i][j] = VERTICAL;
               y1 = j*16 + 6;
               if (nextattr&HORIZONTAL)
                 y1 += 9;
               if (horizontal)
                 y2 -= 9;
            }
         }
      }

      /* check down */

      if (j < MAXROWS-1 && !found && !(path[index-1] == TOP))
      {
         nexttile = layout[i][j+1];
         nextattr = attributes[nexttile];
         nextcross = ((nextattr&VERTICAL) + (nextattr&HORIZONTAL));
         if (!visited[i][j+1] || (nextcross && (visited[i][j+1] != VERTICAL)))
         {
            if (bottom && nextattr&TOP)
            {
               found = TRUE;
               path[index++] = BOTTOM;
               j++;
               visited[i][j] = VERTICAL;
               y2 = j*16 + 10;
               if (horizontal)
                 y1 += 9;
               if (nextattr&HORIZONTAL)
                 y2 -= 9;
            }
         }
      }

      /* check left */

      if (i > 0 && !found && !(path[index-1] == RIGHT))
      {
         nexttile = layout[i-1][j];
         nextattr = attributes[nexttile];
         nextcross = ((nextattr&VERTICAL) + (nextattr&HORIZONTAL));
         if (!visited[i-1][j] || (nextcross && (visited[i-1][j] != HORIZONTAL)))
         {
            if (left && nextattr&RIGHT)
            {
               found = TRUE;
               path[index++] = LEFT;
               i--;
               visited[i][j] = HORIZONTAL;
               x1 = i*16 + 6;
               if (nextattr&VERTICAL)
                 x1 += 9;
               if (vertical)
                 x2 -= 9;
            }
         }
      }

      /* adjacent tile found */

      if (found)
      {
         fg_setcolor(0);
         fg_rect(x1,x2,y1,y2);
         if (is_a_vertex(nexttile))
         {
            path_index = index;

            /* You are at a vertex, do a recursive function call */

            if (calc_truepath(i,j)) 
                return(TRUE);

            /* try again (vertices may have 2 or 3 paths) */

            else 
            {
               unfill_path(i,j,index);
               path_index = index;
               if (calc_truepath(i,j))
                   return(TRUE);
               else
               {
                   /* you are on the wrong path -- backtrack */

                   unfill_path(i,j,index);
               }
            }
         }
      }

      /* reached a dead end */

      else
      {
         n_nodes = index;
         return(FALSE);
      }

      /* reached end of path -- maze solved! */

      if (test_bit(nextattr,7) || test_bit(attr,7))
      {
         n_nodes = index;
         return(TRUE);
      }
   }
}

/****************************************************************************\
*                                                                            *
*  help_window -- press F1 for popup help                                    *
*                                                                            *
\****************************************************************************/

void help_window()
{
   fg_mousevis(OFF);
   fg_transfer(200,599,200,389,200,389,VISUAL,HIDDEN);

   fg_setcolor(7);
   fg_rect(200,599,200,389);
   fg_setcolor(1);
   fg_box(200,599,200,389);
   center_string("Hedge Row Help",400,220);

   fg_setcolor(0);
   put_string("Use the mouse to maneuver through the maze",230,240);
   put_string("from the blue square to the red square.",230,256);

   put_string("F1:",260,280);
   put_string("Help",320,280);

   put_string("N:",260,300);
   put_string("Next Maze",320,300);

   put_string("R:",260,320);
   put_string("Recursive Solution",320,320);

   put_string("C:",260,340);
   put_string("Cheat mode",320,340);

   put_string("Esc:",260,360);
   put_string("Exit",320,360);

   fg_setcolor(1);
   center_string("Press any key to continue",400,380);

   fg_waitkey();
   fg_transfer(200,599,200,389,200,389,HIDDEN,VISUAL);
   fg_mousevis(ON);
}

/****************************************************************************\
*                                                                            *
*  intro_screen -- display copyright information, etc.                       *
*                                                                            *
\****************************************************************************/

void intro_screen()
{
   fg_mousevis(OFF);
   fg_setcolor(7);
   center_string("Hedge Row Version 1.01",400,84);
   center_string("Copyright 1993 Diana Gruber. All rights reserved.",400,116);
   center_string("Written with Fastgraph programmer's graphics library.",400,148);
   center_string("Please wait...",400,300);
}

/****************************************************************************\
*                                                                            *
*  is_a_vertex -- check a tile to see if it is a vertex                      *
*                                                                            *
\****************************************************************************/

int is_a_vertex(int tile)
{
   int attr;
   int left,right,top,bottom;
   int horizontal,vertical;

   attr = attributes[tile];

   left   = ((attr&LEFT)>0);
   right  = ((attr&RIGHT)>0);
   top    = ((attr&TOP)>0);
   bottom = ((attr&BOTTOM)>0);

   vertical   = attr&VERTICAL;
   horizontal = attr&HORIZONTAL;

   if (vertical || horizontal)
      return(FALSE);

   if (left+right+top+bottom >= 3)
      return(TRUE);
   else
      return(FALSE);
}

/****************************************************************************\
*                                                                            *
*  load_maze -- read maze information from a file                            *
*                                                                            *
\****************************************************************************/

void load_maze(char *mazename)
{
   register int i,j;
   int nrows,ncols;
   int x,y,tile;
   char buffer[100];

   /* open the maze file and read the maze data */

   if ((tstream = fopen(mazename,"rb")) == NULL)
   {
      sprintf(abort_string,"%s not found.",mazename);
      abort_game();
   }

   fread(&ncols,sizeof(int),1,tstream);
   fread(&nrows,sizeof(int),1,tstream);

   for (i = 0; i < 50; i++)
   {
      fread(buffer,sizeof(char),nrows,tstream);
      memcpy(&layout[i][0],buffer,37);
   }
   fclose(tstream);

   /* display the maze tiles */

   fg_mousevis(OFF);
   for (i = 0; i < ncols; i++)
   {
      for (j = 0; j < nrows; j++)
      {
         x = i*16;
         y = j*16+15;
         tile = layout[i][j];
         put_tile(tile,x,y);
      }
   }
}

/****************************************************************************\
*                                                                            *
*  put_tile -- transfer a maze tile from the hidden page to the visual page  *
*                                                                            *
\****************************************************************************/

void put_tile(int tile,int x,int y)
{
   int x1,x2,y1,y2;

   x1 = (tile%20) * 16;
   x2 = x1+15;
   y1 = (tile/20) * 16+8;
   y2 = y1+15;

   fg_tcxfer(x1,x2,y1,y2,x,y,HIDDEN,VISUAL);
}

/****************************************************************************\
*                                                                            *
*  run_maze -- this is where all the user interaction happens                *
*                                                                            *
\****************************************************************************/

void run_maze()
{
   unsigned char key,aux;
   register int i,j;
   int solution;
   int xmouse,ymouse,buttons;
   int tile,attr;
   int x1,x2,x3,x4;
   int y1,y2,y3,y4;
   int xmin,xmax,ymin,ymax;
   int old_xmin,old_xmax,old_ymin,old_ymax;
   int old_xmouse,old_ymouse;
   int left,right,top,bottom;
   int horizontal,vertical;
   int direction;
   int old_i,old_j;
   int old_tile, old_attr;
   int norect;

   fg_mousevis(ON);

   old_xmin = 0; old_xmax = 0;
   old_ymin = 0; old_ymax = 0;

   solution = FALSE;

   fg_mouselim(0,799,0,599);
   fg_mousemov(20,8);
   old_i = 1;
   old_j = 0;
   direction = VERTICAL;

   fg_mousepos(&old_xmouse,&old_ymouse,&buttons);

   while(1)
   {
      fg_intkey(&key,&aux);
      if (key == 27)
         quit_graphics();
      else if (key == 'n' || key == 'N')
         return;
      else if (aux == F1)
         help_window();
      else if (key == 'r' || key == 'R')
      {
         fg_mousevis(OFF);
         calc_truepath(1,0);
         fg_getkey(&key,&aux);
         if (key == 27)
            quit_graphics();
         return;
      }
      else if (key == 'c' || key == 'C')
      {
         solution = !solution;
         if (solution)
            fg_setrgb(15,25,25,63);
         else
            fg_setrgb(15,63,63,63);
      }

      fg_mousepos(&xmouse,&ymouse,&buttons);
      i = xmouse/16;
      j = ymouse/16;

      if (i != old_i)
         direction = HORIZONTAL;
      else if (j != old_j)
         direction = VERTICAL;

      tile = layout[i][j];
      attr = attributes[tile];

      x1 = i*16-1;
      x2 = x1+7;
      x3 = x1+11;
      x4 = MIN(x1+17,799);
      x1 = MAX(i*16-1,0);

      y1 = j*16-1;
      y2 = y1+7;
      y3 = y1+11;
      y4 = MIN(y1+17,599);
      y1 = MAX(j*16-1,0);

      left       = attr&LEFT;
      right      = attr&RIGHT;
      top        = attr&TOP;
      bottom     = attr&BOTTOM;
      vertical   = attr&VERTICAL;
      horizontal = attr&HORIZONTAL;

      if (horizontal || vertical)
      {
         if (direction == HORIZONTAL)
         {
            top = FALSE; bottom = FALSE;
         }
         else if (direction == VERTICAL)
         {
            left = FALSE; right = FALSE;
         }
      }

      /* calculate extents of mouse limits */

      if (right && xmouse > x2)
      {
         if (i == MAXCOLS-1 || !(attributes[layout[i+1][j]]&LEFT))
            xmax = x3;
         else
            xmax = x4;
      }
      else
         xmax = x3;

      if (left && xmouse < x3)
      {
         if (i == 0 || !(attributes[layout[i-1][j]]&RIGHT))
            xmin = x2;
         else
            xmin = x1;
      }
      else
         xmin = x2;

      if (bottom && ymouse > y2)
      {
         if (j == MAXROWS-1 || !(attributes[layout[i][j+1]]&TOP))
            ymax = y3;
         else
            ymax = y4;
      }
      else
         ymax = y3;

      if (top && ymouse < y3)
      {
         if (j == 0 || !(attributes[layout[i][j-1]]&BOTTOM))
            ymin = y2;
         else
            ymin = y1;
      }
      else
         ymin = y2;

      /* correct for diagonals - upper left */

      if (xmin == x1 && ymin == y1)
      {
         if (xmouse <= x2)
            ymin = y2 - 3;
         else
            xmin = x2 - 3;
      }

      /* upper right */

      if (xmax == x4 && ymin == y1)
      {
         if (xmouse >= x3)
            ymin = y2 - 3;
         else
            xmax = x3 + 3;
      }

      /* lower left */

      if (xmin == x1 && ymax == y4)
      {
         if (xmouse <= x2)
            ymax = y3 + 3;
         else
            xmin = x2 - 3;
      }

      /* lower right */

      if (xmax == x4 && ymax == y4)
      {
         if (xmouse >= x3)
            ymax = y3 + 3;
         else
            xmax = x3 + 3;
      }

      fg_mouselim(xmin,xmax,ymin,ymax);

      /* draw the path only if the mouse has moved*/

      if (xmouse != old_xmouse || ymouse != old_ymouse)
      {

         /* going right */

         norect = FALSE;
         if (old_i < i)
         {
            old_tile = layout[i-1][j];
            old_attr = attributes[old_tile];
            if (old_attr&VERTICAL)
               xmin = x1;
            else
               xmin = x1 - 8;
            if (vertical)
               xmax = x2 - 5;
            else
               xmax = x3;
         }

         /* going left */

         else if (old_i > i)
         {
            old_tile = layout[i+1][j];
            old_attr = attributes[old_tile];
            if (old_attr&VERTICAL)
               xmax = x4 + 1;
            else
               xmax = x4 + 8;
            if (vertical)
               xmin = x3 + 5;
            else
               xmin = x2;
         }

         /* no horizontal movement */

         else
         {
            xmin = x2;
            xmax = x3;
         }


         /* going down */

         if (old_j < j)
         {
            old_tile = layout[i][j-1];
            old_attr = attributes[old_tile];
            if (old_attr&HORIZONTAL)
               ymin = y1;
            else
               ymin = y1 - 8;
            if (horizontal)
               ymax = y2 - 5;
            else
               ymax = y3;
         }

         /* going up */

         else if (old_j > j)
         {
            old_tile = layout[i][j+1];
            old_attr = attributes[old_tile];
            if (old_attr&HORIZONTAL)
               ymax = y4 + 1;
            else
               ymax = y4 + 8;
            if (horizontal)
               ymin = y3 + 5;
            else
               ymin = y2;
         }

         /* no vertical movement */

         else
         {
            ymin = y2;
            ymax = y3;
         }
         if (i == old_i && j == old_j)
            norect = TRUE;

         if (!norect)
         {
            fg_mousevis(OFF);
            fg_setcolor(7);
            if (old_xmin > 0) fg_rect(old_xmin,old_xmax,old_ymin,old_ymax);
            fg_setcolor(3);
            fg_rect(xmin,xmax,ymin,ymax);
            fg_mousevis(ON);

            old_xmin = xmin; old_xmax = xmax;
            old_ymin = ymin; old_ymax = ymax;
         }
      }

      old_xmouse = xmouse;
      old_ymouse = ymouse;
      old_i = i;
      old_j = j;
   }
}

/****************************************************************************\
*                                                                            *
* test_bit -- used to check for tile attributes                              *
*                                                                            *
\****************************************************************************/

test_bit(int num,int bit)
{
   return((_rotr(num,bit))&1);
}

/****************************************************************************\
*                                                                            *
*  unfill_path -- change the color back to white                             *
*                                                                            *
\****************************************************************************/

int unfill_path(int i,int j,int n)
{
   int index;
   int x1,x2,y1,y2;
   int tile;
   int attr;

   fg_setcolor(7);
   for (index = n; index < n_nodes; index++)
   {
      x1 = i*16 + 6;
      x2 = x1 + 4;
      y1 = j*16 + 6;
      y2 = y1 + 4;

      switch(path[index])
      {
         case LEFT:
            tile = layout[i][j];
            attr = attributes[tile];
            if (attr&VERTICAL)
              x2 -= 9;

            i--;
            x1 = i*16 + 6;

            tile = layout[i][j];
            attr = attributes[tile];
            if (attr&VERTICAL)
               x1 += 9;

            break;
         case RIGHT:
            tile = layout[i][j];
            attr = attributes[tile];
            if (attr&VERTICAL)
               x1 += 9;

            i++;
            x2 = i*16 + 10;

            tile = layout[i][j];
            attr = attributes[tile];
            if (attr&VERTICAL)
               x2 -= 9;

            break;
         case TOP:
            tile = layout[i][j];
            attr = attributes[tile];
            if (attr&HORIZONTAL)
              y2 -= 9;

            j--;
            y1 = j*16 + 6;

            tile = layout[i][j];
            attr = attributes[tile];
            if (attr&HORIZONTAL)
              y1 += 9;

            break;
         case BOTTOM:
            tile = layout[i][j];
            attr = attributes[tile];
            if (attr&HORIZONTAL)
              y1 += 9;

            j++;
            y2 = j*16 + 10;

            tile = layout[i][j];
            attr = attributes[tile];
            if (attr&HORIZONTAL)
              y2 -= 9;

            break;
         default:
            return(FALSE);
      }
      fg_rect(x1,x2,y1,y2);
   }
   return(TRUE);
}
