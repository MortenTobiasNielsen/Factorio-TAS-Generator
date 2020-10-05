#pragma once

#include <string>
#include <vector>
#include <map>

// it is important to go though all of the lists When changes to the game is implemented to ensure that the lists are still accurate

static const std::vector<std::string> fuel_list = { "Wood", 
													"Coal", 
													"Solid fuel", 
													"Rocket fuel", 
													"Nuclear fuel", 
													"Uranium fuel cell" };

static const std::vector<std::string> chest_list = { "Wooden chest", 
													 "Iron chest", 
													 "Steel chest" };

static const std::vector<std::string> splitter_list = { "Splitter", 
														"Fast splitter", 
														"Express splitter" };

static const std::vector<std::string> filter_inserter_list = { "Filter inserter", 
															   "Stack filter inserter" };

static const std::vector<std::string> building_list = { "Accumulator",
														"Wooden chest",
														"Iron chest",
														"Steel chest",
														"Storage tank",
														"Transport belt",
														"Fast transport belt",
														"Underground belt",
														"Fast underground belt",
														"Splitter",
														"Fast splitter",
														"Burner inserter",
														"Inserter",
														"Long handed inserter",
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
														"Rail",
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
														"Spidertron remote",
														"Logistic robot",
														"Construction robot",
														"Active provider chest",
														"Passive provider chest",
														"Storage chest",
														"Buffer chest",
														"Requester chest",
														"Roboport",
														"Lamp",
														"Red wire",
														"Green wire",
														"Arithmetic combinator",
														"Decider combinator",
														"Constant combinator",
														"Power switch",
														"Programmable speaker",
														"Hazard concrete",
														"Refined hazard concrete",
														"Landfill",
														"Land mine", 
														"Wall",
														"Gate",
														"Gun turret",
														"Laser turret",
														"Flamethrower turret",
														"Artillery turret",
														"Radar",
														"Rocket silo",
														"Repair pack",
														"Boiler",
														"Steam engine",
														"Steam turbine",
														"Solar panel",
														"Nuclear reactor",
														"Heat exchanger",
														"Heat pipe",
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
														"Express transport belt",
														"Express underground belt",
														"Express splitter",
														"Concrete",
														"Refined concrete",
														"Stone brick" };

