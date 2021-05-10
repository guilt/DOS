/******************************************************************\
*  EditDefs.h -- Main header file for Fastgraph Game Editor        *
*  copyright 1994 Diana Gruber                                     *
*  compile using large model, link with Fastgraph (tm)             *
\******************************************************************/

/********************* standard include files *********************/
#include <fastgraf.h>           /* Fastgraph function declarations*/
#include <ctype.h>
#include <dos.h>
#include <io.h>
#include <process.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Borland C and Turbo C have different names for some of the
   standard include files */

#ifdef __TURBOC__
  #include <alloc.h>
  #include <mem.h>
#else
  #include <malloc.h>
  #include <memory.h>
#endif

#ifdef common_c
    #define DECLARE                  /* declarations are not extern */
#else
    #define DECLARE extern           /* declarations are extern */
#endif

/********************* macro definitions *************************/
#define BETWEEN(x,a,b) ((x >= a) && (x <= b))
#define MAX(x,y) ((x) > (y)) ? (x) : (y)
#define MIN(x,y) ((x) < (y)) ? (x) : (y)

/******************** symbolic constants *************************/
#define OFF          0
#define ON           1
#define ERR         -1
#define OK           1
#define FALSE        0
#define TRUE         1
#define BS           8
#define ENTER       13
#define ESC         27
#define SPACE       32
#define SPACEBAR    32
#define CR          13
#define UP_ARROW    72
#define LEFT_ARROW  75
#define RIGHT_ARROW 77
#define DOWN_ARROW  80
#define TAB          9
#define CTRL_LEFT_ARROW  115
#define CTRL_RIGHT_ARROW 116
#define HOME        71
#define PGUP        73
#define END         79
#define PGDN        81
#define INSERT      82
#define DELETE      83
#define BACKGROUND  0
#define FOREGROUND  1
#define F1          59
#define F2          60
#define F10         68

#define GAMEFILE    0
#define LEVELFILE   1
#define BACKFILE    2
#define FOREFILE    3
#define SPRITEFILE  4

/********************* misc. declarations *************************/
DECLARE int hidden;               /* hidden page */
DECLARE int visual;               /* visual page */
DECLARE int white;                /* colors */
DECLARE int black;
DECLARE int blue;
DECLARE int grey;
DECLARE int redraw;               /* flag: redraw screen? */
DECLARE int xlimit, ylimit;       /* used in redraw_screen */
DECLARE int menu_top;             /* screen coordinates */
DECLARE int menu_bottom;
DECLARE int foreground_color;     /* sprite editor foreground color */
DECLARE int background_color;     /* sprite editor background color */

DECLARE int background_changed;   /* flag: background tiles changed? */
DECLARE int foreground_changed;   /* flag: foreground tiles changed? */
DECLARE int sprite_changed;       /* flag: sprite changed? */
DECLARE int editing_sprite_files; /* flag: editing sprite files? */
DECLARE char abort_string[50];    /* error message string */

DECLARE FILE *dstream;            /* file handle: debug.dat */
DECLARE FILE *tstream;            /* file handle */
DECLARE FILE *stream;

/******************** mouse declarations *************************/
DECLARE int buttons;              /* state of mouse buttons */
DECLARE int xmouse, ymouse;       /* mouse coords */
DECLARE int back_xmouse;          /* mouse coords on background tiles */
DECLARE int back_ymouse;
DECLARE int fore_xmouse;          /* mouse coords on foreground tiles */
DECLARE int fore_ymouse;
DECLARE int level_xmouse;         /* mouse coords on level editor */
DECLARE int level_ymouse;

/************************** file names ****************************/
DECLARE char game_fname[13];        /* game.dat */
DECLARE char level_fname[13];       /* level data */

DECLARE char background_fname[13];  /* pcx file--background tiles */
DECLARE char backattr_fname[13];    /* background tile attributes */
DECLARE char backimport_fname[13];  /* import file for background tiles */

DECLARE char foreattr_fname[13];    /* pcx file--foreground tiles */
DECLARE char foreground_fname[13];  /* foreground tile attributes */
DECLARE char tile_import_fname[13]; /* import file for foreground tiles */

DECLARE char sprite_fname[13];      /* sprite.dat */
DECLARE char spritelist_fname[13];  /* sprite list */
DECLARE char sprite_pcxname[13];    /* for importing pcx files */

DECLARE char ripper_inpcx[13];      /* input file names for tile ripper */
DECLARE char ripper_outpcx[13];     /* output file for tile ripper */
DECLARE char ripper_outlvl[13];     /* ripper.lev */

/********************  sprite declarations ************************/
#define MAXSPRITELISTS 16
DECLARE char far list_fnames[MAXSPRITELISTS][13];
DECLARE int  nspritelists;
DECLARE int current_spritelist;

