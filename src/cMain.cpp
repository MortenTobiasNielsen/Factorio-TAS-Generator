#pragma once

#include "cMain.h"
#include "ShortcutChanger.h"
#include "SteptypeColour.h"

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

	for (auto& s : inventory_types_list)
	{
		take_from_choices.Add(s);
	}

	for (auto& s : tech_list)
	{
		tech_choices.Add(s);
	}

	for (auto& s : orientation_list)
	{
		building_orientation_choices.Add(s);
	}

	for (auto& s : Priority::Names)
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
	for (auto it = orientation_list.begin(); it < orientation_list.end(); it++)
	{
		cmb_building_orientation->Append(*it);
		cmb_direction_to_build->Append(*it);
	}
	cmb_building_orientation->SetValue(*orientation_list.begin());
	cmb_building_orientation->AutoComplete(building_orientation_choices);
	cmb_direction_to_build->SetValue(*orientation_list.begin());
	cmb_direction_to_build->AutoComplete(building_orientation_choices);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++)
	{
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	cmb_from_into->Clear();
	for (auto it = inventory_types_list.begin(); it < inventory_types_list.end(); it++)
	{
		cmb_from_into->Append(*it);
	}
	cmb_from_into->SetValue(*inventory_types_list.begin());
	cmb_from_into->AutoComplete(take_from_choices);

	// set steps grid formatting
	grid_steps->SetColFormatFloat(1, 4, 2);
	grid_steps->SetColFormatFloat(2, 4, 2);
	grid_steps->SetColFormatNumber(8);
	grid_steps->SetColFormatNumber(9);
	grid_steps->SetSelectionMode(grid_steps->wxGridSelectRows);

	// set template grid formatting
	grid_template->SetColFormatFloat(1, 4, 2);
	grid_template->SetColFormatFloat(2, 4, 2);
	grid_template->SetColFormatNumber(3);
	grid_steps->SetColFormatNumber(8);
	grid_steps->SetColFormatNumber(9);
	grid_template->SetSelectionMode(grid_template->wxGridSelectRows);

	// Checking steel axe as a goal
	menu_goals->GetMenuItems()[0]->Check();

	// split steps into seperate panel
	wxAuiNotebook* a = (wxAuiNotebook*)step_panel->GetParent();
	a->Split(1, wxRIGHT);

	SetupWalkPanelUnicodeCharacters();

	//set shortcuts from settings file
	ShortcutChanger::UpdateShortcutsFromFile(main_menubar);
	SteptypeColourHandler::UpdateSteptypeColoursFromFile();
	settings::setting settings = settings::ReadSettingFile();
	if (settings.last_tas != "")
	{
		std::ifstream tas_file(settings.last_tas);
		Open(&tas_file);
	}
	TemplatePageStartup();
}

void cMain::OnStepsFocusCheckbox(wxCommandEvent& event)
{
	const int row_count = grid_steps->GetNumberRows();
	auto selectedRows = grid_steps->GetSelectedRows();
	const int first_row_index = grid_steps->IsSelection() ? selectedRows[0] : row_count - 1;

	steps_focus_checkbox->Disable();
	{
		HandleFocusMode(event.IsChecked(), true);
		if (first_row_index != -1)
		{
			grid_steps->GoToCell(row_count - 1, 0);
			grid_steps->GoToCell(first_row_index - (first_row_index > 4 ? 3 : 0), 0); // move the grid to first selected row
		}
	}
	steps_focus_checkbox->Enable();
}

void cMain::HandleFocusMode(bool checked, bool changed)
{
	const int row_count = grid_steps->GetNumberRows();

	if (checked)
	{
		int last_save = 0;
		for (int i = StepGridData.size() - 1; i >= 0; i--)
		{
			if (StepGridData[i].type == StepType::e_save && !StepGridData[i].Modifiers.skip)
			{
				last_save = i;
				break;
			}
		}
		if (last_save > 0)
		{
			grid_steps->BeginBatch();
			{
				for (int i = 0; i < last_save; i++)
				{
					grid_steps->HideRow(i);
					if (changed && i % 800 == 799)
					{
						grid_steps->EndBatch();
						this->Update();
						grid_steps->BeginBatch();
					}
				}
			}
			grid_steps->EndBatch();
		

			for (int i = last_save; i < row_count; i++)
				grid_steps->ShowRow(i);
		}
	}
	else
	{
		grid_steps->BeginBatch();
		{
			for (int i = 0; i < row_count; i++)
			{
				grid_steps->ShowRow(i);
				if (changed && i % 800 == 799)
				{
					grid_steps->GoToCell(row_count - 1, 0);
					grid_steps->EndBatch();
					this->Update();
					grid_steps->BeginBatch();
				}
			}
		}
		grid_steps->EndBatch();
	}
}

void cMain::OnStepsGridCellChange(wxGridEvent& event)
{
	auto row = event.GetRow();
	auto col = event.GetCol();
	auto old_string = event.GetString();
	auto new_string = grid_steps->GetCellValue(row, col);
	bool success = false;

	vector< tuple<int, Step>> change{};
	change.push_back({ row, StepGridData[row] });

	Step& step = StepGridData[row];
	switch (col) {
	case 1:
		success = new_string.ToDouble(&step.OriginalX);
		step.X = success ? step.OriginalX : step.X;
		break;

	case 2:
		success = new_string.ToDouble(&step.OriginalY);
		step.Y = success ? step.OriginalY : step.Y;
		break;

	case 3:
		success = new_string.ToInt(&step.amount) && step.amount >= 0;
		if (success && step.amount == 0) grid_steps->SetCellValue(row, col, "All");
		break;
		
	case 4:
	{
		auto new_item = new_string.ToStdString();
		auto items = &all_items;
		switch (step.type) {
		case e_build: 
			items = &all_buildings;  break;
		case e_craft:
		case e_cancel_crafting:
			items = &handcrafted_list; 
			break;
		}
		for (auto& item : *items)
		{
			if (new_item == item) {
				step.Item = new_item;
				success = true;
				break;
			}
		}
		break;
	}

	case 5:
		switch (step.type)
		{
		case e_build:
			success = MapStringToOrientation(new_string, step.orientation);
			break;
		case e_put:
		case e_take:
			try {
				step.inventory = GetInventoryType(new_string.ToStdString());
				success = true;
			} catch (...) {}
			break;
		}
		break;

	case 6: // modifiers
		step.Modifiers.FromString(new_string.ToStdString());
		grid_steps->SetCellValue(row, col, step.Modifiers.ToString());
		success = true;
		break;
		
	case 7:
		success = MapStringToOrientation(new_string, step.Direction);
		break;

	case 8:
		success = new_string.ToInt(&step.Size);
		break;

	case 9:
		success = new_string.ToInt(&step.Buildings);
		break;

	case 10:
		step.Comment = new_string.ToStdString();
		success = true;
		break;
	}

	if (!success) grid_steps->SetCellValue(row, col, old_string);
	else {
		no_changes = false;
		change.push_back({ row, step });
		stack.Push({
			.row = row,
			.type = T_MODIFY,
			.rows = change
			}
		);
	}
}

void cMain::OnStepsGridEditorShown(wxGridEvent& event)
{
	auto row = event.GetRow();
	auto col = event.GetCol();
	
	if (col == 0) 
	{
		grid_steps->SetReadOnly(row, col);
		event.Veto();
	}
}

void cMain::OnStepsGridEditorHidden(wxGridEvent& event)
{
}

void cMain::StepSeachOnText(wxCommandEvent& event)
{
	bool up = step_search_toggle_updown->GetValue();
	Search::FindCurrentOrNext(event, grid_steps, up);
	event.Skip();
}

void cMain::StepSeachOnTextEnter(wxCommandEvent& event)
{
	StepSeachOnSearchButton(event);//seems not to fire
}

void cMain::StepSeachOnSearchButton(wxCommandEvent& event)
{
	bool up = step_search_toggle_updown->GetValue();
	Search::FindNext(event, grid_steps, up);
	event.Skip();
}

void cMain::StepSeachOnCancelButton(wxCommandEvent& event)
{
	event.Skip();// do nothing, it will clear the search box
}

