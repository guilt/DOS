/********************************************************************

 FILE: WINMGR.CPP

********************************************************************/

#include "winmgr.h"

/********************************************************************

 WinMgr::handleEvent

 This function sends keyboard events to the handleKey function and
 mouse events to the handleMouse function.

********************************************************************/

void WinMgr::handleEvent( const Event &action )
{
    switch ( action.getType() )
    {
    case KBD_EVENT:
        handleKey( (KbdEvent &) action );
        break;

    case MOUSE_EVENT:
        handleMouse( (MouseEvent &) action );
        break;

    default:
        break;
    }
}

/********************************************************************

 WinMgr::handleMouse

 This function directs mouse events to the various windows. First
 it sees whether any windows exist, and then it iterates through the
 list of windows and looks for the first window that the given
 MouseEvent falls on. If that window is the active one, the location
 of the MouseEvent is translated to the window's coordinate system
 and passed to the window's handleEvent function. If not, the
 function sees if the event falls within the borders of another
 window, and if so, it activates that window. The previously active
 window is deactivated, and the new active window is moved to the
 end of the list.

********************************************************************/

void WinMgr::handleMouse( const MouseEvent &action )
{
    Win *targetWin;

    if( winlist.isEmpty() )
        return;

    winlist.initIterator();
    targetWin = (Win *)winlist.getPrev();
    if( targetWin->withinBounds( action.getPosition() ) )
    {
        MouseEvent localAction( action.getPosition() - targetWin->origin(),
                                action.getButton() );

        targetWin->handleEvent( localAction );
    }
    else
     {
        while( (targetWin = (Win *)winlist.getPrev()) != 0 )
        {
            if( targetWin->withinBounds( action.getPosition() ) )
            {
                Win *oldActive = (Win *)winlist.getTail();

                oldActive->deactivate();
                oldActive->paint( Rect( 0, 0, oldActive->width(), oldActive->height() ) );

                winlist.remove();   // remove current
                winlist.addTail( targetWin );

                targetWin->activate();
                targetWin->paint( Rect( 0, 0, targetWin->width(), targetWin->height() ) );
                break;
            }
        }
    }

}

/********************************************************************

 WinMgr::handleKey

 This function screens keyboard events, responding to some and
 passing the rest on to the active window to handle. If the key hit
 was ESC, the program is exited (this is the only event that can be
 handled without any windows existing). If the key wasn't ESC, the
 function checks whether any windows exist, and then examines the
 keyboard event. The keys handled are TAB (cycle through windows),
 CTRL-T, CTRL-F, CTRL-G, CTRL-V (resizing: make window shorter,
 narrower, wider, or longer, respectively), CTRL-U, CTRL-H, CTRL-J,
 CTRL-N (move window up, left, right, or down, respectively), and
 DELETE (remove window). Any other keyboard events are passed to
 the individual windows.

********************************************************************/

