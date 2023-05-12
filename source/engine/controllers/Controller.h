#pragma once

#include <memory>

#include <glm/vec2.hpp>


class Unit;
class AStarRTS;
class Goal;

struct Cell;

const glm::vec2 right_vector = glm::vec2(1.f, 0.f);
const glm::vec2 up_vector = glm::vec2(0.f, 1.f);

class Controller
{
public:
	Controller(Unit* controlledPawn, const float moveSpeed);
	Controller(const float moveSpeed);
	Controller();

	virtual ~Controller();
	virtual void Move(float deltaTime);

	void SetNewGoal(const glm::ivec2& map_coord);
	void SetMoveSpeed(const float move_speed) { _move_speed = move_speed; }

	virtual void ChangeMoveVector(glm::vec2 inputVector);
	void ChangeGoalPositionWindow(const glm::vec2 offset) { _goal += offset; }

	inline glm::vec2 GetMoveValue() { return _move_vector; }
	glm::vec2 GetGoal() const { return _goal; }
	glm::ivec2 GetMapGoal() const { return _goal_int; }

	bool GetPathComplete() { return _complete_path; }

	void MakePathForGoal(const Cell& goal, const glm::ivec2& move_from);
protected:
	bool is_pause = false;
	bool _complete_path = true;

	float _move_speed;

	glm::vec2 _move_vector = glm::vec2(0.f);
	glm::vec2 _move_value  = glm::vec2(0.f);

	glm::ivec2 _goal_int;
	glm::vec2 _goal;

	Unit* _controlled_pawn;
	AStarRTS* _a_star;
private:
	
};