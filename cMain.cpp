#include "cMain.h"
#include "GUI_Base.h"
#include "utils.h"
#include "Functions.h"
#include <fstream>
#include <sstream>
#include <iomanip>

cMain::cMain() : GUI_Base(nullptr, wxID_ANY, "Factorio Script Helper", wxPoint(30, 30), wxSize(1560, 1080)) {
	//all_items.resize(item_logistics.size() + item_production.size() + item_intermediates.size() + item_combat.size());
	all_items.insert(all_items.end(), item_logistics.begin(), item_logistics.end());
	all_items.insert(all_items.end(), item_production.begin(), item_production.end());
	all_items.insert(all_items.end(), item_intermediates.begin(), item_intermediates.end());
	all_items.insert(all_items.end(), item_combat.begin(), item_combat.end());

	static const std::vector<std::string> all_items_const(all_items);

	std::vector<std::string> test = { "Take", "-15.500000", "-2.500000", "All", "Iron plate", "Chest", "North", "1", "1" };

	task_groups["Burner - Iron"] = test;

	std::string test2 = task_groups["Burner - Iron"][1];

	for (auto s : all_items_const) {
		item_choices.Add(s);
	}

	for (auto s : take_from) {
		take_from_choices.Add(s);
	}

	for (auto s : tech_list) {
		tech_choices.Add(s);
	}

	for (auto s : build_orientations) {
		building_orientation_choices.Add(s);
	}

	list_task_num = 0;
	list_buildings_num = 0;
	//Generate_code_file_location = "C:\\Users\\MTNie\\AppData\\Roaming\\Factorio\\mods\\Speed_run_0.0.1\\tasksV2.lua"; // this needs to be set by the user - most likely in open or save - a save as might also be needed
	//save_file_location = "C:\\Users\\MTNie\\AppData\\Roaming\\Factorio\\mods\\Speed_run_0.0.1\\test.txt"; // this needs to be set by the user - most likely either when they open a file or save as. 

	// set walk as default value and disable inputs not used
	rbtn_walk->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.walk, item_categories, item_logistics);

	cmb_building_orientation->Clear();
	cmb_direction_to_build->Clear();
	for (auto it = build_orientations.begin(); it < build_orientations.end(); it++) {
		cmb_building_orientation->Append(*it);
		cmb_direction_to_build->Append(*it);

	}
	cmb_building_orientation->SetValue(*build_orientations.begin());
	cmb_building_orientation->AutoComplete(building_orientation_choices);
	cmb_direction_to_build->SetValue(*build_orientations.begin());
	cmb_direction_to_build->AutoComplete(building_orientation_choices);

	cmb_item->Clear();
	for (auto it = all_items_const.begin(); it < all_items_const.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items_const.begin());
	cmb_item->AutoComplete(item_choices);

	cmb_from_into->Clear();
	for (auto it = take_from.begin(); it < take_from.end(); it++) {
		cmb_from_into->Append(*it);
	}
	cmb_from_into->SetValue(*take_from.begin());
	cmb_from_into->AutoComplete(take_from_choices);

	cmb_tech->Clear();
	for (auto it = tech_list.begin(); it < tech_list.end(); it++) {
		cmb_tech->Append(*it);
	}
	cmb_tech->SetValue(*tech_list.begin());
	cmb_tech->AutoComplete(tech_choices);

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
	cmb_item->AutoComplete(item_choices); // Autocomplete example
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

void cMain::update_tasks_grid(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string orientation, std::string direction_to_build, std::string building_size, std::string amount_to_build) {

	if (grid_tasks->IsSelection()) {
		if (!grid_tasks->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Task list selection not valid");
			return;
		}
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

	if (grid_tasks->IsSelection()) {
		it1 = tasks_data_to_save.begin();
		it1 += row_num;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_to_build);
	} else {
		tasks_data_to_save.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_to_build);
	}
	
}

void cMain::change_task(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string orientation, std::string direction_to_build, std::string building_size, std::string amount_to_build) {
	if (grid_tasks->IsSelection()) {
		if (!grid_tasks->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Task list selection not valid");
			return;
		}
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

	if (grid_tasks->IsSelection()) {
		it1 = tasks_data_to_save.begin();
		it1 += row_num;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_to_build);
	} else {
		tasks_data_to_save.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_to_build);
	}

}




void cMain::update_buildings_grid(std::string x_cord, std::string y_cord, std::string item, std::string orientation, std::string recipe, std::string priority, std::string filter) {
	row_num = grid_buildings->GetNumberRows();

	grid_buildings->InsertRows(row_num, 1);

	grid_buildings->SetCellValue(row_num, 0, x_cord);
	grid_buildings->SetCellValue(row_num, 1, y_cord);
	grid_buildings->SetCellValue(row_num, 2, item);
	grid_buildings->SetCellValue(row_num, 3, orientation);

	buildings_data_to_save.push_back(x_cord + ";" + y_cord + ";" + item + ";" + orientation + ";" + recipe + ";" + priority + ";" + filter);
}

