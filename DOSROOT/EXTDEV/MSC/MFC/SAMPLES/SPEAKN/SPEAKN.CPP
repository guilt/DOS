// speakn.cpp : Defines the class behaviors for the SpeakN application.
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
//

#include "speakn.h"
#include <mmsystem.h>

/////////////////////////////////////////////////////////////////////////////
// Sound helpers

static void PlaySound(LPCSTR lpszSound)
{
	HRSRC hRes; // resource handle to wave file
	HGLOBAL hData;
	BOOL bOk = FALSE;
	if ((hRes = ::FindResource(AfxGetResourceHandle(), lpszSound,
	  "sound")) != NULL &&
	  (hData = ::LoadResource(AfxGetResourceHandle(), hRes)) != NULL)
	{
		// found the resource, play it
		bOk = sndPlaySound((LPCSTR)::LockResource(hData),
			SND_MEMORY|SND_SYNC|SND_NODEFAULT);
		FreeResource(hData);
	}
	if (!bOk)
		AfxGetApp()->m_pMainWnd->MessageBox("Can't play sound");
}

inline static void PlaySound(UINT nIDS)
	{ PlaySound(MAKEINTRESOURCE(nIDS)); }

/////////////////////////////////////////////////////////////////////////////
// CSpeakNDlg

BEGIN_MESSAGE_MAP(CSpeakNDlg, CModalDialog)
	ON_COMMAND(IDC_REPLAY_SOUND, OnReplaySound)
	ON_COMMAND(IDC_GIVE_UP, OnGiveUp)
	ON_COMMAND(IDC_PICTURE, OnReplaySound)
	ON_EN_CHANGE(IDC_INPUT_EDIT, OnUpdateStatus)
END_MESSAGE_MAP()

BOOL CSpeakNDlg::LoadLesson(LPCSTR lpLessonName)
{
	// load lesson from resource
	HRSRC hRes; // resource handle to lesson data
	HGLOBAL hData;
	if ((hRes = ::FindResource(AfxGetResourceHandle(), lpLessonName,
	  "lesson")) == NULL ||
	  (hData = ::LoadResource(AfxGetResourceHandle(), hRes)) == NULL)
		return FALSE;
	m_lpszNextQuestion = (LPCSTR)::LockResource(hData);
	return TRUE;
}

BOOL CSpeakNDlg::OnInitDialog()
{
	ASSERT(m_targetWord.IsEmpty());     // not started yet

	// set the font of the prompt text to something bigger
	LOGFONT logfont;
	memset(&logfont, 0, sizeof(logfont));
	logfont.lfHeight = 40;
	logfont.lfWeight = FW_BOLD;
	strcpy(logfont.lfFaceName, "Arial");        // TrueType font
	VERIFY(m_biggerFont.CreateFontIndirect(&logfont));
	PromptText().SetFont(&m_biggerFont);
	InputEdit().SetFont(&m_biggerFont);

	// load the bitmaps for bitmap buttons
	VERIFY(m_replayButton.AutoLoad(IDC_REPLAY_SOUND, this));
	InputEdit().ShowWindow(FALSE);      // start with input disabled

	// load initial picture
	VERIFY(m_pictureButton.SubclassDlgItem(IDC_PICTURE, this));
	VERIFY(m_pictureButton.LoadBitmaps("intro", NULL, NULL));

	// Make the dialog visible, and update
	ShowWindow(TRUE);       // SHOW_OPENWINDOW
	UpdateWindow();

	PlaySound(IDSOUND_WELCOME);
	AdvanceLesson();
	return TRUE;
}

void CSpeakNDlg::OnReplaySound()
{
	InputEdit().SetFocus();
	PlaySound(m_targetWord);
}

void CSpeakNDlg::OnOK()
{
	// check results
	CString result;
	InputEdit().GetWindowText(result);
	if (result != m_targetWord)
	{
		PlaySound(IDSOUND_INCORRECT);
		MessageBox("Please try again", "Incorrect Guess");
		return;
	}
	PlaySound(IDSOUND_CORRECT);
	AdvanceLesson();
}

void CSpeakNDlg::OnGiveUp()
{
	PlaySound(IDSOUND_GIVEUP);
	InputEdit().SetWindowText(m_targetWord);        // show answer
	OnReplaySound();
	AdvanceLesson();
}

/////////////////////////////////////////////////////////////////////////////
// Advancing to the next lesson

