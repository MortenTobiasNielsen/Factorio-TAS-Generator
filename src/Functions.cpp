#include "Functions.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

bool compare_task_strings(const wxString& str1, const std::string& str2)
{
	if (str1.length() != str2.length()) {
		return false;
	}

	for (int i = 0; i < str1.length(); i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}

	return true;
}

std::string extract_define(std::string building, std::string from_into)
{
	if (from_into == "wreck") {
		return take_put_list.chest;
	}

	if (from_into == "chest") {
		return take_put_list.chest;
	}

	if (from_into == "fuel") {
		return take_put_list.fuel;
	}

	if (building == "Lab") {
		if (from_into == "input") {
			return take_put_list.lab_input;
		}
		else if (from_into == "modules") {
			return take_put_list.lab_modules;
		}
	}

	if (check_input(building, drills_list)) {
		return take_put_list.drill_modules;
	}

	if (from_into == "input") {
		return take_put_list.assembly_input;
	}

	if (from_into == "modules") {
		return take_put_list.assembly_modules;
	}
	if (from_into == "output") {
		return take_put_list.assembly_output;
	}

	return "Not Found";
}

bool check_input(std::string& item, const std::vector<std::string>& all_items)
{
	std::string item_lower = "";
	for (unsigned int i = 0; i < item.size(); i++) {
		item_lower.push_back(std::tolower(item[i]));
	}

	for (auto it = all_items.begin(); it < all_items.end(); it++) {

		std::string check_item_lower = "";

		for (unsigned int i = 0; i < (*it).size(); i++) {
			check_item_lower.push_back(std::tolower((*it)[i]));
		}

		if (item_lower == check_item_lower) {
			item = *it;
			return true;
		}
	}

	return false;
}

std::string signature(std::string task, std::string action) {
	return "step[" + std::to_string(step) + "] = {{" + task + "," + action + "}, ";
}

std::string check_item_name(std::string item) {
	if (item == "Passive provider chest") {
		return item = "logistic-chest-passive-provider";
	} else if (item == "Active provider chest") {
		return item = "logistic-chest-active-provider";
	} else if (item == "Storage chest") {
		return item = "logistic-chest-storage";
	} else if (item == "Buffer chest") {
		return item = "logistic-chest-buffer";
	} else if (item == "Requester chest") {
		return item = "logistic-chest-requester";
	} else if (item == "Wall") {
		return item = "stone-wall";
	} else if (item == "Discharge defense") {
		return item = "discharge-defense-equipment";
	} else if (item == "Exoskeleton") {
		return item = "exoskeleton-equipment";
	} else if (item == "Personal roboport") {
		return item = "personal-roboport-equipment";
	} else if (item == "Personal roboport MK2") {
		return item = "personal-roboport-mk2-equipment";
	} else if (item == "Night vision") {
		return item = "night-vision-equipment";
	} else if (item == "Personal battery") {
		return item = "battery-equipment";
	} else if (item == "Personal battery MK2") {
		return item = "battery-mk2-equipment";
	} else if (item == "Portable solar panel") {
		return item = "solar-panel-equipment";
	} else if (item == "Personal laser defence") {
		return item = "personal-laser-defence-equipment";
	} else if (item == "Energy shield") {
		return item = "energy-shield-equipment";
	} else if (item == "Energy shield MK2") {
		return item = "energy-shield-mk2-equipment";
	} else if (item == "Portable fusion reactor") {
		return item = "fusion-reactor-equipment";
	} else if (item == "Efficiency module") {
		return item = "effectivity-module";
	} else if (item == "Efficiency module 2") {
		return item = "effectivity-module-2";
	} else if (item == "Efficiency module 3") {
		return item = "effectivity-module-3";
	} else {
		return item = convert_string(item);
	}

	return "Not a known item";
}

void walk(std::string task, std::string action, std::string x_cord, std::string y_cord) {
	step_list += signature(task, action) + "\"walk\", {" + x_cord + ", " + y_cord + "}}\n";
	player_x_cord = std::stof(x_cord);
	player_y_cord = std::stof(y_cord);
	step += 1;
};

void mining(std::string task, std::string x_cord, std::string y_cord, std::string duration, std::string building_name, std::string orientation, bool is_building) {
	if (is_building) {
		check_interact_distance(task, "1", x_cord, y_cord, building_name, orientation);
	} else {
		check_mining_distance(task, "1", x_cord, y_cord);
	}

	step_list += signature(task, "1") + "\"mine\", {" + x_cord + ", " + y_cord + "}, " + duration + "}\n";
	step += 1;
}

