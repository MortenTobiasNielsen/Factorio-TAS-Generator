#include "CommandStack.h"

void CommandStack::Push(Command command)
{
	buffer[head] = command;
	hair = head;
	head = (head + 1) % size;
	tail = head != tail ? tail : (tail + 1) % size;
}

Command CommandStack::Pop()
{
	if (head == tail) 
		return {0, NIL, {}, 0};
	head = (head + size - 1) % size;
	return buffer[head];
}

Command CommandStack::PopBack()
{
	if (head == hair)
		return {0, NIL, {}, 0};
	int head_copy = head;
	head = (head + 1) % size;
	return buffer[head_copy];
}
