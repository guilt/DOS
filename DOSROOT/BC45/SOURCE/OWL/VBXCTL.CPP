//----------------------------------------------------------------------------
// ObjectWindows
// (C) Copyright 1993, 1994 by Borland International, All Rights Reserved
//
//   Implementation of class TVbxControl.
//----------------------------------------------------------------------------
#include <owl/owlpch.h>
#include <owl/vbxctl.h>

//----------------------------------------------------------------------------

const char BIVbxDllName[] = "bivbx11.dll";
const char BIVbxClassPrefix[] = "THUNDER";


TBIVbxLibrary::TBIVbxLibrary()
:
#if defined(BI_PLAT_WIN32)
  TModule(BIVbxDllName, false)
#else
  TModule(BIVbxDllName, true)
#endif
{
  if (!::VBXInit(_hInstance, BIVbxClassPrefix))
    THROW(TXVbxLibrary());
}

TBIVbxLibrary::~TBIVbxLibrary()
{
  ::VBXTerm();
}

//----------------------------------------------------------------------------
//
// Exception class
//

TBIVbxLibrary::TXVbxLibrary::TXVbxLibrary() : TXOwl(IDS_VBXLIBRARYFAIL)
{
}

TXOwl*
TBIVbxLibrary::TXVbxLibrary::Clone()
{
  return new TXVbxLibrary(*this);
}

void
TBIVbxLibrary::TXVbxLibrary::Throw()
{
  THROW( *this );
}

//----------------------------------------------------------------------------

DEFINE_RESPONSE_TABLE2(TVbxControl, TControl, TVbxEventHandler)
  EV_MESSAGE(WM_VSCROLL,EvDefaultProcessing),
  EV_MESSAGE(WM_HSCROLL,EvDefaultProcessing),
  EV_MESSAGE(WM_COMPAREITEM,EvDefaultProcessing),
  EV_MESSAGE(WM_DELETEITEM,EvDefaultProcessing),
  EV_MESSAGE(WM_DRAWITEM,EvDefaultProcessing),
  EV_MESSAGE(WM_MEASUREITEM,EvDefaultProcessing),
END_RESPONSE_TABLE;

IMPLEMENT_CASTABLE(TVbxControl);

//
// constructor for a TVbxControl object
//
TVbxControl::TVbxControl(TWindow*        parent,
                         int             id,
                         const char far* vbxName,
                         const char far* vbxClass,
                         const char far* title,
                         int             x,
                         int             y,
                         int             w,
                         int             h,
                         long            initLen,
                         void far*       initData,
                         TModule*        module)
:
  TControl(parent, id, title, x, y, w, h, module)
{
  VbxName = strnewdup(vbxName);
  VbxClass = strnewdup(vbxClass);
  HCtl = 0;
  InitLen = initLen;
  InitData = initData;
  Attr.Style = 0;
}

void
TVbxControl::SetupWindow()
{
  TControl::SetupWindow();

  // If we haven't bound to HCtl yet, do it here
  //
  if (!HCtl)
    HCtl = ::VBXGetHctl(HWindow);
}

//
// constructor for a TVbxControl to be associated with a MS-Windows
// interface element created by MS-Windows from a resource definition
//
TVbxControl::TVbxControl(TWindow*   parent,
                         int        resourceId,
                         TModule*   module)
  : TControl(parent, resourceId, module)
{
  VbxName = 0;
  VbxClass = 0;
  HCtl = 0;
  InitLen = 0;
  InitData = 0;
}

TVbxControl::~TVbxControl()
{
  delete VbxName;
  delete VbxClass;
}

LRESULT TVbxControl::EvDefaultProcessing(WPARAM, LPARAM)
{
  return DefaultProcessing();
}

//
// Return name of VBX window class
//
char far*
TVbxControl::GetClassName()
{
  return "VBCONTROL";
}

//
// Perform MS Windows window creation
//
void
TVbxControl::PerformCreate(int menuOrId)
{
  HFORMFILE formFile = 0;

  if (InitData)
    formFile = ::VBXCreateFormFile(InitLen,InitData);

  HCtl = ::VBXCreate(Parent->HWindow, menuOrId, VbxName, VbxClass, Title,
                     Attr.Style, Attr.X, Attr.Y, Attr.W, Attr.H, formFile);
  if (formFile)
    ::VBXDeleteFormFile(formFile);

  HWindow = ::VBXGetHwnd(HCtl);
}