void cMain::OnReorderReorderButtonClicked(wxCommandEvent& event)
{
	vector<ReorderStruct> list{};
	if (!OnReorderTextValidate(list)) return;
	
	// find scope in the current step list
	int min = grid_steps->GetNumberRows(), max = 0;
	for (auto& item : list) 
	{
		min = min < item.step_number ? min : item.step_number;
		max = max > item.step_number ? max : item.step_number;
	}
	
	// moved scoped steps into a new list
	vector<ReorderStep> reorder_steplist{}; reorder_steplist.reserve(list.size());
	for (int i = min; i <= max; i++) 
	{
		Step& step = StepGridData[i];
		for (int j = 0; j < step.Buildings; j++) // unroll multibuild
		{
			if (step.type == e_rotate && step.amount != 3)
				for (int k = 0; k < step.amount; k++) reorder_steplist.push_back({step, i, j});
			else
				reorder_steplist.push_back({step, i, j});
			step.Next();
		}
	}

	// set number of buildings to 1 since multibuild has been unrolled
	for (ReorderStep& step : reorder_steplist)
	{
		step.step.OriginalX = step.step.X;
		step.step.OriginalY = step.step.Y;
		step.step.Buildings = 1;
		step.step.amount = step.step.type == e_rotate && step.step.amount != 3 ? 1 : step.step.amount ;
		step.step.Modifiers.force = false;
	}
	
	// reorder the existing steps using the new order
	vector<Step> steplist{}; steplist.reserve(list.size());
	for (ReorderStruct& new_position : list) 
	{
		bool found = false;
		for (ReorderStep& step : reorder_steplist)
		{
			if (step.step_number == new_position.step_number && step.substep_number == new_position.substep_number)
			{
				steplist.push_back(step.step);
				found = true;
				break;
			}
		}
		if (found) continue;
		else throw "item "+ std::to_string(new_position.index) + " not found";
	}

	grid_steps->DeleteRows(min, max - min + 1);
	grid_steps->InsertRows(min, steplist.size());

	StepGridData.erase(StepGridData.begin() + min, StepGridData.begin() + max + 1);
	StepGridData.insert(StepGridData.begin() + min, steplist.begin(), steplist.end());
	
	for (int i = min; i < min + steplist.size(); i++)
	{
		Step& step = StepGridData[i];
		GridEntry gridEntry = PrepareStepForGrid(&step);
		PopulateGrid(grid_steps, i, &gridEntry);
		BackgroundColorUpdate(grid_steps, i, step.type);
	}

	if (reorder_text_input_clear_checkbox->GetValue())
		reorder_text_input->SetValue("");
}
void cMain::OnReorderLocatorButtonClicked(wxCommandEvent& event)
{
	vector<ReorderStruct> list{};
	if (!OnReorderTextValidate(list)) return;
	int min = grid_steps->GetNumberRows();
	grid_steps->ClearSelection();
	for (auto& item : list)
	{
		min = min < item.step_number ? min : item.step_number;
		grid_steps->SelectRow(item.step_number, true);
	}
	grid_steps->GoToCell(min, 0);
}
void cMain::OnReorderTextUpdate(wxCommandEvent& event)
{
	vector<ReorderStruct> list{};
	bool result = OnReorderTextValidate(list);
	reorder_reorder_button->Enable(result);
	reorder_locator_button->Enable(result);
}
bool cMain::OnReorderTextValidate(vector<ReorderStruct>& out)
{
	out.clear();

	stringstream input{
		reorder_text_input->GetValue().ToStdString()
	};
	for (string line; std::getline(input, line);)
	{
		if (line.size() < 6) continue; // There needs to be at least 6 chars to be valid
		ReorderStruct out_segment{};
		stringstream line_input{line};
		string segment;
		for (int i = 0; i < 3; i++)
		{
			if (!std::getline(line_input, segment, ';')) 
				return false;
			try {
				switch (i)
				{
					case 0: out_segment.index = stoi(segment); break;
					case 1: out_segment.step_number = stoi(segment) - 1; break;
					case 2: out_segment.substep_number = stoi(segment) - 1; break;
				}
			}
			catch (...)
			{
				return false;
			}
		}
		out.push_back(out_segment);
	}
	return out.size() > 1;
}

void cMain::ResetToNewWindow()
{
	if (grid_steps->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0)
	{
		if (grid_steps->GetNumberRows() > 0)
		{
			grid_steps->DeleteRows(0, grid_steps->GetNumberRows());
		}
		
		if (grid_template->GetNumberRows() > 0)
		{
			grid_template->DeleteRows(0, grid_template->GetNumberRows());
		}
	}

	rbtn_walk->SetValue(true);
	setup_paramters(parameter_choices.walk);

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

	stack.Clear();
}

bool cMain::CheckBeforeClose()
{
	if (no_changes)
	{
		return true; 
	}

	if (grid_steps->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0)
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

			BackgroundColorUpdate(grid, moveTo, ToStepType(grid->GetCellValue(moveTo, 0).ToStdString()));

			if (StepGridData[row].colour != wxNullColour)
			{
				wxColour colour = StepGridData[row].colour;
				grid->SetCellBackgroundColour(moveTo, 1, colour);
				grid->SetCellBackgroundColour(moveTo, 2, colour);
				grid->SetCellBackgroundColour(moveTo, 3, colour);
			}

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

			BackgroundColorUpdate(grid, moveTo, ToStepType(grid->GetCellValue(moveTo, 0).ToStdString()));
			
			if (StepGridData[row].colour != wxNullColour)
			{
				wxColour colour = StepGridData[row].colour;
				grid->SetCellBackgroundColour(moveTo, 1, colour);
				grid->SetCellBackgroundColour(moveTo, 2, colour);
				grid->SetCellBackgroundColour(moveTo, 3, colour);
			}

			auto it1 = StepGridData.begin();
			it1 += row;

			auto it2 = StepGridData.begin();
			it2 += moveTo;

			auto data = *it1;
			StepGridData.erase(it1);
			StepGridData.insert(it2, data);
		}
	}

	HandleFocusMode(steps_focus_checkbox->IsChecked());
	no_changes = false;
}

bool cMain::DeleteRow(wxGrid* grid, wxComboBox* cmb, map<string, vector<Step>>& map)
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

	no_changes = false;
	return true;
}

bool cMain::ChangeRow(wxGrid* grid, Step step)
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

	GridEntry gridEntry = PrepareStepForGrid(&step);

	PopulateGrid(grid, rowNum, &gridEntry);

	BackgroundColorUpdate(grid, rowNum, step.type);

	no_changes = false;
	return true;
}

void cMain::BackgroundColorUpdate(wxGrid* grid, int row, StepType step)
{
	grid->SetCellBackgroundColour(row, 0, SteptypeColourHandler::GetStepColourOrDefault(step));
}

void cMain::OnAddStepClicked(wxCommandEvent& event)
{
	vector<tuple<int, Step>> change;
	if (grid_steps->IsSelection())
	{
		if (!grid_steps->GetSelectedRows().begin())
		{
			return;
		}

		change = AddStep(*grid_steps->GetSelectedRows().begin(), ExtractStep());
		if (change.size() > 0)
		{
			stack.Push({
				.row = *grid_steps->GetSelectedRows().begin() - 1,
				.type = T_ADD,
				.rows = change,
			});
		}
	}
	else
	{
		int row = grid_steps->GetNumberRows();
		change = AddStep(row, ExtractStep());
		if (change.size() > 0)
		{
			stack.Push({
				.row = row,
				.type = T_ADD,
				.rows = change,
			});
		}
	}
	
	no_changes = false;
	event.Skip();
}

void cMain::OnAddStepRightClicked(wxMouseEvent& event)
{
	vector<tuple<int, Step>> change;
	if (grid_steps->IsSelection())
	{
		if (!grid_steps->GetSelectedRows().Last())
		{
			return;
		}

		change = AddStep(grid_steps->GetSelectedRows().Last() + 1, ExtractStep());
		if (change.size() > 0)
		{
			stack.Push({
				.row = grid_steps->GetSelectedRows().Last() + 1,
				.type = T_ADD,
				.rows = change,
			});
		}
	}
	else
	{
		int row = grid_steps->GetNumberRows();
		change = AddStep(row, ExtractStep());
		if (change.size() > 0)
		{
			stack.Push({
				.row = row,
				.type = T_ADD,
				.rows = change,
			});
		}
	}

	no_changes = false;
	event.Skip();
}

