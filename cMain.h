#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <string>
#include <vector>

class cMain : public wxFrame {
public:
	cMain();

protected:
	wxStaticText* label_x_cord;
	wxTextCtrl* txt_x_cord;
	wxStaticText* label_y_cord;
	wxTextCtrl* txt_y_cord;
	wxStaticText* label_item_category;
	wxComboBox* cmb_item_category;
	wxStaticText* label_item;
	wxComboBox* cmb_item;
	wxStaticText* label_amount;
	wxTextCtrl* txt_amount;
	wxStaticText* label_building_direction;
	wxComboBox* cmb_building_direction;
	wxStaticText* label_direction_to_build;
	wxComboBox* cmb_direction_to_build;
	wxRadioButton* rbtn_walk;
	wxRadioButton* rbtn_mine;
	wxRadioButton* rbtn_game_speed;
	wxRadioButton* rbtn_filter;
	wxRadioButton* rbtn_launch;
	wxRadioButton* rbtn_priority;
	wxRadioButton* rbtn_craft;
	wxRadioButton* rbtn_build;
	wxRadioButton* rbtn_recipe;
	wxRadioButton* rbtn_tech;
	wxRadioButton* rbtn_limit;
	wxRadioButton* rbtn_transfer;
	wxRadioButton* rbtn_fuel;
	wxRadioButton* rbtn_take;
	wxRadioButton* rbtn_put;
	wxRadioButton* rbtn_rotate;
	wxRadioButton* rbtn_pick_up;
	wxRadioButton* rbtn_drop;
	wxStaticLine* m_staticline2;
	wxButton* btn_add_task;
	wxButton* btn_delete_task;
	wxStaticLine* m_staticline14;
	wxStaticText* label_buildings;
	wxGrid* grid_buildings;
	wxStaticText* m_staticText37;
	wxGrid* grid_tasks;


	// Virtual event handlers, overide them in your derived class
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

	void OnItemCategorySelected(wxCommandEvent& event);
	void OnBuildingDirectionSelected(wxCommandEvent& event);
	void OnDirectionToBuildSelected(wxCommandEvent& event);

	void OnAddTaskClicked(wxCommandEvent& event);
	void OnDeleteTaskClicked(wxCommandEvent& event);
	
	void OnTasksGridLeftClick(wxGridEvent& event);
	void OnTasksGridDoubleLeftClick(wxGridEvent& event);
	
	void OnBuildingsGridLeftClick(wxGridEvent& event);
	void OnBuildingsGridLeftDoubleClick(wxGridEvent& event);
	


private:
	const static int task_list_game_speed_white_space = 0;
	const static int Task_list_walk_white_space = 20;

	struct parameter_combobox_choices_struct {
		std::vector<bool> game_speed = { false, false, false, true, false, false, false, false };
	};

	const static parameter_combobox_choices_struct parameter_combobox_choices;


	int tasks_row_selected = 0;

	int list_task_num;
	int list_buildings_num;
	std::string not_relevant = "";
	std::vector<std::string> all_items;
	std::string check;
	std::string item;
	std::string file_location;
	std::string amount;
	std::string x_cord;
	std::string y_cord;
	wxMenuBar* m_MenuBar = nullptr;

	void OnMenuNew(wxCommandEvent& evt);
	void OnMenuOpen(wxCommandEvent& evt);
	void OnMenuSave(wxCommandEvent& evt);
	void OnMenuExit(wxCommandEvent& evt);


	wxDECLARE_EVENT_TABLE();

	void choose_enabled_parameters(bool x_cord, bool y_cord, bool item_category, bool item, bool amount, bool building_direction, bool direction_to_build);

	void populate_comboboxes(std::vector<std::string> item_category, std::vector<std::string> item);

	void setup_paramters_comboboxes(bool change_combo_box, bool x_cord, bool y_cord, bool amount, bool item_category, bool item, bool building_direction, bool direction_to_build, std::vector<std::string> *combo_item_category = nullptr, std::vector<std::string> *combo_item = nullptr);

	void update_tasks_list(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string amount, std::string building_direction, std::string direction_to_build);
};


