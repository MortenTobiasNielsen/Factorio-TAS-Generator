#pragma once

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

/// <summary>
/// Enumaration of all step types
/// </summary>
enum StepType
{
	e_stop = 1, e_build, e_craft, e_game_speed, e_pause, e_save, e_recipe, e_limit, e_filter, e_rotate, e_priority, e_put, e_take, e_mine, e_launch, e_walk, e_tech, e_drop, e_pick_up, e_idle, e_cancel_crafting
};

/// <summary>
/// Contains every step name, aligned with StepType
/// </summary>
/// <note>
/// Starts with "None" for alignments
/// </note>
static const vector<string> StepNames{
	"None", 
	"Stop", "Build", "Craft", "Game speed", "Pause", "Save",
	"Recipe", "Limit", "Filter", "Rotate", "Priority", "Put", "Take", "Mine", "Launch",
	"Walk", "Tech", "Drop", "Pick up", "Idle", "Cancel crafting"
};

/// <summary>
/// Maps StepName(string) to StepType(enum)
/// </summary>
static const map<string, StepType> MapStepNameToStepType = {{"Stop", e_stop}, {"Build", e_build}, {"Craft", e_craft}, {"Game speed", e_game_speed}, {"Pause", e_pause}, {"Save", e_save},
	{"Recipe", e_recipe}, {"Limit", e_limit}, {"Filter", e_filter}, {"Rotate", e_rotate}, {"Priority", e_priority}, {"Put", e_put}, {"Take", e_take}, {"Mine", e_mine}, {"Launch", e_launch},
	{"Walk", e_walk}, {"Tech", e_tech}, {"Drop", e_drop}, {"Pick up", e_pick_up}, {"Idle", e_idle}, {"Cancel crafting", e_cancel_crafting}};

StepType ToStepType(string step);