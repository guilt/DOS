// speakn.h : Declares the class interfaces for the SpeakN application.
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

#ifndef RC_INVOKED
#include <afxwin.h>         // core of MFC
#include <afxpen.h>         // PenWindows extras
#else
#include <windows.h>
#include <afxres.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// Control IDs for main dialog

#define IDC_PICTURE                 201
#define IDC_STATUS_FACE             202
#define IDC_PROMPT_TEXT             203
#define IDC_REPLAY_SOUND            204
#define IDC_GIVE_UP                 205
#define IDC_INPUT_EDIT              206

/////////////////////////////////////////////////////////////////////////////
// Standard sounds 
#define IDSOUND_WELCOME         101
#define IDSOUND_QUESTION        102
#define IDSOUND_CORRECT         103
#define IDSOUND_INCORRECT       104
#define IDSOUND_GIVEUP          105
#define IDSOUND_GOODBYE         106

/////////////////////////////////////////////////////////////////////////////
// Icon IDs

#define IDI_FACE_NEUTRAL    10
#define IDI_FACE_HAPPY      11
#define IDI_FACE_HAPPIER    12
#define IDI_FACE_SAD        13

/////////////////////////////////////////////////////////////////////////////
// CSpeakNDlg:
//   The main user interface to this application is just one big dialog

class CSpeakNDlg : public CModalDialog
{
// Constructors
public:
	CSpeakNDlg() : CModalDialog("MainDialog")
		{ m_lpszNextQuestion = NULL; }
	BOOL LoadLesson(LPCSTR lpLessonName);

// Operations
	void        AdvanceLesson();

// Attributes (the current question/lesson)
	// current question (from resource)
	CString         m_targetWord;           // target word (upper case)

	// resource containing all the questions
	LPCSTR          m_lpszNextQuestion; // empty string => done

// Implementation
protected:
	// special controls
	CFont           m_biggerFont;
	CBitmapButton   m_pictureButton; // main bitmap done as a special button
	CBitmapButton   m_replayButton; // bitmap button for replay sound

	// normal Windows controls
	CStatic&    StatusFace()    // face which smiles or frowns
					{ return *(CStatic*)GetDlgItem(IDC_STATUS_FACE); }
	CStatic&    PromptText()    // prompt area
					{ return *(CStatic*)GetDlgItem(IDC_PROMPT_TEXT); }
	CBEdit&     InputEdit()     // user input (a Pen Boxed Edit)
					{ return *(CBEdit*)GetDlgItem(IDC_INPUT_EDIT); }

	// message handlers
	virtual BOOL OnInitDialog();
	afx_msg void OnReplaySound();
	afx_msg void OnUpdateStatus();
	virtual void OnOK();        // Guess
	virtual void OnGiveUp();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CSpeakNApp:

class CSpeakNApp : public CWinApp
{
public:
	BOOL InitInstance();
};

/////////////////////////////////////////////////////////////////////////////
