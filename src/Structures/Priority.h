#pragma once

#include <vector>
#include <map>
#include <string>

enum INPUT_OUTPUT
{
	LEFT, NONE, RIGHT
};

static const std::vector<std::string> input_output =
{
	"Left",
	"None",
	"Right"
};

static inline std::map<std::string, INPUT_OUTPUT> map_input_output =
{
	{input_output[0], LEFT},
	{input_output[1], NONE},
	{input_output[2], RIGHT}
};