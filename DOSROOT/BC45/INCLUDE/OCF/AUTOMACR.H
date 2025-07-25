//
//----------------------------------------------------------------------------
// ObjectComponents
// (C) Copyright 1994 by Borland International, All Rights Reserved
//
//   Automation Symbol Table, Command, and Proxy Macro Definitions
//----------------------------------------------------------------------------
#if !defined(OCF_AUTOMACR_H)
#define OCF_AUTOMACR_H

#if !defined(OCF_AUTODEFS_H)
# include <ocf/autodefs.h>
#endif

// suppress "Functions taking class-by-value arg(s) are not expanded inline"
#pragma warn -inl

//____________________________________________________________________________
//
// Macros for defining symbol tables
//____________________________________________________________________________
//
//  DEFINE_AUTOCLASS(C++ClassName)
//
//    EXPOSE_METHOD(IntName, ReturnTypeName, ExtName, DocString, HelpContext)
//    EXPOSE_PROPRW(IntName, PropTypeName,   ExtName, DocString, HelpContext)
//    EXPOSE_PROPRO(IntName, PropTypeName,   ExtName, DocString, HelpContext)
//    EXPOSE_PROPWO(IntName, PropTypeName,   ExtName, DocString, HelpContext)
//    EXPOSE_APPLICATION(    AppTypeName,    ExtName, DocString, HelpContext)
//    EXPOSE_QUIT(                           ExtName, DocString, HelpContext)
//
//    REQUIRED_ARG(TypeName, ExtArgName)
//    OPTIONAL_ARG(TypeName, ExtArgName, DefaultValueString)
//
//    EXPOSE_INHERIT(C++ClassName, ExtClassName)
//    EXPOSE_DELEGATE(C++ClassName, ExtClassName, AddressAdjusterFunction)
//
//    EXPOSE_FACTORY(C++ClassName, ExtClassName, C++BaseClass)
//
//  END_AUTOCLASS(C++ClassName , Typeflags,  ExtName, DocString, HelpContext)
//
//  For automated classes which are, inherit from, or delegate to COM objects:
//  Specify the aggregator function for a pre-existing object of the aggreate.
//
//  DEFINE_AUTOAGGREGATE(C++ClassName, AggregatorFunction)
//  END_AUTOAGGREGATE(C++ClassName, ExtClassName, DocString, HelpContext)
//____________________________________________________________________________

#define DEFINE_AUTOCLASS(cls) \
  TAutoSymbol cls::SymbolTable[] = {

#define END_AUTOCLASS(cls, flags, name, doc, help) {{name},{doc}, 0, \
  flags,0,TAutoSymbol::InitAutoDestructor(cls::TCommand_dtr::Build),help} }; \
  TAutoClass cls::ClassInfo(cls::SymbolTable, cls::SymbolTable + \
     (sizeof(cls::SymbolTable)/sizeof(TAutoSymbol) - 1), typeid(cls), 0);

#define DEFINE_AUTOAGGREGATE(cls, aggregator) \
  IUnknown& cls::Aggregator(ObjectPtr inst, TUnknown& inner) \
        { return ((cls*)inst)->aggregator(inner); } \
  DEFINE_AUTOCLASS(cls)

#define END_AUTOAGGREGATE(cls, flags, name, doc, help) {{name},{doc}, 0, \
  flags,0,TAutoSymbol::InitAutoDestructor(cls::TCommand_dtr::Build),help} }; \
  TAutoClass cls::ClassInfo(cls::SymbolTable, cls::SymbolTable + \
  (sizeof(cls::SymbolTable)/sizeof(TAutoSymbol)-1),typeid(cls),cls::Aggregator);

struct TAutoEventDummy {
  struct TCommand_ {
    static TAutoCommand* Build(ObjectPtr,int,TAutoStack&) {return 0;}
  };
};

#define DEFINE_AUTOEVENTCLASS(cls) \
  class cls {static TAutoClass ClassInfo; static TAutoSymbol SymbolTable[]; \
  typedef TAutoEventDummy ThisClass; };\
  TAutoSymbol cls::SymbolTable[] = {

#define END_AUTOEVENTCLASS(cls, flags, name, doc, help) {{name},{doc}, 0, \
  flags|tfEventSource, 0, 0,help} }; \
  TAutoClass cls::ClassInfo(cls::SymbolTable, cls::SymbolTable + \
     (sizeof(cls::SymbolTable)/sizeof(TAutoSymbol) - 1), typeid(cls), 0);

#define DEFINE_AUTODISPATCH(cls) DEFINE_AUTOCLASS(cls)
#define END_AUTODISPATCH(cls)    END_AUTOCLASS(cls, 0, 0, 0)

#define EXPOSE_METHOD(cmd, cls, name, doc, help)     {{name},{doc},\
  asMethod, -1, &cls::ClassInfo, ThisClass::TCommand_##cmd::Build, help},

#define EXPOSE_METHOD_ID(id, cmd, cls, name, doc, help) {{name}, {doc},\
  asMethod, id, &cls::ClassInfo, ThisClass::TCommand_##cmd::Build, help},

#define EXPOSE_PROPRW(cmd, cls, name, doc, help)     {{name},{doc},\
  asGetSet, -1, &cls::ClassInfo, ThisClass::TCommand_##cmd::Build, help},

#define EXPOSE_PROPRW_ID(id, cmd, cls, name, doc, help)     {{name},{doc},\
  asGetSet, id, &cls::ClassInfo, ThisClass::TCommand_##cmd::Build, help},

#define EXPOSE_PROPRO(cmd, cls, name, doc, help)     {{name},{doc},\
  asGet, -1, &cls::ClassInfo, ThisClass::TCommand_##cmd::Build, help},

#define EXPOSE_PROPRO_ID(id, cmd, cls, name, doc, help)     {{name},{doc},\
  asGet, id, &cls::ClassInfo, ThisClass::TCommand_##cmd::Build, help},

#define EXPOSE_PROPWO(cmd, cls, name, doc, help)     {{name},{doc},\
  asSet, -1, &cls::ClassInfo, ThisClass::TCommand_##cmd::Build, help},

#define EXPOSE_PROPWO_ID(id, cmd, cls, name, doc, help)     {{name},{doc},\
  asSet, id, &cls::ClassInfo, ThisClass::TCommand_##cmd::Build, help},