void cMain::update_buildings_grid_new_building(std::string x_cord, std::string y_cord, std::string item, std::string orientation) {
	row_num = grid_buildings->GetNumberRows();
	
	grid_buildings->InsertRows(row_num, 1);

	grid_buildings->SetCellValue(row_num, 0, x_cord);
	grid_buildings->SetCellValue(row_num, 1, y_cord);
	grid_buildings->SetCellValue(row_num, 2, item);
	grid_buildings->SetCellValue(row_num, 3, orientation);

	buildings_data_to_save.push_back(x_cord + ";" + y_cord + ";" + item + ";" + orientation + ";" + "" + ";" + "" + ";" + "");
}

void cMain::update_buildings_grid_from_scratch() {
	if (grid_buildings->GetNumberRows() > 0) {
		grid_buildings->DeleteRows(0, grid_buildings->GetNumberRows());
	}

	buildings_data_to_save = {};

	std::string task;
	std::string x_cord;
	std::string y_cord;
	std::string item;
	std::string orientation;
	std::string direction;
	std::string size;
	std::string amount;

	for (int i = 0; i < grid_tasks->GetNumberRows(); i++) {
		task = grid_tasks->GetCellValue(i, 0).ToStdString();

		if (task == "Build" ) {
			x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
			y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
			item = grid_tasks->GetCellValue(i, 4).ToStdString();
			orientation = grid_tasks->GetCellValue(i, 5).ToStdString();
			direction = grid_tasks->GetCellValue(i, 6).ToStdString();
			size = grid_tasks->GetCellValue(i, 7).ToStdString();
			amount = grid_tasks->GetCellValue(i, 8).ToStdString();

			building_row(x_cord, y_cord, item, orientation, direction, size, amount);
		}
	}
}

void cMain::update_building_orientation(std::string x_cord, std::string y_cord, std::string units) {
	row_num = grid_buildings->GetNumberRows();
	std::string build_x_cord;
	std::string build_y_cord;
	std::string build_orientation;

	for (int i = 0; i < row_num; i++) {
		build_x_cord = grid_buildings->GetCellValue(i, 0);
		build_y_cord = grid_buildings->GetCellValue(i, 1);
		build_orientation = grid_buildings->GetCellValue(i, 3);
		int orientation_location;

		if (build_x_cord != x_cord) {
			continue;
		}
		if (build_y_cord != y_cord) {
			continue;
		}

		for (auto it = build_orientations.begin(); it < build_orientations.end(); it++) {
			if (build_orientation == *it) {
				orientation_location = it - build_orientations.begin();
			}
		}

		grid_buildings->SetCellValue(i, 3, build_orientations[(orientation_location + std::stoi(units)) % 4]);
		return;
	}

	wxMessageBox("Building location does not seem to exit.\nPlease use exactly the same coordinates as you used to build", "Please use the same coordinates");
}

void cMain::building_row(std::string x_cord, std::string y_cord, std::string item, std::string build_orientation, std::string direction_to_build, std::string building_size, std::string amount_of_buildings) {
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
			update_buildings_grid_new_building(x_cord, std::to_string(start_y_cord - i * building_size_int), item, build_orientation);
		}
	} else if (direction_to_build == "South") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			update_buildings_grid_new_building(x_cord, std::to_string(start_y_cord + i * building_size_int), item, build_orientation);
		}
	} else if (direction_to_build == "East") {

		for (int i = 0; i < number_of_buildings_int; i++) {
			update_buildings_grid_new_building(std::to_string(start_x_cord + i * building_size_int), y_cord, item, build_orientation);
		}
	} else if (direction_to_build == "West") {

		for (int i = 0; i < number_of_buildings_int; i++) {
			update_buildings_grid_new_building(std::to_string(start_x_cord - i * building_size_int), y_cord, item, build_orientation);
		}
	}

}