void craft(std::string task, std::string amount, std::string item) {
	item = check_item_name(item);

	step_list += signature(task, "1") + "\"craft\", " + amount + ", \"" + item + "\"}\n";
	step += 1;
};

void build(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string orientation) {
	check_interact_distance(task, action, x_cord, y_cord, item, orientation);

	item = check_item_name(item);

	if (orientation == "North") {
		orientation = build_directions.north;
	} else if (orientation == "South") {
		orientation = build_directions.south;
	} else if (orientation == "East") {
		orientation = build_directions.east;
	} else if (orientation == "West") {
		orientation = build_directions.west;
	} else {
		return;
	}

	step_list += signature(task, action) + "\"build\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + orientation + "}\n";
	step += 1;
};

void row_build(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string orientation, std::string direction, std::string number_of_buildings, std::string building_size) {

	build(task, "1", x_cord, y_cord, item, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		build(task, std::to_string(i + 1), x_cord, y_cord, item, orientation);
	}
}

void take(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string building, std::string orientation) {
	if (orientation == "Wreck") {
		check_interact_distance(task, action, x_cord, y_cord, orientation, "North");
	} else {
		check_interact_distance(task, action, x_cord, y_cord, building, orientation);
	}

	item = check_item_name(item);

	step_list += signature(task, action) + "\"take\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + amount + ", " + from + "}\n";
	step += 1;
}

void row_take(std::string task, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {

	take(task, "1", x_cord, y_cord, amount, item, from, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		take(task, std::to_string(i + 1), x_cord, y_cord, amount, item, from, building, orientation);
	}
}

void put(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string into, std::string building, std::string orientation) {
	if (orientation == "Wreck") {
		check_interact_distance(task, action, x_cord, y_cord, orientation, "North");
	} else {
		check_interact_distance(task, action, x_cord, y_cord, building, orientation);
	}

	item = check_item_name(item);

	step_list += signature(task, action) + "\"put\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + amount + ", " + into + "}\n";
	step += 1;
}

