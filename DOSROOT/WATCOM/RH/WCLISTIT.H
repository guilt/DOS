//
//  wclistit.h    Defines for the WATCOM Container List Iterator Class
//
// =========================================================================
//
//                          Open Watcom Project
//
// Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
// Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
//
//    This file is automatically generated. Do not edit directly.
//
// =========================================================================
//
#ifndef _WCLISTIT_H_INCLUDED
#define _WCLISTIT_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef __cplusplus
 #error This header file requires C++
#endif

//
// There are 12 list iterator classes.
//
// WCValSListIter, WCValDListIter, WCPtrSListIter, WCPtrDListIter,
// WCIsvSListIter and WCIsvDListIter iterate only NON-CONSTANT lists.
// For example, to iterate a non-constant WCValSList, use the WCValSListIter
// class.
//
// WCValConstSListIter, WCValConstDListIter, WCPtrConstSListIter,
// WCPtrConstDListIter, WCIsvConstSListIter and WCIsvConstDListIter iterate
// either constant or non-consant lists.  The insert and append member
// functions are private to these iterator classes.
// For example, to iterate a constant WCIsvDList, use the
// WCIsvConstDListIter class.
//

#pragma warning 621 9       // I want the behaviour this warning points to

#ifndef _WCDEFS_H_INCLUDED
 #include <wcdefs.h>
#endif

#ifndef _WCLIST_H_INCLUDED
 #include <wclist.h>
#endif

#ifndef _WCLIBASE_H_INCLUDED
 #include <wclibase.h>
#endif

//
//  This defines an iterator class for non-const single linked list of
//  values.
//
//  The operators --() and -=() and the insert member function are made
//  private to prevent their being used with a single linked list.
//

template<class Type>
class WCValSListIter : public WCValListIterBase<Type, WCValSList<Type>,
                                                      WCNIsvSLink<Type> >  {
private:
    int operator--();
    int operator-=( int );
    WCbool insert( Type& );

public:
    inline WCValSListIter() {};
    inline virtual ~WCValSListIter() {};
    inline WCValSListIter( WCValSList<Type> & slist )
         : WCValListIterBase( &slist ) {};
};




//
//  This defines an iterator class for the double linked list of
//  values.
//

template<class Type>
class WCValDListIter : public WCValListIterBase<Type, WCValDList<Type>,
                                                      WCNIsvDLink<Type> >  {
public:
    inline WCValDListIter() {};
    inline virtual ~WCValDListIter() {};
    inline WCValDListIter( WCValDList<Type> & slist )
         : WCValListIterBase( &slist ) {};
};




//
//  This defines an iterator class for the single linked list of
//  pointers.
//
//  The operators --() and -=() and the insert member function are made
//  private to prevent their being used with a single linked list.
//

template<class Type>
class WCPtrSListIter : public WCValListIterBase<Type *, WCPtrSList<Type>,
                                                     WCNIsvSLink<Type *> >  {
private:
    int operator--();
    int operator-=( int );
    WCbool insert( Type * );

public:
    inline WCPtrSListIter() {};
    inline virtual ~WCPtrSListIter() {};
    inline WCPtrSListIter( WCPtrSList<Type> & slist )
         : WCValListIterBase( &slist ) {};

    inline WCbool append( Type * datum ) {
        return( WCValListIterBase::append( datum ) );
    }
};




//
//  This defines an iterator class for the double linked list of
//  pointers.
//

template<class Type>
class WCPtrDListIter : public WCValListIterBase<Type *, WCPtrDList<Type>,
                                                     WCNIsvDLink<Type *> >  {
public:
    inline WCPtrDListIter() {};
    inline virtual ~WCPtrDListIter() {};
    inline WCPtrDListIter( WCPtrDList<Type> & dlist )
         : WCValListIterBase( &dlist ) {};

    inline WCbool insert( Type * datum ) {
        return( WCValListIterBase::insert( datum ) );
    }

    inline WCbool append( Type * datum ) {
        return( WCValListIterBase::append( datum ) );
    }
};




//
//  This defines an iterator class for the intrusive single linked list.
//
//  The operators --() and -=() and the insert member function are made
//  private to prevent their being used with a single linked list.
//

template<class Type>
class WCIsvSListIter : public WCIsvListIterBase<Type, WCIsvSList<Type> > {
private:
    Type * operator--();
    Type * operator-=( int );
    WCbool insert( Type * );

public:
    inline WCIsvSListIter() {};
    inline virtual ~WCIsvSListIter() {};
    inline WCIsvSListIter( WCIsvSList<Type> & slist )
         : WCIsvListIterBase( &slist ) {};
};




//
//  This defines an iterator class for the intrusive double linked list.
//

template<class Type>
class WCIsvDListIter : public WCIsvListIterBase<Type, WCIsvDList<Type> > {
public:
    inline WCIsvDListIter() {};
    inline virtual ~WCIsvDListIter() {};
    inline WCIsvDListIter( WCIsvDList<Type> & dlist )
         : WCIsvListIterBase( &dlist ) {};
};




//
//  This defines an iterator class for a constant single linked list of
//  values.  The append member function is made private to prevent it
//  being used with a constant list.
//

