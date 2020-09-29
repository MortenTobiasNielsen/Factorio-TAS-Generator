#include "cMain.h"
#include "GUI_Base.h"
#include "utils.h"
#include "Functions.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>

cMain::cMain() : GUI_Base(nullptr, wxID_ANY, "Factorio Script Helper", wxPoint(30, 30), wxSize(1620, 1080)) {
	all_items.insert(all_items.end(), item_logistics.begin(), item_logistics.end());
	all_items.insert(all_items.end(), item_production.begin(), item_production.end());
	all_items.insert(all_items.end(), item_intermediates.begin(), item_intermediates.end());
	all_items.insert(all_items.end(), item_combat.begin(), item_combat.end());

	static const std::vector<std::string> all_items_const(all_items);

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
	
	for (auto s : input_output) {
		input_output_choices.Add(s);
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
	event.Skip();
}

void cMain::OnTakeChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.take);
	event.Skip();
}

void cMain::OnPutChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.put);
	event.Skip();
}

void cMain::OnCraftChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.craft);
	event.Skip();
}

void cMain::OnRotateChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.rotate);
	event.Skip();
}

void cMain::OnfilterChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.filter);
	event.Skip();
}

void cMain::OnRecipeChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.recipe);
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
	event.Skip();
}

void cMain::OnStopChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.stop);
	event.Skip();
}

bool cMain::move_row(wxGrid* grid, bool up) {
	if (!grid->IsSelection() || !grid->GetSelectedRows().begin()) {
		wxMessageBox("Please select row(s) to move", "Select row(s)");
		return false;
	}

	if (up) {
		if (*grid->GetSelectedRows().begin() == 0) {
			return false;
		}
		row_count = grid->GetSelectedRows().GetCount();
		row_num = *grid->GetSelectedRows().begin();
		row_to_move = row_num - 1;
	} else {
		if ((*grid->GetSelectedRows().begin() + grid->GetSelectedRows().GetCount()) == (grid->GetNumberRows())) {
			return false;
		}
		row_count = grid->GetSelectedRows().GetCount();
		row_num = *grid->GetSelectedRows().begin();
		row_to_move = row_num + row_count + 1;
		row_count = 0;
	}

	grid->InsertRows(row_num + row_count, 1);

	grid->SetCellValue(row_num + row_count, 0, grid->GetCellValue(row_to_move, 0).ToStdString());
	grid->SetCellValue(row_num + row_count, 1, grid->GetCellValue(row_to_move, 1).ToStdString());
	grid->SetCellValue(row_num + row_count, 2, grid->GetCellValue(row_to_move, 2).ToStdString());
	grid->SetCellValue(row_num + row_count, 3, grid->GetCellValue(row_to_move, 3).ToStdString());
	grid->SetCellValue(row_num + row_count, 4, grid->GetCellValue(row_to_move, 4).ToStdString());
	grid->SetCellValue(row_num + row_count, 5, grid->GetCellValue(row_to_move, 5).ToStdString());
	grid->SetCellValue(row_num + row_count, 6, grid->GetCellValue(row_to_move, 6).ToStdString());
	grid->SetCellValue(row_num + row_count, 7, grid->GetCellValue(row_to_move, 7).ToStdString());
	grid->SetCellValue(row_num + row_count, 8, grid->GetCellValue(row_to_move, 8).ToStdString());

	grid->DeleteRows(row_to_move, 1);

	return true;
}

bool cMain::delete_row(wxGrid* grid) {
	if (!grid->IsSelection()) {
		wxMessageBox("Please select row(s) to be deleted", "Selection not valid");
		return false;
	}

	row_num = *grid->GetSelectedRows().begin();
	row_count = grid->GetSelectedRows().GetCount();

	grid->DeleteRows(row_num, row_count);

	return true;
}

bool cMain::change_row(wxGrid* grid) {
	if (!grid->IsSelection() || !grid->GetSelectedRows().begin()) {
		wxMessageBox("Please select a row to change", "Selection not valid");
		return false;
	}

	row_num = *grid->GetSelectedRows().begin();

	grid->SetCellValue(row_num, 0, task);
	grid->SetCellValue(row_num, 1, x_cord);
	grid->SetCellValue(row_num, 2, y_cord);
	grid->SetCellValue(row_num, 3, units);
	grid->SetCellValue(row_num, 4, item);
	grid->SetCellValue(row_num, 5, build_orientation);
	grid->SetCellValue(row_num, 6, direction_to_build);
	grid->SetCellValue(row_num, 7, building_size);
	grid->SetCellValue(row_num, 8, amount_of_buildings);

	return true;
}

void cMain::update_tasks_grid() {

	if (grid_tasks->IsSelection() ) {
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
	grid_tasks->SetCellValue(row_num, 5, build_orientation);
	grid_tasks->SetCellValue(row_num, 6, direction_to_build);
	grid_tasks->SetCellValue(row_num, 7, building_size);
	grid_tasks->SetCellValue(row_num, 8, amount_of_buildings);

	if (grid_tasks->IsSelection()) {
		it1 = tasks_data_to_save.begin();
		it1 += row_num;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);
	} else {
		tasks_data_to_save.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);
	}	
}

void cMain::change_task() {
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin()) {
			wxMessageBox("Please select a row to change", "Task list selection not valid");
			return;
	}
	
	row_num = *grid_tasks->GetSelectedRows().begin();

	grid_tasks->SetCellValue(row_num, 0, task);
	grid_tasks->SetCellValue(row_num, 1, x_cord);
	grid_tasks->SetCellValue(row_num, 2, y_cord);
	grid_tasks->SetCellValue(row_num, 3, units);
	grid_tasks->SetCellValue(row_num, 4, item);
	grid_tasks->SetCellValue(row_num, 5, build_orientation);
	grid_tasks->SetCellValue(row_num, 6, direction_to_build);
	grid_tasks->SetCellValue(row_num, 7, building_size);
	grid_tasks->SetCellValue(row_num, 8, amount_of_buildings);

	tasks_data_to_save[row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);

	update_buildings_grid_from_scratch();
}

void cMain::update_buildings_grid() {
	row_num = grid_buildings->GetNumberRows();

	grid_buildings->InsertRows(row_num, 1);

	grid_buildings->SetCellValue(row_num, 0, x_cord);
	grid_buildings->SetCellValue(row_num, 1, y_cord);
	grid_buildings->SetCellValue(row_num, 2, item);
	grid_buildings->SetCellValue(row_num, 3, build_orientation);
	grid_buildings->SetCellValue(row_num, 4, limit);
	grid_buildings->SetCellValue(row_num, 5, recipe);
	grid_buildings->SetCellValue(row_num, 6, priority_in);
	grid_buildings->SetCellValue(row_num, 7, priority_out);
	grid_buildings->SetCellValue(row_num, 8, filter);
}

