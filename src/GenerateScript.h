#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>

#include "BuildingNameToIndex.h"
#include "DialogProgressBar.h"
#include "Functions.h"
#include "StepParameters.h"
#include "StepNameToEnum.h"
#include "utils.h"

using std::string;
using std::vector;
using std::to_string;

class GenerateScript
{
public:
	GenerateScript();
	void generate(wxWindow* parent, DialogProgressBar* dialog_progress_bar, vector<StepParameters> steps, string& folder_location, bool auto_close, bool only_generate_script, string goal);

private:
	string step_list;
	float player_x_cord;
	float player_y_cord;
	float target_x_cord;
	float target_y_cord;
	float x_building_size;
	float y_building_size;

	string current_step;
	int total_steps;

	string x_cord;
	string y_cord;
	string amount;
	string item;
	string build_orientation;
	string direction_to_build;
	string building_size;
	string amount_of_buildings;
	string comment;
	string from_into;
	string priority_in;
	string priority_out;
	string building;

	string last_walking_comment;

	void reset();
	void ClearSteps();
	string EndSteps();

	void AddInfoFile(string& folder_location);

	void SetBuildingAndOrientation(StepParameters* stepParameters);
	void TransferParameters(StepParameters& stepParameters);

	const map<string, string> map_translation{
		{"Passive provider chest", "logistic-chest-passive-provider"},
		{"Active provider chest", "logistic-chest-active-provider"},
		{"Storage chest", "logistic-chest-storage"},
		{"Buffer chest", "logistic-chest-buffer"},
		{"Requester chest", "logistic-chest-requester"},
		{"Wall", "stone-wall"},
		{"Discharge defense", "discharge-defense-equipment"},
		{"Exoskeleton", "exoskeleton-equipment"},
		{"Personal roboport", "personal-roboport-equipment"},
		{"Personal roboport MK2", "personal-roboport-mk2-equipment"},
		{"Night vision", "night-vision-equipment"},
		{"Personal battery", "battery-equipment"},
		{"Personal battery MK2", "battery-mk2-equipment"},
		{"Portable solar panel", "solar-panel-equipment"},
		{"Personal laser defence", "personal-laser-defence-equipment"},
		{"Energy shield", "energy-shield-equipment"},
		{"Energy shield MK2", "energy-shield-mk2-equipment"},
		{"Portable fusion reactor", "fusion-reactor-equipment"},
		{"Efficiency module", "effectivity-module"},
		{"Efficiency module 2", "effectivity-module-2"},
		{"Efficiency module 3", "effectivity-module-3"}
	};

	string extract_define(string from_into, string building);
	string convert_string(string input);
	string check_item_name(string item);

	void check_mining_distance(string step, string action, string x_cord, string y_cord);
	void check_interact_distance(string step, string action, string x_cord, string y_cord, string building_name, string OrientationEnum);
	double find_min_distance(float& new_x_cord, float& new_y_cord);
	vector<float> find_walk_location(float& min_x_edge, float& max_x_edge, float& min_y_edge, float& max_y_edge, const float& buffer, const float& max_distance);

	string signature(string step, string action);
	string Comment(string comment);
	string Step(string step, string action, string details, string comment);

	void walk(string step, string action, string x_cord, string y_cord, string comment);
	void mining(string step, string x_cord, string y_cord, string duration, string building_name, string OrientationEnum, bool is_building, string comment);
	void craft(string step, string amount, string item, string comment);
	void tech(string step, string tech_to_research, string comment);
	void speed(string step, string speed, string comment);
	void pause(string step, string comment);
	void launch(string step, string x_cord, string y_cord, string comment);
	void save(string step, string nameOfSaveGame);
	void idle(string step, string amount, string comment);
	void rotate(string step, string x_cord, string y_cord, string times, string item, string OrientationEnum, string comment);
	void pick(string step, string amount, string comment);

	void build(string step, string action, string x_cord, string y_cord, string item, string OrientationEnum, string comment = "");
	void row_build(string step, string x_cord, string y_cord, string item, string OrientationEnum, string direction, string number_of_buildings, string building_size, string comment);

	void take(string step, string action, string x_cord, string y_cord, string amount, string item, string from, string building, string OrientationEnum, string comment = "");
	void row_take(string step, string x_cord, string y_cord, string amount, string item, string from, string direction, string number_of_buildings, string building_size, string building, string OrientationEnum, string comment);

	void put(string step, string action, string x_cord, string y_cord, string amount, string item, string into, string building, string OrientationEnum, string comment = "");
	void row_put(string step, string x_cord, string y_cord, string amount, string item, string from, string direction, string number_of_buildings, string building_size, string building, string OrientationEnum, string comment);

	void recipe(string step, string action, string x_cord, string y_cord, string item, string building, string OrientationEnum, string comment = "");
	void row_recipe(string step, string x_cord, string y_cord, string item, string direction, string building_size, string number_of_buildings, string building, string OrientationEnum, string comment);

	void limit(string step, string action, string x_cord, string y_cord, string amount, string from, string building, string OrientationEnum, string comment = "");
	void row_limit(string step, string x_cord, string y_cord, string amount, string from, string direction, string number_of_buildings, string building_size, string building, string OrientationEnum, string comment);

	void priority(string step, string action, string x_cord, string y_cord, string priority_in, string priority_out, string building, string OrientationEnum, string comment = "");
	void row_priority(string step, string x_cord, string y_cord, string priority_in, string priority_out, string direction, string number_of_buildings, string building_size, string building, string OrientationEnum, string comment);

	void filter(string step, string action, string x_cord, string y_cord, string item, string amount, string type, string building, string OrientationEnum, string comment = "");
	void row_filter(string step, string x_cord, string y_cord, string item, string amount, string type, string direction_to_build, string number_of_buildings, string building_size, string building, string OrientationEnum, string comment);

	void drop(string step, string action, string x_cord, string y_cord, string item, string building, string comment = "");
	void row_drop(string step, string x_cord, string y_cord, string item, string direction, string number_of_buildings, string building, string building_size, string comment);
};