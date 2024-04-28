// tcobject.cpp : This file contains code which deal with the respective
//      object functions.  The draw routine is listed here as
//      is the InsertNewObject, the edit, and play routines.
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


#include "resource.h"
#include "testclnt.h"
#include "defs.h"

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

static char szPrefix[] = "Test Client # ";
static int GLOBAL_nCurrentNumber;
extern CStdioFile *pOleDump;
static char szBuffer[80];

/////////////////////////////////////////////////////////////////////////////
// CTestClient OnInsertObject()
//
void CTestClient::OnInsertObject()
{
	char szTmp[CBOBJNAMEMAX];
	CString className;

	ASSERT(m_pClient != NULL);
	ASSERT(m_pItemTitle != NULL);

	if (!AfxOleInsertDialog(className))
	{
		if (m_bLogging)
		{
			ASSERT(pOleDump != NULL);
			wsprintf(szBuffer,
				"CTestClient::OnInsertObject:  No Server Selected\n");
			pOleDump->WriteString(szBuffer);
		}
		return;
	}

	TRY
	{
		if (m_pClient->m_lpObject != NULL)
		{
			m_pClient->Delete();
		}

		if (!m_pClient->CreateNewObject(className, 
			CreateNewUniqueName(szTmp)))
		{
			MessageBox("Failed to create object", "Test Client",
				MB_ICONEXCLAMATION);
			return;
		}
			
		if(!DrawObject())
		{
			MessageBox("Couldn't Draw Object!", "Test Client",
				MB_ICONEXCLAMATION);
			m_pClient->Delete();        // Delete the object here
		}
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

	// Set up Information bar's object title
	m_pItemTitle->SetWindowText(m_pClient->GetName());
	m_bUntitled = TRUE;
	m_bDirty = TRUE;
	Invalidate(TRUE);
}




/////////////////////////////////////////////////////////////////////////////
// CTestClient::FixObjectBounds(CRect& rect)
//
void CTestClient::FixObjectBounds(CRect& rect)
{
	CRect clientRect;
	
	GetClientRect(&clientRect);

	/* If we have an empty rectangle, start at default size */
	if (rect.IsRectEmpty())
	{
		rect.SetRect(0, 0, clientRect.right, clientRect.bottom);
	}
	else
	{
		// First map from HIMETRIC back to screen coordinates
		{
			CClientDC screenDC(NULL);

			short oldMode = screenDC.SetMapMode(MM_HIMETRIC);
			screenDC.LPtoDP(&rect);
			screenDC.SetMapMode(oldMode);
		}

		/* Preserve the Aspect Ratio of the picture */
		DWORD xDiff = (DWORD) (rect.right - rect.left + 1);
		DWORD yDiff = (DWORD) (rect.bottom - rect.top + 1);

		DWORD dwXDiff = (clientRect.right - clientRect.left + 1);
		DWORD dwYDiff = (clientRect.bottom - clientRect.top + 1);

		/* Don't use *= here because of integer arithmetic */
		if (xDiff >  dwXDiff || yDiff > dwYDiff)
		{
			if ((xDiff * dwYDiff) > (yDiff * dwXDiff))
			{
				yDiff = ((yDiff * dwXDiff) / xDiff);
				xDiff = dwXDiff;
			}
			else
			{
				xDiff = ((xDiff * dwYDiff) / yDiff);
				yDiff = dwYDiff;
			}
		}
		rect.SetRect(0, 0, (int)xDiff - 1, (int)yDiff - 1);
	}
}



LPSTR CreateNewUniqueName(LPSTR lpstr)
{
	wsprintf(lpstr, "%s%04d", (LPCSTR)szPrefix, GLOBAL_nCurrentNumber++);
	return(lpstr);
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient DrawObject()
//
BOOL CTestClient::DrawObject()
{
	CRect   rectBounds;
	BOOL bNotBlank;
	
	ASSERT(m_pClient != NULL);

	TRY
	{
		if (!(bNotBlank = m_pClient->GetBounds(&rectBounds)))
		{
			rectBounds.SetRectEmpty();
		}
	}
	CATCH (COleException, e)
	{
		if (m_bLogging)
		{
			LogError (THIS_FILE, e->m_status);
		}
		return FALSE;
	}
	END_CATCH
	
	FixObjectBounds(rectBounds);

	rectBounds.OffsetRect(2 * GetSystemMetrics(SM_CXFRAME),
					2 * GetSystemMetrics(SM_CYFRAME));


	TRY
	{
		if (bNotBlank)
		{
			if (m_pClient->GetType() == OT_EMBEDDED)
			{
				CString s = (m_pClient->GetName());
				m_pClient->SetHostNames(AfxGetAppName(), s);
				CDC *pDC = GetDC();
				PrepareDC(pDC);
				if (!m_pClient->Draw(pDC, rectBounds, NULL, pDC))
				{
					MessageBox("Draw Problem with Embedded Item", 
						"Test Client", MB_ICONEXCLAMATION);
					ReleaseDC(pDC);
					return FALSE;
				}
				ReleaseDC(pDC);
			}
			
			/* If the object is a link... */
			if (m_pClient->GetType() == OT_LINK)
			{
				CDC *pDC = GetDC();
				PrepareDC(pDC);
				if (!m_pClient->Draw(pDC, rectBounds, NULL, pDC))
				{
					MessageBox("Draw Problem with Linked Item", 
						"Test Client", MB_ICONEXCLAMATION);
					ReleaseDC(pDC);
					return FALSE;
				}
				ReleaseDC(pDC);
			}
		}
	}
	CATCH (COleException, e)
	{
		if (m_bLogging)
		{
			LogError (THIS_FILE, e->m_status);
		}
		return FALSE;
	}
	END_CATCH
	
	// Regenerate Objects Clipboard Formats
	
	if (m_pObjectFormat == NULL)
	{
		return TRUE;
	}

	m_pObjectFormat->ResetContent();

	OLECLIPFORMAT wCurrentFormat, wFormat;

	wCurrentFormat = 0;

	while ((wFormat = m_pClient->EnumFormats(wCurrentFormat)) != 0)
	{
		int nCnt = GetClipboardFormatName(wFormat, szBuffer, sizeof(szBuffer));

		if (nCnt == 0)
		{
			if (wFormat & CF_OWNERDISPLAY)
			{
				strcpy(szBuffer, szOwnerFormat[wFormat-CF_OWNERDISPLAY]);
			}
			else
			{
				strcpy(szBuffer, szDefinedFormat[wFormat-CF_TEXT]);
			}
		}
		m_pObjectFormat->AddString(szBuffer);
		wCurrentFormat = wFormat;
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestClient OnEdit()
//
void CTestClient::DoVerb(UINT nVerb)
{

	ASSERT (m_pClient != NULL);

	TRY
	{
		if (m_pClient->GetType() == OT_STATIC)
		{
			return;
		}
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

	CRect   rect;
	GetClientRect(&rect);

	TRY
	{
		m_pClient->Activate(nVerb, TRUE, TRUE, this, &rect);
	}
	CATCH (COleException, e)
	{
		// error when activating
		MessageBox("Error Activating Server to Edit", "Test Client",
			MB_ICONEXCLAMATION);
		if (m_bLogging)
		{
			LogError (THIS_FILE, e->m_status);
		}
		return;
	}
	END_CATCH
	Invalidate(TRUE);
}



