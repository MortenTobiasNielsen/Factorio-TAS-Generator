#include "TaskNameToEnum.h"

TaskType ToTaskType(string task)
{
	return MapTaskNameToTaskType.find(task)->second;
}