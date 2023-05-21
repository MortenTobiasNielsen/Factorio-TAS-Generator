#include "CommandStack.h"

void CommandStack::Clear()
{
	tail = 0;
	head = 0;
	hair = 0;
}

void CommandStack::Push(Command command)
{
	buffer[head] = command;
	head = (head + 1) % size;
	hair = head;
	tail = head != tail ? tail : (tail + 1) % size;
}

Command CommandStack::Pop()
{
	if (head == tail) 
		return {0, T_NULL, {}};
	head = (head + size - 1) % size;
	return buffer[head];
}

Command CommandStack::PopBack()
{
	if (head == hair)
		return {0, T_NULL, {}};
	int head_copy = head;
	head = (head + 1) % size;
	return buffer[head_copy];
}
