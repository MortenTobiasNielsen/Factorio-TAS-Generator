#include "Functions.h"
#include <iostream>
#include <algorithm>



void walk(std::string x_cord, std::string y_cord) {
	task_list += "task[" + std::to_string(task) + "] = {\"walk\", {" + x_cord + ", " + y_cord + "}}\n";
	player_x_cord = std::stof(x_cord);
	player_y_cord = std::stof(y_cord);
	task += 1;
};

float find_min_distance(float &new_x_cord, float &new_y_cord) {
	
	float abs_x_cord = std::abs(target_x_cord - new_x_cord);
	float abs_y_cord = std::abs(target_y_cord - new_y_cord);

	float x_power = std::pow(abs_x_cord, 2);
	float y_power = std::pow(abs_y_cord, 2);

	float total_distance = std::pow(x_power + y_power, 0.5);

	
	return total_distance;

}

// You might need to split this into build and interact, given that e.g. a steam engine will have a further build distance than 10 if the steam engine is turned so the long side faces the player 
void check_build_interact_distance(std::string x_cord, std::string y_cord, std::string building_name, std::string building_direction) {
	target_x_cord = std::stof(x_cord);
	target_y_cord = std::stof(y_cord);
	
	x_building_size = building_size_list.find(building_name)->second[0];
	y_building_size = building_size_list.find(building_name)->second[1];

	static const float delta_distance = 0.1f;
	float min_x_edge;
	float max_x_edge;
	float min_y_edge;
	float max_y_edge;

	float buffer = 0.2;

	float new_x_cord = player_x_cord;
	float new_y_cord = player_y_cord;


	if (building_direction == "North" || building_direction == "South") {
		min_x_edge = target_x_cord - (x_building_size / 2);
		max_x_edge = target_x_cord + (x_building_size / 2);
		min_y_edge = target_y_cord - (y_building_size / 2);
		max_y_edge = target_y_cord + (y_building_size / 2);
	} else {
		min_x_edge = target_x_cord - (y_building_size / 2);
		max_x_edge = target_x_cord + (y_building_size / 2);
		min_y_edge = target_y_cord - (x_building_size / 2);
		max_y_edge = target_y_cord + (x_building_size / 2);
	}

	if (new_x_cord < min_x_edge) {
		if (new_y_cord < min_y_edge) {
			// Top left
			target_x_cord = min_x_edge - buffer;
			target_y_cord = min_y_edge - buffer;

			while (find_min_distance(new_x_cord, new_y_cord) < build_interact_distance) {
				if (new_x_cord < min_x_edge && new_y_cord < min_y_edge) {
					new_x_cord += delta_distance;
					new_y_cord += delta_distance;
				} else if (new_x_cord < min_x_edge) {
					new_x_cord += delta_distance;
				} else {
					new_y_cord += delta_distance;
				}
			}	
		} else if (new_y_cord > min_y_edge) {
			// bottom left
			target_x_cord = min_x_edge - buffer;
			target_y_cord = max_y_edge - buffer;

			while (find_min_distance(new_x_cord, new_y_cord) < build_interact_distance) {
				if (new_x_cord < min_x_edge && new_y_cord > min_y_edge) {
					new_x_cord += delta_distance;
					new_y_cord -= delta_distance;
				} else if (new_x_cord < min_x_edge) {
					new_x_cord += delta_distance;
				} else {
					new_y_cord -= delta_distance;
				}
			}
		} else {
			// Mid left
			while (find_min_distance(new_x_cord, new_y_cord) < build_interact_distance) {
				new_x_cord += delta_distance;
			}
		}
	}

	if (player_x_cord != new_x_cord || player_y_cord != new_y_cord) {
		walk(std::to_string(new_x_cord), std::to_string(new_y_cord));
	}	
}

void check_build_distance(std::string x_cord, std::string y_cord) {
	static const float delta_distance = 0.1f;

	static bool needs_new_location = false;

	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	
	static float new_x_cord = player_x_cord;
	static float new_y_cord = player_y_cord;

	static float x_cord_abs_diff = std::abs(player_x_cord - start_x_cord);
	static float y_cord_abs_diff = std::abs(player_y_cord - start_y_cord);

	static float x_cord_diff = player_x_cord - start_x_cord;
	static float y_cord_diff = player_y_cord - start_y_cord;

	needs_new_location = false;

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);

	new_x_cord = player_x_cord;
	new_y_cord = player_y_cord;

	x_cord_abs_diff = std::abs(player_x_cord - start_x_cord);
	y_cord_abs_diff = std::abs(player_y_cord - start_y_cord);

	x_cord_diff = player_x_cord - start_x_cord;
	y_cord_diff = player_y_cord - start_y_cord;

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

		x_cord_abs_diff = std::abs(new_x_cord - start_x_cord);
		y_cord_abs_diff = std::abs(new_y_cord - start_y_cord);

		x_cord_diff = new_x_cord - start_x_cord;
		y_cord_diff = new_y_cord - start_y_cord;
	}

	if (needs_new_location) {
		walk(std::to_string(new_x_cord), std::to_string(new_y_cord));
	}
};

