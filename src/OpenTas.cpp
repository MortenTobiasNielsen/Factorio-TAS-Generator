#pragma once

#include "OpenTas.h"

void OpenTas::reset()
{
	segments.reserve(100);

	return_data = {};

	return_data.success = false;
}

open_file_return_data* OpenTas::Open(DialogProgressBar* dialog_progress_bar, std::ifstream& file)
{
	reset();

	dialog_progress_bar->set_text("Opening file");
	dialog_progress_bar->set_button_enable(false);
	dialog_progress_bar->set_progress(0);
	dialog_progress_bar->Show();

	if (!extract_total_steps(file) || !extract_goal(file))
	{
		return &return_data;
	}

	Category category = extract_steps(file, dialog_progress_bar);
	switch (category)
	{
		case Invalid:
			return &return_data;

		case Group:
			if (!extract_groups(file, dialog_progress_bar))
			{
				return &return_data;
			}

			// fallthrough so tamplate is also done, if groups are in the save file
		case Template:
			if (!extract_templates(file, dialog_progress_bar))
			{
				return &return_data;
			}

			break;

		default:
			break;
	}

	if (extract_save_location(file) &&
		extract_script_location(file) &&
		extract_auto_close(file) &&
		extract_auto_put(file))
	{
		return_data.success = true;
	}

	return &return_data;
}

bool OpenTas::extract_total_steps(std::ifstream& file)
{

	if (!update_segment(file) || segments[0] != total_steps_indicator)
	{
		return false;
	}

	if (!update_segment(file) || !is_number(segments[0]))
	{
		return false;
	}

	total_lines = std::stoi(segments[0]);

	return true;
}

bool OpenTas::extract_goal(std::ifstream& file)
{
	if (!update_segment(file) || segments[0] != goal_indicator)
	{
		return false;
	}

	if (!update_segment(file) || segments.size() != 1)
	{
		return false;
	}

	return_data.goal = segments[0];

	return true;
}

Category OpenTas::extract_steps(std::ifstream& file, DialogProgressBar* dialog_progress_bar)
{
	if (!update_segment(file) || (segments[0] != steps_indicator && segments[0] != "Tasks:"))
	{
		return Invalid;
	}

	return_data.steps.reserve(total_lines);

	buildingSnapshot.reserve(100000);
	for (int i = 0; i < buildingSnapshot.capacity(); i++)
	{
		buildingSnapshot.emplace_back(invalidX);
	}

	int buildingsInSnapShot = 0;
	int position = 0;

	while (update_segment(file))
	{
		if (segments.size() != step_segment_size && 
			segments.size() != step_segment_size_without_comment &&
			segments.size() != step_segment_size_without_comment_and_colour)
		{
			if (segments[0] == save_templates_indicator)
			{
				return Template;
			}

			if (segments.size() == 1 && (segments[0] == save_groups_indicator))
			{
				return Group;
			}

			return Invalid;
		}

		string comment = "";
		if (segments.size() == step_segment_size || segments.size() == step_segment_size_without_comment)
		{
			comment = segments[9];
		}

		StepParameters step(invalidX, 0);

		if (segments[1] != "")
		{
			step.X = stod(segments[1]);
			step.OriginalX = stod(segments[1]);
			step.Y = stod(segments[2]);
			step.OriginalY = stod(segments[2]);
		}

		if (segments[7] != "")
		{
			step.Size = stoi(segments[7]);
		}

		if (segments[8] != "")
		{
			step.Buildings = stoi(segments[8]);
		}

		step.Step = Capitalize(segments[0]);
		step.Amount = Capitalize(segments[3]);
		step.Item = Capitalize(segments[4], true);
		step.Orientation = Capitalize(segments[5]);
		step.Direction = Capitalize(segments[6]);
		step.Comment = comment;

		if (segments.size() == step_segment_size)
		{
			step.Colour = segments[10];
		}
		else
		{
			step.Colour = "";
		}

		if (step.Step == "Start")
		{
			continue; // Ignore start steps, given that they are obsolete.
		}

		auto mappedtype = MapStepNameToStepType.find(step.Step);
		if (mappedtype == MapStepNameToStepType.end())
		{
			return Invalid;
		}

		step.StepEnum = mappedtype->second;

		switch (step.StepEnum)
		{
			case e_build:
				step.BuildingIndex = BuildingNameToType[step.Item];
				step.OrientationEnum = OrientationToEnum[step.Orientation];

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

			case e_recipe:
			case e_filter:
			case e_rotate:
			case e_launch:
				// Only here to populate extra parameters in step. Actual validation will be done on script generation
				BuildingExists(buildingSnapshot, buildingsInSnapShot, step);
				break;

			case e_limit:
			case e_put:
			case e_take:
				step.FromInto = step.Orientation;
				// Only here to populate extra parameters in step. Actual validation will be done on script generation
				BuildingExists(buildingSnapshot, buildingsInSnapShot, step);
				break;
			default:
				break;
		}

		return_data.steps.push_back(step);

		lines_processed++;

		if (lines_processed > 0 && lines_processed % 25 == 0)
		{
			dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 50);
			wxYield();
		}
	}

	return Invalid;
}