vector<tuple<int, Step>> cMain::AddStep(int row, Step step, bool auto_put)
{
	vector<tuple<int, Step>> returnValue;

	if (!ValidateStep(row, step))
	{
		return returnValue;
	};

	string to_check;
	switch (step.type)
	{
		case e_save:
			UpdateStepGrid(row, &step);
			returnValue.push_back({row, step});

			if (!steps_focus_checkbox->IsChecked() || modifier_skip_checkbox->IsChecked()) return returnValue;

			grid_steps->BeginBatch();
			{
				for (int i = 0; i < row; i++)
					grid_steps->HideRow(i);
			}
			grid_steps->EndBatch();
			return returnValue;

		case e_build:
			step.BuildingIndex = BuildingNameToType[step.Item];

			UpdateStepGrid(row , &step);
			returnValue.push_back({row, step});

			to_check = step.Item;

			step.type = e_put;
			step.amount = 1;
			if (auto_put)
			{
				if (check_furnace->IsChecked() && (to_check == struct_auto_put_furnace_list.stone || to_check == struct_auto_put_furnace_list.steel))
				{
					step.Item = struct_fuel_list.coal;
					step.inventory = Fuel;

					UpdateStepGrid(row + 1, &step);
					returnValue.push_back({row + 1, step});
					return returnValue;
				}

				if (check_burner->IsChecked() && (to_check == struct_auto_put_burner_list.burner_mining_drill || to_check == struct_auto_put_burner_list.burner_inserter || to_check == struct_auto_put_burner_list.boiler))
				{
					step.Item = struct_fuel_list.coal;
					step.inventory = Fuel;

					UpdateStepGrid(row + 1, &step);
					returnValue.push_back({row + 1, step});
					return returnValue;
				}

				if (check_lab->IsChecked() && to_check == struct_science_list.lab)
				{
					step.Item = "Automation science pack";
					step.inventory = Input;

					UpdateStepGrid(row + 1, &step);
					returnValue.push_back({row + 1, step});
					return returnValue;
				}
			}
			
			return returnValue;

		case e_recipe:
		{
			UpdateStepGrid(row, &step);
			returnValue.push_back({row, step});

			to_check = step.Item;
			
			int multiplier = step.amount;

			if (auto_put && 0 < multiplier && check_recipe->IsChecked())
			{
				vector<string> recipe = recipes.find(to_check)->second;

				for (int i = 0; i < recipe.size(); i += 2)
				{
					step.type = e_put;
					step.amount = stoi(recipe[i + 1]) * multiplier;
					step.Item = recipe[i];
					step.inventory = Input;

					UpdateStepGrid(row + 1, &step);
					returnValue.push_back({row + 1, step});
				}
			}
			
			return returnValue;
		}

		default:			
			type_panel->IncrementStateCounter(step.type);
			UpdateStepGrid(row, &step); 
			returnValue.push_back({row, step});
			return returnValue;
	}
}

void cMain::OnChangeStepClicked(wxCommandEvent& event)
{
	event.Skip();
	wxArrayInt rows = grid_steps->GetSelectedRows();
	if (!grid_steps->IsSelection() || rows.empty())
	{
		wxMessageBox("Please select a row to change", "Selection not valid");	
		return;
	}

	int row = *rows.begin();
	if (StepGridData[row].type == e_build)
	{
		if (wxMessageBox("The row selected is a build step - are you sure you want to make this change?\nEnsure that you delete associated steps.", "The build step you are changing could be associated with future step", wxICON_WARNING | wxYES_NO, this) != wxYES)
		{
			return;
		}
	}

	OnChangeStepInternal(rows, row);
}

void cMain::OnChangeStepRightClicked(wxMouseEvent& event)
{
	event.Skip();
	wxArrayInt rows = grid_steps->GetSelectedRows();
	if (!grid_steps->IsSelection() || rows.empty())
	{
		wxMessageBox("Please select a row to change", "Selection not valid");
		return;
	}

	OnChangeStepInternal(rows, *rows.begin());
}

void cMain::OnChangeStepInternal(wxArrayInt& rows, int row)
{
	auto step = ExtractStep();

	if (!ValidateStep(row, step))
	{
		return;
	};

	stack.Push({
		.row = row,
		.type = T_MODIFY,
		.rows = ChangeStep(row, step)
	});

	grid_steps->SelectRow(row);
	HandleFocusMode(steps_focus_checkbox->IsChecked());
	no_changes = false;
}

vector< tuple<int, Step>> cMain::ChangeStep(int row, Step step)
{
	vector< tuple<int, Step>> change{};
	
	if (step.type == e_build)
	{
		step.BuildingIndex = BuildingNameToType[step.Item];
	}
	else if (step.type != StepGridData[row].type)
	{
		type_panel->IncrementStateCounter(step.type);
	}

	GridEntry gridEntry = PrepareStepForGrid(&step);

	change.push_back({row, StepGridData[row]});
	change.push_back({row, step});

	StepGridData[row] = step;
	PopulateGrid(grid_steps, row, &gridEntry);

	BackgroundColorUpdate(grid_steps, row, step.type);
	HandleFocusMode(steps_focus_checkbox->IsChecked());
	return change;
}

void cMain::OnDeleteStepClicked(wxCommandEvent& event)
{
	event.Skip();
	wxArrayInt rows = grid_steps->GetSelectedRows();

	if (!grid_steps->IsSelection() || rows.IsEmpty())
	{
		wxMessageBox("Please select one or more rows to delete", "Selection not valid");
		return;
	}

	if (wxMessageBox(
		rows == 1 ? "Are you sure you want to delete this step?" : "Are you sure you want to delete these steps?",
		rows == 1 ? "Delete step" : "Delete steps", 
		wxICON_QUESTION | wxYES_NO, this) != wxYES)
	{
		return;
	}

	OnDeleteStepInternal(rows, false);
}

void cMain::OnDeleteStepRightClicked(wxMouseEvent& event)
{
	event.Skip();
	wxArrayInt rows = grid_steps->GetSelectedRows();

	if (!grid_steps->IsSelection() || rows.IsEmpty())
	{
		wxMessageBox("Please select one or more rows to delete", "Selection not valid");
		return;
	}

	OnDeleteStepInternal(rows, true);
}

void cMain::OnDeleteStepInternal(wxArrayInt& rows, bool auto_confirm)
{
	int startRow = rows.at(0);
	auto steps = DeleteSteps(rows, auto_confirm);
	stack.Push({
		.row = rows[0],
		.type = T_DELETE,
		.rows = steps
	});

	// The row after the deleted row(s) are selected
	if (startRow < grid_steps->GetNumberRows())
	{
		grid_steps->SelectRow(startRow);
	}
	else if (startRow - 1 >= 0)
	{
		grid_steps->SelectRow(startRow - 1);
	}

	no_changes = false;
}

vector< tuple<int, Step>> cMain::DeleteSteps(wxArrayInt steps, bool auto_confirmed)
{
	vector< tuple<int, Step>> return_list{};
	bool confirmed = auto_confirmed;

	for (const auto step : steps)
	{
		if (confirmed) break;
		if (StepGridData[step].type == e_build)
		{
			if (wxMessageBox("At least one of the rows selected is a build step - are you sure you want to delete the rows selected?\nEnsure that you delete associated steps.", 
				"The build step(s) you are deleting could be associated with future step", 
				wxICON_WARNING | wxYES_NO, this) != wxYES)
			{
				return return_list;
			}
			break;
		}
	}

	for (const auto step : steps)
	{
		type_panel->IncrementStateCounter(StepGridData[step].type); break;
	}

	return_list.reserve(steps.size());
	return_list.push_back({steps[0], StepGridData.at(steps[0])});
	
	pair<int, int> current_block = {steps[0], 1};
	vector<pair<int, int>> blocks{};
	blocks.reserve(steps.size());
	for (int i = 1; i < steps.size(); i++)
	{
		return_list.push_back({steps[i], StepGridData.at(steps[i])});
		int block_size = current_block.first + current_block.second;
		if (steps[i] == block_size)
		{
			current_block.second = current_block.second + 1;
		}
		else
		{
			blocks.push_back(current_block);
			current_block = {steps[i], 1};
		}
	}
	blocks.push_back(current_block);

	for (auto it = blocks.rbegin(); it != blocks.rend(); ++it)
	{
		auto& [start, count] = *it;
		grid_steps->DeleteRows(start, count);

		auto iStart = StepGridData.begin() + start;
		auto iEnd = StepGridData.begin() + start + count;

		StepGridData.erase(iStart, iEnd);
	}

	HandleFocusMode(steps_focus_checkbox->IsChecked());

	return return_list;
}

tuple<int, Step> cMain::GetRowTuple(int index)
{
	return {index, StepGridData.at(index)};
}

vector<tuple<int, Step>> cMain::GetSelectedRowTuples()
{
	vector<tuple<int, Step>> rows{};
	auto selected = grid_steps->GetSelectedRows();
	if (selected.IsEmpty()) return rows;
	else rows.reserve(selected.size());
	for (int i : selected)
		rows.push_back(GetRowTuple(i));
	return rows;
}

void cMain::OnMoveUpClicked(wxCommandEvent& event)
{
	if (!grid_steps->IsSelection() || !grid_steps->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
		return;
	}
	
	MoveRow(grid_steps, true);
	stack.Push({
		.row = *grid_steps->GetSelectedRows().begin(),
		.type = T_MOVE_UP,
		.rows = GetSelectedRowTuples(),
	});
	event.Skip();
}

void cMain::OnMoveDownClicked(wxCommandEvent& event)
{
	if (!grid_steps->IsSelection() || !grid_steps->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
		return;
	}

	MoveRow(grid_steps, false);	
	stack.Push({
		.row = *grid_steps->GetSelectedRows().begin(),
		.type = T_MOVE_DOWN,
		.rows = GetSelectedRowTuples(),
	});
	event.Skip();
}

