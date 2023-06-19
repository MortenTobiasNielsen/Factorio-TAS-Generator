#include "TypePanel.h"

#include "Structures\ParameterChoices.h"
#include "Data\utils.h"
#include "cMain.h"

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
		parent->rbtn_cancel_crafting,
		parent->rbtn_never_idle,
		parent->rbtn_keep_walking,
		parent->rbtn_keep_crafting,
		parent->rbtn_keep_on_path,
		parent->rbtn_shoot,
		parent->rbtn_throw,
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
		case e_never_idle: SetType(parent->rbtn_never_idle);
			break;
		case e_keep_crafting: SetType(parent->rbtn_keep_crafting);
			break;
		case e_keep_on_path: SetType(parent->rbtn_keep_on_path);
			break;
		case e_keep_walking: SetType(parent->rbtn_keep_walking);
			break;
		case e_shoot: SetType(parent->rbtn_shoot);
			break;
		case e_throw: SetType(parent->rbtn_throw);
			break;
		default:
			// ERROR: You have done something wrong
			break;
	}
}

void TypePanel::IncrementStateCounter(StepType steptype)
{
	cMain* parent = ((cMain*)this->GetParent());
	switch (steptype)
	{
		case e_never_idle:
			parent->rbtn_never_idle->SetForegroundColour(warnings_states_counters.never_idle++ % 2 == 0 ? "Green" : "Black");
			parent->rbtn_never_idle->GenerateMouseLeave();
			break;
		case e_keep_on_path:
			parent->rbtn_keep_on_path->SetForegroundColour(warnings_states_counters.keep_on_path++ % 2 == 0 ? "Green" : "Black");
			parent->rbtn_keep_on_path->GenerateMouseLeave();
			break;
		case e_keep_crafting:
			parent->rbtn_keep_crafting->SetForegroundColour(warnings_states_counters.keep_crafting++ % 2 == 0 ? "Green" : "Black");
			parent->rbtn_keep_crafting->GenerateMouseLeave();
			break;
		case e_keep_walking:
			parent->rbtn_keep_walking->SetForegroundColour(warnings_states_counters.keep_walking++ % 2 == 0 ? "Green" : "Black");
			parent->rbtn_keep_walking->GenerateMouseLeave();
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

void cMain::SetupModifiers(StepType type)
{
	modifier_no_order_checkbox->Enable(modifier_types.no_order.contains(type));
	//modifier_skip_checkbox->Enable(modifier_types.skip.contains(type)); //always enabled
	modifier_wait_for_checkbox->Enable(modifier_types.wait_for.contains(type));	
	modifier_force_checkbox->Enable(modifier_types.force.contains(type));
	modifier_cancel_checkbox->Enable(modifier_types.cancel.contains(type));
	modifier_split_checkbox->Enable(modifier_types.split.contains(type));
	modifier_walk_towards_checkbox->Enable(modifier_types.walk_towards.contains(type));
}

// Finds the current radio button that is choosen, 
// determines which step type that is and returns the step name
StepType cMain::ExtractStep()
{
	//row 1
	if (rbtn_take->GetValue())
		return e_take;

	if (rbtn_put->GetValue())
		return e_put;

	if (rbtn_game_speed->GetValue())
		return e_game_speed;

	if (rbtn_craft->GetValue())
		return e_craft;

	if (rbtn_walk->GetValue())
		return e_walk;

	if (rbtn_mine->GetValue())
		return e_mine;

	if (rbtn_pause->GetValue())
		return e_pause;

	//row 2
	if (rbtn_build->GetValue())
		return e_build;

	if (rbtn_recipe->GetValue())
		return e_recipe;

	if (rbtn_tech->GetValue())
		return e_tech;

	if (rbtn_limit->GetValue())
		return e_limit;

	if (rbtn_idle->GetValue())
		return e_idle;

	if (rbtn_filter->GetValue())
		return e_filter;

	if (rbtn_stop->GetValue())
		return e_stop;

	//row 3
	if (rbtn_priority->GetValue())
		return e_priority;

	if (rbtn_rotate->GetValue())
		return e_rotate;

	if (rbtn_pick_up->GetValue())
		return e_pick_up;

	if (rbtn_drop->GetValue())
		return e_drop;

	if (rbtn_launch->GetValue())
		return e_launch;

	if (rbtn_save->GetValue())
		return e_save;

	if (rbtn_cancel_crafting->GetValue())
		return e_cancel_crafting;

	if (rbtn_never_idle->GetValue())
		return e_never_idle;

	if (rbtn_keep_crafting->GetValue())
		return e_keep_crafting;

	if (rbtn_keep_on_path->GetValue())
		return e_keep_on_path;

	if (rbtn_keep_walking->GetValue())
		return e_keep_walking;

	if (rbtn_shoot->GetValue())
		return e_shoot;

	if (rbtn_throw->GetValue())
		return e_throw;

	throw "not found";
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
	SetupModifiers(e_build);

	UpdateCmbItem(&building_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnTakeChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_take);
	setup_paramters(parameter_choices.take);
	SetupModifiers(e_take);

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
	SetupModifiers(e_put);

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
	SetupModifiers(e_craft);

	UpdateCmbItem(&handcrafted_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnRotateChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_rotate);
	setup_paramters(parameter_choices.rotate);
	SetupModifiers(e_rotate);
	event.Skip();
}

void cMain::OnfilterChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_filter);
	setup_paramters(parameter_choices.filter);
	SetupModifiers(e_filter);

	UpdateCmbItem(&item_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnRecipeChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_recipe);
	setup_paramters(parameter_choices.recipe);
	SetupModifiers(e_recipe);

	UpdateCmbItem(&recipe_choices);
	UpdateLabelItem(&TypePanel::recipe);

	event.Skip();
}

