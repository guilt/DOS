/***
*_file.c - perprocess file and buffer data declarations
*
*   Copyright (c) 1985-1992, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*   file and buffer data declarations
*
*******************************************************************************/

/* Validate some assumptions */
#ifdef _WINDOWS
#error Not for use with _WINDOWS
#endif

#include <stdio.h>
#include <file2.h>

#define _NEAR_ near

/* Number of files */

#define _NFILE_ 20


/*
 * FILE and FILE2 descriptors; preset for standard i/o files.
 */

FILE _NEAR_ _cdecl _iob[ _NFILE_ ] = {
    /* ptr, cnt,    base,   flag,   file */
    {
    NULL,   0,  NULL,   _IOREAD,    0   }
    ,
    {
    NULL,   0,  NULL,   _IOWRT, 1   }
    ,
    {
    NULL,   0,  NULL,   _IOWRT, 2   }
    ,
    {
    &(_iob2[3]._charbuf), 0, &(_iob2[3]._charbuf), _IORW|_IONBF, 3  }
    ,
    {
    NULL,   0,  NULL,   _IOWRT, 4   }
    ,
};


FILE2 _NEAR_ _iob2[ _NFILE_ ] = {
    /* flag2,  charbuf,  bufsiz */
    {
    0,  '\0', 0     }
    ,
    {
    0,  '\0', 0     }
    ,
    {
    0,  '\0', 0     }
    ,
    {
    0,  '\0', 1     }
    ,
    {
    0,  '\0', 0     }
    ,
};

/* pointer to end of descriptors */
FILE * _NEAR_ _lastiob = &_iob[ _NFILE_ -1];