static const std::vector<std::string> handcrafted_list = { "Accumulator",
														   "Wooden chest",
														   "Iron chest", 
														   "Steel chest", 
														   "Storage tank", 
														   "Transport belt", 
														   "Fast transport belt", 
														   "Underground belt", 
														   "Fast underground belt", 
														   "Splitter", 
														   "Fast splitter", 
														   "Burner inserter", 
														   "Inserter", 
														   "Long handed inserter", 
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
														   "Rail", 
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
														   "Spidertron remote", 
														   "Logistic robot", 
														   "Construction robot", 
														   "Active provider chest", 
														   "Passive provider chest", 
														   "Storage chest", 
														   "Buffer chest", 
														   "Requester chest", 
														   "Roboport", 
														   "Lamp", 
														   "Red wire", 
														   "Green wire", 
														   "Arithmetic combinator", 
														   "Decider combinator", 
														   "Constant combinator", 
														   "Power switch", 
														   "Programmable speaker", 
														   "Hazard concrete", 
														   "Refined hazard concrete", 
														   "Landfill", 
														   "Cliff explosives", 
														   "Pistol", 
														   "Submachine gun", 
														   "Shotgun", 
														   "Combat shotgun", 
														   "Rocket launcher", 
														   "Flamethrower", 
														   "Land mine", 
														   "Firearm magazine", 
														   "Piercing rounds magazine", 
														   "Uranium rounds magazine", 
														   "Shotgun shells", 
														   "Piercing shotgun shells", 
														   "Cannon shell", 
														   "Explosive cannon shell", 
														   "Uranium cannon shell", 
														   "Explosive uranium cannon shell", 
														   "Artillery shell", 
														   "Rocket", 
														   "Explosive rocket", 
														   "Atomic bomb", 
														   "Grenade", 
														   "Cluster grenade", 
														   "Poison capsule", 
														   "Slowdown capsule", 
														   "Defender capsule", 
														   "Distractor capsule", 
														   "Destroyer capsule", 
														   "Discharge defense remote", 
														   "Artillery targeting remote", 
														   "Light armor", 
														   "Heavy armor", 
														   "Modular armor", 
														   "Power armor", 
														   "Power armor MK2", 
														   "Portable solar panel", 
														   "Portable fusion reactor", 
														   "Energy shield", 
														   "Energy shield MK2", 
														   "Personal battery", 
														   "Personal battery MK2", 
														   "Personal laser defense", 
														   "Discharge defense", 
														   "Belt immunity equipment", 
														   "Exoskeleton", 
														   "Personal roboport", 
														   "Personal roboport MK2", 
														   "Nightvision", 
														   "Wall", 
														   "Gate", 
														   "Gun turret", 
														   "Laser turret", 
														   "Flamethrower turret", 
														   "Artillery turret", 
														   "Radar", 
														   "Rocket silo", 
														   "Repair pack", 
														   "Boiler", 
														   "Steam engine", 
														   "Steam turbine", 
														   "Solar panel", 															 
														   "Nuclear reactor", 
														   "Heat exchanger", 
														   "Heat pipe", 
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
														   "Speed module", 
														   "Speed module 2", 
														   "Speed module 3", 
														   "Efficiency module", 
														   "Efficiency module 2", 
														   "Efficiency module 3", 
														   "Productivity module", 
														   "Productivity module 2", 
														   "Productivity module 3", 
														   "Copper cable", 
														   "Iron stick", 
														   "Iron gear wheel", 
														   "Empty barrel",
														   "Electronic circuit", 
														   "Advanced circuit", 
														   "Flying robot frame", 
														   "Satellite", 
														   "Rocket control unit", 
														   "Low density structure", 
														   "Uranium fuel cell", 
														   "Automation science pack", 
														   "Logistic science pack", 
														   "Military science pack", 
														   "Chemical science pack", 
														   "Production science pack", 
														   "Utility science pack", 
														   "Space science pack" };

static const std::vector<std::string> science_packs = { "Automation science pack", 
														"Logistic science pack", 
														"Military science pack", 
														"Chemical science pack", 
														"Production science pack", 
														"Utility science pack", 
														"Space science pack" };

static const std::vector<std::string> furnace_list = { "Iron plate",
													   "Copper plate",
													   "Steel",
													   "Stone",
													   "Stone brick" };

static const std::vector<std::string> assemply_level1_list = { "Engine unit" };

static const std::vector<std::string> assemply_level2_list = { "Express transport belt",
															   "Express underground belt",
															   "Express splitter",
															   "Concrete",
															   "Refined concrete",
															   "Processing unit",
															   "Electric engine unit",
															   "Rocket fuel",
															   "Fill crude oil barrel",
															   "Fill heavy oil barrel",
															   "Fill light oil barrel",
															   "Fill lubricant barrel",
															   "Fill petroleum gas barrel",
															   "Fill sulfuric acid barrel",
															   "Fill water barrel"};

static const std::vector<std::string> assemply_level2_extra_list = { "Empty crude oil barrel",
																	 "Empty heavy oil barrel",
																	 "Empty light oil barrel",
																	 "Empty lubricant barrel",
																	 "Empty petroleum gas barrel",
																	 "Empty sulfuric acid barrel",
																	 "Empty water barrel" };

static const std::vector<std::string> chemical_plant_list = { "Flamethrower ammo",
															  "Solid fuel", 
															  "Plastic bar", 
															  "Sulfur",															  
															  "Battery",
															  "Explosives" };

