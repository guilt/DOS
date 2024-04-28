/*********************************************************************

 FILE: EVENT.CPP

*********************************************************************/

#include "event.h"

#include <conio.h>
#include <dos.h>

/*********************************************************************

 EventGenerator::EventGenerator

*********************************************************************/

EventGenerator::EventGenerator()
{
    lastStatus.position = Point(10,10);
    lastStatus.button = 0;
}

/*********************************************************************

 EventGenerator::~EventGenerator

*********************************************************************/

EventGenerator::~EventGenerator()
{
}


/*********************************************************************

 EventGenerator::getMouseEvent

*********************************************************************/

MouseEvent *EventGenerator::getMouseEvent()
{
    MouseStatus status;

    if( !theMouse.read( &status ) )
        return 0;

    if( status.button == lastStatus.button )
    {
        return 0;
    }
    else
    {
        lastStatus = status;

        if( status.button != 0 )
        {
//          lastStatus.position.x = (lastStatus.position.x >> 3) + 1;
//          lastStatus.position.y = (lastStatus.position.y >> 3) + 1;
            return new MouseEvent( lastStatus.position,
                                   lastStatus.button );
        }
        else
	        return 0;
    }
}


/*********************************************************************

 EventGenerator::getNextEvent

*********************************************************************/

Event *EventGenerator::getNextEvent()
{
    Event *temp;

    char ch1,
         ch2;

    theMouse.show();

    if( kbhit() )
    {
        ch1 = getch();
        if( ch1 == 0)   // extended key pressed
        {
            ch2 = getch();
            return new KbdEvent(ch1, ch2);
        }
        else
            return new KbdEvent(ch1, 0);
    }
    else if( (temp = getMouseEvent()) != 0 )
    {
        return temp;
    }
    else
    {
        return 0;
    }
}
