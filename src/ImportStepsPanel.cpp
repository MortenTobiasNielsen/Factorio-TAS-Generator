#pragma once
#include "cMain.h"

#include "Shared functions\Functions.h"

#include "Data\BuildingNames.h"
#include "Data\utils.h"

using std::string;
using std::stod;
using std::stoi;

/* ImportStepsPanel variables:
	ImportStepsPanel* import_steps_panel;
	wxTextCtrl* import_steps_text_import;
	wxSpinCtrl* import_steps_into_steps_ctrl;
	wxButton* import_steps_into_steps_btn;
	wxTextCtrl* import_steps_into_template_ctrl;
	wxButton* import_steps_into_template_btn;
	wxCheckBox* import_steps_clear_checkbox;

	wxString import_steps_into_template_ctrl_validator;
*/

bool ImportStepsPanel::update_segment()
{
	std::string line;
	std::string segment;
	std::stringstream data_line;

	if (std::getline(data, line, data.widen('\n')))
	{
		data_line.str(line);

		segments = {};

		while (std::getline(data_line, segment, ';'))
		{
			segments.push_back(segment);
		}

		return true;
	}

	return false;
}

bool ImportStepsPanel::extract_steps(wxString steps, vector<StepParameters>& step_parameters)
{
	buildingSnapshot.clear();
	buildingSnapshot.reserve(1000);
	for (int i = 0; i < buildingSnapshot.capacity(); i++)
	{
		buildingSnapshot.emplace_back(invalidX);
	}

	int counter = 0;
	data = {};
	data.str(steps.ToStdString());
	while (update_segment())
	{
		counter++;
		if (segments.size() != step_segment_size &&
			segments.size() != step_segment_size_without_colour &&
			segments.size() != step_segment_size_without_comment_and_colour)
		{
			wxMessageBox("It was not possible to read line ["+ std::to_string(counter) + "] as it only contained [" + std::to_string(segments.size()) + "] semicolons", "Text import error");
			return false;
		}

		StepParameters step(invalidX, 0);

		int size = segments.size();
		if (size < 1) continue;
		
		step.type = ToStepType(Capitalize(segments[0]));
		step.OriginalX = step.X = size >= 1 && segments[1] != "" ? stod(segments[1]) : 0;
		step.OriginalY = step.Y = size >= 2 && segments[2] != "" ? stod(segments[2]) : 0;
		step.Amount = size >= 3 && segments[3] != "" ? segments[3] == "All" ? 0 : stoi(segments[3]) : 0;
		step.Item = size >= 4 && segments[4] != "" ? Capitalize(segments[4], true) : "";
		step.Orientation = size >= 5 && segments[5] != "" ? Capitalize(segments[5]) : "";
		step.Direction = size >= 6 && segments[6] != "" ? Capitalize(segments[6]) : "";
		step.Size = size >= 7 && segments[7] != "" ? stoi(segments[7]) : 1;
		step.Buildings = size >= 8 && segments[8] != "" ? stoi(segments[8]) : 1;
		step.Comment = size >= 9 ? segments[9] : "";
		step.colour = size >= 10 ? wxColour(segments[10]) : wxNullColour;

		switch (step.type )
		{
			[[likely]] case e_build:
				step.BuildingIndex = BuildingNameToType[step.Item];
				step.OrientationEnum = MapStringToOrientation[step.Orientation];

				buildingsInSnapShot = ProcessBuildStep(buildingSnapshot, buildingsInSnapShot, step);
				break;

			case e_mine:
				ProcessMiningStep(buildingSnapshot, buildingsInSnapShot, step);
				break;

			case e_priority:
				position = step.Orientation.find(",");
				step.PriorityIn = step.Orientation.substr(0, position);
				step.PriorityOut = Capitalize(step.Orientation.substr(position + 1));

				if (step.PriorityOut[0] == ' ')
				{
					step.PriorityOut = Capitalize(step.PriorityOut.substr(1));
				}

				step.Orientation = "";

				// Only here to populate extra parameters in step. Actual validation will be done on script generation
				BuildingExists(buildingSnapshot, buildingsInSnapShot, step);
				break;

			case e_recipe: [[fallthrough]];
			case e_filter: [[fallthrough]];
			case e_rotate: [[fallthrough]];
			case e_launch:
				// Only here to populate extra parameters in step. Actual validation will be done on script generation
				BuildingExists(buildingSnapshot, buildingsInSnapShot, step);
				break;

			case e_limit: [[fallthrough]];
			[[likely]] case e_put: [[fallthrough]];
			[[likely]] case e_take:
				step.FromInto = step.Orientation;
				// Only here to populate extra parameters in step. Actual validation will be done on script generation
				BuildingExists(buildingSnapshot, buildingsInSnapShot, step);
				break;
			default:
				break;
		}

		step_parameters.push_back(step);
	}

	return true;
}

