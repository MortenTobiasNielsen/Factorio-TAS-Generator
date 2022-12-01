#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#include <iomanip>
#include <locale>
#include <codecvt>
#include <filesystem>

#include "TaskNameToEnum.h"
#include "StepParameters.h"
#include "GridEntry.h"
#include "Building.h"
#include "BuildingNameToIndex.h"
#include "GUI_Base.h"
#include "ScriptProgressBar.h"
#include "../icon.xpm"

using std::string;
using std::vector;
using std::to_string;

class cMain : public GUI_Base
{
public:
	cMain();
	friend TypePanel;

protected:
	void OnApplicationClose(wxCloseEvent& event);

	// File menu items
	void OnMenuNew(wxCommandEvent& event);
	void OnMenuOpen(wxCommandEvent& event);
	void OnMenuSave(wxCommandEvent& event);
	void OnMenuSaveAs(wxCommandEvent& event);
	void OnMenuExit(wxCommandEvent& event);

	// Script menu items
	void OnChooseLocation(wxCommandEvent& event);
	void OnGenerateScript(wxCommandEvent& event);

	// Shortcut menu items
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
	void OnSaveMenuSelected(wxCommandEvent& event);
	void OnStartMenuSelected(wxCommandEvent& event);
	void OnPauseMenuSelected(wxCommandEvent& event);

	// Auto-close menu items
	void OnMenuAutoCloseGenerateScriptClicked(wxCommandEvent& event);
	void OnMenuAutoCloseOpenClicked(wxCommandEvent& event);
	void OnMenuAutoCloseSaveClicked(wxCommandEvent& event);
	void OnMenuAutoCloseSaveAsClicked(wxCommandEvent& event);

	// Radio buttons
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
	void OnSaveChosen(wxCommandEvent& event);
	void OnPriorityChosen(wxCommandEvent& event);
	void OnLimitChosen(wxCommandEvent& event);
	void OnIdleChosen(wxCommandEvent& event);
	void OnPickUpChosen(wxCommandEvent& event);
	void OnDropChosen(wxCommandEvent& event);
	void OnStartChosen(wxCommandEvent& event);
	void OnPauseChosen(wxCommandEvent& event);
	void OnStopChosen(wxCommandEvent& event);

	// Task
	void OnAddTaskClicked(wxCommandEvent& event);
	void OnChangeTaskClicked(wxCommandEvent& event);
	void OnDeleteTaskClicked(wxCommandEvent& event);
	void OnMoveUpClicked(wxCommandEvent& event);
	void OnMoveDownClicked(wxCommandEvent& event);
	void OnMoveUpFiveClicked(wxMouseEvent& event);
	void OnMoveDownFiveClicked(wxMouseEvent& event);

	void OnTasksGridDoubleLeftClick(wxGridEvent& event);

	// Group
	void OnNewGroupClicked(wxCommandEvent& event);
	void OnDeleteGroupClicked(wxCommandEvent& event);
	void OnGroupAddFromTasksListClicked(wxCommandEvent& event);
	void OnGroupAddToTasksListClicked(wxCommandEvent& event);
	void In_memory_extract_parameters(const std::string& task_reference);
	void In_memory_extract_parameters_buildings(const std::string& task_reference);
	void split_task(const std::string& task_reference);
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

	void TemplateAlterTask(int row, wxGrid* grid);

	// Building
	void OnBuildingsGridLeftDoubleClick(wxGridEvent& event);

	// Input
	void OnUnitsChanged(wxCommandEvent& event);

	//Seach
	void TaskSeachOnText(wxCommandEvent& event);
	void TaskSeachOnTextEnter(wxCommandEvent& event);
	void TaskSeachOnSearchButton(wxCommandEvent& event);
	void TaskSeachOnCancelButton(wxCommandEvent& event);
	void BuildingSearchOnText(wxCommandEvent& event);
	void BuildingSearchOnTextEnter(wxCommandEvent& event);
	void BuildingSearchOnSearchButton(wxCommandEvent& event);
	void BuildingSearchOnCancelButton(wxCommandEvent& event);

private:
	std::string software_version = "0.0.5";

	wxString window_title = "EZRaiderz TAS Helper";

