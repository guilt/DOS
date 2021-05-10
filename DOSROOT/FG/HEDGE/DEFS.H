#include "hedge.h"
#include "common.h"

#include <fastgraf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __TURBOC__
   #include <alloc.h>
#else
   #include <malloc.h>
#endif

#ifndef common_c
   #define DECLARE extern
#else
   #define DECLARE
#endif

/* global variables */

DECLARE int clockspeed;
DECLARE int stall_time;
DECLARE int old_mode;
DECLARE int seed;

DECLARE FILE *tstream;
DECLARE char abort_string[80];

/* maze path variables */

DECLARE unsigned char layout[50][38];
DECLARE char attributes[240];
DECLARE char path[2000];
DECLARE unsigned char visited [50][38];
DECLARE int path_index;
DECLARE int n_nodes;

/* mouse variables */

DECLARE int buttons;
DECLARE int mouse;
DECLARE int xmouse, ymouse;

#define HORIZONTAL 16
#define VERTICAL   32

#define VISUAL   0
#define HIDDEN   1
#define SPARE   63

#define TOP      1
#define BOTTOM   2
#define LEFT     4
#define RIGHT    8

#define MAXROWS 37
#define MAXCOLS 50

#define F1      59

#define OFF      0
#define ON       1

#define FALSE    0
#define TRUE     1

#define MAX(x,y) ((x) > (y)) ? (x) : (y)
#define MIN(x,y) ((x) < (y)) ? (x) : (y)
