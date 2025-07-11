//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1991, 1994 by Borland International
//   Tutorial application -- step05.cpp
//----------------------------------------------------------------------------
#include <owl/owlpch.h>
#include <owl/applicat.h>
#include <owl/framewin.h>
#include <owl/dc.h>
#include <owl/inputdia.h>
#include <stdlib.h>

class TDrawWindow : public TWindow {
  public:
    TDrawWindow(TWindow* parent = 0);
   ~TDrawWindow()
    {
      delete DragDC;
      delete Pen;
    }

    void SetPenSize(int newSize);

  protected:
    TDC* DragDC;
    int PenSize;
    TPen* Pen;

    // Override member function of TWindow
    bool CanClose();

    // Message response functions
    void EvLButtonDown(uint, TPoint&);
    void EvRButtonDown(uint, TPoint&);
    void EvMouseMove(uint, TPoint&);
    void EvLButtonUp(uint, TPoint&);

  DECLARE_RESPONSE_TABLE(TDrawWindow);
};

DEFINE_RESPONSE_TABLE1(TDrawWindow, TWindow)
  EV_WM_LBUTTONDOWN,
  EV_WM_RBUTTONDOWN,
  EV_WM_MOUSEMOVE,
  EV_WM_LBUTTONUP,
END_RESPONSE_TABLE;

TDrawWindow::TDrawWindow(TWindow* parent)
{
  Init(parent, 0, 0);
  DragDC  = 0;
  PenSize = 1;
  Pen     = new TPen(TColor::Black, PenSize);
}

bool
TDrawWindow::CanClose()
{
  return MessageBox("Do you want to save?", "Drawing has changed",
                    MB_YESNO | MB_ICONQUESTION) == IDNO;
}

void
TDrawWindow::EvLButtonDown(uint, TPoint& point)
{
  Invalidate();

  if (!DragDC) {
    SetCapture();
    DragDC = new TClientDC(*this);
    DragDC->SelectObject(*Pen);
    DragDC->MoveTo(point);
  }
}

void
TDrawWindow::EvRButtonDown(uint, TPoint&)
{
  char inputText[6];

  wsprintf(inputText, "%d", PenSize);
  if ((TInputDialog(this, "Line Thickness",
                        "Input a new thickness:",
                        inputText,
                        sizeof(inputText))).Execute() == IDOK) {
    int newPenSize = atoi(inputText);

    if (newPenSize < 0)
      newPenSize = 1;

    SetPenSize(newPenSize);
  }
}

void
TDrawWindow::EvMouseMove(uint, TPoint& point)
{
  if (DragDC)
    DragDC->LineTo(point);
}

void
TDrawWindow::EvLButtonUp(uint, TPoint&)
{
  if (DragDC) {
    ReleaseCapture();
    delete DragDC;
    DragDC = 0;
  }
}

void
TDrawWindow::SetPenSize(int newSize)
{
  delete Pen;
  PenSize = newSize;
  Pen     = new TPen(TColor::Black, PenSize);
}

class TDrawApp : public TApplication {
  public:
    TDrawApp() : TApplication() {}

    void InitMainWindow()
    {
      SetMainWindow(new TFrameWindow(0, "Drawing Pad", new TDrawWindow));
    }
};

int
OwlMain(int /*argc*/, char* /*argv*/ [])
{
  return TDrawApp().Run();
}
