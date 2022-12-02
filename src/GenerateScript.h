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

#include "StepParameters.h"
#include "ScriptProgressBar.h"

using std::string;
using std::vector;
using std::to_string;

class GenerateScript
{
public:
	GenerateScript();
	void generate(wxWindow* parent, dialog_progress_bar_base* dialog_progress_bar, vector<StepParameters> steps, string& folder_location, bool auto_close, bool only_generate_script, string goal);

private:
	string software_version;

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
	void clear_tasks();
	string end_tasks();

	void SetBuildingAndOrientation(StepParameters* stepParameters);
	void TransferParameters(StepParameters& stepParameters);

	string extract_define(string from_into, string building);
	string convert_string(string input);
	string check_item_name(string item);

	void check_mining_distance(string step, string action, string x_cord, string y_cord);
	void check_interact_distance(string step, string action, string x_cord, string y_cord, string building_name, string orientation);
	double find_min_distance(float& new_x_cord, float& new_y_cord);
	vector<float> find_walk_location(float& min_x_edge, float& max_x_edge, float& min_y_edge, float& max_y_edge, const float& buffer, const float& max_distance);

	string signature(string step, string action);

	void walk(string step, string action, string x_cord, string y_cord, string comment);
	void mining(string step, string x_cord, string y_cord, string duration, string building_name, string orientation, bool is_building);
	void craft(string step, string amount, string item);
	void tech(string step, string tech_to_research);
	void speed(string step, string speed);
	void pause(string step);
	void stop(string step, string speed);
	void launch(string step, string x_cord, string y_cord);
	void save(string step, string nameOfSaveGame);
	void idle(string step, string amount);
	void rotate(string step, string x_cord, string y_cord, string times, string item, string orientation);
	void pick(string step, string amount);

	void build(string step, string action, string x_cord, string y_cord, string item, string orientation);
	void row_build(string step, string x_cord, string y_cord, string item, string orientation, string direction, string number_of_buildings, string building_size);

	void take(string step, string action, string x_cord, string y_cord, string amount, string item, string from, string building, string orientation);
	void row_take(string step, string x_cord, string y_cord, string amount, string item, string from, string direction, string number_of_buildings, string building_size, string building, string orientation);

	void put(string step, string action, string x_cord, string y_cord, string amount, string item, string into, string building, string orientation);
	void row_put(string step, string x_cord, string y_cord, string amount, string item, string from, string direction, string number_of_buildings, string building_size, string building, string orientation);

	void recipe(string step, string action, string x_cord, string y_cord, string item, string building, string orientation);
	void row_recipe(string step, string x_cord, string y_cord, string item, string direction, string building_size, string number_of_buildings, string building, string orientation);

	void limit(string step, string action, string x_cord, string y_cord, string amount, string from, string building, string orientation);
	void row_limit(string step, string x_cord, string y_cord, string amount, string from, string direction, string number_of_buildings, string building_size, string building, string orientation);

	void priority(string step, string action, string x_cord, string y_cord, string priority_in, string priority_out, string building, string orientation);
	void row_priority(string step, string x_cord, string y_cord, string priority_in, string priority_out, string direction, string number_of_buildings, string building_size, string building, string orientation);

	void filter(string step, string action, string x_cord, string y_cord, string item, string amount, string type, string building, string orientation);
	void row_filter(string step, string x_cord, string y_cord, string item, string amount, string type, string direction_to_build, string number_of_buildings, string building_size, string building, string orientation);

	void drop(string step, string action, string x_cord, string y_cord, string item, string building);
	void row_drop(string step, string x_cord, string y_cord, string item, string direction, string number_of_buildings, string building, string building_size);
};