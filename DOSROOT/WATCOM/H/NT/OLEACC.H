/*
 *  oleacc.h    Active Accessibility functions and interfaces
 *
 * =========================================================================
 *
 *                          Open Watcom Project
 *
 * Copyright (c) 2004-2025 The Open Watcom Contributors. All Rights Reserved.
 *
 *    This file is automatically generated. Do not edit directly.
 *
 * =========================================================================
 */

#include <rpc.h>
#include <rpcndr.h>
#ifndef COM_NO_WINDOWS_H
    #include <windows.h>
    #include <ole2.h>
#endif

#ifndef __oleacc_h__
#define __oleacc_h__

#ifndef _ENABLE_AUTODEPEND
 #pragma read_only_file
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
typedef interface IAccessible   IAccessible;

/* Active Accessibility property identifier data type */
typedef GUID    MSAAPROPID;

/* Active Accessibility menu information signature */
#define MSAA_MENU_SIG   0xAA0DF00DL

/* Property identifiers */
DEFINE_GUID( PROPID_ACC_NAME, 0x608D3DF8, 0x8128, 0x4AA7, 0xA4, 0x28, 0xF5, 0x5E, 0x49, 0x26, 0x72, 0x91 );
DEFINE_GUID( PROPID_ACC_VALUE, 0x123FE443, 0x211A, 0x4615, 0x95, 0x27, 0xC4, 0x5A, 0x7E, 0x93, 0x71, 0x7A );
DEFINE_GUID( PROPID_ACC_DESCRIPTION, 0x4D48DFE4, 0xBD3F, 0x491F, 0xA6, 0x48, 0x49, 0x2D, 0x6F, 0x20, 0xC5, 0x88 );
DEFINE_GUID( PROPID_ACC_ROLE, 0xCB905FF2, 0x7BD1, 0x4C05, 0xB3, 0xC8, 0xE6, 0xC2, 0x41, 0x36, 0x4D, 0x70 );
DEFINE_GUID( PROPID_ACC_STATE, 0xA8D4D5B0, 0x0A21, 0x42D0, 0xA5, 0xC0, 0x51, 0x4E, 0x98, 0x4F, 0x45, 0x7B );
DEFINE_GUID( PROPID_ACC_HELP, 0xC831E11F, 0x44DB, 0x4A99, 0x97, 0x68, 0xCB, 0x8F, 0x97, 0x8B, 0x72, 0x31 );
DEFINE_GUID( PROPID_ACC_KEYBOARDSHORTCUT, 0x7D9BCEEE, 0x7D1E, 0x4979, 0x93, 0x82, 0x51, 0x80, 0xF4, 0x17, 0x2C, 0x34 );
DEFINE_GUID( PROPID_ACC_DEFAULTACTION, 0x180C072B, 0xC27F, 0x43C7, 0x99, 0x22, 0xF6, 0x35, 0x62, 0xA4, 0x63, 0x2B );
DEFINE_GUID( PROPID_ACC_HELPTOPIC, 0x787D1379, 0x8EDE, 0x440B, 0x8A, 0xEC, 0x11, 0xF7, 0xBF, 0x90, 0x30, 0xB3 );
DEFINE_GUID( PROPID_ACC_FOCUS, 0x6EB335DF, 0x1C29, 0x4127, 0xB1, 0x2C, 0xDE, 0xE9, 0xFD, 0x15, 0x7F, 0x2B );
DEFINE_GUID( PROPID_ACC_SELECTION, 0xB99D073C, 0xD731, 0x405B, 0x90, 0x61, 0xD9, 0x5E, 0x8F, 0x84, 0x29, 0x84 );
DEFINE_GUID( PROPID_ACC_PARENT, 0x474C22B6, 0xFFC2, 0x467A, 0xB1, 0xB5, 0xE9, 0x58, 0xB4, 0x65, 0x73, 0x30 );
DEFINE_GUID( PROPID_ACC_NAV_UP, 0x016E1A2B, 0x1A4E, 0x4767, 0x86, 0x12, 0x33, 0x86, 0xF6, 0x69, 0x35, 0xEC );
DEFINE_GUID( PROPID_ACC_NAV_DOWN, 0x031670ED, 0x3CDF, 0x48D2, 0x96, 0x13, 0x13, 0x8F, 0x2D, 0xD8, 0xA6, 0x68 );
DEFINE_GUID( PROPID_ACC_NAV_LEFT, 0x228086CB, 0x82F1, 0x4A39, 0x87, 0x05, 0xDC, 0xDC, 0x0F, 0xFF, 0x92, 0xF5 );
DEFINE_GUID( PROPID_ACC_NAV_RIGHT, 0xCD211D9F, 0xE1CB, 0x4FE5, 0xA7, 0x7C, 0x92, 0x0B, 0x88, 0x4D, 0x09, 0x5B );
DEFINE_GUID( PROPID_ACC_NAV_PREV, 0x776D3891, 0xC73B, 0x4480, 0xB3, 0xF6, 0x07, 0x6A, 0x16, 0xA1, 0x5A, 0xF6 );
DEFINE_GUID( PROPID_ACC_NAV_NEXT, 0x1CDC5455, 0x8CD9, 0x4C92, 0xA3, 0x71, 0x39, 0x39, 0xA2, 0xFE, 0x3E, 0xEE );
DEFINE_GUID( PROPID_ACC_NAV_FIRSTCHILD, 0xCFD02558, 0x557B, 0x4C67, 0x84, 0xF9, 0x2A, 0x09, 0xFC, 0xE4, 0x07, 0x49 );
DEFINE_GUID( PROPID_ACC_NAV_LASTCHILD, 0x302ECCA5, 0x48D5, 0x4F8D, 0xB6, 0x71, 0x1A, 0x8D, 0x20, 0xA7, 0x78, 0x32 );
DEFINE_GUID( PROPID_ACC_ROLEMAP, 0xF79ACDA2, 0x140D, 0x4FE6, 0x89, 0x14, 0x20, 0x84, 0x76, 0x32, 0x82, 0x69 );
DEFINE_GUID( PROPID_ACC_VALUEMAP, 0xDA1C3D79, 0xFC5C, 0x420E, 0xB3, 0x99, 0x9D, 0x15, 0x33, 0x54, 0x9E, 0x75 );
DEFINE_GUID( PROPID_ACC_STATEMAP, 0x43946C5E, 0x0AC0, 0x4042, 0xB5, 0x25, 0x07, 0xBB, 0xDB, 0xE1, 0x7F, 0xA7 );
DEFINE_GUID( PROPID_ACC_DESCRIPTIONMAP, 0x1FF1435F, 0x8A14, 0x477B, 0xB2, 0x26, 0xA0, 0xAB, 0xE2, 0x79, 0x97, 0x5D );
DEFINE_GUID( PROPID_ACC_DODEFAULTACTION, 0x1BA09523, 0x2E3B, 0x49A6, 0xA0, 0x59, 0x59, 0x68, 0x2A, 0x3C, 0x48, 0xFD );

