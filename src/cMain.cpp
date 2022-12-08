#pragma once

#include "cMain.h"

cMain::cMain() : GUI_Base(nullptr, wxID_ANY, window_title, wxPoint(30, 30), wxSize(1840, 950))
{
	SetIcon(icon_xpm);
	SetLabel(window_title);

	// Ensure that realocations shouldn't be needed for a long while.
	BuildingsSnapShot.reserve(100000);
	for (int i = 0; i < BuildingsSnapShot.capacity(); i++)
	{
		BuildingsSnapShot.emplace_back(invalidX);
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

	for (auto& s : all_recipes)
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

	for (auto& s : all_items)
	{
		item_choices.Add(s);
	}

	for (auto& s : all_buildings)
	{
		building_choices.Add(s);
	}

	for (auto& s : take_from)
	{
		take_from_choices.Add(s);
	}

	for (auto& s : tech_list)
	{
		tech_choices.Add(s);
	}

	for (auto& s : build_orientations)
	{
		building_orientation_choices.Add(s);
	}

	for (auto& s : input_output)
	{
		input_output_choices.Add(s);
	}

	for (auto& s : handcrafted_list)
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
	a->Split(2, wxRIGHT);
}

void cMain::TaskSeachOnText(wxCommandEvent& event)
{
	Search::FindCurrentOrNext(event, grid_tasks);
	event.Skip();
}

void cMain::TaskSeachOnTextEnter(wxCommandEvent& event)
{
	TaskSeachOnText(event);//seems not to fire
}

void cMain::TaskSeachOnSearchButton(wxCommandEvent& event)
{
	Search::FindNext(event, grid_tasks);
	event.Skip();
}

void cMain::TaskSeachOnCancelButton(wxCommandEvent& event)
{
	event.Skip();// do nothing, it will clear the search box
}

void cMain::ResetToNewWindow()
{
	if (grid_tasks->GetNumberRows() > 0 || grid_group->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0)
	{
		if (grid_tasks->GetNumberRows() > 0)
		{
			grid_tasks->DeleteRows(0, grid_tasks->GetNumberRows());
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

	group_map.clear();
	cmb_choose_group->Clear();
	group_choices = {};

	template_map.clear();
	cmb_choose_template->Clear();
	template_choices = {};

	StepGridData = {};
	save_file_location = "";
	generate_code_folder_location = "";

	if (dialog_progress_bar)
	{
		dialog_progress_bar->Hide();
	}

	SetLabel(window_title);
}

bool cMain::CheckBeforeClose()
{
	if (grid_tasks->GetNumberRows() > 0 || grid_group->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0)
	{
		int answer = wxMessageBox("Do you want to save your changes?", "Ensure that you have saved what you need", wxICON_QUESTION | wxYES_NO | wxCANCEL, this);

		if (answer == wxYES)
		{
			return SaveFile(false);

		}
		
		if (answer == wxNO)
		{
			return true;
		} 

		if (answer == wxCANCEL)
		{
			return false;
		}
	}

	return true;
}

void cMain::MoveRow(wxGrid* grid, bool up)
{
	for (const auto& block : grid->GetSelectedRowBlocks())
	{
		auto rowNum = block.GetTopRow();
		auto rowCount = block.GetBottomRow() - rowNum + 1;

		if (up)
		{
			if (rowNum == 0)
			{
				continue;
			}

			auto row = rowNum - 1;
			auto moveTo = rowNum + rowCount;

			grid->InsertRows(moveTo);

			GridTransfer(grid, row, grid, moveTo);

			BackgroundColorUpdate(grid, moveTo, ToTaskName(grid->GetCellValue(moveTo, 0).ToStdString()));

			grid->DeleteRows(row);

			auto it1 = StepGridData.begin();
			it1 += row;

			auto data = *it1;
			StepGridData.erase(it1);

			auto it2 = StepGridData.begin();
			it2 += moveTo - 1;

			StepGridData.insert(it2, data);
		}
		else
		{
			if ((rowNum + rowCount) == (grid->GetNumberRows()))
			{
				continue;
			}

			auto row = rowNum + rowCount;
			auto moveTo = rowNum;

			grid->InsertRows(moveTo);

			GridTransfer(grid, row + 1, grid, moveTo);

			grid->DeleteRows(row + 1);

			BackgroundColorUpdate(grid, moveTo, ToTaskName(grid->GetCellValue(moveTo, 0).ToStdString()));

			auto it1 = StepGridData.begin();
			it1 += row;

			auto it2 = StepGridData.begin();
			it2 += moveTo;

			auto data = *it1;
			StepGridData.erase(it1);
			StepGridData.insert(it2, data);
		}
	}
}

void cMain::GroupTemplateMoveRow(wxGrid* grid, wxComboBox* cmb, bool up, map<string, vector<StepParameters>>& map)
{
	if (!grid->IsSelection() || !grid->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	for (const auto& block : grid->GetSelectedRowBlocks())
	{
		auto rowNum = block.GetTopRow();
		auto rowCount = block.GetBottomRow() - rowNum + 1;

		auto row = 0;
		if (up)
		{
			if (rowNum == 0)
			{
				continue;
			}

			row = rowNum - 1;

		}
		else
		{
			if ((rowNum + rowCount) == (grid->GetNumberRows()))
			{
				continue;
			}

			row = rowNum + rowCount + 1;
			rowCount = 0;
		}

		grid->InsertRows(rowNum + rowCount);

		GridTransfer(grid, row, grid, rowNum + rowCount);

		BackgroundColorUpdate(grid, rowNum + rowCount, ToTaskName(grid->GetCellValue(rowNum + rowCount, 0).ToStdString()));

		grid->DeleteRows(row);

		if (!map.empty())
		{
			std::string map_name = cmb->GetValue().ToStdString();
			if (map.find(map_name) != map.end())
			{
				if (up)
				{

					auto it1 = map[map_name].begin();
					it1 += row;

					auto data = *it1;
					map[map_name].erase(it1);

					auto it2 = map[map_name].begin();
					it2 += rowNum + rowCount - 1;
					map[map_name].insert(it2, data);
				}
				else
				{
					auto it1 = map[map_name].begin();
					it1 += row - 1;

					auto it2 = map[map_name].begin();
					it2 += rowNum;

					auto data = *it1;
					map[map_name].erase(it1, it1 + 1);
					map[map_name].insert(it2, data);
				}
			}
		}
	}
}

bool cMain::DeleteRow(wxGrid* grid, wxComboBox* cmb, map<string, vector<StepParameters>>& map)
{
	if (!grid->IsSelection())
	{
		wxMessageBox("Please select row(s) to be deleted", "Selection not valid");
		return false;
	}

	row_selections.clear();

	auto rowNum = 0;
	auto rowCount = 0;

	for (const auto& block : grid->GetSelectedRowBlocks())
	{
		rowNum = block.GetTopRow();
		rowCount = block.GetBottomRow() - rowNum + 1;

		row_selections.push_back(std::to_string(block.GetTopRow()) + "," + std::to_string(block.GetBottomRow() - block.GetTopRow() + 1));
	}

	auto rowsDeleted = 0;

	for (const auto& selection : row_selections)
	{
		long long pos = selection.find(",");

		rowNum = std::stoi(selection.substr(0, pos)) - rowsDeleted;
		rowCount = std::stoi(selection.substr(pos + 1));

		grid->DeleteRows(rowNum, rowCount);

		if (!map.empty())
		{
			std::string map_name = cmb->GetValue().ToStdString();

			if (map.find(map_name) != map.end())
			{
				auto it1 = map[map_name].begin();
				auto it2 = map[map_name].begin();

				it1 += rowNum;
				it2 += rowNum + rowCount;

				map[map_name].erase(it1, it2);
			}
		}

		rowsDeleted += rowCount;
	}

	return true;
}

bool cMain::ChangeRow(wxGrid* grid, StepParameters step)
{
	if (!grid->IsSelection() || !grid->GetSelectedRows().begin())
	{
		wxMessageBox("Please select a row to change", "Selection not valid");
		return false;
	}

	auto rowNum = *grid->GetSelectedRows().begin();

	if (!ValidateStep(rowNum, step, false))
	{
		return false;
	}

	GridEntry gridEntry = PrepareStepParametersForGrid(&step);

	PopulateGrid(grid, rowNum, &gridEntry);

	BackgroundColorUpdate(grid, rowNum, step.TaskEnum);

	return true;
}

void cMain::BackgroundColorUpdate(wxGrid* grid, int row, TaskName task)
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

void cMain::UpdateGroupTemplateGrid(wxGrid* grid, vector<StepParameters>& steps)
{
	if (grid->GetNumberRows() > 0)
	{
		grid->DeleteRows(0, grid->GetNumberRows());
	}

	grid->InsertRows(0, steps.size());

	for (int i = 0; i < steps.size(); i++)
	{
		GridEntry gridEntry = PrepareStepParametersForGrid(&steps[i]);

		PopulateGrid(grid, i, &gridEntry);

		BackgroundColorUpdate(grid, i, steps[i].TaskEnum);
	}
}

void cMain::OnAddTaskClicked(wxCommandEvent& event)
{
	if (grid_tasks->IsSelection())
	{
		if (!grid_tasks->GetSelectedRows().begin())
		{
			return;
		}

		AddTask(*grid_tasks->GetSelectedRows().begin());
	}
	else
	{
		AddTask(grid_tasks->GetNumberRows());
	}
	
	event.Skip();
}

void cMain::AddTask(int row)
{
	auto stepParameters = ExtractStepParameters();

	if (!ValidateStep(row, stepParameters))
	{
		return;
	};

	string to_check;
	switch (stepParameters.TaskEnum)
	{
		case e_build:
			stepParameters.BuildingIndex = BuildingNameToIndex.find(stepParameters.Item)->second;

			UpdateStepGrid(row , &stepParameters);

			to_check = stepParameters.Item;

			stepParameters.TaskEnum = e_put;
			stepParameters.Task = struct_tasks_list.put;
			stepParameters.Amount = "1";

			if (check_furnace->IsChecked() && to_check == struct_auto_put_furnace_list.stone || to_check == struct_auto_put_furnace_list.steel)
			{
				stepParameters.Item = struct_fuel_list.coal;
				stepParameters.FromInto = struct_from_into_list.fuel;

				UpdateStepGrid(row, &stepParameters);
				return;
			}

			if (check_burner->IsChecked() && to_check == struct_auto_put_burner_list.burner_mining_drill || to_check == struct_auto_put_burner_list.burner_inserter || to_check == struct_auto_put_burner_list.boiler)
			{
				stepParameters.Item = struct_fuel_list.coal;
				stepParameters.FromInto = struct_from_into_list.fuel;

				UpdateStepGrid(row, &stepParameters);
				return;
			}

			if (check_lab->IsChecked() && to_check == struct_science_list.lab)
			{
				stepParameters.Item = "Automation science pack";
				stepParameters.FromInto = struct_from_into_list.input;

				UpdateStepGrid(row, &stepParameters);
				return;
			}

			return;

		case e_recipe:
			UpdateStepGrid(row, &stepParameters);

			to_check = stepParameters.Item;

			if (check_recipe->IsChecked())
			{
				vector<string> recipe = recipes.find(to_check)->second;

				int multiplier = stoi(stepParameters.Amount);
				for (int i = 0; i < recipe.size(); i += 2)
				{
					stepParameters.TaskEnum = e_put;
					stepParameters.Task = struct_tasks_list.put;
					stepParameters.Amount = to_string(stoi(recipe[i + 1]) * multiplier);
					stepParameters.Item = recipe[i];
					stepParameters.FromInto = struct_from_into_list.input;

					UpdateStepGrid(row, &stepParameters);
				}
			}

			return;

		default:
			UpdateStepGrid(row, &stepParameters);
			return;
	}
}

void cMain::OnChangeTaskClicked(wxCommandEvent& event)
{
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select a row to change", "Selection not valid");
		event.Skip();
		return;
	}

	int row = *grid_tasks->GetSelectedRows().begin();
	if (StepGridData[row].TaskEnum == e_build)
	{
		if (wxMessageBox("The row selected is a build task - are you sure you want to make this change?\nEnsure that you delete associated steps.", "The build task you are changing could be associated with future tasks", wxICON_WARNING | wxYES_NO, this) != wxYES)
		{
			return;
		}
	}

	auto stepParameters = ExtractStepParameters();
	GridEntry gridEntry = PrepareStepParametersForGrid(&stepParameters);

	StepGridData[row] = stepParameters;
	PopulateGrid(grid_tasks, row, &gridEntry);

	grid_tasks->SelectRow(row);
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
	int startRow = 0;
	int RowsToDelete = 0;

	// Find the first block of rows selected - extract the first row and the amount of rows in the block
	for (const auto& block : grid_tasks->GetSelectedRowBlocks())
	{
		if (counter == 1)
		{
			startRow = block.GetTopRow();
			RowsToDelete = block.GetBottomRow() - startRow + 1;

			counter++;
			continue;
		}

		row_selections.push_back(std::to_string(block.GetTopRow()) + "," + std::to_string(block.GetBottomRow() - block.GetTopRow() + 1));
		counter++;
	}

	counter--;

	for (int i = startRow; i < (startRow + RowsToDelete); i++)
	{
		if (StepGridData[i].TaskEnum == e_build)
		{
			if (wxMessageBox("At least one of the rows selected is a build task - are you sure you want to delete the rows selected?\nEnsure that you delete associated steps.", "The build task(s) you are deleting could be associated with future tasks", wxICON_WARNING | wxYES_NO, this) != wxYES)
			{
				return;
			}

			break;
		}
	}

	grid_tasks->DeleteRows(startRow, RowsToDelete);

	auto it1 = StepGridData.begin();
	auto it2 = StepGridData.begin();

	it1 += startRow;
	it2 += startRow + RowsToDelete;

	StepGridData.erase(it1, it2);

	// The row after the deleted row(s) are selected if there were no other row blocks selected
	if (counter == 1)
	{
		if (startRow < grid_tasks->GetNumberRows())
		{
			grid_tasks->SelectRow(startRow);
		}
		else if(startRow - 1 >= 0)
		{
			grid_tasks->SelectRow(startRow - 1);
		}
	}
	else
	{
		// Otherwise the other selections are selected once more
		grid_tasks->ClearSelection();

		auto StartRow = 0;
		auto rowCount = 0;
		for (const auto& selection : row_selections)
		{
			long long pos = selection.find(",");

			StartRow = std::stoi(selection.substr(0, pos)) - RowsToDelete;
			rowCount = std::stoi(selection.substr(pos + 1));

			int total_rows = StartRow + rowCount;

			for (int i = StartRow; i < total_rows; i++)
			{
				grid_tasks->SelectRow(i, true);
			}
		}
	}

	event.Skip();
}

void cMain::OnMoveUpClicked(wxCommandEvent& event)
{
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	MoveRow(grid_tasks, true);
	event.Skip();
}

void cMain::OnMoveDownClicked(wxCommandEvent& event)
{
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	MoveRow(grid_tasks, false);
	event.Skip();
}

void cMain::OnMoveUpFiveClicked(wxMouseEvent& event)
{
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	for (int i = 0; i < 5; i++)
	{
		MoveRow(grid_tasks, true);
	}

	event.Skip();
}

void cMain::OnMoveDownFiveClicked(wxMouseEvent& event)
{
	if (!grid_tasks->IsSelection() || !grid_tasks->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	for (int i = 0; i < 5; i++)
	{
		MoveRow(grid_tasks, false);
	}

	event.Skip();
}

void cMain::OnTasksGridDoubleLeftClick(wxGridEvent& event)
{
	auto gridEntry = ExtractGridEntry(grid_tasks, event.GetRow());

	UpdateParameters(&gridEntry, event);

	event.Skip();
}

void cMain::OnNewGroupClicked(wxCommandEvent& event)
{
	int rowCount = cmb_choose_group->GetCount();
	string name = cmb_choose_group->GetValue().ToStdString();

	if (name == "")
	{
		wxMessageBox("Please write a group name", "Group name cannot be blank");
		event.Skip();
		return;
	}

	for (int i = 0; i < rowCount; i++)
	{
		if (name == cmb_choose_group->GetString(i).ToStdString())
		{
			wxMessageBox("Group names have to be unique - please write a new name in the Choose Group field", "Group names should be unique");
			event.Skip();
			return;
		}
	}

	cmb_choose_group->Clear();
	group_choices.Add(name);
	cmb_choose_group->Append(group_choices);
	cmb_choose_group->SetValue(name);
	
	vector<StepParameters> groupSteps = {};
	group_map.insert(pair<string, vector<StepParameters>>(name, groupSteps));
	
	UpdateGroupTemplateGrid(grid_group, group_map[name]);

	event.Skip();
}

void cMain::OnDeleteGroupClicked(wxCommandEvent& event)
{
	if (wxMessageBox("Are you sure you want to delete this group?", "Delete group", wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		return;
	}

	auto name = cmb_choose_group->GetValue().ToStdString();
	if (group_map.find(name) == group_map.end())
	{
		return;
	}

	group_map.erase(name);
	group_choices.Remove(name);
	cmb_choose_group->Clear();
	cmb_choose_group->Append(group_choices);

	if (group_choices.size())
	{
		cmb_choose_group->SetValue(*group_choices.begin());
		OnGroupChosen(event);
		return;
	}

	if (grid_group->GetNumberRows())
	{
		grid_group->DeleteRows(0, grid_group->GetNumberRows());
	}
}

void cMain::UpdateMapWithNewSteps(wxGrid* grid, wxComboBox* cmb, map<string, vector<StepParameters>>& map)
{
	if (!grid_tasks->IsSelection())
	{
		wxMessageBox("No step is chosen - please select row(s) in the step list", "Cannot add step to group");
		return;
	}

	auto it = map.find(cmb->GetValue().ToStdString());
	if (it == map.end())
	{
		wxMessageBox("The group name doesn't exist - please add a new group before adding steps", "Cannot add step to group");
		return;
	}

	auto moveTo = grid->GetNumberRows();
	if (grid->IsSelection())
	{
		if (!grid->GetSelectedRows().begin())
		{
			wxMessageBox("Please either select row(s) or nothing", "Group list selection not valid");
			return;
		}

		moveTo = *grid->GetSelectedRows().begin();
	}

	vector<StepParameters> steps = it->second;
	for (const auto& block : grid_tasks->GetSelectedRowBlocks())
	{
		auto startRow = block.GetTopRow();
		auto rowCount = block.GetBottomRow() - startRow + 1;

		grid->InsertRows(moveTo, rowCount);

		int rows = startRow + rowCount;

		for (int i = startRow; i < rows; i++)
		{
			GridTransfer(grid_tasks, i, grid, moveTo);

			BackgroundColorUpdate(grid, moveTo, StepGridData[i].TaskEnum);

			auto it1 = steps.begin();
			it1 += moveTo;

			steps.insert(it1, StepGridData[i]);

			moveTo += 1;
		}
	}

	it->second = steps;
}

void cMain::OnGroupAddFromTasksListClicked(wxCommandEvent& event)
{
	UpdateMapWithNewSteps(grid_group, cmb_choose_group, group_map);

	event.Skip();
}

void cMain::OnGroupAddToTasksListClicked(wxCommandEvent& event)
{
	int moveTo = grid_tasks->GetNumberRows();

	if (grid_tasks->IsSelection())
	{
		if (!grid_tasks->GetSelectedRows().begin())
		{
			wxMessageBox("Please either select row(s) or nothing", "Task list selection not valid");
			return;
		}

		moveTo = *grid_tasks->GetSelectedRows().begin();
	}

	if (grid_group->IsSelection())
	{
		for (const auto& block : grid_group->GetSelectedRowBlocks())
		{
			int row = block.GetTopRow();
			int rowCount = block.GetBottomRow() - row + 1;

			int total_rows = row + rowCount;

			for (int i = row; i < total_rows; i++)
			{
				StepParameters step = group_map[cmb_choose_group->GetValue().ToStdString()][i];

				UpdateStepGrid(moveTo, &step);

				moveTo += 1;
			}
		}

		return;
	}

	int rows = grid_group->GetNumberRows();

	for (int i = 0; i < rows; i++)
	{
		StepParameters step = group_map[cmb_choose_group->GetValue().ToStdString()][i];

		UpdateStepGrid(moveTo, &step);

		moveTo += 1;
	}
}

void cMain::GridTransfer(wxGrid* from, const int& fromRow, wxGrid* to, const int& toRow)
{
	to->SetCellValue(toRow, 0, from->GetCellValue(fromRow, 0));
	to->SetCellValue(toRow, 1, from->GetCellValue(fromRow, 1));
	to->SetCellValue(toRow, 2, from->GetCellValue(fromRow, 2));
	to->SetCellValue(toRow, 3, from->GetCellValue(fromRow, 3));
	to->SetCellValue(toRow, 4, from->GetCellValue(fromRow, 4));
	to->SetCellValue(toRow, 5, from->GetCellValue(fromRow, 5));
	to->SetCellValue(toRow, 6, from->GetCellValue(fromRow, 6));
	to->SetCellValue(toRow, 7, from->GetCellValue(fromRow, 7));
	to->SetCellValue(toRow, 8, from->GetCellValue(fromRow, 8));
	to->SetCellValue(toRow, 9, from->GetCellValue(fromRow, 9));
}

void cMain::OnGroupChangeClicked(wxCommandEvent& event)
{
	auto stepParameters = ExtractStepParameters();
	
	if (!ChangeRow(grid_group, stepParameters))
	{
		return;
	}

	auto name = cmb_choose_group->GetValue().ToStdString();
	if (group_map.find(name) == group_map.end())
	{
		return;
	}
	
	auto rowNum = *grid_group->GetSelectedRows().begin();

	group_map[name][rowNum] = stepParameters;

	event.Skip();
}

void cMain::OnGroupDeleteClicked(wxCommandEvent& event)
{
	if (wxMessageBox("Are you sure you want to delete this group task?", "Delete group task", wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		return;
	}

	DeleteRow(grid_group, cmb_choose_group, group_map);

	event.Skip();
}

void cMain::OnGroupMoveUpClicked(wxCommandEvent& event)
{
	GroupTemplateMoveRow(grid_group, cmb_choose_group, true, group_map);

	event.Skip();
}

void cMain::OnGroupMoveDownClicked(wxCommandEvent& event)
{
	GroupTemplateMoveRow(grid_group, cmb_choose_group, false, group_map);

	event.Skip();
}

void cMain::OnGroupGridDoubleLeftClick(wxGridEvent& event)
{
	auto gridEntry = ExtractGridEntry(grid_group, event.GetRow());

	UpdateParameters(&gridEntry, event);

	event.Skip();
}

void cMain::OnGroupChosen(wxCommandEvent& event)
{
	UpdateGroupTemplateGrid(grid_group, group_map[cmb_choose_group->GetValue().ToStdString()]);
	event.Skip();
}

void cMain::OnTemplateChosen(wxCommandEvent& event)
{
	UpdateGroupTemplateGrid(grid_template, template_map[cmb_choose_template->GetValue().ToStdString()]);
	event.Skip();
}

void cMain::OnNewTemplateClicked(wxCommandEvent& event)
{
	int rowCount = cmb_choose_template->GetCount();
	string name = cmb_choose_template->GetValue().ToStdString();

	if (name == "")
	{
		wxMessageBox("Please write a template name", "Template name cannot be blank");
		event.Skip();
		return;
	}

	for (int i = 0; i < rowCount; i++)
	{
		if (name == cmb_choose_template->GetString(i).ToStdString())
		{
			wxMessageBox("Template names have to be unique - please write a new name in the Choose Template field", "Template names should be unique");
			event.Skip();
			return;
		}
	}

	cmb_choose_template->Clear();
	template_choices.Add(name);
	cmb_choose_template->Append(template_choices);
	cmb_choose_template->SetValue(name);

	vector<StepParameters> template_list = {};
	template_map.insert(pair<string, vector<StepParameters>>(name, template_list));
	
	UpdateGroupTemplateGrid(grid_template, template_map[name]);

	event.Skip();
}

void cMain::OnDeleteTemplateClicked(wxCommandEvent& event)
{
	if (wxMessageBox("Are you sure you want to delete this template?", "Delete template", wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		event.Skip();
		return;
	}

	auto name = cmb_choose_template->GetValue().ToStdString();

	if (template_map.find(name) == template_map.end())
	{
		return;
	}

	template_map.erase(name);
	template_choices.Remove(name);
	cmb_choose_template->Clear();
	cmb_choose_template->Append(template_choices);

	if (template_choices.size())
	{
		cmb_choose_template->SetValue(*template_choices.begin());
		OnTemplateChosen(event);
		return;
	}

	if (grid_template->GetNumberRows())
	{
		grid_template->DeleteRows(0, grid_template->GetNumberRows());
	}
}

void cMain::OnTemplateAddFromTasksListClicked(wxCommandEvent& event)
{
	UpdateMapWithNewSteps(grid_template, cmb_choose_template, template_map);

	event.Skip();
}

void cMain::OnTemplateAddToTasksListClicked(wxCommandEvent& event)
{
	if (spin_amount_offset->GetValue() != 0 && spin_amount_multiplier->GetValue() != 0)
	{
		wxMessageBox("Please either use units-offset or units-multiplier", "Invalid use of template attributes");
		return;
	}

	int moveTo = grid_tasks->GetNumberRows();

	if (grid_tasks->IsSelection())
	{
		if (!grid_tasks->GetSelectedRows().begin())
		{
			wxMessageBox("Please either select row(s) or nothing", "Task list selection not valid");
			return;
		}

		moveTo = *grid_tasks->GetSelectedRows().begin();
	}

	if (grid_template->IsSelection())
	{
		for (const auto& block : grid_template->GetSelectedRowBlocks())
		{
			int row = block.GetTopRow();
			int rowCount = block.GetBottomRow() - row + 1;

			int rows = row + rowCount;

			for (int i = row; i < rows; i++)
			{
				StepParameters step = template_map[cmb_choose_template->GetValue().ToStdString()][i];

				TemplateAlterTask(step);

				UpdateStepGrid(moveTo, &step);

				moveTo += 1;
			}
		}

		return;
	}

	int rows = grid_template->GetNumberRows();

	for (int i = 0; i < rows; i++)
	{
		StepParameters step = template_map[cmb_choose_template->GetValue().ToStdString()][i];

		TemplateAlterTask(step);

		UpdateStepGrid(moveTo, &step);

		moveTo += 1;
	}
}

void cMain::TemplateAlterTask(StepParameters& step)
{
	if (step.X != invalidX)
	{
		step.X += spin_x_offset->GetValue();
		step.Y += spin_y_offset->GetValue();
	}

	if (step.Amount == "" || step.Amount == "All")
	{
		return;
	}

	if (spin_amount_offset->GetValue() != 0)
	{
		step.Amount = to_string(stoi(step.Amount) + spin_amount_offset->GetValue());
	}

	if (spin_amount_multiplier->GetValue() != 0)
	{
		step.Amount = to_string(stoi(step.Amount) * spin_amount_multiplier->GetValue());
	}
}

void cMain::OnTemplateChangeTaskClicked(wxCommandEvent& event)
{
	auto stepParameters = ExtractStepParameters();

	if (!ChangeRow(grid_template, stepParameters))
	{
		return;
	}

	auto name = cmb_choose_template->GetValue().ToStdString();
	if (template_map.find(name) == template_map.end())
	{
		return;
	}

	auto rowNum = *grid_template->GetSelectedRows().begin();

	template_map[name][rowNum] = stepParameters;

	event.Skip();
}

void cMain::OnTemplateDeleteTaskClicked(wxCommandEvent& event)
{
	if (wxMessageBox("Are you sure you want to delete this template task?", "Delete template task", wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		return;
	}

	DeleteRow(grid_template, cmb_choose_template, template_map);

	event.Skip();
}

void cMain::OnTemplateMoveUpClicked(wxCommandEvent& event)
{
	GroupTemplateMoveRow(grid_template, cmb_choose_template, true, template_map);

	event.Skip();
}

void cMain::OnTemplateMoveDownClicked(wxCommandEvent& event)
{
	GroupTemplateMoveRow(grid_template, cmb_choose_template, false, template_map);

	event.Skip();
}

void cMain::OnTemplateGridDoubleLeftClick(wxGridEvent& event)
{
	auto gridEntry = ExtractGridEntry(grid_template, event.GetRow());

	UpdateParameters(&gridEntry, event);

	event.Skip();
}

void cMain::OnApplicationClose(wxCloseEvent& event)
{
	if (!CheckBeforeClose())
	{
		return;
	}

	if (dialog_progress_bar)
	{
		delete dialog_progress_bar;
	}

	event.Skip();
}

bool cMain::ChecksBeforeResetWindow()
{
	if (grid_tasks->GetNumberRows() > 0 || grid_group->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0)
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

	if (ChecksBeforeResetWindow())
	{
		if (wxMessageBox("Are you sure you want to reset the window?\nAll in the current window will be cleared.", "Ensure that you have saved what you need before clicking yes", wxICON_QUESTION | wxYES_NO, this) == wxYES)
		{
			ResetToNewWindow();
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

		if (ChecksBeforeResetWindow())
		{
			if (wxMessageBox("Are you sure you want to open this file?\nAll in the current window will be cleared.", "Ensure that you have saved what you need before clicking yes", wxICON_QUESTION | wxYES_NO, this) == wxYES)
			{
				ResetToNewWindow();
			}
			else
			{
				return;
			}
		}

		if (!dialog_progress_bar)
		{
			dialog_progress_bar = new DialogProgressBar(this, wxID_ANY, "Processing request");
		}

		OpenTas open;
		open_file_return_data* result = open.Open(dialog_progress_bar, file);

		if (!result->success)
		{
			malformed_saved_file_message();
			return;
		}

		StepGridData = result->steps;
		group_map = result->group_map;
		template_map = result->template_map;
		save_file_location = result->save_file_location;
		generate_code_folder_location = result->generate_code_folder_location;

		if (result->goal == goal_steelaxe_text)
		{
			menu_goals->GetMenuItems()[0]->Check();
		}
		else if (result->goal == goal_GOTLAP_text)
		{
			menu_goals->GetMenuItems()[1]->Check();
		}
		else if (result->goal == goal_any_percent_text)
		{
			menu_goals->GetMenuItems()[2]->Check();
		}
		else if (result->goal == goal_debug_text)
		{
			menu_goals->GetMenuItems()[3]->Check();
		}
		else
		{
			malformed_saved_file_message();
			return;
		}

		menu_auto_close->GetMenuItems()[0]->Check(result->auto_close_generate_script);
		auto_close_generate_script = result->auto_close_generate_script;

		menu_auto_close->GetMenuItems()[1]->Check(result->auto_close_open);
		auto_close_open = result->auto_close_open;

		menu_auto_close->GetMenuItems()[2]->Check(result->auto_close_save);
		auto_close_save = result->auto_close_save;

		menu_auto_close->GetMenuItems()[3]->Check(result->auto_close_save_as);
		auto_close_save_as = result->auto_close_save_as;

		check_furnace->SetValue(result->auto_put_furnace);
		check_burner->SetValue(result->auto_put_burner);
		check_lab->SetValue(result->auto_put_lab);
		check_recipe->SetValue(result->auto_put_recipe);

		PopulateStepGrid();

		dialog_progress_bar->set_progress(100.0f - 35);
		wxYield();

		if (result->group_map.size())
		{
			vector<string> keys = get_keys(result->group_map);

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

		if (result->template_map.size())
		{
			std::vector<std::string> keys = get_keys(result->template_map);

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

void cMain::PopulateStepGrid()
{
	if (grid_tasks->GetNumberRows() > 0)
	{
		grid_tasks->DeleteRows(0, grid_tasks->GetNumberRows());
	}

	size_t amount_of_tasks = StepGridData.size();

	grid_tasks->InsertRows(0, amount_of_tasks);

	for (int i = 0; i < amount_of_tasks; i++)
	{
		GridEntry gridEntry = PrepareStepParametersForGrid(&StepGridData[i]);

		PopulateGrid(grid_tasks, i, &gridEntry);

		BackgroundColorUpdate(grid_tasks, i, StepGridData[i].TaskEnum);
	}
}

void cMain::OnMenuSave(wxCommandEvent& event)
{
	SaveFile(false);

	event.Skip();
}

void cMain::OnMenuSaveAs(wxCommandEvent& event)
{
	SaveFile(true);

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
	generate_script.generate(this, dialog_progress_bar, StepGridData, generate_code_folder_location, auto_close_generate_script, menu_script->GetMenuItems()[2]->IsChecked(), goal);

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

void cMain::UpdateParameters(GridEntry* gridEntry, wxCommandEvent& event)
{
	TaskName task = ToTaskName(gridEntry->Task.ToStdString());

	string orientation = "";
	float speed;
	long long pos;
	switch (task)
	{
		case e_start:
			OnStartMenuSelected(event);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_stop:
			OnStopMenuSelected(event);
			speed = stof(gridEntry->Amount.ToStdString()) * 100.0;
			spin_amount->SetValue(speed);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_build:
			OnBuildMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			cmb_item->SetValue(gridEntry->Item);
			cmb_building_orientation->SetValue(gridEntry->BuildingOrientation);
			cmb_direction_to_build->SetValue(gridEntry->DirectionToBuild);
			spin_building_size->SetValue(gridEntry->BuildingSize);
			spin_building_amount->SetValue(gridEntry->AmountOfBuildings);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_craft:
			OnCraftMenuSelected(event);
			spin_amount->SetValue(gridEntry->Amount);
			cmb_item->SetValue(gridEntry->Item);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_game_speed:
			OnGameSpeedMenuSelected(event);
			speed = stof(gridEntry->Amount.ToStdString()) * 100.0;
			spin_amount->SetValue(speed);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_pause:
			OnStopMenuSelected(event);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_save:
			OnSaveMenuSelected(event);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_recipe:
			OnRecipeMenuChosen(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			cmb_direction_to_build->SetValue(gridEntry->DirectionToBuild);
			spin_building_size->SetValue(gridEntry->BuildingSize);
			spin_building_amount->SetValue(gridEntry->AmountOfBuildings);
			cmb_item->SetValue(gridEntry->Item);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_limit:
			OnLimitMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			spin_amount->SetValue(gridEntry->Amount);
			cmb_direction_to_build->SetValue(gridEntry->DirectionToBuild);
			spin_building_size->SetValue(gridEntry->BuildingSize);
			spin_building_amount->SetValue(gridEntry->AmountOfBuildings);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_filter:
			OnFilterMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			spin_amount->SetValue(gridEntry->Amount);
			cmb_item->SetValue(gridEntry->Item);
			cmb_direction_to_build->SetValue(gridEntry->DirectionToBuild);
			spin_building_size->SetValue(gridEntry->BuildingSize);
			spin_building_amount->SetValue(gridEntry->AmountOfBuildings);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_rotate:
			OnRotateMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			spin_amount->SetValue(gridEntry->Amount);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_priority:
			OnPriorityMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			cmb_direction_to_build->SetValue(gridEntry->DirectionToBuild);
			spin_building_size->SetValue(gridEntry->BuildingSize);
			spin_building_amount->SetValue(gridEntry->AmountOfBuildings);

			orientation = gridEntry->BuildingOrientation.ToStdString();
			pos = orientation.find(",");

			radio_input->Select(map_input_output[orientation.substr(0, pos)]);
			radio_output->Select(map_input_output[orientation.substr(pos + 2)]);

			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_put:
			OnPutMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			spin_amount->SetValue(gridEntry->Amount);
			cmb_item->SetValue(gridEntry->Item);
			cmb_from_into->SetValue(gridEntry->BuildingOrientation);
			cmb_direction_to_build->SetValue(gridEntry->DirectionToBuild);
			spin_building_size->SetValue(gridEntry->BuildingSize);
			spin_building_amount->SetValue(gridEntry->AmountOfBuildings);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_take:
			OnTakeMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			spin_amount->SetValue(gridEntry->Amount);
			cmb_item->SetValue(gridEntry->Item);
			cmb_from_into->SetValue(gridEntry->BuildingOrientation);
			cmb_direction_to_build->SetValue(gridEntry->DirectionToBuild);
			spin_building_size->SetValue(gridEntry->BuildingSize);
			spin_building_amount->SetValue(gridEntry->AmountOfBuildings);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_mine:
			OnMineMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			spin_amount->SetValue(gridEntry->Amount);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_launch:
			OnLaunchMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_walk:
			OnWalkMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_tech:
			OnTechMenuSelected(event);
			cmb_item->SetValue(gridEntry->Item);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_drop:
			OnDropMenuSelected(event);
			spin_x->SetValue(gridEntry->X);
			spin_y->SetValue(gridEntry->Y);
			cmb_item->SetValue(gridEntry->Item);
			cmb_direction_to_build->SetValue(gridEntry->DirectionToBuild);
			spin_building_size->SetValue(gridEntry->BuildingSize);
			spin_building_amount->SetValue(gridEntry->AmountOfBuildings);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_pick_up:
			OnPickUpMenuSelected(event);
			spin_amount->SetValue(gridEntry->Amount);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		case e_idle:
			OnIdleMenuSelected(event);
			spin_amount->SetValue(gridEntry->Amount);
			txt_comment->SetValue(gridEntry->Comment);

			return;
		default:
			return;
	}
}



// TODO: Do you want to show the item and orientation of the building rotated?
void cMain::update_future_rotate_tasks()
{
	/*int total_rows = grid_tasks->GetNumberRows();

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
	}*/
}

string cMain::find_new_orientation(string originalOrientaion, const int& rotateAmount)
{
	for (auto it = build_orientations.begin(); it < build_orientations.end(); it++)
	{
		if (originalOrientaion == *it)
		{
			return build_orientations[((it - build_orientations.begin()) + rotateAmount) % 4];
		}
	}

	return originalOrientaion;
}

void cMain::malformed_saved_file_message()
{
	ResetToNewWindow();
	wxMessageBox("It seems like the structure of the file does not correspond with an EZRaiderz TAS helper file", "A file error occurred");
	dialog_progress_bar->set_button_enable(true);
}



bool cMain::SaveFile(bool save_as)
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
		StepGridData,
		group_map,
		template_map,
		save_file_location,
		generate_code_folder_location,
		goal);

	std::string file_name = save_file_location.substr(save_file_location.rfind("\\") + 1);

	SetLabel(window_title + " - " + file_name);

	return true;
}

StepParameters cMain::ExtractStepParameters()
{
	auto stepParameters = StepParameters(spin_x->GetValue(), spin_y->GetValue());

	stepParameters.Task = ExtractTask();
	stepParameters.Amount = ExtractAmount();
	stepParameters.Item = Capitalize(cmb_item->GetValue(), true);
	stepParameters.FromInto = Capitalize(cmb_from_into->GetValue());
	stepParameters.Orientation = Capitalize(cmb_building_orientation->GetValue());
	stepParameters.Direction = Capitalize(cmb_direction_to_build->GetValue());
	stepParameters.Size = spin_building_size->GetValue();
	stepParameters.Buildings = spin_building_amount->GetValue();
	stepParameters.PriorityIn = input_output[radio_input->GetSelection()];
	stepParameters.PriorityOut = input_output[radio_output->GetSelection()];
	stepParameters.Comment = txt_comment->GetValue().ToStdString();

	stepParameters.TaskEnum = TaskNames.find(stepParameters.Task)->second;

	return stepParameters;
}

std::string cMain::ExtractAmount()
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

GridEntry cMain::PrepareStepParametersForGrid(StepParameters* stepParameters)
{
	GridEntry gridEntry{
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
			gridEntry.Amount = stepParameters->Amount;

		case e_craft:
			gridEntry.Amount = stepParameters->Amount;
			gridEntry.Item = stepParameters->Item;
			break;

		case e_walk:
		case e_launch:
			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			break;

		case e_mine:
			if (stepParameters->BuildingIndex != 0)
			{
				gridEntry.Item = FindBuildingName(stepParameters->BuildingIndex); 
			}

			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			gridEntry.Amount = stepParameters->Amount;
			break;

		case e_rotate:

			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			gridEntry.Amount = stepParameters->Amount;
			gridEntry.Item = FindBuildingName(stepParameters->BuildingIndex);
			break;

		case e_build:
			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			gridEntry.Item = stepParameters->Item;
			gridEntry.BuildingOrientation = stepParameters->Orientation;
			gridEntry.DirectionToBuild = stepParameters->Direction;
			gridEntry.BuildingSize = std::to_string(stepParameters->Size);
			gridEntry.AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_take:
		case e_put:
			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			gridEntry.Amount = stepParameters->Amount;
			gridEntry.Item = stepParameters->Item;
			gridEntry.BuildingOrientation = stepParameters->FromInto;
			gridEntry.DirectionToBuild = stepParameters->Direction;
			gridEntry.BuildingSize = std::to_string(stepParameters->Size);
			gridEntry.AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_tech:
			gridEntry.Item = stepParameters->Item;
			break;

		case e_recipe:
			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			gridEntry.Amount = stepParameters->Amount;
			gridEntry.Item = stepParameters->Item;
			gridEntry.DirectionToBuild = stepParameters->Direction;
			gridEntry.BuildingSize = std::to_string(stepParameters->Size);
			gridEntry.AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_limit:
			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			gridEntry.Amount = stepParameters->Amount;
			gridEntry.BuildingOrientation = "Chest";
			gridEntry.DirectionToBuild = stepParameters->Direction;
			gridEntry.BuildingSize = std::to_string(stepParameters->Size);
			gridEntry.AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_priority:
			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			gridEntry.BuildingOrientation = stepParameters->PriorityIn + "," + stepParameters->PriorityOut;
			gridEntry.DirectionToBuild = stepParameters->Direction;
			gridEntry.BuildingSize = std::to_string(stepParameters->Size);
			gridEntry.AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_drop:
			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			gridEntry.Item = stepParameters->Item;
			gridEntry.DirectionToBuild = stepParameters->Direction;
			gridEntry.BuildingSize = std::to_string(stepParameters->Size);
			gridEntry.AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;

		case e_filter:
			gridEntry.X = std::to_string(stepParameters->X);
			gridEntry.Y = std::to_string(stepParameters->Y);
			gridEntry.Amount = stepParameters->Amount;
			gridEntry.Item = stepParameters->Item;
			gridEntry.DirectionToBuild = stepParameters->Direction;
			gridEntry.BuildingSize = std::to_string(stepParameters->Size);
			gridEntry.AmountOfBuildings = std::to_string(stepParameters->Buildings);
			break;
	}

	return gridEntry;
}

// ensure that the variables are actually what they are supposed to be
void cMain::UpdateStepGrid(int row, StepParameters* stepParameters)
{
	GridEntry gridEntry = PrepareStepParametersForGrid(stepParameters);

	grid_tasks->InsertRows(row, 1);

	PopulateGrid(grid_tasks, row, &gridEntry);

	if (grid_tasks->IsSelection())
	{
		auto it1 = StepGridData.begin();
		it1 += row;

		StepGridData.insert(it1, *stepParameters);
	}
	else
	{
		StepGridData.push_back(*stepParameters);
	}

	BackgroundColorUpdate(grid_tasks, row, stepParameters->TaskEnum);
}

int cMain::GenerateBuildingSnapShot(int end_row)
{
	int buildingsInSnapShot = 0;

	for (int i = 0; i < end_row; i++)
	{
		switch (StepGridData[i].TaskEnum)
		{
			case e_build:
				buildingsInSnapShot = ProcessBuildStep(BuildingsSnapShot, buildingsInSnapShot, StepGridData[i]);
				continue;

			case e_mine:
				ProcessMiningStep(BuildingsSnapShot, buildingsInSnapShot, StepGridData[i]);

				continue;

			default:
				continue;
		}
	}

	return buildingsInSnapShot;
}

GridEntry cMain::ExtractGridEntry(wxGrid* grid, const int& row)
{
	GridEntry gridEntry{
		.Task = grid->GetCellValue(row, 0),
		.X = grid->GetCellValue(row, 1),
		.Y = grid->GetCellValue(row, 2),
		.Amount = grid->GetCellValue(row, 3),
		.Item = grid->GetCellValue(row, 4),
		.BuildingOrientation = grid->GetCellValue(row, 5),
		.DirectionToBuild = grid->GetCellValue(row, 6),
		.BuildingSize = grid->GetCellValue(row, 7),
		.AmountOfBuildings = grid->GetCellValue(row, 8),
		.Comment = grid->GetCellValue(row, 9)
	};

	return gridEntry;
}

bool cMain::ValidateStep(const int& row, StepParameters& stepParameters, bool validateBuildSteps)
{
	// Cases where an association with a building isn't needed
	switch (stepParameters.TaskEnum)
	{
		case e_start:
		case e_walk:
		case e_game_speed:
		case e_pause:
		case e_save:
		case e_stop:
		case e_pick_up:
		case e_idle:
			return true;

		case e_build:
			return IsValidBuildStep(stepParameters);

		case e_craft:
			return IsValidCraftStep(stepParameters);

		case e_tech:
			return IsValidTechnologyStep(stepParameters);

		default:
			break;
	}

	if (!validateBuildSteps)
	{
		return true;
	}

	int amountOfBuildings = GenerateBuildingSnapShot(row);
	switch (stepParameters.TaskEnum)
	{
		case e_recipe:
			if (!BuildingExists(BuildingsSnapShot, amountOfBuildings, stepParameters))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
				return false;
			};

			return IsValidRecipeStep(stepParameters);

		case e_mine:
			// A building doesn't need to exist, but if it does it should be noted.
			BuildingExists(BuildingsSnapShot, amountOfBuildings, stepParameters);

		case e_put:
		case e_take:
			if (!IsValidPutTakeStep(stepParameters))
			{
				return false;
			}

			if (!BuildingExists(BuildingsSnapShot, amountOfBuildings, stepParameters))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
				return false;
			};

			return true;

		default:

			if (!BuildingExists(BuildingsSnapShot, amountOfBuildings, stepParameters))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
				return false;
			};

			return true;
	}
}

bool cMain::IsValidBuildStep(StepParameters& stepParameters)
{
	if (!check_input(stepParameters.Item, all_buildings))
	{
		wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
		return false;
	}

	if (!check_input(stepParameters.Orientation, build_orientations))
	{
		wxMessageBox("The build direction is not valid - please try again", "Please use the build direction dropdown menu");
		return false;
	}

	if (!check_input(stepParameters.Direction, build_orientations))
	{
		wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
		return false;
	}

	return true;
}

bool cMain::IsValidRecipeStep(StepParameters& stepParameters)
{
	switch (stepParameters.BuildingIndex)
	{
		case AssemblingMachine1:
			if (check_input(stepParameters.Item, part_assembly_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an assembling machine 1", "Item chosen is not valid");
			return false;

		case AssemblingMachine2:
		case AssemblingMachine3:
			if (check_input(stepParameters.Item, full_assembly_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an assembling machine", "Item chosen is not valid");
			return false;

		case OilRefinery:
			if (!check_input(stepParameters.Item, oil_refinery_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an oil refinery", "Item chosen is not valid");
			return false;

		case ChemicalPlant:
			if (!check_input(stepParameters.Item, full_chemical_plant_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a chemical plant", "Item chosen is not valid");
			return false;

		case Centrifuge:
			if (!check_input(stepParameters.Item, centrifuge_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a centrifuge", "Item chosen is not valid");
			return false;

		case StoneFurnace:
		case SteelFurnace:
		case ElectricFurnace:
			if (!check_input(stepParameters.Item, furnace_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a furnace", "Item chosen is not valid");
			return false;

		default:
			return true;;
	}
}

bool cMain::IsValidCraftStep(StepParameters& stepParameters)
{
	if (!check_input(stepParameters.Item, handcrafted_list))
	{
		wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
		return false;
	}

	return true;
}

bool cMain::IsValidPutTakeStep(StepParameters& stepParameters)
{
	if (!CheckTakePut(stepParameters))
	{
		return false;
	}

	if (!check_input(stepParameters.Direction, build_orientations))
	{
		wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
		return false;
	}

	return true;
}

bool cMain::IsValidTechnologyStep(StepParameters& stepParameters)
{
	if (!check_input(stepParameters.Item, tech_list))
	{
		wxMessageBox("The tech is not valid - please try again", "Please use the tech dropdown menu");
		return false;
	}

	return true;
}

bool cMain::CheckTakePut(StepParameters& stepParameters)
{
	std::string to_check = stepParameters.FromInto;

	if (to_check == "Wreck")
	{
		return true;
	}

	string building = FindBuildingName(stepParameters.BuildingIndex);
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
		if (check_input(stepParameters.Item, fuel_list))
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
			if (check_input(stepParameters.Item, science_packs))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a science pack.\nOnly science packs can be used as input for a lab", "Please choose a science pack");
			return false;

		}
		else if (to_check == "Modules")
		{
			if (check_input(stepParameters.Item, module_list))
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
			if (check_input(stepParameters.Item, module_list))
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
		if (check_input(stepParameters.Item, module_list))
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

// TODO: It seems like this should be used somewhere.
bool cMain::ExtraBuildingChecks(StepParameters& stepParameters)
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