void cMain::update_buildings_grid_from_scratch() {
	if (grid_buildings->GetNumberRows() > 0) {
		grid_buildings->DeleteRows(0, grid_buildings->GetNumberRows());
	}

	for (int i = 0; i < grid_tasks->GetNumberRows(); i++) {
		task = grid_tasks->GetCellValue(i, 0).ToStdString();

		if (task == "Build" ) {
			x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
			y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
			item = grid_tasks->GetCellValue(i, 4).ToStdString();
			build_orientation = grid_tasks->GetCellValue(i, 5).ToStdString();
			direction_to_build = grid_tasks->GetCellValue(i, 6).ToStdString();
			building_size = grid_tasks->GetCellValue(i, 7).ToStdString();
			amount_of_buildings = grid_tasks->GetCellValue(i, 8).ToStdString();

			building_row();

		} else if (task == "Recipe") {
			x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
			y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
			item = grid_tasks->GetCellValue(i, 4).ToStdString();
			direction_to_build = grid_tasks->GetCellValue(i, 6).ToStdString();
			building_size = grid_tasks->GetCellValue(i, 7).ToStdString();
			amount_of_buildings = grid_tasks->GetCellValue(i, 8).ToStdString();

			update_recipe();

		} else if (task == "Limit") {
			x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
			y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
			units = grid_tasks->GetCellValue(i, 3).ToStdString();
			direction_to_build = grid_tasks->GetCellValue(i, 6).ToStdString();
			building_size = grid_tasks->GetCellValue(i, 7).ToStdString();
			amount_of_buildings = grid_tasks->GetCellValue(i, 8).ToStdString();

			update_limit();

		} else if (task == "Priority") {
			x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
			y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
			direction_to_build = grid_tasks->GetCellValue(i, 6).ToStdString();
			building_size = grid_tasks->GetCellValue(i, 7).ToStdString();
			amount_of_buildings = grid_tasks->GetCellValue(i, 8).ToStdString();
		
			int pos = grid_tasks->GetCellValue(i, 5).ToStdString().find(",");

			priority_in = grid_tasks->GetCellValue(i, 5).ToStdString().substr(0, pos);
			priority_out = grid_tasks->GetCellValue(i, 5).ToStdString().substr(pos + 2);

			update_priority();

		} else if (task == "Filter") {
			x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
			y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
			item = grid_tasks->GetCellValue(i, 4).ToStdString();
			direction_to_build = grid_tasks->GetCellValue(i, 6).ToStdString();
			building_size = grid_tasks->GetCellValue(i, 7).ToStdString();
			amount_of_buildings = grid_tasks->GetCellValue(i, 8).ToStdString();

			update_filter();
		}
	}
}

bool cMain::update_building_orientation() {
	row_num = grid_buildings->GetNumberRows();
	int orientation_location;

	for (int i = 0; i < row_num; i++) {
		x_cord = grid_buildings->GetCellValue(i, 0);
		y_cord = grid_buildings->GetCellValue(i, 1);
		build_orientation = grid_buildings->GetCellValue(i, 3);

		if (x_cord != grid_buildings->GetCellValue(i, 0)) {
			continue;
		}
		if (y_cord != grid_buildings->GetCellValue(i, 1)) {
			continue;
		}

		for (auto it = build_orientations.begin(); it < build_orientations.end(); it++) {
			if (build_orientation == *it) {
				orientation_location = it - build_orientations.begin();
				break;
			}
		}

		build_orientation = build_orientations[(orientation_location + std::stoi(units)) % 4];
		grid_buildings->SetCellValue(i, 3, build_orientation);
		return true;
	}

	return false;
}

void cMain::building_row() {
	limit = "";
	recipe = "";
	priority_in = "";
	priority_out = "";
	filter = "";

	x_cord_float = std::stof(x_cord);
	y_cord_float = std::stof(y_cord);
	building_size_float = std::stof(building_size);


	for (int i = 0; i < std::stoi(amount_of_buildings); i++) {
		if (direction_to_build == "North") {
			y_cord = std::to_string(y_cord_float - building_size_float * i);
			update_buildings_grid();

		} else if (direction_to_build == "South") {
			y_cord = std::to_string(y_cord_float + building_size_float * i);
			update_buildings_grid();

		} else if (direction_to_build == "East") {
			x_cord = std::to_string(x_cord_float + building_size_float * i);
			update_buildings_grid();

		} else if (direction_to_build == "West") {
			x_cord = std::to_string(x_cord_float - building_size_float * i);
			update_buildings_grid();
		}
	}
}

bool cMain::update_recipe() {
	row_num = grid_buildings->GetNumberRows();

	x_cord_float = std::stof(x_cord);
	y_cord_float = std::stof(y_cord);
	building_size_float = std::stof(building_size);

	int amount_true = 0;

	for (int i = 0; i < std::stoi(amount_of_buildings); i++) {
		if (direction_to_build == "North") {
			y_cord = std::to_string(y_cord_float - building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 5, item);
				amount_true += 1;
				break;
			}

		} else if (direction_to_build == "South") {
			y_cord = std::to_string(y_cord_float + building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 5, item);
				amount_true += 1;
				break;
			}

		} else if (direction_to_build == "East") {
			x_cord = std::to_string(x_cord_float + building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 5, item);
				amount_true += 1;
				break;
			}
		} else if (direction_to_build == "West") {
			x_cord = std::to_string(x_cord_float - building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 5, item);
				amount_true += 1;
				break;
			}
		}
	}

	if (amount_true == std::stoi(amount_of_buildings)) {
		return true;
	} 

	return false;
}

bool cMain::update_limit() {
	row_num = grid_buildings->GetNumberRows();

	x_cord_float = std::stof(x_cord);
	y_cord_float = std::stof(y_cord);
	building_size_float = std::stof(building_size);

	int amount_true = 0;

	for (int i = 0; i < std::stoi(amount_of_buildings); i++) {
		if (direction_to_build == "North") {
			y_cord = std::to_string(y_cord_float - building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 4, units);
				amount_true += 1;
				break;
			}

		} else if (direction_to_build == "South") {
			y_cord = std::to_string(y_cord_float + building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}
				grid_buildings->SetCellValue(i, 4, units);
				amount_true += 1;
				break;
			}

		} else if (direction_to_build == "East") {
			x_cord = std::to_string(x_cord_float + building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}
				grid_buildings->SetCellValue(i, 4, units);
				amount_true += 1;
				break;
			}
		} else if (direction_to_build == "West") {
			x_cord = std::to_string(x_cord_float - building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}
				grid_buildings->SetCellValue(i, 4, units);
				amount_true += 1;
				break;
			}
		}
	}

	if (amount_true == std::stoi(amount_of_buildings)) {
		return true;
	}

	return false;
}

bool cMain::update_priority() {
	row_num = grid_buildings->GetNumberRows();

	x_cord_float = std::stof(x_cord);
	y_cord_float = std::stof(y_cord);
	building_size_float = std::stof(building_size);

	int amount_true = 0;

	for (int i = 0; i < std::stoi(amount_of_buildings); i++) {
		if (direction_to_build == "North") {
			y_cord = std::to_string(y_cord_float - building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				if (!check_building(grid_buildings->GetCellValue(i, 2).ToStdString(), splitters)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 6, priority_in);
				grid_buildings->SetCellValue(i, 7, priority_out);
				amount_true += 1;
				break;
			}

		} else if (direction_to_build == "South") {
			y_cord = std::to_string(y_cord_float + building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				if (!check_building(grid_buildings->GetCellValue(i, 2).ToStdString(), splitters)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 6, priority_in);
				grid_buildings->SetCellValue(i, 7, priority_out);
				amount_true += 1;
				break;
			}

		} else if (direction_to_build == "East") {
			x_cord = std::to_string(x_cord_float + building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}

				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				if (!check_building(grid_buildings->GetCellValue(i, 2).ToStdString(), splitters)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 6, priority_in);
				grid_buildings->SetCellValue(i, 7, priority_out);
				amount_true += 1;
				break;
			}
		} else if (direction_to_build == "West") {
			x_cord = std::to_string(x_cord_float - building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}

				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				if (!check_building(grid_buildings->GetCellValue(i, 2).ToStdString(), splitters)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 6, priority_in);
				grid_buildings->SetCellValue(i, 7, priority_out);
				amount_true += 1;
				break;
			}
		}
	}

	if (amount_true == std::stoi(amount_of_buildings)) {
		return true;
	}

	return false;
}

