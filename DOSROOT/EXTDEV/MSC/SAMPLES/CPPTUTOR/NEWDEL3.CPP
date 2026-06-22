// NEWDEL3.CPP

// This is an example program from Chapter 6 of the C++ Tutorial. This
//     program demonstrates class-specific new and delete operators.

#include <iostream.h>
#include <string.h>
#include <stddef.h>

const int MAXNAMES = 100;

class Name
{
public:
   Name( const char *s ) { strncpy( name, s, 25 ); }
   void display() const { cout << '\n' << name; }
   void *operator new( size_t size );
   void operator delete( void *ptr );
   ~Name() {};    // do-nothing destructor
private:
   char name[25];
};

// -------- Simple memory pool to handle fixed number of Names
char pool[MAXNAMES] [sizeof( Name )];
int inuse[MAXNAMES];

// -------- Overloaded new operator for the Name class
void *Name::operator new( size_t size )
{
    for( int p = 0; p < MAXNAMES; p++ )
        if( !inuse[p] )
        {
            inuse[p] = 1;
            return pool + p;
        }
    return 0;
}

// --------- Overloaded delete operator for the Names class
void Name::operator delete( void *ptr )
{
    inuse[((char *)ptr - pool[0]) / sizeof( Name )] = 0;
}

void main()
{
    Name *directory[MAXNAMES];
    char name[25];

    for( int i = 0; i < MAXNAMES; i++ )
    {
        cout << "\nEnter name # " << i+1 << ": ";
        cin >> name;
        directory[i] = new Name( name );
    }
    for( i = 0; i < MAXNAMES; i++ )
    {
        directory[i]->display();
        delete directory[i];
    }
}
