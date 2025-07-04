//
//----------------------------------------------------------------------------
// ObjectComponents
// (C) Copyright 1994 by Borland International, All Rights Reserved
//
// TAutoVal implementation
//----------------------------------------------------------------------------
#include <ocf/ocfpch.h>
#include <ocf/autodefs.h>

//____________________________________________________________________________
//
// TAutoVal assignment operators (others are inline)
//____________________________________________________________________________

void TAutoVal::operator =(TAutoString s)
{
  vt = atString;
  bstrVal = ::SysAllocString((const OLECHAR far*)s);
  SetLocale(s.GetLangId() ? s.GetLangId() : TLocaleString::NativeLangId);
}

void TAutoVal::operator =(const string& s)
{
  vt = atString;
  bstrVal = ::SysAllocString(s.c_str());
  SetLocale(TLocaleString::NativeLangId);
}

//
// should add operator==(TLocaleString) which translates to proper LangId
// this requires Set/GetLocale to be used for atVoid initialized variants
//

//____________________________________________________________________________
//
// TAutoVal conversion operators
//____________________________________________________________________________

void TAutoVal::SetLocale(TLocaleId locale)
{
  switch (vt) {
  case atVoid:
  case atString:
  case atObject:
    p.Locale = locale;
  };
}

TLocaleId TAutoVal::GetLocale() const
{
  switch (vt) {
  case atVoid:
  case atString:
  case atObject:
    return p.Locale;
  };
  return 0;
}

TLangId TAutoVal::GetLanguage() const
{
  switch (vt) {
  case atVoid:
  case atString:
  case atObject:
    return LANGIDFROMLCID(p.Locale);
  };
  return 0;
}

TAutoVal::operator unsigned char()
{
  unsigned char v;
  switch(vt) {
  case atByte:    return bVal;
  case atShort:   if(::VarUI1FromI2(iVal,  &v)) break; return v;
  case atLong:    if(::VarUI1FromI4(lVal,  &v)) break; return v;
  case atFloat:   if(::VarUI1FromR4(fltVal,&v)) break; return v;
  case atDouble:  if(::VarUI1FromR8(dblVal,&v)) break; return v;
  case atCurrency:if(::VarUI1FromCy(cyVal, &v)) break; return v;
  case atDatetime:if(::VarUI1FromDate(date,&v)) break; return v;
  case atString:  if(::VarUI1FromStr(bstrVal,GetLocale(),0L,&v)) break; return v;
  case atObject:  if(::VarUI1FromDisp(pdispVal,GetLocale(),&v)) break; return v;
  case atBool:    return (unsigned char)(boolVal ? 1 : 0);
  case atByRef+atByte:    return *pbVal;
  case atByRef+atShort:   if(::VarUI1FromI2(*piVal,  &v)) break; return v;
  case atByRef+atLong:    if(::VarUI1FromI4(*plVal,  &v)) break; return v;
  case atByRef+atFloat:   if(::VarUI1FromR4(*pfltVal,&v)) break; return v;
  case atByRef+atDouble:  if(::VarUI1FromR8(*pdblVal,&v)) break; return v;
  case atByRef+atCurrency:if(::VarUI1FromCy(*pcyVal, &v)) break; return v;
  case atByRef+atDatetime:if(::VarUI1FromDate(*pdate,&v)) break; return v;
  case atByRef+atString:  if(::VarUI1FromStr(*pbstrVal,GetLocale(),0L,&v)) break; return v;
  case atByRef+atBool:    return (unsigned char)(*pbool ? 1 : 0);
  }
  throw TXAuto(TXAuto::xConversionFailure);
}

