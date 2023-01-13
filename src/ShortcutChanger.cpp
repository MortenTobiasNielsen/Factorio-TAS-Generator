#include "ShortcutChanger.h"

using json = nlohmann::json;

void ShortcutChanger::Build(wxMenu* menu)
{
	this->menu = menu;

	DefaultShortcuts();
	settings::setting s = settings::ReadSettingFile();

	for (auto& [key, value] : state.shortcuts)
	{
		if (s.shortcuts.contains(key))
			continue;
		else
			s.shortcuts[key] = value;
	}

	state = s;

	//create grid entry for each shortcut
	for (auto& [key, value] : state.shortcuts)
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		wxStaticText* label = new wxStaticText(this, wxID_ANY, wxString(key), wxDefaultPosition, wxSize(80, -1), 0);
		label->Wrap(60);
		sizer->Add(label, 0, wxALL, 5);
		wxTextCtrl* input = new wxTextCtrl(this, wxID_ANY, wxString(std::string(value)), wxDefaultPosition, wxSize(100, -1), 0);
		mapCtrl.insert({key, input});
		sizer->Add(input, 0, wxALL, 5);
		sc_grid_sizer->Add(sizer);
	};
	this->SetSizerAndFit(sc_vertical_sizer);
}

void ShortcutChanger::DefaultShortcuts()
{
	//iterate through the shortcut menu to get some default values
	for (auto a : menu->GetMenuItems())
	{
		auto b = wxSplit(a->GetItemLabel(), wxT('\t'));
		if (b.empty()) continue;

		state.shortcuts[b[0].ToStdString()] = b.size() > 1 ? b[1].ToStdString() : "";
	}
}

void ShortcutChanger::OnCloseShortcutChanger(wxCloseEvent& event)
{
	settings::SaveSettingFile(&state);

	event.Skip();
}

void ShortcutChanger::OnInitDialogShortcutChanger(wxInitDialogEvent& event)
{
	event.Skip();
}

void ShortcutChanger::OnButtonClickSCReset(wxCommandEvent& event)
{
	DefaultShortcuts();
	for (auto& [key, value] : state.shortcuts)
	{
		auto& a = value;
		wxTextCtrl* input = mapCtrl[key];
		input->SetValue(a);
	}
	event.Skip();
}

void ShortcutChanger::OnButtonClickSCSave(wxCommandEvent& event)
{
	for (auto& [key, value] : state.shortcuts)
	{
		wxTextCtrl* input = mapCtrl[key];
		if (input == nullptr) continue;

		value = input->GetValue().ToStdString();
		for (auto& a : menu->GetMenuItems())
		{
			if (a->GetItemLabel().StartsWith(key))
			{
				a->SetItemLabel(key + wxT('\t') + input->GetValue());
			}
		}
	}
	event.Skip();
}

