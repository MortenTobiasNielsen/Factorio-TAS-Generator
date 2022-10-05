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

#include "ScriptProgressBar.h"

class GenerateScript {
public:
	GenerateScript();
	void generate(wxWindow* parent, wxGrid* grid, dialog_progress_bar_base* dialog_progress_bar, std::vector<std::string> steps, std::string& folder_location, bool auto_close, bool only_generate_script, std::string goal_chosen);

private:
	std::string software_version;

	std::string step_list;
	float player_x_cord;
	float player_y_cord;
	float target_x_cord;
	float target_y_cord;
	float x_building_size;
	float y_building_size;

	std::string current_step;
	int total_steps;
	std::string segment;
	std::vector<std::string> step_segments;

	std::string task;
	std::string x_cord;
	std::string y_cord;
	std::string units;
	std::string item;
	std::string build_orientation;
	std::string direction_to_build;
	std::string building_size;
	std::string amount_of_buildings;
	std::string comment;
	std::string from_into;
	std::string priority_in;
	std::string priority_out;

	std::string building;
	std::string building_x_cord;
	std::string building_y_cord;
	std::string building_units;
	std::string building_build_orientation;
	std::string building_direction_to_build;
	std::string building_building_size;
	std::string building_amount_of_buildings;
	std::string building_priority_in;
	std::string building_priority_out;
	std::string building_comment;

	enum step_name {
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

	std::map<std::string, step_name> map_step_names = {
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
	void extract_parameters(const std::string& task_reference);
	std::string extract_define(std::string from_into, std::string building);
	void split_task(const std::string& task_reference);
	bool find_building(int& row, wxGrid* grid, std::vector<std::string>& steps);

	std::string convert_string(std::string input);

	std::string end_tasks();
	std::string signature(std::string task, std::string action);

	std::string check_item_name(std::string item);
	void check_mining_distance(std::string task, std::string action, std::string x_cord, std::string y_cord);
	void check_interact_distance(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string building_name, std::string orientation);

	double find_min_distance(float& new_x_cord, float& new_y_cord);
	std::vector<float> find_walk_location(float& min_x_edge, float& max_x_edge, float& min_y_edge, float& max_y_edge, const float& buffer, const float& max_distance);

	void walk(std::string task, std::string action, std::string x_cord, std::string y_cord);

	void mining(std::string task, std::string x_cord, std::string y_cord, std::string duration, std::string building_name, std::string orientation, bool is_building);

	void craft(std::string task, std::string amount, std::string item);

	void tech(std::string task, std::string tech_to_research);

	void speed(std::string task, std::string speed);

	void pause(std::string task);

	void stop(std::string task, std::string speed);

	void launch(std::string task, std::string x_cord, std::string y_cord);

	void save(std::string task, std::string nameOfSaveGame);

	void idle(std::string task, std::string amount);

	void rotate(std::string task, std::string x_cord, std::string y_cord, std::string times, std::string item, std::string orientation);

	void build(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string orientation);
	void row_build(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string orientation, std::string direction, std::string number_of_buildings, std::string building_size);

	void take(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string building, std::string orientation);
	void row_take(std::string task, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

	void put(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string into, std::string building, std::string orientation);
	void row_put(std::string task, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

	void recipe(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string building, std::string orientation);
	void row_recipe(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string building_size, std::string number_of_buildings, std::string building, std::string orientation);

	void limit(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string building, std::string orientation);
	void row_limit(std::string task, std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

	void priority(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string building, std::string orientation);
	void row_priority(std::string task, std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

	void filter(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string building, std::string orientation);
	void row_filter(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string direction_to_build, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

	void drop(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string building);
	void row_drop(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string number_of_buildings, std::string building, std::string building_size);

	void pick(std::string task, std::string action, std::string x_cord, std::string y_cord);
	void row_pick(std::string task, std::string x_cord, std::string y_cord, std::string direction, std::string number_of_buildings, std::string building_size);
};