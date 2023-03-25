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
	
	delete tests;
}

static void PlayNavMeshTests()
{
	std::cout << std::endl << "NavMesh tests there's nothing: " << std::endl;
}