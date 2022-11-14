#pragma once
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/string.h>


class TypePanel : public wxPanel
{
public:
    struct TASK_TYPE {
        enum task_type {
            Take,       Put,    Game_Speed, Craft,  Walk,   Mine,   Start,
            Build,      Recipe, Tech,       Limit,  Idle,   Filter, Pause,
            Priority,   Rotate, Pick_Up,    Drop,   Launch, Save,   Stop
        };
    };
    
	TypePanel() : wxPanel() {}
	TypePanel(wxWindow* parent,
        wxWindowID winid = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
        const wxString& name = wxASCII_STR(wxPanelNameStr)) : wxPanel(parent, winid, pos, size, style, name) {}

    void SwitchTask(TASK_TYPE::task_type type);

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
