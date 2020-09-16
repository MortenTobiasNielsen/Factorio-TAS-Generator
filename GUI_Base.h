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
#include <wx/scrolwin.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUI_Base
///////////////////////////////////////////////////////////////////////////////
class GUI_Base : public wxFrame {
private:

protected:
	wxMenuBar* m_menubar1;
	wxMenu* menu_file;
	wxMenu* menu_script;
	wxMenu* menu_shortcuts;
	wxPanel* m_panel1;
	wxStaticText* label_x_cord;
	wxTextCtrl* txt_x_cord;
	wxStaticText* label_y_cord;
	wxTextCtrl* txt_y_cord;
	wxStaticText* label_units;
	wxTextCtrl* txt_units;
	wxStaticText* label_item;
	wxComboBox* cmb_item;
	wxStaticText* label_from_into;
	wxComboBox* cmb_from_into;
	wxStaticText* label_tech;
	wxComboBox* cmb_tech;
	wxStaticText* label_building_orientation;
	wxComboBox* cmb_building_orientation;
	wxStaticText* label_direction_to_build;
	wxComboBox* cmb_direction_to_build;
	wxStaticText* label_building_size;
	wxTextCtrl* txt_building_size;
	wxStaticText* label_amount_of_buildings;
	wxTextCtrl* txt_amount_of_buildings;
	wxRadioButton* rbtn_take;
	wxRadioButton* rbtn_put;
	wxRadioButton* rbtn_game_speed;
	wxRadioButton* rbtn_craft;
	wxRadioButton* rbtn_walk;
	wxRadioButton* rbtn_mine;
	wxRadioButton* rbtn_build;
	wxRadioButton* rbtn_recipe;
	wxRadioButton* rbtn_tech;
	wxRadioButton* rbtn_limit;
	wxRadioButton* rbtn_transfer;
	wxRadioButton* rbtn_filter;
	wxRadioButton* rbtn_fuel;
	wxRadioButton* rbtn_priority;
	wxRadioButton* rbtn_rotate;
	wxRadioButton* rbtn_pick_up;
	wxRadioButton* rbtn_drop;
	wxRadioButton* rbtn_launch;
	wxStaticLine* m_staticline2;
	wxButton* btn_add_task;
	wxButton* btn_change_task;
	wxButton* btn_delete_task;
	wxButton* btn_move_up;
	wxButton* btn_move_down;
	wxButton* btn_duplicate_tasks;
	wxStaticText* label_offset_size;
	wxTextCtrl* txt_offset_size;
	wxStaticText* label_offset_direction;
	wxComboBox* cmb_offset_direction;
	wxStaticLine* m_staticline14;
	wxStaticText* label_buildings;
	wxGrid* grid_buildings;
	wxStaticText* label_tasks;
	wxGrid* grid_tasks;