/* IAccessible dispatch identifiers */
#define DISPID_ACC_PARENT           (-5000)
#define DISPID_ACC_CHILDCOUNT       (-5001)
#define DISPID_ACC_CHILD            (-5002)
#define DISPID_ACC_NAME             (-5003)
#define DISPID_ACC_VALUE            (-5004)
#define DISPID_ACC_DESCRIPTION      (-5005)
#define DISPID_ACC_ROLE             (-5006)
#define DISPID_ACC_STATE            (-5007)
#define DISPID_ACC_HELP             (-5008)
#define DISPID_ACC_HELPTOPIC        (-5009)
#define DISPID_ACC_KEYBOARDSHORTCUT (-5010)
#define DISPID_ACC_FOCUS            (-5011)
#define DISPID_ACC_SELECTION        (-5012)
#define DISPID_ACC_DEFAULTACTION    (-5013)
#define DISPID_ACC_SELECT           (-5014)
#define DISPID_ACC_LOCATION         (-5015)
#define DISPID_ACC_NAVIGATE         (-5016)
#define DISPID_ACC_HITTEST          (-5017)
#define DISPID_ACC_DODEFAULTACTION  (-5018)

/* Navigation direction */
#define NAVDIR_MIN          0x00000000L
#define NAVDIR_UP           0x00000001L
#define NAVDIR_DOWN         0x00000002L
#define NAVDIR_LEFT         0x00000003L
#define NAVDIR_RIGHT        0x00000004L
#define NAVDIR_NEXT         0x00000005L
#define NAVDIR_PREVIOUS     0x00000006L
#define NAVDIR_FIRSTCHILD   0x00000007L
#define NAVDIR_LASTCHILD    0x00000008L
#define NAVDIR_MAX          0x00000009L

