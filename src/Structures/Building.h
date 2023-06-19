#pragma once

#include "Orientation.h"

struct Building
{
	double X;
	double Y;
	int type;
	Orientation OrientationEnum;

	Building(double x)
	{
		X = x;
		Y = 0;
		type = 0;
		OrientationEnum = North;
	}
};