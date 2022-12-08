#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <wx/aui/auibook.h>

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <filesystem>

#include "Building.h"
#include "BuildingNameToIndex.h"
#include "Functions.h"
#include "GUI_Base.h"
#include "GenerateScript.h"
#include "GridEntry.h"
#include "OpenTas.h"
#include "SaveTas.h"
#include "StepParameters.h"
#include "SearchUtil.h"
#include "DialogProgressBar.h"
#include "TaskNameToEnum.h"
#include "utils.h"

#include "../icon.xpm"

using std::string;
using std::vector;
using std::pair;
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
	void NewTemplateAlterTask(StepParameters& step);

	//Seach
	void TaskSeachOnText(wxCommandEvent& event);
	void TaskSeachOnTextEnter(wxCommandEvent& event);
	void TaskSeachOnSearchButton(wxCommandEvent& event);
	void TaskSeachOnCancelButton(wxCommandEvent& event);

private:
	wxString window_title = "EZRaiderz TAS Helper";

	DialogProgressBar* dialog_progress_bar = nullptr;

	string generate_code_folder_location = "";
	string save_file_location = "";

	bool auto_close_generate_script = true;
	bool auto_close_open = false;
	bool auto_close_save = true;
	bool auto_close_save_as = false;

	const struct parameter_choices_struct
	{
		// x-cord, y-cord, amount, item, from/to, tech, input, output, building orientation, direction to build, building size, amount of buildings
		vector<bool> game_speed = {false, false, true, false, false, false, false, false, false, false, false, false};
		vector<bool> mining = {true, true, true, false, false, false, false, false, false, false, false, false};
		vector<bool> rotate = {true, true, true, false, false, false, false, false, false, false, false, false};
		vector<bool> craft = {false, false, true, true, false, false, false, false, false, false, false, false};
		vector<bool> walk = {true, true, false, false, false, false, false, false, false, false, false, false};
		vector<bool> build = {true, true, false, true, false, false, false, false, true, true, true, true};
		vector<bool> take = {true, true, true, true, true, false, false, false, false, true, true, true};
		vector<bool> put = {true, true, true, true, true, false, false, false, false, true, true, true};
		vector<bool> filter = {true, true, true, true, false, false, false, false, false, true, true, true};
		vector<bool> recipe = {true, true, true, true, false, false, false, false, false, true, true, true};
		vector<bool> tech = {false, false, false, true, false, false, false, false, false, false, false, false};
		vector<bool> launch = {true, true, false, false, false, false, false, false, false, false, false, false};
		vector<bool> save = {false, false, false, false, false, false, false, false, false, false, false, false};
		vector<bool> priority = {true, true, false, false, false, false, true, true, false, true, true, true};
		vector<bool> limit = {true, true, true, false, false, false, false, false, false, true, true, true};
		vector<bool> Start = {false, false, false, false, false, false, false, false, false, false, false, false};
		vector<bool> Pause = {false, false, false, false, false, false, false, false, false, false, false, false};
		vector<bool> stop = {false, false, true, false, false, false, false, false, false, false, false, false};
		vector<bool> drop = {true, true, false, true, false, false, false, false, false, true, true, true};
		vector<bool> pick = {false, false, true, false, false, false, false, false, false, false, false, false};
		vector<bool> idle = {false, false, true, false, false, false, false, false, false, false, false, false};
	} parameter_choices;

	vector<string> row_selections;

	string not_relevant = "";
	wxString new_not_relevant = "";
	
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
	map<string, vector<StepParameters>> group_map;
	map<string, vector<StepParameters>> template_map;

	void ResetToNewWindow();
	bool ChecksBeforeResetWindow();
	bool CheckBeforeClose();

	void MoveRow(wxGrid* grid, bool up = false);
	void GroupTemplateMoveRow(wxGrid* grid, wxComboBox* cmb, bool up, map<string, vector<StepParameters>>& map);
	bool DeleteRow(wxGrid* grid, wxComboBox* cmb, map<string, vector<StepParameters>>& map);
	bool ChangeRow(wxGrid* grid, StepParameters step);

	void BackgroundColorUpdate(wxGrid* grid, int row, TaskName task);

	void UpdateMapWithNewSteps(wxGrid* grid, wxComboBox* cmb, map<string, vector<StepParameters>>& map);
	void UpdateGroupTemplateGrid(wxGrid* grid, vector<StepParameters>& steps);

	void setup_paramters(std::vector<bool> parameters);

	void UpdateParameters(GridEntry* gridEntry, wxCommandEvent& event);

	bool CheckTakePut(std::string& item);

	bool SaveFile(bool save_as);

	string ExtractTask();
	string ExtractAmount();

	void update_future_rotate_tasks();
	string find_new_orientation(string originalOrientaion, const int& rotateAmount);

	void malformed_saved_file_message();

	void UpdateStepGrid(int row, StepParameters* stepParameters);
	GridEntry PrepareStepParametersForGrid(StepParameters* stepParameters);
	StepParameters ExtractStepParameters();

	bool new_find_building(int startRow, StepParameters stepParameters);
	

	int GenerateBuildingSnapShot(int end_row);
	void PopulateStepGrid();

	void AddTask(int row);
	void DeleteStepsRelatedToBuilding(int startRow, int RowsToDelete);
	void GridTransfer(wxGrid* from, const int& fromRow, wxGrid* to, const int& toRow);
	GridEntry ExtractGridEntry(wxGrid* grid, const int& row);

	bool ValidateStep(const int& row, StepParameters& stepParameters, bool validateBuildSteps = true);
	bool IsValidBuildStep(StepParameters& stepParameters);
	bool IsValidRecipeStep(StepParameters& stepParameters);
	bool IsValidCraftStep(StepParameters& stepParameters);
	bool IsValidPutTakeStep(StepParameters& stepParameters);
	bool IsValidTechnologyStep(StepParameters& stepParameters);
	bool IsValidPriorityStep(StepParameters& stepParameters);

	bool CheckTakePut(StepParameters& stepParameters);
	bool ExtraBuildingChecks(StepParameters& stepParameters);

	vector<string> all_buildings;
	vector<string> all_items;
	vector<string> part_assembly_recipes;
	vector<string> full_assembly_recipes;
	vector<string> full_chemical_plant_recipes;
	vector<string> all_recipes;
	vector<StepParameters> StepGridData;
	vector<Building> BuildingsSnapShot;
};