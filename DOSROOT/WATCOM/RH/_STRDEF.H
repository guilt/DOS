///////////////////////////////////////////////////////////////////////////
// FILE: _strdef.h (Definition of std::string)
//
// =========================================================================
//
//                          Open Watcom Project
//
// Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
//
//    This file is automatically generated. Do not edit directly.
//
// =========================================================================
//
// Description: This is a helper header. It contains the definition of
//              std::string and enough other information so that the
//              standard exception classes can use strings. Yet this
//              header does not require the inclusion of the exception
//              headers and thus mutually recursive inclusions are
//              avoided.
///////////////////////////////////////////////////////////////////////////
#ifndef __STRDEF_H_INCLUDED
#define __STRDEF_H_INCLUDED

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifndef __cplusplus
 #error This header file requires C++
#endif

#ifndef _STDEXCEPT_INCLUDED
 #error The header _strdef.h is not to be directly included in user programs
#endif

#ifndef _CSTRING_INCLUDED
 #include <cstring>
#endif

#ifndef _CWCHAR_INCLUDED
 #include <cwchar>
#endif

#ifndef _ITERATOR_INCLUDED
 #include <iterator>
#endif

#ifndef _MEMORY_INCLUDED
 #include <memory>
#endif

#define EOF         (-1)                /*  End of File/Error return code   */

namespace std {

  // struct char_traits
  // ******************
  template< class CharT > struct char_traits { };

  // struct char_traits< char >
  // **************************
  template< >
  struct char_traits< char > {
    typedef char      char_type;
    typedef int       int_type;
    typedef mbstate_t state_type;

    static void assign( char_type &c1, const char_type &c2 )
      { c1 = c2; }

    static bool eq( const char_type &c1, const char_type &c2 )
      { return( c1 == c2 ); }

    static bool lt( const char_type &c1, const char_type &c2 )
      { return( c1 < c2 ); }

    static int compare( const char_type *s1, const char_type *s2, size_t n )
      { return( memcmp( s1, s2, n ) ); }

    static size_t length( const char_type *s )
      { return( strlen(s) ); }

    static const char_type *find( const char_type *s, size_t n, const char_type &a )
      { return( static_cast< char_type * >( memchr( s, a, n ) ) ); }

    static char_type *move( char_type *s1, const char_type *s2, size_t n )
      { return( static_cast< char_type * >( memmove( s1, s2, n ) ) ); }

    static char_type *copy( char_type *s1, const char_type *s2, size_t n )
      { return( static_cast< char_type * >( memcpy( s1, s2, n ) ) ); }

    static char_type *assign( char_type *s, size_t n, char_type a )
      { return( static_cast< char_type * >( memset( s, a, n ) ) ); }

    static int_type not_eof( const int_type &c )
      { return( (c != EOF) ? c : 0 ); }

    static char_type to_char_type( const int_type &c )
      { return( static_cast< char_type >(c) ); }

    static int_type to_int_type( const char_type &c )
      { return( static_cast< int_type >(c) ); }

    static bool eq_int_type( const int_type &c1, const int_type &c2 )
      { return( c1 == c2 ); }

    static int_type eof( )
      { return( EOF ); }
  };

  // struct char_traits< wchar_t >
  // *****************************
  template< >
  struct char_traits< wchar_t > {
    typedef wchar_t   char_type;
    typedef wint_t    int_type;
    typedef mbstate_t state_type;

    static void assign( char_type &c1, const char_type &c2 )
      { c1 = c2; }

    static bool eq( const char_type &c1, const char_type &c2 )
      { return( c1 == c2 ); }

    static bool lt( const char_type &c1, const char_type &c2 )
      { return( c1 < c2 ); }

    static int compare( const char_type *s1, const char_type *s2, size_t n )
    {
      while( n-- > 0 ) {
        if( *s1 < *s2 ) return( -1 );
        if( *s1 > *s2 ) return(  1 );
        ++s1; ++s2;
      }
      return( 0 );
    }

    static size_t length( const char_type *s )
      { return( wcslen(s) ); }

    static const char_type *find( const char_type *s, size_t n, const char_type &a )
    {
      const char_type *result = NULL;
      while( n-- > 0 ) {
        if( *s == a ) {
          result = s;
          break;
        }
        ++s;
      }
      return( result );
    }

    static char_type *move( char_type *s1, const char_type *s2, size_t n )
    {
      return( static_cast< char_type * >( memmove( s1, s2, n * sizeof( char_type ) ) ) );
    }

    static char_type *copy( char_type *s1, const char_type *s2, size_t n )
    {
      return( static_cast< char_type * >( memcpy( s1, s2, n * sizeof( char_type ) ) ) );
    }

