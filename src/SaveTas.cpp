#pragma once

#include "SaveTas.h"

bool SaveTas::Save(
	wxWindow* parent,
	DialogProgressBar* dialog_progress_bar,
	bool save_as,
	vector<bool> auto_list,
	vector<StepParameters> steps,
	map<string, vector<StepParameters>> templates,
	string folder_location,
	string folder_location_generate,
	string goal)
{
	int total_lines = steps.size();

	for (auto& t : templates)
	{
		total_lines += t.second.size();
	}

	int lines_processed = 0;

	if (!dialog_progress_bar)
	{
		dialog_progress_bar = new DialogProgressBar(parent, wxID_ANY, "Processing request");
	}

	dialog_progress_bar->set_text("Saving file");
	dialog_progress_bar->set_button_enable(false);
	dialog_progress_bar->set_progress(0);
	dialog_progress_bar->Show();

	std::ofstream myfile;
	myfile.open(folder_location);

	myfile << total_steps_indicator << std::endl;
	myfile << total_lines << std::endl;

	myfile << goal_indicator << std::endl;
	myfile << goal << std::endl;

	myfile << steps_indicator << std::endl;
	for (auto it = steps.begin(); it < steps.end(); it++)
	{
		myfile << (*it).ToString() << std::endl;

		lines_processed++;

		if (lines_processed > 0 && lines_processed % 25 == 0)
		{
			dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 1);
			wxYield();
		}
	}

	myfile << save_templates_indicator << std::endl;
	if (templates.size())
	{
		for (auto element : templates)
		{
			for (auto value : element.second)
			{
				myfile << element.first + ";" + value.ToString() << std::endl;

				lines_processed++;

				if (lines_processed > 0 && lines_processed % 25 == 0)
				{
					dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 1);
					wxYield();
				}
			}
		}
	}

	myfile << save_file_indicator << std::endl;
	myfile << folder_location << ";" << std::endl;

	myfile << code_file_indicator << std::endl;
	myfile << folder_location_generate << ";" << std::endl;

	myfile << auto_close_indicator << std::endl;
	myfile << auto_close_generate_script_text << ";" << bool_to_string(auto_list[0]) << std::endl;
	myfile << auto_close_open_text << ";" << bool_to_string(auto_list[1]) << std::endl;
	myfile << auto_close_save_text << ";" << bool_to_string(auto_list[2]) << std::endl;
	myfile << auto_close_save_as_text << ";" << bool_to_string(auto_list[3]) << std::endl;

	myfile << auto_put_indicator << std::endl;
	myfile << auto_put_furnace_text << ";" << bool_to_string(auto_list[4]) << std::endl;
	myfile << auto_put_burner_text << ";" << bool_to_string(auto_list[5]) << std::endl;
	myfile << auto_put_lab_text << ";" << bool_to_string(auto_list[6]) << std::endl;
	myfile << auto_put_recipe_text << ";" << bool_to_string(auto_list[7]);

	myfile.close();

	dialog_progress_bar->set_progress(100);
	if (save_as)
	{
		if (auto_list[8])
		{
			dialog_progress_bar->Close();
		}
		else
		{
			dialog_progress_bar->set_button_enable(true);
		}
	}
	else
	{
		if (auto_list[9])
		{
			dialog_progress_bar->Close();
		}
		else
		{
			dialog_progress_bar->set_button_enable(true);
		}
	}

	SaveLastTas(folder_location);

	return true;
}

inline const char* const SaveTas::bool_to_string(bool b)
{
	return b ? "true" : "false";
}