void cMain::OnTechChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_tech);
	setup_paramters(parameter_choices.tech);
	SetupModifiers(e_tech);

	UpdateCmbItem(&tech_choices);
	UpdateLabelItem(&TypePanel::tech);

	event.Skip();
}

void cMain::OnLaunchChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_launch);
	setup_paramters(parameter_choices.launch);
	SetupModifiers(e_launch);
	event.Skip();
}

void cMain::OnSaveChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_save);
	setup_paramters(parameter_choices.save);
	SetupModifiers(e_save);
	event.Skip();
}

void cMain::OnCancelCraftingChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_cancel_crafting);
	setup_paramters(parameter_choices.cancel_crafting);
	SetupModifiers(e_cancel_crafting);

	UpdateCmbItem(&handcrafted_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnPriorityChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_priority);
	setup_paramters(parameter_choices.priority);
	SetupModifiers(e_priority);
	event.Skip();
}

void cMain::OnLimitChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_limit);
	setup_paramters(parameter_choices.limit);
	SetupModifiers(e_limit);
	event.Skip();
}

void cMain::OnIdleChosen(wxCommandEvent& event)
{
	setup_paramters(parameter_choices.idle);
	SetupModifiers(e_idle);
	event.Skip();
}

void cMain::OnShootChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_shoot);
	setup_paramters(parameter_choices.shoot);
	SetupModifiers(e_shoot);
	event.Skip();
}

void cMain::OnThrowChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_throw);
	setup_paramters(parameter_choices._throw);
	SetupModifiers(e_throw);
	event.Skip();
}

void cMain::OnPickUpChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_pick_up);
	setup_paramters(parameter_choices.pick);
	SetupModifiers(e_pick_up);
	event.Skip();
}

void cMain::OnDropChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_drop);
	setup_paramters(parameter_choices.drop);
	SetupModifiers(e_drop);

	UpdateCmbItem(&item_choices);
	UpdateLabelItem(&TypePanel::item);

	event.Skip();
}

void cMain::OnPauseChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_pause);
	setup_paramters(parameter_choices.Pause);
	SetupModifiers(e_pause);
	event.Skip();
}

void cMain::OnStopChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_stop);
	setup_paramters(parameter_choices.stop);
	SetupModifiers(e_stop);
	event.Skip();
}

void cMain::OnWalkChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_walk);
	setup_paramters(parameter_choices.walk);
	SetupModifiers(e_walk);
	event.Skip();
}

void cMain::OnMineChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_mine);
	setup_paramters(parameter_choices.mining);
	SetupModifiers(e_mine);
	event.Skip();
}

void cMain::OnGameSpeedChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_game_speed);
	setup_paramters(parameter_choices.game_speed);
	SetupModifiers(e_game_speed);
	event.Skip();
}

void cMain::OnNeverIdleChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_never_idle);
	setup_paramters(parameter_choices.never_idle);
	SetupModifiers(e_never_idle);
	event.Skip();
}

void cMain::OnKeepWalkingChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_keep_walking);
	setup_paramters(parameter_choices.keep_walking);
	SetupModifiers(e_keep_walking);
	event.Skip();
}

void cMain::OnKeepOnPathChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_keep_on_path);
	setup_paramters(parameter_choices.keep_on_path);
	SetupModifiers(e_keep_on_path);
	event.Skip();
}

void cMain::OnKeepCraftingChosen(wxCommandEvent& event)
{
	type_panel->SetType(rbtn_keep_crafting);
	setup_paramters(parameter_choices.keep_crafting);
	SetupModifiers(e_keep_crafting);
	event.Skip();
}
#pragma endregion

#pragma region cMain Menu eventhandlers
void cMain::OnWalkMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_walk);
	OnWalkChosen(event);
	event.Skip();
}

void cMain::OnMineMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_mine);
	OnMineChosen(event);
	event.Skip();
}

void cMain::OnThrowMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_throw);
	OnThrowChosen(event);
	event.Skip();
}

void cMain::OnShootMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_shoot);
	OnShootChosen(event);
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

void cMain::OnNeverIdleMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_never_idle);
	OnNeverIdleChosen(event);
	event.Skip();
}

void cMain::OnKeepWalkingMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_keep_walking);
	OnKeepWalkingChosen(event);
	event.Skip();
}

void cMain::OnKeepOnPathMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_keep_on_path);
	OnKeepOnPathChosen(event);
	event.Skip();
}

void cMain::OnKeepCraftingMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_keep_crafting);
	OnKeepCraftingChosen(event);
	event.Skip();
}

void cMain::OnPauseMenuSelected(wxCommandEvent& event)
{
	type_panel->SwitchStep(e_pause);
	OnPauseChosen(event);
	event.Skip();
}
#pragma endregion