void WinMgr::handleKey( const KbdEvent &key )
{
    Rect invalid;
    int w, h;
    Win *activeWin;

    if( key.val() == ESC )  // quit
        exit(1);

    if( winlist.isEmpty() )
        return;

    switch ( key.val() )
    {
    case TAB:         // next window
        Win *oldActive,
            *newActive;

        oldActive = (Win *)winlist.getTail();
        oldActive->deactivate();
        oldActive->paint( Rect( 0, 0, oldActive->width(), oldActive->height() ) );

        newActive = (Win *)winlist.removeHead();
        winlist.addTail( newActive );
        newActive->activate();
        newActive->paint( Rect( 0, 0, newActive->width(), newActive->height() ) );
        break;

    case ExtChar(20,0): // ctrl-T: resize
        activeWin = (Win *)winlist.getTail();
        w = activeWin->width();
        h = activeWin->height();

        activeWin->resize(w, h - 1);

        invalid = Rect( activeWin->origin() + Point( 0, h - 1 ),
                        activeWin->origin() + Point( w - 1, h - 1 ) );

        activeWin->paint( Rect( 0, 0, w, h - 1 ) );
        repaint( invalid );
        break;

    case ExtChar(6,0): // ctrl-F: resize
        activeWin = (Win *)winlist.getTail();
        w = activeWin->width();
        h = activeWin->height();

        activeWin->resize(w - 1, h );

        invalid = Rect( activeWin->origin() + Point( w - 1, 0 ),
                        activeWin->origin() + Point( w - 1, h - 1 ) );
        activeWin->paint( Rect( 0, 0, w - 1, h ) );
        repaint( invalid );
    break;

    case ExtChar(7,0): // ctrl-G: resize
        activeWin = (Win *)winlist.getTail();
        w = activeWin->width();
        h = activeWin->height();

        activeWin->resize(w + 1, h );
        activeWin->paint( Rect( 0, 0, w + 1, h ) );
        break;

    case ExtChar(22,0): // ctrl-V: resize
        activeWin = (Win *)winlist.getTail();
        w = activeWin->width();
        h = activeWin->height();

        activeWin->resize( w, h + 1 );
        activeWin->paint( Rect( 0, 0, w, h + 1 ) );
        break;

    case ExtChar(21,0): // ctrl-U: move
        activeWin = (Win *)winlist.getTail();
        w = activeWin->width();
        h = activeWin->height();

        activeWin->move( activeWin->origin() + Point( 0, -1 ) );

        invalid = Rect( activeWin->origin() + Point( 0, h ),
                        activeWin->origin() + Point( w - 1, h ) );

        activeWin->paint( Rect( 0, 0, w, h ) );
        repaint( invalid );
        break;

    case ExtChar(8,0): // ctrl-H: move
        activeWin = (Win *)winlist.getTail();
        w = activeWin->width();
        h = activeWin->height();

        activeWin->move( activeWin->origin() + Point( -1, 0 ) );

        invalid = Rect( activeWin->origin() + Point( w, 0 ),
                        activeWin->origin() + Point( w, h - 1 ) );
        activeWin->paint( Rect( 0, 0, w, h ) );
        repaint( invalid );
    break;

    case ExtChar(10,0): // ctrl-J: move
        activeWin = (Win *)winlist.getTail();
        w = activeWin->width();
        h = activeWin->height();

        activeWin->move( activeWin->origin() + Point( 1, 0 ) );

        invalid = Rect( activeWin->origin() + Point( -1, 0 ),
                        activeWin->origin() + Point( -1, h - 1 ) );

        activeWin->paint( Rect( 0, 0, w, h ) );
        repaint( invalid );
        break;

    case ExtChar(14,0): // ctrl-N: move
        activeWin = (Win *)winlist.getTail();
        w = activeWin->width();
        h = activeWin->height();

        activeWin->move( activeWin->origin() + Point( 0, 1 ) );

        invalid = Rect( activeWin->origin() + Point( 0, -1 ),
                        activeWin->origin() + Point( w - 1, -1 ) );

        activeWin->paint( Rect( 0, 0, w, h ) );
        repaint( invalid );
        break;

    case ExtChar(0,83): // DELETE
        deleteWindow();
        break;

    default:
        activeWin = (Win *)winlist.getTail();
        activeWin->handleEvent(key);
        break;
    };

}

/********************************************************************

 WinMgr::addWindow

 This function adds a window to the list. The previously active
 window is deactivated, and the new window is added to the end of
 the list and activated.

********************************************************************/

void WinMgr::addWindow( Win *newWindow )
{
    Win *oldActive;

    oldActive = (Win *)winlist.getTail();
    if( oldActive != 0 )
        oldActive->deactivate();
    winlist.addTail( newWindow );
    newWindow->activate();
}

/********************************************************************

 WinMgr::deleteWindow

 This function removes the active window from the list. The window
 is removed and the area it occupied is repainted. The new active
 window is activated.

********************************************************************/

void WinMgr::deleteWindow()
{
    Win *deleted,
        *newActive;
    Rect invalid;
    int w, h;

    if( !winlist.isEmpty() )
    {
        deleted = (Win *)winlist.removeTail();
        w = deleted->width();
        h = deleted->height();
        invalid = Rect( deleted->origin(),
                        deleted->origin() + Point( w, h ) );

        if( (newActive = (Win *)winlist.getTail()) != 0 )
        {
            newActive->activate();
            newActive->paint( Rect( 0, 0, newActive->width(), newActive->height() ) );
        }
        repaint( invalid );
    }
}

/********************************************************************

 WinMgr::repaint

 This function repaints the specified region of the screen. The
 background color is written to the area, and then each window
 in the list paints over the area.

********************************************************************/

void WinMgr::repaint( Rect region )
{
    Win *currWin;
    int x, y;

    theScreen.cursorOff();
    for( x = region.left; x <= region.right; x++ )
        for( y = region.top; y <= region.bottom; y++ )
            theScreen.showChar( Point( x, y ), ' ', WHITE_FORE | BLACK_BACK );
    theScreen.cursorOn();

    winlist.initIterator();
    while( (currWin = (Win *)winlist.getNext()) != 0 )
        currWin->paint( region - currWin->origin() );

}

