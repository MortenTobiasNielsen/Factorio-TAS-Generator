#pragma once

#include "GenerateScript.h"
#include "utils.h"
#include "Functions.h"
#include "control_info.h"

GenerateScript::GenerateScript()
{
	software_version = "0.0.5";
	reset();
}

void GenerateScript::reset()
{
	clear_tasks();
	player_x_cord = 0.0f;
	player_y_cord = 0.0f;
	target_x_cord = 0.0f;
	target_y_cord = 0.0f;
	x_building_size = 0.0f;
	y_building_size = 0.0f;
	step_segments.reserve(100);
}

void GenerateScript::clear_tasks()
{
	total_steps = 1;
	step_list = "local step = {}\n\n";
}

std::string GenerateScript::end_tasks() {
	return step_list + "step[" + std::to_string(total_steps) + "] = {\"break\"}\n\n" + "return step";
}

void GenerateScript::generate(wxWindow* parent, wxGrid* grid, dialog_progress_bar_base* dialog_progress_bar, std::vector<std::string> steps, std::string& folder_location, bool auto_close, bool only_generate_script, std::string goal)
{
	reset();

	if (folder_location == "") {
		wxDirDialog dlg(NULL, "Choose location to generate script", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

		if (dlg.ShowModal() == wxID_OK) {
			folder_location = dlg.GetPath().ToStdString();
		}
		else {
			return;
		}
	}

	if (!dialog_progress_bar) {
		dialog_progress_bar = new dialog_progress_bar_base(parent, wxID_ANY, "Processing request");
	}

	dialog_progress_bar->set_text("Generating Script");
	dialog_progress_bar->set_button_enable(false);
	dialog_progress_bar->set_progress(0);
	dialog_progress_bar->Show();

	size_t amount_of_tasks = steps.size();

	size_t start_step = 0;

	for (int i = amount_of_tasks - 1; i > 0; i--) {
		extract_parameters(steps[i]);
		if (task == "Start") {
			start_step = i + 1;
			break;
		}
	}

	for (int i = start_step; i < amount_of_tasks; i++) {
		extract_parameters(steps[i]);
		auto t = map_step_names[task];
		if (t == step_start) {
			clear_tasks();
		}

		current_step = std::to_string(i + 1);

		if (i > 0 && i % 25 == 0) {
			dialog_progress_bar->set_progress(static_cast<float>(i) / static_cast<float>(amount_of_tasks) * 100.0f - 1);
			wxYield();
		}

		switch (t) {
		case step_game_speed: 
			speed(current_step, units); 
			break;

		case step_walk: 
			walk(current_step, "1", x_cord, y_cord, comment); 
			break;

		case step_mine:
			if (units == "All") {
				units = "1000";
			}

			if (find_building(i, grid, steps)) {
				mining(current_step, x_cord, y_cord, units, building, build_orientation, true);
			}
			else {
				mining(current_step, x_cord, y_cord, units, "", "", false);
			}
			break;

		case step_rotate:
			if (!find_building(i, grid, steps)) {
				return;
			}

			rotate(current_step, x_cord, y_cord, units, item, build_orientation);
			break;

		case step_craft: 
			craft(current_step, units == "All" ? "-1" : units, item);
			break;

		case step_tech: 
			tech(current_step, item); 
			break;

		case step_build: 
			row_build(current_step, x_cord, y_cord, item, build_orientation, direction_to_build, amount_of_buildings, building_size); 
			break;

		case step_take:
			from_into = convert_string(build_orientation);

			if (from_into != struct_from_into_list.wreck) {
				find_building(i, grid, steps);
			}

			from_into = extract_define(from_into, building);

			if (from_into == "Not Found") {
				return;
			}
			
			row_take(current_step, x_cord, y_cord, units == "All" ? "-1" : units, item, from_into, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			break;

		case step_put:
			from_into = convert_string(build_orientation);

			if (from_into != struct_from_into_list.wreck) {
				find_building(i, grid, steps);
			}

			from_into = extract_define(from_into, building);

			if (from_into == "Not Found") {
				return;
			}
			row_put(current_step, x_cord, y_cord, units == "All" ? "-1" : units, item, from_into, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			break;

		case step_recipe:
			if (!find_building(i, grid, steps)) {
				return;
			}

			row_recipe(current_step, x_cord, y_cord, item, direction_to_build, building_size, amount_of_buildings, building, build_orientation);
			break;

		case step_pause: 
			pause(current_step); 
			break;

		case step_stop: 
			stop(current_step, units); 
			break;

		case step_limit:
			from_into = convert_string(build_orientation);

			if (from_into != struct_from_into_list.wreck) {
				find_building(i, grid, steps);
			}

			from_into = extract_define(from_into, building);

			if (from_into == "Not Found") {
				return;
			}

			row_limit(current_step, x_cord, y_cord, units, from_into, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			break;

		case step_priority:
		{
			long long pos = build_orientation.find(",");

			priority_in = build_orientation.substr(0, pos);
			priority_out = build_orientation.substr(pos + 2);
		}

		if (!find_building(i, grid, steps)) {
			return;
		}

		row_priority(current_step, x_cord, y_cord, priority_in, priority_out, direction_to_build, amount_of_buildings, building_size, building, build_orientation);
		break;

		case step_filter:
			if (!find_building(i, grid, steps)) {
				return;
			}
			row_filter(current_step, x_cord, y_cord, item, units, check_input(building, splitter_list) ? "splitter" : "inserter", direction_to_build, amount_of_buildings, building_size, building, build_orientation);
			break;

		case step_drop: 
			if (!find_building(i, grid, steps)) {
				return;
			}
			row_drop(current_step, x_cord, y_cord, item, direction_to_build, amount_of_buildings, building_size, building);
			break;

		case step_pick_up: 
			row_pick(current_step, x_cord, y_cord, direction_to_build, amount_of_buildings, building_size);
			break;

		case step_launch: 
			launch(current_step, x_cord, y_cord); 
			break;

		case step_save: 
			save(current_step, comment); 
			break;

		case step_idle: 
			idle(current_step, units); 
			break;
		}
	}

	// If the file is send to another person the folder location won't exist and should be set to something else.
	namespace fs = std::filesystem;
	if (!fs::exists(folder_location)) {
		wxDirDialog dlg(NULL, "Choose location to generate script", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

		if (dlg.ShowModal() == wxID_OK) {
			folder_location = dlg.GetPath().ToStdString();
		}
		else {
			return;
		}
	}

	if (!only_generate_script) {

		//add locale directory
		fs::create_directories(folder_location + "\\locale\\en");
		fs::copy_file("..\\Lua Files\\locale.cfg", folder_location + "\\locale\\en\\locale.cfg", fs::copy_options::update_existing);

		//copy lua files to tas mod if they are newer
		fs::copy_file("..\\Lua Files\\control.lua", folder_location + "\\control.lua", fs::copy_options::update_existing);
		fs::copy_file("..\\Lua Files\\settings.lua", folder_location + "\\settings.lua", fs::copy_options::update_existing);

		//always copy goal file
		fs::copy_file("..\\Lua Files\\" + goal, folder_location + "\\goal.lua", fs::copy_options::overwrite_existing);
	}

	//generate info file
	std::ofstream saver;
	saver.open(folder_location + "\\info.json");
	saver << "\{\n\t\"name\": \"" + folder_location.substr(folder_location.rfind("\\") + 1) + "\",";
	saver << "\n\t\"version\": \"" << software_version << "\",";
	saver << "\n\t\"title\": \"" + folder_location.substr(folder_location.rfind("\\") + 1) + "\",";
	saver << info;
	saver.close();

	//generate step file
	saver.open(folder_location + "\\steps.lua");

	saver << end_tasks();

	saver.close();

	dialog_progress_bar->set_progress(100);
	if (auto_close) {
		dialog_progress_bar->Close();
	}
	else {
		dialog_progress_bar->set_button_enable(true);
	}
}

void GenerateScript::extract_parameters(const std::string& task_reference)
{
	split_task(task_reference);

	task = step_segments[0];
	x_cord = step_segments[1];
	y_cord = step_segments[2];
	units = step_segments[3];
	item = step_segments[4];
	build_orientation = step_segments[5];
	direction_to_build = step_segments[6];
	building_size = step_segments[7];
	amount_of_buildings = step_segments[8];
	comment = step_segments[9];
}

std::string GenerateScript::extract_define(std::string from_into, std::string building)
{
	if (from_into == struct_from_into_list.wreck) {
		return struct_take_put_list.chest;
	}

	if (from_into == struct_from_into_list.chest) {
		return struct_take_put_list.chest;
	}

	if (from_into == struct_from_into_list.fuel) {
		return struct_take_put_list.fuel;
	}

	if (building == struct_science_list.lab) {
		if (from_into == struct_from_into_list.input) {
			return struct_take_put_list.lab_input;
		}
		else if (from_into == struct_from_into_list.modules) {
			return struct_take_put_list.lab_modules;
		}
	}

	if (check_input(building, drills_list)) {
		return struct_take_put_list.drill_modules;
	}

	if (from_into == struct_from_into_list.input) {
		return struct_take_put_list.assembly_input;
	}

	if (from_into == struct_from_into_list.modules) {
		return struct_take_put_list.assembly_modules;
	}
	if (from_into == struct_from_into_list.output) {
		return struct_take_put_list.assembly_output;
	}

	return "Not Found";
}

void GenerateScript::split_task(const std::string& task_reference)
{
	std::stringstream data_line;
	data_line.str(task_reference);

	step_segments = {};

	while (std::getline(data_line, segment, ';')) {
		step_segments.push_back(segment);
	}
}

bool GenerateScript::find_building(int& row, wxGrid* grid, std::vector<std::string>& steps)
{
	for (int i = row - 1; i > -1; i--) {
		if (compare_task_strings(grid->GetCellValue(i, 0), struct_tasks_list.build)) {
			split_task(steps[i]);

			building_x_cord = step_segments[1];
			building_y_cord = step_segments[2];

			if (x_cord == building_x_cord && y_cord == building_y_cord) {
				building = step_segments[4];
				build_orientation = step_segments[5];

				return true;
			}

			building_direction_to_build = step_segments[6];
			building_building_size = step_segments[7];
			building_amount_of_buildings = step_segments[8];

			for (int j = 1; j < std::stoi(building_amount_of_buildings); j++) {
				find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);

				if (x_cord == building_x_cord && y_cord == building_y_cord) {
					building = step_segments[4];
					build_orientation = step_segments[5];

					return true;
				}
			}
		}
		else if (compare_task_strings(grid->GetCellValue(i, 0), struct_tasks_list.rotate)) {
			split_task(steps[i]);

			building_x_cord = step_segments[1];
			building_y_cord = step_segments[2];

			if (x_cord == building_x_cord && y_cord == building_y_cord) {
				building = step_segments[4];
				build_orientation = step_segments[5];

				return true;
			}
		}
	}

	if (task == struct_tasks_list.mine) {
		return false;
	}

	wxMessageBox("Task: " + current_step + " have no building associated with it - please correct the error and try again", "The building does not exist");
	return false;
}

std::string GenerateScript::convert_string(std::string input) {
	std::for_each(input.begin(), input.end(), [](char& c) {
		if (isspace(c)) {
			c = '-';
		}
		c = ::tolower(c);
		});
	return input;
}

std::string GenerateScript::signature(std::string step, std::string action) {
	return "step[" + std::to_string(total_steps) + "] = {{" + step + "," + action + "}, ";
}

std::string GenerateScript::check_item_name(std::string item) {
	if (item == "Passive provider chest") {
		return item = "logistic-chest-passive-provider";
	}
	else if (item == "Active provider chest") {
		return item = "logistic-chest-active-provider";
	}
	else if (item == "Storage chest") {
		return item = "logistic-chest-storage";
	}
	else if (item == "Buffer chest") {
		return item = "logistic-chest-buffer";
	}
	else if (item == "Requester chest") {
		return item = "logistic-chest-requester";
	}
	else if (item == "Wall") {
		return item = "stone-wall";
	}
	else if (item == "Discharge defense") {
		return item = "discharge-defense-equipment";
	}
	else if (item == "Exoskeleton") {
		return item = "exoskeleton-equipment";
	}
	else if (item == "Personal roboport") {
		return item = "personal-roboport-equipment";
	}
	else if (item == "Personal roboport MK2") {
		return item = "personal-roboport-mk2-equipment";
	}
	else if (item == "Night vision") {
		return item = "night-vision-equipment";
	}
	else if (item == "Personal battery") {
		return item = "battery-equipment";
	}
	else if (item == "Personal battery MK2") {
		return item = "battery-mk2-equipment";
	}
	else if (item == "Portable solar panel") {
		return item = "solar-panel-equipment";
	}
	else if (item == "Personal laser defence") {
		return item = "personal-laser-defence-equipment";
	}
	else if (item == "Energy shield") {
		return item = "energy-shield-equipment";
	}
	else if (item == "Energy shield MK2") {
		return item = "energy-shield-mk2-equipment";
	}
	else if (item == "Portable fusion reactor") {
		return item = "fusion-reactor-equipment";
	}
	else if (item == "Efficiency module") {
		return item = "effectivity-module";
	}
	else if (item == "Efficiency module 2") {
		return item = "effectivity-module-2";
	}
	else if (item == "Efficiency module 3") {
		return item = "effectivity-module-3";
	}
	else {
		return item = convert_string(item);
	}

	return "Not a known item";
}

void GenerateScript::check_mining_distance(std::string step, std::string action, std::string x_cord, std::string y_cord) {
	static const float buffer = 0.50f; // this should be set correctly when you get a better understanding of how it is actually calculated in the game
	static const float max_distance = 2.7f;

	float min_x_edge = std::stof(x_cord) - 0.5f;
	float max_x_edge = std::stof(x_cord) + 0.5f;
	float min_y_edge = std::stof(y_cord) - 0.5f;
	float max_y_edge = std::stof(y_cord) + 0.5f;

	std::vector<float> coordinates = find_walk_location(min_x_edge, max_x_edge, min_y_edge, max_y_edge, buffer, max_distance);

	if (player_x_cord != coordinates[0] || player_y_cord != coordinates[1]) {
		walk(step, action, std::to_string(coordinates[0]), std::to_string(coordinates[1]), last_walking_comment);
	}
}

void GenerateScript::check_interact_distance(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string building_name, std::string orientation) {
	if (building_name == "Wreck") {
		x_building_size = 1;
		y_building_size = 1;
	}
	else {
		x_building_size = building_size_list.find(building_name)->second[0];
		y_building_size = building_size_list.find(building_name)->second[1];
	}

	static const float buffer = 0.0f; // TODO remove
	static const float max_distance = 10.0f; //Default build distance

	float x_target = floor(std::stof(x_cord));
	if ((int)ceil(x_building_size) % 2 == 1) x_target += 0.5; //if a building is an uneven number of tiles wide, it will be placed at a half tile

	float y_target = floor(std::stof(y_cord));
	if ((int)ceil(y_building_size) % 2 == 1) y_target += 0.5; //if a building is an uneven number of tiles tall, it will be placed at a half tile

	float min_x_edge = x_target, max_x_edge = x_target;
	float min_y_edge = y_target, max_y_edge = y_target;

	if (orientation == "North" || orientation == "South") {
		min_x_edge -= (x_building_size / 2);
		max_x_edge += (x_building_size / 2);
		min_y_edge -= (y_building_size / 2);
		max_y_edge += (y_building_size / 2);
	}
	else {
		min_x_edge -= (y_building_size / 2);
		max_x_edge += (y_building_size / 2);
		min_y_edge -= (x_building_size / 2);
		max_y_edge += (x_building_size / 2);
	}

	std::vector<float> coordinates = find_walk_location(min_x_edge, max_x_edge, min_y_edge, max_y_edge, buffer, max_distance);

	if (player_x_cord != coordinates[0] || player_y_cord != coordinates[1]) {
		walk(step, action, std::to_string(coordinates[0]), std::to_string(coordinates[1]), last_walking_comment);
	}
}

double GenerateScript::find_min_distance(float& new_x_cord, float& new_y_cord) {
	return std::pow(std::pow(std::abs(target_x_cord - new_x_cord), 2) + std::pow(std::abs(target_y_cord - new_y_cord), 2), 0.5);
}

std::vector<float> GenerateScript::find_walk_location(float& min_x_edge, float& max_x_edge, float& min_y_edge, float& max_y_edge, const float& buffer, const float& max_distance) {

	static const float delta_distance = 0.01f;
	static const float not_to_close = 0.15f;

	float new_x_cord = player_x_cord;
	float new_y_cord = player_y_cord;

	if (new_x_cord < min_x_edge - not_to_close) {
		if (new_y_cord < min_y_edge - not_to_close) {
			// Top left
			target_x_cord = min_x_edge + buffer;
			target_y_cord = min_y_edge + buffer;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				if (new_x_cord < min_x_edge - not_to_close && new_y_cord < min_y_edge - not_to_close) {
					new_x_cord += delta_distance;
					new_y_cord += delta_distance;
				}
				else if (new_x_cord < min_x_edge - not_to_close) {
					new_x_cord += delta_distance;
				}
				else {
					new_y_cord += delta_distance;
				}
			}
		}
		else if (new_y_cord > max_y_edge + not_to_close) {
			// bottom left
			target_x_cord = min_x_edge + buffer;
			target_y_cord = max_y_edge - buffer;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				if (new_x_cord < min_x_edge - not_to_close && new_y_cord > max_y_edge + not_to_close) {
					new_x_cord += delta_distance;
					new_y_cord -= delta_distance;
				}
				else if (new_x_cord < min_x_edge - not_to_close) {
					new_x_cord += delta_distance;
				}
				else {
					new_y_cord -= delta_distance;
				}
			}
		}
		else {
			// Mid left
			target_x_cord = min_x_edge + buffer;
			target_y_cord = new_y_cord;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				new_x_cord += delta_distance;
			}
		}
	}
	else if (new_x_cord > max_x_edge + not_to_close) {
		if (new_y_cord < min_y_edge - not_to_close) {
			// Top right
			target_x_cord = max_x_edge - buffer;
			target_y_cord = min_y_edge + buffer;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				if (new_x_cord > max_x_edge + not_to_close && new_y_cord < min_y_edge - not_to_close) {
					new_x_cord -= delta_distance;
					new_y_cord += delta_distance;
				}
				else if (new_x_cord > max_x_edge + not_to_close) {
					new_x_cord -= delta_distance;
				}
				else {
					new_y_cord += delta_distance;
				}
			}
		}
		else if (new_y_cord > max_y_edge + not_to_close) {
			// bottom right
			target_x_cord = max_x_edge - buffer;
			target_y_cord = max_y_edge - buffer;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				if (new_x_cord > max_x_edge + not_to_close && new_y_cord > max_y_edge + not_to_close) {
					new_x_cord -= delta_distance;
					new_y_cord -= delta_distance;
				}
				else if (new_x_cord > max_x_edge + not_to_close) {
					new_x_cord -= delta_distance;
				}
				else {
					new_y_cord -= delta_distance;
				}
			}
		}
		else {
			// Mid right
			target_x_cord = max_x_edge - buffer;
			target_y_cord = new_y_cord;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				new_x_cord -= delta_distance;
			}
		}
	}
	else if (new_y_cord < min_y_edge - not_to_close) {
		// Mid top
		target_x_cord = new_x_cord;
		target_y_cord = min_y_edge + buffer;

		while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
			new_y_cord += delta_distance;
		}
	}
	else if (new_y_cord > max_y_edge + not_to_close) {
		// Mid bottom
		target_x_cord = new_x_cord;
		target_y_cord = max_y_edge - buffer;

		while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
			new_y_cord -= delta_distance;
		}
	}

	return { new_x_cord, new_y_cord };
}

