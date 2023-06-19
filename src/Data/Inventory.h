#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

/// <summary>
/// Focused list of inventories, used for script generation
/// Full list available on https://lua-api.factorio.com/latest/defines.html#defines.inventory
/// </summary>
static const struct
{	
	string fuel = "defines.inventory.fuel";
	string chest = "defines.inventory.chest";
	string lab_input = "defines.inventory.lab_input";
	string lab_modules = "defines.inventory.lab_modules";
	string beacon_modules = "defines.inventory.beacon_modules";
	string drill_modules = "defines.inventory.mining_drill_modules";
	string assembly_input = "defines.inventory.assembling_machine_input";
	string assembly_output = "defines.inventory.assembling_machine_output";
	string assembly_modules = "defines.inventory.assembling_machine_modules";
} inventory_defines;

/// <summary>
/// Inventory types used in the GUI
/// </summary>
static const struct
{
	string input = "Input";
	string output = "Output";
	string fuel = "Fuel";
	string modules = "Modules";
	string chest = "Chest";
	string wreck = "Wreck";
} inventory_types;

static const vector<string> inventory_types_list
{
	inventory_types.input,
	inventory_types.output,
	inventory_types.fuel,
	inventory_types.modules,
	inventory_types.chest,
	inventory_types.wreck
};
