/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2010 Wayne Stambaugh <stambaughw@verizon.net>
 * Copyright (C) 2010-2019 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/**
 * @file
 *
 * Subclass of DIALOG_SCH_FIND_BASE, which is generated by wxFormBuilder.
 *
 * This dialog is used to define the search criteria used to search for items
 * in the current schematic.  What is searched depends on the schematic item
 * type.  Check the Matches() method for each item derived from SCH_ITEM() to
 * find out how matching is performed against that item.
 */

#ifndef __dialog_schematic_find__
#define __dialog_schematic_find__

#include "dialog_schematic_find_base.h"

#include <wx/fdrepdlg.h>          // Use the wxFindReplaceDialog events, data, and enums.

class SCH_EDIT_FRAME;
class SCH_EDITOR_CONTROL;


/**
 * Define schematic specific find and replace dialog flags based on the enum entries
 * in wxFindReplaceFlags.   These flags are intended to be used as bit masks in the
 * wxFindReplaceData::m_Flags member variable.  The variable is defined as a wxUint32.
 */
enum SchematicFindReplaceFlags
{
    // The last wxFindReplaceFlag enum is wxFR_MATCHCASE = 0x4.

    /// Search the current sheet only.
    FR_CURRENT_SHEET_ONLY    = wxFR_MATCHCASE << 1,

    /// Search all fields in component, not just the value and reference fields.
    FR_SEARCH_ALL_FIELDS     = wxFR_MATCHCASE << 2,

    /// Search texts (name and number (a 4 letters text) )in pins.
    FR_SEARCH_ALL_PINS       = wxFR_MATCHCASE << 3,

    /// Perform search using simple wild card matching (* & ?).
    FR_MATCH_WILDCARD        = wxFR_MATCHCASE << 4,

    /// Wrap around the beginning or end of search list.
    FR_SEARCH_WRAP           = wxFR_MATCHCASE << 5,

    /// Perform a search for a item that has replaceable text.
    FR_SEARCH_REPLACE        = wxFR_MATCHCASE << 7,

    /// Used by the search event handler to let the dialog know that a replaceable
    /// item has been found.
    FR_REPLACE_ITEM_FOUND    = wxFR_MATCHCASE << 8,

    /// Used by replace to ignore the component reference designator field.
    FR_REPLACE_REFERENCES    = wxFR_MATCHCASE << 9
};


/**
 * Definition FR_MASK_NON_COMPARE_FLAGS
 * is used to mask find/replace flag bits that do not effect the search results.
 */
#define FR_MASK_NON_COMPARE_FLAGS  ~( wxFR_DOWN | FR_SEARCH_WRAP | FR_REPLACE_ITEM_FOUND )


/**
 * Class SCH_FIND_REPLACE_DATA
 * adds missing useful comparison and assignment operators to the wxFindReplaceData object.
 */
class SCH_FIND_REPLACE_DATA : public wxFindReplaceData
{
public:

    SCH_FIND_REPLACE_DATA& operator =( const SCH_FIND_REPLACE_DATA& aFindReplaceData )
    {
        if( this == &aFindReplaceData )
            return *this;

        SetFlags( aFindReplaceData.GetFlags() );
        SetFindString( aFindReplaceData.GetFindString() );
        SetReplaceString( aFindReplaceData.GetReplaceString() );

        return *this;
    }

    bool operator ==( SCH_FIND_REPLACE_DATA& aFindReplaceData )
    {
        return ( (GetFlags() == aFindReplaceData.GetFlags())
                 && (GetFindString() == aFindReplaceData.GetFindString())
                 && (GetReplaceString() == aFindReplaceData.GetReplaceString()) );
    }

    bool operator !=( SCH_FIND_REPLACE_DATA& aFindReplaceData )
    {
        return !( *this == aFindReplaceData );
    }

private:
    /**
     * Function GetSearchFlags
     * @return The flags that only effect the search result.
     */
    wxUint32 GetCompareFlags() const { return GetFlags() & FR_MASK_NON_COMPARE_FLAGS; }
};


/** Implementing DIALOG_SCH_FIND_BASE */
class DIALOG_SCH_FIND : public DIALOG_SCH_FIND_BASE
{
protected:
    // Handlers for DIALOG_SCH_FIND_BASE events.
    void OnClose( wxCloseEvent& aEvent ) override;
    void OnSearchForText( wxCommandEvent& aEvent ) override;
    void OnTextEnter( wxCommandEvent& event ) override;
    void OnOptions( wxCommandEvent& event ) override;
    void OnUpdateReplaceUI( wxUpdateUIEvent& aEvent ) override;
    void OnUpdateReplaceAllUI( wxUpdateUIEvent& aEvent ) override;

    void OnChar( wxKeyEvent& aEvent );
    void OnFind( wxCommandEvent& aEvent ) override;
    void OnReplace( wxCommandEvent& aEvent ) override;

    SCH_EDIT_FRAME*     m_frame;
    SCH_EDITOR_CONTROL* m_editorControl;
    wxFindReplaceData*  m_findReplaceData;

    DECLARE_NO_COPY_CLASS( DIALOG_SCH_FIND )

public:
    DIALOG_SCH_FIND( SCH_EDIT_FRAME* aParent, wxFindReplaceData* aData,
                     const wxPoint& aPosition = wxDefaultPosition,
                     const wxSize& aSize = wxDefaultSize, int aStyle = 0 );

    void SetFindEntries( const wxArrayString& aEntries );
    wxArrayString GetFindEntries() const;

    void SetReplaceEntries( const wxArrayString& aEntries );
    wxArrayString GetReplaceEntries() const { return m_comboReplace->GetStrings(); }
};


#endif // __dialog_schematic_find__
