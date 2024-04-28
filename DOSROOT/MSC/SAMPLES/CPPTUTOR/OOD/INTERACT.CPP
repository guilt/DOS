/********************************************************************

 FILE: INTERACT.CPP

********************************************************************/

#include "interact.h"

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <dos.h>
#include <string.h>

/********************************************************************

 Buffer::Buffer

********************************************************************/

Buffer::Buffer( int wid, int len, unsigned char defAttr )
{
    int i, j;

    width = wid;
    length = len;
    textArray = new ScreenChar[wid * len];
    defaultAttr = defAttr;

    for( i = 0; i < width; i++ )
       for( j = 0; j < length; j++ )
	       setChar( Point( i, j ), ' ', defaultAttr );
}


/********************************************************************

 Buffer::Buffer - copy constructor

********************************************************************/

Buffer::Buffer( const Buffer &other )
{
    int i, j;
    ScreenChar temp;

    width = other.width;
    length = other.length;
    textArray = new ScreenChar[ width * length ];
    for( i = 0; i < width; i++ )
        for( j = 0; j < length; j++ )
        {
            temp = other.getChar( Point( i, j ) );
	        setChar( Point( i, j ), temp.character, temp.attribute );
        }
    defaultAttr = other.defaultAttr;
}

/********************************************************************

 Buffer::operator=

 This function assigns one buffer to another.

********************************************************************/

Buffer &Buffer::operator=( const Buffer &other )
{
    int i, j;
    ScreenChar temp;

    if( &other == this)   // check for self-assignment
        return *this;

    width = other.width;
    length = other.length;
    delete textArray;
    textArray = new ScreenChar[ width * length ];
    for( i = 0; i < width; i++ )
        for( j = 0; j < length; j++ )
        {
            temp = other.getChar( Point( i, j ) );
	        setChar( Point( i, j ), temp.character, temp.attribute );
        }
    defaultAttr = other.defaultAttr;
    return *this;
}

/********************************************************************

 Buffer::setChar

 This function sets the character at the specified location. If no
 attribute is specified, the default attribute of the buffer is used.

********************************************************************/

void Buffer::setChar( Point loc, char newChar, unsigned char newAttr )
{
   if( newAttr == 0 )
      newAttr = defaultAttr;

   textArray[(loc.y * width) + loc.x].character = newChar;
   textArray[(loc.y * width) + loc.x].attribute = newAttr;
}

/********************************************************************

 Buffer::getChar

 This function returns the ScreenChar found at the specified location.

********************************************************************/

ScreenChar Buffer::getChar( Point loc ) const
{
   ScreenChar temp;

   temp.character = textArray[(loc.y * width) + loc.x].character;
   temp.attribute = textArray[(loc.y * width) + loc.x].attribute;

   return temp;
}

/********************************************************************

 Buffer::putStr

 This function writes a string at the specified location. If no
 attribute was specified, the default attribute of the buffer is
 used. Text is wrapped at the end of each line.

********************************************************************/

void Buffer::putStr( Point loc, char *newStr, unsigned char newAttr )
{
    int i = 0;

    if( newAttr == 0 )
       newAttr = defaultAttr;

    while( newStr[i] != '\0' )
    {
       setChar( loc, newStr[i], newAttr );
       loc.x++;
       if( loc.x == width )
       {
     	  loc.x = 0;
	      loc.y++;
       }
       if( loc.y == length )
	      return;

       i++;
    }
}

/********************************************************************

 Buffer::~Buffer

********************************************************************/

Buffer::~Buffer()
{
   delete textArray;
}

/********************************************************************

 Win::setTitle

 This function sets the title of a window.

********************************************************************/

int Win::setTitle( char *newstr )
{
   if( title )
       delete title;

   title = new char[strlen( newstr ) + 1];

   strcpy( title, newstr );

   return 1;
}

/********************************************************************

 Win::paintFrame

 This function paints the frame around a top-level window. A
 double-lined frame is painted if the window is active, and a single-
 lined frame is painted if the window is inactive. If a title exists,
 it is written over the frame.

********************************************************************/

void Win::paintFrame() const
{
   int i;
   char upLeft,
	    upRight,
	    botLeft,
	    botRight,
	    vert,
	    horiz;
   unsigned char attr = WHITE_FORE | BLACK_BACK;

   if( active )
   {
      upLeft   = (char)201;
      botLeft  = (char)200;
      upRight  = (char)187;
      botRight = (char)188;
      vert     = (char)186;
      horiz    = (char)205;
   }
   else
   {
      upLeft   = (char)218;
      botLeft  = (char)192;
      upRight  = (char)191;
      botRight = (char)217;
      vert     = (char)179;
      horiz    = (char)196;
   }

   paintChar( Point( 0, 0 ), upLeft, attr );
   paintChar( Point( 0, height() - 1 ), botLeft, attr );
   paintChar( Point( width() - 1, 0 ), upRight, attr );
   paintChar( Point( width() - 1, height() - 1 ), botRight, attr );

   for( i = 1; i < height() - 1; i++ )
   {
      paintChar( Point( 0, i ), vert, attr );
      paintChar( Point( width() - 1, i ), vert, attr );
   }

   for( i = 1; i < width() - 1; i++ )
   {
      paintChar( Point( i, 0 ), horiz, attr );
      paintChar( Point( i, height() - 1 ), horiz, attr );
   }


   if( *title )
   {
      i = 0;
      while( (i < width() - 2) &&
             (title[i] != '\0')  )
      {
	 paintChar( Point(2 + i, 0), title[i], attr);
	 i++;
      }
   }
}

/********************************************************************

 ScrollBar::ScrollBar

 This function constructs a scroll bar, given a parent window, the
 location of the scroll bar on the window, the length of the scroll
 bar, and its orientation (horizontal or vertical).

********************************************************************/