void cMain::OnAddTaskClicked(wxCommandEvent& event) {
	
	// Extract data needed to add task
	x_cord = extract_x_cord();
	y_cord = extract_y_cord();
	units = extract_units();
	item = extract_item();
	from_into = extract_from_into();
	build_orientation = extract_building_orientation();
	direction_to_build = extract_direction_to_build();
	building_size = extract_building_size();
	amount_of_buildings = extract_amount_of_buildings();
	tech_to_start = extract_tech();

	// Game speed task logic
	if (rbtn_game_speed->GetValue()) {
		update_tasks_grid("Game Speed", not_relevant, not_relevant, not_relevant, units, not_relevant, not_relevant, not_relevant, not_relevant);
		
	// Walk task logic
	} else if (rbtn_walk->GetValue()) {
		update_tasks_grid("Walk", x_cord, y_cord, not_relevant, not_relevant, not_relevant, not_relevant, not_relevant, not_relevant);
	
	// Mine task logic
	} else if (rbtn_mine->GetValue()) {
		update_tasks_grid("Mine", x_cord, y_cord, not_relevant, units, not_relevant, not_relevant, not_relevant, not_relevant);

	// Rotation logic
	} else if (rbtn_rotate->GetValue()) {
		update_tasks_grid("Rotate", x_cord, y_cord, not_relevant, units, not_relevant, not_relevant, not_relevant, not_relevant);
		update_building_orientation(x_cord, y_cord, units);

	// Craft task logic
	} else if (rbtn_craft->GetValue()) {
		if (!check_item(item, all_items)) {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
			return;
		}

		update_tasks_grid("Craft", not_relevant, not_relevant, item, units, not_relevant, not_relevant, not_relevant, not_relevant);
	
	// Fuel task logic
	} else if (rbtn_fuel->GetValue()) {
		if (!check_item(item, all_items)) {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
			return;
		}

		if (!check_building(direction_to_build, build_orientations)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return;
		}

		update_tasks_grid("Fuel", x_cord, y_cord, item, units, not_relevant, direction_to_build, building_size, amount_of_buildings);
	
	// Build task logic
	} else if (rbtn_build->GetValue()) {
		if (!check_item(item, all_items)) {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
			return;
		}

		if (!check_building(build_orientation, build_orientations)) {
			wxMessageBox("The build direction is not valid - please try again", "Please use the build direction dropdown menu");
			return;
		}

		if (!check_building(direction_to_build, build_orientations)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return;
		}

		update_tasks_grid("Build", x_cord, y_cord, item, not_relevant, build_orientation, direction_to_build, building_size, amount_of_buildings);
		building_row(x_cord, y_cord, item, build_orientation, direction_to_build, building_size, amount_of_buildings);

	// Take from logic
	} else if (rbtn_take->GetValue()) {

		if (!check_take_put(item, take_from)) {
			wxMessageBox("The combination of From/Into and item is not valid - please try again", "Please ensure that the combination is valid");
			return;
		}

		if (!check_building(direction_to_build, build_orientations)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return;
		}

		update_tasks_grid("Take", x_cord, y_cord, item, units, from_into, direction_to_build, building_size, amount_of_buildings);

	} else if (rbtn_put->GetValue()) {

		if (!check_take_put(item, take_from)) {
			wxMessageBox("The combination of From/Into and item is not valid - please try again", "Please ensure that the combination is valid");
			return;
		}

		if (!check_building(direction_to_build, build_orientations)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return;
		}

		update_tasks_grid("Put", x_cord, y_cord, item, units, from_into, direction_to_build, building_size, amount_of_buildings);

	} else if (rbtn_tech->GetValue()) {
		if (!check_item(tech_to_start, tech_list)) {
			wxMessageBox("The tech is not valid - please try again", "Please use the tech dropdown menu");
			return;
		}
		update_tasks_grid("Tech", not_relevant, not_relevant, tech_to_start, not_relevant, not_relevant, not_relevant, not_relevant, not_relevant);
	}
	event.Skip();
}

