#pragma once

#include <string>
#include <fstream>
#include <wx/colour.h>

#include "Building.h"
#include "StepType.h"
#include "Orientation.h"
#include "Priority.h"

using std::string;
using std::ofstream;
using std::to_string;

struct Modifiers
{
	static const size_t base_size = 7;
	bool walk_towards = false;
	bool no_order = false;
	bool cancel = false;
	bool wait_for = false;
	bool skip = false;
	bool force = false;
	bool split = false;

	Modifiers(){}
	Modifiers(string);
	void FromString(string);
	string ToString();

	static inline vector<string> Strings = {
		"walk towards", "no order", "cancel", "wait for", "skip", "force", "split"
	};
};

struct StepParameters
{
	StepParameters(double InitialX, double InitialY);

	double X;
	double Y;
	double OriginalX;
	double OriginalY;
	int Amount; // 0 => ALL, for game_speed amount is in percentage
	int BuildingIndex;

	Orientation OrientationEnum;
	StepType type;

	string Item;
	string FromInto;
	string orientation;

	string Comment;
	wxColour colour;
	Modifiers modifiers;

	struct Priority_struct
	{
		Priority input = NONE;
		Priority output = NONE;
	} priority;

	struct MultiBuild
	{
		int size = 1;
		int buildings = 1;
		Orientation direction = North;
	} multi_build;

	void Reset();
	void Next();

	string ToString();

	bool operator==(const Building& toCompare);
	bool operator==(const StepParameters& toCompare);
};
