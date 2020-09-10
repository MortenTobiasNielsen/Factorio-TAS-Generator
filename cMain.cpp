#include "cMain.h"
#include "utils.h"
#include "Functions.h"
#include <fstream>
#include <sstream>
#include <iomanip>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(10001, cMain::OnMenuNew)
EVT_MENU(10002, cMain::OnMenuOpen)
EVT_MENU(10003, cMain::OnMenuSave)
EVT_MENU(10004, cMain::OnMenuExit)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Factorio GUI", wxPoint(30, 30), wxSize(1920, 1080)) {

	all_items.resize(item_logistics.size() + item_production.size() + item_intermediates.size() + item_combat.size());
	all_items.insert(all_items.end(), item_logistics.begin(), item_logistics.end());
	all_items.insert(all_items.end(), item_production.begin(), item_production.end());
	all_items.insert(all_items.end(), item_intermediates.begin(), item_intermediates.end());
	all_items.insert(all_items.end(), item_combat.begin(), item_combat.end());

	static const std::vector<std::string> all_items_const(all_items);

	list_task_num = 0;
	list_buildings_num = 0;
	file_location = "C:\\Users\\MTNie\\AppData\\Roaming\\Factorio\\mods\\Speed_run_0.0.1\\tasksV2.lua"; // this needs to be set by the user - most likely in open or save - a save as might also be needed

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

	wxBoxSizer* bSizer84;
	bSizer84 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer(wxHORIZONTAL);

	bSizer23->SetMinSize(wxSize(10, 10));
	label_x_cord = new wxStaticText(this, wxID_ANY, wxT("X-Cord:"), wxDefaultPosition, wxSize(45, -1), wxALIGN_RIGHT);
	label_x_cord->Wrap(-1);
	bSizer23->Add(label_x_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_x_cord = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer23->Add(txt_x_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer30->Add(bSizer23, 1, 0, 5);

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer(wxHORIZONTAL);

	label_y_cord = new wxStaticText(this, wxID_ANY, wxT("Y-Cord:"), wxDefaultPosition, wxSize(45, -1), wxALIGN_RIGHT);
	label_y_cord->Wrap(-1);
	bSizer28->Add(label_y_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_y_cord = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
	bSizer28->Add(txt_y_cord, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer30->Add(bSizer28, 1, 0, 5);

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer(wxHORIZONTAL);

	label_units = new wxStaticText(this, wxID_ANY, wxT("Units:"), wxDefaultPosition, wxSize(45, -1), wxALIGN_RIGHT);
	label_units->Wrap(-1);
	bSizer36->Add(label_units, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_units = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 0);
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

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer(wxHORIZONTAL);

	label_item_category = new wxStaticText(this, wxID_ANY, wxT("Item Category:"), wxDefaultPosition, wxSize(-1, 25), wxALIGN_RIGHT);
	label_item_category->Wrap(-1);
	label_item_category->SetMinSize(wxSize(80, -1));

	bSizer31->Add(label_item_category, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_item_category = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	cmb_item_category->SetMinSize(wxSize(150, -1));

	bSizer31->Add(cmb_item_category, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer24->Add(bSizer31, 1, 0, 5);

	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer(wxHORIZONTAL);

	label_item = new wxStaticText(this, wxID_ANY, wxT("Item:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	label_item->Wrap(-1);
	label_item->SetMinSize(wxSize(80, -1));

	bSizer35->Add(label_item, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_item = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	cmb_item->SetMinSize(wxSize(150, -1));

	bSizer35->Add(cmb_item, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer24->Add(bSizer35, 1, 0, 5);

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer(wxHORIZONTAL);


	bSizer34->Add(0, 0, 1, wxEXPAND, 5);


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

	label_building_orientation = new wxStaticText(this, wxID_ANY, wxT("Building Orientation:"), wxDefaultPosition, wxSize(115, -1), wxALIGN_RIGHT);
	label_building_orientation->Wrap(-1);
	bSizer58->Add(label_building_orientation, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_building_direction = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0, NULL, 0);
	bSizer58->Add(cmb_building_direction, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer57->Add(bSizer58, 1, 0, 5);

	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer(wxHORIZONTAL);

	label_direction_to_build = new wxStaticText(this, wxID_ANY, wxT("Direction to Build:"), wxDefaultPosition, wxSize(115, -1), wxALIGN_RIGHT);
	label_direction_to_build->Wrap(-1);
	bSizer59->Add(label_direction_to_build, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	cmb_direction_to_build = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0, NULL, 0);
	bSizer59->Add(cmb_direction_to_build, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer57->Add(bSizer59, 1, 0, 5);

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer(wxHORIZONTAL);

	label_building_size = new wxStaticText(this, wxID_ANY, wxT("Building Size:"), wxDefaultPosition, wxSize(115, -1), wxALIGN_RIGHT);
	label_building_size->Wrap(-1);
	bSizer51->Add(label_building_size, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_building_size = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0);
	bSizer51->Add(txt_building_size, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer57->Add(bSizer51, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer(wxHORIZONTAL);

	label_amount_of_buildings = new wxStaticText(this, wxID_ANY, wxT("Amount of Buildings:"), wxDefaultPosition, wxSize(115, -1), wxALIGN_RIGHT);
	label_amount_of_buildings->Wrap(-1);
	bSizer52->Add(label_amount_of_buildings, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	txt_amount_of_buildings = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0);
	bSizer52->Add(txt_amount_of_buildings, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


	bSizer57->Add(bSizer52, 1, wxEXPAND, 5);


	bSizer19->Add(bSizer57, 1, wxEXPAND, 5);


	bSizer19->Add(50, 0, 1, wxEXPAND, 5);

	wxStaticBoxSizer* Tasks;
	Tasks = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Tasks")), wxVERTICAL);

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer(wxVERTICAL);

	rbtn_walk = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Walk"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer15->Add(rbtn_walk, 0, wxALL, 5);


	bSizer6->Add(bSizer15, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxVERTICAL);

	rbtn_mine = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Mine"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer12->Add(rbtn_mine, 0, wxALL, 5);


	bSizer6->Add(bSizer12, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer(wxVERTICAL);

	rbtn_game_speed = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Game Speed"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer17->Add(rbtn_game_speed, 0, wxALL, 5);


	bSizer6->Add(bSizer17, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer(wxVERTICAL);

	rbtn_filter = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Filter"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer65->Add(rbtn_filter, 0, wxALL, 5);


	bSizer6->Add(bSizer65, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer(wxVERTICAL);

	rbtn_launch = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Launch"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer39->Add(rbtn_launch, 0, wxALL, 5);


	bSizer6->Add(bSizer39, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer(wxVERTICAL);

	rbtn_priority = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Priority"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer42->Add(rbtn_priority, 0, wxALL, 5);


	bSizer6->Add(bSizer42, 1, wxEXPAND, 5);


	bSizer18->Add(bSizer6, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer(wxVERTICAL);

	rbtn_craft = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Craft"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer14->Add(rbtn_craft, 0, wxALL, 5);


	bSizer7->Add(bSizer14, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer(wxVERTICAL);

	rbtn_build = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Build"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer16->Add(rbtn_build, 0, wxALL, 5);


	bSizer7->Add(bSizer16, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer64;
	bSizer64 = new wxBoxSizer(wxVERTICAL);

	rbtn_recipe = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Recipe"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer64->Add(rbtn_recipe, 0, wxALL, 5);


	bSizer7->Add(bSizer64, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer63;
	bSizer63 = new wxBoxSizer(wxVERTICAL);

	rbtn_tech = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Tech"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer63->Add(rbtn_tech, 0, wxALL, 5);


	bSizer7->Add(bSizer63, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer(wxVERTICAL);

	rbtn_limit = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Limit"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer40->Add(rbtn_limit, 0, wxALL, 5);


	bSizer7->Add(bSizer40, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer431;
	bSizer431 = new wxBoxSizer(wxVERTICAL);

	rbtn_transfer = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Transfer"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer431->Add(rbtn_transfer, 0, wxALL, 5);


	bSizer7->Add(bSizer431, 1, wxEXPAND, 5);


	bSizer18->Add(bSizer7, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	rbtn_fuel = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Fuel"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer8->Add(rbtn_fuel, 0, wxALL, 5);


	bSizer5->Add(bSizer8, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);

	rbtn_take = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Take"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer9->Add(rbtn_take, 0, wxALL, 5);


	bSizer5->Add(bSizer9, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxVERTICAL);

	rbtn_put = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Put"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer11->Add(rbtn_put, 0, wxALL, 5);


	bSizer5->Add(bSizer11, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	rbtn_rotate = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Rotate"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer13->Add(rbtn_rotate, 0, wxALL, 5);


	bSizer5->Add(bSizer13, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer(wxVERTICAL);

	rbtn_pick_up = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Pick Up"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer41->Add(rbtn_pick_up, 0, wxALL, 5);


	bSizer5->Add(bSizer41, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer441;
	bSizer441 = new wxBoxSizer(wxVERTICAL);

	rbtn_drop = new wxRadioButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Drop"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer441->Add(rbtn_drop, 0, wxALL, 5);


	bSizer5->Add(bSizer441, 1, wxEXPAND, 5);


	bSizer18->Add(bSizer5, 1, wxEXPAND, 5);

	m_staticline2 = new wxStaticLine(Tasks->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer18->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer(wxHORIZONTAL);

	btn_add_task = new wxButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Add Task"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer56->Add(btn_add_task, 0, wxALIGN_CENTER | wxALL, 5);

	btn_delete_task = new wxButton(Tasks->GetStaticBox(), wxID_ANY, wxT("Delete Task"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer56->Add(btn_delete_task, 0, wxALL, 5);


	bSizer18->Add(bSizer56, 1, wxALIGN_CENTER, 5);


	Tasks->Add(bSizer18, 1, wxEXPAND, 5);


	bSizer19->Add(Tasks, 1, 0, 5);


	bSizer19->Add(10000, 0, 1, wxEXPAND, 5);


	bSizer84->Add(bSizer19, 1, 0, 5);


	bSizer1->Add(bSizer84, 1, 0, 5);

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
	bSizer76->Add(label_buildings, 0, wxALIGN_CENTER | wxALL, 5);

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

	m_staticText37 = new wxStaticText(this, wxID_ANY, wxT("Tasks"), wxDefaultPosition, wxSize(-1, -1), 0);
	m_staticText37->Wrap(-1);
	bSizer50->Add(m_staticText37, 0, wxALIGN_CENTER, 5);

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
	cmb_item_category->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(cMain::OnItemCategorySelected), NULL, this);
	cmb_building_direction->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(cMain::OnBuildingDirectionSelected), NULL, this);
	cmb_direction_to_build->Connect(wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(cMain::OnDirectionToBuildSelected), NULL, this);
	rbtn_walk->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnWalkChosen), NULL, this);
	rbtn_mine->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnMineChosen), NULL, this);
	rbtn_game_speed->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnGameSpeedChosen), NULL, this);
	rbtn_filter->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnfilterChosen), NULL, this);
	rbtn_launch->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnLaunchChosen), NULL, this);
	rbtn_priority->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnPriorityChosen), NULL, this);
	rbtn_craft->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnCraftChosen), NULL, this);
	rbtn_build->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnBuildChosen), NULL, this);
	rbtn_recipe->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnRecipeChosen), NULL, this);
	rbtn_tech->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnTechChosen), NULL, this);
	rbtn_limit->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnLimitChosen), NULL, this);
	rbtn_transfer->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnTransferChosen), NULL, this);
	rbtn_fuel->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnFuelChosen), NULL, this);
	rbtn_take->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnTakeChosen), NULL, this);
	rbtn_put->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnPutChosen), NULL, this);
	rbtn_rotate->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnRotateChosen), NULL, this);
	rbtn_pick_up->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnPickUpChosen), NULL, this);
	rbtn_drop->Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(cMain::OnDropChosen), NULL, this);
	btn_add_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnAddTaskClicked), NULL, this);
	btn_delete_task->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnDeleteTaskClicked), NULL, this);
	grid_buildings->Connect(wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(cMain::OnBuildingsGridLeftClick), NULL, this);
	grid_buildings->Connect(wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler(cMain::OnBuildingsGridLeftDoubleClick), NULL, this);
	grid_tasks->Connect(wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(cMain::OnTasksGridLeftClick), NULL, this);
	grid_tasks->Connect(wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler(cMain::OnTasksGridDoubleLeftClick), NULL, this);

	// set walk as default value and disable inputs not used
	rbtn_walk->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.walk, item_categories, item_logistics);

	cmb_building_direction->Clear();
	cmb_direction_to_build->Clear();
	for (auto it = build_directions.begin(); it < build_directions.end(); it++) {
		cmb_building_direction->Append(*it);
		cmb_direction_to_build->Append(*it);

	}
	cmb_building_direction->SetValue(*build_directions.begin());
	cmb_direction_to_build->SetValue(*build_directions.begin());

	// set grid formatting
	grid_tasks->SetColFormatFloat(1, 4, 1);
	grid_tasks->SetColFormatFloat(2, 4, 1);
	grid_tasks->SetColFormatFloat(3, 4, 2);

	grid_buildings->SetColFormatFloat(0, 4, 1);
	grid_buildings->SetColFormatFloat(1, 4, 1);
}