#define EXPOSE_APPLICATION(cls, name, doc, help)     {{name},{doc},\
  asGet, -1, &cls::ClassInfo, ThisClass::TCommand_app::Build, help},

#define EXPOSE_QUIT(name, doc, help)                 {{name},{doc},\
  asMethod, -1, &TAutoVoid::ClassInfo, AutoQuitBuild, help},

#define REQUIRED_ARG(cls, name) {{name}, {0}, \
  asArgument, 0, &cls::ClassInfo, 0, 0},

#define OPTIONAL_ARG(cls, name, dflt) {{name}, {dflt}, \
  asArgument, 0, &cls::ClassInfo, 0, 0},

#define EXPOSE_DELEGATE(cls, name, locator) {{name}, {0}, \
  asClass, 0, &cls::ClassInfo, TAutoSymbol::InitTypeConvert(locator), 0},

#define EXPOSE_INHERIT(cls, name) {{name}, {0}, asClass, 0, &cls::ClassInfo, \
  TAutoSymbol::InitTypeConvert(TTypeConvert<cls,ThisClass>::Cast), 0},

#define EXPOSE_FACTORY(cls, name, base) {{name}, {0}, asFactory, 0, \
  &cls::ClassInfo, TAutoSymbol::InitTypeConvert(TTypeConvert<cls,base>::Cast), 0},

#define EXPOSE_ITERATOR(cls, doc, help)     {{"_NewEnum"},{doc}, asIterator, \
  -4, &cls::ClassInfo, TAutoSymbol::InitAutoIterator(ThisClass::TIterator::Build), help},

// Macros to define enumeration lists
//
//   DEFINE_AUTOENUM(EnumName, TAuto????)
//     AUTOENUM(EnumString1,  constval1)
//     AUTOENUM(EnumString2,  constval2)
//     AUTOENUM(EnumString3,  constval3)
//   END_AUTOENUM(EnumName, TAuto????)

#define DEFINE_AUTOENUM(cls, type) \
  TAutoEnumVal<type##Enum> cls##_Table[] = {

#define AUTOENUM(name, val) {{name}, val},

