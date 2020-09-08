#pragma once

#include <wx/wx.h>
#include <wx/statline.h>
#include <string>

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
	wxStaticText* m_staticText1;
	wxStaticLine* m_staticline1;
	wxRadioButton* rbtn_mine;
	wxRadioButton* rbtn_rotate;
	wxRadioButton* rbtn_craft;
	wxRadioButton* rbtn_walk;
	wxRadioButton* rbtn_build;
	wxRadioButton* rbtn_game_speed;
	wxRadioButton* rbtn_fuel;
	wxRadioButton* rbtn_take;
	wxRadioButton* rbtn_put;
	wxStaticLine* m_staticline2;
	wxButton* btn_add_task;

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
	void OnAddTaskClicked(wxCommandEvent& event);
	void OnItemCategorySelected(wxCommandEvent& event);

private:
	static std::vector<std::string> all_items;
	std::string check;
	std::string item;
	int amount = 1;
	double x_cord = 0;
	double y_cord = 0;
	wxMenuBar* m_MenuBar = nullptr;

	void OnMenuNew(wxCommandEvent& evt);
	void OnMenuOpen(wxCommandEvent& evt);
	void OnMenuSave(wxCommandEvent& evt);
	void OnMenuExit(wxCommandEvent& evt);


	wxDECLARE_EVENT_TABLE();
};


