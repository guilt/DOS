// INLINE.CPP

// This is an example program from Chapter 2 of the C++ Tutorial. This
//     program demonstrates the difference between a macro and an inline
//     function.

#include <iostream.h>

#define MAX( A, B ) ((A) > (B) ? (A) : (B))

inline int max( int a, int b )
{
    if ( a > b ) return a;
    return b;
}

void main()
{
   int i, x, y;

   x = 23; y = 45;
   i = MAX( x++, y++ );  // Side-effect:
                         //     larger value incremented twice
   cout << "x = " << x << " y = " << y << '\n';

   x = 23; y = 45;
   i = max( x++, y++ );  // Works as expected
   cout << "x = " << x << " y = " << y << '\n';
}
