#include "TypePanel.h"

#include "cMain.h"
#include "utils.h"
#include "ParameterChoices.h"

using std::string;

/*
Type panel is the second panel at the top, with a radio button for each steptype
This file extends cMain.h to reduce the size of cMain.cpp
*/

void TypePanel::SetType(wxRadioButton * choosen_btn)
{
	static cMain* parent = ((cMain*)this->GetParent());
	static vector< wxRadioButton*> radio_buttons = {
		parent->rbtn_take,
		parent->rbtn_put,
		parent->rbtn_game_speed,
		parent->rbtn_craft,
		parent->rbtn_walk,
		parent->rbtn_mine,
		parent->rbtn_build,
		parent->rbtn_recipe,
		parent->rbtn_tech,
		parent->rbtn_limit,
		parent->rbtn_idle,
		parent->rbtn_filter,
		parent->rbtn_pause,
		parent->rbtn_priority,
		parent->rbtn_rotate,
		parent->rbtn_pick_up,
		parent->rbtn_drop,
		parent->rbtn_launch,
		parent->rbtn_save,
		parent->rbtn_stop,
		parent->rbtn_cancel_crafting
	};
	parent->rbtn_character_panel_hidden->SetValue(true);
	parent->rbtn_building_panel_hidden->SetValue(true);
	parent->rbtn_game_panel_hidden->SetValue(true);
	for (auto btn : radio_buttons)
	{
		btn->SetValue(btn == choosen_btn);
	}
}

void TypePanel::SwitchStep(StepType type)
{
	cMain* parent = ((cMain*)this->GetParent());
	switch (type)
	{
		case e_take: SetType(parent->rbtn_take);
			break;
		case e_put: SetType(parent->rbtn_put);
			break;
		case e_game_speed: SetType(parent->rbtn_game_speed);
			break;
		case e_craft: SetType(parent->rbtn_craft);
			break;
		case e_walk: SetType(parent->rbtn_walk);
			break;
		case e_mine: SetType(parent->rbtn_mine);
			break;
		case e_build: SetType(parent->rbtn_build);
			break;
		case e_recipe: SetType(parent->rbtn_recipe);
			break;
		case e_tech: SetType(parent->rbtn_tech);
			break;
		case e_limit: SetType(parent->rbtn_limit);
			break;
		case e_idle: SetType(parent->rbtn_idle);
			break;
		case e_filter: SetType(parent->rbtn_filter);
			break;
		case e_pause: SetType(parent->rbtn_pause);
			break;
		case e_priority: SetType(parent->rbtn_priority);
			break;
		case e_rotate: SetType(parent->rbtn_rotate);
			break;
		case e_pick_up: SetType(parent->rbtn_pick_up);
			break;
		case e_drop: SetType(parent->rbtn_drop);
			break;
		case e_launch: SetType(parent->rbtn_launch);
			break;
		case e_save: SetType(parent->rbtn_save);
			break;
		case e_stop: SetType(parent->rbtn_stop);
			break;
		case e_cancel_crafting: SetType(parent->rbtn_cancel_crafting);
			break;
		default:
			// ERROR: You have done something wrong
			break;
	}
}

#pragma region cMain
void cMain::setup_paramters(const int parameters)
{
	using enum choice_bit_vector;
	spin_x->Enable(parameters & x_coordinate);
	spin_y->Enable(parameters & y_coordinate);
	spin_amount->Enable(parameters & amount);
	cmb_item->Enable(parameters & item);
	cmb_from_into->Enable(parameters & from_to);
	radio_input->Enable((bool)(input == (parameters & input)));
	radio_output->Enable((bool)(output == (parameters & output)));
	cmb_building_orientation->Enable(parameters & building_orientation);
	cmb_direction_to_build->Enable(parameters & direction_to_build);
	spin_building_size->Enable(parameters & building_size);
	spin_building_amount->Enable(parameters & amount_of_buildings);
}

