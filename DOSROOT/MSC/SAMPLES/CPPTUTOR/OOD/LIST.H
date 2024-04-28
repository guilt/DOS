/********************************************************************

 FILE: LIST.H

 Defines List and its associated class, ListElem.

********************************************************************/


#if !defined( _LIST_H_ )

#define _LIST_H_

/********************************************************************

 ListElem

 Abstract base class for all objects to be stored in a List.

 Public Interface:

     isEqual - tests for equality against specified ListElem.
         The default implementation is a comparison of the address;
         this can be overriden in derived classes.

********************************************************************/

class ListElem
{
public:
    virtual int isEqual( ListElem *other );
    virtual ~ListElem() {}
};

/********************************************************************

 List

 Maintains a list to ListElem objects. Reference semantics are used;
 that is, adding an element stores a pointer to that object instead
 of making a copy of the object, and removing an object removes
 the pointer but not the object itself. Operations supported are:
 examining the element at either end of the list, adding an element
 to either end of the list, removing the element at the end of the
 list, searching for a given element, testing for an empty list,
 iterating in either direction, removing the current element, and
 inserting a new element before or after the current position.

 Public Interface:

     List - constructor.

     getHead, getTail - returns the element at the head or tail of
         the list, but does not remove it.

     addHead, addTail - adds a new element to the head or tail of the
         list.

     removeHead, removeTail - removes and returns the element at the
         head or tail of the list.

     initIterator - initializes iterator. Must be called before
         iteration in either direction begins. A subsequent call
         to getNext returns the element at the head of the list,
         whereas a call to getPrev returns the element at the the
         tail of the list.

     getNext, getPrev - returns the next or previous element in the
         list. A current position must have previously been
         established through iteration, or with the find function.
         Returns 0 if no further element.

     find - searches for the first occurence of the specified element
         in the list. Returns 1 if the element was found, 0 if not.

     insertBefore, insertAfter - inserts a new element before or
         after the current position. Returns 1 is insertion was
         successful, 0 if current position hasn't been established.

     remove - removes and returns the current element from the list.
         Returns 0 if current position hasn't been established.

     isEmpty - returns 1 is list is empty, 0 otherwise.

********************************************************************/

struct Node
{
public:
    ListElem *data;
    Node     *next;
    Node     *prev;
};

class List
{
public:
              List();
              List( List& other );
    ListElem *getHead() const;
    ListElem *getTail() const;
    void      addHead( ListElem *newItem );
    void      addTail( ListElem *newItem );
    ListElem *removeHead();
    ListElem *removeTail();
    void      initIterator();
    ListElem *getNext();
    ListElem *getPrev();
    int       find( ListElem *searchItem );
    int       insertBefore( ListElem *newItem );
    int       insertAfter( ListElem *newItem );
    ListElem *remove();
    int       isEmpty() const;
             ~List();
private:
    Node *endNode,
         *current;

};

inline int List::isEmpty() const
{
    return ( endNode->next == endNode );
}

inline ListElem *List::getHead() const
{
    if ( endNode->next )
        return endNode->next->data;
    return 0;
}

inline ListElem *List::getTail() const
{
    if ( endNode->prev )
        return endNode->prev->data;
    return 0;
}


inline void List::initIterator()
{
    current = endNode;
}

#endif // _LIST_H_

