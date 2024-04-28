// PHONLIST.H

// This is an example class from Chapter 6 of the C++ Tutorial. This
//     class demonstrates the use of friend classes. The PhoneList class
//     stores an array of Records. The PhoneIter class acts as an
//     iterator for a PhoneList, allowing you to move back and forth in
//     the list.

#if !defined( _PHONLIST_H_ )

#define _PHONLIST_H_

struct Record
{
    char name[30];
    char number[10];
};

const int MAXLENGTH = 100;

class PhoneList
{
friend class PhoneIter;
public:
    PhoneList();
    int add( const Record &newRec );
    Record *search( const char *searchKey );
private:
    Record aray[MAXLENGTH];
    int firstEmpty;          // First unused element
};

class PhoneIter
{
public:
    PhoneIter( PhoneList &m );
    Record *getFirst();
    Record *getLast();
    Record *getNext();
    Record *getPrev();
private:
    PhoneList *const mine;     // Constant pointer to PhoneList object
    int currIndex;
};

#endif  // _PHONLIST_H_

