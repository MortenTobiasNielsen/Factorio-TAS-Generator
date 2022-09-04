///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-234-gd93c9fc0)
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
#include <wx/statline.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/grid.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/scrolwin.h>
#include <wx/gauge.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUI_Base
///////////////////////////////////////////////////////////////////////////////
class GUI_Base : public wxFrame
{
private:

protected:
	wxMenuBar* m_menubar1;
	wxMenu* menu_file;
	wxMenu* menu_script;
	wxMenu* menu_shortcuts;
	wxMenu* menu_goals;
	wxMenu* menu_auto_close;
	wxPanel* m_panel1;
	wxStaticText* label_x_cord;
	wxTextCtrl* txt_x_cord;
	wxStaticText* label_y_cord;
	wxTextCtrl* txt_y_cord;
	wxStaticText* label_units;
	wxTextCtrl* txt_units;
	wxStaticText* label_comment;
	wxTextCtrl* txt_comment;
	wxStaticText* label_item;
	wxComboBox* cmb_item;
	wxStaticText* label_from_into;
	wxComboBox* cmb_from_into;
	wxStaticText* label_tech;
	wxComboBox* cmb_tech;
	wxStaticText* label_input;
	wxComboBox* cmb_input;
	wxStaticText* label_output;
	wxComboBox* cmb_output;
	wxStaticText* label_building_orientation;
	wxComboBox* cmb_building_orientation;
	wxStaticText* label_direction_to_build;
	wxComboBox* cmb_direction_to_build;
	wxStaticText* label_building_size;
	wxTextCtrl* txt_building_size;
	wxStaticText* label_amount_of_buildings;
	wxTextCtrl* txt_amount_of_buildings;
	wxStaticText* label_tasks;
	wxStaticLine* m_staticline3;
	wxRadioButton* rbtn_take;
	wxRadioButton* rbtn_put;
	wxRadioButton* rbtn_game_speed;
	wxRadioButton* rbtn_craft;
	wxRadioButton* rbtn_walk;
	wxRadioButton* rbtn_mine;
	wxRadioButton* rbtn_start;
	wxRadioButton* rbtn_build;
	wxRadioButton* rbtn_recipe;
	wxRadioButton* rbtn_tech;
	wxRadioButton* rbtn_limit;
	wxRadioButton* rbtn_idle;
	wxRadioButton* rbtn_filter;
	wxRadioButton* rbtn_pause;
	wxRadioButton* rbtn_priority;
	wxRadioButton* rbtn_rotate;
	wxRadioButton* rbtn_pick_up;
	wxRadioButton* rbtn_drop;
	wxRadioButton* rbtn_launch;
	wxRadioButton* rbtn_save;
	wxRadioButton* rbtn_stop;
	wxStaticLine* m_staticline4;
	wxStaticLine* m_staticline14;
	wxNotebook* m_notebook1;
	wxPanel* m_panel3;
	wxStaticText* label_choose_group;
	wxComboBox* cmb_choose_group;
	wxButton* btn_new_group;
	wxButton* btn_group_delete;
	wxButton* btn_group_change_task;
	wxButton* btn_group_delete_task;
	wxButton* btn_group_move_up;
	wxButton* btn_gorup_move_down;
	wxButton* btn_group_add_to_tasks_list;
	wxButton* btn_group_add_from_tasks_list;
	wxGrid* grid_group;
	wxPanel* m_panel6;
	wxStaticText* label_choose_template;
	wxComboBox* cmb_choose_template;
	wxButton* btn_template_new;
	wxButton* btn_template_delete;
	wxButton* btn_template_change_task;
	wxButton* btn_template_delete_task;
	wxButton* btn_template_move_up_task;
	wxButton* btn_template_move_down_task;
	wxButton* btn_template_add_to_tasks_list1;
	wxButton* btn_template_add_from_tasks_list1;
	wxStaticText* label_template_x_offset;
	wxTextCtrl* txt_template_x_offset;
	wxStaticText* label_template_y_offset;
	wxTextCtrl* txt_template_y_offset;
	wxGrid* grid_template;
	wxNotebook* m_notebook11;
	wxPanel* m_panel31;
	wxButton* btn_add_task11;
	wxButton* btn_change_task11;
	wxButton* btn_delete_task11;
	wxButton* btn_move_up11;
	wxButton* btn_move_down11;
	wxGrid* grid_tasks;
	wxPanel* m_panel61;
	wxGrid* grid_buildings;

