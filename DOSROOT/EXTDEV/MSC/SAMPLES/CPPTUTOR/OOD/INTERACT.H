/********************************************************************

 FILE: INTERACT.H

 Defines the base class for interactors, defines the predefined
 control elements, and defines the base class for windows.

                 (Interactor)
                      |
               -------------
               |           |
           (Control)     (Win)
               |
         ------------
         |          |
     ScrollBar  PushButton   

********************************************************************/


#if !defined( _INTERACTOR_H_ )

#define _INTERACTOR_H_

#include "list.h"
#include "event.h"

typedef int Boolean;

const int FALSE = 0;
const int TRUE = 1;

struct ScreenChar
{
   char character;
   unsigned char attribute;
};

/********************************************************************

 Buffer

 Defines a rectangular buffer of ScreenChars.

 Public Interface:

     Buffer - constructor taking dimensions of the buffer and a
         text attribute to use as a default.

     Buffer - copy constructor.

     operator= - assignment operator.

     columns - returns columns.

     rows - returns rows.

     setChar - sets character and attribute at specified location.
         Uses default attribute if none specified.

     getChar - returns ScreenChar at specified location.

     putStr - writes string at specified location. Uses default
         attribute if none specified. The text is wrapped at the
         end of each line.

     ~Buffer - destructor.

********************************************************************/

class Buffer
{
public:
    Buffer( int wid, int len,
            unsigned char defAttr = WHITE_FORE | BLUE_BACK );
    Buffer( const Buffer &other );
    Buffer &operator=( const Buffer &other );
    int  columns() const;
    int  rows() const;
    void setChar( Point loc,char newChar, unsigned char newAttr = 0 );
    ScreenChar getChar( Point loc ) const;
    void putStr( Point loc, char *newStr, unsigned char newAttr = 0 );
   ~Buffer();
private:
   int width,
       length;
   unsigned char defaultAttr;
   ScreenChar *textArray;
};

inline int Buffer::columns() const
{
    return width;
}

inline int Buffer::rows() const
{
    return length;
}

/********************************************************************

 Interactor

 Defines a rectangular screen area that responds to events. This
 abstract class acts as a base class for windows and control
 elements.

 Public Interface:

     width - returns width.

     height - returns height.

     origin - returns coordinates of upper-left corner.

     withinBounds - tests whether a point falls within the
         Interactor's bounds.

     move - moves Interactor to specified location.

     resize - resizes Interactor to specified dimensions.

     activate - makes Interactor active (changes appearance).

     deactivate - makes Interactor inactive (changes appearance).

     paint - displays Interactor on screen.

     paintChar - displays single char.

     handleEvent - responds to passed Event.

********************************************************************/

class Interactor : public ListElem
{
public:
    int   width() const;
    int   height() const;
    Point origin() const;
    Boolean withinBounds( Point loc ) const;
    virtual void move( Point newLoc );
    virtual void resize( int newWidth, int newHeight );
    virtual void activate();
    virtual void deactivate();
    virtual void paint( Rect region ) = 0;
    virtual void paintChar( Point loc,
                            char character, unsigned char attr ) const = 0;
    virtual void handleEvent( const Event &action ) = 0;
    // note: virtual destructor inherited from ListElem
protected:
    Rect area;
    int  active;
    Rect paintingRegion;   // region in which painting occurs
                          // used by paintChar
};


inline int Interactor::width() const
{
    return area.width() + 1;
}

inline int Interactor::height() const
{
    return area.height() + 1;
}

inline Point Interactor::origin() const
{
    return Point( area.left, area.top );
}

inline Boolean Interactor::withinBounds( Point loc ) const
{
    return area.Contains( loc );
}

inline void Interactor::move( Point newLoc )
{
    area = Rect(newLoc.x,
                newLoc.y,
	            newLoc.x + area.width(),
                newLoc.y + area.height() );
}

inline void Interactor::resize( int newWidth, int newHeight )
{
    area = Rect(area.left,
                area.top,
   	            area.left + newWidth - 1,
                area.top  + newHeight - 1 );
}

inline void Interactor::activate()
{
    active = 1;
}

inline void Interactor::deactivate()
{
    active = 0;
}

