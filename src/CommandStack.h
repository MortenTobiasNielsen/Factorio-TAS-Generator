#pragma once
#include <vector>
#include <string>
#include <tuple>

#include "StepParameters.h"

using std::vector;
using std::string;
using std::tuple;

enum CommandType
{
	T_NULL, T_ADD, T_DELETE, T_MODIFY, 
	T_MOVE_UP, T_MOVE_FIVE_UP, T_MOVE_DOWN, T_MOVE_FIVE_DOWN
};
struct Command
{
	int row;				// The row the action happened at
	CommandType type;		// The type so it can be reversed
	// List of modified rows: Tuple of row index and row data
	vector<tuple<int, StepParameters>> rows;	 
};

class CommandStack
{
	// missing template actions

private:
	const int size = 32;
	Command buffer[32] = {};
	int head = 0, tail = 0, hair = 0;

public:
	CommandStack() {}

	void Push(Command command);
	Command Pop();
	Command PopBack();
};

