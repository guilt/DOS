/********************************************************************

 FILE: LIFEWIN.H

 Defines LifeWin (derived from TextWin).

********************************************************************/

#if !defined( _LIFEWIN_H_ )

#define _LIFEWIN_H_

#include "textwin.h"

/********************************************************************

 LifeWin

 Defines windows that play the game of Life.

 The game of Life was invented in 1970 by mathematics professor John
 Horton Conway.

 The game of life is based on the following laws:

     1. Law of Survival - If a living cell has either two or or three
        neighbors, it survives.

     2. Law of Death - A living cell with more than three neighbors
        dies of overcrowding. A living cell with less than two
        neighbors dies of isolation.

     3. Law of Birth - A dead cell with exactly three neighbors is born
        in the next generation.

 These simple laws result in complex interactions. For example,
 try entering the following patterns:

       þþ       þ            þþ                  þ    þ
      þ þ         þ         þþ       þþþþþ     þþ þþþþ þþ
        þ      þþ  þþþ       þ       þ   þ       þ    þ

 A LifeWin contains three buttons: CLEAR, which clears the playing
 field; RANDOM, which places a random distribution of live cells on
 the playing field; and NEXT, which calculates the next generation.
 Cells can be added or deleted with the mouse, or by moving the
 cursor with the arrow keys and using the spacebar.

 Public Interface:

     LifeWin - constructor taking a position, the dimensions of the
         window, and a text buffer for displaying the Life field.

     LifeWin - copy constructor.

     operator= - assignment operator.

 (Redefined from TextWin)

     resize - redefined to reposition buttons, and handle scrollbars.

     activate - redefined to activate buttons.

     deactivate - redefined to deactivate buttons.

     paint - redefined to paint Life window.

     handleEvent - redefined to check for button presses and give
         new responses to keyboard and mouse events.

********************************************************************/

const int LIFEWIN_MINWIDTH = 14;
const int LIFEWIN_MINHEIGHT = 5;

const char CELL_CHAR = (char)254;

class LifeWin : public TextWin
{
public:
   LifeWin(Point location, int wid, int len, Buffer *sheet );
   LifeWin( const LifeWin &other );
   LifeWin &operator=( const LifeWin &other );
   void resize( int newWidth, int newLength );
   void activate();
   void deactivate();
   void paint( Rect region );
   void handleEvent( const Event &action );
  ~LifeWin();
private:
   void handleKey( const KbdEvent &key );
   void handleMouse( const MouseEvent &action );
   void handlePush( const PushEvent &action );
   void clearField();
   void randomize();
   void nextGeneration();
   void updateField();

   PushButton *buttons[3];
   char *currField;
   char *neighborField;
};

#endif // _LIFEWIN_H_
