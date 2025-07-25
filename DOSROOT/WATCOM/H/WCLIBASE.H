//
//  wclibase.h    Defines for the WATCOM Container List Iterator Base Classes
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
#ifndef _WCLIBASE_H_INCLUDED
#define _WCLIBASE_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef __cplusplus
 #error This header file requires C++
#endif

#ifndef __COMDEF_H_INCLUDED
 #include <_comdef.h>
#endif

#ifndef _WCDEFS_H_INCLUDED
 #include <wcdefs.h>
#endif

#ifndef _WCEXCEPT_H_INCLUDED
 #include <wcexcept.h>
#endif

//
//  The WCListIterBase class is used as a basis for the iterator
//  classes for the various list containers.
//
//  It is an abstract base class to prevent objects of this class
//  from being created.
//

class WCListIterBase : public WCIterExcept {
protected:
    enum {                      // flags for outside_list
        before_first    = 1,
        after_last
    };
    WCIsvListBase *     curr_list;
    WCSLink *           curr_item;
    // if outside_list is non-zero, curr_item must be 0.
    int                 outside_list;

    _WPRTLINK WCSLink *          base_advance( int );
    _WPRTLINK WCDLink *          base_retreat( int );
    inline WCSLink *             base_get_tail() {
        return( curr_list->tail );
    };

    // helpers for insert and append
    _WPRTLINK WCSLink *          base_tail_hit( WCSLink * );
    _WPRTLINK void               base_tail_unhit( WCSLink * );

    inline void base_reset();
    inline void base_reset_list( WCIsvListBase * list );

public:
    inline WCListIterBase() : curr_item( 0 ), curr_list( 0 )
                                , outside_list( 0 ) {};
    inline WCListIterBase( WCIsvListBase * list )
                         : curr_item( 0 ), curr_list( list )
                         , outside_list( before_first ) {};
    inline virtual ~WCListIterBase() = 0;

    inline WCSLink * operator()();
    inline WCSLink * operator++();
    inline WCSLink * operator+=( int );
    inline WCDLink * operator--();
    inline WCDLink * operator-=( int );
};

inline WCListIterBase::~WCListIterBase() {};

inline void WCListIterBase::base_reset() {
    curr_item = 0;
    outside_list = before_first;
}

inline void WCListIterBase::base_reset_list( WCIsvListBase * list ) {
    curr_list = list;
    base_reset();
}

inline WCSLink * WCListIterBase::operator()() {
    return( base_advance( 1 ) );
}

inline WCSLink * WCListIterBase::operator++() {
    return( base_advance( 1 ) );
}

inline WCDLink * WCListIterBase::operator--() {
    return( base_retreat( 1 ) );
}

inline WCSLink * WCListIterBase::operator+=( int incr_amount ) {
    return( base_advance( incr_amount ) );
}

inline WCDLink * WCListIterBase::operator-=( int incr_amount ) {
    return( base_retreat( incr_amount ) );
}




//
//  The WCIsvListIterBase defines the base iterator class for intrusive
//  value type containers.
//

template<class Type, class FType>
class WCIsvListIterBase : public WCListIterBase {
public:
    inline WCIsvListIterBase() {};
    inline virtual ~WCIsvListIterBase() = 0;
    inline WCIsvListIterBase( FType * slist ) : WCListIterBase( slist ) {};

    inline void reset( FType & slist ) {
        WCListIterBase::base_reset_list( &slist );
    };

    inline void reset() {
        WCListIterBase::base_reset();
    };

    inline Type * operator()() {
        return( (Type *)WCListIterBase::operator()() );
    };

    inline Type * operator++() {
        return( (Type *)WCListIterBase::operator++() );
    };

    inline Type * operator--() {
        return( (Type *)WCListIterBase::operator--() );
    };

    inline Type * operator+=( int adv_amount ) {
        return( (Type *)WCListIterBase::operator+=( adv_amount ) );
    };

    inline Type * operator-=( int adv_amount ) {
        return( (Type *)WCListIterBase::operator-=( adv_amount ) );
    };

    inline Type * current() const {
        if( ( curr_list == 0 )||( curr_item == 0 ) ) {
            base_throw_undef_item();
            return( 0 );
        }
        return( (Type *)curr_item );
    };

    inline FType * container() const {
        if( curr_list == 0 ) {
            base_throw_undef_iter();
        }
        return( (FType *)curr_list );
    };

    WCbool insert( Type * );

    WCbool append( Type * );
};

template<class Type, class FType>
inline WCIsvListIterBase<Type,FType>::~WCIsvListIterBase() {};

