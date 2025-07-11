//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1991, 1993 by Borland International
//----------------------------------------------------------------------------
#include  <owl\owlpch.h>
#include  <owl\dialog.h>
#include  <owl\clipboar.h>
#include  <owl\clipview.h>
#include  "diagxprt.rh"
#include  "setup.h"
#include  "diagxprt.h"
#include  <stdio.h>

//
//  The diagnostic setup dialog box is divided in 2 main groups:
//  * the system group (TSysGroup->TGroup);
//  * the user group (TUsrGroup->TGroup).
//
//  Each group is a list of items (TSetupItem).
//  Items belonging to the system group (TSysItem->TSetupItem) are
//  different than items belonging to the user group (TUsrItem->TSetupItem)
//  in that the setup infos are not maintained the same way in OWL.INI.
//
//  Each item TSysItem and TUsrItem is attached to a set of child windows
//  in the dialog box. Each such set of windows is abstracted thru a class:
//  TUsrWindow and TSysWindow respectively. Each of those classes is
//  generated by a class template, which parametrizes the exact contents
//  of the set of windows: TRadioButton/TRadioButton and TStatic/TEdit resp.
//
//  The number of windows set is limited (by the area in the dialog box);
//  the number of items is NOT limited. Scroll bars are displayed when
//  necessary. Those scrollbars are abstracted thru the class TGroupScroll.
//  Therefore each group maintains two arrays: an array of items TItemsArray
//  and an array of window sets TWindowArray.
//


//
// Utility function to copy diagnostic code to clipboard so that user
// can paste into appropriate source file
//
void
CopyToClipboard(TWindow *w, char *descr, char *className)
{
  // Generate a C++ example on the clipboard, which is a very trivial
  // string subsitution operation.
  //
  string pattern(
    "// Diagnostic: %s\n"
    "DIAG_DEFINE_GROUP_INIT(OWL_INI, %s, 1, 0);\n"
    "//TRACEX(%s, errLevel, \042A comment \042 << aFunction());\n"
   );

  pattern.substring("%s") = descr;
  pattern.substring("%s") = className;
  pattern.substring("%s") = className;

  TClipboard& c = w->OpenClipboard();
  c.EmptyClipboard();
  HANDLE hData = GlobalAlloc(GMEM_SHARE, pattern.length()+1);
  char far* pData = (char far*)GlobalLock(hData);

  pattern.copy(pData, pattern.length()+1);

  GlobalUnlock(hData);
  c.SetClipboardData(CF_TEXT, hData);

  c.CloseClipboard();  // Clipboard is responsible for freeing hData
}

//
//  class TSetupItem
//

TSetupItem::TSetupItem(char *C, char *D) : Enable(0), level(0)
{
  Class = C;
  Descr = D;
}

void
TSetupItem::operator =(TBaseSetupWindow& w)
{
  // Unmap from a physical set of windows: set the enability and
  // warning level accordingly to the setup window:
  //
  SetEnable(w.GetEnable());
  SetLevel(w.GetLevel());
}

void
TSetupItem::Load()
{
  // Loads itself from .ini file - loads the diagnostic classname and the
  // diagnostic description:
  //
  char b[80];
  GetPrivateProfileString(GetSection(), Class.c_str(), "0 0",
                          b, sizeof(b), GetIniFile());
  sscanf(b, "%d %d", &bEnable, &level);
  if (Descr == "") {
    GetPrivateProfileString(GetSectionDesc(), Class.c_str(), Class.c_str(),
                            b, sizeof(b), GetIniFile());
    Descr = b;
  }
}

void
TSetupItem::Save()
{
  // Save itself to the .ini file - save the diagnostic classname and the
  // diagnostic description:
  //
  char b[20];
  sprintf(b, "%d %d", bEnable, level);
  WritePrivateProfileString(GetSection(), Class.c_str(), b, GetIniFile());
  WritePrivateProfileString(GetSectionDesc(), Class.c_str(), Descr.c_str(), GetIniFile());
}

//
//  class TDiagEnable
//

DEFINE_RESPONSE_TABLE1(TDiagEnable, TCheckBox)
  EV_NOTIFY_AT_CHILD(BN_CLICKED, BNClicked),
