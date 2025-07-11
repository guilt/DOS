//
//----------------------------------------------------------------------------
// ObjectComponents
// (C) Copyright 1994 by Borland International, All Rights Reserved
//
//   Implementation of TOcPart Class
//----------------------------------------------------------------------------
#include <ocf/ocfpch.h>
#include <ocf/ocstorag.h>
#include <ocf/ocpart.h>
#include <ocf/ocdoc.h>
#include <ocf/ocapp.h>
#include <ocf/ocview.h>
#include <stdio.h>  // sprintf

const char  PartFormat[]     = "OcPart.%d";
const char  PartStreamName[] = "\03OcPart";

//
// Construct a new part with a given temp id
//
TOcPart::TOcPart(TOcDocument& document, TOcInitInfo far& initInfo,
                 TRect objPos, int id)
:
  OcDocument(document)
#if defined(BI_DATA_NEAR)
 ,Name(*new string),
  Pos(*new TPoint),
  Size(*new TSize)
#endif
{
  BPart   = 0;
  BPartI  = 0;
  BLPartI = 0;
  Flags = Visible;

  // Part position and size are in logical units
  //
  TRect siteRect = objPos;
  TOcView* view = OcDocument.GetActiveView();
  if (!view)
    return;

  view->ForwardEvent(OC_VIEWSETSITERECT, &siteRect);
  Pos = siteRect.TopLeft();
  Size = siteRect.Size();

  if (!id)
    id = ++OcDocument.PartID;
  char name[32];
  sprintf(name, PartFormat, id);
  Name = name;

  // There must be a Root IStorage associated with each document
  //
  if (!OcDocument.GetStorage())
    TXObjComp::Throw(TXObjComp::xMissingRootIStorage);

  // Create a sub-storage from the parent storage in init
  //
  Storage = new TOcStorage(*OcDocument.GetStorage(), name, true, STGM_READWRITE);

  // Initialize our helpers & then add ourselves to our document's part
  // collection if everything succeeds
  //
  Init(initInfo);
  OcDocument.GetParts().Add(this);
}

//
// Construct a part from a named stream in an oc doc's storage
//
TOcPart::TOcPart(TOcDocument& document, const char far* name)
:
  OcDocument(document),
#if defined(BI_DATA_NEAR)
  Name(*new string(name)),
  Pos(*new TPoint),
  Size(*new TSize)
#else
  Name(name)
#endif
{
  BPart   = 0;
  BPartI  = 0;
  BLPartI = 0;
  Flags = Visible;

  // There must be an IStorage associated with each document
  //
  if (!OcDocument.GetStorage())
    TXObjComp::Throw(TXObjComp::xMissingRootIStorage);

  // Open a sub-storage from the parent storage in init
  //
  Storage = new TOcStorage(*OcDocument.GetStorage(), name, false, STGM_READWRITE);

  // Load our data, and then add ourselves to our document's part collection if
  // everthing succeeds. We'll initialize our helper objects when the parts
  // become visible.
  //
  Load();
  OcDocument.GetParts().Add(this);
}

TOcPart::~TOcPart()
{
  // detach this part from its document
  //
  Detach();

  // delete any associated storage
  //
  delete Storage;
#if defined(BI_DATA_NEAR)
  delete &Name;
  delete &Pos;
  delete &Size;
#endif
}

