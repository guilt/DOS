//----------------------------------------------------------------------------
// ObjectWindows
// (C) Copyright 1994 by Borland International, All Rights Reserved
//
//   Implementation of class TOleMDIFrame.
//----------------------------------------------------------------------------
#define INC_OLE2
#include <owl/owlpch.h>
#include <owl/decmdifr.h>
#include <owl/statusba.h>
#include <owl/ocfevent.h>
#include <owl/uihandle.h>
#include <owl/olemdifr.h>

DIAG_DECLARE_GROUP(OwlOleMenu);

DEFINE_RESPONSE_TABLE2(TOleMDIFrame, TOleFrame, TMDIFrame)
  EV_WM_ACTIVATEAPP,
  EV_OC_APPINSMENUS,
END_RESPONSE_TABLE;

TOleMDIFrame::TOleMDIFrame(const char far* title,
                           TResId          menuResId,
                           TMDIClient&     clientWnd,
                           bool            trackMenuSelection,
                           TModule*        module)
:
  TOleFrame(title, &clientWnd, trackMenuSelection, module),
  TMDIFrame(title, menuResId, clientWnd, module)
{
}

//
//
//
TOleMDIFrame::~TOleMDIFrame()
{
}

//
// Forward Activate messages to OcApp to allow it to notify any embedded servers
// about being activated
//
void
TOleMDIFrame::EvActivateApp(bool active, HTASK hTask)
{
  OcApp->EvActivate(active);
  TMDIFrame::EvActivateApp(active, hTask);
}

//
// Insert our menus into a provided menu bar, possibly merging them with a
// child and servers.
//
bool
TOleMDIFrame::EvOcAppInsMenus(TOcMenuDescr far& sharedMenu)
{
  if (HOldMenu)
    return true;

  // Recreate a temporary composite menu for frame and MDI child
  //
  TMenuDescr compMenuDesc; // empty menudescr
  if (GetMenuDescr())
    compMenuDesc.Merge(*GetMenuDescr());
  const TMenuDescr* childMenu = GetClientWindow()->GetActiveMDIChild()->GetMenuDescr();
  if (childMenu)
    compMenuDesc.Merge(*childMenu);

  // Mask off the server menus
  //
  compMenuDesc.Merge(TMenuDescr(0,  0, -1, 0, -1, 0, -1));

  // Merge into the OLE shared menubar
  //
  TMenuDescr shMenuDescr(sharedMenu.HMenu,
                         sharedMenu.Width[0],
                         sharedMenu.Width[1],
                         sharedMenu.Width[2],
                         sharedMenu.Width[3],
                         sharedMenu.Width[4],
                         sharedMenu.Width[5]);
  shMenuDescr.Merge(compMenuDesc);

  // Copy the shared menu widths back to the OC struct
  //
  for (int i = 0; i < 6; i++)
    sharedMenu.Width[i] = shMenuDescr.GetGroupCount(i);

  // Save the container popups so they can be destroyed later
  //
  StashContainerPopups(shMenuDescr);

  TRACEX(OwlOleMenu, 0, "MDI merged menu " << hex << (uint)sharedMenu.HMenu);
  return true;
}

LRESULT
TOleMDIFrame::DefWindowProc(uint message, WPARAM wParam, LPARAM lParam)
{
  //
  // ::DefFrameProc() will response to WM_SIZE by making the MDI client the
  // same size as the client rectangle; this conflicts with what TLayoutWindow
  // has done
  //
  return message == WM_SIZE ?
                      0 :
                      TMDIFrame::DefWindowProc(message, wParam, lParam);
}