template<class Type>
class WCValConstSListIter : public WCValSListIter<Type> {
private:
    WCbool append( Type& );
    typedef WCValSList<Type> NonConstList;

public:
    inline WCValConstSListIter() {};
    inline virtual ~WCValConstSListIter() {};
    inline WCValConstSListIter( const WCValSList<Type> & slist )
         : WCValSListIter( (NonConstList &)slist ) {};

    inline const WCValSList<Type> * container() {
        return( WCValSListIter::container() );
    };

    inline void reset() {
        WCValSListIter::reset();
    };

    inline void reset( const WCValSList<Type> & slist ) {
        WCValSListIter::reset( (NonConstList &)slist );
    };
};




//
//  This defines an iterator class for a constant double linked list of
//  values.  The append and insert member functions are made private to
//  prevent them being used with a constant list.
//

template<class Type>
class WCValConstDListIter : public WCValDListIter<Type> {
private:
    WCbool append( Type& );
    WCbool insert( Type& );
    typedef WCValDList<Type> NonConstList;

public:
    inline WCValConstDListIter() {};
    inline virtual ~WCValConstDListIter() {};
    inline WCValConstDListIter( const WCValDList<Type> & dlist )
         : WCValDListIter( (NonConstList &)dlist ) {};

    inline const WCValDList<Type> * container() {
        return( WCValDListIter::container() );
    };

    inline void reset() {
        WCValDListIter::reset();
    };

    inline void reset( const WCValDList<Type> & dlist ) {
        WCValDListIter::reset( (NonConstList &)dlist );
    };
};




//
//  This defines an iterator class for a constant single linked list of
//  pointers.  The append member function is made private to prevent it
//  being used with a constant list.
//

template<class Type>
class WCPtrConstSListIter : public WCPtrSListIter<Type> {
private:
    WCbool append( Type * );
    typedef WCPtrSList<Type> NonConstList;

public:
    inline WCPtrConstSListIter() {};
    inline virtual ~WCPtrConstSListIter() {};
    inline WCPtrConstSListIter( const WCPtrSList<Type> & slist )
         : WCPtrSListIter( (NonConstList &)slist ) {};

    inline const WCPtrSList<Type> * container() {
        return( WCPtrSListIter::container() );
    };

    inline void reset() {
        WCPtrSListIter::reset();
    };

    inline void reset( const WCPtrSList<Type> & slist ) {
        WCPtrSListIter::reset( (NonConstList &)slist );
    };
};




//
//  This defines an iterator class for a constant double linked list of
//  pointers.  The append and insert member functions are made private to
//  prevent them being used with a constant list.
//

template<class Type>
class WCPtrConstDListIter : public WCPtrDListIter<Type> {
private:
    WCbool append( Type * );
    WCbool insert( Type * );
    typedef WCPtrDList<Type> NonConstList;

public:
    inline WCPtrConstDListIter() {};
    inline virtual ~WCPtrConstDListIter() {};
    inline WCPtrConstDListIter( const WCPtrDList<Type> & dlist )
         : WCPtrDListIter( (NonConstList &)dlist ) {};

    inline const WCPtrDList<Type> * container() {
        return( WCPtrDListIter::container() );
    };

    inline void reset() {
        WCPtrDListIter::reset();
    };

    inline void reset( const WCPtrDList<Type> & dlist ) {
        WCPtrDListIter::reset( (NonConstList &)dlist );
    };
};




//
//  This defines an iterator class for a constant intrusive single linked
//  list.  The append member function is made private to prevent it
//  being used with a constant list.
//

template<class Type>
class WCIsvConstSListIter : public WCIsvSListIter<Type> {
private:
    WCbool append( Type * );
    typedef WCIsvSList<Type> NonConstList;

public:
    inline WCIsvConstSListIter() {};
    inline virtual ~WCIsvConstSListIter() {};
    inline WCIsvConstSListIter( const WCIsvSList<Type> & slist )
         : WCIsvSListIter( (NonConstList &)slist ) {};

    inline const WCIsvSList<Type> * container() {
        return( WCIsvSListIter::container() );
    };

    inline void reset() {
        WCIsvSListIter::reset();
    };

    inline void reset( const WCIsvSList<Type> & slist ) {
        WCIsvSListIter::reset( (NonConstList &)slist );
    };
};




//
//  This defines an iterator class for a constant intrusive double linked
//  pointers.  The append and insert member functions are made private to
//  prevent them being used with a constant list.
//

template<class Type>
class WCIsvConstDListIter : public WCIsvDListIter<Type> {
private:
    WCbool append( Type * );
    WCbool insert( Type * );
    typedef WCIsvDList<Type> NonConstList;

public:
    inline WCIsvConstDListIter() {};
    inline virtual ~WCIsvConstDListIter() {};
    inline WCIsvConstDListIter( const WCIsvDList<Type> & dlist )
         : WCIsvDListIter( (NonConstList &)dlist ) {};

    inline const WCIsvDList<Type> * container() {
        return( WCIsvDListIter::container() );
    };

    inline void reset() {
        WCIsvDListIter::reset();
    };

    inline void reset( const WCIsvDList<Type> & dlist ) {
        WCIsvDListIter::reset( (NonConstList &)dlist );
    };
};

#endif
