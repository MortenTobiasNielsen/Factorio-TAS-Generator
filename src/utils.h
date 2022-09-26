#pragma once

#include <string>
#include <vector>
#include <map>

enum step_name { 
	step_start = 1, 
	step_stop, 
	step_build, 
	step_craft, 
	step_game_speed, 
	step_pause, 
	step_save, 
	step_recipe, 
	step_limit, 
	step_filter, 
	step_rotate, 
	step_priority, 
	step_put, 
	step_take, 
	step_mine, 
	step_launch, 
	step_walk, 
	step_tech, 
	step_drop, 
	step_pick_up, 
	step_idle };

std::map<std::string, step_name> map_step_names = { 
	{"Start", step_start}, 
	{"Stop", step_stop}, 
	{"Build", step_build}, 
	{"Craft", step_craft}, 
	{"Game Speed", step_game_speed}, 
	{"Pause", step_pause}, 
	{"Save", step_save},
	{"Recipe", step_recipe}, 
	{"Limit", step_limit}, 
	{"Filter", step_filter}, 
	{"Rotate", step_rotate}, 
	{"Priority", step_priority}, 
	{"Put", step_put}, 
	{"Take", step_take}, 
	{"Mine", step_mine}, 
	{"Launch", step_launch},
	{"Walk", step_walk}, 
	{"Tech", step_tech}, 
	{"Drop", step_drop}, 
	{"Pick up", step_pick_up}, 
	{"Idle", step_idle} 
};


// it is important to go though all of the lists When changes to the game is implemented to ensure that the lists are still accurate

static const std::vector<std::string> fuel_list = { "Wood", 
													"Coal", 
													"Solid fuel", 
													"Rocket fuel", 
													"Nuclear fuel", 
													"Uranium fuel cell" };

static const std::vector<std::string> chest_list = { "Wooden chest", 
													 "Iron chest", 
													 "Steel chest",
													 "Active provider chest",
													 "Passive provider chest",
													 "Storage chest",
													 "Buffer chest",
													 "Requester chest"};

static const std::vector<std::string> splitter_list = { "Splitter", 
														"Fast splitter", 
														"Express splitter" };

static const std::vector<std::string> filter_inserter_list = { "Filter inserter", 
															   "Stack filter inserter" };

