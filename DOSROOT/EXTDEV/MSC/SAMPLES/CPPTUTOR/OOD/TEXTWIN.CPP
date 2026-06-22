/******************************************************************

 FILE: TEXTWIN.CPP

******************************************************************/

#include "textwin.h"

#include <ctype.h>

/******************************************************************

 TextWin::TextWin

 This function creates a text window. It compares the size of the
 text buffer with the size of the window, and allocates scrollbars
 as needed.

******************************************************************/

TextWin::TextWin( Point location, int wid, int len, Buffer *sheet )
: Win(), canvas( *sheet )
{
    wid = min( wid, canvas.columns() + 2 );  // make sure window isn't
    len = min( len, canvas.rows() + 2 );     //   larger than text buffer, or
    wid = max( wid, TEXTWIN_MINWIDTH );      //   smaller than minimum
    len = max( len, TEXTWIN_MINHEIGHT );

    area = Rect( location.x,
                 location.y,
                 location.x + wid - 1,
                 location.y + len - 1 );

    textView = Rect( 1, 1, wid - 2, len - 2 );

    vscroller = hscroller = 0;

    if( canvas.rows() > textView.height() + 1 )
    {
        vscroller = new ScrollBar( this,
                                   Point( textView.right + 1, textView.top ),
                                   textView.height() + 1,
                                   VERT );
    }

    if( canvas.columns() > textView.width() + 1 )
    {
        hscroller = new ScrollBar( this,
                                   Point( textView.left, textView.bottom + 1 ),
                                   textView.width() + 1,
                                   HORIZ );
    }

    Interactor::activate();

    canvasOffset = Point( 0, 0 );
    cursorPos = Point( 0, 0 );
}

/******************************************************************

 TextWin::TextWin - copy constructor

******************************************************************/

TextWin::TextWin( const TextWin& other )
: canvas( other.canvas )
{
    if( other.hscroller )
        hscroller = new ScrollBar( *other.hscroller );
    if( other.vscroller )
        vscroller = new ScrollBar( *other.vscroller );

    canvas = other.canvas;
    textView = other.textView;
    canvasOffset = other.canvasOffset;
    cursorPos = other.cursorPos;
}

/******************************************************************

 TextWin::operator=

******************************************************************/

TextWin &TextWin::operator=( const TextWin& other )
{
    if( &other == this )   // check for self-assignment
       return *this;

    if( hscroller )
        delete hscroller;
    if( vscroller )
        delete vscroller;

    if( other.hscroller )
        hscroller = new ScrollBar( *other.hscroller );
    if( other.vscroller )
        vscroller = new ScrollBar( *other.vscroller );

    canvas = other.canvas;
    textView = other.textView;
    canvasOffset = other.canvasOffset;
    cursorPos = other.cursorPos;

    return *this;
}

/******************************************************************

 TextWin::resize

 This function resizes the window to the specified dimensions.
 If the specified dimensions fall below the minimum text window
 size, or above the size of the text buffer, the specified
 dimensions are adjusted accordingly. The function deletes or
 creates scroll bars, as needed, and adjusts the position of
 the window on the text buffer.

******************************************************************/

void TextWin::resize( int newWidth, int newHeight )
{
    if( (newWidth == width())  &&
        (newHeight == height())  )
        return;                     // if same size, return

    newWidth = min( newWidth, canvas.columns() + 2 );  // ensure that window isn't
    newWidth = max( newWidth, TEXTWIN_MINWIDTH );      //   larger than text buffer,
    newHeight = min( newHeight, canvas.rows() + 2 );   //   or smaller than minimum
    newHeight = max( newHeight, TEXTWIN_MINHEIGHT );

    textView = Rect( 1, 1, newWidth - 2, newHeight - 2 );

    Interactor::resize( newWidth, newHeight );

    if( canvas.rows() > textView.height() + 1 )  // Vertical scrollbar needed
    {
        if( vscroller )
            delete vscroller;
        vscroller = new ScrollBar( this,
                                   Point( textView.right + 1, textView.top ),
                                   textView.height() + 1,
                                   VERT );
        vscroller->setSlider( (canvasOffset.y * 100) / (canvas.rows() - (textView.height() + 1)) );
    }
    else if( vscroller )  // No vertical scrollbar needed
    {
        delete vscroller;
        vscroller = 0;
    }

    if( canvas.columns() > textView.width() + 1 ) // Horizontal scrollbar needed
    {
        if( hscroller )
            delete hscroller;
        hscroller = new ScrollBar( this,
                                   Point( textView.left, textView.bottom + 1 ),
                                   textView.width() + 1,
                                   HORIZ );
        hscroller->setSlider( (canvasOffset.x * 100) / (canvas.columns() - (textView.width() + 1)) );
    }
    else if( hscroller )  // No horizontal scrollbar needed
    {
        delete hscroller;
        hscroller = 0;
    }

    setCanvasOffset( getCanvasOffset() );  // Adjust canvas offset and cursor position
}