void cMain::OnChangeTaskClicked(wxCommandEvent& event) {
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin()) {
		wxMessageBox("Please select a row to change", "Selection not valid");
		return;
	}

	row_num = *grid_tasks->GetSelectedRows().begin();

	x_cord = extract_x_cord();
	y_cord = extract_y_cord();
	units = extract_units();
	item = extract_item();
	from_into = extract_from_into();
	build_orientation = extract_building_orientation();
	direction_to_build = extract_direction_to_build();
	building_size = extract_building_size();
	amount_of_buildings = extract_amount_of_buildings();
	tech_to_start = extract_tech();



	grid_tasks->SetCellValue(row_num, 0, task);
	grid_tasks->SetCellValue(row_num, 1, extract_x_cord());
	grid_tasks->SetCellValue(row_num, 2, extract_y_cord());
	grid_tasks->SetCellValue(row_num, 3, extract_units());
	grid_tasks->SetCellValue(row_num, 4, extract_item());
	grid_tasks->SetCellValue(row_num, 5, extract_building_orientation());
	grid_tasks->SetCellValue(row_num, 6, extract_direction_to_build());
	grid_tasks->SetCellValue(row_num, 7, extract_building_size());
	grid_tasks->SetCellValue(row_num, 8, extract_amount_of_buildings());
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
	static std::string tasks_units = grid_tasks->GetCellValue(tasks_row_selected, 3).ToStdString();
	static std::string tasks_item = grid_tasks->GetCellValue(tasks_row_selected, 4).ToStdString();
	static std::string tasks_building_direction = grid_tasks->GetCellValue(tasks_row_selected, 5).ToStdString();
	static std::string tasks_direction_to_build = grid_tasks->GetCellValue(tasks_row_selected, 6).ToStdString();
	static std::string tasks_size = grid_tasks->GetCellValue(tasks_row_selected, 7).ToStdString();
	static std::string tasks_building_amount = grid_tasks->GetCellValue(tasks_row_selected, 8).ToStdString();
	
	tasks_task = grid_tasks->GetCellValue(tasks_row_selected, 0).ToStdString();
	tasks_x_cord = grid_tasks->GetCellValue(tasks_row_selected, 1).ToStdString();
	tasks_y_cord = grid_tasks->GetCellValue(tasks_row_selected, 2).ToStdString();
	tasks_units = grid_tasks->GetCellValue(tasks_row_selected, 3).ToStdString();
	tasks_item = grid_tasks->GetCellValue(tasks_row_selected, 4).ToStdString();
	tasks_building_direction = grid_tasks->GetCellValue(tasks_row_selected, 5).ToStdString();
	tasks_direction_to_build = grid_tasks->GetCellValue(tasks_row_selected, 6).ToStdString();
	tasks_size = grid_tasks->GetCellValue(tasks_row_selected, 7).ToStdString();
	tasks_building_amount = grid_tasks->GetCellValue(tasks_row_selected, 8).ToStdString();

	if (tasks_task == "Game Speed") {
		OnGameSpeedMenuSelected(event);
		txt_units->SetValue(tasks_units);

	} else if (tasks_task == "Walk") {
		OnWalkMenuSelected(event);
		txt_x_cord->SetValue(tasks_x_cord);
		txt_y_cord->SetValue(tasks_y_cord);

	} else if (tasks_task == "Mine") {
		OnMineMenuSelected(event);
		txt_x_cord->SetValue(tasks_x_cord);
		txt_y_cord->SetValue(tasks_y_cord);
		txt_units->SetValue(tasks_units);

	} else if (tasks_task == "Rotate") {
		OnRotateMenuSelected(event);
		txt_x_cord->SetValue(tasks_x_cord);
		txt_y_cord->SetValue(tasks_y_cord);
		txt_units->SetValue(tasks_units);

	} else if (tasks_task == "Craft") {
		OnCraftMenuSelected(event);
		txt_units->SetValue(tasks_units);
		cmb_item->SetValue(tasks_item);

	} else if (tasks_task == "Build") {
		OnBuildMenuSelected(event);
		txt_x_cord->SetValue(tasks_x_cord);
		txt_y_cord->SetValue(tasks_y_cord);
		cmb_item->SetValue(tasks_item);
		cmb_building_orientation->SetValue(tasks_building_direction);
		cmb_direction_to_build->SetValue(tasks_direction_to_build);
		txt_building_size->SetValue(tasks_size);
		txt_amount_of_buildings->SetValue(tasks_building_amount);

	} else if (tasks_task == "Take") {
		OnTakeMenuSelected(event);
		txt_x_cord->SetValue(tasks_x_cord);
		txt_y_cord->SetValue(tasks_y_cord);
		txt_units->SetValue(tasks_units);
		cmb_item->SetValue(tasks_item);
		cmb_from_into->SetValue(tasks_building_direction);
		cmb_direction_to_build->SetValue(tasks_direction_to_build);
		txt_building_size->SetValue(tasks_size);
		txt_amount_of_buildings->SetValue(tasks_building_amount);

	} else if (tasks_task == "Put") {
		OnPutMenuSelected(event);
		txt_x_cord->SetValue(tasks_x_cord);
		txt_y_cord->SetValue(tasks_y_cord);
		txt_units->SetValue(tasks_units);
		cmb_item->SetValue(tasks_item);
		cmb_from_into->SetValue(tasks_building_direction);
		cmb_direction_to_build->SetValue(tasks_direction_to_build);
		txt_building_size->SetValue(tasks_size);
		txt_amount_of_buildings->SetValue(tasks_building_amount);

	} else if (tasks_task == "") {

	} else if (tasks_task == "") {

	}

	event.Skip();
}

void cMain::OnBuildingsGridLeftClick(wxGridEvent& event) {
	
	
}

void cMain::OnBuildingsGridLeftDoubleClick(wxGridEvent& event) {
	buildings_row_selected = event.GetRow();

	static std::string buildings_x_cord = grid_buildings->GetCellValue(buildings_row_selected, 0).ToStdString();
	static std::string buildings_y_cord = grid_buildings->GetCellValue(buildings_row_selected, 1).ToStdString();
	static std::string buildings_item = grid_buildings->GetCellValue(buildings_row_selected, 2).ToStdString();
	static std::string buildings_building_direction = grid_buildings->GetCellValue(buildings_row_selected, 3).ToStdString();

	buildings_x_cord = grid_buildings->GetCellValue(buildings_row_selected, 0).ToStdString();
	buildings_y_cord = grid_buildings->GetCellValue(buildings_row_selected, 1).ToStdString();
	buildings_item = grid_buildings->GetCellValue(buildings_row_selected, 2).ToStdString();
	buildings_building_direction = grid_buildings->GetCellValue(buildings_row_selected, 3).ToStdString();

	txt_x_cord->SetValue(buildings_x_cord);
	txt_y_cord->SetValue(buildings_y_cord);
	cmb_item->SetValue(buildings_item);
	cmb_building_orientation->SetValue(buildings_building_direction);
}

