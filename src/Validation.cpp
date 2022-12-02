#include "Validation.h"

bool ValidateStep(int row, StepParameters stepParameters, bool validateBuildSteps = true)
{
	// Cases where an association with a building isn't needed
	switch (stepParameters.TaskEnum)
	{
		case e_start:
		case e_walk:
		case e_game_speed:
		case e_pause:
		case e_save:
		case e_stop:
		case e_pick_up:
		case e_idle:
			return;

		case e_build:
			return IsValidBuildStep(stepParameters);

		case e_craft:
			return IsValidCraftStep(stepParameters);

		case e_tech:
			return IsValidTechnologyStep(stepParameters);

		default:
			break;
	}

	if (!validateBuildSteps)
	{
		return;
	}

	int amountOfBuildings = GenerateBuildingSnapShot(row);
	switch (stepParameters.TaskEnum)
	{
		case e_recipe:
			if (!BuildingExists(BuildingsSnapShot, amountOfBuildings, stepParameters))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
				return false;
			};

			return IsValidRecipeStep(stepParameters);

		case e_mine:
			// A building doesn't need to exist, but if it does it should be noted.
			BuildingExists(BuildingsSnapShot, amountOfBuildings, stepParameters);

		case e_put:
		case e_take:
			if (!IsValidPutTakeStep(stepParameters))
			{
				return false;
			}

			if (!BuildingExists(BuildingsSnapShot, amountOfBuildings, stepParameters))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
				return false;
			};

			return true;

		default:

			if (!BuildingExists(BuildingsSnapShot, amountOfBuildings, stepParameters))
			{
				wxMessageBox("Building location doesn't exist.\n1. Please use exactly the same coordinates as you used to build \n2. Check that you have not removed the building(s)\n3. Check that you are not putting this task before the Build task", "Please use the same coordinates");
				return false;
			};

			return true;
	}
}

bool IsValidBuildStep(StepParameters stepParameters)
{
	if (!check_input(stepParameters.Item, all_buildings))
	{
		wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
		return false;
	}

	if (!check_input(stepParameters.Orientation, build_orientations))
	{
		wxMessageBox("The build direction is not valid - please try again", "Please use the build direction dropdown menu");
		return false;
	}

	if (!check_input(stepParameters.Direction, build_orientations))
	{
		wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
		return false;
	}

	return true;
}

bool IsValidRecipeStep(StepParameters stepParameters)
{
	switch (stepParameters.BuildingIndex)
	{
		case AssemblingMachine1:
			if (check_input(stepParameters.Item, part_assembly_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an assembling machine 1", "Item chosen is not valid");
			return false;

		case AssemblingMachine2:
		case AssemblingMachine3:
			if (check_input(stepParameters.Item, full_assembly_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an assembling machine", "Item chosen is not valid");
			return false;

		case OilRefinery:
			if (!check_input(stepParameters.Item, oil_refinery_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for an oil refinery", "Item chosen is not valid");
			return false;

		case ChemicalPlant:
			if (!check_input(stepParameters.Item, full_chemical_plant_recipes))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a chemical plant", "Item chosen is not valid");
			return false;

		case Centrifuge:
			if (!check_input(stepParameters.Item, centrifuge_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a centrifuge", "Item chosen is not valid");
			return false;

		case StoneFurnace:
		case SteelFurnace:
		case ElectricFurnace:
			if (!check_input(stepParameters.Item, furnace_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a valid recipe for a furnace", "Item chosen is not valid");
			return false;

		default:
			return true;;
	}
}

bool IsValidCraftStep(StepParameters stepParameters)
{
	if (!check_input(stepParameters.Item, handcrafted_list))
	{
		wxMessageBox("The item chosen is not valid - please try again", "Please use the item dropdown menu");
		return false;
	}

	return true;
}

bool IsValidPutTakeStep(StepParameters stepParameters)
{
	if (!CheckTakePut(stepParameters))
	{
		return false;
	}

	if (!check_input(stepParameters.Direction, build_orientations))
	{
		wxMessageBox("The direction to build is not valid - please try again", "Please use the direction to build dropdown menu");
		return false;
	}

	return true;
}

bool IsValidTechnologyStep(StepParameters stepParameters)
{
	if (!check_input(stepParameters.Item, tech_list))
	{
		wxMessageBox("The tech is not valid - please try again", "Please use the tech dropdown menu");
		return false;
	}

	return true;
}

bool CheckTakePut(StepParameters stepParameters)
{
	std::string to_check = stepParameters.FromInto;
	string_capitalized(to_check);

	if (to_check == "Wreck")
	{
		return true;
	}

	string building = FindBuildingName(stepParameters.BuildingIndex);
	if (check_input(building, chest_list))
	{
		if (to_check == "Chest")
		{
			return true;
		}

		wxMessageBox("Only Chest is a valid \"From/Into\" choice for a chest", "Please choose chest");
		return false;
	}

	if (to_check == "Fuel")
	{
		if (check_input(stepParameters.Item, fuel_list))
		{
			return true;
		}

		wxMessageBox("The item chosen is not a valid fuel", "Please select a valid fuel");
		return false;
	}

	if (building == "Lab")
	{
		if (to_check == "Input")
		{
			if (check_input(stepParameters.Item, science_packs))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a science pack.\nOnly science packs can be used as input for a lab", "Please choose a science pack");
			return false;

		}
		else if (to_check == "Modules")
		{
			if (check_input(stepParameters.Item, module_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a module", "Please choose a module");
			return false;
		}

		wxMessageBox("Only Input and Modules are valid \"From/Into\" choices for a lab", "Please choose input or modules");
		return false;
	}

	if (check_input(building, drills_list))
	{
		if (to_check == "Modules")
		{
			if (check_input(stepParameters.Item, module_list))
			{
				return true;
			}

			wxMessageBox("The item chosen is not a module", "Please choose a module");
			return false;
		}

		wxMessageBox("Only Modules is a valid \"From/Into\" choice for a drill/Pump", "Please choose modules");
		return false;
	}

	if (to_check == "Input")
	{
		// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
		return true;
	}

	if (to_check == "Modules")
	{
		if (check_input(stepParameters.Item, module_list))
		{
			return true;
		}

		wxMessageBox("The item chosen is not a module", "Please choose a module");
		return false;
	}

	if (to_check == "Output")
	{
		// You might want to make some check that the input makes sense - but it might be pretty difficult to do in a good way
		return true;
	}

	wxMessageBox("Building location does not seem to exist.\nPlease use exactly the same coordinates as you used to build", "Please use the same coordinates");
	return false;
}

// TODO: It seems like this should be used somewhere.
bool new_extra_building_checks(StepParameters stepParameters)
{
	auto buildingName = FindBuildingName(stepParameters.BuildingIndex);

	switch (stepParameters.TaskEnum)
	{
		case e_limit:
			return check_input(buildingName, chest_list);

		case e_priority:
			return check_input(buildingName, splitter_list);

		case e_filter:
			return check_input(buildingName, splitter_list) && check_input(buildingName, filter_inserter_list);

		default:
			return true;
	}
}