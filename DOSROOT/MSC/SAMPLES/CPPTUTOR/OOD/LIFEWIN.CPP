/********************************************************************

 FILE: LIFEWIN.CPP

********************************************************************/

#include "lifewin.h"

#include <stdlib.h>
#include <string.h>

/********************************************************************

 LifeWin::LifeWin

 This function creates a Life window. It moves the horizontal
 scrollbar, if one exists, and allocates three PushButtons. It
 also allocates two buffers used to represent the Life field.

********************************************************************/

LifeWin::LifeWin( Point location, int wid, int len, Buffer *sheet )
: TextWin ( location, wid, len, sheet )
{
    wid = min( wid, canvas.columns() + 2 );  // make sure window isn't
    len = min( len, canvas.rows() + 2 );     //   larger than text buffer, or
    wid = max( wid, LIFEWIN_MINWIDTH );      //   smaller than minimum
    len = max( len, LIFEWIN_MINHEIGHT );

    textView = Rect(10, 1, wid - 2, len - 2);

    if( hscroller )
    {
        hscroller->move( Point(10, textView.bottom + 1) );
        hscroller->resize( textView.width() + 1, 1 );
    }

    buttons[0] = new PushButton( this, Point( 2, height() / 4 )," Clear ");
    buttons[1] = new PushButton( this, Point( 2, height() / 2 )," Random");
    buttons[2] = new PushButton( this, Point( 2, 3 * height() / 4 )," Next  ");

    int size = canvas.rows() * canvas.columns();

    currField = new char[size];
    neighborField = new char[size];

    clearField();
    randomize();
}

/********************************************************************

 LifeWin::LifeWin - copy constructor

********************************************************************/

LifeWin::LifeWin( const LifeWin &other )
: TextWin( (TextWin &)other )
{
    int i, size;

    for( i = 0; i < 3; i++ )
        buttons[i] = new PushButton( *other.buttons[i] );

    size = canvas.rows() * canvas.columns();
    currField = new char[size];
    strncpy( currField, other.currField, size );
    neighborField = new char[size];
    strncpy( neighborField, other.neighborField, size );
}

/********************************************************************

 LifeWin::operator=

********************************************************************/

LifeWin &LifeWin::operator=( const LifeWin &other )
{
    int i, size;

    if( &other == this )
        return *this;

    for( i = 0; i < 3; i++ )
    {
        delete buttons[i];
        buttons[i] = new PushButton( *other.buttons[i] );
    }

    delete currField;
    delete neighborField;

    size = canvas.rows() * canvas.columns();
    currField = new char[size];
    strncpy( currField, other.currField, size );
    neighborField = new char[size];
    strncpy( neighborField, other.neighborField, size );

    return *this;
}

/********************************************************************

 LifeWin::resize

 This function resizes the window to the specified dimensions.

********************************************************************/

void LifeWin::resize( int newWidth, int newHeight )
{
    if( (newWidth == width())  &&
        (newHeight == height())  )
        return;

    newWidth = min( newWidth, canvas.columns() + 11 );  // make sure window isn't
    newHeight = min( newHeight, canvas.rows() + 2 );   //   larger than text buffer, or
    newWidth = max( newWidth, LIFEWIN_MINWIDTH);       //   smaller than minimum
    newHeight = max( newHeight, LIFEWIN_MINHEIGHT);

    TextWin::resize( newWidth - 10, newHeight );

    Interactor::resize( newWidth, newHeight );

    textView = Rect(10, 1, newWidth - 2, newHeight - 2);

    if( hscroller )
    {
        hscroller->move( Point(10, textView.bottom + 1) );
        hscroller->resize( textView.width() + 1, 1 );
    }

    if( vscroller )
        vscroller->move( Point( textView.right + 1, textView.top ) );

    buttons[0]->move( Point( 2, height() / 4 ) );
    buttons[1]->move( Point( 2, height() / 2 ) );
    buttons[2]->move( Point( 2, 3 * height()/ 4 ) );

}

/********************************************************************

 LifeWin::activate

 This function activates the buttons and calls TextWin::activate.

********************************************************************/

void LifeWin::activate()
{
    TextWin::activate();

    buttons[0]->activate();
    buttons[1]->activate();
    buttons[2]->activate();
}

/********************************************************************

 LifeWin::deactivate

 This function deactivates the buttons and calls TextWin::deactivate.

********************************************************************/

void LifeWin::deactivate()
{
    TextWin::deactivate();

    buttons[0]->deactivate();
    buttons[1]->deactivate();
    buttons[2]->deactivate();
}

