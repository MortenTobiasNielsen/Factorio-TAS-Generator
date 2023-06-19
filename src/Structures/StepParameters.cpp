#include "StepParameters.h"

StepParameters::StepParameters(double InitialX, double InitialY)
{
	X = InitialX;
	Y = InitialY;
	OriginalX = InitialX;
	OriginalY = InitialY;

	OrientationEnum = North;
	type = e_stop;
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
	if (Direction == orientation_list[North])
	{
		Y -= Size;
		return;
	}

	if (Direction == orientation_list[South])
	{
		Y += Size;
		return;
	}

	if (Direction == orientation_list[East])
	{
		X += Size;
		return;
	}

	if (Direction == orientation_list[West])
	{
		X -= Size;
		return;
	}
}

string StepParameters::ToString()
{
	string step = StepNames[type];
	switch (type)
	{
		case e_never_idle:
		case e_keep_crafting:
		case e_keep_on_path:
		case e_keep_walking:
		case e_pause:
		case e_save:
			return step + ";" + ";" + ";" + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_stop:
		case e_game_speed:
		case e_idle:
		case e_pick_up:
			return step + ";" + ";" + ";" + to_string(Amount) + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_build:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + Orientation + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_craft:
			return step + ";" + ";" + ";" + to_string(Amount) + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_recipe:
		case e_filter:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_limit:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + ";" + Orientation + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_rotate:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_mine:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_priority:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + ";" + PriorityIn + "," + PriorityOut + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		[[likely]] case e_put:
		[[likely]] case e_take:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + FromInto + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_launch:
		[[likely]] case e_walk:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_tech:
			return step + ";" + ";" + ";" + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_drop:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + Orientation + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		case e_shoot:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";
		case e_throw:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";

		default:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + Orientation + ";" + Direction + ";" + to_string(Size) + ";" + to_string(Buildings) + ";" + Comment + ";" + Colour + ";" + Modifiers + ";";
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
		if (toCompare.Direction == orientation_list[South])
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

		if (toCompare.Direction == orientation_list[North])
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
		if (toCompare.Direction == orientation_list[East])
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

		if (toCompare.Direction == orientation_list[West])
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