bool cMain::update_filter() {
	row_num = grid_buildings->GetNumberRows();

	x_cord_float = std::stof(x_cord);
	y_cord_float = std::stof(y_cord);
	building_size_float = std::stof(building_size);

	int amount_true = 0;

	for (int i = 0; i < std::stoi(amount_of_buildings); i++) {
		if (direction_to_build == "North") {
			y_cord = std::to_string(y_cord_float - building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				if (check_building(grid_buildings->GetCellValue(i, 2).ToStdString(), splitters)) {
					grid_buildings->SetCellValue(i, 8, item);
					amount_true += 1;
					break; 
				} if (check_building(grid_buildings->GetCellValue(i, 2).ToStdString(), filter_inserters)) {
					grid_buildings->SetCellValue(i, 8, item);
					amount_true += 1;
					break;
				}
				
				continue;
			}

		} else if (direction_to_build == "South") {
			y_cord = std::to_string(y_cord_float + building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}
				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				if (!check_building(grid_buildings->GetCellValue(i, 2).ToStdString(), splitters)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 6, priority_in);
				grid_buildings->SetCellValue(i, 7, priority_out);
				amount_true += 1;
				break;
			}

		} else if (direction_to_build == "East") {
			x_cord = std::to_string(x_cord_float + building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}

				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				if (!check_building(grid_buildings->GetCellValue(i, 2).ToStdString(), splitters)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 6, priority_in);
				grid_buildings->SetCellValue(i, 7, priority_out);
				amount_true += 1;
				break;
			}
		} else if (direction_to_build == "West") {
			x_cord = std::to_string(x_cord_float - building_size_float * i);
			for (int i = 0; i < row_num; i++) {

				if (x_cord != grid_buildings->GetCellValue(i, 0)) {
					continue;
				}

				if (y_cord != grid_buildings->GetCellValue(i, 1)) {
					continue;
				}

				if (!check_building(grid_buildings->GetCellValue(i, 2).ToStdString(), splitters)) {
					continue;
				}

				grid_buildings->SetCellValue(i, 6, priority_in);
				grid_buildings->SetCellValue(i, 7, priority_out);
				amount_true += 1;
				break;
			}
		}
	}

	if (amount_true == std::stoi(amount_of_buildings)) {
		return true;
	}

	return false;
}

void cMain::update_group_grid() {
	if (grid_group->GetNumberRows() > 0) {
		grid_group->DeleteRows(0, grid_group->GetNumberRows());
	}

	group_list = group_map[group_name];
	grid_group->InsertRows(0, group_list.size());

	for (int i = 0; i < group_list.size(); i++) {
		std::stringstream data_line;
		data_line.str(group_list[i]);
		seglist = {};

		while (std::getline(data_line, segment, ';')) {
			seglist.push_back(segment);
		}

		grid_group->SetCellValue(i, 0, seglist[0]);
		grid_group->SetCellValue(i, 1, seglist[1]);
		grid_group->SetCellValue(i, 2, seglist[2]);
		grid_group->SetCellValue(i, 3, seglist[3]);
		grid_group->SetCellValue(i, 4, seglist[4]);
		grid_group->SetCellValue(i, 5, seglist[5]);
		grid_group->SetCellValue(i, 6, seglist[6]);
		grid_group->SetCellValue(i, 7, seglist[7]);
		grid_group->SetCellValue(i, 8, seglist[8]);
	}
}

void cMain::update_template_grid() {
	if (grid_template->GetNumberRows() > 0) {
		grid_template->DeleteRows(0, grid_template->GetNumberRows());
	}

	template_list = template_map[template_name];
	grid_template->InsertRows(0, template_list.size());

	for (int i = 0; i < template_list.size(); i++) {
		std::stringstream data_line;
		data_line.str(template_list[i]);
		seglist = {};

		while (std::getline(data_line, segment, ';')) {
			seglist.push_back(segment);
		}

		grid_template->SetCellValue(i, 0, seglist[0]);
		grid_template->SetCellValue(i, 1, seglist[1]);
		grid_template->SetCellValue(i, 2, seglist[2]);
		grid_template->SetCellValue(i, 3, seglist[3]);
		grid_template->SetCellValue(i, 4, seglist[4]);
		grid_template->SetCellValue(i, 5, seglist[5]);
		grid_template->SetCellValue(i, 6, seglist[6]);
		grid_template->SetCellValue(i, 7, seglist[7]);
		grid_template->SetCellValue(i, 8, seglist[8]);
	}
}

void cMain::OnAddTaskClicked(wxCommandEvent& event) {
	
	extract_parameters();

	if (setup_for_task_grid()) {
		update_tasks_grid();
		if (task == "Build") {
			building_row();

		} else if (task == "Recipe") {
			if (!update_recipe()) {
				wxMessageBox("Building location does not seem to exit.\nPlease use exactly the same coordinates as you used to build", "Please use the same coordinates");
			}

		} else if (task == "Limit") {
			if (!update_limit()) {
				wxMessageBox("Building location does not seem to exit.\nPlease use exactly the same coordinates as you used to build", "Please use the same coordinates");
			}

		} else if (task == "Priority") {
			if (!update_priority()) {
				wxMessageBox("Building is not a splitter or location does not seem to exit.\nPlease use exactly the same coordinates as you used to build and ensure that it is a splitter", "Please use the same coordinates");
			}
		} else if (task == "Filter") {
			if (!update_filter()) {
				wxMessageBox("Building is not a splitter, filter inserter or location does not seem to exit.\nPlease use exactly the same coordinates as you used to build and ensure that it is a splitter or filter inserter", "Please use the same coordinates");
			}
		}
	}

	event.Skip();
}

void cMain::OnChangeTaskClicked(wxCommandEvent& event) {
	extract_parameters();

	if (setup_for_task_grid()) {
		if (change_row(grid_tasks)) {
			tasks_data_to_save[row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);

			update_buildings_grid_from_scratch();
		}
	}

	event.Skip();
}

void cMain::OnTasksGridDoubleLeftClick(wxGridEvent& event) {
	row_num = event.GetRow();

	update_parameteres(grid_tasks, event);

	event.Skip();
}

void cMain::OnNewGroupClicked(wxCommandEvent& event) {

	row_count = cmb_choose_group->GetCount();
	group_name = cmb_choose_group->GetValue().ToStdString();

	if (group_name == "") {
		wxMessageBox("Please write a group name", "Group name cannot be blank");
		return;
	}

	for (int i = 0; i < row_count; i++) {
		if (group_name == cmb_choose_group->GetString(i).ToStdString()) {
			wxMessageBox("Group names has to be unique - please write a new name in the Choose Group field", "Group names should be unique");
			return;
		}
	}

	cmb_choose_group->Clear();
	group_choices.Add(group_name);
	cmb_choose_group->Append(group_choices);
	cmb_choose_group->SetValue(group_name);
	group_list = {};

	if (grid_group->IsSelection()) {
		if (!grid_group->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
			return;
		}
		row_num = *grid_group->GetSelectedRows().begin();
		row_count = grid_group->GetSelectedRows().GetCount();
	} else {
		row_count = grid_group->GetNumberRows();

		if (row_count) {
			row_num = 0;
		} else {
			group_map.insert(std::pair<std::string, std::vector<std::string>>(group_name, group_list));
			event.Skip();
			return;
		}
	}

	for (int i = row_num; i < row_num + row_count; i++) {
		task = grid_group->GetCellValue(i, 0).ToStdString();
		x_cord = grid_group->GetCellValue(i, 1).ToStdString();
		y_cord = grid_group->GetCellValue(i, 2).ToStdString();
		units = grid_group->GetCellValue(i, 3).ToStdString();
		item = grid_group->GetCellValue(i, 4).ToStdString();
		build_orientation = grid_group->GetCellValue(i, 5).ToStdString();
		direction_to_build = grid_group->GetCellValue(i, 6).ToStdString();
		building_size = grid_group->GetCellValue(i, 7).ToStdString();
		amount_of_buildings = grid_group->GetCellValue(i, 8).ToStdString();

		group_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";");
	}
	
	group_map.insert(std::pair<std::string, std::vector<std::string>> (group_name, group_list));

	update_group_grid();

	event.Skip();
}