// Finds the current radio button that is choosen, 
// determines which step type that is and returns the step name
string cMain::ExtractStep()
{
	//row 1
	if (rbtn_take->GetValue())
		return StepNames[e_take];

	if (rbtn_put->GetValue())
		return StepNames[e_put];

	if (rbtn_game_speed->GetValue())
		return StepNames[e_game_speed];

	if (rbtn_craft->GetValue())
		return StepNames[e_craft];

	if (rbtn_walk->GetValue())
		return StepNames[e_walk];

	if (rbtn_mine->GetValue())
		return StepNames[e_mine];

	if (rbtn_pause->GetValue())
		return StepNames[e_pause];

	//row 2
	if (rbtn_build->GetValue())
		return StepNames[e_build];

	if (rbtn_recipe->GetValue())
		return StepNames[e_recipe];

	if (rbtn_tech->GetValue())
		return StepNames[e_tech];

	if (rbtn_limit->GetValue())
		return StepNames[e_limit];

	if (rbtn_idle->GetValue())
		return StepNames[e_idle];

	if (rbtn_filter->GetValue())
		return StepNames[e_filter];

	if (rbtn_stop->GetValue())
		return StepNames[e_stop];

	//row 3
	if (rbtn_priority->GetValue())
		return StepNames[e_priority];

	if (rbtn_rotate->GetValue())
		return StepNames[e_rotate];

	if (rbtn_pick_up->GetValue())
		return StepNames[e_pick_up];

	if (rbtn_drop->GetValue())
		return StepNames[e_drop];

	if (rbtn_launch->GetValue())
		return StepNames[e_launch];

	if (rbtn_save->GetValue())
		return StepNames[e_save];

	if (rbtn_cancel_crafting->GetValue())
		return StepNames[e_cancel_crafting];

	return "not found";
}

void cMain::UpdateCmbItem(wxArrayString* new_list)
{
	if (new_list != current.cmb_item)
	{
		if (!current.map_last_item.contains(new_list)) // if map_last_item does not contain new_list, add it
			current.map_last_item.insert(std::pair(new_list, *new_list->begin()));
		const wxString current_value = cmb_item->GetValue();
		// either the new list contains the current value or default to the new list's last value
		wxString last = ListContains(new_list, current_value) ? current_value : current.map_last_item[new_list];
		current.map_last_item[current.cmb_item] = current_value; // update last item of the list we leave

		current.cmb_item = new_list;
		cmb_item->Clear();
		cmb_item->Append(*new_list);
		cmb_item->SetValue(last);
		cmb_item->AutoComplete(*new_list);
	}
}
void cMain::UpdateLabelItem(const wxString* new_text)
{
	if (new_text != current.label_item)
	{
		current.label_item = new_text;
		label_item->SetLabelText(*new_text);
	}
}
void cMain::UpdateLabelFromInto(const wxString* new_text)
{
	if (new_text != current.label_from_into)
	{
		current.label_from_into = new_text;
		label_from_into->SetLabelText(*new_text);
	}
}
#pragma endregion

#pragma region cMain eventhandlers
void cMain::OnBuildChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_build);
	setup_paramters(parameter_choices.build);

	UpdateCmbItem(&building_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnTakeChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_take);
	setup_paramters(parameter_choices.take);

	UpdateCmbItem(&item_choices);
	UpdateLabelItem(&TypePanel::item);
	UpdateLabelFromInto(&TypePanel::from);

	cmb_from_into->SetValue(TypePanel::output); // set default to output on take step

	event.Skip();
}

void cMain::OnPutChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_put);
	setup_paramters(parameter_choices.put);

	UpdateCmbItem(&item_choices);
	UpdateLabelItem(&TypePanel::item);
	UpdateLabelFromInto(&TypePanel::into);

	cmb_from_into->SetValue(TypePanel::input); // set default to input on put step

	event.Skip();
}

void cMain::OnCraftChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_craft);
	setup_paramters(parameter_choices.craft);

	UpdateCmbItem(&handcrafted_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnRotateChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_rotate);
	setup_paramters(parameter_choices.rotate);
	event.Skip();
}

void cMain::OnfilterChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_filter);
	setup_paramters(parameter_choices.filter);

	UpdateCmbItem(&item_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnRecipeChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_recipe);
	setup_paramters(parameter_choices.recipe);

	UpdateCmbItem(&recipe_choices);
	UpdateLabelItem(&TypePanel::recipe);

	event.Skip();
}

void cMain::OnTechChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_tech);
	setup_paramters(parameter_choices.tech);

	UpdateCmbItem(&tech_choices);
	UpdateLabelItem(&TypePanel::tech);

	event.Skip();
}