static const std::map<std::string, std::vector<std::string>> recipes = { { "Copper cable", {"Copper plate", "1" }},
																		 { "Iron stick", {"Iron plate", "1" }},
																		 { "Iron gear wheel", {"Iron plate", "2" }},
																		 { "Electronic circuit", {"Copper cable", "3", "Iron plate", "1" }},
																		 { "Advanced circuit", {"Copper cable", "4", "Electronic circuit", "2", "Plastic bar", "2" }},
																		 { "Processing unit", {"Advanced circuit", "2", "Electronic circuit", "20" }},
																		 { "Engine unit", {"Iron gear wheel", "1", "Pipe", "2", "Steel plate", "1" }},
																		 { "Electric engine unit", {"Electronic circuit", "2", "Engine unit", "1" }},
																		 { "Flying robot frame", {"Battery", "2", "Electronic circuit", "3", "Steel plate", "1" }},
																		 { "Rocket control unit", {"Processing unit", "1", "Speed module", "1" }},
																		 { "Low density structure", {"Copper plate", "20", "Plastic bar", "5", "Steel plate", "2" }},
																		 { "Stone furnace", {"Stone", "5"}},
																		 { "Steel furnace", {"Steel plate", "6", "Stone brick", "10" }},
																		 { "Electric furnace", {"Advanced circuit", "5", "Steel plate", "10", "Stone brick", "10" }},
																		 { "Burner inserter", {"Iron gear wheel", "1", "Iron plate", "1" }},
																		 { "Inserter", {"Electronic circuit", "1", "Iron gear wheel", "1", "Iron plate", "1" }},
																		 { "Long-handed inserter", {"Inserter", "1", "Iron gear wheel", "1", "Iron plate", "1" }},
																		 { "Fast inserter", {"Electronic circuit", "2", "Inserter", "1", "Iron plate", "2" }},
																		 { "Small electric pole", {"Copper cable", "2", "Wood", "1" }},
																		 { "Pipe", {"Iron plate", "1" }},
																		 { "Pipe to ground", {"Iron plate", "5", "Steel plate", "10" }},
																		 { "Rail", {"Iron stick", "1", "Steel plate", "1", "Stone", "1" }},
																		 { "Wooden chest", {"Wood", "2" }},
																		 { "Iron chest", {"Iron plate", "8" }},
																		 { "Steel chest", {"Steel plate", "8" }},
																		 { "Storage tank", {"Iron plate", "20", "Steel plate", "5" }},
																		 { "Transport belt", {"Iron gear wheel", "1", "Iron plate", "1"  }},
																		 { "Fast transport belt", {"Iron gear wheel", "5", "Transport belt", "1"  }},
																		 { "Underground belt", {"Iron plate", "10", "Transport belt", "5" }},
																		 { "Fast underground belt", {"Iron gear wheel", "40", "Underground belt", "2" }},
																		 { "Splitter", {"Electronic circuit", "5", "Iron plate", "5", "Transport belt", "4" }},
																		 { "Fast splitter", {"Electronic circuit", "10", "Iron gear wheel", "10", "Splitter", "1" }},
																		 { "Boiler", {"Pipe", "4", "Stone furnace", "1" }},
																		 { "Steam engine", {"Iron gear wheel", "8", "Iron plate", "10", "Pipe", "5" }},
																		 { "Burner mining drill", {"Iron gear wheel", "3", "Iron plate", "3", "Stone furnace", "1"}},
																		 { "Electric mining drill", {"Electronic circuit", "3", "Iron gear wheel", "5", "Iron plate", "10" }},
																		 { "Offshore pump", {"Electronic circuit", "2", "Iron gear wheel", "1", "Pipe", "1" }},
																		 { "Pumpjack", {"Electronic circuit", "5", "Iron gear wheel", "10", "Pipe", "10", "Steel plate", "5" }},
																		 { "Assembling machine 1", {"Electronic circuit", "3", "Iron gear wheel", "5", "Iron Plate", "9" }},
																		 { "Assembling machine 2", {"Assembling machine 1", "1", "Electronic circuit", "3", "Iron gear wheel", "5", "Steel plate", "2" }},
																		 { "Oil refinery", {"Electronic circuit", "10", "Iron gear wheel", "10", "Pipe", "10", "Steel plate", "15", "Stone brick", "10" }},
																		 { "Chemical plant", {"Electronic circuit", "5", "Iron gear wheel", "5", "Pipe", "5", "Steel plate", "5" }},
																		 { "Lab", {"Electronic circuit", "10", "Iron gear wheel", "10", "Transport belt", "4" }},
																		 { "Battery", {"Iron plate", "1", "Copper plate", "1" }},
																		 { "Productivity module", {"Advanced circuit", "5", "Electronic circuit", "5" }},
																		 { "Productivity module 2", {"Advanced circuit", "5", "Processing unit", "5", "Productivity module", "4" }},
																		 { "Productivity module 3", {"Advanced circuit", "5", "Processing unit", "5", "Productivity module 2", "5" }},
																		 { "Speed module", {"Advanced circuit", "5", "Electronic circuit", "5" }},
																		 { "Speed module 2", {"Advanced circuit", "5", "Processing unit", "5", "Speed module", "4" }},
																		 { "Speed module 3", {"Advanced circuit", "5", "Processing unit", "5", "Speed module 2", "4" }},
																		 { "Automation science pack", {"Copper plate", "1", "Iron gear wheel", "1" }},
																		 { "Logistic science pack", {"Inserter", "1", "Transport belt", "1" }},
																		 { "Chemical science pack", {"Advanced circuit", "3", "Engine unit", "2", "Sulfur", "1" }},
																		 { "Production science pack", {"Electric furnace", "1", "Productivity module", "1", "Rail", "30" }},
																		 { "Utility science pack", {"Flying robot frame", "1", "Low density structure", "3", "Processing unit", "2" }},
																	   };