void cMain::OnDeleteGroupClicked(wxCommandEvent& event) {
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
		wxMessageBox("No task is chosen - please select a row in the task list", "Cannot add task to group");
		return;
	}

	static int row;

	if (grid_group->IsSelection()) {
		if (!grid_group->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
			return;
		}
		row = *grid_group->GetSelectedRows().begin();
	} else {
		row = grid_group->GetNumberRows();
	}

	row_num = *grid_tasks->GetSelectedRows().begin();
	row_count = grid_tasks->GetSelectedRows().GetCount();

	grid_group->InsertRows(row, row_count);

	for (int i = row_num; i < (row_num + row_count); i++) {

		grid_group->SetCellValue(row + i - row_num, 0, grid_tasks->GetCellValue(i, 0).ToStdString());
		grid_group->SetCellValue(row + i - row_num, 1, grid_tasks->GetCellValue(i, 1).ToStdString());
		grid_group->SetCellValue(row + i - row_num, 2, grid_tasks->GetCellValue(i, 2).ToStdString());
		grid_group->SetCellValue(row + i - row_num, 3, grid_tasks->GetCellValue(i, 3).ToStdString());
		grid_group->SetCellValue(row + i - row_num, 4, grid_tasks->GetCellValue(i, 4).ToStdString());
		grid_group->SetCellValue(row + i - row_num, 5, grid_tasks->GetCellValue(i, 5).ToStdString());
		grid_group->SetCellValue(row + i - row_num, 6, grid_tasks->GetCellValue(i, 6).ToStdString());
		grid_group->SetCellValue(row + i - row_num, 7, grid_tasks->GetCellValue(i, 7).ToStdString());
		grid_group->SetCellValue(row + i - row_num, 8, grid_tasks->GetCellValue(i, 8).ToStdString());
	}

	if (!(group_map.find(cmb_choose_group->GetValue().ToStdString()) == group_map.end())) {
		update_group_map();
	}
}

void cMain::OnGroupAddToTasksListClicked(wxCommandEvent& event) {
	if (!grid_tasks->IsSelection()) {
		row_num = grid_tasks->GetNumberRows();
	} else {
		if (!grid_tasks->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Task list selection not valid");
		} else {
			row_num = *grid_tasks->GetSelectedRows().begin();
		}
	}

	int row_num_group;
	int row_count_group;
	int counter = 0;

	for (auto block : grid_group->GetSelectedRowBlocks()) {
		row_num_group = block.GetTopRow();
		row_count_group = block.GetBottomRow() - row_num_group + 1;
		
		for (int i = row_num_group; i < (row_num_group + row_count_group); i++) {
			grid_tasks->InsertRows(row_num + counter);

			task = grid_group->GetCellValue(i, 0).ToStdString();
			x_cord = grid_group->GetCellValue(i, 1).ToStdString();
			y_cord = grid_group->GetCellValue(i, 2).ToStdString();
			units = grid_group->GetCellValue(i, 3).ToStdString();
			item = grid_group->GetCellValue(i, 4).ToStdString();
			build_orientation = grid_group->GetCellValue(i, 5).ToStdString();
			direction_to_build = grid_group->GetCellValue(i, 6).ToStdString();
			building_size = grid_group->GetCellValue(i, 7).ToStdString();
			amount_of_buildings = grid_group->GetCellValue(i, 8).ToStdString();

			grid_tasks->SetCellValue(row_num + counter, 0, grid_group->GetCellValue(i, 0));
			grid_tasks->SetCellValue(row_num + counter, 1, grid_group->GetCellValue(i, 1));
			grid_tasks->SetCellValue(row_num + counter, 2, grid_group->GetCellValue(i, 2));
			grid_tasks->SetCellValue(row_num + counter, 3, grid_group->GetCellValue(i, 3));
			grid_tasks->SetCellValue(row_num + counter, 4, grid_group->GetCellValue(i, 4));
			grid_tasks->SetCellValue(row_num + counter, 5, grid_group->GetCellValue(i, 5));
			grid_tasks->SetCellValue(row_num + counter, 6, grid_group->GetCellValue(i, 6));
			grid_tasks->SetCellValue(row_num + counter, 7, grid_group->GetCellValue(i, 7));
			grid_tasks->SetCellValue(row_num + counter, 8, grid_group->GetCellValue(i, 8));

			it1 = tasks_data_to_save.begin();
			it1 += row_num + counter;

			tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);

			counter += 1;
		}		
	}

	if (counter > 0) {
		update_buildings_grid_from_scratch();
		return;
	}

	row_num_group = 0;
	row_count_group = grid_group->GetNumberRows();

	for (int i = row_num_group; i < (row_num_group + row_count_group); i++) {
		grid_tasks->InsertRows(row_num + i);

		task = grid_group->GetCellValue(i, 0).ToStdString();
		x_cord = grid_group->GetCellValue(i, 1).ToStdString();
		y_cord = grid_group->GetCellValue(i, 2).ToStdString();
		units = grid_group->GetCellValue(i, 3).ToStdString();
		item = grid_group->GetCellValue(i, 4).ToStdString();
		build_orientation = grid_group->GetCellValue(i, 5).ToStdString();
		direction_to_build = grid_group->GetCellValue(i, 6).ToStdString();
		building_size = grid_group->GetCellValue(i, 7).ToStdString();
		amount_of_buildings = grid_group->GetCellValue(i, 8).ToStdString();

		grid_tasks->SetCellValue(row_num + i, 0, grid_group->GetCellValue(i, 0));
		grid_tasks->SetCellValue(row_num + i, 1, grid_group->GetCellValue(i, 1));
		grid_tasks->SetCellValue(row_num + i, 2, grid_group->GetCellValue(i, 2));
		grid_tasks->SetCellValue(row_num + i, 3, grid_group->GetCellValue(i, 3));
		grid_tasks->SetCellValue(row_num + i, 4, grid_group->GetCellValue(i, 4));
		grid_tasks->SetCellValue(row_num + i, 5, grid_group->GetCellValue(i, 5));
		grid_tasks->SetCellValue(row_num + i, 6, grid_group->GetCellValue(i, 6));
		grid_tasks->SetCellValue(row_num + i, 7, grid_group->GetCellValue(i, 7));
		grid_tasks->SetCellValue(row_num + i, 8, grid_group->GetCellValue(i, 8));

		it1 = tasks_data_to_save.begin();
		it1 += row_num + i;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);
	}
	
	update_buildings_grid_from_scratch();

	event.Skip();
}

void cMain::OnGroupChangeClicked(wxCommandEvent& event) {
	extract_parameters();

	if (setup_for_task_grid()) {
		change_row(grid_group);

		group_name = cmb_choose_group->GetValue().ToStdString();

		if (!(group_map.find(group_name) == group_map.end())) {
			group_map[group_name][row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);
		}
	}

	event.Skip();

}

void cMain::OnGroupDeleteClicked(wxCommandEvent& event) {
	if (!delete_row(grid_group)) {

		event.Skip();
		return;
	}

	group_name = cmb_choose_group->GetValue().ToStdString();

	if (!(group_map.find(group_name) == group_map.end())) {
		it1 = group_map[group_name].begin();
		it2 = group_map[group_name].begin();

		it1 += row_num;
		it2 += row_num + row_count;

		group_map[group_name].erase(it1, it2);
	}

	event.Skip();
}

void cMain::OnGroupMoveUpClicked(wxCommandEvent& event) {
	if (!move_row(grid_group, true)) {
	
		event.Skip();
		return;
	}

	group_name = cmb_choose_group->GetValue().ToStdString();

	if (!(group_map.find(group_name) == group_map.end())) {
		it1 = group_map[group_name].begin();
		it1 += row_to_move;

		data = *it1;
		group_map[group_name].erase(it1);

		it2 = group_map[group_name].begin();
		it2 += row_num + row_count - 1;
		group_map[group_name].insert(it2, data);
	}
	event.Skip();
}

void cMain::OnGroupMoveDownClicked(wxCommandEvent& event) {
	if (!move_row(grid_group, false)) {
		return;
	}

	group_name = cmb_choose_group->GetValue().ToStdString();

	if (!(group_map.find(group_name) == group_map.end())) {
		it1 = group_map[group_name].begin();
		it1 += row_to_move - 1;
		it2 = group_map[group_name].begin();
		it2 += row_num;

		data = *it1;
		group_map[group_name].erase(it1, it1 + 1);
		group_map[group_name].insert(it2, data);
	}

	event.Skip();
}

void cMain::OnGroupGridDoubleLeftClick(wxGridEvent& event) {
	row_num = event.GetRow();

	update_parameteres(grid_group, event);

	event.Skip();
}

void cMain::OnGroupChosen(wxCommandEvent& event) {
	group_name = cmb_choose_group->GetValue();
	update_group_grid();

	event.Skip();
}

