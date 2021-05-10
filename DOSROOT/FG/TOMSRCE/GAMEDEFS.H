/******************************************************************\
*  GameDefs.h -- Main header file for Tommy's Adventures game      *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

/********************* standard include files *********************/
#include <fastgraf.h>                /* Fastgraph function declarations*/
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <io.h>

/* Borland C and Turbo C have different names for some of the
   standard include files */

#ifdef __TURBOC__
  #include <alloc.h>
  #include <mem.h>
#else
  #include <malloc.h>
  #include <memory.h>
#endif

#ifdef tommy_c
    #define DECLARE                  /* declarations are not extern */
#else
    #define DECLARE extern           /* declarations are extern */
#endif

/********************* file i/o variables *************************/

DECLARE int  nlevels;                /* total number of levels */
DECLARE int  current_level;          /* current level number */
DECLARE char game_fname[13];         /* file name of game file */
DECLARE char level_fname[13];        /* file name of level data */
DECLARE char background_fname[13];   /* pcx file -- background tiles */
DECLARE char backattr_fname[13];     /* background tile attributes */
DECLARE char foreground_fname[13];   /* pcx file -- foreground tiles */
DECLARE char foreattr_fname[13];     /* foreground tile attributes */

#define MAXLEVELS 6                  /* max 6 levels per episode */
typedef struct levdef                /* level structure */
{
   char level_fname[13];
   char background_fname[13];
   char backattr_fname[13];
   char foreground_fname[13];
   char foreattr_fname[13];
   char sprite_fname[13];
}  LEVDEF;
DECLARE LEVDEF far level[MAXLEVELS];  /* array of level structures */

DECLARE int  nspritelists;            /* total number of sprite lists */
DECLARE char sprite_fname[13];        /* sprite file name */
DECLARE char list_fname[13];          /* sprite list file name */
#define MAXSPRITELISTS 8              /* max 8 sprite lists per level */
DECLARE char list_fnames[MAXSPRITELISTS][13]; /* array of sprite lists */

DECLARE FILE *stream;                 /* general purpose file handle */
DECLARE FILE *dstream;                /* used for debugging */
DECLARE FILE *level_stream;           /* file handle: level data */
DECLARE FILE *sprite_stream;          /* file handle: sprite file */

/********************  map declarations *************************/

#define BACKGROUND   0                /* tile type is background */
#define FOREGROUND   1                /* tile type is foreground */
DECLARE int tile_type;                /* foreground or background */

DECLARE int tile_orgx;                /* tile space x origin */
DECLARE int tile_orgy;                /* tile space y origin */

DECLARE int screen_orgx;              /* screen space x origin */
DECLARE int screen_orgy;              /* screen space y origin */
DECLARE int screen_xmax;              /* max screen space x coordinate */
DECLARE int screen_ymax;              /* max screen space y coordinate */

DECLARE int world_x;                  /* world space x origin */
DECLARE int world_y;                  /* world space y origin */
DECLARE int world_maxx;               /* max world space x coordinate */
DECLARE int world_maxy;               /* max world space y coordinate */

DECLARE int vpo;                      /* visual page offset */
DECLARE int vpb;                      /* visual page bottom */
DECLARE int hpo;                      /* hidden page offset */
DECLARE int hpb;                      /* hidden page bottom */
DECLARE int tpo;

#define MAXROWS 200                   /* maximum rows of tiles */
#define MAXCOLS 240                   /* maximum columns of tiles */
DECLARE int nrows;                    /* number of rows */
DECLARE int ncols;                    /* number of columns */

/* tile arrays for levels */
DECLARE unsigned char far background_tile[MAXCOLS][MAXROWS];
DECLARE unsigned char far foreground_tile[MAXCOLS][MAXROWS];

/* tile attribute arrays */
DECLARE unsigned char background_attributes[240];
DECLARE unsigned char foreground_attributes[28];

DECLARE char layout[2][22][15];       /* layout array */

DECLARE int warped;                   /* flag: warped this frame? */
DECLARE int scrolled_left;            /* flag: scrolled left? */
DECLARE int scrolled_right;           /* flag: scrolled right? */
DECLARE int scrolled_up;              /* flag: scrolled up? */
DECLARE int scrolled_down;            /* flag: scrolled down? */