TAutoVal::operator short()
{
  short v;
  switch(vt) {
  case atByte:    return (short)bVal;
  case atShort:   return iVal;
  case atLong:    if (lVal>0x7FFFL || lVal <0xFFFF8000L) break; return (short)lVal;
  case atFloat:   if(::VarI2FromR4(fltVal,&v)) break; return v;
  case atDouble:  if(::VarI2FromR8(dblVal,&v)) break; return v;
  case atCurrency:if(::VarI2FromCy(cyVal, &v)) break; return v;
  case atDatetime:if(::VarI2FromDate(date,&v)) break; return v;
  case atString:  if(::VarI2FromStr(bstrVal,GetLocale(),0L,&v)) break; return v;
  case atObject:  if(::VarI2FromDisp(pdispVal,GetLocale(),&v)) break; return v;
  case atBool:    return short(boolVal ? 1 : 0);
  case atByRef+atByte:    return (short)*pbVal;
  case atByRef+atShort:   return *piVal;
  case atByRef+atLong:    if (*plVal>0x7FFFL || *plVal <0xFFFF8000L) break; return (short)*plVal;
  case atByRef+atFloat:   if(::VarI2FromR4(*pfltVal,&v)) break; return v;
  case atByRef+atDouble:  if(::VarI2FromR8(*pdblVal,&v)) break; return v;
  case atByRef+atCurrency:if(::VarI2FromCy(*pcyVal, &v)) break; return v;
  case atByRef+atDatetime:if(::VarI2FromDate(*pdate,&v)) break; return v;
  case atByRef+atString:  if(::VarI2FromStr(*pbstrVal,GetLocale(),0L,&v)) break; return v;
  case atByRef+atBool:    return short(*pbool ? 1 : 0);
  }
  throw TXAuto(TXAuto::xConversionFailure);
}

TAutoVal::operator long()
{
  long v;
  switch(vt) {
  case atByte:    return (long)bVal;
  case atShort:   return (long)iVal;
  case atLong:    return lVal;
  case atFloat:   if(::VarI4FromR4(fltVal,&v)) break; return v;
  case atDouble:  if(::VarI4FromR8(dblVal,&v)) break; return v;
  case atCurrency:if(::VarI4FromCy(cyVal, &v)) break; return v;
  case atDatetime:if(::VarI4FromDate(date,&v)) break; return v;
  case atString:  if(::VarI4FromStr(bstrVal,GetLocale(),0L,&v)) break; return v;
  case atObject:  if(::VarI4FromDisp(pdispVal,GetLocale(),&v)) break; return v;
  case atBool:    return boolVal ? 1L : 0L;
  case atByRef+atByte:    return (long)*pbVal;
  case atByRef+atShort:   return (long)*piVal;
  case atByRef+atLong:    return *plVal;
  case atByRef+atFloat:   if(::VarI4FromR4(*pfltVal,&v)) break; return v;
  case atByRef+atDouble:  if(::VarI4FromR8(*pdblVal,&v)) break; return v;
  case atByRef+atCurrency:if(::VarI4FromCy(*pcyVal, &v)) break; return v;
  case atByRef+atDatetime:if(::VarI4FromDate(*pdate,&v)) break; return v;
  case atByRef+atString:  if(::VarI4FromStr(*pbstrVal,GetLocale(),0L,&v)) break; return v;
  case atByRef+atBool:    return *pbool ? 1L : 0L;
  }
  throw TXAuto(TXAuto::xConversionFailure);
}

TAutoVal::operator TBool()
{
  switch(vt) {
  case atByte:    return static_cast<TBool>(bVal != 0);
  case atShort:   return static_cast<TBool>(iVal != 0);
  case atLong:    return static_cast<TBool>(lVal != 0);
  case atFloat:   return static_cast<TBool>(fltVal != 0);
  case atDouble:  return static_cast<TBool>(dblVal != 0);
  case atCurrency:return static_cast<TBool>(cyVal.Lo!=0 || cyVal.Hi != 0);
  case atDatetime:return static_cast<TBool>(date != 0);
  case atString:  {short v; if(::VarBoolFromStr(bstrVal,GetLocale(),0L,&v)) break; return static_cast<TBool>(v!=0);}
  case atObject:  {short v; if(::VarBoolFromDisp(pdispVal,GetLocale(),&v)) break; return static_cast<TBool>(v!=0);}
  case atBool:    return static_cast<TBool>(boolVal != 0);  // note: VARIANT bool TRUE is -1
  case atByRef+atByte:    return static_cast<TBool>(*pbVal != 0);
  case atByRef+atShort:   return static_cast<TBool>(*piVal != 0);
  case atByRef+atLong:    return static_cast<TBool>(*plVal != 0);
  case atByRef+atFloat:   return static_cast<TBool>(*pfltVal != 0);
  case atByRef+atDouble:  return static_cast<TBool>(*pdblVal != 0);
  case atByRef+atCurrency:return static_cast<TBool>(pcyVal->Lo != 0 || pcyVal->Hi != 0);
  case atByRef+atDatetime:return static_cast<TBool>(*pdate != 0);
  case atByRef+atString:  {short v; if(::VarBoolFromStr(*pbstrVal,GetLocale(),0L,&v)) break; return static_cast<TBool>(v!=0);}
  case atByRef+atBool:    return static_cast<TBool>(*pbool != 0);
  }
  throw TXAuto(TXAuto::xConversionFailure);
}