void cMain::OnTemplateChosen(wxCommandEvent& event) {
	template_name = cmb_choose_template->GetValue();
	update_template_grid();

	event.Skip();
}

void cMain::OnNewTemplateClicked(wxCommandEvent& event) {
	row_count = cmb_choose_template->GetCount();
	template_name = cmb_choose_template->GetValue().ToStdString();

	if (template_name == "") {
		wxMessageBox("Please write a group name", "Group name cannot be blank");
		return;
	}

	for (int i = 0; i < row_count; i++) {
		if (template_name == cmb_choose_template->GetString(i).ToStdString()) {
			wxMessageBox("Group names has to be unique - please write a new name in the Choose Group field", "Group names should be unique");
			return;
		}
	}

	cmb_choose_template->Clear();
	template_choices.Add(template_name);
	cmb_choose_template->Append(template_choices);
	cmb_choose_template->SetValue(template_name);
	template_list = {};

	if (grid_template->IsSelection()) {
		if (!grid_template->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
			event.Skip();
			return;
		}
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
		task = grid_template->GetCellValue(i, 0).ToStdString();
		x_cord = grid_template->GetCellValue(i, 1).ToStdString();
		y_cord = grid_template->GetCellValue(i, 2).ToStdString();
		units = grid_template->GetCellValue(i, 3).ToStdString();
		item = grid_template->GetCellValue(i, 4).ToStdString();
		build_orientation = grid_template->GetCellValue(i, 5).ToStdString();
		direction_to_build = grid_template->GetCellValue(i, 6).ToStdString();
		building_size = grid_template->GetCellValue(i, 7).ToStdString();
		amount_of_buildings = grid_template->GetCellValue(i, 8).ToStdString();

		template_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";");
	}

	template_map.insert(std::pair<std::string, std::vector<std::string>>(template_name, template_list));

	update_template_grid();

	event.Skip();
}

void cMain::OnDeleteTemplateClicked(wxCommandEvent& event) {
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
		return;
	}

	static int row;
	static float x_offset;
	static float y_offset;

	if (grid_template->IsSelection()) {
		if (!grid_template->GetSelectedRows().begin()) {
			wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
			return;
		}
		row = *grid_template->GetSelectedRows().begin();
	} else {
		row = grid_template->GetNumberRows();
	}

	row_num = *grid_tasks->GetSelectedRows().begin();
	row_count = grid_tasks->GetSelectedRows().GetCount();

	grid_template->InsertRows(row, row_count);

	for (int i = row_num; i < (row_num + row_count); i++) {

		if (grid_tasks->GetCellValue(i, 1).ToStdString() != "") {
			x_cord_float = wxAtof(grid_tasks->GetCellValue(i, 1));
			y_cord_float = wxAtof(grid_tasks->GetCellValue(i, 2));

			x_offset = wxAtof(txt_template_x_offset->GetValue());
			y_offset = wxAtof(txt_template_y_offset->GetValue());

			x_cord = std::to_string(x_cord_float + x_offset);
			y_cord = std::to_string(y_cord_float + y_offset);
		} else {
			x_cord = grid_tasks->GetCellValue(i, 1);
			y_cord = grid_tasks->GetCellValue(i, 2);

		}

		grid_template->SetCellValue(row + i - row_num, 0, grid_tasks->GetCellValue(i, 0).ToStdString());
		grid_template->SetCellValue(row + i - row_num, 1, x_cord);
		grid_template->SetCellValue(row + i - row_num, 2, y_cord);
		grid_template->SetCellValue(row + i - row_num, 3, grid_tasks->GetCellValue(i, 3).ToStdString());
		grid_template->SetCellValue(row + i - row_num, 4, grid_tasks->GetCellValue(i, 4).ToStdString());
		grid_template->SetCellValue(row + i - row_num, 5, grid_tasks->GetCellValue(i, 5).ToStdString());
		grid_template->SetCellValue(row + i - row_num, 6, grid_tasks->GetCellValue(i, 6).ToStdString());
		grid_template->SetCellValue(row + i - row_num, 7, grid_tasks->GetCellValue(i, 7).ToStdString());
		grid_template->SetCellValue(row + i - row_num, 8, grid_tasks->GetCellValue(i, 8).ToStdString());
	}

	if (!(template_map.find(cmb_choose_template->GetValue().ToStdString()) == template_map.end())) {
		update_template_map();
	}

	event.Skip();
}

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

	int row_num_template;
	int row_count_template;
	int counter = 0;
	static float x_offset;
	static float y_offset;

	for (auto block : grid_template->GetSelectedRowBlocks()) {
		row_num_template = block.GetTopRow();
		row_count_template = block.GetBottomRow() - row_num_template + 1;

		for (int i = row_num_template; i < (row_num_template + row_count_template); i++) {
			grid_tasks->InsertRows(row_num + counter);

			task = grid_template->GetCellValue(i, 0).ToStdString();
			x_cord = grid_template->GetCellValue(i, 1).ToStdString();
			y_cord = grid_template->GetCellValue(i, 2).ToStdString();
			units = grid_template->GetCellValue(i, 3).ToStdString();
			item = grid_template->GetCellValue(i, 4).ToStdString();
			build_orientation = grid_template->GetCellValue(i, 5).ToStdString();
			direction_to_build = grid_template->GetCellValue(i, 6).ToStdString();
			building_size = grid_template->GetCellValue(i, 7).ToStdString();
			amount_of_buildings = grid_template->GetCellValue(i, 8).ToStdString();

			x_cord_float = std::stof(x_cord);
			y_cord_float = std::stof(y_cord);

			x_offset = wxAtof(txt_template_x_offset->GetValue());
			y_offset = wxAtof(txt_template_y_offset->GetValue());

			x_cord = std::to_string(x_cord_float + x_offset);
			y_cord = std::to_string(y_cord_float + y_offset);

			grid_tasks->SetCellValue(row_num + counter, 0, task);
			grid_tasks->SetCellValue(row_num + counter, 1, x_cord);
			grid_tasks->SetCellValue(row_num + counter, 2, y_cord);
			grid_tasks->SetCellValue(row_num + counter, 3, units);
			grid_tasks->SetCellValue(row_num + counter, 4, item);
			grid_tasks->SetCellValue(row_num + counter, 5, build_orientation);
			grid_tasks->SetCellValue(row_num + counter, 6, direction_to_build);
			grid_tasks->SetCellValue(row_num + counter, 7, building_size);
			grid_tasks->SetCellValue(row_num + counter, 8, amount_of_buildings);

			it1 = tasks_data_to_save.begin();
			it1 += row_num + counter;

			tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);

			counter += 1;
		}
	}

	if (counter > 0) {
		update_buildings_grid_from_scratch();
		return;
	}

	row_num_template = 0;
	row_count_template = grid_template->GetNumberRows();

	for (int i = row_num_template; i < (row_num_template + row_count_template); i++) {
		grid_tasks->InsertRows(row_num + i);

		task = grid_template->GetCellValue(i, 0).ToStdString();
		x_cord = grid_template->GetCellValue(i, 1).ToStdString();
		y_cord = grid_template->GetCellValue(i, 2).ToStdString();
		units = grid_template->GetCellValue(i, 3).ToStdString();
		item = grid_template->GetCellValue(i, 4).ToStdString();
		build_orientation = grid_template->GetCellValue(i, 5).ToStdString();
		direction_to_build = grid_template->GetCellValue(i, 6).ToStdString();
		building_size = grid_template->GetCellValue(i, 7).ToStdString();
		amount_of_buildings = grid_template->GetCellValue(i, 8).ToStdString();

		x_cord_float = std::stof(x_cord);
		y_cord_float = std::stof(y_cord);

		x_offset = wxAtof(txt_template_x_offset->GetValue());
		y_offset = wxAtof(txt_template_y_offset->GetValue());

		x_cord = std::to_string(x_cord_float + x_offset);
		y_cord = std::to_string(y_cord_float + y_offset);

		grid_tasks->SetCellValue(row_num + i, 0, task);
		grid_tasks->SetCellValue(row_num + i, 1, x_cord);
		grid_tasks->SetCellValue(row_num + i, 2, y_cord);
		grid_tasks->SetCellValue(row_num + i, 3, units);
		grid_tasks->SetCellValue(row_num + i, 4, item);
		grid_tasks->SetCellValue(row_num + i, 5, build_orientation);
		grid_tasks->SetCellValue(row_num + i, 6, direction_to_build);
		grid_tasks->SetCellValue(row_num + i, 7, building_size);
		grid_tasks->SetCellValue(row_num + i, 8, amount_of_buildings);

		it1 = tasks_data_to_save.begin();
		it1 += row_num + i;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);
	}

	update_buildings_grid_from_scratch();

	event.Skip();
}

