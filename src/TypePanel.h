#pragma once
#include <wx/panel.h>
#include <wx/radiobut.h>


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
};