/* Selection flags */
#define SELFLAG_NONE            0x00000000L
#define SELFLAG_TAKEFOCUS       0x00000001L
#define SELFLAG_TAKESELECTION   0x00000002L
#define SELFLAG_EXTENDSELECTION 0x00000004L
#define SELFLAG_ADDSELECTION    0x00000008L
#define SELFLAG_REMOVESELECTION 0x00000010L
#define SELFLAG_VALID           0x0000001FL

/* System state flags */
#ifndef STATE_SYSTEM_UNAVAILABLE
    #define STATE_SYSTEM_SELECTED           0x00000002L
    #define STATE_SYSTEM_FOCUSED            0x00000004L
    #define STATE_SYSTEM_PRESSED            0x00000008L
    #define STATE_SYSTEM_CHECKED            0x00000010L
    #define STATE_SYSTEM_MIXED              0x00000020L
    #define STATE_SYSTEM_INDETERMINATE      STATE_SYSTEM_MIXED
    #define STATE_SYSTEM_READONLY           0x00000040L
    #define STATE_SYSTEM_HOTTRACKED         0x00000080L
    #define STATE_SYSTEM_DEFAULT            0x00000100L
    #define STATE_SYSTEM_EXPANDED           0x00000200L
    #define STATE_SYSTEM_COLLAPSED          0x00000400L
    #define STATE_SYSTEM_BUSY               0x00000800L
    #define STATE_SYSTEM_FLOATING           0x00001000L
    #define STATE_SYSTEM_MARQUEED           0x00002000L
    #define STATE_SYSTEM_ANIMATED           0x00004000L
    #define STATE_SYSTEM_INVISIBLE          0x00008000L
    #define STATE_SYSTEM_OFFSCREEN          0x00010000L
    #define STATE_SYSTEM_SIZEABLE           0x00020000L
    #define STATE_SYSTEM_MOVEABLE           0x00040000L
    #define STATE_SYSTEM_SELFVOICING        0x00080000L
    #define STATE_SYSTEM_FOCUSABLE          0x00100000L
    #define STATE_SYSTEM_SELECTABLE         0x00200000L
    #define STATE_SYSTEM_LINKED             0x00400000L
    #define STATE_SYSTEM_TRAVERSED          0x00800000L
    #define STATE_SYSTEM_MULTISELECTABLE    0x01000000L
    #define STATE_SYSTEM_EXTSELECTABLE      0x02000000L
    #define STATE_SYSTEM_ALERT_LOW          0x04000000L
    #define STATE_SYSTEM_ALERT_MEDIUM       0x08000000L
    #define STATE_SYSTEM_ALERT_HIGH         0x10000000L
    #define STATE_SYSTEM_PROTECTED          0x20000000L
    #define STATE_SYSTEM_VALID              0x7FFFFFFFL
#endif
#ifndef STATE_SYSTEM_HASPOPUP
    #define STATE_SYSTEM_HASPOPUP           0x40000000L
#endif

