// ---------------------------------------------------------------------------
// Copyright (C) 1994 Borland International
// dlist.cpp
//    Must link with myclass.cpp.
// ---------------------------------------------------------------------------

#include <classlib/dlistimp.h>
#include <iostream.h>
#include <strstrea.h>
#include "../myclass.h"

typedef TDoubleListImp<MyClass> ContainerType;
typedef TDoubleListIteratorImp<MyClass> IteratorType;

const int MaxItems=6;

void ForEachCallBack(MyClass& mc, void* s)
{
    cout << (char*)s << mc << endl;
}

void AddItems(ContainerType& container, int numItems)
{
    for( int i=numItems; i>0; i-- )
        {
        char buf[80];
        ostrstream str( buf, sizeof(buf) );
        str << i << " hello" << ends;
        if (i%2 == 0)
            container.Add(MyClass(buf));    // defaults to adding at head
        else
            container.AddAtTail(MyClass(buf));
        }
}

void UseForwardIterator(ContainerType& container)
{
    IteratorType iterator(container);
    while( iterator )
        {
        cout << iterator.Current() << endl;
        iterator++;
        }
}

void UseBackwardIterator(ContainerType& container)
{
    IteratorType iterator(container);
    iterator.RestartAtTail();
    while( iterator )
        {
        cout << iterator.Current() << endl;
        iterator--;
        }
}

int main()
{
    ContainerType container;
    AddItems(container, MaxItems);
  
    cout << "--- Starting ForEach" << endl;
    container.ForEach(ForEachCallBack, (void*)"FE ");
  
    cout << "--- Starting Iterator (forward)" << endl;
    UseForwardIterator(container);
  
    cout << "--- Deleting '3 hello'" << endl;
    container.Detach(MyClass("3 hello"));  // detach and delete
  
    cout << "--- Starting Iterator (backward)" << endl;
    UseBackwardIterator(container);
  
    return 0;
}

