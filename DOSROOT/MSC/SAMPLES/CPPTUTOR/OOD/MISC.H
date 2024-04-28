#if !defined( _MISC_H_ )

#define _MISC_H_

#include "prim.h"

/********************************************************************

 Macro: ExtChar
    Encodes ASCII and extended code characters in an integer.
    Note that the ASCII character is stored in the low-order byte;
    this allows encoded ints to be compared with chars.

********************************************************************/

#define ExtChar( a, b ) ((unsigned int)b << 8) | (unsigned char)a

const unsigned int BACKSPACE  = ExtChar( 8, 0 );
const unsigned int TAB        = ExtChar( 9, 0 );
const unsigned int ESC        = ExtChar( 27, 0 );
const unsigned int UPARROW    = ExtChar( 0, 72 );
const unsigned int DOWNARROW  = ExtChar( 0, 80 );
const unsigned int LEFTARROW  = ExtChar( 0, 75 );
const unsigned int RIGHTARROW = ExtChar( 0, 77 );
const unsigned int PGUP       = ExtChar( 0, 73 );
const unsigned int PGDN       = ExtChar( 0, 81 );
const unsigned int HOME       = ExtChar( 0, 71 );
const unsigned int END        = ExtChar( 0, 79 );

// constants for foreground and background colors

const unsigned char BLACK_FORE = 0;
const unsigned char BLUE_FORE  = 0x01;
const unsigned char GREEN_FORE = 0x02;
const unsigned char RED_FORE   = 0x04;
const unsigned char INTENSE    = 0x08;
const unsigned char BLACK_BACK = 0;
const unsigned char BLUE_BACK  = 0x10;
const unsigned char GREEN_BACK = 0x20;
const unsigned char RED_BACK   = 0x40;
const unsigned char BLINKING   = 0x80;


const unsigned char CYAN_FORE    = GREEN_FORE | BLUE_FORE;
const unsigned char MAGENTA_FORE = RED_FORE | BLUE_FORE;
const unsigned char BROWN_FORE   = RED_FORE | GREEN_FORE;
const unsigned char WHITE_FORE   = RED_FORE | GREEN_FORE | BLUE_FORE;
const unsigned char GRAY_FORE          = INTENSE | BLACK_FORE;
const unsigned char LIGHT_BLUE_FORE    = INTENSE | BLUE_FORE;
const unsigned char LIGHT_GREEN_FORE   = INTENSE | GREEN_FORE;
const unsigned char LIGHT_RED_FORE     = INTENSE | RED_FORE;
const unsigned char LIGHT_CYAN_FORE    = INTENSE | CYAN_FORE;
const unsigned char LIGHT_MAGENTA_FORE = INTENSE | MAGENTA_FORE;
const unsigned char YELLOW_FORE        = INTENSE | BROWN_FORE;
const unsigned char BRIGHT_WHITE_FORE  = INTENSE | WHITE_FORE;

const unsigned char CYAN_BACK    = GREEN_BACK | BLUE_BACK;
const unsigned char MAGENTA_BACK = RED_BACK | BLUE_BACK;
const unsigned char BROWN_BACK   = RED_BACK | GREEN_BACK;
const unsigned char WHITE_BACK   = RED_BACK | GREEN_BACK | BLUE_BACK;
const unsigned char GRAY_BACK          = INTENSE | BLACK_BACK;
const unsigned char LIGHT_BLUE_BACK    = INTENSE | BLUE_BACK;
const unsigned char LIGHT_GREEN_BACK   = INTENSE | GREEN_BACK;
const unsigned char LIGHT_RED_BACK     = INTENSE | RED_BACK;
const unsigned char LIGHT_CYAN_BACK    = INTENSE | CYAN_BACK;
const unsigned char LIGHT_MAGENTA_BACK = INTENSE | MAGENTA_BACK;
const unsigned char YELLOW_BACK        = INTENSE | BROWN_BACK;
const unsigned char BRIGHT_WHITE_BACK  = INTENSE | WHITE_BACK;


/********************************************************************

 Screen

 Provides minimal set of operations for using the screen in text
 mode.

 Public Interface:

 showChar - displays character at the specified position.
 setCurPos - moves the screen cursor to the specfied location.
 cursorOn - displays screen cursor.
 cursorOff - hides screen cursor.

********************************************************************/

class Screen
{
public:
    void showChar( Point loc, char chr, unsigned char attr);
    void setCurPos( Point loc );
    void cursorOn();
    void cursorOff();
    ~Screen();
private:
    int cursorShape;
};


inline Screen::~Screen()
{
    cursorOn();
}

extern Screen theScreen;   // global Screen object

/********************************************************************

 Mouse

 Provides minimal set of operations for using a mouse in text
 mode.

 Public Interface:

     Mouse - constructor that sets internal existence flag.

     reset - resets mouse. Returns 1 if mouse exists, 0 if not.

     show - displays mouse cursor. Returns 1 if mouse exists,
         0 if not.

     hide - hides mouse cursor. Returns 1 if mouse exists,
         0 if not.

     read - gets current position of mouse cursor and current
         status of mouse buttons. Returns 1 if mouse exists,
         0 if not.

     move - moves mouse cursor to specified position. Returns 1
         if mouse exists, 0 if not.

********************************************************************/

struct MouseStatus
{
    Point position;
    int button;
};

class Mouse
{
public:
    Mouse();
    int reset();
    int show();
    int hide();
    int read( MouseStatus *status );
    int move( Point location );
   ~Mouse();
private:
    int exists;
};

inline Mouse::~Mouse()
{
    hide();
}

extern Mouse theMouse; // global Mouse object


#endif // _MISC_H_
