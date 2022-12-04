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

bool check_input(const string& item, const vector<string>& all_items);

string Capitalize(const wxString& stringToCapitalize, const bool isItem = false);

void find_coordinates(string& x_cord, string& y_cord, string& direction, string& building_size);

bool is_number(const string& s);

vector<string> get_keys(map<string, vector<StepParameters>> map);

int ProcessBuildStep(vector<Building>& buildings, int buildingsInSnapShot, StepParameters& stepParameters);
void ProcessMiningStep(vector<Building>& buildings, int buildingsInSnapShot, StepParameters& stepParameters);
bool BuildingExists(vector<Building>& buildings, int buildingsInSnapShot, StepParameters& stepParameters);
void PopulateGrid(wxGrid* grid, int row, GridEntry* gridEntry);