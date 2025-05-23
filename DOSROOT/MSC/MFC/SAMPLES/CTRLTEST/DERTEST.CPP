// deredit.cpp : C++ derived Edit control example
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

#include "ctrltest.h"

#include "paredit.h"

/////////////////////////////////////////////////////////////////////////////

class CDerEditDlg : public CModalDialog
{
protected:
	CFont*  m_pFont;
	// construct
	CParsedEdit edit1, edit2, edit3, edit4;
	CStatic static1, static2, static3, static4;
public:
	CDerEditDlg()
		: CModalDialog(IDD_DERIVED_EDIT)
		{ }

	BOOL OnInitDialog();
	void OnSetFont(CFont* pFont)
			{ m_pFont = pFont; }
	void OnOK();
};

BOOL CDerEditDlg::OnInitDialog()
	// create children on InitDialog 
	//  (not in CDerEditDlg constructor since the dialog has
	//    no attached HWND in the constructor)
{
	// This is an example of the _incorrect_ way to create a dialog
	// The following code show you what you should _not_ do:
	//    1) do not use hard coded numbers for coordinates and sizes
	//     (these will break when the font sizes changes and are
	//     hard to edit and maintain).
	//    2) do not put strings in code, they should be in resources.
	//    3) as you can see below the programming steps required
	//     to create controls, pass the correct creation parameters,
	//     and set the appropriate font, is complicated and error prone.

	const int yStart = 8;
	const int height = 30;

	CPoint whereLabel(10, yStart);
	CSize sizeLabel(80, 24);

	CPoint whereEdit(90, yStart);
	CSize sizeEdit(140, 24);

	static1.Create("Letters:", WS_VISIBLE | WS_CHILD | SS_LEFT,
		CRect(whereLabel, sizeLabel), this, -1);
	static1.SetFont(m_pFont);
	whereLabel.y += height;
	edit1.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER |
		PES_LETTERS,
		CRect(whereEdit, sizeEdit), this, IDC_EDIT1);
	edit1.SetFont(m_pFont);
	whereEdit.y += height;

	static2.Create("Numbers:", WS_VISIBLE | WS_CHILD | SS_LEFT,
		CRect(whereLabel, sizeLabel), this, -1);
	static2.SetFont(m_pFont);
	whereLabel.y += height;
	edit2.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER |
		PES_NUMBERS,
		CRect(whereEdit, sizeEdit), this, IDC_EDIT2);
	edit2.SetFont(m_pFont);
	whereEdit.y += height;

	static3.Create("Either:", WS_VISIBLE | WS_CHILD | SS_LEFT,
		CRect(whereLabel, sizeLabel), this, -1);
	static3.SetFont(m_pFont);
	whereLabel.y += height;
	edit3.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER |
		PES_LETTERS | PES_NUMBERS,
		CRect(whereEdit, sizeEdit), this, IDC_EDIT3);
	edit3.SetFont(m_pFont);
	whereEdit.y += height;

	static4.Create("Anything:", WS_VISIBLE | WS_CHILD | SS_LEFT,
		CRect(whereLabel, sizeLabel), this, -1);
	static4.SetFont(m_pFont);
	whereLabel.y += height;
	edit4.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_BORDER |
		PES_ALL,
		CRect(whereEdit, sizeEdit), this, IDC_EDIT4);
	edit4.SetFont(m_pFont);
	whereEdit.y += height;

	// change the dialog height so everything fits
	int yBottom = whereEdit.y + height * 2; // extra space
	CRect rect;
	GetWindowRect(rect);
	VERIFY(SetWindowPos(NULL, -1, -1, rect.Width(), yBottom,
		SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW|SWP_NOACTIVATE));

	// set focus to first one
	edit1.SetFocus();
	return FALSE;   // focus set
}

void CDerEditDlg::OnOK()
{
#ifdef _DEBUG
	// dump results, normally you would do something with these
	CString s;
	edit1.GetWindowText(s);
	TRACE("edit1 = '%s'\n", (const char*) s);
	edit2.GetWindowText(s);
	TRACE("edit2 = '%s'\n", (const char*) s);
	edit3.GetWindowText(s);
	TRACE("edit3 = '%s'\n", (const char*) s);
	edit4.GetWindowText(s);
	TRACE("edit4 = '%s'\n", (const char*) s);
#endif

	EndDialog(IDOK);
}

/////////////////////////////////////////////////////////////////////////////
// Run the test

void CTestWindow::OnTestDerivedEdit()
{
	TRACE("running dialog with special derived CParsedEdit controls in it\n");
	CDerEditDlg dlg;
	dlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