	// Virtual event handlers, overide them in your derived class
	virtual void OnFameKeyDown(wxKeyEvent& event) { event.Skip(); }
	virtual void OnMenuNew(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuOpen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuSave(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuSaveAs(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuExit(wxCommandEvent& event) { event.Skip(); }
	virtual void OnChooseLocation(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGenerateScript(wxCommandEvent& event) { event.Skip(); }
	virtual void OnChangeShortcuts(wxCommandEvent& event) { event.Skip(); }
	virtual void OnWalkMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMineMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGameSpeedMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnBuildMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnFuelMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTakeMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPutMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnCraftMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRotateMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnAddMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnBuildingOrientationSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDirectionToBuildSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTakeChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPutChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGameSpeedChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnCraftChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnWalkKeyDown(wxKeyEvent& event) { event.Skip(); }
	virtual void OnWalkChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMineChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnBuildChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRecipeChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTechChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnLimitChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTransferChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnfilterChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnFuelChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPriorityChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRotateChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPickUpChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDropChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnLaunchChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnAddTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnChangeTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDeleteTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMoveUpClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMoveDownClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDuplicateTasksClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnBuildingsGridLeftClick(wxGridEvent& event) { event.Skip(); }
	virtual void OnBuildingsGridLeftDoubleClick(wxGridEvent& event) { event.Skip(); }
	virtual void OnTasksGridLeftClick(wxGridEvent& event) { event.Skip(); }
	virtual void OnTasksGridDoubleLeftClick(wxGridEvent& event) { event.Skip(); }


public:

	GUI_Base(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Factorio Scripting Helper"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1556, 1080), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~GUI_Base();

};

///////////////////////////////////////////////////////////////////////////////
/// Class Shortcuts_Menu
///////////////////////////////////////////////////////////////////////////////
class Shortcuts_Menu : public wxFrame {
private:

protected:
	wxScrolledWindow* m_scrolledWindow3;
	wxStaticText* label_shortcut_walk;
	wxTextCtrl* m_textCtrl681;
	wxStaticText* label_shortcut_walk1;
	wxTextCtrl* m_textCtrl6811;
	wxStaticText* label_shortcut_walk2;
	wxTextCtrl* m_textCtrl6812;
	wxStaticText* label_shortcut_walk3;
	wxTextCtrl* m_textCtrl6813;
	wxStaticText* label_shortcut_walk4;
	wxTextCtrl* m_textCtrl6814;
	wxStaticText* label_shortcut_walk5;
	wxTextCtrl* m_textCtrl6815;
	wxStaticText* label_shortcut_walk6;
	wxTextCtrl* m_textCtrl6816;
	wxStaticText* label_shortcut_walk7;
	wxTextCtrl* m_textCtrl6817;
	wxStaticText* label_shortcut_walk8;
	wxTextCtrl* m_textCtrl6818;
	wxScrolledWindow* m_scrolledWindow1;
	wxStaticText* label_shortcut_walk9;
	wxTextCtrl* m_textCtrl6819;
	wxStaticText* label_shortcut_walk11;
	wxTextCtrl* m_textCtrl68111;
	wxStaticText* label_shortcut_walk21;
	wxTextCtrl* m_textCtrl68121;
	wxStaticText* label_shortcut_walk31;
	wxTextCtrl* m_textCtrl68131;
	wxStaticText* label_shortcut_walk41;
	wxTextCtrl* m_textCtrl68141;
	wxStaticText* label_shortcut_walk51;
	wxTextCtrl* m_textCtrl68151;
	wxStaticText* label_shortcut_walk61;
	wxTextCtrl* m_textCtrl68161;
	wxStaticText* label_shortcut_walk71;
	wxTextCtrl* m_textCtrl68171;
	wxStaticText* label_shortcut_walk81;
	wxTextCtrl* m_textCtrl68181;
	wxScrolledWindow* m_scrolledWindow11;
	wxStaticText* label_shortcut_walk91;
	wxTextCtrl* m_textCtrl68191;
	wxStaticText* label_shortcut_walk111;
	wxTextCtrl* m_textCtrl681111;
	wxStaticText* label_shortcut_walk211;
	wxTextCtrl* m_textCtrl681211;
	wxStaticText* label_shortcut_walk311;
	wxTextCtrl* m_textCtrl681311;
	wxStaticText* label_shortcut_walk411;
	wxTextCtrl* m_textCtrl681411;
	wxStaticText* label_shortcut_walk511;
	wxTextCtrl* m_textCtrl681511;
	wxStaticText* label_shortcut_walk611;
	wxTextCtrl* m_textCtrl681611;
	wxStaticText* label_shortcut_walk711;
	wxTextCtrl* m_textCtrl681711;
	wxStaticText* label_shortcut_walk811;
	wxTextCtrl* m_textCtrl681811;
	wxButton* m_button3;
	wxButton* m_button4;

public:

	Shortcuts_Menu(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Change Shortcuts"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(570, 370), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~Shortcuts_Menu();

};