void row_put(std::string task, std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {
	put(task, "1", x_cord, y_cord, amount, item, from, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		put(task, std::to_string(i + 1), x_cord, y_cord, amount, item, from, building, orientation);
	}
}

void recipe(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string building, std::string orientation) {
	check_interact_distance(task, action, x_cord, y_cord, building, orientation);

	item = check_item_name(item);

	step_list += signature(task, action) + "\"recipe\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\"}\n";
	step += 1;
}

void row_recipe(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string building_size, std::string number_of_buildings, std::string building, std::string orientation) {

	recipe(task, "1", x_cord, y_cord, item, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		recipe(task, std::to_string(i + 1), x_cord, y_cord, item, building, orientation);
	}
}

void limit(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string building, std::string orientation) {
	check_interact_distance(task, action, x_cord, y_cord, building, orientation);

	step_list += signature(task, action) + "\"limit\", {" + x_cord + ", " + y_cord + "}, " + amount + ", " + from + "}\n";
	step += 1;
}

void row_limit(std::string task, std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {

	limit(task, "1", x_cord, y_cord, amount, from, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		limit(task, std::to_string(i + 1), x_cord, y_cord, amount, from, building, orientation);
	}
}

void priority(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string building, std::string orientation) {
	check_interact_distance(task, action, x_cord, y_cord, building, orientation);

	step_list += signature(task, action) + "\"priority\", {" + x_cord + ", " + y_cord + "}, \"" + priority_in + "\", \"" + priority_out + "\"}\n";
	step += 1;
}

void row_priority(std::string task, std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {
	priority_in = convert_string(priority_in);
	priority_out = convert_string(priority_out);
	
	priority(task, "1", x_cord, y_cord, priority_in, priority_out, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		priority(task, std::to_string(i + 1), x_cord, y_cord, priority_in, priority_out, building, orientation);;
	}
}

void filter(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string building, std::string orientation) {
	check_interact_distance(task, action, x_cord, y_cord, building, orientation);

	item = check_item_name(item);

	step_list += signature(task, action) + "\"filter\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + units + ",  \"" + type + "\"}\n";
	step += 1;
}

void row_filter(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation) {
	filter(task, "1", x_cord, y_cord, item, units, type, building, orientation);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		filter(task, std::to_string(i + 1), x_cord, y_cord, item, units, type, building, orientation);
	}
}

void drop(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string item) {
	check_interact_distance(task, action, x_cord, y_cord, "Drop", "North");

	convert_string(item);

	step_list += signature(task, action) + "\"drop\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\"}\n";
	step += 1;
}

void row_drop(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string number_of_buildings, std::string building_size) {
	drop(task, "1", x_cord, y_cord, item);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		drop(task, std::to_string(i + 1), x_cord, y_cord, item);
	}
}

void pick(std::string task, std::string action, std::string x_cord, std::string y_cord) {
	walk(task, action, x_cord, y_cord);
	step_list += signature(task, action) + "\"pick\", {" + x_cord + ", " + y_cord + "}}\n";
	step += 1;
}

void row_pick(std::string task, std::string x_cord, std::string y_cord, std::string direction, std::string number_of_buildings, std::string building_size) {
	pick(task, "1", x_cord, y_cord);

	for (int i = 1; i < std::stof(number_of_buildings); i++) {
		find_coordinates(x_cord, y_cord, direction, building_size);

		pick(task, std::to_string(i + 1), x_cord, y_cord);
	}
}

void tech(std::string task, std::string tech_to_research) {
	tech_to_research = convert_string(tech_to_research);

	if (tech_to_research == "efficiency-module") {
		tech_to_research = "effectivity-module";
	} else if (tech_to_research == "efficiency-module-2") {
		tech_to_research = "effectivity-module-2";
	} else if (tech_to_research == "efficiency-module-3") {
		tech_to_research = "effectivity-module-3";
	} else if (tech_to_research == "lab-research-speed-1") {
		tech_to_research = "research-speed-1";
	} else if (tech_to_research == "lab-research-speed-2") {
		tech_to_research = "research-speed-2";
	} else if (tech_to_research == "lab-research-speed-3") {
		tech_to_research = "research-speed-3";
	} else if (tech_to_research == "lab-research-speed-4") {
		tech_to_research = "research-speed-4";
	} else if (tech_to_research == "lab-research-speed-5") {
		tech_to_research = "research-speed-5";
	} else if (tech_to_research == "lab-research-speed-6") {
		tech_to_research = "research-speed-6";
	} else if (tech_to_research == "worker-robot-cargo-size-1") {
		tech_to_research = "worker-robots-storage-1";
	} else if (tech_to_research == "worker-robot-cargo-size-2") {
		tech_to_research = "worker-robots-storage-2";
	} else if (tech_to_research == "worker-robot-cargo-size-3") {
		tech_to_research = "worker-robots-storage-3";
	} else if (tech_to_research == "worker-robot-speed-1") {
		tech_to_research = "worker-robots-speed-1";
	} else if (tech_to_research == "worker-robot-speed-2") {
		tech_to_research = "worker-robots-speed-2";
	} else if (tech_to_research == "worker-robot-speed-3") {
		tech_to_research = "worker-robots-speed-3";
	} else if (tech_to_research == "worker-robot-speed-4") {
		tech_to_research = "worker-robots-speed-4";
	} else if (tech_to_research == "worker-robot-speed-5") {
		tech_to_research = "worker-robots-speed-5";
	} else if (tech_to_research == "worker-robot-speed-6") {
		tech_to_research = "worker-robots-speed-6";
	} else if (tech_to_research == "portable-solar-panel") {
		tech_to_research = "solar-panel-equipment";
	} else if (tech_to_research == "land-mines") {
		tech_to_research = "land-mine";
	} else if (tech_to_research == "nightvision-equipment") {
		tech_to_research = "night-vision-equipment";
	} else if (tech_to_research == "personal-battery") {
		tech_to_research = "battery equipment";
	}

	step_list += signature(task, "1") + "\"tech\", \"" + tech_to_research + "\"}\n";
	step += 1;
}

void speed(std::string task, std::string speed) {
	step_list += signature(task, "1") + "\"speed\", " + speed + "}\n";
	step += 1;
}

void pause(std::string task) {
	step_list += signature(task, "1") + "\"pause\"" + "}\n";
	step += 1;
}

void stop(std::string task, std::string speed) {
	step_list += signature(task, "1") + "\"stop\", " + speed + "}\n";
	step += 1;
}

void launch(std::string task, std::string x_cord, std::string y_cord) {
	step_list += signature(task, "1") + "\"launch\", {" + x_cord + ", " + y_cord + "}}\n";
	step += 1;
}

void save(std::string task, std::string nameOfSaveGame) {
	step_list += signature(task, "1") + "\"save\", \"" + nameOfSaveGame + "\"}\n";
	step += 1;
}

void idle(std::string task, std::string amount) {
	step_list += signature(task, "1") + "\"idle\", " + amount + "}\n";
	step += 1;
}

void rotate(std::string task, std::string x_cord, std::string y_cord, std::string times, std::string item, std::string orientation) {

	check_interact_distance(task, "1", x_cord, y_cord, item, orientation);

	if (std::stoi(times) == 3) {
		step_list += signature(task, "1") + "\"rotate\", {" + x_cord + ", " + y_cord + "}, " + "true}\n";
		step += 1;
	} else {
		for (int i = 0; i < std::stoi(times); i++) {
			step_list += signature(task, std::to_string(i + 1)) + "\"rotate\", {" + x_cord + ", " + y_cord + "}, " + "false}\n";
			step += 1;
		}
	}


}

double find_min_distance(float& new_x_cord, float& new_y_cord) {
	return std::pow(std::pow(std::abs(target_x_cord - new_x_cord), 2) + std::pow(std::abs(target_y_cord - new_y_cord), 2), 0.5);
}

std::vector<float> find_walk_location(float& min_x_edge, float& max_x_edge, float& min_y_edge, float& max_y_edge, const float& buffer, const float& max_distance) {

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
				} else if (new_x_cord < min_x_edge - not_to_close) {
					new_x_cord += delta_distance;
				} else {
					new_y_cord += delta_distance;
				}
			}
		} else if (new_y_cord > max_y_edge + not_to_close) {
			// bottom left
			target_x_cord = min_x_edge + buffer;
			target_y_cord = max_y_edge - buffer;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				if (new_x_cord < min_x_edge - not_to_close && new_y_cord > max_y_edge + not_to_close) {
					new_x_cord += delta_distance;
					new_y_cord -= delta_distance;
				} else if (new_x_cord < min_x_edge - not_to_close) {
					new_x_cord += delta_distance;
				} else {
					new_y_cord -= delta_distance;
				}
			}
		} else {
			// Mid left
			target_x_cord = min_x_edge + buffer;
			target_y_cord = new_y_cord;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				new_x_cord += delta_distance;
			}
		}
	} else if (new_x_cord > max_x_edge + not_to_close) {
		if (new_y_cord < min_y_edge - not_to_close) {
			// Top right
			target_x_cord = max_x_edge - buffer;
			target_y_cord = min_y_edge + buffer;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				if (new_x_cord > max_x_edge + not_to_close && new_y_cord < min_y_edge - not_to_close) {
					new_x_cord -= delta_distance;
					new_y_cord += delta_distance;
				} else if (new_x_cord > max_x_edge + not_to_close) {
					new_x_cord -= delta_distance;
				} else {
					new_y_cord += delta_distance;
				}
			}
		} else if (new_y_cord > max_y_edge + not_to_close) {
			// bottom right
			target_x_cord = max_x_edge - buffer;
			target_y_cord = max_y_edge - buffer;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				if (new_x_cord > max_x_edge + not_to_close && new_y_cord > max_y_edge + not_to_close) {
					new_x_cord -= delta_distance;
					new_y_cord -= delta_distance;
				} else if (new_x_cord > max_x_edge + not_to_close) {
					new_x_cord -= delta_distance;
				} else {
					new_y_cord -= delta_distance;
				}
			}
		} else {
			// Mid right
			target_x_cord = max_x_edge - buffer;
			target_y_cord = new_y_cord;

			while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
				new_x_cord -= delta_distance;
			}
		}
	} else if (new_y_cord < min_y_edge - not_to_close) {
		// Mid top
		target_x_cord = new_x_cord;
		target_y_cord = min_y_edge + buffer;

		while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
			new_y_cord += delta_distance;
		}
	} else if (new_y_cord > max_y_edge + not_to_close) {
		// Mid bottom
		target_x_cord = new_x_cord;
		target_y_cord = max_y_edge - buffer;

		while (find_min_distance(new_x_cord, new_y_cord) > max_distance) {
			new_y_cord -= delta_distance;
		}
	}

	return { new_x_cord, new_y_cord };
}

