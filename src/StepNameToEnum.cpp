#include "StepNameToEnum.h"

StepType ToStepType(string step)
{
	return MapStepNameToStepType.find(step)->second;
}