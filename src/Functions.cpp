#pragma once

#include "Functions.h"

bool check_input(const string& item, const vector<string>& all_items)
{
	for (int i = 0; i < all_items.size(); i++)
	{
		if (item.length() != all_items[i].length())
		{
			continue;
		}

		for (int j = 0; j < item.length(); j++)
		{
			if (item[j] != all_items[i][j])
			{
				break;
			}

			if (j == item.length() - 1)
			{
				return true;
			}
		}
	}

	return false;
}

void find_coordinates(std::string& x_cord, std::string& y_cord, std::string& direction, std::string& building_size)
{
	if (direction == "north" || direction == "North")
	{
		y_cord = std::to_string(std::stof(y_cord) - std::stof(building_size));

	}
	else if (direction == "south" || direction == "South")
	{
		y_cord = std::to_string(std::stof(y_cord) + std::stof(building_size));

	}
	else if (direction == "east" || direction == "East")
	{
		x_cord = std::to_string(std::stof(x_cord) + std::stof(building_size));

	}
	else if (direction == "west" || direction == "West")
	{
		x_cord = std::to_string(std::stof(x_cord) - std::stof(building_size));
	}
}

string Capitalize(const wxString& stringToCapitalize, const bool isItem)
{
	if (stringToCapitalize == "")
	{
		return stringToCapitalize.ToStdString();
	}

	string capitalizedString = stringToCapitalize.ToStdString();
	capitalizedString[0] = std::toupper(stringToCapitalize[0]);
	for (int i = 1; i < capitalizedString.length(); ++i)
	{
		capitalizedString[i] = tolower(stringToCapitalize[i]);
	}

	if (!isItem)
	{
		return capitalizedString;
	}

	int stringLength = capitalizedString.length();
	if (stringLength > 3 &&  capitalizedString.substr(stringLength - 3, 3) == "mk2")
	{
		capitalizedString[stringLength - 3] = 'M';
		capitalizedString[stringLength - 2] = 'K';
		capitalizedString[stringLength - 1] = '2';
	}

	return capitalizedString;
}

bool equals_ignore_case(const std::string_view& lhs, const std::string_view& rhs)
{
	auto to_lower{std::ranges::views::transform(std::tolower)};
	return std::ranges::equal(lhs | to_lower, rhs | to_lower);
}

bool starts_with_ignore_case(const std::string& base, const std::string& start)
{
	if (base.size() < start.size()) return false;
	for (int i = 0; i < start.size(); i++)
		if (toupper(base[i]) != toupper(start[i]))
			return false;
	return true;
}

bool starts_with_ignore_case(const wxString& base, const wxString& start)
{
	if (base.size() < start.size()) return false;
	for (int i = 0; i < start.size(); i++)
		if (toupper(base[i]) != toupper(start[i]))
			return false;
	return true;
}

bool is_number(const std::string& str)
{
	for (auto s : str)
	{
		if (!std::isdigit(s))
		{
			return false;
		}
	}

	return true;
}

vector<string> get_keys(map<string, vector<StepParameters>> map)
{
	vector<string> keys;
	for (std::map<string, vector<StepParameters>>::iterator it = map.begin(); it != map.end(); ++it)
	{
		keys.push_back(it->first);
	}

	return keys;
}

int ProcessBuildStep(vector<Building>& buildings, int buildingsInSnapShot, StepParameters& stepParameters)
{
	buildings[buildingsInSnapShot].X = stepParameters.X;
	buildings[buildingsInSnapShot].Y = stepParameters.Y;
	buildings[buildingsInSnapShot].type = stepParameters.BuildingIndex;
	buildings[buildingsInSnapShot].OrientationEnum = stepParameters.OrientationEnum;
	buildingsInSnapShot++;

	if (stepParameters.Buildings == 1)
	{
		return buildingsInSnapShot;
	}

	for (int i = 1; i < stepParameters.Buildings; i++)
	{
		stepParameters.Next();
		
		buildings[buildingsInSnapShot].X = stepParameters.X;
		buildings[buildingsInSnapShot].Y = stepParameters.Y;
		buildings[buildingsInSnapShot].type = stepParameters.BuildingIndex;
		buildings[buildingsInSnapShot].OrientationEnum = stepParameters.OrientationEnum;
		buildingsInSnapShot++;
	}

	stepParameters.Reset();
	return buildingsInSnapShot;
}

void ProcessMiningStep(vector<Building>& buildings, int buildingsInSnapShot, StepParameters& stepParameters)
{
	for (int i = 0; i < buildingsInSnapShot; i++)
	{
		if (stepParameters == buildings[i])
		{
			buildings[i].X = -0.4523543; // Invalidate the building
			return;
		}
	}
}

bool BuildingExists(vector<Building>& buildings, int buildingsInSnapShot, StepParameters& stepParameters)
{
	int buildingsFound = 0;
	Orientation firstOrientation = North;

	for (int i = 0; i < stepParameters.Buildings; i++)
	{
		for (int j = buildingsInSnapShot - 1; j > -1; j--)
		{
			if (stepParameters == buildings[j])
			{
				if (buildingsFound == 0)
				{
					firstOrientation = buildings[j].OrientationEnum;
				}

				buildingsFound++;
				break;
			}
		}

		if (buildingsFound == stepParameters.Buildings)
		{
			stepParameters.Reset();
			stepParameters.OrientationEnum = firstOrientation;
			return true;
		}

		stepParameters.Next();
	}

	stepParameters.Reset();
	return false;
}

void PopulateGrid(wxGrid* grid, int row, GridEntry* gridEntry)
{
	grid->SetCellValue(row, 0, gridEntry->Step);
	grid->SetCellValue(row, 1, gridEntry->X);
	grid->SetCellValue(row, 2, gridEntry->Y);
	grid->SetCellValue(row, 3, gridEntry->Amount);
	grid->SetCellValue(row, 4, gridEntry->Item);
	grid->SetCellValue(row, 5, gridEntry->BuildingOrientation);
	grid->SetCellValue(row, 6, gridEntry->DirectionToBuild);
	grid->SetCellValue(row, 7, gridEntry->BuildingSize);
	grid->SetCellValue(row, 8, gridEntry->AmountOfBuildings);
	grid->SetCellValue(row, 9, gridEntry->Comment);
}

bool StringContainsAny(const wxString& str, const string& chars)
{
	for (int i = 0; i < str.size(); i++)
	{
		for (int j = 0; j < chars.size(); j++)
		{
			if (str[i] == str[j])
			{
				return true;
			}

		}
	}

	return false;
}

vector<wxString> Split(const string& s, char delim)
{
	vector<wxString> result;
	stringstream ss(s);
	string item;

	while (std::getline(ss, item, delim))
	{
		result.push_back(item);
	}
	if (result.empty()) result.push_back(s);
	return result;
}
