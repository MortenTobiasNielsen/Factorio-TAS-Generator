#include "Functions.h"
#include <iostream>
#include <algorithm>


void walk(float x_cord, float y_cord) {
	task_list += "task[" + std::to_string(task) + "] = {\"walk\", {" + std::to_string(x_cord) + ", " + std::to_string(y_cord) + "}}\n";
	player_x_cord = x_cord;
	player_y_cord = y_cord;
	task += 1;
};

void check_build_distance(float x_cord, float y_cord) {
	static const float delta_distance = 0.1f;

	static bool needs_new_location = false;

	static float new_x_cord = player_x_cord;
	static float new_y_cord = player_y_cord;

	static float x_cord_abs_diff = std::abs(player_x_cord - x_cord);
	static float y_cord_abs_diff = std::abs(player_y_cord - y_cord);

	static float x_cord_diff = player_x_cord - x_cord;
	static float y_cord_diff = player_y_cord - y_cord;

	needs_new_location = false;

	new_x_cord = player_x_cord;
	new_y_cord = player_y_cord;

	x_cord_abs_diff = std::abs(player_x_cord - x_cord);
	y_cord_abs_diff = std::abs(player_y_cord - y_cord);

	x_cord_diff = player_x_cord - x_cord;
	y_cord_diff = player_y_cord - y_cord;

	while (true) {
		if (x_cord_abs_diff <= build_distance.one && y_cord_abs_diff <= build_distance.five ||
			x_cord_abs_diff <= build_distance.two && y_cord_abs_diff <= build_distance.four ||
			x_cord_abs_diff <= build_distance.three && y_cord_abs_diff <= build_distance.three ||
			x_cord_abs_diff <= build_distance.four && y_cord_abs_diff <= build_distance.two ||
			x_cord_abs_diff <= build_distance.five && y_cord_abs_diff <= build_distance.one) {

			std::cout << "new build walk\n";
			break;
		}

		needs_new_location = true;

		// The delta from current location to build location is positive
		if (x_cord_diff > build_distance.one) {
			if (y_cord_diff > build_distance.five) {
				new_x_cord -= delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.five) {
				new_x_cord -= delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord -= delta_distance;
			}
		} else if (x_cord_diff > build_distance.two) {
			if (y_cord_diff > build_distance.four) {
				new_x_cord -= delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.four) {
				new_x_cord -= delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord -= delta_distance;
			}
		} else if (x_cord_diff > build_distance.three) {
			if (y_cord_diff > build_distance.three) {
				new_x_cord -= delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.three) {
				new_x_cord -= delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord -= delta_distance;
			}
		} else if (x_cord_diff > build_distance.four) {
			if (y_cord_diff > build_distance.two) {
				new_x_cord -= delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.two) {
				new_x_cord -= delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord -= delta_distance;
			}
		} else if (x_cord_diff > build_distance.five) {
			if (y_cord_diff > build_distance.one) {
				new_x_cord -= delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.one) {
				new_x_cord -= delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord -= delta_distance;
			}
		} else if (x_cord_diff < build_distance.five && x_cord_diff > 0) {
			if (y_cord_diff > build_distance.one) {
				new_y_cord -= delta_distance;
			} else {
				new_y_cord += delta_distance;
			}

			// The delta from current location to build location is negative
		} else if (x_cord_diff < -build_distance.one) {
			if (y_cord_diff > build_distance.five) {
				new_x_cord += delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.five) {
				new_x_cord += delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord += delta_distance;
			}
		} else if (x_cord_diff < -build_distance.two) {
			if (y_cord_diff > build_distance.four) {
				new_x_cord += delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.four) {
				new_x_cord += delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord += delta_distance;
			}
		} else if (x_cord_diff < -build_distance.three) {
			if (y_cord_diff > build_distance.three) {
				new_x_cord += delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.three) {
				new_x_cord += delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord += delta_distance;
			}
		} else if (x_cord_diff < -build_distance.four) {
			if (y_cord_diff > build_distance.two) {
				new_x_cord += delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.two) {
				new_x_cord += delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord += delta_distance;
			}
		} else if (x_cord_diff < -build_distance.five) {
			if (y_cord_diff > build_distance.one) {
				new_x_cord += delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -build_distance.one) {
				new_x_cord += delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord += delta_distance;
			}
		} else if (x_cord_diff < build_distance.five) {
			if (y_cord_diff > build_distance.one) {
				new_y_cord -= delta_distance;
			} else {
				new_y_cord += delta_distance;
			}
		}

		x_cord_abs_diff = std::abs(new_x_cord - x_cord);
		y_cord_abs_diff = std::abs(new_y_cord - y_cord);

		x_cord_diff = new_x_cord - x_cord;
		y_cord_diff = new_y_cord - y_cord;
	}

	if (needs_new_location) {
		walk(new_x_cord, new_y_cord);
	}
};