/********************************************************************

 LifeWin::paint

 This function repaints the window, including the life field,
 scrollbars, and buttons. The painting region is set to the
 invalid rectangle for the window's own painting. The invalid
 rectangle is passed on the scrollbars' and buttons' paint
 functions, displaced to fit their coordinate systems. Finally
 the painting region is reset to the entire active window, for
 the next time the window becomes active.

********************************************************************/

void LifeWin::paint( Rect invalid )
{
    int i, j;

    paintingRegion = invalid;

    paintFrame();

    if( vscroller )
        vscroller->paint( invalid - vscroller->origin() );
    if( hscroller )
        hscroller->paint( invalid - hscroller->origin() );

    for( i = 1; i <= 9; i++ )
        for( j = 1; j <= height() - 2; j++ )
            paintChar( Point(i,j), ' ', GREEN_FORE | GREEN_BACK );

    for( i = 0; i < 3; i++ )
        buttons[i]->paint( invalid - buttons[i]->origin() );

    paintText();

    paintingRegion = Rect( 0, 0, width(), height() );
}

/********************************************************************

 LifeWin::clearField

  This function initializes the Life matrixes. It clears currField
  and neighborField, then initialize all the zones (1-9) of currField.

  The zones indicate edges and corners, and are used by the Life
  algorithm to determine the method of calculating neighbors. This
  causes the Life field to wrap around in all directions.

     +-+--------------+-+
     |6|      2       |7|
     +-+--------------+-+
     | |              | |
     |4|      1       |5|
     | |              | |
     +-+--------------+-+
     |8|      3       |9|
     +-+--------------+-+

  Zones are recorded in matrix 1 for ease of computation.

********************************************************************/

void LifeWin::clearField()
{
    int x, y, size;

    size = canvas.rows() * canvas.columns();

    memset( currField, 0, size );
    memset( neighborField, 0, size );


    char *p = currField;

    *p++ = 6;
    for( x = 0; x < (canvas.columns() - 2); x++ )
        *p++ = 2;
    *p++ = 7;

    /* Initialize center rows to zones 4, 1, and 5. */
    for( y = 0; y < (canvas.rows() - 2); y++ )
    {
        *p++ = 4;
        for( x = 0; x < (canvas.columns() - 2); x++ )
            *p++ = 1;
        *p++ = 5;
    }

    /* Initialize bottom row to zones 8, 3, and 9. */
    *p++ = 8;
    for( x = 0; x < (canvas.columns() - 2); x++ )
        *p++ = 3;
    *p++ = 9;

    for( x = 0; x < canvas.rows(); x++ )
        for( y = 0; y < canvas.columns(); y++ )
            canvas.setChar( Point(x,y), ' ');

}

/********************************************************************

 LifeWin::randomize

 This function randomly places live cells in currField.

********************************************************************/

void LifeWin::randomize()
{
    int i, x, y, size;

    clearField();

    size = canvas.columns() * canvas.rows();

    for( i = 0; i < (size / 10) ; i++ )
    {
        x = rand() % canvas.columns();
        y = rand() % canvas.rows();
        canvas.setChar( Point( x, y ), CELL_CHAR );
        currField[(y * canvas.columns()) + x] += 100;
    }

}

/********************************************************************

 LifeWin::handleEvent

 This function determines the type of event, and passes it on to
 the appropriate event handler.

********************************************************************/

void LifeWin::handleEvent( const Event &action )
{
    switch ( action.getType() )
    {
    case KBD_EVENT:
    {
        KbdEvent &key = (KbdEvent &)action;
        handleKey( key );
        break;
    }
    case MOUSE_EVENT:
    {
        MouseEvent &mouseAction = (MouseEvent &)action;
        handleMouse( mouseAction );
        break;
    }
    case PUSH_EVENT:
    {
        PushEvent &pushAction = (PushEvent &)action;
        handlePush( pushAction );
        break;
    }
    default:
        TextWin::handleEvent( action );
        break;
    }
}

/********************************************************************

 LifeWin::handleKey

 This function handles keyboard events. It handles the space bar
 (for turning a cell on or off) and the letters C, R and N (for
 "Clear," "Randomize," and "Next," respectively.)

********************************************************************/

