#pragma once

#include <string>
#include "utils.h"

static int task = 1;
static std::string task_list = "local task = {}\n\n";
static float player_x_cord = 0.0f;
static float player_y_cord = 0.0f;

const static build_distance_struct build_distance;
const static mining_distance_struct mining_distance;

void walk(std::string x_cord, std::string y_cord);

void check_build_distance(std::string x_cord, std::string y_cord);

void check_mining_distance(std::string x_cord, std::string y_cord);

void craft(std::string amount, std::string item);

void build(std::string x_cord, std::string y_cord, std::string item, std::string direction);

void mining(std::string x_cord, std::string y_cord, std::string times = "1");

void take(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from);

void put(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string into);

void recipe(std::string x_cord, std::string y_cord, std::string item);

void row_recipe(std::string x_cord, std::string y_cord, std::string item, std::string direction_to_build, std::string building_size, std::string amount_of_buildings);

void tech(std::string tech_to_research);

void speed(std::string speed);

void stop(std::string speed);

void limit(std::string x_cord, std::string y_cord, std::string amount, std::string from);

void limit_row(std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string direction_to_build, std::string number_of_buildings, std::string building_size);

void priority(std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out);

void priority_row(std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string direction_to_build, std::string number_of_buildings, std::string building_size);

void filter(std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type);

void filter_row(std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string direction_to_build, std::string number_of_buildings, std::string building_size);

void drop(std::string x_cord, std::string y_cord, std::string item);

void drop_row(std::string x_cord, std::string y_cord, std::string item, std::string direction_to_build, std::string number_of_buildings, std::string building_size);

void pick(std::string x_cord, std::string y_cord);

void pick_row(std::string x_cord, std::string y_cord, std::string direction_to_build, std::string number_of_buildings, std::string building_size);

void rotate(std::string x_cord, std::string y_cord, std::string times);

void build_row_of_buildings(std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string direction_to_build, std::string number_of_buildings, std::string building_size);

void row_take(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction_to_take, std::string number_of_buildings, std::string building_size);

void row_put(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction_to_take, std::string number_of_buildings, std::string building_size);

std::string end_tasks();

void clear_tasks();

std::string convert_string(std::string input);

void string_capitalized(std::string &string);