void cMain::OnMineChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.mining, item_categories, item_logistics);
}

void cMain::OnRotateChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.rotate, item_categories, item_logistics);
}

void cMain::OnCraftChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.craft, item_categories, item_logistics);
}

void cMain::OnWalkChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.walk, item_categories, item_logistics);
}

void cMain::OnBuildChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.build, item_categories, item_logistics);
}

void cMain::OnGameSpeedChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.game_speed, item_categories, item_logistics);
}

void cMain::OnFuelChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.fuel, item_categories_fuel, item_fuels);
}

void cMain::OnTakeChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.take, item_categories, item_logistics);
}

void cMain::OnPutChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.put, item_categories, item_logistics);
}

void cMain::OnfilterChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.filter, item_categories, item_logistics);
}

void cMain::OnRecipeChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.recipe, item_categories, item_logistics);
}

void cMain::OnTechChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.tech, item_categories, item_logistics); // remember to change to tech categories and tech
}

void cMain::OnLaunchChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.launch, item_categories, item_logistics);
}

void cMain::OnPriorityChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.priority, item_categories, item_logistics);
}

void cMain::OnLimitChosen(wxCommandEvent& event) {
	setup_paramters_comboboxes(parameter_choices.limit, item_categories, item_logistics);
}