	Shortcuts_Menu* shortcuts = nullptr;
	dialog_progress_bar_base* dialog_progress_bar = nullptr;

	std::string generate_code_folder_location = "";
	std::string save_file_location = "";

	std::string open_data_string;

	std::string no_longer_connected = " is no longer connected with a building.\nPlease reverse the change/move or connect the task again by adding a build task in front of it.";
	std::string no_longer_connected_heading = "Tasks are no longer aligned correctly";

	bool auto_close_generate_script = true;
	bool auto_close_open = false;
	bool auto_close_save = true;
	bool auto_close_save_as = false;

	const struct parameter_choices_struct
	{
		// x-cord, y-cord, amount, item, from/to, tech, input, output, building orientation, direction to build, building size, amount of buildings
		std::vector<bool> game_speed = {false, false, true, false, false, false, false, false, false, false, false, false};
		std::vector<bool> mining = {true, true, true, false, false, false, false, false, false, false, false, false};
		std::vector<bool> rotate = {true, true, true, false, false, false, false, false, false, false, false, false};
		std::vector<bool> craft = {false, false, true, true, false, false, false, false, false, false, false, false};
		std::vector<bool> walk = {true, true, false, false, false, false, false, false, false, false, false, false};
		std::vector<bool> build = {true, true, false, true, false, false, false, false, true, true, true, true};
		std::vector<bool> take = {true, true, true, true, true, false, false, false, false, true, true, true};
		std::vector<bool> put = {true, true, true, true, true, false, false, false, false, true, true, true};
		std::vector<bool> filter = {true, true, true, true, false, false, false, false, false, true, true, true};
		std::vector<bool> recipe = {true, true, true, true, false, false, false, false, false, true, true, true};
		std::vector<bool> tech = {false, false, false, true, false, false, false, false, false, false, false, false};
		std::vector<bool> launch = {true, true, false, false, false, false, false, false, false, false, false, false};
		std::vector<bool> save = {false, false, false, false, false, false, false, false, false, false, false, false};
		std::vector<bool> priority = {true, true, false, false, false, false, true, true, false, true, true, true};
		std::vector<bool> limit = {true, true, true, false, false, false, false, false, false, true, true, true};
		std::vector<bool> Start = {false, false, false, false, false, false, false, false, false, false, false, false};
		std::vector<bool> Pause = {false, false, false, false, false, false, false, false, false, false, false, false};
		std::vector<bool> stop = {false, false, true, false, false, false, false, false, false, false, false, false};
		std::vector<bool> drop = {true, true, false, true, false, false, false, false, false, true, true, true};
		std::vector<bool> pick = {false, false, true, false, false, false, false, false, false, false, false, false};
		std::vector<bool> idle = {false, false, true, false, false, false, false, false, false, false, false, false};
	};

	parameter_choices_struct parameter_choices;

	std::vector<std::string>::iterator it1;
	std::vector<std::string>::iterator it2;

	std::string segment;
	std::vector<std::string> seglist;
	std::vector<std::string> task_segments;

	std::vector<std::string> row_selections;

	long long row_num;
	long long row_count;

	long long building_row_num;
	long long building_row_count;

	long long group_row_num;
	long long group_row_count;

	long long template_row_num;
	long long template_row_count;

	long long row_to_move;

	bool mine_building_found;

	std::string task_number;

	std::string data;
	std::string not_relevant = "";
	wxString new_not_relevant = "";
	std::vector<std::string> all_buildings;
	std::vector<std::string> all_items;
	std::vector<std::string> part_assembly_recipes;
	std::vector<std::string> full_assembly_recipes;
	std::vector<std::string> full_chemical_plant_recipes;
	std::vector<std::string> all_recipes;

	// Overall variables for parameters
	std::string task;
	std::string x_cord;
	std::string y_cord;
	std::string amount;
	std::string comment;
	std::string item;
	std::string from_into;
	std::string tech_to_start;
	std::string build_orientation;
	std::string direction_to_build;
	std::string building_size;
	std::string amount_of_buildings;

	int amount_of_buildings_int;

	std::string building;

