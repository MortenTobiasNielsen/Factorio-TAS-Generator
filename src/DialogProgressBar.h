#pragma once

#include "GUI_Base.h"
#include <wx/wx.h>

using std::string;

class DialogProgressBar : public BaseForDialogProgress
{
public:

	DialogProgressBar(wxWindow* parent, wxWindowID id, const wxString& title);

	void set_progress(const int& progress);

	void set_button_enable(bool enabled);

	void set_text(const string& text);

protected:

	void GenerateScriptOnClick(wxCommandEvent& event);
};