void cMain::OnWalkKeyDown(wxKeyEvent& event) {
	
}
void cMain::OnFameKeyDown(wxKeyEvent& event) {
	int test = event.GetKeyCode();

	if (test == 9) {

	};
};

void cMain::OnBuildingDirectionSelected(wxCommandEvent& event) {
	// It seems that this is not needed
}

void cMain::OnDirectionToBuildSelected(wxCommandEvent& event) {
	// It seems that this is not needed
}

void cMain::OnDeleteTaskClicked(wxCommandEvent& event) {
	if (!grid_tasks->IsSelection()) {
		wxMessageBox("No task is chosen - please select a row in the task list", "Cannot delete task");
		return;
	}

	int start_row = *grid_tasks->GetSelectedRows().begin();
	int row_count = grid_tasks->GetSelectedRows().GetCount();

	grid_tasks->DeleteRows(start_row, row_count);
	it1 = tasks_data_to_save.begin();
	it2 = tasks_data_to_save.begin();

	it1 += start_row;
	it2 += start_row + row_count;

	tasks_data_to_save.erase(it1, it2);	

	update_buildings_grid_from_scratch();
}

void cMain::OnMenuNew(wxCommandEvent& evt) {

	if (grid_tasks->GetNumberRows() > 0) {
		if (wxMessageBox("Are you sure you want to create a new file?\nAll in the current window will be cleared.", "Ensure that you have saved what you need in the file", wxICON_QUESTION | wxYES_NO, this) != wxYES) {
			return;
		}
		grid_tasks->DeleteRows(0, grid_tasks->GetNumberRows());
	}

	if (grid_buildings->GetNumberRows() > 0) {
		grid_buildings->DeleteRows(0, grid_buildings->GetNumberRows());
	}

	rbtn_walk->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.walk, item_categories, item_logistics);

	save_file_location = "";
	generate_code_file_location = "";

	tasks_data_to_save = {};
	buildings_data_to_save = {};
}

void cMain::OnMenuOpen(wxCommandEvent& evt) {
	
	wxFileDialog dlg(this, "Open saved factorio script helper file", "", "", ".txt files (*.txt) | *.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (dlg.ShowModal() == wxID_OK) {
		std::ifstream inFile;
		inFile.open(dlg.GetPath().ToStdString());
		bool buildings_list_reached = false;
		bool saved_file_reached = false;
		bool generate_code_reached = false;

		if (!inFile) {
			wxMessageBox("It was not possible to open the file", "A file error occurred");
			return;
		}

		if (grid_tasks->GetNumberRows() > 0) {
			if (wxMessageBox("Are you sure you want to open this file?\nAll in the current window will be cleared and the new data inserted.", "Ensure that you have saved what you need in the file", wxICON_QUESTION | wxYES_NO, this) != wxYES) {
				return;
			}
			grid_tasks->DeleteRows(0, grid_tasks->GetNumberRows());
			if (grid_buildings->GetNumberRows() > 0) {
				grid_buildings->DeleteRows(0, grid_buildings->GetNumberRows());
			}

			tasks_data_to_save = {};
			buildings_data_to_save = {};
		}

		std::string segment;
		std::vector<std::string> seglist;

		while (std::getline(inFile, open_data_string)) {
			std::stringstream open_data_string_line;
			open_data_string_line.str(open_data_string);

			seglist = {};

			while (std::getline(open_data_string_line, segment, ';')) {
				seglist.push_back(segment);
			}

			if (seglist[0] == buildings_list_save_indicator) {
				buildings_list_reached = true;

			} else if (seglist[0] == save_file_location_indicator) {
				saved_file_reached = true;

			} else if (seglist[0] == generate_file_location_indicator) {
				generate_code_reached = true;

			} else if (!buildings_list_reached) {
				if (seglist.size() == 9) {
					update_tasks_grid(seglist[0], seglist[1], seglist[2], seglist[4], seglist[3], seglist[5], seglist[6], seglist[7], seglist[8]);
				} else {
					wxMessageBox("It seems like the structure of the file does not correspond with a factorio script helper file", "A file error occurred");
					return;
				}
		
			} else if (!saved_file_reached) {
				if (seglist.size() == 7) {
					update_buildings_grid(seglist[0], seglist[1], seglist[2], seglist[3], seglist[4], seglist[5], seglist[6]);
				} else {
					wxMessageBox("It seems like the structure of the file does not correspond with a factorio script helper file", "A file error occurred");
					return;
				}
			} else if (!generate_code_reached) {
				if (seglist.size() == 1) {
					save_file_location = seglist[0];
					generate_code_reached = true;
				} else {
					wxMessageBox("It seems like the structure of the file does not correspond with a factorio script helper file", "A file error occurred");
					return;
				}
			} else {
				if (seglist.size() == 1) {
					generate_code_file_location = seglist[0];
					generate_code_reached = true;
				} else {
					wxMessageBox("It seems like the structure of the file does not correspond with a factorio script helper file", "A file error occurred");
					return;
				}
			}
		}

		inFile.close();
	}	
}

