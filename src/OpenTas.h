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
#include "StepParameters.h"
#include "BuildingNameToIndex.h"
#include "utils.h"
#include "ScriptProgressBar.h"

using std::vector;

struct open_file_return_data
{
	bool success = false;
	std::string goal;
	std::vector<StepParameters> steps;
	std::map<std::string, std::vector<std::string>> group_map;
	std::map<std::string, std::vector<std::string>> template_map;
	std::string save_file_location;
	std::string generate_code_folder_location;

	bool auto_close_generate_script = false;
	bool auto_close_open = false;
	bool auto_close_save = false;
	bool auto_close_save_as = false;

	bool auto_put_furnace = false;
	bool auto_put_burner = false;
	bool auto_put_lab = false;
	bool auto_put_recipe = false;
};

class OpenTas
{
public:
	open_file_return_data* Open(dialog_progress_bar_base* dialog_progress_bar, std::ifstream& file);

private:
	open_file_return_data return_data;

	std::string segment;
	std::vector<std::string> seglist;

	std::string group_name;
	std::vector<std::string> group_list;

	std::string template_name;
	std::vector<std::string> template_list;

	vector<Building> buildingSnapshot;

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

