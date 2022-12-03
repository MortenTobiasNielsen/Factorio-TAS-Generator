#include "TaskNameToEnum.h"

TaskName ToTaskName(string task)
{
	return TaskNames.find(task)->second;
}