void cMain::OnTemplateChangeTaskClicked(wxCommandEvent& event) {
	extract_parameters();

	if (setup_for_task_grid()) {
		change_row(grid_template);

		template_name = cmb_choose_template->GetValue().ToStdString();

		if (!(template_map.find(template_name) == template_map.end())) {
			template_map[template_name][row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings);
		}		
	}

	event.Skip();
}

void cMain::OnTemplateDeleteTaskClicked(wxCommandEvent& event) {
	if (!delete_row(grid_template)) {

		event.Skip();
		return;
	}

	template_name = cmb_choose_template->GetValue().ToStdString();

	if (!(template_map.find(template_name) == template_map.end())) {
		it1 = template_map[template_name].begin();
		it2 = template_map[template_name].begin();

		it1 += row_num;
		it2 += row_num + row_count;

		template_map[template_name].erase(it1, it2);
	}

	event.Skip();
}

void cMain::OnTemplateMoveUpClicked(wxCommandEvent& event) {
	if (!move_row(grid_template, true)) {
		
		event.Skip();
		return;
	}

	template_name = cmb_choose_template->GetValue().ToStdString();

	if (!(template_map.find(template_name) == template_map.end())) {
		it1 = template_map[template_name].begin();
		it1 += row_to_move;

		data = *it1;
		template_map[template_name].erase(it1);

		it2 = template_map[template_name].begin();
		it2 += row_num + row_count - 1;
		template_map[template_name].insert(it2, data);
	}

	event.Skip();
}

void cMain::OnTemplateMoveDownClicked(wxCommandEvent& event) {
	if (!move_row(grid_template, false)) {
		
		event.Skip();
		return;
	}

	template_name = cmb_choose_template->GetValue().ToStdString();

	if (!(template_map.find(template_name) == template_map.end())) {
		it1 = template_map[template_name].begin();
		it1 += row_to_move - 1;
		it2 = template_map[template_name].begin();
		it2 += row_num;

		data = *it1;
		template_map[template_name].erase(it1, it1 + 1);
		template_map[template_name].insert(it2, data);
	}

	event.Skip();
}

void cMain::OnTemplateGridDoubleLeftClick(wxGridEvent& event) {
	row_num = event.GetRow();

	update_parameteres(grid_template, event);

	event.Skip();
}

void cMain::OnBuildingsGridLeftDoubleClick(wxGridEvent& event) {
	row_num = event.GetRow();

	x_cord = grid_buildings->GetCellValue(row_num, 0).ToStdString();
	y_cord = grid_buildings->GetCellValue(row_num, 1).ToStdString();
	item = grid_buildings->GetCellValue(row_num, 2).ToStdString();
	build_orientation = grid_buildings->GetCellValue(row_num, 3).ToStdString();

	txt_x_cord->SetValue(x_cord);
	txt_y_cord->SetValue(y_cord);
	cmb_item->SetValue(item);
	cmb_building_orientation->SetValue(build_orientation);

	event.Skip();
}

void cMain::OnDeleteTaskClicked(wxCommandEvent& event) {
	if (!delete_row(grid_tasks)) {

		event.Skip();
		return;
	}

	it1 = tasks_data_to_save.begin();
	it2 = tasks_data_to_save.begin();

	it1 += row_num;
	it2 += row_num + row_count;

	tasks_data_to_save.erase(it1, it2);	

	update_buildings_grid_from_scratch();

	event.Skip();
}

void cMain::OnMoveUpClicked(wxCommandEvent& event) {
	if (!move_row(grid_tasks, true)) {
		return;
	}

	it1 = tasks_data_to_save.begin();
	it1 += row_to_move;

	data = *it1;
	tasks_data_to_save.erase(it1);
	
	it2 = tasks_data_to_save.begin();
	it2 += row_num + row_count - 1;
	tasks_data_to_save.insert(it2, data);

	update_buildings_grid_from_scratch();

	event.Skip();
}

void cMain::OnMoveDownClicked(wxCommandEvent& event) {
	if (!move_row(grid_tasks, false)) {
		return;
	}

	it1 = tasks_data_to_save.begin();
	it1 += row_to_move - 1;
	it2 = tasks_data_to_save.begin();
	it2 += row_num;

	data = *it1;
	tasks_data_to_save.erase(it1, it1+1);
	tasks_data_to_save.insert(it2, data);

	update_buildings_grid_from_scratch();

	event.Skip();
}

void cMain::OnMenuNew(wxCommandEvent& event) {

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
	setup_paramters(parameter_choices.walk);

	save_file_location = "";
	generate_code_file_location = "";

	tasks_data_to_save = {};

	event.Skip();
}

void cMain::OnMenuOpen(wxCommandEvent& event) {
	
	wxFileDialog dlg(this, "Open saved factorio script helper file", "", "", ".txt files (*.txt) | *.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (dlg.ShowModal() == wxID_OK) {
		std::ifstream inFile;
		std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
		inFile.imbue(utf8_locale);
		inFile.open(dlg.GetPath().ToStdString());
		bool groups_reached = false;
		bool templates_reached = false;
		bool groups_in_file = false;
		bool templates_in_file = false;

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
		}

		if (grid_group->GetNumberRows() > 0) {
			grid_group->DeleteRows(0, grid_group->GetNumberRows());
		}

		if (grid_template->GetNumberRows() > 0) {
			grid_template->DeleteRows(0, grid_template->GetNumberRows());
		}

		tasks_data_to_save = {};
		save_file_location = "";
		generate_code_file_location = "";

		group_map.clear();
		cmb_choose_group->Clear();
		group_choices = {};
		group_name = "";

		template_map.clear();
		cmb_choose_template->Clear();
		template_choices = {};
		template_name = "";

		while (std::getline(inFile, open_data_string)) {
			std::stringstream data_line;
			data_line.str(open_data_string);

			seglist = {};

			while (std::getline(data_line, segment, ';')) {
				seglist.push_back(segment);
			}

			if (seglist[0] == save_groups_indicator) {
				groups_reached = true;

			} else if (seglist[0] == save_templates_indicator) {
				templates_reached = true;

			} else if (!groups_reached) {
				if (seglist.size() == 9) {
					task = seglist[0];
					x_cord = seglist[1];
					y_cord = seglist[2];
					units = seglist[3];
					item = seglist[4];
					build_orientation = seglist[5];
					direction_to_build = seglist[6];
					building_size = seglist[7];
					amount_of_buildings = seglist[8];

					update_tasks_grid();
				} else {
					wxMessageBox("It seems like the structure of the file does not correspond with a factorio script helper file", "A file error occurred");
					return;
				}
			} else if (!templates_reached) {
				groups_in_file = true;

				if (seglist.size() == 10) {

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

					group_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";");
				} else if (seglist[0] == "") {

				} else {
					wxMessageBox("It seems like the structure of the file does not correspond with a factorio script helper file", "A file error occurred");
					return;
				}
			} else {
				if (seglist.size() == 10) {
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

					template_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";");
				} else if (seglist[0] == "") {

				} else {
					wxMessageBox("It seems like the structure of the file does not correspond with a factorio script helper file", "A file error occurred");
					return;
				}
			} 
		}

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
	}

	update_buildings_grid_from_scratch();
	
	event.Skip();
}