DECLARE char this_sprite[96][96]; /* sprite currently being edited */
DECLARE char old_sprite[96][96];  /* old sprite, holds undo information */
DECLARE char bitmap[96*96];       /* sprite data in a Fastgraph format */

DECLARE int x_offset;             /* x location of the grid boundary box */
DECLARE int x_limit;              /* width of the grid boundary box */
DECLARE int y_offset;             /* y location of the grid boundary box */
DECLARE int y_limit;              /* height of the grid boundary box */
DECLARE int grid_boundary;        /* flag - is boundary box on or off? */

DECLARE int nsprites;             /* how many sprites in sprite list */
DECLARE int current_sprite;       /* which sprite is currently seen */
DECLARE int sprite_width;         /* width and height */
DECLARE int sprite_height;
DECLARE int sprite_xorg;          /* sprite origin */
DECLARE int sprite_yorg;
DECLARE int sprite_boundx;        /* bounding box for collision detection */
DECLARE int sprite_boundy;
DECLARE int sprite_boundwidth;
DECLARE int sprite_boundheight;

typedef struct _sprite            /* sprite structure */
{
   char far *bitmap;
   int width;
   int height;
   int xorg;
   int yorg;
   int bound_x;
   int bound_y;
   int bound_width;
   int bound_height;
}  SPRITE;

DECLARE SPRITE sprite[20];         /* sprite list array */

/******************** tile declarations *************************/

#define TILESIZE  256    /* tiles are 16 pixels x 16 pixels */
#define TILELIMIT 240    /* only 240 unique tiles */
#define MAXTILES  1440   /* up to 6 screens of art, 240 tiles each*/
#define MAXROWS 200      /* maximum rows of tiles */
#define MAXCOLS 240      /* maximum columns of tiles */
DECLARE int nrows;       /* number of rows */
DECLARE int ncols;       /* number of columns */
DECLARE int col,row;
DECLARE int tile_index;
DECLARE int tilenum;     /* index into tile library */
DECLARE int tile_type;   /* background or foreground tile? */
DECLARE int attribute[8];/* attributes: solid on top, left, etc? */

DECLARE unsigned char this_tile[16][16];   /* tile currently being edited */
DECLARE unsigned char old_tile[16][16];    /* undo information */

/* tile arrays for levels */
DECLARE unsigned char far level_map[MAXCOLS][MAXROWS];
DECLARE unsigned char far foreground_map[MAXCOLS][MAXROWS];
DECLARE unsigned char far ripper_tiles[TILELIMIT][TILESIZE];

/* tile attribute arrays */
DECLARE char background_attributes[240];
DECLARE char foreground_attributes[28];

/******************** level declarations *************************/
DECLARE int nlevels;         /* number of levels */
DECLARE int current_level;   /* current level */
DECLARE int block_cols;      /* for level block moves */
DECLARE int block_rows;
DECLARE unsigned char block[22][15];
DECLARE int tile_orgx;       /* tile x origin */
DECLARE int tile_orgy;       /* tile y origin */
DECLARE int screen_orgx;     /* screen x origin */
DECLARE int screen_orgy;     /* screen y origin */
DECLARE int screen_xmax;     /* max horizontal screen coord */
DECLARE int screen_ymax;     /* max vertical screen coord */
DECLARE int vpo;             /* visual page offset */
DECLARE int hpo;             /* hidden  page offset */
DECLARE int tpo;             /* tile page offset */
DECLARE int tile_type;       /* background or foreground? */

/* tile arrays for undo information */
DECLARE unsigned char far level_undo[MAXCOLS][MAXROWS];
DECLARE unsigned char far foreground_undo[MAXCOLS][MAXROWS];

/* mouse limits */
DECLARE int mouse_limx1, mouse_limx2;
DECLARE int mouse_limy1, mouse_limy2;

/* extents of popup window */
DECLARE int popup_x1,popup_x2;
DECLARE int popup_y1,popup_y2;

#define MAXLEVELS 6          /* max 6 levels per episode */
typedef struct levdef        /* level structure */
{
   char level_fname[13];     /* level file names */
   char background_fname[13];
   char backattr_fname[13];
   char foreground_fname[13];
   char foreattr_fname[13];
   char sprite_fname[13];
}  LEVDEF;

DECLARE LEVDEF far level[MAXLEVELS]; /* level array */

/********************* menu declarations *************************/
typedef int (*PFI)();   /* pointer to an integer function */
#define ITEMS 4         /* number of items on main menu */
typedef struct cmd      /* command structure */
{
   PFI menu_func;       /* function to carry out the command */
   char *menu_item;     /* the menu item as written on the screen */
   int x1;              /* coordinates of location of menu_item */
   int x2;
}  CMD;

extern CMD main_menu[ITEMS];      /* array of menu structures */
extern int mouse_limits[ITEMS+1]; /* menu mouse limits */
DECLARE int main_option;          /* current main menu option */

/********************  function declarations *********************/