void check_mining_distance(std::string x_cord, std::string y_cord) {
	static const float delta_distance = 0.1f;

	static bool needs_new_location = false;

	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);

	static float new_x_cord = player_x_cord;
	static float new_y_cord = player_y_cord;

	static float x_cord_abs_diff = std::abs(player_x_cord - start_x_cord);
	static float y_cord_abs_diff = std::abs(player_y_cord - start_y_cord);

	static float x_cord_diff = player_x_cord - start_x_cord;
	static float y_cord_diff = player_y_cord - start_y_cord;

	needs_new_location = false;

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);

	new_x_cord = player_x_cord;
	new_y_cord = player_y_cord;

	x_cord_abs_diff = std::abs(player_x_cord - start_x_cord);
	y_cord_abs_diff = std::abs(player_y_cord - start_y_cord);

	x_cord_diff = player_x_cord - start_x_cord;
	y_cord_diff = player_y_cord - start_y_cord;

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

		x_cord_abs_diff = std::abs(new_x_cord - start_x_cord);
		y_cord_abs_diff = std::abs(new_y_cord - start_y_cord);

		x_cord_diff = new_x_cord - start_x_cord;
		y_cord_diff = new_y_cord - start_y_cord;
	}

	if (needs_new_location) {
		walk(std::to_string(new_x_cord), std::to_string(new_y_cord));
	}
};

void craft(std::string amount, std::string item) {
	task_list += "task[" + std::to_string(task) + "] = {\"craft\", " + amount + ", \"" + item + "\"}\n";
	task += 1;
};

void build(std::string x_cord, std::string y_cord, std::string item, std::string direction) {
	//check_build_distance(x_cord, y_cord);

	check_build_interact_distance(x_cord, y_cord, item, direction);

	task_list += "task[" + std::to_string(task) + "] = {\"build\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + direction + "}\n";
	task += 1;
};

void mining(std::string x_cord, std::string y_cord, std::string times) {
	check_mining_distance(x_cord, y_cord);
	for (int i = 0; i < std::stoi(times); i++) {
		task_list += "task[" + std::to_string(task) + "] = {\"mine\", {" + x_cord + ", " + y_cord + "}}\n";
		task += 1;
	}
}

void take(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"take\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + amount + ", " + from + "}\n";
	task += 1;
}

void put(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string into) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"put\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + amount + ", " + into + "}\n";
	task += 1;
}

void recipe(std::string x_cord, std::string y_cord, std::string item) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"recipe\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\"}\n";
	task += 1;
}

void row_recipe(std::string x_cord, std::string y_cord, std::string item, std::string direction_to_build, std::string building_size, std::string amount_of_buildings) {
	
	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	static int building_size_int = std::stoi(building_size);
	static int number_of_buildings_int = std::stoi(amount_of_buildings);

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);
	building_size_int = std::stoi(building_size);
	number_of_buildings_int = std::stoi(amount_of_buildings);
	
	if (direction_to_build == "north") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			recipe(x_cord, std::to_string(start_y_cord - i * building_size_int), item);
		}
	} else if (direction_to_build == "south") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			recipe(x_cord, std::to_string(start_y_cord + i * building_size_int), item);
		}
	} else if (direction_to_build == "east") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			recipe(std::to_string(start_x_cord + i * building_size_int), y_cord, item);
		}
	} else if (direction_to_build == "west") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			recipe(std::to_string(start_x_cord - i * building_size_int), y_cord, item);
		}
	}

}

void tech(std::string tech_to_research) {
	task_list += "task[" + std::to_string(task) + "] = {\"tech\", \"" + tech_to_research + "\"}\n";
	task += 1;
}

void speed(std::string speed) {
	task_list += "task[" + std::to_string(task) + "] = {\"speed\", " + speed + "}\n";
	task += 1;
}
void stop(std::string speed) {
	task_list += "task[" + std::to_string(task) + "] = {\"stop\", " + speed + "}\n";
	task += 1;
}

void launch(std::string x_cord, std::string y_cord) {
	task_list += "task[" + std::to_string(task) + "] = {\"launch\", {" + x_cord + ", " + y_cord + "}}\n";
	task += 1;
}

void idle(std::string amount) {
	task_list += "task[" + std::to_string(task) + "] = {\"idle\", " + amount + "}\n";
	task += 1;
}

