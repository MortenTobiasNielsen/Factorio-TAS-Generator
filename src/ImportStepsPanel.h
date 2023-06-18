#pragma once
#include <wx/panel.h>
#include <wx/string.h>
#include <wx/aui/auibook.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/spinctrl.h>

#include <string>
#include <sstream>
#include <vector>

#include "Structures\Building.h"
#include "Structures\StepParameters.h"

class ImportStepsPanel : public wxPanel
{
public:
	ImportStepsPanel(wxWindow* parent,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL,
		const wxString& name = wxT("Import")) : wxPanel(parent, winid, pos, size, style, name)
	{ }
private:
	/* ImportStepsPanel variables:
		ImportStepsPanel* import_steps_panel;
		wxTextCtrl* import_steps_text_import;
		wxSpinCtrl* import_steps_into_steps_ctrl;
		wxButton* import_steps_into_steps_btn;
		wxTextCtrl* import_steps_into_template_ctrl;
		wxButton* import_steps_into_template_btn;
		wxCheckBox* import_steps_clear_checkbox;
	*/
protected:
	std::vector<std::string> segments{};
	std::stringstream data{};
	std::vector<Building> buildingSnapshot{};
	int buildingsInSnapShot = 0;
	int position = 0; 
	
public:
	bool update_segment();
	bool extract_steps(wxString steps, vector<StepParameters>& step_parameters);

};
