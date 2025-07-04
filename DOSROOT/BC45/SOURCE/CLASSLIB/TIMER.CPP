/*------------------------------------------------------------------------*/
/*                                                                        */
/*  TIMER.CPP                                                             */
/*                                                                        */
/*  Copyright (c) 1991, 1994 Borland International                        */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __DOS_H )
#include <dos.h>
#endif

#define BUILDBIDSTIMER

#if !defined( CLASSLIB_TIMER_H )
#include <classlib/timer.h>
#endif

const unsigned long far * const dosTime =
    (const unsigned long far * const)MK_FP( 0x40, 0x6C );

unsigned TTimer::Adjust = Calibrate();

TTimer::TTimer() : Time_(0), Running(0)
{
}

void TTimer::Start()
{
    if( !Running )
        {
        outportb( 0x43, 0x34 );
        asm jmp __1;
    __1:
        outportb( 0x40, 0 );
        asm jmp __2;
    __2:
        outportb( 0x40, 0 );
        StartTime.DosCount = *dosTime;
        StartTime.TimerCount = 0;
        Running = 1;
        }
}

void TTimer::Stop()
{
    outportb( 0x43, 0 );
    unsigned char temp = inportb( 0x40 );

    TIME stopTime;
    stopTime.TimerCount = (inportb( 0x40 ) << 8) + temp;
    stopTime.DosCount = *dosTime;

    TIME elapsedTime;
    elapsedTime.DosCount = stopTime.DosCount - StartTime.DosCount;
    elapsedTime.TimerCount = -( stopTime.TimerCount - Adjust );

    const double fudge = 83810.0/100000.0;
    Time_ += ((elapsedTime.DosCount << 16) + elapsedTime.TimerCount)*fudge;

    Running = 0;

}

void TTimer::Reset()
{
    Time_ = 0;
    if( Running )
        Start();
}

unsigned TTimer::Calibrate()
{
    Adjust = 0;
    unsigned long sum = 0;
    TTimer w;
    for( int i = 0; i < 100; i++ )
        {
        w.Start();
        w.Stop();
        sum += w.Time();
        w.Reset();
        }
    return (unsigned)((sum+5)/100);
}

#if defined( TEST_TIMER )
#include <iostream.h>
#include <stdio.h>

int main( void )
{
    delay( 0 );
    cout << "Resolution: " << Timer::Resolution() << endl;
    TTimer w;
    for( unsigned del = 0; del < 10; del++ )
        {
        unsigned d1 = del*100;
        w.Start();
        delay( d1 );
        w.Stop();
        printf( "%4u ms., actual time = %6f seconds.\n", d1, w.Time() );
        w.Reset();
        }
    return 0;
}
#endif


