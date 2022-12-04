#pragma once

#include "utils.h"

struct Building
{
	double X;
	double Y;
	int Index;
	Orientation OrientationIndex;

	Building(double x)
	{
		X = x;
		Y = 0;
		Index = 0;
		OrientationIndex = North;
	}
};