/******************************************************************

 TextWin::activate

 This function activates the window and the scroll bars, if any
 exist.

******************************************************************/

void TextWin::activate()
{
    Interactor::activate();

    if( hscroller )
        hscroller->activate();
    if( vscroller )
        vscroller->activate();
}

/******************************************************************

 TextWin::deactivate

 This function deactivates the window and the scroll bars, if any
 exist.

******************************************************************/

void TextWin::deactivate()
{
    Interactor::deactivate();

    if( hscroller )
        hscroller->deactivate();
    if( vscroller )
        vscroller->deactivate();
}


/******************************************************************

 TextWin::paint

 This function repaints the window, including text and scrollbars.
 The painting region is set to the invalid rectangle for the
 window's own painting. The invalid rectangle is passed on to the
 scrollbars' paint functions, displaced to fit their coordinate
 systems. Finally the painting region is reset to the entire
 window, for the next time the window becomes active.

******************************************************************/

void TextWin::paint( Rect invalid )
{
    paintingRegion = invalid;

    paintFrame();
    if( vscroller )
        vscroller->paint( invalid - vscroller->origin() );
    if( hscroller )
        hscroller->paint( invalid - hscroller->origin() );
    paintText();

    paintingRegion = Rect( 0, 0, width(), height() );
}

/******************************************************************

 TextWin::paintText

 This function repaints the text displayed in the window.
 The mouse and text cursors are hidden, and the currently visible
 text from the canvas is displayed.

******************************************************************/

void TextWin::paintText() const
{
    int i,j;
    MouseStatus mouseStat;

    ScreenChar temp;

    theMouse.read( &mouseStat );
    if( withinBounds( mouseStat.position ) )
        theMouse.hide();

    theScreen.cursorOff();

    for( i = 0; i < textView.width() + 1; i++ )
    {
        for( j = 0; j < textView.height() + 1; j++ )
        {
            temp = canvas.getChar( Point( i + canvasOffset.x,
                                          j + canvasOffset.y) );
            paintChar( Point( textView.left,
                              textView.top ) + Point( i, j ),
                       temp.character, temp.attribute );
        }
    }

    updateCursor();
    theScreen.cursorOn();
    if( withinBounds( mouseStat.position ) )
        theMouse.show();
}


/******************************************************************

 TextWin::updateCursor

 This function moves the screen cursor to the location specified
 by the cursorPos member variable.

******************************************************************/

void TextWin::updateCursor() const
{
    theScreen.setCurPos( origin() +
                         cursorPos +
                         Point( textView.left, textView.top ) -
                         canvasOffset );
}


/******************************************************************

 TextWin::updateScrollBars

 This function sets the scrollbar sliders, and repaints them.

******************************************************************/

void TextWin::updateScrollBars()
{
    if( vscroller )
    {
        vscroller->setSlider( (canvasOffset.y * 100) /
                              (canvas.rows() - (textView.height() + 1)) );
        vscroller->paint( Rect( 0, 0,
                                vscroller->width(), vscroller->height() ) );
    }
    if( hscroller )
    {
        hscroller->setSlider( (canvasOffset.x * 100) /
                              (canvas.columns() - (textView.width() + 1)) );
        hscroller->paint( Rect( 0, 0,
                                hscroller->width(), hscroller->height() ) );
    }
}


/********************************************************************

 TextWin::setCanvasOffset

 The canvas offset is the text buffer position of the first character
 displayed text in the window.

 This function sets the canvas offset to the specified location.
 If the cursor position no longer falls within the displayed
 area of text (specified by the canvas offset and the dimensions of
 the window), the cursor position is adjusted. This keeps the cursor
 on screen when scrolling is performed with the scroll bars.

********************************************************************/