//
// Perform common ctor initialization
//
void
TOcPart::Init(TOcInitInfo far& initInfo)
{
  AddRef();  // TUnknown defaults to 0, we need 1

  // There must be an IStorage associated with each part, make sure the ctor
  // got it OK
  //
  initInfo.Storage = Storage->GetIStorage();

  // Create part helper
  //
  TXObjComp::Check(
    OcDocument.OcApp.BOleComponentCreate(&BPart, GetOuter(), cidBOlePart),
    TXObjComp::xInternalPartError);

  // Get the interfaces we need & then release the object itself
  //
  if (HRSucceeded(BPart->QueryInterface(IID_IBPart, &(LPVOID)BPartI)))
    BPartI->Release();
  if (HRSucceeded(BPart->QueryInterface(IID_IBLinkable, &(LPVOID)BLPartI)))
    BLPartI->Release();

  HRESULT hr;
  if (!BPartI || !HRSucceeded(hr = BPartI->Init(this, &initInfo))) {
    BPart->Release();
    BPart = 0;
    TXObjComp::Throw(TXObjComp::xPartInitError, hr);
  }

  Rename();
  if (initInfo.How == ihLink)  // Remember that we are a link
    Flags |= Link;

  // New parts become active when they are init'd above. Make sure that our
  // view knows that we are active too.
  //
  if (initInfo.Where == iwNew) {
    Flags |= Active;
    TOcView* activeView = OcDocument.GetActiveView();
    CHECK(activeView);
    activeView->ActivatePart(this);
  }
}

//
// Delete this object. Actually, causes object to shutdown as much as possible
// & then releases a reference.
//
void
TOcPart::Delete()
{
  Activate(false);
  Close();
  Release();
}

//
// Callback from TUnknown's implementation of QueryInterface
//
HRESULT
TOcPart::QueryObject(const IID far& iid, void far* far* iface)
{
  PRECONDITION(iface);
  HRESULT hr;

  // interfaces
  //
     HRSucceeded(hr = IBSite_QueryInterface(this, iid, iface))

  // helpers
  //
  || (BPart && HRSucceeded(hr = BPart->QueryInterface(iid, iface)))
  ;
  return hr;
}

//
// Query server for its interfaces
//
HRESULT
TOcPart::QueryServer(const IID far& iid, void far* far* iface)
{
  PRECONDITION(iface);
  return BPartI->DoQueryInterface(iid, iface);
}


//
// Disconnect servers by closing & releasing our BOle helper
//
bool
TOcPart::Close()
{
  if (!BPartI)
    return true;

  if (HRSucceeded(BPartI->Close())) {
    // release our BOle helper object
    //
    BPart->Release();
    BPart   = 0;
    BPartI  = 0;
    BLPartI = 0;

    // So that it won't get created again in Draw
    //
    Flags |= Closing;
    return true;
  }
  return false;
}

//
// Rename the embed site for linking
//
void
TOcPart::Rename()
{
  TOcView* activeView = OcDocument.GetActiveView();
  CHECK(activeView);

  IBRootLinkable* bLDocumentI;
  activeView->QueryInterface(IID_IBRootLinkable, &(LPVOID)bLDocumentI);
  activeView->Release();

  if (BLPartI && bLDocumentI)
    BLPartI->OnRename(bLDocumentI, GetName());
}

//----------------------------------------------------------------------------
// ISite Implementation--delegates site/view related queries/notifies to the
// active view of this part
//

//
// Show/hide a site.
//
HRESULT _IFUNC
TOcPart::SiteShow(bool show)
{
  Invalidate(invView);

  // When this part is activated, the site is hidden. This is a good time to
  // make sure our state is in sync.
  //
  if (!show) {
    // Make sure the view knows about the active part
    //
    Flags |= Active;
    TOcView* view = OcDocument.GetActiveView();
    if (view) {
      view->ActivatePart(this);
      view->ForwardEvent(OC_VIEWPARTACTIVATE, this);
    }
  }
  return HR_NOERROR;
}

//
// Discard undo stack for our associated [the active] view
//
HRESULT _IFUNC
TOcPart::DiscardUndo()
{
  return HR_NOERROR;
}

//
// Retrieve the site rect [relative to the active view?], and optionally the
// view's rect too?
//
HRESULT _IFUNC
TOcPart::GetSiteRect(TRect far* posRect, TRect far* clipRect)
{
  PRECONDITION(posRect);
  if (!posRect)
    return HR_INVALIDARG;

  TOcView* view = OcDocument.GetActiveView();
  if (!view)
    return HR_FAIL;
  if (posRect)
    *posRect = TRect(Pos, Size);

  view->ForwardEvent(OC_VIEWGETSITERECT, posRect);

  // If we don't know our site size yet, then fail this call. Let the server
  // pick a size.
  //
  if (posRect->right-posRect->left <= 0 || posRect->bottom-posRect->top <= 0) {
    posRect->right = posRect->left;
    posRect->bottom = posRect->top;
    return HR_FAIL;
  }

  if (clipRect)
    view->GetWindowRect(clipRect);
  return HR_NOERROR;
}

