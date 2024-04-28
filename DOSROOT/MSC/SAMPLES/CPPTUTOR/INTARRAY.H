// INTARRAY.H

// This is an example class from Chapter 8 of the C++ Tutorial. This
//     class demonstrates the overloaded subscript operator ([]).

#if !defined( _INTARRAY_H_ )

#define _INTARRAY_H_

class IntArray
{
public:
     IntArray( int len );
     int getLength() const;
     int &operator[]( int index );
     ~IntArray();
private:
     int length;
     int *aray;
};

#endif // _INTARRAY_H_

