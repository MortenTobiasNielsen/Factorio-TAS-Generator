#pragma once

#include <string>
#include <wx/wx.h>

#include "TaskNameToEnum.h"
#include "utils.h"

using std::string;

struct StepParameters
{
	double X;
	double Y;
	double OriginalX;
	double OriginalY;
	int Size;
	int Buildings;
	int BuildingIndex;

	TaskName TaskEnum;

	string Task;
	string Amount;
	wxString Item;
	wxString FromInto;
	wxString Orientation;
	wxString Direction;
	string PriorityIn;
	string PriorityOut;
	wxString Comment;

	StepParameters(double InitialX, double InitialY)
	{
		X = InitialX;
		Y = InitialY;
		OriginalX = InitialX;
		OriginalY = InitialY;
	}

	inline void Reset()
	{
		X = OriginalX;
		Y = OriginalY;
	}

	inline void Next()
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

	inline bool operator==(const Building& toCompare)
	{
		if (toCompare.X == X && toCompare.Y == Y)
		{
			return true;
		}
	}

	inline bool operator==(const StepParameters& toCompare)
	{
		if (toCompare.Task != struct_tasks_list.build ||
			(toCompare.X != X && toCompare.Y != Y))
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
};