void check_mining_distance(float x_cord, float y_cord) {
	static const float delta_distance = 0.1f;

	static bool needs_new_location = false;

	static float new_x_cord = player_x_cord;
	static float new_y_cord = player_y_cord;

	static float x_cord_abs_diff = std::abs(player_x_cord - x_cord);
	static float y_cord_abs_diff = std::abs(player_y_cord - y_cord);

	static float x_cord_diff = player_x_cord - x_cord;
	static float y_cord_diff = player_y_cord - y_cord;

	needs_new_location = false;

	new_x_cord = player_x_cord;
	new_y_cord = player_y_cord;

	x_cord_abs_diff = std::abs(player_x_cord - x_cord);
	y_cord_abs_diff = std::abs(player_y_cord - y_cord);

	x_cord_diff = player_x_cord - x_cord;
	y_cord_diff = player_y_cord - y_cord;

	while (true) {
		if (x_cord_abs_diff <= mining_distance.one && y_cord_abs_diff <= mining_distance.three ||
			x_cord_abs_diff <= mining_distance.two && y_cord_abs_diff <= mining_distance.two ||
			x_cord_abs_diff <= mining_distance.three && y_cord_abs_diff <= mining_distance.one) {

			std::cout << "new mining walk\n";
			break;
		}

		needs_new_location = true;

		// The delta from current location to build location is positive
		if (x_cord_diff > mining_distance.one) {
			if (y_cord_diff > mining_distance.three) {
				new_x_cord -= delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -mining_distance.three) {
				new_x_cord -= delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord -= delta_distance;
			}
		} else if (x_cord_diff > mining_distance.two) {
			if (y_cord_diff > mining_distance.two) {
				new_x_cord -= delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -mining_distance.two) {
				new_x_cord -= delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord -= delta_distance;
			}
		} else if (x_cord_diff > mining_distance.three) {
			if (y_cord_diff > mining_distance.one) {
				new_x_cord -= delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -mining_distance.one) {
				new_x_cord -= delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord -= delta_distance;
			}
		} else if (x_cord_diff < mining_distance.three && x_cord_diff > 0) {
			if (y_cord_diff > mining_distance.one) {
				new_y_cord -= delta_distance;
			} else {
				new_y_cord += delta_distance;
			}

			// The delta from current location to mining location is negative
		} else if (x_cord_diff < -mining_distance.one) {
			if (y_cord_diff > mining_distance.three) {
				new_x_cord += delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -mining_distance.three) {
				new_x_cord += delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord += delta_distance;
			}
		} else if (x_cord_diff < -mining_distance.two) {
			if (y_cord_diff > mining_distance.two) {
				new_x_cord += delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -mining_distance.two) {
				new_x_cord += delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord += delta_distance;
			}
		} else if (x_cord_diff < -mining_distance.three) {
			if (y_cord_diff > mining_distance.one) {
				new_x_cord += delta_distance;
				new_y_cord -= delta_distance;
			} else if (y_cord_diff < -mining_distance.one) {
				new_x_cord += delta_distance;
				new_y_cord += delta_distance;
			} else {
				new_x_cord += delta_distance;
			}
		} else if (x_cord_diff < mining_distance.three) {
			if (y_cord_diff > mining_distance.one) {
				new_y_cord -= delta_distance;
			} else {
				new_y_cord += delta_distance;
			}
		}

		x_cord_abs_diff = std::abs(new_x_cord - x_cord);
		y_cord_abs_diff = std::abs(new_y_cord - y_cord);

		x_cord_diff = new_x_cord - x_cord;
		y_cord_diff = new_y_cord - y_cord;
	}

	if (needs_new_location) {
		walk(new_x_cord, new_y_cord);
	}
};