void cMain::OnMenuSave(wxCommandEvent& evt) {

	if (save_file_location == "") {
		wxFileDialog dlg(this, "Save factorio script helper", "", "", ".txt files (*.txt) | *.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (dlg.ShowModal() == wxID_OK) {
			save_file_location = dlg.GetPath().ToStdString();
		} else {
			return;
		}
	}

	std::ofstream myfile;
	myfile.open(save_file_location);

	for (auto it = tasks_data_to_save.begin(); it < tasks_data_to_save.end(); it++) {
		myfile << *it << ";" << std::endl;
	}

	myfile << buildings_list_save_indicator << std::endl;
		
	for (auto it = buildings_data_to_save.begin(); it < buildings_data_to_save.end(); it++) {
		myfile << *it << ";" << std::endl;
	}

	myfile << save_file_location_indicator << std::endl;

	myfile << save_file_location << std::endl;

	myfile << generate_file_location_indicator << std::endl;

	myfile << generate_code_file_location << std::endl;

	myfile.close();

	clear_tasks();
}

void cMain::OnMenuSaveAs(wxCommandEvent& event) {

	wxFileDialog dlg(this, "Save factorio script helper", "", "", ".txt files (*.txt) | *.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (dlg.ShowModal() == wxID_OK) {
		save_file_location = dlg.GetPath().ToStdString();
		std::ofstream myfile;
		myfile.open(save_file_location);

		for (auto it = tasks_data_to_save.begin(); it < tasks_data_to_save.end(); it++) {
			myfile << *it << ";" << std::endl;
		}

		myfile << buildings_list_save_indicator << std::endl;

		for (auto it = buildings_data_to_save.begin(); it < buildings_data_to_save.end(); it++) {
			myfile << *it << ";" << std::endl;
		}

		myfile.close();

		clear_tasks();
	}
}

void cMain::OnMenuExit(wxCommandEvent& evt) {
	evt.Skip();	
	Close();
}

