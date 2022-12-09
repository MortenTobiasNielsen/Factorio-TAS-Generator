#include "BuildingNameToIndex.h"

string FindBuildingName(int index)
{
	if (index < 1 || index > BuildingNames.size())
	{
		return "N/A";
	}
	else
	{
		return BuildingNames[index];
	}	
}