void LifeWin::handleKey( const KbdEvent &key )
{
    if( key.val() == ' ' )
    {
        if( (canvas.getChar( getCursorPos() )).character == CELL_CHAR )
        {
            currField[(getCursorPos().y * canvas.columns()) + getCursorPos().x] -= 100;
            canvas.setChar( getCursorPos(), ' ');
        }
        else
        {
            currField[(getCursorPos().y * canvas.columns()) + getCursorPos().x] += 100;
            canvas.setChar( getCursorPos(), CELL_CHAR );
        }
        paintText();
    }
    else if( ( key.val() == 'C' ) || ( key.val() == 'c') )
    {
        clearField();
        paint( Rect( 0, 0, width(), height() ) );
    }
    else if( ( key.val() == 'R' ) || ( key.val() == 'r') )
    {
        clearField();
        randomize();
        paint( Rect( 0, 0, width(), height() ) );
    }
    else if( ( key.val() == 'N' ) || ( key.val() == 'n') )
    {
        nextGeneration();
        paint( Rect( 0, 0, width(), height() ) );
    }

    else
        TextWin::handleEvent( key );
}


/********************************************************************

 LifeWin::handleMouse

 This function handles mouse events. Mouse events that fall on
 one of the buttons are passed to that object. The location of
 the mouse event is translated to the scrollbar's coordinate system
 when it is passed. Mouse events that fall on the Life field cause
 a cell to turn on or off.

********************************************************************/

void LifeWin::handleMouse( const MouseEvent &action )
{
    int i;

    for( i = 0; i < 3; i++ )
    {
        if( buttons[i]->withinBounds( action.getPosition() ) )
        {
            MouseEvent localAction( action.getPosition() - buttons[i]->origin(),
                                    action.getButton() );
            buttons[i]->handleEvent( localAction );
            updateCursor();
        }
    }

    if( textView.Contains( action.getPosition() ) )
    {
        setCursorPos( action.getPosition() -
                      Point(textView.left, textView.top) +
                      getCanvasOffset() );
        updateCursor();

        if( ( canvas.getChar( getCursorPos() ) ).character == CELL_CHAR )
        {
            currField[(getCursorPos().y * canvas.columns()) + getCursorPos().x] -= 100;
            canvas.setChar( getCursorPos(), ' ');
        }
        else
        {
            currField[(getCursorPos().y * canvas.columns()) + getCursorPos().x] += 100;
            canvas.setChar( getCursorPos(), CELL_CHAR );
        }
        paintText();
    }
    else
        TextWin::handleEvent( action );
}

/********************************************************************

 LifeWin::handlePush

 This function handles button push events. The source of the push
 event is checked against the window's buttons, and the Life field
 is cleared, randomized, or recalculated accordingly.

********************************************************************/

void LifeWin::handlePush( const PushEvent &action )
{
    PushButton *source = action.getSource();

    if( source == buttons[0] )  // clear
    {
        clearField();
        paint( Rect( 0, 0, width(), height() ) );
    }
    else if( source == buttons[1] ) // new random
    {
        clearField();
        randomize();
        paint( Rect( 0, 0, width(), height() ) );
    }
    else  // source == buttons[2]
    {
        nextGeneration();
        paint( Rect( 0, 0, width(), height() ) );
    }
}

/********************************************************************

 LifeWin::nextGeneration

 This function calculates the next generation of cells. First
 neighborField is cleared, and then currField is scanned. Whenever
 a living cell is found in currField, the corresponding neighbor
 cells in neighborField are incremented by 1, and the corresponding
 cell itself is incremented by 100. At the end of this stage,
 neighborField contains a count of each cell's neighbors.

 The zone number stored in each cell of currField is used to
 determine which cells are treated as neighbors. The zones at the
 edges and corners have neighbors on the other side of the field,
 causing the field to wrap around in all direction.

 The function updateField() is called to determine what actually
 lives or dies, based on the neighbor-count of each cell.

********************************************************************/

#define NW  (-1-canvas.columns())        // Directional constants, within
#define N   (-canvas.columns())          //  matrix 2. For example, NW refers
#define NE  (1-canvas.columns())         //  to the upper, left-hand neighbor
#define E   (1)
#define SE  (1+canvas.columns())
#define S   (canvas.columns())
#define SW  (-1+canvas.columns())
#define W   (-1)

