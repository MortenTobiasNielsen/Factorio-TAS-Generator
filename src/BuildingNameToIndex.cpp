#include "BuildingNameToIndex.h"

string FindBuildingName(int index)
{
	for (auto it = BuildingNameToIndex.begin(); it != BuildingNameToIndex.end(); ++it)
	{
		if (it->second == index)
		{
			return it->first;
		}
	}

	return "N/A";
}