/********************************************************************

 Win

 Describes properties of all top-level windows, e.g. having a
 title and a frame. This abstract class acts as a base class for
 all windows.

 Public Interface:

     setTitle - sets title to specified string.

     paintFrame - paints frame and title on screen.

 (Redefined from Win)

     paintChar - redefined to translate local coordinates to
         global coordinates when painting character.

 Protected Interface:

     Win - constructor taking no arguments. Used to initialize
         title to 0.

     ~Win - destructor. Used to free title if one exists.

********************************************************************/

class Win : public Interactor
{
public:
    int  setTitle( char *titl );
    void paintFrame() const;
    virtual void paint( Rect region ) = 0;
    void paintChar( Point location,
		           char character, unsigned char attr ) const;
    virtual void handleEvent( const Event &action ) = 0;
protected:
    Win() : title( 0 ) {}
    ~Win();
private:
    char *title;
};

inline void Win::paintChar( Point loc,
                            char character, unsigned char attr ) const
{
    if ( paintingRegion.Contains( loc ) )
        theScreen.showChar( origin() + loc, character, attr );
}

inline Win::~Win()
{
    if ( title )
        delete title;
}

/********************************************************************

 Control

 Defines properties of all control elements. This abstract class acts
 as a base class for all controls.

 Public Interface:

 (Redefined from Win)

    paintChar - redefined to translate local coordinates to parent
        window's coordinates, and calls parent's paintChar.

 Protected Interface:

    Control - constructor taking parent window.
        (Because parentWin is a const pointer, it can only be
        initialized in Control's constructor and cannot be assigned
        a value in the constructors of any derived classes. A
        protected constructor lets the derived classes construct a
        Control object and initialize parentWin's value.)

********************************************************************/

class Control : public Interactor
{
public:
    virtual void paint( Rect region ) = 0;
    virtual void handleEvent( const Event &action ) = 0;
    void paintChar( Point location,
                    char character, unsigned char attr ) const;
protected:
    Win *const parentWin;
    Control( Win *parent ) : parentWin( parent ) {}

};


inline void Control::paintChar( Point loc,
				                char character,
				                unsigned char attr ) const
{
    if ( paintingRegion.Contains( loc ) )
        parentWin->paintChar( origin() + loc, character, attr );
}

/********************************************************************

 ScrollBar

 Defines scroll bar control elements, either horizontal or
 vertical. The scroll bars respond only to single mouse clicks,
 not to mouse drags or holding down a mouse button. A click on
 either end means "move one line," and a click on either side
 of the slider means "move one page." When clicked, a scroll bar
 sends a ScrollEvent to its parent window.

 Public Interface:

     ScrollBar - constructor taking a parent window, the position of
         the scroll bar on the window, the length of the scroll bar,
         and a flag indicating its orientation

     setSlider - sets slider to specified position. Takes a number
         from 1 to 100, inclusive.

 (Redefined from Control)

     resize - redefined to restrict the width of vertical scroll bars,
         and the height of horizontal ones, to one character.

     paint - redefined to paint scroll bar on screen.

     handleEvent - redefined to implement scroll bar behavior.

********************************************************************/

enum ScrollerType { VERT = 1, HORIZ = 2 };

class ScrollBar : public Control
{
public:
    ScrollBar( Win *parent, Point location, int len, int orient );
    // use default copy constructor (memberwise initialization)
    // use default operator=  (memberwise assignment)
    void resize( int newWidth, int newLength );
    int  setSlider( int pos );                // set position of slider
    void paint( Rect region );
    void handleEvent( const Event &action );
private:
    int sliderPos;
    int length;
    int orientation;
};


/********************************************************************

 PushButton

 Defines push button control elements. A push button inverts its
 display momentarily when clicked, and sends a PushEvent to its
 parent window.

 Public Interface:

     PushButton - constructor taking a parent window, the location of
         the button on the window, and a label for the button

 (Redefined from Win)

     paint - redefined to paint button on screen.

     handleEvent - redefined to implement push button behavior.

********************************************************************/

class PushButton : public Control
{
public:
    PushButton( Win *parent, Point location, char *labl );
    // use default copy constructor (memberwise initialization)
    // use default operator=  (memberwise assignment)
    void paint( Rect region );
    void handleEvent( const Event &action );
private:
    char label[30];
    int  pressed;
};

#endif // _INTERACTOR_H_
