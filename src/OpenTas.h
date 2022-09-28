#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include "ScriptProgressBar.h"

class OpenTas
{
public:
	bool Open(wxWindow* parent, dialog_progress_bar_base* dialog_progress_bar, std::ifstream& file);

private:
	std::string goal;
	std::string segment;
	std::vector<std::string> seglist;
	std::vector<std::string> steps;

	std::string group_name;
	std::vector<std::string> group_list;
	std::map<std::string, std::vector<std::string>> group_map;

	std::string template_name;
	std::vector<std::string> template_list;
	std::map<std::string, std::vector<std::string>> template_map;

	std::string save_file_location = "";
	std::string generate_code_folder_location = "";

	bool auto_close_generate_script;
	bool auto_close_open;
	bool auto_close_save;
	bool auto_close_save_as;

	bool auto_put_furnace;
	bool auto_put_burner;
	bool auto_put_lab;
	bool auto_put_recipe;

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

