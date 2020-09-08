#include "cMain.h"
#include "utils.h"
#include "Functions.h"
#include <fstream>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(10001, cMain::OnMenuNew)
EVT_MENU(10002, cMain::OnMenuOpen)
EVT_MENU(10003, cMain::OnMenuSave)
EVT_MENU(10004, cMain::OnMenuExit)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Factorio GUI", wxPoint(30, 30), wxSize(800, 600)) {

	all_items.resize(item_logistics.size() + item_production.size() + item_intermediates.size() + item_combat.size());
	all_items.insert(all_items.end(), item_logistics.begin(), item_logistics.end());
	all_items.insert(all_items.end(), item_production.begin(), item_production.end());
	all_items.insert(all_items.end(), item_intermediates.begin(), item_intermediates.end());
	all_items.insert(all_items.end(), item_combat.begin(), item_combat.end());

	static const std::vector<std::string> all_items_const(all_items);

	//Add a menu bar
	m_MenuBar = new wxMenuBar();
	this->SetMenuBar(m_MenuBar);

	// add menu for file operations
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(10001, "New");
	menuFile->Append(10002, "Open");
	menuFile->Append(10003, "Save");
	menuFile->Append(10004, "Exit");

	// add file menu to menu bar
	m_MenuBar->Append(menuFile, "File");

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer(wxHORIZONTAL);

	bSizer23->SetMinSize(wxSize(10, 10));
	label_x_cord = new wxStaticText(this, wxID_ANY, wxT("X-Cord:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	label_x_cord->Wrap(-1);
	bSizer23->Add(label_x_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_x_cord = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, -1), 0);
	bSizer23->Add(txt_x_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer30->Add(bSizer23, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer(wxHORIZONTAL);

	label_y_cord = new wxStaticText(this, wxID_ANY, wxT("Y-Cord:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	label_y_cord->Wrap(-1);
	bSizer28->Add(label_y_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_y_cord = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, -1), 0);
	bSizer28->Add(txt_y_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer30->Add(bSizer28, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer(wxVERTICAL);


	bSizer36->Add(0, 0, 1, wxEXPAND, 5);


	bSizer30->Add(bSizer36, 1, wxEXPAND, 5);


	bSizer37->Add(bSizer30, 1, wxEXPAND, 5);


	bSizer19->Add(bSizer37, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer(wxHORIZONTAL);

	label_item_category = new wxStaticText(this, wxID_ANY, wxT("Item Category:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	label_item_category->Wrap(-1);
	label_item_category->SetMinSize(wxSize(80, -1));

	bSizer31->Add(label_item_category, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_item_category = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	
	
	for (auto it = item_categories.begin(); it < item_categories.end(); it++) {
		cmb_item_category->Append(*it);
	}
	cmb_item_category->SetValue(*item_categories.begin());
	bSizer31->Add(cmb_item_category, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer24->Add(bSizer31, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer(wxHORIZONTAL);

	label_item = new wxStaticText(this, wxID_ANY, wxT("Item:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	label_item->Wrap(-1);
	label_item->SetMinSize(wxSize(80, -1));

	bSizer35->Add(label_item, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_item = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);

	for (auto it = item_logistics.begin(); it < item_logistics.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*item_logistics.begin());

	bSizer35->Add(cmb_item, 0, wxALL, 5);


	bSizer24->Add(bSizer35, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer(wxHORIZONTAL);

	label_amount = new wxStaticText(this, wxID_ANY, wxT("Amount:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	label_amount->Wrap(-1);
	label_amount->SetMinSize(wxSize(80, -1));

	bSizer34->Add(label_amount, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_amount = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer34->Add(txt_amount, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer24->Add(bSizer34, 1, wxEXPAND, 5);


	bSizer20->Add(bSizer24, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer(wxVERTICAL);


	bSizer20->Add(bSizer29, 1, wxEXPAND, 5);


	bSizer19->Add(bSizer20, 1, wxEXPAND, 5);


	bSizer19->Add(50, 0, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer(wxVERTICAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Tasks"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer18->Add(m_staticText1, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer18->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxVERTICAL);

	rbtn_mine = new wxRadioButton(this, wxID_ANY, wxT("Mine"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer12->Add(rbtn_mine, 0, wxALL, 5);


	bSizer6->Add(bSizer12, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	rbtn_rotate = new wxRadioButton(this, wxID_ANY, wxT("Rotate"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer13->Add(rbtn_rotate, 0, wxALL, 5);


	bSizer6->Add(bSizer13, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer(wxVERTICAL);

	rbtn_craft = new wxRadioButton(this, wxID_ANY, wxT("Craft"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer14->Add(rbtn_craft, 0, wxALL, 5);


	bSizer6->Add(bSizer14, 1, wxEXPAND, 5);


	bSizer18->Add(bSizer6, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer(wxVERTICAL);

	rbtn_walk = new wxRadioButton(this, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer15->Add(rbtn_walk, 0, wxALL, 5);


	bSizer7->Add(bSizer15, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer(wxVERTICAL);

	rbtn_build = new wxRadioButton(this, wxID_ANY, wxT("Build"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer16->Add(rbtn_build, 0, wxALL, 5);


	bSizer7->Add(bSizer16, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer(wxVERTICAL);

	rbtn_game_speed = new wxRadioButton(this, wxID_ANY, wxT("Game Speed"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer17->Add(rbtn_game_speed, 0, wxALL, 5);


	bSizer7->Add(bSizer17, 1, wxEXPAND, 5);


	bSizer18->Add(bSizer7, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	rbtn_fuel = new wxRadioButton(this, wxID_ANY, wxT("Fuel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(rbtn_fuel, 0, wxALL, 5);


	bSizer5->Add(bSizer8, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);

	rbtn_take = new wxRadioButton(this, wxID_ANY, wxT("Take"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer9->Add(rbtn_take, 0, wxALL, 5);


	bSizer5->Add(bSizer9, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxVERTICAL);

	rbtn_put = new wxRadioButton(this, wxID_ANY, wxT("Put"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer11->Add(rbtn_put, 0, wxALL, 5);


	bSizer5->Add(bSizer11, 1, wxEXPAND, 5);


	bSizer18->Add(bSizer5, 1, wxEXPAND, 5);

	m_staticline2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer18->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);


	bSizer19->Add(bSizer18, 1, wxEXPAND, 5);


	bSizer19->Add(10000, 0, 1, wxEXPAND, 5);


	bSizer1->Add(bSizer19, 1, wxEXPAND, 5);

	btn_add_task = new wxButton(this, wxID_ANY, wxT("Add Task"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(btn_add_task, 0, wxALL, 5);


	bSizer1->Add(500, 1000, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	rbtn_mine->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnMineChosen), NULL, this);
	rbtn_rotate->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnRotateChosen), NULL, this);
	rbtn_craft->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnCraftChosen), NULL, this);
	rbtn_walk->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnWalkChosen), NULL, this);
	rbtn_build->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnBuildChosen), NULL, this);
	rbtn_game_speed->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnGameSpeedChosen), NULL, this);
	rbtn_fuel->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnFuelChosen), NULL, this);
	rbtn_take->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnTakeChosen), NULL, this);
	rbtn_put->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnPutChosen), NULL, this);
	btn_add_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnAddTaskClicked), NULL, this);
	cmb_item_category->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(cMain::OnItemCategorySelected), NULL, this);
}

void cMain::OnMineChosen(wxCommandEvent& event) {
}

void cMain::OnRotateChosen(wxCommandEvent& event) {
}

void cMain::OnCraftChosen(wxCommandEvent& event) {
	txt_x_cord->Enable(false);
	txt_y_cord->Enable(false);
	cmb_item_category->Enable(true);
	cmb_item->Enable(true);
	txt_amount->Enable(true);
}

void cMain::OnWalkChosen(wxCommandEvent& event) {
	txt_x_cord->Enable(true);
	txt_y_cord->Enable(true);
	cmb_item_category->Enable(false);
	cmb_item->Enable(false);
	txt_amount->Enable(false);
}

void cMain::OnBuildChosen(wxCommandEvent& event) {
}

void cMain::OnGameSpeedChosen(wxCommandEvent& event) {
	txt_x_cord->Enable(false);
	txt_y_cord->Enable(false);
	cmb_item_category->Enable(false);
	cmb_item->Enable(false);
	txt_amount->Enable(true);
}

void cMain::OnFuelChosen(wxCommandEvent& event) {
	txt_x_cord->Enable(true);
	txt_y_cord->Enable(true);
	cmb_item_category->Enable(false);
	cmb_item->Enable(true);
	txt_amount->Enable(true);

	cmb_item_category->Clear();
	cmb_item_category->Append("Fuel");
	cmb_item_category->SetValue("Fuel");

	cmb_item->Clear();
	for (auto it = item_fuels.begin(); it < item_fuels.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*item_fuels.begin());
}

void cMain::OnTakeChosen(wxCommandEvent& event) {
}

void cMain::OnPutChosen(wxCommandEvent& event) {
}

void cMain::OnAddTaskClicked(wxCommandEvent& event) {
	if (rbtn_game_speed->GetValue()) {
		amount = wxAtoi(txt_amount->GetValue());
		if (amount < 1) {
			speed(1);
		} else {
			speed(amount);
		}
		
	} else if (rbtn_walk->GetValue()) {
		
		x_cord = wxAtof(txt_x_cord->GetValue());
		y_cord = wxAtof(txt_y_cord->GetValue());

		walk(x_cord, y_cord);

	} else if (rbtn_craft->GetValue()) {
		amount = wxAtoi(txt_amount->GetValue());
		item = cmb_item->GetValue().ToStdString();

		if (check_item(item, all_items)) {
			item = convert_string(item);
			craft(amount, item);
		} else {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
		}

		

	} else if (rbtn_fuel->GetValue()) {
		x_cord = wxAtof(txt_x_cord->GetValue());
		y_cord = wxAtof(txt_y_cord->GetValue());

		amount = wxAtoi(txt_amount->GetValue());
		if (amount < 1) {
			amount = -1;
		}
		
		item = cmb_item->GetValue().ToStdString();

		if (check_item(item, item_fuels)) {
			item = convert_string(item);
			fill_fuel(x_cord, y_cord, amount, item);
		} else {
			wxMessageBox("The item chosen is not a valid fuel - please try again", "Please use the item dropdown menu");
		}		
	}
	event.Skip();
}

void cMain::OnItemCategorySelected(wxCommandEvent& event) {
	if (cmb_item_category->GetValue() == "Logistics") {
		cmb_item->Clear();
		for (auto it = item_logistics.begin(); it < item_logistics.end(); it++) {
			cmb_item->Append(*it);
		}
		cmb_item->SetValue(*item_logistics.begin());

	} else if (cmb_item_category->GetValue() == "Production") {
		cmb_item->Clear();
		for (auto it = item_production.begin(); it < item_production.end(); it++) {
			cmb_item->Append(*it);
		}
		cmb_item->SetValue(*item_production.begin());

	} else if (cmb_item_category->GetValue() == "Intermediates") {
		cmb_item->Clear();
		for (auto it = item_intermediates.begin(); it < item_intermediates.end(); it++) {
			cmb_item->Append(*it);
		}
		cmb_item->SetValue(*item_intermediates.begin());

	} else if (cmb_item_category->GetValue() == "Combat") {
		cmb_item->Clear();
		for (auto it = item_combat.begin(); it < item_combat.end(); it++) {
			cmb_item->Append(*it);
		}
		cmb_item->SetValue(*item_combat.begin());
	}
}

void cMain::OnMenuNew(wxCommandEvent& evt) {

}

void cMain::OnMenuOpen(wxCommandEvent& evt) {

}

void cMain::OnMenuSave(wxCommandEvent& evt) {
	std::ofstream myfile;
	myfile.open("C:\\Users\\MTNie\\AppData\\Roaming\\Factorio\\mods\\Speed_run_0.0.1\\tasksV2.lua");

	myfile << end_tasks();;

	myfile.close();
}

void cMain::OnMenuExit(wxCommandEvent& evt) {
	Close();
	evt.Skip();
}