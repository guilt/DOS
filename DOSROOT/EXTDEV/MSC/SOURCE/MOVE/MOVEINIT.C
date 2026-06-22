/***
*moveinit.c - MOVE Initialization
*
*	Copyright (c) 1990-1992, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*	This file contains the routine _moveinit(); it determines an
*	appropriate size for the overlay heap and cache and allocates them.
*
*******************************************************************************/

#include "moveapi.h"

#ifndef MOVE_ENV

/***
*_moveinit - Allocate MOVE heap and cache
*
*Purpose:
*	Allocate MOVE heap and cache at initialization time.
*
*	- Although $$MPOVLSIZE is a table of long counts of paragraphs,
*	  overlays generated with /DYNAMIC are never larger than 64 kb,
*	  so only 12 bits are meaningful in each entry.
*
*	- Minimum heap size is the size of the largest overlay.
*	- If the program has four overlays or more
*	  requested heap size is the size of the three largest overlays
*	- If the program has three overlays or less
*	  requested heap size is the size of the largest overlay
*
*	- Minimum cache ressource size is the size of the largest overlay.
*	- Maximum cache ressource size is the total size of all overlays.
*	- If maximum cache ressource size cannot be allocated in the same
*	  ressource, maximum combined cache size is the sum of maximum cache
*	  ressource size and minimum cache ressource
*
*Entry: <none>
*
*Exit:	<none>
*
*Exceptions:
*
*******************************************************************************/

void _far _moveinit (
)
    {
    unsigned long _far * lpulOvlSizeCur; /* ptr to current of overlay size */
    unsigned long _far * lpulOvlSizeEnd; /* ptr to end of overlay size table */

    unsigned short cparaOvl; /* size of current overlay */

    unsigned short cparaLarge; /* size of largest overlay */
    unsigned short cparaMedium; /* size of second largest overlay */
    unsigned short cparaSmall; /* size of third largest overlay */

    unsigned short cparaMax; /* size of heap as requested */
    unsigned short cparaMin; /* minmum heap size */

    unsigned short ckbMax; /* sum of all overlays' sizes */
    unsigned short ckbMin; /* minimum size of a cache ressource */

    unsigned short ckbXms; /* XMS avail size (kilobytes) */
    unsigned short ckbEms; /* EMS avail size (kilobytes) */

    /* cparaLarge, cparaMedium, cparaSmall will be the sizes of
     * the three largest overlays
     */

    cparaLarge = 0;
    cparaMedium = 0;
    cparaSmall = 0;

    /* ckbMax is the sum of the image size of all the overlays. */

    ckbMax = 0;

    for (lpulOvlSizeCur = $$MPOVLSIZE + 1,
	 lpulOvlSizeEnd = $$MPOVLSIZE + $$COVL;
	 lpulOvlSizeCur < lpulOvlSizeEnd;
	 lpulOvlSizeCur ++)
	{
	cparaOvl = (unsigned short) (*lpulOvlSizeCur);
	ckbMax += ((cparaOvl + 0x3f) >> 6);

	if (cparaOvl > cparaSmall)
	    {
	    if (cparaOvl > cparaMedium)
		{
		cparaSmall = cparaMedium;
		if (cparaOvl > cparaLarge)
		    {
		    cparaMedium = cparaLarge;
		    cparaLarge = cparaOvl;
		    }
		else
		    cparaMedium = cparaOvl;
		}
	    else
		cparaSmall = cparaOvl;
	    }
	}

    /* cparaMax is the requested size of the overlay heap in paragraphs.
     * If the program has less than 4 overlays, this will be the size of the
     * largest overlay. If the program has more than 3 overlays, this will be
     * the sum of the largest 3 overlays' sizes.
     */

    if ($$COVL > 4)
	cparaMax = cparaLarge + cparaMedium + cparaSmall;
    else
	cparaMax = cparaLarge;

    /* cparaMax is the minimum size of heap, it is the size
     * of the largest overlay.
     */

    cparaMin = cparaLarge;

    /* attempt to allocate the overlay heap. ignore return value (heap size).
     * note that MOVE will abort if not enough memory to alloc minimum size.
     */

    _movesetheap ($$COVL, cparaLarge, cparaMax);

    /* get available cache ressource amount */

    _movegetcache (&ckbXms, &ckbEms);

    /* ckbMin is the cache resource minimum size (largest overlay size) */

    ckbMin = ((cparaLarge + 0x3f) >> 6);

    /* allocate cache ressource:
     *	1 try to allocate max in XMS
     *	2 try to allocate max in EMS
     *	3 allocate as much as possible in XMS
     *	4 allocate as much as possible in EMS
     */

    if (ckbXms >= ckbMax)
	{
	ckbXms = ckbMax;
	ckbEms = 0;
	}
    else if (ckbEms >= ckbMax)
	{
	ckbXms = 0;
	ckbEms = ckbMax;
	}
    else
	{
	if (ckbXms < ckbMin)
	    ckbXms = 0;

	if (ckbEms < ckbMin)
	    ckbEms = 0;

	if (ckbXms + ckbEms > ckbMax + ckbMin)
	    ckbEms = ckbMax + ckbMin - ckbXms;
	}

    /* attempt to set the cache's size. we ignore errors */

    _movesetcache (ckbXms, ckbEms);

#ifdef MOVE_PROF
    _movetraceon ();
#endif
    }