void cMain::OnMoveUpFiveClicked(wxMouseEvent& event)
{
	if (!grid_steps->IsSelection() || !grid_steps->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	for (int i = 0; i < 5; i++)
	{
		MoveRow(grid_steps, true);
	}

	event.Skip();
}

void cMain::OnMoveDownFiveClicked(wxMouseEvent& event)
{
	if (!grid_steps->IsSelection() || !grid_steps->GetSelectedRows().begin())
	{
		wxMessageBox("Please select row(s) to move", "Select row(s)");
	}

	for (int i = 0; i < 5; i++)
	{
		MoveRow(grid_steps, false);
	}

	event.Skip();
}

void cMain::OnStepsGridDoubleLeftClick(wxGridEvent& event)
{
	auto gridEntry = ExtractGridEntry(grid_steps, event.GetRow());

	UpdateParameters(&gridEntry, event);

	event.Skip();
}

void cMain::OnStepsGridDoubleRightClick(wxGridEvent& event)
{
	auto gridEntry = ExtractGridEntry(grid_steps, event.GetRow());

	UpdateParameters(&gridEntry, event, false);

	event.Skip();
}

void cMain::OnStepsGridRangeSelect(wxGridRangeSelectEvent& event)
{
	event.Skip();
	wxArrayInt rows = grid_steps->GetSelectedRows();
	if (rows.empty()){ //prevents a crash due to somehow selecting zero rows??
		return;
	}

	wxColour colour = grid_steps->GetCellBackgroundColour(rows[0], 1); //retrieve the colour of the first selected element
	step_colour_picker->SetColour(colour);

	if (rows.size() == 1)
	{
		modifier_no_order_checkbox->Show();
		modifier_no_order_button->Hide();
		sizer_no_order->Layout();
		modifier_skip_checkbox->Show();
		modifier_skip_button->Hide();
		sizer_skip->Layout();
		modifier_force_checkbox->Show();
		modifier_force_button->Hide();
		sizer_force->Layout();
		btn_change_step->Enable();
	}
	else
	{
		modifier_no_order_checkbox->Hide();
		modifier_no_order_button->Show();
		sizer_no_order->Layout();
		modifier_skip_checkbox->Hide();
		modifier_skip_button->Show();
		sizer_skip->Layout();
		modifier_force_checkbox->Hide();
		modifier_force_button->Show();
		sizer_force->Layout();
		btn_change_step->Disable();
	}	
	HandleSplitOrMergeToggle(rows);
}

void cMain::OnStepColourPickerColourChanged(wxColourPickerEvent& event)
{
	if (!grid_steps->IsSelection())
	{
		wxMessageBox("No step is chosen - please select row(s) in the step list", "Cannot change colour of steps");
		return;
	}
	const wxColour colour = step_colour_picker->GetColour();
	wxGridBlockCoordsVector rowsBlocks = grid_steps->GetSelectedRowBlocks();
	for (wxGridBlockCoords block : rowsBlocks)
	{
		for (int row = block.GetTopRow(); row <= block.GetBottomRow(); row++)
		{
			StepGridData.at(row).colour = colour;
			grid_steps->SetCellBackgroundColour(row, 1, colour);
			grid_steps->SetCellBackgroundColour(row, 2, colour);
			grid_steps->SetCellBackgroundColour(row, 3, colour);
		}
	}
	event.Skip();
}

void cMain::HandleSplitOrMergeToggle(wxArrayInt& rows)
{
	size_t size = rows.size();
	if (size == 1)
	{
		Step data = StepGridData.at(rows[0]);
		step_split_multibuild_button->Enable(data.Buildings >= 2);
	}
	else
	{
		step_split_multibuild_button->Disable();
	}
}
void cMain::OnSplitMultibuildClicked(wxCommandEvent& event)
{
	wxArrayInt rows = grid_steps->GetSelectedRows();
	SplitMultibuildStep(rows[0]);
}
void cMain::OnSplitMultibuildRightClicked(wxMouseEvent& event)
{
	wxArrayInt rows = grid_steps->GetSelectedRows();
	SplitMultibuildStep(rows[0]);
}
void cMain::SplitMultibuildStep(int row)
{
	Step data = StepGridData[row];
	vector<Step> new_rows;
	const int buildings = data.Buildings - 1;
	data.Buildings = 1;
	StepGridData[row].Buildings = 1;
	new_rows.reserve(buildings);

	for (int i = 0; i < buildings; i++)
	{
		data.Next();
		data.OriginalX = data.X;
		data.OriginalY = data.Y;
		new_rows.push_back(data);
	}

	StepGridData.insert(StepGridData.begin() + row + 1, new_rows.begin(), new_rows.end());

	grid_steps->InsertRows(row + 1, buildings);
	for (int i = row; i < row + buildings + 1; i++)
	{
		GridEntry gridEntry = PrepareStepForGrid(&StepGridData[i]);

		PopulateGrid(grid_steps, i, &gridEntry);

		BackgroundColorUpdate(grid_steps, i, StepGridData[i].type);

		if (StepGridData[i].colour != wxNullColour)
		{
			wxColour colour = StepGridData[i].colour;
			grid_steps->SetCellBackgroundColour(i, 1, colour);
			grid_steps->SetCellBackgroundColour(i, 2, colour);
			grid_steps->SetCellBackgroundColour(i, 3, colour);
		}

		grid_steps->SelectRow(i, true);
	}
}

void cMain::UpdateMapWithNewSteps(wxGrid* grid, wxComboBox* cmb, map<string, vector<Step>>& map)
{
	if (!grid_steps->IsSelection())
	{
		wxMessageBox("No step is chosen - please select row(s) in the step list", "Cannot add step to template");
		return;
	}

	auto it = map.find(cmb->GetValue().ToStdString());
	if (it == map.end())
	{
		wxMessageBox("The template name doesn't exist - please add a new template before adding steps", "Cannot add step to template");
		return;
	}

	auto moveTo = grid->GetNumberRows();
	if (grid->IsSelection())
	{
		if (!grid->GetSelectedRows().begin())
		{
			wxMessageBox("Please either select row(s) or nothing", "template list selection not valid");
			return;
		}

		moveTo = *grid->GetSelectedRows().begin();
	}

	vector<Step> steps = it->second;
	for (const auto& block : grid_steps->GetSelectedRowBlocks())
	{
		auto startRow = block.GetTopRow();
		auto rowCount = block.GetBottomRow() - startRow + 1;

		grid->InsertRows(moveTo, rowCount);

		int rows = startRow + rowCount;

		for (int i = startRow; i < rows; i++)
		{
			GridTransfer(grid_steps, i, grid, moveTo);

			BackgroundColorUpdate(grid, moveTo, StepGridData[i].type);

			auto it1 = steps.begin();
			it1 += moveTo;

			steps.insert(it1, StepGridData[i]);

			moveTo += 1;
		}
	}

	it->second = steps;
	no_changes = false;
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
	to->SetCellValue(toRow, 10, from->GetCellValue(fromRow, 10));
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
	if (grid_steps->GetNumberRows() > 0 || grid_template->GetNumberRows() > 0)
	{
		return true;
	}

	if (template_map.size() > 0)
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

void cMain::Open(std::ifstream * file)
{
	if (!dialog_progress_bar)
	{
		dialog_progress_bar = new DialogProgressBar(this, wxID_ANY, "Processing request");
	}

	OpenTas open;
	open_file_return_data* result = open.Open(dialog_progress_bar, *file);

	if (!result->success)
	{
		malformed_saved_file_message();
		return;
	}

	steps_focus_checkbox->SetValue(false);
	StepGridData = result->steps;
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
	else if (result->goal == goal_any_percent_text || result->goal == goal_any_percent_text_old)
	{
		menu_goals->GetMenuItems()[2]->Check();
	}
	else if (result->goal == goal_debug_text)
	{
		menu_goals->GetMenuItems()[0]->Check();
	}
	else if (result->goal == scenario_supply_challenge_text)
	{
		menu_goals->GetMenuItems()[3]->Check();
		rbtn_next->Enable();
	}
	else
	{
		malformed_saved_file_message();
		return;
	}

	log_config logconfig = result->logconfig;
	auto& logmenu = menu_loglevel->GetMenuItems();
	logmenu[0]->Check(logconfig.savegame);
	logmenu[1]->Check(logconfig.tech);
	logmenu[2]->Check(logconfig.comment);
	logmenu[4 + (int)logconfig.level]->Check();

	generate_config generateConfig = result->generateConfig;
	legacy_mining->Check(generateConfig.legacy_mining);
	intermediate_walk_towards->Check(generateConfig.intermediate_walk_towards);
	no_intermediate_walk->Check(generateConfig.no_intermediate_walk);

	menu_auto_close->GetMenuItems()[0]->Check(result->auto_close.generate_script);
	auto_close_generate_script = result->auto_close.generate_script;

	menu_auto_close->GetMenuItems()[1]->Check(result->auto_close.open);
	auto_close_open = result->auto_close.open;

	menu_auto_close->GetMenuItems()[2]->Check(result->auto_close.save);
	auto_close_save = result->auto_close.save;

	menu_auto_close->GetMenuItems()[3]->Check(result->auto_close.save_as);
	auto_close_save_as = result->auto_close.save_as;

	check_furnace->SetValue(result->auto_put.furnace);
	check_burner->SetValue(result->auto_put.burner);
	check_lab->SetValue(result->auto_put.lab);
	check_recipe->SetValue(result->auto_put.recipe);

	PopulateStepGrid();

	dialog_progress_bar->set_progress(100.0f - 35);
	wxYield();

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
			cmb_choose_template->AutoComplete(template_choices);
			UpdateTemplateGrid(template_map[cmb_choose_template->GetValue().ToStdString()]);
		}
	}

	file->close();

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

	if (!result->selected_rows.empty())
	{
		int row_count = grid_steps->GetNumberRows();
		int first_row_index = result->selected_rows[0].GetTopRow();
		if (row_count > 0 && first_row_index < row_count)
		{
			wxGridEvent mock_event = wxGridEvent(0, wxEVT_GRID_CELL_LEFT_DCLICK, 0, first_row_index);
			OnStepsGridDoubleLeftClick(mock_event); // load first row into detail panel
			grid_steps->GoToCell(row_count-1, 0);
			grid_steps->GoToCell(first_row_index - (first_row_index > 4 ? 3 : 0), 0); // move the grid to first selected row

			for (auto block : result->selected_rows)
			{
				if (block.GetTopRow() < row_count && block.GetBottomRow() < row_count) // verify the selected rows are still in the grid
				{
					grid_steps->SelectBlock(block.GetTopLeft(), block.GetBottomRight(), true); // select each block
				}
			}
			
		}
	}

	import_steps_into_steps_ctrl->SetValue(result->import_into_row);

	{
		type_panel->warnings_states_counters = result->warnings_states_counters;
		rbtn_never_idle->SetForegroundColour(type_panel->warnings_states_counters.never_idle % 2 == 1 ? "Green" : "Black");
		rbtn_keep_on_path->SetForegroundColour(type_panel->warnings_states_counters.keep_on_path % 2 == 1 ? "Green" : "Black");
		rbtn_keep_walking->SetForegroundColour(type_panel->warnings_states_counters.keep_walking % 2 == 1 ? "Green" : "Black");
		rbtn_keep_crafting->SetForegroundColour(type_panel->warnings_states_counters.keep_crafting % 2 == 1 ? "Green" : "Black");
	}

	no_changes = true;
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
		Open(&file);
	}

	event.Skip();
}