bool OpenTas::extract_groups(std::ifstream& file, DialogProgressBar* dialog_progress_bar)
{
	vector<StepParameters> steps = {};
	string name = "";
	int position = 0;

	// Groups are obsolete and have been moved to template. This is here for backwards compatibility. 
	while (update_segment(file))
	{
		if (segments.size() != group_segment_size && segments.size() != group_segment_size_without_comment)
		{
			if (segments.size() == 1 && segments[0] == save_templates_indicator)
			{
				if (name != "")
				{
					return_data.template_map.insert(pair<string, vector<StepParameters>>(name, steps));
				}

				return true;
			}

			return false;
		}

		if (name == "")
		{
			name = segments[0];
			steps = {};

		}
		else if (name != segments[0])
		{
			return_data.template_map.insert(pair<string, vector<StepParameters>>(name, steps));

			name = segments[0];
			steps = {};
		}

		string comment = "";
		if (segments.size() == group_segment_size)
		{
			comment = segments[10];
		}

		StepParameters step(invalidX, 0);

		if (segments[2] != "")
		{
			step.X = stod(segments[2]);
			step.OriginalX = stod(segments[2]);
			step.Y = stod(segments[3]);
			step.OriginalY = stod(segments[3]);
		}

		if (segments[8] != "")
		{
			step.Size = stoi(segments[8]);
		}

		if (segments[9] != "")
		{
			step.Buildings = stoi(segments[9]);
		}

		step.Step = Capitalize(segments[1]);
		step.Amount = Capitalize(segments[4]);
		step.Item = Capitalize(segments[5], true);
		step.Orientation = Capitalize(segments[6]);
		step.Direction = Capitalize(segments[7]);
		step.Comment = comment;

		if (step.Step == "Start")
		{
			continue; // Ignore start steps, given that they are obsolete.
		}

		auto mappedtype = MapStepNameToStepType.find(step.Step);
		if (mappedtype == MapStepNameToStepType.end())
		{
			return false;
		}

		step.StepEnum = mappedtype->second;

		switch (step.StepEnum)
		{
			case e_build:
				step.BuildingIndex = BuildingNameToType[step.Item];
				step.OrientationEnum = OrientationToEnum[step.Orientation];
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
				break;

			case e_limit:
			case e_put:
			case e_take:
				step.FromInto = step.Orientation;
				break;
			default:
				break;
		}

		steps.push_back(step);

		lines_processed++;

		if (lines_processed > 0 && lines_processed % 25 == 0)
		{
			dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 47);
			wxYield();
		}
	}

	return false;
}

