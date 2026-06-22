// NEWDEL4.CPP

// This is an example program from Chapter 6 of the C++ Tutorial. This
//     program demonstrates class-specific new and delete operators
//     with constructor and destructor messages to indicate when they
//     are called.

#include <malloc.h>
#include <iostream.h>

class Name
{
public:
    Name()  { cout << "Name's constructor running\n"; }
    void *operator new( size_t size );
    void operator delete( void *ptr );
    ~Name() { cout << "Name's destructor running\n"; }
private:
    char name[25];
};

// -------- Simple memory pool to handle one Name
char pool[sizeof( Name )];

// -------- Overloaded new operator for the Name class
void *Name::operator new( size_t size )
{
    cout << "Name's new running\n";
    return pool; 
}

// --------- Overloaded delete operator for the Name class
void Name::operator delete( void *p )
{
    cout << "Name's delete running\n";
}

void main()
{
    cout << "Executing: nm = new Name\n";
    Name *nm = new Name;
    cout << "Executing: delete nm\n";
    delete nm;
}
