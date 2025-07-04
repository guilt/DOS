//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1991,1993 by Borland International
//
// This program demonstrates the use of TFloatingFrame.  It uses
// a class derived from TComboBox that catches the <RETURN> key in an
// edit field and executes the command which was typed.  If the command
// executed sucessfully it is stored in the combo box's list box for
// future retrieval.
// 
// Commands supported:
//  DOS     Executes command.com
//  DIR     Launches WINFILE
//  CD x$   Changes default directory (CD\  CD \)
//  EXIT    Closes OWLCMD
//  x$:     Changes default drive (D:)
//  x$      Executes command x$
// 
//----------------------------------------------------------------------------
#include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\edit.h>
#include <owl\combobox.h>
#include <owl\floatfra.h>
#include "string.h"
#include "dir.h"

const int EDITWIDTH  = 300;  // Width of the combo box
const int CMDBUFSIZE = 256;  // Max command size
const int COMBO_ID   = 1;

// For diagnostics
DIAG_DEFINE_GROUP(OwlCmd,1,0);

//
// A Combo box is actually made up of three windows, an edit
// window, a list box window, and a parent window.  If we need to trap
// an event on the edit or list box window, normal OWL event handlers
// won't work.  These event handlers would trap events to the parent
// window.
// 
// TComboEdit is hard wired to the control ID that MS uses for the edit 
// window. This allows us to trap events, like CR.
//

const int COMBO_LIST_ID = 0x3e8;  // Window ID for list box component
const int COMBO_EDIT_ID = 0x3e9;  // Window ID for edit field component

class TComboEdit : public TEdit {
  public:
    TComboEdit(TComboBox* parent, UINT textLen) : 
      TEdit(parent, COMBO_EDIT_ID, textLen) 
      {
        Combo = parent;
      }

  private:
    // This is where we'll look for c/r and special keys
    void EvChar(UINT key, UINT repeatCount, UINT flags);

    void ExecuteCmd(char *cmd);

    // We could also get Parent from TWindow and downcast it
    TComboBox* Combo;

    char EditBuf[CMDBUFSIZE];
    char CmdBuf[CMDBUFSIZE];

  DECLARE_RESPONSE_TABLE(TComboEdit);
};

DEFINE_RESPONSE_TABLE1(TComboEdit,TEdit)
  EV_WM_CHAR,
END_RESPONSE_TABLE;