void check_construction_distance(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string building_name, std::string orientation) {
	static const float buffer = 0.45f; // this should be set correctly when you get a better understanding of how it is actually calculated in the game
	static const float max_distance = 10.0f;

	//should be altered when the can_place_entity in the factorio API is fixed
	float building_max_size = std::min(building_size_list.find(building_name)->second[0], building_size_list.find(building_name)->second[1]);

	float min_x_edge = std::stof(x_cord) - (building_max_size / 2);
	float max_x_edge = std::stof(x_cord) + (building_max_size / 2);
	float min_y_edge = std::stof(y_cord) - (building_max_size / 2);
	float max_y_edge = std::stof(y_cord) + (building_max_size / 2);

	std::vector<float> coordinates = find_walk_location(min_x_edge, max_x_edge, min_y_edge, max_y_edge, buffer, max_distance);

	if (player_x_cord != coordinates[0] || player_y_cord != coordinates[1]) {
		walk(task, action, std::to_string(coordinates[0]), std::to_string(coordinates[1]));
	}
}

void check_interact_distance(std::string task, std::string action, std::string x_cord, std::string y_cord, std::string building_name, std::string orientation) {
	if (building_name == "Wreck") {
		x_building_size = 1;
		y_building_size = 1;
	} else {
		x_building_size = building_size_list.find(building_name)->second[0];
		y_building_size = building_size_list.find(building_name)->second[1];
	}

	static const float buffer = 0.37f; // this should be set correctly when you get a better understanding of how it is actually calculated in the game
	static const float max_distance = 10.0f;
	float min_x_edge;
	float max_x_edge;

	float min_y_edge;
	float max_y_edge;

	if (orientation == "North" || orientation == "South") {
		min_x_edge = std::stof(x_cord) - (x_building_size / 2);
		max_x_edge = std::stof(x_cord) + (x_building_size / 2);
		min_y_edge = std::stof(y_cord) - (y_building_size / 2);
		max_y_edge = std::stof(y_cord) + (y_building_size / 2);
	} else {
		min_x_edge = std::stof(x_cord) - (y_building_size / 2);
		max_x_edge = std::stof(x_cord) + (y_building_size / 2);
		min_y_edge = std::stof(y_cord) - (x_building_size / 2);
		max_y_edge = std::stof(y_cord) + (x_building_size / 2);
	}

	std::vector<float> coordinates = find_walk_location(min_x_edge, max_x_edge, min_y_edge, max_y_edge, buffer, max_distance);

	if (player_x_cord != coordinates[0] || player_y_cord != coordinates[1]) {
		walk(task, action, std::to_string(coordinates[0]), std::to_string(coordinates[1]));
	}
}