#else /* MOVE_ENV */


static char SzMOVE_COVL [] = "MOVE_COVL";
static char SzMOVE_HEAP [] = "MOVE_HEAP";
static char SzMOVE_XMS	[] = "MOVE_XMS";
static char SzMOVE_EMS	[] = "MOVE_EMS";

/***
* __movegetenv - Get value of MOVE environment variable
*
*Purpose:
*	Get the value of the MOVE environment variable
*
*	Value should we stored with exactly four hexadecimal digits
*
*Entry:
*	lpszName = name of variable to look for
*
*Exit:
*	unsigned 16-bit integer = value in environment
*				  zero if name not defined
*
*Exceptions:
*
*******************************************************************************/

unsigned short _far __movegetenv (
char _far * lpszName
)
    {
    _asm
	{
	les	di,[lpszName]	; ES:DI = lpszName
	xor	ax,ax		; search value: null byte
	mov	cx,-1		; so won't stop scan
	repne	scasb		; scan for null, CX = -(1+strlen(lpszName))
	not	cx
	dec	cx		; CX = strlen (lpszName)

	mov	dx,cx		; DX = strlen (lpszName)

	mov	di,seg _movesegenv
	mov	es,di
	mov	di,offset _movesegenv
	mov	es,es:[di]
	xor	di,di		; ES:DI = environment

__mge_next:

	mov	al,es:[di]	; AL = next byte
	or	al,al		; if null, we've failed to find the string
	je	__mge_fail

	lds	si,[lpszName]	; DS:SI = lpszName
	mov	cx,dx		; CX = strlen (lpszName)
	repz	cmpsb		; compare strings

	jne	__mge_bad	; did the compare succeed ?

	mov	al,es:[di]	; AL = next byte
	cmp	al,'='		; if '=', we found the guy
	je	__mge_found

__mge_bad:

	xor	ax,ax		; search value: null byte
	mov	cx,-1		; so won't stop scan
	repne	scasb		; scan for null

	jmp	__mge_next	; check next string

__mge_found:

	mov	cl,16		; CL = 16 (shift factor)
	xor	ax,ax		; AX = 0 (result)

__mge_next_char:

	inc	di		; advance to next char

	mov	dl,es:[di]	; DL = next byte

	or	dl,dl		; final byte ?
	jz	__mge_done	; if yes, we're done

	cmp	dl,'0'		; char < '0' ?
	jb	__mge_fail	; if yes, invalid

	cmp	dl,'9'		; '0' <= char <= '9' ?
	jbe	__mge_digit	; if yes, it's a digit

	cmp	dl,'A'		; '9' < char < 'A' ?
	jb	__mge_fail	; if yes, invalid

	cmp	dl,'F'		; 'A' <= char <= 'F' ?
	jbe	__mge_letter	; if yes, it's a letter

	cmp	dl,'a'		; 'Z' < char < 'a' ?
	jb	__mge_fail	; if yes, invalid

	cmp	dl,'f'		; 'a' <= char <= 'f' ?
	jbe	__mge_letter	; if yes, it's a letter

				; z < char : invalid

__mge_fail:

	xor	ax,ax		; null result
	jmp	__mge_end	; finish

__mge_digit:

	and	dl,0fh

	jmp	__mge_store

__mge_letter:

	and	dl,0fh
	add	dl,09h

__mge_store:

	xor	dh,dh		; DH = 0 (so we can OR AX,DX)

	or	cl,cl		; check shift count
	jz	__mge_fail	; if zero, it's the 5th digit, invalid

	sub	cl,4		; update shift factor

	shl	dx,cl		; shift digit

	or	ax,dx		; put digit in result

	jmp	__mge_next_char

__mge_done:

	or	cl,cl		; check shift count
	jnz	__mge_fail	; if not zero, we had less than 4 digits, invalid

__mge_end:
	}
    }


