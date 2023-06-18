#pragma once
#include <vector>
#include <string>
#include <tuple>

#include "Structures\StepParameters.h"

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
	// The row the action happened at
	int row;
	// The type so it can be reversed
	CommandType type;
	// List of modified rows: Tuple of row index and row data
	vector<tuple<int, StepParameters>> rows;	 
};

class CommandStack
{
	// missing template actions

private:
	static inline const int size = 32;
	Command buffer[size] = {};
	int head = 0, tail = 0, hair = 0;

public:
	CommandStack() {}

	void Clear();
	void Push(Command command);
	Command Pop();
	Command PopBack();
};