void cMain::PopulateStepGrid()
{
	if (grid_steps->GetNumberRows() > 0)
	{
		grid_steps->DeleteRows(0, grid_steps->GetNumberRows());
	}

	size_t steps = StepGridData.size();
	grid_steps->BeginBatch();
	grid_steps->InsertRows(0, steps);

	for (int i = 0; i < steps; i++)
	{
		GridEntry gridEntry = PrepareStepForGrid(&StepGridData[i]);

		PopulateGrid(grid_steps, i, &gridEntry);

		BackgroundColorUpdate(grid_steps, i, StepGridData[i].type);

		if (StepGridData[i].colour != wxNullColour)
		{
			wxColour colour = StepGridData[i].colour;
			grid_steps->SetCellBackgroundColour(i, 1, colour);
			grid_steps->SetCellBackgroundColour(i, 2, colour);
			grid_steps->SetCellBackgroundColour(i, 3, colour);
		}
	}
	grid_steps->EndBatch();
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

std::string cMain::GetGoalConfig()
{
	auto& goals_items = menu_goals->GetMenuItems();
	return goals_items[0]->IsChecked() ? goal_steelaxe_text : goals_items[1]->IsChecked() ? goal_GOTLAP_text : goals_items[2]->IsChecked() ? goal_any_percent_text : scenario_supply_challenge_text;
}

log_config cMain::GetLogConfig()
{
	auto& logging_items = menu_loglevel->GetMenuItems();
	log_config logconfig{
		.savegame = logging_items[0]->IsChecked(),
		.tech = logging_items[1]->IsChecked(),
		.comment = logging_items[2]->IsChecked(),
		.level = logging_items[4]->IsChecked() ? log_config::leveltype::DEBUG : logging_items[5]->IsChecked() ? log_config::leveltype::DEV : log_config::leveltype::RELEASE,
	};
	return logconfig;
}

generate_config cMain::GetGenerateConfig()
{
	return generate_config{
		.legacy_mining = legacy_mining->IsChecked(),
		.intermediate_walk_towards = intermediate_walk_towards->IsChecked(),
		.no_intermediate_walk = no_intermediate_walk->IsChecked(),
	};
}

void cMain::OnGenerateScript(wxCommandEvent& event)
{
	string goal = GetGoalConfig();

	log_config logconfig = GetLogConfig();
	generate_config generateconfig = GetGenerateConfig();

	if (!ValidateAllSteps())
	{
		return;
	};

	GenerateScript generate_script(grid_steps);
	generate_script.generate(this, dialog_progress_bar, StepGridData, generate_code_folder_location, auto_close_generate_script, goal, logconfig, generateconfig);

	grid_steps->Update();

	AutoSave();

	event.Skip();
}

void cMain::OnMenuSteelAxeClicked(wxCommandEvent& event)
{
	rbtn_next->Disable();
}
void cMain::OnMenuGOTLAPClicked(wxCommandEvent& event)
{
	rbtn_next->Disable();
}
void cMain::OnMenuAnyPercentClicked(wxCommandEvent& event)
{
	rbtn_next->Disable();
}
void cMain::OnMenuSupplyChallengeClicked(wxCommandEvent& event)
{
	rbtn_next->Enable();
}

void cMain::OnChangeShortcutMenuSelected(wxCommandEvent& event)
{
	ShortcutChanger * sc = new ShortcutChanger(this, 
		wxID_ANY,
		wxT("Change shortcuts"), 
		wxDefaultPosition,
		wxDefaultSize, 
		wxCAPTION | wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP | wxBORDER_DEFAULT);

	sc->Build(main_menubar);	

	sc->Show();

	event.Skip();
}

void cMain::OnChangeSteptypeColoursMenuSelected(wxCommandEvent& event)
{
	SteptypeColourHandler* sc = new SteptypeColourHandler(this,
		grid_steps, 
		grid_template,
		wxID_ANY,
		wxT("Change colours"),
		wxDefaultPosition,
		wxDefaultSize,
		wxCAPTION | wxCLOSE_BOX | wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP | wxBORDER_DEFAULT);

	sc->Build();

	sc->Show();

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
	if (btn_change_step->IsEnabled())
		OnChangeStepClicked(event);
	else
		wxMessageBox("Please select 1 row to change", "Selection not valid");
	event.Skip();
}

void cMain::OnChangeAltMenuSelected(wxCommandEvent& event)
{
	if (btn_change_step->IsEnabled())
	{
		auto new_event = wxMouseEvent();
		OnChangeStepRightClicked(new_event);
	}
	else
		wxMessageBox("Please select 1 row to change", "Selection not valid");
	event.Skip();
}

void cMain::OnDeleteMenuSelected(wxCommandEvent& event)
{
	OnDeleteStepClicked(event);
	event.Skip();
}

void cMain::OnDeleteAltMenuSelected(wxCommandEvent& event)
{
	auto new_event = wxMouseEvent();
	OnDeleteStepRightClicked(new_event);
	event.Skip();
}

void cMain::OnMoveUpMenuSelected(wxCommandEvent& event)
{
	OnMoveUpClicked(event);
	event.Skip();
}

void cMain::OnMoveUpAltMenuSelected(wxCommandEvent& event)
{
	auto new_event = wxMouseEvent();
	OnMoveUpFiveClicked(new_event);
	event.Skip();
}

void cMain::OnMoveDownMenuSelected(wxCommandEvent& event)
{
	OnMoveDownClicked(event);
	event.Skip();
}

void cMain::OnMoveDownAltMenuSelected(wxCommandEvent& event)
{
	auto new_event = wxMouseEvent();
	OnMoveDownFiveClicked(new_event);
	event.Skip();
}

void cMain::OnSearchMenuSelected(wxCommandEvent& event)
{
	step_search_ctrl->SetFocus();
	event.Skip();
}

void cMain::OnAddMenuSelected(wxCommandEvent& event)
{
	OnAddStepClicked(event);
	event.Skip();
}

void cMain::OnAddAltMenuSelected(wxCommandEvent& event)
{
	auto new_event = wxMouseEvent();
	OnAddStepRightClicked(new_event);
	event.Skip();
}

void cMain::UpdateParametersChangeType(wxCommandEvent& event, StepType step)
{
	switch (step)
	{
		case e_build:
			OnBuildMenuSelected(event);
			break;
		case e_craft:
			OnCraftMenuSelected(event);
			break;
		case e_game_speed:
			OnGameSpeedMenuSelected(event);
			break;
		case e_pause:
			OnPauseMenuSelected(event);
			break;
		case e_save:
			OnSaveMenuSelected(event);
			break;
		case e_never_idle:
			OnNeverIdleMenuSelected(event);
			break;
		case e_keep_walking:
			OnKeepWalkingMenuSelected(event);
			break;
		case e_keep_crafting:
			OnKeepCraftingMenuSelected(event);
			break;
		case e_keep_on_path:
			OnKeepOnPathMenuSelected(event);
			break;
		case e_recipe:
			OnRecipeMenuChosen(event);
			break;
		case e_limit:
			OnLimitMenuSelected(event);
			break;
		case e_filter:
			OnFilterMenuSelected(event);
			break;
		case e_rotate:
			OnRotateMenuSelected(event);
			break;
		case e_priority:
			OnPriorityMenuSelected(event);
			break;
		case e_put:
			OnPutMenuSelected(event);
			break;
		case e_take:
			OnTakeMenuSelected(event);
			break;
		case e_mine:
			OnMineMenuSelected(event);
			break;
		case e_launch:
			OnLaunchMenuSelected(event);
			break;
		case e_next:
			type_panel->SwitchStep(e_next);
			OnNextChosen(event);
			break;
		case e_walk:
			OnWalkMenuSelected(event);
			break;
		case e_tech:
			OnTechMenuSelected(event);
			break;
		case e_drop:
			OnDropMenuSelected(event);
			break;
		case e_pick_up:
			OnPickUpMenuSelected(event);
			break;
		case e_idle:
			OnIdleMenuSelected(event);
			break;
		case e_shoot:
			OnShootMenuSelected(event);
			break;
		case e_throw:
			OnThrowMenuSelected(event);
			break;
		case e_cancel_crafting:
			OnCancelCraftingMenuSelected(event);
			break;
		default:
			break;
	}
}

void cMain::UpdateParameters(GridEntry* gridEntry, wxCommandEvent& event, bool changeType)
{
	auto& modifiers = gridEntry->Modifiers;
	modifier_cancel_checkbox->SetValue(modifiers.find("cancel") != std::string::npos);
	modifier_no_order_checkbox->SetValue(modifiers.find("no order") != std::string::npos);
	modifier_wait_for_checkbox->SetValue(modifiers.find("wait for") != std::string::npos);
	modifier_walk_towards_checkbox->SetValue(modifiers.find("walk towards") != std::string::npos);
	modifier_skip_checkbox->SetValue(modifiers.find("skip") != std::string::npos);
	modifier_force_checkbox->SetValue(modifiers.find("force") != std::string::npos);
	modifier_split_checkbox->SetValue(modifiers.find("split") != std::string::npos);
	modifier_all_checkbox->SetValue(modifiers.find("all") != std::string::npos);

	StepType type = ToStepType(gridEntry->Step.ToStdString());
	int parameters = listStepTypeToParameterChoices[type];

	string orientation_string = gridEntry->BuildingOrientation.ToStdString();
	size_t pos = orientation_string.find(",");

	if (changeType) 
		UpdateParametersChangeType(event, type);

	using enum choice_bit_vector;
	if (parameters & x_coordinate) spin_x->SetValue(gridEntry->X);
	if (parameters & y_coordinate) spin_y->SetValue(gridEntry->Y);
	if (parameters & amount) 
		spin_amount->SetValue(
			type == e_game_speed ? to_string(stoi(gridEntry->Amount.ToStdString())) :
			gridEntry->Amount == "All" ? "0" : gridEntry->Amount.ToStdString()
		);
	if (parameters & item) cmb_item->SetValue(gridEntry->Item);
	if (parameters & from_to) cmb_from_into->SetValue(gridEntry->BuildingOrientation);
	if (parameters & input) radio_input->Select(Priority::MapNameToType[orientation_string.substr(0, pos)]);
	if (parameters & output) radio_output->Select(Priority::MapNameToType[orientation_string.substr(pos + 1)]);
	if (parameters & building_orientation) cmb_building_orientation->SetValue(gridEntry->BuildingOrientation);
	if (parameters & direction_to_build) cmb_direction_to_build->SetValue(gridEntry->DirectionToBuild);
	if (parameters & building_size) spin_building_size->SetValue(gridEntry->BuildingSize);
	if (parameters & amount_of_buildings) spin_building_amount->SetValue(gridEntry->AmountOfBuildings);
	if (parameters & comment) txt_comment->SetValue(gridEntry->Comment);
}

void cMain::malformed_saved_file_message()
{
	ResetToNewWindow();
	wxMessageBox("It seems like the structure of the file does not correspond with an Factorio TAS Generator file", "A file error occurred");
	dialog_progress_bar->set_button_enable(true);
}

bool cMain::Save(string filename, bool save_as, bool set_last_location)
{
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

	SaveTas save;
	return save.Save(
		this,
		dialog_progress_bar,
		save_as,
		auto_list,
		StepGridData,
		template_map,
		filename,
		generate_code_folder_location,
		GetGoalConfig(),
		GetLogConfig(),
		GetGenerateConfig(),
		grid_steps->GetSelectedRowBlocks(),
		import_steps_into_steps_ctrl->GetValue(),
		set_last_location);
}

bool cMain::AutoSave()
{
	using std::to_string;
	if (save_file_location == "" || !save_file_location.ends_with(".txt"))
		return false; //don't autosave if location is not set or it doesn't point to txt file
	static int autosave_count = 0;
	if (++autosave_count > 10) 
		autosave_count = 1; //make files from 1 to 10
	string filename = save_file_location.substr(0, save_file_location.size() - 4) + "_temp_" + to_string(autosave_count) + ".txt";

	return Save(filename, false, false);
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

	bool save = Save(save_file_location, save_as);

	std::string file_name = save_file_location.substr(save_file_location.rfind("\\") + 1);

	SetLabel(window_title + " - " + file_name);

	if (save)
	{
		no_changes = true;
	}

	return save;
}

Step cMain::ExtractStep()
{
	if (spin_y->IsEnabled()) spin_y->SetFocus();
	if (spin_x->IsEnabled()) spin_x->SetFocus();

	auto step = Step(spin_x->GetValue(), spin_y->GetValue());

	step.type = ToStepType(ExtractSteptypeName());
	step.amount = ExtractAmount();
	step.Item = Capitalize(cmb_item->GetValue(), true);
	step.inventory = GetInventoryType(Capitalize(cmb_from_into->GetValue()));
	step.orientation = MapStringToOrientation(cmb_building_orientation->GetValue());
	step.Direction = MapStringToOrientation(cmb_direction_to_build->GetValue());
	step.Size = spin_building_size->GetValue();
	step.Buildings = spin_building_amount->GetValue();
	step.priority.input = (Priority::Type) radio_input->GetSelection();
	step.priority.output = (Priority::Type) radio_output->GetSelection();
	step.Comment = txt_comment->GetValue().ToStdString();

	step.Modifiers = {
		.no_order = modifier_no_order_checkbox->IsEnabled() && modifier_no_order_checkbox->GetValue(),
		.skip = modifier_skip_checkbox->IsEnabled() && modifier_skip_checkbox->GetValue(),
		.wait_for = modifier_wait_for_checkbox->IsEnabled() && modifier_wait_for_checkbox->GetValue(),
		.force = modifier_force_checkbox->IsEnabled() && modifier_force_checkbox->GetValue(),
		.cancel_others = modifier_cancel_checkbox->IsEnabled() && modifier_cancel_checkbox->GetValue(),
		.split = modifier_split_checkbox->IsEnabled() && modifier_split_checkbox->GetValue(),
		.walk_towards = modifier_walk_towards_checkbox->IsEnabled() && modifier_walk_towards_checkbox->GetValue(),
		.all = modifier_all_checkbox->IsEnabled() && modifier_all_checkbox->GetValue(),
	};

	step.colour = step_colour_picker->GetColour();

	return step;
}

int cMain::ExtractAmount()
{
	int amount = spin_amount->GetValue();

	if (rbtn_filter->GetValue())
	{
		return amount < 1 ? 1 : amount > 5 ? 5 : amount;
	}
	if (amount < 1 && (rbtn_rotate->GetValue() || rbtn_idle->GetValue() || rbtn_pick_up->GetValue() || rbtn_game_speed->GetValue()))
	{
		return 1;
	}
	return amount < 1 ? 0 : amount;
}

GridEntry cMain::PrepareStepForGrid(Step* step)
{
	GridEntry gridEntry{
		.Step = StepNames[step->type],
		.Modifiers = step->Modifiers.ToString(),
		.Comment = step->Comment,
	};

	switch (step->type)
	{
		case e_stop:
			gridEntry.Comment = "";
			[[fallthrough]];
		case e_next:
		case e_pause:
		case e_save:
		case e_never_idle:
		case e_keep_crafting:
		case e_keep_on_path:
		case e_keep_walking:
			break;

		case e_game_speed:
			gridEntry.Amount = step->AmountGrid();
			break;

		case e_idle:
		case e_pick_up:
			gridEntry.Amount = step->AmountGrid();
			break;

		case e_craft:
		case e_cancel_crafting:
			gridEntry.Amount = step->AmountGrid();
			gridEntry.Recipe = step->Item;
			break;

		case e_throw:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Item = step->Item;
			break;

		case e_shoot:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Amount = step->AmountGrid();
			break;

		case e_walk:
		case e_launch:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			break;

		case e_mine:
			if (step->BuildingIndex != 0)
			{
				gridEntry.Item = FindBuildingName(step->BuildingIndex);
				step->Item = gridEntry.Item;
			}

			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Amount = step->AmountGrid();
			break;

		case e_rotate:

			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Amount = step->AmountGrid();
			gridEntry.Item = FindBuildingName(step->BuildingIndex);
			gridEntry.DirectionToBuild = orientation_list[step->Direction];
			gridEntry.BuildingSize = std::to_string(step->Size);
			gridEntry.AmountOfBuildings = std::to_string(step->Buildings);
			step->Item = gridEntry.Item;
			break;

		case e_build:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Item = step->Item;
			gridEntry.BuildingOrientation = orientation_list[step->orientation];
			gridEntry.DirectionToBuild = orientation_list[step->Direction];
			gridEntry.BuildingSize = std::to_string(step->Size);
			gridEntry.AmountOfBuildings = std::to_string(step->Buildings);
			break;

		case e_take:
		case e_put:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Amount = step->AmountGrid();
			gridEntry.Item = step->Item;
			gridEntry.Inventory = inventory_types_list[step->inventory];
			gridEntry.DirectionToBuild = orientation_list[step->Direction];
			gridEntry.BuildingSize = std::to_string(step->Size);
			gridEntry.AmountOfBuildings = std::to_string(step->Buildings);
			break;

		case e_tech:
			gridEntry.Item = step->Item;
			break;

		case e_recipe:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Amount = step->AmountGrid();
			gridEntry.Recipe = step->Item;
			gridEntry.DirectionToBuild = orientation_list[step->Direction];
			gridEntry.BuildingSize = std::to_string(step->Size);
			gridEntry.AmountOfBuildings = std::to_string(step->Buildings);
			break;

		case e_limit:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Amount = step->AmountGrid();
			gridEntry.BuildingOrientation = "Chest";
			gridEntry.DirectionToBuild = orientation_list[step->Direction];
			gridEntry.BuildingSize = std::to_string(step->Size);
			gridEntry.AmountOfBuildings = std::to_string(step->Buildings);
			break;

		case e_priority:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Priority = step->priority.ToString();
			gridEntry.DirectionToBuild = orientation_list[step->Direction];
			gridEntry.BuildingSize = std::to_string(step->Size);
			gridEntry.AmountOfBuildings = std::to_string(step->Buildings);
			break;

		case e_drop:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Item = step->Item;
			break;

		case e_filter:
			gridEntry.X = std::to_string(step->X);
			gridEntry.Y = std::to_string(step->Y);
			gridEntry.Amount = step->AmountGrid();
			gridEntry.Item = step->Item;
			gridEntry.DirectionToBuild = orientation_list[step->Direction];
			gridEntry.BuildingSize = std::to_string(step->Size);
			gridEntry.AmountOfBuildings = std::to_string(step->Buildings);
			break;
	}

	return gridEntry;
}

void cMain::UpdateStepGrid(int row, Step* step)
{
	GridEntry gridEntry = PrepareStepForGrid(step);

	grid_steps->InsertRows(row, 1);

	PopulateGrid(grid_steps, row, &gridEntry);

	auto it1 = StepGridData.begin();
	it1 += row;
	StepGridData.insert(it1, *step);

	BackgroundColorUpdate(grid_steps, row, step->type);
}

int cMain::GenerateBuildingSnapShot(int end_row)
{
	int buildingsInSnapShot = 0;

	for (int i = 0; i < end_row; i++)
	{
		switch (StepGridData[i].type)
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
		.Step = grid->GetCellValue(row, 0),
		.X = grid->GetCellValue(row, 1),
		.Y = grid->GetCellValue(row, 2),
		.Amount = grid->GetCellValue(row, 3),
		.Item = grid->GetCellValue(row, 4),
		.BuildingOrientation = grid->GetCellValue(row, 5),
		.Modifiers = grid->GetCellValue(row, 6),
		.DirectionToBuild = grid->GetCellValue(row, 7),
		.BuildingSize = grid->GetCellValue(row, 8),
		.AmountOfBuildings = grid->GetCellValue(row, 9),
		.Comment = grid->GetCellValue(row, 10)
	};

	return gridEntry;
}

bool cMain::ValidateStep(const int& row, Step& step, bool validateBuildSteps)
{
	// Cases where an association with a building isn't needed
	switch (step.type)
	{
		case e_walk:
		case e_game_speed:
		case e_pause:
		case e_save:
		case e_stop:
		case e_pick_up:
		case e_idle:
		case e_drop:
		case e_cancel_crafting:
		case e_never_idle:
		case e_keep_crafting:
		case e_keep_on_path:
		case e_keep_walking:
		case e_shoot:
		case e_throw:
		case e_next:
			return true;

		case e_build:
			return IsValidBuildStep(step);

		case e_craft:
			return IsValidCraftStep(step);

		case e_tech:
			return IsValidTechnologyStep(step);

		default:
			break;
	}

	if (!validateBuildSteps)
	{
		return true;
	}

	int amountOfBuildings = GenerateBuildingSnapShot(row);
	switch (step.type)
	{
		case e_recipe:
			if (!BuildingExists(BuildingsSnapShot, amountOfBuildings, step))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this step before the Build step", "Please use the same coordinates");
				return false;
			};

			return IsValidRecipeStep(step);

		case e_mine:
			// A building doesn't need to exist, but if it does it should be noted.
			BuildingExists(BuildingsSnapShot, amountOfBuildings, step);
			return true;

		case e_put:
		case e_take:
			if (step.inventory != Wreck && !BuildingExists(BuildingsSnapShot, amountOfBuildings, step))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this step before the Build step", "Please use the same coordinates");
				return false;
			};

			if (!IsValidPutTakeStep(step))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this step before the Build step", "Please use the same coordinates");
				return false;
			}

			return true;

		default:

			if (!BuildingExists(BuildingsSnapShot, amountOfBuildings, step))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this step before the Build step", "Please use the same coordinates");
				return false;
			};

			return ExtraBuildingChecks(step);
	}
}

