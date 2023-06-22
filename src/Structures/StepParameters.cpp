#include "StepParameters.h"

StepParameters::StepParameters(double InitialX, double InitialY)
{
	X = InitialX;
	Y = InitialY;
	OriginalX = InitialX;
	OriginalY = InitialY;

	OrientationEnum = North;
	type = e_stop;
	BuildingIndex = 0;
}

Modifiers::Modifiers(string str)
{
	FromString(str);
}

void Modifiers::FromString(string str)
{
	walk_towards = str.find("walk towards") != std::string::npos;
	no_order = str.find("no order") != std::string::npos;
	cancel = str.find("cancel") != std::string::npos;
	wait_for = str.find("wait for") != std::string::npos;
	skip = str.find("skip") != std::string::npos;
	force = str.find("force") != std::string::npos;
	split = str.find("split") != std::string::npos;
}

string Modifiers::ToString()
{
	bool pointers[base_size] = {walk_towards, no_order, cancel, wait_for, skip, force, split};
	string out = "";
	for (int i = 0; i < base_size; i++)
		out += pointers[i] ? Modifiers::Strings[i] + ", " : "";
	return out.size() > 1 ? out.substr(0, out.size() - 2) : out;
}

void StepParameters::Reset()
{
	X = OriginalX;
	Y = OriginalY;
}

void StepParameters::Next()
{
	switch (multi_build.direction)
	{
		case North:
			Y -= multi_build.size;
			break;
		case South:
			Y += multi_build.size;
			break;
		case East:
			X += multi_build.size;
			break;
		case West:
			X -= multi_build.size;
			break;
	}
}

string StepParameters::ToString()
{
	string step = StepNames[type];
	string Colour = colour.GetAsString().ToStdString();
	switch (type)
	{
		case e_never_idle:
		case e_keep_crafting:
		case e_keep_on_path:
		case e_keep_walking:
		case e_pause:
		case e_save:
			return step + ";" + ";" + ";" + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_stop:
		case e_game_speed:
		case e_idle:
		case e_pick_up:
			return step + ";" + ";" + ";" + to_string(Amount) + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_build:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + orientation + ";" + orientation_list[multi_build.direction] + ";" + to_string(multi_build.size) + ";" + to_string(multi_build.buildings) + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_craft:
			return step + ";" + ";" + ";" + to_string(Amount) + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_recipe:
		case e_filter:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + ";" + orientation_list[multi_build.direction] + ";" + to_string(multi_build.size) + ";" + to_string(multi_build.buildings) + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_limit:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + ";" + orientation + ";" + orientation_list[multi_build.direction] + ";" + to_string(multi_build.size) + ";" + to_string(multi_build.buildings) + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_rotate:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + ";" + orientation_list[multi_build.direction] + ";" + to_string(multi_build.size) + ";" + to_string(multi_build.buildings) + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_mine:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_priority:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + ";" + PriorityStrings[priority.input] + "," + PriorityStrings[priority.output] + ";" + orientation_list[multi_build.direction] + ";" + to_string(multi_build.size) + ";" + to_string(multi_build.buildings) + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		[[likely]] case e_put:
		[[likely]] case e_take:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + FromInto + ";" + orientation_list[multi_build.direction] + ";" + to_string(multi_build.size) + ";" + to_string(multi_build.buildings) + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_launch:
		[[likely]] case e_walk:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_tech:
			return step + ";" + ";" + ";" + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_drop:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + orientation + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		case e_shoot:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";
		case e_throw:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + ";" + Item + ";" + ";" + ";" + ";" + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";

		default:
			return step + ";" + to_string(X) + ";" + to_string(Y) + ";" + to_string(Amount) + ";" + Item + ";" + orientation + ";" + orientation_list[multi_build.direction] + ";" + to_string(multi_build.size) + ";" + to_string(multi_build.buildings) + ";" + Comment + ";" + Colour + ";" + modifiers.ToString() + ";";
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

	if (toCompare.multi_build.buildings < 2)
	{
		return false;
	}

	int amountOfBuildings = toCompare.multi_build.buildings;
	int size = toCompare.multi_build.size;

	if (toCompare.X == X)
	{
		if (toCompare.multi_build.direction == South)
		{
			if (toCompare.Y > Y)
			{
				return false;
			}

			for (int i = 1; i < amountOfBuildings; i++)
			{
				if (Y == toCompare.Y + i * toCompare.multi_build.size)
				{
					return true;
				}
			}
		}

		if (toCompare.multi_build.direction == North)
		{
			if (toCompare.Y < Y)
			{
				return false;
			}

			for (int i = 1; i < amountOfBuildings; i++)
			{
				if (Y == toCompare.Y - i * toCompare.multi_build.size)
				{
					return true;
				}
			}
		}
	}

	if (toCompare.Y == Y)
	{
		if (toCompare.multi_build.direction == East)
		{
			if (toCompare.X > X)
			{
				return false;
			}

			for (int i = 1; i < amountOfBuildings; i++)
			{
				if (X == toCompare.X + i * toCompare.multi_build.size)
				{
					return true;
				}
			}
		}

		if (toCompare.multi_build.direction == West)
		{
			if (toCompare.X < X)
			{
				return false;
			}

			for (int i = 1; i < amountOfBuildings; i++)
			{
				if (X == toCompare.X - i * toCompare.multi_build.size)
				{
					return true;
				}
			}
		}
	}

	return false;
}