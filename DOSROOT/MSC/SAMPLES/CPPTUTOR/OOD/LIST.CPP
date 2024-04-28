
/********************************************************************

 FILE: LIST.CPP

********************************************************************/

#include "list.h"

/********************************************************************

 ListElem::isEqual

 This function tests for equality against the specified element.
 The default implementation is a comparison of the address.

********************************************************************/

int ListElem::isEqual( ListElem *other )
{
    return( this == other );
}


/********************************************************************

 Implementation notes about List:

 A List is implemented as a doubly-linked ring of Nodes, each of
 which contains a pointer to a ListElem. Each List contains an
 endNode, which indicates the beginning and end point of the list,
 and a current pointer, which indicates the current position in
 the list. The initIterator function sets the current pointer to
 the endNode, allowing the next call of getNext or getPrev to
 return either the first or the last element in the list.

********************************************************************/


/********************************************************************

 List::List

 This function creates a new List by allocating the endNode.

********************************************************************/

List::List()
{
    endNode = new Node;
    endNode->next = endNode->prev = endNode;
    endNode->data = 0;
    current = 0;
}

/********************************************************************

 List::addHead

 This function adds a new element to the head of the list.

********************************************************************/

void List::addHead( ListElem *newHead )
{
    Node *newNode;

    newNode= new Node;
    newNode->data = newHead;
    newNode->prev = endNode;
    newNode->next = endNode->next;
    endNode->next = newNode;
    newNode->next->prev = newNode;
}

/********************************************************************

 List::addTail

 This function adds a new element to the tail of the list.

********************************************************************/

void List::addTail( ListElem *newTail )
{
    Node *newNode;

    newNode = new Node;
    newNode->data = newTail;
    newNode->prev = endNode->prev;
    newNode->next = endNode;
    endNode->prev = newNode;
    newNode->prev->next = newNode;
}

/********************************************************************

 List::removeHead

 This function removes an element from the head of the list.

********************************************************************/

ListElem *List::removeHead()
{
    Node *temp;
    ListElem *removed;

    if( endNode->next != endNode )
    {
        temp = endNode->next;
        endNode->next = temp->next;
        temp->next->prev = endNode;

        removed = temp->data;
        delete temp;
        return removed;
    }
    else
        return 0;
}

/********************************************************************

 List::removeTail

 This function removes an element from the tail of the list.

********************************************************************/

ListElem *List::removeTail()
{
    Node *temp;
    ListElem *removed;

    if( endNode->prev != endNode )
    {
        temp = endNode->prev;
        endNode->prev = temp->prev;
        temp->prev->next = endNode;

        removed = temp->data;
        delete temp;
        return removed;
    }
    else
        return 0;
}

/********************************************************************

 List::getNext

 This function returns the next element in the list, assuming a current
 position has been established. Returns 0 if at end of list.

********************************************************************/

ListElem *List::getNext()
{
    if( !current )
        return 0;

    current = current->next;
    if( current == endNode )
    {
        current = 0;
        return 0;
    }
    return current->data;
}

/********************************************************************

 List::getPrev

 This function returns the previous element in the list, assuming a
 current position has been established. Returns 0 if at beginning
 of list.

********************************************************************/

ListElem *List::getPrev()
{
    if( !current )
        return 0;

    current = current->prev;
    if( current == endNode )
    {
        current = 0;
        return 0;
    }
    return current->data;
}

/********************************************************************

 List::insertBefore

 This function inserts the specified element before the current
 position in the list. It returns 1 if the insertion was successful,
 or 0 if no current position was established.

********************************************************************/

int List::insertBefore( ListElem *newElem )
{

    // insert after current node
    if( current )
    {
        Node *temp;

        temp->data = newElem;
        temp->next = current;
        temp->prev = current->prev;

        current->prev = temp;
        temp->prev->next = temp;
        return 1;
    }
    else
        return 0;
}

/********************************************************************

 List::insertAfter

 This function inserts the specified element after the current
 position in the list. It returns 1 if the insertion was successful,
 or 0 if no current position was established.

********************************************************************/

int List::insertAfter( ListElem *newElem )
{

    // insert after current node
    if( current )
    {
        Node *temp;

        temp->data = newElem;
        temp->prev = current;
        temp->next = current->next;

        current->next = temp;
        temp->next->prev = temp;
        return 1;
    }
    else
        return 0;
}

/********************************************************************

 List:remove

 This function removes the current element from the list. It returns
 the element if it was successfully removed, or 0 if no current
 position was established.

********************************************************************/

ListElem *List::remove()
{
    Node *temp;
    ListElem *removed;

    if( current )
    {
        temp = current;   // hold element being removed

        current->prev->next = current->next;
        current->next->prev = current->prev;

        current = current->next;

        removed = temp->data;
        delete temp;
        return removed;
    }
    else
        return 0;
}

/********************************************************************

 List::find

 This function searches the list for the first occurrence of the
 specified element. It returns the place of the element in the
 list if it was found, or 0 if it wasn't found.

********************************************************************/

int List::find( ListElem *searchElem )
{
    Node *temp;
    ListElem *temp2;
    int i;

    temp = current;

    // Move to the head and search each element.
    i = 1;
    initIterator();
    while( (temp2 = getNext()) != 0 )
    {
        if( temp2->isEqual( searchElem ) )
            return i;
        i++;
    }

    // Not found, so restore current.
    current = temp;
    return 0;
}

/********************************************************************

 List::~List

 This function removes all elements from the list, and deletes the
 endNode.

********************************************************************/

List::~List()
{
    while( removeTail() )
        ;

    delete endNode;
}

