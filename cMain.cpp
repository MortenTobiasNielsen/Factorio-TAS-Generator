#include "cMain.h"
#include "GUI_Base.h"
#include "utils.h"
#include "Functions.h"
#include "control_info.h"
#include "icon.xpm"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <filesystem>

cMain::cMain() : GUI_Base(nullptr, wxID_ANY, window_title, wxPoint(30, 30), wxSize(1840, 950)) {
	SetIcon(icon_xpm);
	SetLabel(window_title);

	task_segments.reserve(100);
	seglist.reserve(100);

	part_assembly_recipes.insert(part_assembly_recipes.end(), handcrafted_list.begin(), handcrafted_list.end());
	part_assembly_recipes.insert(part_assembly_recipes.end(), assemply_level1_list.begin(), assemply_level1_list.end());
	
	full_assembly_recipes.insert(full_assembly_recipes.end(), part_assembly_recipes.begin(), part_assembly_recipes.end());
	full_assembly_recipes.insert(full_assembly_recipes.end(), assemply_level2_list.begin(), assemply_level2_list.end());
	full_assembly_recipes.insert(full_assembly_recipes.end(), assemply_level2_extra_list.begin(), assemply_level2_extra_list.end());

	full_chemical_plant_recipes.insert(full_chemical_plant_recipes.end(), chemical_plant_list.begin(), chemical_plant_list.end());
	full_chemical_plant_recipes.insert(full_chemical_plant_recipes.end(), chemical_plant_extra_list.begin(), chemical_plant_extra_list.end());

	all_recipes.insert(all_recipes.end(), full_assembly_recipes.begin(), full_assembly_recipes.end());
	all_recipes.insert(all_recipes.end(), centrifuge_list.begin(), centrifuge_list.end());
	all_recipes.insert(all_recipes.end(), full_chemical_plant_recipes.begin(), full_chemical_plant_recipes.end());
	all_recipes.insert(all_recipes.end(), oil_refinery_list.begin(), oil_refinery_list.end());

	for (auto s : all_recipes) {
		recipe_choices.Add(s);
	}

	all_items.insert(all_items.end(), handcrafted_list.begin(), handcrafted_list.end());
	all_items.insert(all_items.end(), assemply_level1_list.begin(), assemply_level1_list.end());
	all_items.insert(all_items.end(), assemply_level2_list.begin(), assemply_level2_list.end());
	all_items.insert(all_items.end(), chemical_plant_list.begin(), chemical_plant_list.end());
	all_items.insert(all_items.end(), filter_take_put_drop_extra_list.begin(), filter_take_put_drop_extra_list.end());
	all_items.insert(all_items.end(), raw_resource_list.begin(), raw_resource_list.end());
	all_items.insert(all_items.end(), furnace_list.begin(), furnace_list.end());

	for (auto it = building_size_list.begin(); it != building_size_list.end(); ++it) {
		all_buildings.push_back(it->first);
	}

	for (auto s : all_items) {
		item_choices.Add(s);
	}

	for (auto s : all_buildings) {
		building_choices.Add(s);
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
	
	for (auto s : input_output) {
		input_output_choices.Add(s);
	}

	for (auto s : handcrafted_list) {
		handcrafted_choices.Add(s);
	}

	// set walk as default value and disable inputs not used
	rbtn_walk->SetValue(true);
	setup_paramters(parameter_choices.walk);

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
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
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

	cmb_input->Clear();
	for (auto it = input_output.begin(); it < input_output.end(); it++) {
		cmb_input->Append(*it);
	}
	cmb_input->SetValue(*input_output.begin());
	cmb_input->AutoComplete(input_output_choices);

	cmb_output->Clear();
	for (auto it = input_output.begin(); it < input_output.end(); it++) {
		cmb_output->Append(*it);
	}
	cmb_output->SetValue(*input_output.begin());
	cmb_output->AutoComplete(input_output_choices);

	// set tasks grid formatting
	grid_tasks->SetColFormatFloat(1, 4, 1);
	grid_tasks->SetColFormatFloat(2, 4, 1);
	grid_tasks->SetColFormatFloat(3, 4, 2);
	grid_tasks->SetSelectionMode(grid_tasks->wxGridSelectRows);

	// set buildings grid formatting
	grid_buildings->SetColFormatFloat(0, 4, 1);
	grid_buildings->SetColFormatFloat(1, 4, 1);
	grid_buildings->SetSelectionMode(grid_buildings->wxGridSelectRows);

	// set group grid formatting
	grid_group->SetColFormatFloat(1, 4, 1);
	grid_group->SetColFormatFloat(2, 4, 1);
	grid_group->SetColFormatFloat(3, 4, 2);
	grid_group->SetSelectionMode(grid_group->wxGridSelectRows);

	// set group grid formatting
	grid_template->SetColFormatFloat(1, 4, 1);
	grid_template->SetColFormatFloat(2, 4, 1);
	grid_template->SetColFormatFloat(3, 4, 2);
	grid_template->SetSelectionMode(grid_group->wxGridSelectRows);

	// Checking steel axe as a goal
	menu_goals->GetMenuItems()[0]->Check();

	// disabling Change shortcuts
	menu_shortcuts->GetMenuItems()[0]->Enable(false);
}


void cMain::OnWalkChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.walk);
	event.Skip();
}

void cMain::OnMineChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.mining);
	event.Skip();
}

void cMain::OnGameSpeedChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.game_speed);
	event.Skip();
}

void cMain::OnBuildChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.build);

	cmb_item->Clear();
	for (auto it = all_buildings.begin(); it < all_buildings.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_buildings.begin());
	cmb_item->AutoComplete(building_choices);

	event.Skip();
}

void cMain::OnTakeChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.take);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	cmb_from_into->SetValue("Output"); // set default to output on take task

	event.Skip();
}

void cMain::OnPutChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.put);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	cmb_from_into->SetValue("Input"); // set default to input on put task

	event.Skip();
}

void cMain::OnCraftChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.craft);

	cmb_item->Clear();
	for (auto it = handcrafted_list.begin(); it < handcrafted_list.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*handcrafted_list.begin());
	cmb_item->AutoComplete(handcrafted_choices);

	event.Skip();
}

void cMain::OnRotateChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.rotate);
	event.Skip();
}

void cMain::OnfilterChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.filter);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	event.Skip();
}

void cMain::OnRecipeChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.recipe);

	cmb_item->Clear();
	for (auto it = all_recipes.begin(); it < all_recipes.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_recipes.begin());
	cmb_item->AutoComplete(recipe_choices);

	event.Skip();
}

void cMain::OnTechChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.tech);
	event.Skip();
}

void cMain::OnLaunchChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.launch);
	event.Skip();
}

void cMain::OnSaveChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.save);
	event.Skip();
}

void cMain::OnPriorityChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.priority);
	event.Skip();
}

void cMain::OnLimitChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.limit);
	event.Skip();
}

void cMain::OnIdleChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.idle);
	event.Skip();
}

void cMain::OnPickUpChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.pick);
	event.Skip();
}

void cMain::OnDropChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.drop);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	event.Skip();
}

void cMain::OnStartChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.Start);
	rbtn_start->SetValue(true);
	event.Skip();
}

void cMain::OnPauseChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.Pause);
	rbtn_pause->SetValue(true);
	event.Skip();
}

void cMain::OnStopChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.stop);
	rbtn_stop->SetValue(true);
	event.Skip();
}

void cMain::reset_to_new_window() {
	if (grid_tasks->GetNumberRows() > 0 || grid_buildings->GetNumberRows() > 0 || grid_group->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0) {
		if (grid_tasks->GetNumberRows() > 0) {
			grid_tasks->DeleteRows(0, grid_tasks->GetNumberRows());
		}

		if (grid_buildings->GetNumberRows() > 0) {
			grid_buildings->DeleteRows(0, grid_buildings->GetNumberRows());
		}

		if (grid_group->GetNumberRows() > 0) {
			grid_group->DeleteRows(0, grid_group->GetNumberRows());
		}

		if (grid_template->GetNumberRows() > 0) {
			grid_template->DeleteRows(0, grid_template->GetNumberRows());
		}
	}

	rbtn_walk->SetValue(true);
	setup_paramters(parameter_choices.walk);

	group_name = "";
	group_map.clear();
	cmb_choose_group->Clear();
	group_list = {};
	group_choices = {};

	template_name = "";
	template_map.clear();
	cmb_choose_template->Clear();
	template_list = {};
	template_choices = {};

	tasks_data_to_save = {};
	save_file_location = "";
	generate_code_folder_location = "";

	if (dialog_progress_bar) {
		dialog_progress_bar->Hide();
	}

	SetLabel(window_title);
}

bool cMain::check_before_close() {
	if (grid_tasks->GetNumberRows() > 0 || grid_buildings->GetNumberRows() > 0 || grid_group->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0) {
		int answer = wxMessageBox("Do you want to save your changes?", "Ensure that you have saved what you need", wxICON_QUESTION | wxYES_NO | wxCANCEL, this);

		if (answer == wxYES) {
			if (save_file(false)) {
				return true;
			} else {
				return false;
			}

		} else if (answer == wxNO) {
			return true;
		}
	} else {
		return true;
	}

	return false;
}

void cMain::move_row(wxGrid* grid, bool up) {
	if (!grid->IsSelection() || !grid->GetSelectedRows().begin()) {
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	for (const auto& block : grid->GetSelectedRowBlocks()) {
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		if (up) {
			if (row_num == 0) {
				continue;
			}

			row_to_move = row_num - 1;

			grid_extract_parameters(row_to_move, grid);

			grid->InsertRows(row_num + row_count);

			grid_insert_data(row_num + row_count, grid);

			background_colour_update(grid, row_num + row_count, grid->GetCellValue(row_num + row_count, 0).ToStdString());

			grid->DeleteRows(row_to_move);

			it1 = tasks_data_to_save.begin();
			it1 += row_to_move;

			data = *it1;
			tasks_data_to_save.erase(it1);

			it2 = tasks_data_to_save.begin();
			it2 += row_num + row_count - 1;

			tasks_data_to_save.insert(it2, data);

		} else {
			if ( (row_num + row_count) == (grid->GetNumberRows()) ) {
				continue;
			}

			row_to_move = row_num + row_count;

			grid_extract_parameters(row_to_move, grid);
			
			grid->DeleteRows(row_to_move);

			grid->InsertRows(row_num);

			grid_insert_data(row_num, grid);

			background_colour_update(grid, row_num, grid->GetCellValue(row_num, 0).ToStdString());

			it1 = tasks_data_to_save.begin();
			it1 += row_to_move;

			it2 = tasks_data_to_save.begin();
			it2 += row_num;

			data = *it1;
			tasks_data_to_save.erase(it1);
			tasks_data_to_save.insert(it2, data);
		}
	}

	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());
}