TAutoVal::operator float()
{
  float v;
  switch(vt) {
  case atByte:     if(::VarR4FromUI1(bVal,&v)) break; return v;
  case atShort:    if(::VarR4FromI2(iVal, &v)) break; return v;
  case atLong:     if(::VarR4FromI4(lVal, &v)) break; return v;
  case atFloat:    return fltVal;
  case atDouble:   if(::VarR4FromR8(dblVal,&v)) break; return v;
  case atCurrency: if(::VarR4FromCy(cyVal, &v)) break; return v;
  case atDatetime: if(::VarR4FromDate(date,&v)) break; return v;
  case atString:   if(::VarR4FromStr(bstrVal,GetLocale(),0L,&v)) break; return v;
  case atObject:   if(::VarR4FromDisp(pdispVal,GetLocale(),&v)) break; return v;
  case atBool:     if(::VarR4FromBool(boolVal,&v)) break; return v;
  case atByRef+atByte:    if(::VarR4FromUI1(*pbVal,&v)) break; return v;
  case atByRef+atShort:   if(::VarR4FromI2(*piVal, &v)) break; return v;
  case atByRef+atLong:    if(::VarR4FromI4(*plVal, &v)) break; return v;
  case atByRef+atFloat:   return *pfltVal;
  case atByRef+atDouble:  if(::VarR4FromR8(*pdblVal,&v)) break; return v;
  case atByRef+atCurrency:if(::VarR4FromCy(*pcyVal, &v)) break; return v;
  case atByRef+atDatetime:if(::VarR4FromDate(*pdate,&v)) break; return v;
  case atByRef+atString:  if(::VarR4FromStr(*pbstrVal,GetLocale(),0L,&v)) break; return v;
  case atByRef+atBool:    if(::VarR4FromBool(*pbool,&v)) break; return v;
  }
  throw TXAuto(TXAuto::xConversionFailure);
}

TAutoVal::operator double()
{
  double v;
  switch(vt) {
  case atByte:    if(::VarR8FromUI1(bVal,&v)) break; return v;
  case atShort:   if(::VarR8FromI2(iVal, &v)) break; return v;
  case atLong:    if(::VarR8FromI4(lVal, &v)) break; return v;
  case atFloat:   if(::VarR8FromR4(fltVal,&v)) break; return v;
  case atDouble:  return dblVal;
  case atCurrency:if(::VarR8FromCy(cyVal, &v)) break; return v;
  case atDatetime:if(::VarR8FromDate(date,&v)) break; return v;
  case atString:  if(::VarR8FromStr(bstrVal,GetLocale(),0L,&v)) break; return v;
  case atObject:  if(::VarR8FromDisp(pdispVal,GetLocale(),&v)) break; return v;
  case atBool:    if(::VarR8FromBool(boolVal,&v)) break; return v;
  case atByRef+atByte:    if(::VarR8FromUI1(*pbVal,&v)) break; return v;
  case atByRef+atShort:   if(::VarR8FromI2(*piVal, &v)) break; return v;
  case atByRef+atLong:    if(::VarR8FromI4(*plVal, &v)) break; return v;
  case atByRef+atFloat:   if(::VarR8FromR4(*pfltVal,&v)) break; return v;
  case atByRef+atDouble:  return *pdblVal;
  case atByRef+atCurrency:if(::VarR8FromCy(*pcyVal, &v)) break; return v;
  case atByRef+atDatetime:if(::VarR8FromDate(*pdate,&v)) break; return v;
  case atByRef+atString:  if(::VarR8FromStr(*pbstrVal,GetLocale(),0L,&v)) break; return v;
  case atByRef+atBool:    if(::VarR8FromBool(*pbool,&v)) break; return v;
  }
  throw TXAuto(TXAuto::xConversionFailure);
}

