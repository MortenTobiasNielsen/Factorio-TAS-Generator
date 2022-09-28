#pragma once

#include "OpenTas.h"
#include "Functions.h"
#include "utils.h"

OpenTas::OpenTas() {
	seglist.reserve(100);
}

bool OpenTas::Open(wxWindow* parent, dialog_progress_bar_base* dialog_progress_bar, std::ifstream file)
{
	if (!dialog_progress_bar) {
		dialog_progress_bar = new dialog_progress_bar_base(parent, wxID_ANY, "Processing request");
	}

	dialog_progress_bar->set_text("Opening file");
	dialog_progress_bar->set_button_enable(false);
	dialog_progress_bar->set_progress(0);
	dialog_progress_bar->Show();

	if (!extract_total_steps(file) ||
		!) {
		return false;
	}
}

bool OpenTas::extract_total_steps(std::ifstream& file) {
	update_segment(file);
	if (seglist[0] != total_steps_indicator) {
		return false;
	}

	update_segment(file);
	if (is_number(seglist[0])) {
		total_lines = std::stoi(seglist[0]);
	} else {
		
		return false;
	}

	return true;
}

bool OpenTas::extract_goal(std::ifstream& file) {
	update_segment(file);
	if (seglist[0] != goal_indicator) {
		return false;
	}

	update_segment(file);
	if (seglist.size() != 1) {
		return false;
	}

	goal = seglist[0];

	return true;
}

void OpenTas::update_segment(std::ifstream& file) {
	std::string line;
	std::stringstream data_line;

	std::getline(file, line);
	data_line.str(line);

	seglist = {};

	while (std::getline(data_line, segment, ';')) {
		seglist.push_back(segment);
	}
}