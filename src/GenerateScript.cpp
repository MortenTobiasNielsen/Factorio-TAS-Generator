#include "GenerateScript.h"
#include "utils.h"
#include "Functions.h"

GenerateScript::GenerateScript() {
	step = 1;
	step_list = "local step = {}\n\n";
	player_x_cord = 0.0f;
	player_y_cord = 0.0f;
	step_segments.reserve(100);
}

void GenerateScript::Generate(wxGrid* grid, std::vector<std::string> steps, std::string folder_location, dialog_progress_bar_base* dialog_progress_bar)
{
	if (folder_location == "") {
		wxDirDialog dlg(NULL, "Choose location to generate script", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

		if (dlg.ShowModal() == wxID_OK) {
			folder_location = dlg.GetPath().ToStdString();
		}
		else {
			return;
		}
	}

	clear_tasks();
	reset_coordinates();

	if (!dialog_progress_bar) {
		dialog_progress_bar = new dialog_progress_bar_base(this, wxID_ANY, "Processing request");
	}

	dialog_progress_bar->set_text("Generating Script");
	dialog_progress_bar->set_button_enable(false);
	dialog_progress_bar->set_progress(0);
	dialog_progress_bar->Show();

	size_t amount_of_tasks = steps.size();

	for (int i = 0; i < amount_of_tasks; i++) {
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
		case step_game_speed: speed(current_step, units); break;
		case step_walk: walk(current_step, "1", x_cord, y_cord); break;
		case step_mine:
			if (units == "All") {
				units = "1000";
			}

			if (find_building(i, grid, steps)) {
				mining(current_step, x_cord, y_cord, units, building_item, build_orientation, true);
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

		case step_craft: craft(current_step, units == "All" ? "-1" : units, item); break;
		case step_tech: tech(current_step, item); break;
		case step_build: row_build(current_step, x_cord, y_cord, item, build_orientation, direction_to_build, amount_of_buildings, building_size); break;
		case step_take:
			from_into = convert_string(build_orientation);

			from_into = extract_define(from_into);

			if (from_into == "Not Found") {
				return;
			}
			row_take(current_step, x_cord, y_cord, units == "All" ? "-1" : units, item, from_into, direction_to_build, amount_of_buildings, building_size, building, build_orientation);

			break;

		case step_put:
			from_into = convert_string(build_orientation);
			from_into = extract_define(i);

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

		case step_pause: pause(current_step); break;
		case step_stop: stop(current_step, units); break;
		case step_limit:
			from_into = convert_string(build_orientation);
			from_into = extract_define(i);

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

		case step_drop: row_drop(current_step, x_cord, y_cord, item, direction_to_build, amount_of_buildings, building_size); break;
		case step_pick_up: row_pick(current_step, x_cord, y_cord, direction_to_build, amount_of_buildings, building_size); break;
		case step_launch: launch(current_step, x_cord, y_cord); break;
		case step_save: save(current_step, comment); break;
		case step_idle: idle(current_step, units); break;
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

	if (!menu_script->GetMenuItems()[2]->IsChecked()) {

		//add locale directory
		fs::create_directories(folder_location + "\\locale\\en");
		fs::copy_file("locale.cfg", folder_location + "\\locale\\en\\locale.cfg", fs::copy_options::update_existing);

		//copy lua files to tas mod if they are newer
		fs::copy_file("control.lua", folder_location + "\\control.lua", fs::copy_options::update_existing);
		fs::copy_file("settings.lua", folder_location + "\\settings.lua", fs::copy_options::update_existing);

		//Determine goal file
		std::string goal = "goal_debug.lua";
		if (menu_goals->GetMenuItems()[0]->IsChecked()) {
			goal = "goal_steelaxe.lua";
		}
		else if (menu_goals->GetMenuItems()[1]->IsChecked()) {
			goal = "goal_gotlap.lua";
		}
		else if (menu_goals->GetMenuItems()[2]->IsChecked()) {
			goal = "goal_any_percent.lua";
		}

		//always copy goal file
		fs::copy_file(goal, folder_location + "\\goal.lua", fs::copy_options::overwrite_existing);
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
	if (auto_close_generate_script) {
		dialog_progress_bar->Close();
	}
	else {
		dialog_progress_bar->set_button_enable(true);
	}

	event.Skip();
}

void GenerateScript::clear_tasks()
{
	step = 1;
	step_list = "local step = {}\n\n";
}

void GenerateScript::reset_coordinates()
{
	player_x_cord = 0.0f;
	player_y_cord = 0.0f;
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
				building_item = step_segments[4];
				build_orientation = step_segments[5];

				return true;
			}

			building_direction_to_build = step_segments[6];
			building_building_size = step_segments[7];
			building_amount_of_buildings = step_segments[8];

			for (int j = 1; j < std::stoi(building_amount_of_buildings); j++) {
				find_coordinates(building_x_cord, building_y_cord, building_direction_to_build, building_building_size);

				if (x_cord == building_x_cord && y_cord == building_y_cord) {
					building_item = step_segments[4];
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
				building_item = step_segments[4];
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