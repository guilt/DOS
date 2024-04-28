// dmtest.cpp : A program to test the CPerson and CPersonList classes.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "person.h"

// Function prototypes.
CPersonList* MakeDataBase();
CFile* OpenForReading( const CString& rFileName );
CFile* OpenForWriting( const CString& rFileName );
CPersonList* ReadDataBase( CFile* pFile );
BOOL WriteDataBase( CFile* pFile, CPersonList* pDataBase );
void TestFindPerson( CPersonList* pDataBase );
void ListDataBase( CPersonList* db );

/////////////////////////////////////////////////////////////////////////////

void main()
{
	const char szFileName[] = "tutorial.dat";

#ifdef _DEBUG
	// Prepare for display of search results
	const int nDumpChildren = 1;
	afxDump.SetDepth( nDumpChildren );
#endif

	printf( "Create a person list and fill it with persons\n" );
	CPersonList* pDataBase = MakeDataBase();

	printf( "Serialize the person list\n" );
	CFile* pFile;  // Declare a file object

	TRY
	{
		// Could throw a file exception if can't open file
		pFile = OpenForWriting( szFileName );

		// Could throw an archive exception if can't create
		WriteDataBase( pFile, pDataBase );
	}
	CATCH( CFileException, theException )
	{
		printf( "Unable to open file for writing\n" );
		exit( -1 );
	}
	AND_CATCH( CArchiveException, theException )
	{
		printf( "Unable to save the database\n" );
		pFile->Close();  // Close up
		delete pFile;
		exit( -1 );
	}
	END_CATCH
	
	// No exceptions, so close up
	pFile->Close();
	delete pFile;

	ListDataBase( pDataBase );
	
	printf( "Delete the list and all its elements\n" );
	pDataBase->DeleteAll();
	ListDataBase( pDataBase );
	delete pDataBase;
	
	printf( "Deserialize the data from disk into a new list\n" );
	CPersonList* pDataBase2;   // Create a new, empty list

	TRY
	{
		// Could throw a file exception if can't open file
		pFile = OpenForReading( szFileName );
	
		// Could throw an archive exception if can't create
		pDataBase2 = ReadDataBase( pFile );
	}
	CATCH( CFileException, theException )
	{
		printf( "Unable to open file for reading database\n" );
		exit( -1 );
	}
	AND_CATCH( CArchiveException, theException )
	{
		printf( "Unable to read the database\n" );
		pFile->Close();  // Close up before exiting
		delete pFile;
		exit( -1 );
	}
	END_CATCH

	// No exceptions, so close up
	pFile->Close();
	delete pFile;

	ListDataBase( pDataBase2 );
	
	printf( "Test the FindPerson function\n" );
	if ( pDataBase2 != NULL )
	TestFindPerson( pDataBase2 );

	printf( "Delete the list and all its elements\n" );
	pDataBase2->DeleteAll();
	delete pDataBase2;

	TRACE( "End of program\n" );
}

// MakeDataBase - Create a database and add some persons
//
CPersonList* MakeDataBase()
{
	TRACE( "  Make a new person list on the heap\n" );
	CPersonList* pDataBase = new CPersonList;

	TRACE( "  Add several new persons to the list\n" );
	CPerson* pNewPerson1 = new CPerson( "Smith", "Mary", "435-8159" );
	pDataBase->AddHead( pNewPerson1 );

	CPerson* pNewPerson2 = new CPerson( "Smith", "Al", "435-4505" );
	pDataBase->AddHead( pNewPerson2 );

	CPerson* pNewPerson3 = new CPerson( "Jones", "Steve", "344-9865" );
	pDataBase->AddHead( pNewPerson3 );

	CPerson* pNewPerson4 = new CPerson( "Hart", "Mary", "287-0987" );
	pDataBase->AddHead( pNewPerson4 );

	CPerson* pNewPerson5 = new CPerson( "Meyers", "Brian", "236-1234" );
	pDataBase->AddHead( pNewPerson5 );

	TRACE( "  Return the completed database to main\n" );
	return pDataBase;
}