void cMain::OnMenuSave(wxCommandEvent& event) {

	if (save_file_location == "") {
		wxFileDialog dlg(this, "Save factorio script helper", "", "", ".txt files (*.txt) | *.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (dlg.ShowModal() == wxID_OK) {
			save_file_location = dlg.GetPath().ToStdString();
		} else {
			return;
		}
	}

	save_file();

	clear_tasks();

	event.Skip();
}

void cMain::OnMenuSaveAs(wxCommandEvent& event) {

	wxFileDialog dlg(this, "Save factorio script helper", "", "", ".txt files (*.txt) | *.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (dlg.ShowModal() == wxID_OK) {
		save_file_location = dlg.GetPath().ToStdString();
	} else {
		return;
	}

	save_file();

	clear_tasks();

	event.Skip();
}

void cMain::OnMenuExit(wxCommandEvent& event) {
	event.Skip();
	Close();
}

void cMain::OnChooseLocation(wxCommandEvent& event) {
	wxFileDialog dlg(this, "Choose location to generate script", "", "", ".lua files (*.lua) | *.lua", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dlg.ShowModal() == wxID_OK) {
		generate_code_file_location = dlg.GetPath().ToStdString();
	}

	event.Skip();
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

	row_num = grid_tasks->GetNumberRows();

	for (int i = 0; i < row_num; i++) {
		task = grid_tasks->GetCellValue(i, 0).ToStdString();
		x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
		y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
		units = grid_tasks->GetCellValue(i, 3).ToStdString();
		item = convert_string(grid_tasks->GetCellValue(i, 4).ToStdString());
		build_orientation = convert_string(grid_tasks->GetCellValue(i, 5).ToStdString());
		direction_to_build = convert_string(grid_tasks->GetCellValue(i, 6).ToStdString());
		building_size = grid_tasks->GetCellValue(i, 7).ToStdString();
		amount_of_buildings = grid_tasks->GetCellValue(i, 8).ToStdString();

		if (task == "Game Speed") {
			speed(units);

		} else if (task == "Walk") {
			walk(x_cord, y_cord);

		} else if (task == "Mine") {
			mining(x_cord, y_cord, units);

		} else if (task == "Rotate") {
			rotate(x_cord, y_cord, units);

		} else if (task == "Craft") {
			if (units == "All") {
				craft("-1", item);
			} else {
				craft(units, item);
			}
			
		} else if (task == "Tech") {
			tech(item);

		} else if (task == "Build") {
			build_row_of_buildings(x_cord, y_cord, item, build_orientation, direction_to_build, amount_of_buildings, building_size);

		} else if (task == "Take") {
			from_into = extract_define(i);
			

			if (units == "All") {
				row_take(x_cord, y_cord, "-1", item, from_into, direction_to_build, amount_of_buildings, building_size);
			} else {
				row_take(x_cord, y_cord, units, item, from_into, direction_to_build, amount_of_buildings, building_size);
			}

		} else if (task == "Put") {
			from_into = extract_define(i);

			if (units == "All") {
				row_put(x_cord, y_cord, "-1", item, from_into, direction_to_build, amount_of_buildings, building_size);
			} else {
				row_put(x_cord, y_cord, units, item, from_into, direction_to_build, amount_of_buildings, building_size);
			}
		} else if (task == "Recipe") {
			row_recipe(x_cord, y_cord, item, direction_to_build, building_size, amount_of_buildings);
		} else if (task == "Stop") {
			stop(units);
		} else if (task == "Limit") {
			from_into = extract_define(i);

			limit_row(x_cord, y_cord, units, from_into, direction_to_build, amount_of_buildings, building_size);
		} else if (task == "Priority") {
			int pos = build_orientation.find(",");

			priority_in = build_orientation.substr(0, pos);
			priority_out = build_orientation.substr(pos + 2);

			priority_row(x_cord, y_cord, priority_in, priority_out, direction_to_build, amount_of_buildings, building_size);
		} else if (task == "Filter") {
			
			extract_building(i);

			if (check_item(building, splitters)) {
				filter_row(x_cord, y_cord, item, units, "splitter", direction_to_build, amount_of_buildings, building_size);
			} else {
				filter_row(x_cord, y_cord, item, units, "inserter", direction_to_build, amount_of_buildings, building_size);
			}			
		} else if (task == "Drop") {
			drop_row(x_cord, y_cord, item, direction_to_build, amount_of_buildings, building_size);

		} else if (task == "Pick up") {
			pick_row(x_cord, y_cord, direction_to_build, amount_of_buildings, building_size);

		} else if (task == "Launch") {
			launch(x_cord, y_cord);

		} else if (task== "Ilde") {
			idle(units);

		}
	}

	std::ofstream myfile;
	myfile.open(generate_code_file_location);

	myfile << end_tasks();

	myfile.close();

	clear_tasks();

	event.Skip();
}

void cMain::OnChangeShortcuts(wxCommandEvent& event) {
	shortcuts = new Shortcuts_Menu(this);
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

bool cMain::setup_for_task_grid() {

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
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

	} else if (task == "Rotate") {
		item = not_relevant;
		build_orientation = not_relevant;
		direction_to_build = not_relevant;
		building_size = not_relevant;
		amount_of_buildings = not_relevant;

		if (!update_building_orientation()) {
			wxMessageBox("Building location does not seem to exit.\nPlease use exactly the same coordinates as you used to build", "Please use the same coordinates");
			return false;
		}
	
	} else if (task == "Craft") {
		if (!check_item(item, all_items)) {
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
		if (!check_item(item, all_items)) {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
			return false;
		}

		if (!check_building(build_orientation, build_orientations)) {
			wxMessageBox("The build direction is not valid - please try again", "Please use the build direction dropdown menu");
			return false;
		}

		if (!check_building(direction_to_build, build_orientations)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return false;
		}

		units = not_relevant;

	} else if (task == "Take" || task == "Put") {

		if (!check_take_put(item, take_from)) {
			wxMessageBox("The combination of From/Into and item is not valid - please try again", "Please ensure that the combination is valid");
			return false;
		}

		if (!check_building(direction_to_build, build_orientations)) {
			wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
			return false;
		}

		build_orientation = from_into;

	} else if (task == "Tech") {
		if (!check_item(tech_to_start, tech_list)) {
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
		// This should be changed so it checks a list of items, which is valid recipes
		if (!check_item(item, all_items)) {
			wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
			return false;
		}

		units = not_relevant;
		build_orientation = not_relevant;
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

		if (!check_item(priority_in, input_output)) {
			wxMessageBox("The input priority chosen is not valid - please try again", "Please use the input dropdown menu");
			return false;
		}

		if (!check_item(priority_out, input_output)) {
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

void cMain::extract_parameters() {
	task = extract_task();
	x_cord = extract_x_cord();
	y_cord = extract_y_cord();
	units = extract_units();
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

void cMain::update_parameteres(wxGrid* grid, wxCommandEvent& event) {
	task = grid->GetCellValue(row_num, 0).ToStdString();
	x_cord = grid->GetCellValue(row_num, 1).ToStdString();
	y_cord = grid->GetCellValue(row_num, 2).ToStdString();
	units = grid->GetCellValue(row_num, 3).ToStdString();
	item = grid->GetCellValue(row_num, 4).ToStdString();
	build_orientation = grid->GetCellValue(row_num, 5).ToStdString();
	direction_to_build = grid->GetCellValue(row_num, 6).ToStdString();
	building_size = grid->GetCellValue(row_num, 7).ToStdString();
	amount_of_buildings = grid->GetCellValue(row_num, 8).ToStdString();

	if (task == "Game Speed") {
		OnGameSpeedMenuSelected(event);
		txt_units->SetValue(units);

	} else if (task == "Walk") {
		OnWalkMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);

	} else if (task == "Mine") {
		OnMineMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		txt_units->SetValue(units);

	} else if (task == "Rotate") {
		OnRotateMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		txt_units->SetValue(units);

	} else if (task == "Craft") {
		OnCraftMenuSelected(event);
		txt_units->SetValue(units);
		cmb_item->SetValue(item);

	} else if (task == "Build") {
		OnBuildMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		cmb_item->SetValue(item);
		cmb_building_orientation->SetValue(build_orientation);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);

	} else if (task == "Take") {
		OnTakeMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		txt_units->SetValue(units);
		cmb_item->SetValue(item);
		cmb_from_into->SetValue(build_orientation);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);

	} else if (task == "Put") {
		OnPutMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		txt_units->SetValue(units);
		cmb_item->SetValue(item);
		cmb_from_into->SetValue(build_orientation);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);

	} else if (task == "Tech") {
		OnTechMenuSelected(event);
		cmb_tech->SetValue(item);

	} else if (task == "Recipe") {
		OnRecipeMenuChosen(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
		cmb_item->SetValue(item);
	} else if (task == "Stop") {
		OnStopChosen(event);
		txt_units->SetValue(units);
	} else if (task == "Limit") {
		OnLimitMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		txt_units->SetValue(units);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);
	} else if (task == "Priority") {
		OnPriorityMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);

		int pos = build_orientation.find(",");

		cmb_input->SetValue(build_orientation.substr(0, pos));
		cmb_output->SetValue(build_orientation.substr(pos + 2));

	} else if (task == "Filter") {
		OnFilterMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		txt_units->SetValue(units);
		cmb_item->SetValue(item);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);

	} else if (task == "Pick up") {
		OnPickUpMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);

	} else if (task == "Drop") {
		OnDropMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
		cmb_item->SetValue(item);
		cmb_direction_to_build->SetValue(direction_to_build);
		txt_building_size->SetValue(building_size);
		txt_amount_of_buildings->SetValue(amount_of_buildings);

	} else if (task == "Idle") {
		OnIdleMenuSelected(event);
		txt_units->SetValue(units);

	} else if (task == "Launch") {
		OnLaunchMenuSelected(event);
		txt_x_cord->SetValue(x_cord);
		txt_y_cord->SetValue(y_cord);
	}
}

