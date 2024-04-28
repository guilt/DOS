// NEWDEL.CPP

// This is an example program from Chapter 6 of the C++ Tutorial. This
//    program demonstrates customized new and delete operators.

#include <iostream.h>
#include <malloc.h>

// ------------- Overloaded new operator
void *operator new( size_t size )
{
    void *rtn = calloc( 1, size );
    return rtn;
}

// ----------- Overloaded delete operator
void operator delete( void *ptr )
{
    free( ptr );
}

void main()
{
    // Allocate a zero-filled array
    int *ip = new int[10];
    // Display the array
    for( int i = 0; i < 10; i++ )
        cout << " " << ip[i];
    // Release the memory
    delete [] ip;
}
