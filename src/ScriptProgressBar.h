#pragma once

#include "GUI_Base.h"
#include <wx/wx.h>

class dialog_progress_bar_base : public BaseForDialogProgress
{
public:

	dialog_progress_bar_base(wxWindow* parent, wxWindowID id, const wxString& title) : BaseForDialogProgress(parent, id, title)
	{};

	void set_progress(const int& progress)
	{
		progress_bar->SetValue(progress);
	};

	void set_button_enable(bool enabled)
	{
		btn_dialog_progress_done->Enable(enabled);
		btn_dialog_progress_done->SetFocus();
	};

	void set_text(const std::string& text)
	{
		txt_dialog_text->SetLabelText(text);
	}

protected:

	void GenerateScriptOnClick(wxCommandEvent& event)
	{
		Hide();
	};

private:

};