#define END_AUTOENUM(cls, type) }; \
  struct cls { static TAutoEnumT<type##Enum> ClassInfo; }; \
  TAutoEnumT<type##Enum> cls::ClassInfo(cls##_Table, \
  sizeof(cls##_Table)/sizeof(TAutoEnumVal<type##Enum>),type::ClassInfo.GetType());

typedef short         TAutoShortEnum;
typedef long          TAutoLongEnum;
typedef const char*   TAutoStringEnum;
typedef float         TAutoFloatEnum;
typedef double        TAutoDoubleEnum;
typedef bool          TAutoBoolEnum;
typedef TAutoCurrency TAutoCurrencyEnum;
typedef TAutoDate     TAutoDateEnum;
typedef unsigned char TAutoByteEnum;

//____________________________________________________________________________
//
// Macros for defining command objects
//____________________________________________________________________________
//
//  DECLARE_AUTOCLASS(C++ClassName)
//    AUTOFUNC0 (InternalName, FuncName, Options)
//    AUTOFUNC1 (InternalName, FuncName, RetType, Arg1Type, Options)
//    AUTOFUNC2 (InternalName, FuncName, RetType, Arg1Type, Arg2Type, Options)
//    AUTOFUNC0V(InternalName, FuncName, Options)           // void return
//    AUTOFUNC1V(InternalName, FuncName, Arg1Type, Options) // void return
//    AUTOFUNC2V(InternalName, FuncName, Arg1Type, Arg2Type, Options)
//    AUTODATA  (InternalName, DataMember, DataType, Options)
//    AUTODATARO(InternalName, DataMember, DataType, Options)
//    AUTOPROP  (InternalName, GetFuncName, SetFuncName, DataType, Options)
//    AUTOFLAG  (InternalName, DataMember, BitMask, Options)
//    AUTOBUILD0(InternalName, Options)
//    AUTOBUILD1(InternalName, Arg1Type, Options)
//    AUTOBUILD2(InternalName, Arg1Type, Arg2Type, Options)
//    AUTOPROXY (InternalName, ProxyMember, Options)
//    AUTOITERATOR(AccessExpr, StateDefs, InitCode, TestExpr, StepCode)
//    AUTODETACH    // invalidates external references upon object destruction
//
//  For automated classes which are, inherit from, or delegate to COM objects,
//  use the following macro in place of DECLARE_AUTOCLASS:
//
//  DECLARE_AUTOAGGREGATE(C++ClassName)
//____________________________________________________________________________

//
// Macros to place in final argument to add capabilites, else leave empty
//
#define AUTOUNDO(code)   TAutoCommand* Undo(){code}  // declare an undo method
#define AUTORECORD(code) int Record(TAutoStack& args){code};  // record method
#define AUTOINVOKE(code) TAutoCommand& Invoke(){code return *this;}// override
#define AUTOVALIDATE(condition) bool Validate() { return condition; }
#define AUTONOHOOK TAutoCommand& Invoke() {Execute();}
#define AUTOREPORT(errcode) long Report() {return errcode;}

//____________________________________________________________________________

//
// Autoclass declaration, adding derived TAutoCommand class with this pointer
//
#define DECLARE_AUTOCLASS(cls) \
  public: \
    static TAutoClass ClassInfo; \
  protected: \
    static TAutoSymbol SymbolTable[]; \
    class TThisCommand : public TAutoCommand { \
      protected: \
        TThisCommand(cls* obj, int attr):TAutoCommand(attr),This(obj){} \
        cls* This; \
    }; \
    typedef cls ThisClass; \
    class TCommand_app : public TAutoCommand { \
     public: \
      TCommand_app(int attr, TServedObject* app) \
                     : TAutoCommand(attr), Val(app) {} \
      void Return(TAutoVal& v) {v=(IDispatch*)Val;} \
      TServedObject* Val; \
      static TAutoCommand* Build(ObjectPtr obj,int attr,TAutoStack& args) \
      { return new TCommand_app(attr, args.Owner->GetAppObject()); } \
    }; \
    class TCommand_dtr : public TThisCommand { \
     public: \
      TCommand_dtr(ThisClass* obj, int attr) \
                     : TThisCommand(obj, attr) {} \
      void Execute(){if (Attr == TObjectDescriptor::PostQuit) \
                       ::PostQuitMessage(0);\
                     else delete This;} \
      static TAutoCommand* Build(ObjectPtr obj,int attr) \
      { return new TCommand_dtr((ThisClass*)obj, attr); }\
    }; friend class TCommand_dtr;

#define DECLARE_AUTODISPATCH(cls) \
  public: \
    static TAutoClass ClassInfo; \
  protected: \
    static TAutoSymbol SymbolTable[]; \
    class TThisCommand : public TAutoCommand { \
      protected: \
        TThisCommand(cls* obj, int attr):TAutoCommand(attr),This(obj){} \
        cls* This; \
    }; typedef cls ThisClass;

// Autoclass declaration for COM-aggregatable classes

#define DECLARE_AUTOAGGREGATE(cls) \
  public: \
    static IUnknown& Aggregator(ObjectPtr inst, TUnknown& inner); \
  DECLARE_AUTOCLASS(cls)

// Command object class definition for methods or get-only properties
//
#define RETARG(t) void Return(TAutoVal& v){v=Val;} t Val;

#define AUTOFUNC_(name, invoke, defs, defargs, bldargs, ctrargs, setargs) \
    class TCommand_##name : public TThisCommand { \
     public:  typedef TCommand_##name ThisCmd; \
      defs defargs \
      TCommand_##name(ThisClass* obj, int attr ctrargs) \
                     : TThisCommand(obj, attr) setargs {} \
      void Execute() {invoke} \
      static TAutoCommand* Build(ObjectPtr obj,int attr,TAutoStack& args) \
      { return new TCommand_##name((ThisClass*)obj, attr bldargs); }\
    }; friend class TCommand_##name;

// Command object class definition for properties with both get and set
//
#define AUTOPROP_(name, getcode, setcode, defs, type) \
    class TCommand_##name : public TThisCommand { \
     public:  typedef TCommand_##name ThisCmd; \
      defs RETARG(type) \
      TCommand_##name(ThisClass* obj, int attr) : TThisCommand(obj, attr) {} \
      TCommand_##name(ThisClass* obj, int attr, type arg) \
                                      : TThisCommand(obj, attr), Val(arg) {} \
      void Execute() {if (IsPropSet()) {setcode} else {getcode}} \
      static TAutoCommand* Build(ObjectPtr obj,int attr,TAutoStack& args) \
      { return (attr & asGet) ?  \
        new TCommand_##name((ThisClass*)obj, attr) : \
        new TCommand_##name((ThisClass*)obj, attr,(type)args[TAutoStack::SetValue]);}\
    }; friend class TCommand_##name;

// Command object class definition for constructor commands
//
#define AUTOBUILD_(name, invoke, defs, defargs, bldargs, ctrargs, setargs) \
    class TCommand_##name : public TAutoCommand {\
     public: \
      defs defargs RETARG(TAutoMono<ThisClass>) \
      TCommand_##name(int attr ctrargs) : TAutoCommand(attr) setargs {} \
      void Execute() {invoke} \
      static TAutoCommand* Build(ObjectPtr, int attr, TAutoStack& args) \
      { return new TCommand_##name(attr bldargs); } \
    };

// Command object class definition for external object property
//
#define AUTOPROXY(name, proxy, defs) \
        AUTOPROP_(name, Val=This->proxy;, This->proxy.Bind(Val);, defs, IDispatch*)

// Iterator class definition
//
#define AUTOITERATOR(state, init, test, step, extract) \
    class TIterator : public TAutoIterator { \
     public: \
      ThisClass* This; \
      state; \
      void Init() {init;} \
      bool Test() {return test;} \
      void Step() {step;} \
      void Return(TAutoVal& v) {v=extract;} \
      TIterator* Copy() {return new TIterator(*this);} \
      TIterator(ThisClass* obj, TAutoCreator& creator, IUnknown* owner, TLangId lang) \
                    : This(obj), TAutoIterator(creator, owner, lang) {} \
      static TAutoIterator* Build(ObjectPtr obj, TAutoCreator& creator, \
                                  IUnknown* owner, TLangId lang) \
      { return new TIterator((ThisClass*)obj, creator, owner, lang); }\
    }; friend class TIterator;

#define AUTOITERATOR_DECLARE(state) \
    class TIterator : public TAutoIterator { \
     public: \
      ThisClass* This; \
      state; \
      void Init(); \
      bool Test(); \
      void Step(); \
      void Return(TAutoVal& v); \
      TIterator* Copy() {return new TIterator(*this);} \
      TIterator(ThisClass* obj, TAutoCreator& creator, IUnknown* owner, TLangId lang) \
                    : This(obj), TAutoIterator(creator, owner, lang) {} \
      static TAutoIterator* Build(ObjectPtr obj, TAutoCreator& creator, \
                                  IUnknown* owner, TLangId lang) \
      { return new TIterator((ThisClass*)obj, creator, owner, lang); }\
    }; friend class TIterator;

//
// Macros for defining lists of arguments
//
                    
#define DEFARGS0(t0)                t0 Val;
#define DEFARGS1(t1)                t1 Arg1;
#define DEFARGS2(t1,t2)             t1 Arg1;t2 Arg2;
#define DEFARGS3(t1,t2,t3)          t1 Arg1;t2 Arg2;t3 Arg3;
#define DEFARGS4(t1,t2,t3,t4)       t1 Arg1;t2 Arg2;t3 Arg3;t4 Arg4;
#define DEFARGS5(t1,t2,t3,t4,t5)    t1 Arg1;t2 Arg2;t3 Arg3;t4 Arg4;t5 Arg5;
#define DEFARGS6(t1,t2,t3,t4,t5,t6) t1 Arg1;t2 Arg2;t3 Arg3;t4 Arg4;t5 Arg5;t6 Arg6;
#define DEFARGS7(t1,t2,t3,t4,t5,t6,t7) \
  t1 Arg1;t2 Arg2;t3 Arg3;t4 Arg4;t5 Arg5;t6 Arg6;t7 Arg7;
#define DEFARGS8(t1,t2,t3,t4,t5,t6,t7,t8) \
  t1 Arg1;t2 Arg2;t3 Arg3;t4 Arg4;t5 Arg5;t6 Arg6;t7 Arg7;t8 Arg8;
#define DEFARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9) \
  t1 Arg1;t2 Arg2;t3 Arg3;t4 Arg4;t5 Arg5;t6 Arg6;t7 Arg7;t8 Arg8;t9 Arg9;
#define DEFARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10) \
  t1 Arg1;t2 Arg2;t3 Arg3;t4 Arg4;t5 Arg5;t6 Arg6;t7 Arg7;t8 Arg8;t9 Arg9;t10 Arg10;

#define BLDARGS0(t0)                ,(t0)args[TAutoStack::SetValue]
#define BLDARGS1(t1)                ,(t1)args[0]
#define BLDARGS2(t1,t2)             ,(t1)args[0],(t2)args[1]
#define BLDARGS3(t1,t2,t3)          ,(t1)args[0],(t2)args[1],(t3)args[2]
#define BLDARGS4(t1,t2,t3,t4)                                  \
  ,(t1)args[0],(t2)args[1],(t3)args[2],(t4)args[3]
#define BLDARGS5(t1,t2,t3,t4,t5)                               \
  ,(t1)args[0],(t2)args[1],(t3)args[2],(t4)args[3],(t5)args[4]
#define BLDARGS6(t1,t2,t3,t4,t5,t6)                            \
  ,(t1)args[0],(t2)args[1],(t3)args[2],(t4)args[3],(t5)args[4],(t6)args[5]
#define BLDARGS7(t1,t2,t3,t4,t5,t6,t7)                         \
  ,(t1)args[0],(t2)args[1],(t3)args[2],(t4)args[3],(t5)args[4] \
  ,(t6)args[5],(t7)args[6]
#define BLDARGS8(t1,t2,t3,t4,t5,t6,t7,t8)                      \
  ,(t1)args[0],(t2)args[1],(t3)args[2],(t4)args[3],(t5)args[4] \
  ,(t6)args[5],(t7)args[6],(t8)args[7]
#define BLDARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9)                   \
  ,(t1)args[0],(t2)args[1],(t3)args[2],(t4)args[3],(t5)args[4] \
  ,(t6)args[5],(t7)args[6],(t8)args[7],(t9)args[8]
#define BLDARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10)              \
  ,(t1)args[0],(t2)args[1],(t3)args[2],(t4)args[3],(t5)args[4] \
  ,(t6)args[5],(t7)args[6],(t8)args[7],(t9)args[8],(t10)args[9]

#define CTRARGS0(t0)                    ,t0 val
#define CTRARGS1(t1)                    ,t1 arg1
#define CTRARGS2(t1,t2)                 ,t1 arg1,t2 arg2
#define CTRARGS3(t1,t2,t3)              ,t1 arg1,t2 arg2,t3 arg3
#define CTRARGS4(t1,t2,t3,t4)           ,t1 arg1,t2 arg2,t3 arg3,t4 arg4
#define CTRARGS5(t1,t2,t3,t4,t5)        ,t1 arg1,t2 arg2,t3 arg3,t4 arg4,t5 arg5
#define CTRARGS6(t1,t2,t3,t4,t5,t6)     ,t1 arg1,t2 arg2,t3 arg3,t4 arg4,t5 arg5,t6 arg6
#define CTRARGS7(t1,t2,t3,t4,t5,t6,t7)  ,t1 arg1,t2 arg2,t3 arg3,t4 arg4,t5 arg5,t6 arg6,t7 arg7
#define CTRARGS8(t1,t2,t3,t4,t5,t6,t7,t8) \
  ,t1 arg1,t2 arg2,t3 arg3,t4 arg4,t5 arg5,t6 arg6,t7 arg7,t8 arg8
#define CTRARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9) \
  ,t1 arg1,t2 arg2,t3 arg3,t4 arg4,t5 arg5,t6 arg6,t7 arg7,t8 arg8,t9 arg9
#define CTRARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10) \
  ,t1 arg1,t2 arg2,t3 arg3,t4 arg4,t5 arg5,t6 arg6,t7 arg7,t8 arg8,t9 arg9,t10 arg10

#define SETARGS0  ,Val(val)
#define SETARGS1  ,Arg1(arg1)
#define SETARGS2  ,Arg1(arg1),Arg2(arg2)
#define SETARGS3  ,Arg1(arg1),Arg2(arg2),Arg3(arg3)
#define SETARGS4  ,Arg1(arg1),Arg2(arg2),Arg3(arg3),Arg4(arg4)
#define SETARGS5  ,Arg1(arg1),Arg2(arg2),Arg3(arg3),Arg4(arg4),Arg5(arg5)
#define SETARGS6  ,Arg1(arg1),Arg2(arg2),Arg3(arg3),Arg4(arg4),Arg5(arg5),Arg6(arg6)
#define SETARGS7  ,Arg1(arg1),Arg2(arg2),Arg3(arg3),Arg4(arg4),Arg5(arg5),Arg6(arg6), \
  Arg7(arg7)
#define SETARGS8  ,Arg1(arg1),Arg2(arg2),Arg3(arg3),Arg4(arg4),Arg5(arg5),Arg6(arg6), \
  Arg7(arg7),Arg8(arg8)
#define SETARGS9  ,Arg1(arg1),Arg2(arg2),Arg3(arg3),Arg4(arg4),Arg5(arg5),Arg6(arg6), \
  Arg7(arg7),Arg8(arg8),Arg9(arg9)
#define SETARGS10 ,Arg1(arg1),Arg2(arg2),Arg3(arg3),Arg4(arg4),Arg5(arg5),Arg6(arg6), \
  Arg7(arg7),Arg8(arg8),Arg9(arg9),Arg10(arg10)

#define AUTOFUNC0(name, func, ret, defs) \
  AUTOFUNC_(name, Val=This->func();, defs, RETARG(ret), , , )

#define AUTOFUNC0V(name, func, defs) \
  AUTOFUNC_(name, This->func();, defs, , , , )

#define AUTOFUNC1(name, func, ret,type1, defs) \
  AUTOFUNC_(name, Val=This->func(Arg1);, defs, RETARG(ret) \
  DEFARGS1(type1), BLDARGS1(type1), CTRARGS1(type1), SETARGS1)

#define AUTOFUNC1V(name, func, type1, defs) \
  AUTOFUNC_(name, This->func(Arg1);, defs, \
  DEFARGS1(type1), BLDARGS1(type1), CTRARGS1(type1), SETARGS1)

#define AUTOFUNC2(name, func, ret,t1,t2, defs) \
  AUTOFUNC_(name, Val=This->func(Arg1,Arg2);, defs, RETARG(ret) \
  DEFARGS2(t1,t2), BLDARGS2(t1,t2), CTRARGS2(t1,t2), SETARGS2)

#define AUTOFUNC2V(name, func, t1,t2, defs) \
  AUTOFUNC_(name, This->func(Arg1,Arg2);, defs, \
  DEFARGS2(t1,t2), BLDARGS2(t1,t2), CTRARGS2(t1,t2), SETARGS2)

#define AUTOFUNC3(name, func, ret,t1,t2,t3, defs) \
  AUTOFUNC_(name, Val=This->func(Arg1,Arg2,Arg3);, defs, RETARG(ret) \
  DEFARGS3(t1,t2,t3), BLDARGS3(t1,t2,t3), CTRARGS3(t1,t2,t3), SETARGS3)

#define AUTOFUNC3V(name, func, t1,t2,t3, defs) \
  AUTOFUNC_(name, This->func(Arg1,Arg2,Arg3);, defs, \
  DEFARGS3(t1,t2,t3), BLDARGS3(t1,t2,t3), CTRARGS3(t1,t2,t3), SETARGS3)

#define AUTOFUNC4(name, func, ret,t1,t2,t3,t4, defs) \
  AUTOFUNC_(name, Val=This->func(Arg1,Arg2,Arg3,Arg4);, defs, RETARG(ret) \
  DEFARGS4(t1,t2,t3,t4), BLDARGS4(t1,t2,t3,t4), CTRARGS4(t1,t2,t3,t4), SETARGS4)

#define AUTOFUNC4V(name, func, t1,t2,t3,t4, defs) \
  AUTOFUNC_(name, This->func(Arg1,Arg2,Arg3,Arg4);, defs,\
  DEFARGS4(t1,t2,t3,t4), BLDARGS4(t1,t2,t3,t4), CTRARGS4(t1,t2,t3,t4), SETARGS4)

#define AUTOFUNC5(name,func,ret,t1,t2,t3,t4,t5,defs)                        \
  AUTOFUNC_(name,Val=This->func(Arg1,Arg2,Arg3,Arg4,Arg5);,defs,RETARG(ret) \
  DEFARGS5(t1,t2,t3,t4,t5),BLDARGS5(t1,t2,t3,t4,t5),CTRARGS5(t1,t2,t3,t4,t5),SETARGS5)

#define AUTOFUNC5V(name,func,t1,t2,t3,t4,t5,defs)            \
  AUTOFUNC_(name,This->func(Arg1,Arg2,Arg3,Arg4,Arg5);,defs, \
  DEFARGS5(t1,t2,t3,t4,t5),BLDARGS5(t1,t2,t3,t4,t5),CTRARGS5(t1,t2,t3,t4,t5),SETARGS5)

#define AUTOFUNC6(name,func,ret,t1,t2,t3,t4,t5,t6,defs)                          \
  AUTOFUNC_(name,Val=This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6);,defs,RETARG(ret) \
  DEFARGS6(t1,t2,t3,t4,t5,t6),BLDARGS6(t1,t2,t3,t4,t5,t6), CTRARGS6(t1,t2,t3,t4,t5,t6),SETARGS6)

#define AUTOFUNC6V(name,func,t1,t2,t3,t4,t5,t6,defs)              \
  AUTOFUNC_(name,This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6);,defs, \
  DEFARGS6(t1,t2,t3,t4,t5,t6),BLDARGS6(t1,t2,t3,t4,t5,t6),        \
  CTRARGS6(t1,t2,t3,t4,t5,t6),SETARGS6)