template<class Type, class FType>
WCbool WCIsvListIterBase<Type,FType>::insert( Type * datum ) {
    if( ( curr_list == 0 )||( curr_item == 0 ) ) {
        base_throw_undef_iter();
        return( FALSE );
    }
    WCSLink * prev_item = curr_item;
    WCbool ret_val;
    if( prev_item != 0 ) {
        prev_item = ((WCDLink *)prev_item)->prev.link;
    }
    // make the tail the element before the element being inserted
    WCSLink * curr_tail = base_tail_hit( prev_item );
    ret_val = ((FType *)curr_list)->insert( datum );
    // restore the tail
    base_tail_unhit( curr_tail );
    return( ret_val );
};

template<class Type, class FType>
WCbool WCIsvListIterBase<Type,FType>::append( Type * datum ) {
    if( ( curr_list == 0 )||( curr_item == 0 ) ) {
        base_throw_undef_iter();
        return( FALSE );
    }
    WCbool ret_val;
    if( curr_item == base_get_tail() ) {
        // append the new element to the end of the list
        ret_val = ((FType *)curr_list)->append( datum );
    } else {
        // the new element is not the last element in the list, so make
        // the tail the element before the new element (curr_item)
        WCSLink * curr_tail = base_tail_hit( curr_item );
        ret_val = ((FType *)curr_list)->insert( datum );
        // restore the tail
        base_tail_unhit( curr_tail );
    }
    return( ret_val );
};




//
//  The WCValListIterBase defines the base iterator class for value type
//  containers.
//

template<class Type, class FType, class LType>
class WCValListIterBase : public WCListIterBase {
public:
    inline WCValListIterBase() {};
    inline virtual ~WCValListIterBase() = 0;
    inline WCValListIterBase( FType * slist ) : WCListIterBase( slist ) {};

    inline void reset( FType & dlist ) {
        WCListIterBase::base_reset_list( &dlist );
    };

    inline void reset() {
        WCListIterBase::base_reset();
    };

    inline int operator()() {
        return( WCListIterBase::operator()() != 0 );
    };

    inline int operator++() {
        return( WCListIterBase::operator++() != 0 );
    };

    inline int operator--() {
        return( WCListIterBase::operator--() != 0 );
    };

    inline int operator+=( int adv_amount ) {
        return( WCListIterBase::operator+=( adv_amount ) != 0 );
    };

    inline int operator-=( int adv_amount ) {
        return( WCListIterBase::operator-=( adv_amount ) != 0 );
    };

    inline FType * container() const {
        if( curr_list == 0 ) {
            base_throw_undef_iter();
        }
        return( (FType *)curr_list );
    };

    Type current() const;

    WCbool insert( Type& );

    WCbool append( Type& );
};

template<class Type, class FType, class LType>
inline WCValListIterBase<Type,FType,LType>::~WCValListIterBase() {};

template<class Type, class FType, class LType>
Type WCValListIterBase<Type,FType,LType>::current() const {
    if( ( curr_list == 0 )||( curr_item == 0 ) ) {
        base_throw_undef_item();
        Type ret_val;
        return( ret_val );
    } else {
        return( ((LType *)curr_item)->data );
    }
};

template<class Type, class FType, class LType>
WCbool WCValListIterBase<Type,FType,LType>::insert( Type& datum ) {
    if( ( curr_list == 0 )||( curr_item == 0 ) ) {
        base_throw_undef_iter();
        return( FALSE );
    }
    WCSLink * prev_item = curr_item;
    WCbool ret_val;
    if( prev_item != 0 ) {
        prev_item = ((WCDLink *)prev_item)->prev.link;
    }
    // make the tail the element before the element being inserted
    WCSLink * curr_tail = base_tail_hit( prev_item );
    ret_val = ((FType *)curr_list)->insert( datum );
    // restore the tail
    base_tail_unhit( curr_tail );
    return( ret_val );
};

template<class Type, class FType, class LType>
WCbool WCValListIterBase<Type,FType,LType>::append( Type& datum ) {
    if( ( curr_list == 0 )||( curr_item == 0 ) ) {
        base_throw_undef_iter();
        return( FALSE );
    }
    WCbool ret_val;
    if( curr_item == base_get_tail() ) {
        // append the new element to the end of the list
        ret_val = ((FType *)curr_list)->append( datum );
    } else {
        // the new element is not the last element in the list, so make
        // the tail the element before the new element (curr_item)
        WCSLink * curr_tail = base_tail_hit( curr_item );
        ret_val = ((FType *)curr_list)->insert( datum );
        // restore the tail
        base_tail_unhit( curr_tail );
    }
    return( ret_val );
};

#endif
