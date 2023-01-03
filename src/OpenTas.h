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

#include "nlohmann/json.hpp"
using json = nlohmann::json;

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


	//entry string for settings json
	static inline const std::string __setting = "last-tas";

	//filename for settings json
	static inline const std::string filename = "generator-settings.json";

	/// <summary>
	/// Gets the fully qualified named of settings json file
	/// </summary>
	/// <returns>The file name as a std::string</returns>
	static inline const std::string GetFile()
	{
		return (std::filesystem::current_path() / filename).string();
	}

	/// <summary>
	/// Opens the settings file and gets the path to last tas
	/// </summary>
	/// <returns>The path to the last tas file or an empty string</returns>
	static inline std::string LoadLastTas()
	{
		using std::fstream;
		fstream file(GetFile(), fstream::in);
		try
		{
			json data = json::parse(file);
			file.close();
			string path = data.value(__setting, "");
			return path;
		}
		catch (...) // ignore all errors and return an empty string
		{
			return "";
		} 
	}

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

