//----------------------------------------------------------------------------
// ObjectWindows
// (C) Copyright 1992, 1994 by Borland International, All Rights Reserved
//
//----------------------------------------------------------------------------
#if !defined(OWL_TINYCAPT_H)
#define OWL_TINYCAPT_H

#if !defined(OWL_WINDOW_H)
# include <owl/window.h>
#endif
class _OWLCLASS TFont;

//
//  class TTinyCaption
//  ----- ------------
//
class _OWLCLASS TTinyCaption : public virtual TWindow {
  protected:
    TTinyCaption();
   ~TTinyCaption();

    //
    // Pass closeBox=true to replace SystemMenu box with a box that will 
    // close window when clicked
    // Used for floating palettes, etc.
    //
    void        EnableTinyCaption(int ch=58, bool closeBox=false);

    //
    // Controller class must handle events that call these mixin handlers
    //
    TEventStatus DoNCHitTest(TPoint& screenPt, uint& evRes);
    TEventStatus DoNCPaint();
    TEventStatus DoNCCalcSize(bool calcValidRects, 
                              NCCALCSIZE_PARAMS far& calcSize, uint& evRes);
    TEventStatus DoNCLButtonDown(uint hitTest, TPoint& screenPt);
    TEventStatus DoMouseMove(uint hitTest, TPoint& screenPt);
    TEventStatus DoLButtonUp(uint hitTest, TPoint& screenPt);
    TEventStatus DoNCActivate(bool active, bool& evRes);
    TEventStatus DoCommand(uint id, HWND hWndCtl, uint notifyCode, LRESULT& evRes);
    TEventStatus DoSysCommand(uint cmdType, TPoint& p);

  protected:
    //
    // Cache system metrics 
    //
    TSize    Border; // Thin frame border size for dividers
    TSize    Frame;  // Actual Left and Right, Top and Bottom frame size

    bool     CloseBox;      // True for special close box
    bool     TCEnabled;
    int      CaptionHeight;
    TFont*   CaptionFont;   // Tiny font for caption bar
    uint     DownHit;       // Mouse down hit test result
    bool     IsPressed;     // Is a button currently pressed
    bool     WaitingForSysCmd;

    void        PaintButton(TDC& dc, TRect& boxRect, bool pressed);
    void        PaintCloseBox(TDC& dc, TRect& boxRect, bool pressed);
    void        PaintSysBox(TDC& dc, TRect& boxRect, bool pressed);
    void        PaintMinBox(TDC& dc, TRect& boxRect, bool pressed);
    void        PaintMaxBox(TDC& dc, TRect& boxRect, bool pressed);
    void        PaintCaption(bool active);
    void        DoSysMenu();

    TRect       GetCaptionRect();  // Get caption area for hit test or paint
    TRect       GetSysBoxRect();   // Same for close box
    TRect       GetMinBoxRect();
    TRect       GetMaxBoxRect();

  protected:
    uint        EvNCHitTest(TPoint& screenPt);
    void        EvNCPaint();
    uint        EvNCCalcSize(bool calcValidRects, NCCALCSIZE_PARAMS far& calcSize);
    void        EvNCLButtonDown(uint hitTest, TPoint& screenPt);
    void        EvMouseMove(uint hitTest, TPoint& screenPt);
    void        EvLButtonUp(uint hitTest, TPoint& screenPt);
    bool        EvNCActivate(bool active);
    LRESULT     EvCommand(uint id, HWND hWndCtl, uint notifyCode);
    void        EvSysCommand(uint cmdType, TPoint& p);

  private:
    //
    // hidden to prevent accidental copying or assignment
    //
    TTinyCaption(const TTinyCaption&);
    TTinyCaption& operator =(const TTinyCaption&);

  DECLARE_RESPONSE_TABLE(TTinyCaption);
  DECLARE_STREAMABLE(_OWLCLASS, TTinyCaption, 1);
};

#endif  // OWL_TINYCAPT_H
