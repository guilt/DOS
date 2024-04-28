/********************************************************************

 FILE: WINMGR.H

********************************************************************/


#if !defined( _WINMGR_H_ )

#define _WINMGR_H_

#include <stdlib.h>

#include "interact.h"
#include "list.h"

/********************************************************************

 WinMgr

 Defines a window manager that maintains one or more windows, keeps
 track of the active window, and directs events to the windows.

********************************************************************/

class WinMgr
{
public:
   void handleEvent( const Event &action );
   void addWindow( Win *newWindow );
   void deleteWindow();
   void repaint( Rect region );
private:
   void handleKey( const KbdEvent &key );
   void handleMouse( const MouseEvent &action );
   List winlist;
};

#endif // _WINMGR_H_
