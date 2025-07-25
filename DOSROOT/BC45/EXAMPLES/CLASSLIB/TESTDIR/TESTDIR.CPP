/*------------------------------------------------------------------------*/
/*                                                                        */
/*  TESTDIR.CPP                                                           */
/*                                                                        */
/*  Copyright (c) 1991, 1993 Borland International                        */
/*  All Rights Reserved.                                                  */
/*                                                                        */
/*  Sorted container example source file                                  */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __DIR_H )
#include <dir.h>
#endif  // __DIR_H

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

#if !defined( __CLASSLIB_ARRAYS_H )
#include <classlib\arrays.h>
#endif

#ifndef __FILEDATA_H
#include "filedata.h"
#endif

template <class T> class Directory
{

public:

    Directory( const char *FileSpec );
    void Show();

private:

    TISArrayAsVector<T> Array;

};

template <class T> Directory<T>::Directory( const char *FileSpec ) :
    Array( 10, 0, 5 )
{
    struct ffblk FileBlock;
    int Done = findfirst( FileSpec, &FileBlock, 0 );
    while( !Done )
        {
        Array.Add( new T(FileBlock) );
        Done = findnext( &FileBlock );
        }
}

static void ShowBlock( FilesByName &blk, void * )
{
    cout << blk << endl;
}

static void ShowBlock( FilesByDate &blk, void * )
{
    cout << blk << endl;
}

static void ShowBlock( FilesBySize &blk, void * )
{
    cout << blk << endl;
}

template <class T> inline void Directory<T>::Show()
{
    Array.ForEach( ShowBlock, 0 );
}

void SortByName( const char *FileSpec )
{
    Directory<FilesByName> dir( FileSpec );
    dir.Show();
}

void SortByDate( const char *FileSpec )
{
    Directory<FilesByDate> dir( FileSpec );
    dir.Show();
}

void SortBySize( const char *FileSpec )
{
    Directory<FilesBySize> dir( FileSpec );
    dir.Show();
}

int main( int argc, char *argv[] )
{
    if( argc < 2 || argc > 3 )
        {
        cerr << "Usage:  directry [options] filespec" << endl << endl;
        cerr << "Options:" << endl;
        cerr << "\t-sd\tsort by date" << endl;
        cerr << "\t-sn\tsort by name" << endl;
        cerr << "\t-ss\tsort by size" << endl;
        exit(1);
        }

    if( argc != 3 )
        SortByName( argv[1] );
    else 
        {
        if( strcmp( argv[1], "-sn" ) == 0 )
            SortByName( argv[2] );
        else if( strcmp( argv[1], "-sd" ) == 0 )
            SortByDate( argv[2] );
        else if( strcmp( argv[1], "-ss" ) == 0 )
            SortBySize( argv[2] );
        }

    return 0;
}
