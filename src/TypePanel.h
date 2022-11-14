#pragma once
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/string.h>


class TypePanel : public wxPanel
{
public:
	TypePanel() : wxPanel() {}
	TypePanel(wxWindow* parent,
        wxWindowID winid = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
        const wxString& name = wxASCII_STR(wxPanelNameStr)) : wxPanel(parent, winid, pos, size, style, name) {}

public:
    // Modifier strings
    static const inline wxString
        item = "Item:", 
        recipe = "Recipe:",
        tech = "Technology:",
        input = "Input",
        output = "Output",
        from = "From:",
        into = "Into:";
};