TAutoVal::operator TAutoDate()
{
  DATE v;
  switch(vt) {
  case atByte:     if(::VarDateFromUI1(bVal,&v)) break; return v;
  case atShort:    if(::VarDateFromI2(iVal, &v)) break; return v;
  case atLong:     if(::VarDateFromI4(lVal, &v)) break; return v;
  case atFloat:    if(::VarDateFromR4(fltVal,&v)) break; return v;
  case atDouble:   if(::VarDateFromR8(dblVal,&v)) break; return v;
  case atDatetime: return date;
  case atString:   if(::VarDateFromStr(bstrVal,GetLocale(),0L,&v)) break; return v;
  case atObject:   if(::VarDateFromDisp(pdispVal,GetLocale(),&v)) break; return v;
  case atBool:     if(::VarDateFromBool(boolVal,&v)) break; return v;
  case atByRef+atByte:    if(::VarDateFromUI1(*pbVal,&v)) break; return v;
  case atByRef+atShort:   if(::VarDateFromI2(*piVal, &v)) break; return v;
  case atByRef+atLong:    if(::VarDateFromI4(*plVal, &v)) break; return v;
  case atByRef+atFloat:   if(::VarDateFromR4(*pfltVal,&v)) break; return v;
  case atByRef+atDouble:  if(::VarDateFromR8(*pdblVal,&v)) break; return v;
  case atByRef+atDatetime:return date;
  case atByRef+atString:  if(::VarDateFromStr(*pbstrVal,GetLocale(),0L,&v)) break; return v;
  case atByRef+atBool:    if(::VarDateFromBool(*pbool,&v)) break; return v;
  }
  throw TXAuto(TXAuto::xConversionFailure);
}

TAutoVal::operator TAutoCurrency()
{
  TAutoCurrency v;
  HRESULT stat = HR_NOERROR;
  switch(vt) {
  case atByte:     stat = ::VarCyFromUI1(bVal, &v); break;
  case atShort:    stat = ::VarCyFromI2(iVal,  &v); break;
  case atLong:     stat = ::VarCyFromI4(lVal,  &v); break;
  case atFloat:    stat = ::VarCyFromR4(fltVal,&v); break;
  case atDouble:   stat = ::VarCyFromR8(dblVal,&v); break;
  case atCurrency: break;
  case atString:   stat = ::VarCyFromStr(bstrVal,GetLocale(),0L,&v); break;
  case atObject:   stat = ::VarCyFromDisp(pdispVal,GetLocale(),&v); break;
  case atBool:     stat = ::VarCyFromBool(boolVal,&v); break;
  case atByRef+atByte:    stat = ::VarCyFromUI1(*pbVal, &v); break;
  case atByRef+atShort:   stat = ::VarCyFromI2(*piVal,  &v); break;
  case atByRef+atLong:    stat = ::VarCyFromI4(*plVal,  &v); break;
  case atByRef+atFloat:   stat = ::VarCyFromR4(*pfltVal,&v); break;
  case atByRef+atDouble:  stat = ::VarCyFromR8(*pdblVal,&v); break;
  case atByRef+atCurrency:break;
  case atByRef+atString:  stat = ::VarCyFromStr(*pbstrVal,GetLocale(),0L,&v); break;
  case atByRef+atBool:    stat = ::VarCyFromBool(*pbool,&v); break;
  default:         stat = (HRESULT)-1;
  }
  if (stat != HR_NOERROR)
    throw TXAuto(TXAuto::xConversionFailure);
  return v;
}

