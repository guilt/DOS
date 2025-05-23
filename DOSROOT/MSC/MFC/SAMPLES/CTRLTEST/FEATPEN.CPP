// featpen.cpp : pen HEdit features
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

// we need the MFC extensions for PenWindows
#include <afxpen.h>
// we also use the MFC common dialogs for color picker
#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////

class CPenFeatureDlg : public CModalDialog
{
public:
	CPenFeatureDlg()
		: CModalDialog(IDD_PENEDIT_FEATURES)
		{ }

	// just 1 HEdit to play with
	CHEdit& Edit1()
				{ return *(CHEdit*)GetDlgItem(IDC_EDIT1); }

// Implementation
protected:
	BOOL OnInitDialog();
	void OnOK();
	void OnConfigure();
	DECLARE_MESSAGE_MAP();
};

BEGIN_MESSAGE_MAP(CPenFeatureDlg, CModalDialog)
	ON_COMMAND(IDC_CONFIGURE, OnConfigure)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL CPenFeatureDlg::OnInitDialog()
{
	// nothing special to do
	return TRUE;
}

void CPenFeatureDlg::OnOK()
{
#ifdef _DEBUG
	// dump results, normally you would do something with these
	CString s;
	Edit1().GetWindowText(s);
	TRACE("edit1 = '%s'\n", (const char*) s);
#endif

	EndDialog(IDOK);
}

/////////////////////////////////////////////////////////////////////////////
// Run the test

void CTestWindow::OnTestPenEditFeatures()
{
	TRACE("running HEdit feature test dialog\n");
	CPenFeatureDlg dlg;
	dlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// Configure the HEdit edit item
	// (note: local changes only)

// Dialog used for the configure option
class CConfigureHEditDlg : public CModalDialog
{
protected:
	CHEdit&     m_rHEdit;       // reference to Edit item to configure
	COLORREF    m_inkColor;     // for color picker

public:
	CConfigureHEditDlg(CHEdit& rHEdit, CWnd* pParent = NULL)
		: CModalDialog(IDD_PENEDIT_CONFIGURE, pParent),
			m_rHEdit(rHEdit)
		{ }

// Implementation
protected:
	BOOL OnInitDialog();
	void OnOK();
	void OnChooseInkColor();
	DECLARE_MESSAGE_MAP();
};

BEGIN_MESSAGE_MAP(CConfigureHEditDlg, CModalDialog)
	ON_COMMAND(IDC_BUTTON2, OnChooseInkColor)
END_MESSAGE_MAP()

BOOL CConfigureHEditDlg::OnInitDialog()
{
	// fill in initial values
	RC rcInfo;
	VERIFY(m_rHEdit.GetRC(&rcInfo));            // get current settings

	// set the ALC bits (max of 32 of them, 1 checkbox each)
	TRACE("initial ALC = 0x%lx\n", rcInfo.alc);
	for (int i = 0; i < 32; i++)
	{
		if (rcInfo.alc & (1L<<i))
			CheckDlgButton(IDC_ALC_FIRST+i, TRUE);
				// check control if there is one
	}

	// set LeftHanded
	if (rcInfo.wRcPreferences & RCP_LEFTHAND)
		CheckDlgButton(IDC_BUTTON1, TRUE);

	// set ink info
	SetDlgItemInt(IDC_EDIT1, rcInfo.nInkWidth);
	m_inkColor = rcInfo.rgbInk;
	return TRUE;
}

void CConfigureHEditDlg::OnOK()
{
	// get info from dialog, update fields of RC as appropriate
	RC rcInfo;
	VERIFY(m_rHEdit.GetRC(&rcInfo));            // get current settings

	for (int i = 0; i < 32; i++)
	{
		CButton* pButton = (CButton*)GetDlgItem(IDC_ALC_FIRST + i);
		if (pButton != NULL)
		{
			// set bit depending on checkbox content
			if (pButton->GetCheck())
				rcInfo.alc |= (1L << i);
			else
				rcInfo.alc &= ~(1L << i);
		}
	}
	TRACE("final ALC = 0x%lx\n", rcInfo.alc);

	if (IsDlgButtonChecked(IDC_BUTTON1))
		rcInfo.wRcPreferences |= RCP_LEFTHAND;
	else
		rcInfo.wRcPreferences &= ~RCP_LEFTHAND;

	BOOL bOk;
	rcInfo.nInkWidth = GetDlgItemInt(IDC_EDIT1, &bOk);
	if (!bOk || rcInfo.nInkWidth < -1 || rcInfo.nInkWidth > 15)
	{
		MessageBox("Illegal Ink Width (-1 .. 15 permitted)");
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetSel(0, -1);
		pEdit->SetFocus();
		return;
	}
	rcInfo.rgbInk = m_inkColor;

	// set the final values
	VERIFY(m_rHEdit.SetRC(&rcInfo));
	EndDialog(IDOK);
}

void CConfigureHEditDlg::OnChooseInkColor()
{
	DWORD dwFlags = CC_PREVENTFULLOPEN;
	COLORREF crPrompt = (m_inkColor != RC_LDEFAULT) ? m_inkColor : 0;
		// default to 0 (black) for default color

	CColorDialog dlg(CC_PREVENTFULLOPEN, crPrompt, this);
	if (dlg.DoModal() == IDOK)
		m_inkColor = dlg.GetColor();
}

void CPenFeatureDlg::OnConfigure()
{
	CConfigureHEditDlg dlg(Edit1(), this);
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
