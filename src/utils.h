#pragma once

#include <string>
#include <vector>
#include <map>

// it is important to go though all of the lists When changes to the game is implemented to ensure that the lists are still accurate

static const int step_segment_size = 10;
static const int step_segment_size_without_comment = 9;
static const int group_segment_size = 11;
static const int group_segment_size_without_comment = 10;
static const int template_segment_size = 11;
static const int template_segment_size_without_comment = 10;

static const std::string total_steps_indicator = "Total lines:";
static const std::string goal_indicator = "Goal:";
static const std::string steps_indicator = "Steps:";
static const std::string save_groups_indicator = "Groups:";
static const std::string save_templates_indicator = "Templates:";
static const std::string save_file_indicator = "Save file location:";
static const std::string code_file_indicator = "Step folder location:";
static const std::string auto_close_indicator = "Auto close settings:";
static const std::string auto_put_indicator = "Auto put settings:";

static const std::string auto_close_generate_script_text = "Generate Script";
static const std::string auto_close_open_text = "Open";
static const std::string auto_close_save_text = "Save";
static const std::string auto_close_save_as_text = "Save As";

static const std::string auto_put_furnace_text = "Furnace";
static const std::string auto_put_burner_text = "Burner";
static const std::string auto_put_lab_text = "Lab";
static const std::string auto_put_recipe_text = "Recipe";

static const std::string goal_steelaxe_text = "Steel Axe";
static const std::string goal_GOTLAP_text = "Getting On Track Like A Pro";
static const std::string goal_any_percent_text = "Any %";
static const std::string goal_debug_text = "Debug";

struct open_file_return_data {
	bool success = false;
	std::string goal;
	std::vector<std::string> steps;
	std::map<std::string, std::vector<std::string>> group_map;
	std::map<std::string, std::vector<std::string>> template_map;
	std::string save_file_location;
	std::string generate_code_folder_location;

	bool auto_close_generate_script = false;
	bool auto_close_open = false;
	bool auto_close_save = false;
	bool auto_close_save_as = false;

	bool auto_put_furnace = false;
	bool auto_put_burner = false;
	bool auto_put_lab = false;
	bool auto_put_recipe = false;
};

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
																		 { "Utility science pack", {"Flying robot frame", "1", "Low density structure", "3", "Processing unit", "2" }}
																	   };

