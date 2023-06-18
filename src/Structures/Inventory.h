#pragma once

#include <vector>
#include <map>
#include <string>

static const struct
{
	std::string chest = "defines.inventory.chest";
	std::string lab_input = "defines.inventory.lab_input";
	std::string lab_modules = "defines.inventory.lab_modules";
	std::string beacon_modules = "defines.inventory.beacon_modules";
	std::string fuel = "defines.inventory.fuel";
	std::string drill_modules = "defines.inventory.mining_drill_modules";
	std::string assembly_input = "defines.inventory.assembling_machine_input";
	std::string assembly_output = "defines.inventory.assembling_machine_output";
	std::string assembly_modules = "defines.inventory.assembling_machine_modules";
} struct_take_put_list;

static const struct
{
	std::string input = "Input";
	std::string output = "Output";
	std::string fuel = "Fuel";
	std::string modules = "Modules";
	std::string chest = "Chest";
	std::string wreck = "Wreck";
} struct_from_into_list;

static const std::vector<std::string> take_from =
{
	struct_from_into_list.input,
	struct_from_into_list.output,
	struct_from_into_list.fuel,
	struct_from_into_list.modules,
	struct_from_into_list.chest,
	struct_from_into_list.wreck
};