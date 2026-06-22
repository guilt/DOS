// OVERLOAD.CPP

// This is an example program from Chapter 2 of the C++ Tutorial. This
//     program demonstrates overloaded functions.

#include <iostream.h>
#include <time.h>

void display_time( const struct tm *tim )
{
   cout << "1. It is now " << asctime( tim );
}

void display_time( const time_t *tim )
{
   cout << "2. It is now " << ctime( tim );
}

void main()
{
   time_t tim = time( NULL );
   struct tm *ltim = localtime( &tim );

   display_time( ltim );
   display_time( &tim );
}
