// DATE.CPP

#include "date.h"
#include <iostream.h>

Date::Date()
{
    month = day = year = 1;   // Initialize data members
}

Date::Date( int mn, int dy, int yr )
{
   setMonth( mn );
   setDay( dy );
   setYear( yr );
}

void Date::setMonth( int mn )
{
    month = max( 1, mn );
    month = min( month, 12 );
}

void Date::setDay( int dy )
{
    static int length[] = { 0, 31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31 };
    day = max( 1, dy );
    day = min( day, length[month] );
}

void Date::setYear( int yr )
{
    year = max( 1, yr );
}

// -------- Member function to printÿdate
void Date::display() const
{
    static char *name[] =
    {
        "zero", "January", "February", "March", "April", "May",
        "June", "July", "August", "September", "October",
        "November","December"
    };

    cout << name[month] << ' ' << day << ", " << year;
}

// ---------- The destructor
Date::~Date()
{
   // do nothing
}

