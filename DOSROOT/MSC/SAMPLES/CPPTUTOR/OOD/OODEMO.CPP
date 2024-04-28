#include <stdio.h>
#include <stdlib.h>
#include <new.h>
#include "winmgr.h"
#include "textwin.h"
#include "lifewin.h"

int my_handler( size_t size )
{
    printf( "new failed on request for %d\n", size );
    exit( -1 );
    return 0;
}

void main()
{
   Buffer buf1( 30, 40, RED_FORE | BLUE_BACK );
   Buffer buf2( 10, 40, GREEN_FORE | BLACK_BACK );
   Buffer buf3( 40, 15, BLACK_FORE | WHITE_BACK );
   Buffer buf4( 50, 50, WHITE_FORE | BLACK_BACK );

   WinMgr winGrp;

   Event *evt;

   TextWin win1( Point( 30, 10 ), 17, 12, &buf1 );
   TextWin win2( Point( 20, 5 ), 12, 12, &buf2 );
   EditWin win3( Point( 40, 7 ), 12, 17, &buf3 );
   LifeWin win4( Point( 45, 8 ), 22, 12, &buf4 );

   EventGenerator evtSource;

   buf1.putStr( Point( 0, 0 ),
               "Whan that April with his shoures soot "
               "/ the droght of March hath perced to the roote "
               "/ and bathed every veyne in switch licour "
               "/ of which vertu engendred is the flour "
               "/ What Zephyrus eke with his sweete breeth "
               "/ inspired hath in every holt and heeth "
               "/ the tender croppes and the younge sonne "
               "/ hath in the Ram his half course-y ronne ");

   buf2.putStr( Point( 0, 0 ),
                "Once upon a time, there was a little girl "
                "who lived in a cottage on the edge of a "
                "forest with her mother. She always wore a "
                "red hood when she went outside, so she was "
                "named Little Red Riding Hood. ");

   buf3.putStr( Point( 0, 0 ),
                "To be or not to be: that is the question "
                " whether tis nobler in the mind to suffer "
                "the slings and arrows of outrageous fortune "
                "or to take up arms against a sea of troubles "
                "and by opposing, end them. ");

   _set_new_handler( my_handler );

   win1.setTitle( "TextWin1" );
   winGrp.addWindow( &win1 );

   win2.setTitle( "TextWin2" );
   winGrp.addWindow( &win2 );

   win3.setTitle( "EditWin" );
   winGrp.addWindow( &win3 );

   win4.setTitle( "LifeWin" );
   winGrp.addWindow( &win4 );

   winGrp.repaint( Rect( 1, 1, 80, 25 ) );

   for(;;)
   {
      if( evt = evtSource.getNextEvent() )
      {
          winGrp.handleEvent( *evt );
          delete evt;
      }
   }
}