static const std::map<std::string, std::vector<float>> building_size_list = { { "Accumulator", {2, 2} },
																			  { "Wooden chest", {1, 1} },
																			  { "Iron chest", {1, 1} },
																			  { "Steel chest", {1, 1} },
																			  { "Storage tank", {3, 3} },
																			  { "Transport belt", {1, 1} },
																			  { "Fast transport belt", {1, 1} },
																			  { "Underground belt", {1, 1} },
																			  { "Fast underground belt", {1, 1} },
																			  { "Splitter", {2, 1} },
																			  { "Fast splitter", {2, 1} },
																			  { "Burner inserter", {1, 1} },
																			  { "Inserter", {1, 1} },
																			  { "Long-handed inserter", {1, 1} },
																			  { "Fast inserter", {1, 1} },
																			  { "Filter inserter", {1, 1} },
																			  { "Stack inserter", {1, 1} },
																			  { "Stack filter inserter", {1, 1} },
																			  { "Small electric pole", {1, 1} },
																			  { "Medium electric pole", {1, 1} },
																			  { "Big electric pole", {2, 2} },
																			  { "Substation", {2, 2} },
																			  { "Pipe", {1, 1} },
																			  { "Pipe to ground", {1, 1} },
																			  { "Pump", {3, 3} },
																			  { "Rail", {1.7f, 2.4f} },
																			  { "Train stop", {1.8f, 1.8f} },
																			  { "Rail signal", {1, 1} },
																			  { "Rail chain signal", {1, 1} },
																			  { "Locomotive", {2, 6} },
																			  { "Cargo wagon", {2, 6} },
																			  { "Fluid wagon", {2, 6} },
																			  { "Artillery wagon", {2, 6} },
																			  { "Car", {1.2f, 1.9f} },
																			  { "Tank", {1.7f, 2.5f} },
																			  { "Spidertron",  {2, 1.9f} },
																			  { "Logistic robot", {1, 1} },
																			  { "Construction robot", {1, 1} },
																			  { "Active provider chest", {1, 1} },
																			  { "Passive provider chest", {1, 1} },
																			  { "Storage chest", {1, 1} },
																			  { "Buffer chest", {1, 1} },
																			  { "Requester chest", {1, 1} },
																			  { "Roboport", {4, 4} },
																			  { "Lamp", {1, 1} },
																			  { "Red wire", {1, 1} },
																			  { "Green wire", {1, 1} },
																			  { "Arithmetic combinator", {1, 2} },
																			  { "Decider combinator", {1, 2} },
																			  { "Constant combinator", {1, 1} },
																			  { "Power switch", {2, 2} },
																			  { "Programmable speaker", {1, 1} },
																			  { "Hazard concrete", {1, 1} },
																			  { "Refined hazard concrete", {1, 1} },
																			  { "Landfill", {1, 1} },
																			  { "Land mine", {1, 1} },
																			  { "Wall", {1, 1} },
																			  { "Gate", {1, 1} },
																			  { "Gun turret", {2, 2} },
																			  { "Laser turret", {2, 2} },
																			  { "Flamethrower turret", {2, 3} },
																			  { "Artillery turret", {3, 3} },
																			  { "Radar", {3, 3} },
																			  { "Rocket silo", {9, 9} },
																			  { "Repair pack", {1, 1} },
																			  { "Boiler", {3, 2} },
																			  { "Steam engine", {3, 5} },
																			  { "Steam turbine", {3, 5} },
																			  { "Solar panel", {3, 3} },
																			  { "Nuclear reactor", {5, 5} },
																			  { "Heat exchanger", {3, 2} },
																			  { "Heat pipe", {1, 1} },
																			  { "Burner mining drill", {2, 2} },																			  
																			  { "Electric mining drill", {3, 3} },
																			  { "Offshore pump", {1, 2} },
																			  { "Pumpjack", {3, 3} },
																			  { "Stone furnace", {1.6f, 2} },
																			  { "Steel furnace", {1.6f, 2} },
																			  { "Electric furnace", {1.6f, 2} },
																			  { "Assembling machine 1", {3, 3} },
																			  { "Assembling machine 2", {3, 3} },
																			  { "Assembling machine 3", {3, 3} },
																			  { "Oil refinery", {5, 5} },
																			  { "Chemical plant", {3, 3} },
																			  { "Centrifuge", {3, 3} },
																			  { "Lab", {3, 3} },
																			  { "Beacon", {3, 3} },
																			  { "Express transport belt", {1, 1} },
																			  { "Express underground belt", {1, 1} },
																			  { "Express splitter", {1, 1} },
																			  { "Concrete", {1, 1} },
																			  { "Refined concrete", {1, 1} },
																			  { "Stone brick",  {1, 1} } };

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
													   "Steel plate",
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
														"Long-handed inserter", 
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
												   "Chest",
												   "Wreck" };

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
													"Advanced electronics 2",
													"Automation",
													"Automation 2",
													"Automation 3",
													"Electric energy accumulators",
													"Electric energy distribution 1",
													"Electric energy distribution 2",
													"Fast inserter",
													"Fluid handling",
													"Logistics",
													"Logistics 2",
													"Logistics 3",
													"Nuclear power",
													"Oil processing",
													"Rocket silo",
													"Solar energy",
													"Stack inserter",
													"Atomic bomb",
													"Combat robotics",
													"Combat robotics 2",
													"Combat robotics 3",
													"Flamethrower",
													"Military",
													"Military 2",
													"Military 3",
													"Military 4",
													"Rocketry",
													"Explosive rocketry",
													"Uranium ammo",
													"Artillery shell range",
													"Artillery shell shooting speed",
													"Braking force 1",
													"Braking force 2",
													"Braking force 3",
													"Braking force 4",
													"Braking force 5",
													"Braking force 6",
													"Braking force 7",
													"Energy weapons damage 1",
													"Energy weapons damage 2",
													"Energy weapons damage 3",
													"Energy weapons damage 4",
													"Energy weapons damage 5",
													"Energy weapons damage 6",
													"Energy weapons damage 7",
													"Follower robot count 1",
													"Follower robot count 2",
													"Follower robot count 3",
													"Follower robot count 4",
													"Follower robot count 5",
													"Follower robot count 6",
													"Follower robot count 7",
													"Inserter capacity bonus 1",
													"Inserter capacity bonus 2",
													"Inserter capacity bonus 3",
													"Inserter capacity bonus 4",
													"Inserter capacity bonus 5",
													"Inserter capacity bonus 6",
													"Inserter capacity bonus 7",
													"Lab research speed 1",
													"Lab research speed 2",
													"Lab research speed 3",
													"Lab research speed 4",
													"Lab research speed 5",
													"Lab research speed 6",
													"Laser turret shooting speed 1",
													"Laser turret shooting speed 2",
													"Laser turret shooting speed 3",
													"Laser turret shooting speed 4",
													"Laser turret shooting speed 5",
													"Laser turret shooting speed 6",
													"Laser turret shooting speed 7",
													"Mining productivity 1",
													"Mining productivity 2",
													"Mining productivity 3",
													"Mining productivity 4",
													"Mining productivity 4",
													"Physical projectile damage 1",
													"Physical projectile damage 2",
													"Physical projectile damage 3",
													"Physical projectile damage 4",
													"Physical projectile damage 5",
													"Physical projectile damage 6",
													"Physical projectile damage 7",
													"Refined flammables",
													"Refined flammables 2",
													"Stronger explosives 1",
													"Stronger explosives 2",
													"Stronger explosives 3",
													"Stronger explosives 4",
													"Stronger explosives 5",
													"Stronger explosives 6",
													"Stronger explosives 7",
													"Weapon shooting speed 1",
													"Weapon shooting speed 2",
													"Weapon shooting speed 3",
													"Weapon shooting speed 4",
													"Weapon shooting speed 5",
													"Weapon shooting speed 6",
													"Worker robot cargo size 1",
													"Worker robot cargo size 2",
													"Worker robot cargo size 3",
													"Worker robot speed 1",
													"Worker robot speed 2",
													"Worker robot speed 3",
													"Worker robot speed 4",
													"Worker robot speed 5",
													"Worker robot speed 6",
													"Construction robotics",
													"Logistic robotics",
													"Steel axe",
													"Toolbelt",
													"Heavy armor",
													"Modular armor",
													"Power armor",
													"Power armor MK2",
													"Gates",
													"Land mines",
													"Stone walls",
													"turrets",
													"Laser turrets",
													"Artillery",
													"Advanced material processing",
													"Advanced material processing 2",
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
													"Energy shield equipment MK2",
													"Exoskeleton equipment",
													"Nightvision equipment",
													"Personal battery",
													"Personal battery MK2",
													"Personal laser defense",
													"Personal roboport",
													"Personal roboport MK2",
													"Portable fusion reactor",
													"Portable solar panel",
													"Modules",
													"Effect transmission",
													"Efficiency module",
													"Efficiency module 2",
													"Efficiency module 3",
													"Productivity module",
													"Productivity module 2",
													"Productivity module 3",
													"Speed module",
													"Speed module 2",
													"Speed module 3" };

