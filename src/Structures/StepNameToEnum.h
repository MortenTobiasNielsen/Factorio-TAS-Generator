#pragma once

#include <map>
#include <string>
#include <vector>
#include <set>

using std::map;
using std::string;
using std::vector;
using std::set;

/// <summary>
/// Enumaration of all step types
/// </summary>
enum StepType
{
	e_stop = 1, e_build, e_craft, e_game_speed, e_pause, e_save, e_recipe, e_limit,
	e_filter, e_rotate, e_priority, e_put, e_take, e_mine, e_launch, e_walk, e_tech, e_drop, e_pick_up, e_idle, e_cancel_crafting,
	e_never_idle, e_keep_walking, e_keep_on_path, e_keep_crafting,
	e_shoot, e_throw
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
	"Walk", "Tech", "Drop", "Pick up", "Idle", "Cancel",
	"Never idle", "Keep walking", "Keep on path", "Keep crafting",
	"Shoot", "Throw"
};

/// <summary>
/// Maps StepName(string) to StepType(enum)
/// </summary>
static const map<string, StepType> MapStepNameToStepType = {{"Stop", e_stop}, {"Build", e_build}, {"Craft", e_craft}, {"Game speed", e_game_speed}, {"Pause", e_pause}, {"Save", e_save},
	{"Recipe", e_recipe}, {"Limit", e_limit}, {"Filter", e_filter}, {"Rotate", e_rotate}, {"Priority", e_priority}, {"Put", e_put}, {"Take", e_take}, {"Mine", e_mine}, {"Launch", e_launch},
	{"Walk", e_walk}, {"Tech", e_tech}, {"Drop", e_drop}, {"Pick up", e_pick_up}, {"Idle", e_idle}, {"Cancel", e_cancel_crafting},
	{"Never idle", e_never_idle}, {"Keep walking", e_keep_walking}, {"Keep on path", e_keep_on_path}, {"Keep crafting", e_keep_crafting},
	{"Shoot", e_shoot}, {"Throw", e_throw}
};

StepType ToStepType(string step);

static struct ModifierTypeSets{
	set<StepType> walk_towards{
		e_walk,
	};
	set<StepType> no_order{
		e_build,
		e_craft,
		e_recipe,
		e_limit,
		e_filter,
		e_rotate,
		e_priority,
		e_put,
		e_take,
		e_launch,
		e_tech,
		e_drop,
		e_cancel_crafting,
	};
	set<StepType> cancel{
		e_tech,
		e_craft,
	};
	set<StepType> wait_for{
		e_recipe,
		e_craft,
	};
	set<StepType> skip{
		//all
		e_stop, e_build, e_craft, e_game_speed, e_pause, e_save, e_recipe, e_limit,
		e_filter, e_rotate, e_priority, e_put, e_take, e_mine, e_launch, e_walk, e_tech, e_drop, e_pick_up, e_idle, e_cancel_crafting,
		e_never_idle, e_keep_walking, e_keep_on_path, e_keep_crafting
	};
	set<StepType> force{
		//character steps
		e_drop, 
		e_mine,
		//building steps
		e_take, 
		e_put, 
		e_build, 
		e_recipe, 
		e_limit,
		e_filter,
		e_priority,
		e_launch,
		e_rotate,
	};
	set<StepType> split{
		e_mine,
	};
} modifier_types;
