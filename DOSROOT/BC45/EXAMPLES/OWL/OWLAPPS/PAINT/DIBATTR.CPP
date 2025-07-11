//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1991, 1993 by Borland International
//   Example paint program dib attribute dialog
//----------------------------------------------------------------------------
#include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\button.h>
#include "dibattr.h"
#include "paint.rh"

DEFINE_RESPONSE_TABLE1(TDibAttrDialog, TDialog)
  EV_BN_CLICKED(IDC_2COLOR, Bn2Color),
  EV_BN_CLICKED(IDC_16COLOR, Bn16Color),
  EV_BN_CLICKED(IDC_256COLOR, Bn256Color),
END_RESPONSE_TABLE;

TDibAttrDialog::TDibAttrDialog(TWindow* parent, 
                               int&     width,
                               int&     height,
                               int&     colors,
                               TModule* module)
 : TDialog(parent, "IDD_DIBATTR", module),
   Width(width), Height(height), Colors(colors)
{
}

void
TDibAttrDialog::SetupWindow()
{
  SetDlgItemInt(IDC_WIDTH, Width);
  SetDlgItemInt(IDC_HEIGHT, Height);
  
  CheckRadioButton(IDC_2COLOR, IDC_256COLOR, 
       Colors == 2 ? IDC_2COLOR : Colors == 16 ? IDC_16COLOR : IDC_256COLOR);
}

BOOL
TDibAttrDialog::CanClose()
{
  Width = GetDlgItemInt(IDC_WIDTH);
  Height = GetDlgItemInt(IDC_HEIGHT);
  return TRUE;
}