void GenerateScript::walk(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string comment)
{
	if (comment == "old" || comment == "Old") {
		last_walking_comment = convert_string(comment);
	} else if (comment == "new" || comment == "New") {
		last_walking_comment = "";
	} else if (comment != "") {
		last_walking_comment = comment;
	}

	step_list += signature(step, action) + "\"walk\", {" + x_cord + ", " + y_cord + "}, \"" + last_walking_comment + "\"}\n";
	player_x_cord = std::stof(x_cord);
	player_y_cord = std::stof(y_cord);
	total_steps += 1;
}

void GenerateScript::mining(std::string step, std::string x_cord, std::string y_cord, std::string duration, std::string building_name, std::string orientation, bool is_building)
{
	if (is_building) {
		check_interact_distance(step, "1", x_cord, y_cord, building_name, orientation);
	}
	else {
		check_mining_distance(step, "1", x_cord, y_cord);
	}

	step_list += signature(step, "1") + "\"mine\", {" + x_cord + ", " + y_cord + "}, " + duration + "}\n";
	total_steps += 1;
}

void GenerateScript::craft(std::string step, std::string amount, std::string item) {
	item = check_item_name(item);

	step_list += signature(step, "1") + "\"craft\", " + amount + ", \"" + item + "\"}\n";
	total_steps += 1;
};