//
// Convert TAutoVal to TUString, used by TAutoString contructor and assignment
//
TAutoVal::operator TUString*()
{
  BSTR v;
  HRESULT stat;
#if defined(BI_PLAT_WIN32)
  LCID lcid = MAKELCID(LangUserDefault, SORT_DEFAULT);
#else
  LCID lcid = MAKELCID(LangUserDefault);
#endif

  switch (vt) {
  case atByte:     stat = ::VarBstrFromUI1(bVal, lcid,0, &v); break;
  case atShort:    stat = ::VarBstrFromI2(iVal,  lcid,0, &v); break;
  case atLong:     stat = ::VarBstrFromI4(lVal,  lcid,0, &v); break;
  case atFloat:    stat = ::VarBstrFromR4(fltVal,lcid,0, &v); break;
  case atDouble:   stat = ::VarBstrFromR8(dblVal,lcid,0, &v); break;
  case atCurrency: stat = ::VarBstrFromCy(cyVal ,lcid,0, &v); break;
  case atDatetime: stat = ::VarBstrFromDate(date,lcid,0, &v); break;
  case atString:   if (bstrVal) vt = atLoanedBSTR;
             return (s.Holder=TUString::Create(bstrVal, true, GetLanguage()));
  case atObject:   stat = ::VarBstrFromDisp(pdispVal,GetLocale(),0, &v); break;
  case atBool:     stat = ::VarBstrFromBool(boolVal,lcid,0, &v); break;
  case atByRef+atByte:     stat = ::VarBstrFromUI1(*pbVal, lcid,0, &v); break;
  case atByRef+atShort:    stat = ::VarBstrFromI2(*piVal,  lcid,0, &v); break;
  case atByRef+atLong:     stat = ::VarBstrFromI4(*plVal,  lcid,0, &v); break;
  case atByRef+atFloat:    stat = ::VarBstrFromR4(*pfltVal,lcid,0, &v); break;
  case atByRef+atDouble:   stat = ::VarBstrFromR8(*pdblVal,lcid,0, &v); break;
  case atByRef+atCurrency: stat = ::VarBstrFromCy(*pcyVal ,lcid,0, &v); break;
  case atByRef+atDatetime: stat = ::VarBstrFromDate(*pdate,lcid,0, &v); break;
  case atByRef+atString:   if (*pbstrVal) vt = atByRef+atLoanedBSTR;
           return (s.Holder=TUString::Create(*pbstrVal, true, GetLanguage()));
  case atByRef+atBool:     stat = ::VarBstrFromBool(*pbool,lcid,0,&v);break;
  default:         stat = (HRESULT)-1;
  }
  if (stat != HR_NOERROR)
    throw TXAuto(TXAuto::xConversionFailure);
  return TUString::Create(v, false, LANGIDFROMLCID(lcid));
}

//
// Convert TAutoVal to string, high performance if already of string type
//
TAutoVal::operator string()
{
  BSTR v;
  HRESULT stat;
#if defined(BI_PLAT_WIN32)
  LCID lcid = MAKELCID(LangUserDefault, SORT_DEFAULT);
#else
  LCID lcid = MAKELCID(LangUserDefault);
#endif

  switch (vt) {
  case atByte:     stat = ::VarBstrFromUI1(bVal, lcid,0, &v); break;
  case atShort:    stat = ::VarBstrFromI2(iVal,  lcid,0, &v); break;
  case atLong:     stat = ::VarBstrFromI4(lVal,  lcid,0, &v); break;
  case atFloat:    stat = ::VarBstrFromR4(fltVal,lcid,0, &v); break;
  case atDouble:   stat = ::VarBstrFromR8(dblVal,lcid,0, &v); break;
  case atCurrency: stat = ::VarBstrFromCy(cyVal ,lcid,0, &v); break;
  case atDatetime: stat = ::VarBstrFromDate(date,lcid,0, &v); break;
#if defined(BI_OLECHAR_WIDE)
  case atString:   return string(TString(bstrVal));
#else
  case atString:   return string(bstrVal);
#endif
  case atObject:   stat = ::VarBstrFromDisp(pdispVal,GetLocale(),0, &v); break;
  case atBool:     stat = ::VarBstrFromBool(boolVal,lcid,0, &v); break;
  case atByRef+atByte:     stat = ::VarBstrFromUI1(*pbVal, lcid,0, &v); break;
  case atByRef+atShort:    stat = ::VarBstrFromI2(*piVal,  lcid,0, &v); break;
  case atByRef+atLong:     stat = ::VarBstrFromI4(*plVal,  lcid,0, &v); break;
  case atByRef+atFloat:    stat = ::VarBstrFromR4(*pfltVal,lcid,0, &v); break;
  case atByRef+atDouble:   stat = ::VarBstrFromR8(*pdblVal,lcid,0, &v); break;
  case atByRef+atCurrency: stat = ::VarBstrFromCy(*pcyVal ,lcid,0, &v); break;
  case atByRef+atDatetime: stat = ::VarBstrFromDate(*pdate,lcid,0, &v); break;
#if defined(BI_OLECHAR_WIDE)
  case atByRef+atString:   return string(TString(*pbstrVal));
#else
  case atByRef+atString:   return string(*pbstrVal);
#endif
  case atByRef+atBool:     stat = ::VarBstrFromBool(*pbool,lcid,0,&v); break;
  default:         stat = (HRESULT)-1;
  }
  if (stat != HR_NOERROR)
    throw TXAuto(TXAuto::xConversionFailure);
#if defined(BI_OLECHAR_WIDE)
  string s((TString)v);
#else
  string s(v);
#endif
  ::SysFreeString(v);
  return s;
}

