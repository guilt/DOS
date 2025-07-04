//
//----------------------------------------------------------------------------
// ObjectComponents
// (C) Copyright 1994 by Borland International, All Rights Reserved
//
//   Implementation of TOcDataProvider Class
//----------------------------------------------------------------------------
#include <ocf/ocfpch.h>
#include <ocf/ocapp.h>
#include <ocf/ocdata.h>

TOcDataProvider::TOcDataProvider(TOcView& ocView, TRegList* regList, IUnknown* outer,
                                 void* userData, TDeleteUserData callBack)
:
  OcView(ocView), BSite(0), BSiteI(0), BLSiteI(0),
  UserData(userData), CBDelete(callBack),
#if defined(BI_DATA_NEAR)
  Origin(*new TPoint(0,0)),
  Extent(*new TSize(0,0))
#else
  Origin(0,0),
  Extent(0,0)
#endif
{
  SetOuter(outer);
  AddRef();    // TUnknown defaults to 0, we need 1

  // Create a site for this data provider
  //
  if (SUCCEEDED(OcView.OcApp.BOleComponentCreate(&BSite, (IUnknown*)(IBDataProvider*)this,
      cidBOleSite))) {

    if (SUCCEEDED(BSite->QueryInterface(IID_IBSite, &(LPVOID)BSiteI)))
      Release();

    // Connect the part and the site
    //
    if (BSiteI) {
      const char* progid = regList->Lookup(OcView.OcApp.IsOptionSet(amDebug) ?
                                           "debugprogid" : "progid");
      BSiteI->Init(this, 0, OleStr(progid), true);
    }

    if (SUCCEEDED(BSite->QueryInterface(IID_IBLinkable,&(LPVOID)BLSiteI)))
      BLSiteI->Release();   // avoid deadlock

    // Remember the dataprovider in OcView
    //
    OcView.SetOcData(this);

    // Set up monikers for selection
    //
    Rename();
  }
}

TOcDataProvider::~TOcDataProvider()
{
  // If the TOcDataProvider object is released by the clipboard
  //
  if (OcView.GetOcData() == this)
    OcView.SetOcData(0);

  // user data clean up
  //
  if (CBDelete)
    CBDelete(UserData);

  if(BSite)
    BSite->Release();
}

//
//
//
HRESULT
TOcDataProvider::QueryObject(const IID far& iid, void far* far* iface)
{
  PRECONDITION(iface);
  HRESULT hr;

  // interfaces
  //
     SUCCEEDED(hr = IBDataProvider_QueryInterface(this, iid, iface))

  // helpers
  //
  || (BSite && SUCCEEDED(hr = BSite->QueryInterface(iid, iface)))
  ;

  return hr;
}

//
// Disconnect from the site
//
void
TOcDataProvider::Disconnect()
{
  if (BSiteI)
    BSiteI->Disconnect();
}

//
// Update item moniker with new name
//
void
TOcDataProvider::Rename()
{
  PRECONDITION(BLSiteI);

  OcView.Rename();

  // Update the item's moniker
  //
  TOcItemName item(true);
  if (OcView.ForwardEvent(OC_VIEWGETITEMNAME, &item))
    BLSiteI->OnRename(OcView.BLDocumentI, OleStr(item.Name));
}

UINT _IFUNC
TOcDataProvider::CountFormats()
{
  return OcView.CountFormats();
}

HRESULT _IFUNC
TOcDataProvider::GetFormat(uint index, TOcFormatInfo far* fmt)
{
  PRECONDITION(fmt);

  return OcView.GetFormat(index, fmt);
}


//
// Request native data for pasting into client application.
// This is only called at paste time (not at copy time).
//
HANDLE _IFUNC
TOcDataProvider::GetFormatData(TOcFormatInfo far* fmt)
{
  PRECONDITION(fmt);

  TOcFormat* format = OcView.FormatList.Find(fmt->Id);
  if (!format || (*format->GetRegName() == 0))
    return 0;

  TOcFormatData formatData(*format, UserData);
  if (OcView.ForwardEvent(OC_VIEWCLIPDATA, &formatData))
    return formatData.Handle;
  else
    return 0;
}

//
// Render the data in the DC provided. May be a MetaFile
// Packup all the args & forward message to real view to paint
//
HRESULT _IFUNC
TOcDataProvider::Draw(HDC dc, const RECTL far* pos, const RECTL far* clip,
                 TOcAspect aspect, TOcDraw bd)
{
  PRECONDITION(dc);
  bool metafile = ::GetDeviceCaps(dc, TECHNOLOGY) == DT_METAFILE;

  // Rely on the bolero shading
  //
  if (bd == drShadingOnly)
    return HR_NOERROR;

  TRect p((int)pos->left, (int)pos->top, (int)pos->right, (int)pos->bottom);
  TRect c((int)clip->left, (int)clip->top, (int)clip->right, (int)clip->bottom);

  if (metafile) {
    p.SetNull();
    ::SetMapMode(dc, MM_ANISOTROPIC);

    ::SetWindowExtEx(dc, Extent.cx, Extent.cy, 0);
    ::SetWindowOrgEx(dc, 0, 0, 0);
  }

  p.Normalize();
  c.Normalize();
  TOcViewPaint vp = { dc, &p, &c, (TOcAspect)aspect, true, 0, UserData };
  bool result = (bool)OcView.ForwardEvent(OC_VIEWPAINT, &vp);

  return HRFailIfZero(result);
}

//
// Return the 'size' of the document that this view is on
//
HRESULT _IFUNC
TOcDataProvider::GetPartSize(TSize far* size)
{
  TOcPartSize ps(true, 0, UserData);

  // Ask the app for initial server extent
  //
  if (!OcView.ForwardEvent(OC_VIEWPARTSIZE, &ps)) {
    // An empty rect as default means that the container
    // decides the size for this server
    //
    ps.PartRect.SetNull();
  }

  Extent = ps.PartRect.Size();
  Origin = ps.PartRect.TopLeft();

  *size = Extent;
  return HR_NOERROR;
}

//
// Save the selection that we are a view on
//
HRESULT _IFUNC
TOcDataProvider::Save(IStorage* storage, BOOL sameAsLoad, BOOL remember)
{
  PRECONDITION(storage);

  TOcSaveLoad ocSave(storage, static_cast<bool>(sameAsLoad),
                     static_cast<bool>(remember), true, UserData);

  return HRFailIfZero((bool)OcView.ForwardEvent(OC_VIEWSAVEPART, &ocSave));
}