#define AUTOFUNC7(name,func,ret,t1,t2,t3,t4,t5,t6,t7,defs)                            \
  AUTOFUNC_(name,Val=This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7);,defs,RETARG(ret) \
  DEFARGS7(t1,t2,t3,t4,t5,t6,t7),BLDARGS7(t1,t2,t3,t4,t5,t6,t7),                      \
  CTRARGS7(t1,t2,t3,t4,t5,t6,t7),SETARGS7)

#define AUTOFUNC7V(name,func,t1,t2,t3,t4,t5,t6,t7,defs)                \
  AUTOFUNC_(name,This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7);,defs, \
  DEFARGS7(t1,t2,t3,t4,t5,t6,t7),BLDARGS7(t1,t2,t3,t4,t5,t6,t7),       \
  CTRARGS7(t1,t2,t3,t4,t5,t6,t7),SETARGS7)

#define AUTOFUNC8(name,func,ret,t1,t2,t3,t4,t5,t6,t7,t8,defs)                              \
  AUTOFUNC_(name,Val=This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8);,defs,RETARG(ret) \
  DEFARGS8(t1,t2,t3,t4,t5,t6,t7,t8),BLDARGS8(t1,t2,t3,t4,t5,t6,t7,t8),                     \
  CTRARGS8(t1,t2,t3,t4,t5,t6,t7,t8),SETARGS8)