void GenerateScript::tech(std::string step, std::string tech_to_research) {
	tech_to_research = convert_string(tech_to_research);

	if (tech_to_research == "efficiency-module") {
		tech_to_research = "effectivity-module";
	}
	else if (tech_to_research == "efficiency-module-2") {
		tech_to_research = "effectivity-module-2";
	}
	else if (tech_to_research == "efficiency-module-3") {
		tech_to_research = "effectivity-module-3";
	}
	else if (tech_to_research == "lab-research-speed-1") {
		tech_to_research = "research-speed-1";
	}
	else if (tech_to_research == "lab-research-speed-2") {
		tech_to_research = "research-speed-2";
	}
	else if (tech_to_research == "lab-research-speed-3") {
		tech_to_research = "research-speed-3";
	}
	else if (tech_to_research == "lab-research-speed-4") {
		tech_to_research = "research-speed-4";
	}
	else if (tech_to_research == "lab-research-speed-5") {
		tech_to_research = "research-speed-5";
	}
	else if (tech_to_research == "lab-research-speed-6") {
		tech_to_research = "research-speed-6";
	}
	else if (tech_to_research == "worker-robot-cargo-size-1") {
		tech_to_research = "worker-robots-storage-1";
	}
	else if (tech_to_research == "worker-robot-cargo-size-2") {
		tech_to_research = "worker-robots-storage-2";
	}
	else if (tech_to_research == "worker-robot-cargo-size-3") {
		tech_to_research = "worker-robots-storage-3";
	}
	else if (tech_to_research == "worker-robot-speed-1") {
		tech_to_research = "worker-robots-speed-1";
	}
	else if (tech_to_research == "worker-robot-speed-2") {
		tech_to_research = "worker-robots-speed-2";
	}
	else if (tech_to_research == "worker-robot-speed-3") {
		tech_to_research = "worker-robots-speed-3";
	}
	else if (tech_to_research == "worker-robot-speed-4") {
		tech_to_research = "worker-robots-speed-4";
	}
	else if (tech_to_research == "worker-robot-speed-5") {
		tech_to_research = "worker-robots-speed-5";
	}
	else if (tech_to_research == "worker-robot-speed-6") {
		tech_to_research = "worker-robots-speed-6";
	}
	else if (tech_to_research == "portable-solar-panel") {
		tech_to_research = "solar-panel-equipment";
	}
	else if (tech_to_research == "land-mines") {
		tech_to_research = "land-mine";
	}
	else if (tech_to_research == "nightvision-equipment") {
		tech_to_research = "night-vision-equipment";
	}
	else if (tech_to_research == "personal-battery") {
		tech_to_research = "battery equipment";
	}

	step_list += signature(step, "1") + "\"tech\", \"" + tech_to_research + "\"}\n";
	total_steps += 1;
}

