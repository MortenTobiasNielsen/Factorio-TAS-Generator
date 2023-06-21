#pragma once

#include <vector>
#include <map>
#include <string>

/*
Orientation and Direction is the same type, but different fields.
	Orientation is used for the direction a building is facing
	Direction is used for multibuild

Factorio uses a longer list of directions: https://lua-api.factorio.com/latest/defines.html#defines.direction
Factorio also uses a float between 0 and 1 to indicate direction.

Buildings and vehicles can't be placed in half directions, with the exception of rails.
The half directions are otherwise exclusive to characters and biters (which is why they aren't implemented)
Underground belts are special as they use both belt_direction and building orientation (not implemented).
*/

static const struct
{
	std::string north = "defines.direction.north";	
	std::string east = "defines.direction.east";
	std::string south = "defines.direction.south";
	std::string west = "defines.direction.west";
} orientation_defines;

static const std::vector<std::string> orientation_defines_list
{
	orientation_defines.north,
	orientation_defines.east,
	orientation_defines.south,
	orientation_defines.west,
};

static const std::vector<std::string> orientation_list
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

static inline std::map<std::string, Orientation> MapStringToOrientation
{
	{orientation_list[North], North},
	{orientation_list[East], East},
	{orientation_list[South], South},
	{orientation_list[West], West},
	{"north", North},
	{"east", East},
	{"south", South},
	{"west", West}
};
