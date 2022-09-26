#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "ScriptProgressBar.h"

class GenerateScript {
public:
	GenerateScript();
	std::string generate(wxWindow* parent, wxGrid* grid, dialog_progress_bar_base* dialog_progress_bar, std::vector<std::string> steps, std::string folder_location, bool auto_close, bool only_generate_script, std::string goal_chosen);

private:
	static std::string software_version;

	static std::string step_list;
	static float player_x_cord;
	static float player_y_cord;
	static float target_x_cord;
	static float target_y_cord;
	static float x_building_size;
	static float y_building_size;

	static std::string current_step;
	static int total_steps;
	static std::string segment;
	static std::vector<std::string> step_segments;

	static std::string task;
	static std::string x_cord;
	static std::string y_cord;
	static std::string units;
	static std::string item;
	static std::string build_orientation;
	static std::string direction_to_build;
	static std::string building_size;
	static std::string amount_of_buildings;
	static std::string comment;
	static std::string from_into;
	static std::string priority_in;
	static std::string priority_out;

	static std::string building;
	static std::string building_x_cord;
	static std::string building_y_cord;
	static std::string building_units;
	static std::string building_build_orientation;
	static std::string building_direction_to_build;
	static std::string building_building_size;
	static std::string building_amount_of_buildings;
	static std::string building_priority_in;
	static std::string building_priority_out;
	static std::string building_comment;

	void reset();
	void clear_tasks();
	void extract_parameters(const std::string& task_reference);
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

	void drop(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string item);
	void row_drop(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string number_of_buildings, std::string building_size);

	void pick(std::string task, std::string action, std::string x_cord, std::string y_cord);
	void row_pick(std::string task, std::string x_cord, std::string y_cord, std::string direction, std::string number_of_buildings, std::string building_size);
};