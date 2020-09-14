///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Sep  9 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI_Base.h"

///////////////////////////////////////////////////////////////////////////

GUI_Base::GUI_Base(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style) {
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	m_menubar1 = new wxMenuBar(0);
	menu_file = new wxMenu();
	wxMenuItem* menu_file_new;
	menu_file_new = new wxMenuItem(menu_file, wxID_ANY, wxString(wxT("New")) + wxT('\t') + wxT("CTRL+N"), wxEmptyString, wxITEM_NORMAL);
	menu_file->Append(menu_file_new);

	wxMenuItem* menu_file_open;
	menu_file_open = new wxMenuItem(menu_file, wxID_ANY, wxString(wxT("Open")) + wxT('\t') + wxT("CTRL+O"), wxEmptyString, wxITEM_NORMAL);
	menu_file->Append(menu_file_open);

	wxMenuItem* menu_file_save;
	menu_file_save = new wxMenuItem(menu_file, wxID_ANY, wxString(wxT("Save")) + wxT('\t') + wxT("CTRL+S"), wxEmptyString, wxITEM_NORMAL);
	menu_file->Append(menu_file_save);

	wxMenuItem* menu_file_save_as;
	menu_file_save_as = new wxMenuItem(menu_file, wxID_ANY, wxString(wxT("Save As")) + wxT('\t') + wxT("CTRL+SHIFT+S"), wxEmptyString, wxITEM_NORMAL);
	menu_file->Append(menu_file_save_as);

	wxMenuItem* menu_file_exit;
	menu_file_exit = new wxMenuItem(menu_file, wxID_ANY, wxString(wxT("Exit")), wxEmptyString, wxITEM_NORMAL);
	menu_file->Append(menu_file_exit);

	m_menubar1->Append(menu_file, wxT("FIle"));

	menu_script = new wxMenu();
	wxMenuItem* menu_script_choose_location;
	menu_script_choose_location = new wxMenuItem(menu_script, wxID_ANY, wxString(wxT("Choose Location")), wxEmptyString, wxITEM_NORMAL);
	menu_script->Append(menu_script_choose_location);

	wxMenuItem* menu_script_generate_script;
	menu_script_generate_script = new wxMenuItem(menu_script, wxID_ANY, wxString(wxT("Generate Script")), wxEmptyString, wxITEM_NORMAL);
	menu_script->Append(menu_script_generate_script);

	m_menubar1->Append(menu_script, wxT("Script"));

	menu_shortcuts = new wxMenu();
	wxMenuItem* menu_shortcuts_change_shortcuts;
	menu_shortcuts_change_shortcuts = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Change Shortcuts")), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(menu_shortcuts_change_shortcuts);

	wxMenuItem* shortcut_walk;
	shortcut_walk = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Walk")) + wxT('\t') + wxT("Ctrl+2"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_walk);

	wxMenuItem* shortcut_mine;
	shortcut_mine = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Mine")) + wxT('\t') + wxT("Alt+1"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_mine);

	wxMenuItem* shortcut_game_speed;
	shortcut_game_speed = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Game Speed")) + wxT('\t') + wxT("Ctrl+3"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_game_speed);

	wxMenuItem* shortcut_build;
	shortcut_build = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Build")) + wxT('\t') + wxT("Alt+2"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_build);

	wxMenuItem* shortcut_fuel;
	shortcut_fuel = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Fuel")) + wxT('\t') + wxT("Alt+3"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_fuel);

	wxMenuItem* shortcut_take;
	shortcut_take = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Take")) + wxT('\t') + wxT("Alt+4"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_take);

	wxMenuItem* shortcut_put;
	shortcut_put = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Put")) + wxT('\t') + wxT("Alt+5"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_put);

	wxMenuItem* shortcut_craft;
	shortcut_craft = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Craft")) + wxT('\t') + wxT("Ctrl+1"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_craft);

	wxMenuItem* shortcut_rotate;
	shortcut_rotate = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Rotate")) + wxT('\t') + wxT("Ctrl+4"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_rotate);

	wxMenuItem* shortcut_add_task;
	shortcut_add_task = new wxMenuItem(menu_shortcuts, wxID_ANY, wxString(wxT("Add Task")) + wxT('\t') + wxT("Ctrl+t"), wxEmptyString, wxITEM_NORMAL);
	menu_shortcuts->Append(shortcut_add_task);

	m_menubar1->Append(menu_shortcuts, wxT("Shortcuts"));

	this->SetMenuBar(m_menubar1);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* bSizer84;
	bSizer84 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer841;
	bSizer841 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer(wxHORIZONTAL);

	bSizer23->SetMinSize(wxSize(10, 10));
	label_x_cord = new wxStaticText(m_panel1, wxID_ANY, wxT("X-Cord:"), wxDefaultPosition, wxSize(45, -1), wxALIGN_RIGHT);
	label_x_cord->Wrap(-1);
	bSizer23->Add(label_x_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_x_cord = new wxTextCtrl(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer23->Add(txt_x_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer30->Add(bSizer23, 1, 0, 5);

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer(wxHORIZONTAL);

	label_y_cord = new wxStaticText(m_panel1, wxID_ANY, wxT("Y-Cord:"), wxDefaultPosition, wxSize(45, -1), wxALIGN_RIGHT);
	label_y_cord->Wrap(-1);
	bSizer28->Add(label_y_cord, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	txt_y_cord = new wxTextCtrl(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer28->Add(txt_y_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer30->Add(bSizer28, 1, 0, 5);

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer(wxHORIZONTAL);

	label_units = new wxStaticText(m_panel1, wxID_ANY, wxT("Units:"), wxDefaultPosition, wxSize(45, -1), wxALIGN_RIGHT);
	label_units->Wrap(-1);
	bSizer36->Add(label_units, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_units = new wxTextCtrl(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer36->Add(txt_units, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer30->Add(bSizer36, 1, 0, 5);

	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer(wxVERTICAL);


	bSizer49->Add(0, 0, 1, wxEXPAND, 5);


	bSizer30->Add(bSizer49, 1, 0, 5);


	bSizer37->Add(bSizer30, 1, 0, 5);


	bSizer19->Add(bSizer37, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer(wxHORIZONTAL);

	label_item = new wxStaticText(m_panel1, wxID_ANY, wxT("Item:"), wxDefaultPosition, wxSize(60, -1), wxALIGN_RIGHT);
	label_item->Wrap(-1);
	bSizer35->Add(label_item, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_item = new wxComboBox(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT);
	cmb_item->SetMinSize(wxSize(150, -1));

	bSizer35->Add(cmb_item, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer24->Add(bSizer35, 1, 0, 5);

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer(wxHORIZONTAL);

	label_from_into = new wxStaticText(m_panel1, wxID_ANY, wxT("From/Into:"), wxDefaultPosition, wxSize(60, -1), wxALIGN_RIGHT);
	label_from_into->Wrap(-1);
	bSizer31->Add(label_from_into, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_from_into = new wxComboBox(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT);
	cmb_from_into->SetSelection(0);
	cmb_from_into->SetMinSize(wxSize(150, -1));

	bSizer31->Add(cmb_from_into, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer24->Add(bSizer31, 1, 0, 5);

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer(wxHORIZONTAL);

	label_tech = new wxStaticText(m_panel1, wxID_ANY, wxT("Tech:"), wxDefaultPosition, wxSize(60, -1), wxALIGN_RIGHT);
	label_tech->Wrap(-1);
	bSizer34->Add(label_tech, 0, wxALL, 5);

	cmb_tech = new wxComboBox(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_SORT);
	cmb_tech->SetSelection(0);
	cmb_tech->SetMinSize(wxSize(150, -1));

	bSizer34->Add(cmb_tech, 0, wxALL, 5);


	bSizer24->Add(bSizer34, 1, 0, 5);

	wxBoxSizer* bSizer47;
	bSizer47 = new wxBoxSizer(wxVERTICAL);


	bSizer47->Add(0, 0, 1, wxEXPAND, 5);


	bSizer24->Add(bSizer47, 1, 0, 5);

	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer(wxVERTICAL);


	bSizer24->Add(bSizer48, 1, 0, 5);


	bSizer20->Add(bSizer24, 1, wxEXPAND, 5);


	bSizer19->Add(bSizer20, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer(wxHORIZONTAL);

	label_building_orientation = new wxStaticText(m_panel1, wxID_ANY, wxT("Building Orientation:"), wxDefaultPosition, wxSize(115, -1), wxALIGN_RIGHT);
	label_building_orientation->Wrap(-1);
	bSizer58->Add(label_building_orientation, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_building_orientation = new wxComboBox(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0, NULL, 0);
	bSizer58->Add(cmb_building_orientation, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer57->Add(bSizer58, 1, 0, 5);

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer(wxHORIZONTAL);

	label_direction_to_build = new wxStaticText(m_panel1, wxID_ANY, wxT("Direction:"), wxDefaultPosition, wxSize(115, -1), wxALIGN_RIGHT);
	label_direction_to_build->Wrap(-1);
	bSizer59->Add(label_direction_to_build, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_direction_to_build = new wxComboBox(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0, NULL, 0);
	bSizer59->Add(cmb_direction_to_build, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer57->Add(bSizer59, 1, 0, 5);

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer(wxHORIZONTAL);

	label_building_size = new wxStaticText(m_panel1, wxID_ANY, wxT("Building Size:"), wxDefaultPosition, wxSize(115, -1), wxALIGN_RIGHT);
	label_building_size->Wrap(-1);
	bSizer51->Add(label_building_size, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_building_size = new wxTextCtrl(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0);
	bSizer51->Add(txt_building_size, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer57->Add(bSizer51, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer(wxHORIZONTAL);

	label_amount_of_buildings = new wxStaticText(m_panel1, wxID_ANY, wxT("Amount of Buildings:"), wxDefaultPosition, wxSize(115, -1), wxALIGN_RIGHT);
	label_amount_of_buildings->Wrap(-1);
	bSizer52->Add(label_amount_of_buildings, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_amount_of_buildings = new wxTextCtrl(m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0);
	bSizer52->Add(txt_amount_of_buildings, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer57->Add(bSizer52, 1, wxEXPAND, 5);


	bSizer19->Add(bSizer57, 1, wxEXPAND, 5);


	bSizer19->Add(50, 0, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer(wxVERTICAL);

	rbtn_take = new wxRadioButton(m_panel1, wxID_ANY, wxT("Take"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer42->Add(rbtn_take, 0, wxALL, 5);


	bSizer6->Add(bSizer42, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxVERTICAL);

	rbtn_put = new wxRadioButton(m_panel1, wxID_ANY, wxT("Put"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer11->Add(rbtn_put, 0, wxALL, 5);


	bSizer6->Add(bSizer11, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer(wxVERTICAL);

	rbtn_game_speed = new wxRadioButton(m_panel1, wxID_ANY, wxT("Game Speed"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer17->Add(rbtn_game_speed, 0, wxALL, 5);


	bSizer6->Add(bSizer17, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer(wxVERTICAL);

	rbtn_craft = new wxRadioButton(m_panel1, wxID_ANY, wxT("Craft"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer39->Add(rbtn_craft, 0, wxALL, 5);


	bSizer6->Add(bSizer39, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer(wxVERTICAL);

	rbtn_walk = new wxRadioButton(m_panel1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer15->Add(rbtn_walk, 0, wxALL, 5);


	bSizer6->Add(bSizer15, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxVERTICAL);

	rbtn_mine = new wxRadioButton(m_panel1, wxID_ANY, wxT("Mine"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer12->Add(rbtn_mine, 0, wxALL, 5);


	bSizer6->Add(bSizer12, 1, wxEXPAND, 5);


	bSizer18->Add(bSizer6, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer(wxVERTICAL);

	rbtn_build = new wxRadioButton(m_panel1, wxID_ANY, wxT("Build"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer16->Add(rbtn_build, 0, wxALL, 5);


	bSizer7->Add(bSizer16, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer(wxVERTICAL);

	rbtn_recipe = new wxRadioButton(m_panel1, wxID_ANY, wxT("Recipe"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer64->Add(rbtn_recipe, 0, wxALL, 5);


	bSizer7->Add(bSizer64, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer(wxVERTICAL);

	rbtn_tech = new wxRadioButton(m_panel1, wxID_ANY, wxT("Tech"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer63->Add(rbtn_tech, 0, wxALL, 5);


	bSizer7->Add(bSizer63, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer(wxVERTICAL);

	rbtn_limit = new wxRadioButton(m_panel1, wxID_ANY, wxT("Limit"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer40->Add(rbtn_limit, 0, wxALL, 5);


	bSizer7->Add(bSizer40, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer431;
	bSizer431 = new wxBoxSizer(wxVERTICAL);

	rbtn_transfer = new wxRadioButton(m_panel1, wxID_ANY, wxT("Transfer"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer431->Add(rbtn_transfer, 0, wxALL, 5);


	bSizer7->Add(bSizer431, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer(wxVERTICAL);

	rbtn_filter = new wxRadioButton(m_panel1, wxID_ANY, wxT("Filter"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer65->Add(rbtn_filter, 0, wxALL, 5);


	bSizer7->Add(bSizer65, 1, wxEXPAND, 5);


	bSizer18->Add(bSizer7, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	rbtn_fuel = new wxRadioButton(m_panel1, wxID_ANY, wxT("Fuel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(rbtn_fuel, 0, wxALL, 5);


	bSizer5->Add(bSizer8, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);

	rbtn_priority = new wxRadioButton(m_panel1, wxID_ANY, wxT("Priority"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer9->Add(rbtn_priority, 0, wxALL, 5);


	bSizer5->Add(bSizer9, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	rbtn_rotate = new wxRadioButton(m_panel1, wxID_ANY, wxT("Rotate"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer13->Add(rbtn_rotate, 0, wxALL, 5);


	bSizer5->Add(bSizer13, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer(wxVERTICAL);

	rbtn_pick_up = new wxRadioButton(m_panel1, wxID_ANY, wxT("Pick Up"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer41->Add(rbtn_pick_up, 0, wxALL, 5);


	bSizer5->Add(bSizer41, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer441;
	bSizer441 = new wxBoxSizer(wxVERTICAL);

	rbtn_drop = new wxRadioButton(m_panel1, wxID_ANY, wxT("Drop"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer441->Add(rbtn_drop, 0, wxALL, 5);


	bSizer5->Add(bSizer441, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer(wxVERTICAL);

	rbtn_launch = new wxRadioButton(m_panel1, wxID_ANY, wxT("Launch"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer14->Add(rbtn_launch, 0, wxALL, 5);


	bSizer5->Add(bSizer14, 1, wxEXPAND, 5);


	bSizer18->Add(bSizer5, 1, wxEXPAND, 5);

	m_staticline2 = new wxStaticLine(m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer18->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer(wxHORIZONTAL);

	btn_add_task = new wxButton(m_panel1, wxID_ANY, wxT("Add Task"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer56->Add(btn_add_task, 0, wxALIGN_CENTER | wxALL, 5);

	btn_delete_task = new wxButton(m_panel1, wxID_ANY, wxT("Delete Task"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer56->Add(btn_delete_task, 0, wxALL, 5);


	bSizer18->Add(bSizer56, 1, wxALIGN_CENTER, 5);


	bSizer19->Add(bSizer18, 1, wxEXPAND, 5);


	bSizer19->Add(10000, 0, 1, wxEXPAND, 5);


	bSizer841->Add(bSizer19, 1, 0, 5);


	bSizer84->Add(bSizer841, 1, wxEXPAND, 5);


	m_panel1->SetSizer(bSizer84);
	m_panel1->Layout();
	bSizer84->Fit(m_panel1);
	bSizer1->Add(m_panel1, 1, wxEXPAND | wxALL, 5);

	m_staticline14 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer1->Add(m_staticline14, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer45;
	bSizer45 = new wxBoxSizer(wxVERTICAL);

	bSizer45->SetMinSize(wxSize(400, -1));
	wxBoxSizer* bSizer76;
	bSizer76 = new wxBoxSizer(wxVERTICAL);

	bSizer76->SetMinSize(wxSize(400, -1));
	label_buildings = new wxStaticText(this, wxID_ANY, wxT("Buildings"), wxDefaultPosition, wxDefaultSize, 0);
	label_buildings->Wrap(-1);
	bSizer76->Add(label_buildings, 0, wxALIGN_CENTER, 5);

	grid_buildings = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	grid_buildings->CreateGrid(0, 7);
	grid_buildings->EnableEditing(true);
	grid_buildings->EnableGridLines(true);
	grid_buildings->EnableDragGridSize(false);
	grid_buildings->SetMargins(0, 0);

	// Columns
	grid_buildings->SetColSize(0, 50);
	grid_buildings->SetColSize(1, 50);
	grid_buildings->SetColSize(2, 120);
	grid_buildings->SetColSize(3, 70);
	grid_buildings->SetColSize(4, 120);
	grid_buildings->SetColSize(5, 120);
	grid_buildings->SetColSize(6, 120);
	grid_buildings->EnableDragColMove(false);
	grid_buildings->EnableDragColSize(true);
	grid_buildings->SetColLabelValue(0, wxT("X-cord"));
	grid_buildings->SetColLabelValue(1, wxT("Y-cord"));
	grid_buildings->SetColLabelValue(2, wxT("Building"));
	grid_buildings->SetColLabelValue(3, wxT("Orientation"));
	grid_buildings->SetColLabelValue(4, wxT("Recipe"));
	grid_buildings->SetColLabelValue(5, wxT("Priority"));
	grid_buildings->SetColLabelValue(6, wxT("Filter"));
	grid_buildings->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	grid_buildings->EnableDragRowSize(true);
	grid_buildings->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	grid_buildings->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	grid_buildings->SetMinSize(wxSize(-1, 2500));

	bSizer76->Add(grid_buildings, 0, wxALL, 5);


	bSizer45->Add(bSizer76, 1, wxEXPAND, 5);


	bSizer43->Add(bSizer45, 1, wxEXPAND, 5);


	bSizer43->Add(50, 0, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer(wxVERTICAL);

	bSizer44->SetMinSize(wxSize(500, -1));
	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer(wxVERTICAL);

	label_tasks = new wxStaticText(this, wxID_ANY, wxT("Tasks"), wxDefaultPosition, wxSize(-1, -1), 0);
	label_tasks->Wrap(-1);
	bSizer50->Add(label_tasks, 0, wxALIGN_CENTER, 5);

	grid_tasks = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	grid_tasks->CreateGrid(0, 9);
	grid_tasks->EnableEditing(false);
	grid_tasks->EnableGridLines(true);
	grid_tasks->EnableDragGridSize(false);
	grid_tasks->SetMargins(0, 0);

	// Columns
	grid_tasks->SetColSize(0, 75);
	grid_tasks->SetColSize(1, 50);
	grid_tasks->SetColSize(2, 50);
	grid_tasks->SetColSize(3, 50);
	grid_tasks->SetColSize(4, 120);
	grid_tasks->SetColSize(5, 70);
	grid_tasks->SetColSize(6, 70);
	grid_tasks->SetColSize(7, 50);
	grid_tasks->SetColSize(8, 50);
	grid_tasks->EnableDragColMove(false);
	grid_tasks->EnableDragColSize(true);
	grid_tasks->SetColLabelValue(0, wxT("Task"));
	grid_tasks->SetColLabelValue(1, wxT("X-cord"));
	grid_tasks->SetColLabelValue(2, wxT("Y-cord"));
	grid_tasks->SetColLabelValue(3, wxT("Units"));
	grid_tasks->SetColLabelValue(4, wxT("Item"));
	grid_tasks->SetColLabelValue(5, wxT("Orientation"));
	grid_tasks->SetColLabelValue(6, wxT("Direction"));
	grid_tasks->SetColLabelValue(7, wxT("Size"));
	grid_tasks->SetColLabelValue(8, wxT("Amount"));
	grid_tasks->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Rows
	grid_tasks->EnableDragRowSize(true);
	grid_tasks->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

	// Label Appearance

	// Cell Defaults
	grid_tasks->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	grid_tasks->SetMinSize(wxSize(-1, 2500));

	bSizer50->Add(grid_tasks, 0, wxALL, 5);


	bSizer44->Add(bSizer50, 1, wxEXPAND, 5);


	bSizer43->Add(bSizer44, 1, wxEXPAND, 5);


	bSizer43->Add(10000, 0, 1, wxEXPAND, 5);


	bSizer1->Add(bSizer43, 1, wxEXPAND, 5);


	bSizer1->Add(0, 10000, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(GUI_Base::OnFameKeyDown));
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnMenuNew), this, menu_file_new->GetId());
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnMenuOpen), this, menu_file_open->GetId());
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnMenuSave), this, menu_file_save->GetId());
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnMenuSaveAs), this, menu_file_save_as->GetId());
	menu_file->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnMenuExit), this, menu_file_exit->GetId());
	menu_script->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnChooseLocation), this, menu_script_choose_location->GetId());
	menu_script->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnGenerateScript), this, menu_script_generate_script->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnChangeShortcuts), this, menu_shortcuts_change_shortcuts->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnWalkMenuSelected), this, shortcut_walk->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnMineMenuSelected), this, shortcut_mine->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnGameSpeedMenuSelected), this, shortcut_game_speed->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnBuildMenuSelected), this, shortcut_build->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnFuelMenuSelected), this, shortcut_fuel->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnTakeMenuSelected), this, shortcut_take->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnPutMenuSelected), this, shortcut_put->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnCraftMenuSelected), this, shortcut_craft->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnRotateMenuSelected), this, shortcut_rotate->GetId());
	menu_shortcuts->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUI_Base::OnAddMenuSelected), this, shortcut_add_task->GetId());
	cmb_building_orientation->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(GUI_Base::OnBuildingOrientationSelected), NULL, this);
	cmb_direction_to_build->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(GUI_Base::OnDirectionToBuildSelected), NULL, this);
	rbtn_take->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnTakeChosen), NULL, this);
	rbtn_put->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnPutChosen), NULL, this);
	rbtn_game_speed->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnGameSpeedChosen), NULL, this);
	rbtn_craft->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnCraftChosen), NULL, this);
	rbtn_walk->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(GUI_Base::OnWalkKeyDown), NULL, this);
	rbtn_walk->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnWalkChosen), NULL, this);
	rbtn_mine->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnMineChosen), NULL, this);
	rbtn_build->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnBuildChosen), NULL, this);
	rbtn_recipe->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnRecipeChosen), NULL, this);
	rbtn_tech->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnTechChosen), NULL, this);
	rbtn_limit->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnLimitChosen), NULL, this);
	rbtn_transfer->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnTransferChosen), NULL, this);
	rbtn_filter->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnfilterChosen), NULL, this);
	rbtn_fuel->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnFuelChosen), NULL, this);
	rbtn_priority->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnPriorityChosen), NULL, this);
	rbtn_rotate->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnRotateChosen), NULL, this);
	rbtn_pick_up->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnPickUpChosen), NULL, this);
	rbtn_drop->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnDropChosen), NULL, this);
	rbtn_launch->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnLaunchChosen), NULL, this);
	btn_add_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_Base::OnAddTaskClicked), NULL, this);
	btn_delete_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_Base::OnDeleteTaskClicked), NULL, this);
	grid_buildings->Connect(wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(GUI_Base::OnBuildingsGridLeftClick), NULL, this);
	grid_buildings->Connect(wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler(GUI_Base::OnBuildingsGridLeftDoubleClick), NULL, this);
	grid_tasks->Connect(wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(GUI_Base::OnTasksGridLeftClick), NULL, this);
	grid_tasks->Connect(wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler(GUI_Base::OnTasksGridDoubleLeftClick), NULL, this);
}

GUI_Base::~GUI_Base() {
	// Disconnect Events
	this->Disconnect(wxEVT_KEY_DOWN, wxKeyEventHandler(GUI_Base::OnFameKeyDown));
	cmb_building_orientation->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(GUI_Base::OnBuildingOrientationSelected), NULL, this);
	cmb_direction_to_build->Disconnect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(GUI_Base::OnDirectionToBuildSelected), NULL, this);
	rbtn_take->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnTakeChosen), NULL, this);
	rbtn_put->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnPutChosen), NULL, this);
	rbtn_game_speed->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnGameSpeedChosen), NULL, this);
	rbtn_craft->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnCraftChosen), NULL, this);
	rbtn_walk->Disconnect(wxEVT_KEY_DOWN, wxKeyEventHandler(GUI_Base::OnWalkKeyDown), NULL, this);
	rbtn_walk->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnWalkChosen), NULL, this);
	rbtn_mine->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnMineChosen), NULL, this);
	rbtn_build->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnBuildChosen), NULL, this);
	rbtn_recipe->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnRecipeChosen), NULL, this);
	rbtn_tech->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnTechChosen), NULL, this);
	rbtn_limit->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnLimitChosen), NULL, this);
	rbtn_transfer->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnTransferChosen), NULL, this);
	rbtn_filter->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnfilterChosen), NULL, this);
	rbtn_fuel->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnFuelChosen), NULL, this);
	rbtn_priority->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnPriorityChosen), NULL, this);
	rbtn_rotate->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnRotateChosen), NULL, this);
	rbtn_pick_up->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnPickUpChosen), NULL, this);
	rbtn_drop->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnDropChosen), NULL, this);
	rbtn_launch->Disconnect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(GUI_Base::OnLaunchChosen), NULL, this);
	btn_add_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_Base::OnAddTaskClicked), NULL, this);
	btn_delete_task->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI_Base::OnDeleteTaskClicked), NULL, this);
	grid_buildings->Disconnect(wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(GUI_Base::OnBuildingsGridLeftClick), NULL, this);
	grid_buildings->Disconnect(wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler(GUI_Base::OnBuildingsGridLeftDoubleClick), NULL, this);
	grid_tasks->Disconnect(wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(GUI_Base::OnTasksGridLeftClick), NULL, this);
	grid_tasks->Disconnect(wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler(GUI_Base::OnTasksGridDoubleLeftClick), NULL, this);

}

