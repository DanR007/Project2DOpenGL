#include "AStar.h"

#include "../default_classes/Actor.h"

#include "poly2tri/common/shapes.h" 

#include "../../main.h"

#include <algorithm>

AStar* g_a_star;

AStar::NavMeshPoint::NavMeshPoint(p2t::Point* current_point)
{
	_current_point = current_point;
	_cost = 0;
	_length = 0;
	_previous_point = nullptr;
}
AStar::NavMeshPoint::NavMeshPoint(NavMeshPoint* previous_point, p2t::Point* current)
{
	_current_point = current;
	_previous_point = previous_point;
	_length = previous_point->_length + AStar::Length(previous_point->_current_point->_pos - _current_point->_pos);
	_cost = _length + AStar::Length(g_a_star->_target->_pos - _current_point->_pos);
}
void AStar::DevelopPath(const std::vector<p2t::Triangle*> nav_mesh, p2t::Point* start_point, p2t::Point* target)
{
	g_a_star = this;

	_current_position = start_point;
	_target = target;

	p2t::Triangle* start_triangle = nullptr, * finish_triangle = nullptr;

	for (p2t::Triangle* t : nav_mesh)
	{
		if (t->ContainPoint(start_point) && !start_triangle)
		{
			start_triangle = t;
		}
		if (t->ContainPoint(target) && !finish_triangle)
		{
			finish_triangle = t;
		}
		if (finish_triangle && start_triangle)
		{
			break;
		}
	}

	if (finish_triangle == start_triangle)
	{
		_path.push_back(target);
		return;
	}

	DevelopPath(start_triangle, finish_triangle);

	FillPath(start_point);
	ClearNavPath();
}

void AStar::ClearNavPath()
{
	for (NavMeshPoint* p : _close_coordinates)
	{
		delete p;
		p = nullptr;
	}
	_close_coordinates.clear();
	while(_open_coordinates.empty() == false)
	{
		NavMeshPoint* p = _open_coordinates.top();
		_open_coordinates.pop();
		delete p;
		p = nullptr;
	}
}

void AStar::FillPath(p2t::Point* start)
{
	NavMeshPoint* current_point = _close_coordinates.back();

	while (current_point->GetPoint() != start)
	{
		_path.emplace(_path.begin(), current_point->GetPoint());

		current_point = current_point->GetPreviousPoint();
	}
}

void AStar::DevelopPath(p2t::Triangle* start_triangle, p2t::Triangle* finish_triangle)
{
	NavMeshPoint* start = new NavMeshPoint(_current_position);

	_close_coordinates.push_back(start);

	_open_coordinates.push(new NavMeshPoint(start, start_triangle->GetPoint(0)));
	_open_coordinates.push(new NavMeshPoint(start, start_triangle->GetPoint(1)));
	_open_coordinates.push(new NavMeshPoint(start, start_triangle->GetPoint(2)));

	NavMeshPoint* point = _open_coordinates.top();

	_close_coordinates.push_back(point);
	_open_coordinates.pop();

	while (finish_triangle->Contains(point->GetPoint()) == false)
	{
		std::vector<p2t::Edge*> edges = point->GetPoint()->edge_list;
		for (p2t::Edge* e : edges)
		{
			p2t::Point* p1, * p2;
			p1 = e->GetPoint1();
			p2 = e->GetPoint2();
			NavMeshPoint* new_point1, *new_point2;
			std::vector<NavMeshPoint*>::iterator close_found_point1, close_found_point2,
				open_found_point1, open_found_point2;
			if (p1 != point->GetPoint())
			{
				new_point1 = new NavMeshPoint(point, p1);
				close_found_point1 = std::find(_close_coordinates.begin(), _close_coordinates.end(), new_point1);
				
				if (close_found_point1 == _close_coordinates.end())
				{
					_open_coordinates.push(new_point1);
				}
				else
				{
					delete new_point1;
				}
			}
			else
			{
				new_point2 = new NavMeshPoint(point, p2);
				close_found_point2 = std::find(_close_coordinates.begin(), _close_coordinates.end(), new_point2);
				
				if (close_found_point2 == _close_coordinates.end())
				{
					_open_coordinates.push(new_point2);
				}
				else
				{
					delete new_point2;
				}
			}
		}

		point = _open_coordinates.top();
		_close_coordinates.push_back(point);
		_open_coordinates.pop();
	}

	_close_coordinates.push_back(new NavMeshPoint(point, _target));
}



