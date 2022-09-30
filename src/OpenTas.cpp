#pragma once

#include "OpenTas.h"


void OpenTas::reset() {
	seglist.reserve(100);

	group_name = "";
	group_list = {};

	template_name = "";
	template_list = {};

	return_data = {};

	return_data.success = false;
}

open_file_return_data OpenTas::Open(dialog_progress_bar_base* dialog_progress_bar, std::ifstream& file)
{
	reset();
	
	dialog_progress_bar->set_text("Opening file");
	dialog_progress_bar->set_button_enable(false);
	dialog_progress_bar->set_progress(0);
	dialog_progress_bar->Show();

	if (extract_total_steps(file) && 
		extract_goal(file) &&
		extract_steps(file, dialog_progress_bar) &&
		extract_groups(file, dialog_progress_bar) &&
		extract_templates(file, dialog_progress_bar) &&
		extract_save_location(file) &&
		extract_script_location(file) &&
		extract_auto_close(file) &&
		extract_auto_put(file)) {
		return_data.success = true;
	}

	return return_data;
}

bool OpenTas::extract_total_steps(std::ifstream& file) {
	
	if (!update_segment(file) || seglist[0] != total_steps_indicator) {
		return false;
	}

	if (!update_segment(file) || !is_number(seglist[0])) {
		return false;
	} 

	total_lines = std::stoi(seglist[0]);
	
	return true;
}

bool OpenTas::extract_goal(std::ifstream& file) {
	if (!update_segment(file) || seglist[0] != goal_indicator) {
		return false;
	}

	if (!update_segment(file) || seglist.size() != 1) {
		return false;
	}

	return_data.goal = seglist[0];

	return true;
}

bool OpenTas::extract_steps(std::ifstream& file, dialog_progress_bar_base* dialog_progress_bar)
{
	if (!update_segment(file) || (seglist[0] != steps_indicator && seglist[0] != "Tasks:")) {
		return false;
	}

	return_data.steps.reserve(total_lines);

	while (update_segment(file)) {
		if (seglist.size() != Step_segment_size) {
			return seglist.size() == 1 && seglist[0] == save_groups_indicator;
		}

		return_data.steps.push_back(seglist[0] + ";" + seglist[1] + ";" + seglist[2] + ";" + seglist[3] + ";" + seglist[4] + ";" + seglist[5] + ";" + seglist[6] + ";" + seglist[7] + ";" + seglist[8] + ";" + seglist[9] + ";");

		lines_processed++;

		if (lines_processed > 0 && lines_processed % 25 == 0) {
			dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 50);
			wxYield();
		}
	}

	return false;
}

bool OpenTas::extract_groups(std::ifstream& file, dialog_progress_bar_base* dialog_progress_bar)
{
	while (update_segment(file)) {
		if (seglist.size() != Group_segment_size) {
			if (seglist.size() == 1 && seglist[0] == save_templates_indicator) {
				return_data.group_map.insert(std::pair<std::string, std::vector<std::string>>(group_name, group_list));
				return true;
			}

			return false;
		}

		if (group_name == "") {
			group_name = seglist[0];
			group_list = {};

		}
		else if (group_name != seglist[0]) {
			return_data.group_map.insert(std::pair<std::string, std::vector<std::string>>(group_name, group_list));

			group_name = seglist[0];
			group_list = {};
		}

		group_list.push_back(seglist[1] + ";" + seglist[2] + ";" + seglist[3] + ";" + seglist[4] + ";" + seglist[5] + ";" + seglist[6] + ";" + seglist[7] + ";" + seglist[8] + ";" + seglist[9] + ";" + seglist[10] + ";");

		lines_processed++;

		if (lines_processed > 0 && lines_processed % 25 == 0) {
			dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 47);
			wxYield();
		}
	}

	return false;
}

