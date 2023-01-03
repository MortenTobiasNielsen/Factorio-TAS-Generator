#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "DialogProgressBar.h"
#include "StepParameters.h"
#include "utils.h"
#include <filesystem>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

using std::string;
using std::vector;
using std::map;

class SaveTas
{
public:
	bool Save(
		wxWindow* parent,
		DialogProgressBar* dialog_progress_bar,
		bool save_as,
		vector<bool> auto_list,
		vector<StepParameters> steps,
		map<string, vector<StepParameters>> templates,
		string folder_location,
		string folder_location_generate,
		string goal
	);

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
	/// Saves the last tas file location in the settings file
	/// </summary>
	/// <param name="path">to the last tas location</param>
	static inline void SaveLastTas(string path)
	{
		using std::fstream;
		json data;
		try
		{
			fstream file(GetFile(), fstream::in);
			data = json::parse(file);
			file.close();
		}
		catch (...) // ignore all errors
		{ }

		data[__setting] = path;

		try
		{
			std::ofstream o;
			o.open(GetFile());
			if (o.is_open())
			{
				auto dump = data.dump(4);
				o << dump << std::endl;
				o.close();
			}
		}
		catch (...) // ignore all errors
		{ } 
	}

private:
	inline const char* const bool_to_string(bool b);
};