/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        gui/CGUIComboBox_Impl.h
*  PURPOSE:     Combobox widget class
*  DEVELOPERS:  Christian Myhre Lundheim <>
*               Cecill Etheredge <ijsf@gmx.net>
*               Stanislav Bobrov <lil_Toady@hotmail.com>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CGUICOMBOBOX_IMPL_H
#define __CGUICOMBOBOX_IMPL_H

#include "CGUIElement_Impl.h"
#include "CGUIListItem_Impl.h"

#include <unordered_map>

class CGUIComboBox_Impl : public CGUIComboBox, public CGUIElement_Impl
{
public:
                                CGUIComboBox_Impl           ( class CGUI_Impl* pGUI, CGUIElement* pParent = NULL, const char* szCaption = "" );
                                ~CGUIComboBox_Impl          ( void );

    eCGUIType                   GetType                     ( void ) { return CGUI_COMBOBOX; };

    CGUIListItem*               AddItem                     ( const char* szText );
    CGUIListItem*               AddItem                     ( CGUIStaticImage* pImage );
    bool                        RemoveItem                  ( int index );
    CGUIListItem*               GetItemByIndex              ( int index );
    CGUIListItem*               GetSelectedItem             ( void );
    int                         GetSelectedItemIndex        ( void );
    size_t                      GetItemCount                ( void );
    int                         GetItemIndex                ( CGUIListItem* pItem );
    const char*                 GetItemText                 ( int index );
    bool                        SetItemText                 ( int index, const char* szText );
    bool                        SetSelectedItemByIndex      ( int index );
    void                        Clear                       ( void );

    void                        SetReadOnly                 ( bool bReadonly );

    void                        SetSelectionHandler         ( GUI_CALLBACK Callback );
    void                        SetDropListRemoveHandler    ( GUI_CALLBACK Callback );

    void                        ShowDropList                ( void );
    void                        HideDropList                ( void );

    #include "CGUIElement_Inc.h"

protected:

    std::unordered_map < CEGUI::ListboxItem*, CGUIListItem_Impl* > m_Items;

    bool                                Event_OnSelectionAccepted  ( const CEGUI::EventArgs& e );
    bool                                Event_OnDropListRemoved    ( const CEGUI::EventArgs& e );
    CGUIListItem_Impl*                  GetListItem                ( CEGUI::ListboxItem* pItem );
    CEGUI::String                       storedCaption;
    GUI_CALLBACK                        m_OnSelectChange;
    GUI_CALLBACK                        m_OnDropListRemoved;
};

#endif
