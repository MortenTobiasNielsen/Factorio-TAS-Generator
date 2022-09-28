#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "ScriptProgressBar.h"
#include "utils.h"

class SaveTas
{
public:
	bool Save(
		wxWindow* parent,
		dialog_progress_bar_base* dialog_progress_bar,
		bool save_as,
		std::vector<bool> auto_list,
		std::vector<std::string> steps,
		std::map<std::string, std::vector<std::string>> maps,
		std::map<std::string, std::vector<std::string>> templates,
		std::string folder_location,
		std::string folder_location_generate,
		std::string goal);

private:
	inline const char* const bool_to_string(bool b);
};