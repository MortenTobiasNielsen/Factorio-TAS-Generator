#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "ScriptProgressBar.h"
#include "StepParameters.h"
#include "utils.h"

using std::string;
using std::vector;
using std::map;

class SaveTas
{
public:
	bool Save(
		wxWindow* parent,
		dialog_progress_bar_base* dialog_progress_bar,
		bool save_as,
		vector<bool> auto_list,
		vector<StepParameters> steps,
		map<string, vector<StepParameters>> maps,
		map<string, vector<StepParameters>> templates,
		string folder_location,
		string folder_location_generate,
		string goal);

private:
	inline const char* const bool_to_string(bool b);
};