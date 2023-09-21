#include "Step.h"

#include "../Data/BuildingNames.h"

#include <format>

Step::Step(double InitialX, double InitialY)
{
	X = InitialX;
	Y = InitialY;
	OriginalX = InitialX;
	OriginalY = InitialY;
}

string Step::AmountLua()
{
	if (type == e_game_speed)
		return to_string(static_cast<float>(amount < 1 ? 1 : amount) / 100.0);
	else if (amount <= 0)
	{
		if (type == e_rotate || type == e_idle || type == e_pick_up)
			return "1";
		else if (type == e_mine)
			return "1000";
		else
			return "-1";
	}
	else return to_string(amount);
}

string Step::AmountGrid()
{
	if (type == e_game_speed)
	{
		return std::format("{}%", amount);
	}
	if (amount < 1)
	{
		return "All";
	}

	return to_string(amount);
}

void Step::Reset()
{
	X = OriginalX;
	Y = OriginalY;
}

void Step::Next()
{
	switch (Direction)
	{
		case North: 
			Y -= Size; 
			break;
		case South: 
			Y += Size; 
			break;
		case East: 
			X += Size; 
			break;
		case West: 
			X -= Size; 
			break;
	}
}

string Step::ToString()
{
	const string string_end = ";" + Comment + ";" + colour.GetAsString().ToStdString() + ";" + Modifiers.ToString() + ";";
	const string steptype = StepNames[type];
	switch (type)
	{
		case e_never_idle:
		case e_keep_crafting:
		case e_keep_on_path:
		case e_keep_walking:
		case e_pause:
		case e_save:
		case e_next:
			return steptype + ";" + ";" + ";" + ";" + ";" + ";" + ";" + ";" + string_end;

		case e_game_speed:
			return steptype + ";" + ";" + ";" + to_string(amount / 100) + ";" + ";" + ";" + ";" + ";" + string_end;

		case e_stop:
		case e_idle:
		case e_pick_up:
			return steptype + ";" + ";" + ";" + to_string(amount) + ";" + ";" + ";" + ";" + ";" + string_end;

		case e_build:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + orientation_list[orientation] + ";" + orientation_list[Direction] + ";" + to_string(Size) + ";" + to_string(Buildings) + string_end;

		case e_craft:
			return steptype + ";" + ";" + ";" + to_string(amount) + ";" + Item + ";" + ";" + ";" + ";" + string_end;

		case e_recipe:
		case e_filter:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(amount) + ";" + Item + ";" + ";" + orientation_list[Direction] + ";" + to_string(Size) + ";" + to_string(Buildings) + string_end;

		case e_limit:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(amount) + ";" + ";" + "Chest" + ";" + orientation_list[Direction] + ";" + to_string(Size) + ";" + to_string(Buildings) + string_end;

		case e_rotate:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(amount) + ";" + Item + ";" + ";" + orientation_list[Direction] + ";" + to_string(Size) + ";" + to_string(Buildings) + string_end;

		case e_mine:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(amount) + ";" + Item + ";" + ";" + ";" + ";" + string_end;

		case e_priority:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + ";" + priority.ToString() + ";" + orientation_list[Direction] + ";" + to_string(Size) + ";" + to_string(Buildings) + string_end;

		[[likely]] case e_put:
		[[likely]] case e_take:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(amount) + ";" + Item + ";" + inventory_types_list[inventory] + ";" + orientation_list[Direction] + ";" + to_string(Size) + ";" + to_string(Buildings) + string_end;

		case e_launch:
		[[likely]] case e_walk:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + ";" + ";" + ";" + ";" + string_end;

		case e_tech:
			return steptype + ";" + ";" + ";" + ";" + Item + ";" + ";" + ";" + ";" + string_end;

		case e_drop:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + orientation_list[orientation] + ";" + ";" + ";" + string_end;

		case e_shoot:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(amount) + ";" + ";" + ";" + ";" + ";" + string_end;
		case e_throw:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + ";" + ";" + ";" + string_end;

		default:
			return steptype + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(amount) + ";" + Item + ";" + orientation_list[orientation] + ";" + orientation_list[Direction] + ";" + to_string(Size) + ";" + to_string(Buildings) + string_end;
	}
}

bool Step::operator==(const Building& toCompare)
{
	if (toCompare.X == X && toCompare.Y == Y)
	{
		BuildingIndex = toCompare.type;
		orientation = toCompare.OrientationEnum;
		return true;
	}

	return false;
}

bool Step::operator==(const Step& toCompare)
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
		if (toCompare.Direction == South)
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

		if (toCompare.Direction == North)
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
		if (toCompare.Direction == East)
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

		if (toCompare.Direction == West)
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