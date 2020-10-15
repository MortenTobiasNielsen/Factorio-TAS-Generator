#pragma once
#include "GUI_Base.h"
#include <wx/wx.h>

class script_progress_bar : public DialogGeneratingScript {
public:

	script_progress_bar(wxWindow* parent) : DialogGeneratingScript(parent) {
	};

	void set_progress(const int &progress) {
		generate_script_progress->SetValue(progress);
	};

	void set_button_enable(bool enabled) {
		btn_generate_script_done->Enable(enabled);
	};

protected:

	void GenerateScriptOnClick(wxCommandEvent& event) {
		Hide();
	};

private:
	
};