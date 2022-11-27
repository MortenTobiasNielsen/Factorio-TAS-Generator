#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

enum TaskName
{
	e_start = 1, e_stop, e_build, e_craft, e_game_speed, e_pause, e_save, e_recipe, e_limit, e_filter, e_rotate, e_priority, e_put, e_take, e_mine, e_launch, e_walk, e_tech, e_drop, e_pick_up, e_idle
};

std::map<string, TaskName> TaskNames = {{"Start", e_start}, {"Stop", e_stop}, {"Build", e_build}, {"Craft", e_craft}, {"Game Speed", e_game_speed}, {"Pause", e_pause}, {"Save", e_save},
	{"Recipe", e_recipe}, {"Limit", e_limit}, {"Filter", e_filter}, {"Rotate", e_rotate}, {"Priority", e_priority}, {"Put", e_put}, {"Take", e_take}, {"Mine", e_mine}, {"Launch", e_launch},
	{"Walk", e_walk}, {"Tech", e_tech}, {"Drop", e_drop}, {"Pick up", e_pick_up}, {"Idle", e_idle}};