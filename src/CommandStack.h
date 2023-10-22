#pragma once
#include <vector>
#include <string>

#include "Structures\Step.h"

using std::vector;
using std::string;

struct StepLine
{
	int row;
	Step step;

	bool operator < (const StepLine& other) const
	{
		return row < other.row;
	}
	bool operator > (const StepLine& other) const
	{
		return row > other.row;
	}
};

struct Command
{
	vector<StepLine> before = {};
	vector<StepLine> after = {};
	string template_name = ""; // The name of the template or empty for steps grid

	bool empty()
	{
		return before.empty() && after.empty();
	}
};

class CommandStack
{
private:
	static inline const int size = 128;
	Command buffer[size] = {};
	int head = 0, tail = 0, hair = 0;

public:
	CommandStack() {}

	void Clear();
	void Push(Command command);
	Command Pop();
	Command PopBack();
};
