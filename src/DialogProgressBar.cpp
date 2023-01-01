#include "DialogProgressBar.h"

DialogProgressBar::DialogProgressBar(wxWindow* parent, wxWindowID id, const wxString& title) : BaseForDialogProgress(parent, id, title)
{};

void DialogProgressBar::set_progress(const int& progress)
{
	progress_bar->SetValue(progress);
};

void DialogProgressBar::set_button_enable(bool enabled)
{
	btn_dialog_progress_done->Enable(enabled);
	btn_dialog_progress_done->SetFocus();
};

void DialogProgressBar::set_text(const string& text)
{
	txt_dialog_text->SetLabelText(text);
}

void DialogProgressBar::GenerateScriptOnClick(wxCommandEvent& event)
{
	Hide();
};