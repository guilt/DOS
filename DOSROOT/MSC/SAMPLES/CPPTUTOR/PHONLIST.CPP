// PHONLIST.CPP

#include "phonlist.h"
#include <string.h>

PhoneList::PhoneList()
{
    firstEmpty = 0;
}

int PhoneList::add( const Record &newRec )
{
    if( firstEmpty < MAXLENGTH - 1 )
    {
        aray[firstEmpty++] = newRec;
        return 1;   // Indicate success
    }
    else return 0;
}

Record *PhoneList::search( const char *searchKey )
{
    for( int i = 0; i < firstEmpty; i++ )
        if( !strcmp( aray[i].name, searchKey ) )
            return &aray[i];

    return 0;
}

PhoneIter::PhoneIter( PhoneList &m )
    : mine( &m )          // Initialize the constant member
{
    currIndex = 0;
}

Record *PhoneIter::getFirst()
{
    currIndex = 0;
    return &(mine->aray[currIndex]);
}

Record *PhoneIter::getLast()
{
    currIndex = mine->firstEmpty - 1;
    return &(mine->aray[currIndex]);
}

Record *PhoneIter::getNext()
{
    if( currIndex < mine->firstEmpty - 1 )
    {
        currIndex++;
        return &(mine->aray[currIndex]);
    } 
    else return 0;
}

Record *PhoneIter::getPrev()
{
    if( currIndex > 0 )
    {
        currIndex--;
        return &(mine->aray[currIndex]);
    }
    else return 0;
}