void craft(int amount, std::string item) {
	task_list += "task[" + std::to_string(task) + "] = {\"craft\", " + std::to_string(amount) + ", \"" + item + "\"}\n";
	task += 1;
};

void build(float x_cord, float y_cord, std::string item, std::string direction) {
	check_build_distance(x_cord, y_cord);

	task_list += "task[" + std::to_string(task) + "] = {\"build\", {" + std::to_string(x_cord) + ", " + std::to_string(y_cord) + "}, \"" + item + "\", " + direction + "}\n";
	task += 1;
};

void fill_fuel(float x_cord, float y_cord, int amount, std::string fuel_type) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"put\", {" + std::to_string(x_cord) + ", " + std::to_string(y_cord) + "}, \"" + fuel_type + "\", " + std::to_string(amount) + ", defines.inventory.fuel}\n";
	task += 1;
};



void mining(float x_cord, float y_cord, int times) {
	check_mining_distance(x_cord, y_cord);
	for (int i = 0; i < times; i++) {
		task_list += "task[" + std::to_string(task) + "] = {\"mine\", {" + std::to_string(x_cord) + ", " + std::to_string(y_cord) + "}}\n";
		task += 1;
	}
}

void take(float x_cord, float y_cord, int amount, std::string item, std::string from) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"take\", {" + std::to_string(x_cord) + ", " + std::to_string(y_cord) + "}, \"" + item + "\", " + std::to_string(amount) + ", " + from + "}\n";
	task += 1;
}

void put(float x_cord, float y_cord, int amount, std::string item, std::string into) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"put\", {" + std::to_string(x_cord) + ", " + std::to_string(y_cord) + "}, \"" + item + "\", " + std::to_string(amount) + ", " + into + "}\n";
	task += 1;
}

void recipe(float x_cord, float y_cord, std::string item) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"recipe\", {" + std::to_string(x_cord) + ", " + std::to_string(y_cord) + "}, \"" + item + "\"}\n";
	task += 1;
}

void tech(std::string tech_to_research) {
	task_list += "task[" + std::to_string(task) + "] = {\"tech\", \"" + tech_to_research + "\"}\n";
	task += 1;
}

void speed(float speed) {
	task_list += "task[" + std::to_string(task) + "] = {\"speed\", " + std::to_string(speed) + "}\n";
	task += 1;
};

void rotate(float x_cord, float y_cord, int times) {
	check_build_distance(x_cord, y_cord);
	for (int i = 0; i < times; i++) {
		task_list += "task[" + std::to_string(task) + "] = {\"rotate\", {" + std::to_string(x_cord) + ", " + std::to_string(y_cord) + "}}\n";
		task += 1;
	}
}

void build_row_of_buildings(float x_cord, float y_cord, std::string item, std::string direction, std::string direction_to_build, int number_of_buildings, int building_size) {

	if (direction_to_build == "north") {
		for (int i = 0; i < number_of_buildings; i++) {
			build(x_cord, y_cord - i * building_size, item, direction);
		}
	} else if (direction_to_build == "south") {
		for (int i = 0; i < number_of_buildings; i++) {
			build(x_cord, y_cord + i * building_size, item, direction);
		}
	} else if (direction_to_build == "east") {
		for (int i = 0; i < number_of_buildings; i++) {
			build(x_cord + i * building_size, y_cord, item, direction);
		}
	} else if (direction_to_build == "west") {
		for (int i = 0; i < number_of_buildings; i++) {
			build(x_cord - i * building_size, y_cord, item, direction);
		}
	}
}