/* System roles */
#define ROLE_SYSTEM_TITLEBAR            0x00000001L
#define ROLE_SYSTEM_MENUBAR             0x00000002L
#define ROLE_SYSTEM_SCROLLBAR           0x00000003L
#define ROLE_SYSTEM_GRIP                0x00000004L
#define ROLE_SYSTEM_SOUND               0x00000005L
#define ROLE_SYSTEM_CURSOR              0x00000006L
#define ROLE_SYSTEM_CARET               0x00000007L
#define ROLE_SYSTEM_ALERT               0x00000008L
#define ROLE_SYSTEM_WINDOW              0x00000009L
#define ROLE_SYSTEM_CLIENT              0x0000000AL
#define ROLE_SYSTEM_MENUPOPUP           0x0000000BL
#define ROLE_SYSTEM_MENUITEM            0x0000000CL
#define ROLE_SYSTEM_TOOLTIP             0x0000000DL
#define ROLE_SYSTEM_APPLICATION         0x0000000EL
#define ROLE_SYSTEM_DOCUMENT            0x0000000FL
#define ROLE_SYSTEM_PANE                0x00000010L
#define ROLE_SYSTEM_CHART               0x00000011L
#define ROLE_SYSTEM_DIALOG              0x00000012L
#define ROLE_SYSTEM_BORDER              0x00000013L
#define ROLE_SYSTEM_GROUPING            0x00000014L
#define ROLE_SYSTEM_SEPARATOR           0x00000015L
#define ROLE_SYSTEM_TOOLBAR             0x00000016L
#define ROLE_SYSTEM_STATUSBAR           0x00000017L
#define ROLE_SYSTEM_TABLE               0x00000018L
#define ROLE_SYSTEM_COLUMNHEADER        0x00000019L
#define ROLE_SYSTEM_ROWHEADER           0x0000001AL
#define ROLE_SYSTEM_COLUMN              0x0000001BL
#define ROLE_SYSTEM_ROW                 0x0000001CL
#define ROLE_SYSTEM_CELL                0x0000001DL
#define ROLE_SYSTEM_LINK                0x0000001EL
#define ROLE_SYSTEM_HELPBALLOON         0x0000001FL
#define ROLE_SYSTEM_CHARACTER           0x00000020L
#define ROLE_SYSTEM_LIST                0x00000021L
#define ROLE_SYSTEM_LISTITEM            0x00000022L
#define ROLE_SYSTEM_OUTLINE             0x00000023L
#define ROLE_SYSTEM_OUTLINEITEM         0x00000024L
#define ROLE_SYSTEM_PAGETAB             0x00000025L
#define ROLE_SYSTEM_PROPERTYPAGE        0x00000026L
#define ROLE_SYSTEM_INDICATOR           0x00000027L
#define ROLE_SYSTEM_GRAPHIC             0x00000028L
#define ROLE_SYSTEM_STATICTEXT          0x00000029L
#define ROLE_SYSTEM_TEXT                0x0000002AL
#define ROLE_SYSTEM_PUSHBUTTON          0x0000002BL
#define ROLE_SYSTEM_CHECKBUTTON         0x0000002CL
#define ROLE_SYSTEM_RADIOBUTTON         0x0000002DL
#define ROLE_SYSTEM_COMBOBOX            0x0000002EL
#define ROLE_SYSTEM_DROPLIST            0x0000002FL
#define ROLE_SYSTEM_PROGRESSBAR         0x00000030L
#define ROLE_SYSTEM_DIAL                0x00000031L
#define ROLE_SYSTEM_HOTKEYFIELD         0x00000032L
#define ROLE_SYSTEM_SLIDER              0x00000033L
#define ROLE_SYSTEM_SPINBUTTON          0x00000034L
#define ROLE_SYSTEM_DIAGRAM             0x00000035L
#define ROLE_SYSTEM_ANIMATION           0x00000036L
#define ROLE_SYSTEM_EQUATION            0x00000037L
#define ROLE_SYSTEM_BUTTONDROPDOWN      0x00000038L
#define ROLE_SYSTEM_BUTTONMENU          0x00000039L
#define ROLE_SYSTEM_BUTTONDROPDOWNGRID  0x0000003AL
#define ROLE_SYSTEM_WHITESPACE          0x0000003BL
#define ROLE_SYSTEM_PAGETABLIST         0x0000003CL
#define ROLE_SYSTEM_CLOCK               0x0000003DL
#define ROLE_SYSTEM_SPLITBUTTON         0x0000003EL
#define ROLE_SYSTEM_IPADDRESS           0x0000003FL
#define ROLE_SYSTEM_OUTLINEBUTTON       0x00000040L

/* Active Accessibility menu information */
typedef struct tagMSAAMENUINFO {
    DWORD   dwMSAASignature;
    DWORD   cchWText;
    LPWSTR  pszWText;
} MSAAMENUINFO;
typedef MSAAMENUINFO    *LPMSAAMENUINFO;

/* Active Accessibility callbacks */
typedef LRESULT (STDAPICALLTYPE *LPFNLRESULTFROMOBJECT)( REFIID, WPARAM, LPUNKNOWN );
typedef HRESULT (STDAPICALLTYPE *LPFNOBJECTFROMLRESULT)( LRESULT, REFIID, WPARAM, void ** );
typedef HRESULT (STDAPICALLTYPE *LPFNACCESSIBLEOBJECTFROMWINDOW)( HWND, DWORD, REFIID, void ** );
typedef HRESULT (STDAPICALLTYPE *LPFNACCESSIBLEOBJECTFROMPOINT)( POINT, IAccessible **, VARIANT * );
typedef HRESULT (STDAPICALLTYPE *LPFNCREATESTDACCESSIBLEOBJECT)( HWND, LONG, REFIID, void ** );
typedef HRESULT (STDAPICALLTYPE *LPFNACCESSIBLECHILDREN)( IAccessible *, LONG, LONG, VARIANT *, LONG * );