/* function declarations: char.c */
void  center_string(char *string,int x1,int x2,int y);
void  erase_char(int x,int y);
int   get_center(char *string,int x1,int x2);
void  put_char(unsigned char key,int x,int y);
void  put_cursor(int x,int y,int cursor_color);
int   get_string(char *string,int x,int y,int max_length,
                 unsigned char key,unsigned char aux);
void  put_string(char *string,int ix,int iy);

/* function declarations: common.c */
void  abort_game(void);
int   file_exists(char *filename);
void  flushkey(void);
void  init_graphics(void);
void  init_mouse(void);
void  quit_graphics(void);
void  fix_palettes(int status);

/* function declarations: fge.c */
void  main(void);
void  edit_menu(void);
void  draw_screen(void);
int   load_game_file(void);
int   check_suffixes(char *fname,int file_type);
void  file_help_screen(void);
void  level_to_array(int n);
void  array_to_level(int n);
void  show_level_names(void);

/* function declarations: level.c */
int   edit_level(void);
void  activate_level_editor(void);
void  delete_tiles(void);
void  get_block(void);
void  get_a_tile(void);
void  insert_tiles(void);
void  level_help(void);
void  load_level(void);
int   page_left(void);
int   page_right(void);
int   page_down(void);
int   page_up(void);
void  popup_message(char *string);
void  popdown(void);
void  put_tile(int xtile,int ytile,int page);
void  put_foreground_tile(int xtile,int ytile,int page);
void  save_level(void);
int   scroll_left(int npixels);
int   scroll_right(int npixels);
int   scroll_up(int npixels);
int   scroll_down(int npixels);
void  swap(void);
void  set_mouse_limx(void);
void  set_mouse_limy(void);
void  set_top(void);
void  set_bottom(void);
void  set_left(void);
void  set_right(void);
void  clear_tile_attributes(void);
void  show_coords(void);
void  update_level_undo(void);
void  undo_level(void);
int   load_level_name(void);
int   save_level_name(void);

/* function declarations: menu.c */
void  highlight_option(int n);
int   horizontal_menu(struct cmd *cmdtab,int n,int current);
int   submenu1(void);
int   submenu2(void);
int   submenu3(void);
int   submenu4(void);
int   vertical_menu(struct cmd *cmdtab,int index,int n);
void  wait_for_keystroke(void);
void  wait_for_mouse_buttons(void);
int   exit_program(void);

/* function declarations: ripper.c */
int   do_ripper(void);
int   ripit(void);
int   check_ripper_suffixes(char *fname,int file_type);
void  write_level(void);

/* function declarations: sprite.c */
int   edit_sprites(void);
int   activate_sprite_editor(void);
void  animate_sprite_list(void);
void  array_to_sprite(int n);
void  bitmap_to_grid(void);
void  bounding_box(void);
void  calculate_sprite_size(void);
int   check_sprite_suffixes(char *fname,int file_type);
void  clear_sprite(void);
void  delete_sprite(void);
void  draw_sprite_editor(void);
void  flip_sprite(void);
void  flood_fill_sprite(void);
void  get_minimal_sprite(void);
void  get_sprite(void);
void  import_sprite(void);
void  init_sprite(void);
void  init_this_spritelist(void);
int   load_edit_sprites(void);
int   load_sprites(void);
void  mask_sprite(void);
void  move_grid_boundary(void);
void  next_sprite(void);
void  previous_sprite(void);
void  put_spritenum(void);
void  restore_this_sprite(void);
void  save_sprite(void);
void  set_grid_boundary(int status);
void  set_sprite_background_color(int color);
void  set_sprite_foreground_color(int color);
void  set_sprite_grid(int i,int j,int color);
void  set_sprite_point(int x,int y,int color);
void  show_sprite_coords(int x,int y);
void  sprite_to_array(int n);
void  transpose_sprite_colors(void);
void  undo_sprite(void);
void  update_sprite_old(void);
void  xor_horiz_line(int x1,int x2,int y);
void  xor_vert_line(int x,int y1,int y2);

/* function declarations: tile.c */
void  activate_tile_editor(void);
void  clear_tile(void);
int   do_background(void);
int   do_foreground(void);
void  draw_this_tile(void);
void  draw_tile_editor(void);
void  fill_tile(void);
void  get_attributes(int tile_num);
void  get_tile(void);
void  horizontal_flip(void);
void  import_tiles(void);
void  init_tiles(void);
void  rotate_tile(void);
void  save_tiles(void);
void  set_attribute(int num);
void  set_attributes(void);
void  set_background_color(int color);
void  set_bit(int tile_num,int bit,int value);
void  set_foreground_color(int color);
void  set_grid(int i,int j,int color);
int   test_bit(int tile_num,int bit);
void  tile_put(void);
void  transpose_tile_colors(void);
void  undo_tiles(void);
void  update_attributes(int tile_num);
void  update_old(void);
void  update_tiles(void);
void  vertical_flip(void);
