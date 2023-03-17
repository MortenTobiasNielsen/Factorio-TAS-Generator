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

class ImportStepsPanel : public wxPanel
{
public:
	ImportStepsPanel(wxWindow* parent,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxTAB_TRAVERSAL,
		const wxString& name = wxT("Import")) : wxPanel(parent, winid, pos, size, style, name)
	{}
private:
	/*
	ImportStepsPanel* import_steps_panel;
	wxTextCtrl* import_steps_text_import;
	wxSpinCtrl* import_steps_into_steps_ctrl;
	wxButton* import_steps_into_steps_btn;
	wxTextCtrl* import_steps_into_template_ctrl;
	wxButton* import_steps_into_template_btn;
	*/
protected:
public:

	virtual void OnImportStepsIntoStepsCtrlEnter(wxCommandEvent& event)
	{
		event.Skip();
	}
	virtual void OnImportStepsIntoStepsBtnClick(wxCommandEvent& event)
	{
		event.Skip();
	}
	virtual void OnImportStepsIntoTemplateCtrlEnter(wxCommandEvent& event)
	{
		event.Skip();
	}
	virtual void OnImportStepsIntoTemplateBtnClick(wxCommandEvent& event)
	{
		event.Skip();
	}

};