END_RESPONSE_TABLE;

//  TDiagEnable provides an abstraction for the small check box associated
//  to each setup item. This checkbox enables of disables the associated
//  setup item. But the checkbox can itself be disabled (by a upper level
//  checkbox).
//
void
TDiagEnable::BNClicked()
{
  TCheckBox::BNClicked();
  EnableWindow(TRUE);
}

BOOL
TDiagEnable::EnableWindow(BOOL enable)
{
  BOOL ret = TCheckBox::EnableWindow(enable);
  if (enable)
    enable = GetCheck();
  if (W0) W0->EnableWindow(enable);
  if (W1) W1->EnableWindow(enable);
  if (S0) S0->EnableWindow(enable);
  if (S1) S1->EnableWindow(enable);
  return ret;
}

//
//  TMainEnable provides the abstraction for the main checkbox which
//  enables of disables ALL the diagnostic groups. It knows how to save/load
//  it state from the .ini file:
//
char* TMainEnable::Class = "Enabled";

TMainEnable::TMainEnable(TWindow* p, int n, TGroup* g1, TGroup* g2) :
  TDiagEnable(p, n, g1, g2)
{
  Create();
  Load();
}

void
TMainEnable::Load()
{
  char b[80];
  GetPrivateProfileString(SYS_CLS, Class, "0", b, sizeof(b), SYS_INI);
  SetCheck(atoi(b));
  TDiagEnable::EnableWindow(TRUE);
}

void
TMainEnable::Save()
{
  char b[80];
  wsprintf(b, "%d", GetCheck() != 0);
  WritePrivateProfileString(SYS_CLS, Class, b, SYS_INI);
}


//
//  TGroup is the base class for diagnostic groups. TGroup knows how to
//  enable/disable itself (by enabling/disabling all the associated setup
//  items), to load/save from the .ini file and to map/unmap its setup
//  items to the associated windows sets. The purpose of the map/unmap
//  operations is to allow setup items to be scrolled.
//

void
TGroup::EnableWindow(BOOL bEnable)
{
  for (int i = 0; i < Windows.GetItemsInContainer(); i++)
    Windows[i]->EnableWindow(bEnable);
}

void
TGroup::Load()
{
  for (int i = 0; i < Items.GetItemsInContainer(); i++)
    Items[i]->Load();
}

void
TGroup::Save()
{
  Cleanup();
  for (int i = 0; i < Items.GetItemsInContainer(); i++)
    Items[i]->Save();
}

int
TGroup::Map(int x)
{
  // May have to re-validate <x>
  //
  if (x == MapAsBefore)
    x = scrollPos;
  if (x > Items.GetItemsInContainer() || x == MapToBottom)
    x = Items.GetItemsInContainer() - Windows.GetItemsInContainer();
  if (x < 0 || x == MapToTop)
    x = 0;
  scrollPos = x;

  // Map each item to a window, as long as they fit
  //
  for (int i = 0; i < Windows.GetItemsInContainer(); i++, x++) {
    if (x < Items.GetItemsInContainer()) {
      *Windows[i] = *Items[x];
      Windows[i]->EnableWindow(IsEnable());
    } else
      *Windows[i] = 0;      // No more item: "empty" the associated window
  }
  return scrollPos;
}

int
TGroup::UnMap()
{
  int i, x;
  for (i = 0, x = scrollPos; i < Windows.GetItemsInContainer(); i++, x++) {
    if (x < Items.GetItemsInContainer())
      *Items[x] = *Windows[i];
  }
  return scrollPos;
}


//
//  class TSysGroup
//

TSysGroup::TSysGroup(TWindow *Dialog, int nID)
{
  // Create the child windows
  //
  for (int i = 0; Dialog->GetDlgItem(nID + i*4); i++)
    Windows.Add(new TSysWindow(Dialog, nID + i*4));

  // Create the predefined system items (read from resources)
  //
  HRSRC hRes = GetApplicationObject()->FindResource(IDR_SYS_ITEMS, RT_RCDATA);
  if (hRes) {
    HGLOBAL hData = GetApplicationObject()->LoadResource(hRes);
    if (hData) {
      LPSTR pData = (LPSTR)::LockResource(hData);
      // pData now points to a set of strings

      LPSTR pC = pData;
      LPSTR pD;

      while(pC && *pC) {
        char name[128];
        char desc[128];
        pD = pC + strlen(pC) + 2;
        lstrcpy(name, pC);
        lstrcpy(desc, pD);
        Items.Add(new TSysItem(name, desc));
        pC = pD + strlen(pD) + 2;
      }
      #if !defined(__WIN32__)
        ::UnlockResource(hData);
      #endif
    }
    #if !defined(__WIN32__)
      ::FreeResource(hData);
    #endif
  }
  // Load the values associated to each item
  TGroup::Load();
}