void row_fill_fuel(float x_cord, float y_cord, int amount, std::string fuel_type, std::string direction_to_fuel, int number_of_buildings, int building_size) {
	if (direction_to_fuel == "north") {
		for (int i = 0; i < number_of_buildings; i++) {
			fill_fuel(x_cord, y_cord - i * building_size, amount, fuel_type);
		}
	} else if (direction_to_fuel == "south") {
		for (int i = 0; i < number_of_buildings; i++) {
			fill_fuel(x_cord, y_cord + i * building_size, amount, fuel_type);
		}
	} else if (direction_to_fuel == "east") {
		for (int i = 0; i < number_of_buildings; i++) {
			fill_fuel(x_cord + i * building_size, y_cord, amount, fuel_type);
		}
	} else if (direction_to_fuel == "west") {
		for (int i = 0; i < number_of_buildings; i++) {
			fill_fuel(x_cord - i * building_size, y_cord, amount, fuel_type);
		}
	}
}

void row_empty_fill_fuel(float x_cord, float y_cord, int amount, std::string item_to_take, std::string from, std::string fuel_type, std::string direction_to_fuel, int number_of_buildings, int building_size) {
	if (direction_to_fuel == "north") {
		for (int i = 0; i < number_of_buildings; i++) {
			take(x_cord, y_cord - i * building_size, -1, item_to_take, from);
			fill_fuel(x_cord, y_cord - i * building_size, amount, fuel_type);
		}
	} else if (direction_to_fuel == "south") {
		for (int i = 0; i < number_of_buildings; i++) {
			take(x_cord, y_cord + i * building_size, -1, item_to_take, from);
			fill_fuel(x_cord, y_cord + i * building_size, amount, fuel_type);
		}
	} else if (direction_to_fuel == "east") {
		for (int i = 0; i < number_of_buildings; i++) {
			take(x_cord + i * building_size, y_cord, -1, item_to_take, from);
			fill_fuel(x_cord + i * building_size, y_cord, amount, fuel_type);
		}
	} else if (direction_to_fuel == "west") {
		for (int i = 0; i < number_of_buildings; i++) {
			take(x_cord - i * building_size, y_cord, -1, item_to_take, from);
			fill_fuel(x_cord - i * building_size, y_cord, amount, fuel_type);
		}
	}
}

void row_take(float x_cord, float y_cord, int amount, std::string item, std::string from, std::string direction_to_take, int number_of_buildings, int building_size) {
	if (direction_to_take == "north") {
		for (int i = 0; i < number_of_buildings; i++) {
			take(x_cord, y_cord - i * building_size, amount, item, from);
		}
	} else if (direction_to_take == "south") {
		for (int i = 0; i < number_of_buildings; i++) {
			take(x_cord, y_cord + i * building_size, amount, item, from);
		}
	} else if (direction_to_take == "east") {
		for (int i = 0; i < number_of_buildings; i++) {
			take(x_cord + i * building_size, y_cord, amount, item, from);
		}
	} else if (direction_to_take == "west") {
		for (int i = 0; i < number_of_buildings; i++) {
			take(x_cord - i * building_size, y_cord, amount, item, from);
		}
	}
}

std::string end_tasks() {
	return task_list + "task[" + std::to_string(task) + "] = {\"break\"}\n\n" + "return task";
};

std::string convert_string(std::string input) {
	std::for_each(input.begin(), input.end(), [](char& c) {
		if (isspace(c)) {
			c = '-';
		}
		c = ::tolower(c);
	});
	return input;
}
bool isInteger(const std::string& s) {
	if (s.empty() || !isdigit(s[0])) return false;

	char* p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}
bool check_item(const std::string &item, const std::vector<std::string> &all_items) {
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		if (item == *it) {
			return true;
		}
	}
	return false;
};