/***
*_moveinit - Allocate MOVE heap and cache
*
*Purpose:
*	Allocate MOVE heap and cache at initialization time.
*
*	- Although $$MPOVLSIZE is a table of long counts of paragraphs,
*	  overlays generated with /DYNAMIC are never larger than 64 kb,
*	  so only 12 bits are meaningful in each entry.
*
*	- Minimum heap size is the size of the largest overlay.
*	- If the program has four overlays or more
*	  requested heap size is the size of the three largest overlays
*	- If the program has three overlays or less
*	  requested heap size is the size of the largest overlay
*
*	- Minimum cache ressource size is the size of the largest overlay.
*	- Maximum cache ressource size is the total size of all overlays.
*	- If maximum cache ressource size cannot be allocated in the same
*	  ressource, maximum combined cache size is the sum of maximum cache
*	  ressource size and minimum cache ressource
*
*Entry: <none>
*
*Exit:	<none>
*
*Exceptions:
*
*******************************************************************************/

void _far _moveinit (
)
    {
    unsigned long _far * lpulOvlSizeCur; /* ptr to current of overlay size */
    unsigned long _far * lpulOvlSizeEnd; /* ptr to end of overlay size table */

    unsigned short covlMax; /* maximum number of ovls supported */

    unsigned short cparaOvl; /* size of current overlay */

    unsigned short cparaLarge; /* size of largest overlay */
    unsigned short cparaMedium; /* size of second largest overlay */
    unsigned short cparaSmall; /* size of third largest overlay */

    unsigned short cparaMax; /* size of heap as requested */
    unsigned short cparaMin; /* minmum heap size */

    unsigned short ckbMax; /* sum of all overlays' sizes */
    unsigned short ckbMin; /* minimum size of a cache ressource */

    unsigned short ckbXms; /* XMS avail size (kilobytes) */
    unsigned short ckbEms; /* EMS avail size (kilobytes) */

    unsigned short covlEnv; /* max number of ovls requested by env var */
    unsigned short cparaEnv; /* heap size requested by env var */
    unsigned short ckbXmsEnv; /* XMS cache size requested by env var */
    unsigned short ckbEmsEnv; /* EMS cache size requested by env var */

    /* cparaLarge, cparaMedium, cparaSmall will be the sizes of
     * the three largest overlays
     */

    cparaLarge = 0;
    cparaMedium = 0;
    cparaSmall = 0;

    /* ckbMax is the sum of the image size of all the overlays. */

    ckbMax = 0;

    for (lpulOvlSizeCur = $$MPOVLSIZE + 1,
	 lpulOvlSizeEnd = $$MPOVLSIZE + $$COVL;
	 lpulOvlSizeCur < lpulOvlSizeEnd;
	 lpulOvlSizeCur ++)
	{
	cparaOvl = (unsigned short) (*lpulOvlSizeCur);
	ckbMax += ((cparaOvl + 0x3f) >> 6);

	if (cparaOvl > cparaSmall)
	    {
	    if (cparaOvl > cparaMedium)
		{
		cparaSmall = cparaMedium;
		if (cparaOvl > cparaLarge)
		    {
		    cparaMedium = cparaLarge;
		    cparaLarge = cparaOvl;
		    }
		else
		    cparaMedium = cparaOvl;
		}
	    else
		cparaSmall = cparaOvl;
	    }
	}

    /* covlMax is the requested size of the overlay table, it is the maximum
     * number of overlays supported by MOVE for the application and its
     * extensions
     */

    covlEnv = __movegetenv (SzMOVE_COVL);

    if (covlEnv > $$COVL)
	covlMax = covlEnv;
    else
	covlMax = $$COVL;

    /* cparaMin is the minimum size of heap, it is the size
     * of the largest overlay.
     */

    cparaMin = cparaLarge;

    /* cparaMax is the requested size of the overlay heap in paragraphs.
     * If the program has less than 4 overlays, this will be the size of the
     * largest overlay. If the program has more than 3 overlays, this will be
     * the sum of the largest 3 overlays' sizes.
     */

    cparaEnv = __movegetenv (SzMOVE_HEAP);

    if (cparaEnv != 0)
	if (cparaEnv < cparaMin)
	    cparaMax = cparaMin;
	else
	    cparaMax = cparaEnv;
    else
	if ($$COVL > 4)
	    cparaMax = cparaLarge + cparaMedium + cparaSmall;
	else
	    cparaMax = cparaLarge;

    /* attempt to allocate the overlay heap. ignore return value (heap size).
     * note that MOVE will abort if not enough memory to alloc minimum size.
     */

    _movesetheap (covlMax, cparaMin, cparaMax);

    /* get available cache ressource amount */

    _movegetcache (&ckbXms, &ckbEms);

    /* ckbMin is the cache resource minimum size (largest overlay size) */

    ckbMin = ((cparaLarge + 0x3f) >> 6);

    /* allocate cache ressource: */

    ckbEmsEnv = __movegetenv (SzMOVE_EMS);
    ckbXmsEnv = __movegetenv (SzMOVE_XMS);

    if (ckbEmsEnv != 0 || ckbXmsEnv != 0)
	{
	if (ckbEmsEnv < ckbMin || ckbEms < ckbMin)
	    ckbEms = 0;
	else
	    if (ckbEmsEnv < ckbEms)
		ckbEms = ckbEmsEnv;

	if (ckbXmsEnv < ckbMin || ckbXms < ckbMin)
	    ckbXms = 0;
	else
	    if (ckbXmsEnv < ckbXms)
		ckbXms = ckbXmsEnv;
	}
    else
	{

	/* default algorithm:
	 *  1 try to allocate max in XMS
	 *  2 try to allocate max in EMS
	 *  3 allocate as much as possible in XMS
	 *  4 allocate as much as possible in EMS
	 */

	if (ckbXms >= ckbMax)
	    {
	    ckbXms = ckbMax;
	    ckbEms = 0;
	    }
	else if (ckbEms >= ckbMax)
	    {
	    ckbXms = 0;
	    ckbEms = ckbMax;
	    }
	else
	    {
	    if (ckbXms < ckbMin)
		ckbXms = 0;

	    if (ckbEms < ckbMin)
		ckbEms = 0;

	    if (ckbXms + ckbEms > ckbMax + ckbMin)
		ckbEms = ckbMax + ckbMin - ckbXms;
	    }
	}

    /* attempt to set the cache's size. we ignore errors */

    _movesetcache (ckbXms, ckbEms);

#ifdef MOVE_PROF
    _movetraceon ();
#endif
    }

#endif // MOVE_ENV