void
TSysGroup::Cleanup()
{
  WritePrivateProfileString(SYS_CLS, 0, 0, SYS_INI);
  WritePrivateProfileString(SYS_DSC, 0, 0, SYS_INI);
}

//
//  class TUsrGroup
//

TUsrGroup::TUsrGroup(TWindow *Dialog, int nID)
{
  // Create the child windows
  //
  for (int i = 0; Dialog->GetDlgItem(nID + i*4); i++)
    Windows.Add(new TUsrWindow(Dialog, nID + i*4));

  // Create the setup items (loaded from IniFile)
  //
  const int s = 4096;
  char *p, *b = new char[s];
  GetPrivateProfileString(USR_DSC, 0, "", b, s, USR_INI);
  for (i = 0, p = b; p && *p; i++, p += strlen(p) + 1)
    Items.Add(new TUsrItem(p));
  delete b;

  // Load the values associated to each item
  //
  TGroup::Load();
}

void
TUsrGroup::Cleanup()
{
//  WritePrivateProfileString(USR_CLS, 0, 0, USR_INI);
  WritePrivateProfileString(USR_DSC, 0, 0, USR_INI);
}

//
//  TSizableDialog makes a dialog sizable. Two sizes are defined: a small
//  size and a large size. Call the Toggle function to switch to any size.
//  To determine the size, define a dummy control in the dialog which
//  provides the upper-right corner of the small size.
//  TSizableDialog also know how to center itself accordingly to the parent
//  window, and how to re-adjust its position after being centered, if gone
//  out of view.
//

void
TSizableDialog::SetupWindow()
{
  TDialog::SetupWindow();
  HWND hBox = GetDlgItem(nBoxID);
  if (hBox) {
    ::ShowWindow(hBox, SW_HIDE);
    TRect rSmall, rLarge;
    ::GetWindowRect(hBox, (LPRECT)&rSmall);
    GetWindowRect(rLarge);
    small.cx = rSmall.left - rLarge.left;
    small.cy = rSmall.top - rLarge.top;
    large = rLarge.Size();
    tSize = t_max;
    bMaximized = TRUE;

    // Tolerate some inaccuracy on the positionning of the small box...
    //
    if (abs(small.cx - large.cx) < 4)
      small.cx = large.cx;
    if (abs(small.cy - large.cy) < 4)
      small.cy = large.cy;
    Toggle(t_min);
  }
  Center();
}

void
TSizableDialog::Toggle(int tType)
{
  TSize newSize;
  if (tType == t_minmax)
    tType = (tSize == t_min) ? t_max : t_min;

  tSize = tType;
  switch (tType) {
    case t_min:
      newSize = small;
      break;
    case t_max:
      newSize = large;
      break;
    default:
      return;
  }
  bMaximized = tType != t_max;
  SetWindowPos(0, TRect(TPoint(0, 0), newSize), SWP_NOZORDER|SWP_NOMOVE);
//  EnableControls();
}

void
TSizableDialog::EnableControls()
{
  TRect rParent = GetWindowRect();
  HWND hChld = GetWindow(GW_CHILD);
  while (hChld) {
    POINT pt[2];
    ::GetWindowRect(hChld, (RECT*)&pt);
    if (!PtInRect(&rParent, pt[0]))
      ::EnableWindow(hChld, 0);
    hChld = ::GetWindow(hChld, GW_HWNDNEXT);
  }
}