void cMain::OnTransferChosen(wxCommandEvent& event) {

}

void cMain::OnPickUpChosen(wxCommandEvent& event) {
}

void cMain::OnDropChosen(wxCommandEvent& event) {
}

void cMain::update_tasks_grid(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string orientation, std::string direction_to_build, std::string amount_to_build, std::string building_size) {

	if (grid_tasks->IsSelection()) {
		row_num = *grid_tasks->GetSelectedRows().begin();
	} else {
		row_num = grid_tasks->GetNumberRows();
	}

	grid_tasks->InsertRows(row_num, 1);

	grid_tasks->SetCellValue(row_num, 0, task);
	grid_tasks->SetCellValue(row_num, 1, x_cord);
	grid_tasks->SetCellValue(row_num, 2, y_cord);
	grid_tasks->SetCellValue(row_num, 3, units);
	grid_tasks->SetCellValue(row_num, 4, item);
	grid_tasks->SetCellValue(row_num, 5, orientation);
	grid_tasks->SetCellValue(row_num, 6, direction_to_build);
	grid_tasks->SetCellValue(row_num, 7, building_size);
	grid_tasks->SetCellValue(row_num, 8, amount_to_build);

	
}

void cMain::update_buildings_grid_new_building(std::string x_cord, std::string y_cord, std::string item, std::string orientation) {
	row_num = grid_buildings->GetNumberRows();
	
	grid_buildings->InsertRows(row_num, 1);

	grid_buildings->SetCellValue(row_num, 0, x_cord);
	grid_buildings->SetCellValue(row_num, 1, y_cord);
	grid_buildings->SetCellValue(row_num, 2, item);
	grid_buildings->SetCellValue(row_num, 3, orientation);
}