#define AUTOFUNC8V(name,func,t1,t2,t3,t4,t5,t6,t7,t8,defs)                  \
  AUTOFUNC_(name,This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8);,defs, \
  DEFARGS8(t1,t2,t3,t4,t5,t6,t7,t8),BLDARGS8(t1,t2,t3,t4,t5,t6,t7,t8),      \
  CTRARGS8(t1,t2,t3,t4,t5,t6,t7,t8),SETARGS8)

#define AUTOFUNC9(name,func,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,defs)                                \
  AUTOFUNC_(name,Val=This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9);,defs,RETARG(ret) \
  DEFARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),BLDARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),                    \
  CTRARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),SETARGS9)

#define AUTOFUNC9V(name,func,t1,t2,t3,t4,t5,t6,t7,t8,t9,defs)                    \
  AUTOFUNC_(name,This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9);,defs, \
  DEFARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),BLDARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),     \
  CTRARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),SETARGS9)

#define AUTOFUNC10(name,func,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,defs)                                 \
  AUTOFUNC_(name,Val=This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9,Arg10);,defs,RETARG(ret) \
  DEFARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),BLDARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),                \
  CTRARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),SETARGS10)

#define AUTOFUNC10V(name,func,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,defs)                     \
  AUTOFUNC_(name,This->func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9,Arg10);,defs, \
  DEFARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),BLDARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10), \
  CTRARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),SETARGS10)