void GenerateScript::speed(std::string step, std::string speed) {
	step_list += signature(step, "1") + "\"speed\", " + speed + "}\n";
	total_steps += 1;
}

void GenerateScript::pause(std::string step) {
	step_list += signature(step, "1") + "\"pause\"" + "}\n";
	total_steps += 1;
}

void GenerateScript::stop(std::string step, std::string speed) {
	step_list += signature(step, "1") + "\"stop\", " + speed + "}\n";
	total_steps += 1;
}

void GenerateScript::launch(std::string step, std::string x_cord, std::string y_cord) {
	step_list += signature(step, "1") + "\"launch\", {" + x_cord + ", " + y_cord + "}}\n";
	total_steps += 1;
}

void GenerateScript::save(std::string step, std::string nameOfSaveGame) {
	step_list += signature(step, "1") + "\"save\", \"" + nameOfSaveGame + "\"}\n";
	total_steps += 1;
}

void GenerateScript::idle(std::string step, std::string amount) {
	step_list += signature(step, "1") + "\"idle\", " + amount + "}\n";
	total_steps += 1;
}

void GenerateScript::rotate(std::string step, std::string x_cord, std::string y_cord, std::string times, std::string item, std::string orientation) {

	check_interact_distance(step, "1", x_cord, y_cord, item, orientation);

	if (std::stoi(times) == 3) {
		step_list += signature(step, "1") + "\"rotate\", {" + x_cord + ", " + y_cord + "}, " + "true}\n";
		total_steps += 1;
	}
	else {
		for (int i = 0; i < std::stoi(times); i++) {
			step_list += signature(step, std::to_string(i + 1)) + "\"rotate\", {" + x_cord + ", " + y_cord + "}, " + "false}\n";
			total_steps += 1;
		}
	}
}

