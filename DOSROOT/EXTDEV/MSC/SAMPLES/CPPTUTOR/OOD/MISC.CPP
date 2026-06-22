// FILE: MISC.CPP

#include "misc.h"

#include <stdlib.h>
#include <ctype.h>
#include <dos.h>

/********************************************************************

 Screen::showChar

 This function displays the specified character at the specified
 position.

********************************************************************/


void Screen::showChar( Point loc, char chr, unsigned char attr )
{
    union REGS regs;

    regs.h.ah = 2;
    regs.h.bh = 0;
    regs.h.dh = --loc.y;
    regs.h.dl = --loc.x;

    int86( 0x10, &regs, &regs );

    regs.h.ah = 9;
    regs.h.al = (int)chr;
    regs.h.bh = 0;
    regs.h.bl = (int)attr;
    regs.x.cx = 1;
    int86( 0x10, &regs, &regs );
}

/********************************************************************

 Screen::setCurPos

 This function moves the screen cursor to the specified position.

********************************************************************/

void Screen::setCurPos( Point loc )
{
    union REGS regs;

    regs.h.ah = 2;
    regs.h.bh = 0;
    regs.h.dh = --loc.y;
    regs.h.dl = --loc.x;

    int86( 0x10, &regs, &regs );
}

/********************************************************************

 Screen::cursorOff

 This function hides the screen cursor.

********************************************************************/

void Screen::cursorOff()
{
    union REGS regs;

    regs.h.ah = 3;
    regs.h.bh = 0;

    int86( 0x10, &regs, &regs );

    cursorShape = regs.x.cx;

    regs.h.ah = 1;
    regs.x.cx = 0x2000;
    int86( 0x10, &regs, &regs );
}

/********************************************************************

 Screen::cursorOn

 This function displays the screen cursor.

********************************************************************/

void Screen::cursorOn()
{
    union REGS regs;

    regs.h.ah = 1;
    regs.x.cx = cursorShape;

    int86( 0x10, &regs, &regs );
}


Screen theScreen;  // global Screen object

/********************************************************************

 Mouse::Mouse

 This function checks whether a mouse exists and sets the
 existence flag accordingly.

********************************************************************/

Mouse::Mouse()
{

    if( reset() )
    {
        show();
        exists = 1;
    }
    else
        exists = 0;
}


/********************************************************************

 Mouse::reset

 This function resets the mouse.

********************************************************************/

int Mouse::reset()
{
    union REGS regs;

    regs.x.ax = 0;               // Mouse function 0: reset
    int86( 0x33, &regs, &regs );
    return regs.x.ax;
}


/********************************************************************

 Mouse::show

 This function displays the mouse cursor.

********************************************************************/

int Mouse::show()
{
    union REGS regs;

    if( exists )
    {
        regs.x.ax = 1;           // Mouse Function 1: show cursor
        int86( 0x33, &regs, &regs );
        return 1;
    }
    else return 0;
}

/********************************************************************

 Mouse::hide

 This function hides the mouse cursor.

********************************************************************/

int Mouse::hide()
{
    union REGS regs;

    if( exists )
    {
        regs.x.ax = 2;               // Mouse function 2: hide cursor
        int86( 0x33, &regs, &regs );
        return 1;
    }
    else return 0;
}

/********************************************************************

 Mouse::read

 This function reads the current position of the mouse cursor and
 the current status of the mouse buttons, whether or not any
 mouse event occurred.

********************************************************************/

int Mouse::read( MouseStatus *status )
{
    union REGS regs;

    if( exists )
    {
        regs.x.ax = 3;               // Mouse function 3: get status
        int86( 0x33, &regs, &regs );

        status->position.x = (regs.x.cx >> 3) + 1;
        status->position.y = (regs.x.dx >> 3) + 1;
        status->button = regs.x.bx;

        return 1;
    }
    else return 0;
}

/********************************************************************

 Mouse::move

 This function moves the mouse cursor to the specified position.

********************************************************************/

int Mouse::move( Point position )
{
    union REGS regs;

    if( exists )
    {
        position.x--;        // adjust column,row to virtual x,y coords
        position.y--;
        position.x <<= 3;
        position.y <<= 3;

        regs.x.ax = 4;             // Mouse function 4: move cursor
        regs.x.cx = position.x;
        regs.x.dx = position.y;
        int86( 0x33, &regs, &regs );
        return 1;
    }
    else return 0;
}


Mouse theMouse;   // global Mouse object