static const std::vector<std::string> drills_list = { "Electric mining drill", 
													  "Pumpjack" };

static const struct {
	std::string game_speed = "Game Speed";
	std::string walk = "Walk";
	std::string mine = "Mine";
	std::string rotate = "Rotate";
	std::string craft = "Craft";
	std::string build = "Build";
	std::string take = "Take";
	std::string put = "Put";
	std::string tech = "Tech";
	std::string recipe = "Recipe";
	std::string start = "Start";
	std::string pause = "Pause";
	std::string stop = "Stop";
	std::string limit = "Limit";
	std::string priority = "Priority";
	std::string filter = "Filter";
	std::string pick_up = "Pick up";
	std::string drop = "Drop";
	std::string idle = "Idle";
	std::string launch = "Launch";
	std::string save = "Save";

} struct_tasks_list;

static const struct {
	std::string input = "Input";
	std::string output = "Output";
	std::string fuel = "Fuel";
	std::string modules = "Modules";
	std::string chest = "Chest";
	std::string wreck = "Wreck";
} struct_from_into_list;

static const struct {
	std::string stone = "Stone furnace";
	std::string steel = "Steel furnace";
} struct_auto_put_furnace_list;

static const struct {
	std::string burner_mining_drill = "Burner mining drill";
	std::string burner_inserter = "Burner inserter";
	std::string boiler = "Boiler";
} struct_auto_put_burner_list;

static const struct {
	std::string wood = "Wood";
	std::string coal = "Coal";
	std::string solid_fuel = "Solid fuel";
	std::string rocket_fuel = "Rocket fuel";
	std::string nuclear_fuel = "Nuclear fuel";
	std::string uranium_fuel_cell = "Uranium fuel cell";
} struct_fuel_list;

static const struct {
	std::string lab = "Lab";
	std::string red_science = "automation-science-pack";
	std::string green_science = "logistic-science-pack";
	std::string black_science = "military-science-pack";
	std::string blue_science = "chemical-science-pack";
	std::string purple_science = "production-science-pack";
	std::string yellow_science = "utility-science-pack";
	std::string white_science = "space-science-pack";
} struct_science_list;

struct drill_types {
	std::string burner = "burner-mining-drill";
	std::string electric = "electric-mining-drill";
};

struct transport_types {
	std::string yellow_belt = "transport-belt";
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