void TextWin::setCanvasOffset( Point pos )
{

    // ensure that text area doesn't fall outside text buffer
    pos.y = max( pos.y, 0 );
    pos.y = min( pos.y, canvas.rows() - (textView.height() + 1) );
    pos.x = max( pos.x, 0 );
    pos.x = min( pos.x, canvas.columns() - (textView.width() + 1) );

    canvasOffset = pos;

    // move cursor within displayed text area
    cursorPos.y = max( pos.y, cursorPos.y );
    cursorPos.y = min( pos.y + textView.height(), cursorPos.y );
    cursorPos.x = max( pos.x, cursorPos.x );
    cursorPos.x = min( pos.x + textView.width(), cursorPos.x );
}


/******************************************************************

 TextWin::setCursorPos

 This function sets the cursor to the specified location. If the
 new cursor position doesn't fall within the currently displayed
 area of text, the canvas offset is adjusted just enough so that
 the cursor position is displayed. This allows cursor movement to
 causes scrolling.

 returns: TRUE, if the text displayed has been shifted. Requires
              that paintText() be called.
          FALSE, if the text displayed has not been shifted.
              Requires that updateCursor() be called.

******************************************************************/

int TextWin::setCursorPos( Point loc )
{
    int shifted = FALSE;
    Point newCanvasOffset = canvasOffset;

    // ensure that cursor is within text buffer
    loc.y = max( loc.y, 0 );
    loc.y = min( loc.y, canvas.rows() - 1 );
    loc.x = max( loc.x, 0 );
    loc.x = min( loc.x, canvas.columns() - 1 );

    cursorPos = loc;

    // check if cursor is outside displayed text area
    if( cursorPos.y < canvasOffset.y )
    {
        newCanvasOffset.y = cursorPos.y;
        shifted = TRUE;
    }
    else if( cursorPos.y > canvasOffset.y + textView.height() )
    {
        newCanvasOffset.y = cursorPos.y - textView.height();
        shifted = TRUE;
    }

    if( cursorPos.x < canvasOffset.x )
    {
        newCanvasOffset.x = cursorPos.x;
        shifted = TRUE;
    }
    else if( cursorPos.x > canvasOffset.x + textView.width() )
    {
        newCanvasOffset.x = cursorPos.x - textView.width();
        shifted = TRUE;
    }

    if( shifted )  // adjust canvas offset so cursor is within bounds
        canvasOffset = newCanvasOffset;

    return shifted;
}


/******************************************************************

 TextWin::handleEvent

 This function determines the type of event, and passes it on to
 the appropriate event handler.

******************************************************************/

void TextWin::handleEvent( const Event &action )
{
    switch ( action.getType() )
    {
    case KBD_EVENT:
        handleKey( (KbdEvent &)action );
        break;
    case MOUSE_EVENT:
        handleMouse( (MouseEvent &)action );
        break;
    case SCRL_EVENT:
        handleScroll( (ScrollEvent &)action );
        break;
    default:
        break;
    };
}


/******************************************************************

 TextWin::handleKey

 This function handles keyboard events. The cursor movement keys
 are handled, including the arrow keys, HOME, END, PGUP, and PGDN.

******************************************************************/

void TextWin::handleKey( const KbdEvent &key )
{
    if( (key.val() == UPARROW) ||
        (key.val() == DOWNARROW) ||
        (key.val() == LEFTARROW) ||
        (key.val() == RIGHTARROW) ||
        (key.val() == HOME) ||
        (key.val() == END) )
    {
        Point delta;    // a vector indicating cursor movement

        switch ( key.val() )
        {
        case UPARROW:
            delta = Point( 0, -1 );
            break;
        case DOWNARROW:
            delta = Point( 0, 1 );
            break;
        case LEFTARROW:
            delta = Point( -1, 0 );
            break;
        case RIGHTARROW:
            delta = Point( 1, 0 );
            break;
        case HOME:
            delta = Point( -cursorPos.x, 0 );
            break;
        case END:
            delta = Point( canvas.columns() - 1 - cursorPos.x, 0 );
            break;
        default:
            break;
        }

        if( setCursorPos( cursorPos + delta ) )
        {
            updateScrollBars();
            paintText();
        }
        else
            updateCursor();
    }
    else

        switch( key.val() )
        {
        case PGUP:
           setCanvasOffset( canvasOffset + Point( 0, -textView.height() + 1 ) );
           updateScrollBars();
           paintText();
           break;
        case PGDN:
           setCanvasOffset( canvasOffset + Point( 0, textView.height() - 1 ) );
           updateScrollBars();
           paintText();
           break;
        default:
           break;
        };
}