static const std::vector<std::string> chemical_plant_extra_list = { "Sulfuric acid", 
																	"Lubricant",
																	"Heavy oil cracking",
																	"Light oil cracking" };

static const std::vector<std::string> centrifuge_list = { "Nuclear fuel", 
														  "Uranium processing",														  
														  "Nuclear fuel reprocessing", 
														  "Kovarex enrichment process" };

static const std::vector<std::string> oil_refinery_list = { "Basic oil processing",
															"Advanced oil processing",															
															"Coal liquefaction" };

static const std::vector<std::string> rocket_silo_list = { "Rocket part" };


static const std::vector<std::string> raw_resource_list = { "Wood", 
														    "Coal",
															"Stone",
															"Iron ore",
															"Copper ore",
															"Uranium ore",
															"Raw fish" };

static const std::vector<std::string> filter_take_put_drop_extra_list = { "Nuclear fuel",
																		  "Uranium-235", 
																		  "Uranium-238", 
																		  "Used-up uranium fuel cell" };

															
static const std::vector<std::string> weapon_list = { "Pistol", 
													  "Submachine gun", 
													  "Shotgun", 
													  "Combat shotgun", 
													  "Flamethrower", 
													  "Rocket launcher" };

static const std::vector<std::string> magazine_list = { "Firearm magazine",
														"Piercing rounds magazine",
														"Uranium rounds magazine" };

static const std::vector<std::string> shotgun_shell_list = { "Shotgun shells",
															 "Piercing shotgun shells" };

static const std::vector<std::string> rocket_list = { "Rocket", 
													  "Explosive rocket", 
													  "Atomic bomb" };

static const std::vector<std::string> flamethrower_fuel_list = { "Flamethrower ammo" };

static const std::vector<std::string> tank_shell_list = { "Cannon shell", 
														  "Explosive cannon shell", 
														  "Uranium cannon shell", 
														  "Explosive uranium cannon shell" };

static const std::vector<std::string> grenade_list = {};



static const std::vector<std::string> tank_shells = {};

static const std::vector<std::string> tank_shells2 = {};

static const std::vector<std::string> item_categories = {"Logistics", 
														 "Production", 
														 "Intermediates", 
														 "Combat"};

static const std::vector<std::string> item_categories_fuel = { "Fuel"};

static const std::vector<std::string> item_logistics = {"None", 
														"Wooden chest", 
														"Iron chest", 
														"Steel chest", 
														"Transport belt", 
														"Burner inserter", 
														"Inserter", 
														"Long handed inserter", 
														"Fast inserter", 
														"Filter inserter", 
														"Stack inserter", 
														"Stack filter inserter", 
														"Small electric pole", 
														"Pipe", "Pipe to ground", 
														"Underground belt", 
														"Splitter" };

static const std::vector<std::string> item_production = { "Boiler", 
														  "Steam engine", 
														  "Burner mining drill", 
														  "Electric mining drill", 
														  "Offshore pump", "Pumpjack", 
														  "Stone furnace", 
														  "Steel furnace", 
														  "Assembling machine 1", 
														  "Assembling machine 2", 
														  "Lab", 
														  "Speed module", 
														  "Speed module 2" , 
														  "Speed module 3", 
														  "Efficiency module", 
														  "Efficiency module 2", 
														  "Efficiency module 3", 
														  "Productivity module", 
														  "Productivity module 2", 
														  "Productivity module 3" };

static const std::vector<std::string> item_intermediates = { "Wood", 
															 "Coal", 
															 "Stone", 
															 "Iron ore", 
															 "Copper ore", 
															 "Iron plate", 
															 "Copper plate", 
															 "Iron gear wheel", 
															 "Copper cable", 
															 "Automation science pack", 
															 "Electronic circuit" };

static const std::vector<std::string> item_combat = { "Pistol", 
												      "Submachine gun", 
													  "Shotgun"};

static const std::vector<std::string> take_from = {"Input", 
												   "Output", 
												   "Fuel", 
												   "Modules", 
												   "Chest" };


