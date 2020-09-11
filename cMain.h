#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <vector>

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
	void OnDeleteTaskClicked(wxCommandEvent& event);
	
	void OnTasksGridLeftClick(wxGridEvent& event);
	void OnTasksGridDoubleLeftClick(wxGridEvent& event);
	
	void OnBuildingsGridLeftClick(wxGridEvent& event);
	void OnBuildingsGridLeftDoubleClick(wxGridEvent& event);

	void OnWalkKeyDown(wxKeyEvent& event);
	void OnFameKeyDown(wxKeyEvent& event);

private:
	Shortcuts_Menu* shortcuts = nullptr;

	const static int task_list_game_speed_white_space = 0;
	const static int Task_list_walk_white_space = 20;

	const struct parameter_choices_struct {
		// change combobo, x-cord, y-cord, amount, item category, item, building direction, direction to build, building size, amount of buildings, tech
		std::vector<bool> game_speed = { false, false, false, true, false, false, false, false , false, false, false};
		std::vector<bool> mining = { false, true, true, true, false, false, false, false, false, false, false };
		std::vector<bool> rotate = { false, true, true, true, false, false, false, false, false, false, false };
		std::vector<bool> craft = { false, false, false, true, false, true, false, false, false, false, false };
		std::vector<bool> walk = { false, true, true, false, false, false, false, false, false, false, false };
		std::vector<bool> build = { false, true, true, false, true, true, true, true, true, true, false };
		std::vector<bool> fuel = { false, true, true, true, false, true, false, true, true, true, false };
		std::vector<bool> take = { false, true, true, true, true, true, false, true, true, true, false, false };
		std::vector<bool> put = { false, true, true, true, true, true, false, false, true, true, false };
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


	int row_num;
	int list_task_num;
	int list_buildings_num;
	std::string not_relevant = "";
	std::vector<std::string> all_items;
	std::string check;
	std::string item;
	std::string file_location;
	std::string units;
	std::string amount_of_buildings;
	std::string building_size;
	std::string x_cord;
	std::string y_cord;
	std::string build_direction;
	std::string direction_to_build;
	std::string from_into;
	std::string from_into_tasks;

	wxArrayString item_choices;
	wxArrayString take_from_choices;
	wxArrayString tech_choices;
	

	void populate_comboboxes(std::vector<std::string> item_category, std::vector<std::string> item);

	void update_tasks_grid(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string amount, std::string building_direction, std::string direction_to_build, std::string amount_to_build, std::string building_size);

	void update_buildings_grid_new_building(std::string x_cord, std::string y_cord, std::string item, std::string orientation);

	void setup_paramters_comboboxes(std::vector<bool> parameters, std::vector<std::string> combo_item_category, std::vector<std::string> combo_item);

	void setup_paramters(std::vector<bool> parameters);
};


