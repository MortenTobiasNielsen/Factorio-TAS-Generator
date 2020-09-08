#pragma once

#include <string>
#include "utils.h"

static int task = 1;
static std::string task_list = "local task = {}\n\n";
static float player_x_cord = 0.0f;
static float player_y_cord = 0.0f;

const static build_distance_struct build_distance;
const static mining_distance_struct mining_distance;

void walk(float x_cord, float y_cord);

void check_build_distance(float x_cord, float y_cord);

void check_mining_distance(float x_cord, float y_cord);

void craft(int amount, std::string item);

void build(float x_cord, float y_cord, std::string item, std::string direction);

void fill_fuel(float x_cord, float y_cord, int amount, std::string fuel_type);

void mining(float x_cord, float y_cord, int times = 1);

void take(float x_cord, float y_cord, int amount, std::string item, std::string from);

void put(float x_cord, float y_cord, int amount, std::string item, std::string into);

void recipe(float x_cord, float y_cord, std::string item);

void tech(std::string tech_to_research);

void speed(float speed);

void rotate(float x_cord, float y_cord, int times);

void build_row_of_buildings(float x_cord, float y_cord, std::string item, std::string direction, std::string direction_to_build, int number_of_buildings, int building_size);

void row_fill_fuel(float x_cord, float y_cord, int amount, std::string fuel_type, std::string direction_to_fuel, int number_of_buildings, int building_size);

void row_empty_fill_fuel(float x_cord, float y_cord, int amount, std::string item_to_take, std::string from, std::string fuel_type, std::string direction_to_fuel, int number_of_buildings, int building_size);

void row_take(float x_cord, float y_cord, int amount, std::string item, std::string from, std::string direction_to_take, int number_of_buildings, int building_size);

std::string end_tasks();

std::string convert_string(std::string input);

bool check_item(const std::string &item, const std::vector<std::string> &all_items);
