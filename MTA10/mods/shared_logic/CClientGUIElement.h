/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.2
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientGUIElement.h
*  PURPOSE:     GUI wrapper entity class
*  DEVELOPERS:  Ed Lyons <eai@opencoding.net>
*               Cecill Etheredge <ijsf@gmx.net>
*               Jax <>
*               The_GTA <quiret@gmx.de>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

class CClientGUIElement;

#ifndef __CCLIENTGUIELEMENT_H
#define __CCLIENTGUIELEMENT_H

#include "CClientGUIManager.h"
#include "CClientEntity.h"
#include <gui/CGUI.h>

#include "gui/CClientGUIButton.h"
#include "gui/CClientGUICheckbox.h"
#include "gui/CClientGUICombobox.h"
#include "gui/CClientGUIEdit.h"
#include "gui/CClientGUIGridlist.h"
#include "gui/CClientGUILabel.h"
#include "gui/CClientGUIMemo.h"
#include "gui/CClientGUIProgressbar.h"
#include "gui/CClientGUIRadiobutton.h"
#include "gui/CClientGUIScrollbar.h"
#include "gui/CClientGUIScrollpane.h"
#include "gui/CClientGUIStaticImage.h"
#include "gui/CClientGUITab.h"
#include "gui/CClientGUITabpanel.h"
#include "gui/CClientGUIWindow.h"

#define LUACLASS_GUIELEMENT     46

#define MAX_EVENT_NAME 256

#define CGUI_GET_CCLIENTGUIELEMENT(x)   static_cast < CClientGUIElement* > ( x->GetUserData () )
#define CGUI_SET_CCLIENTGUIELEMENT(x,y) x->SetUserData ( reinterpret_cast < void* > ( y ) )

// use just for events, for all gui specific stuff use the funcs in the CGUI* classes

// supports 2 events

#define IS_CGUIELEMENT_BUTTON(entity)           ((entity)->GetCGUIType()==CGUI_BUTTON)
#define IS_CGUIELEMENT_CHECKBOX(entity)         ((entity)->GetCGUIType()==CGUI_CHECKBOX)
#define IS_CGUIELEMENT_EDIT(entity)             ((entity)->GetCGUIType()==CGUI_EDIT)
#define IS_CGUIELEMENT_GRIDLIST(entity)         ((entity)->GetCGUIType()==CGUI_GRIDLIST)
#define IS_CGUIELEMENT_LABEL(entity)            ((entity)->GetCGUIType()==CGUI_LABEL)
#define IS_CGUIELEMENT_MEMO(entity)             ((entity)->GetCGUIType()==CGUI_MEMO)
#define IS_CGUIELEMENT_PROGRESSBAR(entity)      ((entity)->GetCGUIType()==CGUI_PROGRESSBAR)
#define IS_CGUIELEMENT_SCROLLBAR(entity)        ((entity)->GetCGUIType()==CGUI_SCROLLBAR)
#define IS_CGUIELEMENT_SCROLLPANE(entity)       ((entity)->GetCGUIType()==CGUI_SCROLLPANE)
#define IS_CGUIELEMENT_RADIOBUTTON(entity)      ((entity)->GetCGUIType()==CGUI_RADIOBUTTON)
#define IS_CGUIELEMENT_STATICIMAGE(entity)      ((entity)->GetCGUIType()==CGUI_STATICIMAGE)
#define IS_CGUIELEMENT_TAB(entity)              ((entity)->GetCGUIType()==CGUI_TAB)
#define IS_CGUIELEMENT_TABPANEL(entity)         ((entity)->GetCGUIType()==CGUI_TABPANEL)
#define IS_CGUIELEMENT_COMBOBOX(entity)         ((entity)->GetCGUIType()==CGUI_COMBOBOX)
#define IS_CGUIELEMENT_WINDOW(entity)           ((entity)->GetCGUIType()==CGUI_WINDOW)

#define IS_CGUIELEMENT_VALID_PARENT(entity)     (IS_CGUIELEMENT_SCROLLPANE(entity) || IS_CGUIELEMENT_WINDOW(entity) || IS_CGUIELEMENT_TAB(entity) )

class CClientGUIElement : public CClientEntity
{
    friend class CClientGUIManager;

public:
                                CClientGUIElement( CClientManager *pManager, CLuaMain *pLuaMain, CGUIElement *pCGUIElement, bool system = false, ElementID ID = INVALID_ELEMENT_ID );
                                ~CClientGUIElement();

    void                        Unlink();

    inline eClientEntityType    GetType() const                                     { return CCLIENTGUI; }
    inline eCGUIType            GetCGUIType() const                                 { return m_pCGUIElement->GetType(); }
    inline const char*          GetCGUITypeName() const                             { return m_szCGUITypeName; }

    inline GUI_CALLBACK         GetCallback1()                                      { return GUI_CALLBACK( &CClientGUIElement::_CallbackEvent1, this ); }
    inline GUI_CALLBACK         GetCallback2()                                      { return GUI_CALLBACK( &CClientGUIElement::_CallbackEvent2, this ); }

    void                        SetEvents( const char *szFunc1, const char *szFunc2 = NULL );

    inline CLuaMain*            GetVirtualMachine()                                 { return m_pLuaMain; }

    // dummy overrides
    inline void                 SetPosition( const CVector& vecDummy )              {}
    inline void                 GetPosition( CVector& vecDummy ) const              {}

    // cgui element access
    inline CGUIElement*         GetCGUIElement()                                    { return m_pCGUIElement; }
    inline void                 SetCGUIElement( CGUIElement *pCGUIElement )         { m_pCGUIElement = pCGUIElement; }

    SString                     GetFont( class CClientGuiFont **ppFontElement );
    bool                        SetFont( const SString& strFontName, CClientGuiFont *pFontElement );

private:
    bool                        _CallbackEvent1( CGUIElement *pCGUIElement );
    bool                        _CallbackEvent2( CGUIElement *pCGUIElement );

    char                        _szCallbackFunc1[MAX_EVENT_NAME];
    char                        _szCallbackFunc2[MAX_EVENT_NAME];

    const char*                 m_szCGUITypeName;
    CClientGUIManager*          m_pGUIManager;
    CGUIElement*                m_pCGUIElement;
    CClientGuiFont*             m_pFontElement;
    CLuaMain*                   m_pLuaMain;
};

#endif
