/******************************************************************\
*  action.c -- Tommy game action functions source code             *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

void near bullet_go(OBJp objp)
{
   int min_x,max_x;
   register int i;

   /* increment the bullet's horizontal position */
   objp->x += objp->xspeed;

   /* collision detection */
   for (i = 0; i < nenemies; i++)
   {
      if (enemy[i]->frame < 6 && objp->x>enemy[i]->x
          && objp->x<enemy[i]->x+enemy[i]->sprite->width
          && objp->y<enemy[i]->y
          && objp->y>enemy[i]->y-enemy[i]->sprite->height)
      {
         launch_floating_points(enemy[i]);
         enemy[i]->frame = 6;
         objp->action = kill_bullet;
      }
   }

   /* check if the bullet has moved off the screen */
   max_x = (tile_orgx + objp->tile_xmax) * 16;
   min_x = (tile_orgx + objp->tile_xmin) * 16;

   /* if it has moved off the screen, kill it by setting the action
      function to kill for the next frame */

   if (objp->x > max_x || objp->x < min_x)
      objp->action = kill_bullet;

   if (objp->direction == RIGHT && !can_move_right(objp))
      objp->action = kill_bullet;
   else if (objp->direction == LEFT && !can_move_left(objp))
      objp->action = kill_bullet;
}
/******************************************************************/
void near enemy_hopper_go(OBJp objp)
{
   if (objp->frame > 4)   /* is this enemy dying? */
   {
      /* after 100 frames, kill this enemy off */
      objp->frame++;
      if (objp->frame > 100)
         objp->action = kill_enemy;
      objp->sprite = enemy_sprite[5];

      /* enemy can fall while dying */
      objp->yspeed = how_far_down(objp,12);
      if (objp->yspeed > 0)
         objp->y += objp->yspeed;

      /* no point in doing anything else while dying */
      return;
   }

   /* this enemy moves every 12 clock ticks */
   objp->time += delta_time;
   if (objp->time < 12)
      return;
   else
      objp->time = 0;

   objp->yspeed = how_far_down(objp,12);    /* falling? */
   if (objp->yspeed > 0)
      objp->y += objp->yspeed;
   else
   {
      /* increment the object's horizontal position */
      if (objp->direction == LEFT)
      {
         if (!can_move_left(objp))
         {
            objp->direction = RIGHT;
            objp->xspeed = 12;
         }
      }
      else if (objp->direction == RIGHT)
      {
         if (!can_move_right(objp))
         {
            objp->direction = LEFT;
            objp->xspeed = -12;
         }
      }
      objp->x += objp->xspeed;
   }
   objp->frame = 7-objp->frame;           /* increment the frame */
   objp->sprite = enemy_sprite[objp->frame];

   /* if the player hasn't been hit recently, can we hit him now? */
   if (!player_blink)
   {
      if (collision_detection(objp, player) && !kicking)
      {
         player_blink = TRUE;             /* make the player blink */
         nhits++;                         /* seven hits per life */
         if (nhits > 7)
         {
            nlives--;
            if (nlives == 0)              /* three lives per game */
               nlives = 3;
            nhits = 0;
         }

         /* update the action function for the score */
         score->action = update_score;
      }
   }
}
/******************************************************************/
void near enemy_scorpion_go(OBJp objp)
{
   if (objp->frame > 1)                   /* is this enemy is dying? */
   {
      objp->frame++;

      /* after 100 frames, kill this enemy off */
      if (objp->frame > 100)
         objp->action = kill_enemy;

      objp->sprite = enemy_sprite[2];

      /* enemy can fall while dying */
      objp->yspeed = how_far_down(objp,12);
      if (objp->yspeed > 0)
         objp->y += objp->yspeed;

      /* no point in doing anything else while dying */
      return;
   }

   /* this enemy moves every 16 clock ticks */
   objp->time += delta_time;
   if (objp->time < 16)
      return;
   else
      objp->time = 0;

   objp->yspeed = how_far_down(objp,12);  /* falling? */
   if (objp->yspeed > 0)
      objp->y += objp->yspeed;
   else
   {
      /* increment the object's horizontal position */
      if (objp->direction == LEFT)
      {
         if (!can_move_left(objp))
         {
            objp->direction = RIGHT;
            objp->xspeed = 12;
         }
      }
      else if (objp->direction == RIGHT)
      {
         if (!can_move_right(objp))
         {
            objp->direction = LEFT;
            objp->xspeed = -12;
         }
      }
      objp->x += objp->xspeed;
   }
   objp->frame = 1-objp->frame;           /* increment frame */
   objp->sprite = enemy_sprite[objp->frame];

   /* if the player hasn't been hit recently, can we hit him now? */
   if (!player_blink)
   {
      if (collision_detection(objp, player) && !kicking)
      {
         player_blink = TRUE;             /* make the player blink */
         nhits++;                         
         if (nhits > 7)                   /* seven hits per life */
         {
            nlives--;
            if (nlives == 0)              /* three lives per game */
               nlives = 3;
            nhits = 0;
         }

         /* update the score box */
         score->action = update_score;
      }
   }
}
/******************************************************************/
void near floating_points_go(OBJp objp)
{
   /* update the vertical position */
   objp->y += objp->yspeed;

   /* score goes up 75 frames, then disappears */
   objp->frame++;
   if (objp->frame > 75)
      objp->action = kill_object;
}
/******************************************************************/
void near kill_bullet(OBJp objp)
{
   /* decrement the bullet count and kill the bullet */
   nbullets--;
   kill_object(objp);
}
/******************************************************************/
void near kill_enemy(OBJp objp)
{
   register int i;
   int enemy_no;

   for (i = 0; i < nenemies; i++)        /* which enemy is it? */
   {
      if (enemy[i] == objp)
      {
         enemy_no = i;
         break;
      }
   }
   nenemies--;                           /* decrement the enemy count */
   for (i = enemy_no; i < nenemies; i++) /* update the array */
      enemy[i] = enemy[i+1];
   enemy[nenemies] = (OBJp)NULL;         /* last enemy points to NULL */
   kill_object(objp);                    /* remove node from list */
   player_score += 100;                  /* increment the score */
   score->action = update_score;
}
/******************************************************************/
void near kill_object(OBJp objp)         /* remove node from list */
{
   OBJp node;

   node = objp;
   if (node == bottom_node)              /* remove bottom node */
   {
      bottom_node = node->next;
      if (bottom_node != (OBJp) NULL)
         bottom_node->prev = (OBJp)NULL;
   }
   else if (node == top_node)            /* remove top node */
   {
      top_node = node->prev;
      top_node->next = (OBJp)NULL;
   }
   else                                  /* remove middle node */
   {
      node->prev->next = node->next;
      node->next->prev = node->prev;
   }
   free(node);
}
/******************************************************************/
void near launch_bullet()                /* start a new bullet */
{
   OBJp node;

   if (nbullets > 9) return;             /* max 9 bullets */

   node = (OBJp)malloc(sizeof(OBJ)+3);   /* allocate space */
   if (node == (OBJp)NULL) return;

   if (player->direction == RIGHT)       /* assign values */
   {
      node->direction = RIGHT;
      node->xspeed = 13;
      if (player->sprite == tom_jump[2])  /* jumping */
      {
         node->x = player->x+player->sprite->xoffset+46-node->xspeed;
         node->y = player->y-25;
      }
      else if (player->sprite == tom_jump[3]) /* falling */
      {
         node->x = player->x+player->sprite->xoffset+46-node->xspeed;
         node->y = player->y-25;
      }
      else if (fg_kbtest(KB_RIGHT))      /* running */
      {
         node->x = player->x+player->sprite->xoffset+40-node->xspeed;
         node->y = player->y-26;
      }
      else                               /* standing */
      {
         node->x = player->x+player->sprite->xoffset+40-node->xspeed;
         node->y = player->y-28;
      }
   }
   else
   {
      node->direction = LEFT;
      node->xspeed = -13;
      node->x = player->x+player->sprite->xoffset-node->xspeed-5;
      if (player->sprite == tom_jump[2])      /* jumping */
         node->y = player->y-25;
      else if (player->sprite == tom_jump[3]) /* falling */
         node->y = player->y-25;
      else if (fg_kbtest(KB_LEFT))           /* running */
         node->y = player->y-26;
      else                                   /* standing */
         node->y = player->y-28;
   }
   node->yspeed    = 0;
   node->tile_xmin = 1;
   node->tile_xmax = 21;
   node->tile_ymin = 0;
   node->tile_ymax = 14;
   node->sprite = tom_shoot[6];              /* assign the sprite */

   node->action = bullet_go;                 /* assign action function */

   /* insert the new object at the top of the linked list */
   if (bottom_node == (OBJp)NULL )
   {
      bottom_node = node;
      node->prev = (OBJp)NULL;
   }
   else
   {
      node->prev = top_node;
      node->prev->next = node;
   }
   top_node = node;
   node->next = (OBJp)NULL;

   nbullets++;                               /* increment bullet count */
}
/******************************************************************/
void near launch_enemy(int x, int y, int type)  /* start a new enemy */
{
   OBJp node;

   node = (OBJp)malloc(sizeof(OBJ));         /* allocate space */
   if (node == (OBJp)NULL) return;

   node->direction = RIGHT;                  /* assign values */
   node->x = x;
   node->y = y;
   node->xspeed = 8;
   node->yspeed = 0;
   node->tile_xmin = 1;
   node->tile_xmax = 21;
   node->tile_ymin = 0;
   node->tile_ymax = 14;
   node->time = 0;

   /* assign the sprite and action function */
   if (type == 0)
   {
      node->frame = 0;
      node->action = enemy_scorpion_go;
   }
   else
   {
      node->frame = 3;
      node->action = enemy_hopper_go;
   }
   node->sprite = enemy_sprite[node->frame];

   /* insert the new object at the top of the linked list */
   if (bottom_node == (OBJp)NULL )
   {
      bottom_node = node;
      node->prev = (OBJp)NULL;
   }
   else
   {
      node->prev = top_node;
      node->prev->next = node;
   }
   top_node = node;
   node->next = (OBJp)NULL;

   enemy[nenemies] = node;                   /* update enemy array */
   nenemies++;                               /* increment enemy counter */
}
/******************************************************************/
void near launch_floating_points(OBJp objp)
{
   OBJp node;

   node = (OBJp)malloc(sizeof(OBJ)+3);       /* allocate space */
   if (node == (OBJp)NULL) return;

   node->direction = RIGHT;                  /* assign values */
   node->xspeed = 0;
   node->yspeed = -1;
   node->x = objp->x+16;
   node->y = objp->y-8;
   node->frame = 0;
   node->tile_xmin = 1;
   node->tile_xmax = 21;
   node->tile_ymin = 0;
   node->tile_ymax = 14;
   node->sprite = tom_score[2];              /* assign the sprite */
   node->action = floating_points_go;        /* assign action function */

   /* insert the new object at the top of the linked list */
   if (bottom_node == (OBJp)NULL )
   {
      bottom_node = node;
      node->prev = (OBJp)NULL;
   }
   else
   {
      node->prev = top_node;
      node->prev->next = node;
   }
   top_node = node;
   node->next = (OBJp)NULL;
}
/******************************************************************/
void near player_begin_fall(OBJp objp)
{
   /* called once at the start of a fall */

   objp->yspeed = 1;                         /* initialize variables */
   vertical_thrust = 0;
   shoot_time = 0;

   /* any thrust from the arrow keys? */
   if (fg_kbtest(KB_LEFT) || fg_kbtest(KB_RIGHT))
      forward_thrust = 100;
   else
      forward_thrust = 0;

   if (objp->direction == LEFT)
      tom_jump[3]->xoffset = -10;
   else
      tom_jump[3]->xoffset = -0;

   if (fg_kbtest(KB_ALT))                   /* shooting while falling */
      objp->frame = 3;
   else
      objp->frame = 1;

   objp->sprite = tom_jump[objp->frame];    /* assign the sprite */
   objp->action = player_fall;              /* assign action function */
}
/******************************************************************/
void near player_begin_jump(OBJp objp)
{
   /* called once at the start of a jump */

   objp->yspeed = -15;                      /* initialize variables */
   objp->frame = 0;
   shoot_time = 0;

   if (fg_kbtest(KB_LEFT) || fg_kbtest(KB_RIGHT)) /* walking? */
      forward_thrust = 50;
   else
      forward_thrust = 0;

   if (objp->direction == LEFT)
      tom_jump[3]->xoffset = 25;
   else
      tom_jump[3]->xoffset = 0;

   objp->sprite = tom_jump[objp->frame];    /* assign sprite */
   objp->action = player_jump;              /* assign action function */
}
/******************************************************************/
void near player_begin_kick(OBJp objp)
{
   /*  called once at the start of a kick */

   int i;

   kicking = TRUE;                          /* initialize variables */
   objp->time = 0;
   nkicks = 0;

   /* is this a left (backward) or a right (forward) kick? */
   if (objp->direction == LEFT)
   {
      objp->frame = 0;
      kick_frame = 3;
      kick_basey = objp->y;
      objp->sprite = tom_kick[objp->frame]; /* assign sprite */

      /* back him up a little if needed */
      player->x += 36;
      for (i = 0; i < 36; i++)
      if (can_move_left(player))
         player->x--;
   }
   else
   {
      objp->frame = 6;
      kick_frame = 7;
      kick_basey = objp->y;
      objp->sprite = tom_kick[objp->frame]; /* assign sprite */

      /* back him up a little if needed */
      player->x -= 24;
      for (i = 0; i < 24; i++)
      if (can_move_right(player))
         player->x++;
   }
   objp->action = player_kick;              /* assign action function */
}
/******************************************************************/
void near player_begin_shoot(OBJp objp)
{
   /* called once at the start of shooting */

   register int i;

   objp->frame = 0;                         /* initialize variables */
   objp->time = 0;
   nshots = 0;

   if (objp->direction == RIGHT)
   {
      tom_shoot[0]->xoffset = 2;
      tom_shoot[1]->xoffset = 2;
      tom_shoot[2]->xoffset = 2;

      /* back him up a little if needed */
      if (fg_kbtest(KB_RIGHT))              /* running while shooting? */
      {
         objp->sprite = tom_shoot[3];
         player->x -= 24;
         for (i = 0; i < 24; i++)
         if (can_move_right(player))
            player->x++;
      }
      else
         objp->sprite = tom_shoot[0];       /* assign sprite */
   }
   else
   {
      tom_shoot[0]->xoffset = -1;
      tom_shoot[1]->xoffset = -20;
      tom_shoot[2]->xoffset = -15;
      if (fg_kbtest(KB_LEFT))               /* running while shooting? */
         objp->sprite = tom_shoot[3];       /* assign sprite */
      else
         objp->sprite = tom_shoot[0];
   }
   objp->action = player_shoot;             /* assign action function */
}
/******************************************************************/
void near player_fall(OBJp objp)
{
   int tile_x,tile_y;

   /* less than 5 clock ticks? Then skip this function */
   objp->time += delta_time;
   shoot_time += delta_time;
   if (objp->time > 5)
      objp->time = 0;
   else
      return;

   if (fg_kbtest(KB_ALT))                   /* shooting while falling? */
   {
      objp->frame = 3;

      /* start a new bullet every 15 clock ticks */
      if (shoot_time > 15)
      {
         launch_bullet();
         shoot_time = 0;
      }
   }
   else
      objp->frame = 1;

   objp->sprite = tom_jump[objp->frame];    /* assign sprite */

   /* increase the rate of speed of the fall */
   if (objp->yspeed < 15)
      objp->yspeed += (vertical_thrust++);

   /* vertical position is based on yspeed */
   objp->y += objp->yspeed;

   /* check the arrow keys, starting with left arrow */
   if (objp->direction == LEFT)
   {
      /* horizontal speed */
      if (fg_kbtest(KB_LEFT))
      {
         objp->xspeed = -1;
         if (forward_thrust > 50)
            objp->xspeed *= 3;
         else if (forward_thrust > 0)
            objp->xspeed *= 2;
      }
      else
         objp->xspeed = 0;

      /* check for walls, etc. */
      objp->xspeed = -how_far_left(objp,-objp->xspeed);

      /* increment the x position according to the speed */
      objp->x += objp->xspeed;

      /* are we still on visible screen? If not, scroll */
      tile_x = objp->x/16 - tile_orgx;
      if (tile_x < objp->tile_xmin)
         scroll_left(-objp->xspeed);
   }

   /* same thing for right arrow key */
   else
   {
      if (fg_kbtest(KB_RIGHT))
      {
         objp->xspeed = 1;
         if (forward_thrust > 50)
            objp->xspeed *= 3;
         else if (forward_thrust > 0)
            objp->xspeed *= 2;
      }
      else
         objp->xspeed = 0;

      tom_jump[3]->xoffset = 0;
      objp->direction = RIGHT;
      objp->xspeed = how_far_right(objp,objp->xspeed);
      objp->x += objp->xspeed;

      /* are we still on visible screen? If not, scroll */
      tile_x = objp->x/16 - tile_orgx;
      if (tile_x > objp->tile_xmax)
         scroll_right(objp->xspeed);
   }

   /* decrement the forward thrust */
   forward_thrust--;

   /* are we close to the bottom of the screen? If so, scroll */
   tile_y = objp->y/16 - tile_orgy;
   if (tile_y > objp->tile_ymax)
      scroll_down(objp->yspeed);

   /* have we hit a solid tile yet? If so, stop falling */
   if (!can_move_down(objp))
   {
      objp->y = ((objp->y+1)/16) * 16; /* land on top of tile */
      objp->yspeed = 0;
      objp->action = player_stand;
   }
}
/******************************************************************/
void near player_jump(OBJp objp)
{
   int tile_x,tile_y;

   /* increment the timer, if it is less than 5, skip it */
   objp->time += delta_time;
   shoot_time += delta_time;
   if (objp->time > 5L)
      objp->time = 0;
   else
      return;

   /* check for arrow keys, left arrow first */
   if (fg_kbtest(KB_LEFT))
   {
      objp->direction = LEFT;
      objp->xspeed = -3;

      /* forward thrust gives a little boost at start of jump */
      if (forward_thrust > 30)
         objp->xspeed *= 4;
      else if (forward_thrust > 0)
         objp->xspeed *= 2;

      /* move left, checking for walls, etc. */
      objp->xspeed = -how_far_left(objp,-objp->xspeed);
      objp->x += objp->xspeed;

      /* need to scroll the screen left? */
      tile_x = objp->x/16 - tile_orgx;
      if (tile_x < objp->tile_xmin)
         scroll_left(-objp->xspeed);
   }

   /* same for right arrow key */
   else if (fg_kbtest(KB_RIGHT))
   {
      objp->xspeed = 3;
      if (forward_thrust > 50)
         objp->xspeed *= 4;
      else if (forward_thrust > 0)
         objp->xspeed *= 2;
      objp->direction = RIGHT;
      objp->xspeed = how_far_right(objp,objp->xspeed);

      tile_x = objp->x/16 - tile_orgx;
      if (tile_x > objp->tile_xmax)
         scroll_right(objp->xspeed);
      objp->x += objp->xspeed;
   }

   /* decrement forward thrust */
   forward_thrust--;

   /* additional upward thrust if you hold down the ctrl key */
   if (fg_kbtest(KB_CTRL))
      objp->yspeed++;
   else
      objp->yspeed/=4;

   /* check bumping head on ceiling */
   objp->yspeed = how_far_up(objp,objp->yspeed);
   objp->y += objp->yspeed;

   /* check if we are shooting */
   if (fg_kbtest(KB_ALT))
   {
      /* Tommy's jumping and shooting frame */
      objp->frame = 2;

      /* space the bullets 15 clock ticks apart */
      if (shoot_time > 15)
      {
         launch_bullet();
         shoot_time = 0;
      }
   }

   /* not shooting, just use tommy jumping frame */
   else
      objp->frame = 0;

   /* set sprite to the correct frame */
   objp->sprite = tom_jump[objp->frame];

   /* too close to top of screen? scroll the screen up */
   tile_y = objp->y/16 - tile_orgy;
   if (tile_y < objp->tile_ymin)
      scroll_up(-objp->yspeed);

   /* reached top of arc? Tommy start descent */
   if (objp->yspeed >= 0)
      objp->action = player_begin_fall;
}
/******************************************************************/
void near player_kick(OBJp objp)
{
   register int i;
   int tile_x,tile_y;

   /* collision detection -- did we kick an enemy? */
   for (i = 0; i < nenemies; i++)
   {
      /* frame 6 is the enemy hit frame. enemies are only hit once */
      if (enemy[i]->frame < 6 && collision_detection (objp,enemy[i]))
      {
         /* if you are kicking left, you can only hit enemy
            left of you */

         if (objp->direction == LEFT && enemy[i]->x < objp->x)
         {
            launch_floating_points(enemy[i]);
            enemy[i]->frame = 6;
         }

         /* likewise, right kicks kill enemies on the right */
         else if (objp->direction == RIGHT && enemy[i]->x > objp->x)
         {
            launch_floating_points(enemy[i]);
            enemy[i]->frame = 6;
         }
      }
   }

   /* increment the frame every 10 clock ticks */
   objp->time += delta_time;
   if (objp->time > 10)
   {
      /* case of the left (backwards) kick */
      if (objp->direction == LEFT)
      {
         /* where are we in this kick? */
         if (objp->frame == kick_frame && nkicks < 4
             && fg_kbtest(KB_SPACE))
         {
             /* keep kicking */
         }

         else
         {
            /* increment the frame */
            objp->frame++;

            /* end of kick */
            if (objp->frame > 5)
            {
               objp->y = kick_basey; /* end kick where you started */
               objp->sprite = tom_stand[0];
               kicking = FALSE;

               /* new action function */
               objp->action = player_stand;
            }

            /* still kicking, set the sprite */
            else
            {
               objp->sprite = tom_kick[objp->frame];

               /* horizontal motion */
               if (can_move_left(objp))
               {
                  if (fg_kbtest(KB_LEFT))
                     objp->xspeed = -3;
                  else
                     objp->xspeed = -1;

                  objp->x += objp->xspeed;

                  /* moved past edge of screen? scroll left */
                  tile_x = objp->x/16 - tile_orgx;
                  if (tile_x < objp->tile_xmin)
                     scroll_left(-objp->xspeed);
               }
            }
         }
      }

      /* case of the right (forward) kick */
      else
      {
         /* choose frame */
         if (objp->frame == kick_frame && nkicks < 4
             && fg_kbtest(KB_SPACE))
         {
             /* keep kicking */
         }
         else
         {
            objp->frame++;
            if (objp->frame > 9)
            {
               objp->y = kick_basey; /* end kick where you started */
               objp->sprite = tom_stand[0];
               kicking = FALSE;
               objp->action = player_stand;
            }
            else
            {
               if (objp->frame > 8)
               {
                  objp->sprite = tom_stand[0];
               }
               else if (objp->frame > 7)
               {
                  objp->sprite = tom_kick[6];
               }
               else
                  objp->sprite = tom_kick[objp->frame];

               /* horizontal motion */
               if (can_move_right(objp))
               {
                  if (fg_kbtest(KB_RIGHT))
                     objp->xspeed = 3;
                  else
                     objp->xspeed = 1;

                  objp->xspeed = how_far_right(objp,objp->xspeed);
                  objp->x += objp->xspeed;

                  tile_x = objp->x/16 - tile_orgx;
                  if (tile_x > objp->tile_xmax)
                     scroll_right(objp->xspeed);

               }
            }
         }
      }

      /* vertical motion */
      if (objp->frame == kick_frame)
      {
         /* put a little vertical bounce in the kick */
         if (objp->y == kick_basey)
         {
            objp->yspeed = -3;

            /* barrier above? */
            objp->yspeed = how_far_up(objp,objp->yspeed);
            objp->y += objp->yspeed;

            /* need to scroll up? */
            tile_y = objp->y/16 - tile_orgy;
            if (tile_y < objp->tile_ymin)
               scroll_up(-objp->yspeed);
         }
         else
         {
            objp->y = kick_basey;
            nkicks++;
         }
      }

      /* falling? */
      if (objp->y == kick_basey && can_move_down(objp))
      {
         kicking = FALSE;
         objp->action = player_begin_fall;
      }

      /* set the timer back to 0 */
      objp->time = 0;
   }
}
/******************************************************************/
void near player_run(OBJp objp)
{
   int tile_x;

   /* case where the player is facing left */
   if (objp->direction == LEFT)
   {
      /* gradually increase the speed */
      if (objp->xspeed > -8)
         objp->xspeed--;

      /* change the horizontal position according to the speed */
      if (can_move_left(objp))
      {
         objp->x += objp->xspeed;
         tile_x = objp->x/16 - tile_orgx;

         /* if you have moved out of the visible area, scroll left */
         if (tile_x < objp->tile_xmin)
            scroll_left(-objp->xspeed);
      }
   }

   /* case where the player is facing right */
   else
   {
      if (objp->xspeed < 8)
         objp->xspeed++;

      if (can_move_right(objp))
      {
         objp->x += objp->xspeed;
         tile_x = objp->x/16 - tile_orgx;
         if (tile_x > objp->tile_xmax)
            scroll_right(objp->xspeed);
      }
   }

   /* is it time to increment the the walking stage yet? */
   objp->time += delta_time;
   if (objp->time > 3)
   {
      objp->time = 0;
      objp->frame++;

      /* it's a six-stage walk */
      if (objp->frame > 5) objp->frame = 0;
      objp->sprite = tom_run[objp->frame];
   }

   /* are we pressing any arrow keys? */
   if (fg_kbtest(KB_LEFT))
   {
      /* change the direction if necessary */
      if (objp->direction == RIGHT)
      {
         /* slow down speed in the middle of a direction change */
         objp->xspeed = 0;
         objp->direction = LEFT;
      }
   }
   else if (fg_kbtest(KB_RIGHT))
   {
      if (objp->direction == LEFT)
      {
         objp->xspeed = 0;
         objp->direction = RIGHT;
      }
   }

   /* if we aren't pressing any keys, then we aren't walking. Change
      the action function to standing. */

   else
      objp->action = player_stand;

   /* are we falling? */
   if (can_move_down(objp))
      objp->action = player_begin_fall;

   /* or kicking or jumping or shooting? */
   else if (fg_kbtest(KB_SPACE))
      objp->action = player_begin_kick;
   else if (fg_kbtest(KB_CTRL))
      objp->action = player_begin_jump;
   else if (fg_kbtest(KB_ALT))
      objp->action = player_begin_shoot;
}
/******************************************************************/
void near player_shoot(OBJp objp)
{
   unsigned long max_shoottime;
   int tile_x,tile_y;

   objp->time += delta_time;

   /* check for horizontal motion -- arrow keys pressed? */
   if (fg_kbtest(KB_RIGHT))
   {
      /* changing direction? start shooting all over */
      if (objp->direction == LEFT)
      {
         objp->direction = RIGHT;
         objp->action = player_begin_shoot;
      }
      else
      {
         /* spawn bullets more often when walking */
         max_shoottime = 3;
         if (objp->time > max_shoottime)
         {
            if (objp->sprite == tom_shoot[3])
            {
               objp->sprite = tom_shoot[4];
               launch_bullet();
            }
            else if (objp->sprite == tom_shoot[4])
               objp->sprite = tom_shoot[5];
            else
               objp->sprite = tom_shoot[3];

            /* move forward during walking frames */
            if (can_move_right(objp))
            {
               /* move right, checking for barriers */
               objp->xspeed = how_far_right(objp,8);
               objp->x += objp->xspeed;

               /* need to scroll the screen right? */
               tile_x = objp->x/16 - tile_orgx;
               if (tile_x > objp->tile_xmax)
                  scroll_right(objp->xspeed);
            }
            objp->time = 0;
         }
      }

      if (!fg_kbtest(KB_ALT))               /* done shooting? */
         objp->action = player_run;

      else if (can_move_down(objp))         /* falling? */
      {
         objp->yspeed = how_far_down(objp,5);
         objp->y += objp->yspeed;

         /* are we close to the bottom of the screen? If so, scroll */
         tile_y = objp->y/16 - tile_orgy;
         if (tile_y > objp->tile_ymax)
            scroll_down(objp->yspeed);
      }
      else if (fg_kbtest(KB_CTRL))           /* jumping? */
         objp->action = player_begin_jump;
   }

   /* same thing for left arrow key */
   else if (fg_kbtest(KB_LEFT))
   {
      if (objp->direction == RIGHT)
      {
         objp->direction = LEFT;
         objp->action = player_begin_shoot;
      }
      else
      {
         max_shoottime = 3;
         if (objp->time > max_shoottime)
         {
            if (objp->sprite == tom_shoot[3])
            {
               objp->sprite = tom_shoot[4];
               launch_bullet();
            }
            else if (objp->sprite == tom_shoot[4])
               objp->sprite = tom_shoot[5];
            else
               objp->sprite = tom_shoot[3];

            if (can_move_left(objp))
            {
               objp->xspeed = -8;
               objp->x += objp->xspeed;
               tile_x = objp->x/16 - tile_orgx;
               if (tile_x < objp->tile_xmin)
               scroll_left(-objp->xspeed);
            }
            objp->time = 0;
         }
      }

      if (!fg_kbtest(KB_ALT))               /* done shooting? */
         objp->action = player_run;

      else if (can_move_down(objp))         /* falling? */
      {
         objp->yspeed = how_far_down(objp,5);
         objp->y += objp->yspeed;

         /* are we close to the bottom of the screen? If so, scroll */
         tile_y = objp->y/16 - tile_orgy;
         if (tile_y > objp->tile_ymax)
            scroll_down(objp->yspeed);
      }
      else if (fg_kbtest(KB_CTRL))          /* jumping? */
         objp->action = player_begin_jump;

   }

   /* no arrow keys pressed, standing still */
   else
   {
      max_shoottime = 16;
      if (objp->time > max_shoottime)
      {
         /* pull out gun */
         if (objp->frame == 0)
         {
            objp->frame++;
               objp->sprite = tom_shoot[objp->frame];
         }
         else if (objp->frame == 1)         /* shooting */
         {
            /* done shooting */
            if (!fg_kbtest(KB_ALT))
               objp->frame++;
            nshots++;

            objp->sprite = tom_shoot[objp->frame];
            launch_bullet();
         }
         else if (objp->frame == 2)         /* recoil */
         {
            if (fg_kbtest(KB_ALT))
               objp->frame = 1; /* shoot again */
            else
            {
               objp->frame++;
               objp->sprite = tom_shoot[2];
            }
         }
         else if (objp->frame == 3)         /* done shooting */
         {
            objp->frame = 0;
            objp->sprite = tom_stand[0];
            objp->action = player_stand;
         }
         objp->time = 0;
      }
      if (!fg_kbtest(KB_ALT))              /* done shooting? */
         objp->action = player_stand;
      else if (can_move_down(objp))        /* falling? */
         objp->action = player_begin_fall;
      else if (fg_kbtest(KB_CTRL))         /* jumping? */
         objp->action = player_begin_jump;
   }

}
/******************************************************************/
void near player_stand(OBJp objp)
{
   /* standing still. Start walking? */
   if (fg_kbtest(KB_RIGHT))
   {
      objp->frame = 0;
      objp->xspeed = 1;
      objp->direction = RIGHT;
      objp->action = player_run;
   }
   else if (fg_kbtest(KB_LEFT))
   {
      objp->frame = 0;
      objp->xspeed = -1;
      objp->direction = LEFT;
      objp->action = player_run;
   }

   /* start kicking, jumping or shooting? */
   else if (fg_kbtest(KB_SPACE))
   {
      objp->action = player_begin_kick;
   }
   else if (fg_kbtest(KB_CTRL))
   {
      objp->action = player_begin_jump;
   }
   else if (fg_kbtest(KB_ALT))
   {
      objp->action = player_begin_shoot;
   }

   /* look down, look up */
   else if (fg_kbtest(KB_DOWN))
   {
      if (objp->y - tile_orgy*16 > 48)
         scroll_down(1);
   }
   else if (fg_kbtest(KB_UP))
   {
      if (objp->y - tile_orgy*16 < 200)
         scroll_up(1);
   }

   /* just standing there */
   else if (objp->sprite != tom_stand[0] && objp->frame < 7)
   {
      objp->frame = 0;
      objp->sprite = tom_stand[objp->frame];
   }
   else
   {
      /* change Tommy's facial expression */
      objp->time += delta_time;
      if (objp->time > max_time)
      {
         if (objp->frame == 0)
         {
            objp->frame = irandom(7,8);
            objp->time = 0;
            objp->sprite = tom_stand[objp->frame-6];

            /* how long we smile or frown is random */
            max_time = (long)irandom(200,400);
         }
         else
         {
            objp->frame = 0;
            objp->time = 0;
            objp->sprite = tom_stand[0];

            /* how long we stand straight without smiling */
            max_time = (long)irandom(500,1000);

         }
      }
   }
}
/******************************************************************/
void near put_score(OBJp objp)
{
   /* determine x and y coords based on the screen origin */
   objp->x = tile_orgx*16 + screen_orgx + 2;
   objp->y = tile_orgy*16 + screen_orgy + 43;
}
/******************************************************************/
void near update_score(OBJp objp)  /* called when score has changed */
{
   char string[128];
   SPRITE *scoremap;
   int y;
   register int i;

   /* Convert the (long) score to a character string.  Assume 10 digits
      is enough */

   ltoa(player_score,string,10);

   /* clear an area in video memory below the tile space where nothing
      else is going on */

   fg_setcolor(0);
   fg_rect(0,319,680,724);

   /* draw the score box in offscreen memory */
   scoremap = tom_score[0];
   fg_move(0,724);
   fg_drwimage(scoremap->bitmap,scoremap->width,scoremap->height);

   /* set the color to black and display the score */
   fg_setcolor(1);
   center_string(string,5,56,720);

   /* the status bar indicates how many times you have been hit */
   y = nhits*3;

   fg_setcolor(14);
   if (nhits == 0)            /* all blue */
   {
      fg_setcolor(18);
      fg_rect(62,67,701,723);
   }
   else if (nhits >= 8)       /* all white */
   {
      fg_setcolor(14);
      fg_rect(62,67,701,723);
   }
   else
   {                          /* white and blue */
      fg_setcolor(14);
      fg_rect(62,67,701,700+y);
      fg_setcolor(18);
      fg_rect(62,67,700+y,723);
   }

   scoremap = tom_score[1];    /* tommy one-ups */
   for (i = 0; i < nlives; i++)
   {
      fg_move(80+i*10,716);
      fg_drwimage(scoremap->bitmap,scoremap->width,scoremap->height);
   }

   /* do a getimage to put the score in a bitmap in RAM */
   objp->sprite->width = 80+10*nlives;
   fg_move(0,724);
   fg_getimage(objp->sprite->bitmap,
               objp->sprite->width,objp->sprite->height);

   /* update the x and y coords */
   objp->x = tile_orgx*16 + screen_orgx + 2;
   objp->y = tile_orgy*16 + screen_orgy + 43;

   /* assign action function */
   objp->action = put_score;
}