bool OpenTas::extract_templates(std::ifstream& file, DialogProgressBar* dialog_progress_bar)
{
	vector<StepParameters> steps = {};
	string name = "";
	int position = 0;

	while (update_segment(file))
	{
		if (segments.size() != template_segment_size &&
			segments.size() != template_segment_size_without_comment &&
			segments.size() != template_segment_size_without_comment_and_colour)
		{
			if (segments.size() == 1 && segments[0] == save_file_indicator)
			{
				if (name != "")
				{
					if (return_data.template_map.find(name) != return_data.template_map.end())
					{
						name += "_Template";
					}

					return_data.template_map.insert(pair<string, vector<StepParameters>>(name, steps));
				}

				return true;
			}

			return false;
		}

		if (name == "")
		{
			name = segments[0];
			steps = {};
		}
		else if (name != segments[0])
		{
			if (return_data.template_map.find(name) != return_data.template_map.end())
			{
				name += "_Template";
			}

			return_data.template_map.insert(pair<string, vector<StepParameters>>(name, steps));

			name = segments[0];
			steps = {};
		}

		string comment = "";
		if (segments.size() == template_segment_size)
		{
			comment = segments[10];
		}

		StepParameters step(invalidX, 0);

		if (segments[2] != "")
		{
			step.X = stod(segments[2]);
			step.OriginalX = stod(segments[2]);
			step.Y = stod(segments[3]);
			step.OriginalY = stod(segments[3]);
		}

		if (segments[8] != "")
		{
			step.Size = stoi(segments[8]);
		}

		if (segments[9] != "")
		{
			step.Buildings = stoi(segments[9]);
		}

		step.Step = Capitalize(segments[1]);
		step.Amount = Capitalize(segments[4]);
		step.Item = Capitalize(segments[5], true);
		step.Orientation = Capitalize(segments[6]);
		step.Direction = Capitalize(segments[7]);
		step.Comment = comment;

		if (step.Step == "Start")
		{
			continue; // Ignore start steps, given that they are obsolete.
		}

		auto mappedtype = MapStepNameToStepType.find(step.Step);
		if (mappedtype == MapStepNameToStepType.end())
		{
			return false;
		}

		step.StepEnum = mappedtype->second;

		switch (step.StepEnum)
		{
			case e_build:
				step.BuildingIndex = BuildingNameToType[step.Item];
				step.OrientationEnum = OrientationToEnum[step.Orientation];
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
				break;

			case e_limit:
			case e_put:
			case e_take:
				step.FromInto = step.Orientation;
				break;
			default:
				break;
		}

		steps.push_back(step);

		lines_processed++;

		if (lines_processed > 0 && lines_processed % 25 == 0)
		{
			dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 45);
			wxYield();
		}
	}

	return false;
}

bool OpenTas::extract_save_location(std::ifstream& file)
{
	if (!update_segment(file) || segments.size() != 1)
	{
		return false;
	}

	return_data.save_file_location = segments[0];
	return true;
}

bool OpenTas::extract_script_location(std::ifstream& file)
{
	if (!update_segment(file) || segments[0] != code_file_indicator && segments[0] != "Task folder location:")
	{
		return false;
	}

	if (!update_segment(file) || segments.size() != 1)
	{
		return false;
	}

	return_data.generate_code_folder_location = segments[0];
	return true;
}

bool OpenTas::extract_auto_close(std::ifstream& file)
{
	if (!update_segment(file) || segments[0] != auto_close_indicator)
	{
		return false;
	}

	if (!update_segment(file) || segments.size() != 2 || segments[0] != auto_close_generate_script_text)
	{
		return false;
	}

	return_data.auto_close_generate_script = segments[1] == "true";

	if (!update_segment(file) || segments.size() != 2 || segments[0] != auto_close_open_text)
	{
		return false;
	}

	return_data.auto_close_open = segments[1] == "true";

	if (!update_segment(file) || segments.size() != 2 || segments[0] != auto_close_save_text)
	{
		return false;
	}

	return_data.auto_close_save = segments[1] == "true";

	if (!update_segment(file) || segments.size() != 2 || segments[0] != auto_close_save_as_text)
	{
		return false;
	}

	return_data.auto_close_save_as = segments[1] == "true";

	return true;
}

bool OpenTas::extract_auto_put(std::ifstream& file)
{
	if (!update_segment(file) || segments[0] != auto_put_indicator)
	{
		return false;
	}

	if (!update_segment(file) || segments.size() != 2 || segments[0] != auto_put_furnace_text)
	{
		return false;
	}

	return_data.auto_put_furnace = segments[1] == "true";

	if (!update_segment(file) || segments.size() != 2 || segments[0] != auto_put_burner_text)
	{
		return false;
	}

	return_data.auto_put_burner = segments[1] == "true";

	if (!update_segment(file) || segments.size() != 2 || segments[0] != auto_put_lab_text)
	{
		return false;
	}

	return_data.auto_put_lab = segments[1] == "true";

	if (!update_segment(file) || segments.size() != 2 || segments[0] != auto_put_recipe_text)
	{
		return false;
	}

	return_data.auto_put_recipe = segments[1] == "true";

	return true;
}

bool OpenTas::update_segment(std::ifstream& file)
{
	string line;
	string segment;
	std::stringstream data_line;

	if (std::getline(file, line))
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