    static char_type *assign( char_type *s, size_t n, char_type a )
    {
      char_type *p = s;
      while( n-- > 0 ) {
        *p++ = a;
      }
      return( s );
    }

    static int_type not_eof( const int_type &c )
      { return( (c != WEOF) ? c : static_cast< int_type >( 0 ) ); }

    static char_type to_char_type( const int_type &c )
      { return( static_cast< char_type >(c) ); }

    static int_type to_int_type( const char_type &c )
      { return( static_cast< int_type >(c) ); }

    static bool eq_int_type( const int_type &c1, const int_type &c2 )
      { return( c1 == c2 ); }

    static int_type eof( )
      { return( WEOF ); }
  };


  // ===================================
  // Definition of basic_string template
  // ===================================

  template< class CharT,
            class Traits = char_traits< CharT >,
            class Allocator = allocator< CharT > >
  class basic_string {

    template< class CharT, class Traits, class Allocator >
    friend
    bool operator==( const basic_string< CharT, Traits, Allocator > &left,
                     const basic_string< CharT, Traits, Allocator > &right );

    template< class CharT, class Traits, class Allocator >
    friend
    bool operator==( const CharT *left,
                     const basic_string< CharT, Traits, Allocator > &right );

    template< class CharT, class Traits, class Allocator >
    friend
    bool operator==( const basic_string< CharT, Traits, Allocator > &left,
                     const CharT *right );

    template< class CharT, class Traits, class Allocator >
    friend
    bool operator<( const basic_string< CharT, Traits, Allocator > &left,
                    const basic_string< CharT, Traits, Allocator > &right );

    template< class CharT, class Traits, class Allocator >
    friend
    bool operator<( const CharT *left,
                    const basic_string< CharT, Traits, Allocator > &right );

    template< class CharT, class Traits, class Allocator >
    friend
    bool operator<( const basic_string< CharT, Traits, Allocator > &left,
                    const CharT *right );
    // String swap ambiguous if general swap (in algorithm) visible.
    // Need partial ordering of function templates for this to work.
    //
    #ifdef __NEVER
    template< class CharT, class Traits, class Allocator >
    friend
    void swap( basic_string< CharT, Traits, Allocator > &left,
               basic_string< CharT, Traits, Allocator > &right );
    #endif

    public:
      typedef          Traits                     traits_type;
      typedef typename Traits::char_type          value_type;
      typedef          Allocator                  allocator_type;
      typedef typename Allocator::size_type       size_type;
      typedef typename Allocator::difference_type difference_type;
      typedef typename Allocator::reference       reference;
      typedef typename Allocator::const_reference const_reference;
      typedef typename Allocator::pointer         pointer;
      typedef typename Allocator::const_pointer   const_pointer;

      typedef pointer                                 iterator;
      typedef const_pointer                           const_iterator;
      typedef std::reverse_iterator< iterator >       reverse_iterator;
      typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

      static const size_type npos = static_cast< size_type >( -1 );

      // Constructors.
      explicit basic_string( const Allocator &a = Allocator( ) );
      basic_string( const basic_string &str );
      basic_string( const basic_string &str, size_type pos, size_type n = npos, const Allocator &a = Allocator( ) );
      basic_string( const CharT *s, size_type n, const Allocator &a = Allocator( ) );
      basic_string( const CharT *s, const Allocator &a = Allocator( ) );
      basic_string( size_type n, CharT c, const Allocator &a = Allocator( ) );

     ~basic_string( );

      basic_string &operator=( const basic_string &str );
      basic_string &operator=( const CharT *s );
      basic_string &operator=( CharT c );

      basic_string &assign( const basic_string &str, size_type pos = 0, size_type n = npos );
      basic_string &assign( const CharT *s, size_type n );
      basic_string &assign( const CharT *s );
      basic_string &assign( size_type n, CharT c );

      iterator       begin( )         { return( buffer ); }
      const_iterator begin( ) const   { return( buffer ); }
      iterator       end( )           { return( buffer + str_length ); }
      const_iterator end( )   const   { return( buffer + str_length ); }

      reverse_iterator rbegin( )
          { return( reverse_iterator( buffer + str_length ) ); }
      const_reverse_iterator rbegin( ) const
          { return( const_reverse_iterator( buffer + str_length ) ); }
      reverse_iterator rend( )
          { return( reverse_iterator( buffer ) ); }
      const_reverse_iterator rend( ) const
          { return( const_reverse_iterator( buffer ) ); }

      size_type size( )     const  { return( str_length ); }
      size_type length( )   const  { return( str_length ); }
      size_type capacity( ) const  { return( buf_length - 1 ); }
      size_type max_size( ) const  { return( npos - 1 ); } // ?

