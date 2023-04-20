#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "Functions.h"
#include "StepParameters.h"
#include "BuildingNameToIndex.h"
#include "utils.h"
#include "DialogProgressBar.h"
#include "TasFileConstants.h"

using std::string;
using std::vector;
using std::map;
using std::pair;

struct open_file_return_data
{
	bool success = false;
	string goal;
	vector<StepParameters> steps;
	map<string, vector<StepParameters>> template_map;
	string save_file_location;
	string generate_code_folder_location;

	wxGridBlockCoordsVector selected_rows;

	bool auto_close_generate_script = false;
	bool auto_close_open = false;
	bool auto_close_save = false;
	bool auto_close_save_as = false;

	bool auto_put_furnace = false;
	bool auto_put_burner = false;
	bool auto_put_lab = false;
	bool auto_put_recipe = false;
};

enum Category
{
	Invalid,
	Group,
	Template
};

class OpenTas
{
public:
	open_file_return_data* Open(DialogProgressBar* dialog_progress_bar, std::ifstream& file);

private:
	open_file_return_data return_data;

	vector<string> segments;

	vector<Building> buildingSnapshot;

	int total_lines = 0;
	int lines_processed = 0;

	void reset();

	bool extract_total_steps(std::ifstream& file);
	bool extract_goal(std::ifstream& file);
	Category extract_steps(std::ifstream& file, DialogProgressBar* dialog_progress_bar);
	bool extract_groups(std::ifstream& file, DialogProgressBar* dialog_progress_bar);
	bool extract_templates(std::ifstream& file, DialogProgressBar* dialog_progress_bar);
	bool extract_save_location(std::ifstream& file);
	bool extract_script_location(std::ifstream& file);
	bool extract_auto_close(std::ifstream& file);
	bool extract_auto_put(std::ifstream& file);

	bool update_segment(std::ifstream& file);
};