#define AUTOSTAT0(name, func, ret, defs) \
  AUTOFUNC_(name, Val=func();, defs, RETARG(ret), , , )

#define AUTOSTAT0V(name, func, defs) \
  AUTOFUNC_(name, func();, defs, , , , )

#define AUTOSTAT1(name, func, ret,type1, defs) \
  AUTOFUNC_(name, Val=func(Arg1);, defs, RETARG(ret) \
  DEFARGS1(type1), BLDARGS1(type1), CTRARGS1(type1), SETARGS1)

#define AUTOSTAT1V(name, func, type1, defs) \
  AUTOFUNC_(name, func(Arg1);, defs, \
  DEFARGS1(type1), BLDARGS1(type1), CTRARGS1(type1), SETARGS1)

#define AUTOSTAT2(name, func, ret,t1,t2, defs) \
  AUTOFUNC_(name, Val=func(Arg1,Arg2);, defs, RETARG(ret) \
  DEFARGS2(t1,t2), BLDARGS2(t1,t2), CTRARGS2(t1,t2), SETARGS2)

#define AUTOSTAT2V(name, func, t1,t2, defs) \
  AUTOFUNC_(name, func(Arg1,Arg2);, defs, \
  DEFARGS2(t1,t2), BLDARGS2(t1,t2), CTRARGS2(t1,t2), SETARGS2)

#define AUTOSTAT3(name, func, ret,t1,t2,t3, defs) \
  AUTOFUNC_(name, Val=func(Arg1,Arg2,Arg3);, defs, RETARG(ret) \
  DEFARGS3(t1,t2,t3), BLDARGS3(t1,t2,t3), CTRARGS3(t1,t2,t3), SETARGS3)

#define AUTOSTAT3V(name, func, t1,t2,t3, defs) \
  AUTOFUNC_(name, func(Arg1,Arg2,Arg3);, defs, \
  DEFARGS3(t1,t2,t3), BLDARGS3(t1,t2,t3), CTRARGS3(t1,t2,t3), SETARGS3)

#define AUTOSTAT4(name, func, ret,t1,t2,t3,t4, defs) \
  AUTOFUNC_(name, Val=func(Arg1,Arg2,Arg3,Arg4);, defs, RETARG(ret) \
  DEFARGS4(t1,t2,t3,t4), BLDARGS4(t1,t2,t3,t4), CTRARGS4(t1,t2,t3,t4), SETARGS4)

#define AUTOSTAT4V(name, func, t1,t2,t3,t4, defs) \
  AUTOFUNC_(name, func(Arg1,Arg2,Arg3,Arg4);, defs,\
  DEFARGS4(t1,t2,t3,t4), BLDARGS4(t1,t2,t3,t4), CTRARGS4(t1,t2,t3,t4), SETARGS4)

#define AUTOSTAT5(name,func,ret,t1,t2,t3,t4,t5,defs)                  \
  AUTOFUNC_(name,Val=func(Arg1,Arg2,Arg3,Arg4,Arg5);,defs,RETARG(ret) \
  DEFARGS5(t1,t2,t3,t4,t5),BLDARGS5(t1,t2,t3,t4,t5),CTRARGS5(t1,t2,t3,t4,t5),SETARGS5)

#define AUTOSTAT5V(name,func,t1,t2,t3,t4,t5,defs)      \
  AUTOFUNC_(name,func(Arg1,Arg2,Arg3,Arg4,Arg5);,defs, \
  DEFARGS5(t1,t2,t3,t4,t5),BLDARGS5(t1,t2,t3,t4,t5),CTRARGS5(t1,t2,t3,t4,t5),SETARGS5)

#define AUTOSTAT6(name,func,ret,t1,t2,t3,t4,t5,t6,defs)                    \
  AUTOFUNC_(name,Val=func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6);,defs,RETARG(ret) \
  DEFARGS6(t1,t2,t3,t4,t5,t6),BLDARGS6(t1,t2,t3,t4,t5,t6), CTRARGS6(t1,t2,t3,t4,t5,t6),SETARGS6)

#define AUTOSTAT6V(name,func,t1,t2,t3,t4,t5,t6,defs)        \
  AUTOFUNC_(name,func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6);,defs, \
  DEFARGS6(t1,t2,t3,t4,t5,t6),BLDARGS6(t1,t2,t3,t4,t5,t6), CTRARGS6(t1,t2,t3,t4,t5,t6),SETARGS6)

#define AUTOSTAT7(name,func,ret,t1,t2,t3,t4,t5,t6,t7,defs)                      \
  AUTOFUNC_(name,Val=func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7);,defs,RETARG(ret) \
  DEFARGS7(t1,t2,t3,t4,t5,t6,t7),BLDARGS7(t1,t2,t3,t4,t5,t6,t7),                \
  CTRARGS7(t1,t2,t3,t4,t5,t6,t7),SETARGS7)

#define AUTOSTAT7V(name,func,t1,t2,t3,t4,t5,t6,t7,defs)          \
  AUTOFUNC_(name,func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7);,defs, \
  DEFARGS7(t1,t2,t3,t4,t5,t6,t7),BLDARGS7(t1,t2,t3,t4,t5,t6,t7), \
  CTRARGS7(t1,t2,t3,t4,t5,t6,t7),SETARGS7)

#define AUTOSTAT8(name,func,ret,t1,t2,t3,t4,t5,t6,t7,t8,defs)                        \
  AUTOFUNC_(name,Val=func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8);,defs,RETARG(ret) \
  DEFARGS8(t1,t2,t3,t4,t5,t6,t7,t8),BLDARGS8(t1,t2,t3,t4,t5,t6,t7,t8),               \
  CTRARGS8(t1,t2,t3,t4,t5,t6,t7,t8),SETARGS8)

