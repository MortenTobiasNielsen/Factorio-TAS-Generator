#include "StepParameters.h"

StepParameters::StepParameters(double InitialX, double InitialY)
{
	X = InitialX;
	Y = InitialY;
	OriginalX = InitialX;
	OriginalY = InitialY;

	OrientationEnum = North;
	StepEnum = e_stop;
	Size = 1;
	Buildings = 1;
	BuildingIndex = 0;
}

void StepParameters::Reset()
{
	X = OriginalX;
	Y = OriginalY;
}

void StepParameters::Next()
{
	if (Direction == struct_direction_list.north)
	{
		Y -= Size;
		return;
	}

	if (Direction == struct_direction_list.south)
	{
		Y += Size;
		return;
	}

	if (Direction == struct_direction_list.east)
	{
		X += Size;
		return;
	}

	if (Direction == struct_direction_list.west)
	{
		X -= Size;
		return;
	}
}

string StepParameters::ToString()
{
	switch (StepEnum)
	{

		case e_start:
		case e_pause:
		case e_save:
			return Step + ";" + ";" + ";" + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";";

		case e_stop:
		case e_game_speed:
		case e_idle:
		case e_pick_up:
			return Step + ";" + ";" + ";" + Amount + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";";

		case e_build:
			return Step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + Orientation + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";";

		case e_craft:
			return Step + ";" + ";" + ";" + Amount + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";";

		case e_recipe:
		case e_filter:
			return Step + ";" + to_string(X) + ";" + to_string(Y) + ";" + Amount + ";" + Item + ";" + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";";

		case e_limit:
			return Step + ";" + to_string(X) + ";" + to_string(Y) + ";" + Amount + ";" + ";" + Orientation + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";";

		case e_rotate:
		case e_mine:
			return Step + ";" + to_string(X) + ";" + to_string(Y) + ";" + Amount + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";";

		case e_priority:
			return Step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + ";" + Orientation + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";";

		case e_put:
		case e_take:
			return Step + ";" + to_string(X) + ";" + to_string(Y) + ";" + Amount + ";" + Item + ";" + Orientation + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";";

		case e_launch:
		case e_walk:
			return Step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";";

		case e_tech:
			return Step + ";" + ";" + ";" + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";";

		case e_drop:
			return Step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + Orientation + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";";

		default:
			return Step + ";" + to_string(X) + ";" + to_string(Y) + ";" + Amount + ";" + Item + ";" + Orientation + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";";
	}
}

bool StepParameters::operator==(const Building& toCompare)
{
	if (toCompare.X == X && toCompare.Y == Y)
	{
		BuildingIndex = toCompare.type;
		OrientationEnum = toCompare.OrientationEnum;
		return true;
	}

	return false;
}

bool StepParameters::operator==(const StepParameters& toCompare)
{
	if (toCompare.X != X && toCompare.Y != Y)
	{
		return false;
	}

	if (toCompare.X == X && toCompare.Y == Y)
	{
		return true;
	}

	if (toCompare.Buildings < 2)
	{
		return false;
	}

	int amountOfBuildings = toCompare.Buildings;
	int size = toCompare.Size;

	if (toCompare.X == X)
	{
		if (toCompare.Direction == struct_direction_list.south)
		{
			if (toCompare.Y > Y)
			{
				return false;
			}

			for (int i = 1; i < amountOfBuildings; i++)
			{
				if (Y == toCompare.Y + i * toCompare.Size)
				{
					return true;
				}
			}
		}

		if (toCompare.Direction == struct_direction_list.north)
		{
			if (toCompare.Y < Y)
			{
				return false;
			}

			for (int i = 1; i < amountOfBuildings; i++)
			{
				if (Y == toCompare.Y - i * toCompare.Size)
				{
					return true;
				}
			}
		}
	}

	if (toCompare.Y == Y)
	{
		if (toCompare.Direction == struct_direction_list.east)
		{
			if (toCompare.X > X)
			{
				return false;
			}

			for (int i = 1; i < amountOfBuildings; i++)
			{
				if (X == toCompare.X + i * toCompare.Size)
				{
					return true;
				}
			}
		}

		if (toCompare.Direction == struct_direction_list.west)
		{
			if (toCompare.X < X)
			{
				return false;
			}

			for (int i = 1; i < amountOfBuildings; i++)
			{
				if (X == toCompare.X - i * toCompare.Size)
				{
					return true;
				}
			}
		}
	}

	return false;
}