void LifeWin::nextGeneration()
{
    int x, y;

    int size,
        zone;

    char *p1,
         *p2;

    size = canvas.rows() * canvas.columns();

    memset(neighborField, 0, size);

    // For each cell . . .

    p1 = (char *) currField;

    for( y = 0; y < canvas.rows(); y++ )
    {
        for( x = 0; x < canvas.columns(); x++, p1++ )
        {
            // If matrix 1 cell is alive . . .

            if( *p1 > 100 )
            {
                // Point to matrix 2 cell and update it.
                p2 = (char *)neighborField + (y * canvas.columns()) + x;
                *p2 += 100;
    
                // Get the zone and update the neighbors accordingly.
                zone = (*p1 - 100);
                switch( zone )
                {
                case 1:
                    ++*(p2 + NW);
                    ++*(p2 + N);
                    ++*(p2 + NE);
                    ++*(p2 + E);
                    ++*(p2 + SE);
                    ++*(p2 + S);
                    ++*(p2 + SW);
                    ++*(p2 + W);
                    break;
                case 2:
                    ++*(p2 + NW + size);
                    ++*(p2 + N + size);
                    ++*(p2 + NE + size);
                    ++*(p2 + E);
                    ++*(p2 + SE);
                    ++*(p2 + S);
                    ++*(p2 + SW);
                    ++*(p2 + W);
                    break;
                case 3:
                    ++*(p2 + NW);
                    ++*(p2 + N);
                    ++*(p2 + NE);
                    ++*(p2 + E);
                    ++*(p2 + SE - size);
                    ++*(p2 + S - size);
                    ++*(p2 + SW - size);
                    ++*(p2 + W);
                    break;
                case 4:
                    ++*(p2 + NW + canvas.columns());
                    ++*(p2 + N);
                    ++*(p2 + NE);
                    ++*(p2 + E);
                    ++*(p2 + SE);
                    ++*(p2 + S);
                    ++*(p2 + SW + canvas.columns());
                    ++*(p2 + W + canvas.columns() );
                    break;
                case 5:
                    ++*(p2 + NW);
                    ++*(p2 + N);
                    ++*(p2 + NE - canvas.columns());
                    ++*(p2 + E - canvas.columns());
                    ++*(p2 + SE - canvas.columns());
                    ++*(p2 + S);
                    ++*(p2 + SW);
                    ++*(p2 + W);
                    break;
                case 6:
                    ++*(p2 + NW + size + canvas.columns());
                    ++*(p2 + N + size);
                    ++*(p2 + NE + size);
                    ++*(p2 + E);
                    ++*(p2 + SE);
                    ++*(p2 + S);
                    ++*(p2 + SW + canvas.columns());
                    ++*(p2 + W + canvas.columns());
                    break;
                case 7:
                    ++*(p2 + NW + size);
                    ++*(p2 + N + size);
                    ++*(p2 + NE + size - canvas.columns());
                    ++*(p2 + E - canvas.columns());
                    ++*(p2 + SE - canvas.columns());
                    ++*(p2 + S);
                    ++*(p2 + SW);
                    ++*(p2 + W);
                    break;
                case 8:
                    ++*(p2 + NW + canvas.columns());
                    ++*(p2 + N);
                    ++*(p2 + NE);
                    ++*(p2 + E);
                    ++*(p2 + SE - size);
                    ++*(p2 + S - size);
                    ++*(p2 + SW + canvas.columns() - size);
                    ++*(p2 + W + canvas.columns());
                    break;
                case 9:
                    ++*(p2 + NW);
                    ++*(p2 + N);
                    ++*(p2 + NE - canvas.columns());
                    ++*(p2 + E - canvas.columns());
                    ++*(p2 + SE - size - canvas.columns());
                    ++*(p2 + S - size);
                    ++*(p2 + SW - size);
                    ++*(p2 + W);
                    break;
                default:
                    break;
                }
            } // End if
        } // End for: rows
    } // End for: columns

    updateField();
}

/********************************************************************

 LifeWin::updateField

 This function scans neighborField and updates currField according
 to the following rules:

  neighborField value      currField result
  -------------------      ----------------
          3                new cell is born (right conditions for birth)
          102, 103         no change (right number of neighbors)
          other > 100      cell dies (overcrowding or isolation)
          other < 100      no change (wrong conditions for birth)

********************************************************************/

void LifeWin::updateField()
{
   int x, y;
   char *p2 = neighborField;

    // Outer loop counts rows.

    for( y = 0; y < canvas.rows(); y++ )
    {
        // Next loop counts columns.
        for( x = 0; x < canvas.columns(); x++, p2++ )
        {
            if( *p2 < 100 )
            {
                if( *p2 == 3 )   // Write live cell if 3.
                {
                    currField[ (y * canvas.columns()) + x] += 100;
                    canvas.setChar( Point(x,y), CELL_CHAR );
                }
            }
            else   // Dead cell if above 100, but not 102 or 103.
            {
                if( (*p2 < 102) || (*p2 > 103) )
                {
                    currField[ (y * canvas.columns()) + x] -= 100;
                    canvas.setChar( Point(x,y), ' ');
                }
            }
        } // End for: columns
    } // End for: rows

}



/********************************************************************

 LifeWin::~LifeWin

 This function deallocates the buttons and the buffers used for the
 Life field.

********************************************************************/

LifeWin::~LifeWin()
{
    int i;

    for( i = 0; i < 3; i++ )
        delete buttons[i];
    delete currField;
    delete neighborField;
}