/* Annotation scopes */
typedef enum AnnoScope {
    ANNO_THIS       = 0,
    ANNO_CONTAINER  = 1
} AnnoScope;

/* IAccessible interface */
#undef INTERFACE
#define INTERFACE   IAccessible
DECLARE_INTERFACE_( IAccessible, IDispatch ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;
    
    /* IDispatch methods */
    STDMETHOD( GetTypeInfoCount )( THIS_ UINT * ) PURE;
    STDMETHOD( GetTypeInfo )( THIS_ UINT, LCID, ITypeInfo ** ) PURE;
    STDMETHOD( GetIDsOfNames )( THIS_ REFIID, LPOLESTR *, UINT, LCID, DISPID * ) PURE;
    STDMETHOD( Invoke )( THIS_ DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT * ) PURE;

    /* IAccessible methods */
    STDMETHOD( get_accParent )( THIS_ IDispatch ** ) PURE;
    STDMETHOD( get_accChildCount )( THIS_ long * ) PURE;
    STDMETHOD( get_accChild )( THIS_ VARIANT, IDispatch ** ) PURE;
    STDMETHOD( get_accName )( THIS_ VARIANT, BSTR * ) PURE;
    STDMETHOD( get_accValue )( THIS_ VARIANT, BSTR * ) PURE;
    STDMETHOD( get_accDescription )( THIS_ VARIANT, BSTR * ) PURE;
    STDMETHOD( get_accRole )( THIS_ VARIANT, VARIANT * ) PURE;
    STDMETHOD( get_accState )( THIS_ VARIANT, VARIANT * ) PURE;
    STDMETHOD( get_accHelp )( THIS_ VARIANT, BSTR * ) PURE;
    STDMETHOD( get_accHelpTopic )( THIS_ BSTR *, VARIANT, long * ) PURE;
    STDMETHOD( get_accKeyboardShortcut )( THIS_ VARIANT, BSTR * ) PURE;
    STDMETHOD( get_accFocus )( THIS_ VARIANT * ) PURE;
    STDMETHOD( get_accSelection )( THIS_ VARIANT * ) PURE;
    STDMETHOD( get_accDefaultAction )( THIS_ VARIANT, BSTR * ) PURE;
    STDMETHOD( accSelect )( THIS_ long, VARIANT ) PURE;
    STDMETHOD( accLocation )( THIS_ long *, long *, long *, long *, VARIANT ) PURE;
    STDMETHOD( accNavigate )( THIS_ long, VARIANT, VARIANT * ) PURE;
    STDMETHOD( accHitTest )( THIS_ long, long, VARIANT * ) PURE;
    STDMETHOD( accDoDefaultAction )( THIS_ VARIANT ) PURE;
    STDMETHOD( put_accName )( THIS_ VARIANT, BSTR ) PURE;
    STDMETHOD( put_accValue )( THIS_ VARIANT, BSTR ) PURE;
};
typedef IAccessible *LPACCESSIBLE;

/* IAccessibleHandler interface */
#undef INTERFACE
#define INTERFACE   IAccessibleHandler
DECLARE_INTERFACE_( IAccessibleHandler, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IAccessibleHandler methods */
    STDMETHOD( AccessibleObjectFromID )( THIS_ long, long, LPACCESSIBLE * ) PURE;
};
typedef IAccessibleHandler  *LPACCESSIBLEHANDLER;

/* IAccIdentity interface */
#undef INTERFACE
#define INTERFACE   IAccIdentity
DECLARE_INTERFACE_( IAccIdentity, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IAccIdentity methods */
    STDMETHOD( GetIdentityString )( THIS_ DWORD, BYTE **, DWORD * ) PURE;
};

/* IAccPropServer interface */
#undef INTERFACE
#define INTERFACE   IAccPropServer
DECLARE_INTERFACE_( IAccPropServer, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IAccPropServer methods */
    STDMETHOD( GetPropValue )( THIS_ const BYTE *, DWORD, MSAAPROPID, VARIANT *, BOOL * ) PURE;
};