void cMain::OnAddTaskClicked(wxCommandEvent& event) {
	if (rbtn_game_speed->GetValue()) {
		units = std::to_string(wxAtoi(txt_units->GetValue()));
		if (std::stof(units) < 0.01) {
			units = "0.01";
		}

		update_tasks_grid("Game Speed", not_relevant, not_relevant, not_relevant, units, not_relevant, not_relevant, not_relevant, not_relevant);

		speed(units);

	} else if (rbtn_walk->GetValue()) {
		
		x_cord = std::to_string(wxAtof(txt_x_cord->GetValue()));
		y_cord = std::to_string(wxAtof(txt_y_cord->GetValue()));

		update_tasks_grid("Walk", x_cord, y_cord, not_relevant, not_relevant, not_relevant, not_relevant, not_relevant, not_relevant);

		walk(x_cord, y_cord);

	} else if (rbtn_craft->GetValue()) {
		units = std::to_string(wxAtoi(txt_units->GetValue()));
		item = cmb_item->GetValue().ToStdString();

		if (!check_item(item, all_items)) {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
			return;
		}

		update_tasks_grid("Craft", not_relevant, not_relevant, item, units, not_relevant, not_relevant, not_relevant, not_relevant);
		craft(units, convert_string(item));

	} else if (rbtn_fuel->GetValue()) {
		x_cord = std::to_string(wxAtof(txt_x_cord->GetValue()));
		y_cord = std::to_string(wxAtof(txt_y_cord->GetValue()));

		amount_of_buildings = std::to_string(wxAtoi(txt_amount_of_buildings->GetValue()));
		if (std::stoi(amount_of_buildings) < 1) {
			amount_of_buildings = "1";
		}

		building_size = std::to_string(wxAtoi(txt_building_size->GetValue()));
		if (std::stoi(building_size) < 1) {
			building_size = "1";
		}

		units = std::to_string(wxAtoi(txt_units->GetValue()));
		if (std::stoi(units) < 1) {
			units = "1";
		}
		
		item = cmb_item->GetValue().ToStdString();

		if (!check_item(item, item_fuels)) {
			wxMessageBox("The item is not a valid fuel - please try again", "Please use the item dropdown menu");
			return;
		}

		if (!check_item(direction_to_build, build_directions)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return;
		}

		update_tasks_grid("Fuel", x_cord, y_cord, convert_string(item), units, not_relevant, direction_to_build, amount_of_buildings, building_size);
		row_fill_fuel(x_cord, y_cord, units, item, direction_to_build, amount_of_buildings, building_size);
	
	} else if (rbtn_build->GetValue()) {
		x_cord = std::to_string(wxAtof(txt_x_cord->GetValue()));
		y_cord = std::to_string(wxAtof(txt_y_cord->GetValue()));

		amount_of_buildings = std::to_string(wxAtoi(txt_amount_of_buildings->GetValue()));
		if (std::stoi(amount_of_buildings) < 1) {
			amount_of_buildings = "1";
		}

		building_size = std::to_string(wxAtoi(txt_building_size->GetValue()));
		if (std::stoi(building_size) < 1) {
			building_size = "1";
		}

		item = cmb_item->GetValue().ToStdString();
		build_direction = cmb_building_direction->GetValue().ToStdString();
		direction_to_build = cmb_direction_to_build->GetValue().ToStdString();

		if (!check_item(item, all_items)) {
			wxMessageBox("The item is not valid - please try again", "Please use the item dropdown menu");
			return;
		}

		if (!check_item(build_direction, build_directions)) {
			wxMessageBox("The build direction is not valid - please try again", "Please use the build direction dropdown menu");
			return;
		}

		if (!check_item(direction_to_build, build_directions)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return;
		}
		
		build_row_of_buildings(x_cord, y_cord, convert_string(item), build_direction, direction_to_build, amount_of_buildings, building_size);

		update_tasks_grid("Build", x_cord, y_cord, item, not_relevant, build_direction, direction_to_build, amount_of_buildings, building_size);

		static float start_x_cord = std::stof(x_cord);
		static float start_y_cord = std::stof(y_cord);
		static int building_size_int = std::stoi(building_size);
		static int number_of_buildings_int = std::stoi(amount_of_buildings);

		start_x_cord = std::stof(x_cord);
		start_y_cord = std::stof(y_cord);
		building_size_int = std::stoi(building_size);
		number_of_buildings_int = std::stoi(amount_of_buildings);

		if (direction_to_build == "North") {
			for (int i = 0; i < number_of_buildings_int; i++) {
				update_buildings_grid_new_building(x_cord, std::to_string(start_y_cord - i * building_size_int), item, build_direction);
			}
		} else if (direction_to_build == "South") {
			for (int i = 0; i < number_of_buildings_int; i++) {
				update_buildings_grid_new_building(x_cord, std::to_string(start_y_cord + i * building_size_int), item, build_direction);
			}
		} else if (direction_to_build == "East") {

			for (int i = 0; i < number_of_buildings_int; i++) {
				update_buildings_grid_new_building(std::to_string(start_x_cord + i * building_size_int), y_cord, item, build_direction);
			}
		} else if (direction_to_build == "West") {

			for (int i = 0; i < number_of_buildings_int; i++) {
				update_buildings_grid_new_building(std::to_string(start_x_cord - i * building_size_int), y_cord, item, build_direction);
			}
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

void cMain::OnTasksGridLeftClick(wxGridEvent& event) {
	tasks_row_selected = event.GetRow();
	
	event.Skip();
}

void cMain::OnTasksGridDoubleLeftClick(wxGridEvent& event) {
	tasks_row_selected = event.GetRow();

	static std::string tasks_task = grid_tasks->GetCellValue(tasks_row_selected, 0).ToStdString();
	static std::string tasks_x_cord = grid_tasks->GetCellValue(tasks_row_selected, 1).ToStdString();
	static std::string tasks_y_cord = grid_tasks->GetCellValue(tasks_row_selected, 2).ToStdString();
	static std::string tasks_item = grid_tasks->GetCellValue(tasks_row_selected, 3).ToStdString();
	static std::string tasks_amount = grid_tasks->GetCellValue(tasks_row_selected, 4).ToStdString();
	static std::string tasks_building_direction = grid_tasks->GetCellValue(tasks_row_selected, 5).ToStdString();
	static std::string tasks_direction_to_build = grid_tasks->GetCellValue(tasks_row_selected, 6).ToStdString();

	if (tasks_task == "Game Speed") {
		rbtn_game_speed->SetValue(true);
		
		setup_paramters_comboboxes(parameter_choices.game_speed, item_categories, item_logistics);
		txt_units->SetValue(tasks_amount);
	}

	
	
	event.Skip();
}

void cMain::OnBuildingsGridLeftClick(wxGridEvent& event) {
}

void cMain::OnBuildingsGridLeftDoubleClick(wxGridEvent& event) {
}

void cMain::OnBuildingDirectionSelected(wxCommandEvent& event) {
	// It seems that this is not needed
}

void cMain::OnDirectionToBuildSelected(wxCommandEvent& event) {
	// It seems that this is not needed
}

void cMain::OnDeleteTaskClicked(wxCommandEvent& event) {
}

void cMain::OnMenuNew(wxCommandEvent& evt) {

}

void cMain::OnMenuOpen(wxCommandEvent& evt) {

}

void cMain::OnMenuSave(wxCommandEvent& evt) {
	std::ofstream myfile;
	myfile.open(file_location);

	myfile << end_tasks();;

	myfile.close();
}

void cMain::OnMenuExit(wxCommandEvent& evt) {
	Close();
	evt.Skip();
}

void cMain::setup_paramters(std::vector<bool> parameters) {
	txt_x_cord->Enable(parameters[1]);
	txt_y_cord->Enable(parameters[2]);
	txt_units->Enable(parameters[3]);
	cmb_item_category->Enable(parameters[4]);
	cmb_item->Enable(parameters[5]);
	cmb_building_direction->Enable(parameters[6]);
	cmb_direction_to_build->Enable(parameters[7]);
	txt_amount_of_buildings->Enable(parameters[8]);
	txt_building_size->Enable(parameters[9]);
}

void cMain::populate_comboboxes(std::vector<std::string> item_category, std::vector<std::string> item) {
	cmb_item_category->Clear();
	for (auto it = item_category.begin(); it < item_category.end(); it++) {
		cmb_item_category->Append(*it);
	}
	cmb_item_category->SetValue(*item_category.begin());

	cmb_item->Clear();
	for (auto it = item.begin(); it < item.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*item.begin());
}

void cMain::setup_paramters_comboboxes(std::vector<bool> parameters, std::vector<std::string> combo_item_category, std::vector<std::string> combo_item) {
	setup_paramters(parameters);

	if (parameters[0]) {
		populate_comboboxes(combo_item_category, combo_item);
	}
}