//
// Set the site's rect from an in-place active part. Since user is in control
// we generally respect both Pos & Size changes.
//
HRESULT _IFUNC
TOcPart::SetSiteRect(const TRect far* newRect)
{
  PRECONDITION(newRect);
  if (!newRect)
    return HR_INVALIDARG;

  TOcView* view = OcDocument.GetActiveView();
  if (!view)
    return HR_FAIL;

  // Give other views a chance to update
  //
  Invalidate(invView);   // erase old image

  TRect rect(*newRect);

  view->ForwardEvent(OC_VIEWSETSITERECT, &rect);
  Size = rect.Size();
  Pos  = rect.TopLeft();

  // Give other views a chance to update
  //
  Invalidate(invView);    // refresh new image position
  return HR_NOERROR;
}

//
// Set the part's site extent. This comes either after a SetPartRect, or for
// open editing, comes alone.
//
HRESULT _IFUNC
TOcPart::SetSiteExtent(const TSize far* newSize)
{
  PRECONDITION(newSize);
  if (!newSize)
    return HR_INVALIDARG;

  TOcView* view = OcDocument.GetActiveView();
  if (!view)
    return HR_FAIL;

  // Only accept server's size if we don't have a size yet. Always say OK.
  //
//  if (Size.cx > 0 && Size.cy > 0)
//    return HR_NOERROR;

  // Give other views a chance to update
  //
  Invalidate(invView); // display new image

  TSize ext(*newSize);
  TRect siteRect(Pos, ext);

  view->ForwardEvent(OC_VIEWSETSITERECT, &siteRect);
  Size = siteRect.Size();

  // Give other views a chance to update
  //
  Invalidate(invView);    // refresh new image position

  return HR_NOERROR;
}

//
// Get zoom factor for part
//
HRESULT _IFUNC
TOcPart::GetZoom(TOcScaleInfo* zoom)
{
  PRECONDITION(zoom);
  if (!zoom)
    return HR_INVALIDARG;

  TOcView* view = OcDocument.GetActiveView();
  if (!view)
    return HR_FAIL;

  TOcScaleFactor scale(*zoom);
  if (!view->ForwardEvent(OC_VIEWGETSCALE, &scale)) {
    zoom->xD = zoom->xN = zoom->yD = zoom->yN = 1;
  }
  else
    scale.GetScaleFactor(*zoom);

  return HR_NOERROR;
}

//
// Invalidate the site within the active view
//
void _IFUNC
TOcPart::Invalidate(TOcInvalidate type)
{
  TOcView* view = OcDocument.GetActiveView();
  TOcPartChangeInfo changeInfo(this, type);
  if (view)
    view->InvalidatePart(changeInfo);
}

void _IFUNC
TOcPart::OnSetFocus(bool set)
{
  TOcView* view = OcDocument.GetActiveView();
  if (view && set)
    ::SetFocus(view->GetWindow());
}

HRESULT _IFUNC
TOcPart::Init(IBDataProvider far*, IBPart far*, LPCOLESTR, bool)
{
  return HR_FAIL; // never called
}

void _IFUNC
TOcPart::Disconnect()
{
  // no need to do anything
}

//----------------------------------------------------------------------------

