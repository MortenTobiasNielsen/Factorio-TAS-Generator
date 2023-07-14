#pragma once

#include <vector>
#include <unordered_map>
#include <string>

namespace Priority
{
	enum Type
	{
		LEFT, NONE, RIGHT
	};

	static const std::vector<std::string> Names =
	{
		"Left",
		"None",
		"Right"
	};

	static inline std::unordered_map<std::string, Type> MapNameToType =
	{
		{Names[0], LEFT},
		{Names[1], NONE},
		{Names[2], RIGHT},

		// lowercase copy
		{"left", LEFT},
		{"none", NONE},
		{"right", RIGHT},
	};
};

// Merges a pair of priorities
struct PriorityStruct
{
	Priority::Type input = Priority::NONE;
	Priority::Type output = Priority::NONE;

	std::string ToString()
	{
		return Priority::Names[input] + "," + Priority::Names[output];
	}

	void FromString(std::string str)
	{
		size_t pos = str.find(',');

		auto in = Priority::MapNameToType.find(str.substr(0, pos));
		auto out = Priority::MapNameToType.find(str.substr(pos + 1, str.size()));

		input = in != Priority::MapNameToType.end() ? in->second : Priority::NONE;
		output = out != Priority::MapNameToType.end() ? out->second : Priority::NONE;
	}
};
