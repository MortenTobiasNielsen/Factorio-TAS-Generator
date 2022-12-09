#pragma once

#include <string>
#include <fstream>

#include "Building.h"
#include "StepNameToEnum.h"
#include "utils.h"

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
	int Size;
	int Buildings;
	int BuildingIndex;

	Orientation OrientationIndex;
	StepType StepEnum;

	string Step;
	string Amount;
	string Item;
	string FromInto;
	string Orientation;
	string Direction;
	string PriorityIn;
	string PriorityOut;
	string Comment;

	void Reset();
	void Next();

	string ToString();

	bool operator==(const Building& toCompare);
	bool operator==(const StepParameters& toCompare);
};