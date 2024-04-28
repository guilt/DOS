/********************************************************************

 FILE: TEXTWIN.H

 Defines text windows and editable text windows (derived from Win).

  TextWin
     |
  EditWin

********************************************************************/

#if !defined( _TEXTWIN_H_ )

#define _TEXTWIN_H_

#include "interact.h"

/********************************************************************

 TextWin

 Defines scrollable text windows. A text window receives a
 rectangular text buffer at construction, and can have vertical
 and/or horizontal scrollbars depending on the dimensions of the
 text buffer compared to those of the window. A text window has
 a cursor that responds to the arrow keys and the PGUP, PGDN,
 HOME and END keys. The scrollbars can be used to scroll the
 text, and their sliders reflect the position of the displayed
 text when the cursor is used to scroll.

 Public Interface:

     TextWin - constructor taking a location, the dimensions of the
         window, and a text buffer.

     TextWin - copy constructor.

     operator= - assignment operator.

 (Redefined from Win)

     resize - redefined to add, remove, or resize scroll bars.

     activate - redefined to activate scroll bars.

     deactivate - redefined to deactivate scroll bars.

     paint - redefined to paint text window.

     handleEvent - redefined to implement text window behavior.

 Protected Interface:

     setCanvasOffset - sets the canvas offset (the text buffer
         coordinates of the character displayed in the upper left
         corner of the window) to the specified position. If the
         cursor position doesn't fall within the region of text
         specified by the canvas offset and the window dimensions,
         the cursor position is updated accordingly. This keeps the
         cursor on screen when the scroll bars are used to scroll.

     getCanvasOffset - returns canvas offset.

     setCursorPos - moves the cursor to the specified position within
         the text buffer. If the new cursor position doesn't fall
         within the region of text specified by the canvas offset and
         the window dimensions, the canvas offset is updated
         accordingly. This allows scrolling to be performed by moving
         the cursor. Returns TRUE if the canvas offset has been
         changed, indicating that paintText must be called.
         Otherwise, only updateCursor needs to be called.

     getCursorPos - returns the cursor position.

     updateCursor - updates the screen display of the cursor to reflect
         the cursor's position.

     updateScrollBars - repaints the scroll bars to reflect the cursor's
         position.

     paintText - repaints the text to reflect the current canvas offset.

 (data members)

     hscroller, vscroller - pointers to horizontal and vertical scroll
         bars. equal to 0 if no such scroll bar exists.

     canvas - Buffer object containing text being displayed.

     textView - rectangle indicating region where text is displayed
         (as opposed to window frame, buttons, etc.).

********************************************************************/

const int TEXTWIN_MINWIDTH = 5;
const int TEXTWIN_MINHEIGHT = 5;

class TextWin : public Win
{
public:
    TextWin( Point location, int wid, int len, Buffer *sheet );
    TextWin( const TextWin &other );
    TextWin &operator=( const TextWin &other );
    void resize( int newWidth, int newHeight );
    void activate();
    void deactivate();
    void paint( Rect region );
    void handleEvent( const Event &action );
   ~TextWin();
protected:
    void  setCanvasOffset( Point pos );  // position of window on canvas
    Point getCanvasOffset() const;
    int   setCursorPos( Point pos );
    Point getCursorPos() const;
    void  updateCursor() const;
    void  updateScrollBars();
    void  paintText() const;

    ScrollBar *hscroller;
    ScrollBar *vscroller;
    Buffer &canvas;
    Rect   textView;
private:
    void  handleKey( const KbdEvent &key );
    void  handleMouse( const MouseEvent &action );
    void  handleScroll( const ScrollEvent &action );

    Point canvasOffset;                // position of window on canvas
    Point cursorPos;
};

inline Point TextWin::getCanvasOffset() const
{
    return canvasOffset;
}

inline Point TextWin::getCursorPos() const
{
    return cursorPos;
}

/********************************************************************

 EditWin

 Defines scrollable text windows that accept input from the
 keyboard.

 Public Interface:

     EditWin - constructor taking a location, the dimensions of the
         window, and a text buffer

 (inherited from TextWin)

     handleEvent - redefined to allows text input

********************************************************************/

class EditWin : public TextWin
{
public:
    EditWin( Point location, int wid, int len, Buffer *sheet )
     : TextWin( location, wid, len, sheet) {}
    void handleEvent( const Event &action );
};


#endif // _TEXTWIN_H_
