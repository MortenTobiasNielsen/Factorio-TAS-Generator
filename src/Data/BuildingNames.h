#pragma once

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

enum Assemblers
{
	StoneFurnace = 67,
	SteelFurnace,
	ElectricFurnace,
	AssemblingMachine1,
	AssemblingMachine2,
	AssemblingMachine3,
	OilRefinery,
	ChemicalPlant,
	Centrifuge,
};

static inline const map<string, int> convert_vector_to_map(vector<string> v)
{
	const size_t s = v.size();
	map<string, int> m {};
	for (int i = 0; i < s; i++)
	{
		m.insert({v[i], i});
	}
	return m;
}

static inline const int not_a_building_int = 0;
static inline const string not_a_building_string = "N/A";

static inline const vector<string> BuildingNames =
{
	not_a_building_string, // for alignment
	"Wooden chest",
	"Iron chest",
	"Steel chest",
	"Storage tank",
	"Transport belt",
	"Fast transport belt",
	"Express transport belt",
	"Underground belt",
	"Fast underground belt",
	"Express underground belt",
	"Splitter",
	"Fast splitter",
	"Express splitter",
	"Loader",
	"Fast loader",
	"Express loader",
	"Burner inserter",
	"Inserter",
	"Long-handed inserter",
	"Fast inserter",
	"Filter inserter",
	"Stack inserter",
	"Stack filter inserter",
	"Small electric pole",
	"Medium electric pole",
	"Big electric pole",
	"Substation",
	"Pipe",
	"Pipe to ground",
	"Pump",
	"Curved rail",
	"Straight rail",
	"Train stop",
	"Rail signal",
	"Rail chain signal",
	"Locomotive",
	"Cargo wagon",
	"Fluid wagon",
	"Artillery wagon",
	"Car",
	"Tank",
	"Spidertron",
	"Active provider chest",
	"Passive provider chest",
	"Storage chest",
	"Buffer chest",
	"Requester chest",
	"Roboport",
	"Small lamp",
	"Arithmetic combinator",
	"Decider combinator",
	"Constant combinator",
	"Power switch",
	"Programmable speaker",
	"Boiler",
	"Steam engine",
	"Solar panel",
	"Accumulator",
	"Nuclear reactor",
	"Heat pipe",
	"Heat exchanger",
	"Steam turbine",
	"Burner mining drill",
	"Electric mining drill",
	"Offshore pump",
	"Pumpjack",
	"Stone furnace",
	"Steel furnace",
	"Electric furnace",
	"Assembling machine 1",
	"Assembling machine 2",
	"Assembling machine 3",
	"Oil refinery",
	"Chemical plant",
	"Centrifuge",
	"Lab",
	"Beacon",
	"Rocket silo",
	"Land mine",
	"Stone wall",
	"Gate",
	"Gun turret",
	"Laser turret",
	"Flamethrower turret",
	"Artillery turret",
	"Radar",
	"Item on ground",
	"Rocket silo rocket",
	"Tile ghost",
	"Stone brick",
	"Concrete",
	"Hazard concrete left",
	"Hazard concrete right",
	"Refined concrete",
	"Refined hazard concrete left",
	"Refined hazard concrete right",
	"Landfill"
};

static inline map<string, int> BuildingNameToType = convert_vector_to_map(BuildingNames);

/// <summary>
/// Safe way to get a building name by index
/// </summary>
/// <param name="index">building type</param>
/// <returns>Building name as string or "N/A" if index is out of bounds</returns>
static const string FindBuildingName(const int index)
{
	static const size_t building_names_size = BuildingNames.size();
	if (index < not_a_building_int || index >= building_names_size)
		return not_a_building_string;
	else 
		return BuildingNames[index];
}
