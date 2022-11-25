#pragma once
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/string.h>

//Top center panel with radio buttons
class TypePanel : public wxPanel
{
public:
	const struct TASK_TYPE
	{
		enum task_type
		{
			Take, Put, Game_Speed, Craft, Walk, Mine, Start,
			Build, Recipe, Tech, Limit, Idle, Filter, Pause,
			Priority, Rotate, Pick_Up, Drop, Launch, Save, Stop
		};
	};

	// Empty constructor: likely means you are doing something wrong
	TypePanel() : wxPanel()
	{}
	// Chain constructor: TypePanel -> wxPanel
	TypePanel(wxWindow* parent,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL | wxNO_BORDER,
		const wxString& name = wxASCII_STR(wxPanelNameStr)) : wxPanel(parent, winid, pos, size, style, name)
	{}

	// Takes a task_type and enables the corresponding radio button 
	void SwitchTask(TASK_TYPE::task_type type);

public:
	// Modifier strings: used to manipulate step detail fields and labels
	static const inline wxString
		item = "Item:",
		recipe = "Recipe:",
		tech = "Technology:",
		input = "Input",
		output = "Output",
		from = "From:",
		into = "Into:";
};