void cMain::update_group_map() {
	group_list = {};
	row_num = grid_group->GetNumberRows();

	for (int i = 0; i < row_num; i++) {
		task = grid_group->GetCellValue(i, 0).ToStdString();
		x_cord = grid_group->GetCellValue(i, 1).ToStdString();
		y_cord = grid_group->GetCellValue(i, 2).ToStdString();
		units = grid_group->GetCellValue(i, 3).ToStdString();
		item = grid_group->GetCellValue(i, 4).ToStdString();
		build_orientation = grid_group->GetCellValue(i, 5).ToStdString();
		direction_to_build = grid_group->GetCellValue(i, 6).ToStdString();
		building_size = grid_group->GetCellValue(i, 7).ToStdString();
		amount_of_buildings = grid_group->GetCellValue(i, 8).ToStdString();

		group_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";");
	}

	group_map[group_name] = group_list;

}

void cMain::update_template_map() {
	template_list = {};
	row_num = grid_template->GetNumberRows();

	for (int i = 0; i < row_num; i++) {
		task = grid_template->GetCellValue(i, 0).ToStdString();
		x_cord = grid_template->GetCellValue(i, 1).ToStdString();
		y_cord = grid_template->GetCellValue(i, 2).ToStdString();
		units = grid_template->GetCellValue(i, 3).ToStdString();
		item = grid_template->GetCellValue(i, 4).ToStdString();
		build_orientation = grid_template->GetCellValue(i, 5).ToStdString();
		direction_to_build = grid_template->GetCellValue(i, 6).ToStdString();
		building_size = grid_template->GetCellValue(i, 7).ToStdString();
		amount_of_buildings = grid_template->GetCellValue(i, 8).ToStdString();

		template_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + units + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";");
	}

	template_map[template_name] = template_list;

}

std::string cMain::extract_task() {

	if (rbtn_game_speed->GetValue()) {
		return "Game Speed";

	} else if (rbtn_walk->GetValue()) {
		return "Walk";

	} else if (rbtn_mine->GetValue()) {
		return "Mine";

	} else if (rbtn_rotate->GetValue()) {
		return "Rotate";

	} else if (rbtn_craft->GetValue()) {
		return "Craft";

	} else if (rbtn_build->GetValue()) {
		return "Build";

	} else if (rbtn_take->GetValue()) {
		return "Take";

	} else if (rbtn_put->GetValue()) {
		return "Put";

	} else if (rbtn_tech->GetValue()) {
		return "Tech";

	} else if (rbtn_recipe->GetValue()) {
		return "Recipe";

	} else if (rbtn_limit->GetValue()) {
		return "Limit";

	} else if (rbtn_idle->GetValue()) {
		return "Idle";

	} else if (rbtn_filter->GetValue()) {
		return "Filter";

	} else if (rbtn_priority->GetValue()) {
		return "Priority";

	} else if (rbtn_pick_up->GetValue()) {
		return "Pick up";

	} else if (rbtn_drop->GetValue()) {
		return "Drop";

	} else if (rbtn_launch->GetValue()) {
		return "Launch";

	} else if (rbtn_stop->GetValue()) {
		return "Stop";
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
	units = std::to_string(wxAtoi(txt_units->GetValue()));
	
	if (rbtn_game_speed->GetValue()) {
		if (std::stof(units) < 0.01) {
			units = "0.01";
		}
	} else if (rbtn_mine->GetValue() || rbtn_rotate->GetValue() || rbtn_stop->GetValue()) {
		if (std::stof(units) < 1) {
			units = "1";
		}
	} if (rbtn_limit->GetValue()) {
		if (std::stof(units) < 0) {
			units = "0";
		}
	} else if (rbtn_filter->GetValue()) {
		if (std::stof(units) < 1) {
			units = "1";
		} else if (std::stof(units) > 5) {
			units = "5";
		}
	} else{
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

std::string cMain::extract_priority_in() {
	priority_in = cmb_input->GetValue().ToStdString();
	string_capitalized(priority_in);

	return priority_in;
}

std::string cMain::extract_priority_out() {
	priority_out = cmb_output->GetValue().ToStdString();
	string_capitalized(priority_out);

	return priority_out;
}

std::string cMain::extract_define(int start_row) {
	if (build_orientation == "chest") {
		return take_put_list.chest;
	} else if (build_orientation == "fuel") {
		return take_put_list.fuel;
	} else {

		extract_building(start_row);

		if (building == "Lab") {
			if (build_orientation == "input") {
				return take_put_list.lab_input;
			} else if (build_orientation == "modules") {
				return take_put_list.lab_modules;
			}
		} else if (check_item(building, drills_list)) {
			if (build_orientation == "modules") {
				return take_put_list.drill_modules;
			}
		} else {
			if (build_orientation == "input") {
				return take_put_list.assembly_input;
			} else if (build_orientation == "modules") {
				return take_put_list.assembly_modules;
			} else if (build_orientation == "output") {
				return take_put_list.assembly_output;
			}
		}
	}

	return "Not Found";
}

void cMain::extract_building(int start_row) {
	
	for (int j = start_row - 1; j > -1; j--) {
		if (grid_tasks->GetCellValue(j, 0).ToStdString() == "Build") {
			if (grid_tasks->GetCellValue(j, 1).ToStdString() == x_cord && grid_tasks->GetCellValue(j, 2).ToStdString() == y_cord) {
				building = grid_tasks->GetCellValue(j, 4).ToStdString();
				break;
			}
		}
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

void cMain::save_file() {
	
	std::ofstream myfile;
	myfile.open(save_file_location);

	for (auto it = tasks_data_to_save.begin(); it < tasks_data_to_save.end(); it++) {
		myfile << *it << ";" << std::endl;
	}

	std::string name;
	std::vector<std::string> values;

	if (group_map.size()) {
		myfile << save_groups_indicator << std::endl;
		for (auto element : group_map) {

			for (auto value : element.second) {
				myfile << element.first + ";" + value << std::endl;
			}
		}
	}

	if (template_map.size()) {
		myfile << save_templates_indicator << std::endl;
		for (auto element : template_map) {

			for (auto value : element.second) {
				myfile << element.first + ";" + value << std::endl;
			}
		}
	}

	myfile.close();
}

bool cMain::check_item(const std::string& item, const std::vector<std::string>& all_items) {
	
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		if (item == *it) {
			return true;
		}
	}

	return false;
}