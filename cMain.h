#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <vector>
#include <map>

#include "GUI_Base.h"

class cMain : public GUI_Base {
public:
	cMain();

protected:
	void OnMenuNew(wxCommandEvent& event);
	void OnMenuOpen(wxCommandEvent& event);
	void OnMenuSave(wxCommandEvent& event);
	void OnMenuSaveAs(wxCommandEvent& event);
	void OnMenuExit(wxCommandEvent& event);

	void OnChooseLocation(wxCommandEvent& event);
	void OnGenerateScript(wxCommandEvent& event);
	
	void OnChangeShortcuts(wxCommandEvent& event);

	void OnWalkMenuSelected(wxCommandEvent& event);
	void OnMineMenuSelected(wxCommandEvent& event);
	void OnGameSpeedMenuSelected(wxCommandEvent& event);
	void OnBuildMenuSelected(wxCommandEvent& event);
	void OnFuelMenuSelected(wxCommandEvent& event);
	void OnTakeMenuSelected(wxCommandEvent& event);
	void OnPutMenuSelected(wxCommandEvent& event);
	void OnCraftMenuSelected(wxCommandEvent& event);
	void OnRotateMenuSelected(wxCommandEvent& event);
	void OnAddMenuSelected(wxCommandEvent& event);

	void OnMineChosen(wxCommandEvent& event);
	void OnRotateChosen(wxCommandEvent& event);
	void OnCraftChosen(wxCommandEvent& event); 
	void OnWalkChosen(wxCommandEvent& event);
	void OnBuildChosen(wxCommandEvent& event); 
	void OnGameSpeedChosen(wxCommandEvent& event);
	void OnFuelChosen(wxCommandEvent& event);
	void OnTakeChosen(wxCommandEvent& event);
	void OnPutChosen(wxCommandEvent& event);
	void OnfilterChosen(wxCommandEvent& event);
	void OnRecipeChosen(wxCommandEvent& event);
	void OnTechChosen(wxCommandEvent& event);
	void OnLaunchChosen(wxCommandEvent& event);
	void OnPriorityChosen(wxCommandEvent& event);
	void OnLimitChosen(wxCommandEvent& event);
	void OnTransferChosen(wxCommandEvent& event);
	void OnPickUpChosen(wxCommandEvent& event);
	void OnDropChosen(wxCommandEvent& event);

	void OnBuildingDirectionSelected(wxCommandEvent& event);
	void OnDirectionToBuildSelected(wxCommandEvent& event);

	void OnAddTaskClicked(wxCommandEvent& event);
	void OnChangeTaskClicked(wxCommandEvent& event);
	void OnDeleteTaskClicked(wxCommandEvent& event);
	void OnMoveUpClicked(wxCommandEvent& event);
	void OnMoveDownClicked(wxCommandEvent& event); 
	void OnDuplicateTasksClicked(wxCommandEvent& event);
	
	void OnTasksGridLeftClick(wxGridEvent& event);
	void OnTasksGridDoubleLeftClick(wxGridEvent& event);
	
	void OnBuildingsGridLeftClick(wxGridEvent& event);
	void OnBuildingsGridLeftDoubleClick(wxGridEvent& event);

	void OnWalkKeyDown(wxKeyEvent& event);
	void OnFameKeyDown(wxKeyEvent& event);

private:
	Shortcuts_Menu* shortcuts = nullptr;

	std::string buildings_list_save_indicator = "Buildingsgrid";
	std::string save_file_location_indicator = "File_saved_here";
	std::string generate_file_location_indicator = "Generated_script_saved_here";

