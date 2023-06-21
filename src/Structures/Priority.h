#pragma once

#include <vector>
#include <map>
#include <string>

enum Priority
{
	LEFT, NONE, RIGHT
};

static const std::vector<std::string> PriorityStrings =
{
	"Left",
	"None",
	"Right"
};

static inline std::map<std::string, Priority> MapStringToPriority =
{
	{PriorityStrings[0], LEFT},
	{PriorityStrings[1], NONE},
	{PriorityStrings[2], RIGHT},
	{"LEFT", LEFT},
	{"NONE", NONE},
	{"RIGHT", RIGHT},
	{"left", LEFT},
	{"none", NONE},
	{"right", RIGHT},
};