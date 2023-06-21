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

struct StepParameters
{
	StepParameters(double InitialX, double InitialY);

	double X;
	double Y;
	double OriginalX;
	double OriginalY;
	int Amount; // 0 => ALL, for game_speed amount is in percentage
	int BuildingIndex;

	string Modifiers;

	Orientation OrientationEnum;
	StepType type;

	string Item;
	string FromInto;
	string orientation;

	string Comment;
	wxColour colour;

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