/********************  sprite declarations *************************/

typedef struct _sprite                /* sprite structure */
{
   char far *bitmap;                  /* pointer to bitmap data */
   int width;                         /* width of bitmap */
   int height;                        /* height of bitmap */
   int xoffset;                       /* x offset */
   int yoffset;                       /* y offset */
   int bound_x;                       /* x coord of bounding box */
   int bound_y;                       /* y coord of bounding box */
   int bound_width;                   /* width of bounding box */
   int bound_height;                  /* height of bounding box */
}  far SPRITE;

#define MAXSPRITES 100                /* maximum number of sprites */
DECLARE SPRITE *sprite[MAXSPRITES];   /* sprite array */
DECLARE int nsprites;                 /* number of sprites */

#define STANDFRAMES  3                /* number of frames in sprite list */
#define RUNFRAMES    6
#define JUMPFRAMES   4
#define KICKFRAMES   8
#define SHOOTFRAMES  7
#define SCOREFRAMES  3
#define ENEMYFRAMES  6

DECLARE SPRITE *tom_stand[STANDFRAMES]; /* sprite lists */
DECLARE SPRITE *tom_run  [RUNFRAMES];
DECLARE SPRITE *tom_jump [JUMPFRAMES];
DECLARE SPRITE *tom_kick [KICKFRAMES];
DECLARE SPRITE *tom_shoot[SHOOTFRAMES];
DECLARE SPRITE *tom_score[SCOREFRAMES];
DECLARE SPRITE *enemy_sprite[ENEMYFRAMES];

#define LEFT   0                      /* direction of sprite */
#define RIGHT  1

/************************** object declarations *******************/
DECLARE struct OBJstruct;             /* forward declarations */
typedef struct OBJstruct OBJ, far *OBJp;

typedef void near ACTION (OBJp objp); /* pointer to action function */
typedef ACTION near *ACTIONp;

typedef struct OBJstruct              /* object structure */
{
  OBJp next;                          /* linked list next node */
  OBJp prev;                          /* linked list previous node */
  int x;                              /* x coordinate */
  int y;                              /* y coordinate */
  int xspeed;                         /* horizontal speed */
  int yspeed;                         /* vertical speed */
  int direction;                      /* LEFT or RIGHT */
  int tile_xmin;                      /* tile limits */
  int tile_xmax;
  int tile_ymin;
  int tile_ymax;
  int frame;                          /* frame of animation */
  unsigned long time;                 /* time */
  SPRITE *sprite;                     /* pointer to sprite */
  ACTIONp action;                     /* pointer to action function */
};

DECLARE OBJp player;                  /* main player object */
DECLARE OBJp top_node, bottom_node;   /* nodes in linked list */
DECLARE OBJp score;                   /* score object */

#define MAXENEMIES 5
DECLARE OBJp enemy[MAXENEMIES];       /* array of enemy objects */
DECLARE int nenemies;                 /* how many enemies */

/*********************  special effects **************************/
DECLARE char far *slide_array;
DECLARE int slide_arraysize;          /* size of slide array */

DECLARE int player_blink;             /* flag: is Tommy blinking? */
DECLARE int nblinks;                  /* how many times has he blinked? */
DECLARE unsigned long blink_time;     /* how long since the last blink? */
DECLARE char far blink_map[4000];     /* bitmap mask for the blink */

/*********************  key declarations *************************/
#define BS           8             /* bios key values */
#define ENTER       13
#define ESC         27
#define SPACE       32

#define KB_ALT      56             /* low-level keyboard scan codes */
#define KB_CTRL     29
#define KB_ESC       1
#define KB_SPACE    57
#define KB_UP       72
#define KB_LEFT     75
#define KB_RIGHT    77
#define KB_DOWN     80
#define KB_F1       59
#define KB_F2       60
#define KB_W        17
#define KB_D        32

/************ miscellaneous defines and variables ***********/
#define MAX(x,y) ((x) > (y)) ? (x) : (y)
#define MIN(x,y) ((x) < (y)) ? (x) : (y)
#define OFF   0
#define ON    1
#define ERR  -1
#define OK    1
#define FALSE 0
#define TRUE  1

DECLARE int hidden;                   /* hidden page */
DECLARE int visual;                   /* visual page */
DECLARE int seed;                     /* random number generator seed */