	// Variables specific to the buildings grid
	std::string building_task;
	std::string building_x_cord;
	std::string building_y_cord;
	std::string building_units;
	std::string building_item;
	std::string building_build_orientation;
	std::string building_direction_to_build;
	std::string building_building_size;
	std::string building_amount_of_buildings;
	std::string building_priority_in;
	std::string building_priority_out;
	std::string building_comment;

	int building_amount_of_buildings_int;

	std::string limit;
	std::string recipe;
	std::string priority_in;
	std::string priority_out;
	std::string filter;

	// Arrays used to populate combo boxes
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

	// For group and template strucktures
	std::string group_name;
	std::vector<std::string> group_list;
	std::map<std::string, std::vector<std::string>> group_map;

	std::string template_name;
	std::vector<std::string> template_list;
	std::map<std::string, std::vector<std::string>> template_map;

	// Used when the tasks are saved to a file
	std::vector<std::string> tasks_data_to_save;
	std::vector<StepParameters> StepGridData;
	vector<Building> BuildingsSnapShot;

	void reset_to_new_window();
	bool checks_before_reset_window();
	bool check_before_close();

	void move_row(wxGrid* grid, bool up = false);
	bool delete_row(wxGrid* grid, wxComboBox* cmb, std::map<std::string, std::vector<std::string>>& map);
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

	void group_template_move_row(wxGrid* grid, wxComboBox* cmb, bool up, std::map<std::string, std::vector<std::string>>& map);

	void update_group_template_grid(wxGrid* grid, std::vector<std::string>& list, std::map<std::string, std::vector<std::string>>& map, std::string map_name);
	void grid_extract_parameters(const int& row, wxGrid* grid);
	void grid_insert_data(const int& row, wxGrid* grid);

	void setup_paramters(std::vector<bool> parameters);

	void populate_tasks_grid();

	bool setup_for_task_group_template_grid();

	bool find_building_for_script(int& row);

	bool compare_task_strings(const wxString& str1, const std::string& str2);

	void update_parameters(wxGrid* grid, wxCommandEvent& event);
	void update_group_map();
	void update_template_map();

	bool check_input(std::string& item, const std::vector<std::string>& all_items);
	bool check_take_put(std::string& item);
	bool check_buildings_grid();

	bool extra_building_checks();

	bool save_file(bool save_as);

	void extract_parameters();
	std::string extract_task();
	std::string extract_x_cord();
	std::string extract_y_cord();
	std::string extract_amount();
	std::string extract_comment();
	std::string extract_item();
	std::string extract_from_into();
	std::string extract_tech();
	std::string extract_priority_in();
	std::string extract_priority_out();
	std::string extract_building_orientation();
	std::string extract_direction_to_build();
	std::string extract_building_size();
	std::string extract_amount_of_buildings();

	void auto_put(std::string put_item, std::string put_amount, std::string put_into);

	void update_future_rotate_tasks();
	void find_new_orientation();
	bool find_building(int amount_of_buildings);

	void malformed_saved_file_message();

	void new_update_tasks_grid(StepParameters* stepParameters);
	GridEntry PrepareStepParametersForGrid(StepParameters* stepParameters);
	StepParameters ExtractStepParameters();
	double new_extract_x_cord();
	double new_extract_y_cord();
	int new_extract_building_size();
	int new_extract_amount_of_buildings();

	void new_background_colour_update(wxGrid* grid, int row, TaskName task);

	bool new_check_input(string& item, const std::vector<std::string>& all_items);

	bool IsValidBuildStep(StepParameters stepParameters);
	bool IsValidRecipeStep(StepParameters stepParameters);
	bool IsValidCraftStep(StepParameters stepParameters);
	bool IsValidPutTakeStep(StepParameters stepParameters);
	bool IsValidTechnologyStep(StepParameters stepParameters);
	bool IsValidPriorityStep(StepParameters stepParameters);

	bool new_find_building(int startRow, StepParameters stepParameters);
	bool new_extra_building_checks(StepParameters stepParameters);

	int GenerateBuildingSnapShot(int end_row);
	void new_populate_tasks_grid();

	void AddTask(int row);
	void DeleteStepsRelatedToBuilding(int startRow, int RowsToDelete);
};