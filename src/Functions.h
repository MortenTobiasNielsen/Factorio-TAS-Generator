#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include <string>
#include <vector>
#include <map>
#include <ranges>

#include "Building.h"
#include "GridEntry.h"
#include "StepParameters.h"

using std::vector;
using std::string;

bool compare_task_strings(const wxString& str1, const string& str2);

bool check_input(string& item, const vector<string>& all_items);

void string_capitalized(string& string);
void string_capitalized(wxString& string);

void find_coordinates(string& x_cord, string& y_cord, string& direction, string& building_size);

bool is_number(const string& s);

vector<string> get_keys(map<string, vector<StepParameters>> map);

int ProcessBuildStep(vector<Building>& buildings, int buildingsInSnapShot, StepParameters& stepParameters);
void ProcessMiningStep(vector<Building>& buildings, int buildingsInSnapShot, StepParameters& stepParameters);
bool BuildingExists(vector<Building>& buildings, int buildingsInSnapShot, StepParameters& stepParameters);
void PopulateGrid(wxGrid* grid, int row, GridEntry* gridEntry);