DECLARE int white;                    /* colors for status screen */
DECLARE int black;
DECLARE int blue;

DECLARE unsigned long game_time;      /* total clock ticks */
DECLARE unsigned long last_time;      /* time last frame */
DECLARE unsigned long delta_time;     /* time elapsed between frames */
DECLARE unsigned long max_time;       /* how long Tommy stands still */


DECLARE int nbullets;                 /* how many bullets */
DECLARE unsigned long shoot_time;     /* how long between shots */
DECLARE long player_score;            /* how many points */

DECLARE int show_score;               /* flag: scoreboard on? */

DECLARE int forward_thrust;           /* horizontal acceleration */
DECLARE int vertical_thrust;          /* vertical acceleration */
DECLARE int kicking;                  /* flag: kicking? */
DECLARE int kick_frame;               /* stage of kick animation */
DECLARE int kick_basey;               /* y coord at start of kick */
DECLARE int nkicks;                   /* how many kicks */
DECLARE int nshots;                   /* how many shots */
DECLARE int nhits;                    /* how many hits */
DECLARE int nlives;                   /* how many lives */

DECLARE int warp_to_next_level;       /* flag: warp? */
DECLARE char abort_string[50];        /* display string on exit */

/*****************  function declarations *******************/

void set_rate(int rate);              /* external timer function */

typedef void far interrupt HANDLER (void);
typedef HANDLER far *HANDLERp;
DECLARE HANDLERp oldhandler;

/* action function declarations: action.c */
void  near bullet_go(OBJp objp);
void  near enemy_hopper_go(OBJp objp);
void  near enemy_scorpion_go(OBJp objp);
void  near floating_points_go(OBJp objp);
void  near kill_bullet(OBJp objp);
void  near kill_enemy(OBJp objp);
void  near kill_object(OBJp objp);
void  near launch_bullet(void);
void  near launch_enemy(int x,int y,int type);
void  near launch_floating_points(OBJp objp);
void  near player_begin_fall(OBJp objp);
void  near player_begin_jump(OBJp objp);
void  near player_begin_kick(OBJp objp);
void  near player_begin_shoot(OBJp objp);
void  near player_fall(OBJp objp);
void  near player_jump(OBJp objp);
void  near player_kick(OBJp objp);
void  near player_run(OBJp objp);
void  near player_shoot(OBJp objp);
void  near player_stand(OBJp objp);
void  near put_score(OBJp objp);
void  near update_score(OBJp objp);

/* function declarations: char.c */
void  put_string(char *string,int ix,int iy);
void  center_string(char *string,int x1,int x2,int y);

/* function declarations: effects.c */
void  get_blinkmap(OBJp objp);
void  load_status_screen(void);
void  redraw_screen(void);
int   status_screen(void);
void  status_shape(int shape,int x,int y);

/* function declarations: map.c */
void  load_level(void);
void  page_copy(int ymin);
void  page_fix(void);
void  put_foreground_tile(int xtile,int ytile);
void  put_tile(int xtile,int ytile);
void  rebuild_background(void);
void  rebuild_foreground(void);
int   scroll_down(int npixels);
int   scroll_left(int npixels);
int   scroll_right(int npixels);
int   scroll_up(int npixels);
void  swap(void);
void  warp(int x,int y);

/* function declarations: motion.c */
int   can_move_down(OBJp objp);
int   can_move_up(OBJp objp);
int   can_move_right(OBJp objp);
int   can_move_left(OBJp objp);
int   collision_detection(OBJp objp1,OBJp objp2);
int   how_far_left(OBJp objp,int n);
int   how_far_right(OBJp objp,int n);
int   how_far_up(OBJp objp,int n);
int   how_far_down(OBJp objp,int n);
int   test_bit(char num,int bit);

/* function declarations: tommy.c */
void  main(void);
void  activate_level(void);
void  apply_sprite(OBJp objp);
void  array_to_level(int  n);
void  fix_palettes(void);
void  flushkey(void);
void  getseed(void);
void  get_blinkmap(OBJp objp);
void  interrupt increment_timer(void);
int   irandom(int  min,int max);
void  init_graphics(void);
void  level_to_array(int n);
void  load_sprite(void);
void  load_status_screen(void);
void  terminate_game(void);