// OpenForReading - open a file for reading
//
CFile* OpenForReading( const CString& rFileName )
{
	CFile* pFile = new CFile;
	CFileException* theException = new CFileException;
	if ( !pFile->Open( rFileName, CFile::modeRead, theException ) )
	{
		delete pFile;
		TRACE( "  Threw file exception in OpenForReading\n" );
		THROW( theException );
	}
	delete theException;

	// Exit here if no exceptions
	return pFile;
}

// OpenForWriting - open a file for writing
//
CFile* OpenForWriting( const CString& rFileName )
{
	CFile* pFile = new CFile;
	CFileStatus status;
	UINT nAccess = CFile::modeWrite;

	// GetStatus will return TRUE if file exists,
	// or FALSE if it doesn't exist
	if ( !CFile::GetStatus( rFileName, status ) )
		nAccess |= CFile::modeCreate;
	
	CFileException* theException = new CFileException;
	if ( !pFile->Open( rFileName, nAccess, theException ) )
	{
		delete pFile;
		TRACE( "  Threw a file exception in OpenForWriting\n" );
		THROW( theException );
	}
	delete theException;
	
	// Exit here if no errors or exceptions
	TRACE( "  Opened file for writing OK\n" );
	return pFile;
}

// ReadDataBase - read data into a person list
//
CPersonList* ReadDataBase( CFile* pFile )
{
	CPersonList* pNewDataBase = NULL;

	// Create an archive from pFile for reading
	CArchive archive( pFile, CArchive::load );

	TRY
	{
		// and deserialize the new data base from the archive
		archive >> pNewDataBase;
	}
	CATCH( CArchiveException, theException )
	{
		TRACE( "  Caught an archive exception in ReadDataBase\n" );
#ifdef _DEBUG
		theException->Dump( afxDump );
#endif
		archive.Close();
	
		// If we got part of the database then delete it so we don't
		// have any Memory leaks
		if ( pNewDataBase != NULL )
		{
			pNewDataBase->DeleteAll();
			delete pNewDataBase;
		}
		THROW_LAST();
	}
	END_CATCH

	// Exit here if no errors or exceptions
	archive.Close();
	return pNewDataBase;
}

// WriteDataBase - write data from a person list to disk
//
BOOL WriteDataBase( CFile* pFile, CPersonList* pDataBase )
{
	// Create an archive from pFile for writing
	CArchive archive( pFile, CArchive::store );

	TRY
	{
		// and serialize the data base to the archive
		archive << pDataBase;
	}
	CATCH( CArchiveException, theException )
	{
		TRACE( "  Caught an archive exception in WriteDataBase\n" );
#ifdef _DEBUG
		theException->Dump( afxDump );
#endif
		archive.Close();
		THROW_LAST();
	}
	END_CATCH

	// Exit here if no errors or exceptions
	archive.Close();
	return TRUE;
}

// TestFindPerson - test CPersonList::FindPerson
//
void TestFindPerson( CPersonList* pDataBase )
{
	printf( "  Looking for the name Banipuli\n" );
	CPersonList* pFound = pDataBase->FindPerson( "Banipuli" );
	if ( pFound->IsEmpty() )
	{
		printf( "  No matching persons\n" );
	}
	else
	{
		printf( "  Found matching persons\n" );
#ifdef _DEBUG
		pFound->Dump( afxDump );
#endif
	}
	delete pFound;

	printf( "  Looking for the name Smith\n" );
	pFound = pDataBase->FindPerson( "Smith" );
	if ( pFound->IsEmpty() )
	{
		printf( "  No matching persons\n" );
	}
	else
	{
		printf( "  Found matching persons\n" );
#ifdef _DEBUG
		pFound->Dump( afxDump );
#endif
	}

	// Don't DeleteAll the found list since it
	//  shares CPerson objects with dataBase
	delete pFound; // Deletes only the list object
}

void ListDataBase( CPersonList* db )
{
	CPerson* pCurrent;
	POSITION pos;

	if ( db->GetCount() == 0 )
		printf( "  List is Empty\n" );
	else
	{
		printf( "  List contains:\n" );
		pos = db->GetHeadPosition();
		while ( pos != NULL )
		{
			pCurrent = (CPerson*)db->GetNext( pos );
			printf( "\t%s, %s\t%s\n", (const char*)pCurrent->GetLastName(),
					(const char*)pCurrent->GetFirstName(),
					(const char*)pCurrent->GetPhoneNumber() );
		}
	}
}