ScrollBar::ScrollBar( Win *parent, Point location, int len, int orient )
: Control( parent )
{
   if( orient == VERT )
   {
      area = Rect( location.x,
		           location.y,
		           location.x,
		           location.y + len - 1 );
   }
   else  // orient == HORIZ
   {
      area = Rect( location.x,
		           location.y,
		           location.x + len - 1,
	               location.y );
   }

   length = len;
   sliderPos = 1;
   orientation = orient;
   active = 1;
}


/********************************************************************

 ScrollBar::resize

 This function resizes a scroll bar. Depending on the orientation
 of the scroll bar, one of the parameters is ignored, since scroll
 bars are restricted to being one character in thickness.

********************************************************************/

void ScrollBar::resize( int newWidth, int newLength )
{
   if( orientation == VERT )
   {
      length = newLength;
      Interactor::resize( 1, newLength );
   }
   else  // orientation == HORIZ
   {
      length = newWidth;
      Interactor::resize( newWidth, 1 );
   }

}


/********************************************************************

 ScrollBar::handleEvent

 This function handles mouse events; scroll bars do not respond to
 any other kind of events. The function creates ScrollEvent objects
 and sends them to the parent window.

********************************************************************/

void ScrollBar::handleEvent( const Event &action )
{
   switch ( action.getType() )
   {
   case MOUSE_EVENT:

      int eventpos;

      if( orientation == VERT )
	     eventpos = ( (MouseEvent &) action).getPosition().y;

      else  // orientation == HORIZ
	     eventpos = ( (MouseEvent &) action).getPosition().x;

      if( eventpos == 0 )
	     parentWin->handleEvent( ScrollEvent( BACKWARD, LINE, this ) );

      else if( eventpos == length - 1 )
	     parentWin->handleEvent( ScrollEvent( FORWARD, LINE, this ) );

      else if( eventpos < sliderPos )
	     parentWin->handleEvent( ScrollEvent( BACKWARD, PAGE, this ) );

      else if( eventpos > sliderPos )
	     parentWin->handleEvent( ScrollEvent( FORWARD, PAGE, this ) );

      break;

   default:
      break;
   }
}


/********************************************************************

 ScrollBar::paint

 This function paints the scrollbar. First the painting region is
 set to the rectangle specified for updating (paintingRegion is used
 by paintChar). The body of the scroll bar is painted, and if the
 scroll bar is active, the arrows and slider are painted.

********************************************************************/

void ScrollBar::paint( Rect region )
{
   int i;
   unsigned char at = BLUE_FORE | GREEN_BACK;


    paintingRegion = region;

    // whether active or inactive, paint body of scroll bar

    if( orientation == VERT )
        for( i = 0; i <= length - 1; i++ )
            paintChar( Point( 0, i ), (char)178, at);

    else
        for( i = 0; i <= length - 1; i++ )
            paintChar( Point( i, 0 ), (char)178, at);

    if( active )   // now paint slider and end arrows
    {
        if( orientation == VERT )
        {
            paintChar( Point( 0, 0 ), (char)30, at );
            paintChar( Point( 0, length - 1 ), (char)31, at );
            paintChar( Point( 0, sliderPos ), (char)254, at );
        }
        else   // orientation == HORIZ
        {
            paintChar( Point( 0, 0 ), (char)17, at );
            paintChar( Point( length - 1, 0 ), (char)16, at );
            paintChar( Point( sliderPos, 0 ), (char)254, at );
        }
    }
}


/********************************************************************

 ScrollBar::setSlider

 This function sets the slider position. The specified position
 must be a number between 1 and 100, inclusive.

********************************************************************/

int ScrollBar::setSlider( int pos )
{
   int slideSpan;

   pos = max( pos, 1 );
   pos = min( pos, 100 );

   slideSpan = length - 2;

   sliderPos = 1 + ((pos * (slideSpan - 1)) / 100) ;
   return 1;
}


/********************************************************************

 PushButton::PushButton

 This function constructs a push button, given a parent window,
 the location of the button on the window, and a label for the
 button.

********************************************************************/

PushButton::PushButton( Win *parent, Point location, char *labl )
: Control( parent )
{
   area = Rect( location.x, location.y,
	            location.x + strlen( labl ) - 1, location.y );
   pressed = FALSE;
   strcpy( label, labl );
   active = 1;
}


/********************************************************************

 PushButton::handleEvent

 This function handles mouse events; push buttons do not respond to
 any other kind of event. The button is painted with colors inverted,
 a delay loop is executed, and then the button is painted again with
 normal colors.

********************************************************************/

void PushButton::handleEvent( const Event &action )
{
   switch ( action.getType() )
   {
   case MOUSE_EVENT:

      pressed = TRUE;
      paint( Rect( 0, 0, width(), height() ) );

//      delay(100);

      pressed = FALSE;
      paint( Rect( 0, 0, width(), height() ) );
      parentWin->handleEvent( PushEvent( this ) );
      break;

   default:
      break;
   }
}

/********************************************************************

 PushButton::paint

 This function paints a button. If a button is pressed, it is painted
 with inverted colors.

********************************************************************/

void PushButton::paint( Rect region )
{
   unsigned int i = 0;
   unsigned char attr;

   paintingRegion = region;

   if( active )
   {
       if( pressed )
           attr = WHITE_FORE | BLACK_BACK;
       else
           attr = BLACK_FORE | WHITE_BACK;
   }
   else // inactive
       attr = GRAY_FORE | WHITE_BACK;

   for( i = 0; i < strlen( label ); i++ )
       paintChar( Point(i,0), label[i], attr );
}


