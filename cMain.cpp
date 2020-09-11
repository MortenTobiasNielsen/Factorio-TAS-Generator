#include "cMain.h"
#include "GUI_Base.h"
#include "utils.h"
#include "Functions.h"
#include <fstream>
#include <sstream>
#include <iomanip>

cMain::cMain() : GUI_Base(nullptr, wxID_ANY, "Factorio Script Helper", wxPoint(30, 30), wxSize(1500, 1080)) {
	//all_items.resize(item_logistics.size() + item_production.size() + item_intermediates.size() + item_combat.size());
	all_items.insert(all_items.end(), item_logistics.begin(), item_logistics.end());
	all_items.insert(all_items.end(), item_production.begin(), item_production.end());
	all_items.insert(all_items.end(), item_intermediates.begin(), item_intermediates.end());
	all_items.insert(all_items.end(), item_combat.begin(), item_combat.end());

	static const std::vector<std::string> all_items_const(all_items);

	//item_choices.Add("Wooden chest");
	//item_choices.Add("Inserter");
	//
	//item_choices.Add(all_items_const[0]);
	//item_choices.Add("This is a long sentence");

	for (auto s : all_items_const) {
		item_choices.Add(s);
	}

	list_task_num = 0;
	list_buildings_num = 0;
	file_location = "C:\\Users\\MTNie\\AppData\\Roaming\\Factorio\\mods\\Speed_run_0.0.1\\tasksV2.lua"; // this needs to be set by the user - most likely in open or save - a save as might also be needed

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

	// Game speed task logic
	if (rbtn_game_speed->GetValue()) {
		units = std::to_string(wxAtoi(txt_units->GetValue()));
		if (std::stof(units) < 0.01) {
			units = "0.01";
		}

		update_tasks_grid("Game Speed", not_relevant, not_relevant, not_relevant, units, not_relevant, not_relevant, not_relevant, not_relevant);

		speed(units);
		
	// Walk task logic
	} else if (rbtn_walk->GetValue()) {
		
		x_cord = std::to_string(wxAtof(txt_x_cord->GetValue()));
		y_cord = std::to_string(wxAtof(txt_y_cord->GetValue()));

		units = std::to_string(wxAtoi(txt_units->GetValue()));
		if (std::stof(units) < 1) {
			units = "1";
		}

		update_tasks_grid("Walk", x_cord, y_cord, not_relevant, not_relevant, not_relevant, not_relevant, not_relevant, not_relevant);

		walk(x_cord, y_cord);
	
	// Mine task logic
	} else if (rbtn_mine->GetValue()) {

		x_cord = std::to_string(wxAtof(txt_x_cord->GetValue()));
		y_cord = std::to_string(wxAtof(txt_y_cord->GetValue()));

		units = std::to_string(wxAtoi(txt_units->GetValue()));
		if (std::stof(units) < 1) {
			units = "1";
		}

		update_tasks_grid("Mine", x_cord, y_cord, not_relevant, units, not_relevant, not_relevant, not_relevant, not_relevant);

		mining(x_cord, y_cord, units);

	// Craft task logic
	} else if (rbtn_craft->GetValue()) {
		units = std::to_string(wxAtoi(txt_units->GetValue()));
		item = cmb_item->GetValue().ToStdString();

		if (!check_item(item, all_items)) {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
			return;
		}

		update_tasks_grid("Craft", not_relevant, not_relevant, item, units, not_relevant, not_relevant, not_relevant, not_relevant);
		craft(units, convert_string(item));
	
	// Fuel task logic
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
		direction_to_build = cmb_direction_to_build->GetValue().ToStdString();

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
	
	// Build task logic
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
	} else if (rbtn_take->GetValue()) {
		
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
	static std::string tasks_units = grid_tasks->GetCellValue(tasks_row_selected, 4).ToStdString();
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

	txt_x_cord->SetValue(tasks_x_cord);
	txt_y_cord->SetValue(tasks_y_cord);
	txt_units->SetValue(tasks_units);
	cmb_item->SetValue(tasks_item);
	cmb_building_direction->SetValue(tasks_building_direction);
	cmb_direction_to_build->SetValue(tasks_direction_to_build);
	txt_building_size->SetValue(tasks_size);
	txt_amount_of_buildings->SetValue(tasks_building_amount);

	event.Skip();
}

void cMain::OnBuildingsGridLeftClick(wxGridEvent& event) {
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
	cmb_building_direction->SetValue(buildings_building_direction);
	
}

void cMain::OnBuildingsGridLeftDoubleClick(wxGridEvent& event) {
	
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
	
}

void cMain::OnMenuNew(wxCommandEvent& evt) {

}

void cMain::OnMenuOpen(wxCommandEvent& evt) {

}

void cMain::OnMenuSave(wxCommandEvent& evt) {
	
}

void cMain::OnMenuSaveAs(wxCommandEvent& event) {

}

void cMain::OnMenuExit(wxCommandEvent& evt) {
	Close();
	evt.Skip();
}

void cMain::OnChooseLocation(wxCommandEvent& event) {
}

void cMain::OnGenerateScript(wxCommandEvent& event) {
	std::ofstream myfile;
	myfile.open(file_location);

	myfile << end_tasks();;

	myfile.close();
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