/******************************************************************

 TextWin::handleMouse

 This function handles mouse events. Mouse events that fall on
 one of the scrollbars are passed to that object. The location of
 the mouse event is translated to the scrollbar's coordinate system
 when it is passed. Mouse events that fall on the text cause the
 cursor position to be updated.

******************************************************************/

void TextWin::handleMouse( const MouseEvent &action )
{
    if( vscroller &&
        vscroller->withinBounds( action.getPosition() ) )
    {
        MouseEvent localAction( action.getPosition() - vscroller->origin(),
                                action.getButton() );
        vscroller->handleEvent( localAction );
    }
    else if( hscroller &&
             hscroller->withinBounds( action.getPosition() ) )
    {
        MouseEvent localAction( action.getPosition() - hscroller->origin(),
                                action.getButton() );
        hscroller->handleEvent( localAction );
    }
    else if( textView.Contains( action.getPosition() ) )
    {
       setCursorPos( action.getPosition() -
                     Point( textView.left, textView.top ) +
                     canvasOffset );
       updateCursor();
    }
}

/******************************************************************

 TextWin::handleScroll

 This function handles scrolling events. The magnitude and
 direction of the event is examined, and the source of the
 event is checked against the window's scrollbars. A vector
 indicating the amount of text movement is defined, and the
 cursor is moved accordingly.

******************************************************************/

void TextWin::handleScroll( const ScrollEvent &action )
{
    int dir = action.getDirection(),
        dist = action.getDistance();
    ScrollBar *source = action.getSource();

    Point delta;  // a vector indicating text scrolling

    if( dir == FORWARD )
    {
        if( dist == LINE )
            if( source == vscroller )
                delta = Point( 0, 1 );
            else
                delta = Point( 1, 0 );

        else  // dist == PAGE
            if( source == vscroller )
                delta = Point( 0, textView.height() - 1 );
        else
                delta = Point( textView.width() - 1, 0 );
    }
    else  // dir == BACKWARD
    {
        if( dist == LINE )
            if( source == vscroller )
                delta = Point( 0, -1 );
            else
                delta = Point( -1, 0 );

        else  // dist == PAGE
            if( source == vscroller )
                delta = Point( 0, -textView.height() + 1 );
            else
                delta = Point( -textView.width() + 1, 0 );
    }

    setCanvasOffset( canvasOffset + delta );

    updateScrollBars();
    paintText();

}

/******************************************************************

 TextWin::~TextWin

 This function deletes the scroll bars, if any exist.

******************************************************************/

TextWin::~TextWin()
{
    if( hscroller )
        delete hscroller;
    if( vscroller )
        delete vscroller;

}


/******************************************************************

 EditWin::handleEvent

 This function performs the event handling specific to editing
 windows. If the received event is a keyboard event, and if it
 is a printable character, the text buffer is modified and the
 cursor position is updated. The backspace key is also handled.
 All other events, keyboard or otherwise, are passed to TextWin's
 handleEvent function.

******************************************************************/

void EditWin::handleEvent( const Event &action )
{
    Point newCursorPos;

    switch ( action.getType() )
    {
    case KBD_EVENT:
    {
        KbdEvent &key = (KbdEvent &)action;

        if( isprint( (char)key.val() ) )
        {
            canvas.setChar( getCursorPos(), key.val() );

            newCursorPos = getCursorPos();
            newCursorPos.x++;

            if( newCursorPos.x == canvas.columns() )
            {
                newCursorPos.x = 0;
                newCursorPos.y++;
            }
            if( newCursorPos.y == canvas.rows() )
                newCursorPos = Point( canvas.columns() - 1,
                                      canvas.rows() - 1 );

            if( setCursorPos( newCursorPos ) )   // setCursorPos handles scrolling
                updateScrollBars();

            paintText();
        }
        else
            TextWin::handleEvent( action );

        break;
    }
    default:
        TextWin::handleEvent( action );
        break;
    };
}
