// ---------------------------------------------------------------------------
// Copyright (C) 1994 Borland International
// associdd.cpp
//    Must link with myclass.cpp.    
// ---------------------------------------------------------------------------

#include <classlib/assoc.h>
#include <classlib/dict.h>
#include <iostream.h>
#include <strstrea.h>
#include "../myclass.h" 

typedef TDDAssociation<MyClass, MyValue> AssociationType;
typedef TIDictionaryAsHashTable<AssociationType> ContainerType;
typedef TIDictionaryAsHashTableIterator<AssociationType> IteratorType;

const int MaxItems=6;

void ForEachCallBack(AssociationType& at, void* s)
{
    cout << (char*)s << at.Key() << ", " << at.Value() << endl;
}

void AddItems(ContainerType& container, int numItems)
{
    for( int i=numItems; i>0; i-- )
        {
        char buf1[10];
        ostrstream out1( buf1, sizeof(buf1) );
        out1 << i << ends;
        MyClass mc(buf1);

        char buf2[10];
        ostrstream out2( buf2, sizeof(buf2) );
        out2 << "hello " << i << ends;
        MyValue mv(buf2);
        AssociationType assoc(mc, mv);
        container.Add( new AssociationType(assoc) );
        }
}

void UseForwardIterator(ContainerType &container)
{
    IteratorType iterator(container);
    while (iterator)
        {
        const AssociationType* at = iterator.Current();
        cout << at->Key() << ", " << at->Value() << endl;
        iterator++;
        }
}

int main()
{
    ContainerType container(MaxItems);
    AddItems(container, MaxItems);
  
    cout << "--- Starting ForEach" << endl;
    container.ForEach(ForEachCallBack, (void*)"FE ");
  
    cout << "--- Starting Iterator (forward)" << endl;
    UseForwardIterator(container);
  
    return 0;
}
