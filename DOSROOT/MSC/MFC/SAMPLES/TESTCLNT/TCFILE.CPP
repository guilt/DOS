// tcfile.cpp : This file contains all code dealing with File I/O.  It
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


#include "testclnt.h"
#include "defs.h"
#include "resource.h"

#include "afxdlgs.h"

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;


extern CStdioFile *pOleDump;
static char szBuffer[80];


/////////////////////////////////////////////////////////////////////////////
// CTestClient FileDlg
//
BOOL CTestClient::FileDlg( BOOL bOpen, int nMaxFile, LPSTR szFile)
{
	char szFilter[] = "Test OLE Files (*.ole)|*.ole||";
	CFileDialog dlg(bOpen, "ole", NULL, 
		OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, szFilter);
	
	::GetFileTitle(szFile, szFile, nMaxFile); // trim input to just filename
	dlg.m_ofn.lpstrFile = szFile;
	dlg.m_ofn.nMaxFile = nMaxFile;

	return dlg.DoModal() == IDOK ? TRUE : FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient OnFileOpen()
//
void CTestClient::OnFileOpen()
{
	extern CString GLOBAL_szFile;

	ASSERT(m_pClient != NULL);
	ASSERT(m_pItemTitle != NULL);


	if (!QuerySaveChanges())
	{
		return;     // check to save changes
	}

	if (!FileDlg(TRUE, FILENAMELEN, 
		GLOBAL_szFile.GetBuffer(FILENAMELEN)))
	{
		return;
	}

	GLOBAL_szFile.ReleaseBuffer();

	if (m_pClient->m_lpObject != NULL)
	{
		TRY
		{
			m_pClient->Delete();
		}
		CATCH (COleException, e)
		{
			if (m_bLogging)
			{
				LogError (THIS_FILE, e->m_status);
			}
			return;
		}
		END_CATCH
	}

	if (!LoadFile(((const char *)GLOBAL_szFile)))
	{
		m_pItemTitle->SetWindowText("");
		Invalidate(TRUE);
		return;
	}

	m_szFileName = GLOBAL_szFile;

	// Set up Information bar's object title
	m_pItemTitle->SetWindowText(m_pClient->GetName());
	m_bUntitled = FALSE;
	Invalidate(TRUE);
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient LoadFile(const char* pName)
//
BOOL CTestClient::LoadFile(const char* pName)
{
	CFile file;

	ASSERT(strlen(pName) != 0);
	
	if (!file.Open(pName, CFile::modeRead | CFile::shareDenyWrite))
	{
		MessageBox("Not able to open file.","Test Client",
			MB_ICONEXCLAMATION | MB_OK);

		if (m_bLogging)
		{
			ASSERT(pOleDump != NULL);
			pOleDump->WriteString("CTestClient::Unable to Open File\n");
		}
		return FALSE;
	}

	// Set up a CArchive to serialize in the data.
	//
	CArchive ar(&file, CArchive::load);

	TRY
	{
		Serialize(ar); 
	}
	CATCH(CFileException, e)
	{
		MessageBox("Not able to read from file.", "Test Client",
			MB_ICONEXCLAMATION | MB_OK);
		if (m_bLogging)
		{
			ASSERT(pOleDump != NULL);
			pOleDump->WriteString("Caught an Exception while Reading From File\n");
		}
		ar.Close();
		file.Close();
		return FALSE;
	}
	END_CATCH

	ar.Close();
	file.Close();
	m_bDirty = FALSE;
	m_bRevertAvailable = TRUE;
	return TRUE;
}
		


/////////////////////////////////////////////////////////////////////////////
// CTestClient Serialize(CArchive &ar)
//
void CTestClient::Serialize(CArchive &ar)
{
	WORD wStartFile;  // a private word format to signify start of file
	wStartFile = 0xAFC0;
		
	if (ar.IsStoring())
	{
		ar << wStartFile;
			// note that COleClient::Serialize is called after this
			// in the CTestClient::SaveFile routine
	}
	else
	{
		WORD wNew;
		ar >> wNew;

		if (wNew != wStartFile)
		{
			AfxThrowFileException(CFileException::invalidFile);
			return;
		}

		TRY
		{
			m_pClient->Serialize(ar);
		}
		CATCH (COleException, e)
		{
			if (m_bLogging)
			{
				LogError (THIS_FILE, e->m_status);
			}
			return;
		}
		END_CATCH
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTestClient SaveFile()
//
void CTestClient::SaveFile (BOOL bNewFileName)
{
	CFile file;
	WORD wStartFile;    // a private word format to signify start of file
	wStartFile = 0xAFC0;
	
	ASSERT(m_pClient != NULL);
	ASSERT(m_pDoc != NULL);

	if (bNewFileName)
	{
		if (m_bUntitled)
		{
			// set up a default name
			m_szFileName = "testclnt.ole";
		}


		if (!FileDlg(FALSE, FILENAMELEN, 
			m_szFileName.GetBuffer(FILENAMELEN)))
		{
			return;
		}
		m_szFileName.ReleaseBuffer();

		ASSERT(m_szFileName.GetLength() != 0);
	}

	if (!file.Open(m_szFileName, CFile::modeCreate | CFile::modeWrite))
	{
		MessageBox("Not able to create file.", "Test Client",
			MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	
	// Write out the contents of the buffer to the file.
	// If this fails, inform the user.
	//
	TRY
	{
		CArchive ar(&file, CArchive::store);
		ar << wStartFile;
		m_pClient->Serialize(ar);
		ar.Close();
	}
	CATCH(CFileException, e)
	{
		file.Close();
		MessageBox("Not able to write to file.", "TestClient",
			MB_ICONEXCLAMATION | MB_OK);
		if (m_bLogging)
		{
			ASSERT(pOleDump != NULL);
			pOleDump->WriteString("Caught an Exception while writing file\n");
		}
		return;
	}
	END_CATCH

	TRY
	{
		m_pDoc->NotifySaved();
	}
	CATCH (COleException, e)
	{
		if (m_bLogging)
		{
			LogError (THIS_FILE, e->m_status);
		}

		MessageBox("Exception thrown while reporting save to library",
			"Test Client", MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH
	m_bUntitled = FALSE;
	m_bDirty = FALSE;
	m_bRevertAvailable = TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient OnFileSave()
//
void CTestClient::OnFileSave()
{
	SaveFile(m_bUntitled);
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient OnFileSave()
//
void CTestClient::OnFileSaveAs()
{
	SaveFile(TRUE);
}


/////////////////////////////////////////////////////////////////////////////
// CTestClient::OnChanged()
//
void CTestClient::OnChanged()
{
	Invalidate(TRUE);
	m_bDirty = TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient::OnRevert()
//
void CTestClient::OnRevert()
{
	if (!m_bRevertAvailable)
	{
		return;
	}
	
	TRY
	{
		m_pClient->Delete();
	}
	CATCH (COleException, e)
	{
		MessageBox("Unable to Remove Current Item to Revert", "Test Client",
			MB_ICONEXCLAMATION);
		return;
	}
	END_CATCH

	LoadFile(((const char *)m_szFileName));

	m_pDoc->NotifyRevert();
	m_bRevertAvailable = FALSE;
	m_bDirty = FALSE;
	Invalidate(TRUE);
}

