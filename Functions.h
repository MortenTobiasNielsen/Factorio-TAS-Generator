#pragma once

#include <string>
#include "utils.h"

static int task = 1;
static std::string task_list = "local task = {}\n\n";
static float player_x_cord = 0.0f;
static float player_y_cord = 0.0f;
static float target_x_cord = 0.0f;
static float target_y_cord = 0.0f;
static float x_building_size = 0;
static float y_building_size = 0;

const static int build_interact_distance = 10;

const static build_distance_struct build_distance;
const static mining_distance_struct mining_distance;

void walk(std::string x_cord, std::string y_cord);

void mining(std::string x_cord, std::string y_cord, std::string times, std::string building_name, std::string orientation, bool is_building);

void craft(std::string amount, std::string item);

void build(std::string x_cord, std::string y_cord, std::string item, std::string orientation);
void row_build(std::string x_cord, std::string y_cord, std::string item, std::string orientation, std::string direction, std::string number_of_buildings, std::string building_size);

void take(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string building, std::string orientation);
void row_take(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

void put(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string into, std::string building, std::string orientation);
void row_put(std::string x_cord, std::string y_cord, std::string amount, std::string item, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

void recipe(std::string x_cord, std::string y_cord, std::string item, std::string building, std::string orientation);
void row_recipe(std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string building_size, std::string number_of_buildings, std::string building, std::string orientation);

void limit(std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string building, std::string orientation);
void row_limit(std::string x_cord, std::string y_cord, std::string amount, std::string from, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

void priority(std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string building, std::string orientation);
void row_priority(std::string x_cord, std::string y_cord, std::string priority_in, std::string priority_out, std::string direction, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

void filter(std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string building, std::string orientation);
void row_filter(std::string x_cord, std::string y_cord, std::string item, std::string units, std::string type, std::string direction_to_build, std::string number_of_buildings, std::string building_size, std::string building, std::string orientation);

void drop(std::string x_cord, std::string y_cord, std::string item);
void row_drop(std::string x_cord, std::string y_cord, std::string item, std::string direction, std::string number_of_buildings, std::string building_size);

void pick(std::string x_cord, std::string y_cord);
void row_pick(std::string x_cord, std::string y_cord, std::string direction, std::string number_of_buildings, std::string building_size);

void tech(std::string tech_to_research);

void speed(std::string speed);

void stop(std::string speed);

void launch(std::string x_cord, std::string y_cord);

void idle(std::string amount);

void rotate(std::string x_cord, std::string y_cord, std::string times, std::string item, std::string orientation);

std::string end_tasks();

void clear_tasks();

std::string convert_string(std::string input);

void string_capitalized(std::string &string);

double find_min_distance(float& new_x_cord, float& new_y_cord);

std::vector<float> find_walk_location(float& min_x_edge, float& max_x_edge, float& min_y_edge, float& max_y_edge, const float& buffer, float& max_distance);

void check_construction_distance(std::string x_cord, std::string y_cord, std::string building_name, std::string building_direction);

void check_interact_distance(std::string x_cord, std::string y_cord, std::string building_name, std::string orientation);

void check_mining_distance(std::string x_cord, std::string y_cord);

void find_coordinates(std::string& x_cord, std::string& y_cord, std::string& direction, std::string& building_size);