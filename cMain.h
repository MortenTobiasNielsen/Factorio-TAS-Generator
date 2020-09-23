#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

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
	void OnTakeMenuSelected(wxCommandEvent& event);
	void OnPutMenuSelected(wxCommandEvent& event);
	void OnCraftMenuSelected(wxCommandEvent& event);
	void OnRecipeMenuChosen(wxCommandEvent& event);
	void OnRotateMenuSelected(wxCommandEvent& event);
	void OnAddMenuSelected(wxCommandEvent& event);
	void OnTechMenuSelected(wxCommandEvent& event);
	void OnChangeMenuSelected(wxCommandEvent& event);
	void OnDeleteMenuSelected(wxCommandEvent& event);
	void OnMoveUpMenuSelected(wxCommandEvent& event);
	void OnMoveDownMenuSelected(wxCommandEvent& event);

	void OnMineChosen(wxCommandEvent& event);
	void OnRotateChosen(wxCommandEvent& event);
	void OnCraftChosen(wxCommandEvent& event); 
	void OnWalkChosen(wxCommandEvent& event);
	void OnBuildChosen(wxCommandEvent& event); 
	void OnGameSpeedChosen(wxCommandEvent& event);
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


	// Task
	void OnAddTaskClicked(wxCommandEvent& event);
	void OnChangeTaskClicked(wxCommandEvent& event);
	void OnDeleteTaskClicked(wxCommandEvent& event);
	void OnMoveUpClicked(wxCommandEvent& event);
	void OnMoveDownClicked(wxCommandEvent& event); 

	void OnTasksGridDoubleLeftClick(wxGridEvent& event);

	// Group
	void OnNewGroupClicked(wxCommandEvent& event);
	void OnGroupAddFromTasksListClicked(wxCommandEvent& event);
	void OnGroupAddToTasksListClicked(wxCommandEvent& event);
	void OnGroupChangeClicked(wxCommandEvent& event);
	void OnGroupDeleteClicked(wxCommandEvent& event);
	void OnGroupMoveUpClicked(wxCommandEvent& event);
	void OnGroupMoveDownClicked(wxCommandEvent& event);

	void OnGroupGridDoubleLeftClick(wxGridEvent& event);

	void OnGroupChosen(wxCommandEvent& event);

	// Template
	void OnNewTemplateClicked(wxCommandEvent& event);
	void OnTemplateAddFromTasksListClicked(wxCommandEvent& event);
	void OnTemplateAddToTasksListClicked(wxCommandEvent& event);
	void OnTemplateChangeTaskClicked(wxCommandEvent& event);
	void OnTemplateDeleteTaskClicked(wxCommandEvent& event);
	void OnTemplateMoveUpClicked(wxCommandEvent& event);
	void OnTemplateMoveDownClicked(wxCommandEvent& event);

	void OnTemplateGridDoubleLeftClick(wxGridEvent& event);

	void OnTemplateChosen(wxCommandEvent& event);
	
	// Building
	void OnBuildingsGridLeftDoubleClick(wxGridEvent& event);

private:
	Shortcuts_Menu* shortcuts = nullptr;

	std::string save_groups_indicator = "Groups:";
	std::string save_templates_indicator = "Templates:";

	const struct parameter_choices_struct {
		// x-cord, y-cord, units, item, from/to, tech, building orientation, direction to build, building size, amount of buildings
		std::vector<bool> game_speed = { false, false, true, false, false, false, false , false, false, false};
		std::vector<bool> mining = { true, true, true, false, false, false, false, false, false, false };
		std::vector<bool> rotate = { true, true, true, false, false, false, false, false, false, false };
		std::vector<bool> craft = { false, false, true, true, false, false, false, false, false, false };
		std::vector<bool> walk = { true, true, false, false, false, false, false, false, false, false };
		std::vector<bool> build = { true, true, false, true, false, false, true, true, true, true };
		std::vector<bool> take = { true, true, true, true, true, false, false, true, true, true };
		std::vector<bool> put = { true, true, true, true, true, false, false, true, true, true };
		std::vector<bool> filter = { true, true, false, true, false, false, false, true, true, true };
		std::vector<bool> recipe = { true, true, false, true, false, false, false, true, true, true };
		std::vector<bool> tech = { false, false, false, false, false, true, false, false, false, false };
		std::vector<bool> launch = { true, true, false, false, false, false, false, false, false, false };
		std::vector<bool> priority = { true, true, false, true, false, false, false, true, true, true };
		std::vector<bool> limit = { true, true, true, false, false, false, false, true, true, true };
	};

	parameter_choices_struct parameter_choices;

	std::vector<std::string>::iterator it1;
	std::vector<std::string>::iterator it2;

	std::string segment;
	std::vector<std::string> seglist;
	
	int row_num;
	int row_count;
	int row_to_move;

	std::string data;
	std::string not_relevant = "";
	std::vector<std::string> all_items;

	float x_cord_float;
	float y_cord_float;
	float building_size_float;

	std::string task;
	std::string x_cord;
	std::string y_cord;
	std::string units; 
	std::string item;
	std::string from_into;
	std::string tech_to_start;
	std::string build_orientation;
	std::string direction_to_build;
	std::string building_size;
	std::string amount_of_buildings;
	std::string building;

	std::string recipe;
	std::string priority;
	std::string filter;

	wxArrayString item_choices;
	wxArrayString take_from_choices;
	wxArrayString tech_choices;
	wxArrayString building_orientation_choices;
	wxArrayString direction_to_build_choices;
	wxArrayString group_choices;

	std::string generate_code_file_location = "";
	std::string save_file_location = "";

	std::string open_data_string;
	
	std::string group_name;
	std::vector<std::string> group_list;
	std::map<std::string, std::vector<std::string>> group_map;

	std::string template_name;
	std::vector<std::string> template_list;
	std::map<std::string, std::vector<std::string>> template_map;

	std::vector<std::string> tasks_data_to_save;
	std::vector<std::string> groups_data_to_save;
	std::vector<std::string> template_data_to_save;

	bool move_row(wxGrid* grid, bool up = false);
	bool delete_row(wxGrid* grid);
	bool change_row(wxGrid* grid);

	void update_tasks_grid();
	void change_task();
	void update_buildings_grid();
	void update_buildings_grid_from_scratch();
	void building_row();
	bool update_building_orientation();
	bool update_recipe();
	
	void update_group_grid();
	void update_template_grid();

	void setup_paramters(std::vector<bool> parameters);

	bool setup_for_task_grid();

	void extract_parameters();
	void update_parameteres(wxGrid* grid, wxCommandEvent& event);
	void update_group_map();
	void update_template_map();

	bool check_item(const std::string& item, const std::vector<std::string>& all_items);
	bool check_building(const std::string& item, const std::vector<std::string>& all_items);
	bool check_take_put(const std::string& item, const std::vector<std::string>& all_items);

	void save_file();

	std::string extract_task();
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
	std::string extract_define(int start_row);
};


