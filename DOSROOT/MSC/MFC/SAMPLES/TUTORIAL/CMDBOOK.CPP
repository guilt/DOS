// cmdbook.cpp : A character interface to the CPerson Databaes
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

#include <iostream.h>
#include <afx.h>
#include <afxcoll.h>

// Define the database class to handle all the transactions for us
#include "database.h"

#define INPUTSIZE 80

// This viewer can only handle on database at a time so we declare it
// globally to simplify the code
CDataBase db;

// Command Function prototypes
BOOL OnNew();
BOOL OnOpen();
BOOL OnAdd();
BOOL OnEnd();
BOOL OnHelp();
BOOL OnFind();
BOOL OnList();
BOOL OnSave();
BOOL OnQuit();
BOOL OnWrite();

// Helper Function prototypes
BOOL CheckFile();
BOOL Save( BOOL bNamed = FALSE );

struct commandmap
{
	char* verb;
	char* description;
	BOOL (*cmd)();
};

// A static array that contains the the commandmap structure.  There is
// one structure per command.  Each structure contains the text of the
// command, the help text for that command, and the address of the function
// that performs that command.
//
static commandmap commands[] =
{
	{ "help",  "displays this text",                              OnHelp },
	{ "new",   "creates a new database for entry",                OnNew },
	{ "open",  "opens a file on the disk",                        OnOpen },
	{ "quit",  "leaves the program without saving the book file", OnQuit },
	{ "add",   "adds a new person to the book file",              OnAdd },
	{ "end",   "saves the book file and leaves the program",      OnEnd },
	{ "find",  "finds all people with a given last name",         OnFind },
	{ "list",  "lists the people in the book file",               OnList },
	{ "save",  "saves the book file",                             OnSave },
	{ "write", "saves the book file to a new filename",           OnWrite },
	{ NULL  ,   "matches any verb and displays help",             OnHelp }
};

/////////////////////////////////////////////////////////////////////////////
//  The command functions

//////////////////////////////////////////////////
//  OnNew
//  Checks to see if the current list should be saved and then
//  allocations a new list.
//
BOOL OnNew()
{
	if ( CheckFile() )
		db.New();
	
	return TRUE;
}

//////////////////////////////////////////////////
//  OnOpen
//  Checks to see if the current list should be saved and then
//  open a new file using the filename provided by the user.
//
BOOL OnOpen()
{
	if ( CheckFile() )
	{
		CString bookfile;
	
		cout << "book file: ";
		cin >> bookfile.GetBuffer( INPUTSIZE ); bookfile.ReleaseBuffer();
	
		TRY
		{
			db.DoOpen( bookfile );
		}
		CATCH( CFileException, e )
		{
			cout << "Not able to open " << bookfile << " as a database\n";
		}
		AND_CATCH( CArchiveException, e )
		{
			cout << "Not able to open " << bookfile << " as a database\n";
		}
		END_CATCH
	
		return OnList();
	}
	else
		return TRUE;
}

//////////////////////////////////////////////////
//  OnAdd
//  Add a person into the current list.
//
BOOL OnAdd()
{
	if ( !db.IsPresent() )
	{
		cout << "There is no current database to add to.\n";
		return FALSE;
	}
	
	CPerson* p = new CPerson();
	CString input;

	cout << "last name:";
	cin >> input.GetBuffer( INPUTSIZE ); input.ReleaseBuffer();
	p->SetLastName( input );

	cout << "first name:";
	cin >> input.GetBuffer( INPUTSIZE ); input.ReleaseBuffer();
	p->SetFirstName( input );

	cout << "phone number (no spaces):";
	cin >> input.GetBuffer( INPUTSIZE ); input.ReleaseBuffer();
	p->SetPhoneNumber( input );

	db.AddPerson( p );

	return TRUE;
}

//////////////////////////////////////////////////
//  OnEnd
//  End the program saving the file.
//
BOOL OnEnd()
{
	if ( db.IsDirty() )
		if ( !Save( db.IsNamed() ) )
		{
			cout << "An error occurred while saving file!  Abort Program[y/n]?";
			CString answer;
			cin >> answer.GetBuffer( INPUTSIZE );
			answer.ReleaseBuffer();
			answer.MakeUpper();
			if ( answer[0] == 'N' )
				return TRUE;
		}
	
	return FALSE;
}

//////////////////////////////////////////////////
//  OnFind
//  Gets filter text from the user and then lists all the
//  CPerson objects that match that filter.  Note that after
//  it calls OnList it calls DoFind with no input clearing the
//  stored find list.
//
BOOL OnFind()
{
	if ( !db.IsPresent() )
	{
		cout << "There is no current database to search.\n";
		return FALSE;
	}
	
	CString lastname;

	cout << "find last name: ";
	cin >> lastname.GetBuffer( INPUTSIZE ); lastname.ReleaseBuffer();

	db.DoFind( lastname );
	OnList();
	db.DoFind();

	return TRUE;
}

