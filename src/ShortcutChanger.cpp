#include "ShortcutChanger.h"

using json = nlohmann::json;

void ShortcutChanger::extract(json savedata)
{
	for (auto& [key, value] : savedata[shortcuts].items())
	{
		state[shortcuts][key] = value;
	}
}

void ShortcutChanger::Build(wxMenu* menu)
{
	this->menu = menu;

	//get labels and text input (start value)
	std::ifstream file(GetFile());
	state = DefaultShortcuts();
	if (file.is_open())
	{
		try { 
			json data = json::parse(file);
			if (data[shortcuts].is_object())
				extract(data);
		} catch (...) { }
		file.close();
	}

	//create grid entry for each shortcut
	for (auto& [key, value] : state[shortcuts].items())
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

json ShortcutChanger::DefaultShortcuts()
{
	//iterate through the shortcut menu to get some default values
	json j;
	for (auto a : menu->GetMenuItems())
	{
		auto b = wxSplit(a->GetItemLabel(), wxT('\t'));
		if (b.empty()) continue;

		j[shortcuts][b[0].ToStdString()] = b.size() > 1 ? b[1].ToStdString() : "";
	}
	return j;
}

void ShortcutChanger::OnCloseShortcutChanger(wxCloseEvent& event)
{
	//load settings file
	using std::fstream;
	fstream file(filename, fstream::in | fstream::out | fstream::app);
	json data;
	if (!file.is_open())
	{
		file.open(filename, fstream::in | fstream::out | fstream::app);
		data[shortcuts] = {};
	}
	else
	{
		try {
			data = json::parse(file); 
		} catch (...) {
			data[shortcuts] = {};
		}
		
	}
	file.close();

	//update settings file -> shortcuts
	std::ofstream o;
	o.open(GetFile());
	if (o.is_open())
	{
		data[shortcuts] = state[shortcuts];
		auto dump = data.dump(4);
		o << dump << std::endl;
		o.close();
	}

	event.Skip();
}

void ShortcutChanger::OnInitDialogShortcutChanger(wxInitDialogEvent& event)
{
	event.Skip();
}

void ShortcutChanger::OnButtonClickSCReset(wxCommandEvent& event)
{
	json j = state = DefaultShortcuts();
	for (auto& [key, value] : j[shortcuts].items())
	{
		auto a = std::string(value);
		wxTextCtrl* input = mapCtrl[key];
		input->SetValue(a);
	}
	event.Skip();
}

void ShortcutChanger::OnButtonClickSCSave(wxCommandEvent& event)
{
	json j = state;
	for (auto& [key, value] : j[shortcuts].items())
	{
		wxTextCtrl* input = mapCtrl[key];
		if (input == nullptr) continue;
		state[shortcuts][key] = input->GetValue().ToStdString();
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

