///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.9.0 Sep  9 2020)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/combobox.h>
#include <wx/radiobut.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUI_Base
///////////////////////////////////////////////////////////////////////////////
class GUI_Base : public wxFrame {
private:

protected:
	wxMenuBar* m_menubar1;
	wxMenu* menu_file;
	wxPanel* m_panel1;
	wxStaticText* label_x_cord;
	wxTextCtrl* txt_x_cord;
	wxStaticText* label_y_cord;
	wxTextCtrl* txt_y_cord;
	wxStaticText* label_units;
	wxTextCtrl* txt_units;
	wxStaticText* label_item_category;
	wxComboBox* cmb_item_category;
	wxStaticText* label_item;
	wxComboBox* cmb_item;
	wxStaticText* label_building_orientation;
	wxComboBox* cmb_building_direction;
	wxStaticText* label_direction_to_build;
	wxComboBox* cmb_direction_to_build;
	wxStaticText* label_building_size;
	wxTextCtrl* txt_building_size;
	wxStaticText* label_amount_of_buildings;
	wxTextCtrl* txt_amount_of_buildings;
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
	wxStaticText* label_tasks;
	wxGrid* grid_tasks;

	// Virtual event handlers, overide them in your derived class
	virtual void OnMenuNew(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuOpen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuSave(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuSaveAs(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuExit(wxCommandEvent& event) { event.Skip(); }
	virtual void OnItemCategorySelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnBuildingDirectionSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDirectionToBuildSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnWalkChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMineChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGameSpeedChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnfilterChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnLaunchChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPriorityChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnCraftChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnBuildChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRecipeChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTechChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnLimitChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTransferChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnFuelChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTakeChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPutChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRotateChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPickUpChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDropChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnAddTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDeleteTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnBuildingsGridLeftClick(wxGridEvent& event) { event.Skip(); }
	virtual void OnBuildingsGridLeftDoubleClick(wxGridEvent& event) { event.Skip(); }
	virtual void OnTasksGridLeftClick(wxGridEvent& event) { event.Skip(); }
	virtual void OnTasksGridDoubleLeftClick(wxGridEvent& event) { event.Skip(); }


public:

	GUI_Base(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Factorio Scripting Helper"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(2413, 1114), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~GUI_Base();

};