void
TSizableDialog::Center()
{
  TRect rPar;
  TRect rDlg;
  GetWindowRect(rDlg);
  HWND hParent = GetParent();
  if (!hParent)
    hParent = GetDesktopWindow();
  ::GetWindowRect(hParent, &rPar);

  int wDlgWidth = rDlg.Width();
  int wDlgHeight = (rDlg.bottom - rDlg.top);

  int w = (rPar.right - rPar.left) - wDlgWidth;
  int h = (rPar.bottom - rPar.top) - wDlgHeight;

  int x = rPar.left + (w / 2);
  int y = rPar.top + (h / 2);

  MoveWindow(x, y, wDlgWidth , wDlgHeight, FALSE);
  AdjustPos();
}

void
TSizableDialog::AdjustPos(void)
{
  int W = GetSystemMetrics(SM_CXSCREEN);
  int H = GetSystemMetrics(SM_CYSCREEN);

  TRect r = GetWindowRect();
  int w = r.Width();
  int h = r.Height();

  if (r.left < 0)
    r.left = 0;
  if (r.top < 0)
    r.top = 0;
  if (r.right > W)
    r.left = W - w;
  if (r.bottom > H)
    r.top -= (H - h);

  SetWindowPos(0, r.left, r.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


//
//  TGroupScroll provides the abstraction for a diagnostic group scrollbar.
//  Associated to a diagnostic group, TGroupScroll simply map/unmap the
//  diagnostic group on scroll events. It also knows how to hide itself when
//  scrolling is irrelevant for that group (and show back if necessary):

DEFINE_RESPONSE_TABLE1(TGroupScroll, TScrollBar)
  EV_WM_VSCROLL, 
END_RESPONSE_TABLE;

TGroupScroll::TGroupScroll(TWindow* w, int i, TGroup* g)
  : group(g), x(0), TScrollBar(w, i)
{
  Create();
  Initialize(0);
}

void
TGroupScroll::Initialize(int pos)
{
  min = 0;
  max = group->Items.GetItemsInContainer() - group->Windows.GetItemsInContainer();

  if (max <= min)
    ShowWindow(SW_HIDE);    // Hide itself because scrolling is irrelevant

  else {
    SetRange(min, max);
    TScrollBar::SetPosition(x = pos);
    EndScroll();
    PageMagnitude = group->Windows.GetItemsInContainer() - 1;
    ShowWindow(SW_SHOW);    // Show back itself, in case was previously hidden
  }
}

void
TGroupScroll::EvVScroll(UINT code, UINT pos, HWND /*hCtl*/)
{
  switch (code) {
    case SB_LINEDOWN:      if (x < max) SetPosition(x + LineMagnitude); break;
    case SB_LINEUP:        if (x > min) SetPosition(x - LineMagnitude); break;
    case SB_PAGEDOWN:      if (x < max) SetPosition(x + PageMagnitude); break;
    case SB_PAGEUP:        if (x > min) SetPosition(x - PageMagnitude); break;
    case SB_THUMBPOSITION: SetPosition(pos); break;
    case SB_ENDSCROLL:     EndScroll(); break;
  }
}

void
TGroupScroll::SetPosition(int pos)
{
  x = pos;
  if (x < min) x = min;
  if (x > max) x = max;
  TScrollBar::SetPosition(x);

  // Perform the logical scroll by first unmaping the group and then
  // by maping it to the new position:'
  //
  group->UnMap();
  group->Map(x);
}

void
TGroupScroll::EndScroll()
{
  ::EnableScrollBar(*this, SB_CTL, ESB_ENABLE_BOTH);
  if (x == min)
    ::EnableScrollBar(*this, SB_CTL, ESB_DISABLE_LTUP);
  if (x == max)
    ::EnableScrollBar(*this, SB_CTL, ESB_DISABLE_RTDN);
  if (::GetFocus()) {
    ::InvalidateRect(::GetFocus(), 0, TRUE);
    ::UpdateWindow(::GetFocus());
  }
}

//
//  TSetupDialog drives the setup diagnostic dialog box
//

DEFINE_RESPONSE_TABLE1(TSetupDialog, TDialog)
  EV_COMMAND(IDC_MORE, CmZoom), 
  EV_COMMAND(IDOK, CmOk), 
  EV_COMMAND(IDC_ADD, CmAddUsr), 
  EV_COMMAND(IDC_DEL, CmDelUsr), 
  EV_COMMAND(IDC_EDT, CmEdtUsr), 
END_RESPONSE_TABLE;

void
TSetupDialog::SetupWindow()
{
  TSizableDialog::SetupWindow();

  // Create the two groups:
  //
  SysGroup = new TSysGroup(this, ID_SYS_CHECK);
  UsrGroup = new TUsrGroup(this, ID_USR_CHECK);

  // Create the master enable switch and make it known to each group:
  //
  MainEnable = new TMainEnable(this, ID_SYS_ENABLE, SysGroup, UsrGroup);
  SysGroup->SetMainSwitch(MainEnable);
  UsrGroup->SetMainSwitch(MainEnable);

  // Map each group to the first position:
  //
  SysGroup->Map(0);
  UsrGroup->Map(0);

  // Create the two group scrollbars and attach them to their groups:
  //
  SysScroll = new TGroupScroll(this, IDC_SYS_SCROLL, SysGroup);
  UsrScroll = new TGroupScroll(this, IDC_USR_SCROLL, UsrGroup);

  // Finally, create the actions buttons and update their enable states:
  //
  pDel = new TButton(this, IDC_DEL);
  pDel->Create();
  pEdt = new TButton(this, IDC_EDT);
  pEdt->Create();
  UpdateButtons();
}

void
TSetupDialog::CleanupWindow()
{
  // Delete everybody
  //
  delete MainEnable;
  delete UsrScroll;
  delete SysScroll;
  delete SysGroup;
  delete UsrGroup;
  delete pDel;
  delete pEdt;
}

void
TSetupDialog::CmZoom()
{
  // The uses clicked on the <More/Less> button: resize the dialog box
  // and update the button title accordingly:
  //
  Toggle(TSizableDialog::t_minmax);
  SetDlgItemText(IDC_MORE, !IsMaximized()? "<<< &Less" : "&More >>>");
}

void
TSetupDialog::CmOk()
{
  // The user validated the changes: unmap to get the physical states and
  // save each group:
  //
  SysGroup->UnMap();
  UsrGroup->UnMap();
  SysGroup->Save();
  UsrGroup->Save();
  MainEnable->Save();
  TSizableDialog::CmOk();
}

void
TSetupDialog::CmAddUsr()
{
  // The user selected the 'Add User Group' command. Execute the AddUser
  // dialog box
  //
  TAddUsrDialog Dialog(this);
  if (Dialog.Execute() == IDOK) {
    // Unmap the user group to not lose the last changes, append
    // the new user group to the end of the group and map the group
    // by positionning to the bottom:
    //
    UsrGroup->UnMap();
    UsrGroup->Items.Add(new TUsrItem(Dialog.Class, Dialog.Descr));

    int x = UsrGroup->Map(TGroup::MapToBottom);

    // Don't forget to reset the scrollbar:
    //
    if (UsrScroll)
      UsrScroll->Initialize(x);
  }
  UpdateButtons();
}

void
TSetupDialog::CmDelUsr()
{
  // The user selected the 'Delete User Group' command. Execute the DelUser
  // dialog box
  //
  TDelUsrDialog Dialog(this, &UsrGroup->Items);
  if (Dialog.Execute() == IDOK) {
    // Unmap the user group to not lose the last changes, delete
    // the chosen user group re-map the group:
    //
    int x = UsrGroup->UnMap();
    UsrGroup->Items.Detach(Dialog.nSel);
    x = UsrGroup->Map(x - 1);

    // Don't forget to reset the scrollbar:
    //
    if (UsrScroll)
      UsrScroll->Initialize(x);
  }
  UpdateButtons();
}

void
TSetupDialog::CmEdtUsr()
{
  // The user selected the 'Edit User Group' command. Execute the EdtUser
  // dialog box
  //
  TEdtUsrDialog Dialog(this, &UsrGroup->Items);
  if (Dialog.Execute() == IDOK) {
    UsrGroup->Map(TGroup::MapAsBefore);
  }
}

void
TSetupDialog::UpdateButtons()
{
  // Can only edit/delete not empty user group!
  //
  BOOL bEnable = UsrGroup->Items.GetItemsInContainer() > 0;
  pDel->EnableWindow(bEnable);
  pEdt->EnableWindow(bEnable);
}

//
//  TAddUsrDialog: Prompts the user for two informations - a diagnostic
//  classname and a diagnostic description. Require the classname and
//  defaults the description to the classname.
//

DEFINE_RESPONSE_TABLE1(TAddUsrDialog, TDialog)
  EV_COMMAND(IDOK, CmOk), 
END_RESPONSE_TABLE;

void
TAddUsrDialog::CmOk()
{
  ::GetWindowText(GetDlgItem(IDC_DESCR), Descr, sizeof(Descr));
  ::GetWindowText(GetDlgItem(IDC_CLASS), Class, sizeof(Class));
  if (!*Class) {
    // Classname is required
    //
    MessageBox(
      string(*GetModule(), IDS_ERR_ADD_TXT).c_str(), 
      string(*GetModule(), IDS_ERR_ADD_CAP).c_str(), 
      MB_OK|MB_ICONHAND);
    ::SetFocus(GetDlgItem(IDC_CLASS));
    return;
  }
  if (!*Descr)
    // Defaults the description to the classname
    //
    strcpy(Descr, Class);

  // Put the template on the clipboard
  //
  CopyToClipboard(this, Descr, Class);

  TDialog::CmOk();
}

//
//  TItemsDialog: serves as a base class to the dialogs which need to
//  show to the user a list of setup items. Know how to fill itself, 
//  given an array of setup items.
//

DEFINE_RESPONSE_TABLE1(TItemsDialog, TDialog)
  EV_COMMAND(IDOK, CmOk), 
  EV_LBN_DBLCLK(IDC_LIST, LBDblClk), 
  EV_LBN_SELCHANGE(IDC_LIST, LBSelChange), 
END_RESPONSE_TABLE;

void
TItemsDialog::SetupWindow()
{
  CHECK(items != 0);
  pList = new TListBox(this, IDC_LIST);
  CHECK(pList != 0);
  pList->Create();
  for (int i = 0; i < items->GetItemsInContainer(); i++)
    pList->AddString((*items)[i]->GetDescr());
}

TItemsDialog::~TItemsDialog() { delete pList; }

//
//  TDelUsrDialog: animates the 'Delete User Group' dialog box. Just have
//  to do the error handling, the base class doing the rest:
//

void
TDelUsrDialog::CmOk()
{
  nSel = pList->GetSelIndex();
  if (nSel == LB_ERR) {
    MessageBox(
      string(*GetModule(), IDS_ERR_DEL_TXT).c_str(), 
      string(*GetModule(), IDS_ERR_DEL_CAP).c_str(), 
      MB_OK|MB_ICONHAND);
    ::SetFocus(*pList);
  } else
    TItemsDialog::CmOk();
}

//
//  TEdtUsrDialog: animates the 'edit User Group' dialog box. This enable
//  the user to change classname/description of setup items after having
//  created them. Also, generates on demand a C++ example on the clipboard:
//


DEFINE_RESPONSE_TABLE1(TEdtUsrDialog, TItemsDialog)
END_RESPONSE_TABLE;

void
TEdtUsrDialog::LBSelChange()
{
  if (nPrevSel != LB_ERR) {
    char Class[40], Descr[40];
    GetDlgItemText(IDC_DESCR, Descr, sizeof(Descr));
    GetDlgItemText(IDC_CLASS, Class, sizeof(Class));
    (*items)[nPrevSel]->SetDescr(Descr);
    (*items)[nPrevSel]->SetClass(Class);
    pList->SetItemData(nPrevSel, (DWORD)Descr);
  }
  if ((nPrevSel = nSel = pList->GetSelIndex()) != LB_ERR) {
    SetDlgItemText(IDC_DESCR, (*items)[nSel]->GetDescr());
    SetDlgItemText(IDC_CLASS, (*items)[nSel]->GetClass());
  }
}

void  
TEdtUsrDialog::CmOk()
{ 
  LBSelChange(); 

  char descr[40], className[40];

  GetDlgItemText(IDC_DESCR, descr, sizeof(descr));
  GetDlgItemText(IDC_CLASS, className, sizeof(className));
  CopyToClipboard(this, descr, className);

  TItemsDialog::CmOk(); 
}