void cMain::group_template_move_row(wxGrid* grid, wxComboBox* cmb, bool up, std::map<std::string, std::vector<std::string>>& map) {
	if (!grid->IsSelection() || !grid->GetSelectedRows().begin()) {
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	for (const auto& block : grid->GetSelectedRowBlocks()) {
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		if (up) {
			if (row_num == 0) {
				continue;
			}

			row_to_move = row_num - 1;

		} else {
			if ((row_num + row_count) == (grid->GetNumberRows())) {
				continue;
			}

			row_to_move = row_num + row_count + 1;
			row_count = 0;
		}

		grid->InsertRows(row_num + row_count);

		grid_extract_parameters(row_to_move, grid);

		grid_insert_data(row_num + row_count, grid);

		background_colour_update(grid, row_num + row_count, grid->GetCellValue(row_num + row_count, 0).ToStdString());

		grid->DeleteRows(row_to_move);

		if (!map.empty()) {
			std::string map_name = cmb->GetValue().ToStdString();
			if (map.find(map_name) != map.end()) {
				if (up) {

					it1 = map[map_name].begin();
					it1 += row_to_move;

					data = *it1;
					map[map_name].erase(it1);

					it2 = map[map_name].begin();
					it2 += row_num + row_count - 1;
					map[map_name].insert(it2, data);
				} else {
					it1 = map[map_name].begin();
					it1 += row_to_move - 1;

					it2 = map[map_name].begin();
					it2 += row_num;

					data = *it1;
					map[map_name].erase(it1, it1 + 1);
					map[map_name].insert(it2, data);
				}
			}
		}
	}
}

// ensure that you are not deleting rows, which you are not supposed to if the user has ctrl + clicked multiple blocks of tasks
bool cMain::delete_row(wxGrid* grid, wxComboBox* cmb, std::map<std::string, std::vector<std::string>>& map) {
	if (!grid->IsSelection()) {
		wxMessageBox("Please select row(s) to be deleted", "Selection not valid");
		return false;
	}

	row_selections.clear();

	for (const auto& block : grid->GetSelectedRowBlocks()) {
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		row_selections.push_back(std::to_string(block.GetTopRow()) + "," + std::to_string(block.GetBottomRow() - block.GetTopRow() + 1));
	}

	building_row_count = 0;

	for (auto selection : row_selections) {
		long long pos = selection.find(",");

		row_num = std::stoi(selection.substr(0, pos)) - building_row_count;
		row_count = std::stoi(selection.substr(pos + 1));

		grid->DeleteRows(row_num, row_count);
		
		if (!map.empty()) {
			std::string map_name = cmb->GetValue().ToStdString();

			if (map.find(map_name) != map.end()) {
				it1 = map[map_name].begin();
				it2 = map[map_name].begin();

				it1 += row_num;
				it2 += row_num + row_count;

				map[map_name].erase(it1, it2);
			}
		}

		building_row_count += row_count;
	}	

	return true;
}

// ensure that the variables are actually what they are supposed to be
bool cMain::change_row(wxGrid* grid) {
	if (!grid->IsSelection() || !grid->GetSelectedRows().begin()) {
		wxMessageBox("Please select a row to change", "Selection not valid");
		return false;
	}

	row_num = *grid->GetSelectedRows().begin();

	setup_for_task_group_template_grid();

	grid_insert_data(row_num, grid);

	background_colour_update(grid, row_num, task);

	return true;
}

void cMain::background_colour_update(wxGrid* grid, int row, std::string task) {
	if (task == "Start") {
		grid->SetCellBackgroundColour(row, 0, *wxGREEN);
		return;
	}

	if (task == "Game Speed" || task == "Pause" || task == "Save") {
		grid->SetCellBackgroundColour(row, 0, *wxYELLOW);
		return;
	}

	if (task == "Stop") {
		grid->SetCellBackgroundColour(row, 0, *wxRED);
		return;
	}

	if (task == "Build") {
		grid->SetCellBackgroundColour(row, 0, *wxCYAN);
		return;
	}

	if (task == "Craft") {
		grid->SetCellBackgroundColour(row, 0, *wxLIGHT_GREY);
		return;
	}

	grid->SetCellBackgroundColour(row, 0, *wxWHITE);
}

// ensure that the variables are actually what they are supposed to be
void cMain::update_tasks_grid() {

	if (grid_tasks->IsSelection()) {
		if (!grid_tasks->GetSelectedRows().begin()) {
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
	grid_tasks->SetCellValue(row_num, 5, build_orientation);
	grid_tasks->SetCellValue(row_num, 6, direction_to_build);
	grid_tasks->SetCellValue(row_num, 7, building_size);
	grid_tasks->SetCellValue(row_num, 8, amount_of_buildings);
	grid_tasks->SetCellValue(row_num, 9, comment);

	if (grid_tasks->IsSelection()) {
		it1 = tasks_data_to_save.begin();
		it1 += row_num;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	} else {
		tasks_data_to_save.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	}
	
	background_colour_update(grid_tasks, row_num, task);
}

// Ensure that the variables are actually what they are supposed to be and have not been altered by side functions
void cMain::update_buildings_grid() {
	building_row_num = grid_buildings->GetNumberRows();

	grid_buildings->InsertRows(building_row_num, 1);

	grid_buildings->SetCellValue(building_row_num, 0, building_x_cord);
	grid_buildings->SetCellValue(building_row_num, 1, building_y_cord);
	grid_buildings->SetCellValue(building_row_num, 2, building_item);
	grid_buildings->SetCellValue(building_row_num, 3, building_build_orientation);
	grid_buildings->SetCellValue(building_row_num, 4, limit);
	grid_buildings->SetCellValue(building_row_num, 5, recipe);
	grid_buildings->SetCellValue(building_row_num, 6, building_priority_in);
	grid_buildings->SetCellValue(building_row_num, 7, building_priority_out);
	grid_buildings->SetCellValue(building_row_num, 8, filter);
}

// Check that the variables found here are not used by functions calling this function
void cMain::update_buildings_grid_from_scratch(int start_row, int end_row) {
	if (start_row == 0 && grid_buildings->GetNumberRows() > 0) {
		grid_buildings->DeleteRows(0, grid_buildings->GetNumberRows());
	}

	for (int i = start_row; i < end_row; i++) {
		In_memory_extract_parameters_buildings(tasks_data_to_save[i]);
		task_number = std::to_string(i + 1);

		if (building_task == "Build" ) {
			update_buildings();

		} else if (building_task == "Recipe") {
			if (!update_recipe()) {
				wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
				return;
			}
			

		} else if (building_task == "Limit") {
			if (!update_limit()) {
				wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
				return;
			}

		} else if (building_task == "Priority") {
			long long pos = building_build_orientation.find(",");

			building_priority_in = building_build_orientation.substr(0, pos);
			building_priority_out = building_build_orientation.substr(pos + 2);

			if (!update_priority()) {
				wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
				return;
			}

		} else if (building_task == "Filter") {
			if (!update_filter()) {
				wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
				return;
			}

		} else if (building_task == "Rotate") {

			if (grid_buildings->GetNumberRows() == 0) {
				wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
				return;
			}

			for (int j = 0; j < grid_buildings->GetNumberRows(); j++) {
				if (grid_buildings->GetCellValue(j, 0).ToStdString() == building_x_cord && grid_buildings->GetCellValue(j, 1).ToStdString() == building_y_cord) {
					grid_buildings->SetCellValue(j, 3, building_build_orientation);
					break;
				}

				if (j == grid_buildings->GetNumberRows()) {
					wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
					return;
				}
			}

		} else if (building_task == "Mine") {
			if (find_building(1)) {
				grid_buildings->DeleteRows(building_row_num);
			}
		} else if (building_task == "Take" || building_task == "Put") {
			if (building_build_orientation != "Wreck") {
				building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
				for (int j = 0; j < building_amount_of_buildings_int; j++) {

					if (!find_building(building_amount_of_buildings_int)) {
						wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
						return;
					}

					find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
				}
			}
		}
	}
}

void cMain::update_buildings() {
	limit = "";
	recipe = "";
	building_priority_in = "";
	building_priority_out = "";
	filter = "";

	update_buildings_grid();

	int amount_of_buildings = std::stoi(building_amount_of_buildings);
	for (int i = 1; i < amount_of_buildings; i++) {
		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
		update_buildings_grid();
	}
}

bool cMain::update_recipe() {
	building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
	for (int i = 0; i < building_amount_of_buildings_int; i++) {
		if (find_building(building_amount_of_buildings_int)) {
			grid_buildings->SetCellValue(building_row_num, 5, building_item);
		} else {
			return false;
		}

		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
	}

	return true;
}

bool cMain::update_limit() {
	building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
	for (int i = 0; i < std::stoi(building_amount_of_buildings); i++) {
		if (find_building(building_amount_of_buildings_int)) {
			grid_buildings->SetCellValue(building_row_num, 4, building_units);
		} else {
			return false;
		}

		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
	}
	return true;
}

bool cMain::update_priority() {
	building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
	for (int i = 0; i < building_amount_of_buildings_int; i++) {
		if (find_building(building_amount_of_buildings_int)) {
			grid_buildings->SetCellValue(building_row_num, 6, building_priority_in);
			grid_buildings->SetCellValue(building_row_num, 7, building_priority_out);
		} else {
			return false;
		}

		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
	}

	return true;
}

bool cMain::update_filter() {
	building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
	for (int i = 0; i < building_amount_of_buildings_int; i++) {
		if (find_building(building_amount_of_buildings_int)) {
			grid_buildings->SetCellValue(building_row_num, 8, building_item);
		} else {
			return false;
		}

		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
	}

	return true;
}

bool cMain::Update_rotation() {
	if (find_building(1)) {
		building_build_orientation = grid_buildings->GetCellValue(building_row_num, 5);

		find_new_orientation();

		grid_buildings->SetCellValue(building_row_num, 3, building_build_orientation);

		return true;
	}

	return false;
}

void cMain::update_group_template_grid(wxGrid* grid, std::vector<std::string>& list, std::map<std::string, std::vector<std::string>>& map, std::string map_name) {
	if (grid->GetNumberRows() > 0) {
		grid->DeleteRows(0, grid->GetNumberRows());
	}

	list = map[map_name];
	grid->InsertRows(0, list.size());

	for (unsigned int i = 0; i < list.size(); i++) {
		std::stringstream data_line;
		data_line.str(list[i]);
		seglist = {};

		while (std::getline(data_line, segment, ';')) {
			seglist.push_back(segment);
		}

		grid->SetCellValue(i, 0, seglist[0]);
		grid->SetCellValue(i, 1, seglist[1]);
		grid->SetCellValue(i, 2, seglist[2]);
		grid->SetCellValue(i, 3, seglist[3]);
		grid->SetCellValue(i, 4, seglist[4]);
		grid->SetCellValue(i, 5, seglist[5]);
		grid->SetCellValue(i, 6, seglist[6]);
		grid->SetCellValue(i, 7, seglist[7]);
		grid->SetCellValue(i, 8, seglist[8]);

		if (seglist.size() > 9) {
			grid->SetCellValue(i, 9, seglist[9]);
		}

		background_colour_update(grid, i, seglist[0]);
	}
}

// You have chosen not to implement a check to see if there are already a building at the location, given that it would open for a lot of concerns about fast replaceing buildings 
void cMain::OnAddTaskClicked(wxCommandEvent& event) {
	if (grid_tasks->IsSelection()) {
		if (!grid_tasks->GetSelectedRows().begin()) {
			return;
		}
		row_num = *grid_tasks->GetSelectedRows().begin();
	} else {
		row_num = grid_tasks->GetNumberRows();
	}

	extract_parameters();
	mine_building_found = false;

	if (task == "Mine" || task == "Recipe" || task == "Build" || task == "Limit" || task == "Priority" || task == "Filter" || task == "Rotate" || task == "Put" || task == "Take" || task == "Launch") {
		if (row_num != grid_tasks->GetNumberRows()) {
			update_buildings_grid_from_scratch(0, row_num);
		}
		
		building_task = task;
		building_x_cord = x_cord;
		building_y_cord = y_cord;
		building_units = units;
		building_item = item;
		building_build_orientation = build_orientation;
		building_direction_to_build = direction_to_build;
		building_building_size = building_size;
		building_amount_of_buildings = amount_of_buildings;
		building_priority_in = priority_in;
		building_priority_out = priority_out;
		building_comment = comment;

		if (check_buildings_grid()) {
			if (setup_for_task_group_template_grid()) {

				update_tasks_grid();

				std::string base_units = "1";
				std::string to_check = item;
				string_capitalized(to_check);

				if (task == struct_tasks_list.build) {
					if (check_furnace->IsChecked() && to_check == struct_auto_put_furnace_list.stone || to_check == struct_auto_put_furnace_list.steel) {
						auto_put(struct_fuel_list.coal, base_units, struct_from_into_list.fuel);
					}

					if (check_burner->IsChecked() && to_check == struct_auto_put_burner_list.burner_mining_drill || to_check == struct_auto_put_burner_list.burner_inserter || to_check == struct_auto_put_burner_list.boiler) {
						auto_put(struct_fuel_list.coal, base_units, struct_from_into_list.fuel);
					}

					if (check_lab->IsChecked() && to_check == struct_science_list.lab) {
						auto_put(struct_science_list.red_science, base_units, struct_from_into_list.input);
					}
				}

				if (task == struct_tasks_list.recipe && check_recipe->IsChecked() ) {
					std::vector<std::string> recipe = recipes.find(to_check)->second;

					for (int i = 0; i < recipe.size(); i += 2 ) {
						auto_put(recipe[i], recipe[i + 1], struct_from_into_list.input);
					}
				}
			}
		} else {
			if (row_num != grid_tasks->GetNumberRows()) {
				update_buildings_grid_from_scratch(row_num, grid_tasks->GetNumberRows());
			}

			event.Skip();
			return;
		}

		if (row_num != grid_tasks->GetNumberRows()) {
			update_buildings_grid_from_scratch(row_num + 1, grid_tasks->GetNumberRows());
		}
	} else {
		if (setup_for_task_group_template_grid()) {
			update_tasks_grid();
		}
	}

	event.Skip();
}

// It has been chosen to not make massive checks when a task is changed, given that it would be very complicated
void cMain::OnChangeTaskClicked(wxCommandEvent& event) {
	extract_parameters();

	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin()) {
		wxMessageBox("Please select a row to change", "Selection not valid");
		event.Skip();
		return;
	}
	
	row_num = *grid_tasks->GetSelectedRows().begin();

	// setup buildingsgrid and ensure the building exists
	if (task == "Mine" || task == "Recipe" || task == "Build" || task == "Limit" || task == "Priority" || task == "Filter" || task == "Rotate" || task == "Put" || task == "Take" || task == "Launch") {
		if (row_num != grid_tasks->GetNumberRows()) {
			update_buildings_grid_from_scratch(0, row_num);
		}

		building_task = task;
		building_x_cord = x_cord;
		building_y_cord = y_cord;
		building_units = units;
		building_comment = comment;
		building_item = item;
		building_build_orientation = build_orientation;
		building_direction_to_build = direction_to_build;
		building_building_size = building_size;
		building_amount_of_buildings = amount_of_buildings;
		building_priority_in = priority_in;
		building_priority_out = priority_out;

		if (!check_buildings_grid() || !setup_for_task_group_template_grid()) {
			if (row_num != grid_tasks->GetNumberRows()) {
				update_buildings_grid_from_scratch(row_num, grid_tasks->GetNumberRows());
			}

			event.Skip();
			return;
		}
	}

	if (task == "Build" && grid_tasks->GetCellValue(row_num, 0) == "Build") {
		std::string saved_x_cord = x_cord;
		std::string saved_y_cord = y_cord;

		building_x_cord = grid_tasks->GetCellValue(row_num, 1);
		building_y_cord = grid_tasks->GetCellValue(row_num, 2);
		building_direction_to_build = grid_tasks->GetCellValue(row_num, 6);
		building_building_size = grid_tasks->GetCellValue(row_num, 7);
		building_comment = grid_tasks->GetCellValue(row_num, 9);

		int total_rows = grid_tasks->GetNumberRows();
		std::vector<int> changed_rows = {};

		building_amount_of_buildings = std::to_string(std::min(std::stoi(amount_of_buildings), wxAtoi(grid_tasks->GetCellValue(row_num, 8))));

		for (int i = 0; i < std::stoi(building_amount_of_buildings); i++) {
			for (int j = row_num + 1; j < total_rows; j++) {
				if (grid_tasks->GetCellValue(j, 1) == building_x_cord && grid_tasks->GetCellValue(j, 2) == building_y_cord) {
					if (grid_tasks->GetCellValue(j, 0) == "Mine") {
						break;
					}
					if (std::find(changed_rows.begin(), changed_rows.end(), j) == changed_rows.end()) {
						grid_tasks->SetCellValue(j, 1, x_cord);
						grid_tasks->SetCellValue(j, 2, y_cord);
						changed_rows.push_back(j);

						tasks_data_to_save[j] = (grid_tasks->GetCellValue(j, 0) + ";" + grid_tasks->GetCellValue(j, 1) + ";" + grid_tasks->GetCellValue(j, 2) + ";" + grid_tasks->GetCellValue(j, 3) + ";" + grid_tasks->GetCellValue(j, 4) + ";" + grid_tasks->GetCellValue(j, 5) + ";" + grid_tasks->GetCellValue(j, 6) + ";" + grid_tasks->GetCellValue(j, 7) + ";" + grid_tasks->GetCellValue(j, 8) + ";" + grid_tasks->GetCellValue(j, 9) + ";");
					}
				}
			}

			find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
			find_coordinates(x_cord, y_cord, direction_to_build, building_size);
		}

		x_cord = saved_x_cord;
		y_cord = saved_y_cord;
	}

	change_row(grid_tasks);
	tasks_data_to_save[row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());

	event.Skip();
}

void cMain::OnDeleteTaskClicked(wxCommandEvent& event) {
	if (!grid_tasks->IsSelection()) {
		wxMessageBox("Please select row(s) to be deleted", "Selection not valid");
		return;
	}

	if (wxMessageBox("Are you sure you want to delete this task?", "Delete task", wxICON_QUESTION | wxYES_NO, this) != wxYES) {
		return;
	}

	int counter = 1;
	
	row_selections.clear();

	// Find the first block of rows selected - extract the first row and the amount of rows in the block
	for (const auto& block : grid_tasks->GetSelectedRowBlocks()) {
		if (counter == 1) {
			building_row_num = block.GetTopRow();
			building_row_count = block.GetBottomRow() - building_row_num + 1;

			counter++;
		} else {			
			row_selections.push_back(std::to_string(block.GetTopRow()) + "," + std::to_string(block.GetBottomRow() - block.GetTopRow() + 1));
		}
	}

	// If the last row of the block is also the tasks_grid's last row then the rows are just deleted
	if ((building_row_num + building_row_count) == grid_tasks->GetNumberRows()) {
		grid_tasks->DeleteRows(building_row_num, building_row_count);

	} else {
		// Otherwise the rows are run through to see if at least one of the tasks is a build task
		for (int i = building_row_num; i < (building_row_num + building_row_count); i++) {
			building_task = grid_tasks->GetCellValue(i, 0).ToStdString();

			if (building_task == "Build") {
				if (wxMessageBox("At least one of the rows selected is a build task - are you sure you want to delete the rows selected?\nAll future tasks associated with the building(s) will be removed to avoid issues.", "The build task(s) you are deleting could be associated with future tasks", wxICON_QUESTION | wxYES_NO, this) != wxYES) {
					return;
				} else {
					break;
				}
			}
		}

		// The rows are run through, if there are no build tasks or the user gives permission to delete the build tasks
		int total_rows = building_row_num + building_row_count;
		int main_lines_deleted = 0;
		
		for (int i = building_row_num; i < total_rows; i++) {
			building_task = grid_tasks->GetCellValue(i, 0).ToStdString();

			if (building_task == "Build") {
				building_x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
				building_y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
				building_direction_to_build = grid_tasks->GetCellValue(i, 6).ToStdString();
				building_building_size = grid_tasks->GetCellValue(i, 7).ToStdString();
				building_amount_of_buildings = grid_tasks->GetCellValue(i, 8).ToStdString();

				// The current row is a build task and each building of the task are run through to check for associated tasks 
				for (int j = 0; j < std::stoi(building_amount_of_buildings); j++) {
					int total_rows_inner = grid_tasks->GetNumberRows();

					// All of the future tasks on the tasks grid are run through
					for (int k = (building_row_num + building_row_count - main_lines_deleted); k < total_rows_inner; k++) {
						if (grid_tasks->GetCellValue(k, 1).ToStdString() == building_x_cord && grid_tasks->GetCellValue(k, 2).ToStdString() == building_y_cord) {
							if (grid_tasks->GetCellValue(k, 0).ToStdString() == "Mine" || grid_tasks->GetCellValue(k, 0).ToStdString() == "Build") {
								break;
							}

							grid_tasks->DeleteRows(k);
							it1 = tasks_data_to_save.begin();
							it1 += k + main_lines_deleted;
							tasks_data_to_save.erase(it1);

							k--;
							total_rows_inner--;
						} else if (grid_tasks->GetCellValue(k, 0).ToStdString() == "Build") {
							if (wxAtoi(grid_tasks->GetCellValue(k, 8)) > 1) {
								x_cord = grid_tasks->GetCellValue(k, 1).ToStdString();
								y_cord = grid_tasks->GetCellValue(k, 2).ToStdString();
								direction_to_build = grid_tasks->GetCellValue(k, 6).ToStdString();
								building_size = grid_tasks->GetCellValue(k, 7).ToStdString();
								amount_of_buildings = grid_tasks->GetCellValue(k, 8).ToStdString();

								for (int l = 1; l < std::stoi(amount_of_buildings); l++) {
									find_coordinates(x_cord, y_cord, direction_to_build, building_size);
									if (x_cord == building_x_cord && y_cord == building_y_cord) {
										k = total_rows_inner;
										break;
									}
								}
							}
						}							
					}

					find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
				}

			} else if (building_task == "Rotate") {
				x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();;
				y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();;
				building = grid_tasks->GetCellValue(i, 4).ToStdString();
				building_build_orientation = grid_tasks->GetCellValue(i, 5).ToStdString();
				row_num = i;

				update_future_rotate_tasks();
			} 

			grid_tasks->DeleteRows(i);
			i--;
			total_rows--;
			main_lines_deleted++;
		}
	}

	// The row after the deleted row(s) are selected if there were no other row blocks selected
	if (counter == 1) {
		grid_tasks->SelectRow(building_row_num);
	} else {
	// Otherwise the other selections are selected once more
		grid_tasks->ClearSelection();
		for (auto selection : row_selections) {
			long long pos = selection.find(",");

			row_num = std::stoi(selection.substr(0, pos)) - building_row_count;
			row_count = std::stoi(selection.substr(pos + 1));

			int total_rows = row_num + row_count;

			for (int i = row_num; i < total_rows; i++) {
				grid_tasks->SelectRow(i, true);
			}
		}
	}

	it1 = tasks_data_to_save.begin();
	it2 = tasks_data_to_save.begin();

	it1 += building_row_num;
	it2 += building_row_num + building_row_count;

	tasks_data_to_save.erase(it1, it2);

	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());

	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnMoveUpClicked(wxCommandEvent& event) {
	move_row(grid_tasks, true);

	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnMoveDownClicked(wxCommandEvent& event) {
	move_row(grid_tasks, false);

	event.Skip();
}

void cMain::OnTasksGridDoubleLeftClick(wxGridEvent& event) {
	row_num = event.GetRow();

	update_parameters(grid_tasks, event);

	event.Skip();
}

void cMain::OnNewGroupClicked(wxCommandEvent& event) {

	group_row_count = cmb_choose_group->GetCount();
	group_name = cmb_choose_group->GetValue().ToStdString();

	if (group_name == "") {
		wxMessageBox("Please write a group name", "Group name cannot be blank");
		event.Skip();
		return;
	}

	for (int i = 0; i < group_row_count; i++) {
		if (group_name == cmb_choose_group->GetString(i).ToStdString()) {
			wxMessageBox("Group names have to be unique - please write a new name in the Choose Group field", "Group names should be unique");
			event.Skip();
			return;
		}
	}

	if (grid_group->IsSelection() && !grid_group->GetSelectedRows().begin()) {
		wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
		event.Skip();
		return;
	}

	cmb_choose_group->Clear();
	group_choices.Add(group_name);
	cmb_choose_group->Append(group_choices);
	cmb_choose_group->SetValue(group_name);
	group_list = {};

	if (grid_group->IsSelection()) {
		group_row_num = *grid_group->GetSelectedRows().begin();
		group_row_count = grid_group->GetSelectedRows().GetCount();
	} else {
		group_row_num = 0;
		group_row_count = grid_group->GetNumberRows();

		if (!group_row_count) {
			group_map.insert(std::pair<std::string, std::vector<std::string>>(group_name, group_list));
			event.Skip();
			return;
		}
	}

	for (int i = group_row_num; i < (group_row_num + group_row_count); i++) {
		grid_extract_parameters(i, grid_group);

		group_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	
		background_colour_update(grid_group, i, task);
	}
	
	group_map.insert(std::pair<std::string, std::vector<std::string>> (group_name, group_list));

	update_group_template_grid(grid_group, group_list, group_map, group_name);

	event.Skip();
}

void cMain::OnDeleteGroupClicked(wxCommandEvent& event) {
	if (wxMessageBox("Are you sure you want to delete this group?", "Delete group", wxICON_QUESTION | wxYES_NO, this) != wxYES) {
		return;
	}

	group_name = cmb_choose_group->GetValue();

	if (group_map.find(group_name) != group_map.end()) {
		group_map.erase(group_name);
		group_choices.Remove(group_name);
		cmb_choose_group->Clear();
		cmb_choose_group->Append(group_choices);

		if (group_choices.size()) {
			cmb_choose_group->SetValue(*group_choices.begin());
			OnGroupChosen(event);
		} else if (grid_group->GetNumberRows()) {
			grid_group->DeleteRows(0, grid_group->GetNumberRows());
		}
	}

	event.Skip();
}

void cMain::OnGroupAddFromTasksListClicked(wxCommandEvent& event) {
	if (!grid_tasks->IsSelection()) {
		wxMessageBox("No task is chosen - please select row(s) in the task list", "Cannot add task to group");
		event.Skip();
		return;
	}

	if (grid_group->IsSelection()) {
		if (!grid_group->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
			event.Skip();
			return;
		}
		group_row_num = *grid_group->GetSelectedRows().begin();
	} else {
		group_row_num = grid_group->GetNumberRows();
	}

	for (const auto& block : grid_tasks->GetSelectedRowBlocks()) {
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		grid_group->InsertRows(group_row_num, row_count);

		int total_rows = row_num + row_count;

		for (int i = row_num; i < total_rows; i++) {

			grid_extract_parameters(i, grid_tasks);

			grid_insert_data(group_row_num, grid_group);

			background_colour_update(grid_group, group_row_num, grid_tasks->GetCellValue(i, 0).ToStdString());

			group_row_num += 1;
		}
	}

	if (group_map.find(cmb_choose_group->GetValue().ToStdString()) != group_map.end()) {
		update_group_map();
	}
}

// You have chosen to exclude the checks normally made when adding a task to the task list, given the increased complexity of handling multiple tasks at once
void cMain::OnGroupAddToTasksListClicked(wxCommandEvent& event) {
	if (grid_tasks->IsSelection()) {
		if (!grid_tasks->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Task list selection not valid");
		} else {
			row_num = *grid_tasks->GetSelectedRows().begin();
		}

	} else {
		row_num = grid_tasks->GetNumberRows();
	}

	bool check = false;

	for (const auto& block : grid_group->GetSelectedRowBlocks()) {
		group_row_num = block.GetTopRow();
		group_row_count = block.GetBottomRow() - group_row_num + 1;

		grid_tasks->InsertRows(row_num, group_row_count);

		int total_rows = group_row_num + group_row_count;

		for (int i = group_row_num; i < total_rows; i++) {

			grid_extract_parameters(i, grid_group);

			grid_insert_data(row_num, grid_tasks);

			it1 = tasks_data_to_save.begin();
			it1 += row_num;

			tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

			background_colour_update(grid_tasks, row_num, task);

			row_num +=1;

			check = true;
		}		
	}

	if (check) {
		update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());
		event.Skip();
		return;
	}

	group_row_count = grid_group->GetNumberRows();
	grid_tasks->InsertRows(row_num, group_row_count);

	for (int i = 0; i < group_row_count; i++) {

		grid_extract_parameters(i, grid_group);

		grid_insert_data(row_num, grid_tasks);

		it1 = tasks_data_to_save.begin();
		it1 += row_num;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
		
		background_colour_update(grid_tasks, row_num, task);

		row_num += 1;
	}
	
	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());

	event.Skip();
}

void cMain::In_memory_extract_parameters(const std::string& task_reference) {
	split_task(task_reference);

	task = task_segments[0];
	x_cord = task_segments[1];
	y_cord = task_segments[2];
	units = task_segments[3];
	item = task_segments[4];
	build_orientation = task_segments[5];
	direction_to_build = task_segments[6];
	building_size = task_segments[7];
	amount_of_buildings = task_segments[8];
	comment = task_segments[9];
}

void cMain::In_memory_extract_parameters_buildings(const std::string& task_reference) {
	split_task(task_reference);

	building_task = task_segments[0];
	building_x_cord = task_segments[1];
	building_y_cord = task_segments[2];
	building_units = task_segments[3];
	building_item = task_segments[4];
	building_build_orientation = task_segments[5];
	building_direction_to_build = task_segments[6];
	building_building_size = task_segments[7];
	building_amount_of_buildings = task_segments[8];
	building_comment = task_segments[9];
}

void cMain::split_task(const std::string& task_reference) {

	std::stringstream data_line;
	data_line.str(task_reference);

	task_segments = {};

	while (std::getline(data_line, segment, ';')) {
		task_segments.push_back(segment);
	}
}

void cMain::grid_extract_parameters(const int &row, wxGrid* grid) {
	task = grid->GetCellValue(row, 0).ToStdString();
	x_cord = grid->GetCellValue(row, 1).ToStdString();
	y_cord = grid->GetCellValue(row, 2).ToStdString();
	units = grid->GetCellValue(row, 3).ToStdString();
	item = grid->GetCellValue(row, 4).ToStdString();
	build_orientation = grid->GetCellValue(row, 5).ToStdString();
	direction_to_build = grid->GetCellValue(row, 6).ToStdString();
	building_size = grid->GetCellValue(row, 7).ToStdString();
	amount_of_buildings = grid->GetCellValue(row, 8).ToStdString();
	comment = grid->GetCellValue(row, 9).ToStdString();
}

void cMain::grid_insert_data(const int& row, wxGrid* grid) {
	grid->SetCellValue(row, 0, task);
	grid->SetCellValue(row, 1, x_cord);
	grid->SetCellValue(row, 2, y_cord);
	grid->SetCellValue(row, 3, units);
	grid->SetCellValue(row, 4, item);
	grid->SetCellValue(row, 5, build_orientation);
	grid->SetCellValue(row, 6, direction_to_build);
	grid->SetCellValue(row, 7, building_size);
	grid->SetCellValue(row, 8, amount_of_buildings);
	grid->SetCellValue(row, 9, comment);
}	

// You have chosen to exclude the checks normally made when adding a task to the task list, given the increased complexity of handling multiple tasks at once
void cMain::OnGroupChangeClicked(wxCommandEvent& event) {
	extract_parameters();

	if (setup_for_task_group_template_grid()) {
		change_row(grid_group);

		group_name = cmb_choose_group->GetValue().ToStdString();

		if (!(group_map.find(group_name) == group_map.end())) {
			group_map[group_name][row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
		}
	}

	event.Skip();
}

void cMain::OnGroupDeleteClicked(wxCommandEvent& event) {
	if (wxMessageBox("Are you sure you want to delete this group task?", "Delete group task", wxICON_QUESTION | wxYES_NO, this) != wxYES) {
		return;
	}

	delete_row(grid_group, cmb_choose_group, group_map);

	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnGroupMoveUpClicked(wxCommandEvent& event) {
	group_template_move_row(grid_group, cmb_choose_group, true, group_map);

	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnGroupMoveDownClicked(wxCommandEvent& event) {
	group_template_move_row(grid_group, cmb_choose_group, false, group_map);

	event.Skip();
}

void cMain::OnGroupGridDoubleLeftClick(wxGridEvent& event) {
	row_num = event.GetRow();

	update_parameters(grid_group, event);

	event.Skip();
}

void cMain::OnGroupChosen(wxCommandEvent& event) {
	group_name = cmb_choose_group->GetValue();
	update_group_template_grid(grid_group, group_list, group_map, group_name);;

	event.Skip();
}

void cMain::OnTemplateChosen(wxCommandEvent& event) {
	template_name = cmb_choose_template->GetValue();
	update_group_template_grid(grid_template, template_list, template_map, template_name);

	event.Skip();
}

void cMain::OnNewTemplateClicked(wxCommandEvent& event) {
	row_count = cmb_choose_template->GetCount();
	template_name = cmb_choose_template->GetValue().ToStdString();

	if (template_name == "") {
		wxMessageBox("Please write a template name", "Template name cannot be blank");
		event.Skip();
		return;
	}

	for (int i = 0; i < row_count; i++) {
		if (template_name == cmb_choose_template->GetString(i).ToStdString()) {
			wxMessageBox("Template names have to be unique - please write a new name in the Choose Template field", "Template names should be unique");
			event.Skip();
			return;
		}
	}

	if (grid_template->IsSelection() && !grid_template->GetSelectedRows().begin()) {
		wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
		event.Skip();
		return;
	}

	cmb_choose_template->Clear();
	template_choices.Add(template_name);
	cmb_choose_template->Append(template_choices);
	cmb_choose_template->SetValue(template_name);
	template_list = {};

	if (grid_template->IsSelection()) {
		
		row_num = *grid_template->GetSelectedRows().begin();
		row_count = grid_template->GetSelectedRows().GetCount();
	} else {
		row_count = grid_template->GetNumberRows();

		if (row_count) {
			row_num = 0;
		} else {
			template_map.insert(std::pair<std::string, std::vector<std::string>>(template_name, template_list));
			event.Skip();
			return;
		}
	}

	for (int i = row_num; i < row_num + row_count; i++) {
		grid_extract_parameters(i, grid_template);

		template_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	}

	template_map.insert(std::pair<std::string, std::vector<std::string>>(template_name, template_list));

	update_group_template_grid(grid_template, template_list, template_map, template_name);

	event.Skip();
}

void cMain::OnDeleteTemplateClicked(wxCommandEvent& event) {
	if (wxMessageBox("Are you sure you want to delete this template?", "Delete template", wxICON_QUESTION | wxYES_NO, this) != wxYES) {
		event.Skip();
		return;
	}

	template_name = cmb_choose_template->GetValue();
	
	if (template_map.find(template_name) != template_map.end()) {
		template_map.erase(template_name);
		template_choices.Remove(template_name);
		cmb_choose_template->Clear();
		cmb_choose_template->Append(template_choices);

		if (template_choices.size()) {
			cmb_choose_template->SetValue(*template_choices.begin());
			OnTemplateChosen(event);
		} else if (grid_template->GetNumberRows()){
			grid_template->DeleteRows(0, grid_template->GetNumberRows());
		}
	}

	event.Skip();
}

void cMain::OnTemplateAddFromTasksListClicked(wxCommandEvent& event) {
	if (!grid_tasks->IsSelection()) {
		wxMessageBox("No task is chosen - please select a row in the task list", "Cannot add task to group");
		event.Skip();
		return;
	}

	if (grid_template->IsSelection()) {
		if (!grid_template->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
			event.Skip();
			return;
		}
		template_row_num = *grid_template->GetSelectedRows().begin();
	} else {
		template_row_num = grid_template->GetNumberRows();
	}

	for (const auto& block : grid_tasks->GetSelectedRowBlocks()) {
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		grid_template->InsertRows(template_row_num, row_count);

		int total_rows = row_num + row_count;

		for (int i = row_num; i < total_rows; i++) {

			grid_extract_parameters(i, grid_tasks);

			if (grid_tasks->GetCellValue(i, 1).ToStdString() != "") {
				x_cord = std::to_string(std::stof(x_cord) + wxAtof(txt_template_x_offset->GetValue()));
				y_cord = std::to_string(std::stof(y_cord) + wxAtof(txt_template_y_offset->GetValue()));
			} 

			grid_insert_data(template_row_num, grid_template);

			background_colour_update(grid_template, template_row_num, grid_tasks->GetCellValue(i, 0).ToStdString());

			template_row_num += 1;
		}
	}

	if (!(template_map.find(cmb_choose_template->GetValue().ToStdString()) == template_map.end())) {
		update_template_map();
	}

	event.Skip();
}

// You have chosen to exclude the checks normally made when adding a task to the task list, given the increased complexity of handling multiple tasks at once
void cMain::OnTemplateAddToTasksListClicked(wxCommandEvent& event) {
	if (!grid_tasks->IsSelection()) {
		row_num = grid_tasks->GetNumberRows();
	} else {
		if (!grid_tasks->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Task list selection not valid");
		} else {
			row_num = *grid_tasks->GetSelectedRows().begin();
		}
	}

	bool check = false;

	for (const auto& block : grid_template->GetSelectedRowBlocks()) {
		template_row_num = block.GetTopRow();
		template_row_count = block.GetBottomRow() - template_row_num + 1;

		grid_tasks->InsertRows(row_num, template_row_count);

		int total_rows = template_row_num + template_row_count;

		for (int i = template_row_num; i < total_rows; i++) {
			grid_extract_parameters(i, grid_template);

			if (x_cord != "" || y_cord != "") {
				x_cord = std::to_string(std::stof(x_cord) + wxAtof(txt_template_x_offset->GetValue()));
				y_cord = std::to_string(std::stof(y_cord) + wxAtof(txt_template_y_offset->GetValue()));
			}

			grid_insert_data(row_num, grid_tasks);

			background_colour_update(grid_tasks, row_num, task);

			it1 = tasks_data_to_save.begin();
			it1 += row_num;

			check = true;

			tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
		
			row_num += 1;
		}
	}

	if (check) {
		update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());
		event.Skip();
		return;
	}

	template_row_count = grid_template->GetNumberRows();

	grid_tasks->InsertRows(row_num, template_row_count);

	for (int i = 0; i < template_row_count; i++) {
		
		grid_extract_parameters(i, grid_template);

		if (x_cord != "" || y_cord != "") {
			x_cord = std::to_string(std::stof(x_cord) + wxAtof(txt_template_x_offset->GetValue()));
			y_cord = std::to_string(std::stof(y_cord) + wxAtof(txt_template_y_offset->GetValue()));
		} 	

		grid_insert_data(row_num, grid_tasks);

		background_colour_update(grid_tasks, row_num, task);

		it1 = tasks_data_to_save.begin();
		it1 += row_num;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	
		row_num += 1;
	}

	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());

	event.Skip();
}

void cMain::OnTemplateChangeTaskClicked(wxCommandEvent& event) {
	extract_parameters();

	if (setup_for_task_group_template_grid()) {
		change_row(grid_template);

		template_name = cmb_choose_template->GetValue().ToStdString();

		if (!(template_map.find(template_name) == template_map.end())) {
			template_map[template_name][row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
		}		
	}

	event.Skip();
}

void cMain::OnTemplateDeleteTaskClicked(wxCommandEvent& event) {
	if (wxMessageBox("Are you sure you want to delete this template task?", "Delete template task", wxICON_QUESTION | wxYES_NO, this) != wxYES) {
		return;
	}

	delete_row(grid_template, cmb_choose_template, template_map);

	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnTemplateMoveUpClicked(wxCommandEvent& event) {
	group_template_move_row(grid_template, cmb_choose_template, true, template_map);
	
	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnTemplateMoveDownClicked(wxCommandEvent& event) {
	group_template_move_row(grid_template, cmb_choose_template, false, template_map);

	event.Skip();
}

void cMain::OnTemplateGridDoubleLeftClick(wxGridEvent& event) {
	row_num = event.GetRow();

	update_parameters(grid_template, event);

	event.Skip();
}

void cMain::OnBuildingsGridLeftDoubleClick(wxGridEvent& event) {
	row_num = event.GetRow();

	txt_x_cord->SetValue(grid_buildings->GetCellValue(row_num, 0).ToStdString());
	txt_y_cord->SetValue(grid_buildings->GetCellValue(row_num, 1).ToStdString());
	cmb_item->SetValue(grid_buildings->GetCellValue(row_num, 2).ToStdString());
	cmb_building_orientation->SetValue(grid_buildings->GetCellValue(row_num, 3).ToStdString());
	txt_units->SetValue(grid_buildings->GetCellValue(row_num, 4).ToStdString());
	cmb_input->SetValue(grid_buildings->GetCellValue(row_num, 6).ToStdString());
	cmb_output->SetValue(grid_buildings->GetCellValue(row_num, 7).ToStdString());

	event.Skip();
}

void cMain::OnApplicationClose(wxCloseEvent& event) {
	if (check_before_close()) { // You do not want to skip the event if the application shouldn't be closed
		if (shortcuts) {
			delete shortcuts;
		}

		if (dialog_progress_bar) {
			delete dialog_progress_bar;
		}

		event.Skip();
	}
}

bool cMain::checks_before_reset_window() {
	if (grid_tasks->GetNumberRows() > 0 || grid_buildings->GetNumberRows() > 0 || grid_group->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0) {
		return true;
	}

	if (group_map.size() > 0 || template_map.size() > 0) {
		return true;
	}

	return false;
}

void cMain::OnMenuNew(wxCommandEvent& event) {

	if (checks_before_reset_window()) {
		if (wxMessageBox("Are you sure you want to reset the window?\nAll in the current window will be cleared.", "Ensure that you have saved what you need before clicking yes", wxICON_QUESTION | wxYES_NO, this) == wxYES) {
			reset_to_new_window();
		}
	}

	event.Skip();
}

void cMain::OnMenuOpen(wxCommandEvent& event) {
	
	wxFileDialog dlg(this, "Open saved file", "", "", ".txt files (*.txt) | *.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (dlg.ShowModal() == wxID_OK) {
		std::ifstream inFile;
#pragma warning(suppress : 4996)
		std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
		inFile.imbue(utf8_locale);
		inFile.open(dlg.GetPath().ToStdString());
		
		bool total_tasks_reached = false;
		bool goal_reached = false;
		bool tasks_reached = false;
		bool groups_reached = false;
		bool templates_reached = false;
		bool save_file_reached = false;
		bool task_file_reached = false;
		bool generate_code_folder_reached = false;
		bool auto_close_reached = false;
		bool auto_put_reached = false;

		bool groups_in_file = false;
		bool templates_in_file = false;

		int total_lines = 0;
		int lines_processed = 0;

		if (!inFile) {
			wxMessageBox("It was not possible to open the file", "A file error occurred");
			return;
		}

		if (checks_before_reset_window()) {
			if (wxMessageBox("Are you sure you want to open this file?\nAll in the current window will be cleared.", "Ensure that you have saved what you need before clicking yes", wxICON_QUESTION | wxYES_NO, this) == wxYES) {
				reset_to_new_window();
			} else { 
				return;
			}
		}

		if (!dialog_progress_bar) {
			dialog_progress_bar = new dialog_progress_bar_base(this, wxID_ANY, "Processing request");
		}

		dialog_progress_bar->set_text("Opening file");
		dialog_progress_bar->set_button_enable(false);
		dialog_progress_bar->set_progress(0);
		dialog_progress_bar->Show();

		while (std::getline(inFile, open_data_string)) {
			std::stringstream data_line;
			data_line.str(open_data_string);

			seglist = {};

			while (std::getline(data_line, segment, ';')) {
				seglist.push_back(segment);
			}

			if (!total_tasks_reached){
				if (seglist[0] == total_tasks_indicator) {
					total_tasks_reached = true;
				} else {
					malformed_saved_file_message();
					return;
				}
			
			} else if (seglist[0] == goal_indicator) {
				goal_reached = true;

			} else if (seglist[0] == tasks_indicator) {
				tasks_reached = true;

			} else if (seglist[0] == save_groups_indicator) {
				groups_reached = true;

			} else if (seglist[0] == save_templates_indicator) {
				groups_reached = true;
				templates_reached = true;

			} else if (seglist[0] == save_file_indicator) {
				groups_reached = true;
				templates_reached = true;
				save_file_reached = true;
			
			} else if (seglist[0] == code_file_indicator) {
				groups_reached = true;
				templates_reached = true;
				save_file_reached = true;
				task_file_reached = true;
			
			} else if (seglist[0] == auto_close_indicator) {
				groups_reached = true;
				templates_reached = true;
				save_file_reached = true;
				task_file_reached = true;
				generate_code_folder_reached = true;

			} else if (seglist[0] == auto_put_indicator) {
				groups_reached = true;
				templates_reached = true;
				save_file_reached = true;
				task_file_reached = true;
				generate_code_folder_reached = true;
				auto_close_reached = true;

			} else if (!goal_reached) {
				if (seglist.size() == 1) {
					if (is_number(seglist[0])){
						total_lines = std::stoi(seglist[0]);
					} else {
						malformed_saved_file_message();
						return;
					}

					
				} else {
					malformed_saved_file_message();
					return;
				}				

			} else if (!tasks_reached) {
				if (seglist.size() == 1) {
					if (seglist[0] == goal_steelaxe_text) {
						menu_goals->GetMenuItems()[0]->Check();
					} else if (seglist[0] == goal_GOTLAP_text) {
						menu_goals->GetMenuItems()[1]->Check();
					} else if (seglist[0] == goal_any_percent_text) {
						menu_goals->GetMenuItems()[2]->Check();
					} else if (seglist[0] == goal_debug_text) {
						menu_goals->GetMenuItems()[3]->Check();
					} else {
						malformed_saved_file_message();
						return;
					}

				} else {
					malformed_saved_file_message();
					return;
				}

			} else if (!groups_reached) {
				tasks_data_to_save.reserve(total_lines * 2);

				if (seglist.size() == 9 || seglist.size() == 10) {
					task = seglist[0];
					x_cord = seglist[1];
					y_cord = seglist[2];
					units = seglist[3];
					item = seglist[4];
					build_orientation = seglist[5];
					direction_to_build = seglist[6];
					building_size = seglist[7];
					amount_of_buildings = seglist[8];

					if (seglist.size() > 9) {
						comment = seglist[9];
					} else {
						comment = "";
					}

					// Needed to fix a misalignment between previous version and the actual name in game.
					if (item == "Long handed inserter") {
						item = "Long-handed inserter";
					}

					tasks_data_to_save.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

					lines_processed++;

					if (lines_processed > 0 && lines_processed % 25 == 0) {
						dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 5);
						wxYield();
					}

				} else {
					malformed_saved_file_message();
					return;
				}
			} else if (!templates_reached) {
				groups_in_file = true;

				if (seglist.size() == 10 || seglist.size() == 11) {

					if (group_name == "") {
						group_name = seglist[0];
						cmb_choose_group->SetValue(seglist[0]);
						group_choices.Add(group_name);

						group_list = {};

					} else if (group_name != seglist[0]) {
						group_map.insert(std::pair<std::string, std::vector<std::string>>(group_name, group_list));

						group_name = seglist[0];
						group_choices.Add(group_name);
						group_list = {};
					}

					task = seglist[1];
					x_cord = seglist[2];
					y_cord = seglist[3];
					units = seglist[4];
					item = seglist[5];
					build_orientation = seglist[6];
					direction_to_build = seglist[7];
					building_size = seglist[8];
					amount_of_buildings = seglist[9];

					if (seglist.size() > 10) {
						comment = seglist[10];
					} else {
						comment = "";
					}

					group_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
				
					lines_processed++;

					if (lines_processed > 0 && lines_processed % 25 == 0) {
						dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 5);
						wxYield();
					}
				
				} else {
					malformed_saved_file_message();
					return;
				}
			} else if (!save_file_reached) {
				if (seglist.size() == 10 || seglist.size() == 11) {
					templates_in_file = true;
					
					if (template_name == "") {
						template_name = seglist[0];
						cmb_choose_template->SetValue(seglist[0]);
						template_choices.Add(template_name);
						template_list = {};

					} else if (template_name != seglist[0]) {
						template_map.insert(std::pair<std::string, std::vector<std::string>>(template_name, template_list));

						template_name = seglist[0];
						template_choices.Add(template_name);
						template_list = {};
					}

					task = seglist[1];
					x_cord = seglist[2];
					y_cord = seglist[3];
					units = seglist[4];
					item = seglist[5];
					build_orientation = seglist[6];
					direction_to_build = seglist[7];
					building_size = seglist[8];
					amount_of_buildings = seglist[9];

					if (seglist.size() > 10) {
						comment = seglist[10];
					} else {
						comment = "";
					}

					template_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
				
					lines_processed++;

					if (lines_processed > 0 && lines_processed % 25 == 0) {
						dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 5);
						wxYield();
					}

				} else {
					malformed_saved_file_message();
					return;
				}
				
			} else if (!task_file_reached) {
				save_file_location = seglist[0];

			} else if (!generate_code_folder_reached) {
				generate_code_folder_location = seglist[0];

			} else if (!auto_close_reached) {
				if (seglist.size() == 2) {
					if (seglist[0] == auto_close_generate_script_text) {
						menu_auto_close->GetMenuItems()[0]->Check(seglist[1] == "true");
						auto_close_generate_script = seglist[1] == "true";

					} else if (seglist[0] == auto_close_open_text) {
						menu_auto_close->GetMenuItems()[1]->Check(seglist[1] == "true");
						auto_close_open = seglist[1] == "true";

					} else if (seglist[0] == auto_close_save_text) {
						menu_auto_close->GetMenuItems()[2]->Check(seglist[1] == "true");
						auto_close_save = seglist[1] == "true";

					} else if (seglist[0] == auto_close_save_as_text) {
						menu_auto_close->GetMenuItems()[3]->Check(seglist[1] == "true");
						auto_close_save_as = seglist[1] == "true";

					} else {
						malformed_saved_file_message();
						return;
					}
				} else {
					malformed_saved_file_message();
					return;
				}
			} else if (!auto_put_reached) {
				if (seglist.size() == 2) {
					if (seglist[0] == auto_put_furnace_text) {
						check_furnace->SetValue(seglist[1] == "true");

					} else if (seglist[0] == auto_put_burner_text) {
						check_burner->SetValue(seglist[1] == "true");

					} else if (seglist[0] == auto_put_lab_text) {
						check_lab->SetValue(seglist[1] == "true");

					} else if (seglist[0] == auto_put_recipe_text) {
						check_recipe->SetValue(seglist[1] == "true");

					} else {
						malformed_saved_file_message();
						return;
					}
				} else {
					malformed_saved_file_message();
					return;
				}
			}
		}

		populate_tasks_grid();

		if (groups_in_file) {
			group_map.insert(std::pair<std::string, std::vector<std::string>>(group_name, group_list));
			cmb_choose_group->Clear();
			cmb_choose_group->Append(group_choices);

			if (group_choices.size()) {
				cmb_choose_group->SetValue(*group_choices.begin());
				OnGroupChosen(event);
			}
		}
		
		if (templates_in_file) {
			template_map.insert(std::pair<std::string, std::vector<std::string>>(template_name, template_list));
			cmb_choose_template->Clear();
			cmb_choose_template->Append(template_choices);
			
			if (template_choices.size()) {
				cmb_choose_template->SetValue(*template_choices.begin());
				OnTemplateChosen(event);
			}
		}

		inFile.close();

		std::string file_name = save_file_location.substr(save_file_location.rfind("\\") + 1);

		SetLabel(window_title + " - " + file_name);

		update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());

		dialog_progress_bar->set_progress(100);
		if (auto_close_open) {
			dialog_progress_bar->Close();
		}
		else {
			dialog_progress_bar->set_button_enable(true);
		}
	}

	event.Skip();
}

void cMain::populate_tasks_grid() {
	if (grid_tasks->GetNumberRows() > 0) {
		grid_tasks->DeleteRows(0, grid_tasks->GetNumberRows());
	}

	size_t amount_of_tasks = tasks_data_to_save.size();

	grid_tasks->InsertRows(0, amount_of_tasks);

	for (unsigned int i = 0; i < amount_of_tasks; i++) {
		std::stringstream data_line;
		data_line.str(tasks_data_to_save[i]);
		seglist = {};

		while (std::getline(data_line, segment, ';')) {
			seglist.push_back(segment);
		}

		grid_tasks->SetCellValue(i, 0, seglist[0]);
		grid_tasks->SetCellValue(i, 1, seglist[1]);
		grid_tasks->SetCellValue(i, 2, seglist[2]);
		grid_tasks->SetCellValue(i, 3, seglist[3]);
		grid_tasks->SetCellValue(i, 4, seglist[4]);
		grid_tasks->SetCellValue(i, 5, seglist[5]);
		grid_tasks->SetCellValue(i, 6, seglist[6]);
		grid_tasks->SetCellValue(i, 7, seglist[7]);
		grid_tasks->SetCellValue(i, 8, seglist[8]);
		grid_tasks->SetCellValue(i, 9, seglist[9]);

		background_colour_update(grid_tasks, i, seglist[0]);
	}
}

void cMain::OnMenuSave(wxCommandEvent& event) {

	save_file(false);

	event.Skip();
}

void cMain::OnMenuSaveAs(wxCommandEvent& event) {

	save_file(true);

	event.Skip();
}

void cMain::OnMenuExit(wxCommandEvent& event) { 
	wxCloseEvent close_event;
	OnApplicationClose(close_event);

	event.Skip();
	Close();
}

void cMain::OnChooseLocation(wxCommandEvent& event) {
	wxDirDialog dlg(NULL, "Choose location to generate script", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

	if (dlg.ShowModal() == wxID_OK) {
		generate_code_folder_location = dlg.GetPath().ToStdString();
	}

	event.Skip();
}

void cMain::OnGenerateScript(wxCommandEvent& event) {
	if (generate_code_folder_location == "") {
		wxDirDialog dlg(NULL, "Choose location to generate script", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

		if (dlg.ShowModal() == wxID_OK) {
			generate_code_folder_location = dlg.GetPath().ToStdString();
		} else {
			return;
		}
	}

	clear_tasks();
	reset_coordinates();

	if (!dialog_progress_bar) {
		dialog_progress_bar = new dialog_progress_bar_base(this, wxID_ANY, "Processing request");
	}

	dialog_progress_bar->set_text("Generating Script");
	dialog_progress_bar->set_button_enable(false);
	dialog_progress_bar->set_progress(0);
	dialog_progress_bar->Show();

	size_t amount_of_tasks = tasks_data_to_save.size();

	for (int i = 0; i < amount_of_tasks; i++) {
		
		if (i > 2937) {
			int test = 1;
		}

		In_memory_extract_parameters(tasks_data_to_save[i]);

		if (task == "Start") {
			clear_tasks();
		}

		task_number = std::to_string(i + 1);

		if (i > 0 && i % 25 == 0) {
			dialog_progress_bar->set_progress(static_cast<float>(i) / static_cast<float>(amount_of_tasks) * 100.0f - 1);
			wxYield();
		}

		if (task == "Game Speed") {
			speed(task_number, units);
			continue;
		}
		
		if (task == "Walk") {
			walk(task_number, "1", x_cord, y_cord);
			continue;
		}
		
		if (task == "Mine") {
			if (units == "All") {
				units = "1000";
			}

			if (find_building_for_script(i)) {
				mining(task_number, x_cord, y_cord, units, building, build_orientation, true);
			} else {
				mining(task_number, x_cord, y_cord, units, "", "", false);
			}

			continue;
		}
		
		if (task == "Rotate") {
			if (!find_building_for_script(i)) {
				return;
			}

			rotate(task_number, x_cord, y_cord, units, item, build_orientation);
			continue;
		}
		
		if (task == "Craft") {
			if (units == "All") {
				craft(task_number, "-1", item);
			} else {
				craft(task_number, units, item);
			}

			continue;
		}
		
		if (task == "Tech") {
			tech(task_number, item);
			continue;
		}
		
		if (task == "Build") {
			row_build(task_number, x_cord, y_cord, item, build_orientation, direction_to_build, amount_of_buildings, building_size);
			continue;
		}
		
		if (task == "Take") {
			from_into = convert_string(build_orientation);
			from_into = extract_define(i);

			if (from_into == "Not Found") {
				return;
			}

			if (units == "All") {
				row_take(task_number, x_cord, y_cord, "-1", item, from_into, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			} else {
				row_take(task_number, x_cord, y_cord, units, item, from_into, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			}

			continue;
		}
		
		if (task == "Put") {
			from_into = convert_string(build_orientation);
			from_into = extract_define(i);

			if (from_into == "Not Found") {
				return;
			}

			if (units == "All") {
				row_put(task_number, x_cord, y_cord, "-1", item, from_into, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			} else {
				row_put(task_number, x_cord, y_cord, units, item, from_into, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			}

			continue;
		}
		
		if (task == "Recipe") {
			if (!find_building_for_script(i)) {
				return;
			}

			row_recipe(task_number, x_cord, y_cord, item, direction_to_build, building_size, amount_of_buildings, building, build_orientation);
			continue;
		}

		if (task == "Pause") {
			pause(task_number);
			continue;
		}
		
		if (task == "Stop") {
			stop(task_number, units);
			continue;
		}
		
		if (task == "Limit") {
			from_into = convert_string(build_orientation);
			from_into = extract_define(i);

			if (from_into == "Not Found") {
				return;
			}

			row_limit(task_number, x_cord, y_cord, units, from_into, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			continue;
		}
		
		if (task == "Priority") {
			long long pos = build_orientation.find(",");

			priority_in = build_orientation.substr(0, pos);
			priority_out = build_orientation.substr(pos + 2);
			
			if (!find_building_for_script(i)) {
				return;
			}

			row_priority(task_number, x_cord, y_cord, priority_in, priority_out, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			continue;
		}
		
		if (task == "Filter") {
			if (!find_building_for_script(i)) {
				return;
			}

			if (check_input(building, splitter_list)) {
				row_filter(task_number, x_cord, y_cord, item, units, "splitter", direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			} else {
				row_filter(task_number, x_cord, y_cord, item, units, "inserter", direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			}

			continue;
		}
		
		if (task == "Drop") {
			row_drop(task_number, x_cord, y_cord, item, direction_to_build, amount_of_buildings, building_size);
			continue;

		}
		
		if (task == "Pick up") {
			row_pick(task_number, x_cord, y_cord, direction_to_build, amount_of_buildings, building_size);
			continue;

		}
		
		if (task == "Launch") {
			launch(task_number, x_cord, y_cord);
			continue;

		}
		
		if (task == "Save") {
			save(task_number, comment);
			continue;
		}

		if (task== "Idle") {
			idle(task_number, units);
			continue;
		}
	}

	// If the file is send to another person the folder location won't exist and should be set to something else. 
	try
	{
		std::ofstream saver;

		namespace fs = std::filesystem; // create folders if they don't exist
		fs::create_directories(generate_code_folder_location + "\\locale\\en");

		saver.open(generate_code_folder_location + "\\locale\\en\\locale.cfg"); //it doesn't need to be named locale but the path is important

		saver << locale;
		saver.close();

		if (!menu_script->GetMenuItems()[2]->IsChecked()) {
			saver.open(generate_code_folder_location + "\\control.lua");
			saver << control_lua1;
			saver << control_lua2;

			if (menu_goals->GetMenuItems()[0]->IsChecked()) {
				saver << control_steel_axe << std::endl;
			} else if (menu_goals->GetMenuItems()[1]->IsChecked()) {
				saver << control_GOTLAP << std::endl;
			} else if (menu_goals->GetMenuItems()[2]->IsChecked()) {
				saver << control_any_percent << std::endl;
			} else if (menu_goals->GetMenuItems()[3]->IsChecked()) {
				saver << control_debug << std::endl;
			}

			saver.close();

			saver.open(generate_code_folder_location + "\\info.json");
			saver << "\{\n\t\"name\": \"" + generate_code_folder_location.substr(generate_code_folder_location.rfind("\\") + 1) + "\",";
			saver << "\n\t\"version\": \"" << software_version << "\",";
			saver << "\n\t\"title\": \"" + generate_code_folder_location.substr(generate_code_folder_location.rfind("\\") + 1) + "\",";
			saver << info;
			saver.close();
		}

		saver.open(generate_code_folder_location + "\\steps.lua");

		saver << end_tasks();

		saver.close();

		saver.open(generate_code_folder_location + "\\settings.lua");
		saver << settings;
		saver.close();
	}
	catch (const std::exception&)
	{
		wxDirDialog dlg(NULL, "Choose location to generate script", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

		if (dlg.ShowModal() == wxID_OK) {
			generate_code_folder_location = dlg.GetPath().ToStdString();
		}
		else {
			return;
		}
	}

	dialog_progress_bar->set_progress(100);
	if (auto_close_generate_script) {
		dialog_progress_bar->Close();
	} else {
		dialog_progress_bar->set_button_enable(true);
	}

	event.Skip();
}

void cMain::OnChangeShortcuts(wxCommandEvent& event) {
	if (!shortcuts) {
		shortcuts = new Shortcuts_Menu(this);
	}

	shortcuts->Show();
	event.Skip();
}

void cMain::OnWalkMenuSelected(wxCommandEvent& event) {
	rbtn_walk->SetValue(true);
	OnWalkChosen(event);
	
	//// IMPORTANT -- This can be used to change the shortcuts of menuitems
	//wxAcceleratorEntry* plusAccel = new wxAcceleratorEntry(wxACCEL_CTRL, 50, wxID_ZOOM_IN);
	//menu_shortcuts->FindChildItem(10001)->SetAccel(plusAccel); // 10001 is the id of the menu item and can be set to what ever you want
	event.Skip();
}

void cMain::OnMineMenuSelected(wxCommandEvent& event) {
	rbtn_mine->SetValue(true);
	OnMineChosen(event);
	event.Skip();
}

void cMain::OnGameSpeedMenuSelected(wxCommandEvent& event) {
	rbtn_game_speed->SetValue(true);
	OnGameSpeedChosen(event);
	event.Skip();
}

void cMain::OnBuildMenuSelected(wxCommandEvent& event) {
	rbtn_build->SetValue(true);
	OnBuildChosen(event);
	event.Skip();
}

void cMain::OnTakeMenuSelected(wxCommandEvent& event) {
	rbtn_take->SetValue(true);
	OnTakeChosen(event);
	event.Skip();
}

void cMain::OnPutMenuSelected(wxCommandEvent& event) {
	rbtn_put->SetValue(true);
	OnPutChosen(event);
	event.Skip();
}

void cMain::OnCraftMenuSelected(wxCommandEvent& event) {
	rbtn_craft->SetValue(true);
	OnCraftChosen(event);
	event.Skip();
}

void cMain::OnRecipeMenuChosen(wxCommandEvent& event) {
	rbtn_recipe->SetValue(true);
	OnRecipeChosen(event);
	event.Skip();
}

void cMain::OnRotateMenuSelected(wxCommandEvent& event) {
	rbtn_rotate->SetValue(true);
	OnRotateChosen(event);
	event.Skip();
}

void cMain::OnTechMenuSelected(wxCommandEvent& event) {
	rbtn_tech->SetValue(true);
	OnTechChosen(event);
	event.Skip();
}

void cMain::OnPriorityMenuSelected(wxCommandEvent& event) {
	rbtn_priority->SetValue(true);
	OnPriorityChosen(event);
	event.Skip();
}

void cMain::OnLimitMenuSelected(wxCommandEvent& event) {
	rbtn_limit->SetValue(true);
	OnLimitChosen(event);
	event.Skip();
}

void cMain::OnFilterMenuSelected(wxCommandEvent& event) {
	rbtn_filter->SetValue(true);
	OnfilterChosen(event);
	event.Skip();
}

void cMain::OnStopMenuSelected(wxCommandEvent& event) {
	rbtn_stop->SetValue(true);
	OnStopChosen(event);
	event.Skip();
}

void cMain::OnIdleMenuSelected(wxCommandEvent& event) {
	rbtn_idle->SetValue(true);
	OnIdleChosen(event);
	event.Skip();
}

void cMain::OnLaunchMenuSelected(wxCommandEvent& event) {
	rbtn_launch->SetValue(true);
	OnLaunchChosen(event);
	event.Skip();
}

void cMain::OnDropMenuSelected(wxCommandEvent& event) {
	rbtn_drop->SetValue(true);
	OnDropChosen(event);
	event.Skip();
}

void cMain::OnPickUpMenuSelected(wxCommandEvent& event) {
	rbtn_pick_up->SetValue(true);
	OnPickUpChosen(event);
	event.Skip();
}

void cMain::OnSaveMenuSelected(wxCommandEvent& event) {
	rbtn_save->SetValue(true);
	OnSaveChosen(event);
	event.Skip();
}

void cMain::OnStartMenuSelected(wxCommandEvent& event) {
	rbtn_start->SetValue(true);
	OnStartChosen(event);
	event.Skip();
}

void cMain::OnPauseMenuSelected(wxCommandEvent& event) {
	rbtn_pause->SetValue(true);
	OnPauseChosen(event);
	event.Skip();
}

void cMain::OnMenuAutoCloseGenerateScriptClicked(wxCommandEvent& event) {
	auto_close_generate_script = menu_auto_close->GetMenuItems()[0]->IsChecked();
	event.Skip();
}

void cMain::OnMenuAutoCloseOpenClicked(wxCommandEvent& event) {
	auto_close_open = menu_auto_close->GetMenuItems()[1]->IsChecked();
	event.Skip();
}

void cMain::OnMenuAutoCloseSaveClicked(wxCommandEvent& event) {
	auto_close_save = menu_auto_close->GetMenuItems()[2]->IsChecked();

	event.Skip();
}

void cMain::OnMenuAutoCloseSaveAsClicked(wxCommandEvent& event) {
	auto_close_save_as = menu_auto_close->GetMenuItems()[3]->IsChecked();
	event.Skip();
}

void cMain::OnChangeMenuSelected(wxCommandEvent& event) {
	OnChangeTaskClicked(event);
	event.Skip();
}

void cMain::OnDeleteMenuSelected(wxCommandEvent& event) {
	OnDeleteTaskClicked(event);
	event.Skip();
}

void cMain::OnMoveUpMenuSelected(wxCommandEvent& event) {
	OnMoveUpClicked(event);
	event.Skip();
}

void cMain::OnMoveDownMenuSelected(wxCommandEvent& event) {
	OnMoveDownClicked(event);
	event.Skip();
}

void cMain::OnAddMenuSelected(wxCommandEvent& event) {
	OnAddTaskClicked(event);
	event.Skip();
}

void cMain::setup_paramters(std::vector<bool> parameters) {
	txt_x_cord->Enable(parameters[0]);
	txt_y_cord->Enable(parameters[1]);
	txt_units->Enable(parameters[2]);
	cmb_item->Enable(parameters[3]);
	cmb_from_into->Enable(parameters[4]);
	cmb_tech->Enable(parameters[5]);
	cmb_input->Enable(parameters[6]);
	cmb_output->Enable(parameters[7]);
	cmb_building_orientation->Enable(parameters[8]);
	cmb_direction_to_build->Enable(parameters[9]);
	txt_amount_of_buildings->Enable(parameters[10]);
	txt_building_size->Enable(parameters[11]);
}

bool cMain::setup_for_task_group_template_grid() {

	if (task == "Game Speed") {
		x_cord = not_relevant;
		y_cord = not_relevant;
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

	} else if (task == "Walk") {
		units = not_relevant;
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

	} else if (task == "Mine") {
		if (mine_building_found) {
			item = building;
		} else {
			item = not_relevant;
		}

		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

	} else if (task == "Rotate") {
		item = building;

		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;
	
	} else if (task == "Craft") {
		if (!check_input(item, handcrafted_list)) {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
			return false;
		}

		x_cord = not_relevant;
		y_cord = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;
		
	} else if (task == "Build") {
		if (!check_input(item, all_buildings)) {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
			return false;
		}

		if (!check_input(build_orientation, build_orientations)) {
			wxMessageBox("The build direction is not valid - please try again", "Please use the build direction dropdown menu");
			return false;
		}

		if (!check_input(direction_to_build, build_orientations)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return false;
		}
		
		units = not_relevant;

	} else if (task == "Take" || task == "Put") {
		if (!check_take_put(item)) {
			return false;
		}

		if (!check_input(direction_to_build, build_orientations)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return false;
		}

		build_orientation = from_into;

	} else if (task == "Tech") {
		if (!check_input(tech_to_start, tech_list)) {
			wxMessageBox("The tech is not valid - please try again", "Please use the tech dropdown menu");
			return false;
		}

		x_cord = not_relevant;
		y_cord = not_relevant;
		units = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

		item = tech_to_start;
	} else if (task == "Recipe") {
		if (building == "Assembling machine 1") {
			if (!check_input(item, part_assembly_recipes)) {
				wxMessageBox("The item chosen is not a valid recipe for an assembling machine 1", "Item chosen is not valid");
				return false;
			}
		} else if (building == "Assembling machine 2" || building == "Assembling machine 3") {
			if (!check_input(item, full_assembly_recipes)) {
				wxMessageBox("The item chosen is not a valid recipe for an assembling machine", "Item chosen is not valid");
				return false;
			}
		} else if (building == "Oil refinery") {
			if (!check_input(item, oil_refinery_list)) {
				wxMessageBox("The item chosen is not a valid recipe for an oil refinery", "Item chosen is not valid");
				return false;
			}
		} else if (building == "Chemical plant") {
			if (!check_input(item, full_chemical_plant_recipes)) {
				wxMessageBox("The item chosen is not a valid recipe for a chemical plant", "Item chosen is not valid");
				return false;
			}
		} else if (building == "Centrifuge") {
			if (!check_input(item, centrifuge_list)) {
				wxMessageBox("The item chosen is not a valid recipe for a centrifuge", "Item chosen is not valid");
				return false;
			}
		} else if (building == "Stone furnace" || building == "Steel furnace" || building == "Electric furnace") {
			if (!check_input(item, furnace_list)) { 
				wxMessageBox("The item chosen is not a valid recipe for a furnace", "Item chosen is not valid");
				return false;
			}
		}

		units = not_relevant;
		build_orientation = not_relevant;
	} else if (task == "Start") {
		x_cord = not_relevant;
		y_cord = not_relevant;
		units = not_relevant;
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

	} else if (task == "Pause") {
		x_cord = not_relevant;
		y_cord = not_relevant;
		units = not_relevant;
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

	} else if (task == "Stop") {
		x_cord = not_relevant;
		y_cord = not_relevant;
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

	} else if (task == "Limit") {
		item = not_relevant;
		build_orientation = "Chest";

	} else if (task == "Priority") {
		item = not_relevant;
		units = not_relevant;

		if (!check_input(priority_in, input_output)) {
			wxMessageBox("The input priority chosen is not valid - please try again", "Please use the input dropdown menu");
			return false;
		}

		if (!check_input(priority_out, input_output)) {
			wxMessageBox("The output priority chosen is not valid - please try again", "Please use the output dropdown menu");
			return false;
		}

		build_orientation = priority_in + ", " + priority_out;

	} else if (task == "Filter") {
		build_orientation = not_relevant;

	} else if (task == "Drop") {
		units = not_relevant;
		build_orientation = not_relevant;

	} else if (task == "Pick up") {
		units = not_relevant;
		item = not_relevant;
		build_orientation = not_relevant;

	} else if (task == "Launch") {
		units = not_relevant;
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

	} else if (task == "Save") {
		x_cord = not_relevant;
		y_cord = not_relevant;
		units = not_relevant;
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

	} else if (task == "Idle") {
		x_cord = not_relevant;
		y_cord = not_relevant;
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;
	}
	
	return true;
}


std::string FormatString(wxString s) {
	int i = s.size() - 1;
	if (i < 0) {
		return s.ToStdString();
	}

	if (i == 0) {
		return s.ToStdString() + ".0";
	}

	for (i; i > 0; i--) {
		if (s[i] == '.') {
			i += 2;
			break;
		}

		if (s[i] != '0') {
			i++;
			break;
		}
	}

	s.erase(i, s.size());

	return s.ToStdString();
}

void cMain::update_parameters(wxGrid* grid, wxCommandEvent& event) {
	grid_extract_parameters(row_num, grid);

	std::string x_cord_formatted = FormatString(x_cord);
	std::string y_cord_formatted = FormatString(y_cord);
	std::string units_formatted = FormatString(units);

	if (task == struct_tasks_list.game_speed) {
		OnGameSpeedMenuSelected(event);
		txt_units->SetValue(units_formatted);
		
		return;
	}
	
	if (task == struct_tasks_list.walk) {
		OnWalkMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		txt_comment->SetValue(comment);
		
		return;
	}
	
	if (task == struct_tasks_list.mine) {
		OnMineMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		txt_units->SetValue(units_formatted);
		txt_comment->SetValue(comment);

		return;
	}
	if (task == struct_tasks_list.rotate) {
		OnRotateMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		txt_units->SetValue(units_formatted);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.craft) {
		OnCraftMenuSelected(event);
		txt_units->SetValue(units_formatted);
		cmb_item->SetValue(item);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.build) {
		OnBuildMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		cmb_item->SetValue(item);
		cmb_building_orientation->SetValue(build_orientation);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.take) {
		OnTakeMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		txt_units->SetValue(units_formatted);
		cmb_item->SetValue(item);
		cmb_from_into->SetValue(build_orientation);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.put) {
		OnPutMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		txt_units->SetValue(units_formatted);
		cmb_item->SetValue(item);
		cmb_from_into->SetValue(build_orientation);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.tech) {
		OnTechMenuSelected(event);
		cmb_tech->SetValue(item);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.recipe) {
		OnRecipeMenuChosen(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
		cmb_item->SetValue(item);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.start) {
		OnStartMenuSelected(event);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.pause) {
		OnPauseMenuSelected(event);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.stop) {
		OnStopMenuSelected(event);
		txt_units->SetValue(units_formatted);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.limit) {
		OnLimitMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		txt_units->SetValue(units_formatted);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.priority) {
		OnPriorityMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);

		long long pos = build_orientation.find(",");

		cmb_input->SetValue(build_orientation.substr(0, pos));
		cmb_output->SetValue(build_orientation.substr(pos + 2));
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.filter) {
		OnFilterMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		txt_units->SetValue(units_formatted);
		cmb_item->SetValue(item);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.pick_up) {
		OnPickUpMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.drop) {
		OnDropMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		cmb_item->SetValue(item);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.idle) {
		OnIdleMenuSelected(event);
		txt_units->SetValue(units_formatted);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.launch) {
		OnLaunchMenuSelected(event);
		txt_x_cord->SetValue(x_cord_formatted);
		txt_y_cord->SetValue(y_cord_formatted);
		txt_comment->SetValue(comment);

		return;
	}
	
	if (task == struct_tasks_list.save) {
		OnSaveMenuSelected(event);
		txt_units->SetValue(units_formatted);
		txt_comment->SetValue(comment);
	}
}

void cMain::update_group_map() {
	group_list = {};
	row_num = grid_group->GetNumberRows();

	for (int i = 0; i < row_num; i++) {
		grid_extract_parameters(i, grid_group);

		group_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	}

	group_map[group_name] = group_list;
}

void cMain::update_template_map() {
	template_list = {};
	row_num = grid_template->GetNumberRows();

	for (int i = 0; i < row_num; i++) {
		grid_extract_parameters(i, grid_template);

		template_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	}

	template_map[template_name] = template_list;
}

void cMain::extract_parameters() {
	task = extract_task();
	x_cord = extract_x_cord();
	y_cord = extract_y_cord();
	units = extract_units();
	comment = extract_comment();
	item = extract_item();
	from_into = extract_from_into();
	tech_to_start = extract_tech();
	priority_in = extract_priority_in();
	priority_out = extract_priority_out();
	build_orientation = extract_building_orientation();
	direction_to_build = extract_direction_to_build();
	building_size = extract_building_size();
	amount_of_buildings = extract_amount_of_buildings();
}

std::string cMain::extract_task() {

	if (rbtn_game_speed->GetValue()) {
		return struct_tasks_list.game_speed;

	}
	
	if (rbtn_walk->GetValue()) {
		return struct_tasks_list.walk;

	}
	
	if (rbtn_mine->GetValue()) {
		return struct_tasks_list.mine;

	}
	
	if (rbtn_rotate->GetValue()) {
		return struct_tasks_list.rotate;

	}
	
	if (rbtn_craft->GetValue()) {
		return struct_tasks_list.craft;

	}
	
	if (rbtn_build->GetValue()) {
		return struct_tasks_list.build;

	}
	
	if (rbtn_take->GetValue()) {
		return struct_tasks_list.take;

	}
	
	if (rbtn_put->GetValue()) {
		return struct_tasks_list.put;

	}
	
	if (rbtn_tech->GetValue()) {
		return struct_tasks_list.tech;

	}
	
	if (rbtn_recipe->GetValue()) {
		return struct_tasks_list.recipe;

	}
	
	if (rbtn_limit->GetValue()) {
		return struct_tasks_list.limit;

	}
	
	if (rbtn_idle->GetValue()) {
		return struct_tasks_list.idle;

	}
	
	if (rbtn_filter->GetValue()) {
		return struct_tasks_list.filter;

	}
	
	if (rbtn_priority->GetValue()) {
		return struct_tasks_list.priority;

	}
	
	if (rbtn_pick_up->GetValue()) {
		return struct_tasks_list.pick_up;

	}
	
	if (rbtn_drop->GetValue()) {
		return struct_tasks_list.drop;

	}
	
	if (rbtn_launch->GetValue()) {
		return struct_tasks_list.launch;

	}

	if (rbtn_save->GetValue()) {
		return struct_tasks_list.save;
	}

	if (rbtn_start->GetValue()) {
		return struct_tasks_list.start;
	}

	if (rbtn_pause->GetValue()) {
		return struct_tasks_list.pause;
	}
	
	if (rbtn_stop->GetValue()) {
		return struct_tasks_list.stop;
	}

	return "not found";
}

std::string cMain::extract_x_cord() {
	return std::to_string(wxAtof(txt_x_cord->GetValue()));
}

std::string cMain::extract_y_cord() {
	return std::to_string(wxAtof(txt_y_cord->GetValue()));
}

std::string cMain::extract_units() {
	float units = wxAtof(txt_units->GetValue());
	
	if (units < 1 && (rbtn_rotate->GetValue() || rbtn_idle->GetValue())) {
		return "1";
	}
	
	if (units < 0 && rbtn_limit->GetValue()) {
		return "0";
	}
	
	if (rbtn_filter->GetValue()) {
		if (units < 1) {
			return "1";
		}
		
		if (units > 5) {
			return "5";
		}
	}

	if (rbtn_game_speed->GetValue() || rbtn_stop->GetValue()) {
		if (units < 0.01) {
			return "0.01";
		}

		return std::to_string(units);
	}

	if (units < 1) {
		return "All";
	}

	return std::to_string(units);
}

std::string cMain::extract_comment()
{
	return txt_comment->GetValue().ToStdString();
}

std::string cMain::extract_item() {
	return cmb_item->GetValue().ToStdString();
}

std::string cMain::extract_amount_of_buildings() {
	if (wxAtoi(txt_amount_of_buildings->GetValue()) < 1) {
		return "1";
	} 

	return std::to_string(wxAtoi(txt_amount_of_buildings->GetValue()));
}

void cMain::auto_put(std::string put_item, std::string put_units, std::string put_into)
{
	cmb_from_into->SetValue(put_into);

	task = struct_tasks_list.put;
	item = put_item;
	units = put_units;
	from_into = put_into;
	setup_for_task_group_template_grid();
	update_tasks_grid();
}

std::string cMain::extract_building_size() {
	if (wxAtoi(txt_building_size->GetValue()) < 1) {
		return "1";
	} 

	return std::to_string(wxAtoi(txt_building_size->GetValue()));
}

std::string cMain::extract_from_into() {
	return cmb_from_into->GetValue().ToStdString();
}

std::string cMain::extract_direction_to_build() {
	return cmb_direction_to_build->GetValue().ToStdString();
}

std::string cMain::extract_building_orientation() {
	return cmb_building_orientation->GetValue().ToStdString();
}

std::string cMain::extract_tech() {
	return cmb_tech->GetValue().ToStdString();
}

std::string cMain::extract_priority_in() {
	return cmb_input->GetValue().ToStdString();
}

std::string cMain::extract_priority_out() {
	return cmb_output->GetValue().ToStdString();
}

std::string cMain::extract_define(int start_row) {

	if (from_into == "wreck") {
		return take_put_list.chest;
	}

	if (find_building_for_script(start_row)) {
		if (from_into == "chest") {
			return take_put_list.chest;
		}

		if (from_into == "fuel") {
			return take_put_list.fuel;
		}

		if (building == "Lab") {
			if (from_into == "input") {
				return take_put_list.lab_input;
			} else if (from_into == "modules") {
				return take_put_list.lab_modules;
			}
		}

		if (check_input(building, drills_list)) {
			return take_put_list.drill_modules;
		}

		if (from_into == "input") {
			return take_put_list.assembly_input;
		}

		if (from_into == "modules") {
			return take_put_list.assembly_modules;
		}
		if (from_into == "output") {
			return take_put_list.assembly_output;
		}
	}

	return "Not Found";
}

void cMain::update_future_rotate_tasks() {
	int total_rows = grid_tasks->GetNumberRows();

	for (int i = row_num + 1; i < total_rows; i++) {

		if (grid_tasks->GetCellValue(i, 0).ToStdString() == "Rotate") {
			if (grid_tasks->GetCellValue(i, 1).ToStdString() == x_cord && grid_tasks->GetCellValue(i, 2).ToStdString() == y_cord && grid_tasks->GetCellValue(i, 4).ToStdString() == building) {				
				
				grid_extract_parameters(i, grid_tasks);

				find_new_orientation();

				grid_tasks->SetCellValue(i, 5, building_build_orientation);

				tasks_data_to_save[i] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + building_build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
			}
		}
	}
}

void cMain::find_new_orientation() {
	for (auto it = build_orientations.begin(); it < build_orientations.end(); it++) {
		if (building_build_orientation == *it) {
			building_build_orientation = build_orientations[((it - build_orientations.begin()) + std::stoi(units)) % 4];
			break;
		}
	}
}

bool cMain::find_building_for_script(int& row) {
	for (int i = row - 1; i > -1; i--) {
		if (compare_task_strings(grid_tasks->GetCellValue(i, 0), struct_tasks_list.build)) {
			split_task(tasks_data_to_save[i]);

			building_x_cord = task_segments[1];
			building_y_cord = task_segments[2];

			if (x_cord == building_x_cord && y_cord == building_y_cord) {
				building = task_segments[4];
				build_orientation = task_segments[5];

				return true;
			}

			building_direction_to_build = task_segments[6];
			building_building_size = task_segments[7];
			building_amount_of_buildings = task_segments[8];

			for (int j = 1; j < std::stoi(building_amount_of_buildings); j++) {
				find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);

				if (x_cord == building_x_cord && y_cord == building_y_cord) {
					building = task_segments[4];
					build_orientation = task_segments[5];

					return true;
				}
			}
		} else if (compare_task_strings(grid_tasks->GetCellValue(i, 0), struct_tasks_list.rotate)) {
			split_task(tasks_data_to_save[i]);

			building_x_cord = task_segments[1];
			building_y_cord = task_segments[2];

			if (x_cord == building_x_cord && y_cord == building_y_cord) {
				building = task_segments[4];
				build_orientation = task_segments[5];

				return true;
			}
		}
	}

	if (task == struct_tasks_list.mine) {
		return false;
	}

	wxMessageBox("Task: " + task_number + " have no building associated with it - please correct the error and try again", "The building does not exist");
	return false;
}

bool cMain::compare_task_strings(const wxString& str1, const std::string& str2) {
	if (str1.length() != str2.length()) {
		return false;
	}
	
	for (int i = 0; i < str1.length(); i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}

	return true;
}

// New function
bool cMain::find_building(int amount_of_buildings) {
	building_row_num = grid_buildings->GetNumberRows();

	if (building_row_num == 0) {
		return false;
	}

	if (amount_of_buildings > building_row_num) {
		return false;
	}
	
	for (int j = 0; j < building_row_num; j++) {

		if (!compare_task_strings(grid_buildings->GetCellValue(j, 0), building_x_cord) || !compare_task_strings(grid_buildings->GetCellValue(j, 1), building_y_cord)) {
			if (j == (building_row_num - 1)) {
				return false;
			}

			continue;
		}

		building = grid_buildings->GetCellValue(j, 2);
		building_row_num = j;
		break;
	}

	if (extra_building_checks()) {
		return true;
	}

	return false;
}

void cMain::malformed_saved_file_message()
{
	reset_to_new_window();
	wxMessageBox("It seems like the structure of the file does not correspond with an EZRaiderz TAS helper file", "A file error occurred");
}

inline const char* const cMain::bool_to_string(bool b)
{
	return b ? "true" : "false";
}

bool cMain::extra_building_checks() {
	std::string building_item_check = "";

	building_item_check = grid_buildings->GetCellValue(building_row_num, 2).ToStdString();
	if (building_task == "Limit") {
		if (!check_input(building_item_check, chest_list)) {
			return false;
		}
	} else if (building_task == "Priority") {
		if (!check_input(building_item_check, splitter_list)) {
			return false;
		}
	} else if (building_task == "Filter") {
		if (!check_input(building_item_check, splitter_list) && !check_input(building_item_check, filter_inserter_list)) {
			return false;
		}
	}

	return true;
}

bool cMain::check_take_put(std::string& item) {
	std::string to_check = extract_from_into();
	string_capitalized(to_check);

	if (to_check == "Wreck") {
		return true;
	}

	if (check_input(building, chest_list)) {
		if (to_check == "Chest") {
			return true;
		}

		wxMessageBox("Only Chest is a valid \"From/Into\" choice for a chest", "Please choose chest");
		return false;
	}

	if (to_check == "Fuel") {
		if (check_input(item, fuel_list)) {
			return true;
		}

		wxMessageBox("The item chosen is not a valid fuel", "Please select a valid fuel");
		return false;
	}

	if (building == "Lab") {
		if (to_check == "Input") {
			if (check_input(item, science_packs)) {
				return true;
			}

			wxMessageBox("The item chosen is not a science pack.\nOnly science packs can be used as input for a lab", "Please choose a science pack");
			return false;

		} else if (to_check == "Modules") {
			if (check_input(item, module_list)) {
				return true;
			}

			wxMessageBox("The item chosen is not a module", "Please choose a module");
			return false;
		}

		wxMessageBox("Only Input and Modules are valid \"From/Into\" choices for a lab", "Please choose input or modules");
		return false;
	}

	if (check_input(building, drills_list)) {
		if (to_check == "Modules") {
			if (check_input(item, module_list)) {
				return true;
			}

			wxMessageBox("The item chosen is not a module", "Please choose a module");
			return false;
		}

		wxMessageBox("Only Modules is a valid \"From/Into\" choice for a drill/Pump", "Please choose modules");
		return false;
	}

	if (to_check == "Input") {
		// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
		return true;
	}
			
	if (to_check == "Modules") {
		if (check_input(item, module_list)) {
			return true;
		}

		wxMessageBox("The item chosen is not a module", "Please choose a module");
		return false;
	}
			
	if (to_check == "Output") {
		// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
		return true;
	} 
	
	wxMessageBox("Building location does not seem to exist.\nPlease use exactly the same coordinates as you used to build", "Please use the same coordinates");
	return false;
}

bool cMain::check_buildings_grid() {
	
	if (building_task == "Mine")  {
		if (find_building(1)) {
			int total_rows = grid_tasks->GetNumberRows();

			mine_building_found = true;

			if (row_num + 1 >= total_rows) {
				grid_buildings->DeleteRows(building_row_num);
			} else {
				for (int i = row_num + 1; i < total_rows; i++) {
					if (grid_tasks->GetCellValue(i, 1).ToStdString() == x_cord && grid_tasks->GetCellValue(i, 2).ToStdString() == y_cord) {
						if (grid_tasks->GetCellValue(i, 0).ToStdString() != "Mine" && grid_tasks->GetCellValue(i, 0).ToStdString() != "Build") {
							if (wxMessageBox("Are you sure you want to remove this building?\nAll future tasks associated with the building will be removed to avoid issues.", "The building you are removing has tasks associated with it", wxICON_QUESTION | wxYES_NO, this) == wxYES) {
								grid_buildings->DeleteRows(building_row_num);
								for (int j = i; j < total_rows; j++) {
									if (grid_tasks->GetCellValue(j, 1).ToStdString() == x_cord && grid_tasks->GetCellValue(j, 2).ToStdString() == y_cord) {
										if (grid_tasks->GetCellValue(j, 0).ToStdString() == "Mine") {
											grid_tasks->SelectRow(row_num);
											grid_tasks->SetCellValue(j, 4, "");

											grid_extract_parameters(j, grid_tasks);

											item = "";

											tasks_data_to_save[j] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

											return true;
										} else if (grid_tasks->GetCellValue(j, 0).ToStdString() == "Build") {
											grid_tasks->SelectRow(row_num);
											return true;
										}

										grid_tasks->DeleteRows(j);

										it1 = tasks_data_to_save.begin();
										it1 += j;
										tasks_data_to_save.erase(it1);

										j--;
										total_rows--;
									}
								}

								grid_tasks->SelectRow(row_num);
								return true;
							} else {
								return false;
							}
						} else {
							if (grid_tasks->GetCellValue(i, 0).ToStdString() == "Mine") {
								grid_tasks->SetCellValue(i, 4, "");

								grid_extract_parameters(i, grid_tasks);

								item = "";

								tasks_data_to_save[i] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

							}

							grid_tasks->SelectRow(row_num);
							return true;
						}
					}
				}
			}
		}

	} else if (building_task == "Recipe") {
		if (!update_recipe()) {
			wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build\n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	} else if (building_task == "Build") {
		update_buildings();

	} else if (building_task == "Limit") {
		if (!update_limit()) {
			wxMessageBox("Building is not a chest or location doesn't exist.\n1. Please use exactly the same coordinates as you used to build\n2. Check that you have not removed the building(s)\n3. Ensure that all are chests\n4. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	} else if (building_task == "Priority") {

		if (!update_priority()) {
			wxMessageBox("Building is not a splitter or location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Ensure that all are splitters\n4. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	} else if (building_task == "Filter") {
		if (!update_filter()) {
			wxMessageBox("Building is not a splitter, filter inserter or location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Ensure that all are splitters or filter inserters\n4. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	} else if (building_task == "Take" || building_task == "Put") {
		building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
		for (int i = 0; i < building_amount_of_buildings_int; i++) {
			if (from_into != "Wreck" && !find_building(building_amount_of_buildings_int)) {
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
				return false;
			} 

			find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
		}

	} else if (building_task == "Launch") {
		if (!find_building(1)) {
			wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	} else if (building_task == "Rotate") {
		if (!Update_rotation()) {
			wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

		std::string saved_orientation = building_build_orientation;

		if ((row_num + 1) < grid_tasks->GetNumberRows()) {
			update_future_rotate_tasks();
		}

		build_orientation = saved_orientation;
	}
	return true;
}

bool cMain::save_file(bool save_as) {

	if (save_as) {
		wxFileDialog dlg(this, "Save file", "", "", ".txt files (*.txt) | *.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (dlg.ShowModal() == wxID_OK) {
			save_file_location = dlg.GetPath().ToStdString();
		} else {
			return false;
		}
	} else {
		if (save_file_location == "") {
			wxFileDialog dlg(this, "Save file", "", "", ".txt files (*.txt) | *.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

			if (dlg.ShowModal() == wxID_OK) {
				save_file_location = dlg.GetPath().ToStdString();
			} else {
				return false;
			}
		}
	}

	int total_lines = tasks_data_to_save.size() + group_map.size() + template_map.size();
	int lines_processed = 0; 

	if (!dialog_progress_bar) {
		dialog_progress_bar = new dialog_progress_bar_base(this, wxID_ANY, "Processing request");
	}

	dialog_progress_bar->set_text("Saving file");
	dialog_progress_bar->set_button_enable(false);
	dialog_progress_bar->set_progress(0);
	dialog_progress_bar->Show();

	std::ofstream myfile;
	myfile.open(save_file_location);

	myfile << total_tasks_indicator << std::endl;
	myfile << total_lines << std::endl;

	myfile << goal_indicator << std::endl;
	if (menu_goals->GetMenuItems()[0]->IsChecked()) {
		myfile << goal_steelaxe_text << std::endl;
	} else if (menu_goals->GetMenuItems()[1]->IsChecked()) {
		myfile << goal_GOTLAP_text << std::endl;
	} else if (menu_goals->GetMenuItems()[2]->IsChecked()) {
		myfile << goal_any_percent_text << std::endl;
	} else if (menu_goals->GetMenuItems()[3]->IsChecked()) {
		myfile << goal_debug_text << std::endl;
	} else {
		myfile << goal_steelaxe_text << std::endl;
	}

	myfile << tasks_indicator << std::endl;
	for (auto it = tasks_data_to_save.begin(); it < tasks_data_to_save.end(); it++) {
		myfile << *it << std::endl;

		lines_processed++;

		if (lines_processed > 0 && lines_processed % 25 == 0) {
			dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 1);
			wxYield();
		}
	}

	myfile << save_groups_indicator << std::endl;
	if (group_map.size()) {
		for (auto element : group_map) {
			for (auto value : element.second) {
				myfile << element.first + ";" + value << std::endl;

				lines_processed++;

				if (lines_processed > 0 && lines_processed % 25 == 0) {
					dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 1);
					wxYield();
				}
			}
		}
	}

	myfile << save_templates_indicator << std::endl;
	if (template_map.size()) {
		for (auto element : template_map) {
			for (auto value : element.second) {
				myfile << element.first + ";" + value << std::endl;

				lines_processed++;

				if (lines_processed > 0 && lines_processed % 25 == 0) {
					dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 1);
					wxYield();
				}
			}
		}
	}

	myfile << save_file_indicator << std::endl;
	myfile << save_file_location << std::endl;

	myfile << code_file_indicator << std::endl;
	if (generate_code_folder_location != "") {
		myfile << generate_code_folder_location << std::endl;
	}

	myfile << auto_close_indicator << std::endl;
	myfile << auto_close_generate_script_text << ";" << bool_to_string(menu_auto_close->GetMenuItems()[0]->IsChecked()) << std::endl;
	myfile << auto_close_open_text << ";" << bool_to_string(menu_auto_close->GetMenuItems()[1]->IsChecked()) << std::endl;
	myfile << auto_close_save_text << ";" << bool_to_string(menu_auto_close->GetMenuItems()[2]->IsChecked()) << std::endl;
	myfile << auto_close_save_as_text << ";" << bool_to_string(menu_auto_close->GetMenuItems()[3]->IsChecked()) << std::endl;

	myfile << auto_put_indicator << std::endl;
	myfile << auto_put_furnace_text << ";" << bool_to_string(check_furnace->IsChecked()) << std::endl;
	myfile << auto_put_burner_text << ";" << bool_to_string(check_burner->IsChecked()) << std::endl;
	myfile << auto_put_lab_text << ";" << bool_to_string(check_lab->IsChecked()) << std::endl;
	myfile << auto_put_recipe_text << ";" << bool_to_string(check_recipe->IsChecked());

	myfile.close();

	std::string file_name = save_file_location.substr(save_file_location.rfind("\\") + 1);

	SetLabel(window_title + " - " + file_name);

	dialog_progress_bar->set_progress(100);
	if (save_as) {
		if (auto_close_save_as) {
			dialog_progress_bar->Close();
		}
		else {
			dialog_progress_bar->set_button_enable(true);
		}
	} else {
		if (auto_close_save) {
			dialog_progress_bar->Close();
		}
		else {
			dialog_progress_bar->set_button_enable(true);
		}
	}

	return true;
}

bool cMain::check_input(std::string& item, const std::vector<std::string>& all_items) {
	std::string item_lower = "";
	for (unsigned int i = 0; i < item.size(); i++) {
		item_lower.push_back(std::tolower(item[i]));
	}

	for (auto it = all_items.begin(); it < all_items.end(); it++) {

		std::string check_item_lower = "";

		for (unsigned int i = 0; i < (*it).size(); i++) {
			check_item_lower.push_back(std::tolower((*it)[i]));
		}

		if (item_lower == check_item_lower) {
			item = *it;
			return true;
		}
	}

	return false;
}