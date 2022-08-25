#pragma once

#include <iostream>

#include "engine/managers/physics_tests/CheckBlockPhysicsBetweenTwoObjects.h"
#include "engine/managers/physics_tests/CheckOverlappingBetweenTwoObjects.h"

template<typename T>
bool IsCorrect(T answer, T correct_answer)
{
	return answer == correct_answer;
}

static void PlayPhysicsTestCases()
{
	std::cout << IsCorrect(CheckBlockPhysicsBetweenTwoObjects(), true) << std::endl;
	std::cout << IsCorrect(CheckOverlappingBetweenTwoObjects(), true) << std::endl;
}