void limit(std::string x_cord, std::string y_cord, std::string amount, std::string from) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"limit\", {" + x_cord + ", " + y_cord + "}, " + amount + ", " + from + "}\n";
	task += 1;
}

void limit_row(std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string direction_to_build, std::string number_of_buildings, std::string building_size) {
	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	static int building_size_int = std::stoi(building_size);
	static int number_of_buildings_int = std::stoi(number_of_buildings);

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);
	building_size_int = std::stoi(building_size);
	number_of_buildings_int = std::stoi(number_of_buildings);

	if (direction_to_build == "north") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			limit(x_cord, std::to_string(start_y_cord - i * building_size_int), amount, from);
		}
	} else if (direction_to_build == "south") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			limit(x_cord, std::to_string(start_y_cord + i * building_size_int), amount, from);
		}
	} else if (direction_to_build == "east") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			limit(std::to_string(start_x_cord + i * building_size_int), y_cord, amount, from);
		}
	} else if (direction_to_build == "west") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			limit(std::to_string(start_x_cord - i * building_size_int), y_cord, amount, from);
		}
	}
}

void priority(std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"priority\", {" + x_cord + ", " + y_cord + "}, \"" + priority_in + "\", \"" + priority_out + "\"}\n";
	task += 1;
}

void priority_row(std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string direction_to_build, std::string number_of_buildings, std::string building_size) {
	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	static int building_size_int = std::stoi(building_size);
	static int number_of_buildings_int = std::stoi(number_of_buildings);

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);
	building_size_int = std::stoi(building_size);
	number_of_buildings_int = std::stoi(number_of_buildings);

	if (direction_to_build == "north") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			priority(x_cord, std::to_string(start_y_cord - i * building_size_int), priority_in, priority_out);
		}
	} else if (direction_to_build == "south") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			priority(x_cord, std::to_string(start_y_cord + i * building_size_int), priority_in, priority_out);
		}
	} else if (direction_to_build == "east") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			priority(std::to_string(start_x_cord + i * building_size_int), y_cord, priority_in, priority_out);
		}
	} else if (direction_to_build == "west") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			priority(std::to_string(start_x_cord - i * building_size_int), y_cord, priority_in, priority_out);
		}
	}
}

void filter(std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"filter\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\", " + units + ",  \"" + type + "\"}\n";
	task += 1;
}

void filter_row(std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string direction_to_build, std::string number_of_buildings, std::string building_size) {
	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	static int building_size_int = std::stoi(building_size);
	static int number_of_buildings_int = std::stoi(number_of_buildings);

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);
	building_size_int = std::stoi(building_size);
	number_of_buildings_int = std::stoi(number_of_buildings);

	if (direction_to_build == "north") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			filter(x_cord, std::to_string(start_y_cord - i * building_size_int), item, units, type);
		}
	} else if (direction_to_build == "south") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			filter(x_cord, std::to_string(start_y_cord + i * building_size_int), item, units, type);
		}
	} else if (direction_to_build == "east") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			filter(std::to_string(start_x_cord + i * building_size_int), y_cord, item, units, type);
		}
	} else if (direction_to_build == "west") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			filter(std::to_string(start_x_cord - i * building_size_int), y_cord, item, units, type);
		}
	}
}

void drop(std::string x_cord, std::string y_cord, std::string item) {
	check_build_distance(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"drop\", {" + x_cord + ", " + y_cord + "}, \"" + item + "\"}\n";
	task += 1;
}

void drop_row(std::string x_cord, std::string y_cord, std::string item, std::string direction_to_build, std::string number_of_buildings, std::string building_size) {
	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	static int building_size_int = std::stoi(building_size);
	static int number_of_buildings_int = std::stoi(number_of_buildings);

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);
	building_size_int = std::stoi(building_size);
	number_of_buildings_int = std::stoi(number_of_buildings);

	if (direction_to_build == "north") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			drop(x_cord, std::to_string(start_y_cord - i * building_size_int), item);
		}
	} else if (direction_to_build == "south") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			drop(x_cord, std::to_string(start_y_cord + i * building_size_int), item);
		}
	} else if (direction_to_build == "east") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			drop(std::to_string(start_x_cord + i * building_size_int), y_cord, item);
		}
	} else if (direction_to_build == "west") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			drop(std::to_string(start_x_cord - i * building_size_int), y_cord, item);
		}
	}
}

void pick(std::string x_cord, std::string y_cord) {
	walk(x_cord, y_cord);
	task_list += "task[" + std::to_string(task) + "] = {\"pick\", {" + x_cord + ", " + y_cord + "}}\n";
	task += 1;
}