/* IAccPropServices interface */
#undef INTERFACE
#define INTERFACE   IAccPropServices
DECLARE_INTERFACE_( IAccPropServices, IUnknown ) {
    /* IUnknown methods */
    STDMETHOD( QueryInterface )( THIS_ REFIID, void ** ) PURE;
    STDMETHOD_( ULONG, AddRef )( THIS ) PURE;
    STDMETHOD_( ULONG, Release )( THIS ) PURE;

    /* IAccPropServices methods */
    STDMETHOD( SetPropValue )( THIS_ const BYTE *, DWORD, MSAAPROPID, VARIANT ) PURE;
    STDMETHOD( SetPropServer )( THIS_ const BYTE *, DWORD, const MSAAPROPID *, int, IAccPropServer *, AnnoScope ) PURE;
    STDMETHOD( ClearProps )( THIS_ const BYTE *, DWORD, const MSAAPROPID *, int ) PURE;
    STDMETHOD( SetHwndProp )( THIS_ HWND, DWORD, DWORD, MSAAPROPID, VARIANT ) PURE;
    STDMETHOD( SetHwndPropStr )( THIS_ HWND, DWORD, DWORD, MSAAPROPID, LPCWSTR ) PURE;
    STDMETHOD( SetHwndPropServer )( THIS_ HWND, DWORD, DWORD, const MSAAPROPID *, int, IAccPropServer *, AnnoScope ) PURE;
    STDMETHOD( ClearHwndProps )( THIS_ HWND, DWORD, DWORD, const MSAAPROPID *, int ) PURE;
    STDMETHOD( CompareHwndIdentityString )( THIS_ HWND, DWORD, DWORD, BYTE **, DWORD * ) PURE;
    STDMETHOD( DecompareHwndIdentityString )( THIS_ const BYTE *, DWORD, HWND *, DWORD *, DWORD * ) PURE;
    STDMETHOD( SetHmenuProp )( THIS_ HMENU, DWORD, MSAAPROPID, VARIANT ) PURE;
    STDMETHOD( SetHmenuPropStr )( THIS_ HMENU, DWORD, MSAAPROPID, LPCWSTR ) PURE;
    STDMETHOD( SetHmenuPropServer )( THIS_ HMENU, DWORD, const MSAAPROPID *, int, IAccPropServer *, AnnoScope ) PURE;
    STDMETHOD( ClearHmenuProps )( THIS_ HMENU, DWORD, const MSAAPROPID *, int ) PURE;
    STDMETHOD( CompareHmenuIdentityString )( THIS_ HMENU, DWORD, BYTE **, DWORD * ) PURE;
    STDMETHOD( DecompareHmenuIdentityString )( THIS_ const BYTE *, DWORD, HMENU *, DWORD * ) PURE;
};

