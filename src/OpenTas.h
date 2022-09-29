#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "Functions.h"
#include "utils.h"
#include "ScriptProgressBar.h"

class OpenTas
{
public:
	open_file_return_data Open(wxWindow* parent, dialog_progress_bar_base* dialog_progress_bar, std::ifstream& file);

private:
	open_file_return_data return_data;

	std::string segment;
	std::vector<std::string> seglist;

	std::string group_name;
	std::vector<std::string> group_list;

	std::string template_name;
	std::vector<std::string> template_list;

	int total_lines = 0;
	int lines_processed = 0;

	void reset();

	bool extract_total_steps(std::ifstream& file);
	bool extract_goal(std::ifstream& file);
	bool extract_steps(std::ifstream& file, dialog_progress_bar_base* dialog_progress_bar);
	bool extract_groups(std::ifstream& file, dialog_progress_bar_base* dialog_progress_bar);
	bool extract_templates(std::ifstream& file, dialog_progress_bar_base* dialog_progress_bar);
	bool extract_save_location(std::ifstream& file);
	bool extract_script_location(std::ifstream& file);
	bool extract_auto_close(std::ifstream& file);
	bool extract_auto_put(std::ifstream& file);

	bool update_segment(std::ifstream& file);
};

