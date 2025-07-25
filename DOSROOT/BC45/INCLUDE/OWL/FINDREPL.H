//----------------------------------------------------------------------------
// ObjectWindows
// (C) Copyright 1992, 1994 by Borland International, All Rights Reserved
//
//   Definition of FindReplace- abstract, Find-, Replace- common Dialog 
//   classes
//----------------------------------------------------------------------------
#if !defined(OWL_FINDREPL_H)
#define OWL_FINDREPL_H

#if !defined(OWL_COMMDIAL_H)
# include <owl/commdial.h>
#endif

class _OWLCLASS TFindReplaceDialog : public TCommonDialog {
  public:
    class _OWLCLASS TData {
      public:
        uint32   Flags;
        uint32   Error;
        char*    FindWhat;
        char*    ReplaceWith;
        int      BuffSize;
      
        TData(uint32 flags = 0, int buffSize = 81);
        TData(const TData& src);
       ~TData();

        TData& operator =(const TData& src);

        void     Write(opstream& os);
        void     Read(ipstream& is);
    };

    TFindReplaceDialog(TWindow*        parent, 
                       TData&          data,
                       TResId          templateId = 0,
                       const char far* title = 0,
                       TModule*        module = 0);

    void         UpdateData(LPARAM lParam = 0);
    
  protected:
    FINDREPLACE  fr;
    TData&       Data;

    HWND         DoCreate() = 0;

    TFindReplaceDialog(TWindow*        parent,
                       TResId          templateId = 0,
                       const char far* title = 0,
                       TModule*        module = 0);

    void     Init(TResId templateId);
    bool     DialogFunction(uint message, WPARAM, LPARAM);

    //
    // Default behavior inline for message response functions
    //
    void     CmFindNext() {DefaultProcessing();}   //EV_COMMAND(IDOK,
    void     CmReplace() {DefaultProcessing();}    //EV_COMMAND(psh1,
    void     CmReplaceAll() {DefaultProcessing();} //EV_COMMAND(psh2,
    void     CmCancel() {DefaultProcessing();}     //EV_COMMAND(IDCANCEL,

    void     EvNCDestroy();

  DECLARE_RESPONSE_TABLE(TFindReplaceDialog);
  DECLARE_CASTABLE;
};

class _OWLCLASS TFindDialog : public TFindReplaceDialog {
  public:
    TFindDialog(TWindow*        parent,
                TData&          data,
                TResId          templateId = 0,
                const char far* title = 0,
                TModule*        module = 0);

  protected:
    HWND     DoCreate();

  private:
    TFindDialog();
    TFindDialog(const TFindDialog&);

  DECLARE_CASTABLE;
};

class _OWLCLASS TReplaceDialog : public TFindReplaceDialog {
  public:
    TReplaceDialog(TWindow*        parent,
                   TData&          data,
                   TResId          templateId = 0,
                   const char far* title = 0,
                   TModule*        module = 0);

  protected:
    HWND     DoCreate();

  private:
    TReplaceDialog(const TReplaceDialog&);
    TReplaceDialog& operator=(const TReplaceDialog&);

  DECLARE_CASTABLE;
};

#endif  // OWL_FINDREPL_H