void cMain::OnChooseLocation(wxCommandEvent& event) {
	wxFileDialog dlg(this, "Choose location to generate script", "", "", ".lua files (*.lua) | *.lua", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	generate_code_file_location = dlg.GetPath().ToStdString();
}

void cMain::OnGenerateScript(wxCommandEvent& event) {
	if (generate_code_file_location == "") {
		wxFileDialog dlg(this, "Choose location to generate script", "", "", ".lua files (*.lua) | *.lua", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() == wxID_OK) {
			generate_code_file_location = dlg.GetPath().ToStdString();
		} else {
			return;
		}
	}

	int tasks = grid_tasks->GetNumberRows();

	static std::string tasks_task;
	static std::string tasks_x_cord;
	static std::string tasks_y_cord;
	static std::string tasks_item; 
	static std::string tasks_units;
	static std::string tasks_orientation;
	static std::string tasks_direction_to_build; 
	static std::string tasks_size;
	static std::string tasks_building_amount;
	static std::string building;

	for (int i = 0; i < tasks; i++) {
		tasks_task = grid_tasks->GetCellValue(i, 0).ToStdString();
		tasks_x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
		tasks_y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
		tasks_units = grid_tasks->GetCellValue(i, 3).ToStdString();
		tasks_item = convert_string(grid_tasks->GetCellValue(i, 4).ToStdString());
		tasks_orientation = convert_string(grid_tasks->GetCellValue(i, 5).ToStdString());
		tasks_direction_to_build = convert_string(grid_tasks->GetCellValue(i, 6).ToStdString());
		tasks_size = grid_tasks->GetCellValue(i, 7).ToStdString();
		tasks_building_amount = grid_tasks->GetCellValue(i, 8).ToStdString();

		if (tasks_task == "Game Speed") {
			speed(tasks_units);

		} else if (tasks_task == "Walk") {
			walk(tasks_x_cord, tasks_y_cord);

		} else if (tasks_task == "Mine") {
			mining(tasks_x_cord, tasks_y_cord, tasks_units);

		} else if (tasks_task == "Rotate") {
			rotate(tasks_x_cord, tasks_y_cord, tasks_units);

		} else if (tasks_task == "Craft") {
			if (tasks_units == "All") {
				craft("-1", tasks_item);
			} else {
				craft(tasks_units, tasks_item);
			}
			
		} else if (tasks_task == "Tech") {
			tech(tasks_item);

		} else if (tasks_task == "Build") {
			build_row_of_buildings(tasks_x_cord, tasks_y_cord, tasks_item, tasks_orientation, tasks_direction_to_build, tasks_building_amount, tasks_size);

		} else if (tasks_task == "Take") {

			if (tasks_orientation == "chest") {
				from_into = take_put_list.chest;
			} else if (tasks_orientation == "fuel") {
				from_into = take_put_list.fuel;
			} else {

				for (int j = i-1; j > -1; j--) {
					if (grid_tasks->GetCellValue(j, 0).ToStdString() == "Build") {
						if (grid_tasks->GetCellValue(j, 1).ToStdString() == tasks_x_cord && grid_tasks->GetCellValue(j, 2).ToStdString() == tasks_y_cord) {
							building = grid_tasks->GetCellValue(j, 4).ToStdString();
							break;
						}
					}
				}

				if (building == "Lab") {
					if (tasks_orientation == "input") {
						from_into = take_put_list.lab_input;
					} else if (tasks_orientation == "modules") {
						from_into = take_put_list.lab_modules;
					}
				} else if (check_item(building, drills_list)) {
					if (tasks_orientation == "modules") {
						from_into = take_put_list.drill_modules;
					}
				} else {
					if (tasks_orientation == "input") {
						from_into = take_put_list.assembly_input;
					} else if (tasks_orientation == "modules") {
						from_into = take_put_list.assembly_modules;
					} else if (tasks_orientation == "output") {
						from_into = take_put_list.assembly_output;
					}
				}
			}
			

			if (tasks_units == "All") {
				row_take(tasks_x_cord, tasks_y_cord, "-1", tasks_item, from_into, tasks_direction_to_build, tasks_building_amount, tasks_size);
			} else {
				row_take(tasks_x_cord, tasks_y_cord, tasks_units, tasks_item, from_into, tasks_direction_to_build, tasks_building_amount, tasks_size);

			}

		} else if (tasks_task == "Put") {
			if (tasks_orientation == "chest") {
				from_into = take_put_list.chest;
			} else if (tasks_orientation == "fuel") {
				from_into = take_put_list.fuel;
			} else {

				for (int j = i - 1; j > -1; j--) {
					if (grid_tasks->GetCellValue(j, 0).ToStdString() == "Build") {
						if (grid_tasks->GetCellValue(j, 1).ToStdString() == tasks_x_cord && grid_tasks->GetCellValue(j, 2).ToStdString() == tasks_y_cord) {
							building = grid_tasks->GetCellValue(j, 4).ToStdString();
							break;
						}
					}
				}

				if (building == "Lab") {
					if (tasks_orientation == "input") {
						from_into = take_put_list.lab_input;
					} else if (tasks_orientation == "modules") {
						from_into = take_put_list.lab_modules;
					}
				} else if (check_item(building, drills_list)) {
					if (tasks_orientation == "modules") {
						from_into = take_put_list.drill_modules;
					}
				} else {
					if (tasks_orientation == "input") {
						from_into = take_put_list.assembly_input;
					} else if (tasks_orientation == "modules") {
						from_into = take_put_list.assembly_modules;
					} else if (tasks_orientation == "output") {
						from_into = take_put_list.assembly_output;
					}
				}
			}

			if (tasks_units == "All") {
				row_put(tasks_x_cord, tasks_y_cord, "-1", tasks_item, from_into, tasks_direction_to_build, tasks_building_amount, tasks_size);
			} else {
				row_put(tasks_x_cord, tasks_y_cord, tasks_units, tasks_item, from_into, tasks_direction_to_build, tasks_building_amount, tasks_size);
			}
		}
	}




	std::ofstream myfile;
	myfile.open(generate_code_file_location);

	myfile << end_tasks();

	myfile.close();

	clear_tasks();
}

void cMain::OnChangeShortcuts(wxCommandEvent& event) {
	shortcuts = new Shortcuts_Menu(this);
	shortcuts->Show();
}

void cMain::OnWalkMenuSelected(wxCommandEvent& event) {
	rbtn_walk->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.walk, item_categories, item_logistics);
	
	//// IMPORTANT -- This can be used to change the shortcuts of menuitems
	//wxAcceleratorEntry* plusAccel = new wxAcceleratorEntry(wxACCEL_CTRL, 50, wxID_ZOOM_IN);
	//menu_shortcuts->FindChildItem(10001)->SetAccel(plusAccel); // 10001 is the id of the menu item and can be set to what ever you want
}

void cMain::OnMineMenuSelected(wxCommandEvent& event) {
	rbtn_mine->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.mining, item_categories, item_logistics);
}

void cMain::OnGameSpeedMenuSelected(wxCommandEvent& event) {
	rbtn_game_speed->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.game_speed, item_categories, item_logistics);
}

void cMain::OnBuildMenuSelected(wxCommandEvent& event) {
	rbtn_build->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.build, item_categories, item_logistics);
}

void cMain::OnFuelMenuSelected(wxCommandEvent& event) {
	rbtn_fuel->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.fuel, item_categories_fuel, item_fuels);

}

void cMain::OnTakeMenuSelected(wxCommandEvent& event) {
	rbtn_take->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.take, item_categories, item_logistics);
}

void cMain::OnPutMenuSelected(wxCommandEvent& event) {
	rbtn_put->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.put, item_categories, item_logistics);

}

void cMain::OnCraftMenuSelected(wxCommandEvent& event) {
	rbtn_craft->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.craft, item_categories, item_logistics);
}

