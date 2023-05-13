#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

enum CommandType
{
	NIL, ADD, DELETE, MODIFY, MOVE
};
struct Command
{
	int row;				// The row the action happened at
	CommandType type;		// The type so it can be reversed
	vector<string> rows;	// Add should have one string representing a whole row. move should contain 2 rows, one for the current value and one for the new value 
	int by;					// for move - negative values will be move up
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

