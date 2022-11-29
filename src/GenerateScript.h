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
	string segment;
	vector<string> step_segments;

	string task;
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

	enum step_name
	{
		step_start = 1,
		step_stop,
		step_build,
		step_craft,
		step_game_speed,
		step_pause,
		step_save,
		step_recipe,
		step_limit,
		step_filter,
		step_rotate,
		step_priority,
		step_put,
		step_take,
		step_mine,
		step_launch,
		step_walk,
		step_tech,
		step_drop,
		step_pick_up,
		step_idle
	};

	std::map<string, step_name> map_step_names = {
		{"Start", step_start},
		{"Stop", step_stop},
		{"Build", step_build},
		{"Craft", step_craft},
		{"Game Speed", step_game_speed},
		{"Pause", step_pause},
		{"Save", step_save},
		{"Recipe", step_recipe},
		{"Limit", step_limit},
		{"Filter", step_filter},
		{"Rotate", step_rotate},
		{"Priority", step_priority},
		{"Put", step_put},
		{"Take", step_take},
		{"Mine", step_mine},
		{"Launch", step_launch},
		{"Walk", step_walk},
		{"Tech", step_tech},
		{"Drop", step_drop},
		{"Pick up", step_pick_up},
		{"Idle", step_idle}
	};

	void reset();
	void clear_tasks();
	void TransferParameters(StepParameters& stepParameters);
	void SetBuildingAndOrientation(StepParameters* stepParameters);
	string extract_define(string from_into, string building);
	bool find_building(int& row, std::vector<StepParameters>& steps);

	string convert_string(string input);

	string end_tasks();
	string signature(string task, string action);

	string check_item_name(string item);
	void check_mining_distance(string task, string action, string x_cord, string y_cord);
	void check_interact_distance(string task, string action, string x_cord, string y_cord, string building_name, string orientation);

	double find_min_distance(float& new_x_cord, float& new_y_cord);
	std::vector<float> find_walk_location(float& min_x_edge, float& max_x_edge, float& min_y_edge, float& max_y_edge, const float& buffer, const float& max_distance);

	void walk(string step, string action, string x_cord, string y_cord, string comment);

	void mining(string task, string x_cord, string y_cord, string duration, string building_name, string orientation, bool is_building);

	void craft(string task, string amount, string item);

	void tech(string task, string tech_to_research);

	void speed(string task, string speed);

	void pause(string task);

	void stop(string task, string speed);

	void launch(string task, string x_cord, string y_cord);

	void save(string task, string nameOfSaveGame);

	void idle(string task, string amount);

	void rotate(string task, string x_cord, string y_cord, string times, string item, string orientation);

	void pick(string step, string amount);

	void build(string task, string action, string x_cord, string y_cord, string item, string orientation);
	void row_build(string task, string x_cord, string y_cord, string item, string orientation, string direction, string number_of_buildings, string building_size);

	void take(string task, string action, string x_cord, string y_cord, string amount, string item, string from, string building, string orientation);
	void row_take(string task, string x_cord, string y_cord, string amount, string item, string from, string direction, string number_of_buildings, string building_size, string building, string orientation);

	void put(string task, string action, string x_cord, string y_cord, string amount, string item, string into, string building, string orientation);
	void row_put(string task, string x_cord, string y_cord, string amount, string item, string from, string direction, string number_of_buildings, string building_size, string building, string orientation);

	void recipe(string task, string action, string x_cord, string y_cord, string item, string building, string orientation);
	void row_recipe(string task, string x_cord, string y_cord, string item, string direction, string building_size, string number_of_buildings, string building, string orientation);

	void limit(string task, string action, string x_cord, string y_cord, string amount, string from, string building, string orientation);
	void row_limit(string task, string x_cord, string y_cord, string amount, string from, string direction, string number_of_buildings, string building_size, string building, string orientation);

	void priority(string task, string action, string x_cord, string y_cord, string priority_in, string priority_out, string building, string orientation);
	void row_priority(string task, string x_cord, string y_cord, string priority_in, string priority_out, string direction, string number_of_buildings, string building_size, string building, string orientation);

	void filter(string task, string action, string x_cord, string y_cord, string item, string amount, string type, string building, string orientation);
	void row_filter(string task, string x_cord, string y_cord, string item, string amount, string type, string direction_to_build, string number_of_buildings, string building_size, string building, string orientation);

	void drop(string task, string action, string x_cord, string y_cord, string item, string building);
	void row_drop(string task, string x_cord, string y_cord, string item, string direction, string number_of_buildings, string building, string building_size);
};