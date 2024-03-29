#pragma once
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/string.h>

#include "Data\utils.h"
#include "Structures\StepType.h"

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

	// Mutual exclusive radio button logic - selects the one btn and diselect the rest
	void SetType(wxRadioButton * choosen_btn);

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

	WarningsStatesCounters warnings_states_counters;

	void IncrementStateCounter(StepType steptype);
};