	// Virtual event handlers, override them in your derived class
	virtual void OnApplicationClose(wxCloseEvent& event) { event.Skip(); }
	virtual void OnMenuNew(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuOpen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuSave(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuSaveAs(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuExit(wxCommandEvent& event) { event.Skip(); }
	virtual void OnChooseLocation(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGenerateScript(wxCommandEvent& event) { event.Skip(); }
	virtual void OnOnlyGenerateSteps(wxCommandEvent& event) { event.Skip(); }
	virtual void OnChangeShortcuts(wxCommandEvent& event) { event.Skip(); }
	virtual void OnCraftMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnWalkMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGameSpeedMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRotateMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRecipeMenuChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnStopMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMineMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnBuildMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTechMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTakeMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPutMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnIdleMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPriorityMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnLimitMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnFilterMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPickUpMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDropMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnLaunchMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnSaveMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnStartMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPauseMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnAddMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnChangeMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDeleteMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMoveUpMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMoveDownMenuSelected(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuSteelAxeClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuGOTLAPClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuAnyPercentClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuDebugClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuAutoCloseGenerateScriptClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuAutoCloseOpenClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuAutoCloseSaveClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMenuAutoCloseSaveAsClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTakeChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPutChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGameSpeedChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnCraftChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnWalkChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMineChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnStartChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnBuildChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRecipeChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTechChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnLimitChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnIdleChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnfilterChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPauseChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPriorityChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRotateChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnPickUpChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDropChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnLaunchChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnSaveChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnStopChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGroupChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnNewGroupClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDeleteGroupClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGroupChangeClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGroupDeleteClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGroupMoveUpClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGroupMoveDownClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGroupAddToTasksListClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGroupAddFromTasksListClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnGroupGridDoubleLeftClick(wxGridEvent& event) { event.Skip(); }
	virtual void OnTemplateChosen(wxCommandEvent& event) { event.Skip(); }
	virtual void OnNewTemplateClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDeleteTemplateClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTemplateChangeTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTemplateDeleteTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTemplateMoveUpClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTemplateMoveDownClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTemplateAddToTasksListClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTemplateAddFromTasksListClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTemplateGridDoubleLeftClick(wxGridEvent& event) { event.Skip(); }
	virtual void OnAddTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnChangeTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnDeleteTaskClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMoveUpClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnMoveDownClicked(wxCommandEvent& event) { event.Skip(); }
	virtual void OnTasksGridDoubleLeftClick(wxGridEvent& event) { event.Skip(); }
	virtual void OnBuildingsGridLeftDoubleClick(wxGridEvent& event) { event.Skip(); }


public:

	GUI_Base(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Factorio Scripting Helper"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1840, 1080), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~GUI_Base();

};

///////////////////////////////////////////////////////////////////////////////
/// Class Shortcuts_Menu
///////////////////////////////////////////////////////////////////////////////
class Shortcuts_Menu : public wxFrame
{
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

	Shortcuts_Menu(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Change Shortcuts"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(570, 396), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~Shortcuts_Menu();

};

///////////////////////////////////////////////////////////////////////////////
/// Class BaseForDialogProgress
///////////////////////////////////////////////////////////////////////////////
class BaseForDialogProgress : public wxDialog
{
private:

protected:
	wxPanel* m_panel7;
	wxStaticText* txt_dialog_text;
	wxGauge* progress_bar;
	wxButton* btn_dialog_progress_done;

	// Virtual event handlers, override them in your derived class
	virtual void GenerateScriptOnClick(wxCommandEvent& event) { event.Skip(); }


public:

	BaseForDialogProgress(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Generating Script"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);

	~BaseForDialogProgress();

};