//
// Save this part to storage. May be any of:
//   Save to our storage : sameAsLoad==1
//   Copy to a storage   : sameAsLoad==0, remember==0
//   SaveAs a new storage: sameAsLoad==0, remember==1
//
bool
TOcPart::Save(bool sameAsLoad, bool remember)
{
  STATSTG  statstg;
  if (!HRSucceeded(Storage->Stat(&statstg, STATFLAG_NONAME)))
    return false;

  TOcStorage* oldStorage = 0;

  // If not sameAsLoad, then we are saving to a new storage. Switch to that,
  // at least for this save.
  //
  if (!sameAsLoad) {
    oldStorage = Storage;
    Storage = new TOcStorage(*OcDocument.GetStorage(), GetName(), true, STGM_READWRITE);
  }

  // Create/open a stream in our storage to save part information
  //
  TOcStream  stream(*Storage, ::PartStreamName, true, statstg.grfMode);

  // Write TOcPart data into stream, Name was written by our Doc
  //
  if (!HRSucceeded(stream.Write(&Pos, sizeof Pos)))
    return false;

  if (!HRSucceeded(stream.Write(&Size, sizeof Size)))
    return false;

  if (!HRSucceeded(stream.Write(&Flags, sizeof Flags)))
    return false;

  // Now have actual server part write itself to this storage
  //
  bool result = Save(Storage->GetIStorage(), sameAsLoad, remember);

  // If this is a different storage, then either save it (remember) or put
  // it back & clean up.
  //
  if (!sameAsLoad) {
    if (remember) {
      delete oldStorage;
    }
    else {
      delete Storage;
      Storage = oldStorage;
    }
  }

  return result;
}

//
// Load this part from its ocpart stream in its current storage
//
bool
TOcPart::Load()
{
  // Open a stream with oc part information
  //
  STATSTG statstg;
  if (!HRSucceeded(Storage->Stat(&statstg, STATFLAG_NONAME)))
    return false;
  TOcStream  stream(*Storage, ::PartStreamName, false, statstg.grfMode);

  // Read TOcPart data from stream. Server part info will be read in as needed
  // after Init()
  //
  if (!HRSucceeded(stream.Read(&Pos, sizeof Pos)))
    return false;

  if (!HRSucceeded(stream.Read(&Size, sizeof Size)))
    return false;

  if (!HRSucceeded(stream.Read(&Flags, sizeof Flags)))
    return false;
  Flags &= ~(Closing | Active); // These Flags are not persistent

  return true;
}

//
// Update this part's idea of its size via the server, & then return that.
// Use GetRect() to just get the current site rect.
//
TSize
TOcPart::GetSize() const
{
  BPartI->GetPartSize(&const_cast<TSize&>(Size));
  return Size;
}

//
// Set part to the new position given in logical units
//
void
TOcPart::SetPos(const TPoint& pos)
{
  Pos = pos;
//  UpdateRect();
}

//
// Set part to the new size given in logical units
//
void
TOcPart::SetSize(const TSize& size)
{
  Size = size;
//  UpdateRect();
}

//
// Set part to the new rect given in logical units
//
void
TOcPart::UpdateRect()
{
  // Use device units for Bolero
  //
  TRect rect(Pos, Size);
  TOcView* view = OcDocument.GetActiveView();
  if (!view)
    return;

  view->ForwardEvent(OC_VIEWGETSITERECT, &rect);

  BPartI->SetPartPos(&rect);
}

//----------------------------------------------------------------------------
// IBPart pass-thrus not inlined
//
bool
TOcPart::Activate(bool activate)
{
  TOcView* activeView = OcDocument.GetActiveView();
  CHECK(activeView);

  if (activate && activeView->GetActivePart())
    if (!activeView->ActivatePart(0))  // deactivate currently active part, if any
      return false;

  // Makes sure that the part gets the active view as its host.
  // This is important in multi-view situation.
  //
  SetHost(activeView);
  if (!HRSucceeded(BPartI->Activate(activate)))
    return false;

  if (activate) {
    Flags |= Active;
    activeView->SetActivePart(this);
  }
  else {
    Flags &= ~Active;
    activeView->SetActivePart(0);
  }
  return true;
}

void
TOcPart::FinishLoading()
{
  // Load embeded object on demand
  //
  if (!BPartI) {
    TOcInitInfo initInfo(ihEmbed, iwStorage, OcDocument.GetActiveView());
    Init(initInfo);
  }
}


