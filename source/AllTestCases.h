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
	std::cout << IsCorrect(tests->CheckBlockPhysicsBetweenTwoObjectsMustBeTrue(), true) << std::endl;
	std::cout << IsCorrect(tests->CheckOverlappingBetweenTwoObjectsMustBeFalse(), false) << std::endl;
	std::cout << IsCorrect(tests->CheckOverlappingBetweenTwoObjectsMustBeTrue(), true) << std::endl;
	std::cout << "=======================" << std::endl;
	delete tests;
}

static void PlayNavMeshTests()
{
	std::cout << std::endl << "NavMesh tests: " << std::endl;
	NavMesh* nav_mesh = new NavMesh();

	std::cout << "GetPointsFromMap: " << std::endl;
	GetPointsFromMap(nav_mesh);
	std::cout << "-----------------------" << std::endl;
	std::cout << "TriangulateTestMap: " << std::endl;
	TriangulateTestMap(nav_mesh);
	std::cout << "-----------------------" << std::endl;
	std::cout <<"AStarTestPointsInOneTriangle: " << std::endl << AStarTestPointsInOneTriangle(nav_mesh) << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << "AStarTestPointsInTwoNeightbouringTrianglesAndNotSeparatedByWalls: " << std::endl <<
		AStarTestPointsInTwoNeightbouringTrianglesAndNotSeparatedByWalls(nav_mesh) << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << "AStarTestPointsSeparatedByWalls: " << std::endl << AStarTestPointsSeparatedByWalls(nav_mesh) << std::endl;
	std::cout << "=======================" << std::endl;
	delete nav_mesh;
}