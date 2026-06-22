// DEFARG.CPP

// This is an example program from Chapter 2 of the C++ Tutorial. This
//     program demonstrates default arguments in a function prototype.

#include <iostream.h>

void show( int = 1, float = 2.3, long = 4 );

void main()
{
   show();                // All three arguments default
   show( 5 );             // Provide 1st argument
   show( 6, 7.8 );        // Provide 1st and 2nd
   show( 9, 10.11, 12L ); // Provide all three arguments
}

void show( int first, float second, long third )
{
   cout << "\nfirst = "  << first;
   cout << ", second = " << second;
   cout << ", third = "  << third;
}