void cMain::OnImportStepsIntoStepsIndexBtnClicked(wxCommandEvent& event)
{
	auto rows = grid_steps->GetSelectedRows();
	if (rows.IsEmpty()) return;
	auto row = rows.front();

	import_steps_into_steps_ctrl->SetValue(row);
	event.Skip();
}

void cMain::OnImportStepsIntoStepsIndexBtnRight(wxMouseEvent& event)
{
	auto rows = grid_steps->GetSelectedRows();
	if (rows.IsEmpty()) return;
	auto row = rows.Last();
	auto totalRows = grid_steps->GetNumberRows();

	import_steps_into_steps_ctrl->SetValue(row - totalRows);
	event.Skip();
}

void cMain::OnImportStepsTextUpdate(wxCommandEvent& event)
{
	if (import_steps_text_import->IsEmpty())
	{
		import_steps_into_steps_btn->Enable(false);
		import_steps_into_template_btn->Enable(false);
	}
	else
	{
		int row = import_steps_into_steps_ctrl->GetValue();
		int rows = grid_steps->GetNumberRows();
		if (row >= 0 && row <= rows)
		{
			import_steps_into_steps_ctrl->SetBackgroundColour(wxColour("Window"));
			import_steps_into_steps_btn->Enable(!import_steps_text_import->IsEmpty());
		}
		else if (row < 0 && -row <= rows + 1)
		{
			import_steps_into_steps_ctrl->SetBackgroundColour(wxColour("Window"));
			import_steps_into_steps_btn->Enable(!import_steps_text_import->IsEmpty());
		}
		else
		{
			import_steps_into_steps_ctrl->SetBackgroundColour(wxColour("Red"));
			import_steps_into_steps_btn->Enable(false);
		}
		validateTemplateName();
	}
	event.Skip();
}

void cMain::OnImportStepsIntoStepsCtrl(wxSpinEvent& event)
{
	int row = import_steps_into_steps_ctrl->GetValue();
	int rows = grid_steps->GetNumberRows();
	if (row >= 0 && row <= rows)
	{
		import_steps_into_steps_ctrl->SetBackgroundColour(wxColour("Window"));
		import_steps_into_steps_btn->Enable(!import_steps_text_import->IsEmpty());
	}
	else if (row < 0 && -row <= rows+1)
	{
		import_steps_into_steps_ctrl->SetBackgroundColour(wxColour("Window"));
		import_steps_into_steps_btn->Enable(!import_steps_text_import->IsEmpty());
	}
	else
	{
		import_steps_into_steps_ctrl->SetBackgroundColour(wxColour("Red"));
		import_steps_into_steps_btn->Enable(false);
	}
	event.Skip();
}

void cMain::OnImportStepsIntoStepsCtrlEnter(wxCommandEvent& event)
{
	if (import_steps_into_steps_btn->IsEnabled()) OnImportStepsIntoStepsBtnClick(event);
	else event.Skip();
}

