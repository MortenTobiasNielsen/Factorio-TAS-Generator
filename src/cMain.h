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

#include "GUI_Base.h"
#include "GenerateScript.h"
#include "SearchUtil.h"
#include "DialogProgressBar.h"

#include "Data\utils.h"
#include "Data\Inventory.h"
#include "Data\BuildingNames.h"

#include "Structures\Building.h"
#include "Structures\ParameterChoices.h"
#include "Structures\Priority.h"
#include "Structures\StepType.h"
#include "Structures\GridEntry.h"
#include "Structures\StepParameters.h"

#include "TAS save file\OpenTas.h"
#include "TAS save file\SaveTas.h"
#include "TAS save file\TasFileConstants.h"

#include "Shared functions\Functions.h"

#include "../icon.xpm"
#include "CommandStack.h"

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
	void Open(std::ifstream *);
	void OnMenuOpen(wxCommandEvent& event);
	void OnMenuSave(wxCommandEvent& event);
	void OnMenuSaveAs(wxCommandEvent& event);
	void OnMenuExit(wxCommandEvent& event);

	// Script menu items
	void OnChooseLocation(wxCommandEvent& event);
	std::string GetGoalConfig();
	log_config GetLogConfig();
	void OnGenerateScript(wxCommandEvent& event);

	// Step types menu
	void OnChangeSteptypeColoursMenuSelected(wxCommandEvent& event);

	void OnWalkMenuSelected(wxCommandEvent& event);
	void OnCraftMenuSelected(wxCommandEvent& event);
	void OnTechMenuSelected(wxCommandEvent& event);
	void OnIdleMenuSelected(wxCommandEvent& event);
	void OnPickUpMenuSelected(wxCommandEvent& event);
	void OnDropMenuSelected(wxCommandEvent& event);
	void OnCancelCraftingMenuSelected(wxCommandEvent& event);
	void OnMineMenuSelected(wxCommandEvent& event);
	void OnThrowMenuSelected(wxCommandEvent& event);
	void OnShootMenuSelected(wxCommandEvent& event);

	void OnTakeMenuSelected(wxCommandEvent& event);
	void OnPutMenuSelected(wxCommandEvent& event);
	void OnBuildMenuSelected(wxCommandEvent& event);
	void OnRecipeMenuChosen(wxCommandEvent& event);
	void OnLimitMenuSelected(wxCommandEvent& event);
	void OnFilterMenuSelected(wxCommandEvent& event);
	void OnPriorityMenuSelected(wxCommandEvent& event);
	void OnLaunchMenuSelected(wxCommandEvent& event);
	void OnRotateMenuSelected(wxCommandEvent& event);

	void OnGameSpeedMenuSelected(wxCommandEvent& event);
	void OnPauseMenuSelected(wxCommandEvent& event);
	void OnStopMenuSelected(wxCommandEvent& event);
	void OnSaveMenuSelected(wxCommandEvent& event);
	void OnNeverIdleMenuSelected(wxCommandEvent& event);
	void OnKeepWalkingMenuSelected(wxCommandEvent& event);
	void OnKeepOnPathMenuSelected(wxCommandEvent& event);
	void OnKeepCraftingMenuSelected(wxCommandEvent& event);

	// Shortcut menu
	void OnChangeShortcutMenuSelected(wxCommandEvent& event);

	void OnAddMenuSelected(wxCommandEvent& event);
	void OnAddAltMenuSelected(wxCommandEvent& event);
	void OnChangeMenuSelected(wxCommandEvent& event);
	void OnChangeAltMenuSelected(wxCommandEvent& event);
	void OnDeleteMenuSelected(wxCommandEvent& event);
	void OnDeleteAltMenuSelected(wxCommandEvent& event);
	void OnMoveUpMenuSelected(wxCommandEvent& event);
	void OnMoveUpAltMenuSelected(wxCommandEvent& event);
	void OnMoveDownMenuSelected(wxCommandEvent& event);
	void OnMoveDownAltMenuSelected(wxCommandEvent& event);
	void OnSearchMenuSelected(wxCommandEvent& event);

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
	void OnCancelCraftingChosen(wxCommandEvent& event);
	void OnPriorityChosen(wxCommandEvent& event);
	void OnLimitChosen(wxCommandEvent& event);
	void OnIdleChosen(wxCommandEvent& event);
	void OnShootChosen(wxCommandEvent& event);
	void OnThrowChosen(wxCommandEvent& event);
	void OnPickUpChosen(wxCommandEvent& event);
	void OnDropChosen(wxCommandEvent& event);
	void OnPauseChosen(wxCommandEvent& event);
	void OnStopChosen(wxCommandEvent& event);
	void OnNeverIdleChosen(wxCommandEvent& event);
	void OnKeepWalkingChosen(wxCommandEvent& event);
	void OnKeepOnPathChosen(wxCommandEvent& event);
	void OnKeepCraftingChosen(wxCommandEvent& event);

	// Modifiers
	void OnNoOrderClicked(wxCommandEvent& event);
	void OnNoOrderRightClicked(wxMouseEvent& event);
	void NoOrderButtonHandle(bool force = false);
	void OnSkipClicked(wxCommandEvent& event);
	void OnForceClicked(wxCommandEvent& event);
	void OnForceRightClicked(wxMouseEvent& event);
	void ForceButtonHandle(bool force = false);

	// walk panel
	void SetupWalkPanelUnicodeCharacters();
	int AddWalkScanStartRow();
	pair<double, double> AddWalkScanCurrentPosition();
	void CreateWalkStep(int x_modifier, int y_modifier);
	void OnWalkPanelBtnUpLeftClicked(wxCommandEvent& event);
	void OnWalkPanelBtnUpClicked(wxCommandEvent& event);
	void OnWalkPanelBtnUpRightClicked(wxCommandEvent& event);
	void OnWalkPanelBtnLeftClicked(wxCommandEvent& event);
	void OnWalkPanelBtnRightClicked(wxCommandEvent& event);
	void OnWalkPanelBtnDownLeftClicked(wxCommandEvent& event);
	void OnWalkPanelBtnDownClicked(wxCommandEvent& event);
	void OnWalkPanelBtnDownRightClicked(wxCommandEvent& event);
	

	// Step
	void OnAddStepClicked(wxCommandEvent& event);
	void OnAddStepRightClicked(wxMouseEvent & event);
	void OnChangeStepClicked(wxCommandEvent& event);
	void OnChangeStepRightClicked(wxMouseEvent& event);
	void OnChangeStepInternal(wxArrayInt& rows, int row);
	void OnDeleteStepClicked(wxCommandEvent& event);
	void OnDeleteStepRightClicked(wxMouseEvent& event);
	void OnDeleteStepInternal(wxArrayInt& rows, bool auto_confirm);
	void OnMoveUpClicked(wxCommandEvent& event);
	void OnMoveDownClicked(wxCommandEvent& event);
	void OnMoveUpFiveClicked(wxMouseEvent& event);
	void OnMoveDownFiveClicked(wxMouseEvent& event);

	void OnStepsGridDoubleLeftClick(wxGridEvent& event);
	void OnStepsGridDoubleRightClick(wxGridEvent& event);
	void OnStepsGridRangeSelect(wxGridRangeSelectEvent& event);
	void OnStepColourPickerColourChanged(wxColourPickerEvent& event);
	void HandleSplitOrMergeToggle(wxArrayInt& rows);
	void OnSplitMultibuildClicked(wxCommandEvent& event);
	void OnSplitMultibuildRightClicked(wxMouseEvent& event);

	void SplitMultibuildStep(int row);

	void OnStepsFocusCheckbox(wxCommandEvent & event);
	void HandleFocusMode(bool checked, bool changed = false);

	// Template
	void OnNewTemplateClicked(wxCommandEvent& event);
	void OnDeleteTemplateClicked(wxCommandEvent& event);
	void OnDeleteTemplateRightClicked(wxMouseEvent& event);
	void OnDeleteTemplate(bool force);
	void OnTemplateAddFromStepsListClicked(wxCommandEvent& event);
	void OnTemplateAddToStepsListClicked(wxCommandEvent& event);
	void OnTemplateAddStepClicked(wxCommandEvent& event);
	void OnTemplateChangeStepClicked(wxCommandEvent& event);
	void OnTemplateDeleteStepClicked(wxCommandEvent& event);
	void OnTemplateMoveUpClicked(wxCommandEvent& event);
	void OnTemplateMoveDownClicked(wxCommandEvent& event);

	void OnTemplateGridDoubleLeftClick(wxGridEvent& event);
	void OnTemplateGridRangeSelect(wxGridRangeSelectEvent& event);

	void OnTemplateChosen(wxCommandEvent& event);
	void OnTemplateText(wxCommandEvent& event);

	void TemplateAlterStep(StepParameters& step, const int direction, int x_off, int y_off, int amount_off, int amount_multi);

	//Seach
	void StepSeachOnText(wxCommandEvent& event);
	void StepSeachOnTextEnter(wxCommandEvent& event);
	void StepSeachOnSearchButton(wxCommandEvent& event);
	void StepSeachOnCancelButton(wxCommandEvent& event);

	//Import steps panel
	void OnImportStepsIntoStepsCtrl(wxSpinEvent& event);
	void OnImportStepsIntoStepsCtrlEnter(wxCommandEvent& event);
	void OnImportStepsIntoStepsBtnClick(wxCommandEvent& event);
	void OnImportStepsIntoStepsIndexBtnClicked(wxCommandEvent& event);
	void OnImportStepsIntoStepsIndexBtnRight(wxMouseEvent& event);
	bool validateTemplateName();
	void OnImportStepsIntoTemplateCtrlText(wxCommandEvent& event);
	void OnImportStepsIntoTemplateCtrlEnter(wxCommandEvent& event);
	void OnImportStepsIntoTemplateBtnClick(wxCommandEvent& event);
	void OnImportStepsTextUpdate(wxCommandEvent& event);

	//Main book
	void OnMainBookPageChanged(wxAuiNotebookEvent& event);

