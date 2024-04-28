// NEWDEL2.CPP

// This is an example program from Chapter 6 of the C++ Tutorial. This
//     program demonstrates customized new and delete operators with
//     character fill.

#include <iostream.h>
#include <malloc.h>
#include <string.h>

// ------------- Overloaded new operator
void *operator new( size_t size, int filler )
{
    void *rtn;
    if( (rtn = malloc( size )) != NULL )
        memset( rtn, filler, size );
    return rtn;
}

// ----------- Overloaded delete operator
void operator delete( void *ptr )
{
    free( ptr );
}

void main()
{
    // Allocate an asterisk-filled array
    char *cp = new( '*' ) char[10];
    // Display the array
    for( int i = 0; i < 10; i++ )
        cout << " " << cp[i];
    // Release the memory
    delete [] cp;
}