#define AUTOSTAT8V(name,func,t1,t2,t3,t4,t5,t6,t7,t8,defs)             \
  AUTOFUNC_(name,func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8);,defs,  \
  DEFARGS8(t1,t2,t3,t4,t5,t6,t7,t8),BLDARGS8(t1,t2,t3,t4,t5,t6,t7,t8), \
  CTRARGS8(t1,t2,t3,t4,t5,t6,t7,t8),SETARGS8)

#define AUTOSTAT9(name,func,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,defs)                          \
  AUTOFUNC_(name,Val=func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9);,defs,RETARG(ret) \
  DEFARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),BLDARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),              \
  CTRARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),SETARGS9)

#define AUTOSTAT9V(name,func,t1,t2,t3,t4,t5,t6,t7,t8,t9,defs)                \
  AUTOFUNC_(name,func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9);,defs,   \
  DEFARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),BLDARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9), \
  CTRARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),SETARGS9)

#define AUTOSTAT10(name,func,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,defs)                           \
  AUTOFUNC_(name,Val=func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9,Arg10);,defs,RETARG(ret) \
  DEFARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),BLDARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),          \
  CTRARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),SETARGS10)

#define AUTOSTAT10V(name,func,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,defs)                     \
  AUTOFUNC_(name,func(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9,Arg10);,defs,       \
  DEFARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),BLDARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10), \
  CTRARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),SETARGS10)


#define AUTOPROP( name, get, set, type, defs) \
  AUTOPROP_(name, Val=This->get();, This->set(Val);, defs, type)

#define AUTOPROPRO(name, get, type, defs) \
  AUTOFUNC0( name, get, type, defs)

#define AUTOPROPWO( name, set, type, defs) \
  AUTOFUNC_(name, This->set(Val);, defs, \
  DEFARGS0(type), BLDARGS0(type), CTRARGS0(type), SETARGS0)

#define AUTODATA( name, data, type, defs) \
  AUTOPROP_(name, Val=This->data;, This->data=Val;, defs, type)

#define AUTODATARO(name, data, type, defs) \
  AUTOFUNC_(name, Val=This->data;, defs, RETARG(type), , , )

#define AUTOTHIS(name, type, defs) \
  AUTOFUNC_(name, Val=*This;, defs, RETARG(type), , , )

#define AUTOFLAG( name, data, mask, defs) \
  AUTOPROP_(name, Val=(TBool)((This->data & (mask)) != 0);, \
  if (Val) This->data|=(mask); else This->data&=~(mask);, defs, TBool)

#define AUTOBUILD0(name, defs) \
  AUTOBUILD_(name, Val = new ThisClass();, defs, , , , )

#define AUTOBUILD1(name, type1, defs) \
  AUTOBUILD_(name, Val = new ThisClass(Arg1);, defs, \
  DEFARGS1(type1), BLDARGS1(type1), CTRARGS1(type1), SETARGS1)

#define AUTOBUILD2(name, t1,t2, defs) \
  AUTOBUILD_(name, Val = new ThisClass(Arg1,Arg2);, defs, \
  DEFARGS2(t1,t2), BLDARGS2(t1,t2), CTRARGS2(t1,t2), SETARGS2)

#define AUTOBUILD3(name, t1,t2,t3, defs) \
  AUTOBUILD_(name, Val = new ThisClass(Arg1,Arg2,Arg3);, defs, \
  DEFARGS3(t1,t2,t3), BLDARGS3(t1,t2,t3), CTRARGS3(t1,t2,t3), SETARGS3)

#define AUTOBUILD4(name, t1,t2,t3,t4, defs) \
  AUTOBUILD_(name, Val = new ThisClass(Arg1,Arg2,Arg3,Arg4);, defs, \
  DEFARGS4(t1,t2,t3,t4), BLDARGS4(t1,t2,t3,t4), CTRARGS4(t1,t2,t3,t4), SETARGS4)

#define AUTOBUILD5(name,func,t1,t2,t3,t4,t5,defs)                    \
  AUTOBUILD_(name,Val=new ThisClass(Arg1,Arg2,Arg3,Arg4,Arg5);,defs, \
  DEFARGS5(t1,t2,t3,t4,t5),BLDARGS5(t1,t2,t3,t4,t5),CTRARGS5(t1,t2,t3,t4,t5),\
  SETARGS5)

#define AUTOBUILD6(name,func,t1,t2,t3,t4,t5,t6,defs)                      \
  AUTOBUILD_(name,Val=new ThisClass(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6);,defs, \
  DEFARGS6(t1,t2,t3,t4,t5,t6),BLDARGS6(t1,t2,t3,t4,t5,t6),                \
  CTRARGS6(t1,t2,t3,t4,t5,t6),SETARGS6)

#define AUTOBUILD7(name,func,t1,t2,t3,t4,t5,t6,t7,defs)                       \
  AUTOBUILD_(name,Val=new ThisClass(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7);,defs,\
  DEFARGS7(t1,t2,t3,t4,t5,t6,t7),BLDARGS7(t1,t2,t3,t4,t5,t6,t7),              \
  CTRARGS7(t1,t2,t3,t4,t5,t6,t7),SETARGS7)

#define AUTOBUILD8(name,func,t1,t2,t3,t4,t5,t6,t7,t8,defs)                    \
  AUTOBUILD_(name,Val=new ThisClass(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8);,defs, \
  DEFARGS8(t1,t2,t3,t4,t5,t6,t7,t8),BLDARGS8(t1,t2,t3,t4,t5,t6,t7,t8),              \
  CTRARGS8(t1,t2,t3,t4,t5,t6,t7,t8),SETARGS8)

#define AUTOBUILD9(name,func,t1,t2,t3,t4,t5,t6,t7,t8,t9,defs)                            \
  AUTOBUILD_(name,Val=new ThisClass(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9);,defs, \
  DEFARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),BLDARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),             \
  CTRARGS9(t1,t2,t3,t4,t5,t6,t7,t8,t9),SETARGS9)

#define AUTOBUILD10(name,func,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,defs)                             \
  AUTOBUILD_(name,Val=new ThisClass(Arg1,Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8,Arg9,Arg10);,defs, \
  DEFARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),BLDARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),         \
  CTRARGS10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10),SETARGS10)

#define AUTODETACH \
    struct TDetach : public TAutoDetach { \
      ~TDetach(){Notify((int)&((ThisClass*)0)->dtr_notify,typeid(ThisClass));} \
    } dtr_notify; friend struct TDetach;

