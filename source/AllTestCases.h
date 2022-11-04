#pragma once

#include <iostream>

#include "engine/tests/PhysicsTests.h"

template<typename T>
bool IsCorrect(T answer, T correct_answer)
{
	return answer == correct_answer;
}

static void PlayPhysicsTestCases()
{
	PhysicsTests* tests = new PhysicsTests();

	std::cout << "Physic tests: " << std::endl;
	std::cout << IsCorrect(tests->CheckBlockPhysicsBetweenTwoObjects(), true) << std::endl;
	std::cout << IsCorrect(tests->CheckOverlappingBetweenTwoObjects(), true) << std::endl;

	delete tests;
}