//----------------------------------------------------------------------------
// ObjectWindows
// (C) Copyright 1991, 1994 by Borland International, All Rights Reserved
//
//   Defines class TButton.  This defines the basic behavior
//   of all buttons.
//----------------------------------------------------------------------------
#if !defined(OWL_BUTTON_H)
#define OWL_BUTTON_H

#if !defined(OWL_CONTROL_H)
# include <owl/control.h>
#endif

//
//  class TButton
//  ----- -------
//
class _OWLCLASS TButton : public TControl {
  public:
    bool  IsDefPB;

    TButton(TWindow*        parent,
            int             id,
            const char far* text,
            int X, int Y, int W, int H,
            bool            isDefault = false,
            TModule*        module = 0);

    TButton(TWindow *parent, int resourceId, TModule* module = 0);

  protected:
    bool  IsCurrentDefPB;

    //
    // message response functions
    //
    uint      EvGetDlgCode(MSG far*);
    LRESULT   BMSetStyle(WPARAM, LPARAM);

    //
    // Override TWindow member functions
    //
    char far* GetClassName();
    void      SetupWindow();

  private:
    //
    // hidden to prevent accidental copying or assignment
    //
    TButton(const TButton&);
    TButton& operator=(const TButton&);

  DECLARE_RESPONSE_TABLE(TButton);
  DECLARE_STREAMABLE(_OWLCLASS, TButton, 1);
};

//
// button notification response table entry macros, methods are: void method()
//
// EV_BN_CLICKED(id, method)
// EV_BN_DISABLE(id, method)
// EV_BN_DOUBLECLICKED(id, method)
// EV_BN_HILITE(id, method)
// EV_BN_PAINT(id, method)
// EV_BN_UNHILITE(id, method)

#endif  // OWL_BUTTON_H