static const std::vector<std::string> input_output = { "Left", 
													   "Right", 
													   "None"};

static const std::vector<std::string> module_list = {"Speed module", 
													 "Speed module 2", 
													 "Speed module 3", 
													 "Efficiency module", 
													 "Efficiency module 2", 
													 "Efficiency module 3", 
													 "Productivity module", 
													 "Productivity module 2", 
													 "Productivity module 3"};

static const std::vector<std::string> build_orientations = { "North", 
															 "East", 
															 "South", 
															 "West"};

static const std::vector<std::string> tech_list = { "Advanced electronics",
													"Advanced electronics 2",
													"Automation",
													"Automation 2",
													"Automation 3",
													"Electric energy accumulators",
													"Electric energy distribution 1",
													"Electric energy distribution 2",
													"Fast inserter",
													"Fluid handling",
													"Logistics",
													"Logistics 2",
													"Logistics 3",
													"Nuclear power",
													"Oil processing",
													"Rocket silo",
													"Solar energy",
													"Stack inserter",
													"Atomic bomb",
													"Combat robotics",
													"Combat robotics 2",
													"Combat robotics 3",
													"Flamethrower",
													"Military",
													"Military 2",
													"Military 3",
													"Military 4",
													"Rocketry",
													"Explosive rocketry",
													"Uranium ammo",
													"Artillery shell range",
													"Artillery shell shooting speed",
													"Braking force",
													"Energy weapons damage",
													"Follower robot count",
													"Inserter capacity bonus",
													"Lab research speed",
													"Laser turret shooting speed",
													"Mining productivity",
													"Physical projectile damage",
													"Refined flammables",
													"Stronger explosives",
													"Weapon shooting speed",
													"Worker robot cargo size",
													"Worker robot speed",
													"Construction robotics",
													"Logistic robotics",
													"Steel axe",
													"Toolbelt",
													"Heavy armor",
													"Modular armor",
													"Power armor",
													"Power armor MK2",
													"Gates",
													"Landmines",
													"Stone walls",
													"Gun turrets",
													"Laser turrets",
													"Artillery",
													"Advanced material processing",
													"Advanced material processing 2",
													"Advanced oil processing",
													"Battery",
													"Circuit network",
													"Chemical science pack",
													"Cliff explosives",
													"Coal liquefaction",
													"Concrete",
													"Electronics",
													"Engine",
													"Electric engine",
													"Explosives",
													"Flammables",
													"Kovarex enrichment process",
													"Landfill",
													"Laser",
													"Logistic science pack",
													"Logistic system",
													"Low density structure",
													"Lubricant",
													"Military science pack",
													"Nuclear fuel reprocessing",
													"Optics",
													"Plastics",
													"Production science pack",
													"Robotics",
													"Rocket control unit",
													"Rocket fuel",
													"Space science pack",
													"Steel processing",
													"Sulfur processing",
													"Uranium processing",
													"Utility science pack",
													"Automated rail transportation",
													"Automobilism",
													"Fluid wagon",
													"Rail signals",
													"Railway",
													"Tanks",
													"Spidertron",
													"Belt immunity equipment",
													"Discharge defense",
													"Energy shield equipment",
													"Energy shield equipment MK2",
													"Exoskeleton equipment",
													"Nightvision equipment",
													"Personal battery",
													"Personal battery MK2",
													"Personal laser defense",
													"Personal roboport",
													"Personal roboport MK2",
													"Portable fusion reactor",
													"Portable solar panel",
													"Modules",
													"Effect transmission",
													"Efficiency module",
													"Efficiency module 2",
													"Efficiency module 3",
													"Productivity module",
													"Productivity module 2",
													"Productivity module 3",
													"Speed module",
													"Speed module 2",
													"Speed module 3",
};

static const std::vector<std::string> drills_list = { "Electric mining drill", 
													  "Pumpjack" };