void pick_row(std::string x_cord, std::string y_cord, std::string direction_to_build, std::string number_of_buildings, std::string building_size) {
	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	static int building_size_int = std::stoi(building_size);
	static int number_of_buildings_int = std::stoi(number_of_buildings);

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);
	building_size_int = std::stoi(building_size);
	number_of_buildings_int = std::stoi(number_of_buildings);

	if (direction_to_build == "north") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			pick(x_cord, std::to_string(start_y_cord - i * building_size_int));
		}
	} else if (direction_to_build == "south") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			pick(x_cord, std::to_string(start_y_cord + i * building_size_int));
		}
	} else if (direction_to_build == "east") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			pick(std::to_string(start_x_cord + i * building_size_int), y_cord);
		}
	} else if (direction_to_build == "west") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			pick(std::to_string(start_x_cord - i * building_size_int), y_cord);
		}
	}
}

void rotate(std::string x_cord, std::string y_cord, std::string times) {
	check_build_distance(x_cord, y_cord);
	for (int i = 0; i < std::stoi(times); i++) {
		task_list += "task[" + std::to_string(task) + "] = {\"rotate\", {" + x_cord + ", " + y_cord + "}}\n";
		task += 1;
	}
}

void build_row_of_buildings(std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string direction_to_build, std::string number_of_buildings, std::string building_size) {

	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	static int building_size_int = std::stoi(building_size);
	static int number_of_buildings_int = std::stoi(number_of_buildings);

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);
	building_size_int = std::stoi(building_size);
	number_of_buildings_int = std::stoi(number_of_buildings);

	if (direction == "north") {
		direction = build_directions.north;
	} else if (direction == "south") {
		direction = build_directions.south;
	} else if (direction == "east") {
		direction = build_directions.east;
	} else if (direction == "west") {
		direction = build_directions.west;
	} else {
		return;
	}

	if (direction_to_build == "north") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			build(x_cord, std::to_string(start_y_cord - i * building_size_int), item, direction);
		}
	} else if (direction_to_build == "south") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			build(x_cord, std::to_string(start_y_cord + i * building_size_int), item, direction);
		}
	} else if (direction_to_build == "east") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			build(std::to_string(start_x_cord + i * building_size_int), y_cord, item, direction);
		}
	} else if (direction_to_build == "west") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			build(std::to_string(start_x_cord - i * building_size_int), y_cord, item, direction);
		}
	}
}

void row_take(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction_to_take, std::string number_of_buildings, std::string building_size) {
	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	static int building_size_int = std::stoi(building_size);
	static int number_of_buildings_int = std::stoi(number_of_buildings);

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);
	building_size_int = std::stoi(building_size);
	number_of_buildings_int = std::stoi(number_of_buildings);

	if (direction_to_take == "north") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			take(x_cord, std::to_string(start_y_cord - i * building_size_int), amount, item, from);
		}
	} else if (direction_to_take == "south") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			take(x_cord, std::to_string(start_y_cord + i * building_size_int), amount, item, from);
		}
	} else if (direction_to_take == "east") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			take(std::to_string(start_x_cord + i * building_size_int), y_cord, amount, item, from);
		}
	} else if (direction_to_take == "west") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			take(std::to_string(start_x_cord - i * building_size_int), y_cord, amount, item, from);
		}
	}
}

void row_put(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction_to_take, std::string number_of_buildings, std::string building_size) {
	static float start_x_cord = std::stof(x_cord);
	static float start_y_cord = std::stof(y_cord);
	static int building_size_int = std::stoi(building_size);
	static int number_of_buildings_int = std::stoi(number_of_buildings);

	start_x_cord = std::stof(x_cord);
	start_y_cord = std::stof(y_cord);
	building_size_int = std::stoi(building_size);
	number_of_buildings_int = std::stoi(number_of_buildings);

	if (direction_to_take == "north") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			put(x_cord, std::to_string(start_y_cord - i * building_size_int), amount, item, from);
		}
	} else if (direction_to_take == "south") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			put(x_cord, std::to_string(start_y_cord + i * building_size_int), amount, item, from);
		}
	} else if (direction_to_take == "east") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			put(std::to_string(start_x_cord + i * building_size_int), y_cord, amount, item, from);
		}
	} else if (direction_to_take == "west") {
		for (int i = 0; i < number_of_buildings_int; i++) {
			put(std::to_string(start_x_cord - i * building_size_int), y_cord, amount, item, from);
		}
	}
}

std::string end_tasks() {
	return task_list + "task[" + std::to_string(task) + "] = {\"break\"}\n\n" + "return task";
}

void clear_tasks() {
	task = 1;
	task_list = "local task = {}\n\n";
	player_x_cord = 0.0f;
	player_y_cord = 0.0f;
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

void string_capitalized(std::string& string) {
	if (string != "") {
		string[0] = std::toupper(string[0]);
		for (int i = 1; string[i] != '\0'; ++i) {
			string[i] = tolower(string[i]);
		}
	}
};