// error.cpp -- This file contains definitions and code which return
//      error values from OLE.
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

#include "testserv.h"
#include "resource.h"
#include "defs.h"

extern CStdioFile *pOleDump;
static char szBuffer[80];

struct oleStrings
{
	short nError;
	char* szError;
};

static oleStrings oleErrors[] =
{
	{  0, "OLE_OK" },                     
	{  1, "OLE_WAIT_FOR_RELEASE" },
	{  2, "OLE_BUSY" },          
	{  3, "OLE_ERROR_PROTECT_ONLY" },     
	{  4, "OLE_ERROR_MEMORY" },           
	{  5, "OLE_ERROR_STREAM" },           
	{  6, "OLE_ERROR_STATIC" },           
	{  7, "OLE_ERROR_BLANK" },            
	{  8, "OLE_ERROR_DRAW" },             
	{  9, "OLE_ERROR_METAFILE" },         
	{ 10, "OLE_ERROR_ABORT" },            
	{ 11, "OLE_ERROR_CLIPBOARD" },        
	{ 12, "OLE_ERROR_FORMAT" },           
	{ 13, "OLE_ERROR_OBJECT" },           
	{ 14, "OLE_ERROR_OPTION" }, 
	{ 15, "OLE_ERROR_PROTOCOL" },         
	{ 16, "OLE_ERROR_ADDRESS" },          
	{ 17, "OLE_ERROR_NOT_EQUAL" },        
	{ 18, "OLE_ERROR_HANDLE" },           
	{ 19, "OLE_ERROR_GENERIC" },          
	{ 20, "OLE_ERROR_CLASS" },            
	{ 21, "OLE_ERROR_SYNTAX" },           
	{ 22, "OLE_ERROR_DATATYPE" },         
	{ 23, "OLE_ERROR_PALETTE" },          
	{ 24, "OLE_ERROR_NOT_LINK" },         
	{ 25, "OLE_ERROR_NOT_EMPTY" },        
	{ 26, "OLE_ERROR_SIZE" },             
	{ 27, "OLE_ERROR_DRIVE" },            
	{ 28, "OLE_ERROR_NETWORK" },          
	{ 29, "OLE_ERROR_NAME" },             
	{ 30, "OLE_ERROR_TEMPLATE" },         
	{ 31, "OLE_ERROR_NEW" },              
	{ 32, "OLE_ERROR_EDIT" },             
	{ 33, "OLE_ERROR_OPEN" },             
	{ 34, "OLE_ERROR_NOT_OPEN" },         
	{ 35, "OLE_ERROR_LAUNCH" },           
	{ 36, "OLE_ERROR_COMM" },             
	{ 37, "OLE_ERROR_TERMINATE" },        
	{ 38, "OLE_ERROR_COMMAND" },          
	{ 39, "OLE_ERROR_SHOW" },             
	{ 40, "OLE_ERROR_DOVERB" },           
	{ 41, "OLE_ERROR_ADVISE_NATIVE" },    
	{ 42, "OLE_ERROR_ADVISE_PICT" },      
	{ 43, "OLE_ERROR_ADVISE_RENAME" },    
	{ 44, "OLE_ERROR_POKE_NATIVE" },      
	{ 45, "OLE_ERROR_REQUEST_NATIVE" },   
	{ 46, "OLE_ERROR_REQUEST_PICT" },     
	{ 47, "OLE_ERROR_SERVER_BLOCKED" },   
	{ 48, "OLE_ERROR_REGISTRATION" },     
	{ 49, "OLE_ERROR_ALREADY_REGISTERED" },
	{ 50, "OLE_ERROR_TASK" },             
	{ 51, "OLE_ERROR_OUTOFDATE" },        
	{ 52, "OLE_ERROR_CANT_UPDATE_CLIENT" },
	{ 53, "OLE_ERROR_UPDATE" },           
	{ 1000, "OLE_WARN_DELETE_DATA" }
};
								


static oleStrings oleMethods[] =
{
	{  1, "OLE_NONE" },      
	{  2, "OLE_DELETE" },             
	{  3, "OLE_LNKPASTE" },           
	{  4, "OLE_EMBPASTE" },           
	{  5, "OLE_SHOW" },               
	{  6, "OLE_RUN" },                
	{  7, "OLE_ACTIVATE" },           
	{  8, "OLE_UPDATE" },             
	{  9, "OLE_CLOSE" },              
	{ 10, "OLE_RECONNECT" },          
	{ 11, "OLE_SETUPDATEOPTIONS" },   
	{ 12, "OLE_SERVERUNLAUNCH" },     
	{ 13, "OLE_LOADFROMSTREAM" },     
	{ 14, "OLE_SETDATA" },            
	{ 15, "OLE_REQUESTDATA" },        
	{ 16, "OLE_OTHER" },              
	{ 17, "OLE_CREATE" },             
	{ 18, "OLE_CREATEFROMTEMPLATE" }, 
	{ 19, "OLE_CREATELINKFROMFILE" }, 
	{ 20, "OLE_COPYFROMLNK" },        
	{ 21, "OLE_CREATEFROMFILE" },     
};



void CTestServer::LogError ( char *pszFileName, int nStatus)
{
	ASSERT_VALID(this);
	ASSERT(pOleDump != NULL);

	wsprintf(szBuffer, "An %s Exception has been Thrown in:  %s\n", 
		(LPCSTR)oleErrors[nStatus].szError, (LPCSTR)pszFileName);
	pOleDump->WriteString(szBuffer);            
}



void OutputLog (const char* pText)
{
	ASSERT(pOleDump != NULL);
	pOleDump->WriteString(pText);
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnLogging()
//
void CTestServer::OnLogging()
{
	CMenu *pMenu;
	pMenu = GetMenu();
	ASSERT_VALID (this);

	if (m_bLogging)
	{
		ASSERT (pOleDump != NULL);
		pMenu->CheckMenuItem(IDM_LOGGING, MF_UNCHECKED);
		pOleDump->Flush();
		pOleDump->Close();
		delete pOleDump;
		m_bLogging = !m_bLogging;
	}
	else
	{
		pMenu->CheckMenuItem(IDM_LOGGING, MF_CHECKED);
		pOleDump = new CStdioFile();
		if (!pOleDump->Open("testserv.log", CFile::typeText | 
			CFile::modeWrite | CFile::modeCreate))
		{
			TRACE("Logging File TESTSERV.LOG not opened\n");
		}
		else
		{
			m_bLogging = !m_bLogging;
		}
	}
}

