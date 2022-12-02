#pragma once

#include "StepParameters.h"

#include "Functions.h"
#include "BuildingNameToIndex.h"
#include "utils.h"

bool ValidateStep(int row, StepParameters stepParameters, bool validateBuildSteps = true);
bool IsValidBuildStep(StepParameters stepParameters);
bool IsValidRecipeStep(StepParameters stepParameters);
bool IsValidCraftStep(StepParameters stepParameters);
bool IsValidPutTakeStep(StepParameters stepParameters);
bool IsValidTechnologyStep(StepParameters stepParameters);
bool IsValidPriorityStep(StepParameters stepParameters);