//Hi-Res Driver .

/************************************************/
/*                                              */
/*      SuperVGA 256 BGI driver defines         */
/*      Copyright (c) 1991                      */
/*      Jordan Hargraphix Software              */
/*                                              */
/************************************************/

#ifndef _DAC256_
#define _DAC256_

typedef unsigned char DacPalette256[256][3];

#endif

extern int far _Cdecl Svga256_fdriver[];

/* These are the currently supported modes */

#ifndef SVGA320x200x256
#define	SVGA320x200x256		0	/* 320x200x256 Standard VGA */
#define	SVGA640x400x256		1	/* 640x400x256 Svga/VESA */
#define	SVGA640x480x256		2	/* 640x480x256 Svga/VESA */
#define	SVGA800x600x256		3	/* 800x600x256 Svga/VESA */
#define SVGA1024x768x256	4	/* 1024x768x256 Svga/VESA */
#endif

#ifndef XNOR_PUT
#define	XNOR_PUT	5
#define NOR_PUT		6
#define NAND_PUT	7
#define TRANS_COPY_PUT	8               /* Doesn't work with 16-color drivers */
#endif