private:
	wxString window_title = "Factorio TAS Generator";

	DialogProgressBar* dialog_progress_bar = nullptr;

	string generate_code_folder_location = "";
	string save_file_location = "";

	bool auto_close_generate_script = true;
	bool auto_close_open = false;
	bool auto_close_save = true;
	bool auto_close_save_as = false;

	bool no_changes = true;

	vector<string> row_selections;

	string not_relevant = "";
	wxString new_not_relevant = "";
	
	// Arrays used to populate combo boxes
	wxArrayString item_choices;
	wxArrayString take_from_choices;
	wxArrayString tech_choices;
	wxArrayString building_orientation_choices;
	wxArrayString direction_to_build_choices;
	wxArrayString template_choices;
	wxArrayString input_output_choices;
	wxArrayString handcrafted_choices;
	wxArrayString recipe_choices;
	wxArrayString filter_take_put_drop_choices;
	wxArrayString building_choices;

	map<string, vector<StepParameters>> template_map;

	// Undo and redo
	void OnUndoMenuSelected(wxCommandEvent& event);
	void OnRedoMenuSelected(wxCommandEvent& event);
	CommandStack stack;
	vector<tuple<int, StepParameters>> GetSelectedRowTuples();
	tuple<int, StepParameters> GetRowTuple(int index);
	void SelectRowsInGrid(vector<tuple<int, StepParameters>> rows);

	void ResetToNewWindow();
	bool ChecksBeforeResetWindow();
	bool CheckBeforeClose();

	void MoveRow(wxGrid* grid, bool up = false);
	void TemplateMoveRow(wxGrid* grid, wxComboBox* cmb, bool up, map<string, vector<StepParameters>>& map);
	bool DeleteRow(wxGrid* grid, wxComboBox* cmb, map<string, vector<StepParameters>>& map);
	bool ChangeRow(wxGrid* grid, StepParameters step);

	void BackgroundColorUpdate(wxGrid* grid, int row, StepType step);

	void UpdateMapWithNewSteps(wxGrid* grid, wxComboBox* cmb, map<string, vector<StepParameters>>& map);
	void UpdateTemplateGrid(vector<StepParameters>& steps);
	void ClearTemplateGrid(bool disable = true);
	void TemplatePageStartup();

	void setup_paramters(const int parameters);
	void SetupModifiers(StepType type);

	void UpdateParametersChangeType(wxCommandEvent& event, StepType step);
	void UpdateParameters(GridEntry* gridEntry, wxCommandEvent& event, bool changeType = true);
	
	bool Save(string filename, bool save_as, bool set_last_location = true);
	bool AutoSave();
	bool SaveFile(bool save_as);

	string ExtractStep();
	string ExtractAmount();

	void malformed_saved_file_message();

	void UpdateStepGrid(int row, StepParameters* stepParameters);
	GridEntry PrepareStepParametersForGrid(StepParameters* stepParameters);
	StepParameters ExtractStepParameters();

	int GenerateBuildingSnapShot(int end_row);
	void PopulateStepGrid();

	vector<tuple<int, StepParameters>> AddStep(int row, StepParameters step, bool auto_put = true);
	vector< tuple<int, StepParameters>> ChangeStep(int row, StepParameters stepParameters);
	vector< tuple<int, StepParameters>> DeleteSteps(wxArrayInt steps, bool auto_confirm = false);
	void GridTransfer(wxGrid* from, const int& fromRow, wxGrid* to, const int& toRow);
	GridEntry ExtractGridEntry(wxGrid* grid, const int& row);

	bool ValidateStep(const int& row, StepParameters& stepParameters, bool validateBuildSteps = true);
	bool IsValidBuildStep(StepParameters& stepParameters);
	bool IsValidRecipeStep(StepParameters& stepParameters);
	bool IsValidCraftStep(StepParameters& stepParameters);
	bool IsValidPutTakeStep(StepParameters& stepParameters);
	bool IsValidTechnologyStep(StepParameters& stepParameters);

	bool CheckTakePut(StepParameters& stepParameters);
	bool ExtraBuildingChecks(StepParameters& stepParameters);

	bool ValidateAllSteps();

	vector<string> all_buildings;
	vector<string> all_items;
	vector<string> part_assembly_recipes;
	vector<string> full_assembly_recipes;
	vector<string> full_chemical_plant_recipes;
	vector<string> all_recipes;
	vector<StepParameters> StepGridData;
	vector<Building> BuildingsSnapShot;

	// holds the current state of some gui elements
	struct
	{
		wxArrayString* cmb_item;
		const wxString* label_item;
		const wxString* label_from_into;
		map<wxArrayString*, wxString> map_last_item;
	}current; 

	void UpdateCmbItem(wxArrayString* new_list);
	void UpdateLabelItem(const wxString* new_text);
	void UpdateLabelFromInto(const wxString* new_text);
};
