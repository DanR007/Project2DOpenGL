#pragma once 

#include <glm/vec2.hpp>

#include <cmath>
#include <vector>

namespace Game
{
	class Actor;
}

class AStar
{
	enum EDirection
	{
		ED_Up, ED_Down, ED_Right, ED_Left,
		ED_UpLeft, ED_UpRight, ED_DownLeft,
		ED_DownRight, ED_Zero
	};
	struct Vector2
	{
		Vector2() : _pos(glm::vec2(0.f)), _dir(ED_Zero) {}
		Vector2(const glm::vec2& pos) : _pos(pos), _dir(ED_Zero) {}
		Vector2(const glm::vec2& pos, const EDirection& dir) : _pos(pos), _dir(dir) {}
		
		void SetCost(const float cost) { _cost = cost; }
		float GetCost() { return _cost; }

		bool operator==(const Vector2& vec)
		{
			return vec._pos == _pos;
		}

		glm::vec2 _pos;
		EDirection _dir;
	private:
		float _cost = FLT_MAX;
	};
public:
	AStar() {}
	glm::vec2 DevelopPath(const glm::vec2& position, const glm::vec2& target, Game::Actor* actor);
	glm::vec2 GetMoveVector();
private:
	inline float SquareDistance(const glm::vec2& first, const glm::vec2& second) const
	{
		return (float)std::pow(first.x - second.x, 2) + (float)std::pow(first.y - second.y, 2);
	}
	inline float Distance(const glm::vec2& first, const glm::vec2& second) const
	{
		return (float)std::sqrt(std::pow(first.x - second.x, 2) + std::pow(first.y - second.y, 2));
	}
	inline float SquareLength(const glm::vec2& vec) const
	{
		return (float)std::pow(vec.x , 2) + (float)std::pow(vec.y, 2);
	}
	inline float Length(const glm::vec2& vec) const
	{
		return (float)std::sqrt(std::pow(vec.x, 2) + std::pow(vec.y, 2));
	}
	inline float DistanceInTurns(const glm::vec2& cell) const
	{
		return std::abs(cell.x - _target.x) + std::abs(cell.y - _target.y);
	}

	void ChoiceSmallestCost(Vector2& smallest_position);
	glm::vec2 MakePathToPlayer(Vector2 pos_algorithm);

	glm::vec2 _position, _target;
	Vector2 _next_position_algorithm;
	Vector2 _move_vector;

	const size_t c_count_step = 8;
	std::vector<glm::vec2> _steps = { glm::vec2(-1.f, -1.f), glm::vec2(0.f, -1.f), glm::vec2(-1.f, 0.f), glm::vec2(1.f, 1.f),
								glm::vec2(0.f, 1.f), glm::vec2(1.f, 0.f), glm::vec2(-1.f, 1.f), glm::vec2(1.f, -1.f) };
	const EDirection _steps_direction[8] = {ED_UpRight, ED_Up, ED_Right, ED_DownLeft, ED_Left, ED_Down, ED_DownRight, ED_UpLeft};

	std::vector<glm::vec2> _path;
	std::vector<Vector2> _closed_coordinates;
	std::vector<Vector2> _open_coordinates;
};