#pragma once

#include <wx/colour.h>

#include <string>
#include <fstream>

#include "Building.h"
#include "StepType.h"
#include "Orientation.h"
#include "Priority.h"
#include "StepModifiers.h"

#include "../Data/Inventory.h"

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

	int Size = 1;
	int Buildings = 1;
	int BuildingIndex = 0;

	StepModifiers Modifiers;

	Orientation OrientationEnum = North;
	StepType type = e_stop;
	InventoryType inventory = Wreck;

	string Amount;
	string Item;
	string orientation;
	Orientation Direction = North;
	PriorityStruct priority;
	string Comment;
	wxColour colour;

	void Reset();
	void Next();

	string ToString();

	bool operator==(const Building& toCompare);
	bool operator==(const StepParameters& toCompare);
};