	const struct parameter_choices_struct {
		// change combobo, x-cord, y-cord, amount, item category, item, building direction, direction to build, building size, amount of buildings, tech
		std::vector<bool> game_speed = { false, false, false, true, false, false, false, false , false, false, false};
		std::vector<bool> mining = { false, true, true, true, false, false, false, false, false, false, false };
		std::vector<bool> rotate = { false, true, true, true, false, false, false, false, false, false, false };
		std::vector<bool> craft = { false, false, false, true, false, true, false, false, false, false, false };
		std::vector<bool> walk = { false, true, true, false, false, false, false, false, false, false, false };
		std::vector<bool> build = { false, true, true, false, false, true, true, true, true, true, false };
		std::vector<bool> fuel = { false, true, true, true, false, true, false, true, true, true, false };
		std::vector<bool> take = { false, true, true, true, true, true, false, true, true, true, false, false };
		std::vector<bool> put = { false, true, true, true, true, true, false, true, true, true, false, false };
		std::vector<bool> filter = { false, true, true, false, true, true, false, false, true, true, false };
		std::vector<bool> recipe = { false, true, true, false, true, true, false, false, true, true, false };
		std::vector<bool> tech = { false, false, false, false, false, false, false, false, false, false, true };
		std::vector<bool> launch = { false, true, true, false, false, false, false, false, false, false, false };
		std::vector<bool> priority = { false, true, true, false, true, true, false, false, true, true, false };
		std::vector<bool> limit = { false, true, true, true, false, false, false, false, true, true, false };
	};

	parameter_choices_struct parameter_choices;

	int tasks_row_selected = 0;
	int buildings_row_selected = 0;

	std::vector<std::string>::iterator it1;
	std::vector<std::string>::iterator it2;

	std::map<std::string, std::vector<std::string>> task_groups;


	int row_num;
	int list_task_num;
	int list_buildings_num;
	std::string not_relevant = "";
	std::vector<std::string> all_items;
	std::string check;
	std::string item;
	
	std::string units;
	std::string amount_of_buildings;
	std::string building_size;
	std::string x_cord;
	std::string y_cord;
	std::string build_orientation;
	std::string direction_to_build;
	std::string from_into;
	std::string from_into_tasks;
	std::string tech_to_start;

	wxArrayString item_choices;
	wxArrayString take_from_choices;
	wxArrayString tech_choices;
	wxArrayString building_orientation_choices;
	wxArrayString direction_to_build_choices;

	std::string generate_code_file_location = "";
	std::string save_file_location = "";

	std::string open_data_string;

	std::vector<std::string> tasks_data_to_save;
	std::vector<std::string> buildings_data_to_save;

	

	void populate_comboboxes(std::vector<std::string> item_category, std::vector<std::string> item);

	void update_tasks_grid(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string orientation, std::string direction_to_build, std::string building_size, std::string amount_to_build);
	void change_task(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string units, std::string orientation, std::string direction_to_build, std::string building_size, std::string amount_to_build);

	void update_buildings_grid(std::string x_cord, std::string y_cord, std::string item, std::string orientation, std::string recipe, std::string priority, std::string filter);
	void update_buildings_grid_new_building(std::string x_cord, std::string y_cord, std::string item, std::string orientation);
	void update_buildings_grid_from_scratch();
	void update_building_orientation(std::string x_cord, std::string y_cord, std::string units);
	void building_row(std::string x_cord, std::string y_cord, std::string item, std::string build_orientation, std::string direction_to_build, std::string building_size, std::string amount_of_buildings);

	void setup_paramters_comboboxes(std::vector<bool> parameters, std::vector<std::string> combo_item_category, std::vector<std::string> combo_item);

	void setup_paramters(std::vector<bool> parameters);

	bool check_item(const std::string& item, const std::vector<std::string>& all_items);
	bool check_building(const std::string& item, const std::vector<std::string>& all_items);
	bool check_take_put(const std::string& item, const std::vector<std::string>& all_items);

	std::string extract_x_cord();
	std::string extract_y_cord();
	std::string extract_units();
	std::string extract_item();
	std::string extract_amount_of_buildings();
	std::string extract_building_size();
	std::string extract_from_into();
	std::string extract_direction_to_build();
	std::string extract_building_orientation();
	std::string extract_tech();

};


