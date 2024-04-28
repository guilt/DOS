// clipbd.cpp : This file contains code which implements functions
//  specific to the clipboard.
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

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

extern void OutputLog (const char* pText);
extern UINT GLOBAL_uNativeFormat, GLOBAL_uOwnerFormat, GLOBAL_uObjectFormat;

/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnCopyLink()
//
void CTestServer::OnCopyLink()
{
	ASSERT_VALID(this);
	if (!OpenClipboard())
	{
		MessageBox ("Unable to Open Clipboard", "Test Server",
			MB_ICONEXCLAMATION);

		if (m_bLogging)
		{
			OutputLog("CTestServer::OnCopyLink : Unable to Open Clipboard\n");
		}
		return;
	}

	EmptyClipboard();

	// copy the text into a memory block so it can be put on the
	// clipboard.

	HANDLE hText;
	CString stringText;
	LPSTR lpTextLock;
	
	ASSERT(m_pItem != NULL);
	m_pItem->OnGetTextData(stringText);
	hText = ::GlobalAlloc (GMEM_DDESHARE | GHND, stringText.GetLength()+1);
	lpTextLock = (LPSTR) ::GlobalLock(hText);

	for (int i=0; i<stringText.GetLength(); i++)
	{
		*lpTextLock++ = stringText[i];
	}

	*lpTextLock++ = '\0';

	::GlobalUnlock (hText);

	TRY
	{
		// Here we will set up the appropriate linking formats
		SetClipboardData (CF_TEXT, hText);
		SetClipboardData (CF_METAFILEPICT, m_pItem->GetMetafileData());
		SetClipboardData (GLOBAL_uNativeFormat, m_pItem->GetNativeData());
		SetClipboardData (GLOBAL_uOwnerFormat, m_pItem->GetLinkData());
		SetClipboardData (GLOBAL_uObjectFormat, m_pItem->GetLinkData());
	}
	CATCH (COleException, e)
	{
		if (m_bLogging)
		{
			LogError(THIS_FILE, e->m_status);
		}
	}
	END_CATCH
	CloseClipboard();
}



/////////////////////////////////////////////////////////////////////////////
// CTestServer::OnCopyObject()
//
void CTestServer::OnCopyObject()
{
	ASSERT_VALID(this);

	if (!OpenClipboard())
	{
		MessageBox ("Unable to Open Clipboard", "Test Server",
			MB_ICONEXCLAMATION);
		
		if (m_bLogging)
		{
			OutputLog("CTestServer::OnCopyObject : Couldn't Open Clipboard\n");
		}
		return;
	}

	EmptyClipboard();

	// Here we will set up the appropriate embedding formats
	HANDLE hText;
	CString stringText;
	LPSTR lpTextLock;
	
	ASSERT(m_pItem != NULL);
	m_pItem->OnGetTextData(stringText);
	hText = ::GlobalAlloc (GMEM_DDESHARE | GHND, stringText.GetLength()+1);
	lpTextLock = (LPSTR) ::GlobalLock(hText);

	for (int i=0; i<stringText.GetLength(); i++)
	{
		*lpTextLock++ = stringText[i];
	}

	*lpTextLock++ = '\0';

	::GlobalUnlock (hText);

	TRY
	{
		// Here we will set up the appropriate linking formats
		SetClipboardData (CF_TEXT, hText);
		SetClipboardData (CF_METAFILEPICT, m_pItem->GetMetafileData());
		SetClipboardData (GLOBAL_uNativeFormat, m_pItem->GetNativeData());
		SetClipboardData (GLOBAL_uOwnerFormat, m_pItem->GetLinkData());
	}
	CATCH (COleException, e)
	{
		if (m_bLogging)
		{
			LogError(THIS_FILE, e->m_status);
		}
	}
	END_CATCH
	CloseClipboard();
}
