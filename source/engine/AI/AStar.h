#pragma once 

#include <glm/vec2.hpp>

#include <cmath>
#include <vector>
#include <queue>

namespace p2t
{
	struct Point;
	class Triangle;
}

namespace Game
{
	class Actor;
}

class AStar
{
	struct NavMeshPoint
	{
		NavMeshPoint(p2t::Point* current_point);
		NavMeshPoint(NavMeshPoint* previous_point, p2t::Point* current);

		inline double GetCost() const { return _cost; }
		inline double GetLength() const { return _length; }
		inline p2t::Point* GetPoint() const { return _current_point; }
		inline NavMeshPoint* GetPreviousPoint() const { return _previous_point; }

		bool operator() (NavMeshPoint* l, NavMeshPoint* r) { return l->GetCost() > r->GetCost(); }
		bool operator== (NavMeshPoint* p) { return _current_point == (p->_current_point); }
	private:
		double _cost, _length;
		NavMeshPoint* _previous_point;
		p2t::Point* _current_point;
	};
public:
	AStar() {}
	void DevelopPath(const std::vector<p2t::Triangle*> nav_mesh, p2t::Point* position, p2t::Point* target);

	std::vector<p2t::Point*> GetPath() { return _path; }
	p2t::Point* GetPointOfPath() { return _path[_path_index]; }

	void ClearNavPath();
private:

	void FillPath(p2t::Point* start);
	void DevelopPath(p2t::Triangle* start_triangle, p2t::Triangle* finish_triangle);

	inline static double SquareDistance(const glm::dvec2& first, const glm::dvec2& second)
	{
		return std::pow(first.x - second.x, 2) + std::pow(first.y - second.y, 2);
	}
	inline static double Distance(const glm::dvec2& first, const glm::dvec2& second)
	{
		return std::sqrt(std::pow(first.x - second.x, 2) + std::pow(first.y - second.y, 2));
	}
	inline static double SquareLength(const glm::dvec2& vec)
	{
		return std::pow(vec.x , 2) + std::pow(vec.y, 2);
	}
	inline static double Length(const glm::dvec2& vec)
	{
		return std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
	}

	p2t::Point* _current_position,* _target;

	size_t _path_index;

	std::vector<p2t::Point*> _path;
	std::vector<NavMeshPoint*> _close_coordinates;
	std::priority_queue<NavMeshPoint*, std::vector<NavMeshPoint*>, std::less<NavMeshPoint*>> _open_coordinates;

	friend NavMeshPoint;
};