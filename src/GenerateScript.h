#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "ScriptProgressBar.h"


class GenerateScript {
public:
	void Generate(wxGrid* grid, std::vector<std::string> steps, std::string folder_location, dialog_progress_bar_base* dialog_progress_bar);

private:
	static int step;
	static std::string step_list;
	static float player_x_cord;
	static float player_y_cord;
	static std::string current_step;
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

	static std::string building_x_cord;
	static std::string building_y_cord;
	static std::string building_units;
	static std::string building_item;
	static std::string building_build_orientation;
	static std::string building_direction_to_build;
	static std::string building_building_size;
	static std::string building_amount_of_buildings;
	static std::string building_priority_in;
	static std::string building_priority_out;
	static std::string building_comment;

	void clear_tasks();
	void reset_coordinates();
	void extract_parameters(const std::string& task_reference);
	void split_task(const std::string& task_reference);
	bool find_building(int& row, wxGrid* grid, std::vector<std::string>& steps);
};