//
// This is where we look for the <ENTER> key and execute commands
//
void
TComboEdit::EvChar(UINT key, UINT /*repeatCount*/, UINT /*flags*/)
{
  char*    ptr;
  int      result;
  TWindow* fw;

  if (key == VK_RETURN) {
    //
    // Get Line into local buffer for parsing
    //
    GetText(EditBuf, sizeof(EditBuf));
    if (!EditBuf[0]) // Ignore empty strings
      return;

    strupr(EditBuf);
    ptr = EditBuf;

    //
    // Brain dead parser
    //
    if (strcmp(EditBuf, "DIR") == 0) {
      wsprintf(CmdBuf,"winfile");
      ExecuteCmd(CmdBuf);
      return;

    } else if (strcmp(EditBuf,"DOS") == 0) {
      wsprintf(CmdBuf,"COMMAND.COM");
      ExecuteCmd(CmdBuf);
      return;

     } else if (strcmp(EditBuf,"EXIT") == 0) {
      //Quit
      PostQuitMessage(0);
      return;

    } else if (strncmp(EditBuf,"CD",2) == 0 && strlen(EditBuf) > 2 ) {
      if (EditBuf[2] == '\\')     
        result = chdir(EditBuf+2);
      else if (EditBuf[2] == ' ') {
        for (char* p = EditBuf+3; *p && *p == ' '; p++);
        result = chdir(p); // Point past space
      } else {
        // Must be a program name starting with "cd"
        ExecuteCmd(EditBuf);
        return;
      }
      if (result) {
        ptr = "Invalid directory";
        MessageBox(ptr,"OWLCMD",MB_OK);
        return;
      } else {
        ExecuteCmd(0); //Just store result and clear edit field
        ptr = getcwd(EditBuf,sizeof(EditBuf));
        if (ptr) {
          fw = GetApplication()->GetMainWindow();
          fw->SetCaption(ptr);
          fw->SetWindowPos(0, TRect(), SWP_DRAWFRAME|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
          
        }
        return;
      }

    } else if (isalpha(EditBuf[0]) && 
        EditBuf[1] == ':' &&
        EditBuf[2] == 0) {
      //
      // Set drive
      //
      setdisk(toupper(EditBuf[0])-'A');
      ptr = getcwd(EditBuf,sizeof(EditBuf));
      if (ptr){
        ExecuteCmd(0); // Store and clear
        fw = GetApplication()->GetMainWindow();
        fw->SetCaption(ptr);
        fw->SetWindowPos(0, TRect(), SWP_DRAWFRAME|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
      }

    } else {
      ExecuteCmd(EditBuf);
      return;
    }
  } else
    DefaultProcessing();

  return;
}

void
TComboEdit::ExecuteCmd(char* cmd)
{
  if (cmd) {
    int result = WinExec(cmd, SW_SHOWNORMAL);
    switch (result) {
      case 0:  cmd = "Out of memory"; break;
      case 2:  cmd = "File not found"; break;
      case 3:  cmd = "Path not found"; break;
      default: cmd = "Error in WinExec"; break;
    }
    if (result <= 32 ) {
      MessageBox(cmd, "OWLCMD", MB_OK);
      return;
    }
  }

  //
  // If we got here, then command was sucessful
  // Store command in pick list buffer, & clear edit control
  //
  Combo->InsertString(EditBuf,0);
  Clear();
}

//------------------------------------------------------------------------

class TLineEdit : public TComboBox {
  public:
    TLineEdit(TWindow* p,int w, int h);

    TComboEdit* Ed;
};                              

TLineEdit::TLineEdit(TWindow* p, int w, int h)
  : TComboBox(p, COMBO_ID, -1, -1, w, h, CBS_DROPDOWN, CMDBUFSIZE-1)
{
  Ed = new TComboEdit(this, CMDBUFSIZE-1);

  // We don't want a sorted list!
  Attr.Style &= ~CBS_SORT;
}

//------------------------------------------------------------------------

class TMyFrame : public TFloatingFrame {
  public:
    TMyFrame(TWindow* client, char* title);

  private:
    void    SetupWindow();

    TLineEdit* Cmd;

  DECLARE_RESPONSE_TABLE(TMyFrame);
};

DEFINE_RESPONSE_TABLE1(TMyFrame, TFloatingFrame)
END_RESPONSE_TABLE;

TMyFrame::TMyFrame(TWindow* client, char* title)
  : TFloatingFrame(0, title, client)
{
  //
  // We can set our own attributes, but must be before EnableTiny...
  //
  Attr.Style = WS_POPUP | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX;

  //
  // Or we can be specific, even make it BIGGER if we want
  // If we set the option CloseBox flag to true, then clicking the box
  // will close the window instead of displaying the system menu
  //
  EnableTinyCaption(58, FALSE);

  //
  // Create our combo box and size it for an edit line and 5 text items
  // What's the correct way to get the height of an edit control?
  //
  int lineH = GetSystemMetrics(SM_CYCAPTION)+2; // 1pixel top & bottom border
  Cmd = new TLineEdit(this, EDITWIDTH, lineH*6);
  Attr.X = (GetSystemMetrics(SM_CXSCREEN) - EDITWIDTH)/2;
  Attr.Y = (GetSystemMetrics(SM_CYSCREEN) - lineH*6)/2;
  Attr.W = EDITWIDTH;
  Attr.H = 0;  // Resize ourselves later, when we know the actual size
}

void
TMyFrame::SetupWindow()
{
  TFloatingFrame::SetupWindow();

  //
  // Resize window to actual combo box size
  //
  TRect cr = Cmd->GetWindowRect();
  TRect newRect = GetWindowRect();
  MoveWindow(newRect.left, newRect.top, 
             newRect.Width(), CaptionHeight + cr.Height(), TRUE);

  char buf[MAXDIR+1];
  if (getcwd(buf, sizeof(buf))) {
//    strlwr(buf);
    SetCaption(buf);
  }
}

//------------------------------------------------------------------------

class TOwlCmd : public TApplication {
  public:
    TOwlCmd() : TApplication("Owl Command") {}

  protected:
    void InitMainWindow() {MainWindow = new TMyFrame(0,"OwlCmd");}
};

int
OwlMain(int /*argc*/, char* /*argv*/ [])
{
  return TOwlCmd().Run();
}