void GenerateScript::build(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string orientation) {
	check_interact_distance(step, action, x_cord, y_cord, item, orientation);

	item = check_item_name(item);

	if (orientation == "North") {
		orientation = build_directions.north;
	}
	else if (orientation == "South") {
		orientation = build_directions.south;
	}
	else if (orientation == "East") {
		orientation = build_directions.east;
	}
	else if (orientation == "West") {
		orientation = build_directions.west;
	}
	else {
		return;
	}

	step_list += signature(step, action) + "\"build\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + orientation + "}\n";
	total_steps += 1;
};

void GenerateScript::row_build(std::string step, std::string x_cord, std::string y_cord, std::string item, std::string orientation, std::string direction, std::string number_of_buildings, std::string building_size) {

	build(step, "1", x_cord, y_cord, item, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		build(step, std::to_string(i + 1), x_cord, y_cord, item, orientation);
	}
}

void GenerateScript::take(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string building, std::string orientation) {
	if (orientation == "Wreck") {
		check_interact_distance(step, action, x_cord, y_cord, orientation, "North");
	}
	else {
		check_interact_distance(step, action, x_cord, y_cord, building, orientation);
	}

	item = check_item_name(item);

	step_list += signature(step, action) + "\"take\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + amount + ", " + from + "}\n";
	total_steps += 1;
}

