/******************************************************************\
*                                                                  *
*  Defs.h -- Main header file for palette reduction program        *
*                                                                  *
*  copyright 1994 Diana Gruber                                     *
*                                                                  *
*  compile using large model, link with Fastgraph (tm)             *
*                                                                  *
\******************************************************************/

#include <fastgraf.h>

#include <conio.h>
#include <ctype.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <io.h>

#ifdef __TURBOC__
  #include <alloc.h>
  #include <mem.h>
#else
  #include <malloc.h>
  #include <memory.h>
#endif

/* we define a string "DECLARE", which will be equal to "extern" in
   all the files except common.c. This has the effect of allowing
   us to declare our global variables once, in common.c, and 
   everywhere else they will be declared as externals. */

#ifndef palette_c
    #define DECLARE extern
#else
    #define DECLARE
#endif

#define FALSE 0
#define TRUE  1

#define CHOOSE 0
#define MATCH  1
#define MERGE  2

#define SPRITE 0
#define BACKGROUND 1

/******************** color declarations *************************/

DECLARE int white;
DECLARE int black;
DECLARE int blue;
DECLARE int grey;
DECLARE int palette_white;
DECLARE int palette_black;
DECLARE int palette_blue;
DECLARE int palette_grey;

/*********************  key declarations *************************/

#define BS     8
#define ENTER 13
#define ESC   27
#define SPACE 32
#define F2    60
#define F10   68
#define CR          13
#define SPACEBAR    32

#define UP_ARROW    72
#define LEFT_ARROW  75
#define RIGHT_ARROW 77
#define DOWN_ARROW  80
#define TAB          9

#define LEFT   0
#define RIGHT  1
#define UP     2
#define DOWN   3

#define ERR -1
#define OK   1
#define QUIT 0

/****************** global variables and arrays *************/

DECLARE int file_type;
DECLARE int reduction_type;
DECLARE int field;

DECLARE unsigned char far default_colors[768];
DECLARE unsigned char far input_colors[768];
DECLARE unsigned char far match_colors[768];
DECLARE unsigned char far output_colors[768];
DECLARE unsigned char far match_palette[256];
DECLARE unsigned long far pixel_count[256];

DECLARE char infile[13];
DECLARE char matchfile[13];
DECLARE char outfile[13];
DECLARE unsigned char far buffer1[64000];
DECLARE unsigned char far buffer2[64000];

/****************** function declarations *******************/

/* palette.c declarations */

void  main(void);
int   activate_screen(void);
int   do_reduction(void);
void  error_message(char *string);
int   file_exists(char *filename);
int   fix_suffix(char *fname);
void  match(int ncolors);
int   merge(int ncolors);
void  quit_graphics(void);
void  redraw_screen(void);
void  reduce(int ncolors);
void  show_match_string(void);

/* char.c declarations */

void  center_string(char *string,int x1,int x2,int y);
void  erase_char(int x,int y);
int   get_center(char *string,int x1,int x2);
void  put_char(unsigned char key,int x,int y);
void  put_cursor(int x,int y,int cursor_color);
int   get_string(char *string,int x,int y,int max_length,
                 unsigned char key,unsigned char aux);
void  put_string(unsigned char *string,int ix,int iy);