//____________________________________________________________________________
//
// Macros for defining automation proxy call wrappers
//____________________________________________________________________________
//
//  RetType|void C++ClassName::C++MethodName(C++ArgumentList)
//  {
//    AUTONAMES?(FunctionName&NamedArgs)  // ? = named argument count
//    AUTOARGS?(ArgumentList)            // ? = total argument count
//    AUTOCALL_?                        // ? = call type and return value type
//  }
//____________________________________________________________________________

#define AUTOCALL_ASSIGN \
   ExtObjRef operator =(ExtObjRef ifc) {return TAutoProxy::operator =(ifc);}

#define _A(a) "\0" a

#define AUTONAMES0(id)       static TAutoDispId     i_(this, id);
#define AUTONAMES1(id,n1)    static TAutoDispIds<1> i_(this, id _A(n1));
#define AUTONAMES2(id,n1,n2) static TAutoDispIds<2> i_(this, id _A(n2)_A(n1));
#define AUTONAMES3(id,n1,n2,n3) \
  static TAutoDispIds<3> i_(this, id _A(n3)_A(n2)_A(n1));
#define AUTONAMES4(id,n1,n2,n3,n4) \
  static TAutoDispIds<4> i_(this, id _A(n4)_A(n3)_A(n2)_A(n1));
#define AUTONAMES5(id,n1,n2,n3,n4,n5) \
  static TAutoDispIds<5> i_(this, id _A(n5)_A(n4)_A(n3)_A(n2)_A(n1));
#define AUTONAMES6(id,n1,n2,n3,n4,n5,n6) \
  static TAutoDispIds<6> i_(this, id _A(n6)_A(n5)_A(n4)_A(n3)_A(n2)_A(n1));
#define AUTONAMES7(id,n1,n2,n3,n4,n5,n6,n7) \
  static TAutoDispIds<7> i_(this,id,_A(n7)_A(n6)_A(n5)_A(n4)_A(n3)_A(n2)_A(n1));
#define AUTONAMES8(id,n1,n2,n3,n4,n5,n6,n7,n8) \
  static TAutoDispIds<8> i_(this,id,_A(n8)_A(n7)_A(n6)_A(n5)_A(n4)_A(n3)_A(n2)_A(n1));
#define AUTONAMES9(id,n1,n2,n3,n4,n5,n6,n7,n8,n9) \
  static TAutoDispIds<9> i_(this,id,_A(n9)_A(n8)_A(n7)_A(n6)_A(n5)_A(n4)_A(n3)_A(n2)_A(n1));
#define AUTONAMES10(id,n1,n2,n3,n4,n5,n6,n7,n8,n9,n10) \
  static TAutoDispIds<10> i_(this,id,_A(n10)_A(n9)_A(n8)_A(n7)_A(n6)_A(n5)_A(n4)_A(n3)_A(n2)_A(n1));

#define AUTOARGS0()          TAutoArgs<0>a_;
#define AUTOARGS1(a1)        TAutoArgs<1>a_; a_[1]=a1;
#define AUTOARGS2(a1,a2)     TAutoArgs<2>a_; a_[1]=a1; a_[2]=a2;
#define AUTOARGS3(a1,a2,a3)  TAutoArgs<3>a_; a_[1]=a1; a_[2]=a2; a_[3]=a3;
#define AUTOARGS4(a1,a2,a3,a4)                                  \
  TAutoArgs<4>a_; a_[1]=a1; a_[2]=a2; a_[3]=a3; a_[4]=a4;
#define AUTOARGS5(a1,a2,a3,a4,a5)                               \
  TAutoArgs<5>a_; a_[1]=a1; a_[2]=a2; a_[3]=a3; a_[4]=a4; a_[5]=a5;
#define AUTOARGS6(a1,a2,a3,a4,a5,a6)                            \
  TAutoArgs<6>a_; a_[1]=a1; a_[2]=a2; a_[3]=a3; a_[4]=a4; a_[5]=a5;a_[6]=a6;
#define AUTOARGS7(a1,a2,a3,a4,a5,a6,a7)                         \
  TAutoArgs<7>a_;a_[1]=a1;a_[2]=a2;a_[3]=a3;a_[4]=a4;a_[5]=a5;  \
  a_[6]=a6;a_[7]=a7;
#define AUTOARGS8(a1,a2,a3,a4,a5,a6,a7,a8)                      \
  TAutoArgs<8>a_;a_[1]=a1;a_[2]=a2;a_[3]=a3;a_[4]=a4;a_[5]=a5;  \
  a_[6]=a6;a_[7]=a7;a_[8]=a8;
#define AUTOARGS9(a1,a2,a3,a4,a5,a6,a7,a8,a9)                   \
  TAutoArgs<9>a_;a_[1]=a1;a_[2]=a2;a_[3]=a3;a_[4]=a4;a_[5]=a5;  \
  a_[6]=a6;a_[7]=a7;a_[8]=a8;a_[9]=a9;
#define AUTOARGS10(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)              \
  TAutoArgs<10>a_;a_[1]=a1;a_[2]=a2;a_[3]=a3;a_[4]=a4;a_[5]=a5; \
  a_[6]=a6;a_[7]=a7;a_[8]=a8;a_[9]=a9;a_[10]=a10;

#define AUTOCALL_METHOD_RET        return Invoke(acMethod,  a_, i_, i_);
#define AUTOCALL_METHOD_VOID              Invoke(acMethod,  a_, i_, i_);
#define AUTOCALL_METHOD_REF(prx) prx.Bind(Invoke(acMethod,  a_, i_, i_));
#define AUTOCALL_METHOD_CONV(t)  return t(Invoke(acMethod,  a_, i_, i_));

#define AUTOCALL_PROP_GET          return Invoke(acPropGet, a_, i_, i_);
#define AUTOCALL_PROP_SET(val) a_[0]=val; Invoke(acPropSet, a_, i_, i_);
#define AUTOCALL_PROP_REF(prx)   prx.Bind(Invoke(acPropGet, a_, i_, i_));
#define AUTOCALL_PROP_CONV(t)    return t(Invoke(acPropGet, a_, i_, i_));

#endif  // OCF_AUTOMACR_H