//////////////////////////////////////////////////
//  OnHelp
//  Displays the text for all the command verbs followed by
//  their help strings.
//
BOOL OnHelp()
{
	commandmap* cmd;

	cout << "available commands are:\n";

	for ( cmd = commands; cmd->verb != NULL; cmd++ )
		cout << "\t" << cmd->verb << "\t" << cmd->description << "\n";

	return TRUE;
}

//////////////////////////////////////////////////
//  OnList
//  Iterates over the list writing each CPerson object out
//  to cout.
//
BOOL OnList()
{

	if ( !db.IsPresent() )
	{
		cout << "There is no current database to list.\n";
	}
	else
	{
		CPerson* pCurrent;
		
		cout << "  List contains:\n";
		for ( int i = 0; i < db.GetCount(); i++ )
		{
			pCurrent = db.GetPerson( i );
			cout << '\t' << pCurrent->GetLastName() << ", " <<
					pCurrent->GetFirstName() << '\t' <<
					pCurrent->GetPhoneNumber() << '\n';
		}
	}
	return TRUE;
}

//////////////////////////////////////////////////
//  OnSave
//  Saves the database with the current name.  If there is no
//  current name then the user will be prompted for one.
//
BOOL OnSave()
{
	if ( !Save( db.IsNamed() ) )
	{
		cout << "An error occurred while saving file!  Abort Program[y/n]?";
		CString answer;
		cin >> answer.GetBuffer( INPUTSIZE );
		answer.ReleaseBuffer();
		answer.MakeUpper();
		if ( answer[0] == 'Y' )
			return FALSE;
	}
	
	return TRUE;
}

//////////////////////////////////////////////////
//  OnQuit
//  Quits the program without saving changes to the database.
//
BOOL OnQuit()
{
	return FALSE;
}

//////////////////////////////////////////////////
//  OnWrite
//  Gets a filename from the user and writes the database
//  to the file.
//
BOOL OnWrite()
{
	if ( !Save() )
	{
		cout << "An error occurred while saving file!  Abort Program[y/n]?";
		CString answer;
		cin >> answer.GetBuffer( INPUTSIZE );
		answer.ReleaseBuffer();
		answer.MakeUpper();
		if ( answer[0] == 'Y' )
			return FALSE;
	}
	
	return TRUE;
}

//////////////////////////////////////////////////
//  CheckFile
//  Determines if there currently is a database that needs
//  to be saved.  If so it calls Save.
//
BOOL CheckFile()
{
	if ( db.IsDirty() )
	{
		CString answer;
		cout << "Save File[ync] " << db.GetName();
		cin >> answer.GetBuffer( INPUTSIZE );
		answer.ReleaseBuffer();
		answer.MakeUpper();
		if ( answer[0] == 'Y' )
		{
			if ( !Save( db.IsNamed() ) )
				return FALSE;
		}
		else if ( answer[0] == 'C' )
			return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////
//  Save
//  If provided with a name it saves the database to that file
//  otherwise it prompts the user for a name to save to.
//
BOOL Save( BOOL bNamed /* = FALSE */ )
{
	if ( !db.IsPresent() )
	{
		cout << "But you don't have a database to save.\n";
		return FALSE;
	}
	TRY
	{
		if ( bNamed )
			db.DoSave();
		else
		{
			CString strFileName;
			cout << "write to file: ";
			cin >> strFileName.GetBuffer( INPUTSIZE );
			strFileName.ReleaseBuffer();
			db.DoSave( strFileName );
		}
	}
	CATCH( CFileException, e )
	{
		cout << "File Save Error ->" << e->m_lOsError << " while saving "
				<< db.GetName() << '\n';
		return FALSE;
	}
	AND_CATCH( CArchiveException, e )
	{
		cout << "Archive Write while saving " << db.GetName() << '\n';
		return FALSE;
	}
	END_CATCH
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//  main
//  Loops until the global bLeave is set to TRUE.  It processes commands
//  by iterating through the list until either the text matches or the
//  the end of the command list is hit.  If a match is found the the
//  command function is called otherwise an error is displayed and
//  OnHelp is called.
//
void main()
{
	commandmap* finder;
	CString strVerb;

	do
	{
		cout << db.GetName() << " - command: ";
		cin >> strVerb.GetBuffer( INPUTSIZE );
		strVerb.ReleaseBuffer();

		finder = commands;
		while (finder->verb != NULL && finder->verb != strVerb )
			finder++;

		if ( finder->verb == NULL )
			cout << "command \"" << strVerb << "\" is not known.\n";

	} while ( (*finder).cmd() );

	db.Terminate();

	return;
}
