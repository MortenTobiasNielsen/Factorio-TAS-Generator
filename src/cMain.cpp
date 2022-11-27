#pragma once

#include "cMain.h"
#include "GUI_Base.h"
#include "utils.h"
#include "Functions.h"
#include "GenerateScript.h"
#include "SaveTas.h"
#include "OpenTas.h"
#include "search_util.h"
#include <wx/aui/auibook.h>

cMain::cMain() : GUI_Base(nullptr, wxID_ANY, window_title, wxPoint(30, 30), wxSize(1840, 950))
{
	SetIcon(icon_xpm);
	SetLabel(window_title);

	task_segments.reserve(100);
	seglist.reserve(100);

	// Ensure that realocations shouldn't be needed for a long while.
	BuildingsSnapShot.reserve(10000);
	auto invalidBuilding = new Building{
		.X = invalidBuildingX,
		.Y = 0,
		.Index = 0,
	};

	for (int i = 0; i < BuildingsSnapShot.capacity(); i++)
	{
		BuildingsSnapShot.push_back(*invalidBuilding);
	}

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

	for (auto s : all_recipes)
	{
		recipe_choices.Add(s);
	}

	all_items.insert(all_items.end(), handcrafted_list.begin(), handcrafted_list.end());
	all_items.insert(all_items.end(), assemply_level1_list.begin(), assemply_level1_list.end());
	all_items.insert(all_items.end(), assemply_level2_list.begin(), assemply_level2_list.end());
	all_items.insert(all_items.end(), chemical_plant_list.begin(), chemical_plant_list.end());
	all_items.insert(all_items.end(), filter_take_put_drop_extra_list.begin(), filter_take_put_drop_extra_list.end());
	all_items.insert(all_items.end(), raw_resource_list.begin(), raw_resource_list.end());
	all_items.insert(all_items.end(), furnace_list.begin(), furnace_list.end());

	for (auto it = building_size_list.begin(); it != building_size_list.end(); ++it)
	{
		all_buildings.push_back(it->first);
	}

	for (auto s : all_items)
	{
		item_choices.Add(s);
	}

	for (auto s : all_buildings)
	{
		building_choices.Add(s);
	}

	for (auto s : take_from)
	{
		take_from_choices.Add(s);
	}

	for (auto s : tech_list)
	{
		tech_choices.Add(s);
	}

	for (auto s : build_orientations)
	{
		building_orientation_choices.Add(s);
	}

	for (auto s : input_output)
	{
		input_output_choices.Add(s);
	}

	for (auto s : handcrafted_list)
	{
		handcrafted_choices.Add(s);
	}

	// set walk as default value and disable inputs not used
	rbtn_walk->SetValue(true);
	setup_paramters(parameter_choices.walk);

	cmb_building_orientation->Clear();
	cmb_direction_to_build->Clear();
	for (auto it = build_orientations.begin(); it < build_orientations.end(); it++)
	{
		cmb_building_orientation->Append(*it);
		cmb_direction_to_build->Append(*it);
	}
	cmb_building_orientation->SetValue(*build_orientations.begin());
	cmb_building_orientation->AutoComplete(building_orientation_choices);
	cmb_direction_to_build->SetValue(*build_orientations.begin());
	cmb_direction_to_build->AutoComplete(building_orientation_choices);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	cmb_from_into->Clear();
	for (auto it = take_from.begin(); it < take_from.end(); it++)
	{
		cmb_from_into->Append(*it);
	}
	cmb_from_into->SetValue(*take_from.begin());
	cmb_from_into->AutoComplete(take_from_choices);

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

	// split steps into seperate panel
	wxAuiNotebook* a = (wxAuiNotebook*)step_panel->GetParent();
	a->Split(3, wxRIGHT);
}

void cMain::TaskSeachOnText(wxCommandEvent& event)
{
	search::findCurrentOrNext(event, grid_tasks);
	event.Skip();
}

void cMain::TaskSeachOnTextEnter(wxCommandEvent& event)
{
	TaskSeachOnText(event);//seems not to fire
}

void cMain::TaskSeachOnSearchButton(wxCommandEvent& event)
{
	search::findNext(event, grid_tasks);
	event.Skip();
}

void cMain::TaskSeachOnCancelButton(wxCommandEvent& event)
{
	event.Skip();// do nothing, it will clear the search box
}

void cMain::BuildingSearchOnText(wxCommandEvent& event)
{
	search::findCurrentOrNext(event, grid_buildings, false);
	event.Skip();
}

void cMain::BuildingSearchOnTextEnter(wxCommandEvent& event)
{
	BuildingSearchOnText(event);//seems not to fire
}

void cMain::BuildingSearchOnSearchButton(wxCommandEvent& event)
{
	search::findNext(event, grid_buildings, false);
	event.Skip();
}

void cMain::BuildingSearchOnCancelButton(wxCommandEvent& event)
{
	event.Skip();// do nothing, it will clear the search box
}

