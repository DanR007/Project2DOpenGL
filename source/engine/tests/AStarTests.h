#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../AI/NavMesh.h"
#include "../AI/AStar.h"

#include "../AI/poly2tri/poly2tri.h"

NavMesh* nav_mesh;
std::vector<std::string> test_map = {
	"OOOOOOOOOOOO",
	"OWWWWWWWWWWO",
	"OW........WO",
	"OW........WO",
	"OW........WO",
	"OWWWWWW..WWO",
	"OOOOOOW..WOO",
	"OOOOOOW..WOO",
	"OWWWWWW..WWO",
	"OW........WO",
	"OW........WO",
	"OW........WO",
	"OWWWWWWWWWWO"
};

void PrintPoints(p2t::Point* p1, p2t::Point* p2)
{
	std::cout << "Points not equal first point (answer by algorithm): (x, y) " << p1->_pos.x <<" " << p1->_pos.y
		<< " Second (My answer): " << p2->_pos.x <<" " << p2->_pos.y << std::endl;
}

void GetPointsFromMap(NavMesh* nav_mesh)
{
	nav_mesh->FillArrayOfPoints(test_map, glm::dvec2(45., 45.));
	std::vector<p2t::Point*> points = nav_mesh->GetArrayOfPoints();
	if (points.size() == 12)
	{
		std::vector<p2t::Point*> answer_points =
		{
			new p2t::Point(67.5,  517.5),
			new p2t::Point(427.5, 517.5),
			new p2t::Point(427.5, 382.5),
			new p2t::Point(382.5, 382.5),
			new p2t::Point(382.5, 202.5),
			new p2t::Point(427.5, 202.5),
			new p2t::Point(427.5, 67.5),
			new p2t::Point(67.5,  67.5),
			new p2t::Point(67.5,  202.5),
			new p2t::Point(292.5, 202.5),
			new p2t::Point(292.5, 382.5),
			new p2t::Point(67.5,  382.5)
		};
		bool flag = true;
		for (int i = 0; i < answer_points.size(); i++)
		{
			if (*points[i] != *answer_points[i])
			{
				std::cout << "ERROR ID: " << i << "\t";
				PrintPoints(points[i], answer_points[i]);
				flag = false;
			}
		}

		if (flag)
		{
			std::cout << "All Points right" << std::endl << std::endl;;
		}
	}
	else
	{
		std::cout << "Count points from map: " << points.size() << " but true is 12" << std::endl;
	}
}

void TriangulateTestMap(NavMesh* nav_mesh)
{
	nav_mesh->_cdt = new p2t::CDT(nav_mesh->_points);
	nav_mesh->_cdt->Triangulate();
	nav_mesh->_triangles = nav_mesh->_cdt->GetTriangles();
	std::vector<p2t::Triangle*> triangles = nav_mesh->_triangles;
	for (p2t::Triangle* tr : triangles)
	{
		tr->DebugPrint();
	}
}

bool AStarTestPointsInOneTriangle(NavMesh* nav_mesh)
{

	std::vector<p2t::Point*> answer_path = 
	{
		new p2t::Point(397.5, 497.5)
	};
	AStar* a_star = new AStar();
	p2t::Point* start = new p2t::Point(77.5, 517.5), *target = new p2t::Point(397.5, 497.5);
	a_star->DevelopPath(nav_mesh->GetTriangles(), start, target);

	std::vector<p2t::Point*> path = a_star->GetPath();

	bool flag = true;

	for (int i = 0; i < answer_path.size(); i++)
	{
		if (*answer_path[i] != *path[i])
		{
			flag = false;
			PrintPoints(path[i], answer_path[i]);
		}
	}

	for (p2t::Point* p : answer_path)
	{
		delete p;
		p = nullptr;
	}
	answer_path.clear();

	delete start;
	delete target;
	delete a_star;

	return flag;
}

bool AStarTestPointsInTwoNeightbouringTrianglesAndNotSeparatedByWalls(NavMesh* nav_mesh)
{
	std::vector<p2t::Point*> answer_path =
	{
		new p2t::Point(292.5, 382.5),
		new p2t::Point(302.5, 382.5)
	};
	AStar* a_star = new AStar();
	p2t::Point* start = new p2t::Point(77.5, 402.5), * target = new p2t::Point(302.5, 382.5);
	a_star->DevelopPath(nav_mesh->GetTriangles(), start, target);

	std::vector<p2t::Point*> path = a_star->GetPath();

	bool flag = true;

	for (int i = 0; i < answer_path.size(); i++)
	{
		if (*answer_path[i] != *path[i])
		{
			flag = false;
			PrintPoints(path[i], answer_path[i]);
		}
	}

	for (p2t::Point* p : answer_path)
	{
		delete p;
		p = nullptr;
	}
	answer_path.clear();

	delete start;
	delete target;
	delete a_star;

	return flag;
}

bool AStarTestPointsSeparatedByWalls(NavMesh* nav_mesh)
{
	std::vector<p2t::Point*> answer_path =
	{
		new p2t::Point(292.5, 382.5),
		new p2t::Point(292.5, 202.5),
		new p2t::Point(77.5, 102.5)
	};
	AStar* a_star = new AStar();
	p2t::Point* start = new p2t::Point(77.5, 402.5), * target = new p2t::Point(77.5, 102.5);
	a_star->DevelopPath(nav_mesh->GetTriangles(), start, target);

	std::vector<p2t::Point*> path = a_star->GetPath();

	bool flag = true;

	for (int i = 0; i < answer_path.size(); i++)
	{
		if (*answer_path[i] != *path[i])
		{
			flag = false;
			PrintPoints(path[i], answer_path[i]);
		}
	}
	for (p2t::Point* p : answer_path)
	{
		delete p;
		p = nullptr;
	}
	answer_path.clear();
	delete start;
	delete target;
	delete a_star;

	return flag;
}