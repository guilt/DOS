// tsfile.cpp : This file contains all code dealing with File I/O.  It
//        contains the serialization routines as well as the 
//            commdlg file routines, and load/save file routines.
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

#include <afxdlgs.h>

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

extern void OutputLog(const char* pText);
static char szBuffer[80];


/////////////////////////////////////////////////////////////////////////////
// CTestServer FileDlg
//
BOOL CTestServer::FileDlg( BOOL bOpen, int nMaxFile, LPSTR szFile)
{
	char szFilter[] = "Test OLE Files (*.ols)|*.ols||";

	CFileDialog dlg(bOpen, "ols", NULL, 
		OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, szFilter);
	
	::GetFileTitle(szFile, szFile, nMaxFile);
	dlg.m_ofn.lpstrFile = szFile;
	dlg.m_ofn.nMaxFile = nMaxFile;

	return dlg.DoModal() == IDOK ? TRUE : FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer OnOpen()
//
void CTestServer::OnOpen()
{
	extern CString GLOBAL_szFileName;

	ASSERT_VALID (this);

	if (!FileDlg(TRUE, FILENAMELEN, 
		GLOBAL_szFileName.GetBuffer(FILENAMELEN)))
	{
		if (m_bLogging)
		{
			OutputLog("CTestServer::OnOpen : Cancelling due to invalid filename\n");
		}
		return;
	}

	GLOBAL_szFileName.ReleaseBuffer();


	if (!LoadFile(GLOBAL_szFileName))
	{
		return;
	}

	m_szFileName = GLOBAL_szFileName;
	m_bUntitled = FALSE;

	m_pList->ResetContent();
	m_pList->AddString(m_pItem->m_Text);
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer LoadFile(const char* pName)
//
BOOL CTestServer::LoadFile(const char* pName)
{
	CFile file;

	ASSERT_VALID(this);
	ASSERT(strlen(pName) != 0);
	
	if (!file.Open(pName, CFile::modeRead | CFile::shareDenyWrite))
	{
		MessageBox("Not able to open file.","Test Server",
			MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
		
		if (m_bLogging)
		{
			wsprintf(szBuffer, 
				"CTestServer::Load File : Couldn't Open File %s\n",
				(LPCSTR)pName);
				OutputLog(szBuffer);
		}
		return FALSE;
	}

	// Set up a CArchive to serialize in the data.
	//
	CArchive ar(&file, CArchive::load);

	TRY
	{
		Serialize(ar); // a way to serialize in data
	}
	CATCH(CFileException, e)
	{
		MessageBox("Not able to read from file.", "Test Server",
			MB_ICONEXCLAMATION | MB_OK);

		ar.Close();
		file.Close();

		if (m_bLogging)
		{
			OutputLog("Have caught a CFileException during loading\n");
		}
		return FALSE;
	}
	END_CATCH
	m_bDirty = FALSE;
	m_pItem->m_pOwner = this;
	m_pDoc->m_pItem = m_pItem;

	extern BOOL GLOBAL_bEmbedded;
	if (!GLOBAL_bEmbedded)
	{
		m_pDoc->NotifyRename(pName);
	}
	m_pItem->SetDocName(pName);
			   
	ar.Close();
	file.Close();

	char szBuf[32], szCaption[80];  
	::GetFileTitle(pName, szBuf, sizeof(szBuf));
	wsprintf(szCaption,"%s - %s", (LPCSTR)AfxGetAppName(), (LPCSTR)szBuf);
	SetWindowText(szCaption);

	return TRUE;
}
		


/////////////////////////////////////////////////////////////////////////////
// CTestServer Serialize(CArchive &ar)
//
void CTestServer::Serialize(CArchive &ar)
{
	ASSERT_VALID(this);
	WORD wStartFile = 0xAFC1;  // Private Start-of-File marker

	if (ar.IsStoring())
	{
		ar << wStartFile;
			// note that COleClient::Serialize should be called after this
		ar << m_pItem;
	}
	else
	{
		WORD wNew;
		ar >> wNew;
		if (wNew != wStartFile)
		{
			AfxThrowFileException(CFileException::invalidFile);
			return;     // Not our file, don't read it
		}

		ar >> m_pItem;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTestServer SaveFile()
//
void CTestServer::SaveFile (BOOL bNewFileName)
{
	CFile file;
	WORD wStartFile;
	wStartFile = 0xAFC1;  // Private Start-Of-File marker
	
	if (bNewFileName)
	{
		if (m_bUntitled)
		{
			// set up a default name
			m_szFileName = "testserv.ols";
		}


		if (!FileDlg(FALSE, FILENAMELEN, 
			m_szFileName.GetBuffer(FILENAMELEN)))
		{
			if (m_bLogging)
			{
				OutputLog("CTestServer::SaveFile : Cancelling due to invalid filename\n");
			}
			return;
		}
		m_szFileName.ReleaseBuffer();

		ASSERT(m_szFileName.GetLength() != 0);
	}

	if (!file.Open(m_szFileName, CFile::modeCreate | CFile::modeWrite))
	{
		MessageBox("Not able to create file.", "Test Server",
			MB_ICONEXCLAMATION | MB_OK);

		if (m_bLogging)
		{
			wsprintf(szBuffer, 
				"CTestServer::SaveFile : Couldn't Open File %s\n",
					(LPCSTR)m_szFileName);
			OutputLog(szBuffer);
		}
		return;
	}
	
	// Write out the contents of the buffer to the file.
	// If this fails, inform the user.
	//
	TRY
	{
		CArchive ar(&file,CArchive::store);
		ar << wStartFile;
		ar << m_pItem;
		ar.Close();
	}
	CATCH(CFileException, e)
	{
		file.Close();
		MessageBox("Not able to write to file.", "Test Server",
			MB_ICONEXCLAMATION | MB_OK);

		if (m_bLogging)
		{
			OutputLog("CTestServer::SaveFile : Caught archive exception while archiving file\n");
		}
		return;
	}
	END_CATCH
	
	file.Close();

	TRY
	{
		m_pDoc->NotifySaved();
		if (bNewFileName)
		{
			m_pDoc->NotifyRename(m_szFileName);
			m_pItem->SetDocName(m_szFileName);
		}
	}
	CATCH (COleException, e)
	{
		if (m_bLogging)
		{
			LogError (THIS_FILE, e->m_status);
		}

		MessageBox("Exception Thrown Will Reporting Save to Library",
			"Test Server", MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH

	m_bUntitled = FALSE;
	m_bDirty = FALSE;

	char szBuf[80];
	wsprintf(szBuf,"%s - %s", (LPCSTR)AfxGetAppName(), (LPCSTR)m_szFileName);
	SetWindowText(szBuf);
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer OnSave()
//
void CTestServer::OnSave()
{
	ASSERT_VALID (this);
	SaveFile(m_bUntitled);
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer OnSaveAs()
//
void CTestServer::OnSaveAs()
{
	ASSERT_VALID(this);
	SaveFile(TRUE);
}