void cMain::OnLaunchChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_launch);
	setup_paramters(parameter_choices.launch);
	event.Skip();
}

void cMain::OnSaveChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_save);
	setup_paramters(parameter_choices.save);
	event.Skip();
}

void cMain::OnCancelCraftingChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_cancel_crafting);
	setup_paramters(parameter_choices.cancel_crafting);

	UpdateCmbItem(&handcrafted_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnPriorityChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_priority);
	setup_paramters(parameter_choices.priority);
	event.Skip();
}

void cMain::OnLimitChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_limit);
	setup_paramters(parameter_choices.limit);
	event.Skip();
}

void cMain::OnIdleChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.idle);
	event.Skip();
}

void cMain::OnPickUpChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_pick_up);
	setup_paramters(parameter_choices.pick);
	event.Skip();
}

void cMain::OnDropChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_drop);
	setup_paramters(parameter_choices.drop);

	UpdateCmbItem(&item_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnPauseChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_pause);
	setup_paramters(parameter_choices.Pause);
	event.Skip();
}

void cMain::OnStopChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_stop);
	setup_paramters(parameter_choices.stop);
	event.Skip();
}

void cMain::OnWalkChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_walk);
	setup_paramters(parameter_choices.walk);
	event.Skip();
}

void cMain::OnMineChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_mine);
	setup_paramters(parameter_choices.mining);
	event.Skip();
}

void cMain::OnGameSpeedChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_game_speed);
	setup_paramters(parameter_choices.game_speed);
	event.Skip();
}
#pragma endregion

#pragma region cMain Menu eventhandlers
void cMain::OnWalkMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_walk);
	OnWalkChosen(event);

	//// IMPORTANT -- This can be used to change the shortcuts of menuitems
	//wxAcceleratorEntry* plusAccel = new wxAcceleratorEntry(wxACCEL_CTRL, 50, wxID_ZOOM_IN);
	//menu_shortcuts->FindChildItem(10001)->SetAccel(plusAccel); // 10001 is the id of the menu item and can be set to what ever you want
	event.Skip();
}

void cMain::OnMineMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_mine);
	OnMineChosen(event);
	event.Skip();
}

void cMain::OnGameSpeedMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_game_speed);
	OnGameSpeedChosen(event);
	event.Skip();
}

void cMain::OnBuildMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_build);
	OnBuildChosen(event);
	event.Skip();
}

void cMain::OnTakeMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_take);
	OnTakeChosen(event);
	event.Skip();
}

void cMain::OnPutMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_put);
	OnPutChosen(event);
	event.Skip();
}

void cMain::OnCraftMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_craft);
	OnCraftChosen(event);
	event.Skip();
}

void cMain::OnCancelCraftingMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_cancel_crafting);
	OnCancelCraftingChosen(event);
	event.Skip();
}

void cMain::OnRecipeMenuChosen(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_recipe);
	OnRecipeChosen(event);
	event.Skip();
}

void cMain::OnRotateMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_rotate);
	OnRotateChosen(event);
	event.Skip();
}

void cMain::OnTechMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_tech);
	OnTechChosen(event);
	event.Skip();
}

void cMain::OnPriorityMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_priority);
	OnPriorityChosen(event);
	event.Skip();
}

void cMain::OnLimitMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_limit);
	OnLimitChosen(event);
	event.Skip();
}

void cMain::OnFilterMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_filter);
	OnfilterChosen(event);
	event.Skip();
}

void cMain::OnStopMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_stop);
	OnStopChosen(event);
	event.Skip();
}

void cMain::OnIdleMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_idle);
	OnIdleChosen(event);
	event.Skip();
}

void cMain::OnLaunchMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_launch);
	OnLaunchChosen(event);
	event.Skip();
}

void cMain::OnDropMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_drop);
	OnDropChosen(event);
	event.Skip();
}

void cMain::OnPickUpMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_pick_up);
	OnPickUpChosen(event);
	event.Skip();
}

void cMain::OnSaveMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_save);
	OnSaveChosen(event);
	event.Skip();
}

void cMain::OnPauseMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_pause);
	OnPauseChosen(event);
	event.Skip();
}
#pragma endregion