void check_mining_distance(std::string task, std::string action, std::string x_cord, std::string y_cord) {
	static const float buffer = 0.50f; // this should be set correctly when you get a better understanding of how it is actually calculated in the game
	static const float max_distance = 2.7f;

	float min_x_edge = std::stof(x_cord) - 0.5f;
	float max_x_edge = std::stof(x_cord) + 0.5f;
	float min_y_edge = std::stof(y_cord) - 0.5f;
	float max_y_edge = std::stof(y_cord) + 0.5f;

	std::vector<float> coordinates = find_walk_location(min_x_edge, max_x_edge, min_y_edge, max_y_edge, buffer, max_distance);

	if (player_x_cord != coordinates[0] || player_y_cord != coordinates[1]) {
		walk(task, action, std::to_string(coordinates[0]), std::to_string(coordinates[1]));
	}
}

void find_coordinates(std::string& x_cord, std::string& y_cord, std::string& direction, std::string& building_size) {

	if (direction == "north" || direction == "North") {
		y_cord = std::to_string(std::stof(y_cord) - std::stof(building_size));

	} else if (direction == "south" || direction == "South") {
		y_cord = std::to_string(std::stof(y_cord) + std::stof(building_size));

	} else if (direction == "east" || direction == "East") {
		x_cord = std::to_string(std::stof(x_cord) + std::stof(building_size));

	} else if (direction == "west" || direction == "West") {
		x_cord = std::to_string(std::stof(x_cord) - std::stof(building_size));

	}
}

std::string end_tasks() {
	return step_list + "step[" + std::to_string(step) + "] = {\"break\"}\n\n" + "return step";
}

void clear_tasks() {
	step = 1;
	step_list = "local step = {}\n\n";
}

void reset_coordinates()
{
	player_x_cord = 0.0f;
	player_y_cord = 0.0f;
}

std::string convert_string(std::string input) {
	std::for_each(input.begin(), input.end(), [](char& c) {
		if (isspace(c)) {
			c = '-';
		}
		c = ::tolower(c);
		});
	return input;
}

void string_capitalized(std::string& string) {
	if (string != "") {
		string[0] = std::toupper(string[0]);
		for (int i = 1; string[i] != '\0'; ++i) {
			string[i] = tolower(string[i]);
		}
	}
}

bool is_number(const std::string& str) {
	for (auto s : str) {
		if (!std::isdigit(s)) {
			return false;
		}
	}

	return true;
}