/* C object macros */
#if (!defined( __cplusplus ) || defined( CINTERFACE )) && defined( COBJMACROS )
    #define IAccessible_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IAccessible_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IAccessible_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IAccessible_GetTypeInfoCount( x, p ) \
        (x)->lpVtbl->GetTypeInfoCount( x, p )
    #define IAccessible_GetTypeInfo( x, p1, p2, p3 ) \
        (x)->lpVtbl->GetTypeInfo( x, p1, p2, p3 )
    #define IAccessible_GetIDsOfNames( x, p1, p2, p3, p4, p5 ) \
        (x)->lpVtbl->GetIDsOfNames( x, p1, p2, p3, p4, p5 )
    #define IAccessible_Invoke( x, p1, p2, p3, p4, p5, p6, p7, p8 ) \
        (x)->lpVtbl->Invoke( x, p1, p2, p3, p4, p5, p6, p7, p8 )
    #define IAccessible_get_accParent( x, p ) \
        (x)->lpVtbl->get_accParent( x, p )
    #define IAccessible_get_accChildCount( x, p ) \
        (x)->lpVtbl->get_accChildCount( x, p )
    #define IAccessible_get_accChild( x, p1, p2 ) \
        (x)->lpVtbl->get_accChild( x, p1, p2 )
    #define IAccessible_get_accName( x, p1, p2 ) \
        (x)->lpVtbl->get_accName( x, p1, p2 )
    #define IAccessible_get_accValue( x, p1, p2 ) \
        (x)->lpVtbl->get_accValue( x, p1, p2 )
    #define IAccessible_get_accDescription( x, p1, p2 ) \
        (x)->lpVtbl->get_accDescription( x, p1, p2 )
    #define IAccessible_get_accRole( x, p1, p2 ) \
        (x)->lpVtbl->get_accRole( x, p1, p2 )
    #define IAccessible_get_accState( x, p1, p2 ) \
        (x)->lpVtbl->get_accState( x, p1, p2 )
    #define IAccessible_get_accHelp( x, p1, p2 ) \
        (x)->lpVtbl->get_accHelp( x, p1, p2 )
    #define IAccessible_get_accHelpTopic( x, p1, p2, p3 ) \
        (x)->lpVtbl->get_accHelpTopic( x, p1, p2, p3 )
    #define IAccessible_get_accKeyboardShortcut( x, p1, p2 ) \
        (x)->lpVtbl->get_accKeyboardShortcut( x, p1, p2 )
    #define IAccessible_get_accFocus( x, p ) \
        (x)->lpVtbl->get_accFocus( x, p )
    #define IAccessible_get_accSelection( x, p ) \
        (x)->lpVtbl->get_accSelection( x, p )
    #define IAccessible_get_accDefaultAction( x, p1, p2 ) \
        (x)->lpVtbl->get_accDefaultAction( x, p1, p2 )
    #define IAccessible_accSelect( x, p1, p2 ) \
        (x)->lpVtbl->accSelect( x, p1, p2 )
    #define IAccessible_accLocation( x, p1, p2, p3, p4, p5 ) \
        (x)->lpVtbl->accLocation( x, p1, p2, p3, p4, p5 )
    #define IAccessible_accNavigate( x, p1, p2, p3 ) \
        (x)->lpVtbl->accNavigate( x, p1, p2, p3 )
    #define IAccessible_accHitTest( x, p1, p2, p3 ) \
        (x)->lpVtbl->accHitTest( x, p1, p2, p3 )
    #define IAccessible_accDoDefaultAction( x, p ) \
        (x)->lpVtbl->accDoDefaultAction( x, p )
    #define IAccessible_put_accName( x, p1, p2 ) \
        (x)->lpVtbl->put_accName( x, p1, p2 )
    #define IAccessible_put_accValue( x, p1, p2 ) \
        (x)->lpVtbl->put_accValue( x, p1, p2 )
    #define IAccessibleHandler_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IAccessibleHandler_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IAccessibleHandler_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IAccessibleHandler_AccessibleObjectFromID( x, p1, p2, p3 ) \
        (x)->lpVtbl->AccessibleObjectFromID( x, p1, p2, p3 )
    #define IAccIdentity_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IAccIdentity_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IAccIdentity_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IAccIdentity_GetIdentityString( x, p1, p2, p3 ) \
        (x)->lpVtbl->GetIdentityString( x, p1, p2, p3 )
    #define IAccPropServer_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IAccPropServer_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IAccPropServer_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IAccPropServer_GetPropValue( x, p1, p2, p3, p4, p5 ) \
        (x)->lpVtbl->GetPropValue( x, p1, p2, p3, p4, p5 )
    #define IAccPropServices_QueryInterface( x, p1, p2 ) \
        (x)->lpVtbl->QueryInterface( x, p1, p2 )
    #define IAccPropServices_AddRef( x ) \
        (x)->lpVtbl->AddRef( x )
    #define IAccPropServices_Release( x ) \
        (x)->lpVtbl->Release( x )
    #define IAccPropServices_SetPropValue( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->SetPropValue( x, p1, p2, p3, p4 )
    #define IAccPropServices_SetPropServer( x, p1, p2, p3, p4, p5, p6 ) \
        (x)->lpVtbl->SetPropServer( x, p1, p2, p3, p4, p5, p6 )
    #define IAccPropServices_ClearProps( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->ClearProps( x, p1, p2, p3, p4 )
    #define IAccPropServices_SetHwndProp( x, p1, p2, p3, p4, p5 ) \
        (x)->lpVtbl->SetHwndProp( x, p1, p2, p3, p4, p5 )
    #define IAccPropServices_SetHwndPropStr( x, p1, p2, p3, p4, p5 ) \
        (x)->lpVtbl->SetHwndPropStr( x, p1, p2, p3, p4, p5 )
    #define IAccPropServices_SetHwndPropServer( x, p1, p2, p3, p4, p5, p6, p7 ) \
        (x)->lpVtbl->SetHwndPropServer( x, p1, p2, p3, p4, p5, p6, p7 )
    #define IAccPropServices_ClearHwndProps( x, p1, p2, p3, p4, p5 ) \
        (x)->lpVtbl->ClearHwndProps( x, p1, p2, p3, p4, p5 )
    #define IAccPropServices_CompareHwndIdentityString( x, p1, p2, p3, p4, p5 ) \
        (x)->lpVtbl->CompareHwndIdentityString( x, p1, p2, p3, p4, p5 )
    #define IAccPropServices_DecompareHwndIdentityString( x, p1, p2, p3, p4, p5 ) \
        (x)->lpVtbl->DecompareHwndIdentityString( x, p1, p2, p3, p4, p5 )
    #define IAccPropServices_SetHmenuProp( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->SetHmenuProp( x, p1, p2, p3, p4 )
    #define IAccPropServices_SetHmenuPropStr( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->SetHmenuPropStr( x, p1, p2, p3, p4 )
    #define IAccPropServices_SetHmenuPropServer( x, p1, p2, p3, p4, p5, p6 ) \
        (x)->lpVtbl->SetHmenuPropServer( x, p1, p2, p3, p4, p5, p6 )
    #define IAccPropServices_ClearHmenuProps( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->ClearHmenuProps( x, p1, p2, p3, p4 )
    #define IAccPropServices_ComposeHmenuIdentityString( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->ComposeHmenuIdentityString( x, p1, p2, p3, p4 )
    #define IAccPropServices_DecomposeHmenuIdentityString( x, p1, p2, p3, p4 ) \
        (x)->lpVtbl->DecomposeHmenuIdentityString( x, p1, p2, p3, p4 )