//
// Set data into the server object
//
bool
TOcPart::SetFormatData(TOcFormatInfo far* fmt, HANDLE data, bool release)
{
  IBPart2* bPartI2;
  if (HRSucceeded(BPart->QueryInterface(IID_IBPart2, &(LPVOID)bPartI2)))
    ((IBPart*)bPartI2)->Release();
  else
    return false;

  return HRSucceeded(bPartI2->SetFormatData(fmt, data, release));
}


bool
TOcPart::Save(IStorage* storage, bool sameAsLoad, bool remember)
{
  PRECONDITION(storage);
  if (BPartI)
    return HRSucceeded(BPartI->Save(storage, sameAsLoad, remember));
  return false;
}

bool
TOcPart::Draw(HDC dc, const TRect& pos, const TRect& clip, TOcAspect aspect)
{
  PRECONDITION(dc);

  // Don't draw anything if we are closing down the part
  //
  if (Flags & Closing)
    return true;

  const RECTL posl = { pos.left, pos.top, pos.right, pos.bottom };
  const RECTL clipl = { clip.left, clip.top, clip.right, clip.bottom };

  // Load embeded object on demand
  //
  if (!BPartI) {
    TOcInitInfo initInfo(ihEmbed, iwStorage, OcDocument.GetActiveView());
    Init(initInfo);
    // Update the link
    //
    if (IsLink()) {
      TOcView* view = OcDocument.GetActiveView();
      if (view)
        view->UpdateLinks();
    }

  }

  return HRSucceeded(BPartI->Draw(dc, &posl, &clipl, aspect, drNone));
}

bool
TOcPart::EnumVerbs(const TOcVerb& verb)
{
  if (BPartI)
    return HRIsOK(BPartI->EnumVerbs(const_cast<TOcVerb*>(&verb)));

  return false;
}

bool
TOcPart::DoVerb(UINT whichVerb)
{
  if (BPartI) {
    if (HRSucceeded(BPartI->DoVerb(whichVerb))) {
      TOcView* activeView = OcDocument.GetActiveView();
      CHECK(activeView);
      activeView->SetActivePart(this);  // we may be activated now...
      return true;
    }
  }
  return false;
}

int
TOcPart::Detach()
{
  return OcDocument.GetParts().Detach(this);
}

//----------------------------------------------------------------------------
// CdPartCollection
//

TOcPartCollection::TOcPartCollection()
:
  TCVectorImp<TOcPart*>(0, 10)
{
}

TOcPartCollection::~TOcPartCollection()
{
  Clear();
}

//
// Release parts in the collection
//
void
TOcPartCollection::Clear()
{
  for (int i = Count() - 1; i >= 0; i--) {
    TOcPart* part = (TOcPart*)(*this)[i];
    part->Release();
  }
}

//
// walk thru Part collection & return the last one that logical point hits,
// (first one in Z order)
//
TOcPart*
TOcPartCollection::Locate(TPoint& logicalPoint)
{
  TRect hitRect(logicalPoint, TSize(1,1));

  TOcPart* p = 0;
  for (TOcPartCollectionIter i(*this); i; i++)
    if (i.Current()->IsVisible(hitRect))
      p = (TOcPart*)i.Current();
  return p;
}

//
// Select/unselect all parts
//
bool
TOcPartCollection::SelectAll(bool select)
{
  for (TOcPartCollectionIter i(*this); i; i++)
    i.Current()->Select(select);
  return true;
}

int
TOcPartCollection::Detach(TOcPart* const& part, int del)
{
  int ret = Base::Detach(Find(part));
  if (ret && del)
    const_cast<TOcPart*>(part)->Release();
  return ret;
}

//---------------------------------  OcVerb  -----------------------------------
//
TOcVerb::TOcVerb()
:
  TypeName(0),
  VerbName(0),
  VerbIndex(0),
  CanDirty(false)
{
}

