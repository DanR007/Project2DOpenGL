#pragma once

#include <iostream>

#include "engine/tests/PhysicsTests.h"
#include "engine/tests/AStarTests.h"

template<typename T>
bool IsCorrect(T answer, T correct_answer)
{
	return answer == correct_answer;
}

static void PlayPhysicsTestCases()
{
	PhysicsTests* tests = new PhysicsTests();

	std::cout << std::endl << "Physic tests: " << std::endl;
	std::cout << IsCorrect(tests->CheckBlockPhysicsBetweenTwoObjectsMustBeFalse(), false) << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << IsCorrect(tests->CheckBlockPhysicsBetweenTwoObjectsMustBeTrue(), true) << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << IsCorrect(tests->CheckOverlappingBetweenTwoObjectsMustBeFalse(), false) << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << IsCorrect(tests->CheckOverlappingBetweenTwoObjectsMustBeTrue(), true) << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << IsCorrect(tests->CheckRaycastMustBeTrueAndPosZero(), true) << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << IsCorrect(tests->CheckRaycastMustBeFalse(), false) << std::endl;
	//std::cout << "-----------------------" << std::endl;
	//std::cout << IsCorrect(tests->CheckRaycastMustBeTruePosSqrtOf3MUltyply10ByXAndMinus10ByY(), true) << std::endl;
	std::cout << "=======================" << std::endl;
	delete tests;
}

static void PlayNavMeshTests()
{
	std::cout << std::endl << "NavMesh tests: " << std::endl;
	NavMeshTests* nav_mesh_tests = new NavMeshTests();

	std::cout << "TriangulateTestMap: " << std::endl;
	nav_mesh_tests->TriangulateTestMap();
	std::cout << "-----------------------" << std::endl;
	std::cout <<"AStarTestPointsInOneTriangle: " << std::endl << nav_mesh_tests->AStarTestPointsInOneTriangle() << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << "AStarTestPointsInTwoNeightbouringTrianglesAndNotSeparatedByWalls: " << std::endl <<
		nav_mesh_tests->AStarTestPointsInTwoNeightbouringTrianglesAndNotSeparatedByWalls() << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << "AStarTestPointsSeparatedByWalls: " << std::endl << nav_mesh_tests->AStarTestPointsSeparatedByWalls() << std::endl;
	std::cout << "=======================" << std::endl;

	delete nav_mesh_tests;
}