Shortcuts_Menu::Shortcuts_Menu(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style) {
	this->SetSizeHints(wxSize(570, 370), wxDefaultSize);

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer98;
	bSizer98 = new wxBoxSizer(wxHORIZONTAL);

	m_scrolledWindow3 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_scrolledWindow3->SetScrollRate(5, 5);
	wxBoxSizer* bSizer519;
	bSizer519 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer5181;
	bSizer5181 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk = new wxStaticText(m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk->Wrap(-1);
	bSizer5181->Add(label_shortcut_walk, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl681 = new wxTextCtrl(m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer5181->Add(m_textCtrl681, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer519->Add(bSizer5181, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer51811;
	bSizer51811 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk1 = new wxStaticText(m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk1->Wrap(-1);
	bSizer51811->Add(label_shortcut_walk1, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl6811 = new wxTextCtrl(m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer51811->Add(m_textCtrl6811, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer519->Add(bSizer51811, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer51812;
	bSizer51812 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk2 = new wxStaticText(m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk2->Wrap(-1);
	bSizer51812->Add(label_shortcut_walk2, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl6812 = new wxTextCtrl(m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer51812->Add(m_textCtrl6812, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer519->Add(bSizer51812, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer51813;
	bSizer51813 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk3 = new wxStaticText(m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk3->Wrap(-1);
	bSizer51813->Add(label_shortcut_walk3, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl6813 = new wxTextCtrl(m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer51813->Add(m_textCtrl6813, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer519->Add(bSizer51813, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer51814;
	bSizer51814 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk4 = new wxStaticText(m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk4->Wrap(-1);
	bSizer51814->Add(label_shortcut_walk4, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl6814 = new wxTextCtrl(m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer51814->Add(m_textCtrl6814, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer519->Add(bSizer51814, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer51815;
	bSizer51815 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk5 = new wxStaticText(m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk5->Wrap(-1);
	bSizer51815->Add(label_shortcut_walk5, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl6815 = new wxTextCtrl(m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer51815->Add(m_textCtrl6815, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer519->Add(bSizer51815, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer51816;
	bSizer51816 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk6 = new wxStaticText(m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk6->Wrap(-1);
	bSizer51816->Add(label_shortcut_walk6, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl6816 = new wxTextCtrl(m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer51816->Add(m_textCtrl6816, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer519->Add(bSizer51816, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer51817;
	bSizer51817 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk7 = new wxStaticText(m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk7->Wrap(-1);
	bSizer51817->Add(label_shortcut_walk7, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl6817 = new wxTextCtrl(m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer51817->Add(m_textCtrl6817, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer519->Add(bSizer51817, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer51818;
	bSizer51818 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk8 = new wxStaticText(m_scrolledWindow3, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk8->Wrap(-1);
	bSizer51818->Add(label_shortcut_walk8, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl6818 = new wxTextCtrl(m_scrolledWindow3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer51818->Add(m_textCtrl6818, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer519->Add(bSizer51818, 1, wxEXPAND, 5);


	m_scrolledWindow3->SetSizer(bSizer519);
	m_scrolledWindow3->Layout();
	bSizer519->Fit(m_scrolledWindow3);
	bSizer98->Add(m_scrolledWindow3, 1, wxEXPAND | wxALL, 5);

	m_scrolledWindow1 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_scrolledWindow1->SetScrollRate(5, 5);
	m_scrolledWindow1->SetMinSize(wxSize(-1, 50));

	wxBoxSizer* bSizer5191;
	bSizer5191 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer51819;
	bSizer51819 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk9 = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk9->Wrap(-1);
	bSizer51819->Add(label_shortcut_walk9, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl6819 = new wxTextCtrl(m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer51819->Add(m_textCtrl6819, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer5191->Add(bSizer51819, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer518111;
	bSizer518111 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk11 = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk11->Wrap(-1);
	bSizer518111->Add(label_shortcut_walk11, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl68111 = new wxTextCtrl(m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer518111->Add(m_textCtrl68111, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer5191->Add(bSizer518111, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer518121;
	bSizer518121 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk21 = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk21->Wrap(-1);
	bSizer518121->Add(label_shortcut_walk21, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl68121 = new wxTextCtrl(m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer518121->Add(m_textCtrl68121, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer5191->Add(bSizer518121, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer518131;
	bSizer518131 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk31 = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk31->Wrap(-1);
	bSizer518131->Add(label_shortcut_walk31, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl68131 = new wxTextCtrl(m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer518131->Add(m_textCtrl68131, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer5191->Add(bSizer518131, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer518141;
	bSizer518141 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk41 = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk41->Wrap(-1);
	bSizer518141->Add(label_shortcut_walk41, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl68141 = new wxTextCtrl(m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer518141->Add(m_textCtrl68141, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer5191->Add(bSizer518141, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer518151;
	bSizer518151 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk51 = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk51->Wrap(-1);
	bSizer518151->Add(label_shortcut_walk51, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl68151 = new wxTextCtrl(m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer518151->Add(m_textCtrl68151, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer5191->Add(bSizer518151, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer518161;
	bSizer518161 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk61 = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk61->Wrap(-1);
	bSizer518161->Add(label_shortcut_walk61, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl68161 = new wxTextCtrl(m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer518161->Add(m_textCtrl68161, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer5191->Add(bSizer518161, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer518171;
	bSizer518171 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk71 = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk71->Wrap(-1);
	bSizer518171->Add(label_shortcut_walk71, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl68171 = new wxTextCtrl(m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer518171->Add(m_textCtrl68171, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer5191->Add(bSizer518171, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer518181;
	bSizer518181 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk81 = new wxStaticText(m_scrolledWindow1, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk81->Wrap(-1);
	bSizer518181->Add(label_shortcut_walk81, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl68181 = new wxTextCtrl(m_scrolledWindow1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer518181->Add(m_textCtrl68181, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer5191->Add(bSizer518181, 1, wxEXPAND, 5);


	m_scrolledWindow1->SetSizer(bSizer5191);
	m_scrolledWindow1->Layout();
	bSizer5191->Fit(m_scrolledWindow1);
	bSizer98->Add(m_scrolledWindow1, 1, wxEXPAND | wxALL, 5);

	m_scrolledWindow11 = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_scrolledWindow11->SetScrollRate(5, 5);
	m_scrolledWindow11->SetMinSize(wxSize(-1, 50));

	wxBoxSizer* bSizer51911;
	bSizer51911 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer518191;
	bSizer518191 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk91 = new wxStaticText(m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk91->Wrap(-1);
	bSizer518191->Add(label_shortcut_walk91, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl68191 = new wxTextCtrl(m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer518191->Add(m_textCtrl68191, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer51911->Add(bSizer518191, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5181111;
	bSizer5181111 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk111 = new wxStaticText(m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk111->Wrap(-1);
	bSizer5181111->Add(label_shortcut_walk111, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl681111 = new wxTextCtrl(m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer5181111->Add(m_textCtrl681111, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer51911->Add(bSizer5181111, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5181211;
	bSizer5181211 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk211 = new wxStaticText(m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk211->Wrap(-1);
	bSizer5181211->Add(label_shortcut_walk211, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl681211 = new wxTextCtrl(m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer5181211->Add(m_textCtrl681211, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer51911->Add(bSizer5181211, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5181311;
	bSizer5181311 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk311 = new wxStaticText(m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk311->Wrap(-1);
	bSizer5181311->Add(label_shortcut_walk311, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl681311 = new wxTextCtrl(m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer5181311->Add(m_textCtrl681311, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer51911->Add(bSizer5181311, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5181411;
	bSizer5181411 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk411 = new wxStaticText(m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk411->Wrap(-1);
	bSizer5181411->Add(label_shortcut_walk411, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl681411 = new wxTextCtrl(m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer5181411->Add(m_textCtrl681411, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer51911->Add(bSizer5181411, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5181511;
	bSizer5181511 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk511 = new wxStaticText(m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk511->Wrap(-1);
	bSizer5181511->Add(label_shortcut_walk511, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl681511 = new wxTextCtrl(m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer5181511->Add(m_textCtrl681511, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer51911->Add(bSizer5181511, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5181611;
	bSizer5181611 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk611 = new wxStaticText(m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk611->Wrap(-1);
	bSizer5181611->Add(label_shortcut_walk611, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl681611 = new wxTextCtrl(m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer5181611->Add(m_textCtrl681611, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer51911->Add(bSizer5181611, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5181711;
	bSizer5181711 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk711 = new wxStaticText(m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk711->Wrap(-1);
	bSizer5181711->Add(label_shortcut_walk711, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl681711 = new wxTextCtrl(m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer5181711->Add(m_textCtrl681711, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer51911->Add(bSizer5181711, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5181811;
	bSizer5181811 = new wxBoxSizer(wxHORIZONTAL);

	label_shortcut_walk811 = new wxStaticText(m_scrolledWindow11, wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	label_shortcut_walk811->Wrap(-1);
	bSizer5181811->Add(label_shortcut_walk811, 0, wxALIGN_CENTER | wxALL, 5);

	m_textCtrl681811 = new wxTextCtrl(m_scrolledWindow11, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer5181811->Add(m_textCtrl681811, 0, wxALIGN_CENTER | wxALL, 5);


	bSizer51911->Add(bSizer5181811, 1, wxEXPAND, 5);


	m_scrolledWindow11->SetSizer(bSizer51911);
	m_scrolledWindow11->Layout();
	bSizer51911->Fit(m_scrolledWindow11);
	bSizer98->Add(m_scrolledWindow11, 1, wxEXPAND | wxALL, 5);


	bSizer50->Add(bSizer98, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer76;
	bSizer76 = new wxBoxSizer(wxHORIZONTAL);

	bSizer76->SetMinSize(wxSize(-1, 50));
	m_button3 = new wxButton(this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer76->Add(m_button3, 0, wxALL, 5);

	m_button4 = new wxButton(this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer76->Add(m_button4, 0, wxALL, 5);


	bSizer50->Add(bSizer76, 1, wxALIGN_CENTER, 5);


	this->SetSizer(bSizer50);
	this->Layout();

	this->Centre(wxBOTH);
}

Shortcuts_Menu::~Shortcuts_Menu() {
}