bool OpenTas::extract_templates(std::ifstream& file, dialog_progress_bar_base* dialog_progress_bar) {

	while (update_segment(file)) {
		if (seglist.size() != Template_segment_size) {
			if (seglist.size() == 1 && seglist[0] == save_file_indicator) {
				return_data.template_map.insert(std::pair<std::string, std::vector<std::string>>(template_name, template_list));
				return true;
			}

			return false;
		}

		if (template_name == "") {
			template_name = seglist[0];
			template_list = {};
		}
		else if (template_name != seglist[0]) {
			return_data.template_map.insert(std::pair<std::string, std::vector<std::string>>(template_name, template_list));

			template_name = seglist[0];
			template_list = {};
		}

		template_list.push_back(seglist[1] + ";" + seglist[2] + ";" + seglist[3] + ";" + seglist[4] + ";" + seglist[5] + ";" + seglist[6] + ";" + seglist[7] + ";" + seglist[8] + ";" + seglist[9] + ";" + seglist[10] + ";");

		lines_processed++;

		if (lines_processed > 0 && lines_processed % 25 == 0) {
			dialog_progress_bar->set_progress(static_cast<float>(lines_processed) / static_cast<float>(total_lines) * 100.0f - 45);
			wxYield();
		}
	}

	return false;
}

bool OpenTas::extract_save_location(std::ifstream& file) {
	if (!update_segment(file) || seglist.size() != 1) {
		return false;
	}

	return_data.save_file_location = seglist[0];
	return true;
}

bool OpenTas::extract_script_location(std::ifstream& file) {
	if (!update_segment(file) || seglist[0] != code_file_indicator && seglist[0] != "Task folder location:") {
		return false;
	}
	
	if (!update_segment(file) || seglist.size() != 1) {
		return false;
	}

	return_data.generate_code_folder_location = seglist[0];
	return true;
}

bool OpenTas::extract_auto_close(std::ifstream& file) {
	if (!update_segment(file) || seglist[0] != auto_close_indicator) {
		return false;
	}

	if (!update_segment(file) || seglist.size() != 2 || seglist[0] != auto_close_generate_script_text) {
		return false;
	}

	return_data.auto_close_generate_script = seglist[1] == "true";

	if (!update_segment(file) || seglist.size() != 2 || seglist[0] != auto_close_open_text) {
		return false;
	}

	return_data.auto_close_open = seglist[1] == "true";

	if (!update_segment(file) || seglist.size() != 2 || seglist[0] != auto_close_save_text) {
		return false;
	}

	return_data.auto_close_save = seglist[1] == "true";

	if (!update_segment(file) || seglist.size() != 2 || seglist[0] != auto_close_save_as_text) {
		return false;
	}

	return_data.auto_close_save_as = seglist[1] == "true";

	return true;
}

bool OpenTas::extract_auto_put(std::ifstream& file) {
	if (!update_segment(file) || seglist[0] != auto_put_indicator) {
		return false;
	}

	if (!update_segment(file) || seglist.size() != 2 || seglist[0] != auto_put_furnace_text) {
		return false;
	}

	return_data.auto_put_furnace = seglist[1] == "true";

	if (!update_segment(file) || seglist.size() != 2 || seglist[0] != auto_put_burner_text) {
		return false;
	}

	return_data.auto_put_burner = seglist[1] == "true";

	if (!update_segment(file) || seglist.size() != 2 || seglist[0] != auto_put_lab_text) {
		return false;
	}

	return_data.auto_put_lab = seglist[1] == "true";

	if (!update_segment(file) || seglist.size() != 2 || seglist[0] != auto_put_recipe_text) {
		return false;
	}

	return_data.auto_put_recipe = seglist[1] == "true";
	
	return true;
}

bool OpenTas::update_segment(std::ifstream& file) {
	std::string line;
	std::stringstream data_line;

	if (std::getline(file, line)) {
		data_line.str(line);

		seglist = {};

		while (std::getline(data_line, segment, ';')) {
			seglist.push_back(segment);
		}

		return true;
	}
	
	return false;
}