static const std::map<std::string, std::vector<int>> building_size_list = {{ "Oil refinery", {5, 5}},
																		   { "Electric mining drill", {3, 3}}};

struct furnace_types {
	std::string stone = "stone-furnace";
};

struct drill_types {
	std::string burner = "burner-mining-drill";
	std::string electric = "electric-mining-drill";
};

struct transport_types {
	std::string yellow_belt = "transport-belt";
};

struct fuel_types {
	std::string wood = "wood";
	std::string coal = "coal";
};

struct take_put_defines_list {
	std::string chest = "defines.inventory.chest";
	std::string lab_input = "defines.inventory.lab_input";
	std::string lab_modules = "defines.inventory.lab_modules";
	std::string fuel = "defines.inventory.fuel";
	std::string drill_modules = "defines.inventory.mining_drill_modules";
	std::string assembly_input = "defines.inventory.assembling_machine_input";
	std::string assembly_output = "defines.inventory.assembling_machine_output";
	std::string assembly_modules = "defines.inventory.assembling_machine_modules";
};

const static take_put_defines_list take_put_list;

struct plate_types {
	std::string iron = "iron-plate";
	std::string copper = "copper-plate";
};

struct ore_types {
	std::string stone = "stone";
	std::string iron = "iron-ore";
	std::string copper = "copper-ore";
};

struct intermediate_types {
	std::string iron_gear_wheel = "iron-gear-wheel";
	std::string copper_cable = "copper-cable";
	std::string circuit_green = "electronic-circuit";
};

struct pipe_struct {
	std::string pipe = "pipe";
	std::string pipe_ground = "pipe-to-ground";
};

struct power_structures_struct {
	std::string boiler = "boiler";
	std::string steam_engine = "steam-engine";
	std::string pump = "offshore-pump";
	std::string small_pole = "small-electric-pole";
};

struct chest_types {
	std::string wood = "wooden-chest";
};

struct assembly_types {
	std::string level_1 = "assembling-machine-1";
	std::string level_2 = "assembling-machine-2";

};

struct science_struct {
	std::string lab = "lab";
	std::string red_science = "automation-science-pack";
	std::string green_science = "logistic-science-pack";
};

struct build_distance_struct {
	float one = 9.8f;
	float two = 8.8f;
	float three = 6.8f;
	float four = 5.8f;
	float five = 3.8f;
};


// Observations. The middle of a normal mining path are x.5, y.5 So this should be the point used to calculate how close the player needs to be to mine it
// The tip-over point from the game to choose one mining path over an adjacent seem to be at the x.0 mark, but this should be tested in the API with e.g. 1.00001 and see if it takes the patch at 0.5 or 1.5
// It seems like the tip-over point for the player to reach something 3 tiles away is 0.269531 (very random)
// It furthermore seems like the 3 tiles can only be reached for tiles being a maximum of 
// maybe the walk function in lua should be changed, so it does not make the studdering but stops as soon as it has rached the distination so if it is 80.1235 then when it is 80.1235 or larger it will stop if it came from below 80.1235. i THink this complexity will slow down the script too much.


struct mining_distance_struct {
	float one = 2.65f;
	float two = 1.65f;
	float three = 0.65f;
};

struct build_direction_struct {
	std::string north = "defines.direction.north";
	std::string south = "defines.direction.south";
	std::string east = "defines.direction.east";
	std::string west = "defines.direction.west";
};

static const build_direction_struct build_directions;

struct row_direction_struct {
	std::string north = "north";
	std::string south = "south";
	std::string east = "east";
	std::string west = "west";

};

struct inserter_types {
	std::string yellow = "inserter";
};

struct building_size_struct {
	int small_building = 1;
	int medium_building = 2;
	int large_building = 3;
	int very_large_building = 7;
};

enum walk_direction {
	north = 1,
	northeast = 2,
	northwest = 3,
	south = 4,
	southeast = 5,
	southwest = 6,
	east = 7,
	west = 8
};