bool cMain::IsValidBuildStep(Step& step)
{
	if (!check_input(step.Item, all_buildings))
	{
		wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
		return false;
	}

	return true;
}

bool cMain::IsValidRecipeStep(Step& step)
{
	switch (step.BuildingIndex)
	{
		case AssemblingMachine1:
			if (check_input(step.Item, part_assembly_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an assembling machine 1", "Item chosen is not valid");
			return false;

		case AssemblingMachine2:
		case AssemblingMachine3:
			if (check_input(step.Item, full_assembly_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an assembling machine", "Item chosen is not valid");
			return false;

		case OilRefinery:
			if (check_input(step.Item, oil_refinery_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an oil refinery", "Item chosen is not valid");
			return false;

		case ChemicalPlant:
			if (check_input(step.Item, full_chemical_plant_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a chemical plant", "Item chosen is not valid");
			return false;

		case Centrifuge:
			if (check_input(step.Item, centrifuge_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a centrifuge", "Item chosen is not valid");
			return false;

		case StoneFurnace:
		case SteelFurnace:
		case ElectricFurnace:
			if (check_input(step.Item, furnace_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a furnace", "Item chosen is not valid");
			return false;

		default:
			return true;;
	}
}

bool cMain::IsValidCraftStep(Step& step)
{
	if (!check_input(step.Item, handcrafted_list))
	{
		wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
		return false;
	}

	return true;
}

bool cMain::IsValidPutTakeStep(Step& step)
{
	if (!CheckTakePut(step))
	{
		return false;
	}

	return true;
}

bool cMain::IsValidTechnologyStep(Step& step)
{
	if (!check_input(step.Item, tech_list))
	{
		wxMessageBox("The tech is not valid - please try again", "Please use the tech dropdown menu");
		return false;
	}

	return true;
}

bool cMain::CheckTakePut(Step& step)
{
	InventoryType to_check = step.inventory;

	if (to_check == Wreck)
	{
		return true;
	}

	string building = FindBuildingName(step.BuildingIndex);
	if (check_input(building, chest_list))
	{
		step.inventory = Chest;
		return true;
	}

	if (to_check == Fuel)
	{
		if (check_input(step.Item, fuel_list))
		{
			return true;
		}

		wxMessageBox("The item chosen is not a valid fuel", "Please select a valid fuel");
		return false;
	}

	if (building == "Lab")
	{
		if (to_check == Input)
		{
			if (check_input(step.Item, science_packs))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a science pack.\nOnly science packs can be used as input for a lab", "Please choose a science pack");
			return false;

		}
		else if (to_check == Modules)
		{
			if (check_input(step.Item, module_list))
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
		if (to_check == Modules)
		{
			if (check_input(step.Item, module_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a module", "Please choose a module");
			return false;
		}

		wxMessageBox("Only Modules is a valid \"From/Into\" choice for a drill/Pump", "Please choose modules");
		return false;
	}

	if (to_check == Input)
	{
		// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
		return true;
	}

	if (to_check == Modules)
	{
		if (check_input(step.Item, module_list))
		{
			return true;
		}

		wxMessageBox("The item chosen is not a module", "Please choose a module");
		return false;
	}

	if (to_check == Output)
	{
		// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
		return true;
	}

	wxMessageBox("Building location does not seem to exist.\nPlease use exactly the same coordinates as you used to build", "Please use the same coordinates");
	return false;
}

bool cMain::ExtraBuildingChecks(Step& step)
{
	auto buildingName = FindBuildingName(step.BuildingIndex);

	switch (step.type)
	{
		case e_limit:
			if (check_input(buildingName, chest_list))
			{
				return true;
			}

			wxMessageBox(buildingName + " isn't a chest type and limit can therefore not be used.");
			return false;

		case e_priority:
			if (check_input(buildingName, splitter_list))
			{
				return true;
			}

			wxMessageBox(buildingName + " isn't a splitter type and priority can therefore not used.");
			return false;

		case e_filter:
			if (check_input(buildingName, splitter_list) || check_input(buildingName, filter_inserter_list))
			{
				return true;
			}

			wxMessageBox(buildingName + " isn't a splitter or filter inserter type and filter can therefore not be used.");
			return false;

		default:
			return true;
	}
}

bool cMain::ValidateAllSteps()
{
	int buildingsInSnapShot = 0;

	for (int i = 0; i < StepGridData.size(); i++)
	{
		Step& step = StepGridData[i];

		switch (step.type)
		{
			case e_build:
				step.BuildingIndex = BuildingNameToType.find(step.Item)->second;
				buildingsInSnapShot = ProcessBuildStep(BuildingsSnapShot, buildingsInSnapShot, step);
				break;

			case e_mine:
				ProcessMiningStep(BuildingsSnapShot, buildingsInSnapShot, step);
				break;

			case e_recipe:
			case e_filter:
			case e_rotate:
			case e_priority:
			case e_launch:
				if (!BuildingExists(BuildingsSnapShot, buildingsInSnapShot, step))
				{
					string message = "Step " + to_string(i + 1) + " is not connected to a building. Ensure that the step is not placed before the build step.";
					wxMessageBox(message, "Step not connected to building");
					return false;
				}
				break;

			case e_limit:
			case e_put:
			case e_take:
				if (step.inventory != Wreck && !BuildingExists(BuildingsSnapShot, buildingsInSnapShot, step))
				{
					string message = "Step " + to_string(i + 1) + " is not connected to a building. Ensure that the step is not placed before the build step.";
					wxMessageBox(message, "Step not connected to building");
					return false;
				}

				break;
			default:
				break;
		}
	}

	return true;
}

void cMain::OnMainBookPageChanged(wxAuiNotebookEvent& event)
{
	auto page = event.GetSelection();
	if (page == 2)
	{
		import_steps_text_import->SetFocus();
	}
	event.Skip();
}

void cMain::OnNoOrderRightClicked(wxMouseEvent& event)
{
	NoOrderButtonHandle(true);
}
void cMain::OnNoOrderClicked(wxCommandEvent& event)
{
	NoOrderButtonHandle();
}
void cMain::NoOrderButtonHandle(bool force)
{
	wxArrayInt rows = grid_steps->GetSelectedRows();
	if (rows.size() < 2) return;
	if (!force)
	{
		for (int row : rows)
		{
			StepType e = StepGridData.at(row).type;
			if (! modifier_types.no_order.contains(e)) 
			{
				wxMessageBox(std::format("Step {} is unable to be assigned the no-order modifier. \n As it is of the type {}.", row + 1, StepNames[e]),
					"One or more steps can't be assigned no-order modifier");
				return;
			}
		}
	}
	bool modifier_value = StepGridData.at(rows.front()).Modifiers.no_order;
	for (int row : rows)
	{
		auto& step = StepGridData.at(row);
		if (step.Modifiers.no_order == modifier_value && 
			modifier_types.no_order.contains(step.type))
		{
			step.Modifiers.no_order = !modifier_value;
			grid_steps->SetCellValue(row, 6, step.Modifiers.ToString());
		}
	}
}

void cMain::OnForceRightClicked(wxMouseEvent& event)
{
	ForceButtonHandle(true);
}
void cMain::OnForceClicked(wxCommandEvent& event)
{
	ForceButtonHandle();
}
void cMain::ForceButtonHandle(bool force)
{
	wxArrayInt rows = grid_steps->GetSelectedRows();
	if (rows.size() < 2) return;
	if (!force)
	{
		for (int row : rows)
		{
			StepType e = StepGridData.at(row).type;
			if (! modifier_types.force.contains(e))
			{
				wxMessageBox(std::format("Step {} is unable to be assigned the force modifier. \n As it is of the type {}.", row + 1, StepNames[e]),
					"One or more steps can't be assigned force modifier");
				return;
			}
		}
	}
	bool modifier_value = StepGridData.at(rows.front()).Modifiers.force;
	for (int row : rows)
	{
		auto& step = StepGridData.at(row);
		if (step.Modifiers.force == modifier_value &&
			modifier_types.force.contains(step.type))
		{
			step.Modifiers.force = !modifier_value;
			grid_steps->SetCellValue(row, 6, step.Modifiers.ToString());
		}
	}
}

void cMain::OnSkipClicked(wxCommandEvent& event)
{
	wxArrayInt rows = grid_steps->GetSelectedRows();
	if (rows.size() < 2) return;

	bool modifier_value = StepGridData.at(rows.front()).Modifiers.skip;
	for (int row : rows)
	{
		auto& step = StepGridData.at(row);
		if (step.Modifiers.skip == modifier_value)
		{
			step.Modifiers.skip = !modifier_value;
			grid_steps->SetCellValue(row, 6, step.Modifiers.ToString());
		}
	}
}

void cMain::SelectRowsInGrid(vector<tuple<int, Step>> rows)
{
	grid_steps->ClearSelection();
	for (auto& [index, data] : rows)
	{
		grid_steps->SelectRow(index, true);
	}
}

void cMain::OnUndoMenuSelected(wxCommandEvent& event)
{
	auto current_selected = grid_steps->GetSelectedRows();
	
	Command command = stack.Pop();

	switch (command.type)
	{
		case T_NULL:
			break;
		case T_ADD:
		{
			wxArrayInt rows{};
			for (auto& [row, _] : command.rows)
			{
				rows.Add(row);
			}
			DeleteSteps(rows, true);
		}
			break;
		case T_DELETE:
			for (auto& [row, step] : command.rows)
			{
				AddStep(row, step, false);
			}
			break;
		case T_MODIFY:
			{
				auto& [row, param] = command.rows[0];
				ChangeStep(command.row, param);
			}
			break;
		case T_MOVE_UP:
		{
			SelectRowsInGrid(command.rows);
			MoveRow(grid_steps, false);
		}
			break;
		case T_MOVE_DOWN:
		{
			SelectRowsInGrid(command.rows);
			MoveRow(grid_steps, true);
		}
			break;

		default:
			break;
	}
}

void cMain::OnRedoMenuSelected(wxCommandEvent& event)
{
	Command command = stack.PopBack();

	switch (command.type)
	{
		case T_NULL:
			break;
		case T_ADD:
			{
				for (auto& [row, step] : command.rows)
				{
					AddStep(row, step, false);
				}
			}
			break;
		case T_DELETE:
			{
				wxArrayInt rows{};
				for (auto& [row, _] : command.rows)
				{
					rows.Add(row);
				}
				DeleteSteps(rows, true);
			}
			break;
		case T_MODIFY:
			{
				auto& [row, param] = command.rows[1];
				ChangeStep(command.row, param);
			}
			break;
		case T_MOVE_UP:
			{
				SelectRowsInGrid(command.rows);
				MoveRow(grid_steps, true);
			}
			break;
		case T_MOVE_DOWN:
			{
				SelectRowsInGrid(command.rows);
				MoveRow(grid_steps, false);
			}
			break;

		default:
			break;
	}
}

