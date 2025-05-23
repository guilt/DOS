// wclsedit.cpp : registered WNDCLASS Edit control example
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
// Dialog class

class CWclsEditDlg : public CModalDialog
{
public:
	CWclsEditDlg()
		: CModalDialog(IDD_WNDCLASS_EDIT)
		{ }

	// access to controls is through inline helpers
	CEdit&  Edit1()
				{ return *(CEdit*)GetDlgItem(IDC_EDIT1); }
	CEdit&  Edit2()
				{ return *(CEdit*)GetDlgItem(IDC_EDIT2); }
	CEdit&  Edit3()
				{ return *(CEdit*)GetDlgItem(IDC_EDIT3); }
	CEdit&  Edit4()
				{ return *(CEdit*)GetDlgItem(IDC_EDIT4); }

	BOOL OnInitDialog();
	void OnOK();

	void OnIllegalChar();
	DECLARE_MESSAGE_MAP();
};

BOOL CWclsEditDlg::OnInitDialog()
{
	// nothing special to do
	return TRUE;
}

void CWclsEditDlg::OnOK()
{
#ifdef _DEBUG
	// dump results, normally you would do something with these
	CString s;
	Edit1().GetWindowText(s);
	TRACE("edit1 = '%s'\n", (const char*) s);
	Edit2().GetWindowText(s);
	TRACE("edit2 = '%s'\n", (const char*) s);
	Edit3().GetWindowText(s);
	TRACE("edit3 = '%s'\n", (const char*) s);
	Edit4().GetWindowText(s);
	TRACE("edit4 = '%s'\n", (const char*) s);
#endif

	EndDialog(IDOK);
}

/////////////////////////////////////////////////////////////////////////////
// Handle custom control notification here

BEGIN_MESSAGE_MAP(CWclsEditDlg, CModalDialog)
	ON_CONTROL(PEN_ILLEGALCHAR, IDC_EDIT1, OnIllegalChar)
	ON_CONTROL(PEN_ILLEGALCHAR, IDC_EDIT2, OnIllegalChar)
	ON_CONTROL(PEN_ILLEGALCHAR, IDC_EDIT3, OnIllegalChar)
	ON_CONTROL(PEN_ILLEGALCHAR, IDC_EDIT4, OnIllegalChar)
END_MESSAGE_MAP()


void  CWclsEditDlg::OnIllegalChar()
{
	TRACE("Don't do that!\n");
	// add extra reporting here...
}

/////////////////////////////////////////////////////////////////////////////
// Run the test

void CTestWindow::OnTestWndClassEdit()
{
	TRACE("running dialog containing WNDCLASS special edit items\n");
	if (!CParsedEdit::RegisterControlClass())
	{
		MessageBox("Failed to register WNDCLASS for parsed control");
		return;
	}
	CWclsEditDlg dlg;
	dlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
