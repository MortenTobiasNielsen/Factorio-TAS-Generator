#include "TypePanel.h"

#include "cMain.h"
#include "utils.h"

/**/


#pragma region cMain
void cMain::OnBuildChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.build);

	cmb_item->Clear();
	for (auto it = all_buildings.begin(); it < all_buildings.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_buildings.begin());
	cmb_item->AutoComplete(building_choices);

	label_item->SetLabelText("Item:");

	event.Skip();
}

void cMain::OnTakeChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.take);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	cmb_from_into->SetValue("Output"); // set default to output on take task

	label_item->SetLabelText("Item:");
	label_from_into->SetLabelText("From:");

	event.Skip();
}

void cMain::OnPutChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.put);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	cmb_from_into->SetValue("Input"); // set default to input on put task

	label_item->SetLabelText("Item:");
	label_from_into->SetLabelText("Into:");

	event.Skip();
}

void cMain::OnCraftChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.craft);

	cmb_item->Clear();
	for (auto it = handcrafted_list.begin(); it < handcrafted_list.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*handcrafted_list.begin());
	cmb_item->AutoComplete(handcrafted_choices);

	label_item->SetLabelText("Item:");

	event.Skip();
}

void cMain::OnRotateChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.rotate);
	event.Skip();
}

void cMain::OnfilterChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.filter);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	label_item->SetLabelText("Item:");

	event.Skip();
}

void cMain::OnRecipeChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.recipe);

	cmb_item->Clear();
	for (auto it = all_recipes.begin(); it < all_recipes.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_recipes.begin());
	cmb_item->AutoComplete(recipe_choices);

	label_item->SetLabelText("Recipe:");

	event.Skip();
}

void cMain::OnTechChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.tech);

	cmb_item->Clear();
	for (auto it = tech_list.begin(); it < tech_list.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*tech_list.begin());
	cmb_item->AutoComplete(tech_choices);

	label_item->SetLabelText("Technology:");

	event.Skip();
}

void cMain::OnLaunchChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.launch);
	event.Skip();
}

void cMain::OnSaveChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.save);
	event.Skip();
}

void cMain::OnPriorityChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.priority);
	event.Skip();
}

void cMain::OnLimitChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.limit);
	event.Skip();
}

void cMain::OnIdleChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.idle);
	event.Skip();
}

void cMain::OnPickUpChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.pick);
	event.Skip();
}

void cMain::OnDropChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.drop);

	cmb_item->Clear();
	for (auto it = all_items.begin(); it < all_items.end(); it++) {
		cmb_item->Append(*it);
	}
	cmb_item->SetValue(*all_items.begin());
	cmb_item->AutoComplete(item_choices);

	label_item->SetLabelText("Item:");

	event.Skip();
}

void cMain::OnStartChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.Start);
	rbtn_start->SetValue(true);
	event.Skip();
}

void cMain::OnPauseChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.Pause);
	rbtn_pause->SetValue(true);
	event.Skip();
}

void cMain::OnStopChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.stop);
	rbtn_stop->SetValue(true);
	event.Skip();
}

void cMain::OnWalkChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.walk);
	event.Skip();
}

void cMain::OnMineChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.mining);
	event.Skip();
}

void cMain::OnGameSpeedChosen(wxCommandEvent& event) {
	setup_paramters(parameter_choices.game_speed);
	event.Skip();
}
#pragma endregion
