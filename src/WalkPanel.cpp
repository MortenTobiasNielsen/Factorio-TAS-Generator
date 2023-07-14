﻿#include "cMain.h"

using std::pair;
using std::set;

set<StepType> control_types = {
	e_pause,
	e_stop,
	e_idle,
};
void cMain::SetupWalkPanelUnicodeCharacters()
{
	walk_panel_button_upleft->SetLabel(L'↖');
	walk_panel_button_up->SetLabel(L'↑');
	walk_panel_button_upright->SetLabel(L'↗');
	walk_panel_button_left->SetLabel(L'←');

	walk_panel_button_right->SetLabel(L'→');
	walk_panel_button_downleft->SetLabel(L'↙');
	walk_panel_button_down->SetLabel(L'↓');
	walk_panel_button_downright->SetLabel(L'↘');
}
int cMain::AddWalkScanStartRow()
{
	for (int i = StepGridData.size() - 1; i >= 0; i--)
		if (!control_types.contains(StepGridData[i].StepEnum))
			return i;
		
	return 0;
}
pair<double, double> cMain::AddWalkScanCurrentPosition()
{
	for (int i = StepGridData.size() - 1; i >= 0; i--)
		if (StepGridData[i].StepEnum == e_walk)
			return pair<double, double> {StepGridData[i].X, StepGridData[i].Y};
	
	return pair<double, double>{0, 0};
}

void cMain::CreateWalkStep(int x_modifier, int y_modifier)
{
	auto row = AddWalkScanStartRow() + 1;
	auto [x, y] = AddWalkScanCurrentPosition();
	auto increment = walk_panel_increment_spin->GetValue();

	auto step = StepParameters(x + increment * x_modifier, y + increment * y_modifier);
	step.StepEnum = e_walk; step.Step = StepNames[e_walk];
	stack.Push({
		.row = row,
		.type = T_ADD,
		.rows = AddStep(row, step),
	});

	grid_steps->SelectRow(row);
	grid_steps->GoToCell(row, 0);
	no_changes = false;
}

void cMain::OnWalkPanelBtnUpLeftClicked(wxCommandEvent& event)
{
	CreateWalkStep(-1, -1);
}
void cMain::OnWalkPanelBtnUpClicked(wxCommandEvent& event)
{
	CreateWalkStep(0, -1);
}
void cMain::OnWalkPanelBtnUpRightClicked(wxCommandEvent& event)
{
	CreateWalkStep(+1, -1);
}
void cMain::OnWalkPanelBtnLeftClicked(wxCommandEvent& event)
{
	CreateWalkStep(-1, 0);
}
void cMain::OnWalkPanelBtnRightClicked(wxCommandEvent& event)
{
	CreateWalkStep(+1, 0);
}
void cMain::OnWalkPanelBtnDownLeftClicked(wxCommandEvent& event)
{
	CreateWalkStep(-1, +1);
}
void cMain::OnWalkPanelBtnDownClicked(wxCommandEvent& event)
{
	CreateWalkStep(0, +1);
}
void cMain::OnWalkPanelBtnDownRightClicked(wxCommandEvent& event)
{
	CreateWalkStep(+1, +1);
}