void CSpeakNDlg::AdvanceLesson()
{
	if (*m_lpszNextQuestion == '\0')
	{
		// out of questions
		PlaySound(IDSOUND_GOODBYE);
		EndDialog(IDOK);
		return;
	}
	// lesson resource points to 1 keyword string per lesson
	m_targetWord = m_lpszNextQuestion;
	m_lpszNextQuestion += m_targetWord.GetLength() + 1;
	m_targetWord.MakeUpper();       // just in case
	int nBoxes = m_targetWord.GetLength();

	PlaySound(IDSOUND_QUESTION);

	// draw the picture (bitmap with the same name as the target)
	if (!m_pictureButton.LoadBitmaps(m_targetWord))
	{
		MessageBox("Picture unavailable");
		VERIFY(m_pictureButton.LoadBitmaps("intro", NULL, NULL));
			// go back to the initial bitmap
	}
	m_pictureButton.Invalidate(TRUE);
	CBEdit* pEdit = &InputEdit();
	pEdit->SetWindowText("");           // clear out the edit

	m_pictureButton.UpdateWindow();     // draw the picture now

	// adjust boxed edit item to be centered and the right size
	CRect rect;         // get edit control size
	pEdit->GetWindowRect(&rect);
	ScreenToClient(&rect);                  // in parent coordinate
	int xMid = (rect.left + rect.right) / 2;
	RC rc;              // get pen input info
	VERIFY(pEdit->GetRC(&rc));
	TEXTMETRIC tm;      // get size of font
	{
		CClientDC dc(this);
		CFont* pOldFont = dc.SelectObject(&m_biggerFont);
		dc.GetTextMetrics(&tm);
		dc.SelectObject(pOldFont);
	}

	// set input guides to match big font
	const int xGap = 8;
	const int yGap = 8;
	rc.guide.cHorzBox = nBoxes;
	rc.guide.cxBox = tm.tmMaxCharWidth + tm.tmMaxCharWidth / 3; // 4/3
	rc.guide.cyBox = tm.tmHeight;
	rc.guide.cyBase = tm.tmAscent + yGap;               // uppercase
	int cxEdit = rc.guide.cxBox * nBoxes + yGap;        // extra room for sides
	rect.left = xMid - cxEdit / 2;
	rect.right = xMid + cxEdit / 2;
	rect.bottom = rect.top + tm.tmHeight + yGap;        // extra space
	pEdit->MoveWindow(rect);
	VERIFY(pEdit->SetRC(&rc));
	pEdit->Invalidate(TRUE);
	pEdit->ShowWindow(TRUE);

	OnUpdateStatus();               // set appropriate face
	OnReplaySound();                // ask question
}

/////////////////////////////////////////////////////////////////////////////
// Happy face status indicator

void CSpeakNDlg::OnUpdateStatus()
{
	CString result;
	InputEdit().GetWindowText(result);

	UINT nIDI = IDI_FACE_NEUTRAL;       // default
	if (result == m_targetWord)
		nIDI = IDI_FACE_HAPPIER;        // exact match
	else if (result.IsEmpty())
		nIDI = IDI_FACE_NEUTRAL;        // not started yet
	else if (result[0] == m_targetWord[0])
		nIDI = IDI_FACE_HAPPY;          // first letter correct
	else
		nIDI = IDI_FACE_SAD;            // not even close
	HICON hNew = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(nIDI));
	ASSERT(hNew != NULL);
	::DestroyIcon(StatusFace().SetIcon(hNew));
	UpdateWindow();                 // draw everything now

	if (nIDI == IDI_FACE_HAPPIER)
	{
		// exact match - automatic advance
		OnReplaySound();
		PlaySound(IDSOUND_CORRECT);
		AdvanceLesson();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSpeakNApp

BOOL CSpeakNApp::InitInstance()
{
	// Must have PenWindows installed
	if (GetSystemMetrics(SM_PENWINDOWS) == NULL)
	{
		MessageBox(NULL, "This application requires Microsoft Windows for"
			" Pen Computing", "SpeakNPen", MB_OK);
		return FALSE;
	}

	// Creates a simple dialog and do it
	CSpeakNDlg mainDlg;
	if (!mainDlg.LoadLesson("SAMPLE1"))
		return FALSE;
	m_pMainWnd = &mainDlg;
	mainDlg.DoModal();

	// that's all, quit app
	::PostQuitMessage(0);
	return TRUE;
}

CSpeakNApp theApp;

/////////////////////////////////////////////////////////////////////////////