void GenerateScript::row_take(std::string step, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {

	take(step, "1", x_cord, y_cord, amount, item, from, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		take(step, std::to_string(i + 1), x_cord, y_cord, amount, item, from, building, orientation);
	}
}

void GenerateScript::put(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string into, std::string building, std::string orientation) {
	if (orientation == "Wreck") {
		check_interact_distance(step, action, x_cord, y_cord, orientation, "North");
	}
	else {
		check_interact_distance(step, action, x_cord, y_cord, building, orientation);
	}

	item = check_item_name(item);

	step_list += signature(step, action) + "\"put\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + amount + ", " + into + "}\n";
	total_steps += 1;
}

void GenerateScript::row_put(std::string step, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {
	put(step, "1", x_cord, y_cord, amount, item, from, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		put(step, std::to_string(i + 1), x_cord, y_cord, amount, item, from, building, orientation);
	}
}

void GenerateScript::recipe(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string building, std::string orientation) {
	check_interact_distance(step, action, x_cord, y_cord, building, orientation);

	item = check_item_name(item);

	step_list += signature(step, action) + "\"recipe\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\"}\n";
	total_steps += 1;
}

void GenerateScript::row_recipe(std::string step, std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string building_size, std::string number_of_buildings, std::string building, std::string orientation) {

	recipe(step, "1", x_cord, y_cord, item, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		recipe(step, std::to_string(i + 1), x_cord, y_cord, item, building, orientation);
	}
}

void GenerateScript::limit(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string building, std::string orientation) {
	check_interact_distance(step, action, x_cord, y_cord, building, orientation);

	step_list += signature(step, action) + "\"limit\", {" + x_cord + ", " + y_cord + "}, " + amount + ", " + from + "}\n";
	total_steps += 1;
}

void GenerateScript::row_limit(std::string step, std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {

	limit(step, "1", x_cord, y_cord, amount, from, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		limit(step, std::to_string(i + 1), x_cord, y_cord, amount, from, building, orientation);
	}
}

void GenerateScript::priority(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string building, std::string orientation) {
	check_interact_distance(step, action, x_cord, y_cord, building, orientation);

	step_list += signature(step, action) + "\"priority\", {" + x_cord + ", " + y_cord + "}, \"" + priority_in + "\", \"" + priority_out + "\"}\n";
	total_steps += 1;
}

void GenerateScript::row_priority(std::string step, std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {
	priority_in = convert_string(priority_in);
	priority_out = convert_string(priority_out);

	priority(step, "1", x_cord, y_cord, priority_in, priority_out, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		priority(step, std::to_string(i + 1), x_cord, y_cord, priority_in, priority_out, building, orientation);;
	}
}

void GenerateScript::filter(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string building, std::string orientation) {
	check_interact_distance(step, action, x_cord, y_cord, building, orientation);

	item = check_item_name(item);

	step_list += signature(step, action) + "\"filter\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + units + ",  \"" + type + "\"}\n";
	total_steps += 1;
}

void GenerateScript::row_filter(std::string step, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {
	filter(step, "1", x_cord, y_cord, item, units, type, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		filter(step, std::to_string(i + 1), x_cord, y_cord, item, units, type, building, orientation);
	}
}

void GenerateScript::drop(std::string step, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string building) {
	check_interact_distance(step, action, x_cord, y_cord, building, "North");

	convert_string(item);

	step_list += signature(step, action) + "\"drop\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\"}\n";
	total_steps += 1;
}

void GenerateScript::row_drop(std::string step, std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string number_of_buildings, std::string building_size, std::string building) {
	drop(step, "1", x_cord, y_cord, item, building);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		drop(step, std::to_string(i + 1), x_cord, y_cord, item, building);
	}
}

void GenerateScript::pick(std::string step, std::string action, std::string x_cord, std::string y_cord) {
	walk(step, action, x_cord, y_cord, last_walking_comment);
	step_list += signature(step, action) + "\"pick\", {" + x_cord + ", " + y_cord + "}}\n";
	total_steps += 1;
}

void GenerateScript::row_pick(std::string step, std::string x_cord, std::string y_cord, std::string direction, std::string number_of_buildings, std::string building_size) {
	pick(step, "1", x_cord, y_cord);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		pick(step, std::to_string(i + 1), x_cord, y_cord);
	}
}