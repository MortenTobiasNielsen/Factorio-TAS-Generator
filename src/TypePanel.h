#pragma once
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/string.h>

#include "StepNameToEnum.h"

//Top center panel with radio buttons
class TypePanel : public wxPanel
{
public:
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

	// Takes a step_type and enables the corresponding radio button 
	void SwitchStep(StepType type);

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