static const std::map<std::string, std::vector<float>> building_size_list = { 
{ "Wooden chest" , {0.695313f, 0.695313f} },
{ "Iron chest" , {0.695313f, 0.695313f} },
{ "Steel chest" , {0.695313f, 0.695313f} },
{ "Storage tank" , {2.593750f, 2.593750f} },
{ "Transport belt" , {0.796875f, 0.796875f} },
{ "Fast transport belt" , {0.796875f, 0.796875f} },
{ "Express transport belt" , {0.796875f, 0.796875f} },
{ "Underground belt" , {0.796875f, 0.796875f} },
{ "Fast underground belt" , {0.796875f, 0.796875f} },
{ "Express underground belt" , {0.796875f, 0.796875f} },
{ "Splitter" , {1.796875f, 0.796875f} },
{ "Fast splitter" , {1.796875f, 0.796875f} },
{ "Express splitter" , {1.796875f, 0.796875f} },
{ "Loader" , {0.796875f, 1.796875f} },
{ "Fast loader" , {0.796875f, 1.796875f} },
{ "Express loader" , {0.796875f, 1.796875f} },
{ "Burner inserter" , {0.296875f, 0.296875f} },
{ "Inserter" , {0.296875f, 0.296875f} },
{ "Long-handed inserter" , {0.296875f, 0.296875f} },
{ "Fast inserter" , {0.296875f, 0.296875f} },
{ "Filter inserter" , {0.296875f, 0.296875f} },
{ "Stack inserter" , {0.296875f, 0.296875f} },
{ "Stack filter inserter" , {0.296875f, 0.296875f} },
{ "Small electric pole" , {0.296875f, 0.296875f} },
{ "Medium electric pole" , {0.296875f, 0.296875f} },
{ "Big electric pole" , {1.296875f, 1.296875f} },
{ "Substation" , {1.398438f, 1.398438f} },
{ "Pipe" , {0.578125f, 0.578125f} },
{ "Pipe to ground" , {0.578125f, 0.488281f} },
{ "Pump" , {0.578125f, 1.796875f} },
{ "Curved rail" , {1.500000f, 2.144531f} },
{ "Straight rail" , {1.398438f, 1.976563f} },
{ "Train stop" , {1.000000f, 1.000000f} },
{ "Rail signal" , {0.398438f, 0.398438f} },
{ "Rail chain signal" , {0.398438f, 0.398438f} },
{ "Locomotive" , {1.195313f, 5.195313f} },
{ "Cargo wagon" , {1.195313f, 4.796875f} },
{ "Fluid wagon" , {1.195313f, 4.796875f} },
{ "Artillery wagon" , {1.195313f, 4.796875f} },
{ "Car" , {1.398438f, 2.000000f} },
{ "Tank" , {1.796875f, 2.593750f} },
{ "Spidertron" , {2.000000f, 2.000000f} },
{ "Active provider chest" , {0.695313f, 0.695313f} },
{ "Passive provider chest" , {0.695313f, 0.695313f} },
{ "Storage chest" , {0.695313f, 0.695313f} },
{ "Buffer chest" , {0.695313f, 0.695313f} },
{ "Requester chest" , {0.695313f, 0.695313f} },
{ "Roboport" , {3.398438f, 3.398438f} },
{ "Small lamp" , {0.296875f, 0.296875f} },
{ "Arithmetic combinator" , {0.695313f, 1.296875f} },
{ "Decider combinator" , {0.695313f, 1.296875f} },
{ "Constant combinator" , {0.695313f, 0.695313f} },
{ "Power switch" , {1.398438f, 1.398438f} },
{ "Programmable speaker" , {0.593750f, 0.593750f} },
{ "Boiler" , {2.578125f, 1.578125f} },
{ "Steam engine" , {2.500000f, 4.695313f} },
{ "Solar panel" , {2.796875f, 2.796875f} },
{ "Accumulator" , {1.796875f, 1.796875f} },
{ "Nuclear reactor" , {4.398438f, 4.398438f} },
{ "Heat pipe" , {0.593750f, 0.593750f} },
{ "Heat exchanger" , {2.578125f, 1.578125f} },
{ "Steam turbine" , {2.500000f, 4.695313f} },
{ "Burner mining drill" , {1.398438f, 1.398438f} },
{ "Electric mining drill" , {2.796875f, 2.796875f} },
{ "Offshore pump" , {1.195313f, 1.343750f} },
{ "Pumpjack" , {2.398438f, 2.398438f} },
{ "Stone furnace" , {1.398438f, 1.398438f} },
{ "Steel furnace" , {1.398438f, 1.398438f} },
{ "Electric furnace" , {2.398438f, 2.398438f} },
{ "Assembling machine 1" , {2.398438f, 2.398438f} },
{ "Assembling machine 2" , {2.398438f, 2.398438f} },
{ "Assembling machine 3" , {2.398438f, 2.398438f} },
{ "Oil refinery" , {4.796875f, 4.796875f} },
{ "Chemical plant" , {2.398438f, 2.398438f} },
{ "Centrifuge" , {2.398438f, 2.398438f} },
{ "Lab" , {2.398438f, 2.398438f} },
{ "Beacon" , {2.398438f, 2.398438f} },
{ "Rocket silo" , {8.796875f, 8.796875f} },
{ "Land mine" , {0.796875f, 0.796875f} },
{ "Stone wall" , {0.578125f, 0.578125f} },
{ "Gate" , {0.578125f, 0.578125f} },
{ "Gun turret" , {1.398438f, 1.398438f} },
{ "Laser turret" , {1.398438f, 1.398438f} },
{ "Flamethrower turret" , {1.398438f, 2.398438f} },
{ "Artillery turret" , {2.398438f, 2.398438f} },
{ "Radar" , {2.398438f, 2.398438f} },
{ "Item on ground" , {0.273438f, 0.273438f} },
{ "Rocket silo rocket" , {4.000000f, 11.000000f} },
{ "Tile ghost" , {1.000000f, 1.000000f} },
{ "Stone path" , {1, 1} },
{ "Concrete" , {1, 1} },
{ "Hazard concrete left" , {1, 1} },
{ "Hazard concrete right" , {1, 1} },
{ "Refined concrete" , {1, 1} },
{ "Refined hazard concrete left" , {1, 1} },
{ "Refined hazard concrete right" , {1, 1} },
{ "Landfill" , {1, 1} }
};

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
	std::string input = "input";
	std::string output = "output";
	std::string fuel = "fuel";
	std::string modules = "modules";
	std::string chest = "chest";
	std::string wreck = "wreck";
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

static const struct {
	std::string chest = "defines.inventory.chest";
	std::string lab_input = "defines.inventory.lab_input";
	std::string lab_modules = "defines.inventory.lab_modules";
	std::string fuel = "defines.inventory.fuel";
	std::string drill_modules = "defines.inventory.mining_drill_modules";
	std::string assembly_input = "defines.inventory.assembling_machine_input";
	std::string assembly_output = "defines.inventory.assembling_machine_output";
	std::string assembly_modules = "defines.inventory.assembling_machine_modules";
} struct_take_put_list;

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

struct {
	std::string north = "North";
	std::string south = "South";
	std::string east = "East";
	std::string west = "West";

} struct_direction_list;

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