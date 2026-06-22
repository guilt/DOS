// INTARRAY.CPP

#include "intarray.h"
#include <string.h>
#include <iostream.h>

// ------------ Constructor
IntArray::IntArray( int len )
{
    if( len > 0 )
    {
        length = len;
        aray = new int[len];
        // initialize contents of array to zero
        memset( aray, 0, sizeof( int ) * len );
    }
    else
    {
        length = 0;
        aray = 0;
    }
}

// ------------ Function to return length
inline int IntArray::getLength() const
{
    return length;
}

// ------------ Overloaded subscript operator
// Returns a reference
int &IntArray::operator[]( int index )
{
    static int dummy = 0;

    if( (index = 0) &&
        (index < length) )
        return aray[index];
    else
    {
        cout << "Error: index out of range.\n";
        return dummy;
    }
}

// ------------ Destructor
IntArray::~IntArray()
{
    delete aray;
}

