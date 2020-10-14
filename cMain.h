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
	void OnApplicationClose(wxCloseEvent& event);

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
	void OnPriorityMenuSelected(wxCommandEvent& event);
	void OnLimitMenuSelected(wxCommandEvent& event);
	void OnFilterMenuSelected(wxCommandEvent& event);
	void OnStopMenuSelected(wxCommandEvent& event);
	void OnIdleMenuSelected(wxCommandEvent& event);
	void OnLaunchMenuSelected(wxCommandEvent& event);
	void OnDropMenuSelected(wxCommandEvent& event);
	void OnPickUpMenuSelected(wxCommandEvent& event);

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
	void OnIdleChosen(wxCommandEvent& event);
	void OnPickUpChosen(wxCommandEvent& event);
	void OnDropChosen(wxCommandEvent& event);
	void OnStopChosen(wxCommandEvent& event);


	// Task
	void OnAddTaskClicked(wxCommandEvent& event);
	void OnChangeTaskClicked(wxCommandEvent& event);
	void OnDeleteTaskClicked(wxCommandEvent& event);
	void OnMoveUpClicked(wxCommandEvent& event);
	void OnMoveDownClicked(wxCommandEvent& event); 

	void OnTasksGridDoubleLeftClick(wxGridEvent& event);

	// Group
	void OnNewGroupClicked(wxCommandEvent& event);
	void OnDeleteGroupClicked(wxCommandEvent& event);
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
	void OnDeleteTemplateClicked(wxCommandEvent& event);
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
	std::string save_file_indicator = "Save file location:";
	std::string code_file_indicator = "Task folder location:";

	const struct parameter_choices_struct {
		// x-cord, y-cord, units, item, from/to, tech, input, output, building orientation, direction to build, building size, amount of buildings
		std::vector<bool> game_speed = { false, false, true, false, false, false, false, false, false , false, false, false};
		std::vector<bool> mining = { true, true, true, false, false, false, false, false, false, false, false, false };
		std::vector<bool> rotate = { true, true, true, false, false, false, false, false, false, false, false, false };
		std::vector<bool> craft = { false, false, true, true, false, false, false, false, false, false, false, false };
		std::vector<bool> walk = { true, true, false, false, false, false, false, false, false, false, false, false };
		std::vector<bool> build = { true, true, false, true, false, false, false, false, true, true, true, true };
		std::vector<bool> take = { true, true, true, true, true, false, false, false, false, true, true, true };
		std::vector<bool> put = { true, true, true, true, true, false, false, false, false, true, true, true };
		std::vector<bool> filter = { true, true, true, true, false, false, false, false, false, true, true, true };
		std::vector<bool> recipe = { true, true, false, true, false, false, false, false, false, true, true, true };
		std::vector<bool> tech = { false, false, false, false, false, true, false, false, false, false, false, false };
		std::vector<bool> launch = { true, true, false, false, false, false, false, false, false, false, false, false };
		std::vector<bool> priority = { true, true, false, false, false, false, true, true, false, true, true, true };
		std::vector<bool> limit = { true, true, true, false, false, false, false, false, false, true, true, true };
		std::vector<bool> stop = { false, false, true, false, false, false, false, false, false , false, false, false };
		std::vector<bool> drop = { true, true, false, true, false, false, false, false, false , true, true, true };
		std::vector<bool> pick = { true, true, false, false, false, false, false, false, false , true, true, true };
		std::vector<bool> idle = { false, false, true, false, false, false, false, false, false , false, false, false };
	};

	parameter_choices_struct parameter_choices;

	

	std::vector<std::string>::iterator it1;
	std::vector<std::string>::iterator it2;

	std::string segment;
	std::vector<std::string> seglist;
	
	int row_num;
	int row_count;

	int building_row_num;
	int building_row_count;

	int group_row_num;
	int group_row_count;

	int template_row_num;
	int template_row_count;

	int row_to_move;

	std::string data;
	std::string not_relevant = "";
	std::vector<std::string> all_buildings;
	std::vector<std::string> all_items;
	std::vector<std::string> part_assembly_recipes;
	std::vector<std::string> full_assembly_recipes;
	std::vector<std::string> full_chemical_plant_recipes;
	std::vector<std::string> all_recipes;

	float x_cord_float;
	float y_cord_float;
	float building_size_float;

	float new_x_cord; // Should most likely be std::string or removed 
	float new_y_cord; // Should most likely be std::string or removed 

	// Overall variables for parameters
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
	std::string new_orientation;

	// Variables specific to the buildings grid
	std::string building_task;
	std::string building_x_cord;
	std::string building_y_cord;
	std::string building_units;
	std::string building_item;
	//std::string building_from_into;
	//std::string building_tech_to_start;
	std::string building_build_orientation;
	std::string building_direction_to_build;
	std::string building_building_size;
	std::string building_amount_of_buildings;
	std::string building_priority_in;
	std::string building_priority_out;
	//std::string building_building;
	//std::string building_new_orientation;

	std::string x_cord_origen;
	std::string y_cord_origen;

	std::string limit;
	std::string recipe;
	std::string priority_in;
	std::string priority_out;
	std::string filter;

	wxArrayString item_choices;
	wxArrayString take_from_choices;
	wxArrayString tech_choices;
	wxArrayString building_orientation_choices;
	wxArrayString direction_to_build_choices;
	wxArrayString group_choices;
	wxArrayString template_choices;
	wxArrayString input_output_choices;
	wxArrayString handcrafted_choices;
	wxArrayString recipe_choices;
	wxArrayString filter_take_put_drop_choices;
	wxArrayString building_choices;

	std::string generate_code_folder_location = "";
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

	void reset_to_new_window();
	bool check_before_close();

	bool move_row(wxGrid* grid, bool up = false);
	bool delete_row(wxGrid* grid);
	bool change_row(wxGrid* grid);

	void update_tasks_grid();
	void update_buildings_grid();
	void update_buildings_grid_from_scratch(int start_row, int end_row);
	void update_buildings();
	bool update_recipe();
	bool update_limit();
	bool update_priority();
	bool update_filter();
	bool Update_rotation();

	void background_colour_update(wxGrid* grid, int row, std::string task);
	
	void update_group_template_grid(wxGrid* grid, std::vector<std::string>& list, std::map<std::string, std::vector<std::string>>& map, std::string map_name);
	void grid_extract_parameters(const int& row, wxGrid* grid);
	void grid_insert_data(const int& row, wxGrid* grid);

	void setup_paramters(std::vector<bool> parameters);

	bool setup_for_task_grid();

	
	void update_parameteres(wxGrid* grid, wxCommandEvent& event);
	void update_group_map();
	void update_template_map();

	bool check_input (std::string& item, const std::vector<std::string>& all_items);
	bool check_take_put(const std::string& item);
	bool check_buildings_grid();
	bool check_mine_building();

	bool extra_building_checks();

	bool save_file(bool save_as);


	void extract_parameters();
	std::string extract_task();
	std::string extract_x_cord();
	std::string extract_y_cord();
	std::string extract_units();
	std::string extract_item();
	std::string extract_from_into();
	std::string extract_tech();
	std::string extract_priority_in();
	std::string extract_priority_out();
	std::string extract_building_orientation();
	std::string extract_direction_to_build();
	std::string extract_building_size();
	std::string extract_amount_of_buildings();

	
	
	
	
	std::string extract_define(int start_row);
	bool extract_building(int start_row);
	bool extract_building_info();

	int find_row_num(wxGrid* grid);

	void update_coordinates();
	void update_future_rotate_tasks();
	void find_new_orientation();
	bool find_old_orientation();
	bool find_building();
};