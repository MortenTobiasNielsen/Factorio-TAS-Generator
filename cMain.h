#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
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
	wxStaticText* m_staticText161;
	wxStaticText* m_staticText171;
	wxStaticText* m_staticText191;
	wxStaticText* m_staticText34;
	wxStaticText* m_staticText35;
	wxStaticText* m_staticText36;
	wxListBox* list_buildings;
	wxStaticText* label_task_list;
	wxStaticText* m_staticText37;
	wxStaticText* m_staticText16;
	wxStaticText* m_staticText17;
	wxStaticText* m_staticText18;
	wxStaticText* m_staticText19;
	wxStaticText* m_staticText20;
	wxListBox* list_tasks;


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

	void OnBuildingsListDoubleClicked(wxCommandEvent& event);
	void OnTasksListDoubleClicked(wxCommandEvent& event);

	void OnTasksListKeyDown(wxKeyEvent& event);	
	void OnBuildingsListKeyDown(wxKeyEvent& event);
	
	
	
	


private:
	std::string not_relevant = "N/A";
	int list_task_num;
	int list_buildings_num;
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

	void update_task_list(std::string task, std::string x_cord, std::string y_cord, std::string item, std::string amount, std::string building_direction, std::string direction_to_build, int index);
};