void cMain::OnRotateMenuSelected(wxCommandEvent& event) {
	rbtn_rotate->SetValue(true);
	setup_paramters_comboboxes(parameter_choices.rotate, item_categories, item_logistics);
}

void cMain::OnAddMenuSelected(wxCommandEvent& event) {
	OnAddTaskClicked(event);
}

void cMain::setup_paramters(std::vector<bool> parameters) {
	txt_x_cord->Enable(parameters[1]);
	txt_y_cord->Enable(parameters[2]);
	txt_units->Enable(parameters[3]);
	cmb_item->Enable(parameters[5]);
	cmb_from_into->Enable(parameters[4]);
	cmb_tech->Enable(parameters[10]);
	cmb_building_orientation->Enable(parameters[6]);
	cmb_direction_to_build->Enable(parameters[7]);
	txt_amount_of_buildings->Enable(parameters[8]);
	txt_building_size->Enable(parameters[9]);
}

std::string cMain::extract_x_cord() {
	return std::to_string(wxAtof(txt_x_cord->GetValue()));
}

std::string cMain::extract_y_cord() {
	return std::to_string(wxAtof(txt_y_cord->GetValue()));
}

std::string cMain::extract_units() {
	units = std::to_string(wxAtoi(txt_units->GetValue()));
	
	if (rbtn_game_speed->GetValue()) {
		if (std::stof(units) < 0.01) {
			units = "0.01";
		}
	} else if (rbtn_mine->GetValue() || rbtn_limit->GetValue() || rbtn_rotate->GetValue()) {
		if (std::stof(units) < 1) {
			units = "1";
		}
	} else {
		if (std::stof(units) < 1) {
			units = "All";
		}
	}

	return units;
}

std::string cMain::extract_item() {
	item = cmb_item->GetValue().ToStdString();
	string_capitalized(item);

	return item;
}

std::string cMain::extract_amount_of_buildings() {
	amount_of_buildings = std::to_string(wxAtoi(txt_amount_of_buildings->GetValue()));
	if (std::stoi(amount_of_buildings) < 1) {
		amount_of_buildings = "1";
	}
	
	return amount_of_buildings;
}

std::string cMain::extract_building_size() {
	building_size = std::to_string(wxAtoi(txt_building_size->GetValue()));
	if (std::stoi(building_size) < 1) {
		building_size = "1";
	}
	return building_size;
}

std::string cMain::extract_from_into() {
	from_into = cmb_from_into->GetValue().ToStdString();
	string_capitalized(from_into);
	
	return from_into;
}

std::string cMain::extract_direction_to_build() {
	direction_to_build = cmb_direction_to_build->GetValue().ToStdString();
	string_capitalized(direction_to_build);

	return direction_to_build;
}

std::string cMain::extract_building_orientation() {
	build_orientation = cmb_building_orientation->GetValue().ToStdString();
	string_capitalized(build_orientation);

	return build_orientation;
}

std::string cMain::extract_tech() {
	tech_to_start = cmb_tech->GetValue().ToStdString();
	string_capitalized(tech_to_start);

	return tech_to_start;
}

void cMain::populate_comboboxes(std::vector<std::string> item_category, std::vector<std::string> item) {
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

bool cMain::check_building(const std::string& item, const std::vector<std::string>& all_items) {
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		if (item == *it) {
			return true;
		}
	}

	return false;
}

bool cMain::check_take_put(const std::string& item, const std::vector<std::string>& all_items) {
	std::string to_check = extract_from_into();
	string_capitalized(to_check);

	if (to_check == "Chest") {
		return true;

	} else if (to_check == "Fuel") {
		for (auto it = item_fuels.begin(); it < item_fuels.end(); it++) {
			if (item == *it) {
				return true;
			}
		}
		return false;

	} else if (item == "Lab") {
		if (to_check == "Input") {
			for (auto it = science_packs.begin(); it < science_packs.end(); it++) {
				if (item == *it) {
					return true;
				}
			}
			return false;
		} else if (to_check == "Modules") {
			for (auto it = module_list.begin(); it < module_list.end(); it++) {
				if (item == *it) {
					return true;
				}
			}
			
			return false;
		}

	} else if (check_item(item, drills_list)) {
		if (to_check == "Modules") {
			for (auto it = module_list.begin(); it < module_list.end(); it++) {
				if (item == *it) {
					return true;
				}
			}

			return false;
		}
	} else {
		if (to_check == "Input") {
			// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
			return true;
		} else if (to_check == "Modules") { 
			for (auto it = module_list.begin(); it < module_list.end(); it++) {
				if (item == *it) {
					return true;
				}
			}

			return false;
		} else if (to_check == "Output") {
			// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
			return true;
		} else {
			return false;
		}
	}

	return false;
}

bool cMain::check_item(const std::string& item, const std::vector<std::string>& all_items) {
	
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		if (item == *it) {
			return true;
		}
	}

	return false;
}


