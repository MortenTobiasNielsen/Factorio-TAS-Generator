#pragma once

#include <string>
#include <fstream>
#include <wx/colour.h>

#include "Building.h"
#include "StepType.h"
#include "Orientation.h"

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
	int Size;
	int Buildings;
	int BuildingIndex;

	string Modifiers;

	Orientation OrientationEnum;
	StepType type;

	string Item;
	string FromInto;
	string Orientation;
	string Direction;
	string PriorityIn;
	string PriorityOut;
	string Comment;
	wxColour colour;

	void Reset();
	void Next();

	string ToString();

	bool operator==(const Building& toCompare);
	bool operator==(const StepParameters& toCompare);
};