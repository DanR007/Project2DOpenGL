#pragma once
#include <glm/vec2.hpp>

#include <vector>
#include <queue>

#include <cmath>

#include "../generators/RTSMapGenerator.h"

class NavMeshRTS;
class Goal;


float GetLengthTurn(const glm::ivec2& dir, const Cell& cell);

struct PathCell
{
	PathCell(PathCell* prev, const Cell& cell)
	{
		_cell = cell;
		_prev = prev;
		_dir = prev->_cell._position - cell._position;
		_length = prev->GetLength() + GetLengthTurn(_dir, cell);
	}
	PathCell(const Cell& cell)
	{
		_cell = cell;
		_prev = nullptr;
		_dir = glm::ivec2(0);
		_length = 0;
	}
	PathCell(PathCell&& c)
	{
		_cell = c._cell;
		_cost = c._cost;
		_length = c._length;
		_prev = c._prev;
		_dir = c._dir;
	}

	bool operator== (PathCell& c)
	{
		return c._cell == _cell;
	}
	bool operator!= (PathCell& c)
	{
		return c._cell != _cell;
	}
	bool operator> (PathCell& c)
	{
		return _cost > c._cost;
	}

	PathCell& operator= (PathCell&& c) noexcept
	{
		_cell = c._cell;
		_cost = c._cost;
		_length = c._length;
		_prev = c._prev;
		_dir = c._dir;

		return *this;
	}
	

	inline float GetCost() const { return _cost; }
	inline float GetLength() const { return _length; }
	inline Cell GetCell() const { return _cell; }
	inline PathCell* GetPrev() { return _prev; }

	void SetCell(const Cell& c) { _cell = c; }
	void SetCost(const float& c) { _cost = c; }
	void SetLength(const float& l) { _length = l; }
	void SetPrev(PathCell* c) { _prev = std::move(c); }
	void SetDistance(const glm::ivec2& point) { _distance = std::sqrtf(std::powf(point.x - _cell._position.x, 2) + std::powf(point.y - _cell._position.y, 2)); }
	void SetDirection(const glm::ivec2& dir) { _dir = dir; }

	void CalculateCost() { _cost = _length + _distance; }
private:
	PathCell* _prev;
	Cell _cell;
	float _cost, _length, _distance;

	glm::ivec2 _dir;
};

class AStarRTS
{
public:
	AStarRTS();
	~AStarRTS();

	Goal* DevelopPath(const glm::ivec2& start, const Cell& target);

	void Clear();

	glm::ivec2 GetNextMapGoal();
private:
	void CollectPath(PathCell* cell);
	bool LocateInMap(const glm::ivec2& pos);

	Cell FindNearestCell(const Cell& target, unsigned short need_id);

	PathCell* GetMinCostCell();

	bool CanStepInto(const glm::ivec2& move, const Cell& next_cell, const Cell& cur_cell);

	static const short unsigned int _count_move_dir = 8;

	const glm::ivec2 _move_dir[_count_move_dir]=
	{
		glm::ivec2(1, 0),
		glm::ivec2(-1, 0),
		glm::ivec2(0, 1),
		glm::ivec2(0, -1),
		glm::ivec2(1, 1),
		glm::ivec2(1, -1),
		glm::ivec2(-1, 1),
		glm::ivec2(-1, -1)
	};

	NavMeshRTS* _nav_mesh;

	std::vector<glm::ivec2> _path;
	std::vector<PathCell*> _close_cells;
	std::vector<PathCell*> _open_cells;
};