void cMain::OnImportStepsIntoStepsBtnClick(wxCommandEvent& event)
{
	// validate steps
	wxString steps = import_steps_text_import->GetValue();
	vector<StepParameters> step_parameters = {};
	if (!import_steps_panel->extract_steps(steps, step_parameters)) return;

	// import steps
	int row = import_steps_into_steps_ctrl->GetValue();
	int rows = grid_steps->GetNumberRows();
	int start = row >= 0 ? row : rows + row + 1;
	size_t steps_size = step_parameters.size();

	grid_steps->InsertRows(start, steps_size);

	for (int i = 0; i < steps_size; i++)
	{
		GridEntry gridEntry = PrepareStepParametersForGrid(&step_parameters[i]);

		PopulateGrid(grid_steps, start + i, &gridEntry);

		BackgroundColorUpdate(grid_steps, start + i, step_parameters[i].type);

		if (step_parameters[i].colour != wxNullColour)
		{
			wxColour colour = step_parameters[i].colour;
			grid_steps->SetCellBackgroundColour(start + i, 1, colour);
			grid_steps->SetCellBackgroundColour(start + i, 2, colour);
			grid_steps->SetCellBackgroundColour(start + i, 3, colour);
		}
	}
	auto it1 = StepGridData.begin();
	it1 += start;
	StepGridData.insert(it1, step_parameters.begin(), step_parameters.end());

	if (import_steps_clear_checkbox->IsChecked()) import_steps_text_import->Clear();

	no_changes = false;

	event.Skip();
}

bool cMain::validateTemplateName()
{
	wxValidator* validator = import_steps_into_template_ctrl->GetValidator();
	validator->TransferFromWindow();
	if (!validator->Validate(this) && !import_steps_into_template_ctrl_validator.empty())
	{
		import_steps_into_template_btn->Enable(false);
		import_steps_into_template_ctrl->SetForegroundColour(wxColour("Red"));
		return false;
	}
	std::string text = import_steps_into_template_ctrl_validator.ToStdString();

	for (auto& template_name : template_choices)
	{
		if (equals_ignore_case(template_name.ToStdString(), text))
		{
			import_steps_into_template_btn->Enable(false);
			import_steps_into_template_ctrl->SetForegroundColour(wxColour("Red"));
			return false;
		}
		else continue;
	}
	
	import_steps_into_template_ctrl->SetForegroundColour(wxColour("Window"));
	import_steps_into_template_btn->Enable(!import_steps_text_import->IsEmpty());
	return true;
}

void cMain::OnImportStepsIntoTemplateCtrlText(wxCommandEvent& event)
{
	validateTemplateName();
	event.Skip();
}

void cMain::OnImportStepsIntoTemplateCtrlEnter(wxCommandEvent& event)
{
	if (!validateTemplateName()) return;

	// validate steps
	wxString steps = import_steps_text_import->GetValue();
	vector<StepParameters> step_parameters = {};
	if (!import_steps_panel->extract_steps(steps, step_parameters)) return;

	// create template
	std::string name = import_steps_into_template_ctrl_validator.ToStdString();
	cmb_choose_template->Clear();
	template_choices.Add(name);
	template_choices.Sort();
	cmb_choose_template->Append(template_choices);
	cmb_choose_template->SetValue(name);
	cmb_choose_template->AutoComplete(template_choices);

	auto a = template_map.insert(std::pair<std::string, std::vector<StepParameters>>(name, step_parameters) );
	for (int i = 0; i < step_parameters.size(); i++) template_map[name].push_back(step_parameters[i]);

	UpdateTemplateGrid(grid_template, template_map[name]);

	if (import_steps_clear_checkbox->IsChecked()) import_steps_text_import->Clear();

	import_steps_into_template_btn->Enable(false);
	import_steps_into_template_ctrl->SetForegroundColour(wxColour("Red"));
	no_changes = false;

	event.Skip();
}

void cMain::OnImportStepsIntoTemplateBtnClick(wxCommandEvent& event)
{
	OnImportStepsIntoTemplateCtrlEnter(event);
}