//
// Get a string property
//
bool
TVbxControl::GetProp(int prop, string& value, int /*index*/)
{
#if defined(BI_PLAT_WIN32)
  uint32 strHandle;
  if (!VBXGetProp(HCtl, prop, &strHandle))
    return false;

  char buf[256];
  if (!::VBXGetCStringBuf(HSZ(strHandle), buf, sizeof(buf)))
    return false;
  value = buf;
  ::VBXDestroyCString(HSZ(strHandle));
  return true;
#else
  uint32 strHandle;
  if (!VBXGetProp(HCtl, prop, &strHandle))
    return false;

  char far* str = ::VBXGetCStringPtr(HSZ(strHandle));
  value = str;
  ::VBXDestroyCString(HSZ(strHandle));
  return true;
#endif
}

//
// Get a VBX property
//
bool
TVbxControl::GetVBXProperty(int propIndex, void far* value, int arrayIndex)
{
  if (arrayIndex == -1)
    return ::VBXGetProp(HCtl, propIndex, value);
  else
    return ::VBXGetArrayProp(HCtl, propIndex, arrayIndex, value);
}

//
// Set a VBX property
//
bool
TVbxControl::SetVBXProperty(int propIndex, int32 value, int arrayIndex)
{
  if (arrayIndex == -1)
    return ::VBXSetProp(HCtl, propIndex, value);
  else
    return ::VBXSetArrayProp(HCtl, propIndex, arrayIndex, value);
}


//----------------------------------------------------------------------------

DEFINE_RESPONSE_TABLE(TVbxEventHandler)
  EV_MESSAGE(WM_VBXFIREEVENT, EvVbxDispatch),
  EV_MESSAGE(WM_VBXINITFORM, EvVbxInitForm),
END_RESPONSE_TABLE;

class TVbxEventInfo : public TEventHandler::TEventInfo {
  public:
    TVbxEventInfo(const char far* eventName, uint msg, uint id = 0)
      : TEventHandler::TEventInfo(msg, id), EventName(eventName) {}

    const char far* EventName;
};

//
// Compare a response table entry to an eventinfo struct, looking for a
// string version of an entry.
// String is in dispatcher field of the entry, & the Entry field of the info.
// If found, replace with i_LPARAM_Dispatch and insert the info's msg into
// the msg field.
//
static bool
VbxEqualOperator(TGenericTableEntry __RTFAR& entry,
                 TEventHandler::TEventInfo& info)
{
  if (entry.Msg == WM_VBXNAME && entry.Id == info.Id &&
      strcmpi((const char far*)(*(TVbxEventInfo*)&info).EventName,
              (const char far*)entry.Dispatcher) == 0) {
     entry.Msg = info.Msg;
     entry.Dispatcher = (TAnyDispatcher)::i_LPARAM_Dispatch;
     return true;
   }
   return false;
}

//
// Handle a VBX fire event message by forwarding to control and/or
// sub-dispatching to specific event handlers.
//
LRESULT
TVbxEventHandler::EvVbxDispatch(WPARAM wp, LPARAM lp)
{
  VBXEVENT far* e = (VBXEVENT far*)lp;
  TVbxEventInfo eventInfo(e->EventName, WM_VBXBASE + e->EventIndex,
                          ::GetDlgCtrlID(e->Window));

  //
  // If the control is not us, then send the fire event message to it to give
  // it first crack.
  //
  TWindow* ctl = GetWindowPtr(e->Window);
  if (ctl &&
    STATIC_CAST(TEventHandler*, ctl) != STATIC_CAST(TEventHandler*, this))
    if (ctl->HandleMessage(WM_VBXFIREEVENT, wp, lp))
      return 1;

  //
  // See if we have a handler for this event
  //
  if (Find(eventInfo) || Find(eventInfo, VbxEqualOperator))
    return Dispatch(eventInfo, wp, lp);
  return 0;
}

LRESULT
TVbxEventHandler::EvVbxInitForm(WPARAM wp, LPARAM lp)
{
  HWND hWnd = HWND(wp);
#if defined(BI_PLAT_WIN32)
  HINSTANCE hInst = (HINSTANCE)::GetWindowLong(hWnd, GWL_HINSTANCE);
#else
  HINSTANCE hInst = (HINSTANCE)::GetWindowWord(hWnd, GWW_HINSTANCE);
#endif
  return ::VBXInitDialog(hWnd, hInst, (char far*)lp) ? 1 : -1;
}
