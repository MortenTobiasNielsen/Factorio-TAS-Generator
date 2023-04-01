#pragma once

#include <vector>
#include <map>
#include <string>

static const struct
{
	std::string north = "defines.direction.north";
	std::string south = "defines.direction.south";
	std::string east = "defines.direction.east";
	std::string west = "defines.direction.west";
} build_direction_struct;

static const std::vector<std::string> build_orientations =
{
	"North",
	"East",
	"South",
	"West"
};

enum Orientation
{
	North,
	East,
	South,
	West,
};

static inline std::map<std::string, Orientation> OrientationToEnum =
{
	{build_orientations[North], North},
	{build_orientations[East], East},
	{build_orientations[South], South},
	{build_orientations[West], West}
};