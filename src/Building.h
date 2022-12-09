#pragma once

#include "utils.h"

struct Building
{
	double X;
	double Y;
	int type;
	Orientation orientation;

	Building(double x)
	{
		X = x;
		Y = 0;
		type = 0;
		orientation = North;
	}
};