TAutoVal::operator unsigned short()
{
  long temp = operator long();
  if (temp < 0 || temp > 65535L)
    throw TXAuto(TXAuto::xConversionFailure);
  return (unsigned short)temp;
}

//
// Pointer data type conversion operators
//
TAutoVal::operator unsigned char far*() {ConvRef(atByte); return pbVal;}
TAutoVal::operator short  far*() {ConvRef(atShort);  return piVal;}
TAutoVal::operator unsigned short far*()
       {ConvRef(atShort); return (unsigned short far*)piVal;} // may overflow!
TAutoVal::operator long   far*() {ConvRef(atLong);   return plVal;}
TAutoVal::operator unsigned long far*()
       {ConvRef(atLong); return (unsigned long far*)plVal;}  // may overflow!
TAutoVal::operator TBool   far*() {ConvRef(atBool); return (TBool far*)pbool;}
TAutoVal::operator float  far*() {ConvRef(atFloat);  return pfltVal;}
TAutoVal::operator double far*() {ConvRef(atDouble); return pdblVal;}
TAutoVal::operator TAutoDate far*() {ConvRef(atDatetime); return (TAutoDate far*)pdate;}
TAutoVal::operator TAutoCurrency far*() {ConvRef(atDatetime); return pcyVal;}

void TAutoVal::ConvRef(int type)
{
  if (type != (vt | atByRef)) {
    throw TXAuto(TXAuto::xConversionFailure);
  }
}

TAutoVal::operator IDispatch*()
{
  if (vt == atObject) {
    if (pdispVal)
      pdispVal->AddRef();
    return pdispVal;
  }
  if (vt == (atObject | atByRef)) {
    if (*ppdispVal)
      (*ppdispVal)->AddRef();
    return *ppdispVal;
  }
  throw TXAuto(TXAuto::xConversionFailure);
}

TAutoVal::operator IUnknown*()
{
  if (vt == atUnknown) {
    if (punkVal)
      punkVal->AddRef();
    return punkVal;
  }
  if (vt == (atUnknown | atByRef)) {
    if (*ppunkVal)
      (*ppunkVal)->AddRef();
    return *ppunkVal;
  }
  throw TXAuto(TXAuto::xConversionFailure);
}


TAutoVal::operator IDispatch&()
{
  if (vt == atObject && pdispVal)
    return *pdispVal;
  if (vt == (atObject | atByRef) && *ppdispVal)
    return **ppdispVal;
  throw TXAuto(TXAuto::xConversionFailure);
}

TAutoVal::operator IUnknown&()
{
  if (vt == atUnknown && punkVal)
    return *punkVal;
  if (vt == (atUnknown | atByRef) && *ppunkVal)
    return **ppunkVal;
  throw TXAuto(TXAuto::xConversionFailure);
}

