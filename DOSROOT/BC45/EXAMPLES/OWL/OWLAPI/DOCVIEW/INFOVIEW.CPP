//----------------------------------------------------------------------------
// ObjectWindows - (C) Copyright 1993 by Borland International
//   Implements class TInfoView
//----------------------------------------------------------------------------
#include <owl\owlpch.h>
#include <owl\docmanag.h>
#include <owl\filedoc.h>
#include <owl\dc.h>
#include "infoview.rc"

class _DOCVIEWCLASS TInfoView : public TWindowView {
  public:
    struct Data {
      const char*  PropName;
      char*        PropData;
      int          PropSize;
      int          PropFlags;
    };
    TInfoView(TDocument& doc, TWindow* parent = 0);
   ~TInfoView();
    static LPCSTR StaticName() {return "Info View";}  // put in resource
    LPCSTR   GetViewName() {return StaticName();}
    BOOL     SetDocTitle(LPCSTR docname, int index)
             { Invalidate(); return TWindow::SetDocTitle(docname, index); }
    void Paint(TDC&, BOOL, TRect&);

  protected:
    Data* PropList;
    int   PropCount;
    int   YLoc;
    int   OpenCount;  //temp
    int   CloseCount; //temp
    void  GetInfo();
    void  Init();

    //
    // event handlers
    //
    void  CmInfoOpen();
    BOOL  VnViewOpened(TView*);
    BOOL  VnViewClosed(TView*);
    BOOL  VnDocOpened(int omode);
    BOOL  VnDocClosed(int omode);
    BOOL  VnIsWindow(HWND hWnd) {return HWindow == hWnd;}

  DECLARE_RESPONSE_TABLE(TInfoView);
  DECLARE_STREAMABLE(,TInfoView,1);
};

DEFINE_RESPONSE_TABLE1(TInfoView, TWindow)
  EV_COMMAND(CM_INFOOPEN, CmInfoOpen),
  EV_VN_DOCOPENED,
  EV_VN_DOCCLOSED,
  EV_VN_VIEWOPENED,
  EV_VN_VIEWCLOSED,
  EV_VN_ISWINDOW,
END_RESPONSE_TABLE;

TInfoView::TInfoView(TDocument& doc,TWindow* parent) : TWindowView(doc,parent)
{
  Attr.Style &= ~(WS_BORDER);
  SetViewMenu(new TMenuDescr(IDM_INFOVIEW,0,1,0,0,0,1));
  Init();
}

void TInfoView::Init()
{
  PropCount = Doc->PropertyCount();
  PropList = new Data[PropCount];
  for (int i = 0; i < PropCount; i++) {
    PropList[i].PropName = Doc->PropertyName(i+1);
    PropList[i].PropFlags = Doc->PropertyFlags(i+1);
    PropList[i].PropData = 0;
  }
  OpenCount = CloseCount = 0;  //temp
  GetInfo();
}

TInfoView::~TInfoView()
{
  for (int i = 0; i < PropCount; i++) {
    delete PropList[i].PropData;
  }
  delete PropList;
}

void TInfoView::GetInfo()
{
  BOOL changed = FALSE;
  int prop;
  int len;
  char buf[256+1];

  for (prop = 0; prop < PropCount; prop++) {
    int flags = PropList[prop].PropFlags;
    if ((flags & pfGetText) && !(flags & pfHidden)
    && (len = Doc->GetProperty(prop+1, buf, sizeof(buf)-1)) != 0) {
      if (PropList[prop].PropData) {
        if (flags & pfConstant)
          continue;
        if (len == PropList[prop].PropSize) {
          if (strcmp(buf, PropList[prop].PropData) != 0) {
            strcpy(PropList[prop].PropData, buf);
            changed = TRUE;
          }
          continue;
        }
        delete PropList[prop].PropData;
      
      }
      PropList[prop].PropData = strnewdup(buf);
      PropList[prop].PropSize = len;
      changed = TRUE;
    }
  }
  if (changed)
    Invalidate();
}

//  len = wsprintf(buf, "Document State:  %s  (Opens=%d Closes=%d)", (char far*)(Doc->IsOpen() ? "Open" : "Closed"),OpenCount,CloseCount);

void TInfoView::Paint(TDC& dc, BOOL /*erase*/, TRect&)
{
  TSize size;
  static char separator[] = " = ";
  int sepsize;
  int prop;

  YLoc = 0;
  dc.GetTextExtent(separator, sizeof(separator)-1, size);
  sepsize = size.cx;
  for (prop = 0; prop < PropCount; prop++) {
    if (!PropList[prop].PropData)
      continue;
    int len = strlen(PropList[prop].PropName);
    dc.GetTextExtent(   PropList[prop].PropName, len, size);
    dc.TextOut(0, YLoc, PropList[prop].PropName, len);
    dc.TextOut(size.cx, YLoc, separator, sizeof(separator)-1);
    dc.TextOut(size.cx+sepsize, YLoc, PropList[prop].PropData,
                               strlen(PropList[prop].PropData));
    YLoc += size.cy;
  }
}

void
TInfoView::CmInfoOpen()
{
  if (!Doc->IsOpen()
  && Doc->GetDocPath() != 0
  && Doc->Open(ofRead | shReadWrite | ofNoCreate | ofPriority)) {
//  GetInfo();
    Doc->Close();
    OpenCount--; CloseCount--;
  }
}

BOOL
TInfoView::VnViewOpened(TView*)
{
  GetInfo();
  return TRUE;
}

BOOL
TInfoView::VnViewClosed(TView*)
{
  GetInfo();
  return TRUE;
}

BOOL
TInfoView::VnDocOpened(int)
{
  ++OpenCount;
  GetInfo();
  return TRUE;
}

BOOL
TInfoView::VnDocClosed(int)
{
  ++CloseCount;
  GetInfo();
  return TRUE;
}

IMPLEMENT_STREAMABLE1(TInfoView, TWindowView);

void*
TInfoView::Streamer::Read(ipstream& is, uint32 /*version*/) const
{
  ReadBaseObject((TWindowView*)GetObject(), is);
  GetObject()->Init();
  return GetObject();
}

void
TInfoView::Streamer::Write(opstream &os) const
{
  WriteBaseObject((TWindowView*)GetObject(), os);
}

DEFINE_DOC_TEMPLATE_CLASS(TFileDocument, TInfoView,   InfoTemplate);
InfoTemplate infoTpl("InfoView, All files", "*.*", 0, 0,dtAutoDelete|dtReadOnly);