void cMain::reset_to_new_window()
{
	if (grid_tasks->GetNumberRows() > 0 || grid_buildings->GetNumberRows() > 0 || grid_group->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0)
	{
		if (grid_tasks->GetNumberRows() > 0)
		{
			grid_tasks->DeleteRows(0, grid_tasks->GetNumberRows());
		}

		if (grid_buildings->GetNumberRows() > 0)
		{
			grid_buildings->DeleteRows(0, grid_buildings->GetNumberRows());
		}

		if (grid_group->GetNumberRows() > 0)
		{
			grid_group->DeleteRows(0, grid_group->GetNumberRows());
		}

		if (grid_template->GetNumberRows() > 0)
		{
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

	if (dialog_progress_bar)
	{
		dialog_progress_bar->Hide();
	}

	SetLabel(window_title);
}

bool cMain::check_before_close()
{
	if (grid_tasks->GetNumberRows() > 0 || grid_buildings->GetNumberRows() > 0 || grid_group->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0)
	{
		int answer = wxMessageBox("Do you want to save your changes?", "Ensure that you have saved what you need", wxICON_QUESTION | wxYES_NO | wxCANCEL, this);

		if (answer == wxYES)
		{
			return save_file(false);

		}
		else if (answer == wxNO)
		{
			return true;
		}
	}

	return true;
}

void cMain::move_row(wxGrid* grid, bool up)
{
	for (const auto& block : grid->GetSelectedRowBlocks())
	{
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		if (up)
		{
			if (row_num == 0)
			{
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

		}
		else
		{
			if ((row_num + row_count) == (grid->GetNumberRows()))
			{
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
}

void cMain::group_template_move_row(wxGrid* grid, wxComboBox* cmb, bool up, std::map<std::string, std::vector<std::string>>& map)
{
	if (!grid->IsSelection() || !grid->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	for (const auto& block : grid->GetSelectedRowBlocks())
	{
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		if (up)
		{
			if (row_num == 0)
			{
				continue;
			}

			row_to_move = row_num - 1;

		}
		else
		{
			if ((row_num + row_count) == (grid->GetNumberRows()))
			{
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

		if (!map.empty())
		{
			std::string map_name = cmb->GetValue().ToStdString();
			if (map.find(map_name) != map.end())
			{
				if (up)
				{

					it1 = map[map_name].begin();
					it1 += row_to_move;

					data = *it1;
					map[map_name].erase(it1);

					it2 = map[map_name].begin();
					it2 += row_num + row_count - 1;
					map[map_name].insert(it2, data);
				}
				else
				{
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
bool cMain::delete_row(wxGrid* grid, wxComboBox* cmb, std::map<std::string, std::vector<std::string>>& map)
{
	if (!grid->IsSelection())
	{
		wxMessageBox("Please select row(s) to be deleted", "Selection not valid");
		return false;
	}

	row_selections.clear();

	for (const auto& block : grid->GetSelectedRowBlocks())
	{
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		row_selections.push_back(std::to_string(block.GetTopRow()) + "," + std::to_string(block.GetBottomRow() - block.GetTopRow() + 1));
	}

	building_row_count = 0;

	for (auto selection : row_selections)
	{
		long long pos = selection.find(",");

		row_num = std::stoi(selection.substr(0, pos)) - building_row_count;
		row_count = std::stoi(selection.substr(pos + 1));

		grid->DeleteRows(row_num, row_count);

		if (!map.empty())
		{
			std::string map_name = cmb->GetValue().ToStdString();

			if (map.find(map_name) != map.end())
			{
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
bool cMain::change_row(wxGrid* grid)
{
	if (!grid->IsSelection() || !grid->GetSelectedRows().begin())
	{
		wxMessageBox("Please select a row to change", "Selection not valid");
		return false;
	}

	row_num = *grid->GetSelectedRows().begin();

	setup_for_task_group_template_grid();

	grid_insert_data(row_num, grid);

	background_colour_update(grid, row_num, task);

	return true;
}

void cMain::background_colour_update(wxGrid* grid, int row, std::string task)
{
	switch (TaskNames.find(task)->second)
	{
		case e_start:
			grid->SetCellBackgroundColour(row, 0, *wxGREEN);
			return;
		case e_stop:
			grid->SetCellBackgroundColour(row, 0, *wxRED);
			return;
		case e_build:
			grid->SetCellBackgroundColour(row, 0, *wxCYAN);
			return;
		case e_craft:
			grid->SetCellBackgroundColour(row, 0, *wxLIGHT_GREY);
			return;
		case e_game_speed:
		case e_pause:
		case e_save:
			grid->SetCellBackgroundColour(row, 0, *wxYELLOW);
			return;
		default:
			grid->SetCellBackgroundColour(row, 0, *wxWHITE);
	}
}

// ensure that the variables are actually what they are supposed to be
void cMain::update_tasks_grid()
{

	if (grid_tasks->IsSelection())
	{
		if (!grid_tasks->GetSelectedRows().begin())
		{
			return;
		}
		row_num = *grid_tasks->GetSelectedRows().begin();
	}
	else
	{
		row_num = grid_tasks->GetNumberRows();
	}

	grid_tasks->InsertRows(row_num, 1);

	grid_tasks->SetCellValue(row_num, 0, task);
	grid_tasks->SetCellValue(row_num, 1, x_cord);
	grid_tasks->SetCellValue(row_num, 2, y_cord);
	grid_tasks->SetCellValue(row_num, 3, amount);
	grid_tasks->SetCellValue(row_num, 4, item);
	grid_tasks->SetCellValue(row_num, 5, build_orientation);
	grid_tasks->SetCellValue(row_num, 6, direction_to_build);
	grid_tasks->SetCellValue(row_num, 7, building_size);
	grid_tasks->SetCellValue(row_num, 8, amount_of_buildings);
	grid_tasks->SetCellValue(row_num, 9, comment);

	if (grid_tasks->IsSelection())
	{
		it1 = tasks_data_to_save.begin();
		it1 += row_num;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	}
	else
	{
		tasks_data_to_save.push_back(task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	}

	background_colour_update(grid_tasks, row_num, task);
}

// Ensure that the variables are actually what they are supposed to be and have not been altered by side functions
void cMain::update_buildings_grid()
{
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
void cMain::update_buildings_grid_from_scratch(int start_row, int end_row)
{
	if (start_row == 0 && grid_buildings->GetNumberRows() > 0)
	{
		grid_buildings->DeleteRows(0, grid_buildings->GetNumberRows());
	}

	for (int i = start_row; i < end_row; i++)
	{
		In_memory_extract_parameters_buildings(tasks_data_to_save[i]);
		task_number = std::to_string(i + 1);

		switch (TaskNames.find(task)->second)
		{
			case e_build:
				update_buildings();
				break;

			case e_recipe:
				if (!update_recipe())
				{
					wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
					return;
				}
				break;

			case e_limit:
				if (!update_limit())
				{
					wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
					return;
				}
				break;

			case e_priority:
			{
				long long pos = building_build_orientation.find(",");

				building_priority_in = building_build_orientation.substr(0, pos);
				building_priority_out = building_build_orientation.substr(pos + 2);
			}

			if (!update_priority())
			{
				wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
				return;
			}
			break;

			case e_filter:
				if (!update_filter())
				{
					wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
					return;
				}
				break;

			case e_rotate:
				if (grid_buildings->GetNumberRows() == 0)
				{
					wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
					return;
				}

				for (int j = 0; j < grid_buildings->GetNumberRows(); j++)
				{
					if (grid_buildings->GetCellValue(j, 0).ToStdString() == building_x_cord && grid_buildings->GetCellValue(j, 1).ToStdString() == building_y_cord)
					{
						grid_buildings->SetCellValue(j, 3, building_build_orientation);
						break;
					}

					if (j == grid_buildings->GetNumberRows())
					{
						wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
						return;
					}
				}
				break;

			case e_mine:
				if (find_building(1))
				{
					grid_buildings->DeleteRows(building_row_num);
				}
				break;

			case e_put: // fallthrough
			case e_take:
				if (building_build_orientation != "Wreck")
				{
					building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
					for (int j = 0; j < building_amount_of_buildings_int; j++)
					{

						if (!find_building(building_amount_of_buildings_int))
						{
							wxMessageBox("Task: " + task_number + no_longer_connected, no_longer_connected_heading);
							return;
						}

						find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
					}
				}
				break;

			default: break;
		}
	}
}

void cMain::update_buildings()
{
	limit = "";
	recipe = "";
	building_priority_in = "";
	building_priority_out = "";
	filter = "";

	update_buildings_grid();

	int amount_of_buildings = std::stoi(building_amount_of_buildings);
	for (int i = 1; i < amount_of_buildings; i++)
	{
		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
		update_buildings_grid();
	}
}

bool cMain::update_recipe()
{
	building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
	for (int i = 0; i < building_amount_of_buildings_int; i++)
	{
		if (find_building(building_amount_of_buildings_int))
		{
			grid_buildings->SetCellValue(building_row_num, 5, building_item);
		}
		else
		{
			return false;
		}

		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
	}

	return true;
}

bool cMain::update_limit()
{
	building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
	for (int i = 0; i < std::stoi(building_amount_of_buildings); i++)
	{
		if (find_building(building_amount_of_buildings_int))
		{
			grid_buildings->SetCellValue(building_row_num, 4, building_units);
		}
		else
		{
			return false;
		}

		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
	}
	return true;
}

bool cMain::update_priority()
{
	building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
	for (int i = 0; i < building_amount_of_buildings_int; i++)
	{
		if (find_building(building_amount_of_buildings_int))
		{
			grid_buildings->SetCellValue(building_row_num, 6, building_priority_in);
			grid_buildings->SetCellValue(building_row_num, 7, building_priority_out);
		}
		else
		{
			return false;
		}

		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
	}

	return true;
}

bool cMain::update_filter()
{
	building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
	for (int i = 0; i < building_amount_of_buildings_int; i++)
	{
		if (find_building(building_amount_of_buildings_int))
		{
			grid_buildings->SetCellValue(building_row_num, 8, building_item);
		}
		else
		{
			return false;
		}

		find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
	}

	return true;
}

bool cMain::Update_rotation()
{
	if (find_building(1))
	{
		building_build_orientation = grid_buildings->GetCellValue(building_row_num, 5);

		find_new_orientation();

		grid_buildings->SetCellValue(building_row_num, 3, building_build_orientation);

		return true;
	}

	return false;
}

void cMain::update_group_template_grid(wxGrid* grid, std::vector<std::string>& list, std::map<std::string, std::vector<std::string>>& map, std::string map_name)
{
	if (grid->GetNumberRows() > 0)
	{
		grid->DeleteRows(0, grid->GetNumberRows());
	}

	list = map[map_name];
	grid->InsertRows(0, list.size());

	for (unsigned int i = 0; i < list.size(); i++)
	{
		std::stringstream data_line;
		data_line.str(list[i]);
		seglist = {};

		while (std::getline(data_line, segment, ';'))
		{
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

		if (seglist.size() > 9)
		{
			grid->SetCellValue(i, 9, seglist[9]);
		}

		background_colour_update(grid, i, seglist[0]);
	}
}

// You have chosen not to implement a check to see if there are already a building at the location, given that it would open for a lot of concerns about fast replaceing buildings 
void cMain::OnAddTaskClicked(wxCommandEvent& event)
{
	if (grid_tasks->IsSelection())
	{
		if (!grid_tasks->GetSelectedRows().begin())
		{
			return;
		}

		row_num = *grid_tasks->GetSelectedRows().begin();
	}
	else
	{
		row_num = grid_tasks->GetNumberRows();
	}

	auto stepParameters = ExtractStepParameters();

	if (stepParameters.TaskEnum == e_build)
	{
		if (!IsValidBuildStep(stepParameters))
		{
			return;
		}

		stepParameters.BuildingIndex = BuildingNameToIndex.find(stepParameters.Item.ToStdString())->second;

		new_update_tasks_grid(&stepParameters);

		std::string to_check = stepParameters.Item.ToStdString();
		string_capitalized(to_check);

		if (check_furnace->IsChecked() && to_check == struct_auto_put_furnace_list.stone || to_check == struct_auto_put_furnace_list.steel)
		{
			stepParameters.TaskEnum = e_put;
			stepParameters.Task = struct_tasks_list.put;
			stepParameters.Amount = "1";
			stepParameters.Item = struct_fuel_list.coal;
			stepParameters.FromInto = struct_from_into_list.fuel;

			new_update_tasks_grid(&stepParameters);
		}

		if (check_burner->IsChecked() && to_check == struct_auto_put_burner_list.burner_mining_drill || to_check == struct_auto_put_burner_list.burner_inserter || to_check == struct_auto_put_burner_list.boiler)
		{
			stepParameters.TaskEnum = e_put;
			stepParameters.Task = struct_tasks_list.put;
			stepParameters.Amount = "1";
			stepParameters.Item = struct_fuel_list.coal;
			stepParameters.FromInto = struct_from_into_list.fuel;

			new_update_tasks_grid(&stepParameters);
		}

		if (check_lab->IsChecked() && to_check == struct_science_list.lab)
		{
			stepParameters.TaskEnum = e_put;
			stepParameters.Task = struct_tasks_list.put;
			stepParameters.Amount = "1";
			stepParameters.Item = "Automation science pack";
			stepParameters.FromInto = struct_from_into_list.input;

			new_update_tasks_grid(&stepParameters);
		}

		event.Skip();
		return;
	}

	if (stepParameters.TaskEnum == e_craft)
	{
		if (!IsValidCraftStep(stepParameters))
		{
			return;
		}

		new_update_tasks_grid(&stepParameters);
	}

	int amountOfBuildings = GenerateBuildingSnapShot(row_num);

	if (stepParameters.TaskEnum == e_recipe)
	{
		for (int i = 0; i < stepParameters.Buildings; i++)
		{
			for (int j = amountOfBuildings - 1; j > -1; j--)
			{
				if (stepParameters == BuildingsSnapShot[j])
				{
					if (IsValidRecipeStep(stepParameters))
					{
						break;
					}
					
					wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
					return;
				}

				if (j == 0)
				{
					wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
					return;
				}
			}

			stepParameters.Next();
		}

		stepParameters.Reset();

		new_update_tasks_grid(&stepParameters);

		std::string to_check = stepParameters.Item.ToStdString();
		string_capitalized(to_check);

		if (check_recipe->IsChecked())
		{
			std::vector<std::string> recipe = recipes.find(to_check)->second;

			int multiplier = std::stoi(stepParameters.Amount);
			for (int i = 0; i < recipe.size(); i += 2)
			{
				stepParameters.TaskEnum = e_put;
				stepParameters.Task = struct_tasks_list.put;
				stepParameters.Amount = std::to_string(stoi(recipe[i + 1]) * multiplier);
				stepParameters.Item = recipe[i];
				stepParameters.FromInto = struct_from_into_list.input;

				new_update_tasks_grid(&stepParameters);
			}
		}

		event.Skip();
		return;
	}

	if (stepParameters.TaskEnum == e_put || task == e_take)
	{
		if (!IsValidPutTakeStep(stepParameters))
		{
			return;
		}

		new_update_tasks_grid(&stepParameters);
	}

	if (stepParameters.TaskEnum == e_tech)
	{
		if (!IsValidTechStep(stepParameters))
		{
			return;
		}

		new_update_tasks_grid(&stepParameters);
	}

	if (stepParameters.TaskEnum == e_priority)
	{
		new_update_tasks_grid(&stepParameters);
	}




	if (task == e_mine || task == e_limit || task == e_filter || task == e_rotate || task == e_launch)
	{
		if (check_buildings_grid())
		{
			if (setup_for_task_group_template_grid())
			{

				update_tasks_grid();

				std::string base_units = "1";
				std::string to_check = item;
				string_capitalized(to_check);

				if (task == struct_tasks_list.build)
				{
					if (check_furnace->IsChecked() && to_check == struct_auto_put_furnace_list.stone || to_check == struct_auto_put_furnace_list.steel)
					{
						auto_put(struct_fuel_list.coal, base_units, struct_from_into_list.fuel);
					}

					if (check_burner->IsChecked() && to_check == struct_auto_put_burner_list.burner_mining_drill || to_check == struct_auto_put_burner_list.burner_inserter || to_check == struct_auto_put_burner_list.boiler)
					{
						auto_put(struct_fuel_list.coal, base_units, struct_from_into_list.fuel);
					}

					if (check_lab->IsChecked() && to_check == struct_science_list.lab)
					{
						auto_put("Automation science pack", base_units, struct_from_into_list.input);
					}
				}

				if (task == struct_tasks_list.recipe && check_recipe->IsChecked())
				{
					std::vector<std::string> recipe = recipes.find(to_check)->second;

					int multiplier = std::stoi(amount);
					for (int i = 0; i < recipe.size(); i += 2)
					{
						std::string units_to_put = std::to_string(stoi(recipe[i + 1]) * multiplier);
						auto_put(recipe[i], units_to_put, struct_from_into_list.input);
					}
				}
			}
		}
	}
	else
	{
		if (setup_for_task_group_template_grid())
		{
			update_tasks_grid();
		}
	}

	event.Skip();
}

// It has been chosen to not make massive checks when a task is changed, given that it would be very complicated
void cMain::OnChangeTaskClicked(wxCommandEvent& event)
{
	extract_parameters();

	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select a row to change", "Selection not valid");
		event.Skip();
		return;
	}

	row_num = *grid_tasks->GetSelectedRows().begin();

	// setup buildingsgrid and ensure the building exists
	auto t = TaskNames.find(task)->second;
	if (t == e_mine || t == e_recipe || t == e_build || t == e_limit || t == e_priority || t == e_filter || t == e_rotate || t == e_put || t == e_take || t == e_launch)
	{
		if (row_num != grid_tasks->GetNumberRows())
		{
			update_buildings_grid_from_scratch(0, row_num);
		}

		building_task = task;
		building_x_cord = x_cord;
		building_y_cord = y_cord;
		building_units = amount;
		building_comment = comment;
		building_item = item;
		building_build_orientation = build_orientation;
		building_direction_to_build = direction_to_build;
		building_building_size = building_size;
		building_amount_of_buildings = amount_of_buildings;
		building_priority_in = priority_in;
		building_priority_out = priority_out;

		if (!check_buildings_grid() || !setup_for_task_group_template_grid())
		{
			if (row_num != grid_tasks->GetNumberRows())
			{
				update_buildings_grid_from_scratch(row_num, grid_tasks->GetNumberRows());
			}

			event.Skip();
			return;
		}
	}

	if (task == "Build" && grid_tasks->GetCellValue(row_num, 0) == "Build")
	{
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

		for (int i = 0; i < std::stoi(building_amount_of_buildings); i++)
		{
			for (int j = row_num + 1; j < total_rows; j++)
			{
				if (grid_tasks->GetCellValue(j, 1) == building_x_cord && grid_tasks->GetCellValue(j, 2) == building_y_cord)
				{
					if (grid_tasks->GetCellValue(j, 0) == "Mine")
					{
						break;
					}
					if (std::find(changed_rows.begin(), changed_rows.end(), j) == changed_rows.end())
					{
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
	tasks_data_to_save[row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());

	event.Skip();
}

void cMain::OnDeleteTaskClicked(wxCommandEvent& event)
{
	if (!grid_tasks->IsSelection())
	{
		wxMessageBox("Please select row(s) to be deleted", "Selection not valid");
		return;
	}

	if (wxMessageBox("Are you sure you want to delete this task?", "Delete task", wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		return;
	}

	int counter = 1;

	row_selections.clear();

	// Find the first block of rows selected - extract the first row and the amount of rows in the block
	for (const auto& block : grid_tasks->GetSelectedRowBlocks())
	{
		if (counter == 1)
		{
			building_row_num = block.GetTopRow();
			building_row_count = block.GetBottomRow() - building_row_num + 1;

			counter++;
		}
		else
		{
			row_selections.push_back(std::to_string(block.GetTopRow()) + "," + std::to_string(block.GetBottomRow() - block.GetTopRow() + 1));
		}
	}

	// If the last row of the block is also the tasks_grid's last row then the rows are just deleted
	if ((building_row_num + building_row_count) == grid_tasks->GetNumberRows())
	{
		grid_tasks->DeleteRows(building_row_num, building_row_count);

	}
	else
	{
		// Otherwise the rows are run through to see if at least one of the tasks is a build task
		for (int i = building_row_num; i < (building_row_num + building_row_count); i++)
		{
			building_task = grid_tasks->GetCellValue(i, 0).ToStdString();

			if (building_task == "Build")
			{
				if (wxMessageBox("At least one of the rows selected is a build task - are you sure you want to delete the rows selected?\nAll future tasks associated with the building(s) will be removed to avoid issues.", "The build task(s) you are deleting could be associated with future tasks", wxICON_QUESTION | wxYES_NO, this) != wxYES)
				{
					return;
				}
				else
				{
					break;
				}
			}
		}

		// The rows are run through, if there are no build tasks or the user gives permission to delete the build tasks
		int total_rows = building_row_num + building_row_count;
		int main_lines_deleted = 0;

		for (int i = building_row_num; i < total_rows; i++)
		{
			building_task = grid_tasks->GetCellValue(i, 0).ToStdString();

			if (building_task == "Build")
			{
				building_x_cord = grid_tasks->GetCellValue(i, 1).ToStdString();
				building_y_cord = grid_tasks->GetCellValue(i, 2).ToStdString();
				building_direction_to_build = grid_tasks->GetCellValue(i, 6).ToStdString();
				building_building_size = grid_tasks->GetCellValue(i, 7).ToStdString();
				building_amount_of_buildings = grid_tasks->GetCellValue(i, 8).ToStdString();

				// The current row is a build task and each building of the task are run through to check for associated tasks 
				for (int j = 0; j < std::stoi(building_amount_of_buildings); j++)
				{
					int total_rows_inner = grid_tasks->GetNumberRows();

					// All of the future tasks on the tasks grid are run through
					for (int k = (building_row_num + building_row_count - main_lines_deleted); k < total_rows_inner; k++)
					{
						if (grid_tasks->GetCellValue(k, 1).ToStdString() == building_x_cord && grid_tasks->GetCellValue(k, 2).ToStdString() == building_y_cord)
						{
							if (grid_tasks->GetCellValue(k, 0).ToStdString() == "Mine" || grid_tasks->GetCellValue(k, 0).ToStdString() == "Build")
							{
								break;
							}

							grid_tasks->DeleteRows(k);
							it1 = tasks_data_to_save.begin();
							it1 += k + main_lines_deleted;
							tasks_data_to_save.erase(it1);

							k--;
							total_rows_inner--;
						}
						else if (grid_tasks->GetCellValue(k, 0).ToStdString() == "Build")
						{
							if (wxAtoi(grid_tasks->GetCellValue(k, 8)) > 1)
							{
								x_cord = grid_tasks->GetCellValue(k, 1).ToStdString();
								y_cord = grid_tasks->GetCellValue(k, 2).ToStdString();
								direction_to_build = grid_tasks->GetCellValue(k, 6).ToStdString();
								building_size = grid_tasks->GetCellValue(k, 7).ToStdString();
								amount_of_buildings = grid_tasks->GetCellValue(k, 8).ToStdString();

								for (int l = 1; l < std::stoi(amount_of_buildings); l++)
								{
									find_coordinates(x_cord, y_cord, direction_to_build, building_size);
									if (x_cord == building_x_cord && y_cord == building_y_cord)
									{
										k = total_rows_inner;
										break;
									}
								}
							}
						}
					}

					find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
				}

			}
			else if (building_task == "Rotate")
			{
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
	if (counter == 1)
	{
		grid_tasks->SelectRow(building_row_num);
	}
	else
	{
		// Otherwise the other selections are selected once more
		grid_tasks->ClearSelection();
		for (auto selection : row_selections)
		{
			long long pos = selection.find(",");

			row_num = std::stoi(selection.substr(0, pos)) - building_row_count;
			row_count = std::stoi(selection.substr(pos + 1));

			int total_rows = row_num + row_count;

			for (int i = row_num; i < total_rows; i++)
			{
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
void cMain::OnMoveUpClicked(wxCommandEvent& event)
{
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}
	move_row(grid_tasks, true);
	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());
	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnMoveDownClicked(wxCommandEvent& event)
{
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}
	move_row(grid_tasks, false);
	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());
	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnMoveUpFiveClicked(wxMouseEvent& event)
{
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}
	for (int i = 0; i < 5; i++)
	{
		move_row(grid_tasks, true);
	}
	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());
	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnMoveDownFiveClicked(wxMouseEvent& event)
{
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}
	for (int i = 0; i < 5; i++)
	{
		move_row(grid_tasks, false);
	}
	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());
	event.Skip();
}

void cMain::OnTasksGridDoubleLeftClick(wxGridEvent& event)
{
	row_num = event.GetRow();

	update_parameters(grid_tasks, event);

	event.Skip();
}


void cMain::OnNewGroupClicked(wxCommandEvent& event)
{

	group_row_count = cmb_choose_group->GetCount();
	group_name = cmb_choose_group->GetValue().ToStdString();

	if (group_name == "")
	{
		wxMessageBox("Please write a group name", "Group name cannot be blank");
		event.Skip();
		return;
	}

	for (int i = 0; i < group_row_count; i++)
	{
		if (group_name == cmb_choose_group->GetString(i).ToStdString())
		{
			wxMessageBox("Group names have to be unique - please write a new name in the Choose Group field", "Group names should be unique");
			event.Skip();
			return;
		}
	}

	if (grid_group->IsSelection() && !grid_group->GetSelectedRows().begin())
	{
		wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
		event.Skip();
		return;
	}

	cmb_choose_group->Clear();
	group_choices.Add(group_name);
	cmb_choose_group->Append(group_choices);
	cmb_choose_group->SetValue(group_name);
	group_list = {};

	if (grid_group->IsSelection())
	{
		group_row_num = *grid_group->GetSelectedRows().begin();
		group_row_count = grid_group->GetSelectedRows().GetCount();
	}
	else
	{
		group_row_num = 0;
		group_row_count = grid_group->GetNumberRows();

		if (!group_row_count)
		{
			group_map.insert(std::pair<std::string, std::vector<std::string>>(group_name, group_list));
			event.Skip();
			return;
		}
	}

	for (int i = group_row_num; i < (group_row_num + group_row_count); i++)
	{
		grid_extract_parameters(i, grid_group);

		group_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

		background_colour_update(grid_group, i, task);
	}

	group_map.insert(std::pair<std::string, std::vector<std::string>>(group_name, group_list));

	update_group_template_grid(grid_group, group_list, group_map, group_name);

	event.Skip();
}

void cMain::OnDeleteGroupClicked(wxCommandEvent& event)
{
	if (wxMessageBox("Are you sure you want to delete this group?", "Delete group", wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		return;
	}

	group_name = cmb_choose_group->GetValue();

	if (group_map.find(group_name) != group_map.end())
	{
		group_map.erase(group_name);
		group_choices.Remove(group_name);
		cmb_choose_group->Clear();
		cmb_choose_group->Append(group_choices);

		if (group_choices.size())
		{
			cmb_choose_group->SetValue(*group_choices.begin());
			OnGroupChosen(event);
		}
		else if (grid_group->GetNumberRows())
		{
			grid_group->DeleteRows(0, grid_group->GetNumberRows());
		}
	}

	event.Skip();
}

void cMain::OnGroupAddFromTasksListClicked(wxCommandEvent& event)
{
	if (!grid_tasks->IsSelection())
	{
		wxMessageBox("No task is chosen - please select row(s) in the task list", "Cannot add task to group");
		event.Skip();
		return;
	}

	if (grid_group->IsSelection())
	{
		if (!grid_group->GetSelectedRows().begin())
		{
			wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
			event.Skip();
			return;
		}
		group_row_num = *grid_group->GetSelectedRows().begin();
	}
	else
	{
		group_row_num = grid_group->GetNumberRows();
	}

	for (const auto& block : grid_tasks->GetSelectedRowBlocks())
	{
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		grid_group->InsertRows(group_row_num, row_count);

		int total_rows = row_num + row_count;

		for (int i = row_num; i < total_rows; i++)
		{

			grid_extract_parameters(i, grid_tasks);

			grid_insert_data(group_row_num, grid_group);

			background_colour_update(grid_group, group_row_num, grid_tasks->GetCellValue(i, 0).ToStdString());

			group_row_num += 1;
		}
	}

	if (group_map.find(cmb_choose_group->GetValue().ToStdString()) != group_map.end())
	{
		update_group_map();
	}
}

// You have chosen to exclude the checks normally made when adding a task to the task list, given the increased complexity of handling multiple tasks at once
void cMain::OnGroupAddToTasksListClicked(wxCommandEvent& event)
{
	if (grid_tasks->IsSelection())
	{
		if (!grid_tasks->GetSelectedRows().begin())
		{
			wxMessageBox("Please either select row(s) or nothing", "Task list selection not valid");
		}
		else
		{
			row_num = *grid_tasks->GetSelectedRows().begin();
		}

	}
	else
	{
		row_num = grid_tasks->GetNumberRows();
	}

	bool check = false;

	for (const auto& block : grid_group->GetSelectedRowBlocks())
	{
		group_row_num = block.GetTopRow();
		group_row_count = block.GetBottomRow() - group_row_num + 1;

		grid_tasks->InsertRows(row_num, group_row_count);

		int total_rows = group_row_num + group_row_count;

		for (int i = group_row_num; i < total_rows; i++)
		{

			grid_extract_parameters(i, grid_group);

			grid_insert_data(row_num, grid_tasks);

			it1 = tasks_data_to_save.begin();
			it1 += row_num;

			tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

			background_colour_update(grid_tasks, row_num, task);

			row_num += 1;

			check = true;
		}
	}

	if (check)
	{
		update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());
		event.Skip();
		return;
	}

	group_row_count = grid_group->GetNumberRows();
	grid_tasks->InsertRows(row_num, group_row_count);

	for (int i = 0; i < group_row_count; i++)
	{

		grid_extract_parameters(i, grid_group);

		grid_insert_data(row_num, grid_tasks);

		it1 = tasks_data_to_save.begin();
		it1 += row_num;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

		background_colour_update(grid_tasks, row_num, task);

		row_num += 1;
	}

	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());

	event.Skip();
}

void cMain::In_memory_extract_parameters(const std::string& task_reference)
{
	split_task(task_reference);

	task = task_segments[0];
	x_cord = task_segments[1];
	y_cord = task_segments[2];
	amount = task_segments[3];
	item = task_segments[4];
	build_orientation = task_segments[5];
	direction_to_build = task_segments[6];
	building_size = task_segments[7];
	amount_of_buildings = task_segments[8];
	comment = task_segments[9];
}

void cMain::In_memory_extract_parameters_buildings(const std::string& task_reference)
{
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

void cMain::split_task(const std::string& task_reference)
{

	std::stringstream data_line;
	data_line.str(task_reference);

	task_segments = {};

	while (std::getline(data_line, segment, ';'))
	{
		task_segments.push_back(segment);
	}
}

void cMain::grid_extract_parameters(const int& row, wxGrid* grid)
{
	task = grid->GetCellValue(row, 0).ToStdString();
	x_cord = grid->GetCellValue(row, 1).ToStdString();
	y_cord = grid->GetCellValue(row, 2).ToStdString();
	amount = grid->GetCellValue(row, 3).ToStdString();
	item = grid->GetCellValue(row, 4).ToStdString();
	build_orientation = grid->GetCellValue(row, 5).ToStdString();
	direction_to_build = grid->GetCellValue(row, 6).ToStdString();
	building_size = grid->GetCellValue(row, 7).ToStdString();
	amount_of_buildings = grid->GetCellValue(row, 8).ToStdString();
	comment = grid->GetCellValue(row, 9).ToStdString();
}

void cMain::grid_insert_data(const int& row, wxGrid* grid)
{
	grid->SetCellValue(row, 0, task);
	grid->SetCellValue(row, 1, x_cord);
	grid->SetCellValue(row, 2, y_cord);
	grid->SetCellValue(row, 3, amount);
	grid->SetCellValue(row, 4, item);
	grid->SetCellValue(row, 5, build_orientation);
	grid->SetCellValue(row, 6, direction_to_build);
	grid->SetCellValue(row, 7, building_size);
	grid->SetCellValue(row, 8, amount_of_buildings);
	grid->SetCellValue(row, 9, comment);
}

// You have chosen to exclude the checks normally made when adding a task to the task list, given the increased complexity of handling multiple tasks at once
void cMain::OnGroupChangeClicked(wxCommandEvent& event)
{
	extract_parameters();

	if (setup_for_task_group_template_grid())
	{
		change_row(grid_group);

		group_name = cmb_choose_group->GetValue().ToStdString();

		if (!(group_map.find(group_name) == group_map.end()))
		{
			group_map[group_name][row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
		}
	}

	event.Skip();
}

void cMain::OnGroupDeleteClicked(wxCommandEvent& event)
{
	if (wxMessageBox("Are you sure you want to delete this group task?", "Delete group task", wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		return;
	}

	delete_row(grid_group, cmb_choose_group, group_map);

	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnGroupMoveUpClicked(wxCommandEvent& event)
{
	group_template_move_row(grid_group, cmb_choose_group, true, group_map);

	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnGroupMoveDownClicked(wxCommandEvent& event)
{
	group_template_move_row(grid_group, cmb_choose_group, false, group_map);

	event.Skip();
}

void cMain::OnGroupGridDoubleLeftClick(wxGridEvent& event)
{
	row_num = event.GetRow();

	update_parameters(grid_group, event);

	event.Skip();
}

void cMain::OnGroupChosen(wxCommandEvent& event)
{
	group_name = cmb_choose_group->GetValue();
	update_group_template_grid(grid_group, group_list, group_map, group_name);;

	event.Skip();
}

void cMain::OnTemplateChosen(wxCommandEvent& event)
{
	template_name = cmb_choose_template->GetValue();
	update_group_template_grid(grid_template, template_list, template_map, template_name);

	event.Skip();
}

void cMain::OnNewTemplateClicked(wxCommandEvent& event)
{
	row_count = cmb_choose_template->GetCount();
	template_name = cmb_choose_template->GetValue().ToStdString();

	if (template_name == "")
	{
		wxMessageBox("Please write a template name", "Template name cannot be blank");
		event.Skip();
		return;
	}

	for (int i = 0; i < row_count; i++)
	{
		if (template_name == cmb_choose_template->GetString(i).ToStdString())
		{
			wxMessageBox("Template names have to be unique - please write a new name in the Choose Template field", "Template names should be unique");
			event.Skip();
			return;
		}
	}

	if (grid_template->IsSelection() && !grid_template->GetSelectedRows().begin())
	{
		wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
		event.Skip();
		return;
	}

	cmb_choose_template->Clear();
	template_choices.Add(template_name);
	cmb_choose_template->Append(template_choices);
	cmb_choose_template->SetValue(template_name);
	template_list = {};

	if (grid_template->IsSelection())
	{

		row_num = *grid_template->GetSelectedRows().begin();
		row_count = grid_template->GetSelectedRows().GetCount();
	}
	else
	{
		row_count = grid_template->GetNumberRows();

		if (row_count)
		{
			row_num = 0;
		}
		else
		{
			template_map.insert(std::pair<std::string, std::vector<std::string>>(template_name, template_list));
			event.Skip();
			return;
		}
	}

	for (int i = row_num; i < row_num + row_count; i++)
	{
		grid_extract_parameters(i, grid_template);

		template_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	}

	template_map.insert(std::pair<std::string, std::vector<std::string>>(template_name, template_list));

	update_group_template_grid(grid_template, template_list, template_map, template_name);

	event.Skip();
}

void cMain::OnDeleteTemplateClicked(wxCommandEvent& event)
{
	if (wxMessageBox("Are you sure you want to delete this template?", "Delete template", wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		event.Skip();
		return;
	}

	template_name = cmb_choose_template->GetValue();

	if (template_map.find(template_name) != template_map.end())
	{
		template_map.erase(template_name);
		template_choices.Remove(template_name);
		cmb_choose_template->Clear();
		cmb_choose_template->Append(template_choices);

		if (template_choices.size())
		{
			cmb_choose_template->SetValue(*template_choices.begin());
			OnTemplateChosen(event);
		}
		else if (grid_template->GetNumberRows())
		{
			grid_template->DeleteRows(0, grid_template->GetNumberRows());
		}
	}

	event.Skip();
}

void cMain::OnTemplateAddFromTasksListClicked(wxCommandEvent& event)
{
	if (!grid_tasks->IsSelection())
	{
		wxMessageBox("No task is chosen - please select a row in the task list", "Cannot add task to group");
		event.Skip();
		return;
	}

	if (spin_amount_offset->GetValue() != 0 && spin_amount_multiplier->GetValue() != 0)
	{
		wxMessageBox("Please either use units-offset or units-multiplier", "Invalid use of template attributes");
		return;
	}

	if (grid_template->IsSelection())
	{
		if (!grid_template->GetSelectedRows().begin())
		{
			wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
			event.Skip();
			return;
		}
		template_row_num = *grid_template->GetSelectedRows().begin();
	}
	else
	{
		template_row_num = grid_template->GetNumberRows();
	}

	for (const auto& block : grid_tasks->GetSelectedRowBlocks())
	{
		row_num = block.GetTopRow();
		row_count = block.GetBottomRow() - row_num + 1;

		grid_template->InsertRows(template_row_num, row_count);

		int total_rows = row_num + row_count;

		for (int i = row_num; i < total_rows; i++)
		{

			grid_extract_parameters(i, grid_tasks);

			TemplateAlterTask(i, grid_tasks);

			grid_insert_data(template_row_num, grid_template);

			background_colour_update(grid_template, template_row_num, grid_tasks->GetCellValue(i, 0).ToStdString());

			template_row_num += 1;
		}
	}

	if (!(template_map.find(cmb_choose_template->GetValue().ToStdString()) == template_map.end()))
	{
		update_template_map();
	}

	event.Skip();
}

// You have chosen to exclude the checks normally made when adding a task to the task list, given the increased complexity of handling multiple tasks at once
void cMain::OnTemplateAddToTasksListClicked(wxCommandEvent& event)
{
	if (!grid_tasks->IsSelection())
	{
		row_num = grid_tasks->GetNumberRows();
	}
	else
	{
		if (!grid_tasks->GetSelectedRows().begin())
		{
			wxMessageBox("Please either select row(s) or nothing", "Task list selection not valid");
			return;
		}

		row_num = *grid_tasks->GetSelectedRows().begin();
	}

	if (spin_amount_offset->GetValue() != 0 && spin_amount_multiplier->GetValue() != 0)
	{
		wxMessageBox("Please either use units-offset or units-multiplier", "Invalid use of template attributes");
		return;
	}

	bool check = false;

	for (const auto& block : grid_template->GetSelectedRowBlocks())
	{
		template_row_num = block.GetTopRow();
		template_row_count = block.GetBottomRow() - template_row_num + 1;

		grid_tasks->InsertRows(row_num, template_row_count);

		int total_rows = template_row_num + template_row_count;

		for (int i = template_row_num; i < total_rows; i++)
		{
			grid_extract_parameters(i, grid_template);

			TemplateAlterTask(i, grid_template);

			grid_insert_data(row_num, grid_tasks);

			background_colour_update(grid_tasks, row_num, task);

			it1 = tasks_data_to_save.begin();
			it1 += row_num;

			check = true;

			tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

			row_num += 1;
		}
	}

	if (check)
	{
		update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());
		event.Skip();
		return;
	}

	template_row_count = grid_template->GetNumberRows();

	grid_tasks->InsertRows(row_num, template_row_count);

	for (int i = 0; i < template_row_count; i++)
	{

		grid_extract_parameters(i, grid_template);

		TemplateAlterTask(i, grid_template);

		grid_insert_data(row_num, grid_tasks);

		background_colour_update(grid_tasks, row_num, task);

		it1 = tasks_data_to_save.begin();
		it1 += row_num;

		tasks_data_to_save.insert(it1, task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

		row_num += 1;
	}

	update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());

	event.Skip();
}

void cMain::TemplateAlterTask(int row, wxGrid* grid)
{
	grid_extract_parameters(row, grid);

	if (grid->GetCellValue(row, 1).ToStdString() != "")
	{
		x_cord = std::to_string(std::stof(x_cord) + spin_x_offset->GetValue());
		y_cord = std::to_string(std::stof(y_cord) + spin_y_offset->GetValue());
	}

	if (grid->GetCellValue(row, 3).ToStdString() != "")
	{
		if (amount == "All")
		{
			return;
		}

		if (spin_amount_offset->GetValue() != 0)
		{
			amount = std::to_string(std::stof(amount) + spin_amount_offset->GetValue());
		}

		if (spin_amount_multiplier->GetValue() != 0)
		{
			amount = std::to_string(std::stoi(amount) * spin_amount_multiplier->GetValue());
		}
	}
}

void cMain::OnTemplateChangeTaskClicked(wxCommandEvent& event)
{
	extract_parameters();

	if (setup_for_task_group_template_grid())
	{
		change_row(grid_template);

		template_name = cmb_choose_template->GetValue().ToStdString();

		if (!(template_map.find(template_name) == template_map.end()))
		{
			template_map[template_name][row_num] = (task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
		}
	}

	event.Skip();
}

void cMain::OnTemplateDeleteTaskClicked(wxCommandEvent& event)
{
	if (wxMessageBox("Are you sure you want to delete this template task?", "Delete template task", wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		return;
	}

	delete_row(grid_template, cmb_choose_template, template_map);

	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnTemplateMoveUpClicked(wxCommandEvent& event)
{
	group_template_move_row(grid_template, cmb_choose_template, true, template_map);

	event.Skip();
}

// You have chosen to not make checks when tasks are moved, given that it most likely would make the function very clunky to use
void cMain::OnTemplateMoveDownClicked(wxCommandEvent& event)
{
	group_template_move_row(grid_template, cmb_choose_template, false, template_map);

	event.Skip();
}

void cMain::OnTemplateGridDoubleLeftClick(wxGridEvent& event)
{
	row_num = event.GetRow();

	update_parameters(grid_template, event);

	event.Skip();
}

void cMain::OnBuildingsGridLeftDoubleClick(wxGridEvent& event)
{
	row_num = event.GetRow();

	spin_x->SetValue(grid_buildings->GetCellValue(row_num, 0).ToStdString());
	spin_y->SetValue(grid_buildings->GetCellValue(row_num, 1).ToStdString());
	cmb_item->SetValue(grid_buildings->GetCellValue(row_num, 2).ToStdString());
	cmb_building_orientation->SetValue(grid_buildings->GetCellValue(row_num, 3).ToStdString());
	spin_amount->SetValue(grid_buildings->GetCellValue(row_num, 4).ToStdString());
	radio_input->Select(1);//grid_buildings->GetCellValue(row_num, 6).ToStdString());
	radio_output->Select(1);//grid_buildings->GetCellValue(row_num, 7).ToStdString());

	event.Skip();
}

void cMain::OnUnitsChanged(wxCommandEvent& event)
{
	spin_amount->SetValue(event.GetInt());
}

void cMain::OnApplicationClose(wxCloseEvent& event)
{
	if (check_before_close())
	{ // You do not want to skip the event if the application shouldn't be closed
		if (shortcuts)
		{
			delete shortcuts;
		}

		if (dialog_progress_bar)
		{
			delete dialog_progress_bar;
		}

		event.Skip();
	}
}

bool cMain::checks_before_reset_window()
{
	if (grid_tasks->GetNumberRows() > 0 || grid_buildings->GetNumberRows() > 0 || grid_group->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0)
	{
		return true;
	}

	if (group_map.size() > 0 || template_map.size() > 0)
	{
		return true;
	}

	return false;
}

void cMain::OnMenuNew(wxCommandEvent& event)
{

	if (checks_before_reset_window())
	{
		if (wxMessageBox("Are you sure you want to reset the window?\nAll in the current window will be cleared.", "Ensure that you have saved what you need before clicking yes", wxICON_QUESTION | wxYES_NO, this) == wxYES)
		{
			reset_to_new_window();
		}
	}

	event.Skip();
}

void cMain::OnMenuOpen(wxCommandEvent& event)
{

	wxFileDialog dlg(this, "Open saved file", "", "", ".txt files (*.txt) | *.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (dlg.ShowModal() == wxID_OK)
	{
		std::ifstream file;
#pragma warning(suppress : 4996)
		std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
		file.imbue(utf8_locale);
		file.open(dlg.GetPath().ToStdString());

		if (!file)
		{
			wxMessageBox("It was not possible to open the file", "A file error occurred");
			return;
		}

		if (checks_before_reset_window())
		{
			if (wxMessageBox("Are you sure you want to open this file?\nAll in the current window will be cleared.", "Ensure that you have saved what you need before clicking yes", wxICON_QUESTION | wxYES_NO, this) == wxYES)
			{
				reset_to_new_window();
			}
			else
			{
				return;
			}
		}

		if (!dialog_progress_bar)
		{
			dialog_progress_bar = new dialog_progress_bar_base(this, wxID_ANY, "Processing request");
		}

		OpenTas open;
		open_file_return_data result = open.Open(dialog_progress_bar, file);

		if (!result.success)
		{
			malformed_saved_file_message();
			return;
		}

		tasks_data_to_save = result.steps;
		group_map = result.group_map;
		template_map = result.template_map;
		save_file_location = result.save_file_location;
		generate_code_folder_location = result.generate_code_folder_location;

		if (result.goal == goal_steelaxe_text)
		{
			menu_goals->GetMenuItems()[0]->Check();
		}
		else if (result.goal == goal_GOTLAP_text)
		{
			menu_goals->GetMenuItems()[1]->Check();
		}
		else if (result.goal == goal_any_percent_text)
		{
			menu_goals->GetMenuItems()[2]->Check();
		}
		else if (result.goal == goal_debug_text)
		{
			menu_goals->GetMenuItems()[3]->Check();
		}
		else
		{
			malformed_saved_file_message();
			return;
		}

		menu_auto_close->GetMenuItems()[0]->Check(result.auto_close_generate_script);
		auto_close_generate_script = result.auto_close_generate_script;

		menu_auto_close->GetMenuItems()[1]->Check(result.auto_close_open);
		auto_close_open = result.auto_close_open;

		menu_auto_close->GetMenuItems()[2]->Check(result.auto_close_save);
		auto_close_save = result.auto_close_save;

		menu_auto_close->GetMenuItems()[3]->Check(result.auto_close_save_as);
		auto_close_save_as = result.auto_close_save_as;

		check_furnace->SetValue(result.auto_put_furnace);
		check_burner->SetValue(result.auto_put_burner);
		check_lab->SetValue(result.auto_put_lab);
		check_recipe->SetValue(result.auto_put_recipe);

		populate_tasks_grid();

		dialog_progress_bar->set_progress(100.0f - 35);
		wxYield();

		if (result.group_map.size())
		{
			std::vector<std::string> keys = get_keys(result.group_map);

			for (int i = 0; i < keys.size(); i++)
			{
				group_choices.Add(keys[i]);
			}

			cmb_choose_group->Clear();

			if (group_choices.size())
			{
				cmb_choose_group->Append(group_choices);
				cmb_choose_group->SetValue(*group_choices.begin());
				OnGroupChosen(event);
			}
		}

		dialog_progress_bar->set_progress(100.0f - 25);
		wxYield();

		if (result.template_map.size())
		{
			std::vector<std::string> keys = get_keys(result.template_map);

			for (int i = 0; i < keys.size(); i++)
			{
				template_choices.Add(keys[i]);
			}

			cmb_choose_template->Clear();

			if (template_choices.size())
			{
				cmb_choose_template->Append(template_choices);
				cmb_choose_template->SetValue(*template_choices.begin());
				OnTemplateChosen(event);
			}
		}

		file.close();

		dialog_progress_bar->set_progress(100.0f - 20);
		wxYield();

		std::string file_name = save_file_location.substr(save_file_location.rfind("\\") + 1);

		SetLabel(window_title + " - " + file_name);

		update_buildings_grid_from_scratch(0, grid_tasks->GetNumberRows());

		dialog_progress_bar->set_progress(100);
		if (auto_close_open)
		{
			dialog_progress_bar->Close();
		}
		else
		{
			dialog_progress_bar->set_button_enable(true);
		}
	}

	event.Skip();
}

void cMain::populate_tasks_grid()
{
	if (grid_tasks->GetNumberRows() > 0)
	{
		grid_tasks->DeleteRows(0, grid_tasks->GetNumberRows());
	}

	size_t amount_of_tasks = tasks_data_to_save.size();

	grid_tasks->InsertRows(0, amount_of_tasks);

	for (int i = 0; i < amount_of_tasks; i++)
	{
		std::stringstream data_line;
		data_line.str(tasks_data_to_save[i]);
		seglist = {};

		while (std::getline(data_line, segment, ';'))
		{
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

void cMain::OnMenuSave(wxCommandEvent& event)
{

	save_file(false);

	event.Skip();
}

void cMain::OnMenuSaveAs(wxCommandEvent& event)
{

	save_file(true);

	event.Skip();
}

void cMain::OnMenuExit(wxCommandEvent& event)
{
	wxCloseEvent close_event;
	OnApplicationClose(close_event);

	event.Skip();
	Close();
}

void cMain::OnChooseLocation(wxCommandEvent& event)
{
	wxDirDialog dlg(NULL, "Choose location to generate script", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

	if (dlg.ShowModal() == wxID_OK)
	{
		generate_code_folder_location = dlg.GetPath().ToStdString();
	}

	event.Skip();
}

void cMain::OnGenerateScript(wxCommandEvent& event)
{
	std::string goal = "goal_debug.lua";
	if (menu_goals->GetMenuItems()[0]->IsChecked())
	{
		goal = "goal_steelaxe.lua";
	}
	else if (menu_goals->GetMenuItems()[1]->IsChecked())
	{
		goal = "goal_gotlap.lua";
	}
	else if (menu_goals->GetMenuItems()[2]->IsChecked())
	{
		goal = "goal_any_percent.lua";
	}

	GenerateScript generate_script;
	generate_script.generate(this, grid_tasks, dialog_progress_bar, tasks_data_to_save, generate_code_folder_location, auto_close_generate_script, menu_script->GetMenuItems()[2]->IsChecked(), goal);

	event.Skip();
}

void cMain::OnChangeShortcuts(wxCommandEvent& event)
{
	if (!shortcuts)
	{
		shortcuts = new Shortcuts_Menu(this);
	}

	shortcuts->Show();
	event.Skip();
}

void cMain::OnMenuAutoCloseGenerateScriptClicked(wxCommandEvent& event)
{
	auto_close_generate_script = menu_auto_close->GetMenuItems()[0]->IsChecked();
	event.Skip();
}

void cMain::OnMenuAutoCloseOpenClicked(wxCommandEvent& event)
{
	auto_close_open = menu_auto_close->GetMenuItems()[1]->IsChecked();
	event.Skip();
}

void cMain::OnMenuAutoCloseSaveClicked(wxCommandEvent& event)
{
	auto_close_save = menu_auto_close->GetMenuItems()[2]->IsChecked();

	event.Skip();
}

void cMain::OnMenuAutoCloseSaveAsClicked(wxCommandEvent& event)
{
	auto_close_save_as = menu_auto_close->GetMenuItems()[3]->IsChecked();
	event.Skip();
}

void cMain::OnChangeMenuSelected(wxCommandEvent& event)
{
	OnChangeTaskClicked(event);
	event.Skip();
}

void cMain::OnDeleteMenuSelected(wxCommandEvent& event)
{
	OnDeleteTaskClicked(event);
	event.Skip();
}

void cMain::OnMoveUpMenuSelected(wxCommandEvent& event)
{
	OnMoveUpClicked(event);
	event.Skip();
}

void cMain::OnMoveDownMenuSelected(wxCommandEvent& event)
{
	OnMoveDownClicked(event);
	event.Skip();
}

void cMain::OnAddMenuSelected(wxCommandEvent& event)
{
	OnAddTaskClicked(event);
	event.Skip();
}

bool cMain::setup_for_task_group_template_grid()
{
	auto t = TaskNames.find(task)->second;
	switch (t)
	{
		case e_game_speed:
			x_cord = not_relevant;
			y_cord = not_relevant;
			item = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_walk:
			amount = not_relevant;
			item = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_mine:
			if (mine_building_found)
			{
				item = building;
			}
			else
			{
				item = not_relevant;
			}

			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_rotate:
			item = building;

			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_craft:
			if (!check_input(item, handcrafted_list))
			{
				wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
				return false;
			}

			x_cord = not_relevant;
			y_cord = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_build:
			if (!check_input(item, all_buildings))
			{
				wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
				return false;
			}

			if (!check_input(build_orientation, build_orientations))
			{
				wxMessageBox("The build direction is not valid - please try again", "Please use the build direction dropdown menu");
				return false;
			}

			if (!check_input(direction_to_build, build_orientations))
			{
				wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
				return false;
			}

			amount = not_relevant;
			break;

		case e_take: //fallthrough
		case e_put:
			if (!check_take_put(item))
			{
				return false;
			}

			if (!check_input(direction_to_build, build_orientations))
			{
				wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
				return false;
			}

			build_orientation = from_into;
			break;

		case e_tech:
			if (!check_input(tech_to_start, tech_list))
			{
				wxMessageBox("The tech is not valid - please try again", "Please use the tech dropdown menu");
				return false;
			}

			x_cord = not_relevant;
			y_cord = not_relevant;
			amount = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;

			item = tech_to_start;
			break;

		case e_recipe:
			if (building == "Assembling machine 1")
			{
				if (!check_input(item, part_assembly_recipes))
				{
					wxMessageBox("The item chosen is not a valid recipe for an assembling machine 1", "Item chosen is not valid");
					return false;
				}
			}
			else if (building == "Assembling machine 2" || building == "Assembling machine 3")
			{
				if (!check_input(item, full_assembly_recipes))
				{
					wxMessageBox("The item chosen is not a valid recipe for an assembling machine", "Item chosen is not valid");
					return false;
				}
			}
			else if (building == "Oil refinery")
			{
				if (!check_input(item, oil_refinery_list))
				{
					wxMessageBox("The item chosen is not a valid recipe for an oil refinery", "Item chosen is not valid");
					return false;
				}
			}
			else if (building == "Chemical plant")
			{
				if (!check_input(item, full_chemical_plant_recipes))
				{
					wxMessageBox("The item chosen is not a valid recipe for a chemical plant", "Item chosen is not valid");
					return false;
				}
			}
			else if (building == "Centrifuge")
			{
				if (!check_input(item, centrifuge_list))
				{
					wxMessageBox("The item chosen is not a valid recipe for a centrifuge", "Item chosen is not valid");
					return false;
				}
			}
			else if (building == "Stone furnace" || building == "Steel furnace" || building == "Electric furnace")
			{
				if (!check_input(item, furnace_list))
				{
					wxMessageBox("The item chosen is not a valid recipe for a furnace", "Item chosen is not valid");
					return false;
				}
			}

			build_orientation = not_relevant;
			break;

		case e_start:
			x_cord = not_relevant;
			y_cord = not_relevant;
			amount = not_relevant;
			item = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_pause:
			x_cord = not_relevant;
			y_cord = not_relevant;
			amount = not_relevant;
			item = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_stop:
			x_cord = not_relevant;
			y_cord = not_relevant;
			item = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_limit:
			item = not_relevant;
			build_orientation = "Chest";
			break;

		case e_priority:
			item = not_relevant;
			amount = not_relevant;

			if (!check_input(priority_in, input_output))
			{
				wxMessageBox("The input priority chosen is not valid - please try again", "Please use the input dropdown menu");
				return false;
			}

			if (!check_input(priority_out, input_output))
			{
				wxMessageBox("The output priority chosen is not valid - please try again", "Please use the output dropdown menu");
				return false;
			}

			build_orientation = priority_in + ", " + priority_out;
			break;

		case e_pick_up:
			x_cord = not_relevant;
			y_cord = not_relevant;
			item = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_drop:
			amount = not_relevant;
			build_orientation = not_relevant;
			break;

		case e_filter:
			build_orientation = not_relevant;
			break;

		case e_launch:
			amount = not_relevant;
			item = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_save:
			x_cord = not_relevant;
			y_cord = not_relevant;
			amount = not_relevant;
			item = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;

		case e_idle:
			x_cord = not_relevant;
			y_cord = not_relevant;
			item = not_relevant;
			build_orientation = not_relevant;
			direction_to_build = not_relevant;
			building_size = not_relevant;
			amount_of_buildings = not_relevant;
			break;
	}

	return true;
}




std::string FormatString(wxString s)
{
	int i = s.size() - 1;
	if (i < 0)
	{
		return s.ToStdString();
	}

	if (i == 0)
	{
		return s.ToStdString() + ".0";
	}

	for (i; i > 0; i--)
	{
		if (s[i] == '.')
		{
			i += 2;
			break;
		}

		if (s[i] != '0')
		{
			i++;
			break;
		}
	}

	s.erase(i, s.size());

	return s.ToStdString();
}

void cMain::update_parameters(wxGrid* grid, wxCommandEvent& event)
{
	grid_extract_parameters(row_num, grid);

	if (task == struct_tasks_list.game_speed)
	{
		OnGameSpeedMenuSelected(event);
		float speed = std::stof(amount) * 100.0;
		spin_amount->SetValue(speed);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.walk)
	{
		OnWalkMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		txt_comment->SetValue(comment);

		return;
	}
	if (task == struct_tasks_list.mine)
	{
		OnMineMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		spin_amount->SetValue(amount);
		txt_comment->SetValue(comment);

		return;
	}
	if (task == struct_tasks_list.rotate)
	{
		OnRotateMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		spin_amount->SetValue(amount);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.craft)
	{
		OnCraftMenuSelected(event);
		spin_amount->SetValue(amount);
		cmb_item->SetValue(item);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.build)
	{
		OnBuildMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		cmb_item->SetValue(item);
		cmb_building_orientation->SetValue(build_orientation);
		cmb_direction_to_build->SetValue(direction_to_build);
		spin_building_size->SetValue(building_size);
		spin_building_amount->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.take)
	{
		OnTakeMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		spin_amount->SetValue(amount);
		cmb_item->SetValue(item);
		cmb_from_into->SetValue(build_orientation);
		cmb_direction_to_build->SetValue(direction_to_build);
		spin_building_size->SetValue(building_size);
		spin_building_amount->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.put)
	{
		OnPutMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		spin_amount->SetValue(amount);
		cmb_item->SetValue(item);
		cmb_from_into->SetValue(build_orientation);
		cmb_direction_to_build->SetValue(direction_to_build);
		spin_building_size->SetValue(building_size);
		spin_building_amount->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.tech)
	{
		OnTechMenuSelected(event);
		cmb_item->SetValue(item);
		txt_comment->SetValue(comment);

		return;
	}
	if (task == struct_tasks_list.recipe)
	{
		OnRecipeMenuChosen(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		cmb_direction_to_build->SetValue(direction_to_build);
		spin_building_size->SetValue(building_size);
		spin_building_amount->SetValue(amount_of_buildings);
		cmb_item->SetValue(item);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.start)
	{
		OnStartMenuSelected(event);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.pause)
	{
		OnPauseMenuSelected(event);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.stop)
	{
		OnStopMenuSelected(event);
		spin_amount->SetValue(amount);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.limit)
	{
		OnLimitMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		spin_amount->SetValue(amount);
		cmb_direction_to_build->SetValue(direction_to_build);
		spin_building_size->SetValue(building_size);
		spin_building_amount->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.priority)
	{
		OnPriorityMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		cmb_direction_to_build->SetValue(direction_to_build);
		spin_building_size->SetValue(building_size);
		spin_building_amount->SetValue(amount_of_buildings);

		long long pos = build_orientation.find(",");
		radio_input->Select(map_input_output[build_orientation.substr(0, pos)]);
		radio_output->Select(map_input_output[build_orientation.substr(pos + 2)]);

		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.filter)
	{
		OnFilterMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		spin_amount->SetValue(amount);
		cmb_item->SetValue(item);
		cmb_direction_to_build->SetValue(direction_to_build);
		spin_building_size->SetValue(building_size);
		spin_building_amount->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.pick_up)
	{
		OnPickUpMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		cmb_direction_to_build->SetValue(direction_to_build);
		spin_building_size->SetValue(building_size);
		spin_building_amount->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.drop)
	{
		OnDropMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		cmb_item->SetValue(item);
		cmb_direction_to_build->SetValue(direction_to_build);
		spin_building_size->SetValue(building_size);
		spin_building_amount->SetValue(amount_of_buildings);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.idle)
	{
		OnIdleMenuSelected(event);
		spin_amount->SetValue(amount);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.launch)
	{
		OnLaunchMenuSelected(event);
		spin_x->SetValue(x_cord);
		spin_y->SetValue(y_cord);
		txt_comment->SetValue(comment);

		return;
	}

	if (task == struct_tasks_list.save)
	{
		OnSaveMenuSelected(event);
		txt_comment->SetValue(comment);
	}
}

void cMain::update_group_map()
{
	group_list = {};
	row_num = grid_group->GetNumberRows();

	for (int i = 0; i < row_num; i++)
	{
		grid_extract_parameters(i, grid_group);

		group_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	}

	group_map[group_name] = group_list;
}

void cMain::update_template_map()
{
	template_list = {};
	row_num = grid_template->GetNumberRows();

	for (int i = 0; i < row_num; i++)
	{
		grid_extract_parameters(i, grid_template);

		template_list.push_back(task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
	}

	template_map[template_name] = template_list;
}

void cMain::extract_parameters()
{
	task = extract_task();
	x_cord = extract_x_cord();
	y_cord = extract_y_cord();
	amount = extract_amount();
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

std::string cMain::extract_x_cord()
{
	return std::to_string(spin_x->GetValue());
}

std::string cMain::extract_y_cord()
{
	return std::to_string(spin_y->GetValue());
}

std::string cMain::extract_amount()
{
	int amount = spin_amount->GetValue();

	if (amount < 1 && (rbtn_rotate->GetValue() || rbtn_idle->GetValue() || rbtn_recipe->GetValue() || rbtn_pick_up->GetValue()))
	{
		return "1";
	}

	if (amount < 0 && rbtn_limit->GetValue())
	{
		return "0";
	}

	if (rbtn_filter->GetValue())
	{
		if (amount < 1)
		{
			return "1";
		}

		if (amount > 5)
		{
			return "5";
		}
	}

	if (rbtn_game_speed->GetValue() || rbtn_stop->GetValue())
	{
		float speed = static_cast<float>(amount) / 100.0;
		if (speed < 0.01)
		{
			return "0.01";
		}

		return std::to_string(speed);
	}

	if (amount < 1)
	{
		return "All";
	}

	return std::to_string(amount);
}

std::string cMain::extract_comment()
{
	return txt_comment->GetValue().ToStdString();
}

std::string cMain::extract_item()
{
	return cmb_item->GetValue().ToStdString();
}

std::string cMain::extract_amount_of_buildings()
{
	if (spin_building_amount->GetValue() < 1)
	{
		return "1";
	}

	return std::to_string(spin_building_amount->GetValue());
}

void cMain::auto_put(std::string put_item, std::string put_amount, std::string put_into)
{
	cmb_from_into->SetValue(put_into);

	task = struct_tasks_list.put;
	item = put_item;
	amount = put_amount;
	from_into = put_into;
	setup_for_task_group_template_grid();
	update_tasks_grid();
}

std::string cMain::extract_building_size()
{
	if (spin_building_size->GetValue() < 1)
	{
		return "1";
	}

	return std::to_string(spin_building_size->GetValue());
}

std::string cMain::extract_from_into()
{
	return cmb_from_into->GetValue().ToStdString();
}

std::string cMain::extract_direction_to_build()
{
	return cmb_direction_to_build->GetValue().ToStdString();
}

std::string cMain::extract_building_orientation()
{
	return cmb_building_orientation->GetValue().ToStdString();
}

std::string cMain::extract_tech()
{
	return cmb_item->GetValue().ToStdString();
}

std::string cMain::extract_priority_in()
{
	return input_output[radio_input->GetSelection()];
}

std::string cMain::extract_priority_out()
{
	return input_output[radio_output->GetSelection()];
}

void cMain::update_future_rotate_tasks()
{
	int total_rows = grid_tasks->GetNumberRows();

	for (int i = row_num + 1; i < total_rows; i++)
	{

		if (grid_tasks->GetCellValue(i, 0).ToStdString() == "Rotate")
		{
			if (grid_tasks->GetCellValue(i, 1).ToStdString() == x_cord && grid_tasks->GetCellValue(i, 2).ToStdString() == y_cord && grid_tasks->GetCellValue(i, 4).ToStdString() == building)
			{

				grid_extract_parameters(i, grid_tasks);

				find_new_orientation();

				grid_tasks->SetCellValue(i, 5, building_build_orientation);

				tasks_data_to_save[i] = (task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + building_build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");
			}
		}
	}
}

void cMain::find_new_orientation()
{
	for (auto it = build_orientations.begin(); it < build_orientations.end(); it++)
	{
		if (building_build_orientation == *it)
		{
			building_build_orientation = build_orientations[((it - build_orientations.begin()) + std::stoi(amount)) % 4];
			break;
		}
	}
}

bool cMain::find_building_for_script(int& row)
{
	for (int i = row - 1; i > -1; i--)
	{
		if (compare_task_strings(grid_tasks->GetCellValue(i, 0), struct_tasks_list.build))
		{
			split_task(tasks_data_to_save[i]);

			building_x_cord = task_segments[1];
			building_y_cord = task_segments[2];

			if (x_cord == building_x_cord && y_cord == building_y_cord)
			{
				building = task_segments[4];
				build_orientation = task_segments[5];

				return true;
			}

			building_direction_to_build = task_segments[6];
			building_building_size = task_segments[7];
			building_amount_of_buildings = task_segments[8];

			for (int j = 1; j < std::stoi(building_amount_of_buildings); j++)
			{
				find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);

				if (x_cord == building_x_cord && y_cord == building_y_cord)
				{
					building = task_segments[4];
					build_orientation = task_segments[5];

					return true;
				}
			}
		}
		else if (compare_task_strings(grid_tasks->GetCellValue(i, 0), struct_tasks_list.rotate))
		{
			split_task(tasks_data_to_save[i]);

			building_x_cord = task_segments[1];
			building_y_cord = task_segments[2];

			if (x_cord == building_x_cord && y_cord == building_y_cord)
			{
				building = task_segments[4];
				build_orientation = task_segments[5];

				return true;
			}
		}
	}

	if (task == struct_tasks_list.mine)
	{
		return false;
	}

	wxMessageBox("Task: " + task_number + " have no building associated with it - please correct the error and try again", "The building does not exist");
	return false;
}

bool cMain::compare_task_strings(const wxString& str1, const std::string& str2)
{
	if (str1.length() != str2.length())
	{
		return false;
	}

	for (int i = 0; i < str1.length(); i++)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}

	return true;
}

bool cMain::find_building(int amount_of_buildings)
{
	building_row_num = grid_buildings->GetNumberRows();

	if (building_row_num == 0)
	{
		return false;
	}

	if (amount_of_buildings > building_row_num)
	{
		return false;
	}

	for (int j = 0; j < building_row_num; j++)
	{

		if (!compare_task_strings(grid_buildings->GetCellValue(j, 0), building_x_cord) || !compare_task_strings(grid_buildings->GetCellValue(j, 1), building_y_cord))
		{
			if (j == (building_row_num - 1))
			{
				return false;
			}

			continue;
		}

		building = grid_buildings->GetCellValue(j, 2);
		building_row_num = j;
		break;
	}

	if (extra_building_checks())
	{
		return true;
	}

	return false;
}

void cMain::malformed_saved_file_message()
{
	reset_to_new_window();
	wxMessageBox("It seems like the structure of the file does not correspond with an EZRaiderz TAS helper file", "A file error occurred");
	dialog_progress_bar->set_button_enable(true);
}

bool cMain::extra_building_checks()
{
	std::string building_item_check = "";

	building_item_check = grid_buildings->GetCellValue(building_row_num, 2).ToStdString();
	if (building_task == "Limit")
	{
		if (!check_input(building_item_check, chest_list))
		{
			return false;
		}
	}
	else if (building_task == "Priority")
	{
		if (!check_input(building_item_check, splitter_list))
		{
			return false;
		}
	}
	else if (building_task == "Filter")
	{
		if (!check_input(building_item_check, splitter_list) && !check_input(building_item_check, filter_inserter_list))
		{
			return false;
		}
	}

	return true;
}

bool cMain::check_take_put(std::string& item)
{
	std::string to_check = extract_from_into();
	string_capitalized(to_check);

	if (to_check == "Wreck")
	{
		return true;
	}

	if (check_input(building, chest_list))
	{
		if (to_check == "Chest")
		{
			return true;
		}

		wxMessageBox("Only Chest is a valid \"From/Into\" choice for a chest", "Please choose chest");
		return false;
	}

	if (to_check == "Fuel")
	{
		if (check_input(item, fuel_list))
		{
			return true;
		}

		wxMessageBox("The item chosen is not a valid fuel", "Please select a valid fuel");
		return false;
	}

	if (building == "Lab")
	{
		if (to_check == "Input")
		{
			if (check_input(item, science_packs))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a science pack.\nOnly science packs can be used as input for a lab", "Please choose a science pack");
			return false;

		}
		else if (to_check == "Modules")
		{
			if (check_input(item, module_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a module", "Please choose a module");
			return false;
		}

		wxMessageBox("Only Input and Modules are valid \"From/Into\" choices for a lab", "Please choose input or modules");
		return false;
	}

	if (check_input(building, drills_list))
	{
		if (to_check == "Modules")
		{
			if (check_input(item, module_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a module", "Please choose a module");
			return false;
		}

		wxMessageBox("Only Modules is a valid \"From/Into\" choice for a drill/Pump", "Please choose modules");
		return false;
	}

	if (to_check == "Input")
	{
		// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
		return true;
	}

	if (to_check == "Modules")
	{
		if (check_input(item, module_list))
		{
			return true;
		}

		wxMessageBox("The item chosen is not a module", "Please choose a module");
		return false;
	}

	if (to_check == "Output")
	{
		// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
		return true;
	}

	wxMessageBox("Building location does not seem to exist.\nPlease use exactly the same coordinates as you used to build", "Please use the same coordinates");
	return false;
}

bool cMain::check_buildings_grid()
{

	if (building_task == "Mine")
	{
		if (find_building(1))
		{
			int total_rows = grid_tasks->GetNumberRows();

			mine_building_found = true;

			if (row_num + 1 >= total_rows)
			{
				grid_buildings->DeleteRows(building_row_num);
			}
			else
			{
				for (int i = row_num + 1; i < total_rows; i++)
				{
					if (grid_tasks->GetCellValue(i, 1).ToStdString() == x_cord && grid_tasks->GetCellValue(i, 2).ToStdString() == y_cord)
					{
						if (grid_tasks->GetCellValue(i, 0).ToStdString() != "Mine" && grid_tasks->GetCellValue(i, 0).ToStdString() != "Build")
						{
							if (wxMessageBox("Are you sure you want to remove this building?\nAll future tasks associated with the building will be removed to avoid issues.", "The building you are removing has tasks associated with it", wxICON_QUESTION | wxYES_NO, this) == wxYES)
							{
								grid_buildings->DeleteRows(building_row_num);
								for (int j = i; j < total_rows; j++)
								{
									if (grid_tasks->GetCellValue(j, 1).ToStdString() == x_cord && grid_tasks->GetCellValue(j, 2).ToStdString() == y_cord)
									{
										if (grid_tasks->GetCellValue(j, 0).ToStdString() == "Mine")
										{
											grid_tasks->SelectRow(row_num);
											grid_tasks->SetCellValue(j, 4, "");

											grid_extract_parameters(j, grid_tasks);

											item = "";

											tasks_data_to_save[j] = (task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

											return true;
										}
										else if (grid_tasks->GetCellValue(j, 0).ToStdString() == "Build")
										{
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
							}
							else
							{
								return false;
							}
						}
						else
						{
							if (grid_tasks->GetCellValue(i, 0).ToStdString() == "Mine")
							{
								grid_tasks->SetCellValue(i, 4, "");

								grid_extract_parameters(i, grid_tasks);

								item = "";

								tasks_data_to_save[i] = (task + ";" + x_cord + ";" + y_cord + ";" + amount + ";" + item + ";" + build_orientation + ";" + direction_to_build + ";" + building_size + ";" + amount_of_buildings + ";" + comment + ";");

							}

							grid_tasks->SelectRow(row_num);
							return true;
						}
					}
				}
			}
		}

	}
	else if (building_task == "Recipe")
	{
		if (!update_recipe())
		{
			wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build\n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	}
	else if (building_task == "Build")
	{
		update_buildings();

	}
	else if (building_task == "Limit")
	{
		if (!update_limit())
		{
			wxMessageBox("Building is not a chest or location doesn't exist.\n1. Please use exactly the same coordinates as you used to build\n2. Check that you have not removed the building(s)\n3. Ensure that all are chests\n4. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	}
	else if (building_task == "Priority")
	{

		if (!update_priority())
		{
			wxMessageBox("Building is not a splitter or location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Ensure that all are splitters\n4. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	}
	else if (building_task == "Filter")
	{
		if (!update_filter())
		{
			wxMessageBox("Building is not a splitter, filter inserter or location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Ensure that all are splitters or filter inserters\n4. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	}
	else if (building_task == "Take" || building_task == "Put")
	{
		building_amount_of_buildings_int = std::stoi(building_amount_of_buildings);
		for (int i = 0; i < building_amount_of_buildings_int; i++)
		{
			if (from_into != "Wreck" && !find_building(building_amount_of_buildings_int))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
				return false;
			}

			find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);
		}

	}
	else if (building_task == "Launch")
	{
		if (!find_building(1))
		{
			wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

	}
	else if (building_task == "Rotate")
	{
		if (!Update_rotation())
		{
			wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
			return false;
		}

		std::string saved_orientation = building_build_orientation;

		if ((row_num + 1) < grid_tasks->GetNumberRows())
		{
			update_future_rotate_tasks();
		}

		build_orientation = saved_orientation;
	}
	return true;
}

bool cMain::save_file(bool save_as)
{

	if (save_file_location == "" || save_as)
	{
		wxFileDialog dlg(this, "Save file", "", "", ".txt files (*.txt) | *.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (dlg.ShowModal() == wxID_OK)
		{
			save_file_location = dlg.GetPath().ToStdString();
		}
		else
		{
			return false;
		}
	}

	std::vector<bool> auto_list{
		menu_auto_close->GetMenuItems()[0]->IsChecked(),
		menu_auto_close->GetMenuItems()[1]->IsChecked(),
		menu_auto_close->GetMenuItems()[2]->IsChecked(),
		menu_auto_close->GetMenuItems()[3]->IsChecked(),
		check_furnace->IsChecked(),
		check_burner->IsChecked(),
		check_lab->IsChecked(),
		check_recipe->IsChecked(),
		auto_close_save_as,
		auto_close_save,
	};

	std::string goal;
	if (menu_goals->GetMenuItems()[0]->IsChecked())
	{
		goal = goal_steelaxe_text;
	}
	else if (menu_goals->GetMenuItems()[1]->IsChecked())
	{
		goal = goal_GOTLAP_text;
	}
	else if (menu_goals->GetMenuItems()[2]->IsChecked())
	{
		goal = goal_any_percent_text;
	}
	else
	{
		goal = goal_debug_text;
	}

	SaveTas save;
	save.Save(
		this,
		dialog_progress_bar,
		save_as,
		auto_list,
		tasks_data_to_save,
		group_map,
		template_map,
		save_file_location,
		generate_code_folder_location,
		goal);

	std::string file_name = save_file_location.substr(save_file_location.rfind("\\") + 1);

	SetLabel(window_title + " - " + file_name);

	return true;
}

bool cMain::check_input(std::string& item, const std::vector<std::string>& all_items)
{
	std::string item_lower = "";
	for (unsigned int i = 0; i < item.size(); i++)
	{
		item_lower.push_back(std::tolower(item[i]));
	}

	for (auto it = all_items.begin(); it < all_items.end(); it++)
	{

		std::string check_item_lower = "";

		for (unsigned int i = 0; i < (*it).size(); i++)
		{
			check_item_lower.push_back(std::tolower((*it)[i]));
		}

		if (item_lower == check_item_lower)
		{
			item = *it;
			return true;
		}
	}

	return false;
}

StepParameters cMain::ExtractStepParameters()
{
	auto stepParameters = StepParameters(new_extract_x_cord(), new_extract_y_cord());

	stepParameters.Task = extract_task();
	stepParameters.Amount = extract_amount();
	stepParameters.Item = extract_item();
	stepParameters.FromInto = extract_from_into();
	stepParameters.Orientation = extract_building_orientation();
	stepParameters.Direction = extract_direction_to_build();
	stepParameters.Size = new_extract_building_size();
	stepParameters.Buildings = new_extract_amount_of_buildings();
	stepParameters.PriorityIn = extract_priority_in();
	stepParameters.PriorityOut = extract_priority_out();
	stepParameters.Comment = extract_comment();

	stepParameters.TaskEnum = TaskNames.find(stepParameters.Task)->second;

	return stepParameters;
}

double cMain::new_extract_x_cord()
{
	return spin_x->GetValue();
}

double cMain::new_extract_y_cord()
{
	return spin_y->GetValue();
}

int cMain::new_extract_building_size()
{
	return spin_building_size->GetValue();
}

int cMain::new_extract_amount_of_buildings()
{
	return spin_building_amount->GetValue();
}

GridEntry* cMain::PrepareStepParametersForGrid(StepParameters* stepParameters)
{
	auto gridEntry = new GridEntry{
		.Task = stepParameters->Task,
		.Comment = stepParameters->Comment,
	};

	switch (stepParameters->TaskEnum)
	{
		case e_start:
		case e_pause:
		case e_save:
			break;

		case e_game_speed:
		case e_stop:
		case e_idle:
		case e_pick_up:
		case e_craft:
			gridEntry->Amount = stepParameters->Amount;
			break;

		case e_walk:
		case e_launch:
			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			break;

		case e_mine:
			if (mine_building_found)
			{
				gridEntry->Item = building; // This should be changed to something less convoluted 
			}

			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			gridEntry->Amount = stepParameters->Amount;
			break;

		case e_rotate:
			item = building;

			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			gridEntry->Amount = stepParameters->Amount;
			gridEntry->Item = item; // This should be changed to something less convoluted 
			break;

		case e_build:
			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			gridEntry->Item = stepParameters->Item;
			gridEntry->BuildingOrientation = stepParameters->Orientation;
			gridEntry->DirectionToBuild = stepParameters->Direction;
			gridEntry->BuildingSize = std::to_string(stepParameters->Size);
			gridEntry->AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_take:
		case e_put:
			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			gridEntry->Amount = stepParameters->Amount;
			gridEntry->Item = stepParameters->Item;
			gridEntry->BuildingOrientation = stepParameters->FromInto;
			gridEntry->DirectionToBuild = stepParameters->Direction;
			gridEntry->BuildingSize = std::to_string(stepParameters->Size);
			gridEntry->AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_tech:
			gridEntry->Item = stepParameters->Item;
			break;

		case e_recipe:
			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			gridEntry->Amount = stepParameters->Amount;
			gridEntry->Item = stepParameters->Item;
			gridEntry->DirectionToBuild = stepParameters->Direction;
			gridEntry->BuildingSize = std::to_string(stepParameters->Size);
			gridEntry->AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_limit:
			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			gridEntry->Amount = stepParameters->Amount;
			gridEntry->BuildingOrientation = "Chest";
			gridEntry->DirectionToBuild = stepParameters->Direction;
			gridEntry->BuildingSize = std::to_string(stepParameters->Size);
			gridEntry->AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_priority:
			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			gridEntry->BuildingOrientation = stepParameters->PriorityIn + "," + stepParameters->PriorityOut;
			gridEntry->DirectionToBuild = stepParameters->Direction;
			gridEntry->BuildingSize = std::to_string(stepParameters->Size);
			gridEntry->AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_drop:
			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			gridEntry->Item = stepParameters->Item;
			gridEntry->DirectionToBuild = stepParameters->Direction;
			gridEntry->BuildingSize = std::to_string(stepParameters->Size);
			gridEntry->AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_filter:
			gridEntry->X = std::to_string(stepParameters->X);
			gridEntry->Y = std::to_string(stepParameters->Y);
			gridEntry->Amount = stepParameters->Amount;
			gridEntry->Item = stepParameters->Item;
			gridEntry->DirectionToBuild = stepParameters->Direction;
			gridEntry->BuildingSize = std::to_string(stepParameters->Size);
			gridEntry->AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;
	}

	return gridEntry;
}

// ensure that the variables are actually what they are supposed to be
void cMain::new_update_tasks_grid(StepParameters* stepParameters)
{
	auto gridEntry = PrepareStepParametersForGrid(stepParameters);

	int row_num;

	if (grid_tasks->IsSelection())
	{
		if (!grid_tasks->GetSelectedRows().begin())
		{
			return;
		}

		row_num = *grid_tasks->GetSelectedRows().begin();
	}
	else
	{
		row_num = grid_tasks->GetNumberRows();
	}

	grid_tasks->InsertRows(row_num, 1);

	grid_tasks->SetCellValue(row_num, 0, gridEntry->Task);
	grid_tasks->SetCellValue(row_num, 1, gridEntry->X);
	grid_tasks->SetCellValue(row_num, 2, gridEntry->Y);
	grid_tasks->SetCellValue(row_num, 3, gridEntry->Amount);
	grid_tasks->SetCellValue(row_num, 4, gridEntry->Item);
	grid_tasks->SetCellValue(row_num, 5, gridEntry->BuildingOrientation);
	grid_tasks->SetCellValue(row_num, 6, gridEntry->DirectionToBuild);
	grid_tasks->SetCellValue(row_num, 7, gridEntry->BuildingSize);
	grid_tasks->SetCellValue(row_num, 8, gridEntry->AmountOfBuildings);
	grid_tasks->SetCellValue(row_num, 9, gridEntry->Comment);

	if (grid_tasks->IsSelection())
	{
		auto it1 = StepGridData.begin();
		it1 += row_num;

		StepGridData.insert(it1, *stepParameters);
	}
	else
	{
		StepGridData.push_back(*stepParameters);
	}

	new_background_colour_update(grid_tasks, row_num, stepParameters->TaskEnum);
}

void cMain::new_background_colour_update(wxGrid* grid, int row, TaskName task)
{
	switch (task)
	{
		case e_start:
			grid->SetCellBackgroundColour(row, 0, *wxGREEN);
			return;
		case e_stop:
			grid->SetCellBackgroundColour(row, 0, *wxRED);
			return;
		case e_build:
			grid->SetCellBackgroundColour(row, 0, *wxCYAN);
			return;
		case e_craft:
			grid->SetCellBackgroundColour(row, 0, *wxLIGHT_GREY);
			return;
		case e_game_speed:
		case e_pause:
		case e_save:
			grid->SetCellBackgroundColour(row, 0, *wxYELLOW);
			return;
		default:
			grid->SetCellBackgroundColour(row, 0, *wxWHITE);
	}
}

bool cMain::IsValidBuildStep(StepParameters stepParameters)
{
	if (!new_check_input(stepParameters.Item, all_buildings))
	{
		wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
		return false;
	}

	if (!new_check_input(stepParameters.Orientation, build_orientations))
	{
		wxMessageBox("The build direction is not valid - please try again", "Please use the build direction dropdown menu");
		return false;
	}

	if (!new_check_input(stepParameters.Direction, build_orientations))
	{
		wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
		return false;
	}

	return true;
}

bool cMain::IsValidRecipeStep(StepParameters stepParameters)
{
	switch (stepParameters.BuildingIndex)
	{
		case AssemblingMachine1:
			if (new_check_input(stepParameters.Item, part_assembly_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an assembling machine 1", "Item chosen is not valid");
			return false;

		case AssemblingMachine2:
		case AssemblingMachine3:
			if (new_check_input(stepParameters.Item, full_assembly_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an assembling machine", "Item chosen is not valid");
			return false;

		case OilRefinery:
			if (!new_check_input(stepParameters.Item, oil_refinery_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an oil refinery", "Item chosen is not valid");
			return false;

		case ChemicalPlant:
			if (!new_check_input(stepParameters.Item, full_chemical_plant_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a chemical plant", "Item chosen is not valid");
			return false;

		case Centrifuge:
			if (!new_check_input(stepParameters.Item, centrifuge_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a centrifuge", "Item chosen is not valid");
			return false;

		case StoneFurnace:
		case SteelFurnace:
		case ElectricFurnace:
			if (!new_check_input(stepParameters.Item, furnace_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a furnace", "Item chosen is not valid");
			return false;

		default:
			return true;;
	}
}

bool cMain::IsValidCraftStep(StepParameters stepParameters)
{
	if (!new_check_input(stepParameters.Item, handcrafted_list))
	{
		wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
		return false;
	}

	return true;
}

bool cMain::IsValidPutTakeStep(StepParameters stepParameters)
{
	if (!check_take_put(item))
	{
		return false;
	}

	if (!check_input(direction_to_build, build_orientations))
	{
		wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
		return false;
	}

	return true;
}

bool cMain::IsValidTechStep(StepParameters stepParameters)
{
	if (!new_check_input(stepParameters.Item, tech_list))
	{
		wxMessageBox("The tech is not valid - please try again", "Please use the tech dropdown menu");
		return false;
	}

	return true;
}

bool cMain::new_check_input(wxString& item, const std::vector<std::string>& all_items)
{
	std::string item_lower = "";
	for (unsigned int i = 0; i < item.size(); i++)
	{
		item_lower.push_back(std::tolower(item[i]));
	}

	for (auto it = all_items.begin(); it < all_items.end(); it++)
	{

		std::string check_item_lower = "";

		for (unsigned int i = 0; i < (*it).size(); i++)
		{
			check_item_lower.push_back(std::tolower((*it)[i]));
		}

		if (item_lower == check_item_lower)
		{
			item = *it;
			return true;
		}
	}

	return false;
}

void cMain::new_auto_put(std::string put_item, std::string put_amount, std::string put_into)
{
	cmb_from_into->SetValue(put_into);

	task = struct_tasks_list.put;
	item = put_item;
	amount = put_amount;
	from_into = put_into;
	setup_for_task_group_template_grid();
	update_tasks_grid();


	//new_update_tasks_grid();
}

bool cMain::new_extra_building_checks(StepParameters stepParameters)
{
	auto buildingName = FindBuildingName(stepParameters.BuildingIndex);

	switch (stepParameters.TaskEnum)
	{
		case e_limit:
			return check_input(buildingName, chest_list);

		case e_priority:
			return check_input(buildingName, splitter_list);

		case e_filter:
			return check_input(buildingName, splitter_list) && check_input(buildingName, filter_inserter_list);

		default:
			return true;
	}
}

int cMain::GenerateBuildingSnapShot(int end_row)
{
	int buildingsInSnapShot = 0;

	for (int i = 0; i < end_row; i++)
	{
		switch (StepGridData[i].TaskEnum)
		{
			case e_build:
				for (int j = 0; j < StepGridData[i].Buildings; j++)
				{
					BuildingsSnapShot[buildingsInSnapShot].X = StepGridData[i].X;
					BuildingsSnapShot[buildingsInSnapShot].Y = StepGridData[i].Y;
					BuildingsSnapShot[buildingsInSnapShot].Index = StepGridData[i].BuildingIndex;

					StepGridData[i].Next();
					buildingsInSnapShot++;
				}

				StepGridData[i].Reset();
				continue;

			case e_mine:
				for (int j = 0; j < buildingsInSnapShot; j++)
				{
					if (BuildingsSnapShot[j] == StepGridData[i])
					{
						BuildingsSnapShot[j].X = -0.4523543; // Invalidate the building
					}
				}

				continue;

			default:
				continue;
		}
	}

	return buildingsInSnapShot;
}