      void      resize( size_type n, CharT c );
      void      resize( size_type n ) { resize( n, CharT( ) ); }
      void      reserve( size_type new_capacity );

      void      clear( )       { str_length = 0;            }
      bool      empty( ) const { return( str_length == 0 ); }

      const_reference operator[]( size_type pos ) const
          { return( buffer[pos] ); }
      reference operator[]( size_type pos )
          { return( buffer[pos] ); }

      const_reference at( size_type pos ) const;
      reference       at( size_type pos );

      basic_string &operator+=( const basic_string &str );
      basic_string &operator+=( const CharT *s );
      basic_string &operator+=( CharT c );

      basic_string &append( const basic_string &str, size_type pos = 0, size_type n = npos );
      basic_string &append( const CharT *s, size_type n );
      basic_string &append( const CharT *s );
      basic_string &append( size_type n, CharT c );

      void          push_back( CharT c );

      basic_string &insert( size_type pos1, const basic_string &str, size_type pos2 = 0, size_type n = npos );
      basic_string &insert( size_type pos, const CharT *s, size_type n );
      basic_string &insert( size_type pos, const CharT *s );
      basic_string &insert( size_type pos, size_type n, CharT c );
      iterator      insert( iterator p, CharT c );
      void          insert( iterator p, size_type n, CharT c );

      basic_string &erase( size_type pos = 0, size_type n = npos );
      iterator      erase( iterator p );
      iterator      erase( iterator first, iterator last );

      basic_string &replace( size_type pos1, size_type n, const basic_string &str );
      basic_string &replace( size_type pos1, size_type n1, const basic_string &str, size_type pos2, size_type n2 );
      basic_string &replace( size_type pos, size_type n1, const CharT *s, size_type n2 );
      basic_string &replace( size_type pos, size_type n1, const CharT *s );
      basic_string &replace( size_type pos, size_type n1, size_type n2, CharT c );
      basic_string &replace( iterator i1, iterator i2, const basic_string &str );
      basic_string &replace( iterator i1, iterator i2, const CharT *s, size_type n );
      basic_string &replace( iterator i1, iterator i2, const CharT *s );
      basic_string &replace( iterator i1, iterator i2, size_type n, CharT c );

      size_type     copy( CharT *s, size_type n, size_type pos = 0 ) const;
      void          swap( basic_string &str );

      const CharT   *c_str( )         const;
      const CharT   *data( )          const  { return( buffer ); }
      allocator_type get_allocator( ) const  { return( mem);     }

      size_type find( const basic_string &str, size_type pos = 0 ) const;
      size_type find( const CharT *s, size_type pos, size_type n ) const;
      size_type find( const CharT *s, size_type pos = 0 ) const;
      size_type find( CharT c, size_type pos = 0 ) const;

      size_type rfind( const basic_string &str, size_type pos = npos ) const;
      size_type rfind( const CharT *s, size_type pos, size_type n ) const;
      size_type rfind( const CharT *s, size_type pos = npos ) const;
      size_type rfind( CharT c, size_type pos = npos ) const;

      size_type find_first_of( const basic_string &str, size_type pos = 0 ) const;
      size_type find_first_of( const CharT *s, size_type pos, size_type n ) const;
      size_type find_first_of( const CharT *s, size_type pos = 0 ) const;
      size_type find_first_of( CharT c, size_type pos = 0 ) const;

      size_type find_last_of( const basic_string &str, size_type pos = npos ) const;
      size_type find_last_of( const CharT *s, size_type pos, size_type n ) const;
      size_type find_last_of( const CharT *s, size_type pos = npos ) const;
      size_type find_last_of( CharT c, size_type pos = npos ) const;

      size_type find_first_not_of( const basic_string &str, size_type pos = 0 ) const;
      size_type find_first_not_of( const CharT *s, size_type pos, size_type n ) const;
      size_type find_first_not_of( const CharT *s, size_type pos = 0 ) const;
      size_type find_first_not_of( CharT c, size_type pos = 0 ) const;

      size_type find_last_not_of( const basic_string &str, size_type pos = npos ) const;
      size_type find_last_not_of( const CharT *s, size_type pos, size_type n ) const;
      size_type find_last_not_of( const CharT *s, size_type pos = npos ) const;
      size_type find_last_not_of( CharT c, size_type pos = npos ) const;

      basic_string substr( size_type pos = 0, size_type n = npos ) const;

      bool _Sane( ) const;  // Check invariants (approximately).

    private:
      // Invariants:
      // 1. buffer has size buf_length.
      // 2. buf_length is a power of two.
      // 3. buf_length > str_length. Extra space for an O(1) c_str().
      // 4. buffer never shrinks.
      // 5. buffer allocated with mem or a copy of mem.
      // 6. Every string has its own buffer (no reference counting).
      //
      Allocator mem;         // Object used to get and release memory.
      pointer   buffer;      // Points at start of string.
      size_type str_length;  // Number of buffer slots with characters.
      size_type buf_length;  // Total number of buffer slots.

      // This method encapsulates the memory allocation policy.
      pointer alloc( size_type required, size_type &found );

      // This method replaces current text with other text.
      void replace_buffer( const_pointer other_buf, size_type other_length );

      // Returns an iterator to the freshly inserted material.
      iterator insert_helper( iterator p, size_type n, CharT c );
  };


  // ======================================
  // Specific typedefs for char and wchar_t
  // ======================================
  typedef basic_string< char > string;
  typedef basic_string< wchar_t > wstring;


  // ================================================================
  // Members of basic_string that are needed by the exception classes
  // ================================================================

  template< class CharT, class Traits, class Allocator >
  typename basic_string< CharT, Traits, Allocator >::pointer
    basic_string< CharT, Traits, Allocator >::alloc(
      size_type required,
      size_type &found )
  {
    pointer   result;
    size_type length = 8;

    // Find a power of two that produces a sufficient size.
    while( length < required )
        length <<= 1;
    result = mem.allocate( length );

    // Update outputs only if allocation successful.
    found = length;
    return( result );
  }


  template< class CharT, class Traits, class Allocator >
  void basic_string< CharT, Traits, Allocator >::replace_buffer(
    const_pointer other_buffer,
    size_type other_length )
  {
    size_type new_length;
    pointer new_buffer = alloc( other_length + 1, new_length );
    Traits::copy( new_buffer, other_buffer, other_length );

    // Commit.
    mem.deallocate( buffer, buf_length );
    buffer = new_buffer;
    buf_length = new_length;
    str_length = other_length;
  }


  template< class CharT, class Traits, class Allocator >
  bool basic_string< CharT, Traits, Allocator >::_Sane( ) const
  {
    if( buf_length == 0 ) return( false );
    if( buf_length <= str_length ) return( false );

    // Is buf_length a power of 2?
    size_type temp = buf_length;
    while( temp != 1 ) {
      if( temp & 0x1 )
        return( false );
      temp >>= 1;
    }
    return( true );
  }


  // basic_string( const Allocator & )
  // *********************************
  template< class CharT, class Traits, class Allocator >
  basic_string< CharT, Traits, Allocator >::basic_string(
    const Allocator &a ) : mem( a )
  {
    buffer = alloc(1, buf_length);
    str_length = 0;
  }


  // basic_string( const basic_string &, const Allocator & )
  // ***************************************************************
  template< class CharT, class Traits, class Allocator >
  basic_string< CharT, Traits, Allocator >::basic_string(
    const basic_string &other ) : mem( other.mem )
  {
    buffer = alloc( other.str_length + 1, buf_length );
    Traits::copy( buffer, other.buffer, other.str_length );
    str_length = other.str_length;
  }


  // basic_string( const CharT *, const Allocator & )
  // ************************************************
  template< class CharT, class Traits, class Allocator >
  basic_string< CharT, Traits, Allocator >::basic_string(
    const CharT     *other,
    const Allocator &a ) : mem( a )
  {
    size_type other_length = Traits::length( other );
    buffer = alloc( other_length + 1, buf_length );
    Traits::copy( buffer, other, other_length );
    str_length = other_length;
  }


  // ~basic_string( )
  // ****************
  template< class CharT, class Traits, class Allocator >
  basic_string< CharT, Traits, Allocator >::~basic_string( )
  {
    // No need to destroy characters. CharT must be POD type.
    mem.deallocate( buffer, buf_length );
  }


  // operator=( const basic_string & )
  // *********************************
  template< class CharT, class Traits, class Allocator >
  basic_string< CharT, Traits, Allocator > &
    basic_string< CharT, Traits, Allocator >::operator=(
      const basic_string &other )
  {
    if( this == &other ) return *this;

    if( buf_length > other.str_length ) {
      Traits::copy( buffer, other.buffer, other.str_length );
      str_length = other.str_length;
    } else {
      replace_buffer( other.buffer, other.str_length );
    }
    return( *this );
  }


  // c_str( ) const
  // **************
  template< class CharT, class Traits, class Allocator >
  inline
  const CharT *basic_string< CharT, Traits, Allocator >::c_str( ) const
  {
    buffer[str_length] = CharT();
    return( buffer );
  }

} // namespace std

#endif
