#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "GUI_Base.h"
#include "Settings.h"

class SteptypeColourHandler : public StepTypeColoursDialog
{
private:
	struct sColour
	{
		bool set = false;
		wxColour colour;
		sColour()
		{
			set = false;
			colour = {};
		}
		sColour(wxColour c)
		{
			colour = c;
			set = true;
		}
		sColour(std::string s)
		{
			colour = wxColour(s);
			set = true;
		}
	};

public:
	SteptypeColourHandler(wxWindow* parent, wxGrid* steps, wxGrid* templates, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style);

	~SteptypeColourHandler();

	void OnSteptypeColoursPickerColourChanged(wxColourPickerEvent& event);

	void Build();
	void DefaultColours();

	static inline void UpdateSteptypeColoursFromFile()
	{
		try
		{
			SteptypeToColour.resize(StepNames.size() + 1);
			settings::setting s = settings::ReadSettingFile();
			// For each shortcut type in the settings file
			for (auto& [steptype, colour] : s.colours)
			{
				SteptypeToColour[ToStepType(steptype)] = sColour(colour);
			}
		}
		catch (...) { } // ignore all errors
	}

	static inline wxColour GetStepColourOrDefault(StepType steptype)
	{
		return SteptypeToColour[steptype].set ? SteptypeToColour[steptype].colour : DefaultColour(steptype);
	}

	static inline wxColour DefaultColour(StepType steptype)
	{
		switch (steptype)
		{
			case e_build:
				return wxColour("Cyan");
			case e_stop:
				return wxColour("Red");
			case e_craft:
				return wxColour("Light Grey");
			case e_game_speed:
			case e_pause:
			case e_save:
			case e_keep_crafting:
			case e_keep_on_path:
			case e_keep_walking:
			case e_never_idle:
				return wxColour("Yellow");
			default:
				return wxColour("White");
		}
	}

	static inline vector<sColour> SteptypeToColour;

protected:
	std::map<std::string, wxColourPickerCtrl*> mapCtrl = {};
	settings::setting state;
	vector<wxGrid*> grids;

	void OnCloseStepTypeColoursChanger(wxCloseEvent& event);
	void OnInitStepTypeColoursDialog(wxInitDialogEvent& event);
};