#endif

/* Functions in OLEACC.DLL */
STDAPI              AccessibleChildren( IAccessible *, LONG, LONG, VARIANT *, LONG * );
STDAPI              AccessibleObjectFromEvent( HWND, DWORD, DWORD, IAccessible **, VARIANT * );
STDAPI              AccessibleObjectFromPoint( POINT, IAccessible **, VARIANT * );
STDAPI              AccessibleObjectFromWindow( HWND, DWORD, REFIID, void ** );
STDAPI              CreateStdAccessibleObject( HWND, LONG, REFIID, void ** );
STDAPI              CreateStdAccessibleProxyA( HWND, LPCSTR, LONG, REFIID, void ** );
STDAPI              CreateStdAccessibleProxyW( HWND, LPCWSTR, LONG, REFIID, void ** );
STDAPI_( VOID )     GetOleaccVersionInfo( DWORD *, DWORD * );
STDAPI_( UINT )     GetRoleTextA( DWORD, LPSTR, UINT );
STDAPI_( UINT )     GetRoleTextW( DWORD, LPWSTR, UINT );
STDAPI_( UINT )     GetStateTextA( DWORD, LPSTR, UINT );
STDAPI_( UINT )     GetStateTextW( DWORD, LPWSTR, UINT );
STDAPI_( LRESULT )  LresultFromObject( REFIID, WPARAM, LPUNKNOWN );
STDAPI              ObjectFromLresult( LRESULT, REFIID, WPARAM, void ** );
STDAPI              WindowFromAccessibleObject( IAccessible *, HWND * );

/* Map generic function names to the appropriate ANSI or Unicode version. */
#ifdef UNICODE
    #define CreateStdAccessibleProxy    CreateStdAccessibleProxyW
    #define GetRoleText                 GetRoleTextW
    #define GetStateText                GetStateTextW
#else
    #define CreateStdAccessibleProxy    CreateStdAccessibleProxyA
    #define GetRoleText                 GetRoleTextA
    #define GetStateText                GetStateTextA
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

/* GUIDs */
EXTERN_C const IID      __cdecl IID_IAccessible;
EXTERN_C const IID      __cdecl IID_IAccessibleHandler;
EXTERN_C const IID      __cdecl IID_IAccIdentity;
EXTERN_C const IID      __cdecl IID_IAccPropServer;
EXTERN_C const IID      __cdecl IID_IAccPropServices;
EXTERN_C const IID      __cdecl LIBID_Accessibility;
EXTERN_C const CLSID    __cdecl CLSID_CAccPropServices;

#endif /* __oleacc_h__ */
