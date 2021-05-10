/******************************************************************\
*  motion.c -- Tommy game source code file                         *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

#include "gamedefs.h"
/******************************************************************/
int can_move_down(OBJp objp)
{
   /* can the object fall? */

   int tile_x,tile_y,tile_num;

   /* test left side */
   tile_x = (objp->x)/16;
   if (tile_x < 0)
      return(FALSE);

   tile_y = (objp->y+1)/16;
   tile_num = (int)background_tile[tile_x+1][tile_y];

   /* are we at the bottom of the map? */
   if (tile_y >= nrows)
      return(FALSE);

   /* is the tile solid on the top? */
   if (test_bit(background_attributes[tile_num],0))
      return(FALSE);

   /* test the right side too */
   tile_x = (objp->x + objp->sprite->bound_width)/16;
   tile_num = (int)background_tile[tile_x-1][tile_y];
   return (!test_bit(background_attributes[tile_num],0));
}
/******************************************************************/
int can_move_left(OBJp objp)
{
   int tile_x,tile_y,tile_num;

   /* test the bottom of the sprite */
   tile_x = (objp->x-1)/16;
   if (tile_x <= 0)
      return(FALSE);
   tile_y = objp->y/16;
   tile_num = (int)background_tile[tile_x][tile_y];

   /* is the tile solid on the right? */
   if (test_bit(background_attributes[tile_num],3))
      return(FALSE);

   /* check the top of the sprite too */
   tile_y = (objp->y - objp->sprite->height)/16;
   tile_num = (int)background_tile[tile_x][tile_y];
   return (!test_bit(background_attributes[tile_num],2));
}
/******************************************************************/
int can_move_right(OBJp objp)
{
   int tile_x,tile_y,tile_num;

   tile_x = (objp->x + objp->sprite->bound_width)/16;
   if (tile_x >= ncols-1)
      return(FALSE);

   /* test the bottom of the sprite */
   tile_y = objp->y/16;
   tile_num = (int)background_tile[tile_x][tile_y];

   /* is the tile solid on the left? */
   if (test_bit(background_attributes[tile_num],2))
      return(FALSE);

   /* check top of sprite too */
   tile_y = (objp->y - objp->sprite->height)/16;
   tile_num = (int)background_tile[tile_x][tile_y];
   return (!test_bit(background_attributes[tile_num],3));
}
/******************************************************************/
int can_move_up(OBJp objp)
{
   int tile_x,tile_y,tile_num;

   tile_x = objp->x/16;      /* test left side */
   tile_y = (objp->y-objp->sprite->height-1)/16;
   if (tile_y < 0)           /* test top of map */
      return(FALSE);

   tile_num = (int)background_tile[tile_x][tile_y];

   /* is the tile solid on the bottom? */
   if (test_bit(background_attributes[tile_num],1))
      return(FALSE);

   /* test the right side too */
   tile_x = (objp->x + objp->sprite->width)/16;
   tile_num = (int)background_tile[tile_x][tile_y];

   return (!test_bit(background_attributes[tile_num],1));
}
/******************************************************************/
int collision_detection (OBJp objp1,OBJp objp2)
{
   int xmin1,xmax1,xmin2,xmax2;
   int ymin1,ymax1,ymin2,ymax2;

   /* x coordinates of object 1 */
   xmin1 = objp1->x+objp1->sprite->xoffset;
   xmax1 = xmin1+objp1->sprite->width;

   /* x coordinates of object 2 */
   xmin2 = objp2->x+objp2->sprite->xoffset;
   xmax2 = xmin2+objp2->sprite->width;

   /* y coordinates of object 1 */
   ymax1 = objp1->y+objp1->sprite->yoffset;
   ymin1 = ymax1-objp1->sprite->height;

   /* y coordinates of object 2 */
   ymax2 = objp2->y+objp2->sprite->yoffset;
   ymin2 = ymax2-objp2->sprite->height;

   /* object 2 entirely to the left of object 1 */
   if (xmax2 < xmin1) return(FALSE);

   /* object 2 entirely to the right of object 1 */
   if (xmin2 > xmax1) return(FALSE);

   /* object 2 entirely to the below object 1 */
   if (ymax2 < ymin1) return(FALSE);

   /* object 2 entirely to the above object 1 */
   if (ymin2 > ymax1) return(FALSE);

   /* the objects overlap */
   return(TRUE);
}
/******************************************************************/
int how_far_down(OBJp objp,int n)
{
   register int i;
   register int temp;

   temp = objp->y;        /* save the current position */

   /* increment the position until you can't move right any further */
   for (i = 0; i < n; i++)
   {
      objp->y++;
      if (!can_move_down(objp))
      {
          objp->y = temp;
          return(i);
      }
   }
   objp->y = temp;        /* restore the current position */
   return(n);             /* return how far right */
}
/******************************************************************/
int how_far_left(OBJp objp,int n)
{
   register int i;
   register int temp;

   temp = objp->x;       /* save the current position */

   /* increment the position until you can't move left any further */
   for (i = 0; i < n; i++)
   {
      objp->x--;
      if (!can_move_left(objp))
      {
         objp->x = temp;
         return(i);
      }
   }
   objp->x = temp;      /* restore the current position */
   return(n);           /* return how far left */
}
/******************************************************************/
int how_far_right(OBJp objp,int n)
{
   register int i;
   register int temp;

   temp = objp->x;     /* save the current position */

   /* increment the position until you can't move right any further */
   for (i = 0; i < n; i++)
   {
      objp->x++;
      if (!can_move_right(objp))
      {
         objp->x = temp;
         return(i);
      }
   }

   objp->x = temp;     /* restore the current position */
   return(n);          /* return how far right */
}
/******************************************************************/
int how_far_up(OBJp objp,int n)
{
   register int i;
   register int temp;

   temp = objp->y;     /* save the current position */

   /* increment the position until you can't move right any further */
   for (i = 0; i > n; i--)
   {
      objp->y--;
      if (!can_move_up(objp))
      {
          objp->y = temp;
          return(i);
      }
   }
   objp->y = temp;    /* restore the current position */
   return(n);         /* return how far right */
}

/******************************************************************/

test_bit(char num,int bit)
{
   /* test bit flags